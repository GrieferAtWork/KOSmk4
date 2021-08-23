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
#ifdef __INTELLISENSE__
#include "convert.c"
//#define DEFINE_FOR_LATIN1
//#define DEFINE_FOR_ASCII
#define DEFINE_FOR_CP7H
#endif /* __INTELLISENSE__ */

DECL_BEGIN

/************************************************************************/
/* Special optimizations for codecs where the low 128 codepoints are    */
/* equal to ASCII                                                       */
/************************************************************************/


#ifdef DEFINE_FOR_LATIN1
#define LOCAL_libiconv_encode     libiconv_latin1_encode
#define LOCAL_libiconv_encode_buf libiconv_latin1_encode_buf
#define LOCAL_libiconv_decode     libiconv_latin1_decode
#elif defined(DEFINE_FOR_ASCII)
#define LOCAL_libiconv_encode     libiconv_ascii_encode
#define LOCAL_libiconv_encode_buf libiconv_ascii_encode_buf
#define LOCAL_libiconv_decode     libiconv_ascii_decode
#elif defined(DEFINE_FOR_CP7H)
#define LOCAL_libiconv_encode     libiconv_cp7h_encode
#define LOCAL_libiconv_encode_buf libiconv_cp7h_encode_buf
#define LOCAL_libiconv_decode     libiconv_cp7h_decode
#else /* ... */
#error "Invalid mode"
#endif /* !... */

#undef LOCAL_HAS_UNDEFINED_CODEPOINTS
#ifdef DEFINE_FOR_LATIN1
#define LOCAL_UNICODE_IDENT_MAXCHAR 0xff /* latin1 is a one-on-one encoding of unicode U+0000 ... U+00FF */
#else /* DEFINE_FOR_LATIN1 */
#define LOCAL_HAS_UNDEFINED_CODEPOINTS
#define LOCAL_UNICODE_IDENT_MAXCHAR 0x7f /* Ascii only maps U+0000 ... U+007F one-on-one */
#endif /* !DEFINE_FOR_LATIN1 */



#ifdef DEFINE_FOR_CP7H
PRIVATE NONNULL((1, 2)) bool FORMATPRINTER_CC
LOCAL_libiconv_encode_buf(struct iconv_encode const *__restrict self,
                          char *__restrict result,
                          char32_t const *__restrict data, size_t len)
#else /* DEFINE_FOR_CP7H */
PRIVATE NONNULL((1)) bool FORMATPRINTER_CC
LOCAL_libiconv_encode_buf(char *__restrict result,
                          char32_t const *__restrict data, size_t len)
