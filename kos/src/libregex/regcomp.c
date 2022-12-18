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
#ifndef GUARD_LIBREGEX_REGCOMP_C
#define GUARD_LIBREGEX_REGCOMP_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define LIBREGEX_WANT_PROTOTYPES

#include "api.h"
/**/
#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <kos/types.h>

#include <assert.h>
#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unicode.h>

#include <libc/template/hex.h>
#include <libregex/regcomp.h>

#include "regcomp.h"

#ifndef NDEBUG
#include <format-printer.h>
#include <inttypes.h>
#endif /* !NDEBUG */

/* Regex compile-time configuration */
#define RE_COMP_MAXSIZE 0x10000 /* 2^16 (hard limit on how large regex code blobs may get) */

DECL_BEGIN

#undef re_parser_yield
#define re_parser_yield(self) libre_parser_yield(self)

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#define int16_at(p) (*(int16_t *)(p))


/************************************************************************/
/* RE PARSER                                                            */
/************************************************************************/

/* Parse and yield the next regex-token pointed-to by `self->rep_pos'
 * @return: * : A unicode character, or one of `RE_TOKEN_*' */
INTERN WUNUSED NONNULL((1)) re_token_t
NOTHROW_NCX(CC libre_parser_yield)(struct re_parser *__restrict self) {
	unsigned char ch;
	ch = (unsigned char)*self->rep_pos++;
	switch (ch) {

	case '\0':
		--self->rep_pos;
		return RE_TOKEN_EOF;

	case '.':
		return RE_TOKEN_ANY;

	case '[':
		return RE_TOKEN_STARTSET;

	case '{':
		if ((self->rep_syntax & (RE_SYNTAX_INTERVALS | RE_SYNTAX_NO_BK_BRACES)) ==
		    /*               */ (RE_SYNTAX_INTERVALS | RE_SYNTAX_NO_BK_BRACES)) {
			/* TODO: RE_SYNTAX_INVALID_INTERVAL_ORD */
			return RE_TOKEN_STARTINTERVAL;
		}
		break;

	case '(':
		if (self->rep_syntax & RE_SYNTAX_NO_BK_PARENS)
			return RE_TOKEN_STARTGROUP;
		break;

	case ')':
		if ((self->rep_syntax & (RE_SYNTAX_NO_BK_PARENS | RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD)) ==
		    /*               */ (RE_SYNTAX_NO_BK_PARENS)) {
			return RE_TOKEN_ENDGROUP;
		}
		break;

	case '^':
		if (self->rep_syntax & (RE_SYNTAX_CONTEXT_INDEP_ANCHORS | RE_SYNTAX_CARET_ANCHORS_HERE))
			return RE_TOKEN_AT_SOL;
		if (self->rep_pos == self->rep_pat + 1)
			return RE_TOKEN_AT_SOL; /* Always special at start of pattern */
		if (self->rep_pos[-1] == '(') {
			/* Also special if following a non-escaped open-group */
			unsigned int num_bks = 0;
			char const *iter = self->rep_pos - 2;
			while (iter >= self->rep_pat && *iter == '\\') {
				--iter;
				++num_bks;
			}
			if (!(self->rep_syntax & RE_SYNTAX_NO_BK_PARENS))
				++num_bks; /* Invert meaning of escaped vs. non-escaped */
			if ((num_bks & 1) == 0) {
				/* '^' is following a non-escaped '(' -> it's an AT-marker! */
				return RE_TOKEN_AT_SOL;
			}
		}
		break;

	case '$':
		if (self->rep_syntax & RE_SYNTAX_CONTEXT_INDEP_ANCHORS)
			return RE_TOKEN_AT_EOL;
		if (self->rep_pos[0] == '\0')
			return RE_TOKEN_AT_EOL; /* Always special at end of pattern */
		if ((self->rep_pos[0] == ')') && (self->rep_syntax & RE_SYNTAX_NO_BK_PARENS))
			return RE_TOKEN_AT_EOL; /* Always special before group-close */
		if ((self->rep_pos[0] == '\\' && self->rep_pos[1] == '(') && !(self->rep_syntax & RE_SYNTAX_NO_BK_PARENS))
			return RE_TOKEN_AT_EOL; /* Always special before group-close */
		break;

	case '+':
		if (self->rep_syntax & RE_SYNTAX_LIMITED_OPS)
			break; /* "+" operator is disabled */
		if (!(self->rep_syntax & RE_SYNTAX_BK_PLUS_QM))
			return RE_TOKEN_PLUS; /* "+" is an operator */
		break;

	case '?':
		if (self->rep_syntax & RE_SYNTAX_LIMITED_OPS)
			break; /* "?" operator is disabled */
		if (!(self->rep_syntax & RE_SYNTAX_BK_PLUS_QM))
			return RE_TOKEN_QMARK; /* "?" is an operator */
		break;

	case '*':
		return RE_TOKEN_STAR;

	case '\n':
		if (!(self->rep_syntax & RE_SYNTAX_NEWLINE_ALT))
			break;
		ATTR_FALLTHROUGH
	case '|':
		if (self->rep_syntax & RE_SYNTAX_LIMITED_OPS)
			break; /* "|" operator is disabled */
		if (self->rep_syntax & RE_SYNTAX_NO_BK_VBAR)
			return RE_TOKEN_ALTERNATION; /* "|" is an operator */
		break;

	case '\\':
		ch = (unsigned char)*self->rep_pos++;
		switch (ch) {

		case '\0':
			self->rep_pos -= 2; /* Keep on repeating this token! */
			return RE_TOKEN_UNMATCHED_BK;

		case '{':
			if ((self->rep_syntax & (RE_SYNTAX_INTERVALS | RE_SYNTAX_NO_BK_BRACES)) ==
			    /*               */ (RE_SYNTAX_INTERVALS)) {
				/* TODO: RE_SYNTAX_INVALID_INTERVAL_ORD */
				return RE_TOKEN_STARTINTERVAL;
			}
			break;

		case '(':
			if (!(self->rep_syntax & RE_SYNTAX_NO_BK_PARENS))
				return RE_TOKEN_STARTGROUP;
			break;

		case ')':
			if (!(self->rep_syntax & (RE_SYNTAX_NO_BK_PARENS |
			                          RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD)))
				return RE_TOKEN_ENDGROUP;
			break;

		case '+':
			if (self->rep_syntax & RE_SYNTAX_LIMITED_OPS)
				break; /* "+" operator is disabled */
			if (self->rep_syntax & RE_SYNTAX_BK_PLUS_QM)
				return RE_TOKEN_PLUS; /* "\+" is an operator */
			break;

		case '?':
			if (self->rep_syntax & RE_SYNTAX_LIMITED_OPS)
				break; /* "?" operator is disabled */
			if (self->rep_syntax & RE_SYNTAX_BK_PLUS_QM)
				return RE_TOKEN_QMARK; /* "\?" is an operator */
			break;

		case '|':
			if (self->rep_syntax & RE_SYNTAX_LIMITED_OPS)
				break; /* "|" operator is disabled */
			if (!(self->rep_syntax & RE_SYNTAX_NO_BK_VBAR))
				return RE_TOKEN_ALTERNATION; /* "\|" is an operator */
			break;

		case 'w':
			if (!(self->rep_syntax & RE_SYNTAX_NO_GNU_OPS))
				return RE_TOKEN_BK_w;
			break;

		case 'W':
			if (!(self->rep_syntax & RE_SYNTAX_NO_GNU_OPS))
				return RE_TOKEN_BK_W;
			break;

		case 's':
			if (!(self->rep_syntax & RE_SYNTAX_NO_GNU_OPS))
				return RE_TOKEN_BK_s;
			break;

		case 'S':
			if (!(self->rep_syntax & RE_SYNTAX_NO_GNU_OPS))
				return RE_TOKEN_BK_S;
			break;

		case 'd':
			if (!(self->rep_syntax & RE_SYNTAX_NO_KOS_OPS))
				return RE_TOKEN_BK_d;
			break;

		case 'D':
			if (!(self->rep_syntax & RE_SYNTAX_NO_KOS_OPS))
				return RE_TOKEN_BK_D;
			break;

		case 'n':
			if (!(self->rep_syntax & RE_SYNTAX_NO_KOS_OPS))
				return RE_TOKEN_BK_n;
			break;

		case '`':
			if (!(self->rep_syntax & RE_SYNTAX_NO_GNU_OPS))
				return RE_TOKEN_AT_SOI;
			break;

		case '\'':
			if (!(self->rep_syntax & RE_SYNTAX_NO_GNU_OPS))
				return RE_TOKEN_AT_EOI;
			break;

		case 'b':
			if (!(self->rep_syntax & RE_SYNTAX_NO_GNU_OPS))
				return RE_TOKEN_AT_WOB;
			break;

		case 'B':
			if (!(self->rep_syntax & RE_SYNTAX_NO_GNU_OPS))
				return RE_TOKEN_AT_WOB_NOT;
			break;

		case '<':
			if (!(self->rep_syntax & RE_SYNTAX_NO_GNU_OPS))
				return RE_TOKEN_AT_SOW;
			break;

		case '>':
			if (!(self->rep_syntax & RE_SYNTAX_NO_GNU_OPS))
				return RE_TOKEN_AT_EOW;
			break;

		case '_':
			if (*self->rep_pos == '<') {
				++self->rep_pos;
				return RE_TOKEN_AT_SOS;
			}
			if (*self->rep_pos == '>') {
				++self->rep_pos;
				return RE_TOKEN_AT_EOS;
			}
			break;

		case '1' ... '9':
			if (!(self->rep_syntax & RE_SYNTAX_NO_BK_REFS))
				return RE_TOKEN_BKREF_1 + (ch - '1');
			break;

		case 'u':
		case 'U':
			if (self->rep_syntax & RE_SYNTAX_NO_UTF8)
				break;
			ATTR_FALLTHROUGH
		case 'x': {
			uint32_t ord;
			unsigned int i, digits;
			if (self->rep_syntax & RE_SYNTAX_NO_KOS_OPS)
				break;
			digits = ch == 'U' ? 8 : ch == 'u' ? 4 : 2;
			ord    = 0;
			for (i = 0; i < digits; ++i, ++self->rep_pos) {
				uint8_t nibble;
				char hexchar = *self->rep_pos;
				if (!__libc_hex2int(hexchar, &nibble)) {
					self->rep_pos -= i;
					goto default_escaped_char;
				}
				ord <<= 4;
				ord |= nibble;
			}
			if unlikely(ord >= RE_TOKEN_BASE) {
				/* Guard against illegal unicode characters. */
				self->rep_pos -= digits;
				goto default_escaped_char;
			}
			return ord;
		}	break;

		case 0x80 ... 0xff:
			goto handle_utf8;

		default:
default_escaped_char:
			break;
		}
		break;

	case 0x80 ... 0xff: {
		char32_t uni;
		uint8_t i, seqlen;
handle_utf8:
		if (self->rep_syntax & RE_SYNTAX_NO_UTF8)
			break; /* Always emit byte-literals */
		--self->rep_pos;
		/* Make sure that `unicode_readutf8(3)' won't access out-of-bounds memory */
		seqlen = unicode_utf8seqlen[ch];
		for (i = 0; i < seqlen; ++i) {
			if (self->rep_pos[i] == '\0') {
				self->rep_pos += i;
				return RE_TOKEN_EOF;
			}
		}
		uni = unicode_readutf8(&self->rep_pos);
		if unlikely(uni >= RE_TOKEN_BASE)
			uni = 0; /* Guard against illegal unicode characters. */
		return uni;
	}	break;

	default:
		break;
	}
	return ch; /* Regular case: just a literal */
}






