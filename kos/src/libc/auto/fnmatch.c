/* HASH CRC-32:0xf0d61c33 */
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
#ifndef GUARD_LIBC_AUTO_FNMATCH_C
#define GUARD_LIBC_AUTO_FNMATCH_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "fnmatch.h"
#include <ctype.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Match NAME against the filename pattern PATTERN,
 * returning zero if it matches, FNM_NOMATCH if not */
INTERN ATTR_SECTION(".text.crt.string.match") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_fnmatch)(char const *pattern, char const *name, int match_flags) {
	char card_post;
	for (;;) {
		if (!*name) {
			/* End of name (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			goto nomatch;
		}
		if (!*pattern)
			goto nomatch; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip leading asterisks */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			for (;;) {
				char ch = *name++;
				if (ch == card_post ||
				    ((match_flags & 0x10) &&
				     tolower(ch) == tolower(card_post))) {
					/* Recursively check if the rest of the name and pattern match */
					if (!fnmatch(name, pattern, match_flags))
						return 0;
				} else if (!ch) {
					goto nomatch; /* Wildcard suffix not found */
				} else if (ch == '/') {
					if ((match_flags & 0x01))
						goto nomatch;
					if ((match_flags & 0x04) &&
					    name[0] == '.' && card_post != '.')
						goto nomatch;
				}
			}
		}
		if (*pattern == *name) {
next:
			++name;
			++pattern;
			continue; /* single character match */
		}
		if (*pattern == '?') {
			if (*name == '/') {
				if (match_flags & 0x01)
					goto nomatch;
				if ((match_flags & 0x04) &&
				    name[1] == '.' && pattern[1] != '.')
					goto nomatch;
			}
			goto next;
		}
		break; /* mismatch */
	}
nomatch:
	return 1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(fnmatch, libc_fnmatch);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_FNMATCH_C */
