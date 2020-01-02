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
#ifndef GUARD_LIBJSON_WRITER_H
#define GUARD_LIBJSON_WRITER_H 1

#include "api.h"

#include <kos/types.h>

#include <format-printer.h>

#include <libjson/writer.h>

DECL_BEGIN

/* Json writer helper functions.
 * Note all of these have the same return value convention:
 * @return:  0: Success
 * @return: -1: Error: `self->jw_result' has a negative value when the function was called.
 * @return: -1: Error: An invocation of the `self->jw_printer' returned a negative value.
 * @return: -2: Error: Invalid usage during this, or during an earlier call. */
INTDEF NONNULL((1)) int CC libjson_writer_beginobject(struct json_writer *__restrict self);
INTDEF NONNULL((1)) int CC libjson_writer_beginarray(struct json_writer *__restrict self);
INTDEF NONNULL((1)) int CC libjson_writer_endobject(struct json_writer *__restrict self);
INTDEF NONNULL((1)) int CC libjson_writer_endarray(struct json_writer *__restrict self);
INTDEF NONNULL((1, 2)) int CC libjson_writer_addfield(struct json_writer *__restrict self, /*utf-8*/ char const *__restrict key, size_t keylen);
INTDEF NONNULL((1, 2)) int CC libjson_writer_putstring(struct json_writer *__restrict self, /*utf-8*/ char const *__restrict str, size_t len);
INTDEF NONNULL((1)) int CC libjson_writer_putnumber(struct json_writer *__restrict self, intptr_t value);
INTDEF NONNULL((1)) int CC libjson_writer_putint64(struct json_writer *__restrict self, int64_t value);
INTDEF NONNULL((1)) int CC libjson_writer_putuint64(struct json_writer *__restrict self, uint64_t value);
INTDEF NONNULL((1)) int CC libjson_writer_putfloat(struct json_writer *__restrict self, double value);
INTDEF NONNULL((1)) int CC libjson_writer_putbool(struct json_writer *__restrict self, bool value);
INTDEF NONNULL((1)) int CC libjson_writer_putnull(struct json_writer *__restrict self);


DECL_END

#endif /* !GUARD_LIBJSON_WRITER_H */
