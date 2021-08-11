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
#define UTF_WIDTH     32
#define UTF_BYTEORDER 1234
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#if UTF_BYTEORDER == 1234
INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC PP_CAT3(libiconv_utf, UTF_WIDTH, le_encode))(struct iconv_encode *__restrict self,
                                                                          /*utf-8*/ char const *__restrict data,
                                                                          size_t size)
#else /* UTF_BYTEORDER == 1234 */
INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC PP_CAT3(libiconv_utf, UTF_WIDTH, be_encode))(struct iconv_encode *__restrict self,
                                                                          /*utf-8*/ char const *__restrict data,
                                                                          size_t size)
#endif /* UTF_BYTEORDER != 1234 */
{
	PP_CAT3(char, UTF_WIDTH, _t) buf[64], *dst = buf;
	ssize_t temp, result = 0;
	if unlikely(self->ice_flags & ICONV_HASERR)
		goto err_ilseq;
	while (size) {
		do {
			size_t error = PP_CAT2(unicode_c8toc, UTF_WIDTH)(dst, data, size,
			                                                 &self->ice_data.ied_utf8);
			if unlikely(error == (size_t)-1) {
				if (IS_ICONV_ERR_ERRNO(self->ice_flags))
					goto err_ilseq;
				self->ice_data.ied_utf8.__word = __MBSTATE_TYPE_EMPTY;
				*dst = data[0];
				if (IS_ICONV_ERR_REPLACE(self->ice_flags))
					*dst = '?';
				error = 1;
			} else if (error == (size_t)-2) {
				size = 0;
				break;
			}
			data += error;
			size -= error;
#if UTF_BYTEORDER != __BYTE_ORDER__
			*dst = (PP_CAT3(char, UTF_WIDTH, _t))PP_CAT2(BSWAP, UTF_WIDTH)((PP_CAT3(uint, UTF_WIDTH, _t))*dst);
#endif /* UTF_BYTEORDER != __BYTE_ORDER__ */
			++dst;
		} while (dst < COMPILER_ENDOF(buf) && size);
		DO_encode_output((char *)buf, (size_t)((byte_t *)dst - (byte_t *)buf));
		dst = buf;
	}
	return result;
err:
	return temp;
err_ilseq:
	self->ice_flags |= ICONV_HASERR;
	errno = EILSEQ;
	return -1;
}


#if UTF_WIDTH == 16
#if UTF_BYTEORDER == 1234
INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf16le_decode)(struct iconv_decode *__restrict self,
                                                      /*utf-16*/ void const *__restrict data,
                                                      size_t size)
#else /* UTF_BYTEORDER == 1234 */
INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf16be_decode)(struct iconv_decode *__restrict self,
                                                      /*utf-16*/ void const *__restrict data,
                                                      size_t size)
#endif /* UTF_BYTEORDER != 1234 */
{
	ssize_t temp, result = 0;
	/*utf-8*/ char buf[64], *ptr = buf;
	size_t error;
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
	if (self->icd_data.idd_utf.u_pbc) {
		union word {
			uint16_t w;
			uint8_t b[2];
		};
		union word c16;
		if unlikely(!size)
			return 0;
#if UTF_BYTEORDER == 1234
		c16.b[0] = self->icd_data.idd_utf.u_pb[0];
		c16.b[1] = ((byte_t const *)data)[0];
#else /* UTF_BYTEORDER == 1234 */
		c16.b[0] = ((byte_t const *)data)[0];
		c16.b[1] = self->icd_data.idd_utf.u_pb[0];
#endif /* UTF_BYTEORDER != 1234 */
		error = unicode_c16toc8(ptr, c16.w, &self->icd_data.idd_utf.u_16);
		if unlikely(error == (size_t)-1) {
			if (IS_ICONV_ERR_ERRNO(self->icd_flags))
				goto err_ilseq;
			ptr[0] = '?';
			error  = 1;
		}
		ptr += error;
		self->icd_data.idd_utf.u_pbc = 0;
		data = (byte_t const *)data + 1;
		--size;
	}
	while (size >= 2) {
		char16_t c16;
		/* Check if the buffer must be flushed. */
		if ((ptr + UNICODE_16TO8_MAXBUF(1)) >= COMPILER_ENDOF(buf)) {
			DO_decode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
		}
#if UTF_BYTEORDER == 1234
		c16 = (char16_t)UNALIGNED_GETLE16((uint16_t const *)data);
#else /* UTF_BYTEORDER == 1234 */
		c16 = (char16_t)UNALIGNED_GETBE16((uint16_t const *)data);
#endif /* UTF_BYTEORDER != 1234 */
		error = unicode_c16toc8(ptr, c16, &self->icd_data.idd_utf.u_16);
		if unlikely(error == (size_t)-1) {
			if (IS_ICONV_ERR_ERRNO(self->icd_flags))
				goto err_ilseq;
			ptr[0] = '?';
			error  = 1;
		}
		ptr += error;
		data = (byte_t const *)data + 2;
		size -= 2;
	}
	/* Handle unmatched utf-16 byte. */
	if (size) {
		self->icd_data.idd_utf.u_pb[0] = *(byte_t const *)data;
		self->icd_data.idd_utf.u_pbc   = 1;
	}
	/* Flush all remaining data. */
	DO_decode_output(buf, (size_t)(ptr - buf));
	return result;
err:
	return temp;
err_ilseq:
	self->icd_flags |= ICONV_HASERR;
	errno = EILSEQ;
	return -1;
}
#endif /* UTF_WIDTH == 16 */


