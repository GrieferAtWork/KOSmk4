/* HASH CRC-32:0xc802af3d */
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
#ifndef _UNICODE_H
#define _UNICODE_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/__byteorder.h>
#include <hybrid/__byteswap.h>
#include <hybrid/typecore.h>

#include <bits/crt/format-printer.h>
#include <bits/crt/mbstate.h>
#include <bits/crt/uformat-printer.h>
#include <bits/crt/wformat-printer.h>
#include <bits/types.h>


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __utf8_seqlen_defined
#define __utf8_seqlen_defined 1
#ifdef __CRT_HAVE_unicode_utf8seqlen
__LIBC __uint8_t const unicode_utf8seqlen[256] __CASMNAME_SAME("unicode_utf8seqlen");
#else /* __CRT_HAVE_unicode_utf8seqlen */
#include <libc/local/unicode_utf8seqlen.h>
#define unicode_utf8seqlen __LOCAL_unicode_utf8seqlen
#endif /* !__CRT_HAVE_unicode_utf8seqlen */
#endif /* !__utf8_seqlen_defined */

/* The max length of any UTF-8 byte sequence describing a single unicode character. */
#define UNICODE_UTF8_MAXLEN   8   /* == unicode_utf8seqlen[0xff] */

/* The current length of any UTF-8 byte sequence produced by any 32-bit unicode character.
 * While `UNICODE_UTF8_MAXLEN' is the theoretical limit, it allows for up to 42 bits
 * of character digits, while `7' allows for up to `36' bits (`6' would allow `30').
 * As a consequence, the max number of bytes which may be written by `unicode_writeutf8()'
 * is `UNICODE_UTF8_CURLEN', as it takes a 32-bit unicode character.
 * >> char buf[UNICODE_UTF8_CURLEN];
 * >> size_t buflen = (size_t)(unicode_writeutf8(buf,ch) - buf); */
#define UNICODE_UTF8_CURLEN   7

/* The max length of any UTF-16 word sequence describing a single unicode character. */
#define UNICODE_UTF16_MAXLEN  2
#define UNICODE_UTF16_CURLEN  2

/* The max length of any UTF-32 word sequence describing a single unicode character. */
#define UNICODE_UTF32_MAXLEN  1
#define UNICODE_UTF32_CURLEN  1

/* UTF-16 surrogate ranges. */
#define UTF16_HIGH_SURROGATE_MIN 0xd800  /* High surrogate (aka. first byte) */
#define UTF16_HIGH_SURROGATE_MAX 0xdbff
#define UTF16_LOW_SURROGATE_MIN  0xdc00  /* Low surrogate (aka. second byte) */
#define UTF16_LOW_SURROGATE_MAX  0xdfff
#define UTF16_SURROGATE_SHIFT    0x10000 /* Addend when a surrogate is encountered */

/* Check if the given unicode character `ch' can be encoded in UTF-16,
 * returning non-zero if it can, and zero if not.
 * The below function `unicode_writeutf16()' will cause weak undefined
 * behavior if the passed character does not fulfill this requirement. */
#define UNICODE_ISVALIDUTF16(ch)                  \
	(sizeof(ch) == 1                              \
	 ? 1                                          \
	 : ((sizeof(ch) == 2 || (ch) <= 0x10ffff)) && \
	   ((ch) < 0xd800 || (ch) > 0xdfff))

/* The (currently) greatest unicode character */
#define UNICODE_MAXCHAR  0x10ffff

/* Evaluate to the worst-case max required buffer sizes
 * required by different format conversion functions of
 * the same name. */
#define UNICODE_8TO16_MAXBUF(num_chars)   (num_chars)
#define UNICODE_8TO32_MAXBUF(num_chars)   (num_chars)
#define UNICODE_16TO8_MAXBUF(num_chars)  ((num_chars) * 3)
#define UNICODE_16TO32_MAXBUF(num_chars)  (num_chars)
#define UNICODE_32TO8_MAXBUF(num_chars)  ((num_chars) * 7)
#define UNICODE_32TO16_MAXBUF(num_chars) ((num_chars) * 2)

