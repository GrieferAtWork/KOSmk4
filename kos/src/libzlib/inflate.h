/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBZLIB_INFLATE_H
#define GUARD_LIBZLIB_INFLATE_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include <format-printer.h>

#include <libzlib/inflate.h>

DECL_BEGIN

/* Initialize a ZLIB reader, given an initial data blob. */
INTDEF NONNULL((1)) void
NOTHROW_NCX(CC libzlib_reader_init)(struct zlib_reader *__restrict self,
                                    void const *blob, size_t blob_size);

/* Finalize the given zlib reader. */
INTDEF NONNULL((1)) void
NOTHROW_NCX(CC libzlib_reader_fini)(struct zlib_reader *__restrict self);


/* Decompress up to `bufsize' bytes from `self'
 * If an error occurs during this operation, return one of `ZLIB_ERROR_*'
 * @param: buf :           The destination buffer, or `NULL' if data should be skipped.
 * @return: > 0 :          The actual number of decompressed bytes.
 * @return: 0 :            End  of  input  stream,  or  want  more  input   data.
 *                         You may check for the former using `zlib_reader_eof()'
 * @return: ZLIB_ERROR_* : Deflate error. */
INTDEF WUNUSED NONNULL((1)) ssize_t CC
libzlib_reader_read(struct zlib_reader *__restrict self,
                    void *buf, size_t bufsize);

/* Feed the given ZLIB reader  another blob of compressed  data.
 * This function must be called to continue decompression  after
 * `zlib_reader_read()' returned 0 with a non-empty buffer size,
 * and `zlib_reader_eof(self)' also returning false.
 * WARNING: In order for `feed' to function properly, the reader
 *          must   have  access  to  a  sliding  window  buffer.
 *          Otherwise,  you must ensure that the compressed data
 *          blob is already complete from the get-go. */
INTDEF NONNULL((1)) void CC
libzlib_reader_feed(struct zlib_reader *__restrict self,
                    void const *blob, size_t blob_size);

/* Set the absolute reader position.
 * @return: >= 0:          The new (actually set) absolute position.
 * @return: ZLIB_ERROR_* : Deflate error. */
INTDEF WUNUSED NONNULL((1)) ssize_t CC
libzlib_reader_setpos(struct zlib_reader *__restrict self,
                      uintptr_t pos);

/* Rewind the given reader. */
INTDEF NONNULL((1)) void CC
libzlib_reader_rewind(struct zlib_reader *__restrict self);


DECL_END

#endif /* !GUARD_LIBZLIB_INFLATE_H */
