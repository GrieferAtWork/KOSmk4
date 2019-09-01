/* HASH 0xa175d246 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBC_UNICODE_H
#define _LIBC_UNICODE_H 1

#include <__stdinc.h>
#include <__crt.h>
#include "slow/unicode.h"

/* Read a single Unicode character from a given UTF-8 string */
#define __libc_unicode_readutf8 __libc_slow_unicode_readutf8
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
#define __libc_unicode_readutf8_rev __libc_slow_unicode_readutf8_rev
/* Same as `unicode_readutf8()', but don't read past `text_end' */
#define __libc_unicode_readutf8_n __libc_slow_unicode_readutf8_n
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
#define __libc_unicode_readutf8_rev_n __libc_slow_unicode_readutf8_rev_n
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
#define __libc_unicode_writeutf8 __libc_slow_unicode_writeutf8
#define __LIBC_UNICODE_UTF8_MAXLEN       8
#define __LIBC_UNICODE_UTF8_CURLEN       7
#define __LIBC_UNICODE_UTF16_MAXLEN      2
#define __LIBC_UNICODE_UTF16_CURLEN      2
#define __LIBC_UNICODE_UTF32_MAXLEN      1
#define __LIBC_UNICODE_UTF32_CURLEN      1
#define __LIBC_UNICODE_ISVALIDUTF16(ch) (sizeof(ch) == 1 ? 1 : ((sizeof(ch) == 2 || (ch) <= 0x10ffff)) && ((ch) < 0xd800 || (ch) > 0xdfff))
#define __LIBC_UNICODE_MAXCHAR           0x10ffff
#define __LIBC_UNICODE_8TO16_MAXBUF(num_chars)   (num_chars)
#define __LIBC_UNICODE_8TO32_MAXBUF(num_chars)   (num_chars)
#define __LIBC_UNICODE_16TO8_MAXBUF(num_chars)  ((num_chars) * 3)
#define __LIBC_UNICODE_16TO32_MAXBUF(num_chars)  (num_chars)
#define __LIBC_UNICODE_32TO8_MAXBUF(num_chars)  ((num_chars) * 7)
#define __LIBC_UNICODE_32TO16_MAXBUF(num_chars) ((num_chars) * 2)

__DECL_BEGIN

