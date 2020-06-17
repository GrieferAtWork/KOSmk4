/* HASH CRC-32:0xebabf12d */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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
/* Set and/or return the current locale */
INTDEF char *NOTHROW_NCX(LIBCCALL libc_setlocale)(int category, char const *locale);
/* Return the numeric/monetary information for the current locale */
INTDEF struct lconv *NOTHROW_NCX(LIBCCALL libc_localeconv)(void);
/* Return a reference to a data structure representing a set of locale
 * datasets. Unlike for the CATEGORY parameter for `setlocale' the
 * CATEGORY_MASK parameter here uses a single bit for each category,
 * made by OR'ing together LC_*_MASK bits above */
INTDEF locale_t NOTHROW_NCX(LIBCCALL libc_newlocale)(int category_mask, char const *locale, locale_t base);
/* Return a duplicate of the set of locale in DATASET.
 * All usage counters are increased if necessary */
INTDEF locale_t NOTHROW_NCX(LIBCCALL libc_duplocale)(locale_t dataset);
/* Free the data associated with a locale dataset
 * previously returned by a call to `setlocale_r' */
INTDEF void NOTHROW_NCX(LIBCCALL libc_freelocale)(locale_t dataset);
/* Switch the current thread's locale to DATASET.
 * If DATASET is null, instead just return the current setting.
 * The special value LC_GLOBAL_LOCALE is the initial setting
 * for all threads and can also be installed any time, meaning
 * the thread uses the global settings controlled by `setlocale' */
INTDEF locale_t NOTHROW_NCX(LIBCCALL libc_uselocale)(locale_t dataset);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_LOCALE_H */
