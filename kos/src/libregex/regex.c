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
#ifndef GUARD_LIBREGEX_REGEX_C
#define GUARD_LIBREGEX_REGEX_C 1
#define _GNU_SOURCE 1

#include "regex.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <stdbool.h>
#include <stddef.h>
#include <unicode.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#include <libregex/regex.h>


DECL_BEGIN

struct match_count_struct {
	size_t mc_min;    /* Min number of matches */
	size_t mc_max;    /* [!0][>= mc_min] Max number of matches */
	bool   mc_greedy; /* Operate in greedy mode. */
};

struct regex_data {
	size_t    matlen;     /* Match length (success-output-only). */
	char     *data_start; /* [const] Data start pointer. */
	uintptr_t flags;      /* [const] Processing flags. */
};



/* @return: * : New pattern pointer
 * @return: REGEX_ISERROR(*): Error */
PRIVATE WUNUSED NONNULL((1, 2, 3, 4)) char *CC
parse_match_count(char *__restrict pattern_iter,
                  char *__restrict pattern_end,
                  struct match_count_struct *__restrict result,
                  struct regex_data *__restrict data) {
	char *interval_error, *iterval_start;
	result->mc_min    = 1;
	result->mc_max    = 1;
	result->mc_greedy = false;
	if (pattern_iter < pattern_end) {
		char ch = *pattern_iter;
		switch (ch) {

		case '*':
			result->mc_min    = 0;
			result->mc_max    = (size_t)-1;
			result->mc_greedy = true;
check_greedy:
			++pattern_iter;
check_greedy2:
			if (*pattern_iter == '?' && !(data->flags & REGEX_FLAG_LIMITED_OPERATORS)) {
				result->mc_greedy = false;
				++pattern_iter;
			}
			break;

		case '+':
			if (data->flags & (REGEX_FLAG_LIMITED_OPERATORS | REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK))
				break;
do_plus:
			result->mc_max    = (size_t)-1;
			result->mc_greedy = true;
			goto check_greedy;

		case '?':
			if (data->flags & (REGEX_FLAG_LIMITED_OPERATORS | REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK))
				break;
do_questionmark:
			result->mc_min    = 0;
			result->mc_greedy = true;
			goto check_greedy;

		case '\\': {
			uint32_t ch32;
			if ((data->flags & (REGEX_FLAG_ESCAPED_INTERVALS |
			                    REGEX_FLAG_NO_INTERVALS)) !=
			    REGEX_FLAG_ESCAPED_INTERVALS)
				break;
			switch (pattern_iter[1]) {
			case '+':
				if (data->flags & REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK)
					goto do_plus;
				goto done;
			case '?':
				if (data->flags & REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK)
					goto do_questionmark;
				goto done;
			case '{': break;
			default: goto done;
			}
			iterval_start = pattern_iter;
			pattern_iter += 2;
			result->mc_greedy = true;
			ch32 = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
			if (ch32 == ',') {
				result->mc_min = 0;
			} else if (unicode_isdigit(ch32)) {
				/* Digit. */
				result->mc_min = unicode_getnumeric(ch32);
				for (;;) {
					if (pattern_iter >= pattern_end) {
err_eof_in_repeat_escaped:
						interval_error = (char *)REGEX_ERROR_LBRACE_UNMATCHED;
						goto handle_interval_error;
					}
					ch32 = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
					if (!unicode_isdigit(ch32))
						break;
					result->mc_min *= 10;
					result->mc_min += unicode_getnumeric(ch32);
				}
			} else {
				interval_error = (char *)REGEX_ERROR_LBRACE_NO_COMMA_OR_DECIMAL;
				goto handle_interval_error;
			}
			if (ch32 == '\\' && *pattern_iter == '}') {
				++pattern_iter;
				result->mc_max = result->mc_min;
			} else {
				if (ch32 != ',') {
					interval_error = (char *)REGEX_ERROR_LBRACE_NO_COMMA;
					goto handle_interval_error;
				}
				if (pattern_iter == pattern_end)
					goto err_eof_in_repeat_escaped;
				ch32 = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
				if (ch32 == '\\' && *pattern_iter == '}') {
					++pattern_iter;
					result->mc_max = (size_t)-1;
				} else {
					if (unicode_isdigit(ch32)) {
						result->mc_max = unicode_getnumeric(ch32);
						for (;;) {
							if (pattern_iter >= pattern_end)
								goto err_eof_in_repeat_escaped;
							ch32 = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
							if (!unicode_isdigit(ch32))
								break;
							result->mc_max *= 10;
							result->mc_max += unicode_getnumeric(ch32);
						}
					}
					if (ch32 != '\\' || *pattern_iter != '}') {
						interval_error = (char *)REGEX_ERROR_LBRACE_NO_RBRACE;
						goto handle_interval_error;
					}
					++pattern_iter;
					if (result->mc_max < result->mc_min) {
						if (data->flags & REGEX_FLAG_IGNORE_NOOP_PATTERNS) {
							size_t temp;
							temp           = result->mc_max;
							result->mc_max = result->mc_min;
							result->mc_min = temp;
						} else {
							interval_error = (char *)REGEX_ERROR_LBRACE_BOUND_ORDER;
							goto handle_interval_error;
						}
					}
					if (!result->mc_max) {
						/* Don't allow an upper bound of ZERO, which would be pointless
						 * -> Instead, force the user to not write non-sensical regex
						 *    that  would  only  slow  down  the  matching algorithm. */
						if (!(data->flags & REGEX_FLAG_IGNORE_NOOP_PATTERNS)) {
							interval_error = (char *)REGEX_ERROR_LBRACE_BOUND_UPPER_ZERO;
							goto handle_interval_error;
						}
					}
				}
			}
		}	goto check_greedy2;

		case '{': {
			uint32_t ch32;
			if (data->flags & (REGEX_FLAG_ESCAPED_INTERVALS |
			                   REGEX_FLAG_NO_INTERVALS))
				break;
			iterval_start = pattern_iter;
			result->mc_greedy = true;
			++pattern_iter;
			ch32 = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
			if (ch32 == ',') {
				result->mc_min = 0;
			} else if (unicode_isdigit(ch32)) {
				/* Digit. */
				result->mc_min = unicode_getnumeric(ch32);
				for (;;) {
					if (pattern_iter >= pattern_end) {
err_eof_in_repeat:
						interval_error = (char *)REGEX_ERROR_LBRACE_UNMATCHED;
						goto handle_interval_error;
					}
					ch32 = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
					if (!unicode_isdigit(ch32))
						break;
					result->mc_min *= 10;
					result->mc_min += unicode_getnumeric(ch32);
				}
			} else {
				interval_error = (char *)REGEX_ERROR_LBRACE_NO_COMMA_OR_DECIMAL;
				goto handle_interval_error;
			}
			if (ch32 == '}') {
				result->mc_max = result->mc_min;
			} else {
				if (ch32 != ',') {
					interval_error = (char *)REGEX_ERROR_LBRACE_NO_COMMA;
					goto handle_interval_error;
				}
				if (pattern_iter == pattern_end)
					goto err_eof_in_repeat;
				ch32 = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
				if (ch32 == '}') {
					result->mc_max = (size_t)-1;
				} else {
					if (unicode_isdigit(ch32)) {
						result->mc_max = unicode_getnumeric(ch32);
						for (;;) {
							if (pattern_iter >= pattern_end)
								goto err_eof_in_repeat;
							ch32 = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
							if (!unicode_isdigit(ch32))
								break;
							result->mc_max *= 10;
							result->mc_max += unicode_getnumeric(ch32);
						}
					}
					if (ch32 != '}') {
						interval_error = (char *)REGEX_ERROR_LBRACE_NO_RBRACE;
						goto handle_interval_error;
					}
					if (result->mc_max < result->mc_min) {
						if (data->flags & REGEX_FLAG_IGNORE_NOOP_PATTERNS) {
							size_t temp;
							temp           = result->mc_max;
							result->mc_max = result->mc_min;
							result->mc_min = temp;
						} else {
							interval_error = (char *)REGEX_ERROR_LBRACE_BOUND_ORDER;
							goto handle_interval_error;
						}
					}
					if (!result->mc_max) {
						/* Don't allow an upper bound of ZERO, which would be pointless
						 * -> Instead, force the user to not write non-sensical regex
						 *    that  would  only  slow  down  the  matching algorithm. */
						if (!(data->flags & REGEX_FLAG_IGNORE_NOOP_PATTERNS)) {
							interval_error = (char *)REGEX_ERROR_LBRACE_BOUND_UPPER_ZERO;
							goto handle_interval_error;
						}
					}
				}
			}
		}	goto check_greedy2;

		default: break;
		}
	}
done:
	return pattern_iter;
handle_interval_error:
	if (data->flags & REGEX_FLAG_IGNORE_INVALID_INTERVALS)
		return iterval_start;
	return interval_error;
}


/* @return: 0:  Not trait
 * @return: 1:  Is trait
 * @return: <0: Error */
