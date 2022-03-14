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
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/mbctype.h) */
/* (#) Portability: Windows Kits (/ucrt/mbctype.h) */
}

%[default:section(".text.crt.dos.mbstring")]

%(auto_source){
#include "../libc/globals.h"
}

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/crt/ctype.h>
)]%{

#ifdef __USE_DOS
#include <crtdefs.h>
#endif /* __USE_DOS */

}

%
%
%{
/* Bits for `_mbctype' */
#define _MS    0x01 /* _ismbbkalnum: ... */
#define _MP    0x02 /* _ismbbkpunct: ... */
#define _M1    0x04 /* _ismbblead: First byte */
#define _M2    0x08 /* _ismbbtrail: Second byte */
#define _SBUP  0x10 /* _ismbcupper (for characters <= 0xff) */
#define _SBLOW 0x20 /* _ismbclower (for characters <= 0xff) */
/*efine        0x40  * ... */
/*efine        0x80  * ... */
}
%[define(_MS    = 0x01)] /* _ismbbkalnum: ... */
%[define(_MP    = 0x02)] /* _ismbbkpunct: ... */
%[define(_M1    = 0x04)] /* _ismbblead: First byte */
%[define(_M2    = 0x08)] /* _ismbbtrail: Second byte */
%[define(_SBUP  = 0x10)] /* _ismbcupper (for characters <= 0xff) */
%[define(_SBLOW = 0x20)] /* _ismbclower (for characters <= 0xff) */



%
%
%{
/* Values used by `_mbbtype_l(3)' and `_mbsbtype_l(3)' */
#define _MBC_SINGLE  0    /* Single-character byte (~ala `_MS') */
#define _MBC_LEAD    1    /* Lead byte (~ala `_ismbblead(3)') */
#define _MBC_TRAIL   2    /* Trail byte (~ala `_ismbbtrail(3)') */
#define _MBC_ILLEGAL (-1) /* Illegal character. */
}
%[define(_MBC_SINGLE  = 0)]    /* Single-character byte (~ala `_MS') */
%[define(_MBC_LEAD    = 1)]    /* Lead byte (~ala `_ismbblead(3)') */
%[define(_MBC_TRAIL   = 2)]    /* Trail byte (~ala `_ismbbtrail(3)') */
%[define(_MBC_ILLEGAL = (-1))] /* Illegal character. */



%
%
%{
/* Values for `_getmbcp(3)' / `_setmbcp(3)' */
#define _MB_CP_LOCALE (-4)
#define _MB_CP_ANSI   (-3)
#define _MB_CP_OEM    (-2)
#define _MB_CP_SBCS   0
#define _KANJI_CP     932
#define _MB_CP_UTF8   65001
}
%[define(_MB_CP_LOCALE = (-4))]
%[define(_MB_CP_ANSI   = (-3))]
%[define(_MB_CP_OEM    = (-2))]
%[define(_MB_CP_SBCS   = 0)]
%[define(_KANJI_CP     = 932)]
%[define(_MB_CP_UTF8   = 65001)]


%
%
%{
#ifdef __CC__
__SYSDECL_BEGIN

}


%{
#ifndef _mbctype
#ifdef __LOCAL__mbctype
#define _mbctype __LOCAL__mbctype
#elif defined(__CRT_HAVE__mbctype)
extern unsigned char _mbctype[];
#define _mbctype _mbctype
#else /* ... */
}
[[guard, const, nonnull, wunused]]
unsigned char *__p__mbctype(void);
%[insert:pp_if($has_function(__p__mbctype))]
%#define _mbctype __p__mbctype()
%[insert:pp_endif]
%{
#endif /* !... */
#endif /* !_mbctype */
}

%{
#ifndef _mbcasemap
#ifdef __LOCAL__mbcasemap
#define _mbcasemap __LOCAL__mbcasemap
#elif defined(__CRT_HAVE__mbcasemap)
extern unsigned char _mbcasemap[];
#define _mbcasemap _mbcasemap
#else /* ... */
}
[[guard, const, nonnull, wunused]]
unsigned char *__p__mbcasemap(void);
%[insert:pp_if($has_function(__p__mbcasemap))]
%#define _mbcasemap __p__mbcasemap()
%[insert:pp_endif]
%{
#endif /* !... */
#endif /* !_mbcasemap */
}


int _setmbcp(int cp);
[[pure, wunused]] int _getmbcp(void);

[[static, pure, wunused]]
[[requires_function(_getmbcp)]]
int _getmbcp_l($locale_t locale) {
	if (locale == NULL)
		return _getmbcp();
	return _MB_CP_UTF8; /* ??? */
}


%
%
%/* KOS extension: convert a multi-byte character to/from unicode (UTF-32) */
%#ifdef __USE_KOS
[[pure, wunused]] $char32_t _mbctouni_l(unsigned int ch, $locale_t locale);
[[pure, wunused]] unsigned int _unitombc_l($char32_t ch, $locale_t locale);
%#endif /* __USE_KOS */



/************************************************************************/
/* Traits functions                                                     */
/************************************************************************/

[[pure, wunused, requires_function(_ismbbkalnum_l), doc_alias("_ismbbkalnum_l")]]
int _ismbbkalnum(unsigned int ch) {
	return _ismbbkalnum_l(ch, NULL);
}

[[pure, wunused, requires_function(_ismbbkana_l), doc_alias("_ismbbkana_l")]]
[[export_alias("_ismbbkprint")]]
int _ismbbkana(unsigned int ch) {
	return _ismbbkana_l(ch, NULL);
}