/************************************************************************/
/* RE COMPILER                                                          */
/************************************************************************/
PRIVATE NONNULL((1)) bool
NOTHROW_NCX(CC re_compiler_require)(struct re_compiler *__restrict self,
                                    size_t num_bytes) {
	size_t avail;
	avail = (size_t)(self->rec_cend - self->rec_cpos);
	if (num_bytes > avail) {
		/* Must allocate more memory. */
		byte_t *old_base, *new_base;
		size_t old_size, new_minsize, new_size;
		old_base    = self->rec_cbase;
		old_size    = (size_t)(self->rec_cend - old_base);
		new_minsize = old_size - avail + num_bytes;
		assert(new_minsize == (size_t)(self->rec_cpos - self->rec_cbase) + num_bytes);
		new_size = old_size;
		while (new_size < new_minsize)
			new_size = (new_size << 1) | 1;
		++new_size;
		if unlikely(new_size > RE_COMP_MAXSIZE) {
			if (new_minsize > RE_COMP_MAXSIZE) {
				/* Allocate memory up until the maximum allowed (allowing
				 * our  caller  to replace  `RE_ESPACE'  with `RE_ESIZE') */
				re_compiler_require(self, RE_COMP_MAXSIZE - old_size);
				return false; /* Not allowed to allocate that much :( */
			}
			new_size = RE_COMP_MAXSIZE;
		}
		new_base = (byte_t *)realloc(old_base, new_size);
		if unlikely(!new_base) {
			new_size = new_minsize;
			new_base = (byte_t *)realloc(old_base, new_size);
			if unlikely(!new_base)
				return false; /* Unable to reallocate that much :( */
		}
		self->rec_cbase = new_base;
		self->rec_cend  = new_base + new_size;
		if (new_base != old_base) {
			/* Update pointers for the the block currently being compiled. */
			ptrdiff_t delta = new_base - old_base;
			self->rec_estart += delta;
			self->rec_cpos += delta;
		}
	}
	return true;
}


/* Append a single byte of code at the current buffer position. */
#define re_compiler_putc(self, b)        \
	((self)->rec_cpos < (self)->rec_cend \
	 ? (*(self)->rec_cpos++ = (b), true) \
	 : likely(_re_compiler_putc(self, b)))
PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC _re_compiler_putc)(struct re_compiler *__restrict self,
                                  byte_t b) {
	assert(self->rec_cpos == self->rec_cend);
	if likely(re_compiler_require(self, 1)) {
		*self->rec_cpos++ = b;
		return true;
	}
	return false;
}

PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC re_compiler_putn)(struct re_compiler *__restrict self,
                                 void const *p, size_t n) {
	if likely(re_compiler_require(self, n)) {
		self->rec_cpos = (byte_t *)mempcpy(self->rec_cpos, p, n);
		return true;
	}
	return false;
}


/* Return a pointer to the next instruction */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint8_t *
NOTHROW_NCX(CC re_opcode_next)(uint8_t const *__restrict p_instr) {
	uint8_t opcode = *p_instr++;
	switch (opcode) {

	case REOP_EXACT:
	case REOP_EXACT_ASCII_ICASE: {
		uint8_t length;
		length = *p_instr++;
		//assert(length >= 2); // TODO: re-enable me
		p_instr += length;
	}	break;

	case REOP_EXACT_UTF8_ICASE:
	case REOP_CONTAINS_UTF8:
	case REOP_CONTAINS_UTF8_NOT: {
		uint8_t count;
		count = *p_instr++;
		assert(count >= 1);
		do {
			unicode_readutf8((char **)p_instr);
		} while (--count);
	}	break;

	case REOP_BITSET:
	case REOP_BITSET_NOT: {
		uint8_t layout;
		layout = *p_instr++;
		p_instr += REOP_BITSET_LAYOUT_GETBYTES(layout);
	}	break;

	case REOP_CHAR:
	case REOP_GROUP_MATCH:
	case REOP_GROUP_MATCH_JMIN ... REOP_GROUP_MATCH_JMAX:
	case REOP_ASCII_ISDIGIT_EQ:
	case REOP_ASCII_ISDIGIT_NE:
	case REOP_ASCII_ISDIGIT_LO:
	case REOP_ASCII_ISDIGIT_LE:
	case REOP_ASCII_ISDIGIT_GR:
	case REOP_ASCII_ISDIGIT_GE:
	case REOP_UTF8_ISDIGIT_EQ:
	case REOP_UTF8_ISDIGIT_NE:
	case REOP_UTF8_ISDIGIT_LO:
	case REOP_UTF8_ISDIGIT_LE:
	case REOP_UTF8_ISDIGIT_GR:
	case REOP_UTF8_ISDIGIT_GE:
	case REOP_UTF8_ISNUMERIC_EQ:
	case REOP_UTF8_ISNUMERIC_NE:
	case REOP_UTF8_ISNUMERIC_LO:
	case REOP_UTF8_ISNUMERIC_LE:
	case REOP_UTF8_ISNUMERIC_GR:
	case REOP_UTF8_ISNUMERIC_GE:
	case REOP_GROUP_START:
	case REOP_GROUP_END:
	case REOP_GROUP_END_JMIN ... REOP_GROUP_END_JMAX:
		p_instr += 1;
		break;

	case REOP_CHAR2:
	case REOP_JMP:
	case REOP_JMP_ONFAIL:
	case REOP_JMP_AND_RETURN_ONFAIL:
	case REOP_SETVAR:
		p_instr += 2;
		break;

	case REOP_DEC_JMP:
	case REOP_DEC_JMP_AND_RETURN_ONFAIL:
		p_instr += 3;
		break;

	default:
		break;
	}
	return (byte_t *)p_instr;
}

/* Try to allocate a new variable */
PRIVATE WUNUSED NONNULL((1, 2)) bool
NOTHROW_NCX(CC re_compiler_allocvar)(struct re_compiler *__restrict self,
                                     uint8_t *__restrict p_vid) {
	if (self->rec_nvar >= 0x100)
		return false;
	*p_vid = self->rec_nvar++;
	return true;
}


/* Check if code pointed-at by `p_instr' is able to match EPSILON
 * Code at `p_instr' must be terminated by `REOP_MATCHED_PERFECT' */
PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC re_code_matches_epsilon)(uint8_t const *__restrict p_instr) {
	(void)p_instr;
	/* TODO: Just call regexec() on an empty buffer once that's been implemented */
	return true;
}



/* Check if `tolower(ch) != ch || toupper(ch) != ch' */
#define ascii_iscaseable(ch) isalpha(ch)


/* Encode a literal byte.
 * @param: literal_byte: The literal byte */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_literal_byte)(struct re_compiler *__restrict self,
                                                 byte_t literal_byte) {
	if (self->rec_parser.rep_syntax & RE_SYNTAX_ICASE) {
		char lower = (char)tolower((unsigned char)literal_byte);
		char upper = (char)toupper((unsigned char)literal_byte);
		if (lower != upper) {
			assertf((unsigned char)lower == (unsigned char)literal_byte ||
			        (unsigned char)upper == (unsigned char)literal_byte,
			        "This should always be the case under the C locale, "
			        "and KOS doesn't support any other locale");
			if (!re_compiler_putc(self, REOP_CHAR2))
				goto err_nomem;
			if (!re_compiler_putc(self, (unsigned char)lower))
				goto err_nomem;
			if (!re_compiler_putc(self, (unsigned char)upper))
				goto err_nomem;
			goto done_literal;
		}
	}
	if (!re_compiler_putc(self, REOP_CHAR))
		goto err_nomem;
	if (!re_compiler_putc(self, literal_byte))
		goto err_nomem;
done_literal:
	return RE_NOERROR;
err_nomem:
	return RE_ESPACE;
}

/* Encode a literal unicode character.
 * @param: literal_char: The literal unicode character */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_literal_uni)(struct re_compiler *__restrict self,
                                                char32_t literal_char) {
	char utf8[UNICODE_UTF8_MAXLEN];
	size_t utf8_len;
	utf8_len = (size_t)(unicode_writeutf8(utf8, literal_char) - utf8);
	if unlikely(utf8_len == 1) {
		byte_t literal_byte = (byte_t)(unsigned char)utf8[0];
		return re_compiler_compile_literal_byte(self, literal_byte);
	}

	/* Match unicode character */
	if (self->rec_parser.rep_syntax & RE_SYNTAX_ICASE) {
		uint8_t nchars;
		/* XXX: Technically, `chars' should be the set of C,  such
		 *      that `unicode_tolower(tok) == unicode_tolower(C)',
		 *      but the unicode  database has no  way to  (easily)
		 *      determine this... */
		char32_t chars[4];
		char32_t lower = unicode_tolower(literal_char);
		char32_t upper = unicode_toupper(literal_char);
		char32_t title = unicode_totitle(literal_char);

		/* Collect different chars */
		nchars   = 1;
		chars[0] = literal_char;
		if (lower != literal_char)
			chars[nchars++] = lower;
		if (upper != lower && upper != literal_char)
			chars[nchars++] = upper;
		if (title != lower && title != upper && title != literal_char)
			chars[nchars++] = title;
		assert(nchars >= 1 && nchars <= 4);
		if (nchars > 1) {
			char icase_utf8[lengthof(chars) * UNICODE_UTF8_MAXLEN], *endp;
			size_t icase_utf8_len;
			uint8_t i;
			for (endp = icase_utf8, i = 0; i < nchars; ++i)
				endp = unicode_writeutf8(endp, chars[i]);
			icase_utf8_len = (size_t)(endp - icase_utf8);
			if (!re_compiler_putc(self, REOP_CONTAINS_UTF8))
				goto err_nomem;
			if (!re_compiler_putc(self, nchars))
				goto err_nomem;
			if unlikely(!re_compiler_putn(self, icase_utf8, icase_utf8_len))
				goto err_nomem;
			goto done_literal;
		}
	}

	/* Match a single unicode character (consisting of more than 1 byte) */
	assert(utf8_len >= 2);
	if (!re_compiler_putc(self, REOP_EXACT))
		goto err_nomem;
	if (!re_compiler_putc(self, utf8_len))
		goto err_nomem;
	if unlikely(!re_compiler_putn(self, utf8, utf8_len))
		goto err_nomem;
done_literal:
	return RE_NOERROR;
err_nomem:
	return RE_ESPACE;
}


/* Encode an unescaped literal byte sequence.
 * @param: literal_byte_seq_start:  Literal sequence base pointer.
 * @param: literal_byte_seq_end:    Literal sequence end pointer. */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_unescaped_literal_byte_seq)(struct re_compiler *__restrict self,
                                                               char const *literal_byte_seq_start,
                                                               char const *literal_byte_seq_end) {
	size_t literal_seq_size;
	uint8_t reop_exact_opcode;

	/* Select the appropriate `REOP_EXACT' opcode */
	reop_exact_opcode = REOP_EXACT;
	if (self->rec_parser.rep_syntax & RE_SYNTAX_ICASE) {
		/* Can just use the regular code-path, only have the runtime
		 * use `memcasecmp(3)' instead of the usual `memcmp(3)' when
		 * comparing input. */
		reop_exact_opcode = REOP_EXACT_ASCII_ICASE;
	}

	/* Simple require an exact match with `literal_seq_start...literal_seq_end'.
	 * -> For this purpose, we can encode a sequence of `REOP_EXACT' instructions. */
	literal_seq_size = (size_t)(literal_byte_seq_end - literal_byte_seq_start);
	while (literal_seq_size > UINT8_MAX) {
		if (!re_compiler_putc(self, reop_exact_opcode))
			goto err_nomem;
		if (!re_compiler_putc(self, UINT8_MAX))
			goto err_nomem;
		if (!re_compiler_putn(self, literal_byte_seq_start, UINT8_MAX))
			goto err_nomem;
		literal_byte_seq_start += UINT8_MAX;
		literal_seq_size -= UINT8_MAX;
	}
	if (literal_seq_size >= 2) {
		if (!re_compiler_putc(self, reop_exact_opcode))
			goto err_nomem;
		if (!re_compiler_putc(self, (uint8_t)literal_seq_size))
			goto err_nomem;
		if (!re_compiler_putn(self, literal_byte_seq_start, literal_seq_size))
			goto err_nomem;
	} else if (literal_seq_size == 1) {
		return re_compiler_compile_literal_byte(self, literal_byte_seq_start[0]);
	}
/*done_literal:*/
	return RE_NOERROR;
err_nomem:
	return RE_ESPACE;
}

