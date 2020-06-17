/* HASH CRC-32:0xdaa2868b */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_UNICODE_C
#define GUARD_LIBC_AUTO_DOSABI_UNICODE_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../unicode.h"

DECL_BEGIN

/* Read a single Unicode character from a given UTF-8 string */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf8)(char const **__restrict ptext) {
	return libc_unicode_readutf8(ptext);
}
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf8_rev)(char const **__restrict ptext) {
	return libc_unicode_readutf8_rev(ptext);
}
/* Same as `unicode_readutf8()', but don't read past `text_end' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf8_n)(char const **__restrict ptext,
                                              char const *text_end) {
	return libc_unicode_readutf8_n(ptext, text_end);
}
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf8_rev_n)(char const **__restrict ptext,
                                                  char const *text_start) {
	return libc_unicode_readutf8_rev_n(ptext, text_start);
}
/* Read a single Unicode character from a given UTF-16 string */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf16)(char16_t const **__restrict ptext) {
	return libc_unicode_readutf16(ptext);
}
/* Same as `unicode_readutf16()', but don't read past `text_end' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_n)(char16_t const **__restrict ptext,
                                               char16_t const *text_end) {
	return libc_unicode_readutf16_n(ptext, text_end);
}
/* Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_swap)(char16_t const **__restrict ptext) {
	return libc_unicode_readutf16_swap(ptext);
}
/* Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_swap_n)(char16_t const **__restrict ptext,
                                                    char16_t const *text_end) {
	return libc_unicode_readutf16_swap_n(ptext, text_end);
}
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_rev)(char16_t const **__restrict ptext) {
	return libc_unicode_readutf16_rev(ptext);
}
/* Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_swap_rev)(char16_t const **__restrict ptext) {
	return libc_unicode_readutf16_swap_rev(ptext);
}
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_rev_n)(char16_t const **__restrict ptext,
                                                   char16_t const *text_start) {
	return libc_unicode_readutf16_rev_n(ptext, text_start);
}
/* Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_swap_rev_n)(char16_t const **__restrict ptext,
                                                        char16_t const *text_start) {
	return libc_unicode_readutf16_swap_rev_n(ptext, text_start);
}
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_unicode_writeutf8)(char *__restrict dst,
                                             char32_t ch) {
	return libc_unicode_writeutf8(dst, ch);
}
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF16_CURLEN' bytes to `dst' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_unicode_writeutf16)(char16_t *__restrict dst,
                                              char32_t ch) {
	return libc_unicode_writeutf16(dst, ch);
}
/* Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_unicode_writeutf16_chk)(char16_t *__restrict dst,
                                                  char32_t ch) {
	return libc_unicode_writeutf16_chk(dst, ch);
}
/* Convert a given utf-8 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_unicode_8to16)(char16_t *__restrict utf16_dst,
                                         char const *__restrict utf8_text,
                                         size_t utf8_characters) {
	return libc_unicode_8to16(utf16_dst, utf8_text, utf8_characters);
}
/* Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character.
 * @return: NULL: Attempted to write an invalid character */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") WUNUSED NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_unicode_8to16_chk)(char16_t *__restrict utf16_dst,
                                             char const *__restrict utf8_text,
                                             size_t utf8_characters) {
	return libc_unicode_8to16_chk(utf16_dst, utf8_text, utf8_characters);
}
/* Convert a given utf-8 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_characters)' dwords, or `*4' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBDCALL libd_unicode_8to32)(char32_t *__restrict utf32_dst,
                                         char const *__restrict utf8_text,
                                         size_t utf8_characters) {
	return libc_unicode_8to32(utf32_dst, utf8_text, utf8_characters);
}
/* Convert a given utf-16 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_unicode_16to8)(char *__restrict utf8_dst,
                                         char16_t const *__restrict utf16_text,
                                         size_t utf16_characters) {
	return libc_unicode_16to8(utf8_dst, utf16_text, utf16_characters);
}
/* Convert a given utf-16 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_characters)' dwords, or *4 bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBDCALL libd_unicode_16to32)(char32_t *__restrict utf32_dst,
                                          char16_t const *__restrict utf16_text,
                                          size_t utf16_characters) {
	return libc_unicode_16to32(utf32_dst, utf16_text, utf16_characters);
}
/* Convert a given utf-32 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_32TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_unicode_32to8)(char *__restrict utf8_dst,
                                         char32_t const *__restrict utf32_text,
                                         size_t utf32_characters) {
	return libc_unicode_32to8(utf8_dst, utf32_text, utf32_characters);
}
/* Convert a given utf-32 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_32TO16_MAXBUF(utf16_characters)' words, or *2 bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_unicode_32to16)(char16_t *__restrict utf16_dst,
                                          char32_t const *__restrict utf32_text,
                                          size_t utf32_characters) {
	return libc_unicode_32to16(utf16_dst, utf32_text, utf32_characters);
}
/* @return: *:          Success (*pc16 was filled; the return value is the number of bytes taken from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified, but nothing was read from `s'; in this case, a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1, 2, 4)) size_t
NOTHROW_NCX(LIBDCALL libd_unicode_c8toc16)(char16_t *__restrict pc16,
                                           char const *__restrict s,
                                           size_t n,
                                           __mbstate_t *__restrict mbs) {
	return libc_unicode_c8toc16(pc16, s, n, mbs);
}
/* @return: *:          Success (*pc32 was filled; the return value is the number of bytes taken from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") NONNULL((1, 2, 4)) size_t
NOTHROW_NCX(LIBDCALL libd_unicode_c8toc32)(char32_t *__restrict pc32,
                                           char const *__restrict s,
                                           size_t n,
                                           __mbstate_t *__restrict mbs) {
	return libc_unicode_c8toc32(pc32, s, n, mbs);
}
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-16 output */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") ssize_t
NOTHROW_NCX(LIBDCALL libd_format_8to16)(void *arg,
                                        char const *data,
                                        size_t datalen) {
	return libc_format_8to16(arg, data, datalen);
}
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-32 output */
INTERN ATTR_SECTION(".text.crt.dos.unicode.UTF") ssize_t
NOTHROW_NCX(LIBDCALL libd_format_8to32)(void *arg,
                                        char const *data,
                                        size_t datalen) {
	return libc_format_8to32(arg, data, datalen);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf8, libd_unicode_readutf8);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf8_rev, libd_unicode_readutf8_rev);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf8_n, libd_unicode_readutf8_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf8_rev_n, libd_unicode_readutf8_rev_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16, libd_unicode_readutf16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_n, libd_unicode_readutf16_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_swap, libd_unicode_readutf16_swap);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_swap_n, libd_unicode_readutf16_swap_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_rev, libd_unicode_readutf16_rev);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_swap_rev, libd_unicode_readutf16_swap_rev);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_rev_n, libd_unicode_readutf16_rev_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_swap_rev_n, libd_unicode_readutf16_swap_rev_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_writeutf8, libd_unicode_writeutf8);
DEFINE_PUBLIC_ALIAS(DOS$unicode_writeutf16, libd_unicode_writeutf16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_writeutf16_chk, libd_unicode_writeutf16_chk);
DEFINE_PUBLIC_ALIAS(DOS$unicode_8to16, libd_unicode_8to16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_8to16_chk, libd_unicode_8to16_chk);
DEFINE_PUBLIC_ALIAS(DOS$unicode_8to32, libd_unicode_8to32);
DEFINE_PUBLIC_ALIAS(DOS$unicode_16to8, libd_unicode_16to8);
DEFINE_PUBLIC_ALIAS(DOS$unicode_16to32, libd_unicode_16to32);
DEFINE_PUBLIC_ALIAS(DOS$unicode_32to8, libd_unicode_32to8);
DEFINE_PUBLIC_ALIAS(DOS$unicode_32to16, libd_unicode_32to16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_c8toc16, libd_unicode_c8toc16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_c8toc32, libd_unicode_c8toc32);
DEFINE_PUBLIC_ALIAS(DOS$format_8to16, libd_format_8to16);
DEFINE_PUBLIC_ALIAS(DOS$format_8to32, libd_format_8to32);

#endif /* !GUARD_LIBC_AUTO_DOSABI_UNICODE_C */
