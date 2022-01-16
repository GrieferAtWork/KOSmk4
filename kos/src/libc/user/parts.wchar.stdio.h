/* HASH CRC-32:0x136d18dd */
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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_STDIO_H
#define GUARD_LIBC_USER_PARTS_WCHAR_STDIO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/stdio.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wremove)(char16_t const *filename);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wremove)(char32_t const *filename);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBDCALL libd_wfopen)(char16_t const *filename, char16_t const *mode);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBKCALL libc_wfopen)(char32_t const *filename, char32_t const *mode);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBDCALL libd_wfreopen)(char16_t const *filename, char16_t const *mode, FILE *stream);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBKCALL libc_wfreopen)(char32_t const *filename, char32_t const *mode, FILE *stream);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBDCALL libd_wpopen)(char16_t const *command, char16_t const *mode);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBKCALL libc_wpopen)(char32_t const *command, char32_t const *mode);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_STDIO_H */
