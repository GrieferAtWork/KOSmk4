/* HASH CRC-32:0x9ef2a76c */
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
#ifndef GUARD_LIBC_USER_MBSTRING_H
#define GUARD_LIBC_USER_MBSTRING_H 1

#include "../api.h"
#include "../auto/mbstring.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <mbstring.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbbtombc_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__mbbtype_l)(unsigned char ch, int ctype, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctombb_l)(unsigned int ch, locale_t locale);
INTDEF int NOTHROW_NCX(LIBCCALL libc__mbsbtype_l)(unsigned char const *str, size_t pos, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__mbscat_s_l)(unsigned char *buf, size_t bufsize, unsigned char const *src, locale_t locale);
INTDEF WUNUSED NONNULL((1)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbschr_l)(unsigned char const *__restrict haystack, unsigned int needle, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbscmp_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbscoll_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__mbscpy_s_l)(unsigned char *buf, size_t bufsize, unsigned char const *src, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc__mbscspn_l)(unsigned char const *haystack, unsigned char const *reject, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsdec_l)(unsigned char const *start, unsigned char const *pos, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsicmp_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsicoll_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
INTDEF WUNUSED NONNULL((1)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsinc_l)(unsigned char const *ptr, locale_t locale);
INTDEF WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbslen_l)(unsigned char const *str, locale_t locale);
INTDEF WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbsnlen_l)(unsigned char const *str, size_t maxlen, locale_t locale);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__mbslwr_s_l)(unsigned char *buf, size_t buflen, locale_t locale);
INTDEF NONNULL((1)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbslwr_l)(unsigned char *buf, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnbcat_s_l)(unsigned char *buf, size_t bufsize, unsigned char const *src, size_t maxlen, locale_t locale);
INTDEF NONNULL((1, 2)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnbcat_l)(unsigned char *buf, unsigned char const *src, size_t srclen, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbcmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t maxlen, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbcoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t maxlen, locale_t locale);
INTDEF WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbsnbcnt_l)(unsigned char const *str, size_t maxlen, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_s_l)(unsigned char *buf, size_t bufsize, unsigned char const *src, size_t srclen, locale_t locale);
INTDEF NONNULL((1, 2)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_l)(unsigned char *buf, unsigned char const *src, size_t srclen, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbicmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t maxlen, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnbicoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t maxlen, locale_t locale);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnbset_s_l)(unsigned char *buf, size_t bufsize, unsigned int ch, size_t num_chars, locale_t locale);
INTDEF NONNULL((1)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnbset_l)(unsigned char *buf, unsigned int ch, size_t buflen, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__mbsncat_s_l)(unsigned char *buf, size_t bufsize, unsigned char const *src, size_t srclen, locale_t locale);
INTDEF NONNULL((1, 2)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsncat_l)(unsigned char *buf, unsigned char const *src, size_t srclen, locale_t locale);
INTDEF WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbsnccnt_l)(unsigned char const *str, size_t maxlen, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsncmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t maxlen, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsncoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t maxlen, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__mbsncpy_s_l)(unsigned char *buf, size_t bufsize, unsigned char const *src, size_t maxlen, locale_t locale);
INTDEF NONNULL((1, 2)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsncpy_l)(unsigned char *buf, unsigned char const *src, size_t srclen, locale_t locale);
INTDEF WUNUSED NONNULL((1)) unsigned int NOTHROW_NCX(LIBCCALL libc__mbsnextc_l)(unsigned char const *str, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnicmp_l)(unsigned char const *lhs, unsigned char const *rhs, size_t maxlen, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__mbsnicoll_l)(unsigned char const *lhs, unsigned char const *rhs, size_t maxlen, locale_t locale);
INTDEF WUNUSED NONNULL((1)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsninc_l)(unsigned char const *str, size_t maxlen, locale_t locale);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__mbsnset_s_l)(unsigned char *buf, size_t bufsize, unsigned int ch, size_t maxlen, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsnset_l)(unsigned char *buf, unsigned int ch, size_t maxlen, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbspbrk_l)(unsigned char const *haystack, unsigned char const *accept, locale_t locale);
INTDEF WUNUSED NONNULL((1)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsrchr_l)(unsigned char const *haystack, unsigned int needle, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsrev_l)(unsigned char *buf, locale_t locale);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__mbsset_s_l)(unsigned char *buf, size_t bufsize, unsigned int ch, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsset_l)(unsigned char *buf, unsigned int ch, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc__mbsspn_l)(unsigned char const *haystack, unsigned char const *accept, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsspnp_l)(unsigned char const *lhs, unsigned char const *rhs, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsstr_l)(unsigned char const *haystack, unsigned char const *needle, locale_t locale);
INTDEF WUNUSED NONNULL((2, 3)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbstok_s_l)(unsigned char *str, unsigned char const *delim, unsigned char **__restrict save_ptr, locale_t locale);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__mbsupr_s_l)(unsigned char *buf, size_t bufsize, locale_t locale);
INTDEF ATTR_RETNONNULL NONNULL((1)) unsigned char *NOTHROW_NCX(LIBCCALL libc__mbsupr_l)(unsigned char *buf, locale_t locale);
INTDEF WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__mbclen_l)(unsigned char const *str, locale_t locale);
INTDEF NONNULL((1, 2)) void NOTHROW_NCX(LIBCCALL libc__mbccpy_l)(unsigned char *buf, unsigned char const *src, locale_t locale);
INTDEF NONNULL((1, 4)) errno_t NOTHROW_NCX(LIBCCALL libc__mbccpy_s_l)(unsigned char *buf, size_t bufsize, int *p_copied, unsigned char const *src, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcalnum_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcalpha_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcdigit_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcgraph_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbclegal_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbclower_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcprint_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcpunct_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcblank_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcspace_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcupper_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctolower_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctoupper_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbchira_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbckata_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcsymbol_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl0_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl1_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl2_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbcjistojms_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbcjmstojis_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctohira_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctokata_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbblead_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbtrail_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__ismbslead_l)(unsigned char const *str, unsigned char const *pos, locale_t locale);
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc__ismbstrail_l)(unsigned char const *str, unsigned char const *pos, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_MBSTRING_H */
