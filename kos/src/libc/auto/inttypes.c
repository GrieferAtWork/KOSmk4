/* HASH CRC-32:0x75ee4c99 */
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
#ifndef GUARD_LIBC_AUTO_INTTYPES_C
#define GUARD_LIBC_AUTO_INTTYPES_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "inttypes.h"
#include "stdlib.h"
#include "wchar.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.math.utility.imaxabs") intmax_t
NOTHROW(LIBCCALL libc_imaxabs)(intmax_t x) {
#line 494 "kos/src/libc/magic/inttypes.c"
	return x < 0 ? -x : x;
}

INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.math.utility.imaxdiv") imaxdiv_t
NOTHROW(LIBCCALL libc_imaxdiv)(intmax_t numer,
                               intmax_t denom) {
#line 499 "kos/src/libc/magic/inttypes.c"
	imaxdiv_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtoimax") intmax_t
NOTHROW_NCX(LIBCCALL libc_strtoimax)(char const *__restrict nptr,
                                     char **endptr,
                                     int base) {
#line 512 "kos/src/libc/magic/inttypes.c"
#if __SIZEOF_INTMAX_T__ <= 4
	return (intmax_t)libc_strto32(nptr, endptr, base);
#else /* __SIZEOF_INTMAX_T__ <= 4 */
	return (intmax_t)libc_strto64(nptr, endptr, base);
#endif /* __SIZEOF_INTMAX_T__ > 4 */
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.strtoumax") uintmax_t
NOTHROW_NCX(LIBCCALL libc_strtoumax)(char const *__restrict nptr,
                                     char **endptr,
                                     int base) {
#line 526 "kos/src/libc/magic/inttypes.c"
#if __SIZEOF_INTMAX_T__ <= 4
	return (uintmax_t)libc_strtou32(nptr, endptr, base);
#else /* __SIZEOF_INTMAX_T__ <= 4 */
	return (uintmax_t)libc_strtou64(nptr, endptr, base);
#endif /* __SIZEOF_INTMAX_T__ > 4 */
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcstoimax") intmax_t
NOTHROW_NCX(LIBCCALL libc_wcstoimax)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     int base) {
#line 512 "kos/src/libc/magic/inttypes.c"
#if __SIZEOF_INTMAX_T__ <= 4
	return (intmax_t)libc_wcsto32(nptr, endptr, base);
#else /* __SIZEOF_INTMAX_T__ <= 4 */
	return (intmax_t)libc_wcsto64(nptr, endptr, base);
#endif /* __SIZEOF_INTMAX_T__ > 4 */
}
INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcstoimax") intmax_t
NOTHROW_NCX(LIBDCALL libd_wcstoimax)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     int base) {
#line 512 "kos/src/libc/magic/inttypes.c"
#if __SIZEOF_INTMAX_T__ <= 4
	return (intmax_t)libd_wcsto32(nptr, endptr, base);
#else /* __SIZEOF_INTMAX_T__ <= 4 */
	return (intmax_t)libd_wcsto64(nptr, endptr, base);
#endif /* __SIZEOF_INTMAX_T__ > 4 */
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcstoumax") uintmax_t
NOTHROW_NCX(LIBCCALL libc_wcstoumax)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     int base) {
#line 526 "kos/src/libc/magic/inttypes.c"
#if __SIZEOF_INTMAX_T__ <= 4
	return (uintmax_t)libc_wcstou32(nptr, endptr, base);
#else /* __SIZEOF_INTMAX_T__ <= 4 */
	return (uintmax_t)libc_wcstou64(nptr, endptr, base);
#endif /* __SIZEOF_INTMAX_T__ > 4 */
}
INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcstoumax") uintmax_t
NOTHROW_NCX(LIBDCALL libd_wcstoumax)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     int base) {
#line 526 "kos/src/libc/magic/inttypes.c"
#if __SIZEOF_INTMAX_T__ <= 4
	return (uintmax_t)libd_wcstou32(nptr, endptr, base);
#else /* __SIZEOF_INTMAX_T__ <= 4 */
	return (uintmax_t)libd_wcstou64(nptr, endptr, base);
#endif /* __SIZEOF_INTMAX_T__ > 4 */
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.convert.strtoimax_l") intmax_t
NOTHROW_NCX(LIBCCALL libc_strtoimax_l)(char const *__restrict nptr,
                                       char **endptr,
                                       int base,
                                       locale_t locale) {
#line 567 "kos/src/libc/magic/inttypes.c"
	(void)locale;
	return libc_strtoimax(nptr, endptr, base);
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.convert.strtoumax_l") uintmax_t
NOTHROW_NCX(LIBCCALL libc_strtoumax_l)(char const *__restrict nptr,
                                       char **endptr,
                                       int base,
                                       locale_t locale) {
#line 579 "kos/src/libc/magic/inttypes.c"
	(void)locale;
	return libc_strtoumax(nptr, endptr, base);
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.convert.wcstoimax_l") intmax_t
NOTHROW_NCX(LIBCCALL libc_wcstoimax_l)(char32_t const *__restrict nptr,
                                       char32_t **endptr,
                                       int base,
                                       locale_t locale) {
#line 567 "kos/src/libc/magic/inttypes.c"
	(void)locale;
	return libc_wcstoimax(nptr, endptr, base);
}
INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert.wcstoimax_l") intmax_t
NOTHROW_NCX(LIBDCALL libd_wcstoimax_l)(char16_t const *__restrict nptr,
                                       char16_t **endptr,
                                       int base,
                                       locale_t locale) {
#line 567 "kos/src/libc/magic/inttypes.c"
	(void)locale;
	return libd_wcstoimax(nptr, endptr, base);
}

INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.convert.wcstoumax_l") uintmax_t
NOTHROW_NCX(LIBCCALL libc_wcstoumax_l)(char32_t const *__restrict nptr,
                                       char32_t **endptr,
                                       int base,
                                       locale_t locale) {
#line 579 "kos/src/libc/magic/inttypes.c"
	(void)locale;
	return libc_wcstoumax(nptr, endptr, base);
}
INTERN ATTR_LEAF NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert.wcstoumax_l") uintmax_t
NOTHROW_NCX(LIBDCALL libd_wcstoumax_l)(char16_t const *__restrict nptr,
                                       char16_t **endptr,
                                       int base,
                                       locale_t locale) {
#line 579 "kos/src/libc/magic/inttypes.c"
	(void)locale;
	return libd_wcstoumax(nptr, endptr, base);
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(imaxabs, libc_imaxabs);
DEFINE_PUBLIC_WEAK_ALIAS(imaxdiv, libc_imaxdiv);
DEFINE_PUBLIC_WEAK_ALIAS(strtoimax, libc_strtoimax);
DEFINE_PUBLIC_WEAK_ALIAS(strtoumax, libc_strtoumax);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoimax, libc_wcstoimax);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstoimax, libd_wcstoimax);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoumax, libc_wcstoumax);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstoumax, libd_wcstoumax);
DEFINE_PUBLIC_WEAK_ALIAS(strtoimax_l, libc_strtoimax_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtoimax_l, libc_strtoimax_l);
DEFINE_PUBLIC_WEAK_ALIAS(strtoumax_l, libc_strtoumax_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strtoumax_l, libc_strtoumax_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoimax_l, libc_wcstoimax_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcstoimax_l, libc_wcstoimax_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstoimax_l, libd_wcstoimax_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoumax_l, libc_wcstoumax_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcstoumax_l, libc_wcstoumax_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstoumax_l, libd_wcstoumax_l);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_INTTYPES_C */
