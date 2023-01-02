/* HASH CRC-32:0x8be09e5d */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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

#include <hybrid/byteorder.h>
#include <hybrid/__byteswap.h>
#include <hybrid/typecore.h>

#include <bits/crt/format-printer.h>
#include <bits/crt/mbstate.h>
#include <bits/crt/uformat-printer.h>
#include <bits/crt/wformat-printer.h>
#include <bits/crt/unicode.h>
#include <bits/types.h>



/* Other headers only define these under _KOS_SOURCE, but since <unicode.h> is
 * a kos-specific header, we can define these unconditionally (if  available)! */

/* Static initializer for `mbstate_t':
 * >> mbstate_t mbs = MBSTATE_INIT; */
#if !defined(MBSTATE_INIT) && defined(__MBSTATE_INIT)
#define MBSTATE_INIT __MBSTATE_INIT
#endif /* !MBSTATE_INIT && __MBSTATE_INIT */

/* Dynamic initializer for `mbstate_t':
 * >> mbstate_t mbs;
 * >> mbstate_init(&mbs); */
#if !defined(mbstate_init) && defined(__mbstate_init)
#define mbstate_init __mbstate_init
#endif /* !mbstate_init && __mbstate_init */

/* Check if the given mbstate_t is in its zero-shift state:
 * >> if (mbstate_isempty(&mbs)) { ... } */
#if !defined(mbstate_isempty) && defined(__mbstate_isempty)
#define mbstate_isempty __mbstate_isempty
#endif /* !mbstate_isempty && __mbstate_isempty */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __unicode_utf8seqlen_defined
#define __unicode_utf8seqlen_defined
#ifdef __CRT_HAVE_unicode_utf8seqlen
__CSDECLARE2(,__UINT8_TYPE__ const unicode_utf8seqlen[256],unicode_utf8seqlen)
#else /* __CRT_HAVE_unicode_utf8seqlen */
#include <libc/template/unicode_utf8seqlen.h>
#define unicode_utf8seqlen __LOCAL_unicode_utf8seqlen
#endif /* !__CRT_HAVE_unicode_utf8seqlen */
#endif /* !__unicode_utf8seqlen_defined */

/* The max length of any UTF-8 byte sequence describing a single unicode character. */
#define UNICODE_UTF8_MAXLEN  8 /* == unicode_utf8seqlen[0xff] */

/* The current length of any UTF-8 byte sequence produced by any 32-bit unicode character.
 * While `UNICODE_UTF8_MAXLEN'  is the  theoretical limit,  it allows  for up  to 42  bits
 * of  character digits, while `7' allows for up to `36' bits (`6' would only allow `30').
 * As a consequence, the max number of bytes which may be written by `unicode_writeutf8()'
 * is `UNICODE_UTF8_CURLEN', as it takes a 32-bit unicode character.
 * >> char buf[UNICODE_UTF8_CURLEN];
 * >> size_t buflen = (size_t)(unicode_writeutf8(buf, ch) - buf); */
#define UNICODE_UTF8_CURLEN  7

/* The max length of any UTF-16 word sequence describing a single unicode character. */
#define UNICODE_UTF16_MAXLEN 2
#define UNICODE_UTF16_CURLEN 2

/* The max length of any UTF-32 word sequence describing a single unicode character. */
#define UNICODE_UTF32_MAXLEN 1
#define UNICODE_UTF32_CURLEN 1

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

#ifndef __mbstate_t_defined
#define __mbstate_t_defined
typedef struct __mbstate mbstate_t;
#endif /* !__mbstate_t_defined */

#ifndef __char16_t_defined
#define __char16_t_defined
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;
#endif /* !__char16_t_defined */

#ifdef __CRT_HAVE_unicode_readutf8
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf8(3)
 * Read a single Unicode character from a given UTF-8 string */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf8,(char const **__restrict __ptext),unicode_readutf8,(__ptext))
/* >> unicode_readutf8(3)
 * Read a single Unicode character from a given UTF-8 string */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf8,(char **__restrict __ptext),unicode_readutf8,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf8(3)
 * Read a single Unicode character from a given UTF-8 string */
__CDECLARE(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf8,(char const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf8 */
#include <libc/local/unicode/unicode_readutf8.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf8(3)
 * Read a single Unicode character from a given UTF-8 string */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8)(char const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8))(__ptext); }
/* >> unicode_readutf8(3)
 * Read a single Unicode character from a given UTF-8 string */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8)(char **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8))((char const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf8(3)
 * Read a single Unicode character from a given UTF-8 string */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8)(char const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf8 */
#ifdef __CRT_HAVE_unicode_readutf8_rev
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf8_rev(3)
 * Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf8_rev,(char const **__restrict __ptext),unicode_readutf8_rev,(__ptext))
/* >> unicode_readutf8_rev(3)
 * Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf8_rev,(char **__restrict __ptext),unicode_readutf8_rev,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf8_rev(3)
 * Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__CDECLARE(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf8_rev,(char const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf8_rev */
#include <libc/local/unicode/unicode_readutf8_rev.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf8_rev(3)
 * Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev)(char const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev))(__ptext); }
/* >> unicode_readutf8_rev(3)
 * Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev)(char **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev))((char const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf8_rev(3)
 * Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf8_rev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev)(char const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf8_rev */
#ifdef __CRT_HAVE_unicode_readutf8_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf8_n(3)
 * Same as `unicode_readutf8()', but don't read past `text_end' */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf8_n,(char const **__restrict __ptext, char const *__text_end),unicode_readutf8_n,(__ptext,__text_end))
/* >> unicode_readutf8_n(3)
 * Same as `unicode_readutf8()', but don't read past `text_end' */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf8_n,(char **__restrict __ptext, char const *__text_end),unicode_readutf8_n,(__ptext,__text_end))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf8_n(3)
 * Same as `unicode_readutf8()', but don't read past `text_end' */
__CDECLARE(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf8_n,(char const **__restrict __ptext, char const *__text_end),(__ptext,__text_end))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf8_n */
#include <libc/local/unicode/unicode_readutf8_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf8_n(3)
 * Same as `unicode_readutf8()', but don't read past `text_end' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8_n)(char const **__restrict __ptext, char const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_n))(__ptext, __text_end); }
/* >> unicode_readutf8_n(3)
 * Same as `unicode_readutf8()', but don't read past `text_end' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8_n)(char **__restrict __ptext, char const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_n))((char const **)__ptext, __text_end); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf8_n(3)
 * Same as `unicode_readutf8()', but don't read past `text_end' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf8_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8_n)(char const **__restrict __ptext, char const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_n))(__ptext, __text_end); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf8_n */
#ifdef __CRT_HAVE_unicode_readutf8_rev_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf8_rev_n(3)
 * Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf8_rev_n,(char const **__restrict __ptext, char const *__text_start),unicode_readutf8_rev_n,(__ptext,__text_start))
/* >> unicode_readutf8_rev_n(3)
 * Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf8_rev_n,(char **__restrict __ptext, char const *__text_start),unicode_readutf8_rev_n,(__ptext,__text_start))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf8_rev_n(3)
 * Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf8_rev_n,(char const **__restrict __ptext, char const *__text_start),(__ptext,__text_start))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf8_rev_n */
#include <libc/local/unicode/unicode_readutf8_rev_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf8_rev_n(3)
 * Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev_n)(char const **__restrict __ptext, char const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev_n))(__ptext, __text_start); }
/* >> unicode_readutf8_rev_n(3)
 * Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev_n)(char **__restrict __ptext, char const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev_n))((char const **)__ptext, __text_start); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf8_rev_n(3)
 * Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf8_rev_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf8_rev_n)(char const **__restrict __ptext, char const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev_n))(__ptext, __text_start); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf8_rev_n */
#ifdef __CRT_HAVE_unicode_readutf16
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16,(char16_t const **__restrict __ptext),unicode_readutf16,(__ptext))
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16,(char16_t **__restrict __ptext),unicode_readutf16,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
__CDECLARE(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16,(char16_t const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16 */
#include <libc/local/unicode/unicode_readutf16.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16)(char16_t const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16))(__ptext); }
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16)(char16_t **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16))((__CHAR16_TYPE__ const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16)(char16_t const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16 */
#ifdef __CRT_HAVE_unicode_readutf16_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_n(3)
 * Same as `unicode_readutf16()', but don't read past `text_end' */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf16_n,(char16_t const **__restrict __ptext, char16_t const *__text_end),unicode_readutf16_n,(__ptext,__text_end))
/* >> unicode_readutf16_n(3)
 * Same as `unicode_readutf16()', but don't read past `text_end' */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf16_n,(char16_t **__restrict __ptext, char16_t const *__text_end),unicode_readutf16_n,(__ptext,__text_end))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_n(3)
 * Same as `unicode_readutf16()', but don't read past `text_end' */
__CDECLARE(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf16_n,(char16_t const **__restrict __ptext, char16_t const *__text_end),(__ptext,__text_end))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_n */
#include <libc/local/unicode/unicode_readutf16_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_n(3)
 * Same as `unicode_readutf16()', but don't read past `text_end' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_n)(char16_t const **__restrict __ptext, char16_t const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_n))(__ptext, __text_end); }
/* >> unicode_readutf16_n(3)
 * Same as `unicode_readutf16()', but don't read past `text_end' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_n)(char16_t **__restrict __ptext, char16_t const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_n))((__CHAR16_TYPE__ const **)__ptext, __text_end); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_n(3)
 * Same as `unicode_readutf16()', but don't read past `text_end' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_n)(char16_t const **__restrict __ptext, char16_t const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_n))(__ptext, __text_end); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_n */
#ifdef __CRT_HAVE_unicode_readutf16_swap
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_swap(3)
 * Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_swap,(char16_t const **__restrict __ptext),unicode_readutf16_swap,(__ptext))