LOCAL WUNUSED NONNULL((1)) int CC
is_character_trait(char **__restrict piter, uint32_t data_ch,
                   bool isngore_casing) {
	char *iter = *piter;
	char temp = *iter++;
	if (temp == 'a') {
		/* [:alpha:], [:alnum:] */
		if unlikely(iter[0] != 'l')
			goto unknown;
		if (iter[1] == 'p') {
			if unlikely(iter[2] != 'h' || iter[3] != 'a' || iter[4] != ':')
				goto unknown;
			if (unicode_isalpha(data_ch))
				return 1;
		} else if (iter[1] == 'n') {
			if unlikely(iter[2] != 'u' || iter[3] != 'm' || iter[4] != ':')
				goto unknown;
			if (unicode_isalnum(data_ch))
				return 1;
		} else {
			goto unknown;
		}
		iter += 5;
	} else if (temp == 'u') {
		/* [:upper:] */
		if unlikely(iter[0] != 'p' || iter[1] != 'p' ||
		            iter[2] != 'e' || iter[3] != 'r' || iter[4] != ':')
			goto unknown;
		if (unicode_isupper(data_ch) || (isngore_casing && unicode_islower(data_ch)))
			return 1;
		iter += 5;
	} else if (temp == 'l') {
		/* [:lower:] */
		if unlikely(iter[0] != 'o' || iter[1] != 'w' ||
		            iter[2] != 'e' || iter[3] != 'r' || iter[4] != ':')
			goto unknown;
		if (unicode_islower(data_ch) || (isngore_casing && unicode_isupper(data_ch)))
			return 1;
		iter += 5;
	} else if (temp == 'd') {
		/* [:digit:] */
		if unlikely(iter[0] != 'i' || iter[1] != 'g' ||
		            iter[2] != 'i' || iter[3] != 't' || iter[4] != ':')
			goto unknown;
		if (unicode_isdigit(data_ch))
			return 1;
		iter += 5;
	} else if (temp == 'x') {
		/* [:xdigit:] */
		if unlikely(iter[0] != 'x' || iter[1] != 'i' || iter[2] != 'g' ||
		            iter[3] != 'i' || iter[4] != 't' || iter[5] != ':')
			goto unknown;
		if (unicode_isdigit(data_ch) ||
		    (data_ch >= 'a' && data_ch <= 'f') ||
		    (data_ch >= 'A' && data_ch <= 'F'))
			return 1;
		iter += 6;
	} else if (temp == 's') {
		/* [:space:] */
		if unlikely(iter[0] != 'p' || iter[1] != 'a' ||
		            iter[2] != 'c' || iter[3] != 'e' || iter[4] != ':')
			goto unknown;
		if (unicode_isspace(data_ch))
			return 1;
		iter += 5;
	} else if (temp == 'p') {
		/* [:print:], [:punct:] */
		if (iter[0] == 'r') {
			if unlikely(iter[1] != 'i' || iter[2] != 'n' ||
			            iter[3] != 't' || iter[4] != ':')
				goto unknown;
			if (data_ch <= 0xff && isprint((int)data_ch))
				return 1;
		} else if (iter[0] == 'u') {
			if unlikely(iter[1] != 'n' || iter[2] != 'c' ||
			            iter[3] != 't' || iter[4] != ':')
				goto unknown;
			if (data_ch <= 0xff && ispunct((int)data_ch))
				return 1;
		} else {
			goto unknown;
		}
		iter += 5;
	} else if (temp == 'g') {
		/* [:graph:] */
		if unlikely(iter[0] != 'r' || iter[1] != 'a' ||
		            iter[2] != 'p' || iter[3] != 'h' || iter[4] != ':')
			goto unknown;
		if (data_ch <= 0xff && isgraph((int)data_ch))
			return 1;
	} else if (temp == 'c') {
		/* [:cntrl:] */
		if unlikely(iter[0] != 'n' || iter[1] != 't' ||
		            iter[2] != 'r' || iter[3] != 'l' || iter[4] != ':')
			goto unknown;
		if (unicode_iscntrl(data_ch))
			return 1;
		iter += 5;
	} else {
unknown:
		return REGEX_ERROR_UNKNOWN_CHARACTER_TRAIT;
	}
	*piter = iter;
	return 0;
}


/* @return: 0:  Not in range
 * @return: 1:  Is in range
 * @return: <0: Error */
LOCAL WUNUSED NONNULL((1, 2, 4)) int CC
is_in_range(char *range_start, char *range_end,
            uint32_t data_ch, struct regex_data *__restrict data) {
	int error;
	char *iter = range_start;
	if (data->flags & REGEX_FLAG_NOCASE) {
		data_ch = unicode_tolower(data_ch);
		while (iter < range_end) {
			uint32_t ch = unicode_readutf8_n((char const **)&iter, range_end);
			if (ch == ':' && !(data->flags & REGEX_FLAG_NO_CHARACTER_CLASSES)) {
				error = is_character_trait(&iter, data_ch, false);
				if (error != 0)
					return error;
			} else if (ch == '\\' && !(data->flags & REGEX_FLAG_NO_BACKSLASH_IN_RANGES)) {
				/* Escaped character, or special group */
				ch = unicode_readutf8_n((char const **)&iter, range_end);
				switch (ch) {

				case '0' ... '9':
					if (data->flags & REGEX_FLAG_NO_BACKSLASH_DIGIT)
						goto match_single_nocase;
					if (unicode_isdigit(data_ch) &&
					    unicode_getnumeric(data_ch) == (uint8_t)(ch - '0'))
						goto ok;
					break;

				case 'd':
					if (unicode_isdigit(data_ch))
						goto ok;
					break;
				case 'D':
					if (!unicode_isdigit(data_ch))
						goto ok;
					break;
				case 's':
					if (unicode_isspace(data_ch))
						goto ok;
					break;
				case 'S':
					if (!unicode_isspace(data_ch))
						goto ok;
					break;
				case 'w':
					if (unicode_issymcont(data_ch) || unicode_issymstrt(data_ch))
						goto ok;
					break;
				case 'W':
					if (!unicode_issymcont(data_ch) && !unicode_issymstrt(data_ch))
						goto ok;
					break;
				case 'n':
					if (unicode_islf(data_ch))
						goto ok;
					break;
				case 'N':
					if (!unicode_islf(data_ch))
						goto ok;
					break;

				case 'a': ch = 0x07; goto match_single_nocase2;
				case 'b': ch = 0x08; goto match_single_nocase2;
				case 'f': ch = 0x0c; goto match_single_nocase2;
				case 'r': ch = 0x0d; goto match_single_nocase2;
				case 't': ch = 0x09; goto match_single_nocase2;
				case 'v': ch = 0x0b; goto match_single_nocase2;
				case 'e': ch = 0x1b; goto match_single_nocase2;

					/* TODO: `x' (hex-digit) */

				default:
					goto match_single_nocase;
				}
			} else if (iter[0] == '-') {
				/* Ranged match. */
				uint32_t high;
				++iter;
				high = unicode_readutf8_n((char const **)&iter, range_end);
				/* NOTE: Perform the empty-range check  for unifying case, so-as  to
				 *       only generate an error based on the pattern, but not on the
				 *       context flags. */
				if (ch > high && !(data->flags & REGEX_FLAG_ALLOW_EMPTY_RANGES))
					return REGEX_ERROR_EMPTY_RANGE;
				if (data_ch >= unicode_tolower(ch) &&
				    data_ch <= unicode_tolower(high))
					goto ok;
			} else {
				/* Fallback: match single */
match_single_nocase:
				ch = unicode_tolower(ch);
match_single_nocase2:
				if (data_ch == ch)
					goto ok;
			}
		}
	} else {
		while (iter < range_end) {
			uint32_t ch = unicode_readutf8_n((char const **)&iter, range_end);
			if (ch == ':' && !(data->flags & REGEX_FLAG_NO_CHARACTER_CLASSES)) {
				error = is_character_trait(&iter, data_ch, true);
				if (error != 0)
					return error;
			} else if (ch == '\\' && !(data->flags & REGEX_FLAG_NO_BACKSLASH_IN_RANGES)) {
				/* Escaped character, or special group */
				ch = unicode_readutf8_n((char const **)&iter, range_end);
				switch (ch) {

				case '0' ... '9':
					if (data->flags & REGEX_FLAG_NO_BACKSLASH_DIGIT)
						goto match_single;
					if (unicode_isdigit(data_ch) &&
					    unicode_getnumeric(data_ch) == (uint8_t)(ch - '0'))
						goto ok;
					break;

				case 'd':
					if (unicode_isdigit(data_ch))
						goto ok;
					break;
				case 'D':
					if (!unicode_isdigit(data_ch))
						goto ok;
					break;
				case 's':
					if (unicode_isspace(data_ch))
						goto ok;
					break;
				case 'S':
					if (!unicode_isspace(data_ch))
						goto ok;
					break;
				case 'w':
					if (unicode_issymcont(data_ch) || unicode_issymstrt(data_ch))
						goto ok;
					break;
				case 'W':
					if (!unicode_issymcont(data_ch) && !unicode_issymstrt(data_ch))
						goto ok;
					break;
				case 'n':
					if (unicode_islf(data_ch))
						goto ok;
					break;
				case 'N':
					if (!unicode_islf(data_ch))
						goto ok;
					break;

				case 'a': ch = 0x07; goto match_single;
				case 'b': ch = 0x08; goto match_single;
				case 'f': ch = 0x0c; goto match_single;
				case 'r': ch = 0x0d; goto match_single;
				case 't': ch = 0x09; goto match_single;
				case 'v': ch = 0x0b; goto match_single;
				case 'e': ch = 0x1b; goto match_single;

					/* TODO: `x' (hex-digit) */

				default:
					goto match_single;
				}
			} else if (iter[0] == '-') {
				/* Ranged match. */
				uint32_t high;
				++iter;
				high = unicode_readutf8_n((char const **)&iter, range_end);
				if (ch > high && !(data->flags & REGEX_FLAG_ALLOW_EMPTY_RANGES))
					return REGEX_ERROR_EMPTY_RANGE;
				if (data_ch >= ch && data_ch <= high)
					goto ok;
			} else {
				/* Fallback: match single */
match_single:
				if (data_ch == ch)
					goto ok;
			}
		}
	}
	return 0;
ok:
	return 1;
}


PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) char *
CC find_rparen(char const *pattern_iter, char const *pattern_end) {
	unsigned int paren_recursion = 0;
	while (pattern_iter < pattern_end) {
		char ch = *pattern_iter++;
		if (ch == '\\' && pattern_iter < pattern_end) {
			++pattern_iter;
		} else if (ch == '(') {
			++paren_recursion;
		} else if (ch == ')') {
			if (!paren_recursion)
				break;
			--paren_recursion;
		} else if (ch == '[') {
			while (pattern_iter < pattern_end) {
				ch = *pattern_iter++;
				if (ch == '\\' && pattern_iter < pattern_end) {
					++pattern_iter;
				} else if (ch == ']') {
					break;
				}
			}
		}
	}
	return (char *)pattern_iter;
}

PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) char *
CC find_rparen_escaped(char const *pattern_iter, char const *pattern_end) {
	unsigned int paren_recursion = 0;
	while (pattern_iter < pattern_end) {
		char ch = *pattern_iter++;
		if (ch == '\\' && pattern_iter < pattern_end) {
			ch = *pattern_iter++;
			if (ch == '(') {
				++paren_recursion;
			} else if (ch == ')') {
				if (!paren_recursion)
					break;
				--paren_recursion;
			}
		} else if (ch == '[') {
			while (pattern_iter < pattern_end) {
				ch = *pattern_iter++;
				if (ch == '\\' && pattern_iter < pattern_end) {
					++pattern_iter;
				} else if (ch == ']') {
					break;
				}
			}
		}
	}
	return (char *)pattern_iter;
}

