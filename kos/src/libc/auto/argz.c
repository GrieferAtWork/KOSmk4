/* HASH CRC-32:0x8f36a82 */
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
#ifndef GUARD_LIBC_AUTO_ARGZ_C
#define GUARD_LIBC_AUTO_ARGZ_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "argz.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
INTERN ATTR_PURE
ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_count") size_t
NOTHROW_NCX(LIBCCALL libc_argz_count)(char const *argz,
                                      size_t argz_len) {
#line 181 "kos/src/libc/magic/argz.c"
	size_t result = 0;
	if likely(argz_len) {
		for (;;) {
			size_t temp;
			++result;
			temp = libc_strlen(argz) + 1;
			if (temp >= argz_len)
				break;
			argz_len -= temp;
			argz     += temp;
		}
	}
	return result;
}

/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_extract") void
NOTHROW_NCX(LIBCCALL libc_argz_extract)(char const *__restrict argz,
                                        size_t argz_len,
                                        char **__restrict argv) {
#line 205 "kos/src/libc/magic/argz.c"
	size_t i;
	if unlikely(!argz_len)
		return;
	for (i = 0;;) {
		size_t temp;
		argv[i++] = (char *)argz;
		temp = libc_strlen(argz) + 1;
		if (temp >= argz_len)
			break;
		argz_len -= temp;
		argz     += temp;
	}
}

/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_stringify") void
NOTHROW_NCX(LIBCCALL libc_argz_stringify)(char *argz,
                                          size_t len,
                                          int sep) {
#line 225 "kos/src/libc/magic/argz.c"
	size_t i;
	/* replace(base: argz, count: len - 1, old: '\0', new: sep); */
	if unlikely(!len)
		return;
	for (i = 0;;) {
		size_t temp;
		temp = libc_strlen(argz) + 1;
		if (temp >= len)
			break;
		len  -= temp;
		argz += temp;
		argz[-1] = (char)(unsigned char)(unsigned int)sep;
	}
}

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
INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_next") char *
NOTHROW_NCX(LIBCCALL libc_argz_next)(char const *__restrict argz,
                                     size_t argz_len,
                                     char const *__restrict entry) {
#line 548 "kos/src/libc/magic/argz.c"
	char const *argz_end;
	if (!entry)
		return argz_len ? (char *)argz : NULL;
	argz_end = argz + argz_len;
	if (entry < argz_end)
		entry = libc_strend(entry) + 1;
	if (entry >= argz_end)
		return NULL;
	return (char *)entry;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(argz_count, libc_argz_count);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_count, libc_argz_count);
DEFINE_PUBLIC_WEAK_ALIAS(argz_extract, libc_argz_extract);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_extract, libc_argz_extract);
DEFINE_PUBLIC_WEAK_ALIAS(argz_stringify, libc_argz_stringify);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_stringify, libc_argz_stringify);
DEFINE_PUBLIC_WEAK_ALIAS(argz_next, libc_argz_next);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_next, libc_argz_next);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ARGZ_C */