/* Threshold: when  at least this many ascii-only characters appear
 * next to each other in a literal sequence that also contains non-
 * ascii characters, then the ascii portion  is cut out of the  seq
 * and encoded on its own (via `REOP_EXACT_ASCII_ICASE')
 *
 * This is done because `REOP_EXACT_ASCII_ICASE' can be decoded
 * much faster than `REOP_EXACT_UTF8_ICASE' */
#define UTF8_ICASE_ASCII_CHUNK_THRESHOLD 16


/* Encode an unescaped literal sequence.
 * @param: literal_seq_start:  Literal sequence base pointer.
 * @param: literal_seq_end:    Literal sequence end pointer.
 * @param: literal_seq_length: Literal sequence length (in characters; NOT bytes; assumed to be >= 2)
 * @param: literal_seq_isutf8: True if literal sequence is utf-8 encoded (else: it's pure bytes) */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_unescaped_literal_seq)(struct re_compiler *__restrict self,
                                                          char const *literal_seq_start,
                                                          char const *literal_seq_end,
                                                          size_t literal_seq_length,
                                                          bool literal_seq_isutf8) {
	if (!literal_seq_isutf8 || !(self->rec_parser.rep_syntax & RE_SYNTAX_ICASE)) {
		/* If  input is ascii-only, or if casing isn't being ignored, then
		 * we can simply compile the entire literal sequence byte-by-byte. */
		return re_compiler_compile_unescaped_literal_byte_seq(self, literal_seq_start, literal_seq_end);
	}

	assert(self->rec_parser.rep_syntax & RE_SYNTAX_ICASE);
	assert(literal_seq_isutf8);
	/* Must encode a unicode sequence: REOP_EXACT_UTF8_ICASE */
	while (literal_seq_length > 0) {
		/* Check if we can encode a leading ascii-sequence without using `REOP_EXACT_UTF8_ICASE' */
		size_t num_bytes = (size_t)(literal_seq_end - literal_seq_start);
		size_t num_leading_chars = 0;
		char const *literal_seq_iter;
		while (num_leading_chars < num_bytes &&
		       (unsigned char)literal_seq_start[num_leading_chars] < 0x80)
			++num_leading_chars;
		assert(literal_seq_length >= num_leading_chars);
		if (num_leading_chars >= UTF8_ICASE_ASCII_CHUNK_THRESHOLD) {
			/* Encode the ascii-only portion separately */
			re_errno_t error;
			error = re_compiler_compile_unescaped_literal_byte_seq(self,
			                                                       literal_seq_start,
			                                                       literal_seq_start + num_leading_chars);
			if unlikely(error != RE_NOERROR)
				return error;
			literal_seq_start += num_leading_chars;
			literal_seq_length -= num_leading_chars;
			if (!literal_seq_length)
				break;
			assert(literal_seq_start < literal_seq_end);
			num_leading_chars = 0;
		}

		/* Figure out how many unicode characters there are.
		 *
		 * If we reach a gap of at least `UTF8_ICASE_ASCII_CHUNK_THRESHOLD'
		 * ascii-only characters, then  only emit code  up until said  gap!
		 * Also: only parse a sequence of up to UINT8_MAX unicode characters,
		 *       since the `REOP_EXACT_UTF8_ICASE'  opcode can't handle  more
		 *       than that many! */
		literal_seq_iter = literal_seq_start;
		while (num_leading_chars < literal_seq_length &&
		       num_leading_chars < UINT8_MAX) {
			assert(literal_seq_iter < literal_seq_end);
			if ((unsigned char)*literal_seq_iter < 0x80) {
				char const *literal_ascii_end;
				size_t literal_ascii_size = 1;
				literal_ascii_end = literal_seq_iter;
				++literal_ascii_end;
				while ((literal_ascii_end < literal_seq_end) &&
				       ((unsigned char)*literal_ascii_end < 0x80) &&
				       (literal_ascii_size < UTF8_ICASE_ASCII_CHUNK_THRESHOLD)) {
					++literal_ascii_end;
					++literal_ascii_size;
				}
				if (literal_ascii_size >= UTF8_ICASE_ASCII_CHUNK_THRESHOLD) {
					/* Emit the current utf-8 chunk, and have the ascii detector
					 * above deal with  the ascii-chunk once  the current  utf-8
					 * chunk has been written. */
					break;
				}
				/* Ascii-chunk  is too small for non-utf-8 encoding to be more efficient.
				 * As such, advance to its end and include it in the current utf-8 chunk. */
				assert(literal_seq_iter + literal_ascii_size == literal_ascii_end);
				literal_seq_iter = literal_ascii_end;
				num_leading_chars += literal_ascii_size;
				assert(num_leading_chars <= literal_seq_length);
				if (num_leading_chars > UINT8_MAX) {
					size_t too_many = num_leading_chars - UINT8_MAX;
					num_leading_chars -= too_many;
					literal_seq_iter -= too_many;
				}
				continue;
			}
			unicode_readutf8(&literal_seq_iter);
			++num_leading_chars;
		}

		/* Encode  the  `num_leading_chars'-character long
		 * chunk at `literal_seq_start...literal_seq_iter' */
		assert(num_leading_chars > 0);
		if (!re_compiler_putc(self, REOP_EXACT_UTF8_ICASE))
			goto err_nomem;
		if (!re_compiler_putc(self, (uint8_t)num_leading_chars))
			goto err_nomem;
		if (!re_compiler_putn(self, literal_seq_start, (size_t)(literal_seq_iter - literal_seq_start)))
			goto err_nomem;

		/* Continue with the remainder */
		literal_seq_start = literal_seq_iter;
		literal_seq_length -= num_leading_chars;
	}

/*done_literal:*/
	return RE_NOERROR;
err_nomem:
	return RE_ESPACE;
}

/* Encode a literal sequence.
 * @param: literal_seq_start:  Literal sequence base pointer.
 * @param: literal_seq_end:    Literal sequence end pointer.
 * @param: literal_seq_length: Literal sequence length (in characters; NOT bytes; assumed to be >= 1)
 * @param: literal_seq_hasesc: True if literal sequence still contains regex escapes
 * @param: literal_seq_isutf8: True if literal sequence is utf-8 encoded (else: it's pure bytes) */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_literal_seq)(struct re_compiler *__restrict self,
                                                char const *literal_seq_start,
                                                char const *literal_seq_end,
                                                size_t literal_seq_length,
                                                bool literal_seq_hasesc,
                                                bool literal_seq_isutf8) {
	char *unesc_literal_seq_start;
	char *unesc_literal_seq_end;
	re_errno_t error;

	/* At this point, we want to encode a literal sequence:
	 *     [literal_seq_start, literal_seq_end)
	 * Which is still  encoded as a  `literal_seq_length-character',
	 * regex encoded sequence of literal characters, with properties
	 * described by `literal_seq_hasesc' and `literal_seq_isutf8'. */
	assert(literal_seq_length >= 1);
	if (literal_seq_length == 1) {
		/* Special case: single-character literal */
		byte_t literal_byte;
		if (literal_seq_isutf8) {
			char32_t literal_char = unicode_readutf8(&literal_seq_start);
			return re_compiler_compile_literal_uni(self, literal_char);
		}
		literal_byte = (byte_t)literal_seq_start[0];
		return re_compiler_compile_literal_byte(self, literal_byte);
	}

	/* multi-character literal (using `REOP_EXACT' and friends) */
	assert(literal_seq_length >= 2);
	unesc_literal_seq_start = (char *)literal_seq_start;
	unesc_literal_seq_end   = (char *)literal_seq_end;
	if (literal_seq_hasesc) {
		/* Must unescape the literal sequence and convert it to utf-8/bytes */
		char *unesc_literal_seq_iter;
		size_t unesc_seq_maxlen = literal_seq_length;
#ifndef NDEBUG
		size_t unesc_numchars;
#endif /* !NDEBUG */
		if (literal_seq_isutf8) {
			/* No \-sequence can ever be shorter than the character it represents */
			unesc_seq_maxlen = (size_t)(literal_seq_end -
			                            literal_seq_start);
		}
		unesc_literal_seq_start = (char *)malloc(unesc_seq_maxlen);
		if unlikely(!unesc_literal_seq_start)
			goto err_nomem;
		unesc_literal_seq_iter = unesc_literal_seq_start;
		self->rec_parser.rep_pos = literal_seq_start;
#ifndef NDEBUG
		unesc_numchars = 0;
#endif /* !NDEBUG */
		while (self->rec_parser.rep_pos < literal_seq_end) {
			re_token_t lit = re_compiler_yield(self);
			assert(RE_TOKEN_ISLITERAL(lit));
			if (lit >= 0x80 && literal_seq_isutf8) {
				unesc_literal_seq_iter = unicode_writeutf8(unesc_literal_seq_iter, lit);
			} else {
				*unesc_literal_seq_iter++ = (byte_t)lit;
			}
#ifndef NDEBUG
			++unesc_numchars;
#endif /* !NDEBUG */
		}
#ifndef NDEBUG
		assertf(unesc_numchars == literal_seq_length,
		        "First time around we got nchars:  %Iu\n"
		        "Second time around we got nchars: %Iu",
		        literal_seq_length, unesc_numchars);
#endif /* !NDEBUG */
		unesc_literal_seq_end = unesc_literal_seq_iter;
		assert(unesc_literal_seq_end <= unesc_literal_seq_start + unesc_seq_maxlen);
	}

	/* Compile the unescaped literal sequence */
	error = re_compiler_compile_unescaped_literal_seq(self,
	                                                  unesc_literal_seq_start,
	                                                  unesc_literal_seq_end,
	                                                  literal_seq_length,
	                                                  literal_seq_isutf8);
	if (literal_seq_hasesc)
		free(unesc_literal_seq_start);
	return error;

/*done_literal:*/
	return RE_NOERROR;
err_nomem:
	return RE_ESPACE;
}


PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_alternation)(struct re_compiler *__restrict self);

/* Special return value for `re_compiler_compile_prefix':
 * the prefix has  just concluded with  `REOP_GROUP_END',
 * or `REOP_GROUP_MATCH' opcode, but the referenced group
 * is capable of matching epsilon! */
#define RE_COMPILER_COMPILE_PREFIX__AFTER_EPSILON_GROUP (-1)