#ifdef __CRT_HAVE___unicode_descriptor
#ifndef __UNICODE_FPRINT
#define __UNICODE_FPRINT   0x0001 /* The character is printable, or SPC (` '). */
#define __UNICODE_FALPHA   0x0002 /* The character is alphabetic. */
#define __UNICODE_FSPACE   0x0004 /* The character is a space-character. */
#define __UNICODE_FLF      0x0008 /* Line-feed/line-break character. */
#define __UNICODE_FLOWER   0x0010 /* Lower-case. */
#define __UNICODE_FUPPER   0x0020 /* Upper-case. */
#define __UNICODE_FTITLE   0x0040 /* Title-case. */
#define __UNICODE_FCNTRL   0x0080 /* Control character. */
#define __UNICODE_FDIGIT   0x0100 /* The character is a digit. e.g.: `²' (sqare; `ut_digit' is `2') */
#define __UNICODE_FDECIMAL 0x0200 /* The character is a decimal. e.g: `5' (ascii; `ut_digit' is `5') */
#define __UNICODE_FSYMSTRT 0x0400 /* The character can be used as the start of an identifier. */
#define __UNICODE_FSYMCONT 0x0800 /* The character can be used to continue an identifier. */
/*      __UNICODE_F        0x1000 */
/*      __UNICODE_F        0x2000 */
/*      __UNICODE_F        0x4000 */
/*      __UNICODE_F        0x8000 */
struct __unitraits {
	__UINT16_TYPE__ const __ut_flags; /* Character flags (Set of `__UNICODE_F*') */
	__UINT8_TYPE__  const __ut_digit; /* Digit/decimal value (`unicode_isnumeric'), or 0. */
	__UINT8_TYPE__  const __ut_fold;  /* Unicode fold extension index, or `0xff'. */
	__INT32_TYPE__  const __ut_lower; /* Delta added to the character to convert it to lowercase, or 0. */
	__INT32_TYPE__  const __ut_upper; /* Delta added to the character to convert it to uppercase, or 0. */
	__INT32_TYPE__  const __ut_title; /* Delta added to the character to convert it to titlecase, or 0. */
};
__LIBC __ATTR_RETNONNULL __ATTR_CONST struct __unitraits *
__NOTHROW(__LIBCCALL __unicode_descriptor)(__CHAR32_TYPE__ __ch);
#endif /* !__UNICODE_FPRINT */
#ifdef __CRT_HAVE_unicode_fold
#define __LIBC_UNICODE_FOLDED_MAX 3
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_unicode_fold,(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[__LIBC_UNICODE_FOLDED_MAX]),unicode_fold,(__ch,__buf))
#else /* unicode_fold... */
#define __LIBC_UNICODE_FOLDED_MAX 1
__LOCAL __ATTR_RETNONNULL __ATTR_NONNULL((2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __libc_unicode_fold)(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[__LIBC_UNICODE_FOLDED_MAX]) {
	__buf[0] = __ch;
	return __buf + 1;
}
#endif /* !unicode_fold... */
#ifdef __CRT_HAVE___unicode_asciiflags
#ifndef ____unicode_asciiflags_defined
#define ____unicode_asciiflags_defined 1
__LIBC __UINT16_TYPE__ const __unicode_asciiflags[256];
#endif /* !____unicode_asciiflags_defined */
#define __libc_unicode_flags(ch)        (sizeof(ch) == 1 ? __unicode_asciiflags[(uint8_t)(ch)] : __unicode_descriptor(ch)->__ut_flags)
#define __libc_unicode_asciiisupper(ch) (__unicode_asciiflags[(__UINT8_TYPE__)(ch)] & __UNICODE_FUPPER)
#define __libc_unicode_asciiislower(ch) (__unicode_asciiflags[(__UINT8_TYPE__)(ch)] & __UNICODE_FLOWER)
#define __libc_unicode_asciitolower(ch) (__libc_unicode_asciiisupper(ch) ? (__UINT8_TYPE__)(ch) + 0x20 : (__UINT8_TYPE__)(ch))
#define __libc_unicode_asciitoupper(ch) (__libc_unicode_asciiislower(ch) ? (__UINT8_TYPE__)(ch) - 0x20 : (__UINT8_TYPE__)(ch))
#define __libc_unicode_asciitotitle(ch) (__libc_unicode_asciiislower(ch) ? (__UINT8_TYPE__)(ch) - 0x20 : (__UINT8_TYPE__)(ch))
#define __libc_unicode_asciiasdigit(ch) ((__UINT8_TYPE__)(ch) - 0x30)
#define __libc_unicode_tolower(ch)      (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__libc_unicode_asciitolower(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_lower))
#define __libc_unicode_toupper(ch)      (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__libc_unicode_asciitoupper(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_upper))
#define __libc_unicode_totitle(ch)      (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__libc_unicode_asciitoupper(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_title))
#define __libc_unicode_asdigit(ch)      (sizeof(ch) == 1 ? __libc_unicode_asciiasdigit(ch) : __unicode_descriptor(ch)->__ut_digit)
#else /* __CRT_HAVE___unicode_asciiflags */
#define __libc_unicode_flags(ch)        (__unicode_descriptor(ch)->__ut_flags)
#define __libc_unicode_tolower(ch)      (__CHAR32_TYPE__)((ch)+__unicode_descriptor(ch)->__ut_lower)
#define __libc_unicode_toupper(ch)      (__CHAR32_TYPE__)((ch)+__unicode_descriptor(ch)->__ut_upper)
#define __libc_unicode_totitle(ch)      (__CHAR32_TYPE__)((ch)+__unicode_descriptor(ch)->__ut_title)
#define __libc_unicode_asdigit(ch)      (__unicode_descriptor(ch)->__ut_digit)
#endif /* !__CRT_HAVE___unicode_asciiflags */
#define __libc_unicode_isalpha(ch)      (__libc_unicode_flags(ch) & __UNICODE_FALPHA)
#define __libc_unicode_islower(ch)      (__libc_unicode_flags(ch) & __UNICODE_FLOWER)
#define __libc_unicode_isupper(ch)      (__libc_unicode_flags(ch) & __UNICODE_FUPPER)
#define __libc_unicode_isalnum(ch)      (__libc_unicode_flags(ch) & (__UNICODE_FALPHA|__UNICODE_FDECIMAL))
#define __libc_unicode_isspace(ch)      (__libc_unicode_flags(ch) & __UNICODE_FSPACE)
#define __libc_unicode_istab(ch)        ((ch) == 9)
#define __libc_unicode_islf(ch)         (__libc_unicode_flags(ch) & __UNICODE_FLF)
#define __libc_unicode_isprint(ch)      (__libc_unicode_flags(ch) & __UNICODE_FPRINT)
#define __libc_unicode_isdigit(ch)      (__libc_unicode_flags(ch) & __UNICODE_FDIGIT)
#define __libc_unicode_isdecimal(ch)    (__libc_unicode_flags(ch) & __UNICODE_FDECIMAL)
#define __libc_unicode_isnumeric(ch)    (__libc_unicode_flags(ch) & (__UNICODE_FDIGIT|__UNICODE_FDECIMAL))
#define __libc_unicode_istitle(ch)      (__libc_unicode_flags(ch) & (__UNICODE_FTITLE|__UNICODE_FUPPER))
#define __libc_unicode_issymstrt(ch)    (__libc_unicode_flags(ch) & __UNICODE_FSYMSTRT)
#define __libc_unicode_issymcont(ch)    (__libc_unicode_flags(ch) & __UNICODE_FSYMCONT)
#define __libc_unicode_iscntrl(ch)      (__libc_unicode_flags(ch) & __UNICODE_FCNTRL)
#else /* __CRT_HAVE___unicode_descriptor */
#include <libc/ctype.h>

#define __LIBC_UNICODE_FOLDED_MAX 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __libc_unicode_fold)(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[__LIBC_UNICODE_FOLDED_MAX]) {
	__buf[0] = __ch;
	return __buf + 1;
}