/* @return: *: A pointer to the pipe-character
 * @return: NULL: No pipe */
PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2, 3)) char *
CC find_pipe(char const *pattern_iter, char const *pattern_end,
             struct regex_data const *__restrict data) {
	unsigned int paren_recursion = 0;
	if unlikely((data->flags & (REGEX_FLAG_ESCAPED_PIPE |
	                            REGEX_FLAG_LIMITED_OPERATORS)) == REGEX_FLAG_LIMITED_OPERATORS)
		return NULL; /* The pipe-operator is entirely disabled. */
	while (pattern_iter < pattern_end) {
		char ch = *pattern_iter++;
		if (ch == '\\' && pattern_iter < pattern_end) {
			ch = *pattern_iter++;
			if (ch == '|') {
				if (data->flags & REGEX_FLAG_ESCAPED_PIPE)
					goto handle_pipe;
			} else if (data->flags & REGEX_FLAG_ESCAPED_GROUPS) {
				if (ch == '(') {
					++paren_recursion;
				} else if (ch == ')') {
					--paren_recursion;
				}
			}
		} else if (ch == '|' && !(data->flags & REGEX_FLAG_ESCAPED_PIPE)) {
handle_pipe:
			if (!paren_recursion)
				return (char *)pattern_iter;
		} else if ((data->flags & REGEX_FLAG_NEWLINE_IS_PIPE) && unicode_islf(ch)) {
			if (ch == '\r' && *pattern_iter == '\n')
				++pattern_iter;
			goto handle_pipe;
		} else if (ch == '(' && !(data->flags & REGEX_FLAG_ESCAPED_GROUPS)) {
			++paren_recursion;
		} else if (ch == ')' && !(data->flags & REGEX_FLAG_ESCAPED_GROUPS)) {
			--paren_recursion;
		} else if (ch == '[') {
			while (pattern_iter < pattern_end) {
				ch = *pattern_iter++;
				if (ch == '\\' && pattern_iter < pattern_end) {
					++pattern_iter;
				} else if (ch == ']') {
					break;
				}
			}
		}
	}
	return NULL;
}


#define REGEX_CONTEXT_FNORMAL   0x0000
#define REGEX_CONTEXT_FINPAREN  0x0001
#define REGEX_CONTEXT_FEMPTYOK  0x0002 /* Empty matchesare OK */
#define regex_match(pdata_iter, data_end, ppattern_iter, pattern_end, data) \
	regex_match_impl(pdata_iter, data_end, ppattern_iter, pattern_end, data, REGEX_CONTEXT_FNORMAL)
PRIVATE NONNULL((1, 2, 3, 4, 5)) int CC
regex_match_impl(char **__restrict pdata_iter, char *data_end,
                 char **__restrict ppattern_iter, char *pattern_end,
                 struct regex_data *__restrict data,
                 unsigned int context);

PRIVATE NONNULL((1, 2, 3, 4, 5)) int CC
regex_match_or(char **__restrict pdata_iter, char *data_end,
               char *content_start,
               char *content_end,
               struct regex_data *__restrict data,
               unsigned int context) {
	int error;
	assert(context & REGEX_CONTEXT_FINPAREN);
	for (;;) {
		error = regex_match_impl(pdata_iter, data_end,
		                         &content_start, content_end,
		                         data, context);
		if (error != 0)
			break; /* Error, or success. */
		/* Search for the next variant. */
		content_start = find_pipe(content_start, content_end, data);
		if (!content_start)
			break;
	}
	return error;
}

/* @return: 0:                Success
 * @return: REGEX_ISERROR(*): Error */
PRIVATE NONNULL((1, 2, 3)) int CC
parse_u8(char **__restrict ppattern_iter, char *pattern_end,
         uint8_t *__restrict result) {
	bool is_first = true;
	*result       = 0;
	while (*ppattern_iter < pattern_end) {
		char *prev_piter;
		uint32_t ch;
		prev_piter = *ppattern_iter;
		ch         = unicode_readutf8_n((char const **)ppattern_iter, pattern_end);
		if (!unicode_isdigit(ch)) {
			*ppattern_iter = prev_piter;
			break;
		}
		*result *= 10;
		*result += unicode_getnumeric(ch);
		is_first = false;
	}
	if unlikely(is_first)
		return REGEX_ERROR_DIGIT_RANGE_NO_DECIMAL;
	return 0;
}


/* @return: 0:                Success
 * @return: REGEX_ISERROR(*): Error */
PRIVATE NONNULL((1, 2, 3, 4, 5)) int CC
parse_digit_range(char *pattern_iter, char *pattern_end,
                  uint8_t *__restrict plow,
                  uint8_t *__restrict phigh,
                  struct regex_data *__restrict data) {
	int error;
	bool has_low = false, has_high = false;
	while (pattern_iter < pattern_end) {
		if (!has_high && *pattern_iter == '<') {
			++pattern_iter;
			if (*pattern_iter == '=') {
				++pattern_iter;
				error = parse_u8(&pattern_iter, pattern_end, phigh);
				if unlikely(error != 0)
					goto err;
			} else {
				error = parse_u8(&pattern_iter, pattern_end, phigh);
				if unlikely(error != 0)
					goto err;
				if unlikely(!*phigh) {
					if (!(data->flags & REGEX_FLAG_IGNORE_NOOP_PATTERNS))
						return REGEX_ERROR_DIGIT_RANGE_IMPOSSIBLE;
				}
				--*phigh;
			}
			has_high = true;
			continue;
		}
		if (!has_low && *pattern_iter == '>') {
			++pattern_iter;
			if (*pattern_iter == '=') {
				++pattern_iter;
				error = parse_u8(&pattern_iter, pattern_end, plow);
				if unlikely(error != 0)
					goto err;
			} else {
				error = parse_u8(&pattern_iter, pattern_end, plow);
				if unlikely(error != 0)
					goto err;
				if unlikely(*plow == 0xff) {
					if (!(data->flags & REGEX_FLAG_IGNORE_NOOP_PATTERNS))
						return REGEX_ERROR_DIGIT_RANGE_IMPOSSIBLE;
				}
				++*plow;
			}
			has_low = true;
			continue;
		}
		if (!has_low && !has_high && *pattern_iter == '=') {
			++pattern_iter;
			error = parse_u8(&pattern_iter, pattern_end, plow);
			if unlikely(error != 0)
				goto err;
			*phigh = *plow;
			break;
		}
		break;
	}
	assert(pattern_iter <= pattern_end);
	if unlikely(pattern_iter < pattern_end)
		return REGEX_ERROR_DIGIT_RANGE_BADTAIL;
err:
	return error;
}



/* @param: pdata_iter: [IN] A pointer to the starting address of input data
 *                     [OUT][ON_SUCCESS] Updated to point to the end of matched data.
 *                     [OUT][ON_FAILURE] Undefined
 * @param: ppattern_iter: [IN]  A pointer to the starting address of pattern data
 *                        [OUT] Updated to point to the end of matched data.
 * @return:  1:               A match was found (success; `data->matlen' is filled in)
 * @return:  0:               No match was made (failure)
 * @return: REGEX_ISERROR(*): Error. */