/* Compile prefix expressions: literals, '[...]' and '(...)'
 * This function also sets `self->rec_estart' */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_prefix)(struct re_compiler *__restrict self) {
	re_token_t tok;
	char const *tokstart;
again:
	self->rec_estart = self->rec_cpos; /* Start of new (sub-)expression */

	/* Start parsing the current expression */
	tokstart = self->rec_parser.rep_pos;
	tok      = re_compiler_yield(self);
	switch (tok) {

		/* Tokens which we don't consume, but instead treat as an epsilon-match */
	case RE_TOKEN_EOF:         /* End of pattern */
	case RE_TOKEN_ENDGROUP:    /* ')'-token (let the caller deal with this) */
	case RE_TOKEN_ALTERNATION: /* '|'-token (let the caller deal with this) */
		self->rec_parser.rep_pos = tokstart;
		return RE_NOERROR;

	case RE_TOKEN_UNMATCHED_BK: /* Unmatched '\' */
		return RE_EESCAPE;

	case RE_TOKEN_STARTINTERVAL:
		if (self->rec_parser.rep_syntax & (RE_SYNTAX_CONTEXT_INVALID_DUP |
		                                   RE_SYNTAX_CONTEXT_INVALID_OPS))
			return RE_BADRPT;
		tok = '{';
		goto do_literal;

	case RE_TOKEN_PLUS:
		if (self->rec_parser.rep_syntax & RE_SYNTAX_CONTEXT_INVALID_OPS)
			return RE_BADRPT;
		tok = '+';
		goto do_literal;

	case RE_TOKEN_STAR:
		if (self->rec_parser.rep_syntax & RE_SYNTAX_CONTEXT_INVALID_OPS)
			return RE_BADRPT;
		tok = '*';
		goto do_literal;

	case RE_TOKEN_QMARK:
		if (self->rec_parser.rep_syntax & RE_SYNTAX_CONTEXT_INVALID_OPS)
			return RE_BADRPT;
		tok = '?';
		goto do_literal;

	case RE_TOKEN_STARTGROUP: {
		/* Group and parenthesis */
		bool group_matches_epsilon;
		size_t expr_start_offset;
		size_t group_start_offset;
		re_errno_t error;
		uint8_t gid;
		byte_t *body;
		uintptr_t old_syntax;

		if unlikely(self->rec_ngrp >= 0x100)
			return RE_ESIZE; /* Too many groups */
		gid = self->rec_ngrp++;

		/* We're inside of a group, so ')' are no longer literals! */
		old_syntax = self->rec_parser.rep_syntax;
		self->rec_parser.rep_syntax &= ~RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD;

		/* Generate the introductory `REOP_GROUP_START' instruction */
		expr_start_offset = (size_t)(self->rec_estart - self->rec_cbase);
		if (!re_compiler_putc(self, REOP_GROUP_START))
			goto err_nomem;
		if (!re_compiler_putc(self, gid))
			goto err_nomem;

		/* Compile the actual contents of the group. */
		group_start_offset = (size_t)(self->rec_cpos - self->rec_cbase);
		error = re_compiler_compile_alternation(self);
		if unlikely(error != RE_NOERROR)
			return error;

		/* Consume the trailing ')'-token */
		tok = re_compiler_yield(self);
		if unlikely(tok != RE_TOKEN_ENDGROUP) {
			if (tok == RE_TOKEN_UNMATCHED_BK)
				return RE_EESCAPE;
			return RE_EPAREN;
		}

		/* Restore old syntax behavior for  ')' being a literal or  not.
		 * s.a. us clearing `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' above. */
		self->rec_parser.rep_syntax = old_syntax;

		/* Figure out if the group is able to match EPSION */
		if unlikely(!re_compiler_require(self, 1))
			goto err_nomem;
		*self->rec_cpos = REOP_MATCHED_PERFECT;
		body = self->rec_cbase + group_start_offset;
		group_matches_epsilon = re_code_matches_epsilon(body);

		/* Mark the end of the group (this opcode may be overwritten later) */
		*self->rec_cpos++ = REOP_GROUP_END;
		if (!re_compiler_putc(self, gid))
			goto err_nomem;

		/* Restore the expression-start offset to point at the `REOP_GROUP_START' opcode. */
		self->rec_estart = self->rec_cbase + expr_start_offset;

		/* Remember information about the first 9 groups */
		if (gid < lengthof(self->rec_grpinfo)) {
			self->rec_grpinfo[gid] |= RE_COMPILER_GRPINFO_DEFINED;
			if (group_matches_epsilon)
				self->rec_grpinfo[gid] |= RE_COMPILER_GRPINFO_EPSILON;
		}
		if (group_matches_epsilon)
			return RE_COMPILER_COMPILE_PREFIX__AFTER_EPSILON_GROUP;
	}	break;

	case RE_TOKEN_STARTSET:
		/* TODO: set match */
		return RE_BADPAT;

	case RE_TOKEN_BK_w:
	case RE_TOKEN_BK_W:
	case RE_TOKEN_BK_s:
	case RE_TOKEN_BK_S:
	case RE_TOKEN_BK_d:
	case RE_TOKEN_BK_D:
	case RE_TOKEN_BK_n:
		/* TODO: special set matches */
		return RE_BADPAT;

	case RE_TOKEN_ANY: {
		uint8_t opcode;
		switch (self->rec_parser.rep_syntax & (RE_SYNTAX_DOT_NEWLINE |
		                                       RE_SYNTAX_DOT_NOT_NULL |
		                                       RE_SYNTAX_NO_UTF8)) {
		case 0:
			opcode = REOP_ANY_NOTLF_UTF8;
			break;
		case RE_SYNTAX_NO_UTF8:
			opcode = REOP_ANY_NOTLF;
			break;
		case RE_SYNTAX_DOT_NEWLINE:
		case RE_SYNTAX_DOT_NEWLINE | RE_SYNTAX_NO_UTF8:
			opcode = REOP_ANY;
			break;
		case RE_SYNTAX_DOT_NOT_NULL:
			opcode = REOP_ANY_NOTNUL_NOTLF;
			break;
		case RE_SYNTAX_DOT_NOT_NULL | RE_SYNTAX_NO_UTF8:
			opcode = REOP_ANY_NOTNUL_NOTLF_UTF8;
			break;
		case RE_SYNTAX_DOT_NEWLINE | RE_SYNTAX_DOT_NOT_NULL:
		case RE_SYNTAX_DOT_NEWLINE | RE_SYNTAX_DOT_NOT_NULL | RE_SYNTAX_NO_UTF8:
			opcode = REOP_ANY_NOTNUL;
			break;
		default: __builtin_unreachable();
		}
		if (!re_compiler_putc(self, opcode))
			goto err_nomem;
	}	break;

	case RE_TOKEN_AT_MIN ... RE_TOKEN_AT_MAX: {
		static uint8_t const at_opcodes[(RE_TOKEN_AT_MAX - RE_TOKEN_AT_MIN) + 1][2] = {
			[(RE_TOKEN_AT_SOL - RE_TOKEN_AT_MIN)]     = { REOP_AT_SOI, REOP_AT_SOI },
			[(RE_TOKEN_AT_EOL - RE_TOKEN_AT_MIN)]     = { REOP_AT_EOI, REOP_AT_EOI },
			[(RE_TOKEN_AT_SOI - RE_TOKEN_AT_MIN)]     = { REOP_AT_SOL, REOP_AT_SOL_UTF8 },
			[(RE_TOKEN_AT_EOI - RE_TOKEN_AT_MIN)]     = { REOP_AT_EOL, REOP_AT_EOL_UTF8 },
			[(RE_TOKEN_AT_WOB - RE_TOKEN_AT_MIN)]     = { REOP_AT_WOB, REOP_AT_WOB_UTF8 },
			[(RE_TOKEN_AT_WOB_NOT - RE_TOKEN_AT_MIN)] = { REOP_AT_WOB_NOT, REOP_AT_WOB_UTF8_NOT },
			[(RE_TOKEN_AT_SOW - RE_TOKEN_AT_MIN)]     = { REOP_AT_SOW, REOP_AT_SOW_UTF8 },
			[(RE_TOKEN_AT_EOW - RE_TOKEN_AT_MIN)]     = { REOP_AT_EOW, REOP_AT_EOW_UTF8 },
			[(RE_TOKEN_AT_SOS - RE_TOKEN_AT_MIN)]     = { REOP_AT_SOS, REOP_AT_SOS_UTF8 },
			[(RE_TOKEN_AT_EOS - RE_TOKEN_AT_MIN)]     = { REOP_AT_EOS, REOP_AT_EOS_UTF8 },
		};
		uint8_t opcode = at_opcodes[tok - RE_TOKEN_AT_MIN]
		                           [(self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8) ? 0 : 1];
		if (!re_compiler_putc(self, opcode))
			goto err_nomem;
		/* Parse another prefix expression since location assertions don't count as prefixes! */
		goto again;
	}	break;

	case RE_TOKEN_BKREF_1 ... RE_TOKEN_BKREF_9: {
		uint8_t gid = tok - RE_TOKEN_BKREF_1;
		uint8_t ginfo;
		assert(gid <= 8); /* 1-9 --> 9 groups -> 0-based index must be <= 8 */
		ginfo = self->rec_grpinfo[gid];
		if (!(ginfo & RE_COMPILER_GRPINFO_DEFINED))
			return RE_ESUBREG;
		if (!re_compiler_putc(self, REOP_GROUP_MATCH))
			goto err_nomem;
		if (!re_compiler_putc(self, gid))
			goto err_nomem;
		if (ginfo & RE_COMPILER_GRPINFO_EPSILON)
			return RE_COMPILER_COMPILE_PREFIX__AFTER_EPSILON_GROUP;
	}	break;

	default:
		if (!RE_TOKEN_ISLITERAL(tok))
			return RE_BADPAT;
		{
			bool literal_seq_hasesc;
			bool literal_seq_isutf8;
#ifndef __OPTIMIZE_SIZE__
			bool seq_followed_by_suffix;
#endif /* !__OPTIMIZE_SIZE__ */
			char const *literal_seq_start;
			char const *literal_seq_end;
			char const *old_literal_seq_end;
			size_t literal_seq_length;
			re_errno_t error;
do_literal:
			literal_seq_hasesc  = (unsigned char)*tokstart == '\\';
			literal_seq_isutf8  = tok >= 0x80;
			literal_seq_start   = tokstart;
			literal_seq_end     = self->rec_parser.rep_pos;
			old_literal_seq_end = self->rec_parser.rep_pos;
			literal_seq_length  = 1;
#ifndef __OPTIMIZE_SIZE__
			seq_followed_by_suffix = false;
#endif /* !__OPTIMIZE_SIZE__ */
			for (;;) {
				re_token_t lit = re_compiler_yield(self);
				if (!RE_TOKEN_ISLITERAL(lit)) {
					if (RE_TOKEN_ISSUFFIX(lit)) {
						/* literal  sequence immediately followed  by repetition token: "abcdef*"
						 * In  this case, we're only allowed to encode sequence "abcde", followed
						 * by a single-character sequence "f", since only said "f" is meant to be
						 * affected by the trailing "*"! */
						assert(old_literal_seq_end <= literal_seq_end);
						if (literal_seq_end != old_literal_seq_end) {
							assert(literal_seq_length > 1);
							--literal_seq_length;
#ifndef __OPTIMIZE_SIZE__
							seq_followed_by_suffix = true;
#endif /* !__OPTIMIZE_SIZE__ */
						} else {
							assert(literal_seq_length == 1);
						}
						literal_seq_end = old_literal_seq_end;
					}
					self->rec_parser.rep_pos = literal_seq_end;
					break;
				}
				literal_seq_hasesc |= (unsigned char)*literal_seq_end == '\\';
				literal_seq_isutf8 |= lit >= 0x80;
				old_literal_seq_end = literal_seq_end;
				literal_seq_end     = self->rec_parser.rep_pos;
				++literal_seq_length;
			}
			if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8)
				literal_seq_isutf8 = false; /* They're always just bytes! */

			/* Encode the literal sequence */
			error = re_compiler_compile_literal_seq(self,
			                                    literal_seq_start,
			                                    literal_seq_end,
			                                    literal_seq_length,
			                                    literal_seq_hasesc,
			                                    literal_seq_isutf8);
			if unlikely(error != RE_NOERROR)
				return error;
#ifndef __OPTIMIZE_SIZE__
			if (seq_followed_by_suffix)
				goto again; /* Go ahead and compile the literal for the suffix that will follow */
#endif /* !__OPTIMIZE_SIZE__ */
		}
		break;

	}
	return RE_NOERROR;
err_nomem:
	return RE_ESPACE;
}


