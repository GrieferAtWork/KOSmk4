/* HASH CRC-32:0x8476be5f */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_MBSTRING_H
#define GUARD_LIBC_AUTO_MBSTRING_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <mbstring.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbbtombc)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbbtombc)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _mbbtype(3), _mbbtype_l(3)
 * Used for iterating through string bytes to determine byte types. (s.a. `_mbsbtype_l(3)')
 * @param: ch: Should actually be a `unsigned char'
 * @param: ctype: One of:
 *   - `_MBC_LEAD' -> returns:
 *     - if `_ismbbtrail_l(ch, locale)' -> `_MBC_TRAIL'
 *     - else -> `_MBC_ILLEGAL'
 *   - all other values -> returns:
 *     - if `_ismbblead_l(ch, locale)' -> `_MBC_LEAD'
 *     - if `_ismbbprint_l(ch, locale)' -> `_MBC_SINGLE'
 *     - else -> `_MBC_ILLEGAL' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__mbbtype)(unsigned char ch, int ctype);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _mbbtype(3), _mbbtype_l(3)
 * Used for iterating through string bytes to determine byte types. (s.a. `_mbsbtype_l(3)')
 * @param: ch: Should actually be a `unsigned char'
 * @param: ctype: One of:
 *   - `_MBC_LEAD' -> returns:
 *     - if `_ismbbtrail_l(ch, locale)' -> `_MBC_TRAIL'
 *     - else -> `_MBC_ILLEGAL'
 *   - all other values -> returns:
 *     - if `_ismbblead_l(ch, locale)' -> `_MBC_LEAD'
 *     - if `_ismbbprint_l(ch, locale)' -> `_MBC_SINGLE'
 *     - else -> `_MBC_ILLEGAL' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__mbbtype)(unsigned char ch, int ctype);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbctombb)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctombb)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _mbsbtype(3), _mbsbtype_l(3)
 * Returns the type (one of `_MBC_*' from `<mbctype.h>')
 * of the byte at `str[byte_index]'. If that byte is out
 * of bounds, return `_MBC_ILLEGAL' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd__mbsbtype)(unsigned char const *str, size_t byte_index);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _mbsbtype(3), _mbsbtype_l(3)
 * Returns the type (one of `_MBC_*' from `<mbctype.h>')
 * of the byte at `str[byte_index]'. If that byte is out
 * of bounds, return `_MBC_ILLEGAL' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc__mbsbtype)(unsigned char const *str, size_t byte_index);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbscat_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbscat_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbschr)(unsigned char const *__restrict haystack, unsigned int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbschr)(unsigned char const *__restrict haystack, unsigned int needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbscmp)(unsigned char const *lhs, unsigned char const *rhs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbscmp)(unsigned char const *lhs, unsigned char const *rhs);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbscoll)(unsigned char const *lhs, unsigned char const *rhs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbscoll)(unsigned char const *lhs, unsigned char const *rhs);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbscpy_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbscpy_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBDCALL libd__mbscspn)(unsigned char const *haystack, unsigned char const *reject);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBCCALL libc__mbscspn)(unsigned char const *haystack, unsigned char const *reject);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsdec)(unsigned char const *start, unsigned char const *pos);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsdec)(unsigned char const *start, unsigned char const *pos);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsicmp)(unsigned char const *lhs, unsigned char const *rhs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsicmp)(unsigned char const *lhs, unsigned char const *rhs);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsicoll)(unsigned char const *lhs, unsigned char const *rhs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsicoll)(unsigned char const *lhs, unsigned char const *rhs);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsinc)(unsigned char const *ptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsinc)(unsigned char const *ptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd__mbslen)(unsigned char const *str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc__mbslen)(unsigned char const *str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd__mbsnlen)(unsigned char const *str, size_t max_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbsnlen)(unsigned char const *str, size_t max_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbslwr_s)(unsigned char *buf, size_t true_bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbslwr_s)(unsigned char *buf, size_t true_bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbslwr)(unsigned char *buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbslwr)(unsigned char *buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsupr)(unsigned char *buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsupr)(unsigned char *buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) ATTR_INS(3, 4) errno_t NOTHROW_NCX(LIBDCALL libd__mbsnbcat_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) ATTR_INS(3, 4) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnbcat_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT(1) ATTR_INS(2, 3) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsnbcat)(unsigned char *buf, unsigned char const *src, size_t max_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT(1) ATTR_INS(2, 3) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnbcat)(unsigned char *buf, unsigned char const *src, size_t max_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__mbsnbcmp)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbcmp)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__mbsnbcoll)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbcoll)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returns byte-offset from `str' after skipping `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd__mbsnbcnt)(unsigned char const *str, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns byte-offset from `str' after skipping `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc__mbsnbcnt)(unsigned char const *str, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_OUTS(1, 4) errno_t NOTHROW_NCX(LIBDCALL libd__mbsnbcpy_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_OUTS(1, 4) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_OUTS(1, 3) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsnbcpy)(unsigned char *buf, unsigned char const *src, size_t bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_OUTS(1, 3) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnbcpy)(unsigned char *buf, unsigned char const *src, size_t bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__mbsnbicmp)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbicmp)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__mbsnbicoll)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbicoll)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 4) errno_t NOTHROW_NCX(LIBDCALL libd__mbsnbset_s)(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 4) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnbset_s)(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 3) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsnbset)(unsigned char *buf, unsigned int ch, size_t max_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 3) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnbset)(unsigned char *buf, unsigned int ch, size_t max_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsncat_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsncat_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsncat)(unsigned char *buf, unsigned char const *src, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsncat)(unsigned char *buf, unsigned char const *src, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returns # of characters in (up to) first `max_bytes' of `str'. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd__mbsnccnt)(unsigned char const *str, size_t max_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns # of characters in (up to) first `max_bytes' of `str'. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbsnccnt)(unsigned char const *str, size_t max_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsncmp)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsncmp)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsncoll)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsncoll)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsncpy_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsncpy_s)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* WARNING: This function writes up to `max_chars' characters
 *          (read  as: up to `2 * max_chars' bytes) to `buf'! */