/* >> unicode_readutf16_swap(3)
 * Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_swap,(char16_t **__restrict __ptext),unicode_readutf16_swap,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_swap(3)
 * Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__CDECLARE(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_swap,(char16_t const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_swap */
#include <libc/local/unicode/unicode_readutf16_swap.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_swap(3)
 * Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap)(char16_t const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap))(__ptext); }
/* >> unicode_readutf16_swap(3)
 * Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap)(char16_t **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap))((__CHAR16_TYPE__ const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_swap(3)
 * Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_swap, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap)(char16_t const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_swap */
#ifdef __CRT_HAVE_unicode_readutf16_swap_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_swap_n(3)
 * Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf16_swap_n,(char16_t const **__restrict __ptext, char16_t const *__text_end),unicode_readutf16_swap_n,(__ptext,__text_end))
/* >> unicode_readutf16_swap_n(3)
 * Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf16_swap_n,(char16_t **__restrict __ptext, char16_t const *__text_end),unicode_readutf16_swap_n,(__ptext,__text_end))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_swap_n(3)
 * Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__CDECLARE(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf16_swap_n,(char16_t const **__restrict __ptext, char16_t const *__text_end),(__ptext,__text_end))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_swap_n */
#include <libc/local/unicode/unicode_readutf16_swap_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_swap_n(3)
 * Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_n)(char16_t const **__restrict __ptext, char16_t const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_n))(__ptext, __text_end); }
/* >> unicode_readutf16_swap_n(3)
 * Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_n)(char16_t **__restrict __ptext, char16_t const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_n))((__CHAR16_TYPE__ const **)__ptext, __text_end); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_swap_n(3)
 * Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_swap_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_n)(char16_t const **__restrict __ptext, char16_t const *__text_end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_n))(__ptext, __text_end); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_swap_n */
#ifdef __CRT_HAVE_unicode_readutf16_rev
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_rev,(char16_t const **__restrict __ptext),unicode_readutf16_rev,(__ptext))
/* >> unicode_readutf16_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_rev,(char16_t **__restrict __ptext),unicode_readutf16_rev,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__CDECLARE(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_rev,(char16_t const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_rev */
#include <libc/local/unicode/unicode_readutf16_rev.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev)(char16_t const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev))(__ptext); }
/* >> unicode_readutf16_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev)(char16_t **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev))((__CHAR16_TYPE__ const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_rev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev)(char16_t const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_rev */
#ifdef __CRT_HAVE_unicode_readutf16_swap_rev
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_swap_rev(3)
 * Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_swap_rev,(char16_t const **__restrict __ptext),unicode_readutf16_swap_rev,(__ptext))
/* >> unicode_readutf16_swap_rev(3)
 * Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_swap_rev,(char16_t **__restrict __ptext),unicode_readutf16_swap_rev,(__ptext))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_swap_rev(3)
 * Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__CDECLARE(__ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_swap_rev,(char16_t const **__restrict __ptext),(__ptext))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_swap_rev */
#include <libc/local/unicode/unicode_readutf16_swap_rev.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_swap_rev(3)
 * Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev)(char16_t const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev))(__ptext); }
/* >> unicode_readutf16_swap_rev(3)
 * Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev)(char16_t **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev))((__CHAR16_TYPE__ const **)__ptext); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_swap_rev(3)
 * Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_swap_rev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev)(char16_t const **__restrict __ptext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev))(__ptext); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_swap_rev */
#ifdef __CRT_HAVE_unicode_readutf16_rev_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_rev_n(3)
 * Same as `unicode_readutf16_rev()', but don't read ahead of `text_start' */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf16_rev_n,(char16_t const **__restrict __ptext, char16_t const *__text_start),unicode_readutf16_rev_n,(__ptext,__text_start))
/* >> unicode_readutf16_rev_n(3)
 * Same as `unicode_readutf16_rev()', but don't read ahead of `text_start' */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf16_rev_n,(char16_t **__restrict __ptext, char16_t const *__text_start),unicode_readutf16_rev_n,(__ptext,__text_start))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_rev_n(3)
 * Same as `unicode_readutf16_rev()', but don't read ahead of `text_start' */
__CDECLARE(__ATTR_INOUT(1) __ATTR_NONNULL((2)),char32_t,__NOTHROW_NCX,unicode_readutf16_rev_n,(char16_t const **__restrict __ptext, char16_t const *__text_start),(__ptext,__text_start))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_rev_n */
#include <libc/local/unicode/unicode_readutf16_rev_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_rev_n(3)
 * Same as `unicode_readutf16_rev()', but don't read ahead of `text_start' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev_n)(char16_t const **__restrict __ptext, char16_t const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev_n))(__ptext, __text_start); }
/* >> unicode_readutf16_rev_n(3)
 * Same as `unicode_readutf16_rev()', but don't read ahead of `text_start' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev_n)(char16_t **__restrict __ptext, char16_t const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev_n))((__CHAR16_TYPE__ const **)__ptext, __text_start); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_rev_n(3)
 * Same as `unicode_readutf16_rev()', but don't read ahead of `text_start' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_rev_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_rev_n)(char16_t const **__restrict __ptext, char16_t const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_rev_n))(__ptext, __text_start); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_rev_n */
#ifdef __CRT_HAVE_unicode_readutf16_swap_rev_n
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_swap_rev_n(3)
 * Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_swap_rev_n,(char16_t const **__restrict __ptext, char16_t const *__text_start),unicode_readutf16_swap_rev_n,(__ptext,__text_start))
/* >> unicode_readutf16_swap_rev_n(3)
 * Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_swap_rev_n,(char16_t **__restrict __ptext, char16_t const *__text_start),unicode_readutf16_swap_rev_n,(__ptext,__text_start))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_swap_rev_n(3)
 * Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),char32_t,__NOTHROW_NCX,unicode_readutf16_swap_rev_n,(char16_t const **__restrict __ptext, char16_t const *__text_start),(__ptext,__text_start))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#else /* __CRT_HAVE_unicode_readutf16_swap_rev_n */
#include <libc/local/unicode/unicode_readutf16_swap_rev_n.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf16_swap_rev_n(3)
 * Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev_n)(char16_t const **__restrict __ptext, char16_t const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev_n))(__ptext, __text_start); }
/* >> unicode_readutf16_swap_rev_n(3)
 * Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev_n)(char16_t **__restrict __ptext, char16_t const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev_n))((__CHAR16_TYPE__ const **)__ptext, __text_start); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf16_swap_rev_n(3)
 * Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_readutf16_swap_rev_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) char32_t __NOTHROW_NCX(__LIBCCALL unicode_readutf16_swap_rev_n)(char16_t const **__restrict __ptext, char16_t const *__text_start) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev_n))(__ptext, __text_start); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */
#endif /* !__CRT_HAVE_unicode_readutf16_swap_rev_n */
#ifdef __CRT_HAVE_unicode_writeutf8
/* >> unicode_writeutf8(3)
 * Write  a given Unicode character `ch' to `dst'  and return a pointer to its end
 * location. This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_OUT(1),char *,__NOTHROW_NCX,unicode_writeutf8,(char *__restrict __dst, char32_t __ch),(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf8 */
#include <libc/local/unicode/unicode_writeutf8.h>
/* >> unicode_writeutf8(3)
 * Write  a given Unicode character `ch' to `dst'  and return a pointer to its end
 * location. This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_writeutf8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL unicode_writeutf8)(char *__restrict __dst, char32_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf8))(__dst, __ch); })
#endif /* !__CRT_HAVE_unicode_writeutf8 */
#ifdef __CRT_HAVE_unicode_writeutf8_n
/* >> unicode_writeutf8_n(3)
 * Same as `unicode_writeutf8(3)', but don't write emore than `dst_maxbytes' bytes. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),char *,__NOTHROW_NCX,unicode_writeutf8_n,(char *__restrict __dst, char32_t __ch, __SIZE_TYPE__ __dst_maxbytes),(__dst,__ch,__dst_maxbytes))
#else /* __CRT_HAVE_unicode_writeutf8_n */
#include <libc/local/unicode/unicode_writeutf8_n.h>
/* >> unicode_writeutf8_n(3)
 * Same as `unicode_writeutf8(3)', but don't write emore than `dst_maxbytes' bytes. */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_writeutf8_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_OUTS(1, 3) char *__NOTHROW_NCX(__LIBCCALL unicode_writeutf8_n)(char *__restrict __dst, char32_t __ch, __SIZE_TYPE__ __dst_maxbytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf8_n))(__dst, __ch, __dst_maxbytes); })
#endif /* !__CRT_HAVE_unicode_writeutf8_n */
#ifdef __CRT_HAVE_unicode_writeutf16
/* >> unicode_writeutf16(3)
 * Write a given Unicode character  `ch' to `dst' and return  a pointer to its  end
 * location. This function will write at most `UNICODE_UTF16_CURLEN' words to `dst' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_OUT(1),char16_t *,__NOTHROW_NCX,unicode_writeutf16,(char16_t *__restrict __dst, char32_t __ch),(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf16 */
#include <libc/local/unicode/unicode_writeutf16.h>
/* >> unicode_writeutf16(3)
 * Write a given Unicode character  `ch' to `dst' and return  a pointer to its  end
 * location. This function will write at most `UNICODE_UTF16_CURLEN' words to `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_writeutf16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_OUT(1) char16_t *__NOTHROW_NCX(__LIBCCALL unicode_writeutf16)(char16_t *__restrict __dst, char32_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf16))(__dst, __ch); })
#endif /* !__CRT_HAVE_unicode_writeutf16 */
#ifdef __CRT_HAVE_unicode_writeutf16_chk
/* >> unicode_writeutf16_chk(3)
 * Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false */
