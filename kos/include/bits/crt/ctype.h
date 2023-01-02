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
#ifndef _BITS_CRT_CTYPE_H
#define _BITS_CRT_CTYPE_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

/* CRT-specific optimized implementation for <ctype.h> functions */

#ifdef __CC__

#if defined(__CRT_KOS) && defined(__CRT_HAVE___ctype_C_flags)

/************************************************************************/
/* KOS                                                                  */

/* Because KOS uses UTF-8 through, functions from <ctype.h> must
 * operate on only those characters which can be represented  in
 * single-byte mode (iow: ASCII)
 *
 * To improve performance, we make use of a lookup table that
 * defines flags and implement the tolower/toupper functions.
 *
 * CTYPE flags are defined as follows:
 *     0x01: iscntrl   00-1F, 7F
 *     0x02: isspace   09-0D, 20
 *     0x04: islower   61-7A
 *     0x08: isupper   41-5A
 *     0x10: isdigit   30-39
 *     0x20: ishex     41-46, 61-66
 *     0x40: ispunct   21-2F, 3A-40, 5B-60, 7B-7E
 *     0x80: -         20 */
#ifndef ____ctype_C_flags_defined
#define ____ctype_C_flags_defined
__DECL_BEGIN __LIBC __UINT8_TYPE__ const __ctype_C_flags[256] __CASMNAME_SAME("__ctype_C_flags"); __DECL_END
#endif /* !____ctype_C_flags_defined */

/* WARNING: The magic character trait flags below are directly referenced by `/kos/kos/src/libregex/regcomp.c' */
#define __crt_iscntrl(ch)  (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0x01)
#define __crt_isspace(ch)  (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0x02)
#define __crt_islower(ch)  (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0x04)
#define __crt_isupper(ch)  (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0x08)
#define __crt_isalpha(ch)  (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0x0c)
#define __crt_isdigit(ch)  (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0x10)
#define __crt_isxdigit(ch) (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0x30)
#define __crt_isalnum(ch)  (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0x1c)
#define __crt_ispunct(ch)  (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0x40)
#define __crt_isgraph(ch)  (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0x5c)
#define __crt_isprint(ch)  (__ctype_C_flags[(__UINT8_TYPE__)(ch)] & 0xdc)
#ifdef __NO_XBLOCK
#define __crt_isblank(ch) ((__UINT8_TYPE__)(ch) == 9 || (__UINT8_TYPE__)(ch) == 0x20)
#else /* __NO_XBLOCK */
#define __crt_isblank(ch) __XBLOCK({ __UINT8_TYPE__ __cib_ch = (__UINT8_TYPE__)(ch); __XRETURN (__cib_ch) == 9 || (__cib_ch) == 0x20; })
#endif /* !__NO_XBLOCK */

#ifdef __CRT_HAVE___ctype_C_tolower
#ifndef ____ctype_C_tolower_defined
#define ____ctype_C_tolower_defined
__DECL_BEGIN __LIBC char const __ctype_C_tolower[256] __CASMNAME_SAME("__ctype_C_tolower"); __DECL_END
#endif /* !____ctype_C_tolower_defined */
#define __crt_tolower(ch) __ctype_C_tolower[(__UINT8_TYPE__)(ch)]
#endif /* __CRT_HAVE___ctype_C_tolower */

#ifdef __CRT_HAVE___ctype_C_toupper
#ifndef ____ctype_C_toupper_defined
#define ____ctype_C_toupper_defined
__DECL_BEGIN __LIBC char const __ctype_C_toupper[256] __CASMNAME_SAME("__ctype_C_toupper"); __DECL_END
#endif /* !____ctype_C_toupper_defined */
#define __crt_toupper(ch) __ctype_C_toupper[(__UINT8_TYPE__)(ch)]
#endif /* __CRT_HAVE___ctype_C_toupper */
/************************************************************************/

#elif defined(__CRT_GLC) && defined(__CRT_HAVE___ctype_b_loc)
#include <bits/crt/locale.h>