PRIVATE NONNULL((1, 3, 5)) int CC
regex_match_impl(char **__restrict pdata_iter, char *data_end,
                 char **__restrict ppattern_iter, char *pattern_end,
                 struct regex_data *__restrict data,
                 unsigned int context) {
	char *new_data_iter;
	char *new_pattern_iter;
	char *data_iter = *pdata_iter;
	char *pattern_iter = *ppattern_iter;
	uint32_t ch, data_ch;
	struct match_count_struct match;
	int error;
	size_t match_count;
	size_t match_length = 0;
#define CHECK_NONGREEDY_SUFFIX()                                       \
	if (!match.mc_greedy && match_count >= match.mc_min) {             \
		/* Check if the remainder of input data can not be matched. */ \
		new_data_iter = data_iter;                                     \
		new_pattern_iter = pattern_iter;                               \
		error = regex_match_impl(&new_data_iter, data_end,             \
		                         &new_pattern_iter, pattern_end, data, \
		                         context | REGEX_CONTEXT_FEMPTYOK);    \
		if (error != 0)                                                \
			goto forward_error; /* Suffix match found! */              \
	}

	/* Match character if `expr_using_data_ch' is true */
#define DO_CHARACTERWISE_MATCH(expr_using_data_ch)                            \
	while (match_count < match.mc_max) {                                      \
		char *prev_diter;                                                     \
		CHECK_NONGREEDY_SUFFIX();                                             \
		if (data_iter >= data_end)                                            \
			break;                                                            \
		prev_diter = data_iter;                                               \
		data_ch    = unicode_readutf8_n((char const **)&data_iter, data_end); \
		if (!(expr_using_data_ch)) {                                          \
			data_iter = prev_diter;                                           \
			break;                                                            \
		}                                                                     \
		++match_count;                                                        \
		++match_length;                                                       \
	}
next:
	assert(pattern_iter <= pattern_end);
	if (pattern_iter >= pattern_end)
		goto done;
	ch          = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
	match_count = 0;
	switch (ch) {

	case '(': {
		char *rparen;
		char *content_start;
		char *content_end;
		char *variant_diter;
		char *variant_piter;
		char *suffix_piter;
		size_t variant_match_length;
		if (data->flags & REGEX_FLAG_ESCAPED_GROUPS)
			goto match_raw_character;
		rparen = find_rparen(pattern_iter, pattern_end);
		__IF0 {
do_match_lparen_escaped:
			rparen = find_rparen_escaped(pattern_iter, pattern_end);
		}
		content_start = pattern_iter;
		content_end   = rparen - 1;
		if (rparen[-1] != ')')
			++content_end;
		pattern_iter = parse_match_count(rparen, pattern_end, &match, data);
		if unlikely(REGEX_ISERROR(pattern_iter))
			return (int)(intptr_t)(uintptr_t)pattern_iter;
		assert(match.mc_min <= match.mc_max);
		if (content_start[0] == '?') {
			/* Regex extensions. */
			switch (content_start[1]) {

			case '\\':
				/* Match special character trait sub-classes (currently only digit) */
				if (data->flags & REGEX_FLAG_NO_BACKSLASH_UNICODE_DECIMAL)
					break;
				if (content_start[2] == 'd') {
					uint8_t COMPILER_IGNORE_UNINITIALIZED(low);
					uint8_t COMPILER_IGNORE_UNINITIALIZED(high);
					error = parse_digit_range(content_start + 3, content_end, &low, &high, data);
					if (error != 0)
						goto err;
					/* Match digit characters with a numerical value >= low && <= high */
					while (match_count < match.mc_max) {
						char *prev_diter;
						CHECK_NONGREEDY_SUFFIX();
						if (data_iter >= data_end)
							break;
						prev_diter = data_iter;
						data_ch    = unicode_readutf8_n((char const **)&data_iter, data_end);
						if (!unicode_isdigit(data_ch) ||
						    unicode_getnumeric(data_ch) < low ||
						    unicode_getnumeric(data_ch) > high) {
							data_iter = prev_diter;
							break;
						}
						++match_count;
						++match_length;
					}
					goto check_match;
				}
				break;


			case '<':
				if (content_start[2] != '=' && content_start[2] != '!')
					break;
				/* Positive look-behind assertion.
				 * -> Check for if parenthesis contents match before the current position. */
				content_start += 3; /* ?<= */
				if (data_iter == data->data_start) {
					/* Special case: Check if the content string can match an empty string. */
					variant_diter = data_iter;
					error = regex_match_or(&variant_diter, data_iter,
					                       content_start, content_end,
					                       data,
					                       REGEX_CONTEXT_FINPAREN |
					                       REGEX_CONTEXT_FEMPTYOK);
					if (error != 0) { /* Match or error. */
						if unlikely(REGEX_ISERROR(error))
							goto err;
						if (content_start[-1] == '!')
							goto nope;
						goto next; /* It was able to match an empty string! */
					}
				} else {
					variant_diter = data_iter - 1;
					while (variant_diter > data->data_start) {
						error = regex_match_or(&variant_diter, data_iter, /* data_end = current_data_position */
						                       content_start, content_end,
						                       data,
						                       REGEX_CONTEXT_FINPAREN |
						                       REGEX_CONTEXT_FEMPTYOK);
						if (error != 0) { /* Match or error. */
							if unlikely(REGEX_ISERROR(error))
								goto err;
							if unlikely((variant_diter != data_iter) ^ (content_start[-1] == '!'))
								goto nope; /* The match doesn't end where our datastring begins. */
							goto next;
						}
						--variant_diter;
					}
				}
				if (content_start[-1] == '!')
					goto next;
				goto nope;

			case '=':
				if unlikely(!match.mc_min) {
					/* Don't allow optional matches, which  would mean that the entire  lookahead
					 * was optional in itself. And considering that it's not meant to consume any
					 * data, it would become a no-op altogether! */
err_lookahead_must_be_nonzero:
					if (data->flags & REGEX_FLAG_IGNORE_NOOP_PATTERNS)
						goto next;
					return REGEX_ERROR_POSITIVE_LOOKAHEAD_BOUND_LOWER_ZERO;
				}
				/* Lookahead to assert that at the very leas `match.mc_min'  */
				variant_diter = data_iter;
				match_count   = 0;
				while (match_count < match.mc_min) {
					error = regex_match_or(&variant_diter, data_end,
					                       content_start + 2,
					                       content_end,
					                       data,
					                       REGEX_CONTEXT_FEMPTYOK |
					                       REGEX_CONTEXT_FINPAREN);
					if unlikely(REGEX_ISERROR(error))
						goto err;
					if (!error)
						goto nope; /* Insufficient number of matches */
					++match_count;
				}
				goto next;

			case '!':
				/* The inverse of `?=': Lookahead for a non-matching assertion
				 * Useful if you don't want to match anything x followed by y:
				 * >> print repr "foo foobar".refindall(r"foo");        // { (0, 3), (4, 7) }
				 * >> print repr "foo foobar".refindall(r"foo(?!bar)"); // { (0, 3) } */
				if unlikely(!match.mc_min)
					goto err_lookahead_must_be_nonzero;
				variant_diter = data_iter;
				match_count   = 0;
				/* Lookahead to assert that at the very leas `match.mc_min'  */
				while (match_count < match.mc_min) {
					error = regex_match_or(&variant_diter, data_end,
					                       content_start + 2,
					                       content_end,
					                       data,
					                       REGEX_CONTEXT_FEMPTYOK |
					                       REGEX_CONTEXT_FINPAREN);
					if unlikely(REGEX_ISERROR(error))
						goto err;
					if (!error)
						goto next; /* Miss-match found before it would have been too late. */
					++match_count;
				}
				goto nope; /* Too many matches... */

			case '#':
				/* Comment. */
				goto next;

			case '~': /* Invert flag meaning. */
			case 'i': /* Case-insensitive */
			case 'm': /* Multi-line */
			case 's': /* Dot matches all */
				content_start += 1;
				variant_piter = content_start;
				while (content_start < content_end) {
					bool should_invert = false;
					char flag          = *content_start++;
					uintptr_t flag_value;
					if (flag == '~') {
						should_invert = true;
						flag          = *content_start++;
					}
					switch (flag) {
					case 'i': flag_value = REGEX_FLAG_NOCASE; break;
					case 'm': flag_value = REGEX_FLAG_MULTILINE; break;
					case 's': flag_value = REGEX_FLAG_DOTLF|REGEX_FLAG_DOTNUL; break;
					default:
						return REGEX_ERROR_UNKNOWN_FLAG;
					}
					if (should_invert) {
						data->flags &= ~flag_value;
					} else {
						data->flags |= flag_value;
					}
				}
				goto next;


			default:
				break;
			}
			return REGEX_ERROR_UNKNOWN_EXTENSION;
		}

		variant_piter = content_start;
		while (variant_piter < content_end) {
			struct match_backup {
				char *mb_diter;
				size_t mb_dcount;
			};
			/* [0..match_count|ALLOC(backup_a)][owned] */
			struct match_backup *backup_v;
			size_t backup_a;
			char *variant_pstart;
			CHECK_NONGREEDY_SUFFIX();
			variant_diter  = data_iter;
			variant_pstart = variant_piter;
			error = regex_match_impl(&variant_diter, data_end,
			                         &variant_piter, content_end,
			                         data, REGEX_CONTEXT_FINPAREN);
			if unlikely(REGEX_ISERROR(error))
				goto err;
			if (error == 0) {
				/* Variant doesn't result in a match. */
				variant_piter = find_pipe(variant_piter, content_end, data);
				if (!variant_piter)
					break;
				continue;
			}
			variant_match_length = match_length;
			variant_match_length += data->matlen; /* Include the matched length from the inner match. */
			if (match.mc_max == 1) {
				/* Only a single match is allowed (Skip allocating the backup-vector) */
				suffix_piter = pattern_iter;
				error = regex_match_impl(&variant_diter, data_end,
				                         &suffix_piter, pattern_end,
				                         data, context | REGEX_CONTEXT_FEMPTYOK);
				if unlikely(REGEX_ISERROR(error))
					goto err;
				if (error) {
					data->matlen += variant_match_length;
					*ppattern_iter = suffix_piter;
					if unlikely(!data->matlen && !(context & REGEX_CONTEXT_FEMPTYOK))
						return 0;
					*pdata_iter = variant_diter;
					return 1;
				}
				if (match_count <= match.mc_min)
					break;
				continue; /* Try the next variant. */
			}

			/* Found a matching variant. - Do a greedy match
			 * with  the  remainder of  the  pattern string. */
			assert(match.mc_max >= 2);
			match_count = 1;

			if (!match.mc_greedy) { /* No need to keep a backup when not being greedy */
				backup_a = 0;
				backup_v = NULL;
			} else {
				backup_a = 4;
				backup_v = (struct match_backup *)malloc(backup_a * sizeof(struct match_backup));
				if unlikely(!backup_v) {
					backup_a = 1;
					backup_v = (struct match_backup *)malloc(backup_a * sizeof(struct match_backup));
					if unlikely(!backup_v)
						return REGEX_ERROR_BADALLOC;
				}
				backup_v[0].mb_diter  = variant_diter;
				backup_v[0].mb_dcount = variant_match_length;
			}
			while (match_count < match.mc_max) {
				char *post_variant_diter;
				if (!match.mc_greedy && match_count >= match.mc_min) {
					assert(!backup_a);
					assert(!backup_v);
					/* Check if the remainder of input data can not be matched.
					 * -> This is done as early as possible in non-greedy mode. */
					new_data_iter    = data_iter;
					new_pattern_iter = pattern_iter;
					error = regex_match_impl(&new_data_iter, data_end,
					                         &new_pattern_iter, pattern_end, data,
					                         context | REGEX_CONTEXT_FEMPTYOK);
					if (error != 0)
						goto forward_error; /* Suffix match found! */
				}

				/* Repeat the match however often is possible. */
				variant_piter      = variant_pstart;
				post_variant_diter = variant_diter;

				error = regex_match_impl(&post_variant_diter, data_end,
				                         &variant_piter, content_end,
				                         data,
				                         REGEX_CONTEXT_FINPAREN |
				                         /* Pass  EMPTYOK,  because  we check  for  that case
				                          * explicitly by jumping to `has_infinite_submatch'. */
				                         REGEX_CONTEXT_FEMPTYOK);
				if unlikely(REGEX_ISERROR(error)) {
err_backup_v:
					free(backup_v);
					goto err;
				}
				if (!error) {
#if 1 /* Allow the primary variant used for secondary matches to change. */
					/* Check if another variant could be used to match the remainder. */
					char *alt_variant_piter = content_start;
					while (alt_variant_piter < content_end) {
						char *alt_variant_diter;
						char *alt_variant_pstart;
						if (alt_variant_piter == variant_pstart) {
							/* Skip the current primary variant in this suffix-check. */
							alt_variant_piter = find_pipe(alt_variant_piter, content_end, data);
							if (!alt_variant_piter)
								break;
							continue;
						}
						alt_variant_diter = variant_diter;
						/* Check if we can use this alternative variant. */
						alt_variant_pstart = alt_variant_piter;
						error = regex_match_impl(&alt_variant_diter, data_end,
						                         &alt_variant_piter, content_end,
						                         data,
						                         REGEX_CONTEXT_FINPAREN |
						                         /* Pass  EMPTYOK,  because  we check  for  that case
						                          * explicitly by jumping to `has_infinite_submatch'. */
						                         REGEX_CONTEXT_FEMPTYOK);
						if unlikely(REGEX_ISERROR(error))
							goto err_backup_v;
						if (error) {
							if (variant_diter == alt_variant_diter)
								goto has_infinite_submatch; /* No data was parsed -> no data was matched (in this case x/0 == INF) */
							/* One of the secondary variant has just started matching.
							 * -> Set it as the new primary variant and remember this match. */
							variant_pstart     = alt_variant_pstart;
							post_variant_diter = alt_variant_diter;
							goto save_variant_match;
						}
						/* Now try the next variant. */
						alt_variant_piter = find_pipe(alt_variant_piter, content_end, data);
						if (!alt_variant_piter)
							break;
					}
#endif
					break; /* Done matching variant repetitions. */
				}
				if (variant_diter == post_variant_diter)
					goto has_infinite_submatch; /* No data was parsed -> no data was matched (in this case x/0 == INF) */
save_variant_match:
				variant_diter = post_variant_diter;
				variant_match_length += data->matlen;
				if (match.mc_greedy) {
					/* Save the new match entry, so we can undo our greediness if necessary. */
					assert(match_count <= backup_a);
					if unlikely(match_count >= backup_a) {
						size_t new_alloc = backup_a * 2;
						struct match_backup *new_vec;
						new_vec = (struct match_backup *)realloc(backup_v, new_alloc * sizeof(struct match_backup));
						if unlikely(!new_vec) {
							new_alloc = match_count + 1;
							new_vec = (struct match_backup *)realloc(backup_v, new_alloc * sizeof(struct match_backup));
							if unlikely(!new_vec) {
								error = REGEX_ERROR_BADALLOC;
								goto err_backup_v;
							}
						}
						backup_a = new_alloc;
						backup_v = new_vec;
					}
					backup_v[match_count].mb_diter  = variant_diter;
					backup_v[match_count].mb_dcount = variant_match_length;
				}
				++match_count;
			}
			/* Check if we managed to parse the minimum requirement. */
			if (match_count < match.mc_min) {
				free(backup_v);
				continue; /* Try the next variant. */
			}
has_infinite_submatch:
			if (backup_v) { /* NULL when in non-greedy mode. */
				for (;;) {
					assert(match_count);
					--match_count;
					suffix_piter  = pattern_iter;
					variant_diter = backup_v[match_count].mb_diter;
					error = regex_match_impl(&variant_diter, data_end,
					                         &suffix_piter, pattern_end,
					                         data, context | REGEX_CONTEXT_FEMPTYOK);
					if unlikely(REGEX_ISERROR(error))
						goto err_backup_v;
					if (error) {
						data->matlen += backup_v[match_count].mb_dcount;
						*ppattern_iter = suffix_piter;
						free(backup_v);
						if unlikely(!data->matlen && !(context & REGEX_CONTEXT_FEMPTYOK))
							return 0;
						*pdata_iter = variant_diter;
						return 1;
					}
					/* Don't go under the minimum number of matches. */
					if (match_count <= match.mc_min)
						break;
					/* Try to be a little less greedy */
				}
				free(backup_v);
			}
		}
		/* No matches found */
		if (!match.mc_min)
			goto next; /* No match is ok. */
		goto nope;     /* Miss-matching expression. */
	}	break;

	case '|':
		if (data->flags & (REGEX_FLAG_ESCAPED_PIPE |
		                   REGEX_FLAG_CONTEXT_DEPENDENT_GROUPS |
		                   REGEX_FLAG_LIMITED_OPERATORS))
			goto match_raw_character;
		if (context & REGEX_CONTEXT_FINPAREN)
			goto done;
		return REGEX_ERROR_PIPE_OUTSIDE_OF_PAREN;

	case ')':
		if (data->flags & (REGEX_FLAG_ESCAPED_GROUPS | REGEX_FLAG_CONTEXT_DEPENDENT_GROUPS))
			goto match_raw_character;
		return REGEX_ERROR_RPAREN_UNEXPECTED;

	case '+':
	case '?':
		if (data->flags & (REGEX_FLAG_CONTEXT_DEPENDENT_REPEAT |
		                   REGEX_FLAG_LIMITED_OPERATORS |
		                   REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK))
			goto match_raw_character;
		return REGEX_ERROR_REPEAT_UNEXPECTED;
	case '*':
		if (data->flags & REGEX_FLAG_CONTEXT_DEPENDENT_REPEAT)
			goto match_raw_character;
		return REGEX_ERROR_REPEAT_UNEXPECTED;

	case '{':
		if (data->flags & (REGEX_FLAG_ESCAPED_INTERVALS |
		                   REGEX_FLAG_CONTEXT_DEPENDENT_REPEAT |
		                   REGEX_FLAG_NO_INTERVALS))
			goto match_raw_character;
		return REGEX_ERROR_LBRACE_UNEXPECTED;

	case '}':
		if (data->flags & (REGEX_FLAG_ESCAPED_INTERVALS |
		                   REGEX_FLAG_CONTEXT_DEPENDENT_REPEAT |
		                   REGEX_FLAG_NO_INTERVALS))
			goto match_raw_character;
		return REGEX_ERROR_RBRACE_UNMATCHED;

	case ']':
		if (data->flags & REGEX_FLAG_CONTEXT_DEPENDENT_RANGES)
			goto match_raw_character;
		return REGEX_ERROR_RBRACKET_UNEXPECTED;

		/* Character trait matching */
	case '\\':
		if unlikely(pattern_iter >= pattern_end)
			return REGEX_ERROR_ESCAPE_END_OF_PATTERN;
		ch = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
		switch (ch) {
			uint16_t mask;
			uint16_t flag;

		case '+':
		case '?':
			if ((data->flags & (REGEX_FLAG_CONTEXT_DEPENDENT_REPEAT |
			                    REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK)) ==
			    REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK)
				return REGEX_ERROR_REPEAT_UNEXPECTED;
			break;

		case '(':
			if (data->flags & REGEX_FLAG_ESCAPED_GROUPS)
				goto do_match_lparen_escaped;
			break;

		case '|':
			if (data->flags & REGEX_FLAG_ESCAPED_PIPE)
				return REGEX_ERROR_PIPE_OUTSIDE_OF_PAREN;
			break;

		case ')':
			if (data->flags & REGEX_FLAG_ESCAPED_GROUPS)
				return REGEX_ERROR_RPAREN_UNEXPECTED;
			break;

		case '{':
			if ((data->flags & (REGEX_FLAG_ESCAPED_INTERVALS | REGEX_FLAG_NO_INTERVALS)) == REGEX_FLAG_ESCAPED_INTERVALS)
				return REGEX_ERROR_LBRACE_UNEXPECTED;
			break;

		case '}':
			if ((data->flags & (REGEX_FLAG_ESCAPED_INTERVALS | REGEX_FLAG_NO_INTERVALS)) == REGEX_FLAG_ESCAPED_INTERVALS)
				return REGEX_ERROR_RBRACE_UNMATCHED;
			break;

		case '0' ... '9': {
			uint8_t digit_value;
			if (data->flags & REGEX_FLAG_NO_BACKSLASH_DIGIT)
				break;
			pattern_iter = parse_match_count(pattern_iter, pattern_end, &match, data);
			if unlikely(REGEX_ISERROR(pattern_iter)) {
				error = (int)(intptr_t)(uintptr_t)pattern_iter;
				goto err;
			}
			digit_value = (uint8_t)(ch - '0');
			DO_CHARACTERWISE_MATCH(unicode_isdigit(data_ch) &&
			                       unicode_getnumeric(data_ch) == digit_value);
			goto check_match;
		}	break;

		case 'd':
			mask = __UNICODE_ISNUMERIC;
			flag = __UNICODE_ISNUMERIC;
match_unicode_trait:
			pattern_iter = parse_match_count(pattern_iter, pattern_end, &match, data);
			if unlikely(REGEX_ISERROR(pattern_iter)) {
				error = (int)(intptr_t)(uintptr_t)pattern_iter;
				goto err;
			}
			DO_CHARACTERWISE_MATCH((__unicode_descriptor(data_ch)->__ut_flags & mask) == flag);
			goto check_match;
		case 'D':
			mask = __UNICODE_ISNUMERIC;
			flag = 0;
			goto match_unicode_trait;
		case 's':
			mask = __UNICODE_ISSPACE;
			flag = __UNICODE_ISSPACE;
			goto match_unicode_trait;
		case 'S':
			mask = __UNICODE_ISSPACE;
			flag = 0;
			goto match_unicode_trait;
		case 'w':
			pattern_iter = parse_match_count(pattern_iter, pattern_end, &match, data);
			if unlikely(REGEX_ISERROR(pattern_iter)) {
				error = (int)(intptr_t)(uintptr_t)pattern_iter;
				goto err;
			}
			DO_CHARACTERWISE_MATCH(__unicode_descriptor(data_ch)->__ut_flags &
			                       (__UNICODE_ISALPHA | __UNICODE_ISDIGIT |
			                        __UNICODE_ISSYMSTRT | __UNICODE_ISSYMCONT));
			goto check_match;
		case 'W':
			mask = __UNICODE_ISALPHA | __UNICODE_ISDIGIT | __UNICODE_ISSYMSTRT | __UNICODE_ISSYMCONT;
			flag = 0;
			goto match_unicode_trait;

		case 'n':
			pattern_iter = parse_match_count(pattern_iter, pattern_end, &match, data);
			if unlikely(REGEX_ISERROR(pattern_iter)) {
				error = (int)(intptr_t)(uintptr_t)pattern_iter;
				goto err;
			}
			while (match_count < match.mc_max) {
				char *prev_diter;
				CHECK_NONGREEDY_SUFFIX();
				if (data_iter >= data_end)
					break;
				prev_diter = data_iter;
				data_ch    = unicode_readutf8_n((char const **)&data_iter, data_end);
				if (!unicode_islf(data_ch)) {
					data_iter = prev_diter;
					break;
				}
				if (data_ch == '\r' && data_iter < data_end && *data_iter == '\n')
					++data_iter, ++match_length; /* CRLF */
				++match_count;
				++match_length;
			}
			goto check_match;

		case 'N':
			mask = __UNICODE_ISLF;
			flag = 0;
			goto match_unicode_trait;


		case 'A':
			/* Matches only at the start of input data. */
			if (data_iter <= data->data_start)
				goto next; /* Input data start. */
			goto nope;

		case 'Z':
			/* Matches only at the end of input data. */
			if (data_iter >= data_end)
				goto next; /* Input data end. */
			goto nope;


#define IS_ALNUM_EXTENDED(ch)                                                         \
	(__unicode_descriptor(data_ch)->__ut_flags &                                      \
	 (__UNICODE_ISALPHA | __UNICODE_ISLOWER | __UNICODE_ISUPPER | __UNICODE_ISTITLE | \
	  __UNICODE_ISDIGIT | __UNICODE_ISSYMSTRT | __UNICODE_ISSYMCONT))
		case 'b':
		case 'B': {
			char *temp_diter;
			/* Matches only at the start or end of a word */
			if (data_iter <= data->data_start)
				goto next; /* Input data start -> start of a word */
			/* Check what the previous character was */
			temp_diter = data_iter;
			data_ch    = unicode_readutf8_rev_n((char const **)&temp_diter, data->data_start);
			if (IS_ALNUM_EXTENDED(data_ch) ^ (ch == 'B')) { /* Allow an upper-case `B' to invert the logic. */
				/* Previous character is apart of a word.
				 * -> Check if the next data character isn't, or is at the end of input data. */
				if (data_iter >= data_end)
					goto next; /* End of input data */
				temp_diter = data_iter;
				data_ch    = unicode_readutf8_n((char const **)&temp_diter, data_end);
				if (!IS_ALNUM_EXTENDED(data_ch))
					goto next; /* The next character isn't an ALNUM */
			} else {
				/* Previous character isn't apart of a word.
				 * -> Check that the next one is! */
				if (data_iter >= data_end)
					goto nope; /* End of input data */
				temp_diter = data_iter;
				data_ch    = unicode_readutf8_n((char const **)&temp_diter, data_end);
				if (IS_ALNUM_EXTENDED(data_ch))
					goto next; /* The next character is an ALNUM */
			}
			goto nope;
		}	break;

		case 'a': ch = 0x07; goto match_raw_character;
/*		case 'b': ch = 0x08; goto match_raw_character; */
		case 'f': ch = 0x0c; goto match_raw_character;
		case 'r': ch = 0x0d; goto match_raw_character;
		case 't': ch = 0x09; goto match_raw_character;
		case 'v': ch = 0x0b; goto match_raw_character;
		case 'e': ch = 0x1b; goto match_raw_character;

			/* TODO: `x' (hex-digit) */

		default: break;
		}
		goto match_raw_character;


	case '[': {
		char *range_start;
		char *range_end;
		bool inverse_range;
		/* Character range. */
		range_start = pattern_iter;
#if 1
		if (pattern_iter < pattern_end && *pattern_iter != '\\') /* Same effect, but a bit more efficient. */
#else
		if (pattern_iter < pattern_end && *pattern_iter == ']')
#endif
		{
			/* Special case: regex requires that a ']' at the first
				 * position not be used to mark the end of a range, thus
				 * creating an empty one. The following 2 sets are the same:
				 *  - []()[{}]  // RBRACKET at the first position
				 *  - [()[\]{}] // Escaped r-bracket
				 */
			++pattern_iter;
		}
		for (;;) {
			if (pattern_iter >= pattern_end)
				return REGEX_ERROR_LBRACKET_UNMATCHED;
			if (*pattern_iter == ']')
				break;
			if (*pattern_iter == '\\' && pattern_iter + 1 < pattern_end)
				++pattern_iter;
			++pattern_iter;
		}
		range_end = pattern_iter;
		++pattern_iter; /* Skip the `]' */
		pattern_iter = parse_match_count(pattern_iter, pattern_end, &match, data);
		if unlikely(REGEX_ISERROR(pattern_iter)) {
			error = (int)(intptr_t)(uintptr_t)pattern_iter;
			goto err;
		}

		/* Match characters apart of the range. */
		inverse_range = false;
		/* Check for match inversion. */
		if (*range_start == '^') {
			inverse_range = true;
			++range_start;
		}
		while (match_count < match.mc_max) {
			char *prev_diter;
			CHECK_NONGREEDY_SUFFIX();
			if (data_iter >= data_end)
				break;
			prev_diter = data_iter;
			data_ch    = unicode_readutf8_n((char const **)&data_iter, data_end);
			error = is_in_range(range_start, range_end, data_ch, data);
			if unlikely(REGEX_ISERROR(error))
				goto err;
			if (((error != 0) ^ inverse_range) ||
			    /* Special case: Don't allow inverse ranges to catch line-feed characters
			     *               when the  `REGEX_FLAG_RANGE_NOT_NEWLINE'  flag  is  set. */
			    (inverse_range && unicode_islf(data_ch) &&
			     (data->flags & REGEX_FLAG_RANGE_NOT_NEWLINE))) {
				data_iter = prev_diter;
				break;
			}
			++match_count;
			++match_length;
		}
	}	break;

	case '.':
		pattern_iter = parse_match_count(pattern_iter, pattern_end, &match, data);
		if unlikely(REGEX_ISERROR(pattern_iter)) {
			error = (int)(intptr_t)(uintptr_t)pattern_iter;
			goto err;
		}
		if ((data->flags & (REGEX_FLAG_DOTLF | REGEX_FLAG_DOTNUL)) == (REGEX_FLAG_DOTLF | REGEX_FLAG_DOTNUL)) {
			/* Match anything (must still use a regular iteration
			 * because we must match by character, which can have
			 * different lengths in UTF-8). */
			while (match_count < match.mc_max) {
				CHECK_NONGREEDY_SUFFIX();
				if (data_iter >= data_end)
					break;
				unicode_readutf8_n((char const **)&data_iter, data_end);
				++match_length;
				++match_count;
			}
		} else if (data->flags & REGEX_FLAG_DOTLF) {
			DO_CHARACTERWISE_MATCH(data_ch != 0);
		} else if (data->flags & REGEX_FLAG_DOTNUL) {
			DO_CHARACTERWISE_MATCH(!unicode_islf(data_ch));
		} else {
			/* Search for the nearest line-feed, and return its offset */
			DO_CHARACTERWISE_MATCH(data_ch != 0 && !unicode_islf(data_ch));
		}
		break;

	case '^': {
		char *temp_diter;
		if (data->flags & REGEX_FLAG_CONTEXT_DEPENDENT_START_END &&
		    pattern_iter != *ppattern_iter + 1)
			goto match_raw_character;
		if (data_iter <= data->data_start && !(data->flags & REGEX_FLAG_NOT_BEGIN_OF_LINE))
			goto next; /* Input data start. */
		if (!(data->flags & REGEX_FLAG_MULTILINE))
			goto nope; /* Only accept line-feeds in multi-line mode. */
		/* Check if we're at the start of a line (i.e. the previous data-character was a line-feed) */
		temp_diter = data_iter;
		data_ch = unicode_readutf8_rev_n((char const **)&temp_diter,
		                                 data->data_start);
		if (unicode_islf(data_ch))
			goto next; /* Yes, it was a line-feed */
	}	goto nope;

	case '$': {
		char *temp_diter;
		if (data->flags & REGEX_FLAG_CONTEXT_DEPENDENT_START_END &&
		    pattern_iter != pattern_end)
			goto match_raw_character;
		if (data_iter >= data_end && !(data->flags & REGEX_FLAG_NOT_END_OF_LINE))
			goto next; /* Input data end. */
		if (!(data->flags & REGEX_FLAG_MULTILINE))
			goto nope; /* Only accept line-feeds in multi-line mode. */
		/* Check if we're at the end of a line (i.e. the next data-character is a line-feed) */
		temp_diter = data_iter;
		data_ch    = unicode_readutf8_n((char const **)&temp_diter, data_end);
		if (unicode_islf(data_ch))
			goto next; /* Yes, it was a line-feed */
	}	goto nope;

		/* Default: match raw characters. */
	default:
match_raw_character:
		pattern_iter = parse_match_count(pattern_iter, pattern_end, &match, data);
		if unlikely(REGEX_ISERROR(pattern_iter)) {
			error = (int)(intptr_t)(uintptr_t)pattern_iter;
			goto err;
		}
		if (data->flags & REGEX_FLAG_NOCASE) {
			ch = unicode_tolower(ch);
			DO_CHARACTERWISE_MATCH(unicode_tolower(data_ch) == ch);
		} else {
			DO_CHARACTERWISE_MATCH(data_ch == ch);
		}
		break;
	}
check_match:
	/* Check what was actually matched. */
	if (match_count < match.mc_min)
		goto nope; /* Too few matches */
	if (match.mc_greedy) {
		while (match_count > match.mc_min) {
			/* Allow matched characters to be undone. */
			new_data_iter    = data_iter;
			new_pattern_iter = pattern_iter;
			assert(match_length);
			assert(match_count);
			error = regex_match_impl(&new_data_iter, data_end,
			                         &new_pattern_iter, pattern_end,
			                         data,
			                         context |
			                         /* Suffix expressions are always allowed to be empty. */
			                         REGEX_CONTEXT_FEMPTYOK);
			if (error != 0)
				goto forward_error; /* Suffix match found! */
			/* Try to be a little bit less greedy */
			unicode_readutf8_rev_n((char const **)&data_iter, *pdata_iter);
			--match_length;
			--match_count;
		}
	}
	goto next;
done:
	if unlikely(!match_length && !(context & REGEX_CONTEXT_FEMPTYOK))
		goto nope; /* Don't allow empty matches. */
	*ppattern_iter = pattern_iter;
	*pdata_iter    = data_iter;
	data->matlen   = match_length;
	return 1;
nope:
	*ppattern_iter = pattern_iter;
	return 0;
err:
	return error;
forward_error:
	*ppattern_iter = new_pattern_iter;
	data->matlen += match_length;
	if unlikely(!data->matlen && !(context & REGEX_CONTEXT_FEMPTYOK))
		return 0;
	*pdata_iter = new_data_iter;
	return error;
}



