/* HASH CRC-32:0xc84e66fa */
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
#ifndef GUARD_LIBC_AUTO_UNICODE_H
#define GUARD_LIBC_AUTO_UNICODE_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <unicode.h>

DECL_BEGIN

#ifndef __pformatprinter_defined
#define __pformatprinter_defined
typedef __pformatprinter pformatprinter;
#endif /* !__pformatprinter_defined */
#ifndef __pc16formatprinter_defined
#define __pc16formatprinter_defined
typedef __pc16formatprinter pc16formatprinter;
typedef __pc32formatprinter pc32formatprinter;
#endif /* !__pc16formatprinter_defined */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf8(3)
 * Read a single Unicode character from a given UTF-8 string */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf8)(char const **__restrict ptext);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf8(3)
 * Read a single Unicode character from a given UTF-8 string */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf8)(char const **__restrict ptext);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf8_rev(3)
 * Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf8_rev)(char const **__restrict ptext);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf8_rev(3)
 * Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf8_rev)(char const **__restrict ptext);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf8_n(3)
 * Same as `unicode_readutf8()', but don't read past `text_end' */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf8_n)(char const **__restrict ptext, char const *text_end);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf8_n(3)
 * Same as `unicode_readutf8()', but don't read past `text_end' */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf8_n)(char const **__restrict ptext, char const *text_end);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf8_rev_n(3)
 * Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf8_rev_n)(char const **__restrict ptext, char const *text_start);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf8_rev_n(3)
 * Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf8_rev_n)(char const **__restrict ptext, char const *text_start);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf16)(char16_t const **__restrict ptext);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16)(char16_t const **__restrict ptext);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf16_n(3)
 * Same as `unicode_readutf16()', but don't read past `text_end' */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_n)(char16_t const **__restrict ptext, char16_t const *text_end);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf16_n(3)
 * Same as `unicode_readutf16()', but don't read past `text_end' */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_n)(char16_t const **__restrict ptext, char16_t const *text_end);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf16_swap(3)
 * Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_swap)(char16_t const **__restrict ptext);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf16_swap(3)
 * Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap)(char16_t const **__restrict ptext);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf16_swap_n(3)
 * Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_swap_n)(char16_t const **__restrict ptext, char16_t const *text_end);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf16_swap_n(3)
 * Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap_n)(char16_t const **__restrict ptext, char16_t const *text_end);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf16_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_rev)(char16_t const **__restrict ptext);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf16_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_rev)(char16_t const **__restrict ptext);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf16_swap_rev(3)
 * Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_swap_rev)(char16_t const **__restrict ptext);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf16_swap_rev(3)
 * Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
INTDEF ATTR_ACCESS_RW(1) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap_rev)(char16_t const **__restrict ptext);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf16_rev_n(3)
 * Same as `unicode_readutf16_rev()', but don't read ahead of `text_start' */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_rev_n)(char16_t const **__restrict ptext, char16_t const *text_start);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf16_rev_n(3)
 * Same as `unicode_readutf16_rev()', but don't read ahead of `text_start' */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_rev_n)(char16_t const **__restrict ptext, char16_t const *text_start);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_readutf16_swap_rev_n(3)
 * Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBDCALL libd_unicode_readutf16_swap_rev_n)(char16_t const **__restrict ptext, char16_t const *text_start);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_readutf16_swap_rev_n(3)
 * Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
