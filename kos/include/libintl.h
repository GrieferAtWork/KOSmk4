/* HASH CRC-32:0xb164c0fa */
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
/* (#) Portability: EMX kLIBC     (/libc/include/libintl.h) */
/* (#) Portability: GNU C Library (/intl/libintl.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/libintl.h) */
/* (#) Portability: diet libc     (/include/libintl.h) */
/* (#) Portability: libc6         (/include/libintl.h) */
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
#include <asm/crt/locale.h>
#include <hybrid/typecore.h>

#define __USE_GNU_GETTEXT 1 /* We're emulating glibc's <libintl.h> */
#define __GNU_GETTEXT_SUPPORTED_REVISION(major) ((major) == 0 ? 1 : -1)

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __LC_MESSAGES
#define __LC_MESSAGES 0
#endif /* !__LC_MESSAGES */
#ifdef __CRT_HAVE_dcgettext
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,dcgettext,(char const *__domainname, char const *__msgid, int __category),{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __category); })
#elif defined(__CRT_HAVE___dcgettext)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __category); })
#else /* ... */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL dcgettext)(char const *__domainname, char const *__msgid, int __category) { return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __category); }
#endif /* !... */
#ifdef __CRT_HAVE_dgettext
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,dgettext,(char const *__domainname, char const *__msgid),{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __LC_MESSAGES); })
#elif defined(__CRT_HAVE___dgettext)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,dgettext,(char const *__domainname, char const *__msgid),__dgettext,{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __LC_MESSAGES); })
#else /* ... */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL dgettext)(char const *__domainname, char const *__msgid) { return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __LC_MESSAGES); }
#endif /* !... */
#ifdef __CRT_HAVE_gettext
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_FORMAT_ARG(1),char *,__NOTHROW_NCX,gettext,(char const *__msgid),{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__NULLPTR, __msgid, __NULLPTR, 1, __LC_MESSAGES); })
#else /* __CRT_HAVE_gettext */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_FORMAT_ARG(1) char *__NOTHROW_NCX(__LIBCCALL gettext)(char const *__msgid) { return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__NULLPTR, __msgid, __NULLPTR, 1, __LC_MESSAGES); }
#endif /* !__CRT_HAVE_gettext */
#ifdef __CRT_HAVE_ngettext
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(1) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,ngettext,(char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n),{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__NULLPTR, __msgid_singular, __msgid_plural, __n, __LC_MESSAGES); })
#else /* __CRT_HAVE_ngettext */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(1) __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL ngettext)(char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n) { return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__NULLPTR, __msgid_singular, __msgid_plural, __n, __LC_MESSAGES); }
#endif /* !__CRT_HAVE_ngettext */
#ifdef __CRT_HAVE_dngettext
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,dngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n),{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid_singular, __msgid_plural, __n, __LC_MESSAGES); })
#else /* __CRT_HAVE_dngettext */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *__NOTHROW_NCX(__LIBCCALL dngettext)(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n) { return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid_singular, __msgid_plural, __n, __LC_MESSAGES); }
#endif /* !__CRT_HAVE_dngettext */
#ifdef __CRT_HAVE_dcngettext
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(dcngettext, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *__NOTHROW_NCX(__LIBCCALL dcngettext)(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dcngettext))(__domainname, __msgid_singular, __msgid_plural, __n, __category); })
#endif /* !__CRT_HAVE_dcngettext */
__CDECLARE_OPT(,char *,__NOTHROW_NCX,textdomain,(char const *__domainname),(__domainname))
__CDECLARE_OPT(,char *,__NOTHROW_NCX,bindtextdomain,(char const *__domainname, char const *__dirname),(__domainname,__dirname))
__CDECLARE_OPT(,char *,__NOTHROW_NCX,bind_textdomain_codeset,(char const *__domainname, char const *__codeset),(__domainname,__codeset))
#ifdef __CRT_HAVE_dgettext
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__dgettext,(char const *__domainname, char const *__msgid),dgettext,{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __LC_MESSAGES); })
#elif defined(__CRT_HAVE___dgettext)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__dgettext,(char const *__domainname, char const *__msgid),{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __LC_MESSAGES); })
#else /* ... */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL __dgettext)(char const *__domainname, char const *__msgid) { return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __LC_MESSAGES); }
#endif /* !... */
#ifdef __CRT_HAVE_dcgettext
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __category); })
#elif defined(__CRT_HAVE___dcgettext)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__dcgettext,(char const *__domainname, char const *__msgid, int __category),{ return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __category); })
#else /* ... */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dcngettext_defined
#define __local___localdep_dcngettext_defined
#ifdef __CRT_HAVE_dcngettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,__NOTHROW_NCX,__localdep_dcngettext,(char const *__domainname, char const *__msgid_singular, char const *__msgid_plural, __ULONGPTR_TYPE__ __n, int __category),dcngettext,(__domainname,__msgid_singular,__msgid_plural,__n,__category))
#else /* __CRT_HAVE_dcngettext */
__NAMESPACE_LOCAL_END
#include <libc/local/libintl/dcngettext.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dcngettext __LIBC_LOCAL_NAME(dcngettext)
#endif /* !__CRT_HAVE_dcngettext */
#endif /* !__local___localdep_dcngettext_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) __ATTR_FORMAT_ARG(2) char *__NOTHROW_NCX(__LIBCCALL __dcgettext)(char const *__domainname, char const *__msgid, int __category) { return (__NAMESPACE_LOCAL_SYM __localdep_dcngettext)(__domainname, __msgid, __NULLPTR, 1, __category); }
#endif /* !... */

/* If appropriate, provide macro optimizations of the above functions */
#if (!defined(__OPTIMIZE_SIZE__) && (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)))
#ifndef __CRT_HAVE_dcngettext
#define dcngettext(domainname, msgid_singular, msgid_plural, n, category) ((char *)((n) == 1 ? (msgid_singular) : (msgid_plural)))
#define dngettext(domainname, msgid_singular, msgid_plural, n)            ((char *)((n) == 1 ? (msgid_singular) : (msgid_plural)))
#define ngettext(msgid_singular, msgid_plural, n)                         ((char *)((n) == 1 ? (msgid_singular) : (msgid_plural)))
#define dgettext(domainname, msgid)                                       ((char *)(msgid))
#define gettext(msgid)                                                    ((char *)(msgid))
#else /* !__CRT_HAVE_dcngettext */
#if 0 /* Let's not bloat program assembly too much ;) */
#define dngettext(domainname, msgid_singular, msgid_plural, n) \
	dcngettext(domainname, msgid_singular, msgid_plural, n, __LC_MESSAGES)
#define dgettext(domainname, msgid) \
	dcngettext(domainname, msgid, __NULLPTR, 1, __LC_MESSAGES)
#define ngettext(msgid_singular, msgid_plural, n) \
	dcngettext(__NULLPTR, msgid_singular, msgid_plural, n, __LC_MESSAGES)
#define gettext(msgid) \
	dcngettext(__NULLPTR, msgid, __NULLPTR, 1, __LC_MESSAGES)
#endif
#endif /* __CRT_HAVE_dcngettext */
#define __dcngettext(domainname, msgid_singular, msgid_plural, n, category) \
	dcngettext(domainname, msgid_singular, msgid_plural, n, category)
#define __dgettext(domainname, msgid) \
	dgettext(domainname, msgid)
#endif /* !__OPTIMIZE_SIZE__ && (!__cplusplus || __USE_CTYPE_MACROS) */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LIBINTL_H */
