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
%(c_prefix){
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/mbstring.h) */
/* (#) Portability: Windows Kits (/ucrt/mbstring.h) */
}

%[default:section(".text.crt.dos.string.memory")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#ifdef __USE_DOS
#include <crtdefs.h>
#endif /* __USE_DOS */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __ernno_t_defined
#define __ernno_t_defined
typedef __errno_t errno_t;
#endif /* !__ernno_t_defined */

#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
#define __CORRECT_ISO_CPP_MBSTRING_H_PROTO
#endif /* __CORRECT_ISO_CPP_STRING_H_PROTO */

}

_mbsdup([[nonnull]] unsigned char const *__restrict string)
	-> [[malloc/*((_mbslen(string) + 1) * sizeof(char))*/]] unsigned char *
	= strdup;

/************************************************************************/
/* Current-local functions                                              */
/************************************************************************/

[[wunused, requires_function(_mbbtombc_l)]]
unsigned int _mbbtombc(unsigned int ch) {
	return _mbbtombc_l(ch, NULL);
}

[[wunused, requires_function(_mbbtype_l)]]
int _mbbtype(unsigned char ch, int ctype) {
	return _mbbtype_l(ch, ctype, NULL);
}

[[wunused, requires_function(_mbctombb_l)]]
unsigned int _mbctombb(unsigned int ch) {
	return _mbctombb_l(ch, NULL);
}

