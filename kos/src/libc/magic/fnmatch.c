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
%[default_impl_section(.text.crt.string.match)]

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

#define FNM_PATHNAME    (1 << 0) /* No wildcard can ever match '/'. */
#define FNM_NOESCAPE    (1 << 1) /* Backslashes don't quote special chars. */
#define FNM_PERIOD      (1 << 2) /* Leading '.' is matched only explicitly. */
#if !defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 2 || \
     defined(_GNU_SOURCE) || defined(_ALL_SOURCE)
#define FNM_FILE_NAME   FNM_PATHNAME /* Preferred GNU name. */
#define FNM_LEADING_DIR (1 << 3)     /* Ignore '/...' after a match. */
#define FNM_CASEFOLD    (1 << 4)     /* Compare without regard to case. */
#define FNM_EXTMATCH    (1 << 5)     /* Use ksh-like extended matching. */
#endif /* !_POSIX_C_SOURCE || _POSIX_C_SOURCE < 2 || _GNU_SOURCE || _ALL_SOURCE */
#define FNM_NOMATCH      1 /* Value returned by 'fnmatch' if STRING does not match PATTERN. */
#ifdef _XOPEN_SOURCE
#define FNM_NOSYS      (-1)
#endif /* _XOPEN_SOURCE */

#ifdef __CC__
__SYSDECL_BEGIN

}


@@Match NAME against the filename pattern PATTERN,
@@returning zero if it matches, FNM_NOMATCH if not
[ATTR_WUNUSED][ATTR_PURE]
fnmatch:([nonnull] char const *pattern, [nonnull] char const *name, int match_flags) -> int {
#define @__FNM_PATHNAME@    (1 << 0) /* No wildcard can ever match '/'. */
#define @__FNM_NOESCAPE@    (1 << 1) /* Backslashes don't quote special chars. */
#define @__FNM_PERIOD@      (1 << 2) /* Leading '.' is matched only explicitly. */
#define @__FNM_LEADING_DIR@ (1 << 3) /* Ignore '/...' after a match. */
#define @__FNM_CASEFOLD@    (1 << 4) /* Compare without regard to case. */
#define @__FNM_EXTMATCH@    (1 << 5) /* Use ksh-like extended matching. */
#define @__FNM_NOMATCH@      1       /* Value returned by 'fnmatch' if STRING does not match PATTERN. */
	char card_post;
	for (;;) {
		if (!*name) {
			/* End of name (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return @__FNM_NOMATCH@;
		}
		if (!*pattern)
			return @__FNM_NOMATCH@; /* Pattern end doesn't match */
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
				    ((match_flags & @__FNM_CASEFOLD@) && tolower(ch) == tolower(card_post))) {
					/* Recursively check if the rest of the name and pattern match */
					if (!fnmatch(name, pattern, match_flags))
						return 0;
				} else if (!ch) {
					return @__FNM_NOMATCH@; /* Wildcard suffix not found */
				} else if (ch == '/') {
					if ((match_flags & @__FNM_PATHNAME@))
						return @__FNM_NOMATCH@;
					if ((match_flags & @__FNM_PERIOD@) && name[0] == '.' && card_post != '.')
						return @__FNM_NOMATCH@;
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
				if (match_flags & @__FNM_PATHNAME@)
					return @__FNM_NOMATCH@;
				if ((match_flags & @__FNM_PERIOD@) && name[1] == '.' && pattern[1] != '.')
					return @__FNM_NOMATCH@;
			}
			goto next;
		}
		break; /* mismatch */
	}
	return @__FNM_NOMATCH@;
}

%{

__SYSDECL_END
#endif /* __CC__ */

}