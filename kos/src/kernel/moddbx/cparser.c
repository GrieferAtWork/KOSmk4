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
#ifndef GUARD_MODDBX_CPARSER_C
#define GUARD_MODDBX_CPARSER_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/types.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <unicode.h>

/**/
#include "include/cparser.h"
#include "include/malloc.h"

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
DECL_BEGIN

/* Try to auto-complete the given parser's expression by appending `str...+=len'
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
PUBLIC NONNULL((1, 2)) dbx_errno_t
NOTHROW_CB_NCX(FCALL cparser_autocomplete)(struct cparser const *__restrict self,
                                           CHECKED char const *__restrict str, size_t len) {
	enum { STACK_LIMIT = 256 };
	size_t mylen;
	size_t total_len;
	char *buffer, *ptr;
	if (!self->c_autocom)
		return DBX_EOK; /* Don't need to do anything! */
	mylen     = (size_t)(self->c_end - self->c_autocom_start);
	total_len = (mylen + len + 1) * sizeof(char);
	if (total_len <= STACK_LIMIT) {
		buffer = (char *)alloca(total_len);
	} else {
		buffer = (char *)dbx_malloc(total_len);
		if unlikely(!buffer)
			return DBX_ENOMEM;
	}
	ptr = buffer;
	ptr = (char *)mempcpy(ptr, self->c_autocom_start, mylen, sizeof(char));
	ptr = (char *)mempcpy(ptr, str, len, sizeof(char));
	*ptr = '\0';

	/* Invoke the auto-completion callback. */
	(*self->c_autocom)(self->c_autocom_arg, buffer, (size_t)(ptr - buffer));
	if (total_len > STACK_LIMIT)
		dbx_free(buffer);
	return DBX_EOK;
}


/* Advance  the  given  C-parser  to  the  next  token.
 * Parsing starts at `self->c_tokend', and upon return,
 * the  `c_tok',  `c_tokstart'  and  `c_tokend'  fields
 * will have been  updated to describe  the next  token
 * following the initial `c_tokend' */
PUBLIC NONNULL((1)) void
NOTHROW_NCX(FCALL cparser_yield)(struct cparser *__restrict self) {
	char32_t ch;
	CHECKED char const *iter, *end;
	iter = self->c_tokend;
	end  = self->c_end;
again:
	self->c_tokstart = iter;
	if unlikely(iter >= end) {
		self->c_tok    = CTOKEN_TOK_EOF;
		self->c_tokend = iter;
		return;
	}
	ch = unicode_readutf8_n(&iter, end);
	self->c_tok    = ch;
	self->c_tokend = iter;
	switch (ch) {

	case '\'':
	case '\"': {
		char32_t endch = ch;
		do {
			ch = unicode_readutf8_n(&iter, end);
		} while (ch != endch && !unicode_islf(ch) && iter < end);
		self->c_tokend = iter;
	}	break;

	case '/':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '/') {
			do {
				ch = unicode_readutf8_n(&iter, end);
			} while (!unicode_islf(ch) && iter < end);
			goto again;
		} else if (ch == '*') {
			for (;;) {
				ch = unicode_readutf8_n(&iter, end);
				if (ch != '*') {
					if unlikely(!ch && iter >= end)
						break;
				}
				ch = unicode_readutf8_n(&iter, end);
				if (ch == '/')
					break;
			}
			goto again;
		} else if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_SLASH_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case '0' ... '9': {
		/* Integer or float */
		self->c_tok = CTOKEN_TOK_INT;
do_integer_or_float:
		do {
			assert(ch);
			self->c_tokend = iter;
			ch = unicode_readutf8_n(&iter, end);
		} while (unicode_isalnum(ch));
		if (ch == '.' && self->c_tok == CTOKEN_TOK_INT) {
			self->c_tok = CTOKEN_TOK_FLOAT;
			do {
				assert(ch);
				self->c_tokend = iter;
				ch = unicode_readutf8_n(&iter, end);
			} while (unicode_isalnum(ch));
			if (ch == '-' || ch == '+') {
				ch = unicode_readutf8_n(&iter, end);
				if (ch >= '0' && ch <= '9') {
					do {
						assert(ch);
						self->c_tokend = iter;
						ch = unicode_readutf8_n(&iter, end);
					} while (unicode_isalnum(ch));
				}
			}
		}
	}	break;

	case '.':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '.') {
			ch = unicode_readutf8_n(&iter, end);
			if (ch == '.') {
				self->c_tok    = CTOKEN_TOK_DOT_DOT_DOT;
				self->c_tokend = iter;
			}
		} else if (ch >= '0' && ch <= '9') {
			self->c_tok = CTOKEN_TOK_FLOAT;
			goto do_integer_or_float;
		}
		break;

	case '+':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '+') {
			self->c_tok    = CTOKEN_TOK_PLUS_PLUS;
			self->c_tokend = iter;
		} else if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_PLUS_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case '-':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '-') {
			self->c_tok    = CTOKEN_TOK_MINUS_MINUS;
			self->c_tokend = iter;
		} else if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_MINUS_EQUALS;
			self->c_tokend = iter;
		} else if (ch == '>') {
			self->c_tok    = CTOKEN_TOK_MINUS_RANGLE;
			self->c_tokend = iter;
		}
		break;

	case '&':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '&') {
			self->c_tok    = CTOKEN_TOK_AND_AND;
			self->c_tokend = iter;
		} else if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_AND_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case '|':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '|') {
			self->c_tok    = CTOKEN_TOK_PIPE_PIPE;
			self->c_tokend = iter;
		} else if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_PIPE_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case '<':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '<') {
			self->c_tok    = CTOKEN_TOK_LANGLE_LANGLE;
			self->c_tokend = iter;
			ch = unicode_readutf8_n(&iter, end);
			if (ch == '=') {
				self->c_tok    = CTOKEN_TOK_LANGLE_LANGLE_EQUALS;
				self->c_tokend = iter;
			}
		} else if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_LANGLE_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case '>':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '>') {
			self->c_tok    = CTOKEN_TOK_RANGLE_RANGLE;
			self->c_tokend = iter;
			ch = unicode_readutf8_n(&iter, end);
			if (ch == '=') {
				self->c_tok    = CTOKEN_TOK_RANGLE_RANGLE_EQUALS;
				self->c_tokend = iter;
			}
		} else if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_RANGLE_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case '!':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_XCLAIM_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case '=':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_EQUALS_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case '*':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_STAR_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case '%':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_PERCENT_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case '^':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == '=') {
			self->c_tok    = CTOKEN_TOK_ROOF_EQUALS;
			self->c_tokend = iter;
		}
		break;

	case ':':
		ch = unicode_readutf8_n(&iter, end);
		if (ch == ':') {
			self->c_tok    = CTOKEN_TOK_COLON_COLON;
			self->c_tokend = iter;
		}
		break;

	default:
		if (unicode_isspace(ch)) {
	case ' ': case '\t': case '\r': case '\n':
			goto again;
		}
		if (unicode_issymstrt(ch)) {
	case '$':
	case '_':
			/* Keyword */
			self->c_tok = CTOKEN_TOK_KEYWORD;
			do {
				assert(ch);
				self->c_tokend = iter;
				ch = unicode_readutf8_n(&iter, end);
			} while (unicode_issymcont(ch) ||
			         ch == '_' || ch == '$');
			break;
		}
		if unlikely(ch >= 256)
			self->c_tok = CTOKEN_TOK_UNKNOWN;
		break;
	}
}

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_CPARSER_C */