INTDEF ATTR_ACCESS_RW(1) NONNULL((2)) char32_t NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap_rev_n)(char16_t const **__restrict ptext, char16_t const *text_start);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_writeutf8(3)
 * Write  a given Unicode character `ch' to `dst'  and return a pointer to its end
 * location. This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_WR(1) char *NOTHROW_NCX(LIBDCALL libd_unicode_writeutf8)(char *__restrict dst, char32_t ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_writeutf8(3)
 * Write  a given Unicode character `ch' to `dst'  and return a pointer to its end
 * location. This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_WR(1) char *NOTHROW_NCX(LIBCCALL libc_unicode_writeutf8)(char *__restrict dst, char32_t ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_writeutf16(3)
 * Write a given Unicode character  `ch' to `dst' and return  a pointer to its  end
 * location. This function will write at most `UNICODE_UTF16_CURLEN' words to `dst' */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_WR(1) char16_t *NOTHROW_NCX(LIBDCALL libd_unicode_writeutf16)(char16_t *__restrict dst, char32_t ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_writeutf16(3)
 * Write a given Unicode character  `ch' to `dst' and return  a pointer to its  end
 * location. This function will write at most `UNICODE_UTF16_CURLEN' words to `dst' */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_WR(1) char16_t *NOTHROW_NCX(LIBCCALL libc_unicode_writeutf16)(char16_t *__restrict dst, char32_t ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_writeutf16_chk(3)
 * Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false */
INTDEF WUNUSED ATTR_ACCESS_WR(1) char16_t *NOTHROW_NCX(LIBDCALL libd_unicode_writeutf16_chk)(char16_t *__restrict dst, char32_t ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_writeutf16_chk(3)
 * Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false */
INTDEF WUNUSED ATTR_ACCESS_WR(1) char16_t *NOTHROW_NCX(LIBCCALL libc_unicode_writeutf16_chk)(char16_t *__restrict dst, char32_t ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_8to16(3)
 * Convert a given utf-8 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char16_t *NOTHROW_NCX(LIBDCALL libd_unicode_8to16)(char16_t *__restrict utf16_dst, char const *__restrict utf8_text, size_t utf8_characters);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_8to16(3)
 * Convert a given utf-8 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char16_t *NOTHROW_NCX(LIBCCALL libc_unicode_8to16)(char16_t *__restrict utf16_dst, char const *__restrict utf8_text, size_t utf8_characters);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_8to16_chk(3)
 * Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character.
 * @return: NULL: Attempted to write an invalid character */
INTDEF WUNUSED ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char16_t *NOTHROW_NCX(LIBDCALL libd_unicode_8to16_chk)(char16_t *__restrict utf16_dst, char const *__restrict utf8_text, size_t utf8_characters);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> unicode_8to16_chk(3)
 * Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character.
 * @return: NULL: Attempted to write an invalid character */
INTDEF WUNUSED ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char16_t *NOTHROW_NCX(LIBCCALL libc_unicode_8to16_chk)(char16_t *__restrict utf16_dst, char const *__restrict utf8_text, size_t utf8_characters);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_8to32(3)
 * Convert a given utf-8 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_characters)' dwords, or `*4' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char32_t *NOTHROW_NCX(LIBDCALL libd_unicode_8to32)(char32_t *__restrict utf32_dst, char const *__restrict utf8_text, size_t utf8_characters);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_8to32(3)
 * Convert a given utf-8 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_characters)' dwords, or `*4' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char32_t *NOTHROW_NCX(LIBCCALL libc_unicode_8to32)(char32_t *__restrict utf32_dst, char const *__restrict utf8_text, size_t utf8_characters);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_16to8(3)
 * Convert a given utf-16 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char *NOTHROW_NCX(LIBDCALL libd_unicode_16to8)(char *__restrict utf8_dst, char16_t const *__restrict utf16_text, size_t utf16_characters);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_16to8(3)
 * Convert a given utf-16 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char *NOTHROW_NCX(LIBCCALL libc_unicode_16to8)(char *__restrict utf8_dst, char16_t const *__restrict utf16_text, size_t utf16_characters);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_16to32(3)
 * Convert a given utf-16 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_characters)' dwords, or *4 bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char32_t *NOTHROW_NCX(LIBDCALL libd_unicode_16to32)(char32_t *__restrict utf32_dst, char16_t const *__restrict utf16_text, size_t utf16_characters);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_16to32(3)
 * Convert a given utf-16 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_characters)' dwords, or *4 bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char32_t *NOTHROW_NCX(LIBCCALL libc_unicode_16to32)(char32_t *__restrict utf32_dst, char16_t const *__restrict utf16_text, size_t utf16_characters);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_32to8(3)
 * Convert a given utf-32 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_32TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char *NOTHROW_NCX(LIBDCALL libd_unicode_32to8)(char *__restrict utf8_dst, char32_t const *__restrict utf32_text, size_t utf32_characters);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_32to8(3)
 * Convert a given utf-32 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_32TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char *NOTHROW_NCX(LIBCCALL libc_unicode_32to8)(char *__restrict utf8_dst, char32_t const *__restrict utf32_text, size_t utf32_characters);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_32to16(3)
 * Convert a given utf-32 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_32TO16_MAXBUF(utf16_characters)' words, or *2 bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char16_t *NOTHROW_NCX(LIBDCALL libd_unicode_32to16)(char16_t *__restrict utf16_dst, char32_t const *__restrict utf32_text, size_t utf32_characters);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> unicode_32to16(3)
 * Convert a given utf-32 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_32TO16_MAXBUF(utf16_characters)' words, or *2 bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_WR(1) char16_t *NOTHROW_NCX(LIBCCALL libc_unicode_32to16)(char16_t *__restrict utf16_dst, char32_t const *__restrict utf32_text, size_t utf32_characters);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_c8toc16(3)
 * @return: *:          Success (*pc16 was filled; the return value
 *                      is  the  number  of bytes  taken  from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified,
 *                      but nothing was read  from `s'; in this  case,
 *                      a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't
 *                      a valid unicode sequence)
 * @return: (size_t)-2: Success, but  no  character  was  generated
 *                      (`s...+=n', together with `mbs' doesn't for
 *                      a full  character, but  `mbs' was  updated) */
INTDEF ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_RW(4) ATTR_ACCESS_WR(1) size_t NOTHROW_NCX(LIBDCALL libd_unicode_c8toc16)(char16_t *__restrict pc16, char const *__restrict s, size_t n, mbstate_t *__restrict mbs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> unicode_c8toc16(3)
 * @return: *:          Success (*pc16 was filled; the return value
 *                      is  the  number  of bytes  taken  from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified,
 *                      but nothing was read  from `s'; in this  case,
 *                      a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't
 *                      a valid unicode sequence)
 * @return: (size_t)-2: Success, but  no  character  was  generated
 *                      (`s...+=n', together with `mbs' doesn't for
 *                      a full  character, but  `mbs' was  updated) */
INTDEF ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_RW(4) ATTR_ACCESS_WR(1) size_t NOTHROW_NCX(LIBCCALL libc_unicode_c8toc16)(char16_t *__restrict pc16, char const *__restrict s, size_t n, mbstate_t *__restrict mbs);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_c8toc32(3)
 * @return: *:          Success (*pc32 was filled; the return value
 *                      is  the  number  of bytes  taken  from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't
 *                      a valid unicode sequence)
 * @return: (size_t)-2: Success, but  no  character  was  generated
 *                      (`s...+=n', together with `mbs' doesn't for
 *                      a full  character, but  `mbs' was  updated) */
INTDEF ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_RW(4) ATTR_ACCESS_WR(1) size_t NOTHROW_NCX(LIBDCALL libd_unicode_c8toc32)(char32_t *__restrict pc32, char const *__restrict s, size_t n, mbstate_t *__restrict mbs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> unicode_c8toc32(3)
 * @return: *:          Success (*pc32 was filled; the return value
 *                      is  the  number  of bytes  taken  from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't
 *                      a valid unicode sequence)
 * @return: (size_t)-2: Success, but  no  character  was  generated
 *                      (`s...+=n', together with `mbs' doesn't for
 *                      a full  character, but  `mbs' was  updated) */
INTDEF ATTR_ACCESS_ROS(2, 3) ATTR_ACCESS_RW(4) ATTR_ACCESS_WR(1) size_t NOTHROW_NCX(LIBCCALL libc_unicode_c8toc32)(char32_t *__restrict pc32, char const *__restrict s, size_t n, mbstate_t *__restrict mbs);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unicode_c16toc8(3)
 * @return: 0 :         Success, but no characters were generated
 * @return: * :         Success  (this many bytes were written to
 *                      `*pc8'; max is `UNICODE_16TO8_MAXBUF(1)')
 * @return: (size_t)-1: Unicode error (the given input string
 *                      isn't  a   valid  unicode   sequence) */
INTDEF ATTR_ACCESS_RW(3) ATTR_ACCESS_WR(1) size_t NOTHROW_NCX(LIBDCALL libd_unicode_c16toc8)(char pc8[3], char16_t c16, mbstate_t *__restrict mbs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> unicode_c16toc8(3)
 * @return: 0 :         Success, but no characters were generated
 * @return: * :         Success  (this many bytes were written to
 *                      `*pc8'; max is `UNICODE_16TO8_MAXBUF(1)')
 * @return: (size_t)-1: Unicode error (the given input string
 *                      isn't  a   valid  unicode   sequence) */
INTDEF ATTR_ACCESS_RW(3) ATTR_ACCESS_WR(1) size_t NOTHROW_NCX(LIBCCALL libc_unicode_c16toc8)(char pc8[3], char16_t c16, mbstate_t *__restrict mbs);
/* >> format_8tow(3)
 * Format printer  (compatible  with  `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-16/32 output */
INTDEF ATTR_ACCESS_ROS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__FORMATPRINTER_CC libd_format_8tow)(void *arg, char const *data, size_t datalen);
/* >> format_8tow(3)
 * Format printer  (compatible  with  `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-16/32 output */
INTDEF ATTR_ACCESS_ROS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__FORMATPRINTER_CC libc_format_8tow)(void *arg, char const *data, size_t datalen);
/* >> format_wto8(3)
 * Format   printer   (compatible  with   `pc16formatprinter')  for
 * converting wide-character unicode input data into a UTF-8 output */
INTDEF ATTR_ACCESS_ROS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__C16FORMATPRINTER_CC libd_format_wto8)(void *arg, char16_t const *data, size_t datalen);
/* >> format_wto8(3)
 * Format   printer   (compatible  with   `pc16formatprinter')  for
 * converting wide-character unicode input data into a UTF-8 output */
INTDEF ATTR_ACCESS_ROS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__C32FORMATPRINTER_CC libc_format_wto8)(void *arg, char32_t const *data, size_t datalen);
/* >> format_wto32(3)
 * Format  printer   (compatible   with   `pc16formatprinter')   for
 * converting wide-character unicode input data into a UTF-32 output */