#define RE_EPSILON_JMP_ENCODE(baseop, offset) ((baseop) + 1 + (offset) - 3)
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 3) == REOP_GROUP_MATCH_J3);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 4) == REOP_GROUP_MATCH_J4);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 5) == REOP_GROUP_MATCH_J5);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 6) == REOP_GROUP_MATCH_J6);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 7) == REOP_GROUP_MATCH_J7);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 8) == REOP_GROUP_MATCH_J8);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 9) == REOP_GROUP_MATCH_J9);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 10) == REOP_GROUP_MATCH_J10);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 3) == REOP_GROUP_END_J3);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 4) == REOP_GROUP_END_J4);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 5) == REOP_GROUP_END_J5);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 6) == REOP_GROUP_END_J6);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 7) == REOP_GROUP_END_J7);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 8) == REOP_GROUP_END_J8);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 9) == REOP_GROUP_END_J9);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 10) == REOP_GROUP_END_J10);


PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC re_compiler_set_group_epsilon_jmp)(uint8_t *p_group_instruction,
                                                  uint8_t num_bytes_skip_if_empty) {
	assert(num_bytes_skip_if_empty >= 3 && num_bytes_skip_if_empty <= 10);
	assertf(*p_group_instruction == REOP_GROUP_MATCH ||
	        *p_group_instruction == REOP_GROUP_END,
	        "*p_group_instruction = %#I8x",
	        *p_group_instruction);
	*p_group_instruction = RE_EPSILON_JMP_ENCODE(*p_group_instruction, num_bytes_skip_if_empty);
}


/* Compile a repeat expression */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_repeat)(struct re_compiler *__restrict self,
                                           uint8_t interval_min,
                                           uint8_t interval_max,
                                           bool interval_max_is_unbounded,
                                           bool expression_matches_epsilon) {
	size_t expr_size;

	/* Figure out the size of the affected expression */
	expr_size = (size_t)(self->rec_cpos - self->rec_estart);
	assert(!((uintptr_t)self->rec_cbase & 1));

	/* When many are accepted, then `interval_max' is infinite */
	if (interval_max_is_unbounded) {
		if (interval_min == 0) {
			byte_t *writer, *label_1, *label_2;
			/* >> "X*"           REOP_JMP_ONFAIL 2f
			 * >>             1: <X>     // Last instruction is `REOP_*_Jn(N)' transformed to jump to `2f'
			 * >>                REOP_JMP_AND_RETURN_ONFAIL 1b
			 * >>             2: */
			if unlikely(!re_compiler_require(self, 6))
				goto err_nomem;

			/* Make space for code we want to insert in the front */
			writer = self->rec_estart;
			memmoveup(writer + 3, writer, expr_size);

			/* REOP_JMP_ONFAIL 2f */
			*writer++ = REOP_JMP_ONFAIL;
			label_2 = writer + 2 + expr_size + 3;
			int16_at(writer) = (int16_t)(label_2 - (writer + 2));
			writer += 2;

			/* This is where the "1:" is in the pseudo-code */
			label_1 = writer;
			writer += expr_size;
			if (expression_matches_epsilon)
				re_compiler_set_group_epsilon_jmp(writer - 2, 3);

			/* REOP_JMP_AND_RETURN_ONFAIL 1b */
			*writer++ = REOP_JMP_AND_RETURN_ONFAIL;
			int16_at(writer) = (int16_t)(label_1 - (writer + 2));
			writer += 2;
			self->rec_cpos = writer;
			goto done_suffix;
		} else if (interval_min == 1) {
			byte_t *writer;
			/* >> "X+"        1: <X>     // Last instruction is `REOP_*_Jn(N)' transformed to jump to `2f'
			 * >>                REOP_JMP_AND_RETURN_ONFAIL 1b
			 * >>             2: */
			if unlikely(!re_compiler_require(self, 3))
				goto err_nomem;

			/* REOP_JMP_AND_RETURN_ONFAIL 1b */
			writer = self->rec_cpos;
			if (expression_matches_epsilon)
				re_compiler_set_group_epsilon_jmp(writer - 2, 3);
			*writer++ = REOP_JMP_AND_RETURN_ONFAIL;
			int16_at(writer) = (int16_t)(self->rec_estart - (writer + 2));
			writer += 2;
			self->rec_cpos = writer;
			goto done_suffix;
		} else {
			uint8_t var_id;
			byte_t *writer, *label_1;
			/* >> "X{n,}"        REOP_SETVAR  {VAR = (n - 1)}
			 * >>             1: <X>     // Last instruction is `REOP_*_Jn(N)' transformed to jump to `2f'
			 * >>                REOP_DEC_JMP {VAR}, 1b
			 * >>                REOP_JMP_AND_RETURN_ONFAIL 1b
			 * >>             2: */
			if unlikely(!re_compiler_require(self, 10))
				goto err_nomem;
			if unlikely(!re_compiler_allocvar(self, &var_id))
				goto err_esize;

			/* Make space for code we want to insert in the front */
			writer = self->rec_estart;
			memmoveup(writer + 3, writer, expr_size);

			/* REOP_SETVAR  {VAR = (n - 1)} */
			*writer++ = REOP_SETVAR;
			*writer++ = var_id;
			*writer++ = interval_min - 1;

			/* This is where the "1:" is in the pseudo-code */
			label_1 = writer;
			writer += expr_size;
			if (expression_matches_epsilon)
				re_compiler_set_group_epsilon_jmp(writer - 2, 7);

			/* REOP_DEC_JMP {VAR}, 1b */
			*writer++ = REOP_DEC_JMP;
			*writer++ = var_id;
			int16_at(writer) = (int16_t)(label_1 - (writer + 2));
			writer += 2;

			/* REOP_JMP_AND_RETURN_ONFAIL 1b */
			*writer++ = REOP_JMP_AND_RETURN_ONFAIL;
			int16_at(writer) = (int16_t)(label_1 - (writer + 2));
			writer += 2;

			self->rec_cpos = writer;
			goto done_suffix;
		}
		__builtin_unreachable();
	}

	if (interval_max == 0) {
		/* >> "X{0}"         REOP_NOP        // Or just no instruction at all
		 * -> Simply delete the current expression
		 *
		 * NOTE: If the current expression defined groups, then we have to
		 *       re-insert the `REOP_GROUP_START / REOP_GROUP_END' opcodes
		 *       so that those groups are properly matched by `regexec(3)' */
		byte_t *writer = self->rec_estart;
		byte_t *reader = self->rec_estart;
		for (; reader < self->rec_cpos; reader = re_opcode_next(reader)) {
			byte_t opcode = *reader;
			if (opcode >= REOP_GROUP_END_JMIN && opcode <= REOP_GROUP_END_JMAX)
				opcode = REOP_GROUP_END; /* Undo Jn opcode transformation (groups are never followed by a loop suffix) */
			if (opcode == REOP_GROUP_START || opcode == REOP_GROUP_END) {
				uint8_t gid = reader[1];
				*writer++   = opcode; /* Group start/end instruction */
				*writer++   = gid;    /* Reference to group # */
				if (gid < lengthof(self->rec_grpinfo)) {
					/* The group can always be empty now */
					self->rec_grpinfo[gid] |= RE_COMPILER_GRPINFO_EPSILON;
				}
			}
		}
		self->rec_cpos = writer;
		goto done_suffix;
	}

	if (interval_min == 1) {
		uint8_t var_id;
		byte_t *writer, *label_1;

		/* Check for special (and simple) case: always match exactly 1 */
		if (interval_max == 1)
			goto done_suffix;

		/* >> "X{1,m}"       REOP_SETVAR  {VAR = (m - 1)}
		 * >>            1:  <X>     // Last instruction is `REOP_*_Jn(N)' transformed to jump to `2f'
		 * >>                REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b
		 * >>            2: */
		if unlikely(!re_compiler_require(self, 7))
			goto err_nomem;
		if unlikely(!re_compiler_allocvar(self, &var_id))
			goto err_esize;

		/* Make space for code we want to insert in the front */
		writer = self->rec_estart;
		memmoveup(writer + 3, writer, expr_size);

		/* REOP_SETVAR  {VAR = (m - 1)} */
		*writer++ = REOP_SETVAR;
		*writer++ = var_id;
		*writer++ = interval_max - 1;

		/* This is where the "1:" is in the pseudo-code */
		label_1 = writer;
		writer += expr_size;
		if (expression_matches_epsilon)
			re_compiler_set_group_epsilon_jmp(writer - 2, 4);

		/* REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b */
		*writer++ = REOP_DEC_JMP_AND_RETURN_ONFAIL;
		*writer++ = var_id;
		int16_at(writer) = (int16_t)(label_1 - (writer + 2));
		writer += 2;

		self->rec_cpos = writer;
		goto done_suffix;
	}

	if (interval_min == 0) {
		if (interval_max == 1) {
			/* >> "X?"           REOP_JMP_ONFAIL 1f
			 * >>                <X>
			 * >>             1: */
			byte_t *writer;
			if unlikely(!re_compiler_require(self, 3))
				goto err_nomem;
			self->rec_cpos = (byte_t *)mempmoveup(self->rec_estart + 3, self->rec_estart, expr_size);
			writer = self->rec_estart;
			*writer++ = REOP_JMP_ONFAIL;
			int16_at(writer) = (int16_t)expr_size;
			goto done_suffix;
		} else {
			uint8_t var_id;
			byte_t *writer, *label_1, *label_2;
			/* >> "X{0,m}"       REOP_JMP_ONFAIL 2f
			 * >>                REOP_SETVAR  {VAR = (m - 1)}
			 * >>            1:  <X>     // Last instruction is `REOP_*_Jn(N)' transformed to jump to `2f'
			 * >>                REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b
			 * >>            2: */
			if unlikely(!re_compiler_require(self, 10))
				goto err_nomem;
			if unlikely(!re_compiler_allocvar(self, &var_id))
				goto err_esize;

			/* Make space for code we want to insert in the front */
			writer = self->rec_estart;
			memmoveup(writer + 6, writer, expr_size);

			/* Figure out the location of `label_2' */
			label_2 = writer;
			label_2 += 3; /* REOP_JMP_ONFAIL 2f */
			label_2 += 3; /* REOP_SETVAR  {VAR = (m - 1)} */
			label_2 += expr_size;
			label_2 += 4; /* REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b */

			/* REOP_JMP_ONFAIL 2f */
			*writer++ = REOP_JMP_ONFAIL;
			int16_at(writer) = (int16_t)(label_2 - (writer + 2));
			writer += 2;

			/* REOP_SETVAR  {VAR = (m - 1)} */
			*writer++ = REOP_SETVAR;
			*writer++ = var_id;
			*writer++ = interval_max - 1;

			/* This is where the "1:" is in the pseudo-code */
			label_1 = writer;
			writer += expr_size;
			if (expression_matches_epsilon)
				re_compiler_set_group_epsilon_jmp(writer - 2, 4);

			/* REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b */
			*writer++ = REOP_DEC_JMP_AND_RETURN_ONFAIL;
			*writer++ = var_id;
			int16_at(writer) = (int16_t)(label_1 - (writer + 2));
			writer += 2;

			self->rec_cpos = writer;
			goto done_suffix;
		}
		__builtin_unreachable();
	}

	if (interval_min == interval_max) {
		uint8_t var_id;
		byte_t *writer, *label_1;
		/* >> "X{n}"         REOP_SETVAR  {VAR = (n - 1)}
		 * >>             1: <X>
		 * >>                REOP_DEC_JMP {VAR}, 1b */
		if unlikely(!re_compiler_require(self, 7))
			goto err_nomem;
		if unlikely(!re_compiler_allocvar(self, &var_id))
			goto err_esize;

		/* Make space for code we want to insert in the front */
		writer = self->rec_estart;
		memmoveup(writer + 3, writer, expr_size);

		/* REOP_SETVAR  {VAR = (n - 1)} */
		*writer++ = REOP_SETVAR;
		*writer++ = var_id;
		*writer++ = interval_min - 1;

		/* This is where the "1:" is in the pseudo-code */
		label_1 = writer;
		writer += expr_size;

		/* REOP_DEC_JMP {VAR}, 1b */
		*writer++ = REOP_DEC_JMP;
		*writer++ = var_id;
		int16_at(writer) = (int16_t)(label_1 - (writer + 2));
		writer += 2;

		self->rec_cpos = writer;
		goto done_suffix;
	}

	/* >> "X{n,m}"       REOP_SETVAR  {VAR1 = n - 1}
	 * >>                REOP_SETVAR  {VAR2 = (m - n)}
	 * >>            1:  <X>     // Last instruction is `REOP_*_Jn(N)' transformed to jump to `2f'
	 * >>                REOP_DEC_JMP {VAR1}, 1b
	 * >>                REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR2}, 1b
	 * >>            2: */
	{
		uint8_t var1_id, var2_id;
		byte_t *writer, *label_1;
		if unlikely(!re_compiler_require(self, 14))
			goto err_nomem;

		/* Allocate variable IDs */
		if unlikely(!re_compiler_allocvar(self, &var1_id))
			goto err_esize;
		if unlikely(!re_compiler_allocvar(self, &var2_id))
			goto err_esize;

		/* Make space for code we want to insert in the front */
		writer = self->rec_estart;
		memmoveup(writer + 6, writer, expr_size);

		/* REOP_SETVAR  {VAR1 = n - 1} */
		*writer++ = REOP_SETVAR;
		*writer++ = var1_id;
		*writer++ = interval_min - 1;

		/* REOP_SETVAR  {VAR2 = (m - n)} */
		*writer++ = REOP_SETVAR;
		*writer++ = var2_id;
		*writer++ = interval_max - interval_min;

		/* This is where the "1:" is in the pseudo-code */
		label_1 = writer;
		writer += expr_size;
		if (expression_matches_epsilon)
			re_compiler_set_group_epsilon_jmp(writer - 2, 8);

		/* REOP_DEC_JMP {VAR1}, 1b */
		*writer++ = REOP_DEC_JMP;
		*writer++ = var1_id;
		int16_at(writer) = (int16_t)(label_1 - (writer + 2));
		writer += 2;

		/* REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR2}, 1b */
		*writer++ = REOP_DEC_JMP_AND_RETURN_ONFAIL;
		*writer++ = var2_id;
		int16_at(writer) = (int16_t)(label_1 - (writer + 2));
		writer += 2;

		self->rec_cpos = writer;
	}

done_suffix:
	return RE_NOERROR;
err_nomem:
	return RE_ESPACE;
err_esize:
	return RE_ESIZE;
}

