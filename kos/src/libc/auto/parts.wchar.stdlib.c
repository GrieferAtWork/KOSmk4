/* HASH CRC-32:0x8ba6ba45 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_C
#define GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "parts.wchar.stdlib.h"
#include "wchar.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wtoi") int
NOTHROW_NCX(LIBCCALL libc_wtoi)(char32_t const *nptr) {
#line 800 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_INT__ <= 4
	return (int)libc_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_INT__ <= 4 */
	return (int)libc_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_INT__ > 4 */
}
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wtoi") int
NOTHROW_NCX(LIBDCALL libd_wtoi)(char16_t const *nptr) {
#line 800 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_INT__ <= 4
	return (int)libd_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_INT__ <= 4 */
	return (int)libd_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_INT__ > 4 */
}

#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_wtol, libc_wtoi);
#else
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wtol") long
NOTHROW_NCX(LIBCCALL libc_wtol)(char32_t const *nptr) {
#line 810 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG__ <= 4
	return (long)libc_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libc_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* MAGIC:alias */
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libd_wtol, libd_wtoi);
#else
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wtol") long
NOTHROW_NCX(LIBDCALL libd_wtol)(char16_t const *nptr) {
#line 810 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG__ <= 4
	return (long)libd_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libd_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* MAGIC:alias */

#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_wtoll, libc_wtoi);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_wtoll, libc_wtol);
#else
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wtoll") __LONGLONG
NOTHROW_NCX(LIBCCALL libc_wtoll)(char32_t const *nptr) {
#line 821 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libc_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libc_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#endif /* MAGIC:alias */
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libd_wtoll, libd_wtoi);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libd_wtoll, libd_wtol);
#else
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wtoll") __LONGLONG
NOTHROW_NCX(LIBDCALL libd_wtoll)(char16_t const *nptr) {
#line 821 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libd_wcsto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libd_wcsto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#endif /* MAGIC:alias */

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(wtoi, libc_wtoi);
DEFINE_PUBLIC_WEAK_ALIAS(_wtoi, libc_wtoi);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wtoi, libd_wtoi);
DEFINE_PUBLIC_WEAK_ALIAS(wtol, libc_wtol);
DEFINE_PUBLIC_WEAK_ALIAS(_wtol, libc_wtol);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wtol, libd_wtol);
DEFINE_PUBLIC_WEAK_ALIAS(wtoll, libc_wtoll);
DEFINE_PUBLIC_WEAK_ALIAS(_wtoll, libc_wtoll);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wtoll, libd_wtoll);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_C */
