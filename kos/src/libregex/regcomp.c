/*[[[magic
// "sorry, unimplemented: non-trivial designated initializers not supported"  -- UGH!
options["COMPILE.language"] = "c";
]]]*/
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

#include <hybrid/align.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/types.h>
#include <sys/bitstring.h>

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
#include "regfast.h"
#include "regpeep.h"

#ifndef NDEBUG
#include <format-printer.h>
#include <inttypes.h>
#endif /* !NDEBUG */

/* Regex compile-time configuration */
#define RE_COMP_MAXSIZE 0x10000 /* 2^16 (hard limit on how large regex code blobs may get) */

/* Max length for alternation bytecode prefixes.
 * -> These are generated is it later becomes possible to produce per-byte fastmap
 *    offsets,  by replicating regex prefixes (`REOP_AT_*' and `REOP_GROUP_START')
 *    before each element of a top-level alternation.
 *    iow: "^(foo|bar)$" is compiled as "(^foo|^bar)$",
 *         with  a fast-map that dispatches "f" and "b"
 *         directly to the relevant alternation.
 * -> For this purpose, only generate up to `ALTERNATION_PREFIX_MAXLEN' bytes
 *    of prefix instructions before giving up and not repeating any prefixes. */
#define ALTERNATION_PREFIX_MAXLEN 16

/* Must # of  ASCII characters that  should appear in  the
 * operand of `REOP_[N]CONTAINS_UTF8', before the compiler
 * should produce a `REOP_[N]CS_UTF8'-sequence instead. */
#define REOP_CONTAINS_UTF8_MAX_ASCII_COUNT 4

DECL_BEGIN

#undef re_parser_yield
#define re_parser_yield(self) libre_parser_yield(self)

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#define int16_at(p) (*(int16_t *)(p))

#define tswap(T, a, b)   \
	do {                 \
		T _temp = (b);   \
		(b)     = (a);   \
		(a)     = _temp; \
	}	__WHILE0


/************************************************************************/
/* RE PARSER                                                            */
/************************************************************************/

struct re_interval {
	uint8_t ri_min;  /* Interval lower bound */
	uint8_t ri_max;  /* [valid_if(!ri_many)] Interval upper bound */
	bool    ri_many; /* true if `> 1' is accepted (encountered '*' or '+') */
};

/* Parse a regex interval expression, with `*p_pattern' pointing AFTER the leading '{'
 * @return: true:  Interval is OK
 * @return: false: Interval is malformed */
PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC parse_interval)(char const **__restrict p_pattern, uintptr_t syntax,
                               struct re_interval *__restrict result) {
	/* Parse an interval */
	char const *pattern = *p_pattern;
	errno_t parse_errno = 0;
	uint32_t interval_min, interval_max;
	interval_min = strtou32_r(pattern, (char **)&pattern, 10, &parse_errno);
	if unlikely(parse_errno != 0)
		return false;
	result->ri_many  = false;
	interval_max = interval_min;
	if (*pattern == ',') {
		++pattern;
		if ((syntax & RE_SYNTAX_NO_BK_BRACES)
		    ? (pattern[0] == '}')
		    : (pattern[0] == '\0' && pattern[1] == '}')) {
			result->ri_many = true;
		} else {
			interval_max = strtou32_r(pattern, (char **)&pattern, 10, &parse_errno);
			if unlikely(parse_errno != 0)
				return false;
		}
	}
	if (syntax & RE_SYNTAX_NO_BK_BRACES) {
		if (pattern[0] != '}')
			return false;
		++pattern;
	} else {
		if (pattern[0] != '\\')
			return false;
		if (pattern[1] != '}')
			return false;
		pattern += 2;
	}
	if unlikely(interval_min > interval_max)
		return false;
	if unlikely(interval_max > UINT8_MAX)
		return false;
	*p_pattern = pattern;
	result->ri_min = (uint8_t)interval_min;
	result->ri_max = (uint8_t)interval_max;
	return true;
}