/* Given a regular expression `pattern', check if it
 * matches the string found in `data', returning the
 * number of bytes in `data' that are being matched,
 * or `0' if the pattern doesn't match.
 * @param: datalen:           Number of bytes (not characters) in data.
 * @param: patternlen:        Number of bytes (not characters) in pattern.
 * @return: * :               Number of characters (not bytes) matched in `data'.
 * @return: 0 :               Pattern not found.
 * @return: REGEX_ISERROR(*): Error. */
INTERN NONNULL((1, 3)) size_t CC
libregex_matches(/*utf-8*/ char const *__restrict data, size_t datalen,
                 /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                 uintptr_t flags) {
	struct regex_data rdat;
	int error;
	assert(datalen != (size_t)-1);
	assert(patternlen != (size_t)-1);
	rdat.data_start = (char *)data;
	rdat.flags      = flags;
	error = regex_match((char **)&data, (char *)data + datalen,
	                    (char **)&pattern, (char *)pattern + patternlen,
	                    &rdat);
	if unlikely(REGEX_ISERROR(error))
		return (size_t)(ssize_t)error;
	if unlikely(error == 0)
		return 0;
	return rdat.matlen;
}


/* Same as `regex_matches()',  but also  store a  pointer to  the end  of
 * consumed data in `pdataend'. Because input data is formatted in UTF-8,
 * this position would only be equal to `data + return' if all input data
 * was ASCII  only, meaning  that in  the universal  case, this  function
 * becomes useful when dealing with unicode data.
 * @param: pdataend:          Upon success (return != 0 && return != (size_t)-1),
 *                            save a pointer  to the end  of consumed data  here.
 * @param: datalen:           Number of bytes (not characters) in data.
 * @param: patternlen:        Number of bytes (not characters) in pattern.
 * @return: * :               Number of characters (not bytes) matched in `data'.
 * @return: 0 :               Pattern not found.
 * @return: REGEX_ISERROR(*): Error. */
