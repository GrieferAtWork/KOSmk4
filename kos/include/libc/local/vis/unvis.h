/* HASH CRC-32:0x768491ca */
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
#ifndef __local_unvis_defined
#define __local_unvis_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bcmp_defined
#define __local___localdep_bcmp_defined
#ifdef __CRT_HAVE_bcmp
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memcmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_bcmp_defined */
#ifndef __local___localdep_isdigit_defined
#define __local___localdep_isdigit_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isdigit) && defined(__CRT_HAVE_isdigit)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isdigit,(int __ch),isdigit,{ return __crt_isdigit(__ch); })
#elif defined(__crt_isdigit)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isdigit)(int __ch) { return __crt_isdigit(__ch); }
#elif __has_builtin(__builtin_isdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isdigit)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isdigit,(int __ch),isdigit,{ return __builtin_isdigit(__ch); })
#elif defined(__CRT_HAVE_isdigit)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isdigit,(int __ch),isdigit,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isdigit.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isdigit __LIBC_LOCAL_NAME(isdigit)
#endif /* !... */
#endif /* !__local___localdep_isdigit_defined */
#ifndef __local___localdep_isgraph_defined
#define __local___localdep_isgraph_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isgraph) && defined(__CRT_HAVE_isgraph)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph,(int __ch),isgraph,{ return __crt_isgraph(__ch); })
#elif defined(__crt_isgraph)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isgraph)(int __ch) { return __crt_isgraph(__ch); }
#elif __has_builtin(__builtin_isgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isgraph)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph,(int __ch),isgraph,{ return __builtin_isgraph(__ch); })
#elif defined(__CRT_HAVE_isgraph)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph,(int __ch),isgraph,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isgraph.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isgraph __LIBC_LOCAL_NAME(isgraph)
#endif /* !... */
#endif /* !__local___localdep_isgraph_defined */
#ifndef __local___localdep_isxdigit_defined
#define __local___localdep_isxdigit_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isxdigit) && defined(__CRT_HAVE_isxdigit)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isxdigit,(int __ch),isxdigit,{ return __crt_isxdigit(__ch); })
#elif defined(__crt_isxdigit)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isxdigit)(int __ch) { return __crt_isxdigit(__ch); }
#elif __has_builtin(__builtin_isxdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isxdigit)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isxdigit,(int __ch),isxdigit,{ return __builtin_isxdigit(__ch); })
#elif defined(__CRT_HAVE_isxdigit)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isxdigit,(int __ch),isxdigit,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isxdigit.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isxdigit __LIBC_LOCAL_NAME(isxdigit)
#endif /* !... */
#endif /* !__local___localdep_isxdigit_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/vis.h>
#include <hybrid/__overflow.h>
#include <libc/template/hex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(unvis) __ATTR_INOUT(3) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unvis))(char *__p_outbyte, int __inbyte, int *__p_state, int __flags) {
	unsigned int __bstate = ((unsigned int)*__p_state) & 0xff;
	__BYTE_TYPE__ __ch = (__BYTE_TYPE__)(unsigned int)__inbyte;