__CDECLARE(__ATTR_WUNUSED __ATTR_OUT(1),char16_t *,__NOTHROW_NCX,unicode_writeutf16_chk,(char16_t *__restrict __dst, char32_t __ch),(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf16_chk */
#include <libc/local/unicode/unicode_writeutf16_chk.h>
/* >> unicode_writeutf16_chk(3)
 * Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_writeutf16_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT(1) char16_t *__NOTHROW_NCX(__LIBCCALL unicode_writeutf16_chk)(char16_t *__restrict __dst, char32_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf16_chk))(__dst, __ch); })
#endif /* !__CRT_HAVE_unicode_writeutf16_chk */

#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* >> unicode_readutf32(3)
 * Read a single Unicode character from a given UTF-32 string. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32)(/*utf-32*/ char32_t const **__restrict __ptext) { return *(*__ptext)++; }
/* >> unicode_readutf32(3)
 * Read a single Unicode character from a given UTF-32 string. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32)(/*utf-32*/ char32_t **__restrict __ptext) { return *(*__ptext)++; }
/* >> unicode_readutf32_swap(3)
 * Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ char32_t const **__restrict __ptext) { char32_t __res = *(*__ptext++); return __hybrid_bswap32(__res); }
/* >> unicode_readutf32_swap(3)
 * Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ char32_t **__restrict __ptext) { char32_t __res = *(*__ptext++); return __hybrid_bswap32(__res); }
/* >> unicode_readutf32_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ char32_t const **__restrict __ptext) { return *(--*__ptext); }
/* >> unicode_readutf32_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ char32_t **__restrict __ptext) { return *(--*__ptext); }
/* >> unicode_readutf32_swap_rev(3)
 * Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ char32_t const **__restrict __ptext) { char32_t __res = *(--*__ptext); return __hybrid_bswap32(__res); }
/* >> unicode_readutf32_swap_rev(3)
 * Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ char32_t **__restrict __ptext) { char32_t __res = *(--*__ptext); return __hybrid_bswap32(__res); }
/* >> unicode_readutf32_n(3)
 * Same as `unicode_readutf32()', but don't read past `text_end'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_end) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __result;
}
/* >> unicode_readutf32_n(3)
 * Same as `unicode_readutf32()', but don't read past `text_end'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ char32_t **__restrict __ptext, char32_t const *__text_end) {
	return unicode_readutf32_n((char32_t const **)__ptext, __text_end);
}
/* >> unicode_readutf32_rev_n(3)
 * Same as `unicode_readutf32()', but don't read before `text_start'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_start) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __result;
}
/* >> unicode_readutf32_rev_n(3)
 * Same as `unicode_readutf32()', but don't read before `text_start'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ char32_t **__restrict __ptext, char32_t const *__text_start) {
	return unicode_readutf32_rev_n((char32_t const **)__ptext, __text_start);
}
/* >> unicode_readutf32_swap_n(3)
 * Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_end) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* >> unicode_readutf32_swap_n(3)
 * Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ char32_t **__restrict __ptext, char32_t const *__text_end) {
	return unicode_readutf32_swap_n((char32_t const **)__ptext, __text_end);
}
/* >> unicode_readutf32_swap_rev_n(3)
 * Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_start) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* >> unicode_readutf32_swap_rev_n(3)
 * Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ char32_t **__restrict __ptext, char32_t const *__text_start) {
	return unicode_readutf32_swap_rev_n((char32_t const **)__ptext, __text_start);
}
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf32(3)
 * Read a single Unicode character from a given UTF-32 string. */
__LOCAL __ATTR_INOUT(1) char32_t
(__LIBCCALL unicode_readutf32)(/*utf-32*/ char32_t const **__restrict __ptext) {
	return *(*__ptext)++;
}
/* >> unicode_readutf32_swap(3)
 * Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t
(__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ char32_t const **__restrict __ptext) {
	char32_t __res = *(*__ptext++);
	return __hybrid_bswap32(__res);
}
/* >> unicode_readutf32_rev(3)
 * Same  as  `unicode_readutf32', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__LOCAL __ATTR_INOUT(1) char32_t
(__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ char32_t const **__restrict __ptext) {
	return *(--*__ptext);
}
/* >> unicode_readutf32_swap_rev(3)
 * Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t
(__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ char32_t const **__restrict __ptext) {
	char32_t __res = *(--*__ptext);
	return __hybrid_bswap32(__res);
}
/* >> unicode_readutf32_n(3)
 * Same as `unicode_readutf32()', but don't read past `text_end'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_end) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __result;
}
/* >> unicode_readutf32_rev_n(3)
 * Same as `unicode_readutf32()', but don't read before `text_start'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_start) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __result;
}
/* >> unicode_readutf32_swap_n(3)
 * Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_end) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* >> unicode_readutf32_swap_rev_n(3)
 * Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_start) {
	char32_t __result;
	char32_t const *__text = *__ptext;
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
#endif /* __BYTE_ORDER__ == ... */

/* >> unicode_writeutf32(3)
 * Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This  function   will   write   at  most   `UNICODE_UTF32_CURLEN'   dwords   to   `dst' */
__LOCAL __ATTR_RETNONNULL __ATTR_OUT(1) char32_t *
(__LIBCCALL unicode_writeutf32)(/*utf-32*/ char32_t *__restrict __dst, char32_t __ch) {
	*__dst++ = __ch;
	return __dst;
}

#ifdef __CRT_HAVE_unicode_len8to16
/* >> unicode_len8to16(3)
 * Return the number of utf-16 words needed to encode a given utf-8 string
 * HINT: This is the exact number of words written by `unicode_8to16(3)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_INS(1, 2),size_t,__NOTHROW_NCX,unicode_len8to16,(char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),(__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_len8to16 */
#include <libc/local/unicode/unicode_len8to16.h>
/* >> unicode_len8to16(3)
 * Return the number of utf-16 words needed to encode a given utf-8 string
 * HINT: This is the exact number of words written by `unicode_8to16(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_len8to16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(1, 2) size_t __NOTHROW_NCX(__LIBCCALL unicode_len8to16)(char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_len8to16))(__utf8_text, __utf8_bytes); })
#endif /* !__CRT_HAVE_unicode_len8to16 */
#ifdef __CRT_HAVE_unicode_len8to32
/* >> unicode_len8to32(3)
 * Return the number of utf-32 character needed to encode a given utf-8 string
 * HINT: This is the exact number of words written by `unicode_8to32(3)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_INS(1, 2),size_t,__NOTHROW_NCX,unicode_len8to32,(char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),(__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_len8to32 */
#include <libc/local/unicode/unicode_len8to32.h>
/* >> unicode_len8to32(3)
 * Return the number of utf-32 character needed to encode a given utf-8 string
 * HINT: This is the exact number of words written by `unicode_8to32(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_len8to32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(1, 2) size_t __NOTHROW_NCX(__LIBCCALL unicode_len8to32)(char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_len8to32))(__utf8_text, __utf8_bytes); })
#endif /* !__CRT_HAVE_unicode_len8to32 */
#ifdef __CRT_HAVE_unicode_8to16
/* >> unicode_8to16(3)
 * Convert a given utf-8 string to utf-16.
 * @param: utf16_dst:  A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_bytes)' words, or `*2' bytes
 * @param: utf8_text:  The input UTF-8 string to convert
 * @param: utf8_bytes: The amount of UTF-8 bytes found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1),char16_t *,__NOTHROW_NCX,unicode_8to16,(char16_t *__restrict __utf16_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),(__utf16_dst,__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_8to16 */
#include <libc/local/unicode/unicode_8to16.h>
/* >> unicode_8to16(3)
 * Convert a given utf-8 string to utf-16.
 * @param: utf16_dst:  A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_bytes)' words, or `*2' bytes
 * @param: utf8_text:  The input UTF-8 string to convert
 * @param: utf8_bytes: The amount of UTF-8 bytes found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_8to16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1) char16_t *__NOTHROW_NCX(__LIBCCALL unicode_8to16)(char16_t *__restrict __utf16_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_8to16))(__utf16_dst, __utf8_text, __utf8_bytes); })
#endif /* !__CRT_HAVE_unicode_8to16 */
#ifdef __CRT_HAVE_unicode_8to16_n
/* >> unicode_8to16_n(3)
 * Same as `unicode_8to16(3)', but don't write more than `utf16_maxwords' words to `utf16_dst'
 * @param: utf16_dst:      A buffer of at least `utf16_dst' words.
 * @param: utf16_maxwords: Max # of words to write to `utf16_dst'
 * @param: utf8_text:      The input UTF-8 string to convert
 * @param: utf8_bytes:     The amount of UTF-8 bytes found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),char16_t *,__NOTHROW_NCX,unicode_8to16_n,(char16_t *__restrict __utf16_dst, __SIZE_TYPE__ __utf16_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),(__utf16_dst,__utf16_maxwords,__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_8to16_n */
#include <libc/local/unicode/unicode_8to16_n.h>
/* >> unicode_8to16_n(3)
 * Same as `unicode_8to16(3)', but don't write more than `utf16_maxwords' words to `utf16_dst'
 * @param: utf16_dst:      A buffer of at least `utf16_dst' words.
 * @param: utf16_maxwords: Max # of words to write to `utf16_dst'
 * @param: utf8_text:      The input UTF-8 string to convert
 * @param: utf8_bytes:     The amount of UTF-8 bytes found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_8to16_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) char16_t *__NOTHROW_NCX(__LIBCCALL unicode_8to16_n)(char16_t *__restrict __utf16_dst, __SIZE_TYPE__ __utf16_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_8to16_n))(__utf16_dst, __utf16_maxwords, __utf8_text, __utf8_bytes); })
#endif /* !__CRT_HAVE_unicode_8to16_n */
#ifdef __CRT_HAVE_unicode_8to16_chk
/* >> unicode_8to16_chk(3)
 * Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
 * @param: utf16_dst:  A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_bytes)' words, or `*2' bytes
 * @param: utf8_text:  The input UTF-8 string to convert
 * @param: utf8_bytes: The amount of UTF-8 bytes found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character.
 * @return: NULL: Attempted to write an invalid character */
