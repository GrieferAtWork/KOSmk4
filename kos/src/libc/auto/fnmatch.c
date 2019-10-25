/* HASH CRC-32:0x2f4ff55 */
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
#ifndef GUARD_LIBC_AUTO_FNMATCH_C
#define GUARD_LIBC_AUTO_FNMATCH_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "fnmatch.h"
#include "ctype.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Match NAME against the filename pattern PATTERN,
 * returning zero if it matches, FNM_NOMATCH if not */
INTERN ATTR_PURE WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.match.fnmatch") int
NOTHROW_NCX(LIBCCALL libc_fnmatch)(char const *pattern,
                                   char const *name,
                                   int match_flags) {
#line 67 "kos/src/libc/magic/fnmatch.c"
#define __FNM_PATHNAME    (1 << 0) /* No wildcard can ever match '/'. */
#define __FNM_NOESCAPE    (1 << 1) /* Backslashes don't quote special chars. */
#define __FNM_PERIOD      (1 << 2) /* Leading '.' is matched only explicitly. */
#define __FNM_LEADING_DIR (1 << 3) /* Ignore '/...' after a match. */
#define __FNM_CASEFOLD    (1 << 4) /* Compare without regard to case. */
#define __FNM_EXTMATCH    (1 << 5) /* Use ksh-like extended matching. */
#define __FNM_NOMATCH      1       /* Value returned by 'fnmatch' if STRING does not match PATTERN. */
	char card_post;
	for (;;) {
		if (!*name) {
			/* End of name (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return __FNM_NOMATCH;
		}
		if (!*pattern)
			return __FNM_NOMATCH; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip starts */
			do
				++pattern;
			while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			for (;;) {
				char ch = *name++;
				if (ch == card_post ||
				    ((match_flags & __FNM_CASEFOLD) && libc_tolower(ch) == libc_tolower(card_post))) {
					/* Recursively check if the rest of the name and pattern match */
					if (!libc_fnmatch(name, pattern, match_flags))
						return 0;
				} else if (!ch) {
					return __FNM_NOMATCH; /* Wildcard suffix not found */
				} else if (ch == '/') {
					if ((match_flags & __FNM_PATHNAME))
						return __FNM_NOMATCH;
					if ((match_flags & __FNM_PERIOD) && name[0] == '.' && card_post != '.')
						return __FNM_NOMATCH;
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
				if (match_flags & __FNM_PATHNAME)
					return __FNM_NOMATCH;
				if ((match_flags & __FNM_PERIOD) && name[1] == '.' && pattern[1] != '.')
					return __FNM_NOMATCH;
			}
			goto next;
		}
		break; /* mismatch */
	}
	return __FNM_NOMATCH;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(fnmatch, libc_fnmatch);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FNMATCH_C */
