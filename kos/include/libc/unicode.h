/* HASH CRC-32:0x91e53964 */
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
#ifndef _LIBC_UNICODE_H
#define _LIBC_UNICODE_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include "core/unicode.h"

/* >> unicode_readutf8(3)
 * Read a single Unicode character from a given UTF-8 string */
#define __libc_unicode_readutf8 __libc_core_unicode_readutf8
/* >> unicode_readutf8_rev(3)
 * Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
#define __libc_unicode_readutf8_rev __libc_core_unicode_readutf8_rev
/* >> unicode_readutf8_n(3)
 * Same as `unicode_readutf8()', but don't read past `text_end' */
#define __libc_unicode_readutf8_n __libc_core_unicode_readutf8_n
/* >> unicode_readutf8_rev_n(3)
 * Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
#define __libc_unicode_readutf8_rev_n __libc_core_unicode_readutf8_rev_n
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
#define __libc_unicode_readutf16 __libc_core_unicode_readutf16
/* >> unicode_readutf16_n(3)
 * Same as `unicode_readutf16()', but don't read past `text_end' */
#define __libc_unicode_readutf16_n __libc_core_unicode_readutf16_n
/* >> unicode_readutf16_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
#define __libc_unicode_readutf16_rev __libc_core_unicode_readutf16_rev
/* >> unicode_readutf16_rev_n(3)
 * Same as `unicode_readutf16_rev()', but don't read ahead of `text_start' */
#define __libc_unicode_readutf16_rev_n __libc_core_unicode_readutf16_rev_n
/* >> unicode_writeutf8(3)
 * Write  a given Unicode character `ch' to `dst'  and return a pointer to its end
 * location. This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
#define __libc_unicode_writeutf8 __libc_core_unicode_writeutf8
/* >> unicode_writeutf16(3)
 * Write a given Unicode character  `ch' to `dst' and return  a pointer to its  end
 * location. This function will write at most `UNICODE_UTF16_CURLEN' words to `dst' */
#define __libc_unicode_writeutf16 __libc_core_unicode_writeutf16
#if !defined(____libc___unicode_descriptor_defined) && defined(____libc_core___unicode_descriptor_defined)
#define ____libc___unicode_descriptor_defined
#define __libc___unicode_descriptor __libc_core___unicode_descriptor
#endif /* !____libc___unicode_descriptor_defined && ____libc_core___unicode_descriptor_defined */
#if !defined(____libc___unicode_descriptor_digit_defined) && defined(____libc_core___unicode_descriptor_digit_defined)
#define ____libc___unicode_descriptor_digit_defined
#define __libc___unicode_descriptor_digit __libc_core___unicode_descriptor_digit
#endif /* !____libc___unicode_descriptor_digit_defined && ____libc_core___unicode_descriptor_digit_defined */
#if !defined(____libc___unicode_descriptor_digit64_defined) && defined(____libc_core___unicode_descriptor_digit64_defined)
#define ____libc___unicode_descriptor_digit64_defined
#define __libc___unicode_descriptor_digit64 __libc_core___unicode_descriptor_digit64
#endif /* !____libc___unicode_descriptor_digit64_defined && ____libc_core___unicode_descriptor_digit64_defined */
#if !defined(____libc___unicode_descriptor_digitd_defined) && defined(____libc_core___unicode_descriptor_digitd_defined)
#define ____libc___unicode_descriptor_digitd_defined
#define __libc___unicode_descriptor_digitd __libc_core___unicode_descriptor_digitd
#endif /* !____libc___unicode_descriptor_digitd_defined && ____libc_core___unicode_descriptor_digitd_defined */
#if !defined(____libc___unicode_descriptor_digitld_defined) && defined(____libc_core___unicode_descriptor_digitld_defined)
#define ____libc___unicode_descriptor_digitld_defined
#define __libc___unicode_descriptor_digitld __libc_core___unicode_descriptor_digitld
#endif /* !____libc___unicode_descriptor_digitld_defined && ____libc_core___unicode_descriptor_digitld_defined */
/* >> unicode_fold(3)
 * Fold the given unicode character `ch' */
