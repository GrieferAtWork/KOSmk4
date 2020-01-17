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
#ifndef GUARD_LIBJSON_WRITER_C
#define GUARD_LIBJSON_WRITER_C 1

#include "writer.h"

#include "api.h"

#include <kos/types.h>

#include <format-printer.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unicode.h>

#include <libjson/writer.h>

DECL_BEGIN

LOCAL WUNUSED char tohex(unsigned int x) {
	return x >= 10
	       ? ('a' + (x - 10))
	       : ('0' + (x));
}

/* Json writer helper functions.
 * Note all of these have the same return value convention:
 * @return:  0: Success
 * @return: -1: Error: `self->jw_result' has a negative value when the function was called.
 * @return: -1: Error: An invocation of the `self->jw_printer' returned a negative value.
 * @return: -2: Error: Invalid usage during this, or during an earlier call. */

#define CHK_STATE()                                       \
	do {                                                  \
		if (self->jw_result < 0)                          \
			goto err;                                     \
		if (self->jw_state == JSON_WRITER_STATE_BADUSAGE) \
			return -2;                                    \
	} __WHILE0


LOCAL NONNULL((1, 2)) int CC
json_print(struct json_writer *__restrict self,
           char const *__restrict data, size_t len) {
	ssize_t error;
	error = (*self->jw_printer)(self->jw_arg, data, len);
	if unlikely(error < 0) {
		self->jw_result = error;
		return -1;
	}
	self->jw_result += error;
	return 0;
}

LOCAL NONNULL((1, 2)) int CC
json_vprintf(struct json_writer *__restrict self,
             char const *__restrict format,
             va_list args) {
	ssize_t error;
	error = format_vprintf(self->jw_printer,
	                       self->jw_arg,
	                       format,
	                       args);
	if unlikely(error < 0) {
		self->jw_result = error;
		return -1;
	}
	self->jw_result += error;
	return 0;
}

LOCAL NONNULL((1, 2)) int
json_printf(struct json_writer *__restrict self,
            char const *__restrict format,
            ...) {
	int result;
	va_list args;
	va_start(args, format);
	result = json_vprintf(self, format, args);
	va_end(args);
	return result;
}

LOCAL NONNULL((1)) int CC
json_linefeed_and_indent(struct json_writer *__restrict self) {
	if (self->jw_format == JSON_WRITER_FORMAT_PRETTY) {
		char buf[16];
		buf[0] = '\n';
		if likely(self->jw_depth <= COMPILER_LENOF(buf) - 1) {
			memset(buf + 1, '\t', self->jw_depth);
			if unlikely(json_print(self, buf, self->jw_depth + 1))
				goto err;
		} else {
			unsigned int missing;
			memset(buf + 1, '\t', COMPILER_LENOF(buf) - 1);
			if unlikely(json_print(self, buf, COMPILER_LENOF(buf)))
				goto err;
			missing = self->jw_depth - (COMPILER_LENOF(buf) - 1);
			buf[0] = '\t';
			while (missing) {
				unsigned int count = missing;
				if (count > COMPILER_LENOF(buf))
					count = COMPILER_LENOF(buf);
				if unlikely(json_print(self, buf, count))
					goto err;
				missing -= count;
			}
		}
	}
	return 0;
err:
	return -1;
}

LOCAL NONNULL((1)) int CC
json_print_prefixes(struct json_writer *__restrict self) {
	if (self->jw_state == JSON_WRITER_STATE_SIBLING) {
		if unlikely(json_print(self, ",", 1))
			goto err;
		if unlikely(json_linefeed_and_indent(self))
			goto err;
	} else if (self->jw_state == JSON_WRITER_STATE_INITIAL &&
	           self->jw_depth != 0) {
		if unlikely(json_linefeed_and_indent(self))
			goto err;
	}
	return 0;
err:
	return -1;
}


LOCAL NONNULL((1, 2)) int CC
json_begincomponent(struct json_writer *__restrict self,
                    char const *__restrict data, size_t len) {
	CHK_STATE();
	if (self->jw_state == JSON_WRITER_STATE_SIBLING) {
		if unlikely(json_print(self, ", ", self->jw_format == JSON_WRITER_FORMAT_PRETTY ? 2 : 1))
			goto err;
	}
	if unlikely(json_print(self, data, len))
		goto err;
	++self->jw_depth;
	self->jw_state = JSON_WRITER_STATE_INITIAL;
	return 0;
err:
	return -1;
}

LOCAL NONNULL((1, 2)) int CC
json_endcomponent(struct json_writer *__restrict self,
                  char const *__restrict data, size_t len) {
	CHK_STATE();
	if unlikely(self->jw_depth == 0 ||
	            self->jw_state == JSON_WRITER_STATE_ONFIELD) {
		self->jw_state = JSON_WRITER_STATE_BADUSAGE;
		return -2;
	}
	if (self->jw_state == JSON_WRITER_STATE_SIBLING) {
		--self->jw_depth;
		if unlikely(json_linefeed_and_indent(self))
			goto err;
	}
	if unlikely(json_print(self, data, len))
		goto err;
	self->jw_state = JSON_WRITER_STATE_SIBLING;
	return 0;
err:
	return -1;
}

