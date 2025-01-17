/* HASH CRC-32:0xde0e4681 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_UCHAR_H
#define GUARD_LIBC_AUTO_UCHAR_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <uchar.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd_convert_freev)(void *vector);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc_convert_freev)(void *vector);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd_convert_freevn)(void *vector, size_t count);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc_convert_freevn)(void *vector, size_t count);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char *NOTHROW_NCX(LIBDCALL libd_convert_wcstombs)(char16_t const *str);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char *NOTHROW_NCX(LIBKCALL libc_convert_wcstombs)(char32_t const *str);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char *NOTHROW_NCX(LIBDCALL libd_convert_wcstombsn)(char16_t const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char *NOTHROW_NCX(LIBKCALL libc_convert_wcstombsn)(char32_t const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char **NOTHROW_NCX(LIBDCALL libd_convert_wcstombsv)(char16_t const *const *__restrict vector);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char **NOTHROW_NCX(LIBKCALL libc_convert_wcstombsv)(char32_t const *const *__restrict vector);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char **NOTHROW_NCX(LIBDCALL libd_convert_wcstombsvn)(char16_t const *const *__restrict vector, size_t count);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char **NOTHROW_NCX(LIBKCALL libc_convert_wcstombsvn)(char32_t const *const *__restrict vector, size_t count);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char16_t *NOTHROW_NCX(LIBDCALL libd_convert_mbstowcs)(char const *__restrict str);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char32_t *NOTHROW_NCX(LIBKCALL libc_convert_mbstowcs)(char const *__restrict str);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char16_t *NOTHROW_NCX(LIBDCALL libd_convert_mbstowcsn)(char const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char32_t *NOTHROW_NCX(LIBKCALL libc_convert_mbstowcsn)(char const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char16_t **NOTHROW_NCX(LIBDCALL libd_convert_mbstowcsv)(char const *const *__restrict vector);
INTDEF ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char32_t **NOTHROW_NCX(LIBKCALL libc_convert_mbstowcsv)(char const *const *__restrict vector);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char16_t **NOTHROW_NCX(LIBDCALL libd_convert_mbstowcsvn)(char const *const *__restrict vector, size_t count);
INTDEF ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char32_t **NOTHROW_NCX(LIBKCALL libc_convert_mbstowcsvn)(char const *const *__restrict vector, size_t count);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UCHAR_H */