#define __libc_unicode_fold __libc_core_unicode_fold
#define __LIBC_UNICODE_UTF8_MAXLEN              8
#define __LIBC_UNICODE_UTF8_CURLEN              7
#define __LIBC_UNICODE_UTF16_MAXLEN             2
#define __LIBC_UNICODE_UTF16_CURLEN             2
#define __LIBC_UNICODE_UTF32_MAXLEN             1
#define __LIBC_UNICODE_UTF32_CURLEN             1
#define __LIBC_UNICODE_ISVALIDUTF16(ch)         (sizeof(ch) == 1 ? 1 : ((sizeof(ch) == 2 || (ch) <= 0x10ffff)) && ((ch) < 0xd800 || (ch) > 0xdfff))
#define __LIBC_UNICODE_MAXCHAR                  0x10ffff
#define __LIBC_UNICODE_8TO16_MAXBUF(num_chars)  (num_chars)
#define __LIBC_UNICODE_8TO32_MAXBUF(num_chars)  (num_chars)
#define __LIBC_UNICODE_16TO8_MAXBUF(num_chars)  ((num_chars) * 3)
#define __LIBC_UNICODE_16TO32_MAXBUF(num_chars) (num_chars)
#define __LIBC_UNICODE_32TO8_MAXBUF(num_chars)  ((num_chars) * 7)
#define __LIBC_UNICODE_32TO16_MAXBUF(num_chars) ((num_chars) * 2)
#include <hybrid/typecore.h>
#include <bits/crt/unicode.h>

/* Unicode character traits test functions */
#ifdef ____libc___unicode_descriptor_defined
#define __libc_unicode_iscntrl(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISCNTRL) != 0)   /* Control characters */
#define __libc_unicode_istab(ch)     ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISTAB) != 0)     /* 09, 0B-0C */
#define __libc_unicode_iswhite(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISWHITE) != 0)   /* Pure whitespace characters (excluding tabs and line-feeds) */
#define __libc_unicode_isempty(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISEMPTY) != 0)   /* unicode_istab || unicode_iswhite */
#define __libc_unicode_islf(ch)      ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISLF) != 0)      /* Line-feed characters */
#define __libc_unicode_isspace(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSPACE) != 0)   /* unicode_isempty | unicode_islf */
#define __libc_unicode_islower(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISLOWER) != 0)   /* Lowercase characters */
#define __libc_unicode_isupper(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISUPPER) != 0)   /* Uppercase characters */
#define __libc_unicode_isalpha(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISALPHA) != 0)   /* Alphabetical characters */
#define __libc_unicode_isdigit(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISDIGIT) != 0)   /* Only includes stuff like "2" */
#define __libc_unicode_ishex(ch)     ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISHEX) != 0)     /* 'a'-'f', 'A'-'F' */
#define __libc_unicode_isxdigit(ch)  ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISXDIGIT) != 0)  /* unicode_isdigit || unicode_ishex */
#define __libc_unicode_isalnum(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISALNUM) != 0)   /* unicode_isdigit || unicode_isalpha */
#define __libc_unicode_ispunct(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISPUNCT) != 0)   /* Punctuation (such as '.') */
#define __libc_unicode_isgraph(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISGRAPH) != 0)   /* Graphical characters (everything printable, excluding spaces) */
#define __libc_unicode_isprint(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISPRINT) != 0)   /* unicode_isgraph || unicode_iswhite */
#define __libc_unicode_isblank(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISBLANK) != 0)   /* unicode_iswhite || (ch == '\t') */
#define __libc_unicode_istitle(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISTITLE) != 0)   /* title-case */
#define __libc_unicode_isnumeric(ch) ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISNUMERIC) != 0) /* Includes stuff like "²" */
#define __libc_unicode_issymstrt(ch) ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSYMSTRT) != 0) /* Character may appear at the start of a symbol name */
#define __libc_unicode_issymcont(ch) ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSYMCONT) != 0) /* Character may appear in the middle of a symbol name */

#define __libc_unicode_tolower(ch) ((ch) + __libc___unicode_descriptor(ch)->__ut_lower)
#define __libc_unicode_toupper(ch) ((ch) + __libc___unicode_descriptor(ch)->__ut_upper)
#define __libc_unicode_totitle(ch) ((ch) + __libc___unicode_descriptor(ch)->__ut_title)

__DECL_BEGIN

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
__ATTR_WUNUSED __ATTR_ACCESS_WR(3) __BOOL
__NOTHROW_NCX(__libc_unicode_asdigit)(__CHAR32_TYPE__ ch, __UINT8_TYPE__ radix,
                                      __UINT8_TYPE__ * __restrict presult);