#ifdef __CRT_HAVE_unicode_readutf8
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Read a single Unicode character from a given UTF-8 string */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8,(char const **__restrict __ptext),unicode_readutf8,(__ptext))
/* Read a single Unicode character from a given UTF-8 string */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8,(char **__restrict __ptext),unicode_readutf8,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Read a single Unicode character from a given UTF-8 string */
__CDECLARE(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8,(char const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf8 */
#include <libc/local/unicode/unicode_readutf8.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Read a single Unicode character from a given UTF-8 string */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8)(char const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8))(__ptext); }
/* Read a single Unicode character from a given UTF-8 string */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8)(char **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8))((char const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Read a single Unicode character from a given UTF-8 string */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8)(char const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf8 */

#ifdef __CRT_HAVE_unicode_readutf8_rev
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8_rev,(char const **__restrict __ptext),unicode_readutf8_rev,(__ptext))
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8_rev,(char **__restrict __ptext),unicode_readutf8_rev,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__CDECLARE(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8_rev,(char const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf8_rev */
#include <libc/local/unicode/unicode_readutf8_rev.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev)(char const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev))(__ptext); }
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev)(char **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev))((char const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf8_rev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev)(char const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf8_rev */

#ifdef __CRT_HAVE_unicode_readutf8_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf8()', but don't read past `text_end' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8_n,(char const **__restrict __ptext, char const *__text_end),unicode_readutf8_n,(__ptext,__text_end))
/* Same as `unicode_readutf8()', but don't read past `text_end' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8_n,(char **__restrict __ptext, char const *__text_end),unicode_readutf8_n,(__ptext,__text_end))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf8()', but don't read past `text_end' */
__CDECLARE(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8_n,(char const **__restrict __ptext, char const *__text_end),(__ptext,__text_end))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf8_n */
#include <libc/local/unicode/unicode_readutf8_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf8()', but don't read past `text_end' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8_n)(char const **__restrict __ptext, char const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_n))(__ptext, __text_end); }
/* Same as `unicode_readutf8()', but don't read past `text_end' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8_n)(char **__restrict __ptext, char const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_n))((char const **)__ptext, __text_end); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf8()', but don't read past `text_end' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf8_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8_n)(char const **__restrict __ptext, char const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_n))(__ptext, __text_end); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf8_n */

#ifdef __CRT_HAVE_unicode_readutf8_rev_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8_rev_n,(char const **__restrict __ptext, char const *__text_start),unicode_readutf8_rev_n,(__ptext,__text_start))
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8_rev_n,(char **__restrict __ptext, char const *__text_start),unicode_readutf8_rev_n,(__ptext,__text_start))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__CDECLARE(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf8_rev_n,(char const **__restrict __ptext, char const *__text_start),(__ptext,__text_start))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf8_rev_n */
#include <libc/local/unicode/unicode_readutf8_rev_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev_n)(char const **__restrict __ptext, char const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev_n))(__ptext, __text_start); }
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev_n)(char **__restrict __ptext, char const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev_n))((char const **)__ptext, __text_start); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf8_rev_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev_n)(char const **__restrict __ptext, char const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev_n))(__ptext, __text_start); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf8_rev_n */