/* Compile prefix expressions: literals, '[...]' and '(...)'
 * @param: prefix_status: Either `RE_NOERROR', or `RE_COMPILER_COMPILE_PREFIX__AFTER_EPSILON_GROUP'
 */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_suffix)(struct re_compiler *__restrict self,
                                           re_errno_t prefix_status) {
	re_token_t tok;
	char const *tokstart;
	assertf(self->rec_estart <= self->rec_cpos,
	        "self->rec_estart: %p\n"
	        "self->rec_cpos:   %p",
	        self->rec_estart,
	        self->rec_cpos);

	/* Start parsing the current expression */
	tokstart = self->rec_parser.rep_pos;
	tok      = re_compiler_yield(self);
	if (RE_TOKEN_ISSUFFIX(tok)) {
		re_errno_t error;
		uint8_t interval_min = 1, interval_max = 1;
		bool accept_zero = false; /* true if `0'   is accepted (encountered '*' or '?') */
		bool accept_many = false; /* true if `> 1' is accepted (encountered '*' or '+') */
		for (;;) {
			if (tok == RE_TOKEN_STARTINTERVAL) {
				/* Parse an interval */
				errno_t parse_errno = 0;
				uint32_t new_interval_min, new_interval_max;
				new_interval_min = strtou32_r(self->rec_parser.rep_pos,
				                              (char **)&self->rec_parser.rep_pos,
				                              10, &parse_errno);
				if unlikely(parse_errno != 0)
					goto err_badinterval;
				new_interval_max = new_interval_min;
				if (*self->rec_parser.rep_pos == ',') {
					++self->rec_parser.rep_pos;
					if ((self->rec_parser.rep_syntax & RE_SYNTAX_NO_BK_BRACES)
					    ? (self->rec_parser.rep_pos[0] == '}')
					    : (self->rec_parser.rep_pos[0] == '\0' && self->rec_parser.rep_pos[1] == '}')) {
						accept_many = true;
					} else {
						new_interval_max = strtou32_r(self->rec_parser.rep_pos,
						                              (char **)&self->rec_parser.rep_pos,
						                              10, &parse_errno);
						if unlikely(parse_errno != 0)
							goto err_badinterval;
					}
				}
				if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_BK_BRACES) {
					if (self->rec_parser.rep_pos[0] != '}')
						goto err_badinterval;
					++self->rec_parser.rep_pos;
				} else {
					if (self->rec_parser.rep_pos[0] != '\\')
						goto err_badinterval;
					if (self->rec_parser.rep_pos[1] != '}')
						goto err_badinterval;
					self->rec_parser.rep_pos += 2;
				}
				if unlikely(new_interval_min > new_interval_max)
					goto err_badinterval;
				if unlikely(new_interval_max > UINT8_MAX)
					goto err_badinterval;
				/* Merge new interval with already-parsed interval */
				if unlikely(!accept_zero && OVERFLOW_UMUL(interval_min, (uint8_t)new_interval_min, &interval_min))
					goto err_badinterval;
				if unlikely(!accept_many && OVERFLOW_UMUL(interval_max, (uint8_t)new_interval_max, &interval_max))
					goto err_badinterval;
			} else {
				accept_zero |= tok == RE_TOKEN_STAR || tok == RE_TOKEN_QMARK;
				accept_many |= tok == RE_TOKEN_STAR || tok == RE_TOKEN_PLUS;
			}
			tokstart = self->rec_parser.rep_pos;
			tok      = re_compiler_yield(self);
			if (!RE_TOKEN_ISSUFFIX(tok)) {
				self->rec_parser.rep_pos = tokstart;
				break;
			}
		}
		/* When zero is accepted, then the interval always starts at 0 */
		if (accept_zero)
			interval_min = 0;

		/* Encode the interval */
		error = re_compiler_compile_repeat(self, interval_min, interval_max, accept_many,
		                                   prefix_status == RE_COMPILER_COMPILE_PREFIX__AFTER_EPSILON_GROUP);
		if unlikely(error != RE_NOERROR)
			return error;
	} else {
		self->rec_parser.rep_pos = tokstart;
	}
/*done_suffix:*/
	/* Following a suffix, the expression start becomes invalid */
	DBG_memset(&self->rec_estart, 0xcc, sizeof(self->rec_estart));
	return RE_NOERROR;
err_badinterval:
	return RE_BADBR;
}


PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC re_compiler_thread_fwd_jump)(byte_t *__restrict p_jmp_instruction) {
	byte_t *target_instruction;
	int16_t delta;
	assert(p_jmp_instruction[0] == REOP_JMP);
	delta = int16_at(&p_jmp_instruction[1]);
	assertf(delta >= 0, "delta: %I16d", delta);
	target_instruction = p_jmp_instruction + 3 + delta;
	while (*target_instruction == REOP_NOP)
		++target_instruction;

	/* Recursively thread target jumps. */
	if (target_instruction[0] == REOP_JMP) {
		int16_t target_delta;
		int32_t total_delta;
		re_compiler_thread_fwd_jump(target_instruction);
		target_delta = int16_at(&target_instruction[1]);
		assert(target_delta >= 0);
		total_delta = delta + 3 + target_delta;
		if (total_delta <= INT16_MAX) {
			/* Able to thread this jump! */
			int16_at(&p_jmp_instruction[1]) = total_delta;
		}
	}
}


/* Compile a sequence of prefix/suffix expressions, as well as '|' */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_alternation)(struct re_compiler *__restrict self) {
	re_errno_t error;
	size_t initial_alternation_jmpoff;
	size_t previous_alternation_deltaoff;
	size_t current_alternation_startoff;
	re_token_t tok;
	char const *tokstart;
	initial_alternation_jmpoff    = (size_t)-1;
	previous_alternation_deltaoff = (size_t)-1;

again:
	current_alternation_startoff = (size_t)(self->rec_cpos - self->rec_cbase);

	/* Compile expression sequences. */
	for (;;) {
		char const *old_tokptr;
		old_tokptr = self->rec_parser.rep_pos;

		/* Parse an expression */
		error = re_compiler_compile_prefix(self);
		if unlikely(error != RE_NOERROR &&
		            error != RE_COMPILER_COMPILE_PREFIX__AFTER_EPSILON_GROUP)
			goto err;
		error = re_compiler_compile_suffix(self, error);
		if unlikely(error != RE_NOERROR)
			goto err;

		/* Check if we're moving forward in the pattern */
		assert(self->rec_parser.rep_pos >= old_tokptr);
		if (self->rec_parser.rep_pos == old_tokptr)
			break; /* Unchanged parser position -> we're at a token that cannot be processed. */
	}

	/* Check what's the next token */
	tokstart = self->rec_parser.rep_pos;
	tok      = re_compiler_yield(self);
	if (tok != RE_TOKEN_ALTERNATION) {
		/* Rewind to start of token */
		self->rec_parser.rep_pos = tokstart;
		/* Fill in the delta of the `REOP_JMP ...' from a preceding alternation. */
		if (previous_alternation_deltaoff != (size_t)-1) {
			byte_t *previous_alternation_deltaptr;
			int16_t previous_alternation_skipdelta;
			previous_alternation_deltaptr  = self->rec_cbase + previous_alternation_deltaoff;
			previous_alternation_skipdelta = (int16_t)(self->rec_cpos - (previous_alternation_deltaptr + 2));
			assert(previous_alternation_skipdelta >= 0);
			int16_at(previous_alternation_deltaptr) = previous_alternation_skipdelta;
		}
	} else {
		byte_t *current_alternation_startptr;
		size_t current_alternation_size;

		/* Ensure that we've got enough memory for `REOP_JMP' and `REOP_JMP_ONFAIL' */
		if unlikely(!re_compiler_require(self, 6))
			goto err_nomem;
		current_alternation_startptr = self->rec_cbase + current_alternation_startoff;
		current_alternation_size     = (size_t)(self->rec_cpos - current_alternation_startptr);
		memmoveup(current_alternation_startptr + 3,
		          current_alternation_startptr,
		          current_alternation_size);

		/* Insert the leading `REOP_JMP_ONFAIL' that points to the next alternation */
		*current_alternation_startptr++ = REOP_JMP_ONFAIL;
		int16_at(current_alternation_startptr) = (int16_t)(current_alternation_size + 3);
		current_alternation_startptr += 2;
		current_alternation_startptr += current_alternation_size;

		/* Write  the `REOP_JMP' instruction after the alternation
		 * Note that the offset of this instruction will be filled
		 * after the next alternation has been compiled. */
		if (initial_alternation_jmpoff == (size_t)-1) {
			/* Remember the first jump location so we can jump-thread-optimize it later! */
			initial_alternation_jmpoff = (size_t)(current_alternation_startptr - self->rec_cbase);
		}

		/* Fill in the delta of the `REOP_JMP ...' from a preceding alternation. */
		if (previous_alternation_deltaoff != (size_t)-1) {
			byte_t *previous_alternation_deltaptr;
			int16_t previous_alternation_skipdelta;
			previous_alternation_deltaptr  = self->rec_cbase + previous_alternation_deltaoff;
			previous_alternation_skipdelta = (int16_t)(current_alternation_startptr - (previous_alternation_deltaptr + 2));
			assert(previous_alternation_skipdelta >= 0);
			int16_at(previous_alternation_deltaptr) = previous_alternation_skipdelta;
		}

		*current_alternation_startptr++ = REOP_JMP;
		previous_alternation_deltaoff = (size_t)(current_alternation_startptr - self->rec_cbase);
		DBG_memset(current_alternation_startptr, 0xcc, 2); /* UNDEFINED! (filled later) */
		current_alternation_startptr += 2;
		self->rec_cpos = current_alternation_startptr;
		goto again;
	}

	if (initial_alternation_jmpoff != (size_t)-1) {
		byte_t *initial_alternation_jmp;
		/* Up until now, we've compiled the expression "X|Y|Z" as:
		 * >>    REOP_JMP_ONFAIL  1f
		 * >>    <X>
		 * >>    REOP_JMP         2f // << `initial_alternation_jmp' points to this instruction
		 * >> 1: REOP_JMP_ONFAIL  3f
		 * >>    <Y>
		 * >> 2: REOP_JMP         4f
		 * >> 3: <Z>
		 * >> 4:
		 *
		 * But  now we want to optimize this by (trying to) thread these `REOP_JMP' into
		 * each  other, such that rather than jumping from one to the next, all jumps go
		 * as far forward in the expression as possible, (or at least as far as possible
		 * without causing a signed int16 overflow) */

		/* Make sure that the end of the jump-chain isn't out-of-bounds */
		if unlikely(!re_compiler_require(self, 1))
			goto err_nomem;
		/* Anything  that isn't `REOP_JMP'  or `REOP_NOP' works here;
		 * (needed as end-marker for `re_compiler_thread_fwd_jump()') */
		*self->rec_cpos = REOP_MATCHED;

		initial_alternation_jmp = self->rec_cbase + initial_alternation_jmpoff;
		re_compiler_thread_fwd_jump(initial_alternation_jmp);
	}

	return RE_NOERROR;
err:
	return error;
err_nomem:
	return RE_ESPACE;
}