/* Check if `p' (which must point after the leading '{') is a valid interval */
PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC is_a_valid_interval)(char const *__restrict p, uintptr_t syntax) {
	struct re_interval interval;
	return parse_interval((char const **)&p, syntax, &interval);
}

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
		/* TODO: A single-element charset (e.g. "[$]") should be parsed as a literal.
		 *       That way, the compiler can directly merge it with adjacent literals! */
		return RE_TOKEN_STARTSET;

	case '{':
		if ((self->rep_syntax & (RE_SYNTAX_INTERVALS | RE_SYNTAX_NO_BK_BRACES)) ==
		    /*               */ (RE_SYNTAX_INTERVALS | RE_SYNTAX_NO_BK_BRACES)) {
			if (!(self->rep_syntax & RE_SYNTAX_INVALID_INTERVAL_ORD))
				return RE_TOKEN_STARTINTERVAL; /* '{' is always an interval */
			if (is_a_valid_interval(self->rep_pos, self->rep_syntax))
				return RE_TOKEN_STARTINTERVAL; /* '{' followed by a valid interval is OK */
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
		if ((self->rep_pos[0] == '\\' && self->rep_pos[1] == ')') && !(self->rep_syntax & RE_SYNTAX_NO_BK_PARENS))
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
				if (!(self->rep_syntax & RE_SYNTAX_INVALID_INTERVAL_ORD))
					return RE_TOKEN_STARTINTERVAL;
				if (is_a_valid_interval(self->rep_pos, self->rep_syntax))
					return RE_TOKEN_STARTINTERVAL; /* '{' followed by a valid interval is OK */
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

		case 'N':
			if (!(self->rep_syntax & RE_SYNTAX_NO_KOS_OPS))
				return RE_TOKEN_BK_N;
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

		case 'A':
			if (!(self->rep_syntax & RE_SYNTAX_NO_KOS_OPS))
				return RE_TOKEN_AT_SOI;
			break;

		case 'Z':
			if (!(self->rep_syntax & RE_SYNTAX_NO_KOS_OPS))
				return RE_TOKEN_AT_EOI;
			break;

		case '1' ... '9':
			if (!(self->rep_syntax & RE_SYNTAX_NO_BK_REFS))
				return RE_TOKEN_BKREF_1 + (ch - '1');
			break;

		case '0': {
			uint32_t ord;
			unsigned int i, ndigits;
			if (self->rep_syntax & RE_SYNTAX_NO_KOS_OPS)
				break;
			ord     = 0;
			ndigits = 3;
			for (i = 0; i < ndigits; ++i, ++self->rep_pos) {
				uint8_t nibble;
				char octchar = *self->rep_pos;
				if (octchar >= '0' && octchar <= '7') {
					nibble = (uint8_t)(octchar - '0');
				} else {
					break;
				}
				ord <<= 3;
				ord |= nibble;
			}
			if (ord >= 0x80) {
				ord -= 0x80;
				ord += RE_TOKEN_BYTE80h_MIN;
			}
			return ord;
		}	break;

		case 'u':
		case 'U':
			if (self->rep_syntax & RE_SYNTAX_NO_UTF8)
				break;
			ATTR_FALLTHROUGH
		case 'x': {
			uint32_t ord;
			unsigned int i, ndigits;
			if (self->rep_syntax & RE_SYNTAX_NO_KOS_OPS)
				break;
			ndigits = ch == 'U' ? 8 : ch == 'u' ? 4 : 2;
			ord     = 0;
			for (i = 0; i < ndigits; ++i, ++self->rep_pos) {
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
				self->rep_pos -= ndigits;
				goto default_escaped_char;
			}
			if (ch == 'x') {
				/* Special case: This one's 80h-FFh must be encoded as `RE_TOKEN_BYTE80h_MIN',
				 *               as it's not supposed to  match U+0080-U+00FF, but rather  the
				 *               raw bytes 80h-FFh. */
				if (ord >= 0x80) {
					ord -= 0x80;
					ord += RE_TOKEN_BYTE80h_MIN;
				}
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
	return ch; /* Default case: match a literal */
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuse-after-free" /* No: this use of `old_base' after free is OK! */
			ptrdiff_t delta = new_base - old_base;
#pragma GCC diagnostic pop
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

/* Return a pointer to the start of the utf-8 character that contains `cptr' */
PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(CC utf8_baseptr)(char const *__restrict cptr) {
	while (unicode_utf8seqlen[(unsigned char)*cptr] == 0)
		--cptr; /* Seek backwards until we hit a non-follow-up byte. */
	return (char *)cptr;
}

/* Same  as   `unicode_readutf8(3)',   but   don't   advance   `cptr'
 * It is assumed that `cptr' points to the start of a utf-8 sequence. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) char32_t
NOTHROW_NCX(CC utf8_charat)(char const *__restrict cptr) {
	return unicode_readutf8((char const **)&cptr);
}

/* Skip over `n' utf-8 characters. */
PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(CC utf8_skipn)(char const *__restrict cptr, size_t n) {
	for (; n; --n)
		cptr += unicode_utf8seqlen[(unsigned char)*cptr];
	return (char *)cptr;
}



/* Return a pointer to the next instruction */
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t *
NOTHROW_NCX(CC libre_opcode_next)(byte_t const *__restrict p_instr) {
	byte_t opcode = *p_instr++;
	switch (opcode) {

	case REOP_EXACT:
	case REOP_EXACT_ASCII_ICASE: {
		byte_t length;
		length = *p_instr++;
		assert(length >= 2);
		p_instr += length;
	}	break;

	case REOP_EXACT_UTF8_ICASE:
	case REOP_CONTAINS_UTF8:
	case REOP_NCONTAINS_UTF8: {
		byte_t count;
		count = *p_instr++;
		assert(count >= 1);
		do {
			p_instr += unicode_utf8seqlen[*p_instr];
		} while (--count);
	}	break;

	case REOP_CS_BYTE:
	case REOP_CS_UTF8:
	case REOP_NCS_UTF8: {
		byte_t cs_opcode;
		while ((cs_opcode = *p_instr++) != RECS_DONE) {
			switch (cs_opcode) {
			case RECS_BITSET_MIN ... RECS_BITSET_BYTE_MAX:
				if (cs_opcode <= RECS_BITSET_UTF8_MAX || opcode == REOP_CS_BYTE)
					p_instr += RECS_BITSET_GETBYTES(cs_opcode);
				break;
			case RECS_CHAR:
				if (opcode == REOP_CS_BYTE) {
					p_instr += 1;
				} else {
					p_instr += unicode_utf8seqlen[*p_instr];
				}
				break;
			case RECS_CHAR2:
			case RECS_RANGE:
			case RECS_RANGE_ICASE:
				if (opcode == REOP_CS_BYTE) {
					p_instr += 2;
				} else {
					p_instr += unicode_utf8seqlen[*p_instr];
					p_instr += unicode_utf8seqlen[*p_instr];
				}
				break;
			case RECS_CONTAINS: {
				byte_t count = *p_instr++;
				assert(count >= 1);
				if (opcode == REOP_CS_BYTE) {
					p_instr += count;
				} else {
					do {
						p_instr += unicode_utf8seqlen[*p_instr];
					} while (--count);
				}
			}	break;
			default: break;
			}
		}
	}	break;

	case REOP_BYTE:
	case REOP_NBYTE:
	case REOP_GROUP_MATCH:
	case REOP_GROUP_MATCH_JMIN ... REOP_GROUP_MATCH_JMAX:
	case REOP_GROUP_START:
	case REOP_GROUP_END:
	case REOP_GROUP_END_JMIN ... REOP_GROUP_END_JMAX:
		p_instr += 1;
		break;

	case REOP_BYTE2:
	case REOP_NBYTE2:
	case REOP_RANGE:
	case REOP_NRANGE:
	case REOP_JMP:
	case REOP_JMP_ONFAIL:
	case REOP_JMP_AND_RETURN_ONFAIL:
	case REOP_SETVAR:
	case REOP_MAYBE_POP_ONFAIL:
	case REOP_POP_ONFAIL_AT:
	case REOP_JMP_ONFAIL_DUMMY_AT:
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
			if (!re_compiler_putc(self, REOP_BYTE2))
				goto err_nomem;
			if ((unsigned char)lower > (unsigned char)upper) {
				/* `REOP_BYTE2' requires that the 2 bytes be sorted. */
				tswap(char, lower, upper);
			}
			if (!re_compiler_putc(self, (unsigned char)lower))
				goto err_nomem;
			if (!re_compiler_putc(self, (unsigned char)upper))
				goto err_nomem;
			goto done_literal;
		}
	}
	if (!re_compiler_putc(self, REOP_BYTE))
		goto err_nomem;
	if (!re_compiler_putc(self, literal_byte))
		goto err_nomem;
done_literal:
	return RE_NOERROR;
err_nomem:
	return RE_ESPACE;
}

PRIVATE int __LIBCCALL compare_char32_t(void const *a, void const *b) {
	char32_t lhs = *(char32_t const *)a;
	char32_t rhs = *(char32_t const *)b;
	if (lhs < rhs)
		return -1;
	if (lhs > rhs)
		return 1;
	return 0;
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
			/* Must sort `chars', as required by `REOP_CONTAINS_UTF8' */
			qsort(chars, nchars, sizeof(char32_t), &compare_char32_t);
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
			literal_seq_iter += unicode_utf8seqlen[(unsigned char)*literal_seq_iter];
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
	assert(self->rec_parser.rep_pos == literal_seq_end);
	if (literal_seq_length == 1) {
		/* Special case: single-character literal */
		re_token_t literal_tok;
		self->rec_parser.rep_pos = literal_seq_start;
		literal_tok = re_compiler_yield(self);
		assert(self->rec_parser.rep_pos == literal_seq_end);
		assert(RE_TOKEN_ISLITERAL(literal_tok));
		if (literal_seq_isutf8) {
			assert(RE_TOKEN_ISUTF8(literal_tok));
			return re_compiler_compile_literal_uni(self, (char32_t)literal_tok);
		}
		assert(!RE_TOKEN_ISUTF8(literal_tok));
		if (RE_TOKEN_ISBYTE80h(literal_tok))
			literal_tok = RE_TOKEN_GETBYTE80h(literal_tok);
		return re_compiler_compile_literal_byte(self, (byte_t)literal_tok);
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
			if (RE_TOKEN_ISBYTE80h(lit)) {
				*unesc_literal_seq_iter++ = RE_TOKEN_GETBYTE80h(lit);
			} else if (lit >= 0x80 && literal_seq_isutf8) {
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


#if ALTERNATION_PREFIX_MAXLEN > 0
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_alternation)(struct re_compiler *__restrict self,
                                                void const *alternation_prefix,
                                                size_t alternation_prefix_size);
#else /* ALTERNATION_PREFIX_MAXLEN > 0 */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC _re_compiler_compile_alternation)(struct re_compiler *__restrict self);
#define re_compiler_compile_alternation(self, ...) _re_compiler_compile_alternation(self)
#endif /* ALTERNATION_PREFIX_MAXLEN <= 0 */

struct charset_def {
	char    csd_name[7]; /* Charset name */
	uint8_t csd_opcode;  /* Charset opcode (one of `RECS_*') */
};


/* Known character sets, and their corresponding `RECS_*' opcodes. */
PRIVATE struct charset_def const charsets[] = {
	{ "cntrl", RECS_ISCNTRL },
	{ "space", RECS_ISSPACE },
	{ "upper", RECS_ISUPPER },
	{ "lower", RECS_ISLOWER },
	{ "alpha", RECS_ISALPHA },
	{ "digit", RECS_ISDIGIT },
	{ "xdigit", RECS_ISXDIGIT },
	{ "alnum", RECS_ISALNUM },
	{ "punct", RECS_ISPUNCT },
	{ "graph", RECS_ISGRAPH },
	{ "print", RECS_ISPRINT },
	{ "blank", RECS_ISBLANK },
	{ "symstrt", RECS_ISSYMSTRT },
	{ "symcont", RECS_ISSYMCONT },
	{ "tab", RECS_ISTAB },
	{ "white", RECS_ISWHITE },
	{ "empty", RECS_ISEMPTY },
	{ "lf", RECS_ISLF },
	{ "hex", RECS_ISHEX },
	{ "title", RECS_ISTITLE },
	{ { 'n', 'u', 'm', 'e', 'r', 'i', 'c' }, RECS_ISNUMERIC },
};

/* Find  the charset definition, given its `name'
 * Returns `RECS_DONE' if no such charset exists. */
PRIVATE WUNUSED uint8_t
NOTHROW_NCX(CC charset_find)(char const *__restrict name, size_t namelen) {
	size_t i;
	if (namelen > lengthof(charsets[0].csd_name))
		return RECS_DONE;
	for (i = 0; i < lengthof(charsets); ++i) {
		struct charset_def const *set = &charsets[i];
		if (bcmp(set->csd_name, name, namelen) == 0 &&
		    (namelen >= lengthof(charsets[i].csd_name) ||
		     set->csd_name[namelen] == '\0'))
			return set->csd_opcode;
	}
	return RECS_DONE;
}

struct unicode_charset {
	char  *ucs_basep; /* [0..1][<= ucs_endp][owned] Charset base pointer.
	                   *
	                   * The charset itself is a tightly packed utf-8  string,
	                   * with all of its containing characters sorted by their
	                   * unicode ordinal values.
	                   *
	                   * Because  unicode lead bytes can be differentiated from
	                   * unicode follow-up bytes, it is always possible to find
	                   * the start of a  character, given an arbitrary  pointer
	                   * into its sequence (thus: this array can be  bsearch'd) */
	char  *ucs_endp;  /* [0..1][>= ucs_basep] Charset end pointer. */
	size_t ucs_count; /* # of unicode characters in this set. */
};

#define unicode_charset_init(self)    (void)((self)->ucs_basep = (self)->ucs_endp = NULL, (self)->ucs_count = 0)
#define unicode_charset_fini(self)    free((self)->ucs_basep)
#define unicode_charset_isempty(self) ((self)->ucs_basep <= (self)->ucs_endp)

/* Insert (if it's not already contained) the given `ch' into `self'
 * @return:  1: The given `ch' was already contained in `self' (and thus wasn't inserted)
 * @return:  0: The given `ch' has been inserted into `self'
 * @return: -1: Error: insufficient memory. */
PRIVATE WUNUSED NONNULL((1)) int
NOTHROW_NCX(CC unicode_charset_insert)(struct unicode_charset *__restrict self,
                                       char32_t ch) {
	size_t utf8_len, oldsize, newsize, avlsize;
	char utf8[UNICODE_UTF8_MAXLEN];
	char *lo, *hi;
	lo = self->ucs_basep;
	hi = self->ucs_endp;
	while (lo < hi) {
		char32_t mch;
		char *mid;
		mid = lo + ((size_t)(hi - lo) >> 1);
		mid = utf8_baseptr(mid);
		mch = utf8_charat(mid);
		if (ch < mch) {
			hi = mid;
		} else if (ch > mch) {
			lo = mid + unicode_utf8seqlen[(unsigned char)*mid];
		} else {
			/* Already contained in set. */
			return 1;
		}
	}
	assert(lo == hi);

	/* Must insert `ch' at `lo' */
	utf8_len = (size_t)(unicode_writeutf8(utf8, ch) - utf8);
	oldsize  = (size_t)(self->ucs_endp - self->ucs_basep);
	newsize  = oldsize + utf8_len;
	avlsize  = malloc_usable_size(self->ucs_basep);
	if (newsize > avlsize) {
		char *newbuf;
		size_t newalloc = avlsize * 2;
		if (newalloc < 16)
			newalloc = 16;
		if (newalloc < newsize)
			newalloc = newsize;
		newbuf = (char *)realloc(self->ucs_basep, newalloc, sizeof(char));
		if unlikely(!newbuf) {
			newalloc = newsize;
			newbuf   = (char *)realloc(self->ucs_basep, newalloc, sizeof(char));
			if unlikely(!newbuf)
				return -1;
		}
		lo = newbuf + (lo - self->ucs_basep);
		hi = newbuf + (hi - self->ucs_basep);
		self->ucs_basep = newbuf;
		self->ucs_endp  = newbuf + oldsize;
	}

	/* Insert the utf8-sequence at the required offset. */
	memmoveup(lo + utf8_len, lo, (size_t)(self->ucs_endp - lo), sizeof(char));
	memcpy(lo, utf8, utf8_len, sizeof(char));
	self->ucs_endp += utf8_len;
	assert(self->ucs_endp == self->ucs_basep + newsize);
	++self->ucs_count;
	return 0;
}

PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC charvec_contains)(char32_t const *chv, size_t chc, char32_t ch) {
	size_t i;
	for (i = 0; i < chc; ++i) {
		if (chv[i] == ch)
			return true;
	}
	return false;
}

PRIVATE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(CC unicode_charset_insertall)(struct unicode_charset *__restrict self,
                                          char32_t const *chv, size_t chc) {
	size_t i;
	if (chc > 0) {
		if unlikely(unicode_charset_insert(self, chv[0]) == -1)
			goto err;
		if (chc > 1) {
			for (i = 1; i < chc; ++i) {
				char32_t ch = chv[i];
				if (charvec_contains(chv, i, ch))
					continue;
				if unlikely(unicode_charset_insert(self, ch) == -1)
					goto err;
			}
		}
	}
	return 0;
err:
	return -1;
}

/* Generate code `RECS_RANGE lo, hi' */
PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC re_compiler_cs_encode_unirange)(struct re_compiler *__restrict self,
                                               char32_t lo, char32_t hi) {
	size_t codelen;
	byte_t code[1 + (2 * UNICODE_UTF8_MAXLEN)], *writer;
	writer    = code;
	*writer++ = (self->rec_parser.rep_syntax & RE_SYNTAX_ICASE) ? RECS_RANGE_ICASE : RECS_RANGE;
	writer    = (byte_t *)unicode_writeutf8((char *)writer, lo);
	writer    = (byte_t *)unicode_writeutf8((char *)writer, hi);
	codelen   = (size_t)(writer - code);
	return re_compiler_putn(self, code, codelen);
}

/* ASCII character trait flags (s.a. `/kos/kos/include/bits/crt/ctype.h') */
#define CTYPE_C_FLAG_CNTRL  0x01
#define CTYPE_C_FLAG_SPACE  0x02
#define CTYPE_C_FLAG_LOWER  0x04
#define CTYPE_C_FLAG_UPPER  0x08
#define CTYPE_C_FLAG_ALPHA  0x0c
#define CTYPE_C_FLAG_DIGIT  0x10
#define CTYPE_C_FLAG_XDIGIT 0x30
#define CTYPE_C_FLAG_ALNUM  0x1c
#define CTYPE_C_FLAG_PUNCT  0x40
#define CTYPE_C_FLAG_GRAPH  0x5c
#define CTYPE_C_FLAG_PRINT  0xdc

/* Mapping from `RECS_ISxxx - RECS_ISX_MIN' to `CTYPE_C_FLAG_*'.
 *
 * Those cases where mask exists encode `0' as mask, causing the
 * handler to do a custom encode below. */
PRIVATE uint8_t const ctype_c_trait_masks[] = {
#define DEF_CTYPE_TRAIT_MASK(opcode, mask) [((opcode) - RECS_ISX_MIN)] = mask
	DEF_CTYPE_TRAIT_MASK(RECS_ISCNTRL, CTYPE_C_FLAG_CNTRL),
	DEF_CTYPE_TRAIT_MASK(RECS_ISSPACE, CTYPE_C_FLAG_SPACE),
	DEF_CTYPE_TRAIT_MASK(RECS_ISUPPER, CTYPE_C_FLAG_UPPER),
	DEF_CTYPE_TRAIT_MASK(RECS_ISLOWER, CTYPE_C_FLAG_LOWER),
	DEF_CTYPE_TRAIT_MASK(RECS_ISALPHA, CTYPE_C_FLAG_ALPHA),
	DEF_CTYPE_TRAIT_MASK(RECS_ISDIGIT, CTYPE_C_FLAG_DIGIT),
	DEF_CTYPE_TRAIT_MASK(RECS_ISXDIGIT, CTYPE_C_FLAG_XDIGIT),
	DEF_CTYPE_TRAIT_MASK(RECS_ISALNUM, CTYPE_C_FLAG_ALNUM),
	DEF_CTYPE_TRAIT_MASK(RECS_ISPUNCT, CTYPE_C_FLAG_PUNCT),
	DEF_CTYPE_TRAIT_MASK(RECS_ISGRAPH, CTYPE_C_FLAG_GRAPH),
	DEF_CTYPE_TRAIT_MASK(RECS_ISPRINT, CTYPE_C_FLAG_PRINT),
	DEF_CTYPE_TRAIT_MASK(RECS_ISBLANK, 0),
	DEF_CTYPE_TRAIT_MASK(RECS_ISSYMSTRT, 0),
	DEF_CTYPE_TRAIT_MASK(RECS_ISSYMCONT, 0),
	DEF_CTYPE_TRAIT_MASK(RECS_ISTAB, 0),
	DEF_CTYPE_TRAIT_MASK(RECS_ISWHITE, 0),
	DEF_CTYPE_TRAIT_MASK(RECS_ISEMPTY, 0),
	DEF_CTYPE_TRAIT_MASK(RECS_ISLF, 0),
	DEF_CTYPE_TRAIT_MASK(RECS_ISHEX, 0),
	DEF_CTYPE_TRAIT_MASK(RECS_ISTITLE, CTYPE_C_FLAG_UPPER),
	DEF_CTYPE_TRAIT_MASK(RECS_ISNUMERIC, CTYPE_C_FLAG_DIGIT),
#undef DEF_CTYPE_TRAIT_MASK
};

/* Yield a charset literal. Returns:
 * - A unicode ordinal  (return < RE_TOKEN_BASE)
 * - A raw byte literal (return >= RE_TOKEN_BYTE80h_MIN && return <= RE_TOKEN_BYTE80h_MAX)
 * - RE_TOKEN_UNMATCHED_BK when an unmatched '\' is encountered
 */
PRIVATE WUNUSED NONNULL((1)) char32_t
NOTHROW_NCX(CC re_parser_yield_cs_literal)(struct re_parser *__restrict self) {
	unsigned char ch;
	ch = (unsigned char)*self->rep_pos++;
	if (ch >= 0x80) {
decpos_and_readutf8:
		--self->rep_pos;
		return unicode_readutf8((char const **)&self->rep_pos);
	}
	if ((ch == '\\') &&
	    (self->rep_syntax & (RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS | RE_SYNTAX_NO_KOS_OPS)) ==
	    /*               */ (RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS)) {
		ch = (unsigned char)*self->rep_pos++;
		switch (ch) {

		case '\0':
			self->rep_pos -= 2; /* Keep on repeating this token! */
			return RE_TOKEN_UNMATCHED_BK;

		case '0': {
			uint32_t ord;
			unsigned int i, ndigits;
			if (self->rep_syntax & RE_SYNTAX_NO_KOS_OPS)
				break;
			ord     = 0;
			ndigits = 3;
			for (i = 0; i < ndigits; ++i, ++self->rep_pos) {
				uint8_t nibble;
				char octchar = *self->rep_pos;
				if (octchar >= '0' && octchar <= '7') {
					nibble = (uint8_t)(octchar - '0');
				} else {
					break;
				}
				ord <<= 3;
				ord |= nibble;
			}
			if (ord >= 0x80) {
				ord -= 0x80;
				ord += RE_TOKEN_BYTE80h_MIN;
			}
			return ord;
		}	break;

		case 'u':
		case 'U':
			if (self->rep_syntax & RE_SYNTAX_NO_UTF8)
				break;
			ATTR_FALLTHROUGH
		case 'x': {
			uint32_t ord;
			unsigned int i, ndigits;
			if (self->rep_syntax & RE_SYNTAX_NO_KOS_OPS)
				break;
			ndigits = ch == 'U' ? 8 : ch == 'u' ? 4 : 2;
			ord     = 0;
			for (i = 0; i < ndigits; ++i, ++self->rep_pos) {
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
				self->rep_pos -= ndigits;
				goto default_escaped_char;
			}
			if (ch == 'x') {
				/* Special case: This one's 80h-FFh must be encoded as `RE_TOKEN_BYTE80h_MIN',
				 *               as it's not supposed to  match U+0080-U+00FF, but rather  the
				 *               raw bytes 80h-FFh. */
				if (ord >= 0x80) {
					ord -= 0x80;
					ord += RE_TOKEN_BYTE80h_MIN;
				}
			}
			return ord;
		}	break;

		case 0x80 ... 0xff:
			goto decpos_and_readutf8;

		default:
default_escaped_char:
			break;
		}
	}
	return ch;
}

PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_set)(struct re_compiler *__restrict self) {
#define CHARSET_COUNT ((RECS_ISX_MAX - RECS_ISX_MIN) + 1)
	bitstr_t bit_decl(bytes, 256);
	bitstr_t bit_decl(charsets, CHARSET_COUNT);
	struct unicode_charset uchars; /* Extra unicode characters to add to the set. */
	bool negate     = false;
	size_t start_offset; /* Set code start offset (offset of `REOP_[N]CS_*' opcode) */
	if (*self->rec_parser.rep_pos == '^') {
		negate = true;
		++self->rec_parser.rep_pos;
	}

	/* By default, we don't match any bytes. */
	bit_clearall(bytes, 256);
	bit_clearall(charsets, CHARSET_COUNT);
	unicode_charset_init(&uchars);
	if unlikely(!re_compiler_require(self, 1)) /* Will need at least 1 byte */
		goto err_nomem;
	start_offset = (size_t)(self->rec_cpos - self->rec_cbase);
	++self->rec_cpos; /* Reserve space for leading `REOP_[N]CS_*' character. */

	/* Special case: if the character immediately after the open '[' is
	 * either ']' or '-', it will  not have its usual special  meaning. */
	if (*self->rec_parser.rep_pos == ']' || *self->rec_parser.rep_pos == '-') {
		bit_set(bytes, *self->rec_parser.rep_pos);
		++self->rec_parser.rep_pos;
	}

loop_next:
	for (;;) {
		char32_t uchar, hichar;
		unsigned char ch;
		ch = (unsigned char)*self->rec_parser.rep_pos++;
		switch (ch) {

		case '\0':
			goto err_EEND;

		case ']':
			goto done_loop;

		case '[':
			if ((self->rec_parser.rep_syntax & RE_SYNTAX_CHAR_CLASSES) &&
			    (*self->rec_parser.rep_pos == ':')) {
				/* character classes */
				uint8_t cs_opcode;
				char const *csend, *csstart;
				self->rec_parser.rep_pos += 1;
				csstart = self->rec_parser.rep_pos;
				csend   = strchr(csstart, ':');
				if unlikely(!csend)
					goto err_EEND;
				cs_opcode = charset_find(csstart, (size_t)(csend - csstart));
				if unlikely(cs_opcode == RECS_DONE)
					goto err_ECTYPE;
				if (self->rec_parser.rep_syntax & RE_SYNTAX_ICASE) {
					/* Transform char-classes in ICASE-mode */
					if (cs_opcode == RECS_ISUPPER || cs_opcode == RECS_ISLOWER || cs_opcode == RECS_ISTITLE)
						cs_opcode = RECS_ISALNUM;
				}
				csend += 1;
				if unlikely(*csend != ']')
					goto err_BADPAT;
				csend += 1;
				self->rec_parser.rep_pos = csend;

				/* Add the selected charset to the collection of ones that have been used. */
				bit_set(charsets, cs_opcode - RECS_ISX_MIN);
				goto loop_next;
			}
			goto encode_literal;

		case '\\':
			if (self->rec_parser.rep_syntax & RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS) {
				/* Special case: backslash-escape sequences are allowed in charsets */
				ch = (unsigned char)*self->rec_parser.rep_pos++;
				if unlikely(ch == '\0')
					goto err_EEND;
				if (!(self->rec_parser.rep_syntax & RE_SYNTAX_NO_KOS_OPS)) {
					switch (ch) {

					case '\0':
						goto err_EEND;

					case 'w':
						bit_set(charsets, RECS_ISSYMCONT - RECS_ISX_MIN);
						goto loop_next;

					case 'n':
						bit_set(charsets, RECS_ISLF - RECS_ISX_MIN);
						goto loop_next;

					case 's':
						bit_set(charsets, RECS_ISSPACE - RECS_ISX_MIN);
						goto loop_next;

					case 'd':
						bit_set(charsets, RECS_ISDIGIT - RECS_ISX_MIN);
						goto loop_next;

					case '0':
					case 'u':
					case 'U':
					case 'x':
						self->rec_parser.rep_pos -= 2;
						uchar = re_parser_yield_cs_literal(&self->rec_parser);
						if unlikely(uchar == RE_TOKEN_UNMATCHED_BK)
							goto err_EESCAPE;
						if (RE_TOKEN_ISBYTE80h(uchar)) {
							ch = (unsigned char)(byte_t)RE_TOKEN_GETBYTE80h(uchar);
							goto encode_byte_ch;
						}
						goto encode_uchar;

					default: break;
					}
				}
				goto encode_literal;
			}
			goto encode_literal;

		default:
encode_literal:
			if (ch >= 0x80 && !(self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8)) {
				--self->rec_parser.rep_pos;
				uchar = unicode_readutf8((char const **)&self->rec_parser.rep_pos);
encode_uchar:
				if unlikely(uchar < 0x80) {
					ch = (unsigned char)uchar;
					goto encode_byte_ch;
				}
				if (self->rec_parser.rep_pos[0] == '-' &&
				    self->rec_parser.rep_pos[1] != ']') {
					/* Unicode character range. */
					++self->rec_parser.rep_pos; /* Skip over '-' character */
					hichar = re_parser_yield_cs_literal(&self->rec_parser);
					if unlikely(hichar == RE_TOKEN_UNMATCHED_BK)
						goto err_EESCAPE;
					if (RE_TOKEN_ISBYTE80h(hichar))
						goto handle_bad_unicode_range; /* Something like "[ä-\xAB]" isn't allowed */
encode_unicode_range:
					if (hichar < uchar) {
handle_bad_unicode_range:
						/* Bad range lo/hi bounds */
						if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_EMPTY_RANGES)
							goto err_ERANGE;
						goto loop_next; /* Ignore range. */
					}
					if (self->rec_parser.rep_syntax & RE_SYNTAX_ICASE) {
						uchar = unicode_tolower(uchar);
						hichar = unicode_tolower(hichar);
						if unlikely(uchar > hichar)
							tswap(char32_t, uchar, hichar);
					}

					/* Special case: "[ä-ä]" is encoded as "[ä]" */
					if (uchar == hichar)
						goto add_lochar_to_unicode_charset;

					/* Directly encode the utf-8 sequence length. */
					if unlikely(!re_compiler_cs_encode_unirange(self, uchar, hichar))
						goto err_nomem;
					goto loop_next;
				}

				/* Add unicode character to unicode set. */
add_lochar_to_unicode_charset:
				if (self->rec_parser.rep_syntax & RE_SYNTAX_ICASE) {
					char32_t chars[4];
					chars[0] = uchar;
					chars[1] = unicode_tolower(uchar);
					chars[2] = unicode_toupper(uchar);
					chars[3] = unicode_totitle(uchar);
					if unlikely(unicode_charset_insertall(&uchars, chars, 4) < 0)
						goto err_nomem;
				} else {
					if unlikely(unicode_charset_insert(&uchars, uchar) < 0)
						goto err_nomem;
				}
				goto loop_next;
			}
encode_byte_ch:
			if (self->rec_parser.rep_pos[0] == '-' &&
			    self->rec_parser.rep_pos[1] != ']') {
				/* Ascii character range. */
				unsigned char hibyte;
				++self->rec_parser.rep_pos;
				hichar = re_parser_yield_cs_literal(&self->rec_parser);
				if unlikely(hichar == RE_TOKEN_UNMATCHED_BK)
					goto err_EESCAPE;
				if (RE_TOKEN_ISBYTE80h(hichar)) {
					hibyte = RE_TOKEN_GETBYTE80h(hichar);
				} else if (RE_TOKEN_ISUTF8(hichar)) {
					if unlikely(ch >= 0x80)
						goto handle_bad_byte_range; /* Something like "[\xAB-ä]" isn't allowed */
					/* Handle something like "[a-ä]" */
					uchar = (char32_t)ch;
					goto encode_unicode_range;
				} else {
					hibyte = (unsigned char)hichar;
				}
				if (hibyte < ch) {
handle_bad_byte_range:
					/* Bad range lo/hi bounds */
					if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_EMPTY_RANGES)
						goto err_ERANGE;
					goto loop_next; /* Ignore range. */
				}
				bit_nset(bytes, ch, hibyte);
			} else {
				bit_set(bytes, ch);
			}
			break;
		}
	}
