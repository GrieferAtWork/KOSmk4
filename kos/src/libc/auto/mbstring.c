/* HASH CRC-32:0xfaff1e0a */
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") int
NOTHROW_NCX(LIBCCALL libc__mbsbtype)(unsigned char const *str,
                                     size_t pos) {
	return libc__mbsbtype_l(str, pos, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscat_s)(unsigned char *buf,
                                     size_t bufsize,
                                     unsigned char const *src) {
	return libc__mbscat_s_l(buf, bufsize, src, NULL);
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
                                     size_t bufsize,
                                     unsigned char const *src) {
	return libc__mbscpy_s_l(buf, bufsize, src, NULL);
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
                                    size_t maxlen) {
	return libc__mbsnlen_l(str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbslwr_s)(unsigned char *buf,
                                     size_t buflen) {
	return libc__mbslwr_s_l(buf, buflen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbslwr)(unsigned char *buf) {
	return libc__mbslwr_l(buf, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcat_s)(unsigned char *buf,
                                       size_t bufsize,
                                       unsigned char const *src,
                                       size_t maxlen) {
	return libc__mbsnbcat_s_l(buf, bufsize, src, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbcat)(unsigned char *buf,
                                     unsigned char const *src,
                                     size_t srclen) {
	return libc__mbsnbcat_l(buf, src, srclen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcmp)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     size_t maxlen) {
	return libc__mbsnbcmp_l(lhs, rhs, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcoll)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t maxlen) {
	return libc__mbsnbcoll_l(lhs, rhs, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcnt)(unsigned char const *str,
                                     size_t maxlen) {
	return libc__mbsnbcnt_l(str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_s)(unsigned char *buf,
                                       size_t bufsize,
                                       unsigned char const *src,
                                       size_t srclen) {
	return libc__mbsnbcpy_s_l(buf, bufsize, src, srclen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbcpy)(unsigned char *buf,
                                     unsigned char const *src,
                                     size_t srclen) {
	return libc__mbsnbcpy_l(buf, src, srclen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicmp)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t maxlen) {
	return libc__mbsnbicmp_l(lhs, rhs, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicoll)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       size_t maxlen) {
	return libc__mbsnbicoll_l(lhs, rhs, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbset_s)(unsigned char *buf,
                                       size_t bufsize,
                                       unsigned int ch,
                                       size_t num_chars) {
	return libc__mbsnbset_s_l(buf, bufsize, ch, num_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbset)(unsigned char *buf,
                                     unsigned int ch,
                                     size_t buflen) {
	return libc__mbsnbset_l(buf, ch, buflen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncat_s)(unsigned char *buf,
                                      size_t bufsize,
                                      unsigned char const *src,
                                      size_t srclen) {
	return libc__mbsncat_s_l(buf, bufsize, src, srclen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsncat)(unsigned char *buf,
                                    unsigned char const *src,
                                    size_t srclen) {
	return libc__mbsncat_l(buf, src, srclen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnccnt)(unsigned char const *str,
                                     size_t maxlen) {
	return libc__mbsnccnt_l(str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsncmp)(unsigned char const *lhs,
                                    unsigned char const *rhs,
                                    size_t maxlen) {
	return libc__mbsncmp_l(lhs, rhs, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsncoll)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     size_t maxlen) {
	return libc__mbsncoll_l(lhs, rhs, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncpy_s)(unsigned char *buf,
                                      size_t bufsize,
                                      unsigned char const *src,
                                      size_t srclen) {
	return libc__mbsncpy_s_l(buf, bufsize, src, srclen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsncpy)(unsigned char *buf,
                                    unsigned char const *src,
                                    size_t srclen) {
	return libc__mbsncpy_l(buf, src, srclen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(LIBCCALL libc__mbsnextc)(unsigned char const *str) {
	return libc__mbsnextc_l(str, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnicmp)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     size_t maxlen) {
	return libc__mbsnicmp_l(lhs, rhs, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnicoll)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t maxlen) {
	return libc__mbsnicoll_l(lhs, rhs, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsninc)(unsigned char const *str,
                                    size_t maxlen) {
	return libc__mbsninc_l(str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnset_s)(unsigned char *buf,
                                      size_t bufsize,
                                      unsigned int ch,
                                      size_t num_chars) {
	return libc__mbsnset_s_l(buf, bufsize, ch, num_chars, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnset)(unsigned char *buf,
                                    unsigned int ch,
                                    size_t maxlen) {
	return libc__mbsnset_l(buf, ch, maxlen, NULL);
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
                                     size_t bufsize,
                                     unsigned int ch) {
	return libc__mbsset_s_l(buf, bufsize, ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsset)(unsigned char *buf,
                                   unsigned int ch) {
	return libc__mbsset_l(buf, ch, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsspn)(unsigned char const *haystack,
                                   unsigned char const *accept) {
	return libc__mbsspn_l(haystack, accept, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsspnp)(unsigned char const *lhs,
                                    unsigned char const *rhs) {
	return libc__mbsspnp_l(lhs, rhs, NULL);
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
                                     size_t bufsize) {
	return libc__mbsupr_s_l(buf, bufsize, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsupr)(unsigned char *buf) {
	return libc__mbsupr_l(buf, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbclen)(unsigned char const *str) {
	return libc__mbclen_l(str, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL libc__mbccpy)(unsigned char *buf,
                                   unsigned char const *src) {
	libc__mbccpy_l(buf, src, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 4)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbccpy_s)(unsigned char *buf,
                                     size_t bufsize,
                                     int *p_copied,
                                     unsigned char const *src) {
	return libc__mbccpy_s_l(buf, bufsize, p_copied, src, NULL);
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
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbstok_l)(unsigned char *str,
                                     unsigned char const *delim,
                                     locale_t locale) {
	static unsigned char *save_ptr = NULL;
	return libc__mbstok_s_l(str, delim, &save_ptr, locale);
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
DEFINE_PUBLIC_ALIAS(_mbsupr, libc__mbsupr);
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
DEFINE_PUBLIC_ALIAS(_mbstok_l, libc__mbstok_l);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_MBSTRING_C */