/************************************************************************/
/* GLibC                                                                */
#ifndef ____ctype_b_loc_defined
#define ____ctype_b_loc_defined
__DECL_BEGIN
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__UINT16_TYPE__ const **,__NOTHROW,__ctype_b_loc,(void),())
__DECL_END
#endif /* !____ctype_b_loc_defined */

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __crt_isupper(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 0))
#define __crt_islower(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 1))
#define __crt_isalpha(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 2))
#define __crt_isdigit(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 3))
#define __crt_isxdigit(ch)           ((*__ctype_b_loc())[(int)(ch)] & (1 << 4))
#define __crt_isspace(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 5))
#define __crt_isprint(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 6))
#define __crt_isgraph(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 7))
#define __crt_iscntrl(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 9))
#define __crt_ispunct(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 10))
#define __crt_isalnum(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 11))
#define __crt_isblank(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 8))
#define __crt_isupper_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 0))
#define __crt_islower_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 1))
#define __crt_isalpha_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 2))
#define __crt_isdigit_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 3))
#define __crt_isxdigit_l(ch, locale) ((locale)->__ctype_b[(int)(ch)] & (1 << 4))
#define __crt_isspace_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 5))
#define __crt_isprint_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 6))
#define __crt_isgraph_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 7))
#define __crt_iscntrl_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 9))
#define __crt_ispunct_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 10))
#define __crt_isalnum_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 11))
#define __crt_isblank_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 8))
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define __crt_isupper(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 8))
#define __crt_islower(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 9))
#define __crt_isalpha(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 10))
#define __crt_isdigit(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 11))
#define __crt_isxdigit(ch)           ((*__ctype_b_loc())[(int)(ch)] & (1 << 12))
#define __crt_isspace(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 13))
#define __crt_isprint(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 14))
#define __crt_isgraph(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 15))
#define __crt_iscntrl(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 1))
#define __crt_ispunct(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 2))
#define __crt_isalnum(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 3))
#define __crt_isblank(ch)            ((*__ctype_b_loc())[(int)(ch)] & (1 << 0))
#define __crt_isupper_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 8))
#define __crt_islower_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 9))
#define __crt_isalpha_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 10))
#define __crt_isdigit_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 11))
#define __crt_isxdigit_l(ch, locale) ((locale)->__ctype_b[(int)(ch)] & (1 << 12))
#define __crt_isspace_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 13))
#define __crt_isprint_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 14))
#define __crt_isgraph_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 15))
#define __crt_iscntrl_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 1))
#define __crt_ispunct_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 2))
#define __crt_isalnum_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 3))
#define __crt_isblank_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 0))
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

#ifdef __CRT_HAVE___ctype_tolower_loc
#ifndef ____ctype_tolower_loc_defined
#define ____ctype_tolower_loc_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__INT32_TYPE__ const **,__NOTHROW,__ctype_tolower_loc,(void),())
#endif /* !____ctype_tolower_loc_defined */
#define __crt_tolower(ch) ((*__ctype_tolower_loc())[(int)(ch)])
#endif /* __CRT_HAVE___ctype_tolower_loc */

#ifdef __CRT_HAVE___ctype_toupper_loc
#ifndef ____ctype_toupper_loc_defined
#define ____ctype_toupper_loc_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__INT32_TYPE__ const **,__NOTHROW,__ctype_toupper_loc,(void),())
#endif /* !____ctype_toupper_loc_defined */
#define __crt_toupper(ch) ((*__ctype_toupper_loc())[(int)(ch)])
#endif /* __CRT_HAVE___ctype_toupper_loc */
/************************************************************************/

#elif defined(__CRT_CYG) && defined(__CRT_HAVE___locale_ctype_ptr)

/************************************************************************/
/* Cygwin                                                               */
#ifndef ____locale_ctype_ptr_defined
#define ____locale_ctype_ptr_defined
__DECL_BEGIN
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW,__locale_ctype_ptr,(void),())
__DECL_END
#endif /* !____locale_ctype_ptr_defined */
#define __crt_chtype_lookup(ch)           ((__locale_ctype_ptr() + 1)[(int)(ch)])
#define __crt_isalpha(ch)                 (__crt_chtype_lookup(ch) & 3)
#define __crt_isupper(ch)                 ((__crt_chtype_lookup(ch) & 3) == 1)
#define __crt_islower(ch)                 ((__crt_chtype_lookup(ch) & 3) == 2)
#define __crt_isdigit(ch)                 (__crt_chtype_lookup(ch) & 4)
#define __crt_isxdigit(ch)                (__crt_chtype_lookup(ch) & 014)
#define __crt_isspace(ch)                 (__crt_chtype_lookup(ch) & 010)
#define __crt_ispunct(ch)                 (__crt_chtype_lookup(ch) & 020)
#define __crt_isalnum(ch)                 (__crt_chtype_lookup(ch) & 7)
#define __crt_isprint(ch)                 (__crt_chtype_lookup(ch) & 0227)
#define __crt_isgraph(ch)                 (__crt_chtype_lookup(ch) & 027)
#define __crt_iscntrl(ch)                 (__crt_chtype_lookup(ch) & 040)
#ifdef __NO_XBLOCK
#define __crt_isblank(ch) ((__crt_chtype_lookup(ch) & 0200) || (ch) == '\t')
#else /* __NO_XBLOCK */
#define __crt_isblank(ch) __XBLOCK({ int __cib_ch = (ch); __XRETURN (__crt_chtype_lookup(__cib_ch) & 0200) || (__cib_ch) == '\t'; })
#endif /* !__NO_XBLOCK */

