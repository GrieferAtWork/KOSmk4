/*[[[magic
local cflags = options.get("COMPILE.cflags");
for (o: { "-mno-sse", "-mno-sse2", "-mno-sse3", "-mno-sse4", "-mno-ssse3", "-mno-mmx", "-mno-3dnow", "-mno-avx" })
	cflags.remove(o);
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
#ifndef GUARD_MODDBX_CEVAL_C
#define GUARD_MODDBX_CEVAL_C 1
#define _KOS_SOURCE 1
#define __HAVE_FPU 1 /* Enable FPU access */

/* DeBug eXtensions. */

#include <__crt.h>

#ifndef __CRT_HAVE_strtold
/* strtold() uses  format_scanf() to  implement  itself. However  the  kernel
 * version of  that  function  doesn't  include  floating-point  support.  As
 * such, as the headers to provide us with our own version of format_scanf(),
 * which _does_ include floating-point support.
 * (A bit wasteful, since we don't actually use its other features, but
 * it's the simplest solution to this problem...) */
#undef __CRT_HAVE_format_scanf
#undef __CRT_HAVE_format_vscanf
#endif /* !__CRT_HAVE_strtold */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

#include <debugger/rt.h>
#include <kernel/types.h>

#include <hybrid/byteorder.h>
#include <hybrid/unaligned.h>

#include <sys/param.h>

#include <ieee754.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unicode.h>

/**/
#include "include/ceval.h"
#include "include/cexpr.h"
#include "include/cmodule.h"
#include "include/cparser.h"
#include "include/ctype.h"
#include "include/malloc.h"

DECL_BEGIN

/* These may have been defined by <iso646.h> */
#ifndef __cplusplus
#undef bitand
#undef bitor
#endif /* !__cplusplus */


#define yield() cparser_yield(self)

#define KWD_CHECK(kwd_str, kwd_len, name)  \
	((kwd_len) == COMPILER_STRLEN(name) && \
	 memcmp((kwd_str), name, sizeof(name) - sizeof(char)) == 0)



/* Set to  true if  the `,'-operator  should be  interpreted as  it is  in
 * regular C, meaning that it is used to simply select the second operand.
 *
 * When set to `false' (which is the default) then the `,'-operator is used
 * to implement a  cast-to-array behavior, where  the LHS-operator is  then
 * expected to be a pointer:
 * >> &foo, 12
 *
 * Evaluated as:
 * >> *(typeof(foo)(*)[12])&foo
 *
 * Not that while parsing an expression within parenthesis,
 * this option is always set to `true':
 * >> (&foo, 12)
 * Always parsed as:
 * >> 12
 */
PUBLIC bool ceval_comma_is_select2nd = false;


PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_pushparse_inner)(struct cparser *__restrict self) {
	dbx_errno_t result;
	bool old_ceval_comma_is_select2nd;
	old_ceval_comma_is_select2nd = ceval_comma_is_select2nd;
	ceval_comma_is_select2nd     = true;
	result                       = cexpr_pushparse(self);
	ceval_comma_is_select2nd     = old_ceval_comma_is_select2nd;
	return result;
}


PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_unary_prefix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_unary_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_unary)(struct cparser *__restrict self);
#define parse_unary_suffix_check(tok)    \
	((tok) == '[' || (tok) == '(' ||     \
	 (tok) == '.' || (tok) == '@' ||     \
	 (tok) == CTOKEN_TOK_MINUS_RANGLE || \
	 (tok) == CTOKEN_TOK_PLUS_PLUS ||    \
	 (tok) == CTOKEN_TOK_MINUS_MINUS)
#define parse_unary_suffix_CASE   \
	case '[':                     \
	case '(':                     \
	case '.':                     \
	case '@':                     \
	case CTOKEN_TOK_MINUS_RANGLE: \
	case CTOKEN_TOK_PLUS_PLUS:    \
	case CTOKEN_TOK_MINUS_MINUS

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_prod_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_prod)(struct cparser *__restrict self);
#define parse_prod_suffix_check(tok) \
	((tok) == '*' || (tok) == '/' || (tok) == '%')
#define parse_prod_suffix_CASE \
	case '*':                  \
	case '/':                  \
	case '%'

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_sum_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_sum)(struct cparser *__restrict self);
#define parse_sum_suffix_check(tok) \
	((tok) == '+' || (tok) == '-')
#define parse_sum_suffix_CASE \
	case '+':                 \
	case '-'

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_shift_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_shift)(struct cparser *__restrict self);
#define parse_shift_suffix_check(tok)     \
	((tok) == CTOKEN_TOK_LANGLE_LANGLE || \
	 (tok) == CTOKEN_TOK_RANGLE_RANGLE)
#define parse_shift_suffix_CASE    \
	case CTOKEN_TOK_LANGLE_LANGLE: \
	case CTOKEN_TOK_RANGLE_RANGLE

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_cmp_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_cmp)(struct cparser *__restrict self);
#define parse_cmp_suffix_check(tok)       \
	((tok) == '<' || (tok) == '>' ||      \
	 (tok) == CTOKEN_TOK_LANGLE_EQUALS || \
	 (tok) == CTOKEN_TOK_RANGLE_EQUALS)
#define parse_cmp_suffix_CASE      \
	case '<':                      \
	case '>':                      \
	case CTOKEN_TOK_LANGLE_EQUALS: \
	case CTOKEN_TOK_RANGLE_EQUALS

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_cmpeq_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_cmpeq)(struct cparser *__restrict self);
#define parse_cmpeq_suffix_check(tok)     \
	((tok) == CTOKEN_TOK_XCLAIM_EQUALS || \
	 (tok) == CTOKEN_TOK_EQUALS_EQUALS)
#define parse_cmpeq_suffix_CASE    \
	case CTOKEN_TOK_XCLAIM_EQUALS: \
	case CTOKEN_TOK_EQUALS_EQUALS

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_bitand_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_bitand)(struct cparser *__restrict self);
#define parse_bitand_suffix_check(tok) ((tok) == '&')
#define parse_bitand_suffix_CASE       case '&'

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_bitxor_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_bitxor)(struct cparser *__restrict self);
#define parse_bitxor_suffix_check(tok) ((tok) == '^')
#define parse_bitxor_suffix_CASE       case '^'

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_bitor_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_bitor)(struct cparser *__restrict self);
#define parse_bitor_suffix_check(tok) ((tok) == '|')
#define parse_bitor_suffix_CASE       case '|'

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_land_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_land)(struct cparser *__restrict self);
#define parse_land_suffix_check(tok) ((tok) == CTOKEN_TOK_AND_AND)
#define parse_land_suffix_CASE       case CTOKEN_TOK_AND_AND

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_lor_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_lor)(struct cparser *__restrict self);
#define parse_lor_suffix_check(tok) ((tok) == CTOKEN_TOK_PIPE_PIPE)
#define parse_lor_suffix_CASE       case CTOKEN_TOK_PIPE_PIPE

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_cond_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_cond)(struct cparser *__restrict self);
#define parse_cond_suffix_check(tok) ((tok) == '?')
#define parse_cond_suffix_CASE       case '?'

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_assign_suffix)(struct cparser *__restrict self);
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t NOTHROW(FCALL parse_assign)(struct cparser *__restrict self);
#define parse_nocomma parse_assign
#define parse_assign_suffix_check(tok)           \
	((tok) == '=' ||                             \
	 (tok) == CTOKEN_TOK_PLUS_EQUALS ||          \
	 (tok) == CTOKEN_TOK_MINUS_EQUALS ||         \
	 (tok) == CTOKEN_TOK_STAR_EQUALS ||          \
	 (tok) == CTOKEN_TOK_SLASH_EQUALS ||         \
	 (tok) == CTOKEN_TOK_PERCENT_EQUALS ||       \
	 (tok) == CTOKEN_TOK_PIPE_EQUALS ||          \
	 (tok) == CTOKEN_TOK_AND_EQUALS ||           \
	 (tok) == CTOKEN_TOK_LANGLE_LANGLE_EQUALS || \
	 (tok) == CTOKEN_TOK_RANGLE_RANGLE_EQUALS || \
	 (tok) == CTOKEN_TOK_ROOF_EQUALS)
#define parse_assign_suffix_CASE          \
	case '=':                             \
	case CTOKEN_TOK_PLUS_EQUALS:          \
	case CTOKEN_TOK_MINUS_EQUALS:         \
	case CTOKEN_TOK_STAR_EQUALS:          \
	case CTOKEN_TOK_SLASH_EQUALS:         \
	case CTOKEN_TOK_PERCENT_EQUALS:       \
	case CTOKEN_TOK_PIPE_EQUALS:          \
	case CTOKEN_TOK_AND_EQUALS:           \
	case CTOKEN_TOK_LANGLE_LANGLE_EQUALS: \
	case CTOKEN_TOK_RANGLE_RANGLE_EQUALS: \
	case CTOKEN_TOK_ROOF_EQUALS



PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cparser_require)(struct cparser *__restrict self,
                               unsigned int expected_tok) {
	if likely(self->c_tok == expected_tok)
		return DBX_EOK;
	if (self->c_autocom && self->c_tokend == self->c_end) {
		/* Suggest missing characters. */
		char name[1];
		name[0] = (char)expected_tok;
		cparser_autocomplete(self, name, 1);
	}
	return DBX_ESYNTAX; /* Unexpected token */
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cparser_skip)(struct cparser *__restrict self,
                            unsigned int expected_tok) {
	if likely(self->c_tok == expected_tok) {
		yield();
		return DBX_EOK;
	}
	if (self->c_autocom && self->c_tokend == self->c_end) {
		/* Suggest missing characters. */
		char name[1];
		name[0] = (char)expected_tok;
		cparser_autocomplete(self, name, 1);
	}
	return DBX_ESYNTAX; /* Unexpected token */
}

PRIVATE WUNUSED NONNULL((1)) struct ctype *
NOTHROW(FCALL make_unsigned)(struct ctype *__restrict self) {
	struct ctype *result;
	if (self == &ctype_signed_char) {
		result = &ctype_unsigned_char;
	} else if (self == &ctype_short) {
		result = &ctype_unsigned_short;
	} else if (self == &ctype_int) {
		result = &ctype_unsigned_int;
	} else if (self == &ctype_long) {
		result = &ctype_unsigned_long;
	} else if (self == &ctype_long_long) {
		result = &ctype_unsigned_long_long;
	} else {
		result = NULL;
	}
	return result;
}

PRIVATE WUNUSED NONNULL((1)) struct ctype *
NOTHROW(FCALL make_longer)(struct ctype *__restrict self) {
	struct ctype *result;
	if (self == &ctype_int) {
		result = &ctype_long;
	} else if (self == &ctype_unsigned_int) {
		result = &ctype_unsigned_long;
	} else if (self == &ctype_long) {
		result = &ctype_long_long;
	} else if (self == &ctype_unsigned_long) {
		result = &ctype_unsigned_long_long;
	} else {
		result = NULL;
	}
	return result;
}

PRIVATE WUNUSED NONNULL((1, 2)) struct ctype *
NOTHROW(FCALL parse_ctype_from_suffix)(char const *suffix,
                                       char const *suffix_end) {
	struct ctype *result;
	result = &ctype_int;
again:
	if (suffix < suffix_end) {
		char32_t ch;
		ch = unicode_readutf8_n(&suffix, suffix_end);
		if (ch == 'u' || ch == 'U') {
			result = make_unsigned(result);
			if unlikely(!result)
				goto syn; /* Already unsigned... */
			goto again;
		}
		if (ch == 'l' || ch == 'L') {
			result = make_longer(result);
			if unlikely(!result)
				goto syn;
			goto again;
		}
		if (ch == 'i' || ch == 'I') {
			/* Fixed-length / pointer-sized. */
			size_t wanted_length;
again_fixed_length:
			ch = unicode_readutf8_n(&suffix, suffix_end);
			if (ch == 'u' || ch == 'U') {
				result = make_unsigned(result);
				if unlikely(!result)
					goto syn; /* Already unsigned... */
				goto again_fixed_length;
			}
			if (ch == '8') {
				wanted_length = 1;
			} else if (ch == '1') {
				ch = unicode_readutf8_n(&suffix, suffix_end);
				if unlikely(ch != '6')
					goto syn;
				wanted_length = 2;
			} else if (ch == '3') {
				ch = unicode_readutf8_n(&suffix, suffix_end);
				if unlikely(ch != '2')
					goto syn;
				wanted_length = 4;
			} else if (ch == '6') {
				ch = unicode_readutf8_n(&suffix, suffix_end);
				if unlikely(ch != '4')
					goto syn;
				wanted_length = 8;
			} else {
				wanted_length = dbg_current_sizeof_pointer();
			}
			if unlikely(result != &ctype_int &&
			            result != &ctype_unsigned_int)
				goto syn; /* Other non-sign-related modifiers already used. */
			if (wanted_length == 1) {
				result = result == &ctype_unsigned_int ? &ctype_u8 : &ctype_s8;
			} else if (wanted_length == 2) {
				result = result == &ctype_unsigned_int ? &ctype_u16 : &ctype_s16;
			} else if (wanted_length == 4) {
				result = result == &ctype_unsigned_int ? &ctype_u32 : &ctype_s32;
			} else {
				result = result == &ctype_unsigned_int ? &ctype_u64 : &ctype_s64;
			}
			goto again;
		}
	}
	return result;
syn:
	return NULL;
}

