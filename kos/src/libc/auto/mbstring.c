/* HASH CRC-32:0xf214273b */
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
#ifndef GUARD_LIBC_AUTO_MBSTRING_C
#define GUARD_LIBC_AUTO_MBSTRING_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/mbstring.h"
#include "../user/string.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbbtombc)(unsigned int ch) {
	return libc__mbbtombc_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__mbbtype)(unsigned char ch,
                                    int ctype) {
	return libc__mbbtype_l(ch, ctype, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctombb)(unsigned int ch) {
	return libc__mbctombb_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__mbsbtype)(unsigned char const *str,
                                     size_t pos) {
	return libc__mbsbtype_l(str, pos, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscat_s)(unsigned char *buf,
                                     size_t true_bufsize,
                                     unsigned char const *src) {
	return libc__mbscat_s_l(buf, true_bufsize, src, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbschr)(unsigned char const *__restrict haystack,
                                   unsigned int needle) {
	return libc__mbschr_l(haystack, needle, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbscmp)(unsigned char const *lhs,
                                   unsigned char const *rhs) {
	return libc__mbscmp_l(lhs, rhs, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbscoll)(unsigned char const *lhs,
                                    unsigned char const *rhs) {
	return libc__mbscoll_l(lhs, rhs, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscpy_s)(unsigned char *buf,
                                     size_t true_bufsize,
                                     unsigned char const *src) {
	return libc__mbscpy_s_l(buf, true_bufsize, src, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc__mbscspn)(unsigned char const *haystack,
                                    unsigned char const *reject) {
	return libc__mbscspn_l(haystack, reject, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsdec)(unsigned char const *start,
                                   unsigned char const *pos) {
	return libc__mbsdec_l(start, pos, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsicmp)(unsigned char const *lhs,
                                    unsigned char const *rhs) {
	return libc__mbsicmp_l(lhs, rhs, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsicoll)(unsigned char const *lhs,
                                     unsigned char const *rhs) {
	return libc__mbsicoll_l(lhs, rhs, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsinc)(unsigned char const *ptr) {
	return libc__mbsinc_l(ptr, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbslen)(unsigned char const *str) {
	return libc__mbslen_l(str, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnlen)(unsigned char const *str,
                                    size_t max_bytes) {
	return libc__mbsnlen_l(str, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbslwr_s)(unsigned char *buf,
                                     size_t true_bufsize) {
	return libc__mbslwr_s_l(buf, true_bufsize, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbslwr)(unsigned char *buf) {
	return libc__mbslwr_l(buf, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsupr)(unsigned char *buf) {
	return libc__mbsupr_l(buf, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcat_s)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned char const *src,
                                       size_t max_bytes) {
	return libc__mbsnbcat_s_l(buf, true_bufsize, src, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbcat)(unsigned char *buf,
                                     unsigned char const *src,
                                     size_t max_bytes) {
	return libc__mbsnbcat_l(buf, src, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcmp)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     size_t max_bytes) {
	return libc__mbsnbcmp_l(lhs, rhs, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcoll)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t max_bytes) {
	return libc__mbsnbcoll_l(lhs, rhs, max_bytes, NULL);
}
/* Returns byte-offset from `str' after skipping `max_chars' characters. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcnt)(unsigned char const *str,
                                     size_t max_chars) {
	return libc__mbsnbcnt_l(str, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_s)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned char const *src,
                                       size_t bufsize) {
	return libc__mbsnbcpy_s_l(buf, true_bufsize, src, bufsize, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbcpy)(unsigned char *buf,
                                     unsigned char const *src,
                                     size_t bufsize) {
	return libc__mbsnbcpy_l(buf, src, bufsize, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicmp)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t max_bytes) {
	return libc__mbsnbicmp_l(lhs, rhs, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicoll)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       size_t max_bytes) {
	return libc__mbsnbicoll_l(lhs, rhs, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbset_s)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned int ch,
                                       size_t max_bytes) {
	return libc__mbsnbset_s_l(buf, true_bufsize, ch, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbset)(unsigned char *buf,
                                     unsigned int ch,
                                     size_t max_bytes) {
	return libc__mbsnbset_l(buf, ch, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncat_s)(unsigned char *buf,
                                      size_t true_bufsize,
                                      unsigned char const *src,
                                      size_t max_chars) {
	return libc__mbsncat_s_l(buf, true_bufsize, src, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsncat)(unsigned char *buf,
                                    unsigned char const *src,
                                    size_t max_chars) {
	return libc__mbsncat_l(buf, src, max_chars, NULL);
}
/* Returns # of characters in (up to) first `max_bytes' of `str'. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnccnt)(unsigned char const *str,
                                     size_t max_bytes) {
	return libc__mbsnccnt_l(str, max_bytes, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsncmp)(unsigned char const *lhs,
                                    unsigned char const *rhs,
                                    size_t max_chars) {
	return libc__mbsncmp_l(lhs, rhs, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsncoll)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     size_t max_chars) {
	return libc__mbsncoll_l(lhs, rhs, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncpy_s)(unsigned char *buf,
                                      size_t true_bufsize,
                                      unsigned char const *src,
                                      size_t max_chars) {
	return libc__mbsncpy_s_l(buf, true_bufsize, src, max_chars, NULL);
}
/* WARNING: This function writes up to `max_chars' characters
 *          (read  as: up to `2 * max_chars' bytes) to `buf'! */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsncpy)(unsigned char *buf,
                                    unsigned char const *src,
                                    size_t max_chars) {
	return libc__mbsncpy_l(buf, src, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(LIBCCALL libc__mbsnextc)(unsigned char const *str) {
	return libc__mbsnextc_l(str, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnicmp)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     size_t max_chars) {
	return libc__mbsnicmp_l(lhs, rhs, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnicoll)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t max_chars) {
	return libc__mbsnicoll_l(lhs, rhs, max_chars, NULL);
}
/* Returns pointer to `max_chars'th character of `str' (or strend() when `max_chars > _mbslen_l(str)') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsninc)(unsigned char const *str,
                                    size_t max_chars) {
	return libc__mbsninc_l(str, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnset_s)(unsigned char *buf,
                                      size_t true_bufsize,
                                      unsigned int ch,
                                      size_t max_chars) {
	return libc__mbsnset_s_l(buf, true_bufsize, ch, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnset)(unsigned char *buf,
                                    unsigned int ch,
                                    size_t max_chars) {
	return libc__mbsnset_l(buf, ch, max_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbspbrk)(unsigned char const *haystack,
                                    unsigned char const *accept) {
	return libc__mbspbrk_l(haystack, accept, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsrchr)(unsigned char const *haystack,
                                    unsigned int needle) {
	return libc__mbsrchr_l(haystack, needle, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsrev)(unsigned char *buf) {
	return libc__mbsrev_l(buf, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsset_s)(unsigned char *buf,
                                     size_t true_bufsize,
                                     unsigned int ch) {
	return libc__mbsset_s_l(buf, true_bufsize, ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsset)(unsigned char *buf,
                                   unsigned int ch) {
	return libc__mbsset_l(buf, ch, NULL);
}
/* Returs a byte-offset */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsspn)(unsigned char const *haystack,
                                   unsigned char const *accept) {
	return libc__mbsspn_l(haystack, accept, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsspnp)(unsigned char const *haystack,
                                    unsigned char const *accept) {
	return libc__mbsspnp_l(haystack, accept, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsstr)(unsigned char const *haystack,
                                   unsigned char const *needle) {
	return libc__mbsstr_l(haystack, needle, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbstok)(unsigned char *str,
                                   unsigned char const *delim) {
	return libc__mbstok_l(str, delim, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((2, 3)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbstok_s)(unsigned char *str,
                                     unsigned char const *delim,
                                     unsigned char **__restrict save_ptr) {
	return libc__mbstok_s_l(str, delim, save_ptr, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsupr_s)(unsigned char *buf,
                                     size_t true_bufsize) {
	return libc__mbsupr_s_l(buf, true_bufsize, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbclen)(unsigned char const *str) {
	return libc__mbclen_l(str, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL libc__mbccpy)(unsigned char *dst,
                                   unsigned char const *src) {
	libc__mbccpy_l(dst, src, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 4)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbccpy_s)(unsigned char *dst,
                                     size_t true_dstsize,
                                     int *p_copied,
                                     unsigned char const *src) {
	return libc__mbccpy_s_l(dst, true_dstsize, p_copied, src, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcalnum)(unsigned int ch) {
	return libc__ismbcalnum_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcalpha)(unsigned int ch) {
	return libc__ismbcalpha_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcdigit)(unsigned int ch) {
	return libc__ismbcdigit_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcgraph)(unsigned int ch) {
	return libc__ismbcgraph_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbclegal)(unsigned int ch) {
	return libc__ismbclegal_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbclower)(unsigned int ch) {
	return libc__ismbclower_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcprint)(unsigned int ch) {
	return libc__ismbcprint_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcpunct)(unsigned int ch) {
	return libc__ismbcpunct_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcblank)(unsigned int ch) {
	return libc__ismbcblank_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcspace)(unsigned int ch) {
	return libc__ismbcspace_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcupper)(unsigned int ch) {
	return libc__ismbcupper_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctolower)(unsigned int ch) {
	return libc__mbctolower_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctoupper)(unsigned int ch) {
	return libc__mbctoupper_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbchira)(unsigned int ch) {
	return libc__ismbchira_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbckata)(unsigned int ch) {
	return libc__ismbckata_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcsymbol)(unsigned int ch) {
	return libc__ismbcsymbol_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl0)(unsigned int ch) {
	return libc__ismbcl0_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl1)(unsigned int ch) {
	return libc__ismbcl1_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl2)(unsigned int ch) {
	return libc__ismbcl2_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbcjistojms)(unsigned int ch) {
	return libc__mbcjistojms_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbcjmstojis)(unsigned int ch) {
	return libc__mbcjmstojis_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctohira)(unsigned int ch) {
	return libc__mbctohira_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctokata)(unsigned int ch) {
	return libc__mbctokata_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbblead)(unsigned int ch) {
	return libc__ismbblead_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbtrail)(unsigned int ch) {
	return libc__ismbbtrail_l(ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__ismbslead)(unsigned char const *str,
                                      unsigned char const *pos) {
	return libc__ismbslead_l(str, pos, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__ismbstrail)(unsigned char const *str,
                                       unsigned char const *pos) {
	return libc__ismbstrail_l(str, pos, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbscat_l)(unsigned char *__restrict dst,
                                     unsigned char const *__restrict src,
                                     locale_t locale) {
	(void)locale;
	return (unsigned char *)libc_strcat((char *)dst, (char const *)src);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbscpy_l)(unsigned char *__restrict dst,
                                     unsigned char const *__restrict src,
                                     locale_t locale) {
	(void)locale;
	return (unsigned char *)libc_strcpy((char *)dst, (char const *)src);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) void
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
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
	/* Really weird quirk: until this point, `max_chars' were countered
	 * in chars, but this zero-padding (which is also done by DOS), would
	 * mean that it's suddenly counted in characters... */
	libc_bzero(dst, max_chars);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbscoll_l)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbscmp_l(lhs, rhs, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsicoll_l)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbscmp_l(lhs, rhs, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsncoll_l)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       size_t max_chars,
                                       locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbsncmp_l(lhs, rhs, max_chars, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnicoll_l)(unsigned char const *lhs,
                                        unsigned char const *rhs,
                                        size_t max_chars,
                                        locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbsnicmp_l(lhs, rhs, max_chars, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcoll_l)(unsigned char const *lhs,
                                        unsigned char const *rhs,
                                        size_t max_bytes,
                                        locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbsnbcmp_l(lhs, rhs, max_bytes, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicoll_l)(unsigned char const *lhs,
                                         unsigned char const *rhs,
                                         size_t max_bytes,
                                         locale_t locale) {
	/* XXX: Implement properly? */
	return libc__mbsnbicmp_l(lhs, rhs, max_bytes, locale);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL WUNUSED NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsinc_l)(unsigned char const *ptr,
                                     locale_t locale) {
	if (libc__ismbblead_l(*ptr++, locale)) {
		if (*ptr)
			++ptr;
	}
	return (unsigned char *)ptr;
}
/* Returns pointer to `max_chars'th character of `str' (or strend() when `max_chars > _mbslen_l(str)') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsninc_l)(unsigned char const *str,
                                      size_t max_chars,
                                      locale_t locale) {
	if (str != NULL)
		str += libc__mbsnbcnt_l(str, max_chars, locale);
	return (unsigned char *)str;
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc__mbscspn_l)(unsigned char const *haystack,
                                      unsigned char const *reject,
                                      locale_t locale) {
	unsigned char const *iter = haystack;
	for (;;) {
		uint16_t ch;
		ch = *iter++;
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(LIBCCALL libc__mbsnextc_l)(unsigned char const *str,
                                       locale_t locale) {
	uint16_t result = str[0];
	if (libc__ismbblead_l(result, locale))
		result = (result << 8) | str[1];
	return result;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) size_t
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsspnp_l)(unsigned char const *haystack,
                                      unsigned char const *accept,
                                      locale_t locale) {
	haystack += libc__mbsspn_l(haystack, accept, locale);
	if (*haystack == 0)
		haystack = NULL;
	return (unsigned char *)haystack;
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbstok_l)(unsigned char *str,
                                     unsigned char const *delim,
                                     locale_t locale) {
	static unsigned char *save_ptr = NULL;
	return libc__mbstok_s_l(str, delim, &save_ptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((2, 3)) unsigned char *
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbclen_l)(unsigned char const *str,
                                     locale_t locale) {
	size_t result = 1;
	if (libc__ismbblead_l(str[0], locale) && str[1])
		result = 2;
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscat_s_l)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned char const *src,
                                       locale_t locale) {
	(void)locale;
	return libc_strcat_s((char *)buf, true_bufsize, (char const *)src);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscpy_s_l)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned char const *src,
                                       locale_t locale) {
	(void)locale;
	return libc_strcpy_s((char *)buf, true_bufsize, (char const *)src);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbslwr_s_l)(unsigned char *buf,
                                       size_t true_bufsize,
                                       locale_t locale) {
	if (!buf || libc_strlen((char const *)buf) >= true_bufsize)
		return 22;
	libc__mbslwr_l(buf, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsupr_s_l)(unsigned char *buf,
                                       size_t true_bufsize,
                                       locale_t locale) {
	if (!buf || libc_strlen((char const *)buf) >= true_bufsize)
		return 22;
	libc__mbsupr_l(buf, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncat_s_l)(unsigned char *buf,
                                        size_t true_bufsize,
                                        unsigned char const *src,
                                        size_t max_chars,
                                        locale_t locale) {
	if (max_chars && (!buf || !src ||
	                  true_bufsize <= (libc_strlen((char const *)buf) +
	                                   libc__mbsnbcnt_l(src, max_chars, locale))))
		return 22;
	libc__mbsncat_l(buf, src, max_chars, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
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
	/* Really weird quirk: until this point, `max_chars' were countered
	 * in chars, but this zero-padding (which is also done by DOS), would
	 * mean that it's suddenly counted in characters... */
	libc_bzero(buf, max_chars);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsset_s_l)(unsigned char *buf,
                                       size_t true_bufsize,
                                       unsigned int ch,
                                       locale_t locale) {
	if (!buf || true_bufsize == libc_strnlen((char const *)buf, true_bufsize))
		return 22;
	libc__mbsset_l(buf, ch, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 4)) errno_t
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
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
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_mbbtombc, libc__mbbtombc);
DEFINE_PUBLIC_ALIAS(_mbbtype, libc__mbbtype);
DEFINE_PUBLIC_ALIAS(_mbctombb, libc__mbctombb);
DEFINE_PUBLIC_ALIAS(_mbsbtype, libc__mbsbtype);
DEFINE_PUBLIC_ALIAS(_mbscat_s, libc__mbscat_s);
DEFINE_PUBLIC_ALIAS(_mbschr, libc__mbschr);
DEFINE_PUBLIC_ALIAS(_mbscmp, libc__mbscmp);
DEFINE_PUBLIC_ALIAS(_mbscoll, libc__mbscoll);
DEFINE_PUBLIC_ALIAS(_mbscpy_s, libc__mbscpy_s);
DEFINE_PUBLIC_ALIAS(_mbscspn, libc__mbscspn);
DEFINE_PUBLIC_ALIAS(_mbsdec, libc__mbsdec);
DEFINE_PUBLIC_ALIAS(_mbsicmp, libc__mbsicmp);
DEFINE_PUBLIC_ALIAS(_mbsicoll, libc__mbsicoll);
DEFINE_PUBLIC_ALIAS(_mbsinc, libc__mbsinc);
DEFINE_PUBLIC_ALIAS(_mbslen, libc__mbslen);
DEFINE_PUBLIC_ALIAS(_mbsnlen, libc__mbsnlen);
DEFINE_PUBLIC_ALIAS(_mbslwr_s, libc__mbslwr_s);
DEFINE_PUBLIC_ALIAS(_mbslwr, libc__mbslwr);
DEFINE_PUBLIC_ALIAS(_mbsupr, libc__mbsupr);
DEFINE_PUBLIC_ALIAS(_mbsnbcat_s, libc__mbsnbcat_s);
DEFINE_PUBLIC_ALIAS(_mbsnbcat, libc__mbsnbcat);
DEFINE_PUBLIC_ALIAS(_mbsnbcmp, libc__mbsnbcmp);
DEFINE_PUBLIC_ALIAS(_mbsnbcoll, libc__mbsnbcoll);
DEFINE_PUBLIC_ALIAS(_mbsnbcnt, libc__mbsnbcnt);
DEFINE_PUBLIC_ALIAS(_mbsnbcpy_s, libc__mbsnbcpy_s);
DEFINE_PUBLIC_ALIAS(_mbsnbcpy, libc__mbsnbcpy);
DEFINE_PUBLIC_ALIAS(_mbsnbicmp, libc__mbsnbicmp);
DEFINE_PUBLIC_ALIAS(_mbsnbicoll, libc__mbsnbicoll);
DEFINE_PUBLIC_ALIAS(_mbsnbset_s, libc__mbsnbset_s);
DEFINE_PUBLIC_ALIAS(_mbsnbset, libc__mbsnbset);
DEFINE_PUBLIC_ALIAS(_mbsncat_s, libc__mbsncat_s);
DEFINE_PUBLIC_ALIAS(_mbsncat, libc__mbsncat);
DEFINE_PUBLIC_ALIAS(_mbsnccnt, libc__mbsnccnt);
DEFINE_PUBLIC_ALIAS(_mbsncmp, libc__mbsncmp);
DEFINE_PUBLIC_ALIAS(_mbsncoll, libc__mbsncoll);
DEFINE_PUBLIC_ALIAS(_mbsncpy_s, libc__mbsncpy_s);
DEFINE_PUBLIC_ALIAS(_mbsncpy, libc__mbsncpy);
DEFINE_PUBLIC_ALIAS(_mbsnextc, libc__mbsnextc);
DEFINE_PUBLIC_ALIAS(_mbsnicmp, libc__mbsnicmp);
DEFINE_PUBLIC_ALIAS(_mbsnicoll, libc__mbsnicoll);
DEFINE_PUBLIC_ALIAS(_mbsninc, libc__mbsninc);
DEFINE_PUBLIC_ALIAS(_mbsnset_s, libc__mbsnset_s);
DEFINE_PUBLIC_ALIAS(_mbsnset, libc__mbsnset);
DEFINE_PUBLIC_ALIAS(_mbspbrk, libc__mbspbrk);
DEFINE_PUBLIC_ALIAS(_mbsrchr, libc__mbsrchr);
DEFINE_PUBLIC_ALIAS(_mbsrev, libc__mbsrev);
DEFINE_PUBLIC_ALIAS(_mbsset_s, libc__mbsset_s);
DEFINE_PUBLIC_ALIAS(_mbsset, libc__mbsset);
DEFINE_PUBLIC_ALIAS(_mbsspn, libc__mbsspn);
DEFINE_PUBLIC_ALIAS(_mbsspnp, libc__mbsspnp);
DEFINE_PUBLIC_ALIAS(_mbsstr, libc__mbsstr);
DEFINE_PUBLIC_ALIAS(_mbstok, libc__mbstok);
DEFINE_PUBLIC_ALIAS(_mbstok_s, libc__mbstok_s);
DEFINE_PUBLIC_ALIAS(_mbsupr_s, libc__mbsupr_s);
DEFINE_PUBLIC_ALIAS(_mbclen, libc__mbclen);
DEFINE_PUBLIC_ALIAS(_mbccpy, libc__mbccpy);
DEFINE_PUBLIC_ALIAS(_mbccpy_s, libc__mbccpy_s);
DEFINE_PUBLIC_ALIAS(_ismbcalnum, libc__ismbcalnum);
DEFINE_PUBLIC_ALIAS(_ismbcalpha, libc__ismbcalpha);
DEFINE_PUBLIC_ALIAS(_ismbcdigit, libc__ismbcdigit);
DEFINE_PUBLIC_ALIAS(_ismbcgraph, libc__ismbcgraph);
DEFINE_PUBLIC_ALIAS(_ismbclegal, libc__ismbclegal);
DEFINE_PUBLIC_ALIAS(_ismbclower, libc__ismbclower);
DEFINE_PUBLIC_ALIAS(_ismbcprint, libc__ismbcprint);
DEFINE_PUBLIC_ALIAS(_ismbcpunct, libc__ismbcpunct);
DEFINE_PUBLIC_ALIAS(_ismbcblank, libc__ismbcblank);
DEFINE_PUBLIC_ALIAS(_ismbcspace, libc__ismbcspace);
DEFINE_PUBLIC_ALIAS(_ismbcupper, libc__ismbcupper);
DEFINE_PUBLIC_ALIAS(_mbctolower, libc__mbctolower);
DEFINE_PUBLIC_ALIAS(_mbctoupper, libc__mbctoupper);
DEFINE_PUBLIC_ALIAS(_ismbchira, libc__ismbchira);
DEFINE_PUBLIC_ALIAS(_ismbckata, libc__ismbckata);
DEFINE_PUBLIC_ALIAS(_ismbcsymbol, libc__ismbcsymbol);
DEFINE_PUBLIC_ALIAS(_ismbcl0, libc__ismbcl0);
DEFINE_PUBLIC_ALIAS(_ismbcl1, libc__ismbcl1);
DEFINE_PUBLIC_ALIAS(_ismbcl2, libc__ismbcl2);
DEFINE_PUBLIC_ALIAS(_mbcjistojms, libc__mbcjistojms);
DEFINE_PUBLIC_ALIAS(_mbcjmstojis, libc__mbcjmstojis);
DEFINE_PUBLIC_ALIAS(_mbctohira, libc__mbctohira);
DEFINE_PUBLIC_ALIAS(_mbctokata, libc__mbctokata);
DEFINE_PUBLIC_ALIAS(_ismbblead, libc__ismbblead);
DEFINE_PUBLIC_ALIAS(_ismbbtrail, libc__ismbbtrail);
DEFINE_PUBLIC_ALIAS(_ismbslead, libc__ismbslead);
DEFINE_PUBLIC_ALIAS(_ismbstrail, libc__ismbstrail);
DEFINE_PUBLIC_ALIAS(_mbscat_l, libc__mbscat_l);
DEFINE_PUBLIC_ALIAS(_mbscpy_l, libc__mbscpy_l);
DEFINE_PUBLIC_ALIAS(_mbccpy_l, libc__mbccpy_l);
DEFINE_PUBLIC_ALIAS(_mbsncpy_l, libc__mbsncpy_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcpy_l, libc__mbsnbcpy_l);
DEFINE_PUBLIC_ALIAS(_mbschr_l, libc__mbschr_l);
DEFINE_PUBLIC_ALIAS(_mbscoll_l, libc__mbscoll_l);
DEFINE_PUBLIC_ALIAS(_mbsicoll_l, libc__mbsicoll_l);
DEFINE_PUBLIC_ALIAS(_mbsncoll_l, libc__mbsncoll_l);
DEFINE_PUBLIC_ALIAS(_mbsnicoll_l, libc__mbsnicoll_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcoll_l, libc__mbsnbcoll_l);
DEFINE_PUBLIC_ALIAS(_mbsnbicoll_l, libc__mbsnbicoll_l);
DEFINE_PUBLIC_ALIAS(_mbslwr_l, libc__mbslwr_l);
DEFINE_PUBLIC_ALIAS(_mbsupr_l, libc__mbsupr_l);
DEFINE_PUBLIC_ALIAS(_mbsinc_l, libc__mbsinc_l);
DEFINE_PUBLIC_ALIAS(_mbsninc_l, libc__mbsninc_l);
DEFINE_PUBLIC_ALIAS(_mbsdec_l, libc__mbsdec_l);
DEFINE_PUBLIC_ALIAS(_mbscspn_l, libc__mbscspn_l);
DEFINE_PUBLIC_ALIAS(_mbslen_l, libc__mbslen_l);
DEFINE_PUBLIC_ALIAS(_mbsnlen_l, libc__mbsnlen_l);
DEFINE_PUBLIC_ALIAS(_mbsncat_l, libc__mbsncat_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcat_l, libc__mbsnbcat_l);
DEFINE_PUBLIC_ALIAS(_mbsnccnt_l, libc__mbsnccnt_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcnt_l, libc__mbsnbcnt_l);
DEFINE_PUBLIC_ALIAS(_mbscmp_l, libc__mbscmp_l);
DEFINE_PUBLIC_ALIAS(_mbsicmp_l, libc__mbsicmp_l);
DEFINE_PUBLIC_ALIAS(_mbsncmp_l, libc__mbsncmp_l);
DEFINE_PUBLIC_ALIAS(_mbsnicmp_l, libc__mbsnicmp_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcmp_l, libc__mbsnbcmp_l);
DEFINE_PUBLIC_ALIAS(_mbsnbicmp_l, libc__mbsnbicmp_l);
DEFINE_PUBLIC_ALIAS(_mbsnextc_l, libc__mbsnextc_l);
DEFINE_PUBLIC_ALIAS(_mbspbrk_l, libc__mbspbrk_l);
DEFINE_PUBLIC_ALIAS(_mbsrchr_l, libc__mbsrchr_l);
DEFINE_PUBLIC_ALIAS(_mbsrev_l, libc__mbsrev_l);
DEFINE_PUBLIC_ALIAS(_mbsset_l, libc__mbsset_l);
DEFINE_PUBLIC_ALIAS(_mbsnset_l, libc__mbsnset_l);
DEFINE_PUBLIC_ALIAS(_mbsnbset_l, libc__mbsnbset_l);
DEFINE_PUBLIC_ALIAS(_mbsspn_l, libc__mbsspn_l);
DEFINE_PUBLIC_ALIAS(_mbsspnp_l, libc__mbsspnp_l);
DEFINE_PUBLIC_ALIAS(_mbsstr_l, libc__mbsstr_l);
DEFINE_PUBLIC_ALIAS(_mbstok_l, libc__mbstok_l);
DEFINE_PUBLIC_ALIAS(_mbstok_s_l, libc__mbstok_s_l);
DEFINE_PUBLIC_ALIAS(_mbclen_l, libc__mbclen_l);
DEFINE_PUBLIC_ALIAS(_mbscat_s_l, libc__mbscat_s_l);
DEFINE_PUBLIC_ALIAS(_mbscpy_s_l, libc__mbscpy_s_l);
DEFINE_PUBLIC_ALIAS(_mbslwr_s_l, libc__mbslwr_s_l);
DEFINE_PUBLIC_ALIAS(_mbsupr_s_l, libc__mbsupr_s_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcat_s_l, libc__mbsnbcat_s_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcpy_s_l, libc__mbsnbcpy_s_l);
DEFINE_PUBLIC_ALIAS(_mbsnbset_s_l, libc__mbsnbset_s_l);
DEFINE_PUBLIC_ALIAS(_mbsncat_s_l, libc__mbsncat_s_l);
DEFINE_PUBLIC_ALIAS(_mbsncpy_s_l, libc__mbsncpy_s_l);
DEFINE_PUBLIC_ALIAS(_mbsnset_s_l, libc__mbsnset_s_l);
DEFINE_PUBLIC_ALIAS(_mbsset_s_l, libc__mbsset_s_l);
DEFINE_PUBLIC_ALIAS(_mbccpy_s_l, libc__mbccpy_s_l);
DEFINE_PUBLIC_ALIAS(_ismbslead_l, libc__ismbslead_l);
DEFINE_PUBLIC_ALIAS(_ismbstrail_l, libc__ismbstrail_l);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_MBSTRING_C */
