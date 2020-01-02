/* HASH CRC-32:0xb25b65 */
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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_STDIO_H
#define GUARD_LIBC_USER_PARTS_WCHAR_STDIO_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/stdio.h>

DECL_BEGIN

INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_wremove)(char32_t const *filename);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wremove)(char16_t const *filename);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBCCALL libc_wfopen)(char32_t const *filename, char32_t const *mode);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBDCALL libd_wfopen)(char16_t const *filename, char16_t const *mode);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBCCALL libc_wfreopen)(char32_t const *filename, char32_t const *mode, FILE *stream);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBDCALL libd_wfreopen)(char16_t const *filename, char16_t const *mode, FILE *stream);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBCCALL libc_wpopen)(char32_t const *command, char32_t const *mode);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBDCALL libd_wpopen)(char16_t const *command, char16_t const *mode);

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_STDIO_H */
