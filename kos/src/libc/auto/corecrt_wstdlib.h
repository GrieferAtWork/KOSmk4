/* HASH CRC-32:0x89f20c53 */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_WSTDLIB_H
#define GUARD_LIBC_AUTO_CORECRT_WSTDLIB_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wstdlib.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) double NOTHROW_NCX(LIBDCALL libd__wtof)(char16_t const *nptr);
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) double NOTHROW_NCX(LIBKCALL libc__wtof)(char32_t const *nptr);
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) double NOTHROW_NCX(LIBDCALL libd__wtof_l)(char16_t const *nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED ATTR_ACCESS_RO(1) double NOTHROW_NCX(LIBKCALL libc__wtof_l)(char32_t const *nptr, locale_t locale);
INTDEF NONNULL((2)) char16_t *NOTHROW_NCX(LIBDCALL libd__itow)(int val, char16_t *buf, int radix);
INTDEF NONNULL((2)) char32_t *NOTHROW_NCX(LIBKCALL libc__itow)(int val, char32_t *buf, int radix);
INTDEF NONNULL((2)) char16_t *NOTHROW_NCX(LIBDCALL libd__ltow)(long val, char16_t *buf, int radix);
INTDEF NONNULL((2)) char32_t *NOTHROW_NCX(LIBKCALL libc__ltow)(long val, char32_t *buf, int radix);
INTDEF NONNULL((2)) char16_t *NOTHROW_NCX(LIBDCALL libd__ultow)(unsigned long val, char16_t *buf, int radix);
INTDEF NONNULL((2)) char32_t *NOTHROW_NCX(LIBKCALL libc__ultow)(unsigned long val, char32_t *buf, int radix);
INTDEF NONNULL((2)) char16_t *NOTHROW_NCX(LIBDCALL libd__i64tow)(s64 val, char16_t *buf, int radix);
INTDEF NONNULL((2)) char32_t *NOTHROW_NCX(LIBKCALL libc__i64tow)(s64 val, char32_t *buf, int radix);
INTDEF NONNULL((2)) char16_t *NOTHROW_NCX(LIBDCALL libd__ui64tow)(u64 val, char16_t *buf, int radix);
INTDEF NONNULL((2)) char32_t *NOTHROW_NCX(LIBKCALL libc__ui64tow)(u64 val, char32_t *buf, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__itow_s)(int val, char16_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBKCALL libc__itow_s)(int val, char32_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ltow_s)(long val, char16_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBKCALL libc__ltow_s)(long val, char32_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ultow_s)(unsigned long val, char16_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBKCALL libc__ultow_s)(unsigned long val, char32_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__i64tow_s)(s64 val, char16_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBKCALL libc__i64tow_s)(s64 val, char32_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBDCALL libd__ui64tow_s)(u64 val, char16_t *buf, size_t buflen, int radix);
INTDEF NONNULL((2)) errno_t NOTHROW_NCX(LIBKCALL libc__ui64tow_s)(u64 val, char32_t *buf, size_t buflen, int radix);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBDCALL libd__wtoi64)(char16_t const *__restrict nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBKCALL libc__wtoi64)(char32_t const *__restrict nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd__wtoi_l)(char16_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc__wtoi_l)(char32_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long int NOTHROW_NCX(LIBDCALL libd__wtol_l)(char16_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long int NOTHROW_NCX(LIBKCALL libc__wtol_l)(char32_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBDCALL libd__wtoi64_l)(char16_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) s64 NOTHROW_NCX(LIBKCALL libc__wtoi64_l)(char32_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd__wtoll_l)(char16_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBKCALL libc__wtoll_l)(char32_t const *__restrict nptr, locale_t locale);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(1, 3) char16_t *NOTHROW_NCX(LIBDCALL libd__wfullpath)(char16_t *buf, char16_t const *path, size_t buflen);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(1, 3) char32_t *NOTHROW_NCX(LIBKCALL libc__wfullpath)(char32_t *buf, char32_t const *path, size_t buflen);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__wmakepath_s)(char16_t *buf, size_t buflen, char16_t const *drive, char16_t const *dir, char16_t const *file, char16_t const *ext);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc__wmakepath_s)(char32_t *buf, size_t buflen, char32_t const *drive, char32_t const *dir, char32_t const *file, char32_t const *ext);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd__wmakepath)(char16_t *__restrict buf, char16_t const *drive, char16_t const *dir, char16_t const *file, char16_t const *ext);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBKCALL libc__wmakepath)(char32_t *__restrict buf, char32_t const *drive, char32_t const *dir, char32_t const *file, char32_t const *ext);
INTDEF NONNULL((1, 2, 3)) void NOTHROW_RPC(LIBDCALL libd__wsearchenv)(char16_t const *file, char16_t const *envvar, char16_t *__restrict resultpath);
INTDEF NONNULL((1, 2, 3)) void NOTHROW_RPC(LIBKCALL libc__wsearchenv)(char32_t const *file, char32_t const *envvar, char32_t *__restrict resultpath);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd__wsplitpath)(char16_t const *__restrict abspath, char16_t *drive, char16_t *dir, char16_t *file, char16_t *ext);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBKCALL libc__wsplitpath)(char32_t const *__restrict abspath, char32_t *drive, char32_t *dir, char32_t *file, char32_t *ext);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__wsplitpath_s)(char16_t const *__restrict abspath, char16_t *drive, size_t drivelen, char16_t *dir, size_t dirlen, char16_t *file, size_t filelen, char16_t *ext, size_t extlen);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc__wsplitpath_s)(char32_t const *__restrict abspath, char32_t *drive, size_t drivelen, char32_t *dir, size_t dirlen, char32_t *file, size_t filelen, char32_t *ext, size_t extlen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CORECRT_WSTDLIB_H */
