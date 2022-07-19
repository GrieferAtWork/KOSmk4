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
#ifndef GUARD_LIBCMDLINE_ENCODE_C
#define GUARD_LIBCMDLINE_ENCODE_C 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <format-printer.h>
#include <string.h>
#include <unicode.h>

#include <libcmdline/encode.h>

#include "encode.h"

DECL_BEGIN

LOCAL NONNULL((1, 3, 4)) ssize_t CC
encode_escape_backslash(pformatprinter printer, void *arg,
                        char const *arg_start,
                        char const *arg_end) {
	ssize_t temp, result = 0;
	char32_t ch;
	char const *flush_start = arg_start, *iter, *prev;
	for (iter = prev = arg_start; (ch = unicode_readutf8_n(&iter, arg_end)) != 0; prev = iter) {
		if (ch == '\\') {
			temp = (*printer)(arg, flush_start, (size_t)(prev - flush_start));
			if unlikely(temp < 0)
				goto err;
			result += temp;
			temp = (*printer)(arg, "\\", 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			flush_start = prev;
		}
	}
	if (flush_start < arg_end) {
		temp = (*printer)(arg, flush_start, (size_t)(arg_end - flush_start));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}

LOCAL NONNULL((1, 3, 4)) ssize_t CC
encode_escape_spc(pformatprinter printer, void *arg,
                  char const *arg_start,
                  char const *arg_end) {
	ssize_t temp, result = 0;
	char32_t ch;
	char const *flush_start = arg_start, *iter, *prev;
	for (iter = prev = arg_start; (ch = unicode_readutf8_n(&iter, arg_end)) != 0; prev = iter) {
		if (unicode_isspace(ch) || ch == '\\') {
			temp = (*printer)(arg, flush_start, (size_t)(prev - flush_start));
			if unlikely(temp < 0)
				goto err;
			result += temp;
			temp = (*printer)(arg, "\\", 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			flush_start = prev;
		}
	}
	if (flush_start < arg_end) {
		temp = (*printer)(arg, flush_start, (size_t)(arg_end - flush_start));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}

LOCAL NONNULL((1, 3, 4)) ssize_t CC
encode_escape_all(pformatprinter printer, void *arg,
                  char const *arg_start,
                  char const *arg_end) {
	ssize_t temp, result = 0;
	char32_t ch;
	char const *flush_start = arg_start, *iter, *prev;
	for (iter = prev = arg_start; (ch = unicode_readutf8_n(&iter, arg_end)) != 0; prev = iter) {
		if (unicode_isspace(ch) || ch == '\'' || ch == '\"' || ch == '\\') {
			temp = (*printer)(arg, flush_start, (size_t)(prev - flush_start));
			if unlikely(temp < 0)
				goto err;
			result += temp;
			temp = (*printer)(arg, "\\", 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			flush_start = prev;
		}
	}
	if (flush_start < arg_end) {
		temp = (*printer)(arg, flush_start, (size_t)(arg_end - flush_start));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}

LOCAL NONNULL((1, 3, 4)) ssize_t CC
encode_escape_q(pformatprinter printer, void *arg,
                char const *arg_start,
                char const *arg_end, char qchar) {
	ssize_t temp, result = 0;
	char32_t ch;
	char const *flush_start = arg_start, *iter, *prev;
	for (iter = prev = arg_start; (ch = unicode_readutf8_n(&iter, arg_end)) != 0; prev = iter) {
		if (ch == (char32_t)(unsigned char)qchar || ch == '\\') {
			temp = (*printer)(arg, flush_start, (size_t)(prev - flush_start));
			if unlikely(temp < 0)
				goto err;
			result += temp;
			temp = (*printer)(arg, "\\", 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			flush_start = prev;
		}
	}
	if (flush_start < arg_end) {
		temp = (*printer)(arg, flush_start, (size_t)(arg_end - flush_start));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}

LOCAL NONNULL((1, 3)) ssize_t CC
encode_quote(pformatprinter printer, void *arg,
             char const *arg_start,
             size_t arg_len, char qchar,
             unsigned int num_slash) {
	ssize_t temp, result;
	result = (*printer)(arg, &qchar, 1);
	if unlikely(result < 0)
		goto done;
	temp = num_slash ? encode_escape_backslash(printer, arg, arg_start, arg_start + arg_len)
	                 : (*printer)(arg, arg_start, arg_len);
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = (*printer)(arg, &qchar, 1);
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}

LOCAL NONNULL((1, 3, 4)) ssize_t CC
encode_escape_quote(pformatprinter printer, void *arg,
                    char const *arg_start,
                    char const *arg_end,
                    char qchar) {
	ssize_t temp, result;
	result = (*printer)(arg, &qchar, 1);
	if unlikely(result < 0)
		goto done;
	temp = encode_escape_q(printer, arg, arg_start, arg_end, qchar);
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = (*printer)(arg, &qchar, 1);
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}

/* Encode  the  given `arg_start'  argument by  escaping characters
 * that would  confuse  the  commandline  decoder,  and  print  the
 * resulting   string   using  the   given  `printer'   with  `arg'
 * The caller is still responsible to insert space-separators  with
 * a width of at least  1 space-character (' ') between  successive
 * arguments. Alternatively, you may also use `cmdline_encode()' to
 * encode an entire commandline at once.
 * @return: * : The sum of return values of `printer'
 * @return: <0: The propagation of the first negative return value of `printer' (if any) */
INTERN NONNULL((1, 3)) ssize_t CC
libcmdline_encode_argument(pformatprinter printer, void *arg,
                           char const *arg_start, size_t arg_len) {
	ssize_t result;
	char32_t ch;
	char const *iter, *arg_end;
	unsigned int num_spaces, num_dquote, num_squote, num_slash;
	/* Check for special case: Empty argument */
	if (!arg_len)
		return (*printer)(arg, "\"\"", 2);
	arg_end = arg_start + arg_len;
	num_spaces = 0; /* Number of space characters */
	num_dquote = 0; /* Number of "-characters */
	num_squote = 0; /* Number of '-characters */
	num_slash  = 0; /* Number of \-characters */
	for (iter = arg_start; (ch = unicode_readutf8_n(&iter, arg_end)) != 0; ) {
		if (unicode_isspace(ch)) {
			++num_spaces;
		} else {
			if (ch == '\'') {
				++num_squote;
			} else if (ch == '\"') {
				++num_dquote;
			} else if (ch == '\\') {
				++num_slash;
			}
		}
	}
	/* Choose the most compact encoding. */
	if (!num_squote && !num_dquote) {
		if (!num_spaces) {
			if (!num_slash) {
				/* Nothing needs to be escaped (pretty much the most likely case...) */
				result = (*printer)(arg, arg_start, arg_len);
			} else {
				result = encode_escape_backslash(printer, arg, arg_start, arg_end);
			}
		} else {
			if (num_spaces <= 1) {
				/* Only escape the space characters */
				result = encode_escape_spc(printer, arg, arg_start, arg_end);
			} else {
				/* Surround the argument with quotes (which quote is used doesn't matter for this). */
				goto escape_double_quote;
			}
		}
	} else if (!num_squote) {
		if ((num_dquote + num_spaces) < 2) {
escape_all:
			result = encode_escape_all(printer, arg, arg_start, arg_end);
		} else {
			/* Surround the argument with single quotes. */
			result = encode_quote(printer, arg, arg_start, arg_len, '\'', num_slash);
		}
	} else if (!num_dquote) {
		if ((num_squote + num_spaces) < 2)
			goto escape_all;
		/* Surround the argument with double quotes. */
escape_double_quote:
		result = encode_quote(printer, arg, arg_start, arg_len, '\"', num_slash);
	} else {
		/* Special case: If  we don't  need to escape  any space  characters,
		 * and have exactly 1 of each quotes, we can still encode the  entire
		 * argument with only 2 additional characters injected to escape both
		 * quotes.
		 * Without this check, such a string would be encoded with +3 additional
		 * characters:
		 *   encode(fo"b'ar) --> fo\"b\'ar   // This optimization
		 *                   --> "fo\"b'ar"  // What would otherwise happen
		 */
#if 1
		if (num_squote == 1 && num_dquote == 1 && !num_spaces)
			goto escape_all;
#endif
		/* There  are  both   single-quote  and  double-quote   characters
		 * If there are more ' and ", escape all ", else escape all with ' */
		if (num_squote >= num_dquote) {
			result = encode_escape_quote(printer, arg, arg_start, arg_end, '\"');
		} else {
			result = encode_escape_quote(printer, arg, arg_start, arg_end, '\'');
		}
	}
	return result;
}


/* Encode an entire commandline given by `argc' pointers found within
 * the  given  `argv'   vector.  (s.a.   `cmdline_encode_argument()')
 * @return: * : The sum of return values of `printer'
 * @return: <0: The propagation of the first negative return value of `printer' (if any) */
INTERN NONNULL((1, 4)) ssize_t CC
libcmdline_encode(pformatprinter printer, void *arg,
                  size_t argc, char const *const *argv) {
	ssize_t temp, result = 0;
	size_t i, len;
	for (i = 0; i < argc; ++i) {
		char const *arg_str;
		if (i != 0) {
			temp = (*printer)(arg, " ", 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		arg_str = argv[i];
		len     = strlen(arg_str);
		temp = libcmdline_encode_argument(printer, arg,
		                                  arg_str, len);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}


DEFINE_PUBLIC_ALIAS(cmdline_encode_argument, libcmdline_encode_argument);
DEFINE_PUBLIC_ALIAS(cmdline_encode, libcmdline_encode);

DECL_END

#endif /* !GUARD_LIBCMDLINE_ENCODE_C */