/* Parse and compile the pattern given to `self' to generate code.
 * Even upon error, `self' remains  in a valid state (except  that
 * you're  not allowed to  call `re_compiler_compile()' again), so
 * that the caller has to invoke `re_compiler_fini()' in order  to
 * perform cleanup.
 * Upon success, members of `self' are initialized as:
 * - *rec_parser.rep_pos    == '\0'
 * - rec_parser.rep_pos     == strend(rec_parser.rep_pat)
 * - rec_parser.rep_syntax  == <unchanged>
 * - rec_parser.rec_cbase   == <pointer-to-struct re_code>
 * - rec_parser.rec_estart  == <undefined>
 * - rec_parser.rec_cpos    == <undefined>
 * - rec_parser.rec_cend    == <code-end-pointer (1 past the `REOP_MATCHED[_PERFECT]' opcode)>
 * - rec_parser.rec_ngrp    == <greaters-referenced-group + 1>
 * - rec_parser.rec_nvar    == <greaters-referenced-var + 1>
 * - rec_parser.rec_grpinfo == <undefined>
 * @return: RE_NOERROR: Success
 * @return: RE_BADPAT:  General pattern syntax error.
 * @return: RE_ECTYPE:  Invalid/unknown character class name.
 * @return: RE_EESCAPE: Trailing backslash.
 * @return: RE_ESUBREG: Invalid back reference.
 * @return: RE_EBRACK:  Unmatched '['.
 * @return: RE_EPAREN:  Unmatched '('.
 * @return: RE_EBRACE:  Unmatched '{'.
 * @return: RE_BADBR:   Invalid contents of '{...}'.
 * @return: RE_ERANGE:  Invalid range end (e.g. '[z-a]').
 * @return: RE_ESPACE:  Out of memory.
 * @return: RE_BADRPT:  Nothing is preceding '+', '*', '?' or '{'.
 * @return: RE_EEND:    Unexpected end of pattern.
 * @return: RE_ESIZE:   Compiled pattern bigger than 2^16 bytes.
 * @return: RE_ERPAREN: Unmatched ')' (only when `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' was set) */
INTERN WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC libre_compiler_compile)(struct re_compiler *__restrict self) {
	re_errno_t error;
	uint8_t finish_opcode;
	re_token_t trailing_token;

	/* Make space for the `struct re_code' header */
	if unlikely(!re_compiler_require(self, offsetof(struct re_code, rc_code)))
		goto err_nomem;
	self->rec_cpos += offsetof(struct re_code, rc_code);

	/* Do the actual compilation */
	error = re_compiler_compile_alternation(self);
	if unlikely(error != RE_NOERROR)
		goto err;

	/* Check that everything has been parsed. */
	trailing_token = re_compiler_yield(self);
	if unlikely(trailing_token != RE_TOKEN_EOF) {
		if (trailing_token == RE_TOKEN_ENDGROUP)
			return RE_ERPAREN;
		return RE_BADPAT;
	}

	/* Terminate the expression with a `REOP_MATCHED' opcode */
	finish_opcode = REOP_MATCHED;
	if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_POSIX_BACKTRACKING)
		finish_opcode = REOP_MATCHED_PERFECT;
	if (!re_compiler_putc(self, finish_opcode))
		goto err_nomem;

	/* (try to) free unused memory from the code-buffer. */
	if likely(self->rec_cpos < self->rec_cend) {
		byte_t *newbase;
		size_t reqsize;
		reqsize = (size_t)(self->rec_cpos - self->rec_cbase);
		newbase = (byte_t *)realloc(self->rec_cbase, reqsize);
		if likely(newbase) {
			self->rec_cbase  = newbase;
			self->rec_cend   = newbase + reqsize;
		}
	}
	DBG_memset(&self->rec_cpos, 0xcc, sizeof(self->rec_cpos));
	DBG_memset(&self->rec_estart, 0xcc, sizeof(self->rec_estart));

	/* Fill in the regex code header. */
	{
		struct re_code *header;
		header = (struct re_code *)self->rec_cbase;
		header->rc_ngrps = self->rec_ngrp;
		header->rc_nvars = self->rec_nvar;
		/* TODO: Properly calculate the fastmap (instead of dispatching everything at PC=0) */
		/* TODO: Properly calculate the min/max match sizes */
		header->rc_minmatch = 0;
		header->rc_maxmatch = SIZE_MAX;
		bzero(header->rc_fmap, sizeof(header->rc_fmap));
	}

	return RE_NOERROR;
err_nomem:
	error = RE_ESPACE;
err:
	if (error == RE_ESPACE) {
		if ((size_t)(self->rec_cend - self->rec_cbase) >= RE_COMP_MAXSIZE)
			error = RE_ESIZE;
	}
	return error;
}



