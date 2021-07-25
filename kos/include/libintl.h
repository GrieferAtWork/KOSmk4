/* HASH CRC-32:0xc0660248 */
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
/* (#) Portability: GNU C Library (/intl/libintl.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/libintl.h) */
/* (#) Portability: diet libc     (/include/libintl.h) */
/* (#) Portability: musl libc     (/include/libintl.h) */
/* (#) Portability: uClibc        (/include/libintl.h) */
#ifndef _LIBINTL_H
#define _LIBINTL_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/crt/locale.h>
#include <hybrid/typecore.h>

#define __USE_GNU_GETTEXT 1 /* We're emulating glibc's <libintrl.h> */
#define __GNU_GETTEXT_SUPPORTED_REVISION(major) ((major) == 0 ? 1 : -1)

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_dcgettext
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,dcgettext,(char const *__domainname, char const *__msgid, int __category),(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(dcgettext, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL dcgettext)(char const *__domainname, char const *__msgid, int __category) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dcgettext))(__domainname, __msgid, __category); })
#endif /* !... */
#if defined(__CRT_HAVE_dgettext) && defined(__LC_MESSAGES)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,dgettext,(char const *__domainname, char const *__msgid),{ return (__NAMESPACE_LOCAL_SYM __localdep_dcgettext)(__domainname, __msgid, __LC_MESSAGES); })
#elif defined(__CRT_HAVE_dgettext)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,dgettext,(char const *__domainname, char const *__msgid),(__domainname,__msgid))
#elif defined(__CRT_HAVE___dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,dgettext,(char const *__domainname, char const *__msgid),__dgettext,(__domainname,__msgid))
#elif defined(__LC_MESSAGES)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL dgettext)(char const *__domainname, char const *__msgid) { return (__NAMESPACE_LOCAL_SYM __localdep_dcgettext)(__domainname, __msgid, __LC_MESSAGES); }
#endif /* ... */
#if defined(__CRT_HAVE_gettext) && (defined(__CRT_HAVE_dgettext) || defined(__CRT_HAVE___dgettext) || defined(__LC_MESSAGES))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dgettext_defined
#define __local___localdep_dgettext_defined 1
#if defined(__CRT_HAVE_dgettext) && defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,{ return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); })
#elif defined(__CRT_HAVE_dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,(__domainname,__msgid))
#elif defined(__CRT_HAVE___dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),__dgettext,(__domainname,__msgid))
#elif defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL __localdep_dgettext)(char const *__domainname, char const *__msgid) { return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); }
#else /* ... */
#undef __local___localdep_dgettext_defined
#endif /* !... */
#endif /* !__local___localdep_dgettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(1),char *,__NOTHROW_NCX,gettext,(char const *__msgid),{ return (__NAMESPACE_LOCAL_SYM __localdep_dgettext)(__NULLPTR, __msgid); })
#elif defined(__CRT_HAVE_gettext)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(1),char *,__NOTHROW_NCX,gettext,(char const *__msgid),(__msgid))
#elif defined(__CRT_HAVE_dgettext) || defined(__CRT_HAVE___dgettext) || defined(__LC_MESSAGES)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dgettext_defined
#define __local___localdep_dgettext_defined 1
#if defined(__CRT_HAVE_dgettext) && defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,{ return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); })
#elif defined(__CRT_HAVE_dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,(__domainname,__msgid))
#elif defined(__CRT_HAVE___dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),__dgettext,(__domainname,__msgid))
#elif defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL __localdep_dgettext)(char const *__domainname, char const *__msgid) { return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); }
#else /* ... */
#undef __local___localdep_dgettext_defined
#endif /* !... */
#endif /* !__local___localdep_dgettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(1) char *__NOTHROW_NCX(__LIBCCALL gettext)(char const *__msgid) { return (__NAMESPACE_LOCAL_SYM __localdep_dgettext)(__NULLPTR, __msgid); }
#endif /* ... */
#if defined(__CRT_HAVE_ngettext) && (defined(__CRT_HAVE_dgettext) || defined(__CRT_HAVE___dgettext) || defined(__LC_MESSAGES))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dgettext_defined
#define __local___localdep_dgettext_defined 1
#if defined(__CRT_HAVE_dgettext) && defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,{ return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); })
#elif defined(__CRT_HAVE_dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,(__domainname,__msgid))
#elif defined(__CRT_HAVE___dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),__dgettext,(__domainname,__msgid))
#elif defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL __localdep_dgettext)(char const *__domainname, char const *__msgid) { return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); }
#else /* ... */
#undef __local___localdep_dgettext_defined
#endif /* !... */
#endif /* !__local___localdep_dgettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(1) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,ngettext,(char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n),{ return (__NAMESPACE_LOCAL_SYM __localdep_dgettext)(__NULLPTR, (__n) == 1 ? __msgid_singular : __msgid_plural); })
#elif defined(__CRT_HAVE_ngettext)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(1) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,ngettext,(char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n),(__msgid_singular,__msgid_plural,__n))
#elif defined(__CRT_HAVE_dgettext) || defined(__CRT_HAVE___dgettext) || defined(__LC_MESSAGES)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dgettext_defined
#define __local___localdep_dgettext_defined 1
#if defined(__CRT_HAVE_dgettext) && defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,{ return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); })
#elif defined(__CRT_HAVE_dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,(__domainname,__msgid))
#elif defined(__CRT_HAVE___dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),__dgettext,(__domainname,__msgid))
#elif defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL __localdep_dgettext)(char const *__domainname, char const *__msgid) { return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); }
#else /* ... */
#undef __local___localdep_dgettext_defined
#endif /* !... */
#endif /* !__local___localdep_dgettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(1) __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL ngettext)(char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n) { return (__NAMESPACE_LOCAL_SYM __localdep_dgettext)(__NULLPTR, (__n) == 1 ? __msgid_singular : __msgid_plural); }
#endif /* ... */
#if defined(__CRT_HAVE_dngettext) && (defined(__CRT_HAVE_dgettext) || defined(__CRT_HAVE___dgettext) || defined(__LC_MESSAGES))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dgettext_defined
#define __local___localdep_dgettext_defined 1
#if defined(__CRT_HAVE_dgettext) && defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,{ return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); })
#elif defined(__CRT_HAVE_dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,(__domainname,__msgid))
#elif defined(__CRT_HAVE___dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),__dgettext,(__domainname,__msgid))
#elif defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL __localdep_dgettext)(char const *__domainname, char const *__msgid) { return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); }
#else /* ... */
#undef __local___localdep_dgettext_defined
#endif /* !... */
#endif /* !__local___localdep_dgettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,dngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n),{ return (__NAMESPACE_LOCAL_SYM __localdep_dgettext)(__domainname, (__n) == 1 ? __msgid_singular : __msgid_plural); })
#elif defined(__CRT_HAVE_dngettext)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,dngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n),(__domainname,__msgid_singular,__msgid_plural,__n))
#elif defined(__CRT_HAVE_dgettext) || defined(__CRT_HAVE___dgettext) || defined(__LC_MESSAGES)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dgettext_defined
#define __local___localdep_dgettext_defined 1
#if defined(__CRT_HAVE_dgettext) && defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,{ return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); })
#elif defined(__CRT_HAVE_dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,(__domainname,__msgid))
#elif defined(__CRT_HAVE___dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),__dgettext,(__domainname,__msgid))
#elif defined(__LC_MESSAGES)
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL __localdep_dgettext)(char const *__domainname, char const *__msgid) { return __localdep_dcgettext(__domainname, __msgid, __LC_MESSAGES); }
#else /* ... */
#undef __local___localdep_dgettext_defined
#endif /* !... */
#endif /* !__local___localdep_dgettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *__NOTHROW_NCX(__LIBCCALL dngettext)(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n) { return (__NAMESPACE_LOCAL_SYM __localdep_dgettext)(__domainname, (__n) == 1 ? __msgid_singular : __msgid_plural); }
#endif /* ... */
#ifdef __CRT_HAVE_dcngettext
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),{ return (__NAMESPACE_LOCAL_SYM __localdep_dcgettext)(__domainname, (__n) == 1 ? __msgid_singular : __msgid_plural, __category); })
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *__NOTHROW_NCX(__LIBCCALL dcngettext)(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category) { return (__NAMESPACE_LOCAL_SYM __localdep_dcgettext)(__domainname, (__n) == 1 ? __msgid_singular : __msgid_plural, __category); }
#endif /* !__CRT_HAVE_dcngettext */
__CDECLARE_OPT(,char *,__NOTHROW_NCX,textdomain,(char const *__domainname),(__domainname))
__CDECLARE_OPT(,char *,__NOTHROW_NCX,bindtextdomain,(char const *__domainname, char const *__dirname),(__domainname,__dirname))
__CDECLARE_OPT(,char *,__NOTHROW_NCX,bind_textdomain_codeset,(char const *__domainname, char const *__codeset),(__domainname,__codeset))
#if defined(__CRT_HAVE_dgettext) && defined(__LC_MESSAGES)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__NAMESPACE_LOCAL_END
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__dgettext,(char const *__domainname, char const *__msgid),dgettext,{ return (__NAMESPACE_LOCAL_SYM __localdep_dcgettext)(__domainname, __msgid, __LC_MESSAGES); })
#elif defined(__CRT_HAVE_dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__dgettext,(char const *__domainname, char const *__msgid),dgettext,(__domainname,__msgid))
#elif defined(__CRT_HAVE___dgettext)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__dgettext,(char const *__domainname, char const *__msgid),(__domainname,__msgid))
#elif defined(__LC_MESSAGES)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcgettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL __dgettext)(char const *__domainname, char const *__msgid) { return (__NAMESPACE_LOCAL_SYM __localdep_dcgettext)(__domainname, __msgid, __LC_MESSAGES); }
#endif /* ... */
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__dcgettext,(char const *__domainname, char const *__msgid, int __category),(__domainname,__msgid,__category))
#else /* ... */
#include <libc/local/libintl/dcgettext.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL __dcgettext)(char const *__domainname, char const *__msgid, int __category) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dcgettext))(__domainname, __msgid, __category); }
#endif /* !... */

