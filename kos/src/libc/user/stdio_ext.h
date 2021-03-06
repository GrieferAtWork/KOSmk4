/* HASH CRC-32:0xcfb406fb */
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
#ifndef GUARD_LIBC_USER_STDIO_EXT_H
#define GUARD_LIBC_USER_STDIO_EXT_H 1

#include "../api.h"
#include "../auto/stdio_ext.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdio_ext.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> __fbufsize(3)
 * Return the size of the buffer of `stream' in
 * bytes currently in use by the given stream */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc___fbufsize)(FILE *stream);
/* >> __freading(3)
 * Return non-zero value when `stream' is opened readonly,
 * or if the last operation on `stream' was a read operation */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc___freading)(FILE *stream);
/* >> __fwriting(3)
 * Return non-zero value when `stream' is opened write-only or
 * append-only, or if the last operation on `stream' was a write
 * operation */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc___fwriting)(FILE *stream);
/* >> __freadable(3)
 * Return non-zero value when `stream' is not opened write-only or append-only */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc___freadable)(FILE *stream);
/* >> __fwritable(3)
 * Return non-zero value when `stream' is not opened read-only */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc___fwritable)(FILE *stream);
/* >> __flbf(3)
 * Return non-zero value when `stream' is line-buffered */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc___flbf)(FILE *stream);
/* >> __fpurge(3)
 * Discard all pending buffered I/O on `stream' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc___fpurge)(FILE *stream);
/* >> __fpending(3)
 * Return amount of output in bytes pending on a `stream' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc___fpending)(FILE *stream);
/* >> _flushlbf(3)
 * Flush all line-buffered files */
INTDEF void (LIBCCALL libc__flushlbf)(void) THROWS(...);
/* >> __fsetlocking(3)
 * Set locking status of `stream' to `type' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc___fsetlocking)(FILE *stream, int type);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_EXT_H */
