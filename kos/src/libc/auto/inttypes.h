/* HASH CRC-32:0x120bf7c0 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_INTTYPES_H
#define GUARD_LIBC_AUTO_INTTYPES_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <inttypes.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_CONST intmax_t NOTHROW(LIBCCALL libc_imaxabs)(intmax_t x);
INTDEF ATTR_CONST imaxdiv_t NOTHROW(LIBCCALL libc_imaxdiv)(intmax_t numer, intmax_t denom);
INTDEF ATTR_PURE NONNULL((1)) intmax_t NOTHROW_NCX(LIBCCALL libc_strtoimax)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_PURE NONNULL((1)) uintmax_t NOTHROW_NCX(LIBCCALL libc_strtoumax)(char const *__restrict nptr, char **endptr, int base);
INTDEF ATTR_PURE NONNULL((1)) intmax_t NOTHROW_NCX(LIBCCALL libc_wcstoimax)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_PURE NONNULL((1)) intmax_t NOTHROW_NCX(LIBDCALL libd_wcstoimax)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF ATTR_PURE NONNULL((1)) uintmax_t NOTHROW_NCX(LIBCCALL libc_wcstoumax)(char32_t const *__restrict nptr, char32_t **endptr, int base);
INTDEF ATTR_PURE NONNULL((1)) uintmax_t NOTHROW_NCX(LIBDCALL libd_wcstoumax)(char16_t const *__restrict nptr, char16_t **endptr, int base);
INTDEF ATTR_LEAF NONNULL((1)) intmax_t NOTHROW_NCX(LIBCCALL libc_strtoimax_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) uintmax_t NOTHROW_NCX(LIBCCALL libc_strtoumax_l)(char const *__restrict nptr, char **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) intmax_t NOTHROW_NCX(LIBCCALL libc_wcstoimax_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) intmax_t NOTHROW_NCX(LIBDCALL libd_wcstoimax_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) uintmax_t NOTHROW_NCX(LIBCCALL libc_wcstoumax_l)(char32_t const *__restrict nptr, char32_t **endptr, int base, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1)) uintmax_t NOTHROW_NCX(LIBDCALL libd_wcstoumax_l)(char16_t const *__restrict nptr, char16_t **endptr, int base, locale_t locale);
#define libc__strtoimax_l libc_strtoimax_l
#define libc__strtoumax_l libc_strtoumax_l
#define libc__wcstoimax_l libc_wcstoimax_l
#define libc__wcstoumax_l libc_wcstoumax_l
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_INTTYPES_H */