/* If appropriate, provide macro optimizations of the above functions */
#if (!defined(__OPTIMIZE_SIZE__) && (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)))
#define dcngettext(domainname, msgid_singular, msgid_plural, n, category) dcgettext(domainname, (n) == 1 ? msgid_singular : msgid_plural, category)
#ifdef __LC_MESSAGES
#define dgettext(domainname, msgid) dcgettext(domainname, msgid, __LC_MESSAGES)
#endif /* __LC_MESSAGES */
#if defined(dgettext) || defined(__CRT_HAVE_dgettext) || defined(__CRT_HAVE___dgettext) || defined(__LC_MESSAGES)
#define dngettext(domainname, msgid_singular, msgid_plural, n) dgettext(domainname, (n) == 1 ? msgid_singular : msgid_plural)
#define gettext(msgid)                                         dgettext(__NULLPTR, msgid)
#endif /* dgettext || __CRT_HAVE_dgettext || __CRT_HAVE___dgettext || __LC_MESSAGES */
#if defined(gettext) || defined(__CRT_HAVE_gettext) || defined(__CRT_HAVE_dgettext) || defined(__CRT_HAVE___dgettext) || defined(__LC_MESSAGES)
#define ngettext(msgid_singular, msgid_plural, n) gettext((n) == 1 ? msgid_singular : msgid_plural)
#endif /* gettext || __CRT_HAVE_gettext || __CRT_HAVE_dgettext || __CRT_HAVE___dgettext || __LC_MESSAGES */
#endif /* !__OPTIMIZE_SIZE__ && (!__cplusplus || __USE_CTYPE_MACROS) */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LIBINTL_H */
