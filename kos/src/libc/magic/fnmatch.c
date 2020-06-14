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
%[default:section(".text.crt.string.match")]

%{
#include <features.h>

/* Documentation taken from Glibc /usr/include/fnmatch.h */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#define FNM_PATHNAME    0x01 /* No wildcard can ever match '/'. */
#define FNM_NOESCAPE    0x02 /* Backslashes don't quote special chars. */
#define FNM_PERIOD      0x04 /* Leading '.' is matched only explicitly. */
#if (!defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 2 || defined(__USE_GNU))
#define FNM_FILE_NAME   FNM_PATHNAME /* Preferred GNU name. */
#define FNM_LEADING_DIR 0x08 /* Ignore '/...' after a match. */
#define FNM_CASEFOLD    0x10 /* Compare without regard to case. */
#define FNM_EXTMATCH    0x20 /* Use ksh-like extended matching. */
#endif /* !_POSIX_C_SOURCE || _POSIX_C_SOURCE < 2 || __USE_GNU */
#define FNM_NOMATCH      1 /* Value returned by 'fnmatch' if STRING does not match PATTERN. */
#ifdef __USE_XOPEN
#define FNM_NOSYS      (-1)
#endif /* __USE_XOPEN */

#ifdef __CC__
__SYSDECL_BEGIN

}


%[define(FNM_PATHNAME    = 0x01)] /* No wildcard can ever match '/'. */
%[define(FNM_NOESCAPE    = 0x02)] /* Backslashes don't quote special chars. */
%[define(FNM_PERIOD      = 0x04)] /* Leading '.' is matched only explicitly. */
%[define(FNM_LEADING_DIR = 0x08)] /* Ignore '/...' after a match. */
%[define(FNM_CASEFOLD    = 0x10)] /* Compare without regard to case. */
%[define(FNM_EXTMATCH    = 0x20)] /* Use ksh-like extended matching. */
%[define(FNM_NOMATCH     = 1)]    /* Value returned by 'fnmatch' if STRING does not match PATTERN. */



@@Match NAME against the filename pattern PATTERN,
@@returning zero if it matches, FNM_NOMATCH if not
[[wunused, ATTR_PURE]]
int fnmatch([[nonnull]] char const *pattern,
            [[nonnull]] char const *name,
            int match_flags) {
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
				    ((match_flags & FNM_CASEFOLD) &&
				     tolower(ch) == tolower(card_post))) {
					/* Recursively check if the rest of the name and pattern match */
					if (!fnmatch(name, pattern, match_flags))
						return 0;
				} else if (!ch) {
					goto nomatch; /* Wildcard suffix not found */
				} else if (ch == '/') {
					if ((match_flags & FNM_PATHNAME))
						goto nomatch;
					if ((match_flags & FNM_PERIOD) &&
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
				if (match_flags & FNM_PATHNAME)
					goto nomatch;
				if ((match_flags & FNM_PERIOD) &&
				    name[1] == '.' && pattern[1] != '.')
					goto nomatch;
			}
			goto next;
		}
		break; /* mismatch */
	}
nomatch:
	return FNM_NOMATCH;
}

%{

__SYSDECL_END
#endif /* __CC__ */

}