done_loop:

	/* In ASCII-mode, we're not allowed to encode charsets. Instead, we
	 * have to essentially hard-code  ctype attributes in the  charset. */
	if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8) {
		int csid_offset;
		assert(unicode_charset_isempty(&uchars));
		bit_foreach (csid_offset, charsets, CHARSET_COUNT) {
			uint8_t ctype_c_trait_mask;
			ctype_c_trait_mask = ctype_c_trait_masks[csid_offset];
			if (ctype_c_trait_mask != 0) {
				/* Can just copy attributes from `__ctype_C_flags' */
				unsigned int i;
do_copy_ctype_c_trait_mask:
				for (i = 0; i < 256; ++i) {
					if ((__ctype_C_flags[i] & ctype_c_trait_mask) != 0)
						bit_set(bytes, i);
				}
			} else {
				/* Need some custom handling (s.a. 0-cases in `ctype_c_trait_masks') */
				switch (csid_offset) {
				case RECS_ISBLANK - RECS_ISX_MIN:
					bit_set(bytes, 0x09);
					bit_set(bytes, 0x20);
					break;
				case RECS_ISSYMSTRT - RECS_ISX_MIN:
					bit_set(bytes, 0x24); /* '$' */
					bit_set(bytes, 0x5f); /* '_' */
					ctype_c_trait_mask = CTYPE_C_FLAG_ALPHA;
					goto do_copy_ctype_c_trait_mask;
				case RECS_ISSYMCONT - RECS_ISX_MIN:
					bit_set(bytes, 0x24); /* '$' */
					bit_set(bytes, 0x5f); /* '_' */
					ctype_c_trait_mask = CTYPE_C_FLAG_ALNUM;
					goto do_copy_ctype_c_trait_mask;
				case RECS_ISEMPTY - RECS_ISX_MIN:
					bit_set(bytes, 0x20); /* ' ' */
					ATTR_FALLTHROUGH
				case RECS_ISTAB - RECS_ISX_MIN:
					bit_set(bytes, 0x09); /* '\t' */
					bit_set(bytes, 0x0b); /* VT */
					bit_set(bytes, 0x0c); /* FF */
					break;
				case RECS_ISWHITE - RECS_ISX_MIN:
					bit_set(bytes, 0x20); /* ' ' */
					break;
				case RECS_ISLF - RECS_ISX_MIN:
					bit_set(bytes, 0x0a); /* '\n' */
					bit_set(bytes, 0x0d); /* '\r' */
					break;
				case RECS_ISHEX - RECS_ISX_MIN:
					bit_nset(bytes, 0x41, 0x46); /* 'A-F' */
					bit_nset(bytes, 0x61, 0x66); /* 'a-f' */
					break;
				default: __builtin_unreachable();
				}
			}
		}
	}

	/* In ICASE-mode, must merge the is-set state of 'A-Z' and 'a-z' in the ASCII area */
	if (self->rec_parser.rep_syntax & RE_SYNTAX_ICASE) {
		byte_t b;
		for (b = 0x41; b <= 0x5a; ++b) {
			if (bit_test(bytes, b) || bit_test(bytes, b | 0x20)) {
				bit_set(bytes, b);
				bit_set(bytes, b | 0x20);
			}
		}
	}

	/* Figure out how we want to represent everything. */
	if (negate) {
		if (self->rec_parser.rep_syntax & RE_SYNTAX_HAT_LISTS_NOT_NEWLINE) {
			/* Implicitly exclude line-feeds from the charset. */
			if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8) {
				bit_set(bytes, 0x0a); /* '\n' */
				bit_set(bytes, 0x0d); /* '\r' */
			} else {
				bit_set(charsets, RECS_ISLF - RECS_ISX_MIN);
			}
		}
		if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8) {
			self->rec_cbase[start_offset] = REOP_CS_BYTE;
			bit_flipall(bytes, 256);
		} else {
			self->rec_cbase[start_offset] = REOP_NCS_UTF8;
			goto check_bytes_only_ascii;
		}
	} else {
		if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8) {
			self->rec_cbase[start_offset] = REOP_CS_BYTE;
		} else if ((self->rec_cpos == self->rec_cbase + start_offset + 1) &&
		           (uchars.ucs_count == 0) &&
		           (bit_noneset(charsets, CHARSET_COUNT))) {
			/* Special case: even  when compiling in  utf-8-mode, we can still
			 *               encode charsets in their more efficient byte-mode
			 *               encoding,  so-long as the pattern can never match
			 *               a multi-byte utf-8 character! */
			self->rec_cbase[start_offset] = REOP_CS_BYTE;
		} else {
			self->rec_cbase[start_offset] = REOP_CS_UTF8;
check_bytes_only_ascii:
			/* Patterns like "[Ä\xC3]" are invalid, since you can't both
			 * match the singular byte "\xC3", as well as the utf-8 byte
			 * sequence "\xC3\x84" (well...  technically you could,  but
			 * not by using a charset)
			 *
			 * To keep things from escalating, we only allow ascii-chars
			 * being bitset-matched when encoding a utf-8 based charset. */
			if (bit_nanyset(bytes, 0x80, 0xff)) {
				goto err_EILLSET;
			}
		}
	}

	if (!(self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8)) {
		/* Encode `charsets' (if in utf-8 mode) */
		int csid_offset;
		bit_foreach (csid_offset, charsets, CHARSET_COUNT) {
			byte_t cs_opcode = RECS_ISX_MIN + csid_offset;
			if (!re_compiler_putc(self, cs_opcode))
				goto err_nomem;
			/* TODO: In non-negate-mode, try to clear the charset's bits from `bytes', so we don't
			 *       encode  matching bytes redundantly  (optimizes "[[:hex:]a-f]" -> "[[:hex:]]") */
		}

		/* Encode `uchars' (if in utf-8 mode) */
		if (uchars.ucs_count > 0) {
			char *basep  = uchars.ucs_basep;
			size_t count = uchars.ucs_count;
			/* Special case: if the set contains only unicode chars, and
			 *               no  char-sets, and is  short enough to fit,
			 *               then encode as `REOP_[N]CONTAINS_UTF8' */
			if ((self->rec_cpos == self->rec_cbase + start_offset + 1)) {
				unsigned int nbytes = bit_popcount(bytes, 256);
				if ((nbytes <= REOP_CONTAINS_UTF8_MAX_ASCII_COUNT) &&
				    ((count + nbytes) <= 0xff)) {
					/* Yes: we can use `REOP_[N]CONTAINS_UTF8'! */
					self->rec_cpos[-1] = negate ? REOP_NCONTAINS_UTF8
					                            : REOP_CONTAINS_UTF8;
					if (!re_compiler_putc(self, (byte_t)count + nbytes))
						goto err_nomem;
					if (nbytes != 0) {
						/* Include ASCII characters in the CONTAINS-match. */
						byte_t b;
						for (b = 0; b < 0x80; ++b) {
							if (bit_test(bytes, b)) {
								if (!re_compiler_putc(self, b))
									goto err_nomem;
							}
						}
					}
					if (!re_compiler_putn(self, basep, (size_t)(uchars.ucs_endp - basep)))
						goto err_nomem;
					goto done;
				}
			}

			while (count > 0xff) {
				/* Must encode in multiple sets. */
				char *new_basep;
				new_basep = utf8_skipn(basep, 255);
				if (!re_compiler_putc(self, RECS_CONTAINS))
					goto err_nomem;
				if (!re_compiler_putc(self, 255))
					goto err_nomem;
				if (!re_compiler_putn(self, basep, (size_t)(new_basep - basep)))
					goto err_nomem;
				basep = new_basep;
				count -= 0xff;
			}
			if (count == 2) {
				if (!re_compiler_putc(self, RECS_CHAR2))
					goto err_nomem;
			} else if (count == 1) {
				if (!re_compiler_putc(self, RECS_CHAR))
					goto err_nomem;
			} else {
				if (!re_compiler_putc(self, RECS_CONTAINS))
					goto err_nomem;
				if (!re_compiler_putc(self, (byte_t)count))
					goto err_nomem;
			}
			if (!re_compiler_putn(self, basep, (size_t)(uchars.ucs_endp - basep)))
				goto err_nomem;
		}
	}

	/* Encode `bytes' (with optimizations in  case no other prefixes were  written
	 * yet, iow: when `self->rec_cpos == self->rec_cbase + start_offset', in which
	 * case try to encode as `REOP_[N]BYTE', `REOP_[N]BYTE2' or `REOP_[N]RANGE') */
	if (self->rec_cpos == self->rec_cbase + start_offset) {
		/* Nothing out of the ordinary happened, yet.
		 * -> Check if we can encode `bytes' as one of:
		 *    - REOP_[N]BYTE
		 *    - REOP_[N]BYTE2
		 *    - REOP_[N]RANGE
		 */
		unsigned int b;
		unsigned int popcount;
		byte_t range_lo, range_hi;
		for (b = 0;; ++b) {
			if (b >= 256)
				goto put_terminator; /* Empty bytes? -- ok... (but this won't ever match anything) */
			if (bit_test(bytes, b))
				break;
		}
		/* Found the first matching character.
		 * -> check if we can encode this via `REOP_[N]RANGE'. */
		popcount = 1;
		range_lo = (byte_t)b;
		range_hi = (byte_t)b;
		while (range_hi < (256 - 1) && bit_test(bytes, range_hi + 1)) {
			++range_hi;
			++popcount;
		}
		if (range_hi >= 0xff || !bit_nanyset(bytes, range_hi + 1, 0xff)) {
			/* We're dealing with a singular, continuous range [range_lo,range_hi] */
			unsigned int rangelen = (range_hi - range_lo) + 1;
			assert(rangelen >= 1);
			if (rangelen == 1) {
				/* The entire set matches only a single byte, specific. */
				assert(range_lo == range_hi);
				self->rec_cpos[-1] = negate ? REOP_NBYTE : REOP_BYTE;
				if (!re_compiler_putc(self, range_lo))
					goto err_nomem;
				goto done;
			} else if (rangelen == 2) {
				/* The entire set matches only 2 different bytes. */
				assert(range_lo + 1 == range_hi);
				self->rec_cpos[-1] = negate ? REOP_NBYTE2 : REOP_BYTE2;
				if (!re_compiler_putc(self, range_lo))
					goto err_nomem;
				if (!re_compiler_putc(self, range_hi))
					goto err_nomem;
				goto done;
			} else {
				/* The entire set matches only a specific range of bytes */
				assert(range_lo + 1 == range_hi);
				self->rec_cpos[-1] = negate ? REOP_NRANGE : REOP_RANGE;
				if (!re_compiler_putc(self, range_lo))
					goto err_nomem;
				if (!re_compiler_putc(self, range_hi))
					goto err_nomem;
				goto done;
			}
			goto done;
		}
		if (popcount == 1) {
			/* Check if we can find another matching byte somewhere `> b' */
			b += 2;                     /* b+1 was already checked, so start at b += 2 */
			while (!bit_test(bytes, b)) /* We know that there must be more set bits, because `!bit_nanyset' */
				++b;
			/* At this point, we know that `range_lo' and `b' are part of the set.
			 * -> If these are the only 2, then we can generate `REOP_[N]BYTE2'. */
			if (b >= 0xff || !bit_nanyset(bytes, b + 1, 0xff)) {
				self->rec_cpos[-1] = negate ? REOP_NBYTE2 : REOP_BYTE2;
				if (!re_compiler_putc(self, range_lo))
					goto err_nomem;
				if (!re_compiler_putc(self, b))
					goto err_nomem;
				goto done;
			}
		}
	}

	/* Check if there are even any bytes _to_ encode. */
	if unlikely(!bit_anyset(bytes, 256)) {
		/* No byte-matches specified -> don't encode a bitset.
		 * - This can easily happen for (e.g.) "[[:alpha:]]" in utf-8 mode,
		 *   where it  encodes  to  `REOP_CS_UTF8, RECS_ISALPHA, RECS_DONE'
		 */
		goto put_terminator;
	}

	/* No special encoding is possible -> must instead use `RECS_BITSET_MIN'! */
	{
		byte_t cs_opcode;
		byte_t minset, maxset, base, num_bits, num_bytes;
		minset    = 0x00 + bit_clz(bytes);
		maxset    = 0xff - bit_ctz(bytes, 256);
		base      = RECS_BITSET_BASEFOR(minset);
		num_bits  = (maxset + 1) - base;
		num_bytes = CEILDIV(num_bits, 8);
		assertf(num_bytes <= 0x20, "%" PRIuSIZ, num_bytes);
		cs_opcode = RECS_BITSET_BUILD(base, num_bytes);
		assertf((cs_opcode <= RECS_BITSET_UTF8_MAX) ||
		        (self->rec_cbase[start_offset] == REOP_CS_BYTE),
		        "This should have been asserted by the err_EILLSET check above");
		if (!re_compiler_putc(self, cs_opcode))
			goto err_nomem;
		static_assert(sizeof(*bytes) == sizeof(byte_t));
		if (!re_compiler_putn(self, bytes + (base / 8), num_bytes))
			goto err_nomem;
	} /* scope... */

	/* Terminate the generated character-set */
