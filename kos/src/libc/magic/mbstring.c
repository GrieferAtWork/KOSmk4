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

[[nocrt, alias("strdup", "_strdup", "_mbsdup", "__strdup")]]
[if(__has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("strdup", { return (unsigned char *)__builtin_strdup((char const *)string); })]
[[if($has_function(malloc)), bind_local_function("strdup")]]
_mbsdup([[nonnull]] unsigned char const *__restrict string)
	-> [[malloc/*((strlen(string) + 1) * sizeof(unsigned char))*/]] unsigned char *;

/************************************************************************/
/* Current-local functions                                              */
/************************************************************************/

[[wunused, requires_function(_mbbtombc_l), doc_alias("_mbbtombc_l")]]
unsigned int _mbbtombc(unsigned int ch) {
	return _mbbtombc_l(ch, NULL);
}

[[wunused, requires_function(_mbbtype_l), doc_alias("_mbbtype_l")]]
int _mbbtype(unsigned char ch, int ctype) {
	return _mbbtype_l(ch, ctype, NULL);
}

[[wunused, requires_function(_mbctombb_l), doc_alias("_mbctombb_l")]]
unsigned int _mbctombb(unsigned int ch) {
	return _mbctombb_l(ch, NULL);
}

[[requires_function(_mbsbtype_l), doc_alias("_mbsbtype_l")]]
[[wunused, decl_include("<hybrid/typecore.h>")]]
int _mbsbtype([[nonnull]] unsigned char const *str, size_t pos) {
	return _mbsbtype_l(str, pos, NULL);
}

[[requires_function(_mbscat_s_l), doc_alias("_mbscat_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbscat_s([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                          [[nonnull]] unsigned char const *src) {
	return _mbscat_s_l(buf, true_bufsize, src, NULL);
}

[[nonnull, nocrt, leaf, alias("strcat", "_mbscat")]]
[if(__has_builtin(__builtin_strcat) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("strcat", { return (unsigned char *)__builtin_strcat((char *)dst, (char const *)src); })]
[[bind_local_function("strcat")]]
unsigned char *_mbscat([[nonnull]] unsigned char *__restrict dst,
                       [[nonnull]] unsigned char const *__restrict src);


[[wunused, requires_function(_mbschr_l), doc_alias("_mbschr_l")]]
unsigned char *_mbschr([[nonnull]] unsigned char const *__restrict haystack, unsigned int needle)
	[([[nonnull]] unsigned char *__restrict haystack, int needle): unsigned char *]
	[([[nonnull]] unsigned char const *__restrict haystack, int needle): unsigned char const *]
{
	return _mbschr_l(haystack, needle, NULL);
}

[[wunused, requires_function(_mbscmp_l), doc_alias("_mbscmp_l")]]
int _mbscmp([[nonnull]] unsigned char const *lhs,
            [[nonnull]] unsigned char const *rhs) {
	return _mbscmp_l(lhs, rhs, NULL);
}

[[wunused, requires_function(_mbscoll_l), doc_alias("_mbscoll_l")]]
int _mbscoll([[nonnull]] unsigned char const *lhs,
             [[nonnull]] unsigned char const *rhs) {
	return _mbscoll_l(lhs, rhs, NULL);
}

[[requires_function(_mbscpy_s_l), doc_alias("_mbscpy_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbscpy_s([[outp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                          [[nonnull]] unsigned char const *src) {
	return _mbscpy_s_l(buf, true_bufsize, src, NULL);
}

[[nonnull, nocrt, leaf, alias("strcpy", "_mbscpy")]]
[if(__has_builtin(__builtin_strcpy) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("strcpy", { return (unsigned char *)__builtin_strcpy((char *)dst, (char const *)src); })]
[[bind_local_function("strcpy")]]
unsigned char *_mbscpy([[nonnull]] unsigned char *__restrict dst,
                       [[nonnull]] unsigned char const *__restrict src);

[[wunused, requires_function(_mbscspn_l), doc_alias("_mbscspn_l")]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbscspn([[nonnull]] unsigned char const *haystack,
                [[nonnull]] unsigned char const *reject) {
	return _mbscspn_l(haystack, reject, NULL);
}

[[wunused, requires_function(_mbsdec_l), doc_alias("_mbsdec_l")]]
unsigned char *_mbsdec([[nonnull]] unsigned char const *start,
                       [[nonnull]] unsigned char const *pos) {
	return _mbsdec_l(start, pos, NULL);
}

[[wunused, requires_function(_mbsicmp_l), doc_alias("_mbsicmp_l")]]
int _mbsicmp([[nonnull]] unsigned char const *lhs,
             [[nonnull]] unsigned char const *rhs) {
	return _mbsicmp_l(lhs, rhs, NULL);
}

[[wunused, requires_function(_mbsicoll_l), doc_alias("_mbsicoll_l")]]
int _mbsicoll([[nonnull]] unsigned char const *lhs,
              [[nonnull]] unsigned char const *rhs) {
	return _mbsicoll_l(lhs, rhs, NULL);
}

[[wunused, requires_function(_mbsinc_l), doc_alias("_mbsinc_l")]]
unsigned char *_mbsinc([[nonnull]] unsigned char const *ptr) {
	return _mbsinc_l(ptr, NULL);
}

[[wunused, requires_function(_mbslen_l), doc_alias("_mbslen_l")]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbslen([[nonnull]] unsigned char const *str) {
	return _mbslen_l(str, NULL);
}

[[wunused, requires_function(_mbsnlen_l), doc_alias("_mbsnlen_l")]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbsnlen([[nonnull]] unsigned char const *str, size_t max_bytes) {
	return _mbsnlen_l(str, max_bytes, NULL);
}

[[requires_function(_mbslwr_s_l), doc_alias("_mbslwr_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbslwr_s([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize) {
	return _mbslwr_s_l(buf, true_bufsize, NULL);
}

[[nonnull, requires_function(_mbslwr_l), doc_alias("_mbslwr_l")]]
unsigned char *_mbslwr([[nonnull]] unsigned char *buf) {
	return _mbslwr_l(buf, NULL);
}

[[nonnull, requires_function(_mbsupr_l), doc_alias("_mbsupr_l")]]
unsigned char *_mbsupr([[nonnull]] unsigned char *buf) {
	return _mbsupr_l(buf, NULL);
}

[[requires_function(_mbsnbcat_s_l), doc_alias("_mbsnbcat_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbsnbcat_s([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                            [[inp(max_bytes)]] unsigned char const *src, size_t max_bytes) {
	return _mbsnbcat_s_l(buf, true_bufsize, src, max_bytes, NULL);
}

[[requires_function(_mbsnbcat_l), doc_alias("_mbsnbcat_l")]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnbcat([[nonnull]] unsigned char *buf,
                         [[inp(max_bytes)]] unsigned char const *src, size_t max_bytes) {
	return _mbsnbcat_l(buf, src, max_bytes, NULL);
}

[[wunused, requires_function(_mbsnbcmp_l), doc_alias("_mbsnbcmp_l")]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnbcmp([[nonnull]] unsigned char const *lhs,
              [[nonnull]] unsigned char const *rhs,
              size_t max_bytes) {
	return _mbsnbcmp_l(lhs, rhs, max_bytes, NULL);
}

[[wunused, requires_function(_mbsnbcoll_l), doc_alias("_mbsnbcoll_l")]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnbcoll([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs,
               size_t max_bytes) {
	return _mbsnbcoll_l(lhs, rhs, max_bytes, NULL);
}

[[wunused, requires_function(_mbsnbcnt_l), doc_alias("_mbsnbcnt_l")]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbsnbcnt([[nonnull]] unsigned char const *str, size_t max_chars) {
	return _mbsnbcnt_l(str, max_chars, NULL);
}

[[requires_function(_mbsnbcpy_s_l), doc_alias("_mbsnbcpy_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbsnbcpy_s([[outp(bufsize)]] unsigned char *buf, size_t true_bufsize,
                            [[nonnull]] unsigned char const *src, size_t bufsize) {
	return _mbsnbcpy_s_l(buf, true_bufsize, src, bufsize, NULL);
}

[[requires_function(_mbsnbcpy_l), doc_alias("_mbsnbcpy_l")]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnbcpy([[outp(bufsize)]] unsigned char *buf,
                         [[nonnull]] unsigned char const *src,
                         size_t bufsize) {
	return _mbsnbcpy_l(buf, src, bufsize, NULL);
}

[[wunused, requires_function(_mbsnbicmp_l), doc_alias("_mbsnbicmp_l")]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnbicmp([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs,
               size_t max_bytes) {
	return _mbsnbicmp_l(lhs, rhs, max_bytes, NULL);
}

[[wunused, requires_function(_mbsnbicoll_l), doc_alias("_mbsnbicoll_l")]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnbicoll([[nonnull]] unsigned char const *lhs,
                [[nonnull]] unsigned char const *rhs,
                size_t max_bytes) {
	return _mbsnbicoll_l(lhs, rhs, max_bytes, NULL);
}

[[requires_function(_mbsnbset_s_l), doc_alias("_mbsnbset_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbsnbset_s([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                            unsigned int ch, size_t max_bytes) {
	return _mbsnbset_s_l(buf, true_bufsize, ch, max_bytes, NULL);
}

[[requires_function(_mbsnbset_l), doc_alias("_mbsnbset_l")]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnbset([[inoutp(max_bytes)]] unsigned char *buf,
                         unsigned int ch, size_t max_bytes) {
	return _mbsnbset_l(buf, ch, max_bytes, NULL);
}

[[requires_function(_mbsncat_s_l), doc_alias("_mbsncat_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbsncat_s([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                           [[nonnull]] unsigned char const *src, size_t max_chars) {
	return _mbsncat_s_l(buf, true_bufsize, src, max_chars, NULL);
}

[[requires_function(_mbsncat_l), doc_alias("_mbsncat_l")]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsncat([[nonnull]] unsigned char *buf,
                        [[nonnull]] unsigned char const *src, size_t max_chars) {
	return _mbsncat_l(buf, src, max_chars, NULL);
}

[[wunused, requires_function(_mbsnccnt_l), doc_alias("_mbsnccnt_l")]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbsnccnt([[nonnull]] unsigned char const *str, size_t max_bytes) {
	return _mbsnccnt_l(str, max_bytes, NULL);
}

[[wunused, requires_function(_mbsncmp_l), doc_alias("_mbsncmp_l")]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsncmp([[nonnull]] unsigned char const *lhs,
             [[nonnull]] unsigned char const *rhs,
             size_t max_chars) {
	return _mbsncmp_l(lhs, rhs, max_chars, NULL);
}

%[insert:pp_if($has_function(_mbsncmp))]
%#define _mbccmp(lhs, rhs) _mbsncmp(lhs, rhs, 1)
%[insert:pp_endif]

[[wunused, requires_function(_mbsncoll_l), doc_alias("_mbsncoll_l")]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsncoll([[nonnull]] unsigned char const *lhs,
              [[nonnull]] unsigned char const *rhs,
              size_t max_chars) {
	return _mbsncoll_l(lhs, rhs, max_chars, NULL);
}

[[requires_function(_mbsncpy_s_l), doc_alias("_mbsncpy_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbsncpy_s([[outp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                           [[nonnull]] unsigned char const *src, size_t max_chars) {
	return _mbsncpy_s_l(buf, true_bufsize, src, max_chars, NULL);
}

[[requires_function(_mbsncpy_l), doc_alias("_mbsncpy_l")]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsncpy([[nonnull]] unsigned char *buf,
                        [[nonnull]] unsigned char const *src, size_t max_chars) {
	return _mbsncpy_l(buf, src, max_chars, NULL);
}

[[wunused, requires_function(_mbsnextc_l), doc_alias("_mbsnextc_l")]]
unsigned int _mbsnextc([[nonnull]] unsigned char const *str) {
	return _mbsnextc_l(str, NULL);
}

[[wunused, requires_function(_mbsnicmp_l), doc_alias("_mbsnicmp_l")]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnicmp([[nonnull]] unsigned char const *lhs,
              [[nonnull]] unsigned char const *rhs,
              size_t max_chars) {
	return _mbsnicmp_l(lhs, rhs, max_chars, NULL);
}

[[wunused, requires_function(_mbsnicoll_l), doc_alias("_mbsnicoll_l")]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnicoll([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs,
               size_t max_chars) {
	return _mbsnicoll_l(lhs, rhs, max_chars, NULL);
}

[[wunused, requires_function(_mbsninc_l), doc_alias("_mbsninc_l")]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsninc([[nonnull]] unsigned char const *str, size_t max_chars) {
	return _mbsninc_l(str, max_chars, NULL);
}

[[requires_function(_mbsnset_s_l), doc_alias("_mbsnset_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbsnset_s([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                           unsigned int ch, size_t max_chars) {
	return _mbsnset_s_l(buf, true_bufsize, ch, max_chars, NULL);
}

[[nonnull, requires_function(_mbsnset_l), doc_alias("_mbsnset_l")]]
[[decl_include("<hybrid/typecore.h>")]]
unsigned char *_mbsnset([[nonnull]] unsigned char *buf,
                        unsigned int ch, size_t max_chars) {
	return _mbsnset_l(buf, ch, max_chars, NULL);
}

[[wunused, requires_function(_mbspbrk_l), doc_alias("_mbspbrk_l")]]
unsigned char *_mbspbrk([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *accept)
	[([[nonnull]] unsigned char *haystack, [[nonnull]] unsigned char const *accept): unsigned char *]
	[([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *accept): unsigned char const *]
{
	return _mbspbrk_l(haystack, accept, NULL);
}

[[wunused, requires_function(_mbsrchr_l), doc_alias("_mbsrchr_l")]]
unsigned char *_mbsrchr([[nonnull]] unsigned char const *haystack, unsigned int needle)
	[([[nonnull]] unsigned char *__restrict haystack, unsigned int needle): unsigned char *]
	[([[nonnull]] unsigned char const *__restrict haystack, unsigned int needle): unsigned char const *]
{
	return _mbsrchr_l(haystack, needle, NULL);
}

[[nonnull, requires_function(_mbsrev_l), doc_alias("_mbsrev_l")]]
unsigned char *_mbsrev([[nonnull]] unsigned char *buf) {
	return _mbsrev_l(buf, NULL);
}

[[requires_function(_mbsset_s_l), doc_alias("_mbsset_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbsset_s([[inoutp(true_bufsize)]] unsigned char *buf,
                          size_t true_bufsize, unsigned int ch) {
	return _mbsset_s_l(buf, true_bufsize, ch, NULL);
}

[[nonnull, requires_function(_mbsset_l), doc_alias("_mbsset_l")]]
unsigned char *_mbsset([[nonnull]] unsigned char *buf, unsigned int ch) {
	return _mbsset_l(buf, ch, NULL);
}

[[wunused, requires_function(_mbsspn_l), doc_alias("_mbsspn_l")]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbsspn([[nonnull]] unsigned char const *haystack,
               [[nonnull]] unsigned char const *accept) {
	return _mbsspn_l(haystack, accept, NULL);
}

[[wunused, requires_function(_mbsspnp_l), doc_alias("_mbsspnp_l")]]
unsigned char *_mbsspnp([[nonnull]] unsigned char const *haystack,
                        [[nonnull]] unsigned char const *accept) {
	return _mbsspnp_l(haystack, accept, NULL);
}

[[wunused, requires_function(_mbsstr_l), doc_alias("_mbsstr_l")]]
unsigned char *_mbsstr([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *needle)
	[([[nonnull]] unsigned char *haystack, [[nonnull]] unsigned char const *needle): [[nullable]] unsigned char *]
	[([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *needle): [[nullable]] unsigned char const *]
{
	return _mbsstr_l(haystack, needle, NULL);
}

[[wunused, requires_function(_mbstok_l), doc_alias("_mbstok_l")]]
unsigned char *_mbstok([[nullable]] unsigned char *str,
                       [[nonnull]] unsigned char const *delim) {
	return _mbstok_l(str, delim, NULL);
}

[[wunused, requires_function(_mbstok_s_l), doc_alias("_mbstok_s_l")]]
unsigned char *_mbstok_s([[nullable]] unsigned char *str,
                         [[nonnull]] unsigned char const *delim,
                         [[nonnull]] unsigned char **__restrict save_ptr) {
	return _mbstok_s_l(str, delim, save_ptr, NULL);
}

[[requires_function(_mbsupr_s_l), doc_alias("_mbsupr_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbsupr_s([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize) {
	return _mbsupr_s_l(buf, true_bufsize, NULL);
}

[[wunused, requires_function(_mbclen_l), doc_alias("_mbclen_l")]]
[[decl_include("<hybrid/typecore.h>")]]
size_t _mbclen([[nonnull]] unsigned char const *str) {
	return _mbclen_l(str, NULL);
}

[[requires_function(_mbccpy_l), doc_alias("_mbccpy_l")]]
void _mbccpy([[nonnull]] unsigned char *dst,
             [[nonnull]] unsigned char const *src) {
	_mbccpy_l(dst, src, NULL);
}

[[requires_function(_mbccpy_s_l), doc_alias("_mbccpy_s_l")]]
[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
/*dos*/ errno_t _mbccpy_s([[outp(true_dstsize)]] unsigned char *dst, size_t true_dstsize,
                          [[nullable]] int *p_copied, [[nonnull]] unsigned char const *src) {
	return _mbccpy_s_l(dst, true_dstsize, p_copied, src, NULL);
}


/************************************************************************/
/* Character-traits functions                                           */
/************************************************************************/

[[wunused, requires_function(_ismbcalnum_l), doc_alias("_ismbcalnum_l")]]
int _ismbcalnum(unsigned int ch) {
	return _ismbcalnum_l(ch, NULL);
}

[[wunused, requires_function(_ismbcalpha_l), doc_alias("_ismbcalpha_l")]]
int _ismbcalpha(unsigned int ch) {
	return _ismbcalpha_l(ch, NULL);
}

[[wunused, requires_function(_ismbcdigit_l), doc_alias("_ismbcdigit_l")]]
int _ismbcdigit(unsigned int ch) {
	return _ismbcdigit_l(ch, NULL);
}

[[wunused, requires_function(_ismbcgraph_l), doc_alias("_ismbcgraph_l")]]
int _ismbcgraph(unsigned int ch) {
	return _ismbcgraph_l(ch, NULL);
}

[[wunused, requires_function(_ismbclegal_l), doc_alias("_ismbclegal_l")]]
int _ismbclegal(unsigned int ch) {
	return _ismbclegal_l(ch, NULL);
}

[[wunused, requires_function(_ismbclower_l), doc_alias("_ismbclower_l")]]
int _ismbclower(unsigned int ch) {
	return _ismbclower_l(ch, NULL);
}

[[wunused, requires_function(_ismbcprint_l), doc_alias("_ismbcprint_l")]]
int _ismbcprint(unsigned int ch) {
	return _ismbcprint_l(ch, NULL);
}

[[wunused, requires_function(_ismbcpunct_l), doc_alias("_ismbcpunct_l")]]
int _ismbcpunct(unsigned int ch) {
	return _ismbcpunct_l(ch, NULL);
}

[[wunused, requires_function(_ismbcblank_l), doc_alias("_ismbcblank_l")]]
int _ismbcblank(unsigned int ch) {
	return _ismbcblank_l(ch, NULL);
}

[[wunused, requires_function(_ismbcspace_l), doc_alias("_ismbcspace_l")]]
int _ismbcspace(unsigned int ch) {
	return _ismbcspace_l(ch, NULL);
}

[[wunused, requires_function(_ismbcupper_l), doc_alias("_ismbcupper_l")]]
int _ismbcupper(unsigned int ch) {
	return _ismbcupper_l(ch, NULL);
}

[[wunused, requires_function(_mbctolower_l), doc_alias("_mbctolower_l")]]
unsigned int _mbctolower(unsigned int ch) {
	return _mbctolower_l(ch, NULL);
}

[[wunused, requires_function(_mbctoupper_l), doc_alias("_mbctoupper_l")]]
unsigned int _mbctoupper(unsigned int ch) {
	return _mbctoupper_l(ch, NULL);
}

[[wunused, requires_function(_ismbchira_l), doc_alias("_ismbchira_l")]]
int _ismbchira(unsigned int ch) {
	return _ismbchira_l(ch, NULL);
}

[[wunused, requires_function(_ismbckata_l), doc_alias("_ismbckata_l")]]
int _ismbckata(unsigned int ch) {
	return _ismbckata_l(ch, NULL);
}

[[wunused, requires_function(_ismbcsymbol_l), doc_alias("_ismbcsymbol_l")]]
int _ismbcsymbol(unsigned int ch) {
	return _ismbcsymbol_l(ch, NULL);
}

[[wunused, requires_function(_ismbcl0_l), doc_alias("_ismbcl0_l")]]
int _ismbcl0(unsigned int ch) {
	return _ismbcl0_l(ch, NULL);
}

[[wunused, requires_function(_ismbcl1_l), doc_alias("_ismbcl1_l")]]
int _ismbcl1(unsigned int ch) {
	return _ismbcl1_l(ch, NULL);
}

[[wunused, requires_function(_ismbcl2_l), doc_alias("_ismbcl2_l")]]
int _ismbcl2(unsigned int ch) {
	return _ismbcl2_l(ch, NULL);
}

[[wunused, requires_function(_mbcjistojms_l), doc_alias("_mbcjistojms_l")]]
unsigned int _mbcjistojms(unsigned int ch) {
	return _mbcjistojms_l(ch, NULL);
}

[[wunused, requires_function(_mbcjmstojis_l), doc_alias("_mbcjmstojis_l")]]
unsigned int _mbcjmstojis(unsigned int ch) {
	return _mbcjmstojis_l(ch, NULL);
}

[[wunused, requires_function(_mbctohira_l), doc_alias("_mbctohira_l")]]
unsigned int _mbctohira(unsigned int ch) {
	return _mbctohira_l(ch, NULL);
}

[[wunused, requires_function(_mbctokata_l), doc_alias("_mbctokata_l")]]
unsigned int _mbctokata(unsigned int ch) {
	return _mbctokata_l(ch, NULL);
}

[[wunused, requires_function(_ismbblead_l), doc_alias("_ismbblead_l")]]
int _ismbblead(unsigned int ch) {
	return _ismbblead_l(ch, NULL);
}

[[wunused, requires_function(_ismbbtrail_l), doc_alias("_ismbbtrail_l")]]
int _ismbbtrail(unsigned int ch) {
	return _ismbbtrail_l(ch, NULL);
}

[[wunused, requires_function(_ismbslead_l), doc_alias("_ismbslead_l")]]
int _ismbslead([[nonnull]] unsigned char const *str,
               [[nonnull]] unsigned char const *pos) {
	return _ismbslead_l(str, pos, NULL);
}

[[wunused, requires_function(_ismbstrail_l), doc_alias("_ismbstrail_l")]]
int _ismbstrail([[nonnull]] unsigned char const *str,
                [[nonnull]] unsigned char const *pos) {
	return _ismbstrail_l(str, pos, NULL);
}






/************************************************************************/
/* Locale-enabled functions                                             */
/************************************************************************/
[[nonnull]]
unsigned char *_mbscat_l([[nonnull]] unsigned char *__restrict dst,
                         [[nonnull]] unsigned char const *__restrict src, $locale_t locale) {
	(void)locale;
	return (unsigned char *)strcat((char *)dst, (char const *)src);
}

[[nonnull]]
unsigned char *_mbscpy_l([[nonnull]] unsigned char *__restrict dst,
                         [[nonnull]] unsigned char const *__restrict src, $locale_t locale) {
	(void)locale;
	return (unsigned char *)strcpy((char *)dst, (char const *)src);
}

[[requires_function(_ismbblead_l)]]
void _mbccpy_l([[nonnull]] unsigned char *dst,
               [[nonnull]] unsigned char const *src,
               $locale_t locale) {
	unsigned char ch;
	*dst = ch = *src;
	if (_ismbblead_l(ch, locale))
		dst[1] = src[1];
}

@@WARNING: This function writes up to `max_chars' characters
@@         (read  as: up to `2 * max_chars' bytes) to `buf'!
[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l, bzero)]]
unsigned char *_mbsncpy_l([[nonnull]] unsigned char *buf,
                          [[nonnull]] unsigned char const *src,
                          size_t max_chars, $locale_t locale) {
	unsigned char *dst = buf;
	for (; max_chars; --max_chars) {
		unsigned char ch;
		*dst++ = ch = *src++;
		if (!ch)
			break;
		if (_ismbblead_l(ch, locale)) {
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
	bzero(dst, max_chars);
	return buf;
}

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l, bzero)]]
unsigned char *_mbsnbcpy_l([[outp(bufsize)]] unsigned char *buf,
                           [[nonnull]] unsigned char const *src,
                           size_t bufsize, $locale_t locale) {
	unsigned char *dst = buf;
	while (bufsize) {
		unsigned char ch;
		--bufsize;
		*dst++ = ch = *src++;
		if (!ch)
			break;
		if (_ismbblead_l(ch, locale)) {
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
	bzero(dst, bufsize);
	return buf;
}

[[wunused, impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
unsigned char *_mbschr_l([[nonnull]] unsigned char const *__restrict haystack, unsigned int needle, $locale_t locale)
	[([[nonnull]] unsigned char *__restrict haystack, int needle, $locale_t locale): unsigned char *]
	[([[nonnull]] unsigned char const *__restrict haystack, int needle, $locale_t locale): unsigned char const *]
{
	for (;;) {
		unsigned char const *temp;
		uint16_t hay;
		temp = haystack;
		hay  = *haystack++;
		if (_ismbblead_l(hay, locale))
			hay = *haystack ? (hay << 8) | *haystack++ : 0;
		if (hay == 0)
			break;
		if (hay == (uint16_t)(unsigned int)needle)
			return (unsigned char *)temp;
	}
	return NULL;
}

[[wunused, requires_function(_mbscmp_l)]]
int _mbscoll_l([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs,
               $locale_t locale) {
	/* XXX: Implement properly? */
	return _mbscmp_l(lhs, rhs, locale);
}

[[wunused, requires_function(_mbsicmp_l)]]
int _mbsicoll_l([[nonnull]] unsigned char const *lhs,
                [[nonnull]] unsigned char const *rhs,
                $locale_t locale) {
	/* XXX: Implement properly? */
	return _mbscmp_l(lhs, rhs, locale);
}

[[wunused, requires_function(_mbsncmp_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsncoll_l([[nonnull]] unsigned char const *lhs,
                [[nonnull]] unsigned char const *rhs,
                size_t max_chars, $locale_t locale) {
	/* XXX: Implement properly? */
	return _mbsncmp_l(lhs, rhs, max_chars, locale);
}

[[wunused, requires_function(_mbsnicmp_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnicoll_l([[nonnull]] unsigned char const *lhs,
                 [[nonnull]] unsigned char const *rhs,
                 size_t max_chars, $locale_t locale) {
	/* XXX: Implement properly? */
	return _mbsnicmp_l(lhs, rhs, max_chars, locale);
}

[[wunused, requires_function(_mbsnbcmp_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnbcoll_l([[nonnull]] unsigned char const *lhs,
                 [[nonnull]] unsigned char const *rhs,
                 size_t max_bytes, $locale_t locale) {
	/* XXX: Implement properly? */
	return _mbsnbcmp_l(lhs, rhs, max_bytes, locale);
}

[[wunused, requires_function(_mbsnbicmp_l)]]
[[decl_include("<hybrid/typecore.h>")]]
int _mbsnbicoll_l([[nonnull]] unsigned char const *lhs,
                  [[nonnull]] unsigned char const *rhs,
                  size_t max_bytes, $locale_t locale) {
	/* XXX: Implement properly? */
	return _mbsnbicmp_l(lhs, rhs, max_bytes, locale);
}

[[nonnull, impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l, _mbctolower_l)]]
unsigned char *_mbslwr_l([[nonnull]] unsigned char *buf, $locale_t locale) {
	unsigned char *iter = buf;
	for (;;) {
		uint16_t ch = *iter;
		if (!ch)
			break;
		if (_ismbblead_l(ch, locale)) {
			if unlikely(!iter[1])
				goto do_1byte_lower;
			ch      = (ch << 8) | iter[1];
			ch      = _mbctolower_l(ch, locale);
			iter[0] = (unsigned char)((ch & 0xff00) >> 8);
			iter[1] = (unsigned char)(ch & 0xff);
			iter += 2;
		} else {
do_1byte_lower:
			ch      = _mbctolower_l(ch, locale);
			iter[0] = (unsigned char)(ch & 0xff);
			++iter;
		}
	}
	return buf;
}

[[nonnull, impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l, _mbctoupper_l)]]
unsigned char *_mbsupr_l([[nonnull]] unsigned char *buf, $locale_t locale) {
	unsigned char *iter = buf;
	for (;;) {
		uint16_t ch = *iter;
		if (!ch)
			break;
		if (_ismbblead_l(ch, locale)) {
			if unlikely(!iter[1])
				goto do_1byte_lower;
			ch      = (ch << 8) | iter[1];
			ch      = _mbctoupper_l(ch, locale);
			iter[0] = (unsigned char)((ch & 0xff00) >> 8);
			iter[1] = (unsigned char)(ch & 0xff);
			iter += 2;
		} else {
do_1byte_lower:
			ch      = _mbctoupper_l(ch, locale);
			iter[0] = (unsigned char)(ch & 0xff);
			++iter;
		}
	}
	return buf;
}

[[wunused, nonnull, requires_function(_ismbblead_l)]]
unsigned char *_mbsinc_l([[nonnull]] unsigned char const *ptr, $locale_t locale) {
	if (_ismbblead_l(*ptr++, locale)) {
		if (*ptr)
			++ptr;
	}
	return (unsigned char *)ptr;
}

@@Returns pointer to `max_chars'th character of `str' (or strend() when `max_chars > _mbslen_l(str)')
[[wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(_mbsnbcnt_l)]]
unsigned char *_mbsninc_l([[nullable]] unsigned char const *str,
                          size_t max_chars, $locale_t locale) {
	if (str != NULL)
		str += _mbsnbcnt_l(str, max_chars, locale);
	return (unsigned char *)str;
}

[[wunused, nullable, requires_function(_mbsinc_l)]]
unsigned char *_mbsdec_l([[nonnull]] unsigned char const *start,
                         [[nonnull]] unsigned char const *pos,
                         $locale_t locale) {
	unsigned char const *iter;
	if (start >= pos)
		return NULL;
	iter = start;
	for (;;) {
		unsigned char const *next;
		next = _mbsinc_l(iter, locale);
		if (next >= pos)
			break;
		iter = next;
	}
	return (unsigned char *)iter;
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l, _mbschr_l)]]
size_t _mbscspn_l([[nonnull]] unsigned char const *haystack,
                  [[nonnull]] unsigned char const *reject, $locale_t locale) {
	unsigned char const *iter = haystack;
	for (;;) {
		uint16_t ch;
		ch = *iter++;
		if (_ismbblead_l(ch, locale))
			ch = *iter ? (ch << 8) | *iter++ : 0;
		if (ch == 0)
			break;
		if (_mbschr_l(reject, ch, locale) != NULL)
			break;
	}
	return (size_t)(iter - haystack);
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
size_t _mbslen_l([[nonnull]] unsigned char const *str, $locale_t locale) {
	size_t result;
	for (result = 0;; ++result) {
		uint16_t ch = *str++;
		if (_ismbblead_l(ch, locale))
			ch = *str ? (ch << 8) | *str++ : 0;
		if (ch == 0)
			break;
	}
	return result;
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
size_t _mbsnlen_l([[nonnull]] unsigned char const *str,
                  size_t max_bytes, $locale_t locale) {
	size_t result;
	for (result = 0; max_bytes; ++result) {
		uint16_t ch = *str++;
		--max_bytes;
		if (_ismbblead_l(ch, locale)) {
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

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strend, _ismbblead_l)]]
unsigned char *_mbsncat_l([[nonnull]] unsigned char *buf,
                          [[nonnull]] unsigned char const *src,
                          size_t max_chars, $locale_t locale) {
	if (max_chars) {
		unsigned char *dst;
		dst = (unsigned char *)strend((char const *)buf);
		for (; max_chars; --max_chars) {
			unsigned char ch;
			*dst++ = ch = *src++;
			if (!ch)
				return buf;
			if (_ismbblead_l(ch, locale)) {
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

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(strend, _ismbblead_l)]]
unsigned char *_mbsnbcat_l([[nonnull]] unsigned char *buf,
                           [[inp(max_bytes)]] unsigned char const *src,
                           size_t max_bytes, $locale_t locale) {
	unsigned char *dst;
	dst = (unsigned char *)strend((char const *)buf);
	for (;;) {
		unsigned char ch;
		if (!max_bytes)
			break;
		--max_bytes;
		*dst++ = ch = *src++;
		if (!ch)
			return buf;
		if (_ismbblead_l(ch, locale)) {
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

@@Returns # of characters in (up to) first `max_bytes' of `str'.
[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
size_t _mbsnccnt_l([[nonnull]] unsigned char const *str,
                   size_t max_bytes, $locale_t locale) {
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
		if (_ismbblead_l(ch, locale)) {
			if (str >= end)
				break;
			ch = *str++;
			if (ch == 0)
				break;
		}
	}
	return result;
}

@@Returns byte-offset from `str' after skipping `max_chars' characters.
[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
size_t _mbsnbcnt_l([[nonnull]] unsigned char const *str,
                   size_t max_chars, $locale_t locale) {
	unsigned char const *iter = str;
	for (; max_chars; --max_chars) {
		unsigned char ch;
		ch = *iter++;
		if (ch == 0)
			break;
		if (_ismbblead_l(ch, locale)) {
			ch = *iter++;
			if (ch == 0)
				break;
		}
	}
	return (size_t)(iter - str);
}

[[wunused, impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
int _mbscmp_l([[nonnull]] unsigned char const *lhs,
              [[nonnull]] unsigned char const *rhs, $locale_t locale) {
	for (;;) {
		uint16_t lc, rc;
		lc = *lhs++;
		if (_ismbblead_l(lc, locale))
			lc = *lhs ? (lc << 8) | *lhs++ : 0;
		rc = *rhs++;
		if (_ismbblead_l(rc, locale))
			rc = *rhs ? (rc << 8) | *rhs++ : 0;
		if (lc != rc)
			return (int)lc - (int)rc;
		if (lc == 0)
			break;
	}
	return 0;
}

[[wunused, impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l, _mbctolower_l)]]
int _mbsicmp_l([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs, $locale_t locale) {
	for (;;) {
		uint16_t lc, rc;
		lc = *lhs++;
		if (_ismbblead_l(lc, locale))
			lc = *lhs ? (lc << 8) | *lhs++ : 0;
		rc = *rhs++;
		if (_ismbblead_l(rc, locale))
			rc = *rhs ? (rc << 8) | *rhs++ : 0;
		if (lc != rc) {
			lc = _mbctolower_l(lc, locale);
			rc = _mbctolower_l(rc, locale);
			if (lc != rc)
				return (int)lc - (int)rc;
		}
		if (lc == 0)
			break;
	}
	return 0;
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
int _mbsncmp_l([[nonnull]] unsigned char const *lhs,
               [[nonnull]] unsigned char const *rhs,
               size_t max_chars, $locale_t locale) {
	for (; max_chars; --max_chars) {
		uint16_t lc = 0, rc = 0;
		lc = *lhs++;
		if (_ismbblead_l(lc, locale))
			lc = *lhs ? (lc << 8) | *lhs++ : 0;
		rc = *rhs++;
		if (_ismbblead_l(rc, locale))
			rc = *rhs ? (rc << 8) | *rhs++ : 0;
		if (lc != rc)
			return (int)lc - (int)rc;
		if (lc == 0)
			break;
	}
	return 0;
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l, _mbctolower_l)]]
int _mbsnicmp_l([[nonnull]] unsigned char const *lhs,
                [[nonnull]] unsigned char const *rhs,
                size_t max_chars, $locale_t locale) {
	for (; max_chars; --max_chars) {
		uint16_t lc = 0, rc = 0;
		lc = *lhs++;
		if (_ismbblead_l(lc, locale))
			lc = *lhs ? (lc << 8) | *lhs++ : 0;
		rc = *rhs++;
		if (_ismbblead_l(rc, locale))
			rc = *rhs ? (rc << 8) | *rhs++ : 0;
		if (lc != rc) {
			lc = _mbctolower_l(lc, locale);
			rc = _mbctolower_l(rc, locale);
			if (lc != rc)
				return (int)lc - (int)rc;
		}
		if (lc == 0)
			break;
	}
	return 0;
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
int _mbsnbcmp_l([[nonnull]] unsigned char const *lhs,
                [[nonnull]] unsigned char const *rhs,
                size_t max_bytes, $locale_t locale) {
	unsigned char const *lhs_end = lhs + max_bytes;
	unsigned char const *rhs_end = rhs + max_bytes;
	for (;;) {
		uint16_t lc = 0, rc = 0;
		if (lhs < lhs_end) {
			lc = *lhs++;
			if (_ismbblead_l(lc, locale))
				lc = (lhs < lhs_end && *lhs) ? (lc << 8) | *lhs++ : 0;
		}
		if (rhs < rhs_end) {
			rc = *rhs++;
			if (_ismbblead_l(rc, locale))
				rc = (rhs < rhs_end && *rhs) ? (rc << 8) | *rhs++ : 0;
		}
		if (lc != rc)
			return (int)lc - (int)rc;
		if (lc == 0)
			break;
	}
	return 0;
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l, _mbctolower_l)]]
int _mbsnbicmp_l([[nonnull]] unsigned char const *lhs,
                 [[nonnull]] unsigned char const *rhs,
                 size_t max_bytes, $locale_t locale) {
	unsigned char const *lhs_end = lhs + max_bytes;
	unsigned char const *rhs_end = rhs + max_bytes;
	for (;;) {
		uint16_t lc = 0, rc = 0;
		if (lhs < lhs_end) {
			lc = *lhs++;
			if (_ismbblead_l(lc, locale))
				lc = (lhs < lhs_end && *lhs) ? (lc << 8) | *lhs++ : 0;
		}
		if (rhs < rhs_end) {
			rc = *rhs++;
			if (_ismbblead_l(rc, locale))
				rc = (rhs < rhs_end && *rhs) ? (rc << 8) | *rhs++ : 0;
		}
		if (lc != rc) {
			lc = _mbctolower_l(lc, locale);
			rc = _mbctolower_l(rc, locale);
			if (lc != rc)
				return (int)lc - (int)rc;
		}
		if (lc == 0)
			break;
	}
	return 0;
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
unsigned int _mbsnextc_l([[nonnull]] unsigned char const *str,
                         $locale_t locale) {
	uint16_t result = str[0];
	if (_ismbblead_l(result, locale))
		result = (result << 8) | str[1];
	return result;
}

[[wunused, impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
unsigned char *_mbspbrk_l([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *accept, $locale_t locale)
	[([[nonnull]] unsigned char *haystack, [[nonnull]] unsigned char const *accept, $locale_t locale): unsigned char *]
	[([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *accept, $locale_t locale): unsigned char const *]
{
	uint16_t haych, ch;
	for (;;) {
		unsigned char const *temp;
		unsigned char const *ned_iter;
		temp  = haystack;
		haych = *haystack++;
		if (_ismbblead_l(haych, locale))
			haych = *haystack ? (haych << 8) | *haystack++ : 0;
		if (haych == 0)
			break;
		for (ned_iter = accept;;) {
			ch = *ned_iter++;
			if (_ismbblead_l(ch, locale))
				ch = *ned_iter ? (ch << 8) | *ned_iter++ : 0;
			if (ch == 0)
				break;
			if (haych == ch)
				return (unsigned char *)temp;
		}
	}
	return NULL;
}

[[wunused, impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
unsigned char *_mbsrchr_l([[nonnull]] unsigned char const *haystack, unsigned int needle, $locale_t locale)
	[([[nonnull]] unsigned char *__restrict haystack, unsigned int needle, $locale_t locale): unsigned char *]
	[([[nonnull]] unsigned char const *__restrict haystack, unsigned int needle, $locale_t locale): unsigned char const *]
{
	unsigned char *result = NULL;
	for (;;) {
		unsigned char const *temp;
		uint16_t hay;
		temp = haystack;
		hay  = *haystack++;
		if (_ismbblead_l(hay, locale))
			hay = *haystack ? (hay << 8) | *haystack++ : 0;
		if (hay == 0)
			break;
		if (hay == (uint16_t)(unsigned int)needle)
			result = (unsigned char *)temp;
	}
	return result;
}

[[nonnull, requires_function(strrev, strlen, _ismbblead_l)]]
unsigned char *_mbsrev_l([[nonnull]] unsigned char *buf, $locale_t locale) {
	size_t bytes;
	bytes = strlen(strrev((char *)buf));
	while (bytes >= 2) {
		unsigned char ch = buf[bytes - 1];
		if (_ismbblead_l(ch, locale)) {
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

[[nonnull, requires_function(_ismbblead_l, strset)]]
unsigned char *_mbsset_l([[nonnull]] unsigned char *buf,
                         unsigned int ch, $locale_t locale) {
	unsigned char *iter, lob, hib;
	lob = (ch & 0xff);
	hib = (ch & 0xff00) >> 8;
	if (!hib || !_ismbblead_l(lob, locale))
		return (unsigned char *)strset((char *)buf, (int)lob);
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

[[nonnull, decl_include("<hybrid/typecore.h>")]]
[[requires_function(strnset, _ismbblead_l)]]
unsigned char *_mbsnset_l([[nonnull]] unsigned char *buf, unsigned int ch,
                          size_t max_chars, $locale_t locale) {
	unsigned char *iter, lob, hib;
	lob = (ch & 0xff);
	hib = (ch & 0xff00) >> 8;
	if (!hib || !_ismbblead_l(lob, locale))
		return (unsigned char *)strnset((char *)buf, (int)lob, max_chars);
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

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(strnset, _ismbblead_l)]]
unsigned char *_mbsnbset_l([[inoutp(max_bytes)]] unsigned char *buf, unsigned int ch,
                           size_t max_bytes, $locale_t locale) {
	unsigned char *iter, lob, hib;
	lob = (ch & 0xff);
	hib = (ch & 0xff00) >> 8;
	if (!hib || !_ismbblead_l(lob, locale))
		return (unsigned char *)strnset((char *)buf, (int)lob, max_bytes);
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

@@Returs a byte-offset
[[wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l, _mbschr_l)]]
size_t _mbsspn_l([[nonnull]] unsigned char const *haystack,
                 [[nonnull]] unsigned char const *accept,
                 $locale_t locale) {
	unsigned char const *iter = haystack;
	for (;;) {
		uint16_t ch;
		unsigned char const *next;
		next = iter;
		ch   = *next++;
		if (!ch)
			break;
		if (_ismbblead_l(ch, locale))
			ch = *next ? (ch << 8) | *next++ : 0;
		if (!_mbschr_l(accept, ch, locale))
			break;
		iter = next;
	}
	return (size_t)(iter - haystack);
}

[[wunused, nullable, requires_function(_mbsspn_l)]]
unsigned char *_mbsspnp_l([[nonnull]] unsigned char const *haystack,
                          [[nonnull]] unsigned char const *accept,
                          $locale_t locale) {
	haystack += _mbsspn_l(haystack, accept, locale);
	if (*haystack == 0)
		haystack = NULL;
	return (unsigned char *)haystack;
}

[[wunused, requires_function(_ismbblead_l, _mbschr_l, _mbscmp_l, strlen, strcmpz)]]
unsigned char *_mbsstr_l([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *needle, $locale_t locale)
	[([[nonnull]] unsigned char *haystack, [[nonnull]] unsigned char const *needle, $locale_t locale): [[nullable]] unsigned char *]
	[([[nonnull]] unsigned char const *haystack, [[nonnull]] unsigned char const *needle, $locale_t locale): [[nullable]] unsigned char const *]
{
	uint16_t needle_first;
	size_t needle_first_len;
	size_t needle_len;
	needle_first     = *needle++;
	needle_first_len = 1;
	if (_ismbblead_l(needle_first, locale)) {
		needle_first     = *needle ? (needle_first << 8) | *needle++ : 0;
		needle_first_len = 2;
	}
	if unlikely(!needle_first)
		return NULL;
	needle_len = strlen((char const *)needle);

	/* Enumerate candidates */
	while ((haystack = _mbschr_l(haystack, needle_first, locale)) != NULL) {

		/* Skip first character. */
		haystack += needle_first_len;

		/* Check that all of the remaining bytes match. */
		if (strcmpz((char const *)needle, (char const *)haystack, needle_len) == 0)
			break; /* Found it! */
	}
	return (unsigned char *)haystack;
}

[[wunused, requires_function(_mbstok_s_l)]]
unsigned char *_mbstok_l([[nullable]] unsigned char *str,
                         [[nonnull]] unsigned char const *delim,
                         $locale_t locale) {
	static unsigned char *save_ptr = NULL;
	return _mbstok_s_l(str, delim, &save_ptr, locale);
}

[[wunused, requires_function(_mbsspn_l, _mbscspn_l)]]
unsigned char *_mbstok_s_l([[nullable]] unsigned char *str,
                           [[nonnull]] unsigned char const *delim,
                           [[nonnull]] unsigned char **__restrict save_ptr,
                           $locale_t locale) {
	unsigned char *end;
	if (!str)
		str = *save_ptr;
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	str += _mbsspn_l(str, delim, locale);
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	end = str + _mbscspn_l(str, delim, locale);
	if (!*end) {
		*save_ptr = end;
		return str;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return str;
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_function(_ismbblead_l)]]
size_t _mbclen_l([[nonnull]] unsigned char const *str, $locale_t locale) {
	size_t result = 1;
	if (_ismbblead_l(str[0], locale) && str[1])
		result = 2;
	return result;
}


/************************************************************************/
/* """safe""" versions of the above                                     */
/************************************************************************/

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(strcat_s)]]
/*dos*/ errno_t _mbscat_s_l([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                            [[nonnull]] unsigned char const *src, $locale_t locale) {
	(void)locale;
	return strcat_s((char *)buf, true_bufsize, (char const *)src);
}

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(strcpy_s)]]
/*dos*/ errno_t _mbscpy_s_l([[outp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                            [[nonnull]] unsigned char const *src, $locale_t locale) {
	(void)locale;
	return strcpy_s((char *)buf, true_bufsize, (char const *)src);
}

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(_mbslwr_l)]]
/*dos*/ errno_t _mbslwr_s_l([[outp(true_bufsize)]] unsigned char *buf,
                            size_t true_bufsize, $locale_t locale) {
	if (!buf || strlen((char const *)buf) >= true_bufsize)
		return DOS_EINVAL;
	_mbslwr_l(buf, locale);
	return 0;
}

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(_mbsupr_l)]]
/*dos*/ errno_t _mbsupr_s_l([[inoutp(true_bufsize)]] unsigned char *buf,
                            size_t true_bufsize, $locale_t locale) {
	if (!buf || strlen((char const *)buf) >= true_bufsize)
		return DOS_EINVAL;
	_mbsupr_l(buf, locale);
	return 0;
}

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(_mbsnbcat_l)]]
/*dos*/ errno_t _mbsnbcat_s_l([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                              [[inp(max_bytes)]] unsigned char const *src, size_t max_bytes,
                              $locale_t locale) {
	if (!buf || (!src && max_bytes) ||
	    true_bufsize <= strnlen((char const *)src, max_bytes))
		return DOS_EINVAL;
	_mbsnbcat_l(buf, src, max_bytes, locale);
	return 0;
}

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(_mbsnbcpy_l)]]
/*dos*/ errno_t _mbsnbcpy_s_l([[outp(bufsize)]] unsigned char *buf, size_t true_bufsize,
                              [[nonnull]] unsigned char const *src, size_t bufsize,
                              $locale_t locale) {
	if (bufsize && (!buf || !src || true_bufsize < bufsize))
		return DOS_EINVAL;
	_mbsnbcpy_l(buf, src, bufsize, locale);
	return 0;
}

[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/__minmax.h>")]]
[[requires_function(_mbsnbset_l)]]
/*dos*/ errno_t _mbsnbset_s_l([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                              unsigned int ch, size_t max_bytes, $locale_t locale) {
	if (max_bytes && (!buf || true_bufsize <= strnlen((char const *)buf, __hybrid_min2(true_bufsize, max_bytes))))
		return DOS_EINVAL;
	_mbsnbset_l(buf, ch, max_bytes, locale);
	return 0;
}

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(_mbsncat_l, _mbsnbcnt_l)]]
/*dos*/ errno_t _mbsncat_s_l([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                             [[nonnull]] unsigned char const *src, size_t max_chars,
                             $locale_t locale) {
	if (max_chars && (!buf || !src ||
	                  true_bufsize <= (strlen((char const *)buf) +
	                                   _mbsnbcnt_l(src, max_chars, locale))))
		return DOS_EINVAL;
	_mbsncat_l(buf, src, max_chars, locale);
	return 0;
}

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(_ismbblead_l)]]
/*dos*/ errno_t _mbsncpy_s_l([[outp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                             [[nonnull]] unsigned char const *src, size_t max_chars,
                             $locale_t locale) {
	if (max_chars && (!buf || !src))
		return DOS_EINVAL;
	for (; max_chars; --max_chars) {
		unsigned char ch;
		if (!true_bufsize)
			return DOS_EINVAL;
		--true_bufsize;
		*buf++ = ch = *src++;
		if (!ch)
			break;
		if (_ismbblead_l(ch, locale)) {
			if (!true_bufsize)
				return DOS_EINVAL;
			--true_bufsize;
			*buf++ = ch = *src++;
			if unlikely(!ch) {
				buf[-2] = '\0'; /* "fix" incomplete 2-byte character. */
				break;
			}
		}
	}
	if (true_bufsize < max_chars)
		return DOS_EINVAL;
	/* Really weird quirk: until this point, `max_chars' were countered
	 * in chars, but this zero-padding (which is also done by DOS), would
	 * mean that it's suddenly counted in characters... */
	bzero(buf, max_chars);
	return 0;
}

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(_mbsnset_l, strnlen)]]
/*dos*/ errno_t _mbsnset_s_l([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                             unsigned int ch, size_t max_chars, $locale_t locale) {
	if (max_chars && !buf)
		return DOS_EINVAL;
	if (max_chars > true_bufsize && true_bufsize == strnlen((char const *)buf, true_bufsize))
		return DOS_EINVAL;
	_mbsnset_l(buf, ch, max_chars, locale);
	return 0;
}

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(_mbsset_l, strnlen)]]
/*dos*/ errno_t _mbsset_s_l([[inoutp(true_bufsize)]] unsigned char *buf, size_t true_bufsize,
                            unsigned int ch, $locale_t locale) {
	if (!buf || true_bufsize == strnlen((char const *)buf, true_bufsize))
		return DOS_EINVAL;
	_mbsset_l(buf, ch, locale);
	return 0;
}

[[decl_include("<hybrid/typecore.h>", "<bits/types.h>")]]
[[requires_function(_ismbblead_l)]]
/*dos*/ errno_t _mbccpy_s_l([[outp(true_dstsize)]] unsigned char *dst, size_t true_dstsize,
                            [[nullable]] int *p_copied, [[nonnull]] unsigned char const *src,
                            $locale_t locale) {
	unsigned char ch;
	if (p_copied)
		*p_copied = 0;
	if (!dst || !src || !true_dstsize)
		return DOS_EINVAL;
	*dst = ch = *src;
	if (_ismbblead_l(ch, locale)) {
		if (true_dstsize < 2)
			return DOS_EINVAL;
		dst[1] = src[1];
		if (p_copied)
			*p_copied = 2;
	} else {
		if (p_copied)
			*p_copied = 1;
	}
	return 0;
}



/************************************************************************/
/* Character-traits functions                                           */
/************************************************************************/


[[wunused, requires_function(_ismbblead_l)]]
int _ismbslead_l([[nonnull]] unsigned char const *str,
                 [[nonnull]] unsigned char const *pos,
                 $locale_t locale) {
	while (str <= pos) {
		unsigned char ch = *str++;
		if (ch == 0)
			break;
		if (_ismbblead_l(ch, locale)) {
			if (str - 1 == pos)
				return -1; /* No, this isn't an error; this function just returns `-1' for "yes" */
			ch = *str++;
			if (ch == 0)
				break;
		}
	}
	return 0;
}

[[wunused, requires_function(_ismbblead_l)]]
int _ismbstrail_l([[nonnull]] unsigned char const *str,
                  [[nonnull]] unsigned char const *pos,
                  $locale_t locale) {
	while (str <= pos) {
		unsigned char ch = *str++;
		if (ch == 0)
			break;
		if (_ismbblead_l(ch, locale)) {
			if (str == pos)
				return -1; /* No, this isn't an error; this function just returns `-1' for "yes" */
			ch = *str++;
			if (ch == 0)
				break;
		}
	}
	return 0;
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
int _mbsbtype_l([[nonnull]] unsigned char const *str,
                size_t pos, $locale_t locale); /* TODO */

[[wunused]]
unsigned int _mbbtombc_l(unsigned int ch, $locale_t locale); /* TODO */

[[wunused]]
unsigned int _mbctombb_l(unsigned int ch, $locale_t locale); /* TODO */

[[wunused]]
int _mbbtype_l(unsigned char ch, int ctype, $locale_t locale); /* TODO */

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

%{

__SYSDECL_END
#endif /* __CC__ */

}