#endif /* !DEFINE_FOR_CP7H */
{
	size_t i;
	for (i = 0; i < len; ++i) {
		/* Figure out how to encode this unicode character in this codepage. */
		char32_t c32 = data[i];
		if (c32 <= LOCAL_UNICODE_IDENT_MAXCHAR) {
			/* Found it! */
			*result++ = (char)(unsigned char)(uint32_t)c32;
		} else {
#ifdef DEFINE_FOR_CP7H
			size_t lo, hi;
			struct iconv_7h_codepage const *cp;
			cp = self->ice_data.ied_cp7h;
			lo = 0;
			hi = cp->i7hcp_encode_count;
			while (lo < hi) {
				size_t i;
				i = (lo + hi) / 2;
				if (c32 < cp->i7hcp_encode[i].icee_uni) {
					hi = i;
				} else if (c32 > cp->i7hcp_encode[i].icee_uni) {
					lo = i + 1;
				} else {
					/* Found it! */
					*result++ = (char)(unsigned char)cp->i7hcp_encode[i].icee_cp;
					goto next_c32;
#define NEED_next_c32
				}
			}
#endif /* DEFINE_FOR_CP7H */
			return false;
		}
#ifdef NEED_next_c32
#undef NEED_next_c32
next_c32:
		;
#endif /* NEED_next_c32 */
	}
	return true;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
LOCAL_libiconv_encode(struct iconv_encode *__restrict self,
                      /*utf-8*/ char const *__restrict data,
                      size_t size) {
	ssize_t temp, result = 0;
	char const *flush_start, *end;
	flush_start = data;
	end         = data + size;
	if unlikely(self->ice_flags & ICONV_HASERR)
		goto err_ilseq;
	if (!mbstate_isempty(&self->ice_data.ied_utf8)) {
		/* Deal with incomplete characters. */
		if unlikely(!size)
			return 0;
		goto handle_unicode;
	}
	while (data < end) {
		unsigned char ch;
		ch = (unsigned char)*data;
		if (ch >= 0x80) {
			/* Start new unicode sequence. */
			char32_t c32;
			size_t status;
			DO_encode_output(flush_start, (size_t)(data - flush_start));
handle_unicode:
			status = unicode_c8toc32(&c32, data, (size_t)(end - data),
			                         &self->ice_data.ied_utf8);
			if ((ssize_t)status < 0) {
				ch = (unsigned char)*data;
				if (status == (size_t)-1) {
					if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->ice_flags))
						goto err_ilseq;
					if (IS_ICONV_ERR_DISCARD(self->ice_flags)) {
						mbstate_init(&self->ice_data.ied_utf8);
						flush_start = data;
						goto next_data;
					}
					c32 = '?';
					if (IS_ICONV_ERR_IGNORE(self->ice_flags))
						c32 = ch;
					status = 1;
				} else if (status == (size_t)-2) {
					return result; /* Everything parsed! */
				}
			}
			data += status;
			flush_start = data;
			/* Encode `c32' */
#ifdef DEFINE_FOR_ASCII
			if unlikely(c32 <= LOCAL_UNICODE_IDENT_MAXCHAR)
#elif defined(DEFINE_FOR_LATIN1)
			if likely(c32 <= LOCAL_UNICODE_IDENT_MAXCHAR)
#else /* DEFINE_FOR_ASCII */
			if (c32 <= LOCAL_UNICODE_IDENT_MAXCHAR)
#endif /* !DEFINE_FOR_ASCII */
			{
force_normal_output:
				char out[1];
				out[0] = (char)(unsigned char)(uint32_t)c32;
				DO_encode_output(out, 1);
				continue;
			}
#ifdef DEFINE_FOR_CP7H
			size_t lo, hi;
			struct iconv_7h_codepage const *cp;
			cp = self->ice_data.ied_cp7h;
			lo = 0;
			hi = cp->i7hcp_encode_count;
			while (lo < hi) {
				size_t i;
				i = (lo + hi) / 2;
				if (c32 < cp->i7hcp_encode[i].icee_uni) {
					hi = i;
				} else if (c32 > cp->i7hcp_encode[i].icee_uni) {
					lo = i + 1;
				} else {
					/* Found it! */
					DO_encode_output((char const *)&cp->i7hcp_encode[i].icee_cp, 1);
					goto next_data_noinc;
				}
			}
#endif /* DEFINE_FOR_CP7H */
			if (self->ice_flags & ICONV_ERR_TRANSLIT) {
				/* Try to transliterate the character. */
				char cpbuf[ICONV_TRANSLITERATE_MAXLEN];
				char32_t transbuf[ICONV_TRANSLITERATE_MAXLEN];
				size_t nth, len;
				for (nth = 0; (len = libiconv_transliterate(transbuf, c32, nth)) != (size_t)-1; ++nth) {
#ifdef DEFINE_FOR_CP7H
					if (LOCAL_libiconv_encode_buf(self, cpbuf, transbuf, len))
#else /* DEFINE_FOR_CP7H */
					if (LOCAL_libiconv_encode_buf(cpbuf, transbuf, len))
#endif /* !DEFINE_FOR_CP7H */
					{
						DO_encode_output(cpbuf, len);
						goto next_data_noinc;
					}
				}
			}
			if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->ice_flags)) {
				data -= status;
				goto err_ilseq;
			}
			if (!IS_ICONV_ERR_DISCARD(self->ice_flags)) {
				if (IS_ICONV_ERR_IGNORE(self->ice_flags))
					goto force_normal_output;
				DO_encode_output("?", 1);
			}
		} else {
next_data:
			++data;
		}
next_data_noinc:
		;
	}
	DO_encode_output(flush_start, (size_t)(end - flush_start));
	return result;
err:
	return temp;
