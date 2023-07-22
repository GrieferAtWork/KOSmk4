/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODDBX_INCLUDE_CPARSER_H
#define GUARD_MODDBX_INCLUDE_CPARSER_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <debugger/hook.h>
#include <kernel/types.h>

/**/
#include "error.h"

DECL_BEGIN

enum {
	CTOKEN_TOK_EOF        = '\0',    /* <End-of-file> */
	CTOKEN_TOK_INT        = '0',     /* 1234 */
	CTOKEN_TOK_FLOAT      = 'f',     /* 123.456 */
	CTOKEN_TOK_CHAR       = '\'',    /* 'f' */
	CTOKEN_TOK_STRING     = '\"',    /* "foo" */
	CTOKEN_TOK_KEYWORD    = '_',     /* foo */
	CTOKEN_TOK_UNKNOWN    = 254,     /* ??? */
	_CTOKEN_TOK_MULTICHAR = 255,     /* Start of multi-character tokens. */
	CTOKEN_TOK_PLUS_PLUS,            /* ++ */
	CTOKEN_TOK_PLUS_EQUALS,          /* += */
	CTOKEN_TOK_MINUS_MINUS,          /* -- */
	CTOKEN_TOK_MINUS_RANGLE,         /* -> */
	CTOKEN_TOK_PIPE_PIPE,            /* || */
	CTOKEN_TOK_AND_AND,              /* && */
	CTOKEN_TOK_LANGLE_LANGLE,        /* << */
	CTOKEN_TOK_RANGLE_RANGLE,        /* >> */
	CTOKEN_TOK_LANGLE_EQUALS,        /* <= */
	CTOKEN_TOK_RANGLE_EQUALS,        /* >= */
	CTOKEN_TOK_EQUALS_EQUALS,        /* == */
	CTOKEN_TOK_XCLAIM_EQUALS,        /* != */
	CTOKEN_TOK_DOT_DOT_DOT,          /* ... */
	CTOKEN_TOK_MINUS_EQUALS,         /* -= */
	CTOKEN_TOK_STAR_EQUALS,          /* *= */
	CTOKEN_TOK_SLASH_EQUALS,         /* /= */
	CTOKEN_TOK_PERCENT_EQUALS,       /* %= */
	CTOKEN_TOK_PIPE_EQUALS,          /* |= */
	CTOKEN_TOK_AND_EQUALS,           /* &= */
	CTOKEN_TOK_LANGLE_LANGLE_EQUALS, /* <<= */
	CTOKEN_TOK_RANGLE_RANGLE_EQUALS, /* >>= */
	CTOKEN_TOK_ROOF_EQUALS,          /* ^= */
	CTOKEN_TOK_COLON_COLON,          /* :: */
};

struct cparser {
	unsigned int          c_tok;      /* C Token kind. (single-character, or one of `CTOKEN_TOK_*') */
	CHECKED char const   *c_tokstart; /* [1..1] Start character of `c_tok' */
	CHECKED char const   *c_tokend;   /* [1..1] End character of `c_tok' */
	CHECKED char const   *c_end;      /* [1..1][const] End of text to-be parsed (NOTE: must point to a NUL-character!) */
	dbg_autocomplete_cb_t c_autocom;  /* [0..1] Auto-completion callback: When `CTOKEN_TOK_EOF' is reached in certain
	                                   *        positions while parsing an expression, and this callback is NULL, then
	                                   *        this callback will  be invoked  with a list  of possible  continuation
	                                   *        options. */
	void                 *c_autocom_arg;   /* [?..?] Cookie for `c_autocom' */
	char const           *c_autocom_start; /* [1..1][valid_if(c_autocom)] Text start for auto-completion. */
};

/* Try to auto-complete the given parser's expression by appending `str...+=len'
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
FUNDEF NONNULL((1, 2)) dbx_errno_t
NOTHROW_CB_NCX(FCALL cparser_autocomplete)(struct cparser const *__restrict self,
                                           CHECKED char const *__restrict str, size_t len);

#define cparser_init(self, str, len)                         \
	((self)->c_end     = ((self)->c_tokend = (str)) + (len), \
	 (self)->c_autocom = __NULLPTR,                          \
	 cparser_yield(self))

#define cparser_toklen(self) (size_t)((self)->c_tokend - (self)->c_tokstart)

/* Advance  the  given  C-parser  to  the  next  token.
 * Parsing starts at `self->c_tokend', and upon return,
 * the  `c_tok',  `c_tokstart'  and  `c_tokend'  fields
 * will have been  updated to describe  the next  token
 * following the initial `c_tokend' */
FUNDEF NONNULL((1)) void
NOTHROW_NCX(FCALL cparser_yield)(struct cparser *__restrict self);
#define cparser_yieldat(self, pos) \
	((self)->c_tokend = (pos), cparser_yield(self))

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_CPARSER_H */