INTERN NONNULL((1, 3, 5)) size_t CC
libregex_matchesptr(/*utf-8*/ char const *__restrict data, size_t datalen,
                    /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                    /*utf-8*/ char const **__restrict pdataend,
                    uintptr_t flags) {
	struct regex_data rdat;
	int error;
	assert(datalen != (size_t)-1);
	assert(patternlen != (size_t)-1);
	rdat.data_start = (char *)data;
	rdat.flags      = flags;
	error = regex_match((char **)&data, (char *)data + datalen,
	                    (char **)&pattern, (char *)pattern + patternlen,
	                    &rdat);
	if unlikely(REGEX_ISERROR(error))
		return (size_t)(ssize_t)error;
	if unlikely(error == 0)
		return 0;
	*pdataend = data;
	return rdat.matlen;
}



LOCAL ATTR_CONST WUNUSED bool CC is_regex_special(char ch, uintptr_t flags) {
	switch (ch) {

	case '{':
	case '}':
		if (!(flags & (REGEX_FLAG_CONTEXT_DEPENDENT_REPEAT |
		               REGEX_FLAG_ESCAPED_INTERVALS |
		               REGEX_FLAG_NO_INTERVALS)))
			return true;
		break;

	case '(':
		if (!(flags & REGEX_FLAG_ESCAPED_GROUPS))
			return true;
		break;
	case '|':
		if (!(flags & (REGEX_FLAG_CONTEXT_DEPENDENT_GROUPS |
		               REGEX_FLAG_ESCAPED_PIPE |
		               REGEX_FLAG_LIMITED_OPERATORS)))
			return true;
		break;
	case ')':
		if (!(flags & (REGEX_FLAG_CONTEXT_DEPENDENT_GROUPS |
		               REGEX_FLAG_ESCAPED_GROUPS)))
			return true;
		break;

	case '+':
	case '?':
		if (!(flags & (REGEX_FLAG_CONTEXT_DEPENDENT_REPEAT |
		               REGEX_FLAG_LIMITED_OPERATORS |
		               REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK)))
			return true;
		break;
	case '*':
		if (!(flags & REGEX_FLAG_CONTEXT_DEPENDENT_REPEAT))
			return true;
		break;

	case '.':
	case '^':
	case '$':
	case '[':
	case ']':
	case '\\':
		return true;

	default: break;
	}
	return false;
}