__CDECLARE(__ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_OUT(1),char16_t *,__NOTHROW_NCX,unicode_8to16_chk,(char16_t *__restrict __utf16_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),(__utf16_dst,__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_8to16_chk */
#include <libc/local/unicode/unicode_8to16_chk.h>
/* >> unicode_8to16_chk(3)
 * Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
 * @param: utf16_dst:  A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_bytes)' words, or `*2' bytes
 * @param: utf8_text:  The input UTF-8 string to convert
 * @param: utf8_bytes: The amount of UTF-8 bytes found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character.
 * @return: NULL: Attempted to write an invalid character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_8to16_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_OUT(1) char16_t *__NOTHROW_NCX(__LIBCCALL unicode_8to16_chk)(char16_t *__restrict __utf16_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_8to16_chk))(__utf16_dst, __utf8_text, __utf8_bytes); })
#endif /* !__CRT_HAVE_unicode_8to16_chk */
#ifdef __CRT_HAVE_unicode_8to16_chk_n
/* >> unicode_8to16_chk_n(3)
 * Same as `unicode_8to16_chk(3)', but don't write more than `utf16_maxwords' words to `utf16_dst'
 * @param: utf16_dst:      A buffer of at least `utf16_dst' words.
 * @param: utf16_maxwords: Max # of words to write to `utf16_dst'
 * @param: utf8_text:      The input UTF-8 string to convert
 * @param: utf8_bytes:     The amount of UTF-8 bytes found in `utf8_text'
 * @return: * :   A pointer after the last written UTF-16 character
 * @return: NULL: Attempted to write an invalid character */
__CDECLARE(__ATTR_WUNUSED __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),char16_t *,__NOTHROW_NCX,unicode_8to16_chk_n,(char16_t *__restrict __utf16_dst, __SIZE_TYPE__ __utf16_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),(__utf16_dst,__utf16_maxwords,__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_8to16_chk_n */
#include <libc/local/unicode/unicode_8to16_chk_n.h>
/* >> unicode_8to16_chk_n(3)
 * Same as `unicode_8to16_chk(3)', but don't write more than `utf16_maxwords' words to `utf16_dst'
 * @param: utf16_dst:      A buffer of at least `utf16_dst' words.
 * @param: utf16_maxwords: Max # of words to write to `utf16_dst'
 * @param: utf8_text:      The input UTF-8 string to convert
 * @param: utf8_bytes:     The amount of UTF-8 bytes found in `utf8_text'
 * @return: * :   A pointer after the last written UTF-16 character
 * @return: NULL: Attempted to write an invalid character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_8to16_chk_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) char16_t *__NOTHROW_NCX(__LIBCCALL unicode_8to16_chk_n)(char16_t *__restrict __utf16_dst, __SIZE_TYPE__ __utf16_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_8to16_chk_n))(__utf16_dst, __utf16_maxwords, __utf8_text, __utf8_bytes); })
#endif /* !__CRT_HAVE_unicode_8to16_chk_n */
#ifdef __CRT_HAVE_unicode_8to32
/* >> unicode_8to32(3)
 * Convert a given utf-8 string to utf-32.
 * @param: utf32_dst:  A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_bytes)' dwords, or `*4' bytes
 * @param: utf8_text:  The input UTF-8 string to convert
 * @param: utf8_bytes: The amount of UTF-8 bytes found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1),char32_t *,__NOTHROW_NCX,unicode_8to32,(char32_t *__restrict __utf32_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),(__utf32_dst,__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_8to32 */
#include <libc/local/unicode/unicode_8to32.h>
/* >> unicode_8to32(3)
 * Convert a given utf-8 string to utf-32.
 * @param: utf32_dst:  A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_bytes)' dwords, or `*4' bytes
 * @param: utf8_text:  The input UTF-8 string to convert
 * @param: utf8_bytes: The amount of UTF-8 bytes found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_8to32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1) char32_t *__NOTHROW_NCX(__LIBCCALL unicode_8to32)(char32_t *__restrict __utf32_dst, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_8to32))(__utf32_dst, __utf8_text, __utf8_bytes); })
#endif /* !__CRT_HAVE_unicode_8to32 */
#ifdef __CRT_HAVE_unicode_8to32_n
/* >> unicode_8to32_n(3)
 * Same as `unicode_8to32(3)', but don't write more than `utf32_maxwords' words to `utf32_dst'
 * @param: utf32_dst:      A buffer of at least `utf32_maxwords' dwords
 * @param: utf32_maxwords: Max # of words to write to `utf16_dst'
 * @param: utf8_text:      The input UTF-8 string to convert
 * @param: utf8_bytes:     The amount of UTF-8 bytes found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),char32_t *,__NOTHROW_NCX,unicode_8to32_n,(char32_t *__restrict __utf32_dst, __SIZE_TYPE__ __utf32_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),(__utf32_dst,__utf32_maxwords,__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_8to32_n */
#include <libc/local/unicode/unicode_8to32_n.h>
/* >> unicode_8to32_n(3)
 * Same as `unicode_8to32(3)', but don't write more than `utf32_maxwords' words to `utf32_dst'
 * @param: utf32_dst:      A buffer of at least `utf32_maxwords' dwords
 * @param: utf32_maxwords: Max # of words to write to `utf16_dst'
 * @param: utf8_text:      The input UTF-8 string to convert
 * @param: utf8_bytes:     The amount of UTF-8 bytes found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_8to32_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) char32_t *__NOTHROW_NCX(__LIBCCALL unicode_8to32_n)(char32_t *__restrict __utf32_dst, __SIZE_TYPE__ __utf32_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_8to32_n))(__utf32_dst, __utf32_maxwords, __utf8_text, __utf8_bytes); })
#endif /* !__CRT_HAVE_unicode_8to32_n */
#ifdef __CRT_HAVE_unicode_16to8
/* >> unicode_16to8(3)
 * Convert a given utf-16 string to utf-8.
 * @param: utf8_dst:    A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_words)' bytes
 * @param: utf16_text:  The input UTF-16 string to convert
 * @param: utf16_words: The amount of UTF-16 words found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1),char *,__NOTHROW_NCX,unicode_16to8,(char *__restrict __utf8_dst, char16_t const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_words),(__utf8_dst,__utf16_text,__utf16_words))
#else /* __CRT_HAVE_unicode_16to8 */
#include <libc/local/unicode/unicode_16to8.h>
/* >> unicode_16to8(3)
 * Convert a given utf-16 string to utf-8.
 * @param: utf8_dst:    A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_words)' bytes
 * @param: utf16_text:  The input UTF-16 string to convert
 * @param: utf16_words: The amount of UTF-16 words found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_16to8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL unicode_16to8)(char *__restrict __utf8_dst, char16_t const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_16to8))(__utf8_dst, __utf16_text, __utf16_words); })
#endif /* !__CRT_HAVE_unicode_16to8 */
#ifdef __CRT_HAVE_unicode_16to8_n
/* >> unicode_16to8_n(3)
 * Same as `unicode_16to8(3)', but don't write more than `utf8_maxbytes' bytes to `utf8_dst'
 * @param: utf8_dst:      A buffer of at least `utf8_maxbytes' bytes
 * @param: utf8_maxbytes: Max # of bytes to write to `utf8_dst'
 * @param: utf16_text:    The input UTF-16 string to convert
 * @param: utf16_words:   The amount of UTF-16 words found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),char *,__NOTHROW_NCX,unicode_16to8_n,(char *__restrict __utf8_dst, __SIZE_TYPE__ __utf8_maxbytes, char16_t const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_words),(__utf8_dst,__utf8_maxbytes,__utf16_text,__utf16_words))
#else /* __CRT_HAVE_unicode_16to8_n */
#include <libc/local/unicode/unicode_16to8_n.h>
/* >> unicode_16to8_n(3)
 * Same as `unicode_16to8(3)', but don't write more than `utf8_maxbytes' bytes to `utf8_dst'
 * @param: utf8_dst:      A buffer of at least `utf8_maxbytes' bytes
 * @param: utf8_maxbytes: Max # of bytes to write to `utf8_dst'
 * @param: utf16_text:    The input UTF-16 string to convert
 * @param: utf16_words:   The amount of UTF-16 words found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_16to8_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) char *__NOTHROW_NCX(__LIBCCALL unicode_16to8_n)(char *__restrict __utf8_dst, __SIZE_TYPE__ __utf8_maxbytes, char16_t const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_16to8_n))(__utf8_dst, __utf8_maxbytes, __utf16_text, __utf16_words); })
#endif /* !__CRT_HAVE_unicode_16to8_n */
#ifdef __CRT_HAVE_unicode_16to32
/* >> unicode_16to32(3)
 * Convert a given utf-16 string to utf-32.
 * @param: utf32_dst:   A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_words)' dwords, or *4 bytes
 * @param: utf16_text:  The input UTF-16 string to convert
 * @param: utf16_words: The amount of UTF-16 words found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1),char32_t *,__NOTHROW_NCX,unicode_16to32,(char32_t *__restrict __utf32_dst, char16_t const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_words),(__utf32_dst,__utf16_text,__utf16_words))
#else /* __CRT_HAVE_unicode_16to32 */
#include <libc/local/unicode/unicode_16to32.h>
/* >> unicode_16to32(3)
 * Convert a given utf-16 string to utf-32.
 * @param: utf32_dst:   A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_words)' dwords, or *4 bytes
 * @param: utf16_text:  The input UTF-16 string to convert
 * @param: utf16_words: The amount of UTF-16 words found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_16to32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1) char32_t *__NOTHROW_NCX(__LIBCCALL unicode_16to32)(char32_t *__restrict __utf32_dst, char16_t const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_16to32))(__utf32_dst, __utf16_text, __utf16_words); })
#endif /* !__CRT_HAVE_unicode_16to32 */
#ifdef __CRT_HAVE_unicode_16to32_n
/* >> unicode_16to32_n(3)
 * Same as `unicode_16to32(3)', but don't write more than `utf32_maxwords' words to `utf32_dst'
 * @param: utf32_dst:      A buffer of at least `utf32_maxwords' dwords
 * @param: utf32_maxwords: Max # of words to write to `utf16_dst'
 * @param: utf16_text:     The input UTF-16 string to convert
 * @param: utf16_words:    The amount of UTF-16 words found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),char32_t *,__NOTHROW_NCX,unicode_16to32_n,(char32_t *__restrict __utf32_dst, __SIZE_TYPE__ __utf32_maxwords, char16_t const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_words),(__utf32_dst,__utf32_maxwords,__utf16_text,__utf16_words))
#else /* __CRT_HAVE_unicode_16to32_n */
#include <libc/local/unicode/unicode_16to32_n.h>
/* >> unicode_16to32_n(3)
 * Same as `unicode_16to32(3)', but don't write more than `utf32_maxwords' words to `utf32_dst'
 * @param: utf32_dst:      A buffer of at least `utf32_maxwords' dwords
 * @param: utf32_maxwords: Max # of words to write to `utf16_dst'
 * @param: utf16_text:     The input UTF-16 string to convert
 * @param: utf16_words:    The amount of UTF-16 words found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_16to32_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) char32_t *__NOTHROW_NCX(__LIBCCALL unicode_16to32_n)(char32_t *__restrict __utf32_dst, __SIZE_TYPE__ __utf32_maxwords, char16_t const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_16to32_n))(__utf32_dst, __utf32_maxwords, __utf16_text, __utf16_words); })
#endif /* !__CRT_HAVE_unicode_16to32_n */
#ifdef __CRT_HAVE_unicode_32to8
/* >> unicode_32to8(3)
 * Convert a given utf-32 string to utf-8.
 * @param: utf8_dst:     A buffer of at least `UNICODE_32TO8_MAXBUF(utf32_dwords)' bytes
 * @param: utf32_text:   The input UTF-32 string to convert
 * @param: utf32_dwords: The amount of UTF-32 dwords found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1),char *,__NOTHROW_NCX,unicode_32to8,(char *__restrict __utf8_dst, char32_t const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_dwords),(__utf8_dst,__utf32_text,__utf32_dwords))
#else /* __CRT_HAVE_unicode_32to8 */
#include <libc/local/unicode/unicode_32to8.h>
/* >> unicode_32to8(3)
 * Convert a given utf-32 string to utf-8.
 * @param: utf8_dst:     A buffer of at least `UNICODE_32TO8_MAXBUF(utf32_dwords)' bytes
 * @param: utf32_text:   The input UTF-32 string to convert
 * @param: utf32_dwords: The amount of UTF-32 dwords found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_32to8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL unicode_32to8)(char *__restrict __utf8_dst, char32_t const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_32to8))(__utf8_dst, __utf32_text, __utf32_dwords); })
#endif /* !__CRT_HAVE_unicode_32to8 */
#ifdef __CRT_HAVE_unicode_32to8_n
/* >> unicode_32to8_n(3)
 * Same as `unicode_32to8(3)', but don't write more than `utf8_maxbytes' bytes to `utf8_dst'
 * @param: utf8_dst:      A buffer of at least `utf8_maxbytes' bytes
 * @param: utf8_maxbytes: Max # of words to write to `utf8_dst'
 * @param: utf32_text:    The input UTF-32 string to convert
 * @param: utf32_dwords:  The amount of UTF-32 dwords found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),char *,__NOTHROW_NCX,unicode_32to8_n,(char *__restrict __utf8_dst, __SIZE_TYPE__ __utf8_maxbytes, char32_t const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_dwords),(__utf8_dst,__utf8_maxbytes,__utf32_text,__utf32_dwords))
#else /* __CRT_HAVE_unicode_32to8_n */
#include <libc/local/unicode/unicode_32to8_n.h>
/* >> unicode_32to8_n(3)
 * Same as `unicode_32to8(3)', but don't write more than `utf8_maxbytes' bytes to `utf8_dst'
 * @param: utf8_dst:      A buffer of at least `utf8_maxbytes' bytes
 * @param: utf8_maxbytes: Max # of words to write to `utf8_dst'
 * @param: utf32_text:    The input UTF-32 string to convert
 * @param: utf32_dwords:  The amount of UTF-32 dwords found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_32to8_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) char *__NOTHROW_NCX(__LIBCCALL unicode_32to8_n)(char *__restrict __utf8_dst, __SIZE_TYPE__ __utf8_maxbytes, char32_t const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_32to8_n))(__utf8_dst, __utf8_maxbytes, __utf32_text, __utf32_dwords); })
#endif /* !__CRT_HAVE_unicode_32to8_n */
#ifdef __CRT_HAVE_unicode_32to16
/* >> unicode_32to16(3)
 * Convert a given utf-32 string to utf-16.
 * @param: utf16_dst:    A buffer of at least `UNICODE_32TO16_MAXBUF(utf32_dwords)' words, or *2 bytes
 * @param: utf32_text:   The input UTF-32 string to convert
 * @param: utf32_dwords: The amount of UTF-32 dwords found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1),char16_t *,__NOTHROW_NCX,unicode_32to16,(char16_t *__restrict __utf16_dst, char32_t const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_dwords),(__utf16_dst,__utf32_text,__utf32_dwords))
#else /* __CRT_HAVE_unicode_32to16 */
#include <libc/local/unicode/unicode_32to16.h>
/* >> unicode_32to16(3)
 * Convert a given utf-32 string to utf-16.
 * @param: utf16_dst:    A buffer of at least `UNICODE_32TO16_MAXBUF(utf32_dwords)' words, or *2 bytes
 * @param: utf32_text:   The input UTF-32 string to convert
 * @param: utf32_dwords: The amount of UTF-32 dwords found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_32to16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1) char16_t *__NOTHROW_NCX(__LIBCCALL unicode_32to16)(char16_t *__restrict __utf16_dst, char32_t const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_32to16))(__utf16_dst, __utf32_text, __utf32_dwords); })
#endif /* !__CRT_HAVE_unicode_32to16 */
#ifdef __CRT_HAVE_unicode_32to16_n
/* >> unicode_32to16_n(3)
 * Same as `unicode_32to16(3)', but don't write more than `utf16_maxwords' words to `utf16_dst'
 * @param: utf16_dst:      A buffer of at least `utf16_dst' words.
 * @param: utf16_maxwords: Max # of words to write to `utf16_dst'
 * @param: utf32_text:     The input UTF-32 string to convert
 * @param: utf32_dwords:   The amount of UTF-32 dwords found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),char16_t *,__NOTHROW_NCX,unicode_32to16_n,(char16_t *__restrict __utf16_dst, __SIZE_TYPE__ __utf16_maxwords, char32_t const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_dwords),(__utf16_dst,__utf16_maxwords,__utf32_text,__utf32_dwords))
#else /* __CRT_HAVE_unicode_32to16_n */
#include <libc/local/unicode/unicode_32to16_n.h>
/* >> unicode_32to16_n(3)
 * Same as `unicode_32to16(3)', but don't write more than `utf16_maxwords' words to `utf16_dst'
 * @param: utf16_dst:      A buffer of at least `utf16_dst' words.
 * @param: utf16_maxwords: Max # of words to write to `utf16_dst'
 * @param: utf32_text:     The input UTF-32 string to convert
 * @param: utf32_dwords:   The amount of UTF-32 dwords found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_32to16_n, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) char16_t *__NOTHROW_NCX(__LIBCCALL unicode_32to16_n)(char16_t *__restrict __utf16_dst, __SIZE_TYPE__ __utf16_maxwords, char32_t const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_32to16_n))(__utf16_dst, __utf16_maxwords, __utf32_text, __utf32_dwords); })
#endif /* !__CRT_HAVE_unicode_32to16_n */
#ifdef __CRT_HAVE_unicode_c8toc16
/* >> unicode_c8toc16(3)
 * @return: *:          Success (*pc16 was filled; the return value
 *                      is  the  number  of bytes  taken  from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified,
 *                      but nothing was read  from `s'; in this  case,
 *                      a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't
 *                      a valid unicode sequence)
 * @return: (size_t)-2: Success,  but  no  character  was  generated
 *                      (`s...+=n', together with `mbs' doesn't form
 *                      a  full  character, but  `mbs'  was updated) */
__CDECLARE(__ATTR_INOUT(4) __ATTR_INS(2, 3) __ATTR_OUT(1),__SIZE_TYPE__,__NOTHROW_NCX,unicode_c8toc16,(char16_t *__restrict __pc16, char const *__restrict __s, __SIZE_TYPE__ __n, mbstate_t *__restrict __mbs),(__pc16,__s,__n,__mbs))
#else /* __CRT_HAVE_unicode_c8toc16 */
#include <libc/local/unicode/unicode_c8toc16.h>
/* >> unicode_c8toc16(3)
 * @return: *:          Success (*pc16 was filled; the return value
 *                      is  the  number  of bytes  taken  from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified,
 *                      but nothing was read  from `s'; in this  case,
 *                      a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't
 *                      a valid unicode sequence)
 * @return: (size_t)-2: Success,  but  no  character  was  generated
 *                      (`s...+=n', together with `mbs' doesn't form
 *                      a  full  character, but  `mbs'  was updated) */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_c8toc16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(4) __ATTR_INS(2, 3) __ATTR_OUT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_c8toc16)(char16_t *__restrict __pc16, char const *__restrict __s, __SIZE_TYPE__ __n, mbstate_t *__restrict __mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_c8toc16))(__pc16, __s, __n, __mbs); })