#ifdef __CRT_HAVE_unicode_readutf16
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Read a single Unicode character from a given UTF-16 string */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16,(__CHAR16_TYPE__ const **__restrict __ptext),unicode_readutf16,(__ptext))
/* Read a single Unicode character from a given UTF-16 string */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16,(__CHAR16_TYPE__ **__restrict __ptext),unicode_readutf16,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Read a single Unicode character from a given UTF-16 string */
__CDECLARE(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16,(__CHAR16_TYPE__ const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16 */
#include <libc/local/unicode/unicode_readutf16.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Read a single Unicode character from a given UTF-16 string */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16)(__CHAR16_TYPE__ const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16))(__ptext); }
/* Read a single Unicode character from a given UTF-16 string */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16)(__CHAR16_TYPE__ **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16))((__CHAR16_TYPE__ const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Read a single Unicode character from a given UTF-16 string */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16)(__CHAR16_TYPE__ const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16 */

#ifdef __CRT_HAVE_unicode_readutf16_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16()', but don't read past `text_end' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_n,(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end),unicode_readutf16_n,(__ptext,__text_end))
/* Same as `unicode_readutf16()', but don't read past `text_end' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_n,(__CHAR16_TYPE__ **__restrict __ptext, __CHAR16_TYPE__ const *__text_end),unicode_readutf16_n,(__ptext,__text_end))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16()', but don't read past `text_end' */
__CDECLARE(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_n,(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end),(__ptext,__text_end))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_n */
#include <libc/local/unicode/unicode_readutf16_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16()', but don't read past `text_end' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_n)(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_n))(__ptext, __text_end); }
/* Same as `unicode_readutf16()', but don't read past `text_end' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_n)(__CHAR16_TYPE__ **__restrict __ptext, __CHAR16_TYPE__ const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_n))((__CHAR16_TYPE__ const **)__ptext, __text_end); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16()', but don't read past `text_end' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_n)(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_n))(__ptext, __text_end); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_n */

#ifdef __CRT_HAVE_unicode_readutf16_swap
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap,(__CHAR16_TYPE__ const **__restrict __ptext),unicode_readutf16_swap,(__ptext))
/* Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap,(__CHAR16_TYPE__ **__restrict __ptext),unicode_readutf16_swap,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__CDECLARE(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap,(__CHAR16_TYPE__ const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_swap */
#include <libc/local/unicode/unicode_readutf16_swap.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap)(__CHAR16_TYPE__ const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap))(__ptext); }
/* Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap)(__CHAR16_TYPE__ **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap))((__CHAR16_TYPE__ const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_swap, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap)(__CHAR16_TYPE__ const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_swap */

#ifdef __CRT_HAVE_unicode_readutf16_swap_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap_n,(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end),unicode_readutf16_swap_n,(__ptext,__text_end))
/* Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap_n,(__CHAR16_TYPE__ **__restrict __ptext, __CHAR16_TYPE__ const *__text_end),unicode_readutf16_swap_n,(__ptext,__text_end))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__CDECLARE(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap_n,(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end),(__ptext,__text_end))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_swap_n */
#include <libc/local/unicode/unicode_readutf16_swap_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_n)(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_n))(__ptext, __text_end); }
/* Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_n)(__CHAR16_TYPE__ **__restrict __ptext, __CHAR16_TYPE__ const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_n))((__CHAR16_TYPE__ const **)__ptext, __text_end); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_swap_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_n)(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_n))(__ptext, __text_end); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_swap_n */

#ifdef __CRT_HAVE_unicode_readutf16_rev
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_rev,(__CHAR16_TYPE__ const **__restrict __ptext),unicode_readutf16_rev,(__ptext))
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_rev,(__CHAR16_TYPE__ **__restrict __ptext),unicode_readutf16_rev,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__CDECLARE(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_rev,(__CHAR16_TYPE__ const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_rev */
#include <libc/local/unicode/unicode_readutf16_rev.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev)(__CHAR16_TYPE__ const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev))(__ptext); }
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev)(__CHAR16_TYPE__ **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev))((__CHAR16_TYPE__ const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_rev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev)(__CHAR16_TYPE__ const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_rev */

#ifdef __CRT_HAVE_unicode_readutf16_swap_rev
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap_rev,(__CHAR16_TYPE__ const **__restrict __ptext),unicode_readutf16_swap_rev,(__ptext))
/* Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap_rev,(__CHAR16_TYPE__ **__restrict __ptext),unicode_readutf16_swap_rev,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__CDECLARE(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap_rev,(__CHAR16_TYPE__ const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_swap_rev */
#include <libc/local/unicode/unicode_readutf16_swap_rev.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev)(__CHAR16_TYPE__ const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev))(__ptext); }
/* Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev)(__CHAR16_TYPE__ **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev))((__CHAR16_TYPE__ const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_swap_rev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev)(__CHAR16_TYPE__ const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_swap_rev */
#ifdef __CRT_HAVE_unicode_readutf16_rev_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_rev_n,(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_start),unicode_readutf16_rev_n,(__ptext,__text_start))
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_rev_n,(__CHAR16_TYPE__ **__restrict __ptext, __CHAR16_TYPE__ const *__text_start),unicode_readutf16_rev_n,(__ptext,__text_start))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__CDECLARE(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_rev_n,(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_start),(__ptext,__text_start))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_rev_n */
#include <libc/local/unicode/unicode_readutf16_rev_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev_n)(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev_n))(__ptext, __text_start); }
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev_n)(__CHAR16_TYPE__ **__restrict __ptext, __CHAR16_TYPE__ const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev_n))((__CHAR16_TYPE__ const **)__ptext, __text_start); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_rev_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev_n)(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev_n))(__ptext, __text_start); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_rev_n */
#ifdef __CRT_HAVE_unicode_readutf16_swap_rev_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap_rev_n,(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_start),unicode_readutf16_swap_rev_n,(__ptext,__text_start))
/* Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap_rev_n,(__CHAR16_TYPE__ **__restrict __ptext, __CHAR16_TYPE__ const *__text_start),unicode_readutf16_swap_rev_n,(__ptext,__text_start))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__CDECLARE(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,unicode_readutf16_swap_rev_n,(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_start),(__ptext,__text_start))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_swap_rev_n */
#include <libc/local/unicode/unicode_readutf16_swap_rev_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev_n)(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev_n))(__ptext, __text_start); }
/* Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev_n)(__CHAR16_TYPE__ **__restrict __ptext, __CHAR16_TYPE__ const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev_n))((__CHAR16_TYPE__ const **)__ptext, __text_start); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_swap_rev_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev_n)(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev_n))(__ptext, __text_start); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_swap_rev_n */

#ifdef __CRT_HAVE_unicode_writeutf8
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,unicode_writeutf8,(char *__restrict __dst, __CHAR32_TYPE__ __ch),(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf8 */
#include <libc/local/unicode/unicode_writeutf8.h>
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_writeutf8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL unicode_writeutf8)(char *__restrict __dst, __CHAR32_TYPE__ __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf8))(__dst, __ch); })
#endif /* !__CRT_HAVE_unicode_writeutf8 */