put_terminator:
	if (!re_compiler_putc(self, RECS_DONE))
		goto err_nomem;
done:
	unicode_charset_fini(&uchars);
	return RE_NOERROR;
	{
		re_errno_t error;
err_nomem:
		error = RE_ESPACE;
		goto _err_common;
err_EESCAPE:
		error = RE_EESCAPE;
		goto _err_common;
err_EILLSET:
		error = RE_EILLSET;
		goto _err_common;
err_BADPAT:
		error = RE_BADPAT;
		goto _err_common;
err_ERANGE:
		error = RE_ERANGE;
		goto _err_common;
err_ECTYPE:
		error = RE_ECTYPE;
		goto _err_common;
err_EEND:
		error = RE_EEND;
_err_common:
		unicode_charset_fini(&uchars);
		return error;
	}
}

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
#if ALTERNATION_PREFIX_MAXLEN > 0
	byte_t alternation_prefix[ALTERNATION_PREFIX_MAXLEN];
	size_t alternation_prefix_len;
	bool alternation_prefix_wanted;
#define alternation_prefix_hasspace(num_bytes) ((ALTERNATION_PREFIX_MAXLEN - alternation_prefix_len) >= (num_bytes))
#define alternation_prefix_putc(byte)       (void)(alternation_prefix[alternation_prefix_len++] = (byte))
#define alternation_prefix_putn(p, n)       (void)(memcpy(&alternation_prefix[alternation_prefix_len], p, n), alternation_prefix_len += (n))
#define alternation_prefix_dump()                                                    \
	do {                                                                             \
		if (alternation_prefix_len > 0) {                                            \
			if (!re_compiler_putn(self, alternation_prefix, alternation_prefix_len)) \
				goto err_nomem;                                                      \
			alternation_prefix_wanted = false;                                       \
		}                                                                            \
	}	__WHILE0
#else /* ALTERNATION_PREFIX_MAXLEN > 0 */
#define alternation_prefix_hasspace(num_bytes) 0
#define alternation_prefix_dump() (void)0
#endif /* ALTERNATION_PREFIX_MAXLEN <= 0 */


	/* Check if we want to produce alternation prefixes. */
#if ALTERNATION_PREFIX_MAXLEN > 0
	assert(self->rec_cpos >= ((struct re_code *)self->rec_cbase)->rc_code);
	alternation_prefix_wanted = self->rec_cpos <= ((struct re_code *)self->rec_cbase)->rc_code;
	alternation_prefix_len    = 0;
#endif /* ALTERNATION_PREFIX_MAXLEN > 0 */
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

		/* Optimization: "(a|b)" normally compiles as:
		 * >> 0x0000:    REOP_GROUP_START 0
		 * >> 0x0002:    REOP_JMP_ONFAIL  1f
		 * >> 0x0005:    REOP_BYTE        "a"
		 * >> 0x0007:    REOP_JMP         2f
		 * >> 0x000a: 1: REOP_BYTE        "b"
		 * >> 0x000c: 2: REOP_GROUP_END   0
		 * With a fast-map: ["ab": @0x0000]
		 *
		 * However, if we compiled it like this:
		 * >> 0x0000:    REOP_JMP_ONFAIL  1f
		 * >> 0x0003:    REOP_GROUP_START 0
		 * >> 0x0005:    REOP_BYTE        "a"
		 * >> 0x0007:    REOP_JMP         2f
		 * >> 0x000a: 1: REOP_GROUP_START 0
		 * >> 0x000c:    REOP_BYTE        "b"
		 * >> 0x000e: 2: REOP_GROUP_END   0
		 * Then the fastmap would be compiled as:
		 *    - "a": @0x0003
		 *    - "b": @0x000a
		 *
		 * NOTE: Only do this if the base-expression starts with
		 *       a  group that contains  at least 1 alternation! */
		expr_start_offset = (size_t)(self->rec_estart - self->rec_cbase);