LOCAL ATTR_CONST WUNUSED bool CC is_regex_suffix(char ch, uintptr_t flags) {
	switch (ch) {

	case '{':
		if (!(flags & (REGEX_FLAG_ESCAPED_INTERVALS |
		               REGEX_FLAG_NO_INTERVALS)))
			return true;
		break;

	case '+':
	case '?':
		if (!(flags & (REGEX_FLAG_LIMITED_OPERATORS |
		               REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK)))
			return true;
		break;

	case '*':
		return true;

	default: break;
	}
	return false;
}


/* Find  the   first  instance   matching  `pattern'   and  store   the
 * character indices (not byte offsets) in `*pstart' and `*pattern_end'
 * @return: 1:                Pattern was found.
 * @return: 0:                Pattern not found.
 * @return: REGEX_ISERROR(*): Error. */
INTERN NONNULL((1, 3, 5)) int CC
lilbregex_find(/*utf-8*/ char const *__restrict data, size_t datalen,
               /*utf-8*/ char const *__restrict pattern, size_t patternlen,
               struct regex_range *__restrict presult, uintptr_t flags) {
	uint32_t candidate;
	int error;
	char *pattern_iter, *pattern_end;
	char *data_iter, *data_end;
	size_t data_index = 0;
	struct regex_data rdat;
	assert(datalen != (size_t)-1);
	assert(patternlen != (size_t)-1);
	if unlikely(!patternlen)
		goto nope;
	rdat.data_start = (char *)data;
	rdat.flags      = flags;
	data_end        = (data_iter = (char *)data) + datalen;
	pattern_end     = (pattern_iter = (char *)pattern) + patternlen;
	candidate       = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
	if ((candidate > 0x7f || !is_regex_special((char)candidate, flags)) &&
	    (pattern_iter >= pattern_end || !is_regex_suffix((char)*pattern_iter, flags))) {
		/* Search for the first instance of `candidate', simplifying the entire search. */
		while (data_iter < data_end) {
			uint32_t data_ch;
			char *temp_piter;
			data_ch = unicode_readutf8_n((char const **)&data_iter, data_end);
			++data_index;
			if (data_ch != candidate)
				continue;
			if (pattern_iter >= pattern_end) {
				/* Got a match! */
				presult->rr_start = data_index - 1;
				presult->rr_end   = data_index;
				return 1;
			}
			temp_piter = pattern_iter;
			error = regex_match(&data_iter, data_end,
			                    &temp_piter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				presult->rr_start = data_index - 1;
				presult->rr_end   = data_index + rdat.matlen;
				return 1;
			}
		}
	} else {
		/* Fallback: to a manual search on each character individually. */
		while (data_iter < data_end) {
			pattern_iter = (char *)pattern;
			error = regex_match(&data_iter, data_end,
			                    &pattern_iter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				presult->rr_start = data_index;
				presult->rr_end   = data_index + rdat.matlen;
				return 1;
			}
			/* Try again with the next data-character. */
			unicode_readutf8_n((char const **)&data_iter, data_end);
			++data_index;
		}
	}
nope:
	return 0;
err:
	return error;
}

LOCAL WUNUSED NONNULL((1, 2)) size_t CC
count_utf8_characters(char *start,
                      char *end) {
	size_t result = 0;
	while (start < end) {
		unicode_readutf8_n((char const **)&start, end);
		++result;
	}
	return result;
}

INTERN NONNULL((1, 3, 5)) int CC
libregex_rfind(/*utf-8*/ char const *__restrict data, size_t datalen,
               /*utf-8*/ char const *__restrict pattern, size_t patternlen,
               struct regex_range *__restrict presult, uintptr_t flags) {
	uint32_t candidate;
	int error;
	char *pattern_iter, *pattern_end, *data_iter, *data_end;
	struct regex_data rdat;
	assert(datalen != (size_t)-1);
	assert(patternlen != (size_t)-1);
	if unlikely(!patternlen)
		goto nope;
	rdat.data_start = (char *)data;
	rdat.flags      = flags;
	data_end = data_iter = (char *)data + datalen;
	pattern_end = (pattern_iter = (char *)pattern) + patternlen;
	candidate   = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
	if ((candidate > 0x7f || !is_regex_special((char)candidate, flags)) &&
	    (pattern_iter >= pattern_end || !is_regex_suffix((char)*pattern_iter, flags))) {
		/* Search for the first instance of `candidate', simplifying the entire search. */
		while (data_iter > (char *)data) {
			uint32_t data_ch;
			char *match_begin, *temp_piter;
			data_ch = unicode_readutf8_rev_n((char const **)&data_iter, data);
			if (data_ch != candidate)
				continue;
			if (pattern_iter >= pattern_end) {
				/* Got a match! */
				presult->rr_end   = count_utf8_characters((char *)data, data_iter);
				presult->rr_start = presult->rr_end - 1;
				return 1;
			}
			match_begin = data_iter;
			temp_piter  = pattern_iter;
			error = regex_match(&data_iter, data_end,
			                    &temp_piter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				presult->rr_start = count_utf8_characters((char *)data, match_begin);
				presult->rr_end   = presult->rr_start + rdat.matlen;
				--presult->rr_start;
				return 1;
			}
		}
	} else {
		/* Fallback: to a manual search on each character individually. */
		/* Search for the first instance of `candidate', simplifying the entire search. */
		while (data_iter > (char *)data) {
			char *match_begin;
			unicode_readutf8_rev_n((char const **)&data_iter, data);
			match_begin  = data_iter;
			pattern_iter = (char *)pattern;
			error = regex_match(&data_iter, data_end,
			                    &pattern_iter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				presult->rr_start = count_utf8_characters((char *)data, match_begin);
				presult->rr_end   = presult->rr_start + rdat.matlen;
				return 1;
			}
		}
	}
nope:
	return 0;
err:
	return error;
}