#ifdef __CRT_HAVE_unicode_writeutf16
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF16_CURLEN' bytes to `dst' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,unicode_writeutf16,(__CHAR16_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch),(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf16 */
#include <libc/local/unicode/unicode_writeutf16.h>
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF16_CURLEN' bytes to `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_writeutf16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL unicode_writeutf16)(__CHAR16_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf16))(__dst, __ch); })
#endif /* !__CRT_HAVE_unicode_writeutf16 */

#ifdef __CRT_HAVE_unicode_writeutf16_chk
/* Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,unicode_writeutf16_chk,(__CHAR16_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch),(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf16_chk */
#include <libc/local/unicode/unicode_writeutf16_chk.h>
/* Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_writeutf16_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __CHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL unicode_writeutf16_chk)(__CHAR16_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf16_chk))(__dst, __ch); })
#endif /* !__CRT_HAVE_unicode_writeutf16_chk */

#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Read a single Unicode character from a given UTF-32 string. */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) { return *(*__ptext)++; }
/* Read a single Unicode character from a given UTF-32 string. */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext) { return *(*__ptext)++; }
/* Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) { __CHAR32_TYPE__ __res = *(*__ptext++); return __hybrid_bswap32(__res); }
/* Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext) { __CHAR32_TYPE__ __res = *(*__ptext++); return __hybrid_bswap32(__res); }
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) { return *(--*__ptext); }
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext) { return *(--*__ptext); }
/* Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) { __CHAR32_TYPE__ __res = *(--*__ptext); return __hybrid_bswap32(__res); }
/* Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext) { __CHAR32_TYPE__ __res = *(--*__ptext); return __hybrid_bswap32(__res); }
/* Same as `unicode_readutf32()', but don't read past `text_end'. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __result;
}
/* Same as `unicode_readutf32()', but don't read past `text_end'. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	return unicode_readutf32_n((__CHAR32_TYPE__ const **)__ptext,__text_end);
}
/* Same as `unicode_readutf32()', but don't read before `text_start'. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __result;
}
/* Same as `unicode_readutf32()', but don't read before `text_start'. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	return unicode_readutf32_rev_n((__CHAR32_TYPE__ const **)__ptext,__text_start);
}
/* Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	return unicode_readutf32_swap_n((__CHAR32_TYPE__ const **)__ptext,__text_end);
}
/* Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	return unicode_readutf32_swap_rev_n((__CHAR32_TYPE__ const **)__ptext,__text_start);
}
}
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Read a single Unicode character from a given UTF-32 string. */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) {
	return *(*__ptext)++;
}
/* Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) {
	__CHAR32_TYPE__ __res = *(*__ptext++);
	return __hybrid_bswap32(__res);
}
/* Same as `unicode_readutf32', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) {
	return *(--*__ptext);
}
/* Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) {
	__CHAR32_TYPE__ __res = *(--*__ptext);
	return __hybrid_bswap32(__res);
}
/* Same as `unicode_readutf32()', but don't read past `text_end'. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __result;
}
/* Same as `unicode_readutf32()', but don't read before `text_start'. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __result;
}
/* Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define unicode_readutf16le        unicode_readutf16
#define unicode_readutf32le        unicode_readutf32
#define unicode_readutf16be        unicode_readutf16_swap
#define unicode_readutf32be        unicode_readutf32_swap
#define unicode_readutf16le_n      unicode_readutf16_n
#define unicode_readutf32le_n      unicode_readutf32_n
#define unicode_readutf16be_n      unicode_readutf16_swap_n
#define unicode_readutf32be_n      unicode_readutf32_swap_n
#define unicode_readutf16le_rev    unicode_readutf16_rev
#define unicode_readutf32le_rev    unicode_readutf32_rev
#define unicode_readutf16be_rev    unicode_readutf16_swap_rev
#define unicode_readutf32be_rev    unicode_readutf32_swap_rev
#define unicode_readutf16le_rev_n  unicode_readutf16_rev_n
#define unicode_readutf32le_rev_n  unicode_readutf32_rev_n
#define unicode_readutf16be_rev_n  unicode_readutf16_swap_rev_n
#define unicode_readutf32be_rev_n  unicode_readutf32_swap_rev_n
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define unicode_readutf16be        unicode_readutf16
#define unicode_readutf32be        unicode_readutf32
#define unicode_readutf16le        unicode_readutf16_swap
#define unicode_readutf32le        unicode_readutf32_swap
#define unicode_readutf16be_n      unicode_readutf16_n
#define unicode_readutf32be_n      unicode_readutf32_n
#define unicode_readutf16le_n      unicode_readutf16_swap_n
#define unicode_readutf32le_n      unicode_readutf32_swap_n
#define unicode_readutf16be_rev    unicode_readutf16_rev
#define unicode_readutf32be_rev    unicode_readutf32_rev
#define unicode_readutf16le_rev    unicode_readutf16_swap_rev
#define unicode_readutf32le_rev    unicode_readutf32_swap_rev
#define unicode_readutf16be_rev_n  unicode_readutf16_rev_n
#define unicode_readutf32be_rev_n  unicode_readutf32_rev_n
#define unicode_readutf16le_rev_n  unicode_readutf16_swap_rev_n
#define unicode_readutf32le_rev_n  unicode_readutf32_swap_rev_n
#endif

/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF32_CURLEN' bytes to `dst' */
__LOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
(__LIBCCALL unicode_writeutf32)(/*utf-32*/ __CHAR32_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch) {
	*__dst++ = __ch;
	return __dst;
}

