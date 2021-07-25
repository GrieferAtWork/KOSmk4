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
#ifndef GUARD_LIBC_USER_LIBINTL_C
#define GUARD_LIBC_USER_LIBINTL_C 1

#include "../api.h"
/**/

#include "libintl.h"

DECL_BEGIN



/*[[[head:libc_dcgettext,hash:CRC-32=0x737222dd]]]*/
INTERN ATTR_SECTION(".text.crt.l10n") ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) char *
NOTHROW_NCX(LIBCCALL libc_dcgettext)(char const *domainname,
                                     char const *msgid,
                                     int category)
/*[[[body:libc_dcgettext]]]*/
/*AUTO*/{
	/* Generic no-op that works, but doesn't actually support languages */
	COMPILER_IMPURE();
	(void)domainname;
	(void)category;
	return (char *)msgid;
}
/*[[[end:libc_dcgettext]]]*/




/*[[[head:libc_textdomain,hash:CRC-32=0x9128e422]]]*/
INTERN ATTR_SECTION(".text.crt.l10n") char *
NOTHROW_NCX(LIBCCALL libc_textdomain)(char const *domainname)
/*[[[body:libc_textdomain]]]*/
/*AUTO*/{
	(void)domainname;
	CRT_UNIMPLEMENTEDF("textdomain(%q)", domainname); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_textdomain]]]*/

/*[[[head:libc_bindtextdomain,hash:CRC-32=0xec4b401b]]]*/
INTERN ATTR_SECTION(".text.crt.l10n") char *
NOTHROW_NCX(LIBCCALL libc_bindtextdomain)(char const *domainname,
                                          char const *dirname)
/*[[[body:libc_bindtextdomain]]]*/
/*AUTO*/{
	(void)domainname;
	(void)dirname;
	CRT_UNIMPLEMENTEDF("bindtextdomain(%q, %q)", domainname, dirname); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_bindtextdomain]]]*/

/*[[[head:libc_bind_textdomain_codeset,hash:CRC-32=0xbad95f1a]]]*/
INTERN ATTR_SECTION(".text.crt.l10n") char *
NOTHROW_NCX(LIBCCALL libc_bind_textdomain_codeset)(char const *domainname,
                                                   char const *codeset)
/*[[[body:libc_bind_textdomain_codeset]]]*/
/*AUTO*/{
	(void)domainname;
	(void)codeset;
	CRT_UNIMPLEMENTEDF("bind_textdomain_codeset(%q, %q)", domainname, codeset); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_bind_textdomain_codeset]]]*/

/*[[[start:exports,hash:CRC-32=0xa18aa25b]]]*/
DEFINE_PUBLIC_ALIAS(__dcgettext, libc_dcgettext);
DEFINE_PUBLIC_ALIAS(dcgettext, libc_dcgettext);
DEFINE_PUBLIC_ALIAS(textdomain, libc_textdomain);
DEFINE_PUBLIC_ALIAS(bindtextdomain, libc_bindtextdomain);
DEFINE_PUBLIC_ALIAS(bind_textdomain_codeset, libc_bind_textdomain_codeset);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_LIBINTL_C */