/* Same as the functions above, but return both character indices _and_ pointers. */
INTERN NONNULL((1, 3, 5)) int CC
libregex_findex(/*utf-8*/ char const *__restrict data, size_t datalen,
                /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                struct regex_range_ex *__restrict presult, uintptr_t flags) {
	uint32_t candidate;
	int error;
	char *pattern_iter, *pattern_end, *data_iter, *data_end;
	size_t data_index = 0;
	struct regex_data rdat;
	assert(datalen != (size_t)-1);
	assert(patternlen != (size_t)-1);
	if unlikely(!patternlen)
		goto nope;
	rdat.data_start = (char *)data;
	rdat.flags      = flags;
	data_end        = (data_iter = (char *)data) + datalen;
	pattern_end     = (pattern_iter = (char *)pattern) + patternlen;
	candidate       = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
	if ((candidate > 0x7f || !is_regex_special((char)candidate, flags)) &&
	    (pattern_iter >= pattern_end || !is_regex_suffix((char)*pattern_iter, flags))) {
		/* Search for the first instance of `candidate', simplifying the entire search. */
		while (data_iter < data_end) {
			uint32_t data_ch;
			char *temp_piter, *data_start;
			data_start = data_iter;
			data_ch    = unicode_readutf8_n((char const **)&data_iter, data_end);
			++data_index;
			if (data_ch != candidate)
				continue;
			if (pattern_iter >= pattern_end) {
				/* Got a match! */
				presult->rr_start     = data_index - 1;
				presult->rr_end       = data_index;
				presult->rr_start_ptr = data_start;
				presult->rr_end_ptr   = data_iter;
				return 1;
			}
			temp_piter = pattern_iter;
			error = regex_match(&data_iter, data_end,
			                    &temp_piter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				presult->rr_start     = data_index - 1;
				presult->rr_end       = data_index + rdat.matlen;
				presult->rr_start_ptr = data_start;
				presult->rr_end_ptr   = data_iter;
				return 1;
			}
		}
	} else {
		/* Fallback: to a manual search on each character individually. */
		while (data_iter < data_end) {
			char *data_start = data_iter;
			pattern_iter     = (char *)pattern;
			error = regex_match(&data_iter, data_end,
			                    &pattern_iter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				presult->rr_start     = data_index;
				presult->rr_end       = data_index + rdat.matlen;
				presult->rr_start_ptr = data_start;
				presult->rr_end_ptr   = data_iter;
				return 1;
			}
			/* Try again with the next data-character. */
			unicode_readutf8_n((char const **)&data_iter, data_end);
			++data_index;
		}
	}
nope:
	return 0;
err:
	return error;
}

INTERN NONNULL((1, 3, 5)) int CC
libregex_rfindex(/*utf-8*/ char const *__restrict data, size_t datalen,
                 /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                 struct regex_range_ex *__restrict presult, uintptr_t flags) {
	uint32_t candidate;
	int error;
	char *pattern_iter, *pattern_end, *data_iter, *data_end;
	struct regex_data rdat;
	assert(datalen != (size_t)-1);
	assert(patternlen != (size_t)-1);
	if unlikely(!patternlen)
		goto nope;
	rdat.data_start = (char *)data;
	rdat.flags      = flags;
	data_end = data_iter = (char *)data + datalen;
	pattern_end          = (pattern_iter = (char *)pattern) + patternlen;
	candidate            = unicode_readutf8_n((char const **)&pattern_iter, pattern_end);
	if ((candidate > 0x7f || !is_regex_special((char)candidate, flags)) &&
	    (pattern_iter >= pattern_end || !is_regex_suffix((char)*pattern_iter, flags))) {
		/* Search for the first instance of `candidate', simplifying the entire search. */
		while (data_iter > (char *)data) {
			uint32_t data_ch;
			char *match_begin, *temp_piter;
			match_begin = data_iter;
			data_ch     = unicode_readutf8_rev_n((char const **)&data_iter, data);
			if (data_ch != candidate)
				continue;
			if (pattern_iter >= pattern_end) {
				/* Got a match! */
				presult->rr_start     = count_utf8_characters((char *)data, match_begin);
				presult->rr_end       = presult->rr_start + 1;
				presult->rr_start_ptr = match_begin;
				presult->rr_end_ptr   = data_iter;
				return 1;
			}
			temp_piter = pattern_iter;
			error = regex_match(&data_iter, data_end,
			                    &temp_piter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				presult->rr_start     = count_utf8_characters((char *)data, match_begin);
				presult->rr_end       = presult->rr_start + 1 + rdat.matlen;
				presult->rr_start_ptr = match_begin;
				presult->rr_end_ptr   = data_iter;
				return 1;
			}
		}
	} else {
		/* Fallback: to a manual search on each character individually. */
		/* Search for the first instance of `candidate', simplifying the entire search. */
		while (data_iter > (char *)data) {
			char *match_begin;
			unicode_readutf8_rev_n((char const **)&data_iter, data);
			match_begin  = data_iter;
			pattern_iter = (char *)pattern;
			error = regex_match(&data_iter, data_end,
			                    &pattern_iter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				presult->rr_start     = count_utf8_characters((char *)data, match_begin);
				presult->rr_end       = presult->rr_start + rdat.matlen;
				presult->rr_start_ptr = match_begin;
				presult->rr_end_ptr   = data_iter;
				return 1;
			}
		}
	}
nope:
	return 0;
err:
	return error;
}

INTERN NONNULL((1, 3, 5)) int CC
libregex_findptr(/*utf-8*/ char const *__restrict data, size_t datalen,
                 /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                 struct regex_range_ptr *__restrict presult, uintptr_t flags) {
	int error;
	struct regex_data rdat;
	uint8_t candidate;
	char *pattern_iter, *pattern_end, *data_end;
	assert(datalen != (size_t)-1);
	assert(patternlen != (size_t)-1);
	if unlikely(!patternlen)
		goto nope;
	rdat.data_start = (char *)data;
	rdat.flags      = flags;
	data_end        = (char *)data + datalen;
	pattern_end     = (char *)pattern + patternlen;
	candidate       = (uint8_t)*pattern;
	if (candidate <= 0x7f &&
	    (!is_regex_special((char)candidate, flags)) &&
	    (patternlen < 2 || !is_regex_suffix((char)pattern[1], flags))) {
		for (;;) {
			char *data_start, *data_iter;
			data_start = (char *)memchr(data, candidate, datalen);
			if (!data_start)
				goto nope;
			pattern_iter = (char *)pattern + 1;
			if (pattern_iter >= pattern_end) {
				/* Got a match! */
				presult->rr_start = data_start;
				presult->rr_end   = data_start + 1;
				return 1;
			}
			data_iter = data_start + 1;
			error = regex_match(&data_iter, data_end,
			                    &pattern_iter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				/* Got a match! */
				presult->rr_start = data_start;
				presult->rr_end   = data_iter;
				return 1;
			}
			data    = data_start + 1;
			datalen = (size_t)(data_end - (char *)data);
		}
	} else {
		char *data_iter = (char *)data;
		while (data_iter < data_end) {
			char *dend_ptr = data_iter;
			pattern_iter   = (char *)pattern;
			error = regex_match(&dend_ptr, data_end,
			                    &pattern_iter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				/* Got a match! */
				presult->rr_start = data_iter;
				presult->rr_end   = dend_ptr;
				return 1;
			}
			++data_iter;
		}
	}
nope:
	return 0;
err:
	return error;
}

INTERN NONNULL((1, 3, 5)) int CC
libregex_rfindptr(/*utf-8*/ char const *__restrict data, size_t datalen,
                  /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                  struct regex_range_ptr *__restrict presult, uintptr_t flags) {
	int error;
	struct regex_data rdat;
	uint8_t candidate;
	char *pattern_iter, *pattern_end, *data_end;
	assert(datalen != (size_t)-1);
	assert(patternlen != (size_t)-1);
	if unlikely(!patternlen)
		goto nope;
	rdat.data_start = (char *)data;
	rdat.flags      = flags;
	data_end        = (char *)data + datalen;
	pattern_end     = (char *)pattern + patternlen;
	candidate       = (uint8_t)*pattern;
	if (candidate <= 0x7f &&
	    (!is_regex_special((char)candidate, flags)) &&
	    (patternlen < 2 || !is_regex_suffix((char)pattern[1], flags))) {
		for (;;) {
			char *data_start, *data_iter;
			data_start = (char *)memrchr(data, candidate, datalen);
			if (!data_start)
				goto nope;
			pattern_iter = (char *)pattern + 1;
			if (pattern_iter >= pattern_end) {
				/* Got a match! */
				presult->rr_start = data_start;
				presult->rr_end   = data_start + 1;
				return 1;
			}
			data_iter = data_start + 1;
			error = regex_match(&data_iter, data_end,
			                    &pattern_iter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				/* Got a match! */
				presult->rr_start = data_start;
				presult->rr_end   = data_iter;
				return 1;
			}
			datalen = (size_t)(data_start - (char *)data);
		}
	} else {
		char *data_iter = data_end;
		while (data_iter > (char *)data) {
			char *dend_ptr;
			--data_iter;
			dend_ptr     = data_iter;
			pattern_iter = (char *)pattern;
			error = regex_match(&dend_ptr, data_end,
			                    &pattern_iter, pattern_end,
			                    &rdat);
			if (error != 0) {
				if unlikely(REGEX_ISERROR(error))
					goto err;
				/* Got a match! */
				presult->rr_start = data_iter;
				presult->rr_end   = dend_ptr;
				return 1;
			}
		}
	}
nope:
	return 0;
err:
	return error;
}




/* Exports */
DEFINE_PUBLIC_ALIAS(regex_matches, libregex_matches);
DEFINE_PUBLIC_ALIAS(regex_matchesptr, libregex_matchesptr);
DEFINE_PUBLIC_ALIAS(regex_find, libregex_find);
DEFINE_PUBLIC_ALIAS(regex_rfind, libregex_rfind);
DEFINE_PUBLIC_ALIAS(regex_findptr, libregex_findptr);
DEFINE_PUBLIC_ALIAS(regex_rfindptr, libregex_rfindptr);
DEFINE_PUBLIC_ALIAS(regex_findex, libregex_findex);
DEFINE_PUBLIC_ALIAS(regex_rfindex, libregex_rfindex);

DECL_END

#endif /* !GUARD_LIBREGEX_REGEX_C */