#endif /* !__CRT_HAVE_unicode_c8toc16 */
#ifdef __CRT_HAVE_unicode_c8toc32
/* >> unicode_c8toc32(3)
 * @return: *:          Success (*pc32 was filled; the return value
 *                      is  the  number  of bytes  taken  from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't
 *                      a valid unicode sequence)
 * @return: (size_t)-2: Success,  but  no  character  was  generated
 *                      (`s...+=n', together with `mbs' doesn't form
 *                      a  full  character, but  `mbs'  was updated) */
__CDECLARE(__ATTR_INOUT(4) __ATTR_INS(2, 3) __ATTR_OUT(1),__SIZE_TYPE__,__NOTHROW_NCX,unicode_c8toc32,(char32_t *__restrict __pc32, char const *__restrict __s, __SIZE_TYPE__ __n, mbstate_t *__restrict __mbs),(__pc32,__s,__n,__mbs))
#else /* __CRT_HAVE_unicode_c8toc32 */
#include <libc/local/unicode/unicode_c8toc32.h>
/* >> unicode_c8toc32(3)
 * @return: *:          Success (*pc32 was filled; the return value
 *                      is  the  number  of bytes  taken  from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't
 *                      a valid unicode sequence)
 * @return: (size_t)-2: Success,  but  no  character  was  generated
 *                      (`s...+=n', together with `mbs' doesn't form
 *                      a  full  character, but  `mbs'  was updated) */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_c8toc32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(4) __ATTR_INS(2, 3) __ATTR_OUT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_c8toc32)(char32_t *__restrict __pc32, char const *__restrict __s, __SIZE_TYPE__ __n, mbstate_t *__restrict __mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_c8toc32))(__pc32, __s, __n, __mbs); })