[[requires_function(_mbsbtype_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsbtype([[inp_opt(pos)]] unsigned char const *str, size_t pos) {
	return _mbsbtype_l(str, pos, NULL);
}

[[requires_function(_mbscat_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbscat_s([[inoutp(bufsize)]] unsigned char *buf, size_t bufsize,
                  [[nonnull]] unsigned char const *src) {
	return _mbscat_s_l(buf, bufsize, src, NULL);
}

[[nonnull]]
unsigned char *_mbscat([[nonnull]] unsigned char *__restrict dst,
                       [[nonnull]] unsigned char const *__restrict src) = strcat;

[[wunused, requires_function(_mbschr_l)]]
unsigned char *_mbschr([[nonnull]] unsigned char const *__restrict haystack, unsigned int needle)
	[([[nonnull]] unsigned char *__restrict haystack, int needle): unsigned char *]
	[([[nonnull]] unsigned char const *__restrict haystack, int needle): unsigned char const *]
{
	return _mbschr_l(haystack, needle, NULL);
}

[[wunused, requires_function(_mbscmp_l)]]
int _mbscmp([[nonnull]] unsigned char const *lhs,
            [[nonnull]] unsigned char const *rhs) {
	return _mbscmp_l(lhs, rhs, NULL);
}

[[wunused, requires_function(_mbscoll_l)]]
int _mbscoll([[nonnull]] unsigned char const *lhs,
             [[nonnull]] unsigned char const *rhs) {
	return _mbscoll_l(lhs, rhs, NULL);
}

[[requires_function(_mbscpy_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbscpy_s([[outp(bufsize)]] unsigned char *buf, size_t bufsize,
                  [[nonnull]] unsigned char const *src) {
	return _mbscpy_s_l(buf, bufsize, src, NULL);
}

[[nonnull]]
unsigned char *_mbscpy([[nonnull]] unsigned char *__restrict dst,
                       [[nonnull]] unsigned char const *__restrict src) = strcpy;

[[wunused, requires_function(_mbscspn_l)]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbscspn([[nonnull]] unsigned char const *haystack,
                [[nonnull]] unsigned char const *reject) {
	return _mbscspn_l(haystack, reject, NULL);
}

[[wunused, requires_function(_mbsdec_l)]]
unsigned char *_mbsdec([[nonnull]] unsigned char const *start,
                       [[nonnull]] unsigned char const *pos) {
	return _mbsdec_l(start, pos, NULL);
}

[[wunused, requires_function(_mbsicmp_l)]]
int _mbsicmp([[nonnull]] unsigned char const *lhs,
             [[nonnull]] unsigned char const *rhs) {
	return _mbsicmp_l(lhs, rhs, NULL);
}

[[wunused, requires_function(_mbsicoll_l)]]
int _mbsicoll([[nonnull]] unsigned char const *lhs,
              [[nonnull]] unsigned char const *rhs) {
	return _mbsicoll_l(lhs, rhs, NULL);
}

[[wunused, requires_function(_mbsinc_l)]]
unsigned char *_mbsinc([[nonnull]] unsigned char const *ptr) {
	return _mbsinc_l(ptr, NULL);
}

[[wunused, requires_function(_mbslen_l)]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbslen([[nonnull]] unsigned char const *str) {
	return _mbslen_l(str, NULL);
}

[[wunused, requires_function(_mbsnlen_l)]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbsnlen([[nonnull]] unsigned char const *str, size_t maxlen) {
	return _mbsnlen_l(str, maxlen, NULL);
}

[[requires_function(_mbslwr_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbslwr_s([[inoutp(buflen)]] unsigned char *buf, size_t buflen) {
	return _mbslwr_s_l(buf, buflen, NULL);
}

[[requires_function(_mbslwr_l)]]
unsigned char *_mbslwr([[nonnull]] unsigned char *buf) {
	return _mbslwr_l(buf, NULL);
}

[[requires_function(_mbsnbcat_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsnbcat_s([[inoutp(bufsize)]] unsigned char *buf, size_t bufsize,
                    [[nonnull]] unsigned char const *src, size_t maxlen) {
	return _mbsnbcat_s_l(buf, bufsize, src, maxlen, NULL);
}

[[requires_function(_mbsnbcat_l)]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnbcat([[nonnull]] unsigned char *buf,
                         [[inp(srclen)]] unsigned char const *src, size_t srclen) {
	return _mbsnbcat_l(buf, src, srclen, NULL);
}

[[wunused, requires_function(_mbsnbcmp_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnbcmp([[nonnull]] unsigned char const *lhs,
              [[nonnull]] unsigned char const *rhs,
              size_t maxlen) {
	return _mbsnbcmp_l(lhs, rhs, maxlen, NULL);
}

[[wunused, requires_function(_mbsnbcoll_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnbcoll([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs,
               size_t maxlen) {
	return _mbsnbcoll_l(lhs, rhs, maxlen, NULL);
}

[[wunused, requires_function(_mbsnbcnt_l)]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbsnbcnt([[nonnull]] unsigned char const *str, size_t maxlen) {
	return _mbsnbcnt_l(str, maxlen, NULL);
}

[[requires_function(_mbsnbcpy_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsnbcpy_s([[outp(srclen)]] unsigned char *buf, size_t bufsize,
                    [[inp(srclen)]] unsigned char const *src, size_t srclen) {
	return _mbsnbcpy_s_l(buf, bufsize, src, srclen, NULL);
}

[[requires_function(_mbsnbcpy_l)]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnbcpy([[outp(srclen)]] unsigned char *buf,
                         [[inp(srclen)]] unsigned char const *src, size_t srclen) {
	return _mbsnbcpy_l(buf, src, srclen, NULL);
}

[[wunused, requires_function(_mbsnbicmp_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnbicmp([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs,
               size_t maxlen) {
	return _mbsnbicmp_l(lhs, rhs, maxlen, NULL);
}

[[wunused, requires_function(_mbsnbicoll_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnbicoll([[nonnull]] unsigned char const *lhs,
                [[nonnull]] unsigned char const *rhs,
                size_t maxlen) {
	return _mbsnbicoll_l(lhs, rhs, maxlen, NULL);
}

[[requires_function(_mbsnbset_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsnbset_s([[inoutp(bufsize)]] unsigned char *buf,
                    size_t bufsize, unsigned int ch, size_t num_chars) {
	return _mbsnbset_s_l(buf, bufsize, ch, num_chars, NULL);
}

[[requires_function(_mbsnbset_l)]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnbset([[inoutp(buflen)]] unsigned char *buf,
                         unsigned int ch, size_t buflen) {
	return _mbsnbset_l(buf, ch, buflen, NULL);
}

[[requires_function(_mbsncat_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsncat_s([[inoutp(bufsize)]] unsigned char *buf, size_t bufsize,
                   [[nonnull]] unsigned char const *src, size_t srclen) {
	return _mbsncat_s_l(buf, bufsize, src, srclen, NULL);
}

[[requires_function(_mbsncat_l)]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsncat([[nonnull]] unsigned char *buf,
                        [[inp(srclen)]] unsigned char const *src, size_t srclen) {
	return _mbsncat_l(buf, src, srclen, NULL);
}

[[wunused, requires_function(_mbsnccnt_l)]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbsnccnt([[nonnull]] unsigned char const *str, size_t maxlen) {
	return _mbsnccnt_l(str, maxlen, NULL);
}

[[wunused, requires_function(_mbsncmp_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsncmp([[nonnull]] unsigned char const *lhs,
             [[nonnull]] unsigned char const *rhs,
             size_t maxlen) {
	return _mbsncmp_l(lhs, rhs, maxlen, NULL);
}

%[insert:pp_if($has_function(_mbsncmp))]
%#define _mbccmp(lhs, rhs) _mbsncmp(lhs, rhs, 1)
%[insert:pp_endif]

[[wunused, requires_function(_mbsncoll_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsncoll([[nonnull]] unsigned char const *lhs,
              [[nonnull]] unsigned char const *rhs,
              size_t maxlen) {
	return _mbsncoll_l(lhs, rhs, maxlen, NULL);
}

[[requires_function(_mbsncpy_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsncpy_s([[outp(bufsize)]] unsigned char *buf, size_t bufsize,
                   [[inp(srclen)]] unsigned char const *src, size_t srclen) {
	return _mbsncpy_s_l(buf, bufsize, src, srclen, NULL);
}

[[requires_function(_mbsncpy_l)]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsncpy([[nonnull]] unsigned char *buf,
                        [[nonnull]] unsigned char const *src, size_t srclen) {
	return _mbsncpy_l(buf, src, srclen, NULL);
}

[[wunused, requires_function(_mbsnextc_l)]]
unsigned int _mbsnextc([[nonnull]] unsigned char const *str) {
	return _mbsnextc_l(str, NULL);
}

[[wunused, requires_function(_mbsnicmp_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnicmp([[nonnull]] unsigned char const *lhs,
              [[nonnull]] unsigned char const *rhs,
              size_t maxlen) {
	return _mbsnicmp_l(lhs, rhs, maxlen, NULL);
}

[[wunused, requires_function(_mbsnicoll_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnicoll([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs, size_t maxlen) {
	return _mbsnicoll_l(lhs, rhs, maxlen, NULL);
}

[[wunused, requires_function(_mbsninc_l)]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsninc([[nonnull]] unsigned char const *str, size_t maxlen) {
	return _mbsninc_l(str, maxlen, NULL);
}

[[requires_function(_mbsnset_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsnset_s([[inoutp(bufsize)]] unsigned char *buf,
                   size_t bufsize, unsigned int ch, size_t num_chars) {
	return _mbsnset_s_l(buf, bufsize, ch, num_chars, NULL);
}

[[nonnull, requires_function(_mbsnset_l)]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnset([[nonnull]] unsigned char *buf,
                        unsigned int ch, size_t maxlen) {
	return _mbsnset_l(buf, ch, maxlen, NULL);
}

[[wunused, requires_function(_mbspbrk_l)]]
unsigned char *_mbspbrk([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *accept)
	[([[nonnull]] unsigned char *haystack, [[nonnull]] unsigned char const *accept): unsigned char *]
	[([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *accept): unsigned char const *]
{
	return _mbspbrk_l(haystack, accept, NULL);
}

[[wunused, requires_function(_mbsrchr_l)]]
unsigned char *_mbsrchr([[nonnull]] unsigned char const *haystack, unsigned int needle)
	[([[nonnull]] unsigned char *__restrict haystack, unsigned int needle): unsigned char *]
	[([[nonnull]] unsigned char const *__restrict haystack, unsigned int needle): unsigned char const *]
{
	return _mbsrchr_l(haystack, needle, NULL);
}

[[nonnull, requires_function(_mbsrev_l)]]
unsigned char *_mbsrev([[nonnull]] unsigned char *buf) {
	return _mbsrev_l(buf, NULL);
}

[[requires_function(_mbsset_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsset_s([[inoutp(bufsize)]] unsigned char *buf,
                  size_t bufsize, unsigned int ch) {
	return _mbsset_s_l(buf, bufsize, ch, NULL);
}

[[nonnull, requires_function(_mbsset_l)]]
unsigned char *_mbsset([[nonnull]] unsigned char *buf, unsigned int ch) {
	return _mbsset_l(buf, ch, NULL);
}

[[wunused, requires_function(_mbsspn_l)]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbsspn([[nonnull]] unsigned char const *haystack,
               [[nonnull]] unsigned char const *accept) {
	return _mbsspn_l(haystack, accept, NULL);
}

[[wunused, requires_function(_mbsspnp_l)]]
unsigned char *_mbsspnp([[nonnull]] unsigned char const *lhs,
                        [[nonnull]] unsigned char const *rhs) {
	return _mbsspnp_l(lhs, rhs, NULL);
}

[[wunused, requires_function(_mbsstr_l)]]
unsigned char *_mbsstr([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *needle)
	[([[nonnull]] unsigned char *haystack, [[nonnull]] unsigned char const *needle): [[nullable]] unsigned char *]
	[([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *needle): [[nullable]] unsigned char const *]
{
	return _mbsstr_l(haystack, needle, NULL);
}

[[wunused, requires_function(_mbstok_l)]]
unsigned char *_mbstok([[nullable]] unsigned char *str,
                       [[nonnull]] unsigned char const *delim) {
	return _mbstok_l(str, delim, NULL);
}

[[wunused, requires_function(_mbstok_s_l)]]
unsigned char *_mbstok_s([[nullable]] unsigned char *str,
                         [[nonnull]] unsigned char const *delim,
                         [[nonnull]] unsigned char **__restrict save_ptr) {
	return _mbstok_s_l(str, delim, save_ptr, NULL);
}

[[requires_function(_mbsupr_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsupr_s([[inoutp(bufsize)]] unsigned char *buf, size_t bufsize) {
	return _mbsupr_s_l(buf, bufsize, NULL);
}

[[nonnull, requires_function(_mbsupr_l)]]
unsigned char *_mbsupr([[nonnull]] unsigned char *buf) {
	return _mbsupr_l(buf, NULL);
}

[[wunused, requires_function(_mbclen_l)]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbclen([[nonnull]] unsigned char const *str) {
	return _mbclen_l(str, NULL);
}

[[requires_function(_mbccpy_l)]]
void _mbccpy([[nonnull]] unsigned char *buf,
             [[nonnull]] unsigned char const *src) {
	_mbccpy_l(buf, src, NULL);
}

[[requires_function(_mbccpy_s_l)]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbccpy_s([[outp(bufsize)]] unsigned char *buf, size_t bufsize,
                  [[nullable]] int *p_copied, [[nonnull]] unsigned char const *src) {
	return _mbccpy_s_l(buf, bufsize, p_copied, src, NULL);
}


/************************************************************************/
/* Character-traits functions                                           */
/************************************************************************/

[[wunused, requires_function(_ismbcalnum_l)]]
int _ismbcalnum(unsigned int ch) {
	return _ismbcalnum_l(ch, NULL);
}

[[wunused, requires_function(_ismbcalpha_l)]]
int _ismbcalpha(unsigned int ch) {
	return _ismbcalpha_l(ch, NULL);
}

[[wunused, requires_function(_ismbcdigit_l)]]
int _ismbcdigit(unsigned int ch) {
	return _ismbcdigit_l(ch, NULL);
}

[[wunused, requires_function(_ismbcgraph_l)]]
int _ismbcgraph(unsigned int ch) {
	return _ismbcgraph_l(ch, NULL);
}

[[wunused, requires_function(_ismbclegal_l)]]
int _ismbclegal(unsigned int ch) {
	return _ismbclegal_l(ch, NULL);
}

[[wunused, requires_function(_ismbclower_l)]]
int _ismbclower(unsigned int ch) {
	return _ismbclower_l(ch, NULL);
}

[[wunused, requires_function(_ismbcprint_l)]]
int _ismbcprint(unsigned int ch) {
	return _ismbcprint_l(ch, NULL);
}

[[wunused, requires_function(_ismbcpunct_l)]]
int _ismbcpunct(unsigned int ch) {
	return _ismbcpunct_l(ch, NULL);
}

[[wunused, requires_function(_ismbcblank_l)]]
int _ismbcblank(unsigned int ch) {
	return _ismbcblank_l(ch, NULL);
}

[[wunused, requires_function(_ismbcspace_l)]]
int _ismbcspace(unsigned int ch) {
	return _ismbcspace_l(ch, NULL);
}

[[wunused, requires_function(_ismbcupper_l)]]
int _ismbcupper(unsigned int ch) {
	return _ismbcupper_l(ch, NULL);
}

[[wunused, requires_function(_mbctolower_l)]]
unsigned int _mbctolower(unsigned int ch) {
	return _mbctolower_l(ch, NULL);
}

[[wunused, requires_function(_mbctoupper_l)]]
unsigned int _mbctoupper(unsigned int ch) {
	return _mbctoupper_l(ch, NULL);
}

[[wunused, requires_function(_ismbchira_l)]]
int _ismbchira(unsigned int ch) {
	return _ismbchira_l(ch, NULL);
}

[[wunused, requires_function(_ismbckata_l)]]
int _ismbckata(unsigned int ch) {
	return _ismbckata_l(ch, NULL);
}

[[wunused, requires_function(_ismbcsymbol_l)]]
int _ismbcsymbol(unsigned int ch) {
	return _ismbcsymbol_l(ch, NULL);
}

[[wunused, requires_function(_ismbcl0_l)]]
int _ismbcl0(unsigned int ch) {
	return _ismbcl0_l(ch, NULL);
}

[[wunused, requires_function(_ismbcl1_l)]]
int _ismbcl1(unsigned int ch) {
	return _ismbcl1_l(ch, NULL);
}

[[wunused, requires_function(_ismbcl2_l)]]
int _ismbcl2(unsigned int ch) {
	return _ismbcl2_l(ch, NULL);
}

[[wunused, requires_function(_mbcjistojms_l)]]
unsigned int _mbcjistojms(unsigned int ch) {
	return _mbcjistojms_l(ch, NULL);
}

[[wunused, requires_function(_mbcjmstojis_l)]]
unsigned int _mbcjmstojis(unsigned int ch) {
	return _mbcjmstojis_l(ch, NULL);
}

[[wunused, requires_function(_mbctohira_l)]]
unsigned int _mbctohira(unsigned int ch) {
	return _mbctohira_l(ch, NULL);
}

[[wunused, requires_function(_mbctokata_l)]]
unsigned int _mbctokata(unsigned int ch) {
	return _mbctokata_l(ch, NULL);
}

[[wunused, requires_function(_ismbblead_l)]]
int _ismbblead(unsigned int ch) {
	return _ismbblead_l(ch, NULL);
}

[[wunused, requires_function(_ismbbtrail_l)]]
int _ismbbtrail(unsigned int ch) {
	return _ismbbtrail_l(ch, NULL);
}

[[wunused, requires_function(_ismbslead_l)]]
int _ismbslead([[nonnull]] unsigned char const *str,
               [[nonnull]] unsigned char const *pos) {
	return _ismbslead_l(str, pos, NULL);
}

[[wunused, requires_function(_ismbstrail_l)]]
int _ismbstrail([[nonnull]] unsigned char const *str,
                [[nonnull]] unsigned char const *pos) {
	return _ismbstrail_l(str, pos, NULL);
}






/************************************************************************/
/* Locale-enabled functions                                             */
/************************************************************************/
[[wunused]]
unsigned int _mbbtombc_l(unsigned int ch, $locale_t locale); /* TODO */

[[wunused]]
int _mbbtype_l(unsigned char ch, int ctype, $locale_t locale); /* TODO */

[[wunused]]
unsigned int _mbctombb_l(unsigned int ch, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>")]]
int _mbsbtype_l([[inp_opt(pos)]] unsigned char const *str,
                size_t pos, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbscat_s_l([[inoutp(bufsize)]] unsigned char *buf, size_t bufsize,
                    [[nonnull]] unsigned char const *src, $locale_t locale); /* TODO */

[[nonnull]]
unsigned char *_mbscat_l([[nonnull]] unsigned char *__restrict dst,
                         [[nonnull]] unsigned char const *__restrict src, $locale_t locale) {
	(void)locale;
	return (unsigned char *)strcat((char *)dst, (char const *)src);
}

[[wunused]]
unsigned char *_mbschr_l([[nonnull]] unsigned char const *__restrict haystack, unsigned int needle, $locale_t locale)
	[([[nonnull]] unsigned char *__restrict haystack, int needle, $locale_t locale): unsigned char *]
	[([[nonnull]] unsigned char const *__restrict haystack, int needle, $locale_t locale): unsigned char const *]; /* TODO */

[[wunused]]
int _mbscmp_l([[nonnull]] unsigned char const *lhs,
              [[nonnull]] unsigned char const *rhs, $locale_t locale); /* TODO */

[[wunused]]
int _mbscoll_l([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbscpy_s_l([[outp(bufsize)]] unsigned char *buf, size_t bufsize,
                    [[nonnull]] unsigned char const *src, $locale_t locale); /* TODO */

[[nonnull]]
unsigned char *_mbscpy_l([[nonnull]] unsigned char *__restrict dst,
                         [[nonnull]] unsigned char const *__restrict src, $locale_t locale) {
	(void)locale;
	return (unsigned char *)strcpy((char *)dst, (char const *)src);
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
size_t _mbscspn_l([[nonnull]] unsigned char const *haystack,
                  [[nonnull]] unsigned char const *reject, $locale_t locale); /* TODO */

[[wunused]]
unsigned char *_mbsdec_l([[nonnull]] unsigned char const *start,
                         [[nonnull]] unsigned char const *pos, $locale_t locale); /* TODO */

[[wunused]]
int _mbsicmp_l([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs, $locale_t locale); /* TODO */

[[wunused]]
int _mbsicoll_l([[nonnull]] unsigned char const *lhs,
                [[nonnull]] unsigned char const *rhs, $locale_t locale); /* TODO */

[[wunused]]
unsigned char *_mbsinc_l([[nonnull]] unsigned char const *ptr, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
size_t _mbslen_l([[nonnull]] unsigned char const *str, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
size_t _mbsnlen_l([[nonnull]] unsigned char const *str, size_t maxlen, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbslwr_s_l([[outp(buflen)]] unsigned char *buf, size_t buflen, $locale_t locale); /* TODO */

unsigned char *_mbslwr_l([[nonnull]] unsigned char *buf, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsnbcat_s_l([[inoutp(bufsize)]] unsigned char *buf, size_t bufsize,
                      [[nonnull]] unsigned char const *src, size_t maxlen, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnbcat_l([[nonnull]] unsigned char *buf,
                           [[inp(srclen)]] unsigned char const *src,
                           size_t srclen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
int _mbsnbcmp_l([[nonnull]] unsigned char const *lhs,
                [[nonnull]] unsigned char const *rhs,
                size_t maxlen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
int _mbsnbcoll_l([[nonnull]] unsigned char const *lhs,
                 [[nonnull]] unsigned char const *rhs,
                 size_t maxlen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
size_t _mbsnbcnt_l([[nonnull]] unsigned char const *str,
                   size_t maxlen, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsnbcpy_s_l([[outp(srclen)]] unsigned char *buf, size_t bufsize,
                      [[inp(srclen)]] unsigned char const *src, size_t srclen,
                      $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnbcpy_l([[outp(srclen)]] unsigned char *buf,
                           [[inp(srclen)]] unsigned char const *src,
                           size_t srclen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
int _mbsnbicmp_l([[nonnull]] unsigned char const *lhs,
                 [[nonnull]] unsigned char const *rhs,
                 size_t maxlen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
int _mbsnbicoll_l([[nonnull]] unsigned char const *lhs,
                  [[nonnull]] unsigned char const *rhs,
                  size_t maxlen, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>")]]
errno_t _mbsnbset_s_l([[inoutp(bufsize)]] unsigned char *buf, size_t bufsize,
                      unsigned int ch, size_t num_chars, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
unsigned char *_mbsnbset_l([[inoutp(buflen)]] unsigned char *buf,
                           unsigned int ch, size_t buflen, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsncat_s_l([[inoutp(bufsize)]] unsigned char *buf, size_t bufsize,
                     [[inp(srclen)]] unsigned char const *src, size_t srclen,
                     $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsncat_l([[nonnull]] unsigned char *buf,
                          [[nonnull]] unsigned char const *src,
                          size_t srclen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
size_t _mbsnccnt_l([[nonnull]] unsigned char const *str,
                   size_t maxlen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
int _mbsncmp_l([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs,
               size_t maxlen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
int _mbsncoll_l([[nonnull]] unsigned char const *lhs,
                [[nonnull]] unsigned char const *rhs,
                size_t maxlen, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsncpy_s_l([[outp(bufsize)]] unsigned char *buf, size_t bufsize,
                     [[nonnull]] unsigned char const *src, size_t maxlen,
                     $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsncpy_l([[outp(srclen)]] unsigned char *buf,
                          [[nonnull]] unsigned char const *src,
                          size_t srclen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
unsigned int _mbsnextc_l([[nonnull]] unsigned char const *str,
                         $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
int _mbsnicmp_l([[nonnull]] unsigned char const *lhs,
                [[nonnull]] unsigned char const *rhs,
                size_t maxlen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
int _mbsnicoll_l([[nonnull]] unsigned char const *lhs,
                 [[nonnull]] unsigned char const *rhs,
                 size_t maxlen, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsninc_l([[nonnull]] unsigned char const *str,
                          size_t maxlen, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsnset_s_l([[inoutp(bufsize)]] unsigned char *buf, size_t bufsize,
                     unsigned int ch, size_t maxlen, $locale_t locale); /* TODO */

[[nonnull, decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnset_l([[nonnull]] unsigned char *buf, unsigned int ch,
                          size_t maxlen, $locale_t locale); /* TODO */

[[wunused]]
unsigned char *_mbspbrk_l([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *accept, $locale_t locale)
	[([[nonnull]] unsigned char *haystack, [[nonnull]] unsigned char const *accept, $locale_t locale): unsigned char *]
	[([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *accept, $locale_t locale): unsigned char const *];
/* TODO */

[[wunused]]
unsigned char *_mbsrchr_l([[nonnull]] unsigned char const *haystack, unsigned int needle, $locale_t locale)
	[([[nonnull]] unsigned char *__restrict haystack, unsigned int needle, $locale_t locale): unsigned char *]
	[([[nonnull]] unsigned char const *__restrict haystack, unsigned int needle, $locale_t locale): unsigned char const *];
/* TODO */

[[nonnull]]
unsigned char *_mbsrev_l([[nonnull]] unsigned char *buf, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsset_s_l([[inoutp(bufsize)]] unsigned char *buf,
                    size_t bufsize, unsigned int ch, $locale_t locale); /* TODO */

[[nonnull]]
unsigned char *_mbsset_l([[nonnull]] unsigned char *buf,
                         unsigned int ch, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
size_t _mbsspn_l([[nonnull]] unsigned char const *haystack,
                 [[nonnull]] unsigned char const *accept,
                 $locale_t locale); /* TODO */

[[wunused]]
unsigned char *_mbsspnp_l([[nonnull]] unsigned char const *lhs,
                          [[nonnull]] unsigned char const *rhs,
                          $locale_t locale); /* TODO */

[[wunused]]
unsigned char *_mbsstr_l([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *needle, $locale_t locale)
	[([[nonnull]] unsigned char *haystack, [[nonnull]] unsigned char const *needle, $locale_t locale): [[nullable]] unsigned char *]
	[([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *needle, $locale_t locale): [[nullable]] unsigned char const *];
/* TODO */

[[wunused, requires_function(_mbstok_s_l)]]
unsigned char *_mbstok_l([[nullable]] unsigned char *str,
                         [[nonnull]] unsigned char const *delim,
                         $locale_t locale) {
	static unsigned char *save_ptr = NULL;
	return _mbstok_s_l(str, delim, &save_ptr, locale);
}

[[wunused]]
unsigned char *_mbstok_s_l([[nullable]] unsigned char *str,
                           [[nonnull]] unsigned char const *delim,
                           [[nonnull]] unsigned char **__restrict save_ptr,
                           $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbsupr_s_l([[inoutp(bufsize)]] unsigned char *buf,
                    size_t bufsize, $locale_t locale); /* TODO */

[[nonnull]]
unsigned char *_mbsupr_l([[nonnull]] unsigned char *buf, $locale_t locale); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
size_t _mbclen_l([[nonnull]] unsigned char const *str, $locale_t locale); /* TODO */

void _mbccpy_l([[nonnull]] unsigned char *buf,
               [[nonnull]] unsigned char const *src, $locale_t locale); /* TODO */

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
errno_t _mbccpy_s_l([[outp(bufsize)]] unsigned char *buf, size_t bufsize, [[nullable]] int *p_copied,
                    [[nonnull]] unsigned char const *src, $locale_t locale); /* TODO */



/************************************************************************/
/* Character-traits functions                                           */
/************************************************************************/

[[wunused]]
int _ismbcalnum_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbcalpha_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbcdigit_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbcgraph_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbclegal_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbclower_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbcprint_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbcpunct_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbcblank_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbcspace_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbcupper_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
unsigned int _mbctolower_l(unsigned int ch,
                           $locale_t locale); /* TODO */

[[wunused]]
unsigned int _mbctoupper_l(unsigned int ch,
                           $locale_t locale); /* TODO */

[[wunused]]
int _ismbchira_l(unsigned int ch,
                 $locale_t locale); /* TODO */

[[wunused]]
int _ismbckata_l(unsigned int ch,
                 $locale_t locale); /* TODO */

[[wunused]]
int _ismbcsymbol_l(unsigned int ch,
                   $locale_t locale); /* TODO */

[[wunused]]
int _ismbcl0_l(unsigned int ch,
                $locale_t locale); /* TODO */

[[wunused]]
int _ismbcl1_l(unsigned int ch,
                $locale_t locale); /* TODO */

[[wunused]]
int _ismbcl2_l(unsigned int ch,
                $locale_t locale); /* TODO */

[[wunused]]
unsigned int _mbcjistojms_l(unsigned int ch,
                            $locale_t locale); /* TODO */

[[wunused]]
unsigned int _mbcjmstojis_l(unsigned int ch,
                            $locale_t locale); /* TODO */

[[wunused]]
unsigned int _mbctohira_l(unsigned int ch,
                          $locale_t locale); /* TODO */

[[wunused]]
unsigned int _mbctokata_l(unsigned int ch,
                          $locale_t locale); /* TODO */

[[wunused]]
int _ismbblead_l(unsigned int ch,
                 $locale_t locale); /* TODO */

[[wunused]]
int _ismbbtrail_l(unsigned int ch,
                  $locale_t locale); /* TODO */

[[wunused]]
int _ismbslead_l([[nonnull]] unsigned char const *str,
                 [[nonnull]] unsigned char const *pos,
                 $locale_t locale); /* TODO */

[[wunused]]
int _ismbstrail_l([[nonnull]] unsigned char const *str,
                  [[nonnull]] unsigned char const *pos,
                  $locale_t locale); /* TODO */

%{

__SYSDECL_END
#endif /* __CC__ */

}