#ifdef __CRT_HAVE_unicode_8to16
/* Convert a given utf-8 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,unicode_8to16,(__CHAR16_TYPE__ *__restrict __utf16_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_characters),(__utf16_dst,__utf8_text,__utf8_characters))
#else /* __CRT_HAVE_unicode_8to16 */
#include <libc/local/unicode/unicode_8to16.h>
/* Convert a given utf-8 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_8to16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL unicode_8to16)(__CHAR16_TYPE__ *__restrict __utf16_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_characters) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_8to16))(__utf16_dst, __utf8_text, __utf8_characters); })
#endif /* !__CRT_HAVE_unicode_8to16 */

#ifdef __CRT_HAVE_unicode_8to16_chk
/* Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character.
 * @return: NULL: Attempted to write an invalid character */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,unicode_8to16_chk,(__CHAR16_TYPE__ *__restrict __utf16_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_characters),(__utf16_dst,__utf8_text,__utf8_characters))
#else /* __CRT_HAVE_unicode_8to16_chk */
#include <libc/local/unicode/unicode_8to16_chk.h>
/* Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character.
 * @return: NULL: Attempted to write an invalid character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_8to16_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __CHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL unicode_8to16_chk)(__CHAR16_TYPE__ *__restrict __utf16_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_characters) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_8to16_chk))(__utf16_dst, __utf8_text, __utf8_characters); })
#endif /* !__CRT_HAVE_unicode_8to16_chk */

#ifdef __CRT_HAVE_unicode_8to32
/* Convert a given utf-8 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_characters)' dwords, or `*4' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,unicode_8to32,(__CHAR32_TYPE__ *__restrict __utf32_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_characters),(__utf32_dst,__utf8_text,__utf8_characters))
#else /* __CRT_HAVE_unicode_8to32 */
#include <libc/local/unicode/unicode_8to32.h>
/* Convert a given utf-8 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_characters)' dwords, or `*4' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_8to32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *__NOTHROW_NCX(__LIBCCALL unicode_8to32)(__CHAR32_TYPE__ *__restrict __utf32_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_characters) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_8to32))(__utf32_dst, __utf8_text, __utf8_characters); })
#endif /* !__CRT_HAVE_unicode_8to32 */

#ifdef __CRT_HAVE_unicode_16to8
/* Convert a given utf-16 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,unicode_16to8,(char *__restrict __utf8_dst, __CHAR16_TYPE__ const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_characters),(__utf8_dst,__utf16_text,__utf16_characters))
#else /* __CRT_HAVE_unicode_16to8 */
#include <libc/local/unicode/unicode_16to8.h>
/* Convert a given utf-16 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_16to8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL unicode_16to8)(char *__restrict __utf8_dst, __CHAR16_TYPE__ const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_characters) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_16to8))(__utf8_dst, __utf16_text, __utf16_characters); })
#endif /* !__CRT_HAVE_unicode_16to8 */

#ifdef __CRT_HAVE_unicode_16to32
/* Convert a given utf-16 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_characters)' dwords, or *4 bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,unicode_16to32,(__CHAR32_TYPE__ *__restrict __utf32_dst, __CHAR16_TYPE__ const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_characters),(__utf32_dst,__utf16_text,__utf16_characters))
#else /* __CRT_HAVE_unicode_16to32 */
#include <libc/local/unicode/unicode_16to32.h>
/* Convert a given utf-16 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_characters)' dwords, or *4 bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_16to32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *__NOTHROW_NCX(__LIBCCALL unicode_16to32)(__CHAR32_TYPE__ *__restrict __utf32_dst, __CHAR16_TYPE__ const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_characters) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_16to32))(__utf32_dst, __utf16_text, __utf16_characters); })
#endif /* !__CRT_HAVE_unicode_16to32 */

#ifdef __CRT_HAVE_unicode_32to8
/* Convert a given utf-32 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_32TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,unicode_32to8,(char *__restrict __utf8_dst, __CHAR32_TYPE__ const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_characters),(__utf8_dst,__utf32_text,__utf32_characters))
#else /* __CRT_HAVE_unicode_32to8 */
#include <libc/local/unicode/unicode_32to8.h>
/* Convert a given utf-32 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_32TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_32to8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL unicode_32to8)(char *__restrict __utf8_dst, __CHAR32_TYPE__ const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_characters) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_32to8))(__utf8_dst, __utf32_text, __utf32_characters); })
#endif /* !__CRT_HAVE_unicode_32to8 */

