/* HASH CRC-32:0xd91e88d9 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_UNICODE_H
#define GUARD_LIBC_AUTO_UNICODE_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <unicode.h>

DECL_BEGIN

/* Read a single Unicode character from a given UTF-8 string */
INTDEF NONNULL((1)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf8)(/*utf-8*/ char const **__restrict ptext);
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
INTDEF NONNULL((1)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf8_rev)(/*utf-8*/ char const **__restrict ptext);
/* Same as `unicode_readutf8()', but don't read past `text_end' */
INTDEF NONNULL((1, 2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf8_n)(/*utf-8*/ char const **__restrict ptext, char const *text_end);
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
INTDEF NONNULL((1, 2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf8_rev_n)(/*utf-8*/ char const **__restrict ptext, char const *text_start);
/* Read a single Unicode character from a given UTF-16 string */
INTDEF NONNULL((1)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16)(/*utf-16*/ char16_t const **__restrict ptext);
/* Same as `unicode_readutf16()', but don't read past `text_end' */
INTDEF NONNULL((1, 2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_n)(/*utf-16*/ char16_t const **__restrict ptext, char16_t const *text_end);
/* Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
INTDEF NONNULL((1)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap)(/*utf-16-swap*/ char16_t const **__restrict ptext);
/* Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
INTDEF NONNULL((1, 2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap_n)(/*utf-16-swap*/ char16_t const **__restrict ptext, char16_t const *text_end);
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
INTDEF NONNULL((1)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_rev)(/*utf-16*/ char16_t const **__restrict ptext);
/* Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
INTDEF NONNULL((1)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap_rev)(/*utf-16*/ char16_t const **__restrict ptext);
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
INTDEF NONNULL((1, 2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_rev_n)(/*utf-16*/ char16_t const **__restrict ptext, char16_t const *text_start);
/* Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
INTDEF NONNULL((1, 2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap_rev_n)(/*utf-16*/ char16_t const **__restrict ptext, char16_t const *text_start);
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_unicode_writeutf8)(/*utf-8*/ char *__restrict dst, char32_t ch);
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF16_CURLEN' bytes to `dst' */
INTDEF ATTR_RETNONNULL NONNULL((1)) char16_t *NOTHROW_NCX(LIBCCALL libc_unicode_writeutf16)(/*utf-16*/ char16_t *__restrict dst, char32_t ch);
/* Convert a given utf-8 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBCCALL libc_unicode_8to16)(/*utf-16*/ char16_t *__restrict utf16_dst, /*utf-8*/ char const *__restrict utf8_text, size_t utf8_characters);
/* Convert a given utf-8 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_characters)' dwords, or `*4' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_unicode_8to32)(/*utf-32*/ char32_t *__restrict utf32_dst, /*utf-8*/ char const *__restrict utf8_text, size_t utf8_characters);
/* Convert a given utf-16 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_unicode_16to8)(/*utf-8*/ char *__restrict utf8_dst, /*utf-16*/ char16_t const *__restrict utf16_text, size_t utf16_characters);
/* Convert a given utf-16 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_characters)' dwords, or *4 bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBCCALL libc_unicode_16to32)(/*utf-32*/ char32_t *__restrict utf32_dst, /*utf-16*/ char16_t const *__restrict utf16_text, size_t utf16_characters);
/* Convert a given utf-32 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_32TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_unicode_32to8)(/*utf-8*/ char *__restrict utf8_dst, /*utf-32*/ char32_t const *__restrict utf32_text, size_t utf32_characters);
/* Convert a given utf-32 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_32TO16_MAXBUF(utf16_characters)' words, or *2 bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBCCALL libc_unicode_32to16)(/*utf-16*/ char16_t *__restrict utf16_dst, /*utf-32*/ char32_t const *__restrict utf32_text, size_t utf32_characters);
#ifndef __KERNEL__
/* Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false */
INTDEF WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBCCALL libc_unicode_writeutf16_chk)(/*utf-16*/ char16_t *__restrict dst, char32_t ch);
/* Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character.
 * @return: NULL: Attempted to write an invalid character */
INTDEF WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBCCALL libc_unicode_8to16_chk)(/*utf-16*/ char16_t *__restrict utf16_dst, /*utf-8*/ char const *__restrict utf8_text, size_t utf8_characters);
/* @return: *:          Success (*pc16 was filled; the return value is the number of bytes taken from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified, but nothing was read from `s'; in this case, a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
INTDEF NONNULL((1, 2, 4)) size_t NOTHROW_NCX(LIBCCALL libc_unicode_c8toc16)(char16_t *__restrict pc16, /*utf-8*/ char const *__restrict s, size_t n, __mbstate_t *__restrict mbs);
/* @return: *:          Success (*pc32 was filled; the return value is the number of bytes taken from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
INTDEF NONNULL((1, 2, 4)) size_t NOTHROW_NCX(LIBCCALL libc_unicode_c8toc32)(char32_t *__restrict pc32, /*utf-8*/ char const *__restrict s, size_t n, __mbstate_t *__restrict mbs);
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-16 output */
INTDEF ssize_t NOTHROW_NCX(LIBCCALL libc_format_8to16)(/*struct format_8to16_data **/ void *arg, /*utf-8*/ char const *data, size_t datalen);
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-32 output */
INTDEF ssize_t NOTHROW_NCX(LIBCCALL libc_format_8to32)(/*struct format_8to32_data **/ void *arg, /*utf-8*/ char const *data, size_t datalen);
/* Format printer (compatible with `__pc16formatprinter') for
 * converting wide-character unicode input data into a UTF-8 output */
INTDEF ssize_t NOTHROW_NCX(LIBCCALL libc_format_wto8)(/*struct format_wto8_data **/ void *arg, char32_t const *data, size_t datalen);
/* Format printer (compatible with `__pc16formatprinter') for
 * converting wide-character unicode input data into a UTF-8 output */
INTDEF ssize_t NOTHROW_NCX(LIBDCALL libd_format_wto8)(/*struct format_wto8_data **/ void *arg, char16_t const *data, size_t datalen);
/* Format printer (compatible with `__pc16formatprinter') for
 * converting wide-character unicode input data into a UTF-32 output */
INTDEF ssize_t NOTHROW_NCX(LIBCCALL libc_format_wto32)(/*struct format_wto32_data **/ void *arg, char32_t const *data, size_t datalen);
/* Format printer (compatible with `__pc16formatprinter') for
 * converting wide-character unicode input data into a UTF-32 output */
INTDEF ssize_t NOTHROW_NCX(LIBDCALL libd_format_wto32)(/*struct format_wto32_data **/ void *arg, char16_t const *data, size_t datalen);
/* Format printer (compatible with `__pwformatprinter') for
 * converting wide-character unicode input data into a UTF-16 output */
INTDEF ssize_t NOTHROW_NCX(LIBCCALL libc_format_wto16)(/*struct format_wto16_data **/ void *arg, char32_t const *data, size_t datalen);
/* Format printer (compatible with `__pwformatprinter') for
 * converting wide-character unicode input data into a UTF-16 output */
INTDEF ssize_t NOTHROW_NCX(LIBDCALL libd_format_wto16)(/*struct format_wto16_data **/ void *arg, char16_t const *data, size_t datalen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UNICODE_H */