#ifdef __CRT_HAVE___locale_ctype_ptr_l
#ifndef ____locale_ctype_ptr_l_defined
#define ____locale_ctype_ptr_l_defined
__DECL_BEGIN
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__locale_ctype_ptr_l,(__locale_t __locale),(__locale))
__DECL_END
#endif /* !____locale_ctype_ptr_l_defined */
#define __crt_chtype_lookup_l(ch, locale) ((__locale_ctype_ptr_l(locale) + 1)[(int)(ch)])
#define __crt_isalpha_l(ch, locale)       (__crt_chtype_lookup_l(ch, locale) & 3)
#define __crt_isupper_l(ch, locale)       ((__crt_chtype_lookup_l(ch, locale) & 3) == 1)
#define __crt_islower_l(ch, locale)       ((__crt_chtype_lookup_l(ch, locale) & 3) == 2)
#define __crt_isdigit_l(ch, locale)       (__crt_chtype_lookup_l(ch, locale) & 4)
#define __crt_isxdigit_l(ch, locale)      (__crt_chtype_lookup_l(ch, locale) & 014)
#define __crt_isspace_l(ch, locale)       (__crt_chtype_lookup_l(ch, locale) & 010)
#define __crt_ispunct_l(ch, locale)       (__crt_chtype_lookup_l(ch, locale) & 020)
#define __crt_isalnum_l(ch, locale)       (__crt_chtype_lookup_l(ch, locale) & 7)
#define __crt_isprint_l(ch, locale)       (__crt_chtype_lookup_l(ch, locale) & 0227)
#define __crt_isgraph_l(ch, locale)       (__crt_chtype_lookup_l(ch, locale) & 027)
#define __crt_iscntrl_l(ch, locale)       (__crt_chtype_lookup_l(ch, locale) & 040)
#ifdef __NO_XBLOCK
#define __crt_isblank_l(ch, locale) ((__crt_chtype_lookup_l(ch, locale) & 0200) || (ch) == '\t')
#else /* __NO_XBLOCK */
#define __crt_isblank_l(ch, locale) __XBLOCK({ int __cib_ch = (ch); __XRETURN (__crt_chtype_lookup_l(__cib_ch, locale) & 0200) || (__cib_ch) == '\t'; })
#endif /* !__NO_XBLOCK */
#endif /* __CRT_HAVE___locale_ctype_ptr_l */
/************************************************************************/

#elif defined(__CRT_DOS) && defined(__CRT_HAVE__isctype)

/************************************************************************/
/* DOS (MSVC)                                                           */
#ifndef ___isctype_defined
#define ___isctype_defined
__DECL_BEGIN
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_isctype,(int __ch, int __mask),(__ch,__mask))
__DECL_END
#endif /* !___isctype_defined */
#define __crt_isalnum(ch)  _isctype(ch, 0x107)
#define __crt_isalpha(ch)  _isctype(ch, 0x103)
#define __crt_isupper(ch)  _isctype(ch, 0x001)
#define __crt_islower(ch)  _isctype(ch, 0x002)
#define __crt_isdigit(ch)  _isctype(ch, 0x004)
#define __crt_isxdigit(ch) _isctype(ch, 0x080)
#define __crt_isspace(ch)  _isctype(ch, 0x008)
#define __crt_ispunct(ch)  _isctype(ch, 0x010)
#define __crt_isprint(ch)  _isctype(ch, 0x157)
#define __crt_isgraph(ch)  _isctype(ch, 0x117)
#define __crt_iscntrl(ch)  _isctype(ch, 0x020)