INTDEF ATTR_ACCESS_ROS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__C16FORMATPRINTER_CC libd_format_wto32)(void *arg, char16_t const *data, size_t datalen);
/* >> format_wto32(3)
 * Format  printer   (compatible   with   `pc16formatprinter')   for
 * converting wide-character unicode input data into a UTF-32 output */
INTDEF ATTR_ACCESS_ROS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__C32FORMATPRINTER_CC libc_format_wto32)(void *arg, char32_t const *data, size_t datalen);
/* >> format_wto16(3)
 * Format   printer   (compatible   with   `pwformatprinter')    for
 * converting wide-character unicode input data into a UTF-16 output */
INTDEF ATTR_ACCESS_ROS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__C16FORMATPRINTER_CC libd_format_wto16)(void *arg, char16_t const *data, size_t datalen);
/* >> format_wto16(3)
 * Format   printer   (compatible   with   `pwformatprinter')    for
 * converting wide-character unicode input data into a UTF-16 output */
INTDEF ATTR_ACCESS_ROS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__C32FORMATPRINTER_CC libc_format_wto16)(void *arg, char32_t const *data, size_t datalen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> __unicode_descriptor(3)
 * Return the internal descriptor for the given `ch'
 * This is the main accessor function for the unicode database, but
 * should not be called directly (unless you know what you're doing
 * and are aware that your code might break should this API ever be
 * changed)
 * Also note that this function never returns `NULL'! */
INTDEF ATTR_CONST ATTR_RETNONNULL struct __unitraits const *NOTHROW(LIBDCALL libd___unicode_descriptor)(char32_t ch);
/* >> __unicode_descriptor_digit(3), __unicode_descriptor_digit64(3)
 * Return the integer constant associated  with a given digit  index
 * Returns `0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(LIBDCALL libd___unicode_descriptor_digit)(uint8_t digit_idx);
/* >> __unicode_descriptor_digit(3), __unicode_descriptor_digit64(3)
 * Return the integer constant associated  with a given digit  index
 * Returns `0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
INTDEF ATTR_CONST WUNUSED uint64_t NOTHROW(LIBDCALL libd___unicode_descriptor_digit64)(uint8_t digit_idx);
/* >> __unicode_descriptor_digitd(3), __unicode_descriptor_digitld(3)
 * Return the floating-point constant associated with a given digit index
 * Returns `0.0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
INTDEF ATTR_CONST WUNUSED double NOTHROW(LIBDCALL libd___unicode_descriptor_digitd)(uint8_t digit_idx);
/* >> __unicode_descriptor_digitd(3), __unicode_descriptor_digitld(3)
 * Return the floating-point constant associated with a given digit index
 * Returns `0.0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
INTDEF ATTR_CONST WUNUSED __LONGDOUBLE NOTHROW(LIBDCALL libd___unicode_descriptor_digitld)(uint8_t digit_idx);
/* >> unicode_fold(3)
 * Fold the given unicode character `ch' */
INTDEF ATTR_RETNONNULL ATTR_ACCESS_WR(2) char32_t *NOTHROW_NCX(LIBDCALL libd_unicode_fold)(char32_t ch, char32_t buf[3]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UNICODE_H */
