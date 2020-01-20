/* HASH CRC-32:0x5c7a3aaf */
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
#ifndef GUARD_LIBC_USER_SSP_STRING_H
#define GUARD_LIBC_USER_SSP_STRING_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ssp/string.h>

DECL_BEGIN

INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memcpy_chk)(void *__restrict dst, void const *__restrict src, size_t num_bytes, size_t dst_bufsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmove_chk)(void *dst, void const *src, size_t num_bytes, size_t dst_bufsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempcpy_chk)(void *__restrict dst, void const *__restrict src, size_t num_bytes, size_t dst_bufsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc___memset_chk)(void *__restrict dst, int byte, size_t num_bytes, size_t dst_bufsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___stpcpy_chk)(char *__restrict dst, char const *__restrict src, size_t dst_bufsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strcat_chk)(char *__restrict dst, char const *__restrict src, size_t dst_bufsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strcpy_chk)(char *__restrict dst, char const *__restrict src, size_t dst_bufsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strncat_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_bufsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strncpy_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_bufsize);

DECL_END

#endif /* !GUARD_LIBC_USER_SSP_STRING_H */