#endif /* !__CRT_HAVE_unicode_c8toc32 */
#ifdef __CRT_HAVE_unicode_c16toc8
/* >> unicode_c16toc8(3)
 * @return: 0 :         Success, but no characters were generated
 * @return: * :         Success  (this many bytes were written to
 *                      `*pc8'; max is `UNICODE_16TO8_MAXBUF(1)')
 * @return: (size_t)-1: Unicode error (the given input string
 *                      isn't  a   valid  unicode   sequence) */
__CDECLARE(__ATTR_INOUT(3) __ATTR_OUT(1),__SIZE_TYPE__,__NOTHROW_NCX,unicode_c16toc8,(char __pc8[3], char16_t __c16, mbstate_t *__restrict __mbs),(__pc8,__c16,__mbs))
#else /* __CRT_HAVE_unicode_c16toc8 */
#include <libc/local/unicode/unicode_c16toc8.h>
/* >> unicode_c16toc8(3)
 * @return: 0 :         Success, but no characters were generated
 * @return: * :         Success  (this many bytes were written to
 *                      `*pc8'; max is `UNICODE_16TO8_MAXBUF(1)')
 * @return: (size_t)-1: Unicode error (the given input string
 *                      isn't  a   valid  unicode   sequence) */
__NAMESPACE_LOCAL_USING_OR_IMPL(unicode_c16toc8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(3) __ATTR_OUT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL unicode_c16toc8)(char __pc8[3], char16_t __c16, mbstate_t *__restrict __mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_c16toc8))(__pc8, __c16, __mbs); })
#endif /* !__CRT_HAVE_unicode_c16toc8 */

struct format_8to16_data {
	__pc16formatprinter fd_printer;    /* [1..1] Inner printer */
	void               *fd_arg;        /* Argument for `fd_printer' */
	mbstate_t           fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
};
#if defined(__CRT_HAVE_format_8tow) && __SIZEOF_WCHAR_T__ == 2
/* >> format_8to16(3)
 * Format printer (compatible with `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-16 output */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,format_8to16,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8tow,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_8tow) && defined(__LIBDCALL_IS_FORMATPRINTER_CC)
/* >> format_8to16(3)
 * Format printer (compatible with `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-16 output */
__CREDIRECT_DOS(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_8to16,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8tow,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/unicode/format_8tow.h>
/* >> format_8to16(3)
 * Format printer (compatible with `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-16 output */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_8to16)(void *__arg, char const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_8tow))(__arg, __data, __datalen); }
#else /* ... */
#include <libc/local/unicode/format_8to16.h>
/* >> format_8to16(3)
 * Format printer (compatible with `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-16 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_8to16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_8to16)(void *__arg, char const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_8to16))(__arg, __data, __datalen); })
#endif /* !... */

struct format_8to32_data {
	__pc32formatprinter fd_printer;    /* [1..1] Inner printer */
	void               *fd_arg;        /* Argument for `fd_printer' */
	mbstate_t           fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
};
#if defined(__CRT_HAVE_format_8tow) && __SIZEOF_WCHAR_T__ == 4
/* >> format_8to32(3)
 * Format printer (compatible with `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-32 output */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,format_8to32,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8tow,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_8tow) && defined(__LIBKCALL_IS_FORMATPRINTER_CC)
/* >> format_8to32(3)
 * Format printer (compatible with `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-32 output */
__CREDIRECT_KOS(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_8to32,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8tow,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/unicode/format_8tow.h>
/* >> format_8to32(3)
 * Format printer (compatible with `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-32 output */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_8to32)(void *__arg, char const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_8tow))(__arg, __data, __datalen); }
#else /* ... */
#include <libc/local/unicode/format_8to32.h>
/* >> format_8to32(3)
 * Format printer (compatible with `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-32 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_8to32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_8to32)(void *__arg, char const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_8to32))(__arg, __data, __datalen); })
#endif /* !... */

struct format_16to8_data {
	__pformatprinter fd_printer;   /* [1..1] Inner printer */
	void            *fd_arg;       /* Argument for `fd_printer' */
	char16_t         fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
};
#if defined(__CRT_HAVE_format_wto8) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* >> format_16to8(3)
 * Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-8 output */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_16to8,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto8,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wto8)
/* >> format_16to8(3)
 * Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-8 output */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_16to8,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),DOS$format_wto8,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/unicode/format_wto8.h>
/* >> format_16to8(3)
 * Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-8 output */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_16to8)(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wto8))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/unicode/format_16to8.h>
/* >> format_16to8(3)
 * Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-8 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_16to8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_16to8)(void *__arg, char16_t const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_16to8))(__arg, __data, __datalen); })
#endif /* !... */

struct format_32to8_data {
	__pformatprinter fd_printer; /* [1..1] Inner printer */
	void            *fd_arg;     /* Argument for `fd_printer' */
};
#if defined(__CRT_HAVE_format_wto8) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* >> format_32to8(3)
 * Format printer (compatible with `pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-8 output */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_32to8,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto8,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wto8)
/* >> format_32to8(3)
 * Format printer (compatible with `pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-8 output */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_32to8,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),KOS$format_wto8,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/unicode/format_wto8.h>
/* >> format_32to8(3)
 * Format printer (compatible with `pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-8 output */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_32to8)(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wto8))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/unicode/format_32to8.h>
/* >> format_32to8(3)
 * Format printer (compatible with `pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-8 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_32to8, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_32to8)(void *__arg, char32_t const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_32to8))(__arg, __data, __datalen); })
#endif /* !... */

struct format_16to32_data {
	__pc32formatprinter fd_printer;   /* [1..1] Inner printer */
	void               *fd_arg;       /* Argument for `fd_printer' */
	char16_t            fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
};
#if defined(__CRT_HAVE_format_wto32) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* >> format_16to32(3)
 * Format printer (compatible with `pc16formatprinter')  for
 * converting UTF-16 unicode input data into a UTF-32 output */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_16to32,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto32,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wto32)
/* >> format_16to32(3)
 * Format printer (compatible with `pc16formatprinter')  for
 * converting UTF-16 unicode input data into a UTF-32 output */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_16to32,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),DOS$format_wto32,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/unicode/format_wto32.h>
/* >> format_16to32(3)
 * Format printer (compatible with `pc16formatprinter')  for
 * converting UTF-16 unicode input data into a UTF-32 output */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_16to32)(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wto32))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/unicode/format_16to32.h>
/* >> format_16to32(3)
 * Format printer (compatible with `pc16formatprinter')  for
 * converting UTF-16 unicode input data into a UTF-32 output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_16to32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_16to32)(void *__arg, char16_t const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_16to32))(__arg, __data, __datalen); })
#endif /* !... */

struct format_32to16_data {
	__pc16formatprinter fd_printer; /* [1..1] Inner printer */
	void               *fd_arg;     /* Argument for `fd_printer' */
};
#if defined(__CRT_HAVE_format_wto16) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* >> format_32to16(3)
 * Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16  output */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_32to16,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto16,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wto16)
/* >> format_32to16(3)
 * Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16  output */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_32to16,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),KOS$format_wto16,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/unicode/format_wto16.h>
/* >> format_32to16(3)
 * Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16  output */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_32to16)(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wto16))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/unicode/format_32to16.h>
/* >> format_32to16(3)
 * Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16  output */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_32to16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_32to16)(void *__arg, char32_t const *__data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_32to16))(__arg, __data, __datalen); })
#endif /* !... */
#if !defined(____unicode_descriptor_defined) && defined(__CRT_HAVE___unicode_descriptor)
#define ____unicode_descriptor_defined
/* >> __unicode_descriptor(3)
 * Return the internal descriptor for the given `ch'
 * This is the main accessor function for the unicode database, but
 * should not be called directly (unless you know what you're doing
 * and are aware that your code might break should this API ever be
 * changed)
 * Also note that this function never returns `NULL'! */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL,struct __unitraits const *,__NOTHROW,__unicode_descriptor,(char32_t __ch),(__ch))