#if UTF_WIDTH == 32
#if UTF_BYTEORDER == 1234
INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf32le_decode)(struct iconv_decode *__restrict self,
                                                      /*utf-32*/ void const *__restrict data,
                                                      size_t size)
#else /* UTF_BYTEORDER == 1234 */
INTERN NONNULL((1, 2)) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf32be_decode)(struct iconv_decode *__restrict self,
                                                      /*utf-32*/ void const *__restrict data,
                                                      size_t size)
#endif /* UTF_BYTEORDER != 1234 */
{
	ssize_t temp, result = 0;
	/*utf-8*/ char buf[64], *ptr = buf;
	if (self->icd_data.idd_utf.u_pbc) {
		union dword {
			uint32_t l;
			uint8_t b[4];
		};
		union dword c32;
		for (;;) {
			if unlikely(!size)
				return 0;
			if (self->icd_data.idd_utf.u_pbc >= 3)
				break;
			self->icd_data.idd_utf.u_pb[self->icd_data.idd_utf.u_pbc] = *(byte_t const *)data;
			++self->icd_data.idd_utf.u_pbc;
			data = (byte_t const *)data + 1;
			--size;
		}
#if UTF_BYTEORDER == 1234
		c32.b[0] = self->icd_data.idd_utf.u_pb[0];
		c32.b[1] = self->icd_data.idd_utf.u_pb[1];
		c32.b[2] = self->icd_data.idd_utf.u_pb[2];
		c32.b[3] = ((byte_t const *)data)[0];
#else /* UTF_BYTEORDER == 1234 */
		c32.b[0] = ((byte_t const *)data)[0];
		c32.b[1] = self->icd_data.idd_utf.u_pb[2];
		c32.b[2] = self->icd_data.idd_utf.u_pb[1];
		c32.b[3] = self->icd_data.idd_utf.u_pb[0];
#endif /* UTF_BYTEORDER != 1234 */
		ptr = unicode_writeutf8(ptr, c32.l);
		self->icd_data.idd_utf.u_pbc = 0;
		data = (byte_t const *)data + 1;
		--size;
	}
	while (size >= 4) {
		char32_t c32;
		/* Check if the buffer must be flushed. */
		if ((ptr + UNICODE_UTF8_MAXLEN) >= COMPILER_ENDOF(buf)) {
			DO_decode_output(buf, (size_t)(ptr - buf));
			ptr = buf;
		}
#if UTF_BYTEORDER == 1234
		c32 = (char32_t)UNALIGNED_GETLE32((uint32_t const *)data);
#else /* UTF_BYTEORDER == 1234 */
		c32 = (char32_t)UNALIGNED_GETBE32((uint32_t const *)data);
#endif /* UTF_BYTEORDER != 1234 */
		ptr = unicode_writeutf8(ptr, c32);
		data = (byte_t const *)data + 2;
		size -= 2;
	}
	/* Handle unmatched utf-16 byte. */
	if (size) {
		memcpy(self->icd_data.idd_utf.u_pb, data, size);
		self->icd_data.idd_utf.u_pbc = size;
	}
	/* Flush all remaining data. */
	DO_decode_output(buf, (size_t)(ptr - buf));
	return result;
err:
	return temp;
}
#endif /* UTF_WIDTH == 32 */


DECL_END

#undef UTF_BYTEORDER
#undef UTF_WIDTH