err_ilseq:
	self->ice_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->ice_flags))
		errno = EILSEQ;
	return -(ssize_t)(size_t)(end - data);
}


INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
LOCAL_libiconv_decode(struct iconv_decode *__restrict self,
                      /*<CODEC>*/ char const *__restrict data,
                      size_t size) {
	ssize_t temp, result = 0;
	char const *iter, *flush_start, *end;
	iter        = data;
	flush_start = data;
	end         = data + size;
#ifdef LOCAL_HAS_UNDEFINED_CODEPOINTS
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
#endif /* LOCAL_HAS_UNDEFINED_CODEPOINTS */
	while (iter < end) {
		unsigned char ch = (unsigned char)*iter;
		if likely(ch <= 0x7f) {
			++iter;
			continue;
		}
		DO_decode_output(flush_start, (size_t)(iter - flush_start));
		++iter;
		flush_start = iter;
#ifdef LOCAL_HAS_UNDEFINED_CODEPOINTS
#ifdef DEFINE_FOR_CP7H
		/* Try to decode using the code-page. */
		{
			struct iconv_7h_codepage const *cp;
			char16_t c16;
			cp  = self->icd_data.idd_cp7h;
			c16 = cp->i7hcp_decode[ch - 0x80];
			if (c16 != 0) {
				char buf[UNICODE_16TO8_MAXBUF(1)], *dst = buf;
				/* Output `c16' in utf-8 */
				if likely(c16 <= ((uint16_t)1 << 7)-1) {
					*dst++ = (char)(uint8_t)c16;
				} else if (c16 <= ((uint16_t)1 << 11)-1) {
					*dst++ = (char)(0xc0 | (uint8_t)((c16 >> 6)/* & 0x1f*/));
					*dst++ = (char)(0x80 | (uint8_t)((c16) & 0x3f));
				} else {
					*dst++ = (char)(0xe0 | (uint8_t)((c16 >> 12)/* & 0x0f*/));
					*dst++ = (char)(0x80 | (uint8_t)((c16 >> 6) & 0x3f));
					*dst++ = (char)(0x80 | (uint8_t)((c16) & 0x3f));
				}
				DO_decode_output(buf, (size_t)(dst - buf));
				continue;
			}
		}
#endif /* DEFINE_FOR_CP7H */

		if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->icd_flags)) {
			--iter;
			goto err_ilseq;
		}

		/* NOTE: No need to handle `IS_ICONV_ERR_IGNORE()'; our function
		 *       isn't  used when converting  text in error-ignore mode. */
		if (IS_ICONV_ERR_REPLACE(self->icd_flags))
			DO_decode_output("?", 1);
		else if (IS_ICONV_ERR_IGNORE(self->icd_flags)) {
			flush_start = iter - 1; /* Simply re-emit the bad character. */
		}
#else /* LOCAL_HAS_UNDEFINED_CODEPOINTS */
		/* Convert LATIN-1 0x80...0xff to UTF-8 */
		{
			char utf8[2];
			utf8[0] = (char)(0xc0 | (uint8_t)((ch >> 6) /* & 0x1f*/));
			utf8[1] = (char)(0x80 | (uint8_t)(ch & 0x3f));
			DO_decode_output(utf8, 2);
		}
#endif /* !LOCAL_HAS_UNDEFINED_CODEPOINTS */
	}
	DO_decode_output(flush_start, (size_t)(end - flush_start));
	return result;
err:
	return temp;
#ifdef LOCAL_HAS_UNDEFINED_CODEPOINTS
err_ilseq:
	self->icd_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->icd_flags))
		errno = EILSEQ;
	return -(ssize_t)(size_t)(end - iter);
#endif /* LOCAL_HAS_UNDEFINED_CODEPOINTS */
}



#undef LOCAL_UNICODE_IDENT_MAXCHAR
#undef LOCAL_libiconv_encode
#undef LOCAL_libiconv_encode_buf
#undef LOCAL_libiconv_decode
#undef LOCAL_HAS_UNDEFINED_CODEPOINTS

DECL_END

#undef DEFINE_FOR_LATIN1
#undef DEFINE_FOR_ASCII
#undef DEFINE_FOR_CP7H