#if ALTERNATION_PREFIX_MAXLEN > 0
		if (alternation_prefix_wanted) {
			if (!alternation_prefix_hasspace(2)) {
				alternation_prefix_dump();
				goto do_group_start_without_alternation;
			}
			alternation_prefix_putc(REOP_GROUP_START);
			alternation_prefix_putc(gid);
		} else
#endif /* ALTERNATION_PREFIX_MAXLEN > 0 */
		{
			/* Generate the introductory `REOP_GROUP_START' instruction */
#if ALTERNATION_PREFIX_MAXLEN > 0
do_group_start_without_alternation:
#endif /* ALTERNATION_PREFIX_MAXLEN > 0 */
			if (!re_compiler_putc(self, REOP_GROUP_START))
				goto err_nomem;
			if (!re_compiler_putc(self, gid))
				goto err_nomem;
		}

		/* Compile the actual contents of the group. */
		group_start_offset = (size_t)(self->rec_cpos - self->rec_cbase);
		error = re_compiler_compile_alternation(self, alternation_prefix, alternation_prefix_len);
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

		/* Mark the end of the group (this opcode may be overwritten later) */
		if (!re_compiler_putc(self, REOP_GROUP_END))
			goto err_nomem;
		if (!re_compiler_putc(self, gid))
			goto err_nomem;

		/* Figure out if the group is able to match EPSION */
		if unlikely(!re_compiler_require(self, 1))
			goto err_nomem;
		*self->rec_cpos = REOP_MATCHED_PERFECT;
		body = self->rec_cbase + group_start_offset;
		group_matches_epsilon = re_code_matches_epsilon(body);

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
		return RE_NOERROR;
	}

	case RE_TOKEN_STARTSET:
		alternation_prefix_dump();
		return re_compiler_compile_set(self);

	case RE_TOKEN_BK_w:
	case RE_TOKEN_BK_W: {
		if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8) {
			static byte_t const issymcont_y_code[] = {
				REOP_CS_BYTE,
				RECS_BITSET_BUILD(0x20, 12),
				/* 20-27 */ 0x00 | (1 << (0x24 % 8)), /* $ */
				/* 28-2F */ 0x00,
				/* 30-37 */ 0x00 | (1 << (0x30 % 8))  /* 0 */
				/*            */ | (1 << (0x31 % 8))  /* 1 */
				/*            */ | (1 << (0x32 % 8))  /* 2 */
				/*            */ | (1 << (0x33 % 8))  /* 3 */
				/*            */ | (1 << (0x34 % 8))  /* 4 */
				/*            */ | (1 << (0x35 % 8))  /* 5 */
				/*            */ | (1 << (0x36 % 8))  /* 6 */
				/*            */ | (1 << (0x37 % 8)), /* 7 */
				/* 38-3F */ 0x00 | (1 << (0x38 % 8))  /* 8 */
				/*            */ | (1 << (0x39 % 8)), /* 9 */
				/* 40-47 */ 0x00 | (1 << (0x41 % 8))  /* A */
				/*            */ | (1 << (0x42 % 8))  /* B */
				/*            */ | (1 << (0x43 % 8))  /* C */
				/*            */ | (1 << (0x44 % 8))  /* D */
				/*            */ | (1 << (0x45 % 8))  /* E */
				/*            */ | (1 << (0x46 % 8))  /* F */
				/*            */ | (1 << (0x47 % 8)), /* G */
				/* 48-4F */ 0x00 | (1 << (0x48 % 8))  /* H */
				/*            */ | (1 << (0x49 % 8))  /* I */
				/*            */ | (1 << (0x4a % 8))  /* J */
				/*            */ | (1 << (0x4b % 8))  /* K */
				/*            */ | (1 << (0x4c % 8))  /* L */
				/*            */ | (1 << (0x4d % 8))  /* M */
				/*            */ | (1 << (0x4e % 8))  /* N */
				/*            */ | (1 << (0x4f % 8)), /* O */
				/* 50-57 */ 0x00 | (1 << (0x50 % 8))  /* P */
				/*            */ | (1 << (0x51 % 8))  /* Q */
				/*            */ | (1 << (0x52 % 8))  /* R */
				/*            */ | (1 << (0x53 % 8))  /* S */
				/*            */ | (1 << (0x54 % 8))  /* T */
				/*            */ | (1 << (0x55 % 8))  /* U */
				/*            */ | (1 << (0x56 % 8))  /* V */
				/*            */ | (1 << (0x57 % 8)), /* W */
				/* 58-5F */ 0x00 | (1 << (0x58 % 8))  /* X */
				/*            */ | (1 << (0x59 % 8))  /* Y */
				/*            */ | (1 << (0x5a % 8))  /* Z */
				/*            */ | (1 << (0x5f % 8)), /* _ */
				/* 60-67 */ 0x00 | (1 << (0x61 % 8))  /* a */
				/*            */ | (1 << (0x62 % 8))  /* b */
				/*            */ | (1 << (0x63 % 8))  /* c */
				/*            */ | (1 << (0x64 % 8))  /* d */
				/*            */ | (1 << (0x65 % 8))  /* e */
				/*            */ | (1 << (0x66 % 8))  /* f */
				/*            */ | (1 << (0x67 % 8)), /* g */
				/* 68-6F */ 0x00 | (1 << (0x68 % 8))  /* h */
				/*            */ | (1 << (0x69 % 8))  /* i */
				/*            */ | (1 << (0x6a % 8))  /* j */
				/*            */ | (1 << (0x6b % 8))  /* k */
				/*            */ | (1 << (0x6c % 8))  /* l */
				/*            */ | (1 << (0x6d % 8))  /* m */
				/*            */ | (1 << (0x6e % 8))  /* n */
				/*            */ | (1 << (0x6f % 8)), /* o */
				/* 70-77 */ 0x00 | (1 << (0x70 % 8))  /* p */
				/*            */ | (1 << (0x71 % 8))  /* q */
				/*            */ | (1 << (0x72 % 8))  /* r */
				/*            */ | (1 << (0x73 % 8))  /* s */
				/*            */ | (1 << (0x74 % 8))  /* t */
				/*            */ | (1 << (0x75 % 8))  /* u */
				/*            */ | (1 << (0x76 % 8))  /* v */
				/*            */ | (1 << (0x77 % 8)), /* w */
				/* 78-7F */ 0x00 | (1 << (0x78 % 8))  /* x */
				/*            */ | (1 << (0x79 % 8))  /* y */
				/*            */ | (1 << (0x7a % 8)), /* z */
				RECS_DONE
			};
			static byte_t const issymcont_n_code[] = {
				REOP_CS_BYTE,
				RECS_BITSET_BUILD(0x00, 32),
				/* 00-0F */ 0xff, 0xff,
				/* 10-1F */ 0xff, 0xff,
				/* 20-27 */ 0xff & ~(1 << (0x24 % 8)), /* $ */
				/* 28-2F */ 0xff,
				/* 30-37 */ 0xff & ~(1 << (0x30 % 8))  /* 0 */
				/*            */ & ~(1 << (0x31 % 8))  /* 1 */
				/*            */ & ~(1 << (0x32 % 8))  /* 2 */
				/*            */ & ~(1 << (0x33 % 8))  /* 3 */
				/*            */ & ~(1 << (0x34 % 8))  /* 4 */
				/*            */ & ~(1 << (0x35 % 8))  /* 5 */
				/*            */ & ~(1 << (0x36 % 8))  /* 6 */
				/*            */ & ~(1 << (0x37 % 8)), /* 7 */
				/* 38-3F */ 0xff & ~(1 << (0x38 % 8))  /* 8 */
				/*            */ & ~(1 << (0x39 % 8)), /* 9 */
				/* 40-47 */ 0xff & ~(1 << (0x41 % 8))  /* A */
				/*            */ & ~(1 << (0x42 % 8))  /* B */
				/*            */ & ~(1 << (0x43 % 8))  /* C */
				/*            */ & ~(1 << (0x44 % 8))  /* D */
				/*            */ & ~(1 << (0x45 % 8))  /* E */
				/*            */ & ~(1 << (0x46 % 8))  /* F */
				/*            */ & ~(1 << (0x47 % 8)), /* G */
				/* 48-4F */ 0xff & ~(1 << (0x48 % 8))  /* H */
				/*            */ & ~(1 << (0x49 % 8))  /* I */
				/*            */ & ~(1 << (0x4a % 8))  /* J */
				/*            */ & ~(1 << (0x4b % 8))  /* K */
				/*            */ & ~(1 << (0x4c % 8))  /* L */
				/*            */ & ~(1 << (0x4d % 8))  /* M */
				/*            */ & ~(1 << (0x4e % 8))  /* N */
				/*            */ & ~(1 << (0x4f % 8)), /* O */
				/* 50-57 */ 0xff & ~(1 << (0x50 % 8))  /* P */
				/*            */ & ~(1 << (0x51 % 8))  /* Q */
				/*            */ & ~(1 << (0x52 % 8))  /* R */
				/*            */ & ~(1 << (0x53 % 8))  /* S */
				/*            */ & ~(1 << (0x54 % 8))  /* T */
				/*            */ & ~(1 << (0x55 % 8))  /* U */
				/*            */ & ~(1 << (0x56 % 8))  /* V */
				/*            */ & ~(1 << (0x57 % 8)), /* W */
				/* 58-5F */ 0xff & ~(1 << (0x58 % 8))  /* X */
				/*            */ & ~(1 << (0x59 % 8))  /* Y */
				/*            */ & ~(1 << (0x5a % 8))  /* Z */
				/*            */ & ~(1 << (0x5f % 8)), /* _ */
				/* 60-67 */ 0xff & ~(1 << (0x61 % 8))  /* a */
				/*            */ & ~(1 << (0x62 % 8))  /* b */
				/*            */ & ~(1 << (0x63 % 8))  /* c */
				/*            */ & ~(1 << (0x64 % 8))  /* d */
				/*            */ & ~(1 << (0x65 % 8))  /* e */
				/*            */ & ~(1 << (0x66 % 8))  /* f */
				/*            */ & ~(1 << (0x67 % 8)), /* g */
				/* 68-6F */ 0xff & ~(1 << (0x68 % 8))  /* h */
				/*            */ & ~(1 << (0x69 % 8))  /* i */
				/*            */ & ~(1 << (0x6a % 8))  /* j */
				/*            */ & ~(1 << (0x6b % 8))  /* k */
				/*            */ & ~(1 << (0x6c % 8))  /* l */
				/*            */ & ~(1 << (0x6d % 8))  /* m */
				/*            */ & ~(1 << (0x6e % 8))  /* n */
				/*            */ & ~(1 << (0x6f % 8)), /* o */
				/* 70-77 */ 0xff & ~(1 << (0x70 % 8))  /* p */
				/*            */ & ~(1 << (0x71 % 8))  /* q */
				/*            */ & ~(1 << (0x72 % 8))  /* r */
				/*            */ & ~(1 << (0x73 % 8))  /* s */
				/*            */ & ~(1 << (0x74 % 8))  /* t */
				/*            */ & ~(1 << (0x75 % 8))  /* u */
				/*            */ & ~(1 << (0x76 % 8))  /* v */
				/*            */ & ~(1 << (0x77 % 8)), /* w */
				/* 78-7F */ 0xff & ~(1 << (0x78 % 8))  /* x */
				/*            */ & ~(1 << (0x79 % 8))  /* y */
				/*            */ & ~(1 << (0x7a % 8)), /* z */
				/* 80-8F */ 0xff, 0xff,
				/* 90-9F */ 0xff, 0xff,
				/* A0-AF */ 0xff, 0xff,
				/* B0-BF */ 0xff, 0xff,
				/* C0-CF */ 0xff, 0xff,
				/* D0-DF */ 0xff, 0xff,
				/* E0-EF */ 0xff, 0xff,
				/* F0-FF */ 0xff, 0xff,
				RECS_DONE
			};
			if (tok == RE_TOKEN_BK_W) {
				if unlikely(!re_compiler_putn(self, issymcont_n_code, sizeof(issymcont_n_code)))
					goto err_nomem;
			} else {
				if unlikely(!re_compiler_putn(self, issymcont_y_code, sizeof(issymcont_y_code)))
					goto err_nomem;
			}
		} else {
			if (!re_compiler_putc(self, tok == RE_TOKEN_BK_W ? REOP_NCS_UTF8
			                                                 : REOP_CS_UTF8))
				goto err_nomem;
			if (!re_compiler_putc(self, RECS_ISSYMCONT))
				goto err_nomem;
			if (!re_compiler_putc(self, RECS_DONE))
				goto err_nomem;
		}
		goto done_prefix;
	}

	case RE_TOKEN_BK_s:
	case RE_TOKEN_BK_S: {
		if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8) {
			static byte_t const isspace_y_code[] = {
				REOP_CS_BYTE,
				RECS_BITSET_BUILD(0x00, 5),
				/* 00-07 */ 0x00,
				/* 08-0F */ 0x00 | (1 << (0x09 % 8))
				/*            */ | (1 << (0x0A % 8))
				/*            */ | (1 << (0x0B % 8))
				/*            */ | (1 << (0x0C % 8))
				/*            */ | (1 << (0x0D % 8)),
				/* 10-17 */ 0x00,
				/* 18-1F */ 0x00,
				/* 20-27 */ 0x00 | (1 << (0x20 % 8)),
				RECS_DONE
			};
			static byte_t const isspace_n_code[] = {
				REOP_CS_BYTE,
				RECS_BITSET_BUILD(0x00, 32),
				/* 00-0F */ 0xff, 0xff & ~(1 << (0x09 % 8))
				/*                  */ & ~(1 << (0x0A % 8))
				/*                  */ & ~(1 << (0x0B % 8))
				/*                  */ & ~(1 << (0x0C % 8))
				/*                  */ & ~(1 << (0x0D % 8)),
				/* 10-1F */ 0xff, 0xff,
				/* 20-2F */ 0xff & ~(1 << (0x20 % 8)), 0xff,
				/* 30-3F */ 0xff, 0xff,
				/* 40-4F */ 0xff, 0xff,
				/* 50-5F */ 0xff, 0xff,
				/* 60-6F */ 0xff, 0xff,
				/* 70-7F */ 0xff, 0xff,
				/* 80-8F */ 0xff, 0xff,
				/* 90-9F */ 0xff, 0xff,
				/* A0-AF */ 0xff, 0xff,
				/* B0-BF */ 0xff, 0xff,
				/* C0-CF */ 0xff, 0xff,
				/* D0-DF */ 0xff, 0xff,
				/* E0-EF */ 0xff, 0xff,
				/* F0-FF */ 0xff, 0xff,
				RECS_DONE
			};
			if (tok == RE_TOKEN_BK_W) {
				if unlikely(!re_compiler_putn(self, isspace_n_code, sizeof(isspace_n_code)))
					goto err_nomem;
			} else {
				if unlikely(!re_compiler_putn(self, isspace_y_code, sizeof(isspace_y_code)))
					goto err_nomem;
			}
		} else {
			if (!re_compiler_putc(self, (tok == RE_TOKEN_BK_W) ? REOP_NCS_UTF8 : REOP_CS_UTF8))
				goto err_nomem;
			if (!re_compiler_putc(self, RECS_ISSPACE))
				goto err_nomem;
			if (!re_compiler_putc(self, RECS_DONE))
				goto err_nomem;
		}
		goto done_prefix;
	}

	case RE_TOKEN_BK_d:
	case RE_TOKEN_BK_D: {
		if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8) {
			if (!re_compiler_putc(self, (tok == RE_TOKEN_BK_D) ? REOP_NRANGE : REOP_RANGE))
				goto err_nomem;
			if (!re_compiler_putc(self, (byte_t)0x30)) /* '0' */
				goto err_nomem;
			if (!re_compiler_putc(self, (byte_t)0x39)) /* '9' */
				goto err_nomem;
		} else {
			if (!re_compiler_putc(self, (tok == RE_TOKEN_BK_D) ? REOP_NCS_UTF8 : REOP_CS_UTF8))
				goto err_nomem;
			if (!re_compiler_putc(self, RECS_ISDIGIT))
				goto err_nomem;
			if (!re_compiler_putc(self, RECS_DONE))
				goto err_nomem;
		}
		goto done_prefix;
	}

	case RE_TOKEN_BK_n:
	case RE_TOKEN_BK_N: {
		if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8) {
			if (!re_compiler_putc(self, (tok == RE_TOKEN_BK_N) ? REOP_NBYTE2 : REOP_BYTE2))
				goto err_nomem;
			if (!re_compiler_putc(self, (byte_t)0x0a)) /* '\n' */
				goto err_nomem;
			if (!re_compiler_putc(self, (byte_t)0x0d)) /* '\r' */
				goto err_nomem;
		} else {
			if (!re_compiler_putc(self, (tok == RE_TOKEN_BK_N) ? REOP_NCS_UTF8 : REOP_CS_UTF8))
				goto err_nomem;
			if (!re_compiler_putc(self, RECS_ISLF))
				goto err_nomem;
			if (!re_compiler_putc(self, RECS_DONE))
				goto err_nomem;
		}
		goto done_prefix;
	}

	case RE_TOKEN_ANY: {
		uint8_t opcode;
		static_assert(REOP_MAKEANY(false, false, false) == REOP_ANY_NOTNUL_NOTLF);
		static_assert(REOP_MAKEANY(false, false, true) == REOP_ANY_NOTNUL_NOTLF_UTF8);
		static_assert(REOP_MAKEANY(false, true, false) == REOP_ANY_NOTNUL);
		static_assert(REOP_MAKEANY(false, true, true) == REOP_ANY_NOTNUL_UTF8);
		static_assert(REOP_MAKEANY(true, false, false) == REOP_ANY_NOTLF);
		static_assert(REOP_MAKEANY(true, false, true) == REOP_ANY_NOTLF_UTF8);
		static_assert(REOP_MAKEANY(true, true, false) == REOP_ANY);
		static_assert(REOP_MAKEANY(true, true, true) == REOP_ANY_UTF8);
		opcode = REOP_MAKEANY(!(self->rec_parser.rep_syntax & RE_SYNTAX_DOT_NOT_NULL),
		                      self->rec_parser.rep_syntax & RE_SYNTAX_DOT_NEWLINE,
		                      !(self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8));
		alternation_prefix_dump();
		if (!re_compiler_putc(self, opcode))
			goto err_nomem;
		goto done_prefix;
	}

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

		/* Deal with special handling for '^' and '$' */
		if (REOP_AT_SOLEOL_CHECK(opcode) && !(self->rec_parser.rep_syntax & RE_SYNTAX_ANCHORS_IGNORE_EFLAGS))
			opcode = REOP_AT_SOLEOL_MAKEX(opcode);

		/* `REOP_AT_*' qualify for being written as alternation prefixes! */