#ifndef NDEBUG
/* Print a disassembly of `self' (for debugging) */
INTERN NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_code_disasm)(struct re_code const *__restrict self,
                                  pformatprinter printer, void *arg) {
#define DO(x)                         \
	do {                              \
		if unlikely((temp = (x)) < 0) \
			goto err;                 \
		result += temp;               \
	}	__WHILE0
#define PRINT(x)    DO((*printer)(arg, x, COMPILER_STRLEN(x)))
#define printf(...) DO(format_printf(printer, arg, __VA_ARGS__))
	byte_t const *code, *next;
	ssize_t temp, result = 0;
	/* TODO: Print fast-map */
	printf("match: {%" PRIuSIZ "-", self->rc_minmatch);
	if (self->rc_maxmatch == SIZE_MAX) {
		PRINT("inf}\n");
	} else {
		printf("%" PRIuSIZ "}\n", self->rc_minmatch);
	}
	printf("ngrps: %" PRIu16 "\n"
	       "nvars: %" PRIu16 "\n",
	       self->rc_ngrps,
	       self->rc_nvars);
	for (code = self->rc_code;; code = next) {
		size_t offset;
		byte_t opcode;
		char const *opcode_repr;
		next   = re_opcode_next(code);
		offset = (size_t)(code - self->rc_code);
		opcode = *code++;
		printf("%#.4" PRIxSIZ ": ", offset);
		switch (opcode) {

		case REOP_EXACT: {
			uint8_t len = *code++;
			printf("exact %$q", (size_t)len, code);
		}	break;

		case REOP_EXACT_ASCII_ICASE: {
			uint8_t len = *code++;
			printf("exact_ascii_icase %$q", (size_t)len, code);
		}	break;

		case REOP_EXACT_UTF8_ICASE: {
			++code;
			printf("exact_ascii_icase %$q", (size_t)(next - code), code);
		}	break;

		case REOP_CHAR: {
			printf("char %$q", (size_t)1, code);
		}	break;

		case REOP_CHAR2: {
			printf("char2 %$q", (size_t)2, code);
		}	break;

		case REOP_CONTAINS_UTF8: {
			++code;
			printf("contains_utf8 %$q", (size_t)(next - code), code);
		}	break;

		case REOP_CONTAINS_UTF8_NOT: {
			++code;
			printf("contains_utf8_not %$q", (size_t)(next - code), code);
		}	break;

		//TODO: case REOP_BITSET:
		//TODO: case REOP_BITSET_NOT:
		//TODO: case REOP_BITSET_UTF8_NOT:
		//TODO: case REOP_GROUP_MATCH:
		//TODO: case REOP_GROUP_MATCH_J3:
		//TODO: case REOP_GROUP_MATCH_J4:
		//TODO: case REOP_GROUP_MATCH_J5:
		//TODO: case REOP_GROUP_MATCH_J6:
		//TODO: case REOP_GROUP_MATCH_J7:
		//TODO: case REOP_GROUP_MATCH_J8:
		//TODO: case REOP_GROUP_MATCH_J9:
		//TODO: case REOP_GROUP_MATCH_J10:
		//TODO: case REOP_ASCII_ISDIGIT_EQ:
		//TODO: case REOP_ASCII_ISDIGIT_NE:
		//TODO: case REOP_ASCII_ISDIGIT_LO:
		//TODO: case REOP_ASCII_ISDIGIT_LE:
		//TODO: case REOP_ASCII_ISDIGIT_GR:
		//TODO: case REOP_ASCII_ISDIGIT_GE:
		//TODO: case REOP_UTF8_ISDIGIT_EQ:
		//TODO: case REOP_UTF8_ISDIGIT_NE:
		//TODO: case REOP_UTF8_ISDIGIT_LO:
		//TODO: case REOP_UTF8_ISDIGIT_LE:
		//TODO: case REOP_UTF8_ISDIGIT_GR:
		//TODO: case REOP_UTF8_ISDIGIT_GE:
		//TODO: case REOP_UTF8_ISNUMERIC_EQ:
		//TODO: case REOP_UTF8_ISNUMERIC_NE:
		//TODO: case REOP_UTF8_ISNUMERIC_LO:
		//TODO: case REOP_UTF8_ISNUMERIC_LE:
		//TODO: case REOP_UTF8_ISNUMERIC_GR:
		//TODO: case REOP_UTF8_ISNUMERIC_GE:

		case REOP_GROUP_START: {
			uint8_t gid = *code++;
			printf("group_start %" PRIu8, gid);
		}	break;

		case REOP_GROUP_END: {
			uint8_t gid = *code++;
			printf("group_end %" PRIu8, gid);
		}	break;

		case REOP_GROUP_END_JMIN ... REOP_GROUP_END_JMAX: {
			uint8_t gid       = *code++;
			byte_t const *jmp = code + REOP_GROUP_END_Joff(opcode);
			printf("group_end %" PRIu8 ", @%#.4" PRIxSIZ,
			       gid, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_JMP_ONFAIL: {
			byte_t const *jmp = code + 2 + int16_at(code);
			printf("jmp_onfail @%#.4" PRIxSIZ, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_JMP: {
			byte_t const *jmp = code + 2 + int16_at(code);
			printf("jmp @%#.4" PRIxSIZ, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_JMP_AND_RETURN_ONFAIL: {
			byte_t const *jmp = code + 2 + int16_at(code);
			printf("jmp_and_return_onfail @%#.4" PRIxSIZ, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_DEC_JMP: {
			uint8_t varid     = *code++;
			byte_t const *jmp = code + 2 + int16_at(code);
			printf("dec_jmp %" PRIu8 ", @%#.4" PRIxSIZ, varid, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_DEC_JMP_AND_RETURN_ONFAIL: {
			uint8_t varid     = *code++;
			byte_t const *jmp = code + 2 + int16_at(code);
			printf("dec_jmp_and_return_onfail %" PRIu8 ", @%#.4" PRIxSIZ, varid, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_SETVAR: {
			uint8_t varid = *code++;
			uint8_t value = *code++;
			printf("setvar %" PRIu8 ", %" PRIu8, varid, value);
		}	break;

#define SIMPLE_OPCODE(opcode, repr) \
		case opcode:                \
			opcode_repr = repr;     \
			goto do_print_opcode_repr
		SIMPLE_OPCODE(REOP_ANY, "any");
		SIMPLE_OPCODE(REOP_ANY_NOTLF, "any_notlf");
		SIMPLE_OPCODE(REOP_ANY_NOTNUL, "any_notnul");
		SIMPLE_OPCODE(REOP_ANY_NOTNUL_NOTLF, "any_notnul_notlf");
		SIMPLE_OPCODE(REOP_ANY_NOTNUL_NOTLF_UTF8, "any_notnul_notlf_utf8");
		SIMPLE_OPCODE(REOP_ASCII_ISCNTRL, "ascii_iscntrl");
		SIMPLE_OPCODE(REOP_ASCII_ISCNTRL_NOT, "ascii_iscntrl_not");
		SIMPLE_OPCODE(REOP_ASCII_ISSPACE, "ascii_isspace");
		SIMPLE_OPCODE(REOP_ASCII_ISSPACE_NOT, "ascii_isspace_not");
		SIMPLE_OPCODE(REOP_ASCII_ISUPPER, "ascii_isupper");
		SIMPLE_OPCODE(REOP_ASCII_ISUPPER_NOT, "ascii_isupper_not");
		SIMPLE_OPCODE(REOP_ASCII_ISLOWER, "ascii_islower");
		SIMPLE_OPCODE(REOP_ASCII_ISLOWER_NOT, "ascii_islower_not");
		SIMPLE_OPCODE(REOP_ASCII_ISALPHA, "ascii_isalpha");
		SIMPLE_OPCODE(REOP_ASCII_ISALPHA_NOT, "ascii_isalpha_not");
		SIMPLE_OPCODE(REOP_ASCII_ISDIGIT, "ascii_isdigit");
		SIMPLE_OPCODE(REOP_ASCII_ISDIGIT_NOT, "ascii_isdigit_not");
		SIMPLE_OPCODE(REOP_ASCII_ISXDIGIT, "ascii_isxdigit");
		SIMPLE_OPCODE(REOP_ASCII_ISXDIGIT_NOT, "ascii_isxdigit_not");
		SIMPLE_OPCODE(REOP_ASCII_ISALNUM, "ascii_isalnum");
		SIMPLE_OPCODE(REOP_ASCII_ISALNUM_NOT, "ascii_isalnum_not");
		SIMPLE_OPCODE(REOP_ASCII_ISPUNCT, "ascii_ispunct");
		SIMPLE_OPCODE(REOP_ASCII_ISPUNCT_NOT, "ascii_ispunct_not");
		SIMPLE_OPCODE(REOP_ASCII_ISGRAPH, "ascii_isgraph");
		SIMPLE_OPCODE(REOP_ASCII_ISGRAPH_NOT, "ascii_isgraph_not");
		SIMPLE_OPCODE(REOP_ASCII_ISPRINT, "ascii_isprint");
		SIMPLE_OPCODE(REOP_ASCII_ISPRINT_NOT, "ascii_isprint_not");
		SIMPLE_OPCODE(REOP_ASCII_ISBLANK, "ascii_isblank");
		SIMPLE_OPCODE(REOP_ASCII_ISBLANK_NOT, "ascii_isblank_not");
		SIMPLE_OPCODE(REOP_ASCII_ISSYMSTRT, "ascii_issymstrt");
		SIMPLE_OPCODE(REOP_ASCII_ISSYMSTRT_NOT, "ascii_issymstrt_not");
		SIMPLE_OPCODE(REOP_ASCII_ISSYMCONT, "ascii_issymcont");
		SIMPLE_OPCODE(REOP_ASCII_ISSYMCONT_NOT, "ascii_issymcont_not");
		SIMPLE_OPCODE(REOP_UTF8_ISCNTRL, "utf8_iscntrl");
		SIMPLE_OPCODE(REOP_UTF8_ISCNTRL_NOT, "utf8_iscntrl_not");
		SIMPLE_OPCODE(REOP_UTF8_ISSPACE, "utf8_isspace");
		SIMPLE_OPCODE(REOP_UTF8_ISSPACE_NOT, "utf8_isspace_not");
		SIMPLE_OPCODE(REOP_UTF8_ISUPPER, "utf8_isupper");
		SIMPLE_OPCODE(REOP_UTF8_ISUPPER_NOT, "utf8_isupper_not");
		SIMPLE_OPCODE(REOP_UTF8_ISLOWER, "utf8_islower");
		SIMPLE_OPCODE(REOP_UTF8_ISLOWER_NOT, "utf8_islower_not");
		SIMPLE_OPCODE(REOP_UTF8_ISALPHA, "utf8_isalpha");
		SIMPLE_OPCODE(REOP_UTF8_ISALPHA_NOT, "utf8_isalpha_not");
		SIMPLE_OPCODE(REOP_UTF8_ISDIGIT, "utf8_isdigit");
		SIMPLE_OPCODE(REOP_UTF8_ISDIGIT_NOT, "utf8_isdigit_not");
		SIMPLE_OPCODE(REOP_UTF8_ISXDIGIT, "utf8_isxdigit");
		SIMPLE_OPCODE(REOP_UTF8_ISXDIGIT_NOT, "utf8_isxdigit_not");
		SIMPLE_OPCODE(REOP_UTF8_ISALNUM, "utf8_isalnum");
		SIMPLE_OPCODE(REOP_UTF8_ISALNUM_NOT, "utf8_isalnum_not");
		SIMPLE_OPCODE(REOP_UTF8_ISPUNCT, "utf8_ispunct");
		SIMPLE_OPCODE(REOP_UTF8_ISPUNCT_NOT, "utf8_ispunct_not");
		SIMPLE_OPCODE(REOP_UTF8_ISGRAPH, "utf8_isgraph");
		SIMPLE_OPCODE(REOP_UTF8_ISGRAPH_NOT, "utf8_isgraph_not");
		SIMPLE_OPCODE(REOP_UTF8_ISPRINT, "utf8_isprint");
		SIMPLE_OPCODE(REOP_UTF8_ISPRINT_NOT, "utf8_isprint_not");
		SIMPLE_OPCODE(REOP_UTF8_ISBLANK, "utf8_isblank");
		SIMPLE_OPCODE(REOP_UTF8_ISBLANK_NOT, "utf8_isblank_not");
		SIMPLE_OPCODE(REOP_UTF8_ISSYMSTRT, "utf8_issymstrt");
		SIMPLE_OPCODE(REOP_UTF8_ISSYMSTRT_NOT, "utf8_issymstrt_not");
		SIMPLE_OPCODE(REOP_UTF8_ISSYMCONT, "utf8_issymcont");
		SIMPLE_OPCODE(REOP_UTF8_ISSYMCONT_NOT, "utf8_issymcont_not");
		SIMPLE_OPCODE(REOP_UTF8_ISTAB, "utf8_istab");
		SIMPLE_OPCODE(REOP_UTF8_ISTAB_NOT, "utf8_istab_not");
		SIMPLE_OPCODE(REOP_UTF8_ISWHITE, "utf8_iswhite");
		SIMPLE_OPCODE(REOP_UTF8_ISWHITE_NOT, "utf8_iswhite_not");
		SIMPLE_OPCODE(REOP_UTF8_ISEMPTY, "utf8_isempty");
		SIMPLE_OPCODE(REOP_UTF8_ISEMPTY_NOT, "utf8_isempty_not");
		SIMPLE_OPCODE(REOP_UTF8_ISLF, "utf8_islf");
		SIMPLE_OPCODE(REOP_UTF8_ISLF_NOT, "utf8_islf_not");
		SIMPLE_OPCODE(REOP_UTF8_ISHEX, "utf8_ishex");
		SIMPLE_OPCODE(REOP_UTF8_ISHEX_NOT, "utf8_ishex_not");
		SIMPLE_OPCODE(REOP_UTF8_ISTITLE, "utf8_istitle");
		SIMPLE_OPCODE(REOP_UTF8_ISTITLE_NOT, "utf8_istitle_not");
		SIMPLE_OPCODE(REOP_UTF8_ISNUMERIC, "utf8_isnumeric");
		SIMPLE_OPCODE(REOP_UTF8_ISNUMERIC_NOT, "utf8_isnumeric_not");
		SIMPLE_OPCODE(REOP_AT_SOI, "at_soi");
		SIMPLE_OPCODE(REOP_AT_EOI, "at_eoi");
		SIMPLE_OPCODE(REOP_AT_SOL, "at_sol");
		SIMPLE_OPCODE(REOP_AT_SOL_UTF8, "at_sol_utf8");
		SIMPLE_OPCODE(REOP_AT_EOL, "at_eol");
		SIMPLE_OPCODE(REOP_AT_EOL_UTF8, "at_eol_utf8");
		SIMPLE_OPCODE(REOP_AT_WOB, "at_wob");
		SIMPLE_OPCODE(REOP_AT_WOB_UTF8, "at_wob_utf8");
		SIMPLE_OPCODE(REOP_AT_WOB_NOT, "at_wob_not");
		SIMPLE_OPCODE(REOP_AT_WOB_UTF8_NOT, "at_wob_utf8_not");
		SIMPLE_OPCODE(REOP_AT_SOW, "at_sow");
		SIMPLE_OPCODE(REOP_AT_SOW_UTF8, "at_sow_utf8");
		SIMPLE_OPCODE(REOP_AT_EOW, "at_eow");
		SIMPLE_OPCODE(REOP_AT_EOW_UTF8, "at_eow_utf8");
		SIMPLE_OPCODE(REOP_AT_SOS_UTF8, "at_sos_utf8");
		SIMPLE_OPCODE(REOP_NOP, "nop");
		SIMPLE_OPCODE(REOP_MATCHED, "matched");
#undef SIMPLE_OPCODE
		case REOP_MATCHED_PERFECT:
			opcode_repr = "matched_perfect";
do_print_opcode_repr:
			DO((*printer)(arg, opcode_repr, strlen(opcode_repr)));
			break;

		default:
			printf(".byte %#" PRIx8, opcode);
			for (; code < next; ++code)
				printf(", %#" PRIx8, *code);
			break;
		}
		PRINT("\n");
		if (opcode == REOP_MATCHED ||
		    opcode == REOP_MATCHED_PERFECT)
			break;
	}

	return result;
err:
	return temp;
#undef printf
#undef PRINT
#undef DO
}
#endif /* !NDEBUG */



#undef re_parser_yield
DEFINE_PUBLIC_ALIAS(re_parser_yield, libre_parser_yield);
DEFINE_PUBLIC_ALIAS(re_compiler_compile, libre_compiler_compile);
DEFINE_PUBLIC_ALIAS(re_code_disasm, libre_code_disasm);

DECL_END

#endif /* !GUARD_LIBREGEX_REGCOMP_C */
