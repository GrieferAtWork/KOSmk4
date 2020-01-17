/* HASH CRC-32:0xed95f16a */
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
#ifndef GUARD_LIBC_USER_ARGZ_H
#define GUARD_LIBC_USER_ARGZ_H 1

#include "../api.h"
#include "../auto/argz.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <argz.h>

DECL_BEGIN

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
 * `PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
 * `ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()' */
INTDEF NONNULL((1, 2, 3)) error_t NOTHROW_NCX(LIBCCALL libc_argz_create)(char *const argv[], char **__restrict pargz, size_t *__restrict pargz_len);
/* Make a '\0' separated arg vector from a `SEP' separated list in
 * `STRING', returning it in `PARGZ', and the total length in `PLEN'.
 * If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
 * The result can be destroyed using `free()' */
INTDEF error_t NOTHROW_NCX(LIBCCALL libc_argz_create_sep)(char const *__restrict string, int sep, char **__restrict pargz, size_t *__restrict pargz_len);
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
INTDEF NONNULL((1, 2)) error_t NOTHROW_NCX(LIBCCALL libc_argz_append)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict buf, size_t buf_len);
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
INTDEF NONNULL((1, 2, 3)) error_t NOTHROW_NCX(LIBCCALL libc_argz_add)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict str);
/* Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN' */
INTDEF NONNULL((1, 2, 3)) error_t NOTHROW_NCX(LIBCCALL libc_argz_add_sep)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict string, int sep);
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
INTDEF NONNULL((1, 2)) void NOTHROW_NCX(LIBCCALL libc_argz_delete)(char **__restrict pargz, size_t *__restrict pargz_len, char *entry);
/* Insert `ENTRY' into `ARGZ & ARGZ_LEN' before `BEFORE', which should be an
 * existing entry in `ARGZ'; if `BEFORE' is `NULL', `ENTRY' is appended to the end.
 * Since `ARGZ's first entry is the same as `ARGZ', `argz_insert(ARGZ, ARGZ_LEN, ARGZ, ENTRY)'
 * will insert `ENTRY' at the beginning of `ARGZ'. If `BEFORE' is not in `ARGZ', `EINVAL'
 * is returned, else if memory can't be allocated for the new `ARGZ', `ENOMEM' is returned.
 * On success, `0' is returned */
INTDEF NONNULL((1, 2, 4)) error_t NOTHROW_NCX(LIBCCALL libc_argz_insert)(char **__restrict pargz, size_t *__restrict pargz_len, char *before, char const *__restrict entry);
/* Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
 * `PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
 * incremented by number of replacements performed */
INTDEF NONNULL((1, 2, 4)) error_t NOTHROW_NCX(LIBCCALL libc_argz_replace)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict str, char const *__restrict with, unsigned int *__restrict replace_count);

DECL_END

#endif /* !GUARD_LIBC_USER_ARGZ_H */