#ifdef __CRT_HAVE_unicode_32to16
/* Convert a given utf-32 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_32TO16_MAXBUF(utf16_characters)' words, or *2 bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,unicode_32to16,(__CHAR16_TYPE__ *__restrict __utf16_dst, __CHAR32_TYPE__ const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_characters),(__utf16_dst,__utf32_text,__utf32_characters))
#else /* __CRT_HAVE_unicode_32to16 */
#include <libc/local/unicode/unicode_32to16.h>
/* Convert a given utf-32 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_32TO16_MAXBUF(utf16_characters)' words, or *2 bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_32to16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL unicode_32to16)(__CHAR16_TYPE__ *__restrict __utf16_dst, __CHAR32_TYPE__ const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_characters) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_32to16))(__utf16_dst, __utf32_text, __utf32_characters); })
#endif /* !__CRT_HAVE_unicode_32to16 */
#ifdef __CRT_HAVE_unicode_c8toc16
/* @return: *:          Success (*pc16 was filled; the return value is the number of bytes taken from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified, but nothing was read from `s'; in this case, a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),__SIZE_TYPE__,__NOTHROW_NCX,unicode_c8toc16,(__CHAR16_TYPE__ *__restrict __pc16, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs),(__pc16,__s,__n,__mbs))
#else /* __CRT_HAVE_unicode_c8toc16 */
#include <libc/local/unicode/unicode_c8toc16.h>
/* @return: *:          Success (*pc16 was filled; the return value is the number of bytes taken from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified, but nothing was read from `s'; in this case, a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_c8toc16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_c8toc16)(__CHAR16_TYPE__ *__restrict __pc16, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_c8toc16))(__pc16, __s, __n, __mbs); })
#endif /* !__CRT_HAVE_unicode_c8toc16 */
#ifdef __CRT_HAVE_unicode_c8toc32
/* @return: *:          Success (*pc32 was filled; the return value is the number of bytes taken from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),__SIZE_TYPE__,__NOTHROW_NCX,unicode_c8toc32,(__CHAR32_TYPE__ *__restrict __pc32, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs),(__pc32,__s,__n,__mbs))
#else /* __CRT_HAVE_unicode_c8toc32 */
#include <libc/local/unicode/unicode_c8toc32.h>
/* @return: *:          Success (*pc32 was filled; the return value is the number of bytes taken from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_c8toc32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_c8toc32)(__CHAR32_TYPE__ *__restrict __pc32, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_c8toc32))(__pc32, __s, __n, __mbs); })
#endif /* !__CRT_HAVE_unicode_c8toc32 */

struct format_8to16_data {
	__pc16formatprinter fd_printer;    /* [1..1] Inner printer */
	void               *fd_arg;        /* Argument for `fd_printer' */
	__UINT32_TYPE__     fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
};
#ifdef __CRT_HAVE_format_8to16
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-16 output */
__CDECLARE(,__SSIZE_TYPE__,__NOTHROW_NCX,format_8to16,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_8to16 */
#include <libc/local/unicode/format_8to16.h>
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-16 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_8to16, __FORCELOCAL __ATTR_ARTIFICIAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_8to16)(void *__arg, char const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_8to16))(__arg, __data, __datalen); })
#endif /* !__CRT_HAVE_format_8to16 */

struct format_8to32_data {
	__pc32formatprinter fd_printer;    /* [1..1] Inner printer */
	void               *fd_arg;        /* Argument for `fd_printer' */
	__UINT32_TYPE__     fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
};
#ifdef __CRT_HAVE_format_8to32
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-32 output */
__CDECLARE(,__SSIZE_TYPE__,__NOTHROW_NCX,format_8to32,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_8to32 */
#include <libc/local/unicode/format_8to32.h>
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-32 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_8to32, __FORCELOCAL __ATTR_ARTIFICIAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_8to32)(void *__arg, char const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_8to32))(__arg, __data, __datalen); })
#endif /* !__CRT_HAVE_format_8to32 */

struct format_16to8_data {
	__pformatprinter fd_printer;   /* [1..1] Inner printer */
	void            *fd_arg;       /* Argument for `fd_printer' */
	__CHAR16_TYPE__  fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
};
#if defined(__CRT_HAVE_format_wto8) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Format printer (compatible with `__pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-8 output */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,format_16to8,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto8,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wto8)
/* Format printer (compatible with `__pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-8 output */
__CREDIRECT_DOS(,__SSIZE_TYPE__,__NOTHROW_NCX,format_16to8,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto8,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/unicode/format_wto8.h>
/* Format printer (compatible with `__pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-8 output */
__FORCELOCAL __ATTR_ARTIFICIAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL format_16to8)(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wto8))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/unicode/format_16to8.h>
/* Format printer (compatible with `__pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-8 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_16to8, __FORCELOCAL __ATTR_ARTIFICIAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL format_16to8)(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_16to8))(__arg, __data, __datalen); })
#endif /* !... */

