/* HASH CRC-32:0x6731b342 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_VIS_C
#define GUARD_LIBC_AUTO_VIS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "vis.h"
#include "../user/ctype.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.bsd.vis") NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_vis)(char *dst,
                               int c,
                               int flags,
                               int nextc) {
	return libc_nvis(dst, 5, c, flags, nextc);
}
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_OUTS(1, 2) char *
NOTHROW_NCX(LIBCCALL libc_nvis)(char *dst,
                                size_t dstsize,
                                int c,
                                int flags,
                                int nextc) {
	return libc_snvis(dst, dstsize, c, flags, nextc, "");
}
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(5) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_svis)(char *dst,
                                int c,
                                int flags,
                                int nextc,
                                char const *mbextra) {
	return libc_snvis(dst, 5, c, flags, nextc, mbextra);
}
#include <asm/crt/vis.h>
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(6) ATTR_OUTS(1, 2) char *
NOTHROW_NCX(LIBCCALL libc_snvis)(char *dst,
                                 size_t dstsize,
                                 int c,
                                 int flags,
                                 int nextc,
                                 char const *mbextra) {
	int len;
	char src[2];
	src[0] = (char)(unsigned char)(unsigned int)c;
	src[1] = (char)(unsigned char)(unsigned int)nextc;
	flags |= __VIS_SRCEXTRA;
	len = libc_strsnvisx(dst, dstsize, src, 1, flags, mbextra);
	if unlikely(len == -1)
		return NULL;
	return dst + (unsigned int)len;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(2) NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_strvis)(char *dst,
                                  char const *src,
                                  int flags) {

	return libc_strnvis(dst, src, (size_t)-1, flags);



}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN_OPT(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_stravis)(char **p_resstr,
                                   char const *src,
                                   int flags) {
	int result;
	char *dst;
	size_t srclen, dstsize;
	if unlikely(!src || *src) {
		if unlikely((*p_resstr = (char *)libc_calloc(1, sizeof(char))) == NULL)
			return -1;
		return 0;
	}
	srclen  = libc_strlen(src);
	dstsize = (srclen * 4) + 1;
	dst     = (char *)libc_malloc(dstsize);
	if unlikely(!dst)
		return -1;
	result = libc_strnvisx(dst, dstsize, src, srclen, flags);
	if unlikely(result == -1) {

		libc_free(dst);

		return -1;
	}

	/* Free unused trailing memory. */

	{
		char *trimmed_dst;
		trimmed_dst = (char *)libc_realloc(dst, ((size_t)result + 1) * sizeof(char));
		if likely(trimmed_dst)
			dst = trimmed_dst;
	}

	*p_resstr = dst;
	return result;
}
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_strnvis_netbsd)(char *dst,
                                          size_t dstsize,
                                          char const *src,
                                          int flags) {
	return libc_strsnvis(dst, dstsize, src, flags, "");
}
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_OUTS(1, 3) int
NOTHROW_NCX(LIBCCALL libc_strnvis)(char *dst,
                                   char const *src,
                                   size_t dstsize,
                                   int flags) {
	return libc_strsnvis(dst, dstsize, src, flags, "");
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(4) ATTR_IN_OPT(2) NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_strsvis)(char *dst,
                                   char const *src,
                                   int flags,
                                   char const *mbextra) {
	return libc_strsnvis(dst, (size_t)-1, src, flags, mbextra);
}
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(5) ATTR_IN_OPT(3) ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_strsnvis)(char *dst,
                                    size_t dstsize,
                                    char const *src,
                                    int flags,
                                    char const *mbextra) {
	return libc_strsnvisx(dst, dstsize, src, src ? libc_strlen(src) : 0, flags, mbextra);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_INS(2, 3) NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_strvisx)(char *dst,
                                   char const *src,
                                   size_t srclen,
                                   int flags) {
	return libc_strnvisx(dst, (size_t)-1, src, srclen, flags);
}
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_INS(3, 4) ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_strnvisx)(char *dst,
                                    size_t dstsize,
                                    char const *src,
                                    size_t srclen,
                                    int flags) {
	return libc_strenvisx(dst, dstsize, src, srclen, flags, NULL);
}
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_INS(3, 4) ATTR_OUTS(1, 2) ATTR_OUT_OPT(6) int
NOTHROW_NCX(LIBCCALL libc_strenvisx)(char *dst,
                                     size_t dstsize,
                                     char const *src,
                                     size_t srclen,
                                     int flags,
                                     int *cerr_ptr) {
	return libc_strsenvisx(dst, dstsize, src, srclen, flags, "", cerr_ptr);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(5) NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_strsvisx)(char *dst,
                                    char const *src,
                                    size_t srclen,
                                    int flags,
                                    char const *mbextra) {
	return libc_strsnvisx(dst, (size_t)-1, src, srclen, flags, mbextra);
}
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(6) ATTR_INS(3, 4) ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_strsnvisx)(char *dst,
                                     size_t dstsize,
                                     char const *src,
                                     size_t srclen,
                                     int flags,
                                     char const *mbextra) {
	return libc_strsenvisx(dst, dstsize, src, srclen, flags, mbextra, NULL);
}
#include <hybrid/typecore.h>
#include <asm/crt/vis.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(6) ATTR_INS(3, 4) ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_strsenvisx)(char *dst,
                                      size_t dstsize,
                                      char const *src,
                                      size_t srclen,
                                      int flags,
                                      char const *mbextra,
                                      int *cerr_ptr) {
	byte_t *writer, *dstend;
	char const *src_end = src + srclen;
	(void)cerr_ptr; /* Unused in this implementation (something about multi-byte characters?) */
	writer = (byte_t *)dst;
	dstend = (byte_t *)dst + dstsize;
handle_next_byte:
	while (src < src_end) {
		byte_t byte = (byte_t)*src++;
		byte_t next = (src < src_end || (flags & __VIS_SRCEXTRA)) ? *src : 0;
		if (flags & __VIS_HTTPSTYLE) {
			if (libc_isalnum(byte))
				goto encode_byte;
			if (libc_strchr("$-_.+!*'(),", byte))
				goto encode_byte;
			/* Must encode as "%AB" */
			if unlikely((size_t)(dstend - writer) < 3)
				goto err_nospace;
			*writer++ = '%';
			*writer++ = __LOCAL_itoa_digit(false, (byte & 0xf0) >> 4);
			*writer++ = __LOCAL_itoa_digit(false, (byte & 0x0f));
			goto handle_next_byte;
		} else if (flags & __VIS_MIMESTYLE) {
			if (byte == '\n')
				goto encode_byte;
			if (libc_isspace(byte)) {
				/* Only have to escape space if followed by a line-feed */
				if (next != '\r' && next != '\n')
					goto encode_byte;
			} else if (libc_strchr("#$@[\\]^`{|}~=", byte) != NULL) {
				/* Always have to escape these. */
			} else {
				if (byte >= 0x20 && byte <= 0x7e)
					goto encode_byte; /* Normal ASCII doesn't need to be escaped. */
			}
			*writer++ = '=';
			*writer++ = __LOCAL_itoa_digit(true, (byte & 0xf0) >> 4);
			*writer++ = __LOCAL_itoa_digit(true, (byte & 0x0f));
			goto handle_next_byte;
		}

encode_byte:
		if unlikely(writer == dstend)
			goto err_nospace;
		/* Check if `byte' may not need to be escaped. */
		if (libc_isgraph(byte) || libc_strchr("\t\n ", byte) ||
		    ((flags & __VIS_SAFE) && libc_strchr("\x08\x07\r", byte))) {
			if (libc_strchr(mbextra, byte))
				goto escape_byte;
			if ((flags & __VIS_GLOB) && libc_strchr("*?[#", byte))
				goto escape_byte;
			if ((flags & __VIS_SHELL) && libc_strchr("'`\";&<>()|{}]\\$!^~", byte))
				goto escape_byte;
			if ((flags & __VIS_SP) && byte == ' ')
				goto escape_byte;
			if ((flags & __VIS_TAB) && byte == '\t')
				goto escape_byte;
			if ((flags & __VIS_NL) && byte == '\n')
				goto escape_byte;
			if ((flags & __VIS_DQ) && byte == '"')
				goto escape_byte;
			if (!(flags & __VIS_NOSLASH) && byte == '\\')
				goto escape_byte;

			/* Allowed to directly encode `byte' */
			*writer++ = byte;
			goto handle_next_byte;
		}

escape_byte:
		/* Must escape `byte' */
		if (flags & __VIS_CSTYLE) {
			switch (byte) {

			case 0x0a: byte = 'n'; goto escape_bk_byte;
			case 0x0d: byte = 'r'; goto escape_bk_byte;
			case 0x08: byte = 'b'; goto escape_bk_byte;
			case 0x07: byte = 'a'; goto escape_bk_byte;
			case 0x0b: byte = 'v'; goto escape_bk_byte;
			case 0x09: byte = 't'; goto escape_bk_byte;
			case 0x0c: byte = 'f'; goto escape_bk_byte;
			case 0x20: byte = 's'; goto escape_bk_byte;
			case 0x1b: byte = 'E'; goto escape_bk_byte;
			case 0x00:
				if unlikely((size_t)(dstend - writer) < 2)
					goto err_nospace;
				*writer++ = '\\';
				*writer++ = '0';
				if (next >= '0' && next <= '0') {
					if unlikely((size_t)(dstend - writer) < 2)
						goto err_nospace;
					*writer++ = '0';
					*writer++ = '0';
				}
				goto handle_next_byte;

			case 'E': case 'e': case 'n': case 'r':
			case 'b': case 'a': case 'v': case 't':
			case 'f': case 's': case '0': case '1':
			case '2': case '3': case '4': case '5':
			case '6': case '7': case 'M': case '^':
			case '$':
				/* Can't do normal escaping for these characters. */
				break;

			default:
				if (!libc_isgraph(byte))
					break;
escape_bk_byte:
				if unlikely((size_t)(dstend - writer) < 2)
					goto err_nospace;
				*writer++ = '\\';
				*writer++ = byte;
				goto handle_next_byte;
			}
		}

		/* Escape using the octal representation */
		if ((flags & __VIS_OCTAL) || libc_strchr("\x20\xA0", byte) || libc_strchr(mbextra, byte)) {
			if unlikely((size_t)(dstend - writer) < 4)
				goto err_nospace;
			*writer++ = '\\';
			*writer++ = (byte_t)('0' + ((byte & 0700) >> 6));
			*writer++ = (byte_t)('0' + ((byte & 0070) >> 3));
			*writer++ = (byte_t)('0' + ((byte & 0007)));
			goto handle_next_byte;
		}

		if (!(flags & __VIS_NOSLASH)) {
			if unlikely(writer == dstend)
				goto err_nospace;
			*writer++ = '\\';
		}

		if (byte & 0x80) {
			if unlikely(writer == dstend)
				goto err_nospace;
			*writer++ = 'M';
			byte &= 0x7f;
		}

		if unlikely((size_t)(dstend - writer) < 2)
			goto err_nospace;
		if (libc_iscntrl(byte)) {
			*writer++ = '^';
			if (byte == 0x7f) {
				*writer++ = '?';
			} else {
				*writer++ = '@' + byte;
			}
		} else {
			*writer++ = '-';
			*writer++ = byte;
		}
	}
	if unlikely(writer == dstend)
		goto err_nospace;
	*writer = '\0';
	return (int)(unsigned int)(size_t)(writer - (byte_t *)dst);
err_nospace:

	return __libc_seterrno(ENOSPC);



}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(2) NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_strunvis)(char *dst,
                                    char const *src) {

	return libc_strnunvis(dst, src, (size_t)-1);



}
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(3) ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_strnunvis_netbsd)(char *dst,
                                            size_t dstsize,
                                            char const *src) {
	return libc_strnunvisx(dst, dstsize, src, 0);
}
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(2) ATTR_OUTS(1, 3) int
NOTHROW_NCX(LIBCCALL libc_strnunvis)(char *dst,
                                     char const *src,
                                     size_t dstsize) {
	return libc_strnunvisx(dst, dstsize, src, 0);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(2) NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_strunvisx)(char *dst,
                                     char const *src,
                                     int flags) {
	return libc_strnunvisx(dst, (size_t)-1, src, flags);
}
#include <asm/crt/vis.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_IN(3) ATTR_OUTS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_strnunvisx)(char *dst,
                                      size_t dstsize,
                                      char const *src,
                                      int flags) {
	int error, state = 0;
	char inchar, outchar, *writer, *dstend;
	writer = dst;
	dstend    = dst + dstsize;
	while ((inchar = *src++) != '\0') {
		error = libc_unvis(&outchar, (unsigned char)inchar, &state, flags);
		switch (error) {

		case __UNVIS_VALID:
			if unlikely(writer == dstend)
				goto err_nospace;
			*writer++ = outchar;
			break;

		case __UNVIS_VALIDPUSH:
			if unlikely(writer == dstend)
				goto err_nospace;
			*writer++ = outchar;
			continue;

		case __UNVIS_NOCHAR:
			break;


		case __UNVIS_SYNBAD:

			return __libc_seterrno(EINVAL);



		default:
			__builtin_unreachable();








		}
	}
	error = libc_unvis(&outchar, (unsigned char)inchar, &state, __UNVIS_END);
	if (error == UNVIS_VALID) {
		if unlikely(writer == dstend)
			goto err_nospace;
		*writer++ = outchar;
	}
	if unlikely(writer == dstend)
		goto err_nospace;
	*writer = '\0';
	return (int)(unsigned int)(size_t)(writer - dst);
err_nospace:

	return __libc_seterrno(ENOSPC);



}
#include <asm/crt/vis.h>
#include <hybrid/__overflow.h>
#include <libc/template/hex.h>
/* >> unvis(3)
 * WARNING: When returning `UNVIS_NOCHAR', `*p_outbyte' may be part of the internal state  and
 *          has to be copied alongside `*p_state' if you wish to state (and later restore) the
 *          state of this function!
 * @param: flags: Set of `VIS_HTTP1808 | VIS_MIMESTYLE | VIS_HTTP1866 | VIS_NOESCAPE | UNVIS_END'
 * @return: UNVIS_SYNBAD:    [...]
 * @return: UNVIS_VALID:     [...]
 * @return: UNVIS_VALIDPUSH: [...]
 * @return: UNVIS_NOCHAR:    [...] */
