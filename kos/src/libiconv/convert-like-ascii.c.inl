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
#define DEFINE_FOR_LATIN1
//#define DEFINE_FOR_ASCII
#endif /* __INTELLISENSE__ */

DECL_BEGIN

/************************************************************************/
/* Special optimizations for codecs where the low 128 codepoints are    */
/* equal to ASCII                                                       */
/************************************************************************/


#ifdef DEFINE_FOR_LATIN1
#define LOCAL_libiconv_encode    libiconv_latin1_encode
#define LOCAL_libiconv_encode_32 libiconv_latin1_encode_u32
#define LOCAL_libiconv_decode    libiconv_latin1_decode
#elif defined(DEFINE_FOR_ASCII)
#define LOCAL_libiconv_encode    libiconv_ascii_encode
#define LOCAL_libiconv_encode_32 libiconv_ascii_encode_u32
#define LOCAL_libiconv_decode    libiconv_ascii_decode
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



INTERN NONNULL((1, 2)) ssize_t
(FORMATPRINTER_CC LOCAL_libiconv_encode_32)(struct iconv_encode *__restrict self,
                                            char32_t const *__restrict data,
                                            size_t size) {
	size_t i;
	char buf[16], *ptr = buf;
	ssize_t temp, result = 0;
	for (i = 0; i < size; ++i) {
		/* Figure out how to encode this unicode character in this codepage. */
		char32_t c32 = data[i];
		if (ptr >= COMPILER_ENDOF(buf)) {
			DO_encode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
		}
		if (c32 <= LOCAL_UNICODE_IDENT_MAXCHAR) {
			/* Found it! */
			*ptr++ = (char)(unsigned char)(uint32_t)c32;
		} else {
			/* Try to case-fold the character. */
			char32_t folded[UNICODE_FOLDED_MAX];
			size_t len = (size_t)(iconv_transliterate(c32, folded) - folded);
			if (len != 1 || folded[0] != c32) {
				DO_encode_output(buf, (size_t)(ptr - buf));
				ptr = buf;
				DO(LOCAL_libiconv_encode_32(self, folded, len));
			} else {
				if (IS_ICONV_ERR_ERRNO(self->ice_flags)) {
					DO_encode_output(buf, (size_t)(ptr - buf));
					goto err_ilseq;
				}
				if (!IS_ICONV_ERR_DISCARD(self->ice_flags)) {
					if (IS_ICONV_ERR_REPLACE(self->ice_flags))
						*ptr++ = '?';
					else {
						*ptr++ = (char)(unsigned char)(uint32_t)c32;
					}
				}
			}
		}
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
(FORMATPRINTER_CC LOCAL_libiconv_encode)(struct iconv_encode *__restrict self,
                                         /*utf-8*/ char const *__restrict data,
                                         size_t size) {
	ssize_t temp, result = 0;
	char const *iter, *flush_start, *end;
	if unlikely(self->ice_flags & ICONV_HASERR)
		goto err_ilseq;
	iter        = data;
	flush_start = data;
	end         = data + size;
	if (self->ice_data.ied_utf8.__word != __MBSTATE_TYPE_EMPTY) {
		/* Deal with incomplete characters. */
		if unlikely(!size)
			return 0;
		goto handle_unicode;
	}
	while (iter < end) {
		if ((unsigned char)*iter >= 0x80) {
			/* Start new unicode sequence. */
			char32_t c32;
			size_t status;
handle_unicode:
			DO_encode_output(flush_start, (size_t)(iter - flush_start));
			status = unicode_c8toc32(&c32, iter, (size_t)(end - iter),
			                         &self->ice_data.ied_utf8);
			if ((ssize_t)status < 0) {
				if (status == (size_t)-1) {
					if (IS_ICONV_ERR_ERRNO(self->ice_flags))
						goto err_ilseq;
					if (IS_ICONV_ERR_DISCARD(self->ice_flags)) {
						self->ice_data.ied_utf8.__word = __MBSTATE_TYPE_EMPTY;
						goto next_data;
					}
					c32 = '?';
					if (IS_ICONV_ERR_IGNORE(self->ice_flags))
						c32 = *iter;
					status = 1;
				} else if (status == (size_t)-2) {
					return result; /* Everything parsed! */
				}
			}
			iter += status;
			flush_start = iter;
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
			if (self->ice_flags & ICONV_ERR_TRANSLIT) {
				char32_t folded[UNICODE_FOLDED_MAX];
				size_t len = (size_t)(iconv_transliterate(c32, folded) - folded);
				if (len != 1 || folded[0] != c32) {
					DO(LOCAL_libiconv_encode_32(self, folded, len));
					continue;
				}
			}
			if (IS_ICONV_ERR_ERRNO(self->ice_flags))
				goto err_ilseq;
			if (!IS_ICONV_ERR_DISCARD(self->ice_flags)) {
				if (IS_ICONV_ERR_IGNORE(self->ice_flags))
					goto force_normal_output;
				DO_encode_output("?", 1);
			}
		} else {
next_data:
			++iter;
		}
	}
	DO_encode_output(flush_start, (size_t)(end - flush_start));
	return result;
err:
	return temp;
err_ilseq:
	self->ice_flags |= ICONV_HASERR;
	errno = EILSEQ;
	return -1;
}


INTERN NONNULL((1, 2)) ssize_t
(FORMATPRINTER_CC LOCAL_libiconv_decode)(struct iconv_decode *__restrict self,
                                         /*<CODEC>*/ char const *__restrict data,
                                         size_t size) {
	ssize_t temp, result = 0;
	char const *iter, *flush_start, *end;
#ifdef LOCAL_HAS_UNDEFINED_CODEPOINTS
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
#endif /* LOCAL_HAS_UNDEFINED_CODEPOINTS */
	iter        = data;
	flush_start = data;
	end         = data + size;
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
		if (IS_ICONV_ERR_ERRNO(self->icd_flags))
			goto err_ilseq;
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
	errno = EILSEQ;
	return -1;
#endif /* LOCAL_HAS_UNDEFINED_CODEPOINTS */
}

#undef LOCAL_UNICODE_IDENT_MAXCHAR
#undef LOCAL_libiconv_encode
#undef LOCAL_libiconv_encode_32
#undef LOCAL_libiconv_decode

DECL_END

#undef LOCAL_HAS_UNDEFINED_CODEPOINTS
#undef DEFINE_FOR_LATIN1
#undef DEFINE_FOR_ASCII
