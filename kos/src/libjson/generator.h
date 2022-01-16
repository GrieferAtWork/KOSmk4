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
#ifndef GUARD_LIBJSON_GENERATOR_H
#define GUARD_LIBJSON_GENERATOR_H 1

#include "api.h"

#include <__stdinc.h>

#include <libjson/generator.h>

#include "parser.h"
#include "writer.h"

DECL_BEGIN

/* Encode a given object `src' as Json, using the given `codec' as generator.
 * @param: ext: External codec vector (s.a. `JGEN_EXTERN(...)')
 * @return:  0: Success.
 * @return: -1: Error: `writer->jw_result' has a negative value when the function was called.
 * @return: -1: Error: An invocation of the `writer->jw_printer' returned a negative value.
 * @return: -2: Error: Invalid usage during this, or during an earlier call. */
INTDEF NONNULL((1, 2, 3)) int CC
libjson_encode(struct json_writer *__restrict writer,
               void const *__restrict codec,
               void const *__restrict src,
               void const *const *ext);

/* Decode a given object `dst' from Json, using the given `codec' as generator.
 * @param: ext: External codec vector (s.a. `JGEN_EXTERN(...)')
 * @return: JSON_ERROR_OK:     Success.
 * @return: JSON_ERROR_SYNTAX: Syntax error.
 * @return: JSON_ERROR_NOOBJ:  A required field doesn't exist or has wrong typing.
 * @return: JSON_ERROR_SYSERR: Malformed codec.
 * @return: JSON_ERROR_RANGE:  The value of an integer field was too large. */
INTDEF NONNULL((1, 2, 3)) int
NOTHROW_NCX(CC libjson_decode)(struct json_parser *__restrict parser,
                               void const *__restrict codec,
                               void *__restrict dst,
                               void const *const *ext);

DECL_END

#endif /* !GUARD_LIBJSON_GENERATOR_H */