struct format_32to8_data {
	__pformatprinter fd_printer; /* [1..1] Inner printer */
	void            *fd_arg;     /* Argument for `fd_printer' */
};
#if defined(__CRT_HAVE_format_wto8) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-8 output */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,format_32to8,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto8,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wto8)
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-8 output */
__CREDIRECT_KOS(,__SSIZE_TYPE__,__NOTHROW_NCX,format_32to8,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto8,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/unicode/format_wto8.h>
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-8 output */
__FORCELOCAL __ATTR_ARTIFICIAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL format_32to8)(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wto8))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/unicode/format_32to8.h>
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-8 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_32to8, __FORCELOCAL __ATTR_ARTIFICIAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL format_32to8)(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_32to8))(__arg, __data, __datalen); })
#endif /* !... */

struct format_16to32_data {
	__pc32formatprinter fd_printer;   /* [1..1] Inner printer */
	void               *fd_arg;       /* Argument for `fd_printer' */
	__CHAR16_TYPE__     fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
};
#if defined(__CRT_HAVE_format_wto32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-32 output */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,format_16to32,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto32,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wto32)
/* Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-32 output */
__CREDIRECT_DOS(,__SSIZE_TYPE__,__NOTHROW_NCX,format_16to32,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto32,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/unicode/format_wto32.h>
/* Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-32 output */
__FORCELOCAL __ATTR_ARTIFICIAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL format_16to32)(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wto32))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/unicode/format_16to32.h>
/* Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-32 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_16to32, __FORCELOCAL __ATTR_ARTIFICIAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL format_16to32)(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_16to32))(__arg, __data, __datalen); })
#endif /* !... */

struct format_32to16_data {
	__pc16formatprinter fd_printer; /* [1..1] Inner printer */
	void               *fd_arg;     /* Argument for `fd_printer' */
};
#if defined(__CRT_HAVE_format_wto16) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16 output */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,format_32to16,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto16,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wto16)
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16 output */
__CREDIRECT_KOS(,__SSIZE_TYPE__,__NOTHROW_NCX,format_32to16,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto16,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/unicode/format_wto16.h>
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16 output */
__FORCELOCAL __ATTR_ARTIFICIAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL format_32to16)(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wto16))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/unicode/format_32to16.h>
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_32to16, __FORCELOCAL __ATTR_ARTIFICIAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL format_32to16)(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_32to16))(__arg, __data, __datalen); })
#endif /* !... */



/* Unicode character traits database */
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
#ifndef ____unicode_descriptor_defined
#define ____unicode_descriptor_defined 1
__CDECLARE(__ATTR_RETNONNULL __ATTR_CONST,struct __unitraits *,__NOTHROW,__unicode_descriptor,(__CHAR32_TYPE__ __ch),(__ch))
#endif /* !____unicode_descriptor_defined */
#endif /* !__UNICODE_FPRINT */

#ifdef __CRT_HAVE_unicode_fold
/* The max number of characters ever written by `unicode_fold' */
#define UNICODE_FOLDED_MAX 3

/* Fold the given unicode character CH */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,unicode_fold,(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[UNICODE_FOLDED_MAX]),(__ch,__buf))
#else /* __CRT_HAVE_unicode_fold */
/* The max number of characters ever written by `unicode_fold' */
#define UNICODE_FOLDED_MAX 1

