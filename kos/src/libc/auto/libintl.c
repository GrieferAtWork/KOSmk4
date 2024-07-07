/* HASH CRC-32:0xf59d57f1 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_LIBINTL_C
#define GUARD_LIBC_AUTO_LIBINTL_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/libintl.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/crt/locale.h>
#ifndef __LC_MESSAGES
#define __LC_MESSAGES 0
#endif /* !__LC_MESSAGES */
INTERN ATTR_SECTION(".text.crt.i18n") ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) __ATTR_FORMAT_ARG(2) char *
NOTHROW_NCX(LIBCCALL libc_dcgettext)(char const *domainname,
                                     char const *msgid,
                                     int category) {
	return libc_dcngettext(domainname, msgid, NULL, 1, category);
}
#include <asm/crt/locale.h>
#ifndef __LC_MESSAGES
#define __LC_MESSAGES 0
#endif /* !__LC_MESSAGES */
INTERN ATTR_SECTION(".text.crt.i18n") ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) __ATTR_FORMAT_ARG(2) char *
NOTHROW_NCX(LIBCCALL libc_dgettext)(char const *domainname,
                                    char const *msgid) {
	return libc_dcngettext(domainname, msgid, NULL, 1, __LC_MESSAGES);
}
#include <asm/crt/locale.h>
#ifndef __LC_MESSAGES
#define __LC_MESSAGES 0
#endif /* !__LC_MESSAGES */
INTERN ATTR_SECTION(".text.crt.i18n") ATTR_PURE WUNUSED ATTR_IN_OPT(1) __ATTR_FORMAT_ARG(1) char *
NOTHROW_NCX(LIBCCALL libc_gettext)(char const *msgid) {
	return libc_dcngettext(NULL, msgid, NULL, 1, __LC_MESSAGES);
}
#include <asm/crt/locale.h>
#ifndef __LC_MESSAGES
#define __LC_MESSAGES 0
#endif /* !__LC_MESSAGES */
INTERN ATTR_SECTION(".text.crt.i18n") ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) __ATTR_FORMAT_ARG(1) __ATTR_FORMAT_ARG(2) char *
NOTHROW_NCX(LIBCCALL libc_ngettext)(char const *msgid_singular,
                                    char const *msgid_plural,
                                    ulongptr_t n) {
	return libc_dcngettext(NULL, msgid_singular, msgid_plural, n, __LC_MESSAGES);
}
#include <asm/crt/locale.h>
#ifndef __LC_MESSAGES
#define __LC_MESSAGES 0
#endif /* !__LC_MESSAGES */
INTERN ATTR_SECTION(".text.crt.i18n") ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) ATTR_IN_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *
NOTHROW_NCX(LIBCCALL libc_dngettext)(char const *domainname,
                                     char const *msgid_singular,
                                     char const *msgid_plural,
                                     ulongptr_t n) {
	return libc_dcngettext(domainname, msgid_singular, msgid_plural, n, __LC_MESSAGES);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(__dcgettext,libc_dcgettext,ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) __ATTR_FORMAT_ARG(2),char *,NOTHROW_NCX,LIBCCALL,(char const *domainname, char const *msgid, int category),(domainname,msgid,category));
DEFINE_PUBLIC_ALIAS_P(dcgettext,libc_dcgettext,ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) __ATTR_FORMAT_ARG(2),char *,NOTHROW_NCX,LIBCCALL,(char const *domainname, char const *msgid, int category),(domainname,msgid,category));
DEFINE_PUBLIC_ALIAS_P(__dgettext,libc_dgettext,ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) __ATTR_FORMAT_ARG(2),char *,NOTHROW_NCX,LIBCCALL,(char const *domainname, char const *msgid),(domainname,msgid));
DEFINE_PUBLIC_ALIAS_P(dgettext,libc_dgettext,ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) __ATTR_FORMAT_ARG(2),char *,NOTHROW_NCX,LIBCCALL,(char const *domainname, char const *msgid),(domainname,msgid));
DEFINE_PUBLIC_ALIAS_P(__gettext,libc_gettext,ATTR_PURE WUNUSED ATTR_IN_OPT(1) __ATTR_FORMAT_ARG(1),char *,NOTHROW_NCX,LIBCCALL,(char const *msgid),(msgid));
DEFINE_PUBLIC_ALIAS_P(gettext,libc_gettext,ATTR_PURE WUNUSED ATTR_IN_OPT(1) __ATTR_FORMAT_ARG(1),char *,NOTHROW_NCX,LIBCCALL,(char const *msgid),(msgid));
DEFINE_PUBLIC_ALIAS_P(ngettext,libc_ngettext,ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) __ATTR_FORMAT_ARG(1) __ATTR_FORMAT_ARG(2),char *,NOTHROW_NCX,LIBCCALL,(char const *msgid_singular, char const *msgid_plural, ulongptr_t n),(msgid_singular,msgid_plural,n));
DEFINE_PUBLIC_ALIAS_P(dngettext,libc_dngettext,ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) ATTR_IN_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3),char *,NOTHROW_NCX,LIBCCALL,(char const *domainname, char const *msgid_singular, char const *msgid_plural, ulongptr_t n),(domainname,msgid_singular,msgid_plural,n));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_LIBINTL_C */
