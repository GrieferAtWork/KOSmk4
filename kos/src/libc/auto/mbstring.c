/* HASH CRC-32:0xf7ac1033 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_MBSTRING_C
#define GUARD_LIBC_AUTO_MBSTRING_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/mbstring.h"
#include "../user/ctype.h"
#include "../user/mbctype.h"
#include "string.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbbtombc)(unsigned int ch) {
	return libc__mbbtombc_l(ch, NULL);
}
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
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__mbbtype)(unsigned char ch,
                                    int ctype) {
	return libc__mbbtype_l(ch, ctype, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctombb)(unsigned int ch) {
	return libc__mbctombb_l(ch, NULL);
}
/* >> _mbsbtype(3), _mbsbtype_l(3)
 * Returns the type (one of `_MBC_*' from `<mbctype.h>')
 * of the byte at `str[byte_index]'. If that byte is out
 * of bounds, return `_MBC_ILLEGAL' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc__mbsbtype)(unsigned char const *str,
                                     size_t byte_index) {
	return libc__mbsbtype_l(str, byte_index, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscat_s)(unsigned char *buf,
                                     size_t true_bufsize,
                                     unsigned char const *src) {
	return libc__mbscat_s_l(buf, true_bufsize, src, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbschr)(unsigned char const *__restrict haystack,
                                   unsigned int needle) {
	return libc__mbschr_l(haystack, needle, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbscmp)(unsigned char const *lhs,
                                   unsigned char const *rhs) {
	return libc__mbscmp_l(lhs, rhs, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbscoll)(unsigned char const *lhs,
                                    unsigned char const *rhs) {
	return libc__mbscoll_l(lhs, rhs, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscpy_s)(unsigned char *buf,
                                     size_t true_bufsize,
                                     unsigned char const *src) {
	return libc__mbscpy_s_l(buf, true_bufsize, src, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBCCALL libc__mbscspn)(unsigned char const *haystack,
                                    unsigned char const *reject) {
	return libc__mbscspn_l(haystack, reject, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsdec)(unsigned char const *start,
                                   unsigned char const *pos) {
	return libc__mbsdec_l(start, pos, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsicmp)(unsigned char const *lhs,
                                    unsigned char const *rhs) {
	return libc__mbsicmp_l(lhs, rhs, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsicoll)(unsigned char const *lhs,
                                     unsigned char const *rhs) {
	return libc__mbsicoll_l(lhs, rhs, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsinc)(unsigned char const *ptr) {
	return libc__mbsinc_l(ptr, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc__mbslen)(unsigned char const *str) {
	return libc__mbslen_l(str, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnlen)(unsigned char const *str,
                                    size_t max_bytes) {
	return libc__mbsnlen_l(str, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbslwr_s)(unsigned char *buf,
                                     size_t true_bufsize) {
	return libc__mbslwr_s_l(buf, true_bufsize, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbslwr)(unsigned char *buf) {
	return libc__mbslwr_l(buf, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsupr)(unsigned char *buf) {
	return libc__mbsupr_l(buf, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) ATTR_INS(3, 4) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcat_s)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned char const *src,
                                       size_t max_bytes) {
	return libc__mbsnbcat_s_l(buf, true_bufsize, src, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUT(1) ATTR_INS(2, 3) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbcat)(unsigned char *buf,
                                     unsigned char const *src,
                                     size_t max_bytes) {
	return libc__mbsnbcat_l(buf, src, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcmp)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     size_t max_bytes) {
	return libc__mbsnbcmp_l(lhs, rhs, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcoll)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t max_bytes) {
	return libc__mbsnbcoll_l(lhs, rhs, max_bytes, NULL);
}
/* Returns byte-offset from `str' after skipping `max_chars' characters. */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcnt)(unsigned char const *str,
                                     size_t max_chars) {
	return libc__mbsnbcnt_l(str, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(3) ATTR_OUTS(1, 4) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_s)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned char const *src,
                                       size_t bufsize) {
	return libc__mbsnbcpy_s_l(buf, true_bufsize, src, bufsize, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(2) ATTR_OUTS(1, 3) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbcpy)(unsigned char *buf,
                                     unsigned char const *src,
                                     size_t bufsize) {
	return libc__mbsnbcpy_l(buf, src, bufsize, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicmp)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t max_bytes) {
	return libc__mbsnbicmp_l(lhs, rhs, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicoll)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       size_t max_bytes) {
	return libc__mbsnbicoll_l(lhs, rhs, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 4) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbset_s)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned int ch,
                                       size_t max_bytes) {
	return libc__mbsnbset_s_l(buf, true_bufsize, ch, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 3) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbset)(unsigned char *buf,
                                     unsigned int ch,
                                     size_t max_bytes) {
	return libc__mbsnbset_l(buf, ch, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncat_s)(unsigned char *buf,
                                      size_t true_bufsize,
                                      unsigned char const *src,
                                      size_t max_chars) {
	return libc__mbsncat_s_l(buf, true_bufsize, src, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(2) ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsncat)(unsigned char *buf,
                                    unsigned char const *src,
                                    size_t max_chars) {
	return libc__mbsncat_l(buf, src, max_chars, NULL);
}
/* Returns # of characters in (up to) first `max_bytes' of `str'. */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnccnt)(unsigned char const *str,
                                     size_t max_bytes) {
	return libc__mbsnccnt_l(str, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsncmp)(unsigned char const *lhs,
                                    unsigned char const *rhs,
                                    size_t max_chars) {
	return libc__mbsncmp_l(lhs, rhs, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsncoll)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     size_t max_chars) {
	return libc__mbsncoll_l(lhs, rhs, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncpy_s)(unsigned char *buf,
                                      size_t true_bufsize,
                                      unsigned char const *src,
                                      size_t max_chars) {
	return libc__mbsncpy_s_l(buf, true_bufsize, src, max_chars, NULL);
}
/* WARNING: This function writes up to `max_chars' characters
 *          (read  as: up to `2 * max_chars' bytes) to `buf'! */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(2) ATTR_OUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsncpy)(unsigned char *buf,
                                    unsigned char const *src,
                                    size_t max_chars) {
	return libc__mbsncpy_l(buf, src, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) unsigned int
NOTHROW_NCX(LIBCCALL libc__mbsnextc)(unsigned char const *str) {
	return libc__mbsnextc_l(str, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsnicmp)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     size_t max_chars) {
	return libc__mbsnicmp_l(lhs, rhs, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsnicoll)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t max_chars) {
	return libc__mbsnicoll_l(lhs, rhs, max_chars, NULL);
}
/* Returns pointer to `max_chars'th character of `str' (or strend() when `max_chars > _mbslen_l(str)') */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsninc)(unsigned char const *str,
                                    size_t max_chars) {
	return libc__mbsninc_l(str, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnset_s)(unsigned char *buf,
                                      size_t true_bufsize,
                                      unsigned int ch,
                                      size_t max_chars) {
	return libc__mbsnset_s_l(buf, true_bufsize, ch, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnset)(unsigned char *buf,
                                    unsigned int ch,
                                    size_t max_chars) {
	return libc__mbsnset_l(buf, ch, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbspbrk)(unsigned char const *haystack,
                                    unsigned char const *accept) {
	return libc__mbspbrk_l(haystack, accept, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsrchr)(unsigned char const *haystack,
                                    unsigned int needle) {
	return libc__mbsrchr_l(haystack, needle, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsrev)(unsigned char *buf) {
	return libc__mbsrev_l(buf, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsset_s)(unsigned char *buf,
                                     size_t true_bufsize,
                                     unsigned int ch) {
	return libc__mbsset_s_l(buf, true_bufsize, ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsset)(unsigned char *buf,
                                   unsigned int ch) {
	return libc__mbsset_l(buf, ch, NULL);
}
/* Returs a byte-offset */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBCCALL libc__mbsspn)(unsigned char const *haystack,
                                   unsigned char const *accept) {
	return libc__mbsspn_l(haystack, accept, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsspnp)(unsigned char const *haystack,
                                    unsigned char const *accept) {
	return libc__mbsspnp_l(haystack, accept, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsstr)(unsigned char const *haystack,
                                   unsigned char const *needle) {
	return libc__mbsstr_l(haystack, needle, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") WUNUSED ATTR_IN(2) ATTR_INOUT_OPT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbstok)(unsigned char *str,
                                   unsigned char const *delim) {
	return libc__mbstok_l(str, delim, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") WUNUSED ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbstok_s)(unsigned char *str,
                                     unsigned char const *delim,
                                     unsigned char **__restrict save_ptr) {
	return libc__mbstok_s_l(str, delim, save_ptr, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsupr_s)(unsigned char *buf,
                                     size_t true_bufsize) {
	return libc__mbsupr_s_l(buf, true_bufsize, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc__mbclen)(unsigned char const *str) {
	return libc__mbclen_l(str, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(2) ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc__mbccpy)(unsigned char *dst,
                                   unsigned char const *src) {
	libc__mbccpy_l(dst, src, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(4) ATTR_OUTS(1, 2) ATTR_OUT_OPT(3) errno_t
NOTHROW_NCX(LIBCCALL libc__mbccpy_s)(unsigned char *dst,
                                     size_t true_dstsize,
                                     int *p_copied,
                                     unsigned char const *src) {
	return libc__mbccpy_s_l(dst, true_dstsize, p_copied, src, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcalnum)(unsigned int ch) {
	return libc__ismbcalnum_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcalpha)(unsigned int ch) {
	return libc__ismbcalpha_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcdigit)(unsigned int ch) {
	return libc__ismbcdigit_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcgraph)(unsigned int ch) {
	return libc__ismbcgraph_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbclegal)(unsigned int ch) {
	return libc__ismbclegal_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbclower)(unsigned int ch) {
	return libc__ismbclower_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcprint)(unsigned int ch) {
	return libc__ismbcprint_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcpunct)(unsigned int ch) {
	return libc__ismbcpunct_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcblank)(unsigned int ch) {
	return libc__ismbcblank_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcspace)(unsigned int ch) {
	return libc__ismbcspace_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcupper)(unsigned int ch) {
	return libc__ismbcupper_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctolower)(unsigned int ch) {
	return libc__mbctolower_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctoupper)(unsigned int ch) {
	return libc__mbctoupper_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbchira)(unsigned int ch) {
	return libc__ismbchira_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbckata)(unsigned int ch) {
	return libc__ismbckata_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcsymbol)(unsigned int ch) {
	return libc__ismbcsymbol_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl0)(unsigned int ch) {
	return libc__ismbcl0_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl1)(unsigned int ch) {
	return libc__ismbcl1_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl2)(unsigned int ch) {
	return libc__ismbcl2_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbcjistojms)(unsigned int ch) {
	return libc__mbcjistojms_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbcjmstojis)(unsigned int ch) {
	return libc__mbcjmstojis_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctohira)(unsigned int ch) {
	return libc__mbctohira_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctokata)(unsigned int ch) {
	return libc__mbctokata_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__ismbslead)(unsigned char const *str,
                                      unsigned char const *pos) {
	return libc__ismbslead_l(str, pos, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__ismbstrail)(unsigned char const *str,
                                       unsigned char const *pos) {
	return libc__ismbstrail_l(str, pos, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbscat_l)(unsigned char *__restrict dst,
                                     unsigned char const *__restrict src,
                                     locale_t locale) {
	(void)locale;
	return (unsigned char *)libc_strcat((char *)dst, (char const *)src);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbscpy_l)(unsigned char *__restrict dst,
                                     unsigned char const *__restrict src,
                                     locale_t locale) {
	(void)locale;
	return (unsigned char *)libc_strcpy((char *)dst, (char const *)src);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(2) ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc__mbccpy_l)(unsigned char *dst,
                                     unsigned char const *src,
                                     locale_t locale) {
	unsigned char ch;
	*dst = ch = *src;
	if (libc__ismbblead_l(ch, locale))
		dst[1] = src[1];
}
/* WARNING: This function writes up to `max_chars' characters
 *          (read  as: up to `2 * max_chars' bytes) to `buf'! */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(2) ATTR_OUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsncpy_l)(unsigned char *buf,
                                      unsigned char const *src,
                                      size_t max_chars,
                                      locale_t locale) {
	unsigned char *dst = buf;
	for (; max_chars; --max_chars) {
		unsigned char ch;
		*dst++ = ch = *src++;
		if (!ch)
			break;
		if (libc__ismbblead_l(ch, locale)) {
			*dst++ = ch = *src++;
			if unlikely(!ch) {
				dst[-2] = '\0'; /* "fix" incomplete 2-byte character. */
				break;
			}
		}
	}

	/* Really weird  quirk: until  this point,  `max_chars' were  counted
	 * in chars, but this zero-padding (which is also done by DOS), would
	 * mean that it's suddenly counted in bytes... */
	libc_bzero(dst, max_chars);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(2) ATTR_OUTS(1, 3) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_l)(unsigned char *buf,
                                       unsigned char const *src,
                                       size_t bufsize,
                                       locale_t locale) {
	unsigned char *dst = buf;
	while (bufsize) {
		unsigned char ch;
		--bufsize;
		*dst++ = ch = *src++;
		if (!ch)
			break;
		if (libc__ismbblead_l(ch, locale)) {
			if unlikely(!bufsize) {
				dst[-1] = '\0';
				break;
			}
			--bufsize;
			*dst++ = ch = *src++;
			if unlikely(!ch) {
				dst[-2] = '\0'; /* "fix" incomplete 2-byte character. */
				break;
			}
		}
	}
	libc_bzero(dst, bufsize);
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbschr_l)(unsigned char const *__restrict haystack,
                                     unsigned int needle,
                                     locale_t locale) {
	for (;;) {
		unsigned char const *temp;
		uint16_t hay;
		temp = haystack;
		hay  = *haystack++;
		if (libc__ismbblead_l(hay, locale))
			hay = *haystack ? (hay << 8) | *haystack++ : 0;
		if (hay == 0)
			break;
		if (hay == (uint16_t)(unsigned int)needle)
			return (unsigned char *)temp;
	}
	return NULL;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbscoll_l)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbscmp_l(lhs, rhs, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsicoll_l)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbscmp_l(lhs, rhs, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsncoll_l)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       size_t max_chars,
                                       locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbsncmp_l(lhs, rhs, max_chars, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsnicoll_l)(unsigned char const *lhs,
                                        unsigned char const *rhs,
                                        size_t max_chars,
                                        locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbsnicmp_l(lhs, rhs, max_chars, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcoll_l)(unsigned char const *lhs,
                                        unsigned char const *rhs,
                                        size_t max_bytes,
                                        locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbsnbcmp_l(lhs, rhs, max_bytes, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicoll_l)(unsigned char const *lhs,
                                         unsigned char const *rhs,
                                         size_t max_bytes,
                                         locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbsnbicmp_l(lhs, rhs, max_bytes, locale);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbslwr_l)(unsigned char *buf,
                                     locale_t locale) {
	unsigned char *iter = buf;
	for (;;) {
		uint16_t ch = *iter;
		if (!ch)
			break;
		if (libc__ismbblead_l(ch, locale)) {
			if unlikely(!iter[1])
				goto do_1byte_lower;
			ch      = (ch << 8) | iter[1];
			ch      = libc__mbctolower_l(ch, locale);
			iter[0] = (unsigned char)((ch & 0xff00) >> 8);
			iter[1] = (unsigned char)(ch & 0xff);
			iter += 2;
		} else {
do_1byte_lower:
			ch      = libc__mbctolower_l(ch, locale);
			iter[0] = (unsigned char)(ch & 0xff);
			++iter;
		}
	}
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsupr_l)(unsigned char *buf,
                                     locale_t locale) {
	unsigned char *iter = buf;
	for (;;) {
		uint16_t ch = *iter;
		if (!ch)
			break;
		if (libc__ismbblead_l(ch, locale)) {
			if unlikely(!iter[1])
				goto do_1byte_lower;
			ch      = (ch << 8) | iter[1];
			ch      = libc__mbctoupper_l(ch, locale);
			iter[0] = (unsigned char)((ch & 0xff00) >> 8);
			iter[1] = (unsigned char)(ch & 0xff);
			iter += 2;
		} else {
do_1byte_lower:
			ch      = libc__mbctoupper_l(ch, locale);
			iter[0] = (unsigned char)(ch & 0xff);
			++iter;
		}
	}
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsinc_l)(unsigned char const *ptr,
                                     locale_t locale) {
	if (libc__ismbblead_l(*ptr++, locale)) {
		if (*ptr)
			++ptr;
	}
	return (unsigned char *)ptr;
}
/* Returns pointer to `max_chars'th character of `str' (or strend() when `max_chars > _mbslen_l(str)') */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsninc_l)(unsigned char const *str,
                                      size_t max_chars,
                                      locale_t locale) {
	if (str != NULL)
		str += libc__mbsnbcnt_l(str, max_chars, locale);
	return (unsigned char *)str;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsdec_l)(unsigned char const *start,
                                     unsigned char const *pos,
                                     locale_t locale) {
	unsigned char const *iter;
	if (start >= pos)
		return NULL;
	iter = start;
	for (;;) {
		unsigned char const *next;
		next = libc__mbsinc_l(iter, locale);
		if (next >= pos)
			break;
		iter = next;
	}
	return (unsigned char *)iter;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBCCALL libc__mbscspn_l)(unsigned char const *haystack,
                                      unsigned char const *reject,
                                      locale_t locale) {
	unsigned char const *iter = haystack;
	for (;;) {
		uint16_t ch = *iter++;
		if (libc__ismbblead_l(ch, locale))
			ch = *iter ? (ch << 8) | *iter++ : 0;
		if (ch == 0)
			break;
		if (libc__mbschr_l(reject, ch, locale) != NULL)
			break;
	}
	return (size_t)(iter - haystack);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc__mbslen_l)(unsigned char const *str,
                                     locale_t locale) {
	size_t result;
	for (result = 0;; ++result) {
		uint16_t ch = *str++;
		if (libc__ismbblead_l(ch, locale))
			ch = *str ? (ch << 8) | *str++ : 0;
		if (ch == 0)
			break;
	}
	return result;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnlen_l)(unsigned char const *str,
                                      size_t max_bytes,
                                      locale_t locale) {
	size_t result;
	for (result = 0; max_bytes; ++result) {
		uint16_t ch = *str++;
		--max_bytes;
		if (libc__ismbblead_l(ch, locale)) {
			if (!max_bytes)
				break;
			ch = *str ? (ch << 8) | *str++ : 0;
			--max_bytes;
		}
		if (ch == 0)
			break;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(2) ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsncat_l)(unsigned char *buf,
                                      unsigned char const *src,
                                      size_t max_chars,
                                      locale_t locale) {
	if (max_chars) {
		unsigned char *dst;
		dst = (unsigned char *)libc_strend((char const *)buf);
		for (; max_chars; --max_chars) {
			unsigned char ch;
			*dst++ = ch = *src++;
			if (!ch)
				return buf;
			if (libc__ismbblead_l(ch, locale)) {
				*dst++ = ch = *src++;
				if unlikely(!ch) {
					dst[-2] = '\0'; /* "fix" incomplete 2-byte character. */
					return buf;
				}
			}
		}
		*dst = '\0';
	}
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUT(1) ATTR_INS(2, 3) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbcat_l)(unsigned char *buf,
                                       unsigned char const *src,
                                       size_t max_bytes,
                                       locale_t locale) {
	unsigned char *dst;
	dst = (unsigned char *)libc_strend((char const *)buf);
	for (;;) {
		unsigned char ch;
		if (!max_bytes)
			break;
		--max_bytes;
		*dst++ = ch = *src++;
		if (!ch)
			return buf;
		if (libc__ismbblead_l(ch, locale)) {
			if (!max_bytes) {
				dst[-1] = '\0'; /* "fix" incomplete 2-byte character. */
				return buf;
			}
			--max_bytes;
			*dst++ = ch = *src++;
			if unlikely(!ch) {
				dst[-2] = '\0'; /* "fix" incomplete 2-byte character. */
				return buf;
			}
		}
	}
	*dst = '\0';
	return buf;
}
#include <hybrid/typecore.h>
/* Returns # of characters in (up to) first `max_bytes' of `str'. */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnccnt_l)(unsigned char const *str,
                                       size_t max_bytes,
                                       locale_t locale) {
	unsigned char const *end;
	size_t result;
	result = 0;
	end    = str + max_bytes;
	for (;; ++result) {
		unsigned char ch;
		if (str >= end)
			break;
		ch = *str++;
		if (ch == 0)
			break;
		if (libc__ismbblead_l(ch, locale)) {
			if (str >= end)
				break;
			ch = *str++;
			if (ch == 0)
				break;
		}
	}
	return result;
}
#include <hybrid/typecore.h>
/* Returns byte-offset from `str' after skipping `max_chars' characters. */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcnt_l)(unsigned char const *str,
                                       size_t max_chars,
                                       locale_t locale) {
	unsigned char const *iter = str;
	for (; max_chars; --max_chars) {
		unsigned char ch;
		ch = *iter++;
		if (ch == 0)
			break;
		if (libc__ismbblead_l(ch, locale)) {
			ch = *iter++;
			if (ch == 0)
				break;
		}
	}
	return (size_t)(iter - str);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbscmp_l)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     locale_t locale) {
	for (;;) {
		uint16_t lc, rc;
		lc = *lhs++;
		if (libc__ismbblead_l(lc, locale))
			lc = *lhs ? (lc << 8) | *lhs++ : 0;
		rc = *rhs++;
		if (libc__ismbblead_l(rc, locale))
			rc = *rhs ? (rc << 8) | *rhs++ : 0;
		if (lc != rc)
			return (int)lc - (int)rc;
		if (lc == 0)
			break;
	}
	return 0;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsicmp_l)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      locale_t locale) {
	for (;;) {
		uint16_t lc, rc;
		lc = *lhs++;
		if (libc__ismbblead_l(lc, locale))
			lc = *lhs ? (lc << 8) | *lhs++ : 0;
		rc = *rhs++;
		if (libc__ismbblead_l(rc, locale))
			rc = *rhs ? (rc << 8) | *rhs++ : 0;
		if (lc != rc) {
			lc = libc__mbctolower_l(lc, locale);
			rc = libc__mbctolower_l(rc, locale);
			if (lc != rc)
				return (int)lc - (int)rc;
		}
		if (lc == 0)
			break;
	}
	return 0;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsncmp_l)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t max_chars,
                                      locale_t locale) {
	for (; max_chars; --max_chars) {
		uint16_t lc = 0, rc = 0;
		lc = *lhs++;
		if (libc__ismbblead_l(lc, locale))
			lc = *lhs ? (lc << 8) | *lhs++ : 0;
		rc = *rhs++;
		if (libc__ismbblead_l(rc, locale))
			rc = *rhs ? (rc << 8) | *rhs++ : 0;
		if (lc != rc)
			return (int)lc - (int)rc;
		if (lc == 0)
			break;
	}
	return 0;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__mbsnicmp_l)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       size_t max_chars,
                                       locale_t locale) {
	for (; max_chars; --max_chars) {
		uint16_t lc = 0, rc = 0;
		lc = *lhs++;
		if (libc__ismbblead_l(lc, locale))
			lc = *lhs ? (lc << 8) | *lhs++ : 0;
		rc = *rhs++;
		if (libc__ismbblead_l(rc, locale))
			rc = *rhs ? (rc << 8) | *rhs++ : 0;
		if (lc != rc) {
			lc = libc__mbctolower_l(lc, locale);
			rc = libc__mbctolower_l(rc, locale);
			if (lc != rc)
				return (int)lc - (int)rc;
		}
		if (lc == 0)
			break;
	}
	return 0;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcmp_l)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       size_t max_bytes,
                                       locale_t locale) {
	unsigned char const *lhs_end = lhs + max_bytes;
	unsigned char const *rhs_end = rhs + max_bytes;
	for (;;) {
		uint16_t lc = 0, rc = 0;
		if (lhs < lhs_end) {
			lc = *lhs++;
			if (libc__ismbblead_l(lc, locale))
				lc = (lhs < lhs_end && *lhs) ? (lc << 8) | *lhs++ : 0;
		}
		if (rhs < rhs_end) {
			rc = *rhs++;
			if (libc__ismbblead_l(rc, locale))
				rc = (rhs < rhs_end && *rhs) ? (rc << 8) | *rhs++ : 0;
		}
		if (lc != rc)
			return (int)lc - (int)rc;
		if (lc == 0)
			break;
	}
	return 0;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicmp_l)(unsigned char const *lhs,
                                        unsigned char const *rhs,
                                        size_t max_bytes,
                                        locale_t locale) {
	unsigned char const *lhs_end = lhs + max_bytes;
	unsigned char const *rhs_end = rhs + max_bytes;
	for (;;) {
		uint16_t lc = 0, rc = 0;
		if (lhs < lhs_end) {
			lc = *lhs++;
			if (libc__ismbblead_l(lc, locale))
				lc = (lhs < lhs_end && *lhs) ? (lc << 8) | *lhs++ : 0;
		}
		if (rhs < rhs_end) {
			rc = *rhs++;
			if (libc__ismbblead_l(rc, locale))
				rc = (rhs < rhs_end && *rhs) ? (rc << 8) | *rhs++ : 0;
		}
		if (lc != rc) {
			lc = libc__mbctolower_l(lc, locale);
			rc = libc__mbctolower_l(rc, locale);
			if (lc != rc)
				return (int)lc - (int)rc;
		}
		if (lc == 0)
			break;
	}
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) unsigned int
NOTHROW_NCX(LIBCCALL libc__mbsnextc_l)(unsigned char const *str,
                                       locale_t locale) {
	uint16_t result = str[0];
	if (libc__ismbblead_l(result, locale))
		result = (result << 8) | str[1];
	return result;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbspbrk_l)(unsigned char const *haystack,
                                      unsigned char const *accept,
                                      locale_t locale) {
	uint16_t haych, ch;
	for (;;) {
		unsigned char const *temp;
		unsigned char const *ned_iter;
		temp  = haystack;
		haych = *haystack++;
		if (libc__ismbblead_l(haych, locale))
			haych = *haystack ? (haych << 8) | *haystack++ : 0;
		if (haych == 0)
			break;
		for (ned_iter = accept;;) {
			ch = *ned_iter++;
			if (libc__ismbblead_l(ch, locale))
				ch = *ned_iter ? (ch << 8) | *ned_iter++ : 0;
			if (ch == 0)
				break;
			if (haych == ch)
				return (unsigned char *)temp;
		}
	}
	return NULL;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsrchr_l)(unsigned char const *haystack,
                                      unsigned int needle,
                                      locale_t locale) {
	unsigned char *result = NULL;
	for (;;) {
		unsigned char const *temp;
		uint16_t hay;
		temp = haystack;
		hay  = *haystack++;
		if (libc__ismbblead_l(hay, locale))
			hay = *haystack ? (hay << 8) | *haystack++ : 0;
		if (hay == 0)
			break;
		if (hay == (uint16_t)(unsigned int)needle)
			result = (unsigned char *)temp;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsrev_l)(unsigned char *buf,
                                     locale_t locale) {
	size_t bytes;
	bytes = libc_strlen(libc_strrev((char *)buf));
	while (bytes >= 2) {
		unsigned char ch = buf[bytes - 1];
		if (libc__ismbblead_l(ch, locale)) {
			/* Swap with preceding character to fix multi-byte character. */
			buf[bytes - 1] = buf[bytes - 2];
			buf[bytes - 2] = ch;
			bytes -= 2;
		} else {
			bytes -= 1;
		}
	}
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_IN(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsset_l)(unsigned char *buf,
                                     unsigned int ch,
                                     locale_t locale) {
	unsigned char *iter, lob, hib;
	lob = (ch & 0xff);
	hib = (ch & 0xff00) >> 8;
	if (!hib || !libc__ismbblead_l(lob, locale))
		return (unsigned char *)libc_strset((char *)buf, (int)lob);
	for (iter = buf; *iter;) {
		*iter++ = lob;
		if (*iter == 0) {
			/* Undocumented, but disassembly shows that this is also what DOS does. */
			iter[-1] = ' ';
			break;
		}
		*iter++ = hib;
	}
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_RETNONNULL ATTR_INOUT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnset_l)(unsigned char *buf,
                                      unsigned int ch,
                                      size_t max_chars,
                                      locale_t locale) {
	unsigned char *iter, lob, hib;
	lob = (ch & 0xff);
	hib = (ch & 0xff00) >> 8;
	if (!hib || !libc__ismbblead_l(lob, locale))
		return (unsigned char *)libc_strnset((char *)buf, (int)lob, max_chars);
	for (iter = buf; max_chars && *iter; --max_chars) {
		*iter++ = lob;
		if (*iter == 0) {
			/* Undocumented, but disassembly shows that this is also what DOS does. */
			iter[-1] = ' ';
			break;
		}
		*iter++ = hib;
	}
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 3) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbset_l)(unsigned char *buf,
                                       unsigned int ch,
                                       size_t max_bytes,
                                       locale_t locale) {
	unsigned char *iter, lob, hib;
	lob = (ch & 0xff);
	hib = (ch & 0xff00) >> 8;
	if (!hib || !libc__ismbblead_l(lob, locale))
		return (unsigned char *)libc_strnset((char *)buf, (int)lob, max_bytes);
	for (iter = buf;;) {
		if (max_bytes == 0)
			break;
		--max_bytes;
		if (*iter == 0)
			break;
		*iter++ = lob;
		if (max_bytes-- == 0 || *iter == 0) {
			/* Undocumented, but disassembly shows that this is also what DOS does. */
			iter[-1] = ' ';
			break;
		}
		*iter++ = hib;
	}
	return buf;
}
/* Returs a byte-offset */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBCCALL libc__mbsspn_l)(unsigned char const *haystack,
                                     unsigned char const *accept,
                                     locale_t locale) {
	unsigned char const *iter = haystack;
	for (;;) {
		uint16_t ch;
		unsigned char const *next;
		next = iter;
		ch   = *next++;
		if (!ch)
			break;
		if (libc__ismbblead_l(ch, locale))
			ch = *next ? (ch << 8) | *next++ : 0;
		if (!libc__mbschr_l(accept, ch, locale))
			break;
		iter = next;
	}
	return (size_t)(iter - haystack);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsspnp_l)(unsigned char const *haystack,
                                      unsigned char const *accept,
                                      locale_t locale) {
	haystack += libc__mbsspn_l(haystack, accept, locale);
	if (*haystack == 0)
		haystack = NULL;
	return (unsigned char *)haystack;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsstr_l)(unsigned char const *haystack,
                                     unsigned char const *needle,
                                     locale_t locale) {
	uint16_t needle_first;
	size_t needle_first_len;
	size_t needle_len;
	needle_first     = *needle++;
	needle_first_len = 1;
	if (libc__ismbblead_l(needle_first, locale)) {
		needle_first     = *needle ? (needle_first << 8) | *needle++ : 0;
		needle_first_len = 2;
	}
	if unlikely(!needle_first)
		return NULL;
	needle_len = libc_strlen((char const *)needle);

	/* Enumerate candidates */
	while ((haystack = libc__mbschr_l(haystack, needle_first, locale)) != NULL) {

		/* Skip first character. */
		haystack += needle_first_len;

		/* Check that all of the remaining bytes match. */
		if (libc_strcmpz((char const *)needle, (char const *)haystack, needle_len) == 0)
			break; /* Found it! */
	}
	return (unsigned char *)haystack;
}
#include "../libc/tls-globals.h"
INTERN ATTR_SECTION(".text.crt.dos.mbstring") WUNUSED ATTR_IN(2) ATTR_INOUT_OPT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbstok_l)(unsigned char *str,
                                     unsigned char const *delim,
                                     locale_t locale) {
	char **const _p_strtok_save_ptr = &libc_get_tlsglobals()->ltg_strtok_save_ptr;
#define strtok_save_ptr (*_p_strtok_save_ptr)
	return libc__mbstok_s_l(str, delim, (unsigned char **)&strtok_save_ptr, locale);
}
#undef strtok_save_ptr
INTERN ATTR_SECTION(".text.crt.dos.mbstring") WUNUSED ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbstok_s_l)(unsigned char *str,
                                       unsigned char const *delim,
                                       unsigned char **__restrict save_ptr,
                                       locale_t locale) {
	unsigned char *end;
	if (!str)
		str = *save_ptr;
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	str += libc__mbsspn_l(str, delim, locale);
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	end = str + libc__mbscspn_l(str, delim, locale);
	if (!*end) {
		*save_ptr = end;
		return str;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return str;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc__mbclen_l)(unsigned char const *str,
                                     locale_t locale) {
	size_t result = 1;
	if (libc__ismbblead_l(str[0], locale) && str[1])
		result = 2;
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscat_s_l)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned char const *src,
                                       locale_t locale) {
	(void)locale;
	return libc_strcat_s((char *)buf, true_bufsize, (char const *)src);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscpy_s_l)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned char const *src,
                                       locale_t locale) {
	(void)locale;
	return libc_strcpy_s((char *)buf, true_bufsize, (char const *)src);
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbslwr_s_l)(unsigned char *buf,
                                       size_t true_bufsize,
                                       locale_t locale) {
	if (!buf || libc_strnlen((char const *)buf, true_bufsize) >= true_bufsize)
		return 22;
	libc__mbslwr_l(buf, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsupr_s_l)(unsigned char *buf,
                                       size_t true_bufsize,
                                       locale_t locale) {
	if (!buf || libc_strnlen((char const *)buf, true_bufsize) >= true_bufsize)
		return 22;
	libc__mbsupr_l(buf, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) ATTR_INS(3, 4) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcat_s_l)(unsigned char *buf,
                                         size_t true_bufsize,
                                         unsigned char const *src,
                                         size_t max_bytes,
                                         locale_t locale) {
	if (!buf || (!src && max_bytes) ||
	    true_bufsize <= libc_strnlen((char const *)src, max_bytes))
		return 22;
	libc__mbsnbcat_l(buf, src, max_bytes, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(3) ATTR_OUTS(1, 4) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_s_l)(unsigned char *buf,
                                         size_t true_bufsize,
                                         unsigned char const *src,
                                         size_t bufsize,
                                         locale_t locale) {
	if (bufsize && (!buf || !src || true_bufsize < bufsize))
		return 22;
	libc__mbsnbcpy_l(buf, src, bufsize, locale);
	return 0;
}
#include <hybrid/__minmax.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbset_s_l)(unsigned char *buf,
                                         size_t true_bufsize,
                                         unsigned int ch,
                                         size_t max_bytes,
                                         locale_t locale) {
	if (max_bytes && (!buf || true_bufsize <= libc_strnlen((char const *)buf, __hybrid_min2(true_bufsize, max_bytes))))
		return 22;
	libc__mbsnbset_l(buf, ch, max_bytes, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(3) ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncat_s_l)(unsigned char *buf,
                                        size_t true_bufsize,
                                        unsigned char const *src,
                                        size_t max_chars,
                                        locale_t locale) {
	if (max_chars && (!buf || !src ||
	                  true_bufsize <= (libc_strnlen((char const *)buf, true_bufsize) +
	                                   libc__mbsnbcnt_l(src, max_chars, locale))))
		return 22;
	libc__mbsncat_l(buf, src, max_chars, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncpy_s_l)(unsigned char *buf,
                                        size_t true_bufsize,
                                        unsigned char const *src,
                                        size_t max_chars,
                                        locale_t locale) {
	if (max_chars && (!buf || !src))
		return 22;
	for (; max_chars; --max_chars) {
		unsigned char ch;
		if (!true_bufsize)
			return 22;
		--true_bufsize;
		*buf++ = ch = *src++;
		if (!ch)
			break;
		if (libc__ismbblead_l(ch, locale)) {
			if (!true_bufsize)
				return 22;
			--true_bufsize;
			*buf++ = ch = *src++;
			if unlikely(!ch) {
				buf[-2] = '\0'; /* "fix" incomplete 2-byte character. */
				break;
			}
		}
	}
	if (true_bufsize < max_chars)
		return 22;

	/* Really weird  quirk: until  this point,  `max_chars' were  counted
	 * in chars, but this zero-padding (which is also done by DOS), would
	 * mean that it's suddenly counted in characters... */
	libc_bzero(buf, max_chars);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnset_s_l)(unsigned char *buf,
                                        size_t true_bufsize,
                                        unsigned int ch,
                                        size_t max_chars,
                                        locale_t locale) {
	if (max_chars && !buf)
		return 22;
	if (max_chars > true_bufsize && true_bufsize == libc_strnlen((char const *)buf, true_bufsize))
		return 22;
	libc__mbsnset_l(buf, ch, max_chars, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsset_s_l)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned int ch,
                                       locale_t locale) {
	if (!buf || true_bufsize == libc_strnlen((char const *)buf, true_bufsize))
		return 22;
	libc__mbsset_l(buf, ch, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_IN(4) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__mbccpy_s_l)(unsigned char *dst,
                                       size_t true_dstsize,
                                       int *p_copied,
                                       unsigned char const *src,
                                       locale_t locale) {
	unsigned char ch;
	if (p_copied)
		*p_copied = 0;
	if (!dst || !src || !true_dstsize)
		return 22;
	*dst = ch = *src;
	if (libc__ismbblead_l(ch, locale)) {
		if (true_dstsize < 2)
			return 22;
		dst[1] = src[1];
		if (p_copied)
			*p_copied = 2;
	} else {
		if (p_copied)
			*p_copied = 1;
	}
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__ismbslead_l)(unsigned char const *str,
                                        unsigned char const *pos,
                                        locale_t locale) {
	while (str <= pos) {
		unsigned char ch = *str++;
		if (ch == 0)
			break;
		if (libc__ismbblead_l(ch, locale)) {
			if (str - 1 == pos)
				return -1; /* No, this isn't an error; this function just returns `-1' for "yes" */
			ch = *str++;
			if (ch == 0)
				break;
		}
	}
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc__ismbstrail_l)(unsigned char const *str,
                                         unsigned char const *pos,
                                         locale_t locale) {
	while (str <= pos) {
		unsigned char ch = *str++;
		if (ch == 0)
			break;
		if (libc__ismbblead_l(ch, locale)) {
			if (str == pos)
				return -1; /* No, this isn't an error; this function just returns `-1' for "yes" */
			ch = *str++;
			if (ch == 0)
				break;
		}
	}
	return 0;
}
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
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__mbbtype_l)(unsigned char ch,
                                      int ctype,
                                      locale_t locale) {
	if (ctype == 1)
		return libc__ismbbtrail_l(ch, locale) ? 2 : (-1);
	if (libc__ismbblead_l(ch, locale))
		return 1;
	if (libc__ismbbprint_l(ch, locale))
		return 0;
	return (-1);
}
/* >> _mbsbtype(3), _mbsbtype_l(3)
 * Returns the type (one of `_MBC_*' from `<mbctype.h>')
 * of the byte at `str[byte_index]'. If that byte is out
 * of bounds, return `_MBC_ILLEGAL' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc__mbsbtype_l)(unsigned char const *str,
                                       size_t byte_index,
                                       locale_t locale) {
	int result = (-1);
	for (;;) {
		unsigned char ch = *str;
		if unlikely(ch == 0)
			return (-1);
		result = libc__mbbtype_l(ch, result, locale);
		if (!byte_index)
			break;
		--byte_index;
		++str;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbclegal_l)(unsigned int ch,
                                         locale_t locale) {
	if (!libc__ismbblead_l((ch >> 8) & 0xff, locale))
		return 0;
	if (!libc__ismbbtrail_l(ch & 0xff, locale))
		return 0;
	return 1;
}
#include <libc/template/mbcasemap.h>
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctolower_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni;
	uni = libc__mbctouni_l(ch, locale);
	uni = __libc_unicode_tolower(uni);
	return libc__unitombc_l(ch, locale);







}
#include <libc/template/mbcasemap.h>
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctoupper_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni;
	uni = libc__mbctouni_l(ch, locale);
	uni = __libc_unicode_toupper(uni);
	return libc__unitombc_l(ch, locale);







}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcalnum_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni = libc__mbctouni_l(ch, locale);
	return __libc_unicode_isalnum(uni);





}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcalpha_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni = libc__mbctouni_l(ch, locale);
	return __libc_unicode_isalpha(uni);





}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcdigit_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni = libc__mbctouni_l(ch, locale);
	return __libc_unicode_isdigit(uni);





}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcgraph_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni = libc__mbctouni_l(ch, locale);
	return __libc_unicode_isgraph(uni);





}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbclower_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni = libc__mbctouni_l(ch, locale);
	return __libc_unicode_islower(uni);





}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcupper_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni = libc__mbctouni_l(ch, locale);
	return __libc_unicode_isupper(uni);





}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcprint_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni = libc__mbctouni_l(ch, locale);
	return __libc_unicode_isprint(uni);





}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcpunct_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni = libc__mbctouni_l(ch, locale);
	return __libc_unicode_ispunct(uni);





}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcblank_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni = libc__mbctouni_l(ch, locale);
	return __libc_unicode_isblank(uni);





}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcspace_l)(unsigned int ch,
                                         locale_t locale) {

	char32_t uni = libc__mbctouni_l(ch, locale);
	return __libc_unicode_isspace(uni);





}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbchira_l)(unsigned int ch,
                                        locale_t locale) {
	/* Extrapolated from reverse engineering. */
	if (libc__getmbcp_l(locale) != 932)
		return 0;
	if (ch > 0x829e && ch < 0x82f2)
		return 1;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbckata_l)(unsigned int ch,
                                        locale_t locale) {
	/* Extrapolated from reverse engineering. */
	if (libc__getmbcp_l(locale) != 932)
		return 0;
	if (ch > 0x833f && ch < 0x8397 && ch != 0x837f)
		return 1;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcsymbol_l)(unsigned int ch,
                                          locale_t locale) {
	/* Extrapolated from reverse engineering. */
	if (libc__getmbcp_l(locale) != 932)
		return 0;
	if (ch > 0x8140 && ch < 0x81ad && ch != 0x817f)
		return 1;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl0_l)(unsigned int ch,
                                      locale_t locale) {
	/* Extrapolated from reverse engineering. */
	if (libc__getmbcp_l(locale) != 932)
		return 0;
	if (!libc__ismbblead_l((ch >> 8) & 0xff, locale))
		return 0;
	if (!libc__ismbbtrail_l(ch & 0xff, locale))
		return 0;
	if (ch < 0x889f)
		return 1;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl1_l)(unsigned int ch,
                                      locale_t locale) {
	/* Extrapolated from reverse engineering. */
	if (libc__getmbcp_l(locale) != 932)
		return 0;
	if (!libc__ismbblead_l((ch >> 8) & 0xff, locale))
		return 0;
	if (!libc__ismbbtrail_l(ch & 0xff, locale))
		return 0;
	if (ch > 0x889e && ch < 0x9873)
		return 1;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl2_l)(unsigned int ch,
                                      locale_t locale) {
	/* Extrapolated from reverse engineering. */
	if (libc__getmbcp_l(locale) != 932)
		return 0;
	if (!libc__ismbblead_l((ch >> 8) & 0xff, locale))
		return 0;
	if (!libc__ismbbtrail_l(ch & 0xff, locale))
		return 0;
	if (ch > 0x989e && ch < 0xeaa5)
		return 1;
	return 0;
}
#include <libc/errno.h>
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbcjistojms_l)(unsigned int ch,
                                          locale_t locale) {
	unsigned char c1, c2, temp;
	/* Extrapolated from reverse engineering. */
	if (libc__getmbcp_l(locale) != 932)
		return ch;
	c1 = ch & 0xff;
	c2 = ch >> 8 & 0xff;
	if ((c1 > 0x7e) || (c1 < 0x21) ||
	    (c2 > 0x7e) || (c2 < 0x21)) {

		__libc_seterrno(EILSEQ);

		return 0;
	}
	if (((ch >> 8) & 1) == 0) {
		c1 += 0x7e;
	} else {
		c1 += c1 < 0x60 ? 0x1f: 0x20;
	}
	temp = (c2 - 0x21) >> 1;
	c2   = temp + 0x81;
	if (c2 > 0x9f)
		c2 = temp + 0xc1;
	return (uint16_t)c2 << 8 | c1;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbcjmstojis_l)(unsigned int ch,
                                          locale_t locale) {
	unsigned char c1, c2;
	/* Extrapolated from reverse engineering. */
	if (libc__getmbcp_l(locale) != 932)
		return ch;
	c1 = ch & 0xff;
	c2 = (ch >> 8) & 0xff;
	if (libc__ismbblead_l(c1, locale) && libc__ismbbtrail_l(c2, locale)) {
		c2 -= c2 < 0xa0 ? 0x81 : 0xc1;
		if (c1 < 0x9f) {
			ch = (c2 * 0x200) + 0x2100;
			ch |= c1 - (c1 < 0x7f ? 0x1f : 0x20);
		} else {
			ch = (c2 * 0x200) + 0x2200;
			ch |= c1 - 0x7e;
		}
		if ((ch > 0x2120 && ch < 0x7e7f) &&
		    ((ch & 0xff) > 0x20) &&
		    ((ch & 0xff) < 0x7f))
			return ch;
	}

	__libc_seterrno(EILSEQ);

	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctohira_l)(unsigned int ch,
                                        locale_t locale) {
	/* Extrapolated from reverse engineering. */
	if (libc__ismbckata_l(ch, locale) && ch < 0x8394) {
		if (ch < 0x837f) {
			ch -= 0xa1;
		} else {
			ch -= 0xa2;
		}
	}
	return ch;
}
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctokata_l)(unsigned int ch,
                                        locale_t locale) {
	/* Extrapolated from reverse engineering. */
	unsigned int result = ch;
	if (libc__ismbchira_l(ch, locale)) {
		result = ch + 0xa1;
		if (result > 0x837e)
			++result;
	}
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_mbbtombc,libc__mbbtombc,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_mbbtype,libc__mbbtype,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned char ch, int ctype),(ch,ctype));
DEFINE_PUBLIC_ALIAS_P(_mbctombb,libc__mbctombb,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_mbsbtype,libc__mbsbtype,ATTR_PURE WUNUSED ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, size_t byte_index),(str,byte_index));
DEFINE_PUBLIC_ALIAS_P(_mbscat_s,libc__mbscat_s,ATTR_IN(3) ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src),(buf,true_bufsize,src));
DEFINE_PUBLIC_ALIAS_P(_mbschr,libc__mbschr,ATTR_PURE WUNUSED ATTR_IN(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *__restrict haystack, unsigned int needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(_mbscmp,libc__mbscmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs),(lhs,rhs));
DEFINE_PUBLIC_ALIAS_P(_mbscoll,libc__mbscoll,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs),(lhs,rhs));
DEFINE_PUBLIC_ALIAS_P(_mbscpy_s,libc__mbscpy_s,ATTR_IN(3) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src),(buf,true_bufsize,src));
DEFINE_PUBLIC_ALIAS_P(_mbscspn,libc__mbscspn,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned char const *reject),(haystack,reject));
DEFINE_PUBLIC_ALIAS_P(_mbsdec,libc__mbsdec,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *start, unsigned char const *pos),(start,pos));
DEFINE_PUBLIC_ALIAS_P(_mbsicmp,libc__mbsicmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs),(lhs,rhs));
DEFINE_PUBLIC_ALIAS_P(_mbsicoll,libc__mbsicoll,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs),(lhs,rhs));
DEFINE_PUBLIC_ALIAS_P(_mbsinc,libc__mbsinc,ATTR_PURE WUNUSED ATTR_IN(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *ptr),(ptr));
DEFINE_PUBLIC_ALIAS_P(_mbslen,libc__mbslen,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *str),(str));
DEFINE_PUBLIC_ALIAS_P(_mbsnlen,libc__mbsnlen,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, size_t max_bytes),(str,max_bytes));
DEFINE_PUBLIC_ALIAS_P(_mbslwr_s,libc__mbslwr_s,ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize),(buf,true_bufsize));
DEFINE_PUBLIC_ALIAS_P(_mbslwr,libc__mbslwr,ATTR_RETNONNULL ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf),(buf));
DEFINE_PUBLIC_ALIAS_P(_mbsupr,libc__mbsupr,ATTR_RETNONNULL ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf),(buf));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcat_s,libc__mbsnbcat_s,ATTR_INOUTS(1, 2) ATTR_INS(3, 4),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_bytes),(buf,true_bufsize,src,max_bytes));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcat,libc__mbsnbcat,ATTR_INOUT(1) ATTR_INS(2, 3),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned char const *src, size_t max_bytes),(buf,src,max_bytes));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcmp,libc__mbsnbcmp,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes),(lhs,rhs,max_bytes));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcoll,libc__mbsnbcoll,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes),(lhs,rhs,max_bytes));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcnt,libc__mbsnbcnt,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, size_t max_chars),(str,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcpy_s,libc__mbsnbcpy_s,ATTR_IN(3) ATTR_OUTS(1, 4),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t bufsize),(buf,true_bufsize,src,bufsize));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcpy,libc__mbsnbcpy,ATTR_IN(2) ATTR_OUTS(1, 3),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned char const *src, size_t bufsize),(buf,src,bufsize));
DEFINE_PUBLIC_ALIAS_P(_mbsnbicmp,libc__mbsnbicmp,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes),(lhs,rhs,max_bytes));
DEFINE_PUBLIC_ALIAS_P(_mbsnbicoll,libc__mbsnbicoll,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes),(lhs,rhs,max_bytes));
DEFINE_PUBLIC_ALIAS_P(_mbsnbset_s,libc__mbsnbset_s,ATTR_INOUTS(1, 4),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_bytes),(buf,true_bufsize,ch,max_bytes));
DEFINE_PUBLIC_ALIAS_P(_mbsnbset,libc__mbsnbset,ATTR_INOUTS(1, 3),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned int ch, size_t max_bytes),(buf,ch,max_bytes));
DEFINE_PUBLIC_ALIAS_P(_mbsncat_s,libc__mbsncat_s,ATTR_IN(3) ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars),(buf,true_bufsize,src,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsncat,libc__mbsncat,ATTR_IN(2) ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned char const *src, size_t max_chars),(buf,src,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsnccnt,libc__mbsnccnt,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, size_t max_bytes),(str,max_bytes));
DEFINE_PUBLIC_ALIAS_P(_mbsncmp,libc__mbsncmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars),(lhs,rhs,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsncoll,libc__mbsncoll,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars),(lhs,rhs,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsncpy_s,libc__mbsncpy_s,ATTR_IN(3) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars),(buf,true_bufsize,src,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsncpy,libc__mbsncpy,ATTR_IN(2) ATTR_OUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned char const *src, size_t max_chars),(buf,src,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsnextc,libc__mbsnextc,ATTR_PURE WUNUSED ATTR_IN(1),unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned char const *str),(str));
DEFINE_PUBLIC_ALIAS_P(_mbsnicmp,libc__mbsnicmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars),(lhs,rhs,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsnicoll,libc__mbsnicoll,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars),(lhs,rhs,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsninc,libc__mbsninc,ATTR_PURE WUNUSED ATTR_IN(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, size_t max_chars),(str,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsnset_s,libc__mbsnset_s,ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_chars),(buf,true_bufsize,ch,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbsnset,libc__mbsnset,ATTR_RETNONNULL ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned int ch, size_t max_chars),(buf,ch,max_chars));
DEFINE_PUBLIC_ALIAS_P(_mbspbrk,libc__mbspbrk,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned char const *accept),(haystack,accept));
DEFINE_PUBLIC_ALIAS_P(_mbsrchr,libc__mbsrchr,ATTR_PURE WUNUSED ATTR_IN(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned int needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(_mbsrev,libc__mbsrev,ATTR_RETNONNULL ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf),(buf));
DEFINE_PUBLIC_ALIAS_P(_mbsset_s,libc__mbsset_s,ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned int ch),(buf,true_bufsize,ch));
DEFINE_PUBLIC_ALIAS_P(_mbsset,libc__mbsset,ATTR_RETNONNULL ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned int ch),(buf,ch));
DEFINE_PUBLIC_ALIAS_P(_mbsspn,libc__mbsspn,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned char const *accept),(haystack,accept));
DEFINE_PUBLIC_ALIAS_P(_mbsspnp,libc__mbsspnp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned char const *accept),(haystack,accept));
DEFINE_PUBLIC_ALIAS_P(_mbsstr,libc__mbsstr,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned char const *needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(_mbstok,libc__mbstok,WUNUSED ATTR_IN(2) ATTR_INOUT_OPT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *str, unsigned char const *delim),(str,delim));
DEFINE_PUBLIC_ALIAS_P(_mbstok_s,libc__mbstok_s,WUNUSED ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *str, unsigned char const *delim, unsigned char **__restrict save_ptr),(str,delim,save_ptr));
DEFINE_PUBLIC_ALIAS_P(_mbsupr_s,libc__mbsupr_s,ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize),(buf,true_bufsize));
DEFINE_PUBLIC_ALIAS_P(_mbclen,libc__mbclen,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *str),(str));
DEFINE_PUBLIC_ALIAS_P_VOID(_mbccpy,libc__mbccpy,ATTR_IN(2) ATTR_OUT(1),NOTHROW_NCX,LIBCCALL,(unsigned char *dst, unsigned char const *src),(dst,src));
DEFINE_PUBLIC_ALIAS_P(_mbccpy_s,libc__mbccpy_s,ATTR_IN(4) ATTR_OUTS(1, 2) ATTR_OUT_OPT(3),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *dst, size_t true_dstsize, int *p_copied, unsigned char const *src),(dst,true_dstsize,p_copied,src));
DEFINE_PUBLIC_ALIAS_P(_ismbcalnum,libc__ismbcalnum,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcalpha,libc__ismbcalpha,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcdigit,libc__ismbcdigit,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcgraph,libc__ismbcgraph,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbclegal,libc__ismbclegal,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbclower,libc__ismbclower,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcprint,libc__ismbcprint,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcpunct,libc__ismbcpunct,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcblank,libc__ismbcblank,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcspace,libc__ismbcspace,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcupper,libc__ismbcupper,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_mbctolower,libc__mbctolower,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_mbctoupper,libc__mbctoupper,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbchira,libc__ismbchira,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbckata,libc__ismbckata,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcsymbol,libc__ismbcsymbol,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcl0,libc__ismbcl0,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcl1,libc__ismbcl1,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbcl2,libc__ismbcl2,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_mbcjistojms,libc__mbcjistojms,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_mbcjmstojis,libc__mbcjmstojis,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_mbctohira,libc__mbctohira,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_mbctokata,libc__mbctokata,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(_ismbslead,libc__ismbslead,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, unsigned char const *pos),(str,pos));
DEFINE_PUBLIC_ALIAS_P(_ismbstrail,libc__ismbstrail,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, unsigned char const *pos),(str,pos));
DEFINE_PUBLIC_ALIAS_P(_mbscat_l,libc__mbscat_l,ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *__restrict dst, unsigned char const *__restrict src, locale_t locale),(dst,src,locale));
DEFINE_PUBLIC_ALIAS_P(_mbscpy_l,libc__mbscpy_l,ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *__restrict dst, unsigned char const *__restrict src, locale_t locale),(dst,src,locale));
DEFINE_PUBLIC_ALIAS_P_VOID(_mbccpy_l,libc__mbccpy_l,ATTR_IN(2) ATTR_OUT(1),NOTHROW_NCX,LIBCCALL,(unsigned char *dst, unsigned char const *src, locale_t locale),(dst,src,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsncpy_l,libc__mbsncpy_l,ATTR_IN(2) ATTR_OUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned char const *src, size_t max_chars, locale_t locale),(buf,src,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcpy_l,libc__mbsnbcpy_l,ATTR_IN(2) ATTR_OUTS(1, 3),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned char const *src, size_t bufsize, locale_t locale),(buf,src,bufsize,locale));
DEFINE_PUBLIC_ALIAS_P(_mbschr_l,libc__mbschr_l,ATTR_PURE WUNUSED ATTR_IN(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *__restrict haystack, unsigned int needle, locale_t locale),(haystack,needle,locale));
DEFINE_PUBLIC_ALIAS_P(_mbscoll_l,libc__mbscoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, locale_t locale),(lhs,rhs,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsicoll_l,libc__mbsicoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, locale_t locale),(lhs,rhs,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsncoll_l,libc__mbsncoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale),(lhs,rhs,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnicoll_l,libc__mbsnicoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale),(lhs,rhs,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcoll_l,libc__mbsnbcoll_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale),(lhs,rhs,max_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbicoll_l,libc__mbsnbicoll_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale),(lhs,rhs,max_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(_mbslwr_l,libc__mbslwr_l,ATTR_RETNONNULL ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, locale_t locale),(buf,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsupr_l,libc__mbsupr_l,ATTR_RETNONNULL ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, locale_t locale),(buf,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsinc_l,libc__mbsinc_l,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *ptr, locale_t locale),(ptr,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsninc_l,libc__mbsninc_l,ATTR_PURE WUNUSED,unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, size_t max_chars, locale_t locale),(str,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsdec_l,libc__mbsdec_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *start, unsigned char const *pos, locale_t locale),(start,pos,locale));
DEFINE_PUBLIC_ALIAS_P(_mbscspn_l,libc__mbscspn_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned char const *reject, locale_t locale),(haystack,reject,locale));
DEFINE_PUBLIC_ALIAS_P(_mbslen_l,libc__mbslen_l,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, locale_t locale),(str,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnlen_l,libc__mbsnlen_l,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, size_t max_bytes, locale_t locale),(str,max_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsncat_l,libc__mbsncat_l,ATTR_IN(2) ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned char const *src, size_t max_chars, locale_t locale),(buf,src,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcat_l,libc__mbsnbcat_l,ATTR_INOUT(1) ATTR_INS(2, 3),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned char const *src, size_t max_bytes, locale_t locale),(buf,src,max_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnccnt_l,libc__mbsnccnt_l,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, size_t max_bytes, locale_t locale),(str,max_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcnt_l,libc__mbsnbcnt_l,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, size_t max_chars, locale_t locale),(str,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbscmp_l,libc__mbscmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, locale_t locale),(lhs,rhs,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsicmp_l,libc__mbsicmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, locale_t locale),(lhs,rhs,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsncmp_l,libc__mbsncmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale),(lhs,rhs,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnicmp_l,libc__mbsnicmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_chars, locale_t locale),(lhs,rhs,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcmp_l,libc__mbsnbcmp_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale),(lhs,rhs,max_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbicmp_l,libc__mbsnbicmp_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *lhs, unsigned char const *rhs, size_t max_bytes, locale_t locale),(lhs,rhs,max_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnextc_l,libc__mbsnextc_l,ATTR_PURE WUNUSED ATTR_IN(1),unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, locale_t locale),(str,locale));
DEFINE_PUBLIC_ALIAS_P(_mbspbrk_l,libc__mbspbrk_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned char const *accept, locale_t locale),(haystack,accept,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsrchr_l,libc__mbsrchr_l,ATTR_PURE WUNUSED ATTR_IN(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned int needle, locale_t locale),(haystack,needle,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsrev_l,libc__mbsrev_l,ATTR_RETNONNULL ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, locale_t locale),(buf,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsset_l,libc__mbsset_l,ATTR_RETNONNULL ATTR_IN(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned int ch, locale_t locale),(buf,ch,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnset_l,libc__mbsnset_l,ATTR_RETNONNULL ATTR_INOUT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned int ch, size_t max_chars, locale_t locale),(buf,ch,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbset_l,libc__mbsnbset_l,ATTR_INOUTS(1, 3),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, unsigned int ch, size_t max_bytes, locale_t locale),(buf,ch,max_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsspn_l,libc__mbsspn_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned char const *accept, locale_t locale),(haystack,accept,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsspnp_l,libc__mbsspnp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned char const *accept, locale_t locale),(haystack,accept,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsstr_l,libc__mbsstr_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char const *haystack, unsigned char const *needle, locale_t locale),(haystack,needle,locale));
DEFINE_PUBLIC_ALIAS_P(_mbstok_l,libc__mbstok_l,WUNUSED ATTR_IN(2) ATTR_INOUT_OPT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *str, unsigned char const *delim, locale_t locale),(str,delim,locale));
DEFINE_PUBLIC_ALIAS_P(_mbstok_s_l,libc__mbstok_s_l,WUNUSED ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1),unsigned char *,NOTHROW_NCX,LIBCCALL,(unsigned char *str, unsigned char const *delim, unsigned char **__restrict save_ptr, locale_t locale),(str,delim,save_ptr,locale));
DEFINE_PUBLIC_ALIAS_P(_mbclen_l,libc__mbclen_l,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, locale_t locale),(str,locale));
DEFINE_PUBLIC_ALIAS_P(_mbscat_s_l,libc__mbscat_s_l,ATTR_IN(3) ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src, locale_t locale),(buf,true_bufsize,src,locale));
DEFINE_PUBLIC_ALIAS_P(_mbscpy_s_l,libc__mbscpy_s_l,ATTR_IN(3) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src, locale_t locale),(buf,true_bufsize,src,locale));
DEFINE_PUBLIC_ALIAS_P(_mbslwr_s_l,libc__mbslwr_s_l,ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, locale_t locale),(buf,true_bufsize,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsupr_s_l,libc__mbsupr_s_l,ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, locale_t locale),(buf,true_bufsize,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcat_s_l,libc__mbsnbcat_s_l,ATTR_INOUTS(1, 2) ATTR_INS(3, 4),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_bytes, locale_t locale),(buf,true_bufsize,src,max_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbcpy_s_l,libc__mbsnbcpy_s_l,ATTR_IN(3) ATTR_OUTS(1, 4),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t bufsize, locale_t locale),(buf,true_bufsize,src,bufsize,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnbset_s_l,libc__mbsnbset_s_l,ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_bytes, locale_t locale),(buf,true_bufsize,ch,max_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsncat_s_l,libc__mbsncat_s_l,ATTR_IN(3) ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars, locale_t locale),(buf,true_bufsize,src,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsncpy_s_l,libc__mbsncpy_s_l,ATTR_IN(3) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned char const *src, size_t max_chars, locale_t locale),(buf,true_bufsize,src,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsnset_s_l,libc__mbsnset_s_l,ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned int ch, size_t max_chars, locale_t locale),(buf,true_bufsize,ch,max_chars,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsset_s_l,libc__mbsset_s_l,ATTR_INOUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *buf, size_t true_bufsize, unsigned int ch, locale_t locale),(buf,true_bufsize,ch,locale));
DEFINE_PUBLIC_ALIAS_P(_mbccpy_s_l,libc__mbccpy_s_l,ATTR_IN(4) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned char *dst, size_t true_dstsize, int *p_copied, unsigned char const *src, locale_t locale),(dst,true_dstsize,p_copied,src,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbslead_l,libc__ismbslead_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, unsigned char const *pos, locale_t locale),(str,pos,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbstrail_l,libc__ismbstrail_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, unsigned char const *pos, locale_t locale),(str,pos,locale));
DEFINE_PUBLIC_ALIAS_P(_mbbtype_l,libc__mbbtype_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned char ch, int ctype, locale_t locale),(ch,ctype,locale));
DEFINE_PUBLIC_ALIAS_P(_mbsbtype_l,libc__mbsbtype_l,ATTR_PURE WUNUSED ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(unsigned char const *str, size_t byte_index, locale_t locale),(str,byte_index,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbclegal_l,libc__ismbclegal_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_mbctolower_l,libc__mbctolower_l,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_mbctoupper_l,libc__mbctoupper_l,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcalnum_l,libc__ismbcalnum_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcalpha_l,libc__ismbcalpha_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcdigit_l,libc__ismbcdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcgraph_l,libc__ismbcgraph_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbclower_l,libc__ismbclower_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcupper_l,libc__ismbcupper_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcprint_l,libc__ismbcprint_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcpunct_l,libc__ismbcpunct_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcblank_l,libc__ismbcblank_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcspace_l,libc__ismbcspace_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbchira_l,libc__ismbchira_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbckata_l,libc__ismbckata_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcsymbol_l,libc__ismbcsymbol_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcl0_l,libc__ismbcl0_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcl1_l,libc__ismbcl1_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_ismbcl2_l,libc__ismbcl2_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_mbcjistojms_l,libc__mbcjistojms_l,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_mbcjmstojis_l,libc__mbcjmstojis_l,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_mbctohira_l,libc__mbctohira_l,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(_mbctokata_l,libc__mbctokata_l,ATTR_PURE WUNUSED,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int ch, locale_t locale),(ch,locale));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_MBSTRING_C */