#else /* __INTELLISENSE__ */
#define __libc_unicode_asdigit(ch, radix, presult) \
	((*(presult) = __unicode_asdigit(ch)) <= (radix))
#endif /* !__INTELLISENSE__ */

#ifndef ____unicode_asdigit_defined
#define ____unicode_asdigit_defined
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT8_TYPE__
__NOTHROW(__LIBCCALL __unicode_asdigit)(__CHAR32_TYPE__ __ch) {
	struct __unitraits const *__traits = __libc___unicode_descriptor(__ch);
	if (!(__traits->__ut_flags & __UNICODE_ISXDIGIT))
		return 0xff;
	return __traits->__ut_digit_idx;
}
#endif /* !____unicode_asdigit_defined */

/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT8_TYPE__
__NOTHROW(__LIBCCALL __libc_unicode_getnumeric)(__CHAR32_TYPE__ __ch) {
	struct __unitraits const *__traits = __libc___unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return __traits->__ut_digit_idx;
#ifdef ____libc___unicode_descriptor_digit_defined
	return __libc___unicode_descriptor_digit(__traits->__ut_digit_idx);
#elif defined(____libc___unicode_descriptor_digit64_defined)
	return (__UINT8_TYPE__)__libc___unicode_descriptor_digit64(__traits->__ut_digit_idx);
#else /* ... */
	return 0;
#endif /* !... */
}

#ifdef __UINT64_TYPE__
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__
__NOTHROW(__LIBCCALL __libc_unicode_getnumeric64)(__CHAR32_TYPE__ __ch) {
	struct __unitraits const *__traits = __libc___unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return __traits->__ut_digit_idx;
#ifdef ____libc___unicode_descriptor_digit64_defined
	return __libc___unicode_descriptor_digit64(__traits->__ut_digit_idx);
#elif defined(____libc___unicode_descriptor_digit_defined)
	return __libc___unicode_descriptor_digit(__traits->__ut_digit_idx);
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
__NOTHROW(__LIBCCALL __libc_unicode_getnumericdbl)(__CHAR32_TYPE__ __ch) {
	struct __unitraits const *__traits = __libc___unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return (double)__traits->__ut_digit_idx;
#ifdef ____libc___unicode_descriptor_digitd_defined
	return __libc___unicode_descriptor_digitd(__traits->__ut_digit_idx);
#else /* ____libc___unicode_descriptor_digitd_defined */
	return 0.0;
#endif /* !____libc___unicode_descriptor_digitd_defined */
}

#ifdef __COMPILER_HAVE_LONGDOUBLE
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __libc_unicode_getnumericldbl)(__CHAR32_TYPE__ __ch) {
	struct __unitraits const *__traits = __libc___unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return (__LONGDOUBLE)__traits->__ut_digit_idx;
#ifdef ____libc___unicode_descriptor_digitld_defined
	return __libc___unicode_descriptor_digitld(__traits->__ut_digit_idx);
#elif defined(____libc___unicode_descriptor_digitd_defined)
	return __libc___unicode_descriptor_digitd(__traits->__ut_digit_idx);
#else /* ... */
	return 0.0L;
#endif /* !... */
}
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
__DECL_END

#else /* ____libc___unicode_descriptor_defined */