INTERN ATTR_SECTION(".text.crt.bsd.vis") ATTR_INOUT(3) NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_unvis)(char *p_outbyte,
                                 int inbyte,
                                 int *p_state,
                                 int flags) {
	unsigned int bstate = ((unsigned int)*p_state) & 0xff;
	byte_t ch = (byte_t)(unsigned int)inbyte;
#define UNVIS_BSTATE_INIT   0x00 /* Initial zero-shift state */
#define UNVIS_BSTATE_BK     0x01 /* After '\' */
#define UNVIS_BSTATE_OCT2   0x02 /* After '\1' */
#define UNVIS_BSTATE_OCT3   0x03 /* After '\12' */
#define UNVIS_BSTATE_BKM    0x04 /* After '\M' */
#define UNVIS_BSTATE_BKMD   0x05 /* After '\M-' */
#define UNVIS_BSTATE_BKC    0x06 /* After '\^' (C: Circumflex) */
#define UNVIS_BSTATE_HEXP   0x07 /* After '%' */
#define UNVIS_BSTATE_HEX1   0x08 /* After '\x' */
#define UNVIS_BSTATE_HEX2   0x09 /* After '\xA' or '%A' */
#define UNVIS_BSTATE_EQ     0x0a /* After '=' */
#define UNVIS_BSTATE_EQX    0x0b /* After '=A' */
#define UNVIS_BSTATE_EQLF   0x0c /* After '=[CR|LF]' */
#define UNVIS_BSTATE_AMP    0x0d /* After '&' */
#define UNVIS_BSTATE_AMPP   0x0e /* After '&#' */
#define UNVIS_BSTATE_AMPPX  0x0f /* After '&#x' */
#define UNVIS_BSTATE_AMPPXX 0x10 /* After '&#x<0-9a-fA-F>' */
#define UNVIS_BSTATE_AMPPD  0x11 /* After '&#<0-9>' */
#define UNVIS_BSTATE_AMPN   0x12 /* After '&foo' */

	/* Check for the special end-marker flag. */
	if (flags & __UNVIS_END) {
		switch (bstate) {

		case UNVIS_BSTATE_OCT2:
		case UNVIS_BSTATE_OCT3:
		case UNVIS_BSTATE_HEX2:
			/* NOTE: Technically, `UNVIS_VALIDPUSH' would have made more
			 *       sense here (since we're not "consuming" the end  of
			 *       the input string), but better not change the abi... */
			goto done_valid_and_reset; /* goto done_valid_noconsume_and_reset; */

		case UNVIS_BSTATE_INIT:
done_nochar:
			return __UNVIS_NOCHAR;
		default:
			goto err_synbad;
		}
	}

	switch (__builtin_expect(bstate, UNVIS_BSTATE_INIT)) {

	case UNVIS_BSTATE_INIT:
		/* Check for escape sequence start characters. */
		switch (ch) {

		case '\\':
			if (!(flags & __VIS_NOESCAPE)) {
				*p_state = UNVIS_BSTATE_BK;
				goto done_nochar;
			}
			break;

		case '%':
			if (flags & __VIS_HTTPSTYLE) {
				*p_outbyte = 0x00;
				*p_state = UNVIS_BSTATE_HEXP;
				goto done_nochar;
			}
			break;

		case '=':
			if (flags & __VIS_MIMESTYLE) {
				*p_state = UNVIS_BSTATE_EQ;
				goto done_nochar;
			}
			break;

		case '&':
			if (flags & __VIS_HTTP1866) {
				*p_state = UNVIS_BSTATE_AMP;
				goto done_nochar;
			}
			break;

		default:
			break;
		}
		break;

	case UNVIS_BSTATE_BK:
		switch (ch) {

		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			*p_outbyte = (char)(unsigned char)(ch - '0');
			*p_state   = UNVIS_BSTATE_OCT2;
			goto done_nochar;

		case 'M':
			*p_outbyte = 0x80;
			*p_state   = UNVIS_BSTATE_BKM;
			goto done_nochar;
		case '^':
			*p_outbyte = 0x00;
			*p_state   = UNVIS_BSTATE_BKC;
			goto done_nochar;
		case 'x':
			*p_outbyte = 0x00;
			*p_state   = UNVIS_BSTATE_HEX1;
			goto done_nochar;
		case 'n': ch = 0x0a; goto reset_and_return_ch;
		case 'r': ch = 0x0d; goto reset_and_return_ch;
		case 'b': ch = 0x08; goto reset_and_return_ch;
		case 'a': ch = 0x07; goto reset_and_return_ch;
		case 'v': ch = 0x0b; goto reset_and_return_ch;
		case 't': ch = 0x09; goto reset_and_return_ch;
		case 'f': ch = 0x0c; goto reset_and_return_ch;
		case 's': ch = 0x20; goto reset_and_return_ch; /* BSD-extension */
		case 'e': /* KOS-extension */
		case 'E': ch = 0x1b; goto reset_and_return_ch; /* BSD-extension */
		case '$':
		case '\n': *p_state = UNVIS_BSTATE_INIT; goto done_nochar;

		default:
			if (!libc_isgraph(ch))
				goto err_synbad;
			/* Fallthru to re-return `ch' */
reset_and_return_ch:
			*p_state = UNVIS_BSTATE_INIT;
		}
		break;

	case UNVIS_BSTATE_OCT2:
	case UNVIS_BSTATE_OCT3:
		if (ch >= '0' && ch <= '7') {
			*p_outbyte <<= 3;
			*p_outbyte |= (char)(unsigned char)(ch - '0');
			if (*p_state == UNVIS_BSTATE_OCT3)
				goto done_valid_and_reset;
			*p_state = UNVIS_BSTATE_OCT3;
			goto done_nochar;
		}
done_valid_noconsume_and_reset:
		*p_state = UNVIS_BSTATE_INIT;
		return __UNVIS_VALIDPUSH;

	case UNVIS_BSTATE_BKM:
		if (ch == '-') {
			*p_state = UNVIS_BSTATE_BKMD;
			goto done_nochar;
		}
		if (ch == '^') {
			*p_state = UNVIS_BSTATE_BKC;
			goto done_nochar;
		}
		goto err_synbad;

	case UNVIS_BSTATE_BKMD:
		*p_outbyte |= (char)ch;
done_valid_and_reset:
		*p_state = UNVIS_BSTATE_INIT;
/*done_valid:*/
		return __UNVIS_VALID;

	case UNVIS_BSTATE_BKC:
		if (ch == '?') {
			*p_outbyte |= 0x7f;
		} else {
			*p_outbyte |= (char)(ch & 0x1f);
		}
		goto done_valid_and_reset;

	case UNVIS_BSTATE_HEX1:
		if (!libc_isxdigit(ch))
			goto err_synbad;
		ATTR_FALLTHROUGH
	case UNVIS_BSTATE_HEXP:
	case UNVIS_BSTATE_HEX2: {
		byte_t nibble;
		if (!__libc_hex2int(ch, &nibble))
			goto done_valid_noconsume_and_reset;
		*p_outbyte <<= 4;
		*p_outbyte |= (char)nibble;
		if (*p_state == UNVIS_BSTATE_HEX2)
			goto done_valid_and_reset;
		*p_state = UNVIS_BSTATE_HEX2;
		goto done_nochar;
	}

	case UNVIS_BSTATE_EQ:
		if (ch == '\r' || ch == '\n') {
			*p_state = UNVIS_BSTATE_EQLF;
			goto done_nochar;
		}
		if (libc_isdigit(ch)) {
			*p_outbyte = (char)(byte_t)(ch - '0') << 4;
			*p_state   = UNVIS_BSTATE_EQX;
			goto done_nochar;
		}
		if (ch >= 'A' && ch <= 'F') {
			*p_outbyte = (char)(byte_t)(10 + ch - 'A') << 4;
			*p_state   = UNVIS_BSTATE_EQX;
			goto done_nochar;
		}
		goto err_synbad;

	case UNVIS_BSTATE_EQX:
		if (libc_isdigit(ch)) {
			*p_outbyte |= (char)(byte_t)(ch - '0');
			goto done_valid_and_reset;
		}
		if (ch >= 'A' && ch <= 'F') {
			*p_outbyte |= (char)(byte_t)(10 + ch - 'A');
			goto done_valid_and_reset;
		}
		goto err_synbad;

	case UNVIS_BSTATE_EQLF:
		if (ch == '\r' || ch == '\n')
			goto done_nochar;
		if (ch == '=') {
			*p_state = UNVIS_BSTATE_EQ;
			goto done_nochar;
		}
		goto reset_and_return_ch;

	case UNVIS_BSTATE_AMP:
		*p_outbyte = (char)0;
		if (ch == '#') {
			*p_state = UNVIS_BSTATE_AMPP;
			goto done_nochar;
		}
		*p_state = UNVIS_BSTATE_AMPN;
		ATTR_FALLTHROUGH
	case UNVIS_BSTATE_AMPN: {
		/* We only support names for ASCII characters (because we want to remain  codec-neutral)
		 * Note also that KOS's libiconv contains a full database of XML characters, though that
		 * one would already be too large for us to use here. */
		struct xml_ent {
			char   xe_name[7]; /* Entity name */
			byte_t xe_byte;    /* Entity byte */
		};
		static struct xml_ent const xml_entities[] = {
			/* NOTE: This table must be sorted ascendingly by `xe_name' */
			{ "Hat", /*    */ 0x5e },
			{ { 'N', 'e', 'w', 'L', 'i', 'n', 'e' }, /**/ 0x0a },
			{ "Tab", /*    */ 0x09 },
			{ "amp", /*    */ 0x26 },
			{ "apos", /*   */ 0x27 },
			{ "ast", /*    */ 0x2a },
			{ "bne", /*    */ 0x3d },
			{ "bsol", /*   */ 0x5c },
			{ "colon", /*  */ 0x3a },
			{ "comma", /*  */ 0x2c },
			{ "commat", /* */ 0x40 },
			{ "dollar", /* */ 0x24 },
			{ "excl", /*   */ 0x21 },
			{ "fjlig", /*  */ 0x66 },
			{ "grave", /*  */ 0x60 },
			{ "gt", /*     */ 0x3e },
			{ "lcub", /*   */ 0x7b },
			{ "lowbar", /* */ 0x5f },
			{ "lpar", /*   */ 0x28 },
			{ "lsqb", /*   */ 0x5b },
			{ "lt", /*     */ 0x3c },
			{ "num", /*    */ 0x23 },
			{ "percnt", /* */ 0x25 },
			{ "period", /* */ 0x2e },
			{ "plus", /*   */ 0x2b },
			{ "quest", /*  */ 0x3f },
			{ "quot", /*   */ 0x22 },
			{ "rcub", /*   */ 0x7d },
			{ "rpar", /*   */ 0x29 },
			{ "rsqb", /*   */ 0x5d },
			{ "semi", /*   */ 0x3b },
			{ "sol", /*    */ 0x2f },
			{ "vert", /*   */ 0x7c },
		};
		byte_t pos = (byte_t)*p_outbyte;
		byte_t len = ((unsigned int)*p_state) >> 8;
		if unlikely(len >= lengthof(xml_entities[0].xe_name))
			goto err_synbad;
		if unlikely(pos >= lengthof(xml_entities))
			goto err_synbad;
		if unlikely(ch == '\0')
			goto err_synbad;
		if (ch == ';')
			ch = '\0';
		for (;;) {
			if (xml_entities[pos].xe_name[len] == (char)ch)
				break; /* Found it! */
			++pos;
			if unlikely(pos >= lengthof(xml_entities))
				goto err_synbad; /* No such name. */
			if (libc_bcmp(xml_entities[pos - 1].xe_name,
			         xml_entities[pos - 0].xe_name,
			         sizeof(xml_entities[0].xe_name)) != 0)
				goto err_synbad; /* Prefix changed */
		}
		++len;
		if (ch == '\0') {
			/* Found entity! */
			ch = xml_entities[pos].xe_byte;
			goto reset_and_return_ch;
		}

		/* Write back the updated database cursor. */
		*p_outbyte = (char)pos;
		*p_state   = ((unsigned int)len << 8) | UNVIS_BSTATE_AMPN;
	}	goto done_nochar;

	case UNVIS_BSTATE_AMPP:
		if (ch == 'x') {
			*p_state = UNVIS_BSTATE_AMPPX;
			goto done_nochar;
		}
		if (!libc_isdigit(ch))
			goto err_synbad;
		*p_state = UNVIS_BSTATE_AMPPD;
		ATTR_FALLTHROUGH
	case UNVIS_BSTATE_AMPPD:
		if (ch == ';')
			goto done_valid_and_reset;
		if (!libc_isdigit(ch))
			goto err_synbad;
		if (__hybrid_overflow_umul((unsigned char)*p_outbyte, 10, (unsigned char *)p_outbyte))
			goto err_synbad;
		if (__hybrid_overflow_uadd((unsigned char)*p_outbyte, (unsigned char)(ch - '0'), (unsigned char *)p_outbyte))
			goto err_synbad;
		goto done_nochar;
	case UNVIS_BSTATE_AMPPX:
		if (!__libc_hex2int(ch, p_outbyte))
			goto err_synbad;
		*p_state = UNVIS_BSTATE_AMPPXX;
		goto done_nochar;
	case UNVIS_BSTATE_AMPPXX: {
		byte_t nibble;
		if (ch == ';')
			goto done_valid_and_reset;
		if (!__libc_hex2int(ch, &nibble))
			goto err_synbad;
		if (__hybrid_overflow_umul((unsigned char)*p_outbyte, 16, (unsigned char *)p_outbyte))
			goto err_synbad;
		if (__hybrid_overflow_uadd((unsigned char)*p_outbyte, nibble, (unsigned char *)p_outbyte))
			goto err_synbad;
	}	goto done_nochar;

	default:
err_synbad:
		*p_state = UNVIS_BSTATE_INIT;
		return __UNVIS_SYNBAD;
	}
	*p_outbyte = (char)ch;
	return __UNVIS_VALID;
#undef UNVIS_BSTATE_INIT
#undef UNVIS_BSTATE_BK
#undef UNVIS_BSTATE_OCT2
#undef UNVIS_BSTATE_OCT3
#undef UNVIS_BSTATE_BKM
#undef UNVIS_BSTATE_BKMD
#undef UNVIS_BSTATE_BKC
#undef UNVIS_BSTATE_HEXP
#undef UNVIS_BSTATE_HEX1
#undef UNVIS_BSTATE_HEX2
#undef UNVIS_BSTATE_EQ
#undef UNVIS_BSTATE_EQX
#undef UNVIS_BSTATE_EQLF
#undef UNVIS_BSTATE_AMP
#undef UNVIS_BSTATE_AMPP
#undef UNVIS_BSTATE_AMPPX
#undef UNVIS_BSTATE_AMPPXX
#undef UNVIS_BSTATE_AMPPD
#undef UNVIS_BSTATE_AMPN
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(vis, libc_vis);
DEFINE_PUBLIC_ALIAS(nvis, libc_nvis);
DEFINE_PUBLIC_ALIAS(svis, libc_svis);
DEFINE_PUBLIC_ALIAS(snvis, libc_snvis);
DEFINE_PUBLIC_ALIAS(strvis, libc_strvis);
DEFINE_PUBLIC_ALIAS(stravis, libc_stravis);
DEFINE_PUBLIC_ALIAS(strnvis_netbsd, libc_strnvis_netbsd);
DEFINE_PUBLIC_ALIAS(strnvis, libc_strnvis);
DEFINE_PUBLIC_ALIAS(strsvis, libc_strsvis);
DEFINE_PUBLIC_ALIAS(strsnvis, libc_strsnvis);
DEFINE_PUBLIC_ALIAS(strvisx, libc_strvisx);
DEFINE_PUBLIC_ALIAS(strnvisx, libc_strnvisx);
DEFINE_PUBLIC_ALIAS(strenvisx, libc_strenvisx);
DEFINE_PUBLIC_ALIAS(strsvisx, libc_strsvisx);
DEFINE_PUBLIC_ALIAS(strsnvisx, libc_strsnvisx);
DEFINE_PUBLIC_ALIAS(strsenvisx, libc_strsenvisx);
DEFINE_PUBLIC_ALIAS(strunvis, libc_strunvis);
DEFINE_PUBLIC_ALIAS(strnunvis_netbsd, libc_strnunvis_netbsd);
DEFINE_PUBLIC_ALIAS(strnunvis, libc_strnunvis);
DEFINE_PUBLIC_ALIAS(strunvisx, libc_strunvisx);
DEFINE_PUBLIC_ALIAS(strnunvisx, libc_strnunvisx);
DEFINE_PUBLIC_ALIAS(unvis, libc_unvis);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_VIS_C */
