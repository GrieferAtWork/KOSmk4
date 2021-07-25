/* HASH CRC-32:0xd680a50a */
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
#ifndef GUARD_LIBC_AUTO_LIBINTL_C
#define GUARD_LIBC_AUTO_LIBINTL_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/libintl.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/crt/locale.h>
INTERN ATTR_SECTION(".text.crt.l10n") ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) char *
NOTHROW_NCX(LIBCCALL libc_dgettext)(char const *domainname,
                                    char const *msgid) {
	return libc_dcgettext(domainname, msgid, __LC_MESSAGES);
}
INTERN ATTR_SECTION(".text.crt.l10n") ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(1) char *
NOTHROW_NCX(LIBCCALL libc_gettext)(char const *msgid) {
	return libc_dgettext(NULL, msgid);
}
INTERN ATTR_SECTION(".text.crt.l10n") ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(1) __ATTR_FORMAT_ARG(2) char *
NOTHROW_NCX(LIBCCALL libc_ngettext)(char const *msgid_singular,
                                    char const *msgid_plural,
                                    ulongptr_t n) {
	return libc_dgettext(NULL, (n) == 1 ? msgid_singular : msgid_plural);
}
INTERN ATTR_SECTION(".text.crt.l10n") ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *
NOTHROW_NCX(LIBCCALL libc_dngettext)(char const *domainname,
                                     char const *msgid_singular,
                                     char const *msgid_plural,
                                     ulongptr_t n) {
	return libc_dgettext(domainname, (n) == 1 ? msgid_singular : msgid_plural);
}
INTERN ATTR_SECTION(".text.crt.l10n") ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *
NOTHROW_NCX(LIBCCALL libc_dcngettext)(char const *domainname,
                                      char const *msgid_singular,
                                      char const *msgid_plural,
                                      ulongptr_t n,
                                      int category) {
	return libc_dcgettext(domainname, (n) == 1 ? msgid_singular : msgid_plural, category);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__dgettext, libc_dgettext);
DEFINE_PUBLIC_ALIAS(dgettext, libc_dgettext);
DEFINE_PUBLIC_ALIAS(gettext, libc_gettext);
DEFINE_PUBLIC_ALIAS(ngettext, libc_ngettext);
DEFINE_PUBLIC_ALIAS(dngettext, libc_dngettext);
DEFINE_PUBLIC_ALIAS(dcngettext, libc_dcngettext);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_LIBINTL_C */