#endif /* !____unicode_descriptor_defined && __CRT_HAVE___unicode_descriptor */
#if !defined(____unicode_descriptor_digit_defined) && defined(__CRT_HAVE___unicode_descriptor_digit)
#define ____unicode_descriptor_digit_defined
/* >> __unicode_descriptor_digit(3), __unicode_descriptor_digit64(3)
 * Return the integer constant associated  with a given digit  index
 * Returns `0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT8_TYPE__,__NOTHROW,__unicode_descriptor_digit,(__UINT8_TYPE__ __digit_idx),(__digit_idx))
#endif /* !____unicode_descriptor_digit_defined && __CRT_HAVE___unicode_descriptor_digit */
#ifdef __UINT64_TYPE__
#if !defined(____unicode_descriptor_digit64_defined) && defined(__CRT_HAVE___unicode_descriptor_digit64)
#define ____unicode_descriptor_digit64_defined
/* >> __unicode_descriptor_digit(3), __unicode_descriptor_digit64(3)
 * Return the integer constant associated  with a given digit  index
 * Returns `0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW,__unicode_descriptor_digit64,(__UINT8_TYPE__ __digit_idx),(__digit_idx))
#endif /* !____unicode_descriptor_digit64_defined && __CRT_HAVE___unicode_descriptor_digit64 */
#endif /* __UINT64_TYPE__ */
#ifndef __NO_FPU
#if !defined(____unicode_descriptor_digitd_defined) && defined(__CRT_HAVE___unicode_descriptor_digitd)
#define ____unicode_descriptor_digitd_defined
/* >> __unicode_descriptor_digitd(3), __unicode_descriptor_digitld(3)
 * Return the floating-point constant associated with a given digit index
 * Returns `0.0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__unicode_descriptor_digitd,(__UINT8_TYPE__ __digit_idx),(__digit_idx))
#endif /* !____unicode_descriptor_digitd_defined && __CRT_HAVE___unicode_descriptor_digitd */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef ____unicode_descriptor_digitld_defined
#define ____unicode_descriptor_digitld_defined
#ifdef __CRT_HAVE___unicode_descriptor_digitld
/* >> __unicode_descriptor_digitd(3), __unicode_descriptor_digitld(3)
 * Return the floating-point constant associated with a given digit index
 * Returns `0.0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__unicode_descriptor_digitld,(__UINT8_TYPE__ __digit_idx),(__digit_idx))
#elif defined(__CRT_HAVE___unicode_descriptor_digitd) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* >> __unicode_descriptor_digitd(3), __unicode_descriptor_digitld(3)
 * Return the floating-point constant associated with a given digit index
 * Returns `0.0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__unicode_descriptor_digitld,(__UINT8_TYPE__ __digit_idx),__unicode_descriptor_digitd,(__digit_idx))
#else /* ... */
#undef ____unicode_descriptor_digitld_defined
#endif /* !... */
#endif /* !____unicode_descriptor_digitld_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */

/* The max number of characters ever written by `unicode_fold' */
#define UNICODE_FOLDED_MAX 3

#ifdef __CRT_HAVE_unicode_fold
/* >> unicode_fold(3)
 * Fold the given unicode character `ch'
 * @param: ch:  The unicode character to case-fold
 * @param: buf: Output buffer for the case-folding sequence
 * @return: * : A pointer into `buf' to 1 past the last-written character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_OUT(2),char32_t *,__NOTHROW_NCX,unicode_fold,(char32_t __ch, char32_t __buf[3]),(__ch,__buf))
#else /* __CRT_HAVE_unicode_fold */
/* >> unicode_fold(3)
 * Fold the given unicode character `ch'
 * @param: ch:  The unicode character to case-fold
 * @param: buf: Output buffer for the case-folding sequence
 * @return: * : A pointer into `buf' to 1 past the last-written character */
__LOCAL __ATTR_RETNONNULL __ATTR_OUT(2) char32_t *__NOTHROW_NCX(__LIBCCALL unicode_fold)(char32_t __ch, char32_t __buf[3]) { __buf[0] = __ch; return __buf + 1; }
#endif /* !__CRT_HAVE_unicode_fold */

/* Unicode character traits test functions */
#ifdef ____unicode_descriptor_defined
#define unicode_iscntrl(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISCNTRL) != 0)   /* Control characters */
#define unicode_istab(ch)     ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISTAB) != 0)     /* 09, 0B-0C */
#define unicode_iswhite(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISWHITE) != 0)   /* Pure whitespace characters (excluding tabs and line-feeds) */
#define unicode_isempty(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISEMPTY) != 0)   /* unicode_istab || unicode_iswhite */
#define unicode_islf(ch)      ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISLF) != 0)      /* Line-feed characters */
#define unicode_isspace(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSPACE) != 0)   /* unicode_isempty | unicode_islf */
#define unicode_islower(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISLOWER) != 0)   /* Lowercase characters */
#define unicode_isupper(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISUPPER) != 0)   /* Uppercase characters */
#define unicode_isalpha(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISALPHA) != 0)   /* Alphabetical characters */
#define unicode_isdigit(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISDIGIT) != 0)   /* Only includes stuff like "2" */
#define unicode_ishex(ch)     ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISHEX) != 0)     /* 'a'-'f', 'A'-'F' */
#define unicode_isxdigit(ch)  ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISXDIGIT) != 0)  /* unicode_isdigit || unicode_ishex */
#define unicode_isalnum(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISALNUM) != 0)   /* unicode_isdigit || unicode_isalpha */
#define unicode_ispunct(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISPUNCT) != 0)   /* Punctuation (such as '.') */
#define unicode_isgraph(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISGRAPH) != 0)   /* Graphical characters (everything printable, excluding spaces) */
#define unicode_isprint(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISPRINT) != 0)   /* unicode_isgraph || unicode_iswhite */
#define unicode_isblank(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISBLANK) != 0)   /* unicode_iswhite || (ch == '\t') */
#define unicode_istitle(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISTITLE) != 0)   /* title-case */
#define unicode_isnumeric(ch) ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISNUMERIC) != 0) /* Includes stuff like "²" */
#define unicode_issymstrt(ch) ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSYMSTRT) != 0) /* Character may appear at the start of a symbol name */
#define unicode_issymcont(ch) ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSYMCONT) != 0) /* Character may appear in the middle of a symbol name */

#define unicode_tolower(ch) ((ch) + __unicode_descriptor(ch)->__ut_lower)
#define unicode_toupper(ch) ((ch) + __unicode_descriptor(ch)->__ut_upper)
#define unicode_totitle(ch) ((ch) + __unicode_descriptor(ch)->__ut_title)

/* >> unicode_asdigit(3)
 * Check if `ch' is a digit- or hex-character (s.a. `unicode_isxdigit()'),
 * and if so, store  its digit value in  `*presult' and return `true'  iff
 * its  digit value is  less than `radix'.  Otherwise, leave `*presult' as
 * undefined and return `false'.
 * Note that `radix' values >= 16 are supported, but the cut-off  value
 * until which they are is  implementation-defined (but always >=  16).
 * If digit characters which equate to values greater than 16 should be
 * supported, then `unicode_getnumeric(64|dbl|ldbl)' should be used! */
#ifdef __INTELLISENSE__
__ATTR_WUNUSED __ATTR_OUT(3) __BOOL
__NOTHROW_NCX(unicode_asdigit)(char32_t ch, __UINT8_TYPE__ radix,
                               __UINT8_TYPE__ * __restrict presult);
#else /* __INTELLISENSE__ */
#define unicode_asdigit(ch, radix, presult) \
	((*(presult) = __unicode_asdigit(ch)) <= (radix))
#endif /* !__INTELLISENSE__ */

#ifndef ____unicode_asdigit_defined
#define ____unicode_asdigit_defined
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT8_TYPE__
__NOTHROW(__LIBCCALL __unicode_asdigit)(char32_t __ch) {
	struct __unitraits const *__traits = __unicode_descriptor(__ch);
	if (!(__traits->__ut_flags & __UNICODE_ISXDIGIT))
		return 0xff; /* Filter out stuff like `²' */
	/* We assume that `__ut_digit_idx < __UNICODE_DIGIT_IDENTITY_COUNT', and
	 * that `__UNICODE_DIGIT_IDENTITY_COUNT >= 16'. With these  assumptions,
	 * we are allowed to simply return the digit index to our caller  (which
	 * is  the `unicode_asdigit(3)'  macro), who  will then  check that said
	 * index is less than their radix.
	 *
	 * Thus, so-long as `radix <= __UNICODE_DIGIT_IDENTITY_COUNT', there won't
	 * be any inconsistencies! */
	return __traits->__ut_digit_idx;
}
#endif /* !____unicode_asdigit_defined */

/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT8_TYPE__
__NOTHROW(__LIBCCALL unicode_getnumeric)(char32_t __ch) {
	struct __unitraits const *__traits = __unicode_descriptor(__ch);
#ifndef __OPTIMIZE_SIZE__
	if __likely(__traits->__ut_digit_idx < __UNICODE_DIGIT_IDENTITY_COUNT)
		return __traits->__ut_digit_idx;
#endif /* !__OPTIMIZE_SIZE__ */
#ifdef ____unicode_descriptor_digit_defined
	return __unicode_descriptor_digit(__traits->__ut_digit_idx);
#elif defined(____unicode_descriptor_digit64_defined)
	return (__UINT8_TYPE__)__unicode_descriptor_digit64(__traits->__ut_digit_idx);
#else /* ____unicode_descriptor_digit64_defined */
	return 0;
#endif /* !____unicode_descriptor_digit64_defined */
}

