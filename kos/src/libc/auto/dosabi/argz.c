/* HASH CRC-32:0xdc370511 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_ARGZ_C
#define GUARD_LIBC_AUTO_DOSABI_ARGZ_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../argz.h"

DECL_BEGIN

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
 * `PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
 * `ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()' */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") NONNULL((1, 2, 3)) error_t
NOTHROW_NCX(LIBDCALL libd_argz_create)(char *const argv[],
                                       char **__restrict pargz,
                                       size_t *__restrict pargz_len) {
	return libc_argz_create(argv, pargz, pargz_len);
}
/* Make a '\0' separated arg vector from a `SEP' separated list in
 * `STRING', returning it in `PARGZ', and the total length in `PLEN'.
 * If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
 * The result can be destroyed using `free()' */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") NONNULL((1, 3, 4)) error_t
NOTHROW_NCX(LIBDCALL libd_argz_create_sep)(char const *__restrict string,
                                           int sep,
                                           char **__restrict pargz,
                                           size_t *__restrict pargz_len) {
	return libc_argz_create_sep(string, sep, pargz, pargz_len);
}
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") ATTR_PURE size_t
NOTHROW_NCX(LIBDCALL libd_argz_count)(char const *argz,
                                      size_t argz_len) {
	return libc_argz_count(argz, argz_len);
}
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") NONNULL((1, 3)) void
NOTHROW_NCX(LIBDCALL libd_argz_extract)(char const *__restrict argz,
                                        size_t argz_len,
                                        char **__restrict argv) {
	libc_argz_extract(argz, argz_len, argv);
}
/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") void
NOTHROW_NCX(LIBDCALL libd_argz_stringify)(char *argz,
                                          size_t len,
                                          int sep) {
	libc_argz_stringify(argz, len, sep);
}
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") NONNULL((1, 2)) error_t
NOTHROW_NCX(LIBDCALL libd_argz_append)(char **__restrict pargz,
                                       size_t *__restrict pargz_len,
                                       char const *__restrict buf,
                                       size_t buf_len) {
	return libc_argz_append(pargz, pargz_len, buf, buf_len);
}
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") NONNULL((1, 2, 3)) error_t
NOTHROW_NCX(LIBDCALL libd_argz_add)(char **__restrict pargz,
                                    size_t *__restrict pargz_len,
                                    char const *__restrict str) {
	return libc_argz_add(pargz, pargz_len, str);
}
/* Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN' */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") NONNULL((1, 2, 3)) error_t
NOTHROW_NCX(LIBDCALL libd_argz_add_sep)(char **__restrict pargz,
                                        size_t *__restrict pargz_len,
                                        char const *__restrict string,
                                        int sep) {
	return libc_argz_add_sep(pargz, pargz_len, string, sep);
}
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") NONNULL((1, 2)) void
NOTHROW_NCX(LIBDCALL libd_argz_delete)(char **__restrict pargz,
                                       size_t *__restrict pargz_len,
                                       char *entry) {
	libc_argz_delete(pargz, pargz_len, entry);
}
/* Insert `ENTRY' into `ARGZ & ARGZ_LEN' before `BEFORE', which should be an
 * existing entry in `ARGZ'; if `BEFORE' is `NULL', `ENTRY' is appended to the end.
 * Since `ARGZ's first entry is the same as `ARGZ', `argz_insert(ARGZ, ARGZ_LEN, ARGZ, ENTRY)'
 * will insert `ENTRY' at the beginning of `ARGZ'. If `BEFORE' is not in `ARGZ', `EINVAL'
 * is returned, else if memory can't be allocated for the new `ARGZ', `ENOMEM' is returned.
 * On success, `0' is returned */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") NONNULL((1, 2, 4)) error_t
NOTHROW_NCX(LIBDCALL libd_argz_insert)(char **__restrict pargz,
                                       size_t *__restrict pargz_len,
                                       char *before,
                                       char const *__restrict entry) {
	return libc_argz_insert(pargz, pargz_len, before, entry);
}
/* Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
 * `PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
 * incremented by number of replacements performed */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") NONNULL((1, 2, 4)) error_t
NOTHROW_NCX(LIBDCALL libd_argz_replace)(char **__restrict pargz,
                                        size_t *__restrict pargz_len,
                                        char const *__restrict str,
                                        char const *__restrict with,
                                        unsigned int *__restrict replace_count) {
	return libc_argz_replace(pargz, pargz_len, str, with, replace_count);
}
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
INTERN ATTR_SECTION(".text.crt.dos.string.argz") ATTR_PURE WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_argz_next)(char const *__restrict argz,
                                     size_t argz_len,
                                     char const *__restrict entry) {
	return libc_argz_next(argz, argz_len, entry);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__argz_create, libd_argz_create);
DEFINE_PUBLIC_ALIAS(DOS$argz_create, libd_argz_create);
DEFINE_PUBLIC_ALIAS(DOS$__argz_create_sep, libd_argz_create_sep);
DEFINE_PUBLIC_ALIAS(DOS$argz_create_sep, libd_argz_create_sep);
DEFINE_PUBLIC_ALIAS(DOS$__argz_count, libd_argz_count);
DEFINE_PUBLIC_ALIAS(DOS$argz_count, libd_argz_count);
DEFINE_PUBLIC_ALIAS(DOS$__argz_extract, libd_argz_extract);
DEFINE_PUBLIC_ALIAS(DOS$argz_extract, libd_argz_extract);
DEFINE_PUBLIC_ALIAS(DOS$__argz_stringify, libd_argz_stringify);
DEFINE_PUBLIC_ALIAS(DOS$argz_stringify, libd_argz_stringify);
DEFINE_PUBLIC_ALIAS(DOS$__argz_create_sep, libd_argz_append);
DEFINE_PUBLIC_ALIAS(DOS$argz_append, libd_argz_append);
DEFINE_PUBLIC_ALIAS(DOS$__argz_add, libd_argz_add);
DEFINE_PUBLIC_ALIAS(DOS$argz_add, libd_argz_add);
DEFINE_PUBLIC_ALIAS(DOS$__argz_add_sep, libd_argz_add_sep);
DEFINE_PUBLIC_ALIAS(DOS$argz_add_sep, libd_argz_add_sep);
DEFINE_PUBLIC_ALIAS(DOS$__argz_add_sep, libd_argz_delete);
DEFINE_PUBLIC_ALIAS(DOS$argz_delete, libd_argz_delete);
DEFINE_PUBLIC_ALIAS(DOS$__argz_insert, libd_argz_insert);
DEFINE_PUBLIC_ALIAS(DOS$argz_insert, libd_argz_insert);
DEFINE_PUBLIC_ALIAS(DOS$__argz_replace, libd_argz_replace);
DEFINE_PUBLIC_ALIAS(DOS$argz_replace, libd_argz_replace);
DEFINE_PUBLIC_ALIAS(DOS$__argz_next, libd_argz_next);
DEFINE_PUBLIC_ALIAS(DOS$argz_next, libd_argz_next);

#endif /* !GUARD_LIBC_AUTO_DOSABI_ARGZ_C */
