/* HASH CRC-32:0x6e51d531 */
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
#ifndef GUARD_LIBC_AUTO_LIBINTL_H
#define GUARD_LIBC_AUTO_LIBINTL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <libintl.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) char *NOTHROW_NCX(LIBDCALL libd_dcgettext)(char const *domainname, char const *msgid, int category);
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) char *NOTHROW_NCX(LIBDCALL libd_dgettext)(char const *domainname, char const *msgid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) char *NOTHROW_NCX(LIBCCALL libc_dgettext)(char const *domainname, char const *msgid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(1) char *NOTHROW_NCX(LIBDCALL libd_gettext)(char const *msgid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(1) char *NOTHROW_NCX(LIBCCALL libc_gettext)(char const *msgid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(1) __ATTR_FORMAT_ARG(2) char *NOTHROW_NCX(LIBDCALL libd_ngettext)(char const *msgid_singular, char const *msgid_plural, ulongptr_t n);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(1) __ATTR_FORMAT_ARG(2) char *NOTHROW_NCX(LIBCCALL libc_ngettext)(char const *msgid_singular, char const *msgid_plural, ulongptr_t n);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *NOTHROW_NCX(LIBDCALL libd_dngettext)(char const *domainname, char const *msgid_singular, char const *msgid_plural, ulongptr_t n);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *NOTHROW_NCX(LIBCCALL libc_dngettext)(char const *domainname, char const *msgid_singular, char const *msgid_plural, ulongptr_t n);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *NOTHROW_NCX(LIBDCALL libd_dcngettext)(char const *domainname, char const *msgid_singular, char const *msgid_plural, ulongptr_t n, int category);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *NOTHROW_NCX(LIBCCALL libc_dcngettext)(char const *domainname, char const *msgid_singular, char const *msgid_plural, ulongptr_t n, int category);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF char *NOTHROW_NCX(LIBDCALL libd_textdomain)(char const *domainname);
INTDEF char *NOTHROW_NCX(LIBDCALL libd_bindtextdomain)(char const *domainname, char const *dirname);
INTDEF char *NOTHROW_NCX(LIBDCALL libd_bind_textdomain_codeset)(char const *domainname, char const *codeset);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_LIBINTL_H */
