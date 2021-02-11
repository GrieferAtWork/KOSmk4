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
#ifndef GUARD_LIBC_LIBC_UCHAR_H
#define GUARD_LIBC_LIBC_UCHAR_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <uchar.h>

DECL_BEGIN

#ifdef __CC__

/* Helper functions for converting wide-character strings
 * into  UTF-8,  so  they  may  be  used  by  the kernel. */
INTDEF void LIBCCALL libc_uchar_freev(/*utf-8*/ char **ptr);
INTDEF void LIBCCALL libc_uchar_freevn(/*utf-8*/ char **ptr, size_t count);
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char *LIBDCALL libc_uchar_c16tombs(char16_t const *__restrict str);
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char *LIBCCALL libc_uchar_c32tombs(char32_t const *__restrict str);
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char *LIBDCALL libc_uchar_c16tombsn(char16_t const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char *LIBCCALL libc_uchar_c32tombsn(char32_t const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char **LIBDCALL libc_uchar_c16tombsv(char16_t const *const *__restrict vector); /* Terminated by a NULL-pointer */
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char **LIBCCALL libc_uchar_c32tombsv(char32_t const *const *__restrict vector); /* Terminated by a NULL-pointer */
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char **LIBDCALL libc_uchar_c16tombsvn(char16_t const *const *__restrict vector, size_t count);
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char **LIBCCALL libc_uchar_c32tombsvn(char32_t const *const *__restrict vector, size_t count);

INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) char16_t *LIBDCALL libc_uchar_mbstoc16(/*utf-8*/ char const *__restrict str);
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) char32_t *LIBCCALL libc_uchar_mbstoc32(/*utf-8*/ char const *__restrict str);
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) char16_t *LIBDCALL libc_uchar_mbstoc16n(/*utf-8*/ char const *__restrict str, size_t len, size_t *preslen);
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) char32_t *LIBCCALL libc_uchar_mbstoc32n(/*utf-8*/ char const *__restrict str, size_t len, size_t *preslen);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_UCHAR_H */