#define __UNVIS_BSTATE_INIT   0x00 /* Initial zero-shift state */
#define __UNVIS_BSTATE_BK     0x01 /* After '\' */
#define __UNVIS_BSTATE_OCT2   0x02 /* After '\1' */
#define __UNVIS_BSTATE_OCT3   0x03 /* After '\12' */
#define __UNVIS_BSTATE_BKM    0x04 /* After '\M' */
#define __UNVIS_BSTATE_BKMD   0x05 /* After '\M-' */
#define __UNVIS_BSTATE_BKC    0x06 /* After '\^' (C: Circumflex) */
#define __UNVIS_BSTATE_HEXP   0x07 /* After '%' */
#define __UNVIS_BSTATE_HEX1   0x08 /* After '\x' */
#define __UNVIS_BSTATE_HEX2   0x09 /* After '\xA' or '%A' */
#define __UNVIS_BSTATE_EQ     0x0a /* After '=' */
#define __UNVIS_BSTATE_EQX    0x0b /* After '=A' */
#define __UNVIS_BSTATE_EQLF   0x0c /* After '=[CR|LF]' */
#define __UNVIS_BSTATE_AMP    0x0d /* After '&' */
#define __UNVIS_BSTATE_AMPP   0x0e /* After '&#' */
#define __UNVIS_BSTATE_AMPPX  0x0f /* After '&#x' */
#define __UNVIS_BSTATE_AMPPXX 0x10 /* After '&#x<0-9a-fA-F>' */
#define __UNVIS_BSTATE_AMPPD  0x11 /* After '&#<0-9>' */
#define __UNVIS_BSTATE_AMPN   0x12 /* After '&foo' */

	/* Check for the special end-marker flag. */
	if (__flags & __UNVIS_END) {
		switch (__bstate) {

		case __UNVIS_BSTATE_OCT2:
		case __UNVIS_BSTATE_OCT3:
		case __UNVIS_BSTATE_HEX2:
			/* NOTE: Technically, `UNVIS_VALIDPUSH' would have made more
			 *       sense here (since we're not "consuming" the end  of
			 *       the input string), but better not change the abi... */
			goto __done_valid_and_reset; /* goto done_valid_noconsume_and_reset; */

		case __UNVIS_BSTATE_INIT:
__done_nochar:
			return __UNVIS_NOCHAR;
		default:
			goto __err_synbad;
		}
	}

	switch (__builtin_expect(__bstate, __UNVIS_BSTATE_INIT)) {

	case __UNVIS_BSTATE_INIT:
		/* Check for escape sequence start characters. */
		switch (__ch) {

		case '\\':
			if (!(__flags & __VIS_NOESCAPE)) {
				*__p_state = __UNVIS_BSTATE_BK;
				goto __done_nochar;
			}
			break;

		case '%':
			if (__flags & __VIS_HTTPSTYLE) {
				*__p_outbyte = 0x00;
				*__p_state = __UNVIS_BSTATE_HEXP;
				goto __done_nochar;
			}
			break;

		case '=':
			if (__flags & __VIS_MIMESTYLE) {
				*__p_state = __UNVIS_BSTATE_EQ;
				goto __done_nochar;
			}
			break;

		case '&':
			if (__flags & __VIS_HTTP1866) {
				*__p_state = __UNVIS_BSTATE_AMP;
				goto __done_nochar;
			}
			break;

		default:
			break;
		}
		break;

	case __UNVIS_BSTATE_BK:
		switch (__ch) {

		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			*__p_outbyte = (char)(unsigned char)(__ch - '0');
			*__p_state   = __UNVIS_BSTATE_OCT2;
			goto __done_nochar;

		case 'M':
			*__p_outbyte = 0x80;
			*__p_state   = __UNVIS_BSTATE_BKM;
			goto __done_nochar;
		case '^':
			*__p_outbyte = 0x00;
			*__p_state   = __UNVIS_BSTATE_BKC;
			goto __done_nochar;
		case 'x':
			*__p_outbyte = 0x00;
			*__p_state   = __UNVIS_BSTATE_HEX1;
			goto __done_nochar;
		case 'n': __ch = 0x0a; goto __reset_and_return_ch;
		case 'r': __ch = 0x0d; goto __reset_and_return_ch;
		case 'b': __ch = 0x08; goto __reset_and_return_ch;
		case 'a': __ch = 0x07; goto __reset_and_return_ch;
		case 'v': __ch = 0x0b; goto __reset_and_return_ch;
		case 't': __ch = 0x09; goto __reset_and_return_ch;
		case 'f': __ch = 0x0c; goto __reset_and_return_ch;
		case 's': __ch = 0x20; goto __reset_and_return_ch; /* BSD-extension */
		case 'e': /* KOS-extension */
		case 'E': __ch = 0x1b; goto __reset_and_return_ch; /* BSD-extension */
		case '$':
		case '\n': *__p_state = __UNVIS_BSTATE_INIT; goto __done_nochar;

		default:
			if (!(__NAMESPACE_LOCAL_SYM __localdep_isgraph)(__ch))
				goto __err_synbad;
			/* Fallthru to re-return `ch' */
__reset_and_return_ch:
			*__p_state = __UNVIS_BSTATE_INIT;
		}
		break;

	case __UNVIS_BSTATE_OCT2:
	case __UNVIS_BSTATE_OCT3:
		if (__ch >= '0' && __ch <= '7') {
			*__p_outbyte <<= 3;
			*__p_outbyte |= (char)(unsigned char)(__ch - '0');
			if (*__p_state == __UNVIS_BSTATE_OCT3)
				goto __done_valid_and_reset;
			*__p_state = __UNVIS_BSTATE_OCT3;
			goto __done_nochar;
		}
__done_valid_noconsume_and_reset:
		*__p_state = __UNVIS_BSTATE_INIT;
		return __UNVIS_VALIDPUSH;

	case __UNVIS_BSTATE_BKM:
		if (__ch == '-') {
			*__p_state = __UNVIS_BSTATE_BKMD;
			goto __done_nochar;
		}
		if (__ch == '^') {
			*__p_state = __UNVIS_BSTATE_BKC;
			goto __done_nochar;
		}
		goto __err_synbad;

	case __UNVIS_BSTATE_BKMD:
		*__p_outbyte |= (char)__ch;
__done_valid_and_reset:
		*__p_state = __UNVIS_BSTATE_INIT;
/*done_valid:*/
		return __UNVIS_VALID;

	case __UNVIS_BSTATE_BKC:
		if (__ch == '?') {
			*__p_outbyte |= 0x7f;
		} else {
			*__p_outbyte |= (char)(__ch & 0x1f);
		}
		goto __done_valid_and_reset;

	case __UNVIS_BSTATE_HEX1:
		if (!(__NAMESPACE_LOCAL_SYM __localdep_isxdigit)(__ch))
			goto __err_synbad;
		__ATTR_FALLTHROUGH
	case __UNVIS_BSTATE_HEXP:
	case __UNVIS_BSTATE_HEX2: {
		__BYTE_TYPE__ __nibble;
		if (!__libc_hex2int(__ch, &__nibble))
			goto __done_valid_noconsume_and_reset;
		*__p_outbyte <<= 4;
		*__p_outbyte |= (char)__nibble;
		if (*__p_state == __UNVIS_BSTATE_HEX2)
			goto __done_valid_and_reset;
		*__p_state = __UNVIS_BSTATE_HEX2;
		goto __done_nochar;
	}

	case __UNVIS_BSTATE_EQ:
		if (__ch == '\r' || __ch == '\n') {
			*__p_state = __UNVIS_BSTATE_EQLF;
			goto __done_nochar;
		}
		if ((__NAMESPACE_LOCAL_SYM __localdep_isdigit)(__ch)) {
			*__p_outbyte = (char)(__BYTE_TYPE__)(__ch - '0') << 4;
			*__p_state   = __UNVIS_BSTATE_EQX;
			goto __done_nochar;
		}
		if (__ch >= 'A' && __ch <= 'F') {
			*__p_outbyte = (char)(__BYTE_TYPE__)(10 + __ch - 'A') << 4;
			*__p_state   = __UNVIS_BSTATE_EQX;
			goto __done_nochar;
		}
		goto __err_synbad;

	case __UNVIS_BSTATE_EQX:
		if ((__NAMESPACE_LOCAL_SYM __localdep_isdigit)(__ch)) {
			*__p_outbyte |= (char)(__BYTE_TYPE__)(__ch - '0');
			goto __done_valid_and_reset;
		}
		if (__ch >= 'A' && __ch <= 'F') {
			*__p_outbyte |= (char)(__BYTE_TYPE__)(10 + __ch - 'A');
			goto __done_valid_and_reset;
		}
		goto __err_synbad;

	case __UNVIS_BSTATE_EQLF:
		if (__ch == '\r' || __ch == '\n')
			goto __done_nochar;
		if (__ch == '=') {
			*__p_state = __UNVIS_BSTATE_EQ;
			goto __done_nochar;
		}
		goto __reset_and_return_ch;

	case __UNVIS_BSTATE_AMP:
		*__p_outbyte = (char)0;
		if (__ch == '#') {
			*__p_state = __UNVIS_BSTATE_AMPP;
			goto __done_nochar;
		}
		*__p_state = __UNVIS_BSTATE_AMPN;
		__ATTR_FALLTHROUGH
	case __UNVIS_BSTATE_AMPN: {
		/* We only support names for ASCII characters (because we want to remain  codec-neutral)
		 * Note also that KOS's libiconv contains a full database of XML characters, though that
		 * one would already be too large for us to use here. */
		struct xml_ent {
			char   __xe_name[7]; /* Entity name */
			__BYTE_TYPE__ __xe_byte;    /* Entity byte */
		};
		static struct xml_ent const __xml_entities[] = {
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
		__BYTE_TYPE__ __pos = (__BYTE_TYPE__)*__p_outbyte;
		__BYTE_TYPE__ __len = ((unsigned int)*__p_state) >> 8;
		if __unlikely(__len >= __COMPILER_LENOF(__xml_entities[0].__xe_name))
			goto __err_synbad;
		if __unlikely(__pos >= __COMPILER_LENOF(__xml_entities))
			goto __err_synbad;
		if __unlikely(__ch == '\0')
			goto __err_synbad;
		if (__ch == ';')
			__ch = '\0';
		for (;;) {
			if (__xml_entities[__pos].__xe_name[__len] == (char)__ch)
				break; /* Found it! */
			++__pos;
			if __unlikely(__pos >= __COMPILER_LENOF(__xml_entities))
				goto __err_synbad; /* No such name. */
			if ((__NAMESPACE_LOCAL_SYM __localdep_bcmp)(__xml_entities[__pos - 1].__xe_name,
			         __xml_entities[__pos - 0].__xe_name,
			         sizeof(__xml_entities[0].__xe_name)) != 0)
				goto __err_synbad; /* Prefix changed */
		}
		++__len;
		if (__ch == '\0') {
			/* Found entity! */
			__ch = __xml_entities[__pos].__xe_byte;
			goto __reset_and_return_ch;
		}

		/* Write back the updated database cursor. */
		*__p_outbyte = (char)__pos;
		*__p_state   = ((unsigned int)__len << 8) | __UNVIS_BSTATE_AMPN;
	}	goto __done_nochar;

	case __UNVIS_BSTATE_AMPP:
		if (__ch == 'x') {
			*__p_state = __UNVIS_BSTATE_AMPPX;
			goto __done_nochar;
		}
		if (!(__NAMESPACE_LOCAL_SYM __localdep_isdigit)(__ch))
			goto __err_synbad;
		*__p_state = __UNVIS_BSTATE_AMPPD;
		__ATTR_FALLTHROUGH
	case __UNVIS_BSTATE_AMPPD:
		if (__ch == ';')
			goto __done_valid_and_reset;
		if (!(__NAMESPACE_LOCAL_SYM __localdep_isdigit)(__ch))
			goto __err_synbad;
		if (__hybrid_overflow_umul((unsigned char)*__p_outbyte, 10, (unsigned char *)__p_outbyte))
			goto __err_synbad;
		if (__hybrid_overflow_uadd((unsigned char)*__p_outbyte, (unsigned char)(__ch - '0'), (unsigned char *)__p_outbyte))
			goto __err_synbad;
		goto __done_nochar;
	case __UNVIS_BSTATE_AMPPX:
		if (!__libc_hex2int(__ch, __p_outbyte))
			goto __err_synbad;
		*__p_state = __UNVIS_BSTATE_AMPPXX;
		goto __done_nochar;
	case __UNVIS_BSTATE_AMPPXX: {
		__BYTE_TYPE__ __nibble;
		if (__ch == ';')
			goto __done_valid_and_reset;
		if (!__libc_hex2int(__ch, &__nibble))
			goto __err_synbad;
		if (__hybrid_overflow_umul((unsigned char)*__p_outbyte, 16, (unsigned char *)__p_outbyte))
			goto __err_synbad;
		if (__hybrid_overflow_uadd((unsigned char)*__p_outbyte, __nibble, (unsigned char *)__p_outbyte))
			goto __err_synbad;
	}	goto __done_nochar;

	default:
__err_synbad:
		*__p_state = __UNVIS_BSTATE_INIT;
		return __UNVIS_SYNBAD;
	}
	*__p_outbyte = (char)__ch;
	return __UNVIS_VALID;
#undef __UNVIS_BSTATE_INIT
#undef __UNVIS_BSTATE_BK
#undef __UNVIS_BSTATE_OCT2
#undef __UNVIS_BSTATE_OCT3
#undef __UNVIS_BSTATE_BKM
#undef __UNVIS_BSTATE_BKMD
#undef __UNVIS_BSTATE_BKC
#undef __UNVIS_BSTATE_HEXP
#undef __UNVIS_BSTATE_HEX1
#undef __UNVIS_BSTATE_HEX2
#undef __UNVIS_BSTATE_EQ
#undef __UNVIS_BSTATE_EQX
#undef __UNVIS_BSTATE_EQLF
#undef __UNVIS_BSTATE_AMP
#undef __UNVIS_BSTATE_AMPP
#undef __UNVIS_BSTATE_AMPPX
#undef __UNVIS_BSTATE_AMPPXX
#undef __UNVIS_BSTATE_AMPPD
#undef __UNVIS_BSTATE_AMPN
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unvis_defined
#define __local___localdep_unvis_defined
#define __localdep_unvis __LIBC_LOCAL_NAME(unvis)
#endif /* !__local___localdep_unvis_defined */
#endif /* !__local_unvis_defined */
