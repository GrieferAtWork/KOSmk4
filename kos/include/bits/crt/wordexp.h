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
#ifndef _BITS_CRT_WORDEXP_H
#define _BITS_CRT_WORDEXP_H 1

#include <__crt.h>

#include <bits/types.h>

/* Flags for `wordexp(3)' */
#define __WRDE_DOOFFS  0x01 /* [valid_if(!WRDE_APPEND)] Insert `IN:we_offs' leading NULL entries before `we_wordv'.
                             * _NOT_  counted in `we_wordc'. This flag is  ignored if `WRDE_APPEND' is also passed. */
#define __WRDE_APPEND  0x02 /* Same as `WRDE_REUSE', but append additional entries, rather than override existing ones. */
#define __WRDE_NOCMD   0x04 /* Don't do command substitution as per "$(echo hi)" or "`echo hi`" */
#define __WRDE_REUSE   0x08 /* The given `wordexp_t *self' is still filled from a preceding call, and `wordfree(3)' wasn't called. */
#define __WRDE_SHOWERR 0x10 /* Do not redirect STDERR_FILENO to `/dev/null' (normally, this is done to hide error messages) */
#define __WRDE_UNDEF   0x20 /* Return `WRDE_BADVAL' if "$FOO" is used and `getenv("FOO") == NULL' (else, NULL environ variables simply expand to "") */

/* Return values (aside from `0') for `wordexp(3)' */
#define __WRDE_NOSYS   (-1) /* System isn't supported */
#define __WRDE_NOSPACE 1    /* ENOMEM */
#define __WRDE_BADCHAR 2    /* Illegal character encountered (one of "\n|&;<>(){}") */
#define __WRDE_BADVAL  3    /* `WRDE_UNDEF' was given and an undefined environment variable was used. */
#define __WRDE_CMDSUB  4    /* Tried to use "$(echo hi)" or "`echo hi`" when `WRDE_NOCMD' was given. */
#define __WRDE_SYNTAX  5    /* Syntax error (e.g. unmatched '"' or '(') */

#ifdef __CC__
__DECL_BEGIN

/* Control structure for `wordexp(3)' */
struct __wordexp_struct {
	__size_t  we_wordc; /* [IN:valid_if(WRDE_REUSE || WRDE_APPEND)] # of words */
	char    **we_wordv; /* [0..1][0..we_offs+we_wordc][owned]
	                     * [IN:valid_if(WRDE_REUSE || WRDE_APPEND)]
	                     * Vector of words (+ trailing NULL entry) */
	__size_t  we_offs;  /* [IN:valid_if(WRDE_REUSE || WRDE_APPEND || WRDE_DOOFFS)]
	                     * # of leading NULL entries in `we_wordv' (s.a. `WRDE_DOOFFS') */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_WORDEXP_H */
