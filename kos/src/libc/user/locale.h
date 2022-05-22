/* HASH CRC-32:0x4f1432c0 */
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
#ifndef GUARD_LIBC_USER_LOCALE_H
#define GUARD_LIBC_USER_LOCALE_H 1

#include "../api.h"
#include "../auto/locale.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <locale.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> setlocale(3)
 * Get or set the current locale
 * @param: category: One of `LC_*'
 * @param: locale:   Name of the locale (e.g. "C")
 *                   When `NULL', don't change the locale.
 * @return: * :      The current locale set for `category'
 * @return: NULL:    Error */
INTDEF ATTR_ACCESS_RO_OPT(2) char *NOTHROW_NCX(LIBCCALL libc_setlocale)(int category, char const *locale);
/* >> localeconv(3)
 * Return numeric and monetary information for the current locale */
INTDEF ATTR_RETNONNULL WUNUSED struct lconv *NOTHROW_NCX(LIBCCALL libc_localeconv)(void);
/* >> newlocale(3)
 * @param: category_mask: Set of `LC_*_MASK' */
INTDEF locale_t NOTHROW_NCX(LIBCCALL libc_newlocale)(int category_mask, char const *locale, locale_t base);
/* >> duplocale(3)
 * Duplicate the given locale `dataset' */
INTDEF locale_t NOTHROW_NCX(LIBCCALL libc_duplocale)(locale_t dataset);
/* >> freelocale(3) */
INTDEF void NOTHROW_NCX(LIBCCALL libc_freelocale)(locale_t dataset);
/* >> uselocale(3)
 * Set the calling thread's current default locale to `dataset'
 * @param: dataset: NULL:             Don't change the calling thread's locale
 * @param: dataset: LC_GLOBAL_LOCALE: Use the global locale (s.a. `setlocale(3)')
 * @param: dataset: * :               The new locale to set
 * @return: NULL:             Error
 * @return: LC_GLOBAL_LOCALE: The calling thread uses the global locale (default)
 * @return: * :               The currently used locale */
INTDEF locale_t NOTHROW_NCX(LIBCCALL libc_uselocale)(locale_t dataset);
INTDEF void NOTHROW_NCX(LIBCCALL libc__lock_locales)(void);
INTDEF void NOTHROW_NCX(LIBCCALL libc__unlock_locales)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc__configthreadlocale)(int flag);
INTDEF locale_t NOTHROW_NCX(LIBCCALL libc__get_current_locale)(void);
INTDEF locale_t NOTHROW_NCX(LIBCCALL libc__create_locale)(int category, char const *locale);
INTDEF void NOTHROW_NCX(LIBCCALL libc__free_locale)(locale_t locale);
INTDEF ATTR_ACCESS_RO_OPT(2) char16_t *NOTHROW_NCX(LIBDCALL libd__wsetlocale)(int category, char16_t const *locale);
INTDEF ATTR_ACCESS_RO_OPT(2) char32_t *NOTHROW_NCX(LIBKCALL libc__wsetlocale)(int category, char32_t const *locale);
INTDEF ATTR_ACCESS_RO_OPT(2) locale_t NOTHROW_NCX(LIBDCALL libd__wcreate_locale)(int category, char16_t const *locale);
INTDEF ATTR_ACCESS_RO_OPT(2) locale_t NOTHROW_NCX(LIBKCALL libc__wcreate_locale)(int category, char32_t const *locale);
INTDEF WUNUSED char16_t **NOTHROW_NCX(LIBDCALL libd____lc_locale_name_func)(void);
INTDEF WUNUSED char32_t **NOTHROW_NCX(LIBKCALL libc____lc_locale_name_func)(void);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc____lc_codepage_func)(void);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc____lc_collate_cp_func)(void);
INTDEF WUNUSED void *NOTHROW_NCX(LIBCCALL libc__Gettnames)(void);
INTDEF WUNUSED void *NOTHROW_NCX(LIBDCALL libd__W_Gettnames)(void);
INTDEF WUNUSED void *NOTHROW_NCX(LIBKCALL libc__W_Gettnames)(void);
INTDEF ATTR_ACCESS_RO(3) ATTR_ACCESS_RO(4) ATTR_ACCESS_WRS(1, 2) size_t NOTHROW_NCX(LIBCCALL libc__Strftime)(char *buf, size_t bufsize, char const *format, struct tm const *tms, void *lc_time_arg);
INTDEF ATTR_ACCESS_RO(3) ATTR_ACCESS_RO(4) ATTR_ACCESS_WRS(1, 2) size_t NOTHROW_NCX(LIBDCALL libd__Wcsftime)(char16_t *buf, size_t bufsize, char16_t const *format, struct tm const *tms, void *lc_time_arg);
INTDEF ATTR_ACCESS_RO(3) ATTR_ACCESS_RO(4) ATTR_ACCESS_WRS(1, 2) size_t NOTHROW_NCX(LIBKCALL libc__Wcsftime)(char32_t *buf, size_t bufsize, char32_t const *format, struct tm const *tms, void *lc_time_arg);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_LOCALE_H */