#ifdef __CRT_HAVE__isctype_l
#ifndef ___isctype_l_defined
#define ___isctype_l_defined
__DECL_BEGIN
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isctype_l,(int __ch, int __mask, __locale_t __locale),(__ch,__mask,__locale))
__DECL_END
#endif /* !___isctype_l_defined */
#define __crt_isalnum_l(ch, locale)  _isctype_l(ch, 0x107, locale)
#define __crt_isalpha_l(ch, locale)  _isctype_l(ch, 0x103, locale)
#define __crt_isupper_l(ch, locale)  _isctype_l(ch, 0x001, locale)
#define __crt_islower_l(ch, locale)  _isctype_l(ch, 0x002, locale)
#define __crt_isdigit_l(ch, locale)  _isctype_l(ch, 0x004, locale)
#define __crt_isxdigit_l(ch, locale) _isctype_l(ch, 0x080, locale)
#define __crt_isspace_l(ch, locale)  _isctype_l(ch, 0x008, locale)
#define __crt_ispunct_l(ch, locale)  _isctype_l(ch, 0x010, locale)
#define __crt_isprint_l(ch, locale)  _isctype_l(ch, 0x157, locale)
#define __crt_isgraph_l(ch, locale)  _isctype_l(ch, 0x117, locale)
#define __crt_iscntrl_l(ch, locale)  _isctype_l(ch, 0x020, locale)
#endif /* __CRT_HAVE__isctype_l */
/************************************************************************/

#else /* ... */

/* Generic CRT or CRT doesn't provide ctype lookup matrix */

#endif /* !... */

/* Generic ASCII / "C"-locale CType macros. */
#define __ascii_iscntrl(ch)  ((__UINT8_TYPE__)(ch) <= 0x1f || (__UINT8_TYPE__)(ch) == 0x7f)
#define __ascii_isspace(ch)  (((__UINT8_TYPE__)(ch) >= 0x09 && (__UINT8_TYPE__)(ch) <= 0x0d) || (__UINT8_TYPE__)(ch) == 0x20)
#define __ascii_isupper(ch)  ((__UINT8_TYPE__)(ch) >= 0x41 && (__UINT8_TYPE__)(ch) <= 0x5a)
#define __ascii_islower(ch)  ((__UINT8_TYPE__)(ch) >= 0x61 && (__UINT8_TYPE__)(ch) <= 0x7a)
#define __ascii_isalpha(ch)  (__ascii_isupper(ch) || __ascii_islower(ch))
#define __ascii_isdigit(ch)  ((__UINT8_TYPE__)(ch) >= 0x30 && (__UINT8_TYPE__)(ch) <= 0x39)
#define __ascii_isxdigit(ch) (__ascii_isdigit(ch) || ((__UINT8_TYPE__)(ch) >= 0x41 && (__UINT8_TYPE__)(ch) <= 0x46) || ((__UINT8_TYPE__)(ch) >= 0x61 && (__UINT8_TYPE__)(ch) <= 0x66))
#define __ascii_isalnum(ch)  (__ascii_isupper(ch) || __ascii_islower(ch) || __ascii_isdigit(ch))
#define __ascii_ispunct(ch)  (((__UINT8_TYPE__)(ch) >= 0x21 && (__UINT8_TYPE__)(ch) <= 0x2f) || ((__UINT8_TYPE__)(ch) >= 0x3a && (__UINT8_TYPE__)(ch) <= 0x40) || ((__UINT8_TYPE__)(ch) >= 0x5b && (__UINT8_TYPE__)(ch) <= 0x60) || ((__UINT8_TYPE__)(ch) >= 0x7b && (__UINT8_TYPE__)(ch) <= 0x7e))
#define __ascii_isgraph(ch)  ((__UINT8_TYPE__)(ch) >= 0x21 && (__UINT8_TYPE__)(ch) <= 0x7e)
#define __ascii_isprint(ch)  ((__UINT8_TYPE__)(ch) >= 0x20 && (__UINT8_TYPE__)(ch) <= 0x7e)
#define __ascii_isblank(ch)  ((__UINT8_TYPE__)(ch) == 0x09 || (__UINT8_TYPE__)(ch) == 0x20)
#define __ascii__tolower(ch) ((ch) + 0x20)
#define __ascii__toupper(ch) ((ch) - 0x20)
#define __ascii_tolower(ch)  (__ascii_isupper(ch) ? __ascii__tolower(ch) : (ch))
#define __ascii_toupper(ch)  (__ascii_islower(ch) ? __ascii__toupper(ch) : (ch))

#endif /* __CC__ */

#endif /* !_BITS_CRT_CTYPE_H */