#ifdef __UINT64_TYPE__
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__
__NOTHROW(__LIBCCALL unicode_getnumeric64)(char32_t __ch) {
	struct __unitraits const *__traits = __unicode_descriptor(__ch);
#ifndef __OPTIMIZE_SIZE__
	if __likely(__traits->__ut_digit_idx < __UNICODE_DIGIT_IDENTITY_COUNT)
		return __traits->__ut_digit_idx;
#endif /* !__OPTIMIZE_SIZE__ */
#ifdef ____unicode_descriptor_digit64_defined
	return __unicode_descriptor_digit64(__traits->__ut_digit_idx);
#elif defined(____unicode_descriptor_digit_defined)
	return __unicode_descriptor_digit(__traits->__ut_digit_idx);
#else /* ... */
	return 0;
#endif /* !... */
}
#endif /* __UINT64_TYPE__ */

#ifndef __NO_FPU
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL unicode_getnumericdbl)(char32_t __ch) {
	struct __unitraits const *__traits = __unicode_descriptor(__ch);
#ifndef __OPTIMIZE_SIZE__
	if __likely(__traits->__ut_digit_idx < __UNICODE_DIGIT_IDENTITY_COUNT)
		return (double)__traits->__ut_digit_idx;
#endif /* !__OPTIMIZE_SIZE__ */
#ifdef ____unicode_descriptor_digitd_defined
	return __unicode_descriptor_digitd(__traits->__ut_digit_idx);
#else /* ____unicode_descriptor_digitd_defined */
	return 0.0;
#endif /* !____unicode_descriptor_digitd_defined */
}

#ifdef __COMPILER_HAVE_LONGDOUBLE
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
#define unicode_getnumericldbl(ch) ((__LONGDOUBLE)unicode_getnumericdbl(ch))
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL unicode_getnumericldbl)(char32_t __ch) {
	struct __unitraits const *__traits = __unicode_descriptor(__ch);
#ifndef __OPTIMIZE_SIZE__
	if __likely(__traits->__ut_digit_idx < __UNICODE_DIGIT_IDENTITY_COUNT)
		return (__LONGDOUBLE)__traits->__ut_digit_idx;
#endif /* !__OPTIMIZE_SIZE__ */
#ifdef ____unicode_descriptor_digitld_defined
	return __unicode_descriptor_digitld(__traits->__ut_digit_idx);
#elif defined(____unicode_descriptor_digitd_defined)
	return __unicode_descriptor_digitd(__traits->__ut_digit_idx);
#else /* ... */
	return 0.0L;
#endif /* !... */
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */

#else /* ____unicode_descriptor_defined */

#include <libc/ctype.h>
#define unicode_iscntrl(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_iscntrl(ch))              /* Control characters */
#define unicode_istab(ch)     ((ch) == 9 || (ch) == 0xb || (ch) == 0xc)                          /* 09, 0B-0C */
#define unicode_iswhite(ch)   ((ch) == 0x20)                                                     /* Pure whitespace characters (excluding tabs and line-feeds) */
#define unicode_isempty(ch)   (unicode_istab(ch) || unicode_iswhite(ch))                         /* unicode_istab || unicode_iswhite */
#define unicode_islf(ch)      ((ch) == 0xa || (ch) == 0xd)                                       /* Line-feed characters */
#define unicode_isspace(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isspace(ch))              /* unicode_isempty | unicode_islf */
#define unicode_islower(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_islower(ch))              /* Lowercase characters */
#define unicode_isupper(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isupper(ch))              /* Uppercase characters */
#define unicode_isalpha(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isalpha(ch))              /* Alphabetical characters */
#define unicode_isdigit(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isdigit(ch))              /* Only includes stuff like "2" */
#define unicode_ishex(ch)     (((ch) >= 0x41 && (ch) <= 0x46) || ((ch) >= 0x61 && (ch) <= 0x66)) /* 'a'-'f', 'A'-'F' */
#define unicode_isxdigit(ch)  ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isxdigit(ch))             /* unicode_isdigit || unicode_ishex */
#define unicode_isalnum(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isalnum(ch))              /* unicode_isdigit || unicode_isalpha */
#define unicode_ispunct(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_ispunct(ch))              /* Punctuation (such as '.') */
#define unicode_isgraph(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isgraph(ch))              /* Graphical characters (everything printable, excluding spaces) */
#define unicode_isprint(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isprint(ch))              /* unicode_isgraph || unicode_iswhite */
#define unicode_isblank(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isblank(ch))              /* unicode_iswhite || (ch == '\t') */
#define unicode_istitle(ch)   unicode_isupper(ch)                                                /* title-case */
#define unicode_isnumeric(ch) unicode_isdigit(ch)                                                /* Includes stuff like "²" */
#define unicode_issymstrt(ch) (unicode_isalpha(ch) || (ch) == 0x5f || (ch) == 0x24)              /* Character may appear at the start of a symbol name */
#define unicode_issymcont(ch) (unicode_isalnum(ch) || (ch) == 0x5f || (ch) == 0x24)              /* Character may appear in the middle of a symbol name */

#define unicode_tolower(ch) ((__UINT32_TYPE__)(ch) <= 0x7f ? __libc_tolower(ch) : (ch))
#define unicode_toupper(ch) ((__UINT32_TYPE__)(ch) <= 0x7f ? __libc_toupper(ch) : (ch))
#define unicode_totitle(ch) unicode_toupper(ch)

/* >> unicode_asdigit(3)
 * Check if `ch' is a digit- or hex-character (s.a. `unicode_isxdigit()'),
 * and if so, store  its digit value in  `*presult' and return `true'  iff
 * its  digit value is  less than `radix'.  Otherwise, leave `*presult' as
 * undefined and return `false'.
 * Note that `radix' values >= 16 are supported, but the cut-off  value
 * until which they are is  implementation-defined (but always >=  16).
 * If digit characters which equate to values greater than 16 should be
 * supported, then `unicode_getnumeric(64|dbl|ldbl)' should be used! */
#ifdef __INTELLISENSE__
__ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW_NCX(unicode_asdigit)(char32_t ch, __UINT8_TYPE__ radix,
                               __UINT8_TYPE__ * __restrict presult);
#else /* __INTELLISENSE__ */
#define unicode_asdigit(ch, radix, presult)                                                \
	(((ch) >= 0x30 && (ch) <= 0x39)                                                        \
	 ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x30)) <= radix)                               \
	 : ((ch) >= 0x41 && (ch) <= 0x46 && (!__builtin_constant_p(radix) || (radix) >= 10))   \
	   ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x37)) <= radix)                             \
	   : ((ch) >= 0x61 && (ch) <= 0x66 && (!__builtin_constant_p(radix) || (radix) >= 10)) \
	     ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x57)) <= radix)                           \
	     : 0)
#endif /* !__INTELLISENSE__ */

#define __unicode_getnumeric(ch)       \
	((ch) >= 0x30 && (ch) <= 0x39     \
	 ? (ch)-0x30                      \
	 : (ch) >= 0x41 && (ch) <= 0x46   \
	   ? (ch)-0x37                    \
	   : (ch) >= 0x61 && (ch) <= 0x66 \
	     ? (ch)-0x57                  \
	     : 0)

/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define unicode_getnumeric(ch) ((__UINT8_TYPE__)__unicode_getnumeric(ch))

#ifdef __UINT64_TYPE__
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define unicode_getnumeric64(ch) ((__UINT64_TYPE__)__unicode_getnumeric(ch))
#endif /* __UINT64_TYPE__ */

#ifndef __NO_FPU
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define unicode_getnumericdbl(ch) ((double)__unicode_getnumeric(ch))

#ifdef __COMPILER_HAVE_LONGDOUBLE
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define unicode_getnumericldbl(ch) ((__LONGDOUBLE)__unicode_getnumeric(ch))
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#endif /* !____unicode_descriptor_defined */

/* Wide-character integration */
#if __SIZEOF_WCHAR_T__ == 4
#define UNICODE_8TOW_MAXBUF UNICODE_8TO32_MAXBUF
#define UNICODE_WTO8_MAXBUF UNICODE_32TO8_MAXBUF
#define unicode_len8tow     unicode_len8to32
#define unicode_wto8(utf8_dst, wchar_text, wchar_words) \
	unicode_32to8(utf8_dst, (char32_t const *)(wchar_text), wchar_words)
#define unicode_wto8_n(utf8_dst, utf8_maxbytes, wchar_text, wchar_words) \
	unicode_32to8_n(utf8_dst, utf8_maxbytes, (char32_t const *)(wchar_text), wchar_words)
#define unicode_8tow(wide_dst, utf8_text, utf8_bytes) \
	(wchar_t *)unicode_8to32((char32_t *)(wide_dst), utf8_text, utf8_bytes)
#define unicode_8tow_n(wide_dst, wide_maxwords, utf8_text, utf8_bytes) \
	(wchar_t *)unicode_8to32_n((char32_t *)(wide_dst), wide_maxwords, utf8_text, utf8_bytes)
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define UNICODE_8TOW_MAXBUF UNICODE_8TO16_MAXBUF
#define UNICODE_WTO8_MAXBUF UNICODE_16TO8_MAXBUF
#define unicode_len8tow     unicode_len8to16
#define unicode_wto8(utf8_dst, wchar_text, wchar_words) \
	unicode_16to8(utf8_dst, (char16_t const *)(wchar_text), wchar_words)
#define unicode_wto8_n(utf8_dst, utf8_maxbytes, wchar_text, wchar_words) \
	unicode_16to8_n(utf8_dst, utf8_maxbytes, (char16_t const *)(wchar_text), wchar_words)
#define unicode_8tow(wide_dst, utf8_text, utf8_bytes) \
	(wchar_t *)unicode_8to16((char16_t *)(wide_dst), utf8_text, utf8_bytes)
#define unicode_8tow_n(wide_dst, wide_maxwords, utf8_text, utf8_bytes) \
	(wchar_t *)unicode_8to16_n((char16_t *)(wide_dst), wide_maxwords, utf8_text, utf8_bytes)
#endif /* __SIZEOF_WCHAR_T__ != 4 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_UNICODE_H */
