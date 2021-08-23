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
#include <hybrid/minmax.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>

#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <unicode.h>

#include <libiconv/iconv.h>

#include "convert.h"
#include "cp-7h.h"
#include "cp-7l.h"
#include "cp-iso646.h"
#include "cp.h"
#include "iconv.h"
#include "transliterate.h"

DECL_BEGIN

#define IS_ICONV_ERR_ERRNO(flags)                     (((flags) & ICONV_ERRMASK) == ICONV_ERR_ERRNO)
#define IS_ICONV_ERR_ERROR_OR_ERRNO(flags)            (((flags) & ICONV_ERRMASK) <= ICONV_ERR_ERROR)
#define IS_ICONV_ERR_ERROR_OR_ERRNO_OR_DISCARD(flags) (((flags) & ICONV_ERRMASK) <= ICONV_ERR_DISCARD)
#define IS_ICONV_ERR_DISCARD(flags)                   (((flags) & ICONV_ERRMASK) == ICONV_ERR_DISCARD)
#define IS_ICONV_ERR_REPLACE(flags)                   (((flags) & ICONV_ERRMASK) == ICONV_ERR_REPLACE)
#define IS_ICONV_ERR_IGNORE(flags)                    (((flags) & ICONV_ERRMASK) == ICONV_ERR_IGNORE)


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





/* Helper macro for encode functions that enumerates input
 * UTF-8  data  by  the embedded  UTF-32  character codes:
 * >> char32_t c32;
 * >> FOREACH_UTF8(c32, self, data, size) {
 * >>     output(ENCODE(c32));
 * >> }
 */
#define FOREACH_UTF8(c32, self, data, size)                                            \
	for (size_t _uni_status;;)                                                         \
		if ((_uni_status = unicode_c8toc32(&(c32), data, size,                         \
		                                   &(self)->ice_data.ied_utf8),                \
		     0))                                                                       \
			;                                                                          \
		else if unlikely((ssize_t)_uni_status < 0 &&                                   \
		                 (_uni_status == (size_t)-1                                    \
		                  ? (IS_ICONV_ERR_ERROR_OR_ERRNO_OR_DISCARD((self)->ice_flags) \
		                     ? 1                                                       \
		                     : ((c32) = '?', _uni_status = 1, 0))                      \
		                  : _uni_status == (size_t)-2)) {                              \
			/* Error or all data parsed. */                                            \
			if unlikely(_uni_status == (size_t)-1) {                                   \
				if (IS_ICONV_ERR_DISCARD((self)->ice_flags)) {                         \
					(data) += 1;                                                       \
					(size) -= 1;                                                       \
					continue;                                                          \
				}                                                                      \
				goto err_ilseq; /* Error! */                                           \
			}                                                                          \
			break; /* Done! */                                                         \
		} else if (((data) += _uni_status,                                             \
		            (size) -= _uni_status, 0))                                         \
			;                                                                          \
		else


