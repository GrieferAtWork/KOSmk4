/* HASH CRC-32:0x1f4c9ed2 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_INTTYPES_C
#define GUARD_LIBC_AUTO_DOSABI_INTTYPES_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../inttypes.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST intmax_t
NOTHROW(LIBDCALL libd_imaxabs)(intmax_t x) {
	return libc_imaxabs(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST imaxdiv_t
NOTHROW(LIBDCALL libd_imaxdiv)(intmax_t numer,
                               intmax_t denom) {
	return libc_imaxdiv(numer, denom);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) intmax_t
NOTHROW_NCX(LIBDCALL libd_strtoimax)(char const *__restrict nptr,
                                     char **endptr,
                                     int base) {
	return libc_strtoimax(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) uintmax_t
NOTHROW_NCX(LIBDCALL libd_strtoumax)(char const *__restrict nptr,
                                     char **endptr,
                                     int base) {
	return libc_strtoumax(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_LEAF NONNULL((1)) intmax_t
NOTHROW_NCX(LIBDCALL libd_strtoimax_l)(char const *__restrict nptr,
                                       char **endptr,
                                       int base,
                                       locale_t locale) {
	return libc_strtoimax_l(nptr, endptr, base, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_LEAF NONNULL((1)) uintmax_t
NOTHROW_NCX(LIBDCALL libd_strtoumax_l)(char const *__restrict nptr,
                                       char **endptr,
                                       int base,
                                       locale_t locale) {
	return libc_strtoumax_l(nptr, endptr, base, locale);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$imaxabs, libd_imaxabs);
DEFINE_PUBLIC_ALIAS(DOS$imaxdiv, libd_imaxdiv);
DEFINE_PUBLIC_ALIAS(DOS$strtoimax, libd_strtoimax);
DEFINE_PUBLIC_ALIAS(DOS$strtoumax, libd_strtoumax);
DEFINE_PUBLIC_ALIAS(DOS$_strtoimax_l, libd_strtoimax_l);
DEFINE_PUBLIC_ALIAS(DOS$strtoimax_l, libd_strtoimax_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoumax_l, libd_strtoumax_l);
DEFINE_PUBLIC_ALIAS(DOS$strtoumax_l, libd_strtoumax_l);

#endif /* !GUARD_LIBC_AUTO_DOSABI_INTTYPES_C */