INTERN NONNULL((1)) int CC
libjson_writer_beginobject(struct json_writer *__restrict self) {
	return json_begincomponent(self, "{", 1);
}

INTERN NONNULL((1)) int CC
libjson_writer_beginarray(struct json_writer *__restrict self) {
	return json_begincomponent(self, "[", 1);
}

INTERN NONNULL((1)) int CC
libjson_writer_endobject(struct json_writer *__restrict self) {
	return json_endcomponent(self, "}", 1);
}
INTERN NONNULL((1)) int CC
libjson_writer_endarray(struct json_writer *__restrict self) {
	return json_endcomponent(self, "]", 1);
}

LOCAL NONNULL((1)) int CC
json_print_quote(struct json_writer *__restrict self) {
	return json_print(self, "\"", 1);
}

LOCAL NONNULL((1, 2)) int CC
json_print_string(struct json_writer *__restrict self,
                  /*utf-8*/ char const *__restrict str,
                  size_t len) {
	char const *flush_start = str;
	char const *end = str + len;
	if unlikely(json_print_quote(self))
		goto err;
	while (str < end) {
		char const *temp = str;
		char32_t ch = unicode_readutf8_n((char const **)&str, end);
		if ((ch == 0x20 || ch == 0x21) ||
		    (ch >= 0x23 && ch <= 0x5b) ||
		    (ch >= 0x5d && ch <= 0x10ffff)) {
			/* Can be directly emit! */
		} else {
			/* Must escape `ch' */
			char escape_buf[10];
			size_t escape_len = 2;
			escape_buf[0] = '\\';
			switch (ch) {
				/* Characters with dedicated escape codes. */
			case 0x22: escape_buf[1] = '\"'; break;
			case 0x5c: escape_buf[1] = '\\'; break;
			case 0x2f: escape_buf[1] = '/'; break;
			case 0x08: escape_buf[1] = 'b'; break;
			case 0x0c: escape_buf[1] = 'f'; break;
			case 0x0a: escape_buf[1] = 'n'; break;
			case 0x0d: escape_buf[1] = 'r'; break;
			case 0x09: escape_buf[1] = 't'; break;
			default:
				/* General-purpose unicode character escape. */
				if (ch <= 0xffff) {
					escape_len = 6;
					escape_buf[1] = 'u';
					escape_buf[2] = tohex((ch & 0xf000) >> 12);
					escape_buf[3] = tohex((ch & 0x0f00) >> 8);
					escape_buf[4] = tohex((ch & 0x00f0) >> 4);
					escape_buf[5] = tohex((ch & 0x000f));
				} else {
					escape_len = 10;
					escape_buf[1] = 'U';
					escape_buf[2] = tohex((ch & 0xf0000000) >> 28);
					escape_buf[3] = tohex((ch & 0x0f000000) >> 24);
					escape_buf[4] = tohex((ch & 0x00f00000) >> 20);
					escape_buf[5] = tohex((ch & 0x000f0000) >> 16);
					escape_buf[6] = tohex((ch & 0x0000f000) >> 12);
					escape_buf[7] = tohex((ch & 0x00000f00) >> 8);
					escape_buf[8] = tohex((ch & 0x000000f0) >> 4);
					escape_buf[9] = tohex((ch & 0x0000000f));
				}
				break;
			}
			/* Flush unwritten data. */
			if (flush_start < temp) {
				if unlikely(json_print(self, flush_start, (size_t)(temp - flush_start)))
					goto err;
			}
			/* Print the escaped character. */
			if unlikely(json_print(self, escape_buf, escape_len))
				goto err;
			flush_start = str;
		}
	}
	if (flush_start < end) {
		if unlikely(json_print(self, flush_start, (size_t)(end - flush_start)))
			goto err;
	}
	if unlikely(json_print_quote(self))
		goto err;
	return 0;
err:
	return -1;
}


INTERN NONNULL((1, 2)) int CC
libjson_writer_addfield(struct json_writer *__restrict self,
                        /*utf-8*/ char const *__restrict key,
                        size_t keylen) {
	int error;
	CHK_STATE();
	if unlikely(self->jw_depth == 0 ||
	            self->jw_state == JSON_WRITER_STATE_ONFIELD) {
		/* Don't allow fields at the root-scope, or following another field. */
		self->jw_state = JSON_WRITER_STATE_BADUSAGE;
		return -2;
	}
	if unlikely(json_print_prefixes(self))
		goto err;
	error = json_print_string(self, key, keylen);
	if unlikely(error != 0)
		return error;
	if unlikely(json_print(self, ": ", self->jw_format == JSON_WRITER_FORMAT_PRETTY ? 2 : 1))
		goto err;
	self->jw_state = JSON_WRITER_STATE_ONFIELD;
	return 0;
err:
	return -1;
}