#include <libc/ctype.h>
#define __libc_unicode_iscntrl(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_iscntrl(ch))              /* Control characters */
#define __libc_unicode_istab(ch)     ((ch) == 9 || (ch) == 0xb || (ch) == 0xc)                          /* 09, 0B-0C */
#define __libc_unicode_iswhite(ch)   ((ch) == 0x20)                                                     /* Pure whitespace characters (excluding tabs and line-feeds) */
#define __libc_unicode_isempty(ch)   (__libc_unicode_istab(ch) || __libc_unicode_iswhite(ch))           /* unicode_istab || unicode_iswhite */
#define __libc_unicode_islf(ch)      ((ch) == 0xa || (ch) == 0xd)                                       /* Line-feed characters */
#define __libc_unicode_isspace(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isspace(ch))              /* unicode_isempty | unicode_islf */
#define __libc_unicode_islower(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_islower(ch))              /* Lowercase characters */
#define __libc_unicode_isupper(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isupper(ch))              /* Uppercase characters */
#define __libc_unicode_isalpha(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isalpha(ch))              /* Alphabetical characters */
#define __libc_unicode_isdigit(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isdigit(ch))              /* Only includes stuff like "2" */
#define __libc_unicode_ishex(ch)     ((ch) >= (0x41 && (ch) <= 0x46) || ((ch) >= 0x61 && (ch) <= 0x66)) /* 'a'-'f', 'A'-'F' */
#define __libc_unicode_isxdigit(ch)  ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isxdigit(ch))             /* unicode_isdigit || unicode_ishex */
#define __libc_unicode_isalnum(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isalnum(ch))              /* unicode_isdigit || unicode_isalpha */
#define __libc_unicode_ispunct(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_ispunct(ch))              /* Punctuation (such as '.') */
#define __libc_unicode_isgraph(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isgraph(ch))              /* Graphical characters (everything printable, excluding spaces) */
#define __libc_unicode_isprint(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isprint(ch))              /* unicode_isgraph || unicode_iswhite */
#define __libc_unicode_isblank(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isblank(ch))              /* unicode_iswhite || (ch == '\t') */
#define __libc_unicode_istitle(ch)   __libc_unicode_isupper(ch)                                         /* title-case */
#define __libc_unicode_isnumeric(ch) __libc_unicode_isdigit(ch)                                         /* Includes stuff like "²" */
#define __libc_unicode_issymstrt(ch) (__libc_unicode_isalpha(ch) || (ch) == 0x5f || (ch) == 0x24)       /* Character may appear at the start of a symbol name */
#define __libc_unicode_issymcont(ch) (__libc_unicode_isalnum(ch) || (ch) == 0x5f || (ch) == 0x24)       /* Character may appear in the middle of a symbol name */

#define __libc_unicode_tolower(ch) ((__UINT32_TYPE__)(ch) <= 0x7f ? __libc_tolower(ch) : (ch))
#define __libc_unicode_toupper(ch) ((__UINT32_TYPE__)(ch) <= 0x7f ? __libc_toupper(ch) : (ch))
#define __libc_unicode_totitle(ch) __libc_unicode_toupper(ch)

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
__ATTR_WUNUSED __ATTR_ACCESS_WR(3) __BOOL
__NOTHROW_NCX(__libc_unicode_asdigit)(__CHAR32_TYPE__ ch, __UINT8_TYPE__ radix,
                                      __UINT8_TYPE__ *__restrict presult);
#else /* __INTELLISENSE__ */
#define __libc_unicode_asdigit(ch, radix, presult)                                         \
	(((ch) >= 0x30 && (ch) <= 0x39)                                                        \
	 ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x30)) <= radix)                               \
	 : ((ch) >= 0x41 && (ch) <= 0x46 && (!__builtin_constant_p(radix) || (radix) >= 10))   \
	   ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x37)) <= radix)                             \
	   : ((ch) >= 0x61 && (ch) <= 0x66 && (!__builtin_constant_p(radix) || (radix) >= 10)) \
	     ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x57)) <= radix)                           \
	     : 0)
#endif /* !__INTELLISENSE__ */

#define ____libc_unicode_getnumeric(ch) \
	((ch) >= 0x30 && (ch) <= 0x39       \
	 ? (ch)-0x30                        \
	 : (ch) >= 0x41 && (ch) <= 0x46     \
	   ? (ch)-0x37                      \
	   : (ch) >= 0x61 && (ch) <= 0x66   \
	     ? (ch)-0x57                    \
	     : 0)

/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define __libc_unicode_getnumeric(ch) ((__UINT8_TYPE__)____libc_unicode_getnumeric(ch))

#ifdef __UINT64_TYPE__
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define __libc_unicode_getnumeric64(ch) ((__UINT64_TYPE__)____libc_unicode_getnumeric(ch))
#endif /* __UINT64_TYPE__ */

#ifndef __NO_FPU
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define __libc_unicode_getnumericdbl(ch) ((double)____libc_unicode_getnumeric(ch))

#ifdef __COMPILER_HAVE_LONGDOUBLE
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define __libc_unicode_getnumericldbl(ch) ((__LONGDOUBLE)____libc_unicode_getnumeric(ch))
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#endif /* !____libc___unicode_descriptor_defined */


#endif /* __CC__ */

#endif /* !_LIBC_UNICODE_H */
