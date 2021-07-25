/* HASH CRC-32:0x12c6f3b2 */
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
#ifndef __local_gettext_defined
#define __local_gettext_defined 1
#include <__crt.h>
#include <bits/crt/locale.h>
#if ((defined(__CRT_HAVE_dcgettext) || defined(__CRT_HAVE___dcgettext)) && defined(__LC_MESSAGES)) || defined(__CRT_HAVE_dgettext) || defined(__CRT_HAVE___dgettext)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: dcgettext from libintl */
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#ifdef __CRT_HAVE_dcgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),dcgettext,(__domainname,__msgid,__category))
#elif defined(__CRT_HAVE___dcgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dcgettext,(char const *__domainname, char const *__msgid, int __category),__dcgettext,(__domainname,__msgid,__category))
#else /* ... */
#undef __local___localdep_dcgettext_defined
#endif /* !... */
#endif /* !__local___localdep_dcgettext_defined */
/* Dependency: dgettext from libintl */
#ifndef __local___localdep_dgettext_defined
#define __local___localdep_dgettext_defined 1
#ifdef __CRT_HAVE_dgettext
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),dgettext,(__domainname,__msgid))
#elif defined(__CRT_HAVE___dgettext)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2),char *,__NOTHROW_NCX,__localdep_dgettext,(char const *__domainname, char const *__msgid),__dgettext,(__domainname,__msgid))
#else /* ... */
#undef __local___localdep_dgettext_defined
#endif /* !... */
#endif /* !__local___localdep_dgettext_defined */
__LOCAL_LIBC(gettext) __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gettext))(char const *__msgid) {
#if (defined(__CRT_HAVE_dcgettext) || defined(__CRT_HAVE___dcgettext)) && defined(__LC_MESSAGES)
	return __localdep_dcgettext(__NULLPTR, __msgid, __LC_MESSAGES);
#else /* (__CRT_HAVE_dcgettext || __CRT_HAVE___dcgettext) && __LC_MESSAGES */
	return __localdep_dgettext(__NULLPTR, __msgid);
#endif /* (!__CRT_HAVE_dcgettext && !__CRT_HAVE___dcgettext) || !__LC_MESSAGES */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gettext_defined
#define __local___localdep_gettext_defined 1
#define __localdep_gettext __LIBC_LOCAL_NAME(gettext)
#endif /* !__local___localdep_gettext_defined */
#else /* ((__CRT_HAVE_dcgettext || __CRT_HAVE___dcgettext) && __LC_MESSAGES) || __CRT_HAVE_dgettext || __CRT_HAVE___dgettext */
#undef __local_gettext_defined
#endif /* ((!__CRT_HAVE_dcgettext && !__CRT_HAVE___dcgettext) || !__LC_MESSAGES) && !__CRT_HAVE_dgettext && !__CRT_HAVE___dgettext */
#endif /* !__local_gettext_defined */
