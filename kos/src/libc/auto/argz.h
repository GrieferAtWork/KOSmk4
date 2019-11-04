/* HASH CRC-32:0xa56819fd */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBC_AUTO_ARGZ_H
#define GUARD_LIBC_AUTO_ARGZ_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <argz.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
INTDEF ATTR_PURE size_t NOTHROW_NCX(LIBCCALL libc_argz_count)(char const *argz, size_t argz_len);
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
#define libc___argz_count libc_argz_count
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
INTDEF NONNULL((1, 3)) void NOTHROW_NCX(LIBCCALL libc_argz_extract)(char const *__restrict argz, size_t argz_len, char **__restrict argv);
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
#define libc___argz_extract libc_argz_extract
/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
INTDEF void NOTHROW_NCX(LIBCCALL libc_argz_stringify)(char *argz, size_t len, int sep);
/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
#define libc___argz_stringify libc_argz_stringify
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
#define libc___argz_delete libc_argz_delete
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more.  If entry is NULL, then the first entry is returned.  This
 * behavior allows two convenient iteration styles:
 * >> char *entry = 0;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
INTDEF ATTR_PURE WUNUSED char *NOTHROW_NCX(LIBCCALL libc_argz_next)(char const *__restrict argz, size_t argz_len, char const *__restrict entry);
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more.  If entry is NULL, then the first entry is returned.  This
 * behavior allows two convenient iteration styles:
 * >> char *entry = 0;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
#define libc___argz_next libc_argz_next
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ARGZ_H */