/* Fold the given unicode character CH */
__LOCAL __ATTR_RETNONNULL __ATTR_NONNULL((2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL unicode_fold)(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[UNICODE_FOLDED_MAX]) {
	__buf[0] = __ch;
	return __buf + 1;
}
#endif /* !__CRT_HAVE_unicode_fold */

/* Unicode character conversion. */
#ifdef __CRT_HAVE___unicode_asciiflags
#ifndef ____unicode_asciiflags_defined
#define ____unicode_asciiflags_defined 1
__LIBC __UINT16_TYPE__ const __unicode_asciiflags[256];
#endif /* !____unicode_asciiflags_defined */
#define __unicode_flags(ch)        (sizeof(ch) == 1 ? __unicode_asciiflags[(__UINT8_TYPE__)(ch)] : __unicode_descriptor(ch)->__ut_flags)
#define __unicode_asciiisupper(ch) (__unicode_asciiflags[(__UINT8_TYPE__)(ch)] & __UNICODE_FUPPER)
#define __unicode_asciiislower(ch) (__unicode_asciiflags[(__UINT8_TYPE__)(ch)] & __UNICODE_FLOWER)
#define __unicode_asciitolower(ch) (__unicode_asciiisupper(ch) ? (__UINT8_TYPE__)(ch) + 0x20 : (__UINT8_TYPE__)(ch))
#define __unicode_asciitoupper(ch) (__unicode_asciiislower(ch) ? (__UINT8_TYPE__)(ch) - 0x20 : (__UINT8_TYPE__)(ch))
#define __unicode_asciitotitle(ch) (__unicode_asciiislower(ch) ? (__UINT8_TYPE__)(ch) - 0x20 : (__UINT8_TYPE__)(ch))
#define __unicode_asciiasdigit(ch) ((__UINT8_TYPE__)(ch) - 0x30)
#define unicode_tolower(ch)        (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__unicode_asciitolower(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_lower))
#define unicode_toupper(ch)        (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__unicode_asciitoupper(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_upper))
#define unicode_totitle(ch)        (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__unicode_asciitoupper(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_title))
#define unicode_asdigit(ch)        (sizeof(ch) == 1 ? __unicode_asciiasdigit(ch) : __unicode_descriptor(ch)->__ut_digit)
#else /* __CRT_HAVE___unicode_asciiflags */
#define __unicode_flags(ch)        (__unicode_descriptor(ch)->__ut_flags)
#define unicode_tolower(ch)        (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_lower)
#define unicode_toupper(ch)        (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_upper)
#define unicode_totitle(ch)        (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_title)
#define unicode_asdigit(ch)        (__unicode_descriptor(ch)->__ut_digit)
#endif /* !__CRT_HAVE___unicode_asciiflags */

/* Unicode character traits */
#define unicode_isalpha(ch)        (__unicode_flags(ch) & __UNICODE_FALPHA)
#define unicode_islower(ch)        (__unicode_flags(ch) & __UNICODE_FLOWER)
#define unicode_isupper(ch)        (__unicode_flags(ch) & __UNICODE_FUPPER)
#define unicode_isalnum(ch)        (__unicode_flags(ch) & (__UNICODE_FALPHA | __UNICODE_FDECIMAL))
#define unicode_isspace(ch)        (__unicode_flags(ch) & __UNICODE_FSPACE)
#define unicode_istab(ch)          ((ch) == 9)
#define unicode_islf(ch)           (__unicode_flags(ch) & __UNICODE_FLF)
#define unicode_isprint(ch)        (__unicode_flags(ch) & __UNICODE_FPRINT)
#define unicode_isdigit(ch)        (__unicode_flags(ch) & __UNICODE_FDIGIT)
#define unicode_isdecimal(ch)      (__unicode_flags(ch) & __UNICODE_FDECIMAL)
#define unicode_isnumeric(ch)      (__unicode_flags(ch) & (__UNICODE_FDIGIT | __UNICODE_FDECIMAL))
#define unicode_istitle(ch)        (__unicode_flags(ch) & (__UNICODE_FTITLE | __UNICODE_FUPPER))
#define unicode_issymstrt(ch)      (__unicode_flags(ch) & __UNICODE_FSYMSTRT)
#define unicode_issymcont(ch)      (__unicode_flags(ch) & __UNICODE_FSYMCONT)
#define unicode_iscntrl(ch)        (__unicode_flags(ch) & __UNICODE_FCNTRL)

#else /* __CRT_HAVE___unicode_descriptor */
#include <libc/ctype.h>

#define UNICODE_FOLDED_MAX 1
__LOCAL __ATTR_RETNONNULL __ATTR_NONNULL((2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL unicode_fold)(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[UNICODE_FOLDED_MAX]) {
	__buf[0] = __ch;
	return __buf + 1;
}

#define unicode_tolower(ch)   (unicode_isupper(ch) ? (__CHAR32_TYPE__)(ch) + 0x20 : (__CHAR32_TYPE__)(ch))
#define unicode_toupper(ch)   (unicode_islower(ch) ? (__CHAR32_TYPE__)(ch) - 0x20 : (__CHAR32_TYPE__)(ch))
#define unicode_totitle(ch)   (unicode_islower(ch) ? (__CHAR32_TYPE__)(ch) - 0x20 : (__CHAR32_TYPE__)(ch))
#define unicode_asdigit(ch)   ((__UINT8_TYPE__)(ch) - 0x30)
#define unicode_isalpha(ch)   __libc_isalpha(ch)
#define unicode_islower(ch)   __libc_islower(ch)
#define unicode_isupper(ch)   __libc_isupper(ch)
#define unicode_isalnum(ch)   __libc_isalnum(ch)
#define unicode_isspace(ch)   __libc_isspace(ch)
#define unicode_istab(ch)     ((ch) == 9)
#define unicode_islf(ch)      ((ch) == 13 || (ch) == 10)
#define unicode_isprint(ch)   __libc_isprint(ch)
#define unicode_isdigit(ch)   __libc_isdigit(ch)
#define unicode_isdecimal(ch) unicode_isdigit(ch)
#define unicode_isnumeric(ch) unicode_isdigit(ch)
#define unicode_istitle(ch)   unicode_isupper(ch)
#define unicode_issymstrt(ch) __libc_isalpha(ch)
#define unicode_issymcont(ch) __libc_isalnum(ch)
#define unicode_iscntrl(ch)   __libc_iscntrl(ch)
#endif /* !__CRT_HAVE___unicode_descriptor */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_UNICODE_H */