#define __libc_unicode_tolower(ch)  (__libc_unicode_isupper(ch) ? (__CHAR32_TYPE__)(ch) + 0x20 : (__CHAR32_TYPE__)(ch))
#define __libc_unicode_toupper(ch)  (__libc_unicode_islower(ch) ? (__CHAR32_TYPE__)(ch) - 0x20 : (__CHAR32_TYPE__)(ch))
#define __libc_unicode_totitle(ch)  (__libc_unicode_islower(ch) ? (__CHAR32_TYPE__)(ch) - 0x20 : (__CHAR32_TYPE__)(ch))
#define __libc_unicode_asdigit(ch) ((__UINT8_TYPE__)(ch) - 0x30)
#define __libc_unicode_isalpha(ch)   __libc_isalpha(ch)
#define __libc_unicode_islower(ch)   __libc_islower(ch)
#define __libc_unicode_isupper(ch)   __libc_isupper(ch)
#define __libc_unicode_isalnum(ch)   __libc_isalnum(ch)
#define __libc_unicode_isspace(ch)   __libc_isspace(ch)
#define __libc_unicode_istab(ch)     ((ch) == 9)
#define __libc_unicode_islf(ch)      ((ch) == 13 || (ch) == 10)
#define __libc_unicode_isprint(ch)   __libc_isprint(ch)
#define __libc_unicode_isdigit(ch)   __libc_isdigit(ch)
#define __libc_unicode_isdecimal(ch) __libc_unicode_isdigit(ch)
#define __libc_unicode_isnumeric(ch) __libc_unicode_isdigit(ch)
#define __libc_unicode_istitle(ch)   __libc_unicode_isupper(ch)
#define __libc_unicode_issymstrt(ch) __libc_isalpha(ch)
#define __libc_unicode_issymcont(ch) __libc_isalnum(ch)
#define __libc_unicode_iscntrl(ch)   __libc_iscntrl(ch)
#endif /* !__CRT_HAVE___unicode_descriptor */

__DECL_END

#endif /* !_LIBC_UNICODE_H */