[[pure, wunused, requires_function(_ismbbkpunct_l), doc_alias("_ismbbkpunct_l")]]
int _ismbbkpunct(unsigned int ch) {
	return _ismbbkpunct_l(ch, NULL);
}

_ismbbkprint(*) = _ismbbkana;

[[pure, wunused, requires_function(_ismbbalpha_l), doc_alias("_ismbbalpha_l")]]
int _ismbbalpha(unsigned int ch) {
	return _ismbbalpha_l(ch, NULL);
}

[[pure, wunused, requires_function(_ismbbpunct_l), doc_alias("_ismbbpunct_l")]]
int _ismbbpunct(unsigned int ch) {
	return _ismbbpunct_l(ch, NULL);
}

[[pure, wunused, requires_function(_ismbbblank_l), doc_alias("_ismbbblank_l")]]
int _ismbbblank(unsigned int ch) {
	return _ismbbblank_l(ch, NULL);
}

[[pure, wunused, requires_function(_ismbbalnum_l), doc_alias("_ismbbalnum_l")]]
int _ismbbalnum(unsigned int ch) {
	return _ismbbalnum_l(ch, NULL);
}

[[pure, wunused, requires_function(_ismbbprint_l), doc_alias("_ismbbprint_l")]]
int _ismbbprint(unsigned int ch) {
	return _ismbbprint_l(ch, NULL);
}

[[pure, wunused, requires_function(_ismbbgraph_l), doc_alias("_ismbbgraph_l")]]
int _ismbbgraph(unsigned int ch) {
	return _ismbbgraph_l(ch, NULL);
}

[[guard]] /* Also declared in <mbstring.h> */
[[pure, wunused, requires_function(_ismbblead_l), doc_alias("_ismbblead_l")]]
int _ismbblead(unsigned int ch) {
	return _ismbblead_l(ch, NULL);
}

[[guard]] /* Also declared in <mbstring.h> */
[[pure, wunused, requires_function(_ismbbtrail_l), doc_alias("_ismbbtrail_l")]]
int _ismbbtrail(unsigned int ch) {
	return _ismbbtrail_l(ch, NULL);
}



%[insert:extern(_ismbslead)]
%[insert:extern(_ismbstrail)]

[[pure, wunused, static]]
[[requires(defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype))]]
[[impl_include("<libc/template/mbctype.h>")]]
unsigned char _get_mbbtype_l(unsigned char ch, $locale_t locale) {
	if (locale == NULL)
		return (__LOCAL__mbctype + 1)[ch];
	return 0; /* XXX: locale support */
}


@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, guard]] /* Also declared in <mbstring.h> */
[[requires_function(_get_mbbtype_l)]]
int _ismbblead_l(unsigned int ch, $locale_t locale) {
	return _get_mbbtype_l((unsigned char)ch, locale) & _M1;
}

@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, guard]] /* Also declared in <mbstring.h> */
[[requires_function(_get_mbbtype_l)]]
int _ismbbtrail_l(unsigned int ch, $locale_t locale) {
	return _get_mbbtype_l((unsigned char)ch, locale) & _M2;
}

@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, requires_function(_get_mbbtype_l)]]
int _ismbbkalnum_l(unsigned int ch, $locale_t locale) {
	return _get_mbbtype_l((unsigned char)ch, locale) & _MS;
}

@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, export_alias("_ismbbkprint_l")]]
[[requires_function(_get_mbbtype_l)]]
int _ismbbkana_l(unsigned int ch, $locale_t locale) {
	return _get_mbbtype_l((unsigned char)ch, locale) & (_MS | _MP);
}

@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, requires_function(_get_mbbtype_l)]]
int _ismbbkpunct_l(unsigned int ch, $locale_t locale) {
	return _get_mbbtype_l((unsigned char)ch, locale) & _MP;
}

_ismbbkprint_l(*) = _ismbbkana_l;


@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, requires_function(isalpha_l, _ismbbkalnum_l)]]
int _ismbbalpha_l(unsigned int ch, $locale_t locale) {
	return isalpha_l(ch, locale) || _ismbbkalnum_l(ch, locale);
}

@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, requires_function(ispunct_l, _ismbbkpunct_l)]]
int _ismbbpunct_l(unsigned int ch, $locale_t locale) {
	return ispunct_l(ch, locale) || _ismbbkpunct_l(ch, locale);
}

@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, requires_function(isblank_l)]]
int _ismbbblank_l(unsigned int ch, $locale_t locale) {
	return isblank_l(ch, locale) || ch == '\t';
}

@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, requires_function(isalnum_l, _ismbbkalnum_l)]]
int _ismbbalnum_l(unsigned int ch, $locale_t locale) {
	return isalnum_l(ch, locale) || _ismbbkalnum_l(ch, locale);
}

@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, requires_function(isprint_l, _ismbbkprint_l)]]
int _ismbbprint_l(unsigned int ch, $locale_t locale) {
	return isprint_l(ch, locale) || _ismbbkprint_l(ch, locale);
}

@@@param: ch: Should actually be `unsigned char ch'
[[pure, wunused, requires_function(isgraph_l, _ismbbkprint_l)]]
int _ismbbgraph_l(unsigned int ch, $locale_t locale) {
	return isgraph_l(ch, locale) || _ismbbkprint_l(ch, locale);
}


%[insert:extern(_ismbblead_l)]
%[insert:extern(_ismbbtrail_l)]
%[insert:extern(_ismbslead_l)]
%[insert:extern(_ismbstrail_l)]



%{

__SYSDECL_END
#endif /* __CC__ */

}