PRIVATE WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(FCALL unicode_readutf8_unescape)(char const **__restrict ptext,
                                         char const *end,
                                         char32_t *__restrict presult) {
	char32_t result;
	result = unicode_readutf8_n(ptext, end);
	if (result == '\\') {
		result = unicode_readutf8_n(ptext, end);
		switch (result) {

		case 'a': result = 7; break;
		case 'b': result = 8; break;
		case 't': result = 9; break;
		case 'n': result = 10; break;
		case 'v': result = 11; break;
		case 'f': result = 12; break;
		case 'r': result = 13; break;
		case 'e': result = 27; break;
		case '\\':
		case '\'':
		case '\"':
			break;

		case 'x': case 'X':
		case 'u': case 'U': {
			char32_t digit;
			char const *iter = *ptext;
			size_t n = (size_t)-1;
			if (result == 'u')
				n = 4;
			else if (result == 'U') {
				n = 8;
			}
			result = 0;
			if unlikely(iter >= end)
				goto err;
			do {
				*ptext = iter;
				digit  = unicode_readutf8_n(&iter, end);
				if (digit >= '0' && digit <= '9') {
					digit -= '0';
				} else if (digit >= 'a' && digit <= 'f') {
					digit -= 'a';
					digit += 10;
				} else if (digit >= 'A' && digit <= 'F') {
					digit -= 'A';
					digit += 10;
				} else {
					break;
				}
				result *= 10;
				result += digit;
				if (!--n)
					break;
			} while (iter < end);
		}	break;

		case '0' ... '7': {
			char32_t digit;
			char const *iter = *ptext;
			result -= '0';
			while (iter < end) {
				*ptext = iter;
				digit  = unicode_readutf8_n(&iter, end);
				if (digit >= '0' && digit <= '7') {
					digit -= '0';
				} else {
					break;
				}
				result *= 8;
				result += digit;
			}
		}	break;

		default:
			goto err;
		}
	}
	*presult = result;
	return true;
err:
	return false;
}

/* Parse optional parenthesis, followed by either a type, or regular expression.
 * Afterwards,   return   the   type   of   that   expression   in   `*presult'. */
PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL parse_typeof)(struct cparser *__restrict self,
                            struct ctyperef *__restrict presult) {
	dbx_errno_t result;
	bool has_paren;
	has_paren = self->c_tok == '(';
	if (has_paren)
		yield();
	/* Try to parse a type-expression */
	result = ctype_eval(self, presult, NULL, NULL);
	if (result != DBX_EOK) {
		bool old_cexpr_typeonly;
		if (result != DBX_ENOENT)
			goto done;
		old_cexpr_typeonly = cexpr_typeonly;
		cexpr_typeonly     = true;
		result = cexpr_pushparse_inner(self);
		cexpr_typeonly = old_cexpr_typeonly;
		if unlikely(result != DBX_EOK)
			goto done;
		/* Use the type of the stack-top expression. */
		ctyperef_initcopy(presult, &cexpr_stacktop.cv_type);
		result = cexpr_pop();
		if unlikely(result != DBX_EOK)
			goto err_result;
	}
	if (has_paren) {
		result = cparser_skip(self, ')');
		if unlikely(result != DBX_EOK)
			goto err_result;
	}
done:
	return result;
err_result:
	ctyperef_fini(presult);
	return result;
}

struct autocomplete_symbols_data {
	struct cmodsyminfo info;
	struct cparser    *self;
	char const        *name;
	size_t             namelen;
};

PRIVATE WUNUSED NONNULL((1)) ssize_t
NOTHROW(FCALL autocomplete_symbols_callback)(struct cmodsyminfo *__restrict info,
                                             bool UNUSED(info_loaded)) {
	struct autocomplete_symbols_data *cookie;
	char const *symbol_name;
	size_t symbol_namelen;
	cookie         = container_of(info, struct autocomplete_symbols_data, info);
	symbol_name    = cmodsyminfo_name(info);
	symbol_namelen = strlen(symbol_name);
	cparser_autocomplete(cookie->self,
	                     symbol_name + cookie->namelen,
	                     symbol_namelen - cookie->namelen);
	return 1;
}


PRIVATE NONNULL((1)) void
NOTHROW(FCALL autocomplete_symbols)(struct cparser *__restrict self,
                                    char const *__restrict name,
                                    size_t namelen, uintptr_t ns) {
	struct autocomplete_symbols_data data;
	unsigned int scope;
	data.self    = self;
	data.name    = name;
	data.namelen = namelen;
	scope = CMOD_SYMENUM_SCOPE_FNOGLOBAL | CMOD_SYMENUM_SCOPE_FNOFOREIGN;
	for (;;) {
		ssize_t count;
		count = cmod_symenum_local(&data.info,
		                           &autocomplete_symbols_callback,
		                           name, namelen, ns, scope);
		if (count != 0)
			break;
		/* Change the scope to enumerate other things if we've failed to find anything. */
		if (scope == (CMOD_SYMENUM_SCOPE_FNOGLOBAL | CMOD_SYMENUM_SCOPE_FNOFOREIGN))
			scope = CMOD_SYMENUM_SCOPE_FNOLOCAL | CMOD_SYMENUM_SCOPE_FNOFOREIGN;
		else if (scope == (CMOD_SYMENUM_SCOPE_FNOLOCAL | CMOD_SYMENUM_SCOPE_FNOFOREIGN))
			scope = CMOD_SYMENUM_SCOPE_FNOLOCAL | CMOD_SYMENUM_SCOPE_FNOGLOBAL;
		else {
			break;
		}
	}
}


PRIVATE char const misc_expr_keywords[][16] = {
	"sizeof", "NULL", "nullptr", "true", "false",
	"__identifier", "offsetof", "offsetafter",
	"container_of"
};

PRIVATE NONNULL((1)) void
NOTHROW(FCALL autocomplete_nontype_symbols)(struct cparser *__restrict self,
                                            char const *__restrict name,
                                            size_t namelen) {
	if (namelen < (COMPILER_LENOF(misc_expr_keywords[0]) - 1)) {
		unsigned int i;
		for (i = 0; i < COMPILER_LENOF(misc_expr_keywords); ++i) {
			if (memcmp(misc_expr_keywords[i], name, namelen) == 0 &&
			    misc_expr_keywords[i][namelen] != '\0') {
				char const *cname_str = misc_expr_keywords[i];
				size_t cname_len = strlen(cname_str);
				cparser_autocomplete(self,
				                     cname_str + namelen,
				                     cname_len - namelen);
			}
		}
	}
	autocomplete_symbols(self, name, namelen, CMODSYM_DIP_NS_NONTYPE);
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL autocomplete_register_name)(struct cparser *__restrict self,
                                          char const *__restrict name,
                                          size_t namelen) {
	/* TODO: auto-complete register names that start with the given `name...+=namelen' */
	(void)self;
	(void)name;
	(void)namelen;
}


PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_unary_prefix)(struct cparser *__restrict self) {
	dbx_errno_t result;
	switch (self->c_tok) {

	case '(': {
		/* Check for a C-style cast expression. */
		struct ctyperef cast_type;
		char const *afterparen;
		yield();
		afterparen = self->c_tokstart;
		result = ctype_eval(self, &cast_type, NULL, NULL);
		if (result == DBX_EOK) {
			if (self->c_tok != ')' && self->c_tok != CTOKEN_TOK_EOF) {
				/* Look ahead if this really is a cast expression, because
				 * if it isn't, then we mustn't try to parse a type  here.
				 *
				 * Consider this:
				 *       "(stat + 5)"
				 *
				 * Since `struct stat' is a thing, we'd parse the type, only
				 * to later notice that `stat', the function was supposed to
				 * be used.
				 *
				 * We handle this by simply checking if the type-expression
				 * is followed by a ')'. - If it isn't, then we simply  re-
				 * parse the (thought-to-be)  type-expression as a  regular
				 * expression. */
				cparser_yieldat(self, afterparen);
				ctyperef_fini(&cast_type);
				goto doparen_expr;
			}
			/* Cast-expression */
			result = cparser_skip(self, ')');
			if likely(result == DBX_EOK) {
				/* Parse the expression to-be casted. */
				result = parse_unary(self);
				if likely(result == DBX_EOK) {
					/* Do the actual cast. */
					result = cexpr_cast(&cast_type);
				}
			}
			ctyperef_fini(&cast_type);
			goto done;
		}
		/* Handle the case where the wrapped expression isn't a type-expression */
		if unlikely(result != DBX_ENOENT)
			goto done;
doparen_expr:
		/* Simple parenthesis. */
		result = cexpr_pushparse_inner(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cparser_skip(self, ')');
	}	break;

	case CTOKEN_TOK_INT: {
		struct ctype *used_type;
		union {
			u8        _u8;
			u16       _u16;
			u32       _u32;
			u64       _u64;
			uintmax_t _umax;
		} value;
		char *endp;
		value._umax = strtoumax(self->c_tokstart, &endp, 0);
		if unlikely(endp > self->c_tokend)
			goto syn;
		used_type = parse_ctype_from_suffix(endp, self->c_tokend);
		if unlikely(!used_type)
			goto syn;
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
		switch (CTYPE_KIND_CLASSOF(used_type->ct_kind)) {
		case 1: value._u8 = value._umax; break;
		case 2: value._u16 = value._umax; break;
		case 4: value._u32 = value._umax; break;
		case 8: value._u64 = value._umax; break;
		default: break;
		}
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		result = cexpr_pushdata_simple(used_type, &value);
		yield();
	}	break;

	case CTOKEN_TOK_FLOAT: {
		struct ctype *used_type;
		char *endp;
		__IEEE854_LONG_DOUBLE_TYPE__ value;
		/* FIXME: Because of how libc/local functions are linked (using c++ `inline'),
		 *        our  attempt at using a custom version of format_scanf() doesn't end
		 *        up working, since the c++ standard requires that functions  declared
		 *        as  inline   share   the   same  address   throughout   a   program.
		 *        As  such, relocations are  generated that will  end up bypassing our
		 *        custom format_scanf() in favor of  the one exported from the  kernel
		 *        core, which doesn't include floating-point support....
		 * I feel like there's no  point in trying to make  this work. - That would  end
		 * up  being _way_ too hacky, so I feel  like the best solution would be to just
		 * copy the  relevant code  from the  implementation of  format_scanf() that  is
		 * used for parsing floating-point numbers, paste it here, and call it directly.
		 */
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
		value = strtold(self->c_tokstart, &endp);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
		value = strtod(self->c_tokstart, &endp);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
		value = strtof(self->c_tokstart, &endp);
#else /* ... */
		value = (__IEEE854_LONG_DOUBLE_TYPE__)strtold(self->c_tokstart, &endp);
#endif /* !... */
		used_type = &ctype_ieee754_double;
		if (endp != self->c_tokend) {
			char32_t ch;
			if unlikely(endp > self->c_tokend)
				goto syn;
			ch = unicode_readutf8_n(&endp, self->c_tokend);
			if unlikely(endp != self->c_tokend)
				goto syn;
			if (ch == 'f' || ch == 'F') {
				used_type = &ctype_ieee754_float;
#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
			} else if (ch == 'l' || ch == 'L') {
				used_type = &ctype_ieee854_long_double;
#endif /* CTYPE_KIND_IEEE854_LONG_DOUBLE */
			} else {
				goto syn;
			}
		}
		if (used_type == &ctype_ieee754_double) {
			__IEEE754_DOUBLE_TYPE__ used_value;
			used_value = (__IEEE754_DOUBLE_TYPE__)value;
			result     = cexpr_pushdata_simple(used_type, &used_value);
		} else if (used_type == &ctype_ieee754_float) {
			__IEEE754_FLOAT_TYPE__ used_value;
			used_value = (__IEEE754_FLOAT_TYPE__)value;
			result     = cexpr_pushdata_simple(used_type, &used_value);
		} else {
			result = cexpr_pushdata_simple(used_type, &value);
		}
		yield();
	}	break;

	case CTOKEN_TOK_CHAR: {
		char32_t value = 0;
		shift_t shift  = 0;
		char const *reader, *end;
		reader = self->c_tokstart;
		end    = self->c_tokend;
		unicode_readutf8_rev_n(&end, reader); /* Trailing '\'' */
		unicode_readutf8_n(&reader, end);     /* Leading '\'' */
		for (;;) {
			char32_t temp;
			if (!unicode_readutf8_unescape(&reader, end, &temp))
				goto syn;
			value |= temp << shift;
			if (reader >= end)
				break;
			shift += NBBY;
		}
		/* Push as an integer. */
		result = cexpr_pushint_simple(&ctype_int, value);
		yield();
	}	break;

	case CTOKEN_TOK_PLUS_PLUS:
	case CTOKEN_TOK_MINUS_MINUS: {
		struct ctype *typ;
		char op = '+';
		if (self->c_tok == CTOKEN_TOK_MINUS_MINUS)
			op = '-';
		yield();
		result = parse_unary(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_dup();
		if unlikely(result != DBX_EOK)
			goto done;
		typ = cexpr_stacktop.cv_type.ct_typ;
		if (!CTYPE_KIND_ISINT(typ->ct_kind))
			typ = &ctype_ptrdiff_t;
		result = cexpr_pushint_simple(typ, 1);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2(op);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_store();
	}	break;

	case '&': case '*':
	case '+': case '-':
	case '~': case '!': {
		/* Unary operators. */
		char op = (char)self->c_tok;
		yield();
		result = parse_unary(self);
		if unlikely(result != DBX_EOK)
			goto done;
		if (op == '&')
			result = cexpr_ref();
		else if (op == '*')
			result = cexpr_deref();
		else {
			result = cexpr_op1(op);
		}
	}	break;

	case '%':
	case '$': {
		/* Register expression. */
		yield();
		if unlikely(self->c_tok != CTOKEN_TOK_KEYWORD) {
			if (self->c_autocom && self->c_tok == CTOKEN_TOK_EOF)
				autocomplete_register_name(self, NULL, 0);
			goto syn;
		}
		result = cexpr_pushregister(self->c_tokstart,
		                            cparser_toklen(self));
		if unlikely(result != DBX_EOK) {
			if (result == DBX_ENOENT && self->c_autocom && self->c_tokend == self->c_end)
				autocomplete_register_name(self, self->c_tokstart, cparser_toklen(self));
			goto done;
		}
		yield();
	}	break;

	case CTOKEN_TOK_KEYWORD: {
		/* Variable lookup. */
		char const *kwd_str;
		size_t kwd_len;
		kwd_str = self->c_tokstart;
		kwd_len = cparser_toklen(self);
		yield();
		if (KWD_CHECK(kwd_str, kwd_len, "sizeof")) {
			struct ctyperef ct;
			size_t sizeval;
			result = parse_typeof(self, &ct);
			if unlikely(result != DBX_EOK)
				goto done;
			sizeval = ctype_sizeof(ct.ct_typ);
			ctyperef_fini(&ct);
			result = cexpr_pushint_simple(&ctype_size_t, sizeval);
		} else if (KWD_CHECK(kwd_str, kwd_len, "NULL") ||
		           KWD_CHECK(kwd_str, kwd_len, "nullptr") ||
		           KWD_CHECK(kwd_str, kwd_len, "__NULLPTR")) {
			result = cexpr_pushint_simple(&ctype_void_ptr, 0);
		} else if (KWD_CHECK(kwd_str, kwd_len, "true")) {
			result = cexpr_pushint_simple(&ctype_bool, 1);
		} else if (KWD_CHECK(kwd_str, kwd_len, "false")) {
			result = cexpr_pushint_simple(&ctype_bool, 0);
		} else if (KWD_CHECK(kwd_str, kwd_len, "offsetof") ||
		           KWD_CHECK(kwd_str, kwd_len, "offsetafter") ||
		           KWD_CHECK(kwd_str, kwd_len, "__builtin_offsetof") ||
		           KWD_CHECK(kwd_str, kwd_len, "__COMPILER_OFFSETAFTER")) {
			/* For simplicity, and correctness, literally implement offsetof()
			 * as its generic macro implementation:
			 * >> #define offsetof(T, m) (size_t)&((T *)0)->m */
			bool want_after;
			struct ctyperef t;
			REF struct ctype *t_ptr;
			want_after = (kwd_len == COMPILER_STRLEN("offsetafter") ||
			              kwd_len == COMPILER_STRLEN("__COMPILER_OFFSETAFTER"));
			result     = cparser_skip(self, '(');
			if unlikely(result != DBX_EOK)
				goto done;
			result = ctype_eval(self, &t, NULL, NULL);
			if unlikely(result != DBX_EOK)
				goto done;
			t_ptr = ctype_ptr(&t, dbg_current_sizeof_pointer());
			ctyperef_fini(&t);
			if unlikely(!t_ptr)
				goto err_nomem;
			result = cexpr_pushint_simple(t_ptr, 0);
			decref(t_ptr);
			if unlikely(result != DBX_EOK)
				goto done;
			/* NOTE: Also  accept '.' and '::' instead of the ',' before the
			 * member expression, but don't tell auto-completion about this. */
			if (self->c_tok != '.' && self->c_tok != CTOKEN_TOK_COLON_COLON) {
				result = cparser_require(self, ',');
				if unlikely(result != DBX_EOK)
					goto done;
			}
			/* Simply parse any valid integer suffix expression,
			 * but  act as  though the  ',' was  actually a '->' */
			self->c_tok = CTOKEN_TOK_MINUS_RANGLE;
			result      = parse_unary_suffix(self);
			if unlikely(result != DBX_EOK)
				goto done;
			result = cexpr_ref();
			if unlikely(result != DBX_EOK)
				goto done;
			if (want_after) {
				/* Just add +1 (which will be multiplied by `ctype_sizeof(<TOP_TYPE_DEREF>)') */
				result = cexpr_pushint_simple(&ctype_uintptr_t, 1);
				if unlikely(result != DBX_EOK)
					goto done;
				result = cexpr_op2('+');
				if unlikely(result != DBX_EOK)
					goto done;
			}
			result = cexpr_cast_simple(&ctype_size_t);
			if unlikely(result != DBX_EOK)
				goto done;
			result = cparser_skip(self, ')');
		} else if (KWD_CHECK(kwd_str, kwd_len, "container_of") ||
		           KWD_CHECK(kwd_str, kwd_len, "__COMPILER_CONTAINER_OF")) {
			/* For simplicity, and correctness, literally implement container_of()
			 * as its generic macro implementation:
			 * >> #define container_of(p, T, m) (T *)((uintptr_t)(p) - offsetof(T, m))
			 * or fully expanded:
			 * >> #define container_of(p, T, m) (T *)((uintptr_t)(p) - (size_t)&((T *)0)->m) */
			struct ctyperef t;
			REF struct ctype *t_ptr;
			result = cparser_skip(self, '(');
			if unlikely(result != DBX_EOK)
				goto done;
			result = parse_nocomma(self);
			if unlikely(result != DBX_EOK)
				goto done;
			result = cexpr_cast_simple(&ctype_uintptr_t);
			if unlikely(result != DBX_EOK)
				goto done;
			result = cparser_skip(self, ',');
			if unlikely(result != DBX_EOK)
				goto done;
			result = ctype_eval(self, &t, NULL, NULL);
			if unlikely(result != DBX_EOK)
				goto done;
			t_ptr = ctype_ptr(&t, dbg_current_sizeof_pointer());
			ctyperef_fini(&t);
			if unlikely(!t_ptr)
				goto err_nomem;
			result = cexpr_pushint_simple(t_ptr, 0);
			if unlikely(result != DBX_EOK) {
done_container_of_t_ptr:
				decref(t_ptr);
				goto done;
			}
			/* NOTE: Also  accept '.' and '::' instead of the ',' before the
			 * member expression, but don't tell auto-completion about this. */
			if (self->c_tok != '.' && self->c_tok != CTOKEN_TOK_COLON_COLON) {
				result = cparser_require(self, ',');
				if unlikely(result != DBX_EOK)
					goto done_container_of_t_ptr;
			}
			/* Simply parse any valid integer suffix expression,
			 * but  act as  though the  ',' was  actually a '->' */
			self->c_tok = CTOKEN_TOK_MINUS_RANGLE;
			result      = parse_unary_suffix(self);
			if unlikely(result != DBX_EOK)
				goto done_container_of_t_ptr;
			result = cexpr_ref();
			if unlikely(result != DBX_EOK)
				goto done_container_of_t_ptr;
			result = cexpr_cast_simple(&ctype_size_t);
			if unlikely(result != DBX_EOK)
				goto done_container_of_t_ptr;
			/* Add together p + offset */
			result = cexpr_op2('+');
			if unlikely(result != DBX_EOK)
				goto done_container_of_t_ptr;
			/* Cast the result back to `t_ptr' */
			result = cexpr_cast_simple(t_ptr);
			decref(t_ptr);
			if unlikely(result != DBX_EOK)
				goto done;
			result = cparser_skip(self, ')');
		} else if (KWD_CHECK(kwd_str, kwd_len, "__identifier")) {
			bool has_paren;
			has_paren = self->c_tok == '(';
			if (has_paren)
				yield();
			if (self->c_tok != CTOKEN_TOK_KEYWORD)
				goto syn;
			/* Pure symbol lookup. */
			kwd_str = self->c_tokstart;
			kwd_len = cparser_toklen(self);
			/* NOTE: Don't enable automatic symbol offsets within __identifier()! */
			result = cexpr_pushsymbol_byname(kwd_str, kwd_len, false);
			if (result == DBX_ENOENT && self->c_autocom && self->c_tokend == self->c_end)
				autocomplete_symbols(self, kwd_str, kwd_len, CMODSYM_DIP_NS_NONTYPE);
			yield();
			if (has_paren) {
				if unlikely(result != DBX_EOK)
					goto done;
				result = cparser_skip(self, ')');
			}
		} else {
			/* TODO: if (self->c_tok == '*') {
			 *           ...
			 *       }
			 * Only when the '*' is the last token, or is followed by one of ) ] } , ; :
			 * When used,  take  all  variables  as they  would  be  enumerated  by  the
			 * below `autocomplete_nontype_symbols' and push  them on to the  expression
			 * stack. Then,  pack all  of them  together within  a pseudo-struct  object
			 * that  contains  all of  them alongside  their  values, allowing  the user
			 * to quickly list  the values of  a collection of  variables, based on  the
			 * common trait of  all of  the variables  having the  same, common  prefix:
			 * >> eval thiscpu_x86_apic_emutsc_*
			 *
			 * This  would then  print the  values of  all global variables
			 * `thiscpu_x86_apic_emutsc_*', which would look somthing like:
			 * >> {
			 * >>   thiscpu_x86_apic_emutsc_tscbase: 0x14afd85306,
			 * >>   thiscpu_x86_apic_emutsc_prev_current: 0x2cce63f6,
			 * >>   thiscpu_x86_apic_emutsc_mindistance: 0x9ec13,
			 * >>   thiscpu_x86_apic_emutsc_initial_shifted: 0x7fffffff80,
			 * >>   thiscpu_x86_apic_emutsc_initial: 0xffffffff,
			 * >>   thiscpu_x86_apic_emutsc_early_interrupt: false,
			 * >>   thiscpu_x86_apic_emutsc_divide: 7,
			 * >>   thiscpu_x86_apic_emutsc_deadline: 0xffffffffffffffff,
			 * >>   thiscpu_x86_apic_emutsc_cmpxch_delay: 200,
			 * >> }
			 *
			 * The list of variables used  should match those enumerated by  auto-completion
			 * exactly, so it should be obvious to the user which variables would be printed
			 * by using this trick!
			 */


			/* NOTE: Only add  automatic  symbol  offsets  when  this  symbol  isn't
			 *       already being used within an explicit symbol-offset expression.
			 * As such:
			 * >> this_cred          (evaluate to this_cred@dbg_current)
			 * >> this_cred@caller   (evaluate to this_cred@caller) */
			result = cexpr_pushsymbol_byname(kwd_str, kwd_len, self->c_tok != '@');
			if (result == DBX_ENOENT) {
				if (kwd_len && kwd_str[0] == '$') {
					/* This might just be a register name... */
					++kwd_str, --kwd_len;
					result = cexpr_pushregister(kwd_str, kwd_len);
					if (result == DBX_ENOENT && self->c_autocom && self->c_tokend == self->c_end)
						autocomplete_register_name(self, kwd_str, kwd_len);
				} else if (self->c_autocom && (kwd_str + kwd_len) == self->c_end) {
					autocomplete_nontype_symbols(self, kwd_str, kwd_len);
				}
			}
		}
	}	break;

		/* TODO: CTOKEN_TOK_STRING  can  be  implemented  by  pushing
		 *       the associated string-value using `CVALUE_KIND_DATA'
		 *       or `CVALUE_KIND_IDATA', and using `char const[N]' as
		 *       the type. */

	default:
		/* Unexpected token... */
syn:
		result = DBX_ESYNTAX;
	}
done:
	return result;
err_nomem:
	result = DBX_ENOMEM;
	goto done;
}


struct autocomplete_struct_data {
	struct cparser *self;
	char const     *name;
	size_t          namelen;
};

PRIVATE NONNULL((2, 3, 4, 5)) ssize_t
NOTHROW(KCALL autocomplete_struct_fields_callback)(void *arg,
                                                   di_debuginfo_member_t const *__restrict member,
                                                   di_debuginfo_cu_parser_t const *__restrict UNUSED(parser),
                                                   struct cmodule *__restrict UNUSED(mod),
                                                   struct cmodunit *__restrict UNUSED(cu)) {
	struct autocomplete_struct_data *cookie;
	size_t member_namelen;
	cookie         = (struct autocomplete_struct_data *)arg;
	member_namelen = strlen(member->m_name);
	if (member_namelen <= cookie->namelen)
		return 0;
	if (memcmp(member->m_name, cookie->name,
	           cookie->namelen * sizeof(char)) != 0)
		return 0;
	cparser_autocomplete(cookie->self,
	                     member->m_name + cookie->namelen,
	                     member_namelen - cookie->namelen);
	return 0;
}

PRIVATE dbx_errno_t
NOTHROW(KCALL autocomplete_struct_fields)(struct cparser *self,
                                          char const *name,
                                          size_t namelen) {
	struct autocomplete_struct_data data;
	struct ctype *ct;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	ct = cexpr_stacktop.cv_type.ct_typ;
	if unlikely(!CTYPE_KIND_ISSTRUCT(ct->ct_kind))
		return DBX_ESYNTAX;
	data.self    = self;
	data.name    = name;
	data.namelen = namelen;
	ctype_struct_enumfields(ct, &autocomplete_struct_fields_callback, &data);
	return DBX_ENOENT;
}


PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_unary_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case '@': {
		struct ctyperef lhs_ptr_type;
		/* >> foo@bar
		 * Same   as:
		 * >> *(typeof(foo) *)((uintptr_t)&foo + (uintptr_t)bar)
		 *
		 * Intended for ATTR_PERxxx variables within the kernel:
		 * >> this_connections@caller
		 * Where `caller' is presumably a local variable `struct task *caller'.
		 * This  will  then resolve  to  print information  about  the pet-task
		 * variable `this_connections', as viewed by `caller'
		 *
		 * TODO: The 2 operands  should be  interchangeable, so-long  as
		 *       at most one of them is a pointer. When both, or neither
		 *       is a pointer, only then should this operator result  in
		 *       a DBX_ESYNTAX error. */
		if (CTYPE_KIND_ISARRAY(cexpr_stacktop.cv_type.ct_typ->ct_kind)) {
			result = cexpr_promote();
		} else {
			result = cexpr_ref();
		}
		if unlikely(result != DBX_EOK)
			goto done;
		ctyperef_initcopy(&lhs_ptr_type, &cexpr_stacktop.cv_type);
		result = cexpr_cast_simple(&ctype_uintptr_t);
		if unlikely(result != DBX_EOK) {
err_lhs_ptr_type:
			ctyperef_fini(&lhs_ptr_type);
			goto done;
		}
		yield();
		result = parse_unary(self);            /* (uintptr_t)&foo, bar */
		if unlikely(result != DBX_EOK)
			goto err_lhs_ptr_type;
		result = cexpr_cast_simple(&ctype_uintptr_t); /* (uintptr_t)&foo, (uintptr_t)bar */
		if unlikely(result != DBX_EOK)
			goto err_lhs_ptr_type;
		result = cexpr_op2('+');               /* (uintptr_t)&foo + (uintptr_t)bar */
		if unlikely(result != DBX_EOK)
			goto err_lhs_ptr_type;
		result = cexpr_cast(&lhs_ptr_type);    /* (typeof(foo) *)((uintptr_t)&foo + (uintptr_t)bar) */
		ctyperef_fini(&lhs_ptr_type);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_deref();                /* *(typeof(foo) *)((uintptr_t)&foo + (uintptr_t)bar) */
		if unlikely(result != DBX_EOK)
			goto err_lhs_ptr_type;
		goto again;
	}	break;

	case CTOKEN_TOK_MINUS_RANGLE:
		/* C-struct deref+field. */
		result = cexpr_deref();
		if unlikely(result != DBX_EOK)
			goto done;
		ATTR_FALLTHROUGH
	case '.': {
		char const *kwd_str;
		size_t kwd_len;
		/* Field w/o deref */
		yield();
#if 1 /* Extension: Automatically dereference pointers to access struct fields. */
		for (;;) {
			uintptr_half_t kind;
			kind = cexpr_stacktop.cv_type.ct_typ->ct_kind;
			if (!CTYPE_KIND_ISARRAY_OR_POINTER(kind))
				break;
			result = cexpr_deref();
			if unlikely(result != DBX_EOK)
				goto done;
		}
#endif
		if (self->c_tok != CTOKEN_TOK_KEYWORD) {
			/* Special case: If we've reached EOF, then  still
			 *               try to auto-complete field names,
			 *               even if the  user hasn't  written
			 *               any part of the name, yet. */
			if (self->c_tok == CTOKEN_TOK_EOF && self->c_autocom) {
				result = autocomplete_struct_fields(self, NULL, 0);
				goto done;
			}
			goto syn;
		}
		kwd_str = self->c_tokstart;
		kwd_len = cparser_toklen(self);
		result  = cexpr_field(kwd_str, kwd_len);
		/* Autocomplete struct field names. */
		if (result == DBX_ENOENT && self->c_autocom && self->c_tokend == self->c_end)
			result = autocomplete_struct_fields(self, kwd_str, kwd_len);
		yield();
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	case '[':
		/* Array expression. */
		yield();
		result = cexpr_pushparse_inner(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cparser_skip(self, ']');
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2('+');
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_deref();
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;

	case CTOKEN_TOK_PLUS_PLUS:
	case CTOKEN_TOK_MINUS_MINUS: {
		struct ctype *typ;
		char op = '+';
		if (self->c_tok == CTOKEN_TOK_MINUS_MINUS)
			op = '-';
		yield();
		result = cexpr_dup();           /* value, value */
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_rvalue();        /* value, (typeof(value))value */
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_swap();          /* (typeof(value))value, value */
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_dup();           /* (typeof(value))value, value, value */
		if unlikely(result != DBX_EOK)
			goto done;
		typ = cexpr_stacktop.cv_type.ct_typ;
		if (!CTYPE_KIND_ISINT(typ->ct_kind))
			typ = &ctype_ptrdiff_t;
		result = cexpr_pushint_simple(typ, 1); /* (typeof(value))value, value, value, 1 */
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2(op);         /* (typeof(value))value, value, value +- 1 */
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_store();         /* (typeof(value))value, value */
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_pop();           /* (typeof(value))value */
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	case '(': {
		size_t argc = 0;
		yield();
		while (self->c_tok && self->c_tok != ')') {
			/* Parse function arguments. */
			result = parse_nocomma(self);
			if unlikely(result != DBX_EOK)
				goto done;
			++argc;
			if (self->c_tok != ',')
				break;
			yield();
		}
		result = cparser_skip(self, ')');
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_call(argc);
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
syn:
	return DBX_ESYNTAX;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_unary)(struct cparser *__restrict self) {
	dbx_errno_t result;
	result = parse_unary_prefix(self);
	if (likely(result == DBX_EOK) && parse_unary_suffix_check(self->c_tok))
		result = parse_unary_suffix(self);
	return result;
}


PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_prod_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case '*':
	case '/':
	case '%': {
		unsigned int op;
		op = self->c_tok;
		yield();
		result = parse_unary(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2(op);
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_sum_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case '+':
	case '-': {
		unsigned int op;
		op = self->c_tok;
		yield();
		result = parse_prod(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2(op);
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_shift_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case CTOKEN_TOK_RANGLE_RANGLE:
	case CTOKEN_TOK_LANGLE_LANGLE: {
		unsigned int op;
		op = self->c_tok;
		yield();
		result = parse_sum(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2(op);
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_cmp_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case '<':
	case '>':
	case CTOKEN_TOK_LANGLE_EQUALS:
	case CTOKEN_TOK_RANGLE_EQUALS: {
		unsigned int op;
		op = self->c_tok;
		yield();
		result = parse_shift(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2(op);
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_cmpeq_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case CTOKEN_TOK_EQUALS_EQUALS:
	case CTOKEN_TOK_XCLAIM_EQUALS: {
		unsigned int op;
		op = self->c_tok;
		yield();
		result = parse_cmp(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2(op);
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_bitand_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case '&': {
		yield();
		result = parse_cmpeq(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2('&');
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_bitxor_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case '^': {
		yield();
		result = parse_bitand(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2('^');
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_bitor_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case '|': {
		yield();
		result = parse_bitxor(self);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_op2('|');
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}


PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_land_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case CTOKEN_TOK_AND_AND: {
		yield();
		if (cexpr_typeonly) {
			result = parse_bitor(self);
			if unlikely(result != DBX_EOK)
				goto done;
			goto again;
		}
		/* Convert to boolean. */
		result = cexpr_cast_simple(&ctype_bool);
		if unlikely(result != DBX_EOK)
			goto done;
		/* Extract boolean value of LHS. */
		result = cexpr_bool();
		if unlikely(DBX_EISERR(result))
			goto done;
		if (!result) {
			/* Found a false-value within an active expression-part.
			 * In this case, switch to type-only evaluation, and skip the remainder. */
			cexpr_typeonly = true;
			result = parse_land(self);
			cexpr_typeonly = false;
			if unlikely(result != DBX_EOK)
				goto done;
			result = cexpr_pop(); /* Pop the unused expression. */
			goto done;
		}
		result = cexpr_pop(); /* Drop the LHS-branch */
		if unlikely(result != DBX_EOK)
			goto done;
		result = parse_bitor(self); /* Parse the RHS-operand */
		if unlikely(result != DBX_EOK)
			goto done;
		/* Convert to boolean. */
		result = cexpr_cast_simple(&ctype_bool);
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_lor_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case CTOKEN_TOK_PIPE_PIPE: {
		yield();
		if (cexpr_typeonly) {
			result = parse_land(self);
			if unlikely(result != DBX_EOK)
				goto done;
			goto again;
		}
		/* Convert to boolean. */
		result = cexpr_cast_simple(&ctype_bool);
		if unlikely(result != DBX_EOK)
			goto done;
		/* Extract boolean value of LHS. */
		result = cexpr_bool();
		if unlikely(DBX_EISERR(result))
			goto done;
		if (result) {
			/* Found a true-value within an active expression-part.
			 * In this case, switch to type-only evaluation, and skip the remainder. */
			cexpr_typeonly = true;
			result = parse_lor(self);
			cexpr_typeonly = false;
			if unlikely(result != DBX_EOK)
				goto done;
			result = cexpr_pop(); /* Pop the unused expression. */
			goto done;
		}
		result = cexpr_pop(); /* Drop the LHS-branch */
		if unlikely(result != DBX_EOK)
			goto done;
		result = parse_land(self); /* Parse the RHS-operand */
		if unlikely(result != DBX_EOK)
			goto done;
		/* Convert to boolean. */
		result = cexpr_cast_simple(&ctype_bool);
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_cond_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case '?': {
		REF struct ctype *common_type;
		bool old_cexpr_typeonly;
		bool eval_tt = false;
		yield();
		if (!cexpr_typeonly) {
			result = cexpr_bool();
			if unlikely(DBX_EISERR(result))
				goto done;
			eval_tt = result > 0;
		}
		/* Check for special case: re-use the condition as true-branch. */
		if (self->c_tok != ':') {
			result = cexpr_pop();
			if unlikely(result != DBX_EOK)
				goto done;
			if (eval_tt) {
				/* Only evaluate the true-branch. */
				result = parse_lor(self);
			} else {
				old_cexpr_typeonly = cexpr_typeonly;
				cexpr_typeonly     = true;
				result             = parse_cond(self);
				cexpr_typeonly     = old_cexpr_typeonly;
			}
			if unlikely(result != DBX_EOK)
				goto done;
		}
		result = cparser_skip(self, ':');
		if unlikely(result != DBX_EOK)
			goto done;
		if (eval_tt) {
			/* Only evaluate the true-branch. */
			old_cexpr_typeonly = cexpr_typeonly;
			cexpr_typeonly     = true;
			result             = parse_cond(self);
			cexpr_typeonly     = old_cexpr_typeonly;
		} else {
			result = parse_cond(self);
			if unlikely(result != DBX_EOK)
				goto done;
			result = cexpr_swap();
		}
		if unlikely(result != DBX_EOK)
			goto done;
		/* Right now our stack should look like this:
		 * >> `keep_branch', `drop_branch' */
		if unlikely(cexpr_stacksize < 2) {
			/* Shouldn't happen... */
			result = DBX_EINTERN;
			goto done;
		}
		common_type = ctype_common(cexpr_stack[cexpr_stacksize - 2].cv_type.ct_typ,
		                           cexpr_stack[cexpr_stacksize - 1].cv_type.ct_typ);
		if unlikely(!common_type) {
			result = DBX_ENOMEM;
			goto done;
		}
		result = cexpr_pop(); /* Drop the unused branch */
		if likely(result == DBX_EOK)
			result = cexpr_cast_simple(common_type); /* Cast the used branch to the common type. */
		decref(common_type);
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_assign_suffix)(struct cparser *__restrict self) {
	dbx_errno_t result;
	unsigned int op;
again:
	switch (self->c_tok) {

	case '=':
		op = 0;
do_assign:
		if (op != 0) {
			result = cexpr_dup();
			if unlikely(result != DBX_EOK)
				goto done;
		}
		yield();
		result = parse_cond(self);
		if unlikely(result != DBX_EOK)
			goto done;
		if (op != 0) {
			result = cexpr_op2(op);
			if unlikely(result != DBX_EOK)
				goto done;
		}
		result = cexpr_store();
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;

	case CTOKEN_TOK_PLUS_EQUALS:
		op = '+';
		goto do_assign;

	case CTOKEN_TOK_MINUS_EQUALS:
		op = '-';
		goto do_assign;

	case CTOKEN_TOK_STAR_EQUALS:
		op = '*';
		goto do_assign;

	case CTOKEN_TOK_SLASH_EQUALS:
		op = '/';
		goto do_assign;

	case CTOKEN_TOK_PERCENT_EQUALS:
		op = '%';
		goto do_assign;

	case CTOKEN_TOK_PIPE_EQUALS:
		op = '|';
		goto do_assign;

	case CTOKEN_TOK_AND_EQUALS:
		op = '&';
		goto do_assign;

	case CTOKEN_TOK_LANGLE_LANGLE_EQUALS:
		op = CTOKEN_TOK_LANGLE_LANGLE;
		goto do_assign;

	case CTOKEN_TOK_RANGLE_RANGLE_EQUALS:
		op = CTOKEN_TOK_RANGLE_RANGLE;
		goto do_assign;

	case CTOKEN_TOK_ROOF_EQUALS:
		op = '^';
		goto do_assign;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
}


/* TODO: Add  another top-level operator  ":" that comes even  before "=", and can
 *       be used  as a  sort-of with-statement,  where the  left-hand-side can  be
 *       used to specify a struct- or pointer-to-struct expression, where  members
 *       of that struct can be used directly, as though they were local variables:
 * >> eval drivers.m_pointer:dll_drivers,dll_count
 * Same as:
 * >> eval drivers.m_pointer.dll_drivers,drivers.m_pointer.dll_count
 *
 * As far as semantics go, this would simply be parsed as
 *     <parse_assign> ':' <parse_collon>
 * where  the <parse_assign>  has to  result in  the aforementioned struct,
 * or pointer-to-struct typing, and  <parse_collon> is the recursive  part,
 * meaning that an expression `foo:bar:baz' is parsed as `foo:(bar:(baz))'.
 *
 * The members of the left-hand-side are only visible for the duration of  the
 * evaluation of the right-hand-side, and would supersede even local variables
 * as far as scoping goes. If the left-hand-side expression is another collon-
 * expression, struct fields are made available recursively:
 *     foo:bar:baz
 * Evaluate to the first match from (in this order):
 *     #1: HAS_FIELD($GLOBALS["foo"], "bar")
 *            ? $GLOBALS["foo"].bar.baz
 *            :     $GLOBALS["bar"].baz
 *     #2: $GLOBALS["foo"].baz
 *     #3: $GLOBALS["baz"]
 *
 * Additionally, multiple such statements can be chained, where symbols  from
 * those that are further to the right supersede symbols exposed by ones from
 * earlier.
 *
 * This operator also interacts with `symbols_prefix*', such that an expression:
 * >> foo*:bar
 * will evaluation to an arbitrary member "bar" found in a structure who's
 * name starts with "foo"
 */

#define DEFINE_INTERPOS_PARSER(name, inner_name)                                   \
	PRIVATE WUNUSED NONNULL((1)) dbx_errno_t                                       \
	NOTHROW(FCALL parse_##name)(struct cparser *__restrict self) {                 \
		dbx_errno_t result;                                                        \
		result = parse_##inner_name(self);                                         \
		if (likely(result == DBX_EOK) && parse_##name##_suffix_check(self->c_tok)) \
			result = parse_##name##_suffix(self);                                  \
		return result;                                                             \
	}
DEFINE_INTERPOS_PARSER(prod, unary)
DEFINE_INTERPOS_PARSER(sum, prod)
DEFINE_INTERPOS_PARSER(shift, sum)
DEFINE_INTERPOS_PARSER(cmp, shift)
DEFINE_INTERPOS_PARSER(cmpeq, cmp)
DEFINE_INTERPOS_PARSER(bitand, cmpeq)
DEFINE_INTERPOS_PARSER(bitxor, bitand)
DEFINE_INTERPOS_PARSER(bitor, bitxor)
DEFINE_INTERPOS_PARSER(land, bitor)
DEFINE_INTERPOS_PARSER(lor, land)
DEFINE_INTERPOS_PARSER(cond, lor)
/*DEFINE_INTERPOS_PARSER(assign, cond)*/
#undef DEFINE_INTERPOS_PARSER

PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL parse_assign)(struct cparser *__restrict self) {
	dbx_errno_t result;
	/* Parse the base-level unary expression. */
	result = parse_unary_prefix(self);
	if unlikely(result != DBX_EOK)
		goto done;
	/* Parse arbitrary suffix expressions in correct order. */
	switch (self->c_tok) {

	parse_unary_suffix_CASE:
		result = parse_unary_suffix(self);
		if unlikely(result != DBX_EOK)
			goto done;
#define PARSE_CASE_CHECK(name)                          \
		if (parse_##name##_suffix_check(self->c_tok)) { \
	parse_##name##_suffix_CASE:                         \
			result = parse_##name##_suffix(self);       \
			if unlikely(result != DBX_EOK)              \
				goto done;                              \
		}
		PARSE_CASE_CHECK(prod)
		PARSE_CASE_CHECK(sum)
		PARSE_CASE_CHECK(shift)
		PARSE_CASE_CHECK(cmp)
		PARSE_CASE_CHECK(cmpeq)
		PARSE_CASE_CHECK(bitand)
		PARSE_CASE_CHECK(bitxor)
		PARSE_CASE_CHECK(bitor)
		PARSE_CASE_CHECK(land)
		PARSE_CASE_CHECK(lor)
		PARSE_CASE_CHECK(cond)
		PARSE_CASE_CHECK(assign)
#undef PARSE_CASE_CHECK
		break;

	default:
		break;
	}
done:
	return result;
}





/* Parse a  C-expression  from  `self'  and  push  its  value
 * onto the C-expression  stack, return  DBX_EOK on  success,
 * and a potential  error otherwise (in  the later case,  the
 * effective  size  of  the  C-expression  stack  will remain
 * unaltered). NOTE: The given `self' is expected to  already
 * point to the first token apart of the expression on entry. */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_pushparse)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	result = parse_nocomma(self);
	if unlikely(result != DBX_EOK)
		goto done;
	if (self->c_tok == ',') {
again_after_comma:
		yield();
		if (ceval_comma_is_select2nd) {
			result = cexpr_pop();
			if unlikely(result != DBX_EOK)
				goto done;
			goto again;
		} else {
			size_t array_length;
			struct ctyperef new_array_type;
			struct ctyperef lhs_elem_type;
			struct ctype *lhs_operand_type;
			REF struct ctype *array_pointer_type;
			bool old_cexpr_typeonly;
			old_cexpr_typeonly = cexpr_typeonly;
			cexpr_typeonly     = false;
			/* Special case: Implement the comma-for-array expression. */
			result = parse_nocomma(self);
			if unlikely(result != DBX_EOK) {
				cexpr_typeonly = old_cexpr_typeonly;
				goto done;
			}
			if unlikely(self->c_tok == ',') {
				/* Only the last comma acts as an array cast. */
				cexpr_typeonly = old_cexpr_typeonly;
				result = cexpr_swap();
				if unlikely(result != DBX_EOK)
					goto done;
				result = cexpr_pop();
				if unlikely(result != DBX_EOK)
					goto done;
				goto again_after_comma;
			}
			/* Last comma reached, and our expression stack looks like this:
			 * [...]  foo  16
			 * for `foo, 16' */
			/* As such, cast the top-expression (16) to `size_t' */
			result = cexpr_cast_simple(&ctype_size_t);
			if unlikely(result != DBX_EOK) {
				cexpr_typeonly = old_cexpr_typeonly;
				goto done;
			}
			{
				byte_t *data;
				result = cexpr_getdata(&data);
				if (likely(result == DBX_EOK) &&
				    unlikely(dbg_readmemory(data, &array_length, sizeof(size_t)) != 0))
					result = DBX_EFAULT;
				if unlikely(result != DBX_EOK) {
					cexpr_typeonly = old_cexpr_typeonly;
					goto err_nomem;
				}
			}
			/* Pop the array-length expression. */
			result = cexpr_pop();
			cexpr_typeonly = old_cexpr_typeonly;
			if unlikely(result != DBX_EOK)
				goto done;
			/* The left operand of the ,-operator must be a pointer or array. */
			lhs_operand_type = cexpr_stacktop.cv_type.ct_typ;
			if (CTYPE_KIND_ISARRAY(lhs_operand_type->ct_kind)) {
				lhs_elem_type.ct_flags = cexpr_stacktop.cv_type.ct_flags;
				lhs_elem_type.ct_typ   = lhs_operand_type->ct_array.ca_elem;
				lhs_elem_type.ct_info  = lhs_operand_type->ct_array.ca_eleminfo;
			} else if (CTYPE_KIND_ISPOINTER(lhs_operand_type->ct_kind)) {
				memcpy(&lhs_elem_type,
				       &lhs_operand_type->ct_pointer.cp_base,
				       sizeof(struct ctyperef));
			} else {
				result = DBX_ESYNTAX;
				goto done;
			}
			bzero(&new_array_type, sizeof(new_array_type));
			new_array_type.ct_flags = lhs_elem_type.ct_flags;
			new_array_type.ct_typ   = ctype_array(&lhs_elem_type, array_length);
			if unlikely(!new_array_type.ct_typ)
				goto err_nomem;
			array_pointer_type = ctype_ptr(&new_array_type, dbg_current_sizeof_pointer());
			decref(new_array_type.ct_typ);
			if unlikely(!array_pointer_type)
				goto err_nomem;
			/* And now do the actual cast. */
			result = cexpr_cast_simple(array_pointer_type);
			decref(array_pointer_type);
			if unlikely(result != DBX_EOK)
				goto done;
			/* And finally, deref the result. */
			result = cexpr_deref();
		} /* !ceval_comma_is_select2nd */
	} /* if (self->c_tok == ',') */
done:
	return result;
err_nomem:
	result = DBX_ENOMEM;
	goto done;
}


/* Light-weight wrapper around `cexpr_pushparse()', and also
 * the top-level function used for evaluating C expressions.
 * @param: expr:     The C expression that should be parsed.
 * @param: maxlen:   The max length of `expr' (actual length is `strnlen(expr, maxlen)')
 * @return: DBX_EOK: Success
 * @return: * :      Error (the effective c-expression-stack-size is unaltered) */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_pusheval)(char const *__restrict expr,
                              size_t maxlen) {
	dbx_errno_t result;
	struct cparser cp;
	cparser_init(&cp, expr, strnlen(expr, maxlen));
	result = cexpr_pushparse(&cp);
	/* Make sure that the entirety of `expr' was parsed. */
	if (likely(result == DBX_EOK) && unlikely(cp.c_tok != CTOKEN_TOK_EOF))
		result = DBX_ESYNTAX;
	return result;
}

struct ctype_attributes {
	uint16_t ca_fun_cc; /* Calling convention for functions (one of `CTYPE_KIND_FUNPROTO_CC_*') */
};

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) uint16_t
NOTHROW(FCALL keyword_to_calling_convention)(char const *__restrict kwd_str,
                                             size_t kwd_len) {
	(void)kwd_str;
	(void)kwd_len;
#ifdef CTYPE_KIND_FUNPROTO_CC_CDECL
	if (KWD_CHECK(kwd_str, kwd_len, "cdecl"))
		return CTYPE_KIND_FUNPROTO_CC_CDECL;
#endif /* CTYPE_KIND_FUNPROTO_CC_CDECL */
#ifdef CTYPE_KIND_FUNPROTO_CC_FASTCALL
	if (KWD_CHECK(kwd_str, kwd_len, "fastcall"))
		return CTYPE_KIND_FUNPROTO_CC_FASTCALL;
#endif /* CTYPE_KIND_FUNPROTO_CC_FASTCALL */
#ifdef CTYPE_KIND_FUNPROTO_CC_STDCALL
	if (KWD_CHECK(kwd_str, kwd_len, "stdcall"))
		return CTYPE_KIND_FUNPROTO_CC_STDCALL;
#endif /* CTYPE_KIND_FUNPROTO_CC_STDCALL */
#ifdef CTYPE_KIND_FUNPROTO_CC_SYSVABI
	if (KWD_CHECK(kwd_str, kwd_len, "sysv_abi"))
		return CTYPE_KIND_FUNPROTO_CC_SYSVABI;
#endif /* CTYPE_KIND_FUNPROTO_CC_SYSVABI */
#ifdef CTYPE_KIND_FUNPROTO_CC_MSABI
	if (KWD_CHECK(kwd_str, kwd_len, "ms_abi"))
		return CTYPE_KIND_FUNPROTO_CC_MSABI;
#endif /* CTYPE_KIND_FUNPROTO_CC_MSABI */
	return (uint16_t)-1;
}


PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL skip_generic_attribute)(struct cparser *__restrict self) {
	dbx_errno_t result;
again:
	result = cparser_skip(self, CTOKEN_TOK_KEYWORD);
	if unlikely(result != DBX_EOK)
		goto done;
	if (self->c_tok == CTOKEN_TOK_COLON_COLON) {
		yield();
		goto again;
	}
	if (self->c_tok == '(') {
		unsigned int recursion = 0;
		for (;;) {
			yield();
			if (self->c_tok == '(') {
				++recursion;
			} else if (self->c_tok == ')') {
				if (!recursion)
					break;
				--recursion;
			} else if (!self->c_tok) {
				result = DBX_ESYNTAX;
				goto done;
			}
		}
		yield(); /* Skip the trailing ')'-token. */
	}
done:
	return result;
}


PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL ctype_parse_attrib_gcc)(struct cparser *__restrict self,
                                      struct ctype_attributes *__restrict attrib) {
	char const *kwd_str;
	size_t kwd_len;
	uint16_t cc;
	kwd_str = self->c_tokstart;
	kwd_len = cparser_toklen(self);
	while (kwd_len && kwd_str[0] == '_') {
		++kwd_str;
		--kwd_len;
	}
	while (kwd_len && kwd_str[kwd_len - 1] == '_')
		--kwd_len;
	cc = keyword_to_calling_convention(kwd_str, kwd_len);
	if (cc != (uint16_t)-1) {
		attrib->ca_fun_cc = cc;
		yield();
		return DBX_EOK;
	}
	return skip_generic_attribute(self);
}
#define ctype_parse_attrib_declspec ctype_parse_attrib_gcc

PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL ctype_parse_attrib_cxx)(struct cparser *__restrict self,
                                      struct ctype_attributes *__restrict attrib) {
	dbx_errno_t result;
	char const *kwd_str;
	size_t kwd_len;
	if (self->c_tok != CTOKEN_TOK_KEYWORD)
		goto syn;
	kwd_str = self->c_tokstart;
	kwd_len = cparser_toklen(self);
	while (kwd_len && kwd_str[0] == '_') {
		++kwd_str;
		--kwd_len;
	}
	while (kwd_len && kwd_str[kwd_len - 1] == '_')
		--kwd_len;
	if (KWD_CHECK(kwd_str, kwd_len, "gnu")) {
		yield();
		if (self->c_tok == CTOKEN_TOK_COLON_COLON) {
			yield();
			result = ctype_parse_attrib_gcc(self, attrib);
			goto done;
		}
		cparser_yieldat(self, kwd_str);
	}
	result = skip_generic_attribute(self);
done:
	return result;
syn:
	result = DBX_ESYNTAX;
	goto done;
}

PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL ctype_parse_attrib)(struct cparser *__restrict self,
                                  struct ctype_attributes *__restrict attrib) {
	dbx_errno_t result = DBX_EOK;
again:
	if (self->c_tok == '[') {
		char const *tok_start = self->c_tokstart;
		yield();
		if (self->c_tok != '[') {
			cparser_yieldat(self, tok_start);
			goto done;
		}
		yield();
again_parse_attrib_cxx:
		result = ctype_parse_attrib_cxx(self, attrib);
		if unlikely(result != DBX_EOK)
			goto done;
		if (self->c_tok == ',') {
			yield();
			if (self->c_tok == CTOKEN_TOK_KEYWORD)
				goto again_parse_attrib_cxx;
		}
		result = cparser_skip(self, ']');
		if unlikely(result != DBX_EOK)
			goto done;
		result = cparser_skip(self, ']');
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}
	if (self->c_tok == CTOKEN_TOK_KEYWORD) {
		char const *kwd_str;
		size_t kwd_len;
		kwd_str = self->c_tokstart;
		kwd_len = cparser_toklen(self);
		while (kwd_len && kwd_str[0] == '_') {
			++kwd_str;
			--kwd_len;
		}
		while (kwd_len && kwd_str[kwd_len - 1] == '_')
			--kwd_len;
		if (*self->c_tokstart == '_') {
			uint16_t cc;
			cc = keyword_to_calling_convention(kwd_str, kwd_len);
			if (cc != (uint16_t)-1) {
				attrib->ca_fun_cc = cc;
				yield();
				goto again;
			}
		}
		if (KWD_CHECK(kwd_str, kwd_len, "attribute")) {
			yield();
			result = cparser_skip(self, '(');
			if unlikely(result != DBX_EOK)
				goto done;
			result = cparser_skip(self, '(');
			if unlikely(result != DBX_EOK)
				goto done;
again_parse_attrib_gcc:
			result = ctype_parse_attrib_gcc(self, attrib);
			if unlikely(result != DBX_EOK)
				goto done;
			if (self->c_tok == ',') {
				yield();
				if (self->c_tok == CTOKEN_TOK_KEYWORD)
					goto again_parse_attrib_gcc;
			}
			result = cparser_skip(self, ')');
			if unlikely(result != DBX_EOK)
				goto done;
			result = cparser_skip(self, ')');
			if unlikely(result != DBX_EOK)
				goto done;
			goto again;
		}
		if (KWD_CHECK(kwd_str, kwd_len, "declspec")) {
			yield();
			result = cparser_skip(self, '(');
			if unlikely(result != DBX_EOK)
				goto done;
again_parse_attrib_declspec:
			result = ctype_parse_attrib_declspec(self, attrib);
			if unlikely(result != DBX_EOK)
				goto done;
			if (self->c_tok == ',') {
				yield();
				if (self->c_tok == CTOKEN_TOK_KEYWORD)
					goto again_parse_attrib_declspec;
			}
			result = cparser_skip(self, ')');
			if unlikely(result != DBX_EOK)
				goto done;
			goto again;
		}
	}
done:
	return result;
}

/* Parse `const' / `volatile' / `_Atomic' type flags. */
PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL ctype_parse_cv)(struct cparser *__restrict self,
                              uintptr_t *__restrict ct_flags,
                              struct ctype_attributes *__restrict attrib) {
	dbx_errno_t result = DBX_EOK;
	while (self->c_tok == CTOKEN_TOK_KEYWORD) {
		char const *kwd_str;
		size_t kwd_len;
		kwd_str = self->c_tokstart;
		kwd_len = cparser_toklen(self);
		if (KWD_CHECK(kwd_str, kwd_len, "atomic") ||
		    KWD_CHECK(kwd_str, kwd_len, "_Atomic")) {
			if (*ct_flags & CTYPEREF_FLAG_ATOMIC)
				goto syn;
			*ct_flags |= CTYPEREF_FLAG_ATOMIC;
			yield();
			continue;
		}
		/* Strip leading/trailing underscores */
		while (kwd_len && kwd_str[0] == '_') {
			++kwd_str;
			--kwd_len;
		}
		while (kwd_len && kwd_str[kwd_len - 1] == '_')
			--kwd_len;
		if (KWD_CHECK(kwd_str, kwd_len, "const")) {
			if (*ct_flags & CTYPEREF_FLAG_CONST)
				goto syn;
			*ct_flags |= CTYPEREF_FLAG_CONST;
			yield();
			continue;
		}
		if (KWD_CHECK(kwd_str, kwd_len, "volatile")) {
			if (*ct_flags & CTYPEREF_FLAG_VOLATILE)
				goto syn;
			*ct_flags |= CTYPEREF_FLAG_VOLATILE;
			yield();
			continue;
		}
		if (KWD_CHECK(kwd_str, kwd_len, "restrict")) {
			if (*ct_flags & CTYPEREF_FLAG_RESTRICT)
				goto syn;
			*ct_flags |= CTYPEREF_FLAG_RESTRICT;
			yield();
			continue;
		}
#ifdef CTYPEREF_FLAG_SEG_FS
		if (KWD_CHECK(kwd_str, kwd_len, "seg_fs")) {
			if (*ct_flags & CTYPEREF_FLAG_SEGMASK)
				goto syn;
			*ct_flags |= CTYPEREF_FLAG_SEG_FS;
			yield();
			continue;
		}
#endif /* CTYPEREF_FLAG_SEG_FS */
#ifdef CTYPEREF_FLAG_SEG_GS
		if (KWD_CHECK(kwd_str, kwd_len, "seg_gs")) {
			if (*ct_flags & CTYPEREF_FLAG_SEGMASK)
				goto syn;
			*ct_flags |= CTYPEREF_FLAG_SEG_GS;
			yield();
			continue;
		}
#endif /* CTYPEREF_FLAG_SEG_GS */
		kwd_str = self->c_tokstart;
		result  = ctype_parse_attrib(self, attrib);
		if unlikely(result != DBX_EOK)
			goto done;
		if (kwd_str == self->c_tokstart)
			break;
	}
done:
	return result;
syn:
	result = DBX_ESYNTAX;
	goto done;
}


struct builtin_type {
	char          bt_name[24]; /* Type name */
	struct ctype *bt_type;     /* [1..1] Type pointer. */
};

PRIVATE struct builtin_type const builtin_types[] = {
	{ "void", &ctype_void },
	{ "bool", &ctype_bool },
	{ "_Bool", &ctype_bool },
	{ "float", &ctype_ieee754_float },
	{ "wchar_t", &ctype_wchar_t },
	{ "__wchar_t", &ctype_wchar_t },
	{ "char8_t", &ctype_char8_t },
	{ "char16_t", &ctype_char16_t },
	{ "char32_t", &ctype_char32_t },

	/* Some more "known" types for convenience. */
	{ "s8",  &ctype_s8  }, { "__s8",  &ctype_s8  }, { "int8_t",   &ctype_s8  }, { "__int8_t",   &ctype_s8  }, { "__INT8_TYPE__",   &ctype_s8  },
	{ "u8",  &ctype_u8  }, { "__u8",  &ctype_u8  }, { "uint8_t",  &ctype_u8  }, { "__uint8_t",  &ctype_u8  }, { "__UINT8_TYPE__",  &ctype_u8  },
	{ "s16", &ctype_s16 }, { "__s16", &ctype_s16 }, { "int16_t",  &ctype_s16 }, { "__int16_t",  &ctype_s16 }, { "__INT16_TYPE__",  &ctype_s16 },
	{ "u16", &ctype_u16 }, { "__u16", &ctype_u16 }, { "uint16_t", &ctype_u16 }, { "__uint16_t", &ctype_u16 }, { "__UINT16_TYPE__", &ctype_u16 },
	{ "s32", &ctype_s32 }, { "__s32", &ctype_s32 }, { "int32_t",  &ctype_s32 }, { "__int32_t",  &ctype_s32 }, { "__INT32_TYPE__",  &ctype_s32 },
	{ "u32", &ctype_u32 }, { "__u32", &ctype_u32 }, { "uint32_t", &ctype_u32 }, { "__uint32_t", &ctype_u32 }, { "__UINT32_TYPE__", &ctype_u32 },
	{ "s64", &ctype_s64 }, { "__s64", &ctype_s64 }, { "int64_t",  &ctype_s64 }, { "__int64_t",  &ctype_s64 }, { "__INT64_TYPE__",  &ctype_s64 },
	{ "u64", &ctype_u64 }, { "__u64", &ctype_u64 }, { "uint64_t", &ctype_u64 }, { "__uint64_t", &ctype_u64 }, { "__UINT64_TYPE__", &ctype_u64 },

	{ "size_t", &ctype_size_t }, { "__size_t", &ctype_size_t }, { "__SIZE_TYPE__", &ctype_size_t },
	{ "ssize_t", &ctype_ssize_t }, { "__ssize_t", &ctype_ssize_t }, { "__SSIZE_TYPE__", &ctype_ssize_t },
	{ "ptrdiff_t", &ctype_ptrdiff_t }, { "__ptrdiff_t", &ctype_ptrdiff_t }, { "__PTRDIFF_TYPE__", &ctype_ptrdiff_t },
	{ "intptr_t", &ctype_intptr_t }, { "__intptr_t", &ctype_intptr_t }, { "__INTPTR_TYPE__", &ctype_intptr_t },
	{ "uintptr_t", &ctype_uintptr_t }, { "__uintptr_t", &ctype_uintptr_t }, { "__UINTPTR_TYPE__", &ctype_uintptr_t },
};

#ifdef __ARCH_HAVE_COMPAT
PRIVATE struct builtin_type const compat_builtin_types[] = {
	/* Some more "known" types for convenience. */
	{ "size_t", &ctype_compat_size_t }, { "__size_t", &ctype_compat_size_t }, { "__SIZE_TYPE__", &ctype_compat_size_t },
	{ "ssize_t", &ctype_compat_ssize_t }, { "__ssize_t", &ctype_compat_ssize_t }, { "__SSIZE_TYPE__", &ctype_compat_ssize_t },
	{ "ptrdiff_t", &ctype_compat_ptrdiff_t }, { "__ptrdiff_t", &ctype_compat_ptrdiff_t }, { "__PTRDIFF_TYPE__", &ctype_compat_ptrdiff_t },
	{ "intptr_t", &ctype_compat_intptr_t }, { "__intptr_t", &ctype_compat_intptr_t }, { "__INTPTR_TYPE__", &ctype_compat_intptr_t },
	{ "uintptr_t", &ctype_compat_uintptr_t }, { "__uintptr_t", &ctype_compat_uintptr_t }, { "__UINTPTR_TYPE__", &ctype_compat_uintptr_t },
};
#endif /* __ARCH_HAVE_COMPAT */

PRIVATE char const misc_type_keywords[][16] = {
	"int", "short", "char", "long", "signed", "unsigned", "double",
	"__int8", "__int16", "__int32", "__int64", "typeof",
	"struct", "union", "class", "enum"
};


PRIVATE NONNULL((1)) void
NOTHROW(FCALL autocomplete_types)(struct cparser *__restrict self,
                                  char const *__restrict name,
                                  size_t namelen, uintptr_t ns) {
	unsigned int i;
	if (namelen < (COMPILER_LENOF(builtin_types[0].bt_name) - 1)) {
		for (i = 0; i < COMPILER_LENOF(builtin_types); ++i) {
			if (memcmp(builtin_types[i].bt_name, name, namelen) == 0 &&
			    builtin_types[i].bt_name[namelen] != '\0') {
				char const *cname_str = builtin_types[i].bt_name;
				size_t cname_len = strlen(cname_str);
				cparser_autocomplete(self,
				                     cname_str + namelen,
				                     cname_len - namelen);
			}
		}
	}
	if (namelen < (COMPILER_LENOF(misc_type_keywords[0]) - 1)) {
		for (i = 0; i < COMPILER_LENOF(misc_type_keywords); ++i) {
			if (memcmp(misc_type_keywords[i], name, namelen) == 0 &&
			    misc_type_keywords[i][namelen] != '\0') {
				char const *cname_str = misc_type_keywords[i];
				size_t cname_len = strlen(cname_str);
				cparser_autocomplete(self,
				                     cname_str + namelen,
				                     cname_len - namelen);
			}
		}
	}
	autocomplete_symbols(self, name, namelen, ns);
}




PRIVATE WUNUSED NONNULL((1, 2, 3)) dbx_errno_t
NOTHROW(FCALL ctype_parse_base)(struct cparser *__restrict self,
                                /*out:ref*/ struct ctyperef *__restrict presult,
                                struct ctype_attributes *__restrict attrib) {
	dbx_errno_t result;
	char const *kwd_str;
	size_t kwd_len;
	unsigned int integer_type_flags;
#define BASETYPE_FLAG_SIGNED    0x0001 /* FLAG: `signed' was given */
#define BASETYPE_FLAG_UNSIGNED  0x0002 /* FLAG: `unsigned' was given */
#define BASETYPE_FLAG_SIGNMASK  0x0003 /* Mask for explicit sign prefix. */
#define BASETYPE_FLAG_INT       0x0004 /* FLAG: Explicit `int' was given. */
#define BASETYPE_FLAG_CHAR      0x0010 /* FLAG: `char' was given. */
#define BASETYPE_FLAG_SHORT     0x0020 /* FLAG: `short' was given. */
#define BASETYPE_FLAG_LONG      0x0030 /* FLAG: `long' was given. */
#define BASETYPE_FLAG_LLONG     0x0040 /* FLAG: `long long' was given. */
#define BASETYPE_FLAG_INT8      0x0050 /* FLAG: `__int8' was given. */
#define BASETYPE_FLAG_INT16     0x0060 /* FLAG: `__int16' was given. */
#define BASETYPE_FLAG_INT32     0x0070 /* FLAG: `__int32' was given. */
#define BASETYPE_FLAG_INT64     0x0080 /* FLAG: `__int64' was given. */
#define BASETYPE_FLAG_WIDTHMASK 0x00f0 /* MASK: Explicit width was given. */
	char const *orig_tok = self->c_tokstart;
	if (self->c_tok != CTOKEN_TOK_KEYWORD)
		return DBX_ENOENT;
	bzero(presult, sizeof(*presult));
	/* Parse const/volatile flags, and initial attributes. */
	result = ctype_parse_cv(self, &presult->ct_flags, attrib);
	if unlikely(result != DBX_EOK)
		goto err_nopresult;
	if unlikely(self->c_tok != CTOKEN_TOK_KEYWORD)
		goto syn;
	integer_type_flags = 0;
do_scan_keyword:
	kwd_str = self->c_tokstart;
	kwd_len = cparser_toklen(self);
	if (KWD_CHECK(kwd_str, kwd_len, "struct") ||
	    KWD_CHECK(kwd_str, kwd_len, "union") ||
	    KWD_CHECK(kwd_str, kwd_len, "class") ||
	    KWD_CHECK(kwd_str, kwd_len, "enum")) {
		uintptr_t ns;
		struct cmodsyminfo csym;
		struct ctyperef dw_type;
		if unlikely(integer_type_flags)
			goto syn;
		ns = kwd_len == 6
		     ? CMODSYM_DIP_NS_STRUCT
		     : kwd_len == 4
		       ? CMODSYM_DIP_NS_ENUM
		       : kwd_str[0] == 'u'
		         ? CMODSYM_DIP_NS_UNION
		         : CMODSYM_DIP_NS_CLASS;
		yield();
		/* Parse additional attributes before the name. */
		result = ctype_parse_attrib(self, attrib);
		if unlikely(result != DBX_EOK)
			goto err_nopresult;
		if unlikely(self->c_tok != CTOKEN_TOK_KEYWORD)
			goto syn;
		/* Lookup the object name. */
		kwd_str = self->c_tokstart;
		kwd_len = cparser_toklen(self);

		result = cmod_syminfo_local(&csym, kwd_str, kwd_len, ns);
		if unlikely(result != DBX_EOK) {
			if (result == DBX_ENOENT && self->c_autocom && self->c_tokend == self->c_end)
				autocomplete_symbols(self, kwd_str, kwd_len, ns);
			goto err_nopresult;
		}
		/* Load the C-type from the symbol we've found. */
		result = ctype_from_cmodsyminfo(&csym, &dw_type);
		cmod_syminfo_local_fini(&csym);
		if unlikely(result != DBX_EOK)
			goto err_nopresult;
		presult->ct_typ  = dw_type.ct_typ;  /* Inherit reference */
		presult->ct_info = dw_type.ct_info; /* Inherit data */
		presult->ct_flags |= dw_type.ct_flags;
		yield();
	} else if (KWD_CHECK(kwd_str, kwd_len, "int")) {
		if unlikely(integer_type_flags & BASETYPE_FLAG_INT)
			goto syn;
		integer_type_flags |= BASETYPE_FLAG_INT;
yield_and_scan_keyword:
		yield();
		goto do_scan_keyword;
	} else if (KWD_CHECK(kwd_str, kwd_len, "short")) {
		if unlikely(integer_type_flags & BASETYPE_FLAG_WIDTHMASK)
			goto syn;
		integer_type_flags |= BASETYPE_FLAG_SHORT;
		goto yield_and_scan_keyword;
	} else if (KWD_CHECK(kwd_str, kwd_len, "long")) {
		if (integer_type_flags & BASETYPE_FLAG_WIDTHMASK) {
			if ((integer_type_flags & BASETYPE_FLAG_WIDTHMASK) == BASETYPE_FLAG_LONG) {
				integer_type_flags &= ~BASETYPE_FLAG_WIDTHMASK;
				integer_type_flags |= BASETYPE_FLAG_LLONG;
				goto yield_and_scan_keyword;
			}
			goto syn;
		}
		integer_type_flags |= BASETYPE_FLAG_LONG;
		goto yield_and_scan_keyword;
	} else if (KWD_CHECK(kwd_str, kwd_len, "char")) {
		if unlikely(integer_type_flags & BASETYPE_FLAG_WIDTHMASK)
			goto syn;
		integer_type_flags |= BASETYPE_FLAG_CHAR;
		goto yield_and_scan_keyword;
	} else if (KWD_CHECK(kwd_str, kwd_len, "double")) {
#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
		if unlikely(integer_type_flags != 0 &&
		            integer_type_flags != BASETYPE_FLAG_LONG)
			goto syn;
#else /* CTYPE_KIND_IEEE854_LONG_DOUBLE */
		if unlikely(integer_type_flags != 0)
			goto syn;
#endif /* !CTYPE_KIND_IEEE854_LONG_DOUBLE */
		yield();
		presult->ct_typ = &ctype_ieee754_double;
#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
		if (self->c_tok == CTOKEN_TOK_KEYWORD) {
			if unlikely(integer_type_flags != 0)
				goto syn;
			kwd_str = self->c_tokstart;
			kwd_len = cparser_toklen(self);
			if (KWD_CHECK(kwd_str, kwd_len, "long")) {
				presult->ct_typ = &ctype_ieee854_long_double;
				yield();
			}
		} else if (integer_type_flags == BASETYPE_FLAG_LONG) {
			presult->ct_typ = &ctype_ieee854_long_double;
		}
#endif /* CTYPE_KIND_IEEE854_LONG_DOUBLE */
		incref(presult->ct_typ);
	} else {
		/* Check for builtin types. */
		if (kwd_len < COMPILER_LENOF(builtin_types->bt_name)) {
			unsigned int i;
#ifdef __ARCH_HAVE_COMPAT
			if (dbg_current_iscompat()) {
				for (i = 0; i < COMPILER_LENOF(compat_builtin_types); ++i) {
					if (compat_builtin_types[i].bt_name[kwd_len] == '\0' &&
						memcmp(compat_builtin_types[i].bt_name, kwd_str, kwd_len) == 0) {
						/* Found it! */
						if unlikely(integer_type_flags != 0)
							goto syn;
						presult->ct_typ = incref(compat_builtin_types[i].bt_type);
						yield();
						goto done;
					}
				}
			}
#endif /* __ARCH_HAVE_COMPAT */
			for (i = 0; i < COMPILER_LENOF(builtin_types); ++i) {
				if (builtin_types[i].bt_name[kwd_len] == '\0' &&
				    memcmp(builtin_types[i].bt_name, kwd_str, kwd_len) == 0) {
					/* Found it! */
					if unlikely(integer_type_flags != 0)
						goto syn;
					presult->ct_typ = incref(builtin_types[i].bt_type);
					yield();
					goto done;
				}
			}
		}

		/* Strip leading/trailing underscores */
		while (kwd_len && kwd_str[0] == '_') {
			++kwd_str;
			--kwd_len;
		}
		while (kwd_len && kwd_str[kwd_len - 1] == '_')
			--kwd_len;
		/* Check for keywords that are also accepted with underscores. */
		if (KWD_CHECK(kwd_str, kwd_len, "unsigned")) {
			if unlikely(integer_type_flags & BASETYPE_FLAG_SIGNMASK)
				goto syn;
			integer_type_flags |= BASETYPE_FLAG_UNSIGNED;
			goto yield_and_scan_keyword;
		}
		if (KWD_CHECK(kwd_str, kwd_len, "signed")) {
			if (integer_type_flags & BASETYPE_FLAG_SIGNMASK)
				goto syn;
			integer_type_flags |= BASETYPE_FLAG_SIGNED;
			goto yield_and_scan_keyword;
		}
		if (KWD_CHECK(kwd_str, kwd_len, "int8")) {
			if (integer_type_flags & BASETYPE_FLAG_WIDTHMASK)
				goto syn;
			integer_type_flags |= BASETYPE_FLAG_INT8;
			goto yield_and_scan_keyword;
		}
		if (KWD_CHECK(kwd_str, kwd_len, "int16")) {
			if (integer_type_flags & BASETYPE_FLAG_WIDTHMASK)
				goto syn;
			integer_type_flags |= BASETYPE_FLAG_INT16;
			goto yield_and_scan_keyword;
		}
		if (KWD_CHECK(kwd_str, kwd_len, "int32")) {
			if (integer_type_flags & BASETYPE_FLAG_WIDTHMASK)
				goto syn;
			integer_type_flags |= BASETYPE_FLAG_INT32;
			goto yield_and_scan_keyword;
		}
		if (KWD_CHECK(kwd_str, kwd_len, "int64")) {
			if (integer_type_flags & BASETYPE_FLAG_WIDTHMASK)
				goto syn;
			integer_type_flags |= BASETYPE_FLAG_INT64;
			goto yield_and_scan_keyword;
		}
		if (KWD_CHECK(kwd_str, kwd_len, "typeof") ||
		    KWD_CHECK(kwd_str, kwd_len, "decltype")) {
			/* typeof-expression */
			uintptr_t more_flags;
			if unlikely(integer_type_flags != 0)
				goto syn;
			yield();
			more_flags = presult->ct_flags;
			result     = parse_typeof(self, presult);
			if unlikely(result != DBX_EOK)
				goto err_nopresult;
			presult->ct_flags |= more_flags;
		} else if (integer_type_flags != 0) {
			/* Complete a segmented integer type. */
			switch (integer_type_flags & BASETYPE_FLAG_WIDTHMASK) {

			case BASETYPE_FLAG_CHAR:
				if ((integer_type_flags & BASETYPE_FLAG_SIGNMASK) == 0) {
					presult->ct_typ = &ctype_char;
					incref(presult->ct_typ);
					goto done;
				}
				presult->ct_typ = &ctype_signed_char;
				break;

			case BASETYPE_FLAG_SHORT: presult->ct_typ = &ctype_short; break;
			case BASETYPE_FLAG_LONG: presult->ct_typ = &ctype_long; break;
			case BASETYPE_FLAG_LLONG: presult->ct_typ = &ctype_long; break;
			case BASETYPE_FLAG_INT8: presult->ct_typ = &ctype_s8; break;
			case BASETYPE_FLAG_INT16: presult->ct_typ = &ctype_s16; break;
			case BASETYPE_FLAG_INT32: presult->ct_typ = &ctype_s32; break;
			case BASETYPE_FLAG_INT64: presult->ct_typ = &ctype_s64; break;

			default: presult->ct_typ = &ctype_int; break;
			}
			/* Convert to unsigned if required. */
			if ((integer_type_flags & BASETYPE_FLAG_SIGNMASK) == BASETYPE_FLAG_UNSIGNED) {
				presult->ct_typ = make_unsigned(presult->ct_typ);
				if unlikely(!presult->ct_typ)
					presult->ct_typ = &ctype_unsigned_int;
			}
			incref(presult->ct_typ);
		} else {
			/* Fallback: Lookup a typename. */
			struct cmodsyminfo csym;
			struct ctyperef dw_type;
			kwd_str = self->c_tokstart;
			kwd_len = cparser_toklen(self);
			result  = cmod_syminfo_local(&csym, kwd_str, kwd_len, CMODSYM_DIP_NS_TYPEDEF);
			if unlikely(result != DBX_EOK) {
				if (result == DBX_ENOENT && self->c_autocom && self->c_tokend == self->c_end)
					autocomplete_types(self, kwd_str, kwd_len, CMODSYM_DIP_NS_TYPEDEF);
				goto err_nopresult;
			}
			result = ctype_from_cmodsyminfo(&csym, &dw_type);
			cmod_syminfo_local_fini(&csym);
			if unlikely(result != DBX_EOK)
				goto err_nopresult;
			presult->ct_typ  = dw_type.ct_typ;  /* Inherit reference */
			presult->ct_info = dw_type.ct_info; /* Inherit data */
			presult->ct_flags |= dw_type.ct_flags;
			yield();
		}
	}
done:
	/* Parse trailing const/volatile modifiers. */
	result = ctype_parse_cv(self, &presult->ct_flags, attrib);
	if unlikely(result != DBX_EOK)
		goto err;
	return result;
err:
	ctyperef_fini(presult);
err_nopresult:
	/* Restore the original token. */
	cparser_yieldat(self, orig_tok);
	return result;
syn:
	return DBX_ESYNTAX;
}

PRIVATE WUNUSED NONNULL((1, 2, 3)) dbx_errno_t
NOTHROW(FCALL ctype_parse_inner_prefix)(struct cparser *__restrict self,
                                        /*in:ref|out:ref*/ struct ctyperef *__restrict presult,
                                        struct ctype_attributes *__restrict attrib) {
	dbx_errno_t result;
again:
	switch (self->c_tok) {

	case '*': {
		REF struct ctype *pointer_type;
		/* Pointer indirection. */
		pointer_type = ctype_ptr(presult, dbg_current_sizeof_pointer());
		if unlikely(!pointer_type)
			goto err_nomem;
		decref(presult->ct_typ);
		ctypeinfo_fini(&presult->ct_info);
		ctypeinfo_init(&presult->ct_info);
		presult->ct_flags = CTYPEREF_FLAG_NORMAL;
		presult->ct_typ   = pointer_type; /* Inherit reference. */
		yield();
		/* Parse additional const/volatile modifiers */
		result = ctype_parse_cv(self, &presult->ct_flags, attrib);
		if unlikely(result != DBX_EOK)
			goto done;
		goto again;
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
err_nomem:
	result = DBX_ENOMEM;
	goto done;
}

PRIVATE WUNUSED NONNULL((1, 2, 3)) dbx_errno_t
NOTHROW(FCALL ctype_parse_inner_suffix)(struct cparser *__restrict self,
                                        /*in:ref|out:ref*/ struct ctyperef *__restrict presult,
                                        struct ctype_attributes *__restrict attrib) {
	dbx_errno_t result;
	switch (self->c_tok) {

	case '(': {
		/* Function type */
		size_t argc;
		struct ctyperef *argv; /* [0..argc][owned] */
		REF struct ctype *function_type;
		yield();
		argc = 0;
		argv = NULL;
		if (self->c_tok != ')') {
			if (self->c_tok == CTOKEN_TOK_DOT_DOT_DOT) {
handle_dots_in_parameter_list:
				attrib->ca_fun_cc |= CTYPE_KIND_FUNPROTO_VARARGS;
				yield();
				goto at_rparen_of_function;
			}
			if (self->c_tok == CTOKEN_TOK_KEYWORD &&
			    KWD_CHECK(self->c_tokstart, cparser_toklen(self), "void")) {
				char const *tok_start = self->c_tokstart;
				yield();
				if (self->c_tok == ')')
					goto at_rparen_of_function;
				cparser_yieldat(self, tok_start);
			}
			argv = (struct ctyperef *)dbx_malloc(sizeof(struct ctyperef));
			if unlikely(!argv)
				goto err_nomem;
			/* Parse argument types. */
			for (;;) {
				char const *argname_start;
				if ((argc + 1) > dbx_malloc_usable_size(argv) / sizeof(struct ctyperef)) {
					struct ctyperef *new_argv;
					new_argv = (struct ctyperef *)dbx_realloc(argv, (argc + 1) * sizeof(struct ctyperef));
					if unlikely(!new_argv) {
						result = DBX_ENOMEM;
						goto err_fuction_argv;
					}
					argv = new_argv;
				}
				result = ctype_eval(self, &argv[argc], &argname_start, NULL);
				if unlikely(result != DBX_EOK)
					goto err_fuction_argv;
				++argc;
				if (self->c_tok != ',')
					break;
				yield();
				if (self->c_tok == ')')
					goto at_rparen_of_function;
				if (self->c_tok == CTOKEN_TOK_DOT_DOT_DOT)
					goto handle_dots_in_parameter_list;
			}
		}
at_rparen_of_function:
		result = cparser_skip(self, ')');
		if unlikely(result != DBX_EOK) {
err_fuction_argv:
			while (argc) {
				--argc;
				ctyperef_fini(&argv[argc]);
			}
			dbx_free(argv);
			goto done;
		}
		yield(); /* Yield the ')'-token. */
		/* Parse additional attributes. */
		result = ctype_parse_attrib(self, attrib);
		if unlikely(result != DBX_EOK)
			goto err_fuction_argv;
		/* Parse any additional suffixes */
		result = ctype_parse_inner_suffix(self, presult, attrib);
		if unlikely(result != DBX_EOK)
			goto err_fuction_argv;
		/* Create the new function type */
		function_type = ctype_function(presult, argc, argv, attrib->ca_fun_cc);
		if unlikely(!function_type)
			goto err_fuction_argv;
		while (argc) {
			--argc;
			ctyperef_fini(&argv[argc]);
		}
		dbx_free(argv);
		decref(presult->ct_typ);
		ctypeinfo_fini(&presult->ct_info);
		ctypeinfo_init(&presult->ct_info);
		presult->ct_flags = CTYPEREF_FLAG_NORMAL;
		presult->ct_typ   = function_type; /* Inherit reference */
	}	break;

	case '[': {
		REF struct ctype *new_type;
		bool old_cexpr_typeonly;
		size_t array_length = 0;
		yield();
		/* Array type */
		old_cexpr_typeonly = cexpr_typeonly;
		cexpr_typeonly     = false;
		result = cexpr_pushparse(self);
		if likely(result == DBX_EOK) {
			result = cexpr_cast_simple(&ctype_size_t);
			if likely(result == DBX_EOK) {
				byte_t *data;
				result = cexpr_getdata(&data);
				if likely(result == DBX_EOK) {
					if unlikely(dbg_readmemory(data, &array_length, sizeof(array_length)) != 0)
						result = DBX_EFAULT;
					else {
						result = cparser_skip(self, ']');
					}
				}
			}
		}
		cexpr_typeonly = old_cexpr_typeonly;
		if unlikely(result != DBX_EOK)
			goto done;
		/* Parse additional attributes. */
		result = ctype_parse_attrib(self, attrib);
		if unlikely(result != DBX_EOK)
			goto done;
		/* Parse any additional suffixes */
		result = ctype_parse_inner_suffix(self, presult, attrib);
		if unlikely(result != DBX_EOK)
			goto done;
		/* Create the new array type. */
		new_type = ctype_array(presult, array_length);
		if unlikely(!new_type)
			goto err_nomem;
		decref(presult->ct_typ);
		ctypeinfo_fini(&presult->ct_info);
		ctypeinfo_init(&presult->ct_info);
		/* Propagate const/volatile/... from element type. */
		/*---presult->ct_flags = CTYPEREF_FLAG_NORMAL;---*/
		presult->ct_typ = new_type; /* Inherit reference */
	}	break;

	default:
		result = DBX_EOK;
		break;
	}
done:
	return result;
err_nomem:
	result = DBX_ENOMEM;
	goto done;
}

PUBLIC WUNUSED NONNULL((1, 2, 5)) dbx_errno_t
NOTHROW(FCALL ctype_eval_inner)(struct cparser *__restrict self,
                                /*in:ref|out:ref*/ struct ctyperef *__restrict presult,
                                char const **p_varname, size_t *p_varname_len,
                                struct ctype_attributes *__restrict attrib) {
	dbx_errno_t result;
	/* Parse the inner expression. */
	result = ctype_parse_inner_prefix(self, presult, attrib);
	if unlikely(result != DBX_EOK)
		goto done;
	switch (self->c_tok) {

	case '(': {
		/* Recursive type declaration:
		 * >> int (*foo)[42];
		 * In this case, we must first parse the trailing `[42]'
		 * before  we  can  move  on  to  the  inner   `(*foo)'! */
		struct cparser inner_parser;
		struct ctype_attributes inner_attrib;
		unsigned int recursion;
		yield();
		/* Parse leading attributes within the caller's context. */
		result = ctype_parse_attrib(self, attrib);
		if unlikely(result != DBX_EOK)
			goto done;
		memcpy(&inner_parser, self, sizeof(struct cparser));
		recursion = 0;
		for (;;) {
			if (self->c_tok == ')') {
				if (!recursion)
					break;
				--recursion;
			} else if (self->c_tok == '(') {
				++recursion;
			} else if (!self->c_tok) {
				goto syn;
			}
			yield();
		}
		inner_parser.c_end = self->c_tokstart;
		yield();
		/* At this point, we're past the matching `)'-token. */
		result = ctype_parse_inner_suffix(self, presult, attrib);
		if unlikely(result != DBX_EOK)
			goto done;
		/* Now parse the inner type-expression */
		memcpy(&inner_attrib, attrib, sizeof(inner_attrib));
		result = ctype_eval_inner(&inner_parser, presult,
		                          p_varname, p_varname_len,
		                          &inner_attrib);
	}	break;

	case CTOKEN_TOK_KEYWORD:
		/* Variable name. */
		if (p_varname) {
			*p_varname = self->c_tokstart;
			if (p_varname_len)
				*p_varname_len = cparser_toklen(self);
			yield();
		}
		ATTR_FALLTHROUGH
	default:
		if likely(result == DBX_EOK)
			result = ctype_parse_inner_suffix(self, presult, attrib);
		break;
	}
done:
	return result;
syn:
	result = DBX_ESYNTAX;
	goto done;
}


/* Parse a named type from  `self'. This function expects  that
 * `self' points at the first token of the named type on entry.
 * @return: presult:      Filled with the name type that was parsed (token from
 *                        `self' were yielded, and not point to the first token
 *                        after the returned type)
 * @param: p_varname:     When non-NULL, also parse a contained variable name, and
 *                        store its location here. If no variable name is defined,
 *                        but this argument is non-NULL, then NULL will be written
 *                        here. When `NULL', a potential variable name will not be
 *                        parsed, and if present, will result in `DBX_ESYNTAX'.
 * @param: p_varname_len: When non-NULL, store  the length of  `*p_varname' here,  but
 *                        only do so if `p_varname != NULL'. When `p_varname' is given
 *                        as `NULL', then this argument is simply ignored.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_ENOENT:  `self' does not refer to a named type.
 * @return: DBX_ESYNTAX: Syntax error. */
PUBLIC WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL ctype_eval)(struct cparser *__restrict self,
                          /*out:ref*/ struct ctyperef *__restrict presult,
                          char const **p_varname,
                          size_t *p_varname_len) {
	dbx_errno_t result;
	struct ctype_attributes attrib;
	attrib.ca_fun_cc = CTYPE_KIND_FUNPROTO_CC_DEFAULT;
	result = ctype_parse_base(self, presult, &attrib);
	if (result != DBX_EOK)
		return result;
	/* Parse the inner expression. */
	result = ctype_eval_inner(self, presult, p_varname, p_varname_len, &attrib);
	if unlikely(result != DBX_EOK)
		decref(presult->ct_typ);
	return result;
}


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_CEVAL_C */
