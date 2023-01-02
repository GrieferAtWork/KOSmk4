/* HASH CRC-32:0x37cfe7e4 */
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
#ifndef GUARD_LIBC_USER_LIBINTL_H
#define GUARD_LIBC_USER_LIBINTL_H 1

#include "../api.h"
#include "../auto/libintl.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <libintl.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) ATTR_IN_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *NOTHROW_NCX(LIBCCALL libc_dcngettext)(char const *domainname, char const *msgid_singular, char const *msgid_plural, ulongptr_t n, int category);
INTDEF char *NOTHROW_NCX(LIBCCALL libc_textdomain)(char const *domainname);
INTDEF char *NOTHROW_NCX(LIBCCALL libc_bindtextdomain)(char const *domainname, char const *dirname);
INTDEF char *NOTHROW_NCX(LIBCCALL libc_bind_textdomain_codeset)(char const *domainname, char const *codeset);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_LIBINTL_H */
