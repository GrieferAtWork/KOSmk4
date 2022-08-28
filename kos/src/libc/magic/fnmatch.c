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
%(c_prefix){
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/fnmatch.h) */
/* (#) Portability: DJGPP         (/include/fnmatch.h) */
/* (#) Portability: DragonFly BSD (/include/fnmatch.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/fnmatch.h) */
/* (#) Portability: FreeBSD       (/include/fnmatch.h) */
/* (#) Portability: GNU C Library (/posix/fnmatch.h) */
/* (#) Portability: NetBSD        (/include/fnmatch.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/fnmatch.h) */
/* (#) Portability: OpenBSD       (/include/fnmatch.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/fnmatch.h) */
/* (#) Portability: diet libc     (/include/fnmatch.h) */
/* (#) Portability: libc4/5       (/include/fnmatch.h) */
/* (#) Portability: libc6         (/include/fnmatch.h) */
/* (#) Portability: mintlib       (/include/fnmatch.h) */
/* (#) Portability: musl libc     (/include/fnmatch.h) */
/* (#) Portability: uClibc        (/include/fnmatch.h) */
}

%[default:section(".text.crt{|.dos}.string.match")]

%[insert:prefix(
#include <features.h>
)]%{

/* TODO: These constants should go into <asm/crt/fnmatch.h> */
#define FNM_PATHNAME    0x01 /* The wildcard character ('*') doesn't match slashes ('/') */
#define FNM_NOESCAPE    0x02 /* Backslashes characters ('\\') don't escape the follow-up character. */
#define FNM_PERIOD      0x04 /* A leading '.' can only be matched explicitly. */
#if (!defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 2 || defined(__USE_GNU))
#define FNM_FILE_NAME   FNM_PATHNAME /* GNU alias. */
#define FNM_LEADING_DIR 0x08 /* Ignore a sub-string '/...' when a match was already made. */
#define FNM_CASEFOLD    0x10 /* Ignore casing during character compares. */
#define FNM_EXTMATCH    0x20 /* Make use of ksh-like extended matching. */
#endif /* !_POSIX_C_SOURCE || _POSIX_C_SOURCE < 2 || __USE_GNU */
#define FNM_NOMATCH      1 /* The given `pattern' isn't matched. */
#ifdef __USE_XOPEN
#define FNM_NOSYS (-1) /* Never returned (would indicate that `fnmatch()' is not implemented) */
#endif /* __USE_XOPEN */

#ifdef __CC__
__SYSDECL_BEGIN

}


%[define(FNM_PATHNAME    = 0x01)]
%[define(FNM_NOESCAPE    = 0x02)]
%[define(FNM_PERIOD      = 0x04)]
%[define(FNM_LEADING_DIR = 0x08)]
%[define(FNM_CASEFOLD    = 0x10)]
%[define(FNM_EXTMATCH    = 0x20)]
%[define(FNM_NOMATCH     = 1)]



@@>> fnmatch(3)
@@Match the given `name' against `pattern', returning
@@`0'  if  they match,  and  `FNM_NOMATCH' otherwise.
@@@param: match_flags:   Set of `FNM_*'
@@@return: 0           : `name' is matched by `pattern'
@@@return: FNM_NOMATCH : `name' is not matched by `pattern'
[[pure, wunused, decl_include("<features.h>")]]
int fnmatch([[in]] char const *pattern,
            [[in]] char const *name,
            __STDC_INT_AS_UINT_T match_flags) {
	char card_post;
	/* TODO: Support for `FNM_NOESCAPE' */
	/* TODO: Support for `FNM_LEADING_DIR' */
	/* TODO: Support for `FNM_EXTMATCH' */
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