#if ALTERNATION_PREFIX_MAXLEN > 0
		if (alternation_prefix_wanted) {
			if (alternation_prefix_hasspace(1)) {
				alternation_prefix_putc(opcode);
				/* Parse another prefix expression since location assertions don't count as prefixes! */
				goto again;
			} else {
				alternation_prefix_dump();
			}
		}
#endif /* ALTERNATION_PREFIX_MAXLEN > 0 */

		if (!re_compiler_putc(self, opcode))
			goto err_nomem;
		/* Parse another prefix expression since location assertions don't count as prefixes! */
		goto again;
	}

	case RE_TOKEN_BKREF_1 ... RE_TOKEN_BKREF_9: {
		uint8_t gid = tok - RE_TOKEN_BKREF_1;
		uint8_t ginfo;
		assert(gid <= 8); /* 1-9 --> 9 groups -> 0-based index must be <= 8 */
		ginfo = self->rec_grpinfo[gid];
		if (!(ginfo & RE_COMPILER_GRPINFO_DEFINED))
			return RE_ESUBREG;
		alternation_prefix_dump();
		if (!re_compiler_putc(self, REOP_GROUP_MATCH))
			goto err_nomem;
		if (!re_compiler_putc(self, gid))
			goto err_nomem;
		if (ginfo & RE_COMPILER_GRPINFO_EPSILON)
			return RE_COMPILER_COMPILE_PREFIX__AFTER_EPSILON_GROUP;
		goto done_prefix;
	}

	default:
		if (!RE_TOKEN_ISLITERAL(tok)) {
			return RE_BADPAT;
		} else {
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
			literal_seq_isutf8  = RE_TOKEN_ISUTF8(tok);
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
				literal_seq_isutf8 |= RE_TOKEN_ISUTF8(lit);
				old_literal_seq_end = literal_seq_end;
				literal_seq_end     = self->rec_parser.rep_pos;
				++literal_seq_length;
			}
			if (self->rec_parser.rep_syntax & RE_SYNTAX_NO_UTF8)
				literal_seq_isutf8 = false; /* They're always just bytes! */

			/* Encode the literal sequence */
			alternation_prefix_dump();
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
done_prefix:
	return RE_NOERROR;
err_nomem:
	return RE_ESPACE;
}


#define RE_EPSILON_JMP_ENCODE(baseop, offset) ((baseop) + 1 + (offset) - 3)
static_assert(REOP_GROUP_MATCH_JMIN == REOP_GROUP_MATCH_J3);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 3) == REOP_GROUP_MATCH_J3);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 4) == REOP_GROUP_MATCH_J4);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 5) == REOP_GROUP_MATCH_J5);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 6) == REOP_GROUP_MATCH_J6);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 7) == REOP_GROUP_MATCH_J7);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 8) == REOP_GROUP_MATCH_J8);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 9) == REOP_GROUP_MATCH_J9);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 10) == REOP_GROUP_MATCH_J10);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_MATCH, 11) == REOP_GROUP_MATCH_J11);
static_assert(REOP_GROUP_MATCH_JMAX == REOP_GROUP_MATCH_J11);
static_assert(REOP_GROUP_END_JMIN == REOP_GROUP_END_J3);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 3) == REOP_GROUP_END_J3);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 4) == REOP_GROUP_END_J4);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 5) == REOP_GROUP_END_J5);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 6) == REOP_GROUP_END_J6);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 7) == REOP_GROUP_END_J7);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 8) == REOP_GROUP_END_J8);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 9) == REOP_GROUP_END_J9);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 10) == REOP_GROUP_END_J10);
static_assert(RE_EPSILON_JMP_ENCODE(REOP_GROUP_END, 11) == REOP_GROUP_END_J11);
static_assert(REOP_GROUP_END_JMAX == REOP_GROUP_END_J11);


PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC re_compiler_set_group_epsilon_jmp)(uint8_t *p_group_instruction,
                                                  uint8_t num_bytes_skip_if_empty) {
	assert(num_bytes_skip_if_empty >= 3 && num_bytes_skip_if_empty <= 11);
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

	/* TODO: Any use-case that is implemented via `REOP_JMP_ONFAIL_DUMMY_AT' should
	 *       first  check if `expr_size'  is smaller than `EXPR_DUPLICATE_MAXSIZE'.
	 *       If that is the case, then encode the expression twice:
	 *       e.g. "X+" can be encoded as "XX*" (which doesn't use dummy on-fail handlers)
	 */

	/* When many are accepted, then `interval_max' is infinite */
	if (interval_max_is_unbounded) {
		if (interval_min == 0) {
			byte_t *writer, *label_1, *label_2;
			/* >> "X*"           REOP_JMP_ONFAIL 2f
			 * >>             1: <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `2f'
			 * >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
			 * >>                REOP_JMP_AND_RETURN_ONFAIL 1b
			 * >>             2: */
			if unlikely(!re_compiler_require(self, 9))
				goto err_nomem;

			/* Make space for code we want to insert in the front */
			writer = self->rec_estart;
			memmoveup(writer + 3, writer, expr_size);

			/* REOP_JMP_ONFAIL 2f */
			*writer++ = REOP_JMP_ONFAIL;
			label_2 = writer + 2 + expr_size + 3 + 3;
			int16_at(writer) = (int16_t)(label_2 - (writer + 2));
			writer += 2;

			/* This is where the "1:" is in the pseudo-code */
			label_1 = writer;
			writer += expr_size;
			if (expression_matches_epsilon)
				re_compiler_set_group_epsilon_jmp(writer - 2, 3 + 3);

			/* REOP_MAYBE_POP_ONFAIL */
			*writer++ = REOP_MAYBE_POP_ONFAIL;
			writer += 2;

			/* REOP_JMP_AND_RETURN_ONFAIL 1b */
			*writer++ = REOP_JMP_AND_RETURN_ONFAIL;
			int16_at(writer) = (int16_t)(label_1 - (writer + 2));
			writer += 2;
			assert(label_2 == writer);

			self->rec_cpos = writer;
			goto done_suffix;
		} else if (interval_min == 1) {
			byte_t *writer, *label_1, *label_2;
			/* >> "X+"           REOP_JMP_ONFAIL_DUMMY_AT 2f
			 * >>             1: <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `2f'
			 * >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
			 * >>                REOP_JMP_AND_RETURN_ONFAIL 1b
			 * >>             2: */
			if unlikely(!re_compiler_require(self, 9))
				goto err_nomem;

			/* Make space for code we want to insert in the front */
			writer = self->rec_estart;
			memmoveup(writer + 3, writer, expr_size);

			/* REOP_JMP_ONFAIL_DUMMY_AT 2f */
			label_2 = writer + 3 + expr_size + 3 + 3;
			*writer++ = REOP_JMP_ONFAIL_DUMMY_AT;
			int16_at(writer) = (int16_t)(label_2 - (writer + 2));
			writer += 2;

			/* <X> */
			label_1 = writer;
			writer += expr_size;
			if (expression_matches_epsilon)
				re_compiler_set_group_epsilon_jmp(writer - 2, 3 + 3);

			/* REOP_MAYBE_POP_ONFAIL */
			*writer++ = REOP_MAYBE_POP_ONFAIL;
			writer += 2;

			/* REOP_JMP_AND_RETURN_ONFAIL 1b */
			*writer++ = REOP_JMP_AND_RETURN_ONFAIL;
			int16_at(writer) = (int16_t)(label_1 - (writer + 2));
			writer += 2;
			assert(label_2 == writer);

			self->rec_cpos = writer;
			goto done_suffix;
		} else {
			uint8_t var_id;
			byte_t *writer, *label_1, *label_2, *label_3;
			/* >> "X{n,}"        REOP_SETVAR  {VAR = (n - 1)}
			 * >>            1:  REOP_JMP_ONFAIL_DUMMY_AT 3f
			 * >>            2:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `3f'
			 * >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
			 * >>                REOP_DEC_JMP {VAR}, 1b
			 * >>                REOP_JMP_AND_RETURN_ONFAIL 2b
			 * >>            3: */
			if unlikely(!re_compiler_require(self, 16))
				goto err_nomem;
			if unlikely(!re_compiler_allocvar(self, &var_id))
				goto err_esize;

			/* Make space for code we want to insert in the front */
			writer = self->rec_estart;
			memmoveup(writer + 6, writer, expr_size);

			/* REOP_SETVAR  {VAR = (n - 1)} */
			*writer++ = REOP_SETVAR;
			*writer++ = var_id;
			*writer++ = interval_min - 1;

			/* REOP_JMP_ONFAIL_DUMMY_AT 3f */
			label_1 = writer;
			label_3 = writer + 3 + expr_size + 3 + 4 + 3;
			*writer++ = REOP_JMP_ONFAIL_DUMMY_AT;
			int16_at(writer) = (int16_t)(label_3 - (writer + 2));
			writer += 2;

			/* <X> */
			label_2 = writer;
			writer += expr_size;
			if (expression_matches_epsilon)
				re_compiler_set_group_epsilon_jmp(writer - 2, 3 + 4 + 3);

			/* REOP_MAYBE_POP_ONFAIL */
			*writer++ = REOP_MAYBE_POP_ONFAIL;
			writer += 2;

			/* REOP_DEC_JMP {VAR}, 1b */
			*writer++ = REOP_DEC_JMP;
			*writer++ = var_id;
			int16_at(writer) = (int16_t)(label_1 - (writer + 2));
			writer += 2;

			/* REOP_JMP_AND_RETURN_ONFAIL 2b */
			*writer++ = REOP_JMP_AND_RETURN_ONFAIL;
			int16_at(writer) = (int16_t)(label_2 - (writer + 2));
			writer += 2;
			assert(label_3 == writer);

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
		for (; reader < self->rec_cpos; reader = libre_opcode_next(reader)) {
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
		byte_t *writer, *label_1, *label_2;

		/* Check for special (and simple) case: always match exactly 1 */
		if (interval_max == 1)
			goto done_suffix;

		/* >> "X{1,m}"       REOP_SETVAR  {VAR = (m - 1)}
		 * >>                REOP_JMP_ONFAIL_DUMMY_AT 2f
		 * >>            1:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `2f'
		 * >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
		 * >>                REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b
		 * >>            2: */
		if unlikely(!re_compiler_require(self, 13))
			goto err_nomem;
		if unlikely(!re_compiler_allocvar(self, &var_id))
			goto err_esize;

		/* Make space for code we want to insert in the front */
		writer = self->rec_estart;
		memmoveup(writer + 6, writer, expr_size);

		/* REOP_SETVAR  {VAR = (m - 1)} */
		*writer++ = REOP_SETVAR;
		*writer++ = var_id;
		*writer++ = interval_max - 1;

		/* REOP_JMP_ONFAIL_DUMMY_AT 3f */
		label_2 = writer + 3 + expr_size + 3 + 4;
		*writer++ = REOP_JMP_ONFAIL_DUMMY_AT;
		int16_at(writer) = (int16_t)(label_2 - (writer + 2));
		writer += 2;

		/* <X> */
		label_1 = writer;
		writer += expr_size;
		if (expression_matches_epsilon)
			re_compiler_set_group_epsilon_jmp(writer - 2, 3 + 4);

		/* REOP_MAYBE_POP_ONFAIL */
		*writer++ = REOP_MAYBE_POP_ONFAIL;
		writer += 2;

		/* REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b */
		*writer++ = REOP_DEC_JMP_AND_RETURN_ONFAIL;
		*writer++ = var_id;
		int16_at(writer) = (int16_t)(label_1 - (writer + 2));
		writer += 2;
		assert(label_2 == writer);

		self->rec_cpos = writer;
		goto done_suffix;
	}

	if (interval_min == 0) {
		if (interval_max == 1) {
			/* >> "X?"           REOP_JMP_ONFAIL 1f
			 * >>                <X>
			 * >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 1f'
			 * >>            1: */
			byte_t *writer;
			if unlikely(!re_compiler_require(self, 6))
				goto err_nomem;
			writer = self->rec_estart;
			memmoveup(writer + 3, writer, expr_size);

			/* REOP_JMP_ONFAIL 1f */
			*writer++ = REOP_JMP_ONFAIL;
			int16_at(writer) = (int16_t)(expr_size + 3);
			writer += 2;

			/* <X> */
			writer += expr_size;

			/* REOP_MAYBE_POP_ONFAIL */
			*writer++ = REOP_MAYBE_POP_ONFAIL;
			writer += 2;

			self->rec_cpos = writer;
			goto done_suffix;
		} else {
			uint8_t var_id;
			byte_t *writer, *label_1, *label_2;
			/* >> "X{0,m}"       REOP_SETVAR  {VAR = (m - 1)}
			 * >>                REOP_JMP_ONFAIL 2f
			 * >>            1:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `2f'
			 * >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
			 * >>                REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b
			 * >>            2: */
			if unlikely(!re_compiler_require(self, 13))
				goto err_nomem;
			if unlikely(!re_compiler_allocvar(self, &var_id))
				goto err_esize;

			/* Make space for code we want to insert in the front */
			writer = self->rec_estart;
			memmoveup(writer + 6, writer, expr_size);

			/* REOP_SETVAR  {VAR = (m - 1)} */
			*writer++ = REOP_SETVAR;
			*writer++ = var_id;
			*writer++ = interval_max - 1;

			/* REOP_JMP_ONFAIL 2f */
			label_2 = writer + 3 + expr_size + 3 + 4;
			*writer++ = REOP_JMP_ONFAIL;
			int16_at(writer) = (int16_t)(label_2 - (writer + 2));
			writer += 2;

			/* <X> */
			label_1 = writer;
			writer += expr_size;
			if (expression_matches_epsilon)
				re_compiler_set_group_epsilon_jmp(writer - 2, 3 + 4);

			/* REOP_MAYBE_POP_ONFAIL */
			*writer++ = REOP_MAYBE_POP_ONFAIL;
			writer += 2;

			/* REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b */
			*writer++ = REOP_DEC_JMP_AND_RETURN_ONFAIL;
			*writer++ = var_id;
			int16_at(writer) = (int16_t)(label_1 - (writer + 2));
			writer += 2;
			assert(label_2 == writer);

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
	 * >>            1:  REOP_JMP_ONFAIL_DUMMY_AT 3f
	 * >>            2:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `3f'
	 * >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 3f'
	 * >>                REOP_DEC_JMP {VAR1}, 1b
	 * >>                REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR2}, 2b
	 * >>            3: */
	{
		uint8_t var1_id, var2_id;
		byte_t *writer, *label_1, *label_2, *label_3;
		if unlikely(!re_compiler_require(self, 20))
			goto err_nomem;

		/* Allocate variable IDs */
		if unlikely(!re_compiler_allocvar(self, &var1_id))
			goto err_esize;
		if unlikely(!re_compiler_allocvar(self, &var2_id))
			goto err_esize;

		/* Make space for code we want to insert in the front */
		writer = self->rec_estart;
		memmoveup(writer + 9, writer, expr_size);

		/* REOP_SETVAR  {VAR1 = n - 1} */
		*writer++ = REOP_SETVAR;
		*writer++ = var1_id;
		*writer++ = interval_min - 1;

		/* REOP_SETVAR  {VAR2 = (m - n)} */
		*writer++ = REOP_SETVAR;
		*writer++ = var2_id;
		*writer++ = interval_max - interval_min;

		/* 1:  REOP_JMP_ONFAIL_DUMMY_AT 3f */
		label_1 = writer;
		label_3 = writer + 3 + expr_size + 3 + 4 + 4;
		*writer++ = REOP_JMP_ONFAIL_DUMMY_AT;
		int16_at(writer) = (int16_t)(label_3 - (writer + 2));
		writer += 2;

		/* 2:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `3f' */
		label_2 = writer;
		writer += expr_size;
		if (expression_matches_epsilon)
			re_compiler_set_group_epsilon_jmp(writer - 2, 3 + 4 + 4);

		/* REOP_MAYBE_POP_ONFAIL */
		*writer++ = REOP_MAYBE_POP_ONFAIL;
		writer += 2;

		/* REOP_DEC_JMP {VAR1}, 1b */
		*writer++ = REOP_DEC_JMP;
		*writer++ = var1_id;
		int16_at(writer) = (int16_t)(label_1 - (writer + 2));
		writer += 2;

		/* REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR2}, 2b */
		*writer++ = REOP_DEC_JMP_AND_RETURN_ONFAIL;
		*writer++ = var2_id;
		int16_at(writer) = (int16_t)(label_2 - (writer + 2));
		writer += 2;
		assert(label_3 == writer);

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
				struct re_interval interval;
				if unlikely(!parse_interval((char const **)&self->rec_parser.rep_pos,
				                            self->rec_parser.rep_syntax, &interval))
					goto err_badinterval;
				accept_many |= interval.ri_many;

				/* Merge new interval with already-parsed interval */
				if unlikely(!accept_zero && OVERFLOW_UMUL(interval_min, interval.ri_min, &interval_min))
					goto err_badinterval;
				if unlikely(!accept_many && OVERFLOW_UMUL(interval_max, interval.ri_max, &interval_max))
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


/* Compile a sequence of prefix/suffix expressions, as well as '|'
 * @param: alternation_prefix: A code-blob that is inserted before
 *                             the  body  of  every   alternation.
 * @param: alternation_prefix_size: *ditto* */
#if ALTERNATION_PREFIX_MAXLEN > 0
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC re_compiler_compile_alternation)(struct re_compiler *__restrict self,
                                                void const *alternation_prefix,
                                                size_t alternation_prefix_size)
#else /* ALTERNATION_PREFIX_MAXLEN > 0 */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC _re_compiler_compile_alternation)(struct re_compiler *__restrict self)
#endif /* ALTERNATION_PREFIX_MAXLEN <= 0 */
{
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

	/* Insert the alternation prefix (if one was given) */
#if ALTERNATION_PREFIX_MAXLEN > 0
	if (alternation_prefix_size > 0) {
		if (!re_compiler_putn(self, alternation_prefix, alternation_prefix_size))
			goto err_nomem;
	}
#endif /* ALTERNATION_PREFIX_MAXLEN > 0 */

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

		/* Ensure that we've got enough memory for `REOP_JMP_ONFAIL', `REOP_MAYBE_POP_ONFAIL', and `REOP_JMP' */
		if unlikely(!re_compiler_require(self, 9))
			goto err_nomem;
		current_alternation_startptr = self->rec_cbase + current_alternation_startoff;
		current_alternation_size     = (size_t)(self->rec_cpos - current_alternation_startptr);
		memmoveup(current_alternation_startptr + 3,
		          current_alternation_startptr,
		          current_alternation_size);

		/* Insert the leading `REOP_JMP_ONFAIL' that points to the next alternation */
		*current_alternation_startptr++ = REOP_JMP_ONFAIL;
		int16_at(current_alternation_startptr) = (int16_t)(current_alternation_size + 6);
		current_alternation_startptr += 2;
		current_alternation_startptr += current_alternation_size;
		*current_alternation_startptr++ = REOP_MAYBE_POP_ONFAIL;
		current_alternation_startptr += 2;

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
		 * >>    REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 1f'
		 * >>    REOP_JMP         2f // << `initial_alternation_jmp' points to this instruction
		 * >> 1: REOP_JMP_ONFAIL  3f
		 * >>    <Y>
		 * >>    REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 1f'
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


/* Parse  and compile the pattern given to `self' to generate code.
 * Even  upon error, `self'  remains in a  valid state (except that
 * you're  not allowed to call `re_compiler_compile(3R)' again), so
 * that the caller has to invoke `re_compiler_fini(3R)' in order to
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
 * @return: RE_ERPAREN: Unmatched ')' (only when `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' was set)
 * @return: RE_EILLSET: Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]") */
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
	error = re_compiler_compile_alternation(self, NULL, 0);
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

	/* Apply peephole optimizations to the code produced by `self' */
	libre_compiler_peephole(self);

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

		/* Calculate code properties. */
		libre_code_makefast(header);

		/* TODO: FIXME: Non-zero fmap offsets are  allowed to skip across  `REOP_JMP_ONFAIL'
		 *              opcodes (and others that also push  on-fail items). As a result,  it
		 *              regexec starts executing code that assumes a non-empty on-fail stack
		 *              with one that is actually empty.
		 * Currently, this is being worked around by regexec() ignoring empty on-fail stacks
		 * when opcodes try to pop items from said stack. */
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
	byte_t const *pc, *nextpc;
	ssize_t temp, result = 0;
	unsigned int i;
	bool is_first_fmap_entry;
	PRINT("fmap: [");
	/* Print the fast-map */
	is_first_fmap_entry = true;
	for (i = 0; i < 256;) {
		char buf[3];
		unsigned int fend, fcnt;
		byte_t fmap_offset;
		fmap_offset = self->rc_fmap[i];
		if (fmap_offset == 0xff) {
			++i;
			continue;
		}
		fend = i + 1;
		while (fend < 256 && self->rc_fmap[fend] == fmap_offset)
			++fend;
		fcnt = fend - i;
		if (fcnt > 3) {
			buf[0] = (char)i;
			buf[1] = '-';
			buf[2] = (char)(fend - 1);
			fcnt   = 3;
		} else {
			buf[0] = (char)(i + 0);
			buf[1] = (char)(i + 1);
			buf[2] = (char)(i + 2);
		}
		printf("%s\t%$q: %#.4" PRIx8 "\n", is_first_fmap_entry ? "\n" : "",
		       (size_t)fcnt, buf, (uint8_t)fmap_offset);
		is_first_fmap_entry = false;
		i = fend;
	}
	printf("]\n"
	       "minmatch: %" PRIuSIZ "\n"
	       "ngrps: %" PRIu16 "\n"
	       "nvars: %" PRIu16 "\n",
	       self->rc_minmatch,
	       self->rc_ngrps,
	       self->rc_nvars);
	for (pc = self->rc_code;; pc = nextpc) {
		size_t offset;
		byte_t opcode;
		char const *opcode_repr;
		nextpc = libre_opcode_next(pc);
		offset = (size_t)(pc - self->rc_code);
		opcode = *pc++;
		printf("%#.4" PRIxSIZ ": ", offset);
		switch (opcode) {

		case REOP_EXACT: {
			uint8_t len = *pc++;
			printf("exact %$q", (size_t)len, pc);
		}	break;

		case REOP_EXACT_ASCII_ICASE: {
			uint8_t len = *pc++;
			printf("exact_ascii_icase %$q", (size_t)len, pc);
		}	break;

		case REOP_EXACT_UTF8_ICASE: {
			++pc;
			printf("exact_ascii_icase %$q", (size_t)(nextpc - pc), pc);
		}	break;

		case REOP_BYTE:
		case REOP_NBYTE: {
			printf("%schar %$q",
			       opcode == REOP_NBYTE ? "n" : "",
			       (size_t)1, pc);
		}	break;

		case REOP_BYTE2:
		case REOP_NBYTE2: {
			printf("%schar2 %$q",
			       opcode == REOP_NBYTE2 ? "n" : "",
			       (size_t)2, pc);
		}	break;

		case REOP_RANGE:
		case REOP_NRANGE: {
			printf("%srange '%#$q-%#$q'",
			       opcode == REOP_NRANGE ? "n" : "",
			       (size_t)1, pc + 0,
			       (size_t)1, pc + 1);
		}	break;

		case REOP_CONTAINS_UTF8:
		case REOP_NCONTAINS_UTF8: {
			++pc;
			printf("%scontains_utf8 %$q",
			       opcode == REOP_NCONTAINS_UTF8 ? "n" : "",
			       (size_t)(nextpc - pc), pc);
		}	break;

		case REOP_CS_BYTE:
		case REOP_CS_UTF8:
		case REOP_NCS_UTF8: {
			uint8_t cs_opcode;
			bool isfirst;
			switch (opcode) {
			case REOP_CS_BYTE:
				opcode_repr = "cs_byte";
				break;
			case REOP_CS_UTF8:
				opcode_repr = "cs_utf8";
				break;
			case REOP_NCS_UTF8:
				opcode_repr = "ncs_utf8";
				break;
			default: __builtin_unreachable();
			}
			printf("%s [", opcode_repr);
			isfirst = true;
			while ((cs_opcode = *pc++) != RECS_DONE) {
				if (!isfirst)
					PRINT(", ");
				isfirst = false;
				switch (cs_opcode) {

				case RECS_CHAR:
				case RECS_CHAR2: {
					byte_t const *endpc = pc;
					printf("char%s ", cs_opcode == RECS_CHAR2 ? "2" : "");
					if (opcode == REOP_CS_BYTE) {
						endpc += 1;
						if (cs_opcode == RECS_CHAR2)
							endpc += 1;
					} else {
						endpc += unicode_utf8seqlen[*endpc];
						if (cs_opcode == RECS_CHAR2)
							endpc += unicode_utf8seqlen[*endpc];
					}
					printf("%$q", (size_t)(endpc - pc), pc);
					pc = endpc;
				}	break;

				case RECS_RANGE:
				case RECS_RANGE_ICASE:
					printf("range%s ", cs_opcode == RECS_RANGE_ICASE ? "_icase" : "");
					if (opcode == REOP_CS_BYTE) {
						printf("'%#$q-%#$q'", (size_t)1, &pc[0], (size_t)1, &pc[1]);
						pc += 2;
					} else {
						byte_t const *char2;
						byte_t const *endp;
						char2 = pc + unicode_utf8seqlen[*pc];
						endp  = char2 + unicode_utf8seqlen[*char2];
						printf("'%#$q-%#$q'", (size_t)(char2 - pc), pc, (size_t)(endp - char2), char2);
						pc = endp;
					}
					break;

				case RECS_CONTAINS: {
					uint8_t count = *pc++;
					byte_t const *cs_opcode_end;
					assert(count >= 1);
					PRINT("contains ");
					if (opcode == REOP_CS_BYTE) {
						cs_opcode_end = pc + count;
					} else {
						cs_opcode_end = pc;
						do {
							cs_opcode_end += unicode_utf8seqlen[*cs_opcode_end];
						} while (--count);
					}
					printf("%$q", (size_t)(cs_opcode_end - pc), pc);
					pc = cs_opcode_end;
				}	break;

				case RECS_ISX_MIN ... RECS_ISX_MAX: {
					char const *cs_name;
					if (opcode == REOP_CS_BYTE)
						goto do_cs_bitset;
					switch (cs_opcode) {
					case RECS_ISCNTRL:
						cs_name = "cntrl";
						break;
					case RECS_ISSPACE:
						cs_name = "space";
						break;
					case RECS_ISUPPER:
						cs_name = "upper";
						break;
					case RECS_ISLOWER:
						cs_name = "lower";
						break;
					case RECS_ISALPHA:
						cs_name = "alpha";
						break;
					case RECS_ISDIGIT:
						cs_name = "digit";
						break;
					case RECS_ISXDIGIT:
						cs_name = "xdigit";
						break;
					case RECS_ISALNUM:
						cs_name = "alnum";
						break;
					case RECS_ISPUNCT:
						cs_name = "punct";
						break;
					case RECS_ISGRAPH:
						cs_name = "graph";
						break;
					case RECS_ISPRINT:
						cs_name = "print";
						break;
					case RECS_ISBLANK:
						cs_name = "blank";
						break;
					case RECS_ISSYMSTRT:
						cs_name = "symstrt";
						break;
					case RECS_ISSYMCONT:
						cs_name = "symcont";
						break;
					case RECS_ISTAB:
						cs_name = "tab";
						break;
					case RECS_ISWHITE:
						cs_name = "white";
						break;
					case RECS_ISEMPTY:
						cs_name = "empty";
						break;
					case RECS_ISLF:
						cs_name = "lf";
						break;
					case RECS_ISHEX:
						cs_name = "hex";
						break;
					case RECS_ISTITLE:
						cs_name = "title";
						break;
					case RECS_ISNUMERIC:
						cs_name = "numeric";
						break;
					default: __builtin_unreachable();
					}
					printf("is%s", cs_name);
				}	break;

				default:
					if (cs_opcode >= RECS_BITSET_MIN &&
					    cs_opcode <= (opcode == REOP_CS_BYTE ? RECS_BITSET_BYTE_MAX
					                                         : RECS_BITSET_UTF8_MAX)) {
						uint8_t minch, bitset_size;
						unsigned int bitset_bits;
do_cs_bitset:
						minch       = RECS_BITSET_GETBASE(cs_opcode);
						bitset_size = RECS_BITSET_GETBYTES(cs_opcode);
						bitset_bits = bitset_size * 8;
						PRINT("bitset [");
						for (i = 0; i < bitset_bits;) {
							char repr[3];
							unsigned int endi, rangec;
							if ((pc[i / 8] & (1 << (i % 8))) == 0) {
								++i;
								continue;
							}
							endi = i + 1;
							while (endi < bitset_bits && (pc[endi / 8] & (1 << (endi % 8))) != 0)
								++endi;
							rangec = endi - i;
							if (rangec > 3) {
								repr[0] = (char)(minch + i);
								repr[1] = '-';
								repr[2] = (char)(minch + endi - 1);
								rangec  = 3;
							} else {
								repr[0] = (char)(minch + i + 0);
								repr[1] = (char)(minch + i + 1);
								repr[2] = (char)(minch + i + 2);
							}
							printf("%#$q", (size_t)rangec, repr);
							i = endi;
						}
						pc += bitset_size;
						PRINT("]");
						break;
					}
					printf("<BAD BYTE %#.2" PRIx8 ">", cs_opcode);
					break;
				}
			}
			PRINT("]");
			assertf(pc == nextpc, "pc - nextpc = %Id", pc - nextpc);
		}	break;

		case REOP_GROUP_MATCH: {
			uint8_t gid = *pc++;
			printf("group_match %" PRIu8, gid);
		}	break;

		case REOP_GROUP_MATCH_JMIN ... REOP_GROUP_MATCH_JMAX: {
			uint8_t gid       = *pc++;
			byte_t const *jmp = pc + REOP_GROUP_MATCH_Joff(opcode);
			printf("group_match %" PRIu8 ", @%#.4" PRIxSIZ,
			       gid, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_GROUP_START: {
			uint8_t gid = *pc++;
			printf("group_start %" PRIu8, gid);
		}	break;

		case REOP_GROUP_END: {
			uint8_t gid = *pc++;
			printf("group_end %" PRIu8, gid);
		}	break;

		case REOP_GROUP_END_JMIN ... REOP_GROUP_END_JMAX: {
			uint8_t gid       = *pc++;
			byte_t const *jmp = pc + REOP_GROUP_END_Joff(opcode);
			printf("group_end %" PRIu8 ", @%#.4" PRIxSIZ,
			       gid, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_POP_ONFAIL_AT: {
			byte_t const *jmp = pc + 2 + int16_at(pc);
			printf("pop_onfail_at @%#.4" PRIxSIZ, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_JMP_ONFAIL: {
			byte_t const *jmp = pc + 2 + int16_at(pc);
			printf("jmp_onfail @%#.4" PRIxSIZ, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_JMP_ONFAIL_DUMMY_AT: {
			byte_t const *jmp = pc + 2 + int16_at(pc);
			printf("jmp_onfail_dummy_at @%#.4" PRIxSIZ, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_JMP: {
			byte_t const *jmp = pc + 2 + int16_at(pc);
			printf("jmp @%#.4" PRIxSIZ, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_JMP_AND_RETURN_ONFAIL: {
			byte_t const *jmp = pc + 2 + int16_at(pc);
			printf("jmp_and_return_onfail @%#.4" PRIxSIZ, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_DEC_JMP: {
			uint8_t varid     = *pc++;
			byte_t const *jmp = pc + 2 + int16_at(pc);
			printf("dec_jmp %" PRIu8 ", @%#.4" PRIxSIZ, varid, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_DEC_JMP_AND_RETURN_ONFAIL: {
			uint8_t varid     = *pc++;
			byte_t const *jmp = pc + 2 + int16_at(pc);
			printf("dec_jmp_and_return_onfail %" PRIu8 ", @%#.4" PRIxSIZ, varid, (size_t)(jmp - self->rc_code));
		}	break;

		case REOP_SETVAR: {
			uint8_t varid = *pc++;
			uint8_t value = *pc++;
			printf("setvar %" PRIu8 ", %" PRIu8, varid, value);
		}	break;

#define SIMPLE_OPCODE(opcode, repr) \
		case opcode:                \
			opcode_repr = repr;     \
			goto do_print_opcode_repr
		SIMPLE_OPCODE(REOP_ANY, "any");
		SIMPLE_OPCODE(REOP_ANY_UTF8, "any");
		SIMPLE_OPCODE(REOP_ANY_NOTLF, "any_notlf");
		SIMPLE_OPCODE(REOP_ANY_NOTLF_UTF8, "any_notlf");
		SIMPLE_OPCODE(REOP_ANY_NOTNUL, "any_notnul");
		SIMPLE_OPCODE(REOP_ANY_NOTNUL_UTF8, "any_notnul");
		SIMPLE_OPCODE(REOP_ANY_NOTNUL_NOTLF, "any_notnul_notlf");
		SIMPLE_OPCODE(REOP_ANY_NOTNUL_NOTLF_UTF8, "any_notnul_notlf_utf8");
		SIMPLE_OPCODE(REOP_AT_SOI, "at_soi");
		SIMPLE_OPCODE(REOP_AT_EOI, "at_eoi");
		SIMPLE_OPCODE(REOP_AT_SOL, "at_sol");
		SIMPLE_OPCODE(REOP_AT_SOL_UTF8, "at_sol_utf8");
		SIMPLE_OPCODE(REOP_AT_EOL, "at_eol");
		SIMPLE_OPCODE(REOP_AT_EOL_UTF8, "at_eol_utf8");
		SIMPLE_OPCODE(REOP_AT_SOXL, "at_soxl");
		SIMPLE_OPCODE(REOP_AT_SOXL_UTF8, "at_soxl_utf8");
		SIMPLE_OPCODE(REOP_AT_EOXL, "at_eoxl");
		SIMPLE_OPCODE(REOP_AT_EOXL_UTF8, "at_eoxl_utf8");
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
		SIMPLE_OPCODE(REOP_JMP_ONFAIL_DUMMY, "jmp_onfail_dummy");
		SIMPLE_OPCODE(REOP_POP_ONFAIL, "pop_onfail");
		SIMPLE_OPCODE(REOP_MATCHED, "matched");
		SIMPLE_OPCODE(REOP_MAYBE_POP_ONFAIL, "[maybe_pop_onfail]");
#undef SIMPLE_OPCODE
		case REOP_MATCHED_PERFECT:
			opcode_repr = "matched_perfect";
do_print_opcode_repr:
			DO((*printer)(arg, opcode_repr, strlen(opcode_repr)));
			break;

		default:
			printf(".byte %#" PRIx8, opcode);
			for (; pc < nextpc; ++pc)
				printf(", %#" PRIx8, *pc);
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
