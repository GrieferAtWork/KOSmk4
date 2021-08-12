/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif([](x) -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBICONV_CONVERT_C
#define GUARD_LIBICONV_CONVERT_C 1

#include "api.h"
/**/

#include <hybrid/byteswap.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>

#include <errno.h>
#include <string.h>
#include <unicode.h>

#include <libiconv/iconv.h>

#include "convert.h"
#include "cp.h"

DECL_BEGIN

#define IS_ICONV_ERR_ERRNO(flags)   (((flags) & ICONV_ERRMASK) == ICONV_ERR_ERRNO)
#define IS_ICONV_ERR_REPLACE(flags) (((flags) & ICONV_ERRMASK) == ICONV_ERR_REPLACE)
#define IS_ICONV_ERR_IGNORE(flags)  (((flags) & ICONV_ERRMASK) == ICONV_ERR_IGNORE)


#define decode_output_printer self->icd_output.ii_printer
#define decode_output_arg     self->icd_output.ii_arg
#define decode_output(p, s)   (*decode_output_printer)(decode_output_arg, p, s)
#define encode_output_printer self->ice_output.ii_printer
#define encode_output_arg     self->ice_output.ii_arg
#define encode_output(p, s)   (*encode_output_printer)(encode_output_arg, p, s)
#define DO(expr)                         \
	do {                                 \
		if unlikely((temp = (expr)) < 0) \
			goto err;                    \
		result += temp;                  \
	}	__WHILE0
#define DO_encode_output(p, s) DO(encode_output(p, s))
#define DO_decode_output(p, s) DO(decode_output(p, s))


/************************************************************************/
/* ASCII                                                                */
/************************************************************************/
INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC libiconv_ascii_decode_errchk)(struct iconv_decode *__restrict self,
                                                           /*ASCII*/ char const *__restrict data,
                                                           size_t size) {
	ssize_t temp, result = 0;
	char const *iter, *flush_start, *end;
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
	iter        = data;
	flush_start = data;
	end         = data + size;
	while (iter < end) {
		if likely((unsigned char)*iter <= 0x7f) {
			++iter;
			continue;
		}
		DO_decode_output(flush_start, (size_t)(iter - flush_start));
		if (IS_ICONV_ERR_ERRNO(self->icd_flags))
			goto err_ilseq;
		DO_decode_output("?", 1);
		flush_start = iter + 1;
	}
	DO_decode_output(flush_start, (size_t)(end - flush_start));
	return result;
err:
	return temp;
err_ilseq:
	self->icd_flags |= ICONV_HASERR;
	errno = EILSEQ;
	return -1;
}



/* Helper macro for encode functions that enumerates input
 * UTF-8  data  by  the embedded  UTF-32  character codes:
 * >> char32_t c32;
 * >> FOREACH_UTF8(c32, self, data, size) {
 * >>     output(ENCODE(c32));
 * >> }
 */
#define FOREACH_UTF8(c32, self, data, size)                             \
	for (size_t _uni_status;;)                                          \
		if ((_uni_status = unicode_c8toc32(&(c32), data, size,          \
		                                   &(self)->ice_data.ied_utf8), \
		     0))                                                        \
			;                                                           \
		else if unlikely((ssize_t)_uni_status < 0 &&                    \
		                 (_uni_status == (size_t)-1                     \
		                  ? (IS_ICONV_ERR_ERRNO((self)->ice_flags)      \
		                     ? 1                                        \
		                     : ((c32) = '?', _uni_status = 1, 0))       \
		                  : _uni_status == (size_t)-2)) {               \
			/* Error or all data parsed. */                             \
			if unlikely(_uni_status == (size_t)-1)                      \
				goto err_ilseq; /* Error! */                            \
			break;              /* Done! */                             \
		} else if (((data) += _uni_status,                              \
		            (size) -= _uni_status, 0))                          \
			;                                                           \
		else


/************************************************************************/
/* Generic code-page                                                    */
/************************************************************************/
INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC libiconv_cp_encode)(struct iconv_encode *__restrict self,
                                                 /*utf-8*/ char const *__restrict data, size_t size) {
	char buf[64], *ptr = buf;
	ssize_t temp, result = 0;
	char32_t c32;
	struct iconv_codepage const *cp;
	if unlikely(self->ice_flags & ICONV_HASERR)
		goto err_ilseq;
	cp = self->ice_data.ied_cp.ic_cp;
	FOREACH_UTF8(c32, self, data, size) {
		/* Figure out how to encode this unicode character in this codepage. */
		size_t lo, hi;
		if (ptr >= COMPILER_ENDOF(buf)) {
			DO_encode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
		}
		lo = 0;
		hi = cp->icp_encode_max + 1;
		while (lo < hi) {
			size_t i;
			i = (lo + hi) / 2;
			if (c32 < cp->icp_encode[i].icee_uni) {
				hi = i;
			} else if (c32 > cp->icp_encode[i].icee_uni) {
				lo = i + 1;
			} else {
				/* Found it! */
				*ptr++ = (char)(unsigned char)cp->icp_encode[i].icee_cp;
				goto next_c32;
			}
		}
		/* Cannot encode :( */
		if (IS_ICONV_ERR_ERRNO(self->ice_flags)) {
			DO_encode_output(buf, (size_t)(ptr - buf));
			goto err_ilseq;
		}
		if (IS_ICONV_ERR_REPLACE(self->ice_flags))
			*ptr++ = cp->icp_replacement;
		else {
			*ptr++ = (char)(unsigned char)(uint32_t)c32;
		}
next_c32:
		;
	}
	DO_encode_output(buf, (size_t)(ptr - buf));
	return result;
err:
	return temp;
err_ilseq:
	self->ice_flags |= ICONV_HASERR;
	errno = EILSEQ;
	return -1;
}

INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC libiconv_cp_decode)(struct iconv_decode *__restrict self,
                                                 /*cp???*/ char const *__restrict data, size_t size) {
	char buf[64], *ptr = buf;
	ssize_t temp, result = 0;
	struct iconv_codepage const *cp;
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
	cp = self->icd_data.idd_cp;
	while (size) {
		char16_t c;
		if ((ptr + UNICODE_UTF8_MAXLEN) >= COMPILER_ENDOF(buf)) {
			DO_decode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
		}
		/* Decode the character via the codepage. */
		c = cp->icp_decode[(unsigned char)*data];
		if unlikely(c == 0 && *data != 0) {
			/* Invalid/undefined input byte */
			DO_decode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
			if (IS_ICONV_ERR_ERRNO(self->icd_flags))
				goto err_ilseq;
			c = '?';
			if (IS_ICONV_ERR_IGNORE(self->icd_flags))
				c = (unsigned char)*data;
		}
		ptr = unicode_writeutf8(ptr, c);
		++data;
		--size;
	}
	DO_decode_output(buf, (size_t)(ptr - buf));
	return result;
err:
	return temp;
err_ilseq:
	self->icd_flags |= ICONV_HASERR;
	errno = EILSEQ;
	return -1;
}



DECL_END

#ifndef __INTELLISENSE__
#define UTF_WIDTH     16
#define UTF_BYTEORDER 1234
#include "convert-utf.c.inl"
#define UTF_WIDTH     16
#define UTF_BYTEORDER 4321
#include "convert-utf.c.inl"
#define UTF_WIDTH     32
#define UTF_BYTEORDER 1234
#include "convert-utf.c.inl"
#define UTF_WIDTH     32
#define UTF_BYTEORDER 4321
#include "convert-utf.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_LIBICONV_CONVERT_C */