INTDEF ATTR_IN(2) ATTR_OUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsncpy)(unsigned char *buf, unsigned char const *src, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* WARNING: This function writes up to `max_chars' characters
 *          (read  as: up to `2 * max_chars' bytes) to `buf'! */
INTDEF ATTR_IN(2) ATTR_OUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsncpy)(unsigned char *buf, unsigned char const *src, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned int NOTHROW_NCX(LIBDCALL libd__mbsnextc)(unsigned char const *str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned int NOTHROW_NCX(LIBCCALL libc__mbsnextc)(unsigned char const *str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsnicmp)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsnicmp)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsnicoll)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsnicoll)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returns pointer to `max_chars'th character of `str' (or strend() when `max_chars > _mbslen_l(str)') */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsninc)(unsigned char const *str, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns pointer to `max_chars'th character of `str' (or strend() when `max_chars > _mbslen_l(str)') */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsninc)(unsigned char const *str, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsnset_s)(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnset_s)(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsnset)(unsigned char *buf, unsigned int ch, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnset)(unsigned char *buf, unsigned int ch, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbspbrk)(unsigned char const *haystack, unsigned char const *accept);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbspbrk)(unsigned char const *haystack, unsigned char const *accept);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsrchr)(unsigned char const *haystack, unsigned int needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsrchr)(unsigned char const *haystack, unsigned int needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsrev)(unsigned char *buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsrev)(unsigned char *buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsset_s)(unsigned char *buf, size_t true_bufsize, unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsset_s)(unsigned char *buf, size_t true_bufsize, unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsset)(unsigned char *buf, unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsset)(unsigned char *buf, unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returs a byte-offset */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBDCALL libd__mbsspn)(unsigned char const *haystack, unsigned char const *accept);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returs a byte-offset */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBCCALL libc__mbsspn)(unsigned char const *haystack, unsigned char const *accept);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsspnp)(unsigned char const *haystack, unsigned char const *accept);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsspnp)(unsigned char const *haystack, unsigned char const *accept);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsstr)(unsigned char const *haystack, unsigned char const *needle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsstr)(unsigned char const *haystack, unsigned char const *needle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT_OPT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbstok)(unsigned char *str, unsigned char const *delim);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT_OPT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbstok)(unsigned char *str, unsigned char const *delim);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbstok_s)(unsigned char *str, unsigned char const *delim, unsigned char **__restrict save_ptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbstok_s)(unsigned char *str, unsigned char const *delim, unsigned char **__restrict save_ptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsupr_s)(unsigned char *buf, size_t true_bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsupr_s)(unsigned char *buf, size_t true_bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd__mbclen)(unsigned char const *str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc__mbclen)(unsigned char const *str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd__mbccpy)(unsigned char *dst, unsigned char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_OUT(1) void NOTHROW_NCX(LIBCCALL libc__mbccpy)(unsigned char *dst, unsigned char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(4) ATTR_OUTS(1, 2) ATTR_OUT_OPT(3) errno_t NOTHROW_NCX(LIBDCALL libd__mbccpy_s)(unsigned char *dst, size_t true_dstsize, int *p_copied, unsigned char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(4) ATTR_OUTS(1, 2) ATTR_OUT_OPT(3) errno_t NOTHROW_NCX(LIBCCALL libc__mbccpy_s)(unsigned char *dst, size_t true_dstsize, int *p_copied, unsigned char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcalnum)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcalnum)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcalpha)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcalpha)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcdigit)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcdigit)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcgraph)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcgraph)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbclegal)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbclegal)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbclower)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbclower)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcprint)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcprint)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcpunct)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcpunct)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcblank)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcblank)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcspace)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcspace)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcupper)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcupper)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbctolower)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctolower)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbctoupper)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctoupper)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbchira)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbchira)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbckata)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbckata)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcsymbol)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcsymbol)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcl0)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl0)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcl1)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl1)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcl2)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl2)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbcjistojms)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbcjistojms)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbcjmstojis)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbcjmstojis)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbctohira)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctohira)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbctokata)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctokata)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__ismbslead)(unsigned char const *str, unsigned char const *pos);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__ismbslead)(unsigned char const *str, unsigned char const *pos);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__ismbstrail)(unsigned char const *str, unsigned char const *pos);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__ismbstrail)(unsigned char const *str, unsigned char const *pos);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbscat_l)(unsigned char *__restrict dst, unsigned char const *__restrict src, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbscat_l)(unsigned char *__restrict dst, unsigned char const *__restrict src, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbscpy_l)(unsigned char *__restrict dst, unsigned char const *__restrict src, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbscpy_l)(unsigned char *__restrict dst, unsigned char const *__restrict src, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd__mbccpy_l)(unsigned char *dst, unsigned char const *src, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_OUT(1) void NOTHROW_NCX(LIBCCALL libc__mbccpy_l)(unsigned char *dst, unsigned char const *src, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* WARNING: This function writes up to `max_chars' characters
 *          (read  as: up to `2 * max_chars' bytes) to `buf'! */
INTDEF ATTR_IN(2) ATTR_OUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsncpy_l)(unsigned char *buf, unsigned char const *src, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* WARNING: This function writes up to `max_chars' characters
 *          (read  as: up to `2 * max_chars' bytes) to `buf'! */
INTDEF ATTR_IN(2) ATTR_OUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsncpy_l)(unsigned char *buf, unsigned char const *src, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_OUTS(1, 3) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsnbcpy_l)(unsigned char *buf, unsigned char const *src, size_t bufsize, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_OUTS(1, 3) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_l)(unsigned char *buf, unsigned char const *src, size_t bufsize, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbschr_l)(unsigned char const *__restrict haystack, unsigned int needle, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbschr_l)(unsigned char const *__restrict haystack, unsigned int needle, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbscoll_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbscoll_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsicoll_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsicoll_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsncoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsncoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsnicoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsnicoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__mbsnbcoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbcoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__mbsnbicoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbicoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbslwr_l)(unsigned char *buf, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbslwr_l)(unsigned char *buf, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsupr_l)(unsigned char *buf, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsupr_l)(unsigned char *buf, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsinc_l)(unsigned char const *ptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsinc_l)(unsigned char const *ptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returns pointer to `max_chars'th character of `str' (or strend() when `max_chars > _mbslen_l(str)') */
INTDEF ATTR_PURE WUNUSED unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsninc_l)(unsigned char const *str, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns pointer to `max_chars'th character of `str' (or strend() when `max_chars > _mbslen_l(str)') */
INTDEF ATTR_PURE WUNUSED unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsninc_l)(unsigned char const *str, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsdec_l)(unsigned char const *start, unsigned char const *pos, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsdec_l)(unsigned char const *start, unsigned char const *pos, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBDCALL libd__mbscspn_l)(unsigned char const *haystack, unsigned char const *reject, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBCCALL libc__mbscspn_l)(unsigned char const *haystack, unsigned char const *reject, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd__mbslen_l)(unsigned char const *str, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc__mbslen_l)(unsigned char const *str, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd__mbsnlen_l)(unsigned char const *str, size_t max_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbsnlen_l)(unsigned char const *str, size_t max_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsncat_l)(unsigned char *buf, unsigned char const *src, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsncat_l)(unsigned char *buf, unsigned char const *src, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUT(1) ATTR_INS(2, 3) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsnbcat_l)(unsigned char *buf, unsigned char const *src, size_t max_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT(1) ATTR_INS(2, 3) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnbcat_l)(unsigned char *buf, unsigned char const *src, size_t max_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returns # of characters in (up to) first `max_bytes' of `str'. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd__mbsnccnt_l)(unsigned char const *str, size_t max_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns # of characters in (up to) first `max_bytes' of `str'. */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbsnccnt_l)(unsigned char const *str, size_t max_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returns byte-offset from `str' after skipping `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd__mbsnbcnt_l)(unsigned char const *str, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns byte-offset from `str' after skipping `max_chars' characters. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc__mbsnbcnt_l)(unsigned char const *str, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbscmp_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbscmp_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsicmp_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsicmp_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsncmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsncmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__mbsnicmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__mbsnicmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__mbsnbcmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbcmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__mbsnbicmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbicmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned int NOTHROW_NCX(LIBDCALL libd__mbsnextc_l)(unsigned char const *str, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned int NOTHROW_NCX(LIBCCALL libc__mbsnextc_l)(unsigned char const *str, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbspbrk_l)(unsigned char const *haystack, unsigned char const *accept, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbspbrk_l)(unsigned char const *haystack, unsigned char const *accept, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsrchr_l)(unsigned char const *haystack, unsigned int needle, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsrchr_l)(unsigned char const *haystack, unsigned int needle, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsrev_l)(unsigned char *buf, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsrev_l)(unsigned char *buf, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsset_l)(unsigned char *buf, unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_IN(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsset_l)(unsigned char *buf, unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsnset_l)(unsigned char *buf, unsigned int ch, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnset_l)(unsigned char *buf, unsigned int ch, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 3) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsnbset_l)(unsigned char *buf, unsigned int ch, size_t max_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 3) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnbset_l)(unsigned char *buf, unsigned int ch, size_t max_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returs a byte-offset */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBDCALL libd__mbsspn_l)(unsigned char const *haystack, unsigned char const *accept, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returs a byte-offset */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t NOTHROW_NCX(LIBCCALL libc__mbsspn_l)(unsigned char const *haystack, unsigned char const *accept, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsspnp_l)(unsigned char const *haystack, unsigned char const *accept, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsspnp_l)(unsigned char const *haystack, unsigned char const *accept, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbsstr_l)(unsigned char const *haystack, unsigned char const *needle, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsstr_l)(unsigned char const *haystack, unsigned char const *needle, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT_OPT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbstok_l)(unsigned char *str, unsigned char const *delim, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT_OPT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbstok_l)(unsigned char *str, unsigned char const *delim, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) unsigned char *NOTHROW_NCX(LIBDCALL libd__mbstok_s_l)(unsigned char *str, unsigned char const *delim, unsigned char **__restrict save_ptr, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbstok_s_l)(unsigned char *str, unsigned char const *delim, unsigned char **__restrict save_ptr, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd__mbclen_l)(unsigned char const *str, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBCCALL libc__mbclen_l)(unsigned char const *str, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbscat_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbscat_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbscpy_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbscpy_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbslwr_s_l)(unsigned char *buf, size_t true_bufsize, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbslwr_s_l)(unsigned char *buf, size_t true_bufsize, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsupr_s_l)(unsigned char *buf, size_t true_bufsize, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsupr_s_l)(unsigned char *buf, size_t true_bufsize, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) ATTR_INS(3, 4) errno_t NOTHROW_NCX(LIBDCALL libd__mbsnbcat_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) ATTR_INS(3, 4) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnbcat_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_OUTS(1, 4) errno_t NOTHROW_NCX(LIBDCALL libd__mbsnbcpy_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t bufsize, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_OUTS(1, 4) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t bufsize, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsnbset_s_l)(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_bytes, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnbset_s_l)(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_bytes, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsncat_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsncat_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsncpy_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsncpy_s_l)(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsnset_s_l)(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_chars, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnset_s_l)(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_chars, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbsset_s_l)(unsigned char *buf, size_t true_bufsize, unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbsset_s_l)(unsigned char *buf, size_t true_bufsize, unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(4) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mbccpy_s_l)(unsigned char *dst, size_t true_dstsize, int *p_copied, unsigned char const *src, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(4) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mbccpy_s_l)(unsigned char *dst, size_t true_dstsize, int *p_copied, unsigned char const *src, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__ismbslead_l)(unsigned char const *str, unsigned char const *pos, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__ismbslead_l)(unsigned char const *str, unsigned char const *pos, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd__ismbstrail_l)(unsigned char const *str, unsigned char const *pos, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc__ismbstrail_l)(unsigned char const *str, unsigned char const *pos, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _mbbtype(3), _mbbtype_l(3)
 * Used for iterating through string bytes to determine byte types. (s.a. `_mbsbtype_l(3)')
 * @param: ch: Should actually be a `unsigned char'
 * @param: ctype: One of:
 *   - `_MBC_LEAD' -> returns:
 *     - if `_ismbbtrail_l(ch, locale)' -> `_MBC_TRAIL'
 *     - else -> `_MBC_ILLEGAL'
 *   - all other values -> returns:
 *     - if `_ismbblead_l(ch, locale)' -> `_MBC_LEAD'
 *     - if `_ismbbprint_l(ch, locale)' -> `_MBC_SINGLE'
 *     - else -> `_MBC_ILLEGAL' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__mbbtype_l)(unsigned char ch, int ctype, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _mbbtype(3), _mbbtype_l(3)
 * Used for iterating through string bytes to determine byte types. (s.a. `_mbsbtype_l(3)')
 * @param: ch: Should actually be a `unsigned char'
 * @param: ctype: One of:
 *   - `_MBC_LEAD' -> returns:
 *     - if `_ismbbtrail_l(ch, locale)' -> `_MBC_TRAIL'
 *     - else -> `_MBC_ILLEGAL'
 *   - all other values -> returns:
 *     - if `_ismbblead_l(ch, locale)' -> `_MBC_LEAD'
 *     - if `_ismbbprint_l(ch, locale)' -> `_MBC_SINGLE'
 *     - else -> `_MBC_ILLEGAL' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__mbbtype_l)(unsigned char ch, int ctype, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _mbsbtype(3), _mbsbtype_l(3)
 * Returns the type (one of `_MBC_*' from `<mbctype.h>')
 * of the byte at `str[byte_index]'. If that byte is out
 * of bounds, return `_MBC_ILLEGAL' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd__mbsbtype_l)(unsigned char const *str, size_t byte_index, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _mbsbtype(3), _mbsbtype_l(3)
 * Returns the type (one of `_MBC_*' from `<mbctype.h>')
 * of the byte at `str[byte_index]'. If that byte is out
 * of bounds, return `_MBC_ILLEGAL' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc__mbsbtype_l)(unsigned char const *str, size_t byte_index, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbclegal_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbclegal_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbctolower_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctolower_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbctoupper_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctoupper_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcalnum_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcalnum_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcalpha_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcalpha_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcdigit_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcdigit_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcgraph_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcgraph_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbclower_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbclower_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcupper_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcupper_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcprint_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcprint_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcpunct_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcpunct_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcblank_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcblank_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcspace_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcspace_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbchira_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbchira_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbckata_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbckata_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcsymbol_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcsymbol_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcl0_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl0_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcl1_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl1_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbcl2_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl2_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbcjistojms_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbcjistojms_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbcjmstojis_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbcjmstojis_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbctohira_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctohira_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbctokata_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctokata_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbbtombc_l)(unsigned int ch, locale_t locale);
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__mbctombb_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MBSTRING_H */