INTERN NONNULL((1, 2)) int CC
libjson_writer_putstring(struct json_writer *__restrict self,
                         /*utf-8*/ char const *__restrict str,
                         size_t len) {
	CHK_STATE();
	if unlikely(json_print_prefixes(self))
		goto err;
	if unlikely(json_print_string(self, str, len))
		goto err;
	self->jw_state = JSON_WRITER_STATE_SIBLING;
	return 0;
err:
	return -1;
}


INTERN NONNULL((1)) int CC
libjson_writer_putnumber(struct json_writer *__restrict self, intptr_t value) {
	CHK_STATE();
	if unlikely(json_print_prefixes(self))
		goto err;
	if unlikely(json_printf(self, "%Id", value))
		goto err;
	self->jw_state = JSON_WRITER_STATE_SIBLING;
	return 0;
err:
	return -1;
}

#if __SIZEOF_POINTER__ == 8
DEFINE_INTERN_ALIAS(libjson_writer_putint64, libjson_writer_putnumber);
#else /* __SIZEOF_POINTER__ == 8 */
INTERN NONNULL((1)) int CC
libjson_writer_putint64(struct json_writer *__restrict self, int64_t value) {
	CHK_STATE();
	if unlikely(json_print_prefixes(self))
		goto err;
	if unlikely(json_printf(self, "%I64d", value))
		goto err;
	self->jw_state = JSON_WRITER_STATE_SIBLING;
	return 0;
err:
	return -1;
}
#endif /* __SIZEOF_POINTER__ != 8 */

INTERN NONNULL((1)) int CC
libjson_writer_putuint64(struct json_writer *__restrict self, uint64_t value) {
	CHK_STATE();
	if unlikely(json_print_prefixes(self))
		goto err;
	if unlikely(json_printf(self, "%I64u", value))
		goto err;
	self->jw_state = JSON_WRITER_STATE_SIBLING;
	return 0;
err:
	return -1;
}


INTERN NONNULL((1)) int CC
libjson_writer_putfloat(struct json_writer *__restrict self,
                        double value) {
	CHK_STATE();
	if unlikely(json_print_prefixes(self))
		goto err;
	if unlikely(json_printf(self, "%f", value))
		goto err;
	self->jw_state = JSON_WRITER_STATE_SIBLING;
	return 0;
err:
	return -1;
}

LOCAL NONNULL((1)) int CC
json_putkeyword(struct json_writer *__restrict self,
                char const *__restrict kwd, size_t len) {
	CHK_STATE();
	if unlikely(json_print_prefixes(self))
		goto err;
	if unlikely(json_print(self, kwd, len))
		goto err;
	self->jw_state = JSON_WRITER_STATE_SIBLING;
	return 0;
err:
	return -1;
}

INTERN NONNULL((1)) int CC
libjson_writer_putbool(struct json_writer *__restrict self,
                       bool value) {
	int result;
	if (value) {
		result = json_putkeyword(self, "true", 4);
	} else {
		result = json_putkeyword(self, "false", 5);
	}
	return result;
}

INTERN NONNULL((1)) int CC
libjson_writer_putnull(struct json_writer *__restrict self) {
	return json_putkeyword(self, "null", 4);
}



DEFINE_PUBLIC_ALIAS(json_writer_beginobject, libjson_writer_beginobject);
DEFINE_PUBLIC_ALIAS(json_writer_beginarray, libjson_writer_beginarray);
DEFINE_PUBLIC_ALIAS(json_writer_endobject, libjson_writer_endobject);
DEFINE_PUBLIC_ALIAS(json_writer_endarray, libjson_writer_endarray);
DEFINE_PUBLIC_ALIAS(json_writer_addfield, libjson_writer_addfield);
DEFINE_PUBLIC_ALIAS(json_writer_putstring, libjson_writer_putstring);
DEFINE_PUBLIC_ALIAS(json_writer_putnumber, libjson_writer_putnumber);
DEFINE_PUBLIC_ALIAS(json_writer_putint64, libjson_writer_putint64);
DEFINE_PUBLIC_ALIAS(json_writer_putuint64, libjson_writer_putuint64);
DEFINE_PUBLIC_ALIAS(json_writer_putfloat, libjson_writer_putfloat);
DEFINE_PUBLIC_ALIAS(json_writer_putbool, libjson_writer_putbool);
DEFINE_PUBLIC_ALIAS(json_writer_putnull, libjson_writer_putnull);

DECL_END

#endif /* !GUARD_LIBJSON_WRITER_C */
