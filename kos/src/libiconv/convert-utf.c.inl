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
#define UTF_WIDTH     16
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

DECL_END

#undef UTF_BYTEORDER
#undef UTF_WIDTH