/************************************************************************/
/* UTF-* w/ BOM                                                         */
/************************************************************************/
INTERN_CONST unsigned char const libiconv_utf8_bom_seq[3] = { 0xEF, 0xBB, 0xBF };
INTERN_CONST unsigned char const libiconv_utf32le_bom_seq[4] = { 0xFF, 0xFE, 0x00, 0x00 };
INTERN_CONST unsigned char const libiconv_utf32be_bom_seq[4] = { 0x00, 0x00, 0xFE, 0xFF };
#define libiconv_utf16le_bom_seq (libiconv_utf32le_bom_seq + 0)
#define libiconv_utf16be_bom_seq (libiconv_utf32be_bom_seq + 2)

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_utf8_bom_encode(struct iconv_encode *__restrict self,
                         /*utf-8*/ char const *__restrict data, size_t size) {
	if unlikely(!self->ice_data.ied_utf_bom_printed) {
		ssize_t temp, result;
		result = encode_output((char const *)libiconv_utf8_bom_seq, 3);
		if unlikely(result < 0)
			return result;
		self->ice_data.ied_utf_bom_printed = true;
		temp = encode_output(data, size);
		if unlikely(temp < 0)
			return temp;
		return result + temp;
	}
	return encode_output(data, size);
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_utf8_bom_decode(struct iconv_decode *__restrict self,
                         /*utf-8-bom*/ char const *__restrict data, size_t size) {
	ssize_t result;
	switch (__builtin_expect(self->icd_data.idd_utf8_bom_state, _ICONV_DECODE_UTF8_BOM_TEXT)) {
	default:
		__builtin_unreachable();
	case _ICONV_DECODE_UTF8_BOM_TEXT:
default_case:
		result = decode_output(data, size);
		break;

	case _ICONV_DECODE_UTF8_BOM_B0_EF:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely((unsigned char)*data != 0xEF) {
			/* Incorrect sequence (unconditionally ignore) */
			self->icd_data.idd_utf8_bom_state = _ICONV_DECODE_UTF8_BOM_TEXT;
			goto default_case;
		}
		--size;
		++data;
		self->icd_data.idd_utf8_bom_state = _ICONV_DECODE_UTF8_BOM_B1_BB;
		ATTR_FALLTHROUGH
	case _ICONV_DECODE_UTF8_BOM_B1_BB:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely((unsigned char)*data != 0xBB) {
			ssize_t temp;
			/* Incorrect sequence (unconditionally ignore and re-emit what was already there) */
			result = decode_output((char const *)libiconv_utf8_bom_seq, 1);
			if unlikely(result < 0)
				return result;
			self->icd_data.idd_utf8_bom_state = _ICONV_DECODE_UTF8_BOM_TEXT;
			temp = decode_output(data, size);
			if unlikely(temp < 0)
				return result;
			return result + temp;
		}
		--size;
		++data;
		self->icd_data.idd_utf8_bom_state = _ICONV_DECODE_UTF8_BOM_B2_BF;
		ATTR_FALLTHROUGH
	case _ICONV_DECODE_UTF8_BOM_B2_BF:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely((unsigned char)*data != 0xBB) {
			ssize_t temp;
			/* Incorrect sequence (unconditionally ignore and re-emit what was already there) */
			result = decode_output((char const *)libiconv_utf8_bom_seq, 2);
			if unlikely(result < 0)
				return result;
			self->icd_data.idd_utf8_bom_state = _ICONV_DECODE_UTF8_BOM_TEXT;
			temp = decode_output(data, size);
			if unlikely(temp < 0)
				return result;
			return result + temp;
		}
		--size;
		++data;
		self->icd_data.idd_utf8_bom_state = _ICONV_DECODE_UTF8_BOM_TEXT;
		goto default_case;
	}
	return result;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_utf16le_bom_encode(struct iconv_encode *__restrict self,
                            /*utf-8*/ char const *__restrict data, size_t size) {
	if unlikely(!self->ice_data.ied_utf_bom_printed) {
		ssize_t temp, result;
		result = encode_output((char const *)libiconv_utf16le_bom_seq, 2);
		if unlikely(result < 0)
			return result;
		self->ice_data.ied_utf_bom_printed = true;
		temp = libiconv_utf16le_encode(self, data, size);
		if unlikely(temp < 0)
			return temp;
		return result + temp;
	}
	return libiconv_utf16le_encode(self, data, size);
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_utf16be_bom_encode(struct iconv_encode *__restrict self,
                            /*utf-8*/ char const *__restrict data, size_t size) {
	if unlikely(!self->ice_data.ied_utf_bom_printed) {
		ssize_t temp, result;
		result = encode_output((char const *)libiconv_utf16be_bom_seq, 2);
		if unlikely(result < 0)
			return result;
		self->ice_data.ied_utf_bom_printed = true;
		temp = libiconv_utf16le_encode(self, data, size);
		if unlikely(temp < 0)
			return temp;
		return result + temp;
	}
	return libiconv_utf16le_encode(self, data, size);
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_utf32le_bom_encode(struct iconv_encode *__restrict self,
                            /*utf-8*/ char const *__restrict data, size_t size) {
	if unlikely(!self->ice_data.ied_utf_bom_printed) {
		ssize_t temp, result;
		result = encode_output((char const *)libiconv_utf32le_bom_seq, 4);
		if unlikely(result < 0)
			return result;
		self->ice_data.ied_utf_bom_printed = true;
		temp = libiconv_utf16le_encode(self, data, size);
		if unlikely(temp < 0)
			return temp;
		return result + temp;
	}
	return libiconv_utf16le_encode(self, data, size);
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_utf32be_bom_encode(struct iconv_encode *__restrict self,
                            /*utf-8*/ char const *__restrict data, size_t size) {
	if unlikely(!self->ice_data.ied_utf_bom_printed) {
		ssize_t temp, result;
		result = encode_output((char const *)libiconv_utf32be_bom_seq, 4);
		if unlikely(result < 0)
			return result;
		self->ice_data.ied_utf_bom_printed = true;
		temp = libiconv_utf16le_encode(self, data, size);
		if unlikely(temp < 0)
			return temp;
		return result + temp;
	}
	return libiconv_utf16le_encode(self, data, size);
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_utf16le_bom_decode(struct iconv_decode *__restrict self,
                            /*utf-16*/ void const *__restrict data, size_t size) {
	ssize_t result;
	switch (__builtin_expect(self->icd_data.idd_utf.u_bom, _ICONV_DECODE_UTF_BOM_TEXT)) {
	default:
		__builtin_unreachable();
	case _ICONV_DECODE_UTF_BOM_TEXT:
default_case:
		result = libiconv_utf16le_decode(self, data, size);
		break;
	case _ICONV_DECODE_UTF_BOM16LE_B0_FF:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0xFF) {
			/* Incorrect sequence (unconditionally ignore) */
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			goto default_case;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM16LE_B1_FE;
		ATTR_FALLTHROUGH
	case _ICONV_DECODE_UTF_BOM16LE_B1_FE:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0xFE) {
			ssize_t temp;
			result = libiconv_utf16le_decode(self, libiconv_utf16le_bom_seq, 1);
			if unlikely(result < 0)
				return result;
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			temp = libiconv_utf16le_decode(self, data, size);
			if unlikely(temp < 0)
				return temp;
			return result + temp;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
		goto default_case;
	}
	return result;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_utf16be_bom_decode(struct iconv_decode *__restrict self,
                            /*utf-16*/ void const *__restrict data, size_t size) {
	ssize_t result;
	switch (__builtin_expect(self->icd_data.idd_utf.u_bom, _ICONV_DECODE_UTF_BOM_TEXT)) {
	default:
		__builtin_unreachable();
	case _ICONV_DECODE_UTF_BOM_TEXT:
default_case:
		result = libiconv_utf16be_decode(self, data, size);
		break;
	case _ICONV_DECODE_UTF_BOM16BE_B0_FE:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0xFE) {
			/* Incorrect sequence (unconditionally ignore) */
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			goto default_case;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM16BE_B1_FF;
		ATTR_FALLTHROUGH
	case _ICONV_DECODE_UTF_BOM16BE_B1_FF:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0xFF) {
			ssize_t temp;
			result = libiconv_utf16be_decode(self, libiconv_utf16be_bom_seq, 1);
			if unlikely(result < 0)
				return result;
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			temp = libiconv_utf16be_decode(self, data, size);
			if unlikely(temp < 0)
				return temp;
			return result + temp;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
		goto default_case;
	}
	return result;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_utf32le_bom_decode(struct iconv_decode *__restrict self,
                            /*utf-32*/ void const *__restrict data, size_t size) {
	ssize_t result;
	switch (__builtin_expect(self->icd_data.idd_utf.u_bom, _ICONV_DECODE_UTF_BOM_TEXT)) {
	default:
		__builtin_unreachable();
	case _ICONV_DECODE_UTF_BOM_TEXT:
default_case:
		result = libiconv_utf32le_decode(self, data, size);
		break;
	case _ICONV_DECODE_UTF_BOM32LE_B0_FF:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0xFF) {
			/* Incorrect sequence (unconditionally ignore) */
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			goto default_case;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM32LE_B1_FE;
		ATTR_FALLTHROUGH
	case _ICONV_DECODE_UTF_BOM32LE_B1_FE:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0xFE) {
			ssize_t temp;
			result = libiconv_utf32le_decode(self, libiconv_utf32le_bom_seq, 1);
			if unlikely(result < 0)
				return result;
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			temp = libiconv_utf32le_decode(self, data, size);
			if unlikely(temp < 0)
				return temp;
			return result + temp;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM32LE_B2_00;
		ATTR_FALLTHROUGH
	case _ICONV_DECODE_UTF_BOM32LE_B2_00:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0x00) {
			ssize_t temp;
			result = libiconv_utf32le_decode(self, libiconv_utf32le_bom_seq, 2);
			if unlikely(result < 0)
				return result;
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			temp = libiconv_utf32le_decode(self, data, size);
			if unlikely(temp < 0)
				return temp;
			return result + temp;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM32LE_B3_00;
		ATTR_FALLTHROUGH
	case _ICONV_DECODE_UTF_BOM32LE_B3_00:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0x00) {
			ssize_t temp;
			result = libiconv_utf32le_decode(self, libiconv_utf32le_bom_seq, 3);
			if unlikely(result < 0)
				return result;
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			temp = libiconv_utf32le_decode(self, data, size);
			if unlikely(temp < 0)
				return temp;
			return result + temp;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
		goto default_case;
	}
	return result;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_utf32be_bom_decode(struct iconv_decode *__restrict self,
                            /*utf-32*/ void const *__restrict data, size_t size) {
	ssize_t result;
	switch (__builtin_expect(self->icd_data.idd_utf.u_bom, _ICONV_DECODE_UTF_BOM_TEXT)) {
	default:
		__builtin_unreachable();
	case _ICONV_DECODE_UTF_BOM_TEXT:
default_case:
		result = libiconv_utf32be_decode(self, data, size);
		break;
	case _ICONV_DECODE_UTF_BOM32BE_B0_00:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0x00) {
			/* Incorrect sequence (unconditionally ignore) */
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			goto default_case;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM32BE_B1_00;
		ATTR_FALLTHROUGH
	case _ICONV_DECODE_UTF_BOM32BE_B1_00:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0x00) {
			ssize_t temp;
			result = libiconv_utf32be_decode(self, libiconv_utf32be_bom_seq, 1);
			if unlikely(result < 0)
				return result;
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			temp = libiconv_utf32be_decode(self, data, size);
			if unlikely(temp < 0)
				return temp;
			return result + temp;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM32BE_B2_FE;
		ATTR_FALLTHROUGH
	case _ICONV_DECODE_UTF_BOM32BE_B2_FE:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0xFE) {
			ssize_t temp;
			result = libiconv_utf32be_decode(self, libiconv_utf32be_bom_seq, 2);
			if unlikely(result < 0)
				return result;
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			temp = libiconv_utf32be_decode(self, data, size);
			if unlikely(temp < 0)
				return temp;
			return result + temp;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM32BE_B3_FF;
		ATTR_FALLTHROUGH
	case _ICONV_DECODE_UTF_BOM32BE_B3_FF:
		if unlikely(!size) {
			result = 0;
			break;
		}
		if unlikely(*(unsigned char const *)data != 0xFF) {
			ssize_t temp;
			result = libiconv_utf32be_decode(self, libiconv_utf32be_bom_seq, 3);
			if unlikely(result < 0)
				return result;
			self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
			temp = libiconv_utf32be_decode(self, data, size);
			if unlikely(temp < 0)
				return temp;
			return result + temp;
		}
		--size;
		data = (unsigned char const *)data + 1;
		self->icd_data.idd_utf.u_bom = _ICONV_DECODE_UTF_BOM_TEXT;
		goto default_case;
	}
	return result;
}






#if CODEC_CP_COUNT != 0
/************************************************************************/
/* Generic code-page                                                    */
/************************************************************************/
PRIVATE NONNULL((1, 2, 3)) bool FORMATPRINTER_CC
libiconv_cp_encode_buf(struct iconv_encode const *__restrict self,
                       char *__restrict result,
                       char32_t const *__restrict data, size_t len) {
	size_t i;
	struct iconv_codepage const *cp;
	cp = self->ice_data.ied_cp;
	for (i = 0; i < len; ++i) {
		/* Figure out how to encode this unicode character in this codepage. */
		size_t lo, hi;
		char32_t c32 = data[i];
		lo = 0;
		hi = cp->icp_encode_max + 1;
		for (;;) {
			size_t index;
			if (lo >= hi)
				return false; /* Cannot encode :( */
			index = (lo + hi) / 2;
			if (c32 < cp->icp_encode[index].icee_uni) {
				hi = index;
			} else if (c32 > cp->icp_encode[index].icee_uni) {
				lo = index + 1;
			} else {
				/* Found it! */
				*result++ = (char)(unsigned char)cp->icp_encode[index].icee_cp;
				break;
			}
		}
	}
	return true;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_cp_encode(struct iconv_encode *__restrict self,
                   /*utf-8*/ char const *__restrict data, size_t size) {
	char buf[64], *ptr = buf;
	ssize_t temp, result = 0;
	char32_t c32;
	struct iconv_codepage const *cp;
	if unlikely(self->ice_flags & ICONV_HASERR)
		goto err_ilseq;
	cp = self->ice_data.ied_cp;
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
		if (self->ice_flags & ICONV_ERR_TRANSLIT) {
			/* Try to transliterate the character. */
			char32_t transbuf[ICONV_TRANSLITERATE_MAXLEN];
			size_t nth, len;
			if ((ptr + ICONV_TRANSLITERATE_MAXLEN) > COMPILER_ENDOF(buf)) {
				DO_encode_output(buf, (size_t)(ptr - buf));
				ptr = buf;
			}
			for (nth = 0; (len = libiconv_transliterate(transbuf, c32, nth)) != (size_t)-1; ++nth) {
				if (libiconv_cp_encode_buf(self, ptr, transbuf, len)) {
					ptr += len;
					goto next_c32;
				}
			}
		}
		if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->ice_flags)) {
			DO_encode_output(buf, (size_t)(ptr - buf));
			size += _uni_status; /* Revert back to the start of the current character. */
			goto err_ilseq;
		}
		if (!IS_ICONV_ERR_DISCARD(self->ice_flags)) {
			if (IS_ICONV_ERR_REPLACE(self->ice_flags))
				*ptr++ = cp->icp_replacement;
			else {
				*ptr++ = (char)(unsigned char)(uint32_t)c32;
			}
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
	if (IS_ICONV_ERR_ERRNO(self->ice_flags))
		errno = EILSEQ;
	return -(ssize_t)size;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_cp_decode(struct iconv_decode *__restrict self,
                   /*cp???*/ char const *__restrict data, size_t size) {
	char buf[64], *ptr = buf;
	ssize_t temp, result = 0;
	struct iconv_codepage const *cp;
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
	cp = self->icd_data.idd_cp;
	while (size) {
		char16_t c;
		if ((ptr + UNICODE_UTF8_CURLEN) > COMPILER_ENDOF(buf)) {
			DO_decode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
		}
		/* Decode the character via the codepage. */
		c = cp->icp_decode[(unsigned char)*data];
		if unlikely(c == 0 && *data != 0) {
			/* Invalid/undefined input byte */
			DO_decode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
			if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->icd_flags))
				goto err_ilseq;
			if (IS_ICONV_ERR_DISCARD(self->icd_flags))
				goto consume_byte;
			c = '?';
			if (IS_ICONV_ERR_IGNORE(self->icd_flags))
				c = (unsigned char)*data;
		}
		ptr = unicode_writeutf8(ptr, c);
consume_byte:
		++data;
		--size;
	}
	DO_decode_output(buf, (size_t)(ptr - buf));
	return result;
err:
	return temp;
err_ilseq:
	self->icd_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->icd_flags))
		errno = EILSEQ;
	return -(ssize_t)size;
}
#endif /* CODEC_CP_COUNT != 0 */



#if CODEC_CP7L_COUNT != 0
/************************************************************************/
/* 7L-code-page encode/decode                                           */
/************************************************************************/
PRIVATE ATTR_NOINLINE NONNULL((1, 2)) bool FORMATPRINTER_CC
libiconv_cp7l_encode_buf(struct iconv_encode const *__restrict self,
                         char *__restrict result,
                         char32_t const *__restrict data, size_t len) {
	size_t i;
	struct iconv_7l_codepage const *cp;
	cp = self->ice_data.ied_cp7l;
	for (i = 0; i < len; ++i) {
		/* Figure out how to encode this unicode character in this codepage. */
		size_t lo, hi;
		char32_t c32 = data[i];
		lo = 0;
		hi = cp->i7lcp_encode_count;
		for (;;) {
			size_t index;
			if (lo >= hi)
				return false; /* Cannot encode :( */
			index = (lo + hi) / 2;
			if (c32 < cp->i7lcp_encode[index].icee_uni) {
				hi = index;
			} else if (c32 > cp->i7lcp_encode[index].icee_uni) {
				lo = index + 1;
			} else {
				/* Found it! */
				*result++ = (char)(unsigned char)cp->i7lcp_encode[index].icee_cp;
				break;
			}
		}
	}
	return true;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_cp7l_encode(struct iconv_encode *__restrict self,
                     /*utf-8*/ char const *__restrict data, size_t size) {
	char buf[64], *ptr = buf;
	ssize_t temp, result = 0;
	char32_t c32;
	struct iconv_7l_codepage const *cp;
	if unlikely(self->ice_flags & ICONV_HASERR)
		goto err_ilseq;
	cp = self->ice_data.ied_cp7l;
	FOREACH_UTF8(c32, self, data, size) {
		/* Figure out how to encode this unicode character in this codepage. */
		size_t lo, hi;
		if (ptr >= COMPILER_ENDOF(buf)) {
			DO_encode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
		}
		lo = 0;
		hi = cp->i7lcp_encode_count;
		while (lo < hi) {
			size_t i;
			i = (lo + hi) / 2;
			if (c32 < cp->i7lcp_encode[i].icee_uni) {
				hi = i;
			} else if (c32 > cp->i7lcp_encode[i].icee_uni) {
				lo = i + 1;
			} else {
				/* Found it! */
				*ptr++ = (char)(unsigned char)cp->i7lcp_encode[i].icee_cp;
				goto next_c32;
			}
		}
		/* Cannot encode :( */
		if (self->ice_flags & ICONV_ERR_TRANSLIT) {
			/* Try to transliterate the character. */
			char32_t transbuf[ICONV_TRANSLITERATE_MAXLEN];
			size_t nth, len;
			if ((ptr + ICONV_TRANSLITERATE_MAXLEN) > COMPILER_ENDOF(buf)) {
				DO_encode_output(buf, (size_t)(ptr - buf));
				ptr = buf;
			}
			for (nth = 0; (len = libiconv_transliterate(transbuf, c32, nth)) != (size_t)-1; ++nth) {
				if (libiconv_cp7l_encode_buf(self, ptr, transbuf, len)) {
					ptr += len;
					goto next_c32;
				}
			}
		}
		if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->ice_flags)) {
			DO_encode_output(buf, (size_t)(ptr - buf));
			size += _uni_status; /* Revert back to the start of the current character. */
			goto err_ilseq;
		}
		if (!IS_ICONV_ERR_DISCARD(self->ice_flags)) {
			if (IS_ICONV_ERR_REPLACE(self->ice_flags))
				*ptr++ = cp->i7lcp_replacement;
			else {
				*ptr++ = (char)(unsigned char)(uint32_t)c32;
			}
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
	if (IS_ICONV_ERR_ERRNO(self->ice_flags))
		errno = EILSEQ;
	return -(ssize_t)size;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_cp7l_decode(struct iconv_decode *__restrict self,
                     /*cp???*/ char const *__restrict data, size_t size) {
	char buf[64], *ptr = buf;
	ssize_t temp, result = 0;
	struct iconv_7l_codepage const *cp;
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
	cp = self->icd_data.idd_cp7l;
	while (size) {
		unsigned char ch;
		char16_t c16;
		if ((ptr + UNICODE_UTF8_CURLEN) > COMPILER_ENDOF(buf)) {
			DO_decode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
		}
		/* Decode the character via the codepage. */
		ch  = (unsigned char)*data;
		c16 = likely(ch <= 0x7f) ? cp->i7lcp_decode[ch] : 0;
		if unlikely(c16 == 0 && ch != 0) {
			/* Invalid/undefined input byte */
			DO_decode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
			if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->icd_flags))
				goto err_ilseq;
			if (IS_ICONV_ERR_DISCARD(self->icd_flags))
				goto consume_byte;
			c16 = '?';
			if (IS_ICONV_ERR_IGNORE(self->icd_flags))
				c16 = (unsigned char)*data;
		}
		ptr = unicode_writeutf8(ptr, c16);
consume_byte:
		++data;
		--size;
	}
	DO_decode_output(buf, (size_t)(ptr - buf));
	return result;
err:
	return temp;
err_ilseq:
	self->icd_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->icd_flags))
		errno = EILSEQ;
	return -(ssize_t)size;
}
#endif /* CODEC_CP7L_COUNT != 0 */



#if CODEC_ISO646_COUNT != 0
/************************************************************************/
/* iso646 code page encode/decode functions.                            */
/************************************************************************/
PRIVATE ATTR_NOINLINE NONNULL((1, 2)) bool FORMATPRINTER_CC
libiconv_cp646_encode_buf(struct iconv_encode const *__restrict self,
                          char *__restrict result,
                          char32_t const *__restrict data, size_t len) {
	size_t i;
	struct iconv_iso646_codepage const *cp;
	cp = self->ice_data.ied_cp646;
	for (i = 0; i < len; ++i) {
		/* Figure out how to encode this unicode character in this codepage. */
		char32_t c32 = data[i];
		char encoded = iso646_encode(cp, c32);
		if (encoded == 0 && c32 != 0)
			return false; /* Cannot encode :( */
		*result++ = encoded;
	}
	return true;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_cp646_encode(struct iconv_encode *__restrict self,
                      /*utf-8*/ char const *__restrict data, size_t size) {
	char buf[64], *ptr = buf;
	ssize_t temp, result = 0;
	char32_t c32;
	struct iconv_iso646_codepage const *cp;
	if unlikely(self->ice_flags & ICONV_HASERR)
		goto err_ilseq;
	cp = self->ice_data.ied_cp646;
	FOREACH_UTF8(c32, self, data, size) {
		/* Figure out how to encode this unicode character in this codepage. */
		char encoded;
		if (ptr >= COMPILER_ENDOF(buf)) {
			DO_encode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
		}
		encoded = iso646_encode(cp, c32);
		if (encoded || !c32) {
			*ptr++ = encoded;
			goto next_c32;
		}
		/* Cannot encode :( */
		if (self->ice_flags & ICONV_ERR_TRANSLIT) {
			/* Try to transliterate the character. */
			char32_t transbuf[ICONV_TRANSLITERATE_MAXLEN];
			size_t nth, len;
			if ((ptr + ICONV_TRANSLITERATE_MAXLEN) > COMPILER_ENDOF(buf)) {
				DO_encode_output(buf, (size_t)(ptr - buf));
				ptr = buf;
			}
			for (nth = 0; (len = libiconv_transliterate(transbuf, c32, nth)) != (size_t)-1; ++nth) {
				if (libiconv_cp646_encode_buf(self, ptr, transbuf, len)) {
					ptr += len;
					goto next_c32;
				}
			}
		}
		if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->ice_flags)) {
			DO_encode_output(buf, (size_t)(ptr - buf));
			size += _uni_status; /* Revert back to the start of the current character. */
			goto err_ilseq;
		}
		if (!IS_ICONV_ERR_DISCARD(self->ice_flags)) {
			if (IS_ICONV_ERR_REPLACE(self->ice_flags))
				*ptr++ = iconv_iso646_codepage_qmark(cp);
			else {
				*ptr++ = (char)(unsigned char)(uint32_t)c32;
			}
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
	if (IS_ICONV_ERR_ERRNO(self->ice_flags))
		errno = EILSEQ;
	return -(ssize_t)size;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_cp646_decode(struct iconv_decode *__restrict self,
                      /*cp???*/ char const *__restrict data, size_t size) {
	char buf[64], *ptr = buf;
	ssize_t temp, result = 0;
	struct iconv_iso646_codepage const *cp;
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
	cp = self->icd_data.idd_cp646;
	while (size) {
		char16_t c16;
		unsigned char c;
		if ((ptr + UNICODE_UTF8_CURLEN) > COMPILER_ENDOF(buf)) {
			DO_decode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
		}
		/* Decode the character via the codepage. */
		c   = (unsigned char)*data;
		c16 = unlikely(c >= 0x80) ? 0 : iso646_decode(cp, c);
		if unlikely(c16 == 0 && c != 0) {
			/* Invalid/undefined input byte */
			DO_decode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
			if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->icd_flags))
				goto err_ilseq;
			if (IS_ICONV_ERR_DISCARD(self->icd_flags))
				goto consume_byte;
			c16 = '?';
			if (IS_ICONV_ERR_IGNORE(self->icd_flags))
				c16 = c;
		}
		ptr = unicode_writeutf8(ptr, c16);
consume_byte:
		++data;
		--size;
	}
	DO_decode_output(buf, (size_t)(ptr - buf));
	return result;
err:
	return temp;
err_ilseq:
	self->icd_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->icd_flags))
		errno = EILSEQ;
	return -(ssize_t)size;
}
#endif /* CODEC_ISO646_COUNT != 0 */


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


#define DEFINE_FOR_ASCII
#include "convert-like-ascii.c.inl"
#define DEFINE_FOR_LATIN1
#include "convert-like-ascii.c.inl"
#if CODEC_CP7H_COUNT != 0
#define DEFINE_FOR_CP7H
#include "convert-like-ascii.c.inl"
#endif /* CODEC_CP7H_COUNT != 0 */

/* Misc codecs. */
#include "convert-c-escape.c.inl"
#include "convert-hex.c.inl"
#include "convert-uri-escape.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_LIBICONV_CONVERT_C */
