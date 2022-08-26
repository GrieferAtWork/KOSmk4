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
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/tchar.h) */
/* (#) Portability: Windows Kits (/ucrt/tchar.h) */
#ifndef _TCHAR_H
#define _TCHAR_H 1
#define _INC_TCHAR

#include <__stdinc.h>

#include <corecrt.h>

/* WARNING: Most of the stuff referenced by this header is only available with -D_DOS_SOURCE
 *          But also note  that `_DOS_SOURCE' automatically  gets defined under  `_MSC_VER'! */

#ifdef _UNICODE
#include <wchar.h>
#else /* _UNICODE */
#include <string.h>
#ifdef _MBCS
#include <mbstring.h>
#endif /* _MBCS */
#endif /* !_UNICODE */

#ifdef __CC__
#define _ftccmp      _tccmp
#define _ftccpy      _tccpy
#define _ftclen      _tclen
#define _ftcscat     _tcscat
#define _ftcschr     _tcschr
#define _ftcsclen    _tcsclen
#define _ftcscmp     _tcscmp
#define _ftcscoll    _tcscoll
#define _ftcscpy     _tcscpy
#define _ftcscspn    _tcscspn
#define _ftcsdec     _tcsdec
#define _ftcsdup     _tcsdup
#define _ftcsicmp    _tcsicmp
#define _ftcsicoll   _tcsicoll
#define _ftcsinc     _tcsinc
#define _ftcslen     _tcslen
#define _ftcslwr     _tcslwr
#define _ftcsnbcnt   _tcsnbcnt
#define _ftcsncat    _tcsncat
#define _ftcsnccat   _tcsnccat
#define _ftcsnccmp   _tcsnccmp
#define _ftcsnccnt   _tcsnccnt
#define _ftcsnccoll  _tcsnccoll
#define _ftcsnccpy   _tcsnccpy
#define _ftcsncicmp  _tcsncicmp
#define _ftcsncicoll _tcsncicoll
#define _ftcsncmp    _tcsncmp
#define _ftcsncoll   _tcsncoll
#define _ftcsncpy    _tcsncpy
#define _ftcsncset   _tcsncset
#define _ftcsnextc   _tcsnextc
#define _ftcsnicmp   _tcsnicmp
#define _ftcsnicoll  _tcsnicoll
#define _ftcsninc    _tcsninc
#define _ftcsnset    _tcsnset
#define _ftcspbrk    _tcspbrk
#define _ftcsrchr    _tcsrchr
#define _ftcsrev     _tcsrev
#define _ftcsset     _tcsset
#define _ftcsspn     _tcsspn
#define _ftcsspnp    _tcsspnp
#define _ftcsstr     _tcsstr
#define _ftcstok     _tcstok
#define _ftcsupr     _tcsupr


#define __strncnt(str, maxlen)                          strnlen(str, maxlen)
#define _strdec(cpc1, cpc2)                             ((cpc1) >= (cpc2) ? __NULLPTR : (cpc2)-1)
#define _strinc(pc)                                     ((pc) + 1)
#define _strncat_l(buf, src, buflen, locale)            strncat(buf, src, buflen)
#define _strncat_s_l(buf, dstsize, src, maxlen, locale) strncat_s(buf, dstsize, src, maxlen)
#define _strncnt(cpc, maxlen)                           __strncnt(cpc, maxlen)
#define _strncpy_l(buf, src, buflen, locale)            strncpy(buf, src, buflen)
#define _strncpy_s_l(buf, dstsize, src, maxlen, locale) strncpy_s(buf, dstsize, src, maxlen)
#define _strnextc(cpc)                                  ((unsigned int)*(unsigned char const *)(cpc))
#define _strninc(pc, size)                              ((pc) + (size))
#define _strnset_l(buf, ch, buflen, locale)             _strnset(buf, ch, buflen)
#define _strnset_s_l(buf, buflen, ch, maxlen, locale)   _strnset_s(buf, buflen, ch, maxlen)
#define _strset_l(buf, ch, locale)                      _strset(buf, ch)
#define _strset_s_l(buf, dstsize, ch, locale)           _strset_s(buf, dstsize, ch)
#define _strspnp(haystack, accept)                      ((haystack) == __NULLPTR ? __NULLPTR : *((haystack) + strspn(haystack, accept)) ? (haystack) + strspn(haystack, accept) : __NULLPTR)
#define _strtok_l(str, delim, locale)                   strtok(str, delim)
#define _strtok_s_l(str, delim, save_ptr, locale)       strtok_s(str, delim, save_ptr)

#define __wcsncnt(str, maxlen)                          wcsnlen(str, maxlen)
#define _wcsdec(cpc1, cpc2)                             ((cpc1) >= (cpc2) ? __NULLPTR : (cpc2)-1)
#define _wcsinc(pc)                                     ((pc) + 1)
#define _wcsncat_l(dst, src, buflen, locale)            wcsncat(dst, src, buflen)
#define _wcsncat_s_l(dst, dstsize, src, maxlen, locale) wcsncat_s(dst, dstsize, src, maxlen)
#define _wcsncnt(cpc, maxlen)                           __wcsncnt(cpc, maxlen)
#define _wcsncpy_l(dst, src, buflen, locale)            wcsncpy(dst, src, buflen)
#define _wcsncpy_s_l(dst, dstsize, src, maxlen, locale) wcsncpy_s(dst, dstsize, src, maxlen)
#define _wcsnextc(cpc)                                  ((unsigned int)*(cpc))
#define _wcsninc(pc, size)                              ((pc) + (size))
#define _wcsnset_l(dst, ch, buflen, locale)             _wcsnset(dst, ch, buflen)
#define _wcsnset_s_l(dst, buflen, ch, maxlen, locale)   _wcsnset_s(dst, buflen, ch, maxlen)
#define _wcsset_l(dst, ch, locale)                      _wcsset(dst, ch)
#define _wcsset_s_l(dst, buflen, ch, locale)            _wcsset_s(dst, buflen, ch)
#define _wcsspnp(haystack, accept)                      ((haystack) == __NULLPTR ? __NULLPTR : *((haystack) + wcsspn(haystack, accept)) ? (haystack) + wcsspn(haystack, accept) : __NULLPTR)
#define _wcstok_l(str, delim, locale)                   _wcstok(str, delim)
#define _wcstok_s_l(str, delim, save_ptr, locale)       wcstok_s(str, delim, save_ptr)

__DECL_BEGIN

#ifdef _UNICODE
#ifndef __TCHAR_DEFINED
#define __TCHAR_DEFINED
typedef wchar_t _TCHAR;
typedef wchar_t _TSCHAR;
typedef wchar_t _TUCHAR;
typedef wchar_t _TXCHAR;
typedef wint_t _TINT;
#endif /* __TCHAR_DEFINED */
#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
typedef wchar_t *PTBYTE;
typedef wchar_t *PTCHAR;
typedef wchar_t TBYTE;
typedef wchar_t TCHAR;
#endif /* _TCHAR_DEFINED */
#else /* _UNICODE */
#ifdef _MBCS
#ifndef __TCHAR_DEFINED
#define __TCHAR_DEFINED
typedef char _TCHAR;
typedef signed char _TSCHAR;
typedef unsigned char _TUCHAR;
typedef unsigned char _TXCHAR;
typedef unsigned int _TINT;
#endif /* __TCHAR_DEFINED */
#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
typedef char *PTCHAR;
typedef char TCHAR;
typedef unsigned char *PTBYTE;
typedef unsigned char TBYTE;
#endif /* _TCHAR_DEFINED */
#define _tccpy_s   _mbccpy_s
#define _tccpy_s_l _mbccpy_s_l
#else /* _MBCS */
#ifndef __TCHAR_DEFINED
#define __TCHAR_DEFINED
typedef char _TCHAR;
typedef char _TXCHAR;
typedef int _TINT;
typedef signed char _TSCHAR;
typedef unsigned char _TUCHAR;
#endif /* __TCHAR_DEFINED */
#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
typedef char *PTCHAR;
typedef char TCHAR;
typedef unsigned char *PTBYTE;
typedef unsigned char TBYTE;
#endif /* _TCHAR_DEFINED */
#endif /* !_MBCS */
#endif /* !_UNICODE */

__DECL_END

#ifndef _tccpy_s
#define _tccpy_s(dst, true_dstsize, p_copied, src)               \
	((dst) && (src) && (true_dstsize) >= 1                       \
	 ? ((p_copied) && (*(p_copied) = 1), (dst)[0] = (src)[0], 0) \
	 : ((p_copied) && (*(p_copied) = 0), 22))
#endif /* !_tccpy_s */
#ifndef _tccpy_s_l
#define _tccpy_s_l(dst, true_dstsize, p_copied, src, locale) \
	_tccpy_s(dst, true_dstsize, p_copied, src)
#endif /* !_tccpy_s_l */




/*[[[deemon
global final MAPPINGS = {
//  _TCHAR________________WCHAR________________CHAR_________________MBCS_
	("_TEOF",             "WEOF",              "EOF"),
	("__T",               "(x) L##x",          "(x) x"),
	("__targv",           "__wargv",           "__argv"),
	("__tcserror",        "__wcserror",        "_strerror"),
	("__tcserror_s",      "__wcserror_s",      "_strerror_s"),
	("_cgetts_s",         "_cgetws_s",         "_cgets_s"),
	("_cputts",           "_cputws",           "_cputs"),
	("_fgettc",           "fgetwc",            "fgetc"),
	("_fgettc_nolock",    "_fgetwc_nolock",    "_fgetc_nolock"),
	("_fgettchar",        "_fgetwchar",        "_fgetchar"),
	("_fgetts",           "fgetws",            "fgets"),
	("_fputtc",           "fputwc",            "fputc"),
	("_fputtc_nolock",    "_fputwc_nolock",    "_fputc_nolock"),
	("_fputtchar",        "_fputwchar",        "_fputchar"),
	("_fputts",           "fputws",            "fputs"),
	("_ftprintf",         "fwprintf",          "fprintf"),
	("_ftprintf_l",       "_fwprintf_l",       "_fprintf_l"),
	("_ftprintf_p",       "_fwprintf_p",       "_fprintf_p"),
	("_ftprintf_p_l",     "_fwprintf_p_l",     "_fprintf_p_l"),
	("_ftprintf_s",       "fwprintf_s",        "fprintf_s"),
	("_ftprintf_s_l",     "_fwprintf_s_l",     "_fprintf_s_l"),
	("_ftscanf",          "fwscanf",           "fscanf"),
	("_ftscanf_l",        "_fwscanf_l",        "_fscanf_l"),
	("_ftscanf_s",        "fwscanf_s",         "fscanf_s"),
	("_ftscanf_s_l",      "_fwscanf_s_l",      "_fscanf_s_l"),
	("_get_tpgmptr",      "_get_wpgmptr",      "_get_pgmptr"),
	("_gettc",            "getwc",             "getc"),
	("_gettc_nolock",     "_getwc_nolock",     "_getc_nolock"),
	("_gettch",           "_getwch",           "_getch"),
	("_gettch_nolock",    "_getwch_nolock",    "_getch_nolock"),
	("_gettchar",         "getwchar",          "getchar"),
	("_gettchar_nolock",  "_getwchar_nolock",  "_getchar_nolock"),
	("_gettche",          "_getwche",          "_getche"),
	("_gettche_nolock",   "_getwche_nolock",   "_getche_nolock"),
	("_getts_s",          "_getws_s",          "gets_s"),
	("_i64tot",           "_i64tow",           "_i64toa"),
	("_i64tot_s",         "_i64tow_s",         "_i64toa_s"),
	("_istalnum",         "iswalnum",          "isalnum",           "_ismbcalnum"),
	("_istalnum_l",       "_iswalnum_l",       "_isalnum_l",        "_ismbcalnum_l"),
	("_istalpha",         "iswalpha",          "isalpha",           "_ismbcalpha"),
	("_istalpha_l",       "_iswalpha_l",       "_isalpha_l",        "_ismbcalpha_l"),
	("_istascii",         "iswascii",          "__isascii"),
	("_istblank",         "iswblank",          "isblank",           "_ismbcblank"),
	("_istblank_l",       "_iswblank_l",       "_isblank_l",        "_ismbcblank_l"),
	("_istcntrl",         "iswcntrl",          "iscntrl"),
	("_istcntrl_l",       "_iswcntrl_l",       "_iscntrl_l"),
	("_istdigit",         "iswdigit",          "isdigit",           "_ismbcdigit"),
	("_istdigit_l",       "_iswdigit_l",       "_isdigit_l",        "_ismbcdigit_l"),
	("_istgraph",         "iswgraph",          "isgraph",           "_ismbcgraph"),
	("_istgraph_l",       "_iswgraph_l",       "_isgraph_l",        "_ismbcgraph_l"),
	("_istlead",          "(ch) 0",            "(ch) 0",            "_ismbblead"),
	("_istleadbyte",      "(ch) 0",            "(ch) 0",            "isleadbyte"),
	("_istleadbyte_l",    "(ch, locale) 0",    "(ch, locale) 0",    "_isleadbyte_l"),
	("_istlegal",         "(ch) 1",            "(ch) 1",            "_ismbclegal"),
	("_istlegal_l",       "(ch, locale) 1",    "(ch, locale) 1",    "_ismbclegal_l"),
	("_istlower",         "iswlower",          "islower",           "_ismbclower"),
	("_istlower_l",       "_iswlower_l",       "_islower_l",        "_ismbclower_l"),
	("_istprint",         "iswprint",          "isprint",           "_ismbcprint"),
	("_istprint_l",       "_iswprint_l",       "_isprint_l",        "_ismbcprint_l"),
	("_istpunct",         "iswpunct",          "ispunct",           "_ismbcpunct"),
	("_istpunct_l",       "_iswpunct_l",       "_ispunct_l",        "_ismbcpunct_l"),
	("_istspace",         "iswspace",          "isspace",           "_ismbcspace"),
	("_istspace_l",       "_iswspace_l",       "_isspace_l",        "_ismbcspace_l"),
	("_istupper",         "iswupper",          "isupper",           "_ismbcupper"),
	("_istupper_l",       "_iswupper_l",       "_isupper_l",        "_ismbcupper_l"),
	("_istxdigit",        "iswxdigit",         "isxdigit"),
	("_istxdigit_l",      "_iswxdigit_l",      "_isxdigit_l"),
	("_itot",             "_itow",             "_itoa"),
	("_itot_s",           "_itow_s",           "_itoa_s"),
	("_ltot",             "_ltow",             "_ltoa"),
	("_ltot_s",           "_ltow_s",           "_ltoa_s"),
	("_puttc",            "putwc",             "putc"),
	("_puttc_nolock",     "_fputwc_nolock",    "_fputc_nolock"),
	("_puttch",           "_putwch",           "_putch"),
	("_puttch_nolock",    "_putwch_nolock",    "_putch_nolock"),
	("_puttchar",         "putwchar",          "putchar"),
	("_puttchar_nolock",  "_putwchar_nolock",  "_putchar_nolock"),
	("_putts",            "_putws",            "puts"),
	("_sctprintf",        "_scwprintf",        "_scprintf"),
	("_sctprintf_l",      "_scwprintf_l",      "_scprintf_l"),
	("_sctprintf_p",      "_scwprintf_p",      "_scprintf_p"),
	("_sctprintf_p_l",    "_scwprintf_p_l",    "_scprintf_p_l"),
	("_sntprintf",        "_snwprintf",        "_snprintf"),
	("_sntprintf_l",      "_snwprintf_l",      "_snprintf_l"),
	("_sntprintf_s",      "_snwprintf_s",      "_snprintf_s"),
	("_sntprintf_s_l",    "_snwprintf_s_l",    "_snprintf_s_l"),
	("_sntscanf",         "_snwscanf",         "_snscanf"),
	("_sntscanf_l",       "_snwscanf_l",       "_snscanf_l"),
	("_sntscanf_s",       "_snwscanf_s",       "_snscanf_s"),
	("_sntscanf_s_l",     "_snwscanf_s_l",     "_snscanf_s_l"),
	("_stprintf",         "_swprintf",         "sprintf"),
	("_stprintf_l",       "__swprintf_l",      "_sprintf_l"),
	("_stprintf_p",       "_swprintf_p",       "_sprintf_p"),
	("_stprintf_p_l",     "_swprintf_p_l",     "_sprintf_p_l"),
	("_stprintf_s",       "swprintf_s",        "sprintf_s"),
	("_stprintf_s_l",     "_swprintf_s_l",     "_sprintf_s_l"),
	("_stscanf",          "swscanf",           "sscanf"),
	("_stscanf_l",        "_swscanf_l",        "_sscanf_l"),
	("_stscanf_s",        "swscanf_s",         "sscanf_s"),
	("_stscanf_s_l",      "_swscanf_s_l",      "_sscanf_s_l"),
	("_tWinMain",         "wWinMain",          "WinMain"),
	("_taccess",          "_waccess",          "_access"),
	("_taccess_s",        "_waccess_s",        "_access_s"),
	("_tasctime",         "_wasctime",         "asctime"),
	("_tasctime_s",       "_wasctime_s",       "asctime_s"),
	("_tccmp",            "(cpc1, cpc2) (*(cpc1) - *(cpc2))",              "(cpc1, cpc2) ((unsigned char)*(cpc1) - (unsigned char)*(cpc2))", "(cp1, cp2) _tcsnccmp(cp1, cp2, 1)"),
	("_tccpy",            "(pc1, cpc2) (*(pc1) = *(cpc2))",                "(pc1, cpc2) (*(pc1) = *(cpc2))",                                 "_mbccpy"),
	("_tccpy_l",          "(pc1, cpc2, locale) _tccpy(pc1, cpc2)",         "(pc1, cpc2, locale) _tccpy(pc1, cpc2)",                          "_mbccpy_l"),
	("_tchdir",           "_wchdir",           "_chdir"),
	("_tchmod",           "_wchmod",           "_chmod"),
	("_tclen",            "(str) 1",           "(str) 1",           "_mbclen"),
	("_tcprintf",         "_cwprintf",         "_cprintf"),
	("_tcprintf_l",       "_cwprintf_l",       "_cprintf_l"),
	("_tcprintf_p",       "_cwprintf_p",       "_cprintf_p"),
	("_tcprintf_p_l",     "_cwprintf_p_l",     "_cprintf_p_l"),
	("_tcprintf_s",       "_cwprintf_s",       "_cprintf_s"),
	("_tcprintf_s_l",     "_cwprintf_s_l",     "_cprintf_s_l"),
	("_tcreat",           "_wcreat",           "_creat"),
	("_tcscanf",          "_cwscanf",          "_cscanf"),
	("_tcscanf_l",        "_cwscanf_l",        "_cscanf_l"),
	("_tcscanf_s",        "_cwscanf_s",        "_cscanf_s"),
	("_tcscanf_s_l",      "_cwscanf_s_l",      "_cscanf_s_l"),
	("_tcscat",           "wcscat",            "strcat"),
	("_tcscat_s",         "wcscat_s",          "strcat_s"),
	("_tcschr",           "wcschr",            "strchr",            "_mbschr"),
	("_tcsclen",          "wcslen",            "strlen",            "_mbslen"),
	("_tcsclen_l",        "(str, locale) wcslen(str)",                     "(str, locale) strlen(str)",                                      "_mbslen_l"),
	("_tcscmp",           "wcscmp",            "strcmp",            "_mbscmp"),
	("_tcscnlen",         "wcsnlen",           "strnlen",           "_mbsnlen"),
	("_tcscnlen_l",       "(str, maxlen, locale) wcsnlen(str, maxlen)",    "(str, maxlen, locale) strnlen(str, maxlen)",                     "_mbsnlen_l"),
	("_tcscoll",          "wcscoll",           "strcoll",           "_mbscoll"),
	("_tcscoll_l",        "_wcscoll_l",        "_strcoll_l",        "_mbscoll_l"),
	("_tcscpy",           "wcscpy",            "strcpy"),
	("_tcscpy_s",         "wcscpy_s",          "strcpy_s"),
	("_tcscspn",          "wcscspn",           "strcspn",           "_mbscspn"),
	("_tcsdec",           "_wcsdec",           "_strdec",           "_mbsdec"),
	("_tcsdup",           "_wcsdup",           "_strdup"),
	("_tcsdup_dbg",       "_wcsdup_dbg",       "_strdup_dbg"),
	("_tcserror",         "_wcserror",         "strerror"),
	("_tcserror_s",       "_wcserror_s",       "strerror_s"),
	("_tcsftime",         "wcsftime",          "strftime"),
	("_tcsftime_l",       "_wcsftime_l",       "_strftime_l"),
	("_tcsicmp",          "_wcsicmp",          "_stricmp",          "_mbsicmp"),
	("_tcsicmp_l",        "_wcsicmp_l",        "_stricmp_l",        "_mbsicmp_l"),
	("_tcsicoll",         "_wcsicoll",         "_stricoll",         "_mbsicoll"),
	("_tcsicoll_l",       "_wcsicoll_l",       "_stricoll_l",       "_mbsicoll_l"),
	("_tcsinc",           "_wcsinc",           "_strinc",           "_mbsinc"),
	("_tcslen",           "wcslen",            "strlen"),
	("_tcslwr",           "_wcslwr",           "_strlwr",           "_mbslwr"),
	("_tcslwr_l",         "_wcslwr_l",         "_strlwr_l",         "_mbslwr_l"),
	("_tcslwr_s",         "_wcslwr_s",         "_strlwr_s",         "_mbslwr_s"),
	("_tcslwr_s_l",       "_wcslwr_s_l",       "_strlwr_s_l",       "_mbslwr_s_l"),
	("_tcsnbcnt",         "_wcsncnt",          "_strncnt",          "_mbsnbcnt"),
	("_tcsncat",          "wcsncat",           "strncat",           "_mbsnbcat"),
	("_tcsncat_l",        "_wcsncat_l",        "_strncat_l",        "_mbsnbcat_l"),
	("_tcsncat_s",        "wcsncat_s",         "strncat_s",         "_mbsnbcat_s"),
	("_tcsncat_s_l",      "_wcsncat_s_l",      "_strncat_s_l",      "_mbsnbcat_s_l"),
	("_tcsnccat",         "wcsncat",           "strncat",           "_mbsncat"),
	("_tcsnccat_l",       "_wcsncat_l",        "_strncat_l",        "_mbsncat_l"),
	("_tcsnccat_s",       "wcsncat_s",         "strncat_s",         "_mbsncat_s"),
	("_tcsnccat_s_l",     "_wcsncat_s_l",      "_strncat_s_l",      "_mbsncat_s_l"),
	("_tcsnccmp",         "wcsncmp",           "strncmp",           "_mbsncmp"),
	("_tcsnccnt",         "_wcsncnt",          "_strncnt",          "_mbsnccnt"),
	("_tcsnccoll",        "_wcsncoll",         "_strncoll",         "_mbsncoll"),
	("_tcsnccoll_l",      "_wcsncoll_l",       "_strncoll_l",       "_mbsncoll_l"),
	("_tcsnccpy",         "wcsncpy",           "strncpy",           "_mbsncpy"),
	("_tcsnccpy_l",       "_wcsncpy_l",        "_strncpy_l",        "_mbsncpy_l"),
	("_tcsnccpy_s",       "wcsncpy_s",         "strncpy_s",         "_mbsncpy_s"),
	("_tcsnccpy_s_l",     "_wcsncpy_s_l",      "_strncpy_s_l",      "_mbsncpy_s_l"),
	("_tcsncicmp",        "_wcsnicmp",         "_strnicmp",         "_mbsnicmp"),
	("_tcsncicmp_l",      "_wcsnicmp_l",       "_strnicmp_l",       "_mbsnicmp_l"),
	("_tcsncicoll",       "_wcsnicoll",        "_strnicoll",        "_mbsnicoll"),
	("_tcsncicoll_l",     "_wcsnicoll_l",      "_strnicoll_l",      "_mbsnicoll_l"),
	("_tcsncmp",          "wcsncmp",           "strncmp",           "_mbsnbcmp"),
	("_tcsncoll",         "_wcsncoll",         "_strncoll",         "_mbsnbcoll"),
	("_tcsncoll_l",       "_wcsncoll_l",       "_strncoll_l",       "_mbsnbcoll_l"),
	("_tcsncpy",          "wcsncpy",           "strncpy",           "_mbsnbcpy"),
	("_tcsncpy_l",        "_wcsncpy_l",        "_strncpy_l",        "_mbsnbcpy_l"),
	("_tcsncpy_s",        "wcsncpy_s",         "strncpy_s",         "_mbsnbcpy_s"),
	("_tcsncpy_s_l",      "_wcsncpy_s_l",      "_strncpy_s_l",      "_mbsnbcpy_s_l"),
	("_tcsncset",         "_wcsnset",          "_strnset",          "_mbsnset"),
	("_tcsncset_l",       "_wcsnset_l",        "_strnset_l",        "_mbsnset_l"),
	("_tcsncset_s",       "_wcsnset_s",        "_strnset_s",        "_mbsnset_s"),
	("_tcsncset_s_l",     "_wcsnset_s_l",      "_strnset_s_l",      "_mbsnset_s_l"),
	("_tcsnextc",         "_wcsnextc",         "_strnextc",         "_mbsnextc"),
	("_tcsnicmp",         "_wcsnicmp",         "_strnicmp",         "_mbsnbicmp"),
	("_tcsnicmp_l",       "_wcsnicmp_l",       "_strnicmp_l",       "_mbsnbicmp_l"),
	("_tcsnicoll",        "_wcsnicoll",        "_strnicoll",        "_mbsnbicoll"),
	("_tcsnicoll_l",      "_wcsnicoll_l",      "_strnicoll_l",      "_mbsnbicoll_l"),
	("_tcsninc",          "_wcsninc",          "_strninc",          "_mbsninc"),
	("_tcsnlen",          "wcsnlen",           "strnlen"),
	("_tcsnset",          "_wcsnset",          "_strnset",          "_mbsnbset"),
	("_tcsnset_l",        "_wcsnset_l",        "_strnset_l",        "_mbsnbset_l"),
	("_tcsnset_s",        "_wcsnset_s",        "_strnset_s",        "_mbsnbset_s"),
	("_tcsnset_s_l",      "_wcsnset_s_l",      "_strnset_s_l",      "_mbsnbset_s_l"),
	("_tcspbrk",          "wcspbrk",           "strpbrk",           "_mbspbrk"),
	("_tcsrchr",          "wcsrchr",           "strrchr",           "_mbsrchr"),
	("_tcsrev",           "_wcsrev",           "_strrev",           "_mbsrev"),
	("_tcsset",           "_wcsset",           "_strset",           "_mbsset"),
	("_tcsset_l",         "_wcsset_l",         "_strset_l",         "_mbsset_l"),
	("_tcsset_s",         "_wcsset_s",         "_strset_s",         "_mbsset_s"),
	("_tcsset_s_l",       "_wcsset_s_l",       "_strset_s_l",       "_mbsset_s_l"),
	("_tcsspn",           "wcsspn",            "strspn",            "_mbsspn"),
	("_tcsspnp",          "_wcsspnp",          "_strspnp",          "_mbsspnp"),
	("_tcsstr",           "wcsstr",            "strstr",            "_mbsstr"),
	("_tcstod",           "wcstod",            "strtod"),
	("_tcstod_l",         "_wcstod_l",         "_strtod_l"),
	("_tcstof",           "wcstof",            "strtof"),
	("_tcstof_l",         "_wcstof_l",         "_strtof_l"),
	("_tcstoi64",         "_wcstoi64",         "_strtoi64"),
	("_tcstoi64_l",       "_wcstoi64_l",       "_strtoi64_l"),
	("_tcstoimax",        "wcstoimax",         "strtoimax"),
	("_tcstoimax_l",      "_wcstoimax_l",      "_strtoimax_l"),
	("_tcstok",           "_wcstok",           "strtok",            "_mbstok"),
	("_tcstok_l",         "_wcstok_l",         "_strtok_l",         "_mbstok_l"),
	("_tcstok_s",         "wcstok_s",          "strtok_s",          "_mbstok_s"),
	("_tcstok_s_l",       "_wcstok_s_l",       "_strtok_s_l",       "_mbstok_s_l"),
	("_tcstol",           "wcstol",            "strtol"),
	("_tcstol_l",         "_wcstol_l",         "_strtol_l"),
	("_tcstold",          "wcstold",           "strtold"),
	("_tcstold_l",        "_wcstold_l",        "_strtold_l"),
	("_tcstoll",          "wcstoll",           "strtoll"),
	("_tcstoll_l",        "_wcstoll_l",        "_strtoll_l"),
	("_tcstoui64",        "_wcstoui64",        "_strtoui64"),
	("_tcstoui64_l",      "_wcstoui64_l",      "_strtoui64_l"),
	("_tcstoul",          "wcstoul",           "strtoul"),
	("_tcstoul_l",        "_wcstoul_l",        "_strtoul_l"),
	("_tcstoull",         "wcstoull",          "strtoull"),
	("_tcstoull_l",       "_wcstoull_l",       "_strtoull_l"),
	("_tcstoumax",        "wcstoumax",         "strtoumax"),
	("_tcstoumax_l",      "_wcstoumax_l",      "_strtoumax_l"),
	("_tcsupr",           "_wcsupr",           "_strupr",           "_mbsupr"),
	("_tcsupr_l",         "_wcsupr_l",         "_strupr_l",         "_mbsupr_l"),
	("_tcsupr_s",         "_wcsupr_s",         "_strupr_s",         "_mbsupr_s"),
	("_tcsupr_s_l",       "_wcsupr_s_l",       "_strupr_s_l",       "_mbsupr_s_l"),
	("_tcsxfrm",          "wcsxfrm",           "strxfrm"),
	("_tcsxfrm_l",        "_wcsxfrm_l",        "_strxfrm_l"),
	("_tctime",           "_wctime",           "ctime"),
	("_tctime32",         "_wctime32",         "_ctime32"),
	("_tctime32_s",       "_wctime32_s",       "_ctime32_s"),
	("_tctime64",         "_wctime64",         "_ctime64"),
	("_tctime64_s",       "_wctime64_s",       "_ctime64_s"),
	("_tctime_s",         "_wctime_s",         "ctime_s"),
	("_tdupenv_s",        "_wdupenv_s",        "_dupenv_s"),
	("_tdupenv_s_dbg",    "_wdupenv_s_dbg",    "_dupenv_s_dbg"),
	("_tenviron",         "_wenviron",         "_environ"),
	("_texecl",           "_wexecl",           "_execl"),
	("_texecle",          "_wexecle",          "_execle"),
	("_texeclp",          "_wexeclp",          "_execlp"),
	("_texeclpe",         "_wexeclpe",         "_execlpe"),
	("_texecv",           "_wexecv",           "_execv"),
	("_texecve",          "_wexecve",          "_execve"),
	("_texecvp",          "_wexecvp",          "_execvp"),
	("_texecvpe",         "_wexecvpe",         "_execvpe"),
	("_tfdopen",          "_wfdopen",          "_fdopen"),
	("_tfinddata32_t",    "_wfinddata32_t",    "_finddata32_t"),
	("_tfinddata32i64_t", "_wfinddata32i64_t", "_finddata32i64_t"),
	("_tfinddata64_t",    "_wfinddata64_t",    "__finddata64_t"),
	("_tfinddata64i32_t", "_wfinddata64i32_t", "_finddata64i32_t"),
	("_tfinddata_t",      "_wfinddata_t",      "_finddata_t"),
	("_tfinddatai64_t",   "_wfinddatai64_t",   "_finddatai64_t"),
	("_tfindfirst",       "_wfindfirst",       "_findfirst"),
	("_tfindfirst32",     "_wfindfirst32",     "_findfirst32"),
	("_tfindfirst32i64",  "_wfindfirst32i64",  "_findfirst32i64"),
	("_tfindfirst64",     "_wfindfirst64",     "_findfirst64"),
	("_tfindfirst64i32",  "_wfindfirst64i32",  "_findfirst64i32"),
	("_tfindfirsti64",    "_wfindfirsti64",    "_findfirsti64"),
	("_tfindnext",        "_wfindnext",        "_findnext"),
	("_tfindnext32",      "_wfindnext32",      "_findnext32"),
	("_tfindnext32i64",   "_wfindnext32i64",   "_findnext32i64"),
	("_tfindnext64",      "_wfindnext64",      "_findnext64"),
	("_tfindnext64i32",   "_wfindnext64i32",   "_findnext64i32"),
	("_tfindnexti64",     "_wfindnexti64",     "_findnexti64"),
	("_tfopen",           "_wfopen",           "fopen"),
	("_tfopen_s",         "_wfopen_s",         "fopen_s"),
	("_tfreopen",         "_wfreopen",         "freopen"),
	("_tfreopen_s",       "_wfreopen_s",       "freopen_s"),
	("_tfsopen",          "_wfsopen",          "_fsopen"),
	("_tfullpath",        "_wfullpath",        "_fullpath"),
	("_tfullpath_dbg",    "_wfullpath_dbg",    "_fullpath_dbg"),
	("_tgetcwd",          "_wgetcwd",          "_getcwd"),
	("_tgetcwd_dbg",      "_wgetcwd_dbg",      "_getcwd_dbg"),
	("_tgetdcwd",         "_wgetdcwd",         "_getdcwd"),
	("_tgetdcwd_dbg",     "_wgetdcwd_dbg",     "_getdcwd_dbg"),
	("_tgetdcwd_lk_dbg",  "_wgetdcwd_lk_dbg",  "_getdcwd_lk_dbg"),
	("_tgetdcwd_nolock",  "_wgetdcwd_nolock",  "_getdcwd_nolock"),
	("_tgetenv",          "_wgetenv",          "getenv"),
	("_tgetenv_s",        "_wgetenv_s",        "getenv_s"),
	("_tmain",            "wmain",             "main"),
	("_tmakepath",        "_wmakepath",        "_makepath"),
	("_tmakepath_s",      "_wmakepath_s",      "_makepath_s"),
	("_tmkdir",           "_wmkdir",           "_mkdir"),
	("_tmktemp",          "_wmktemp",          "_mktemp"),
	("_tmktemp_s",        "_wmktemp_s",        "_mktemp_s"),
	("_topen",            "_wopen",            "_open"),
	("_totlower",         "towlower",          "tolower",           "_mbctolower"),
	("_totlower_l",       "_towlower_l",       "_tolower_l",        "_mbctolower_l"),
	("_totupper",         "towupper",          "toupper",           "_mbctoupper"),
	("_totupper_l",       "_towupper_l",       "_toupper_l",        "_mbctoupper_l"),
	("_tperror",          "_wperror",          "perror"),
	("_tpgmptr",          "_wpgmptr",          "_pgmptr"),
	("_tpopen",           "_wpopen",           "_popen"),
	("_tprintf",          "wprintf",           "printf"),
	("_tprintf_l",        "_wprintf_l",        "_printf_l"),
	("_tprintf_p",        "_wprintf_p",        "_printf_p"),
	("_tprintf_p_l",      "_wprintf_p_l",      "_printf_p_l"),
	("_tprintf_s",        "wprintf_s",         "printf_s"),
	("_tprintf_s_l",      "_wprintf_s_l",      "_printf_s_l"),
	("_tputenv",          "_wputenv",          "_putenv"),
	("_tputenv_s",        "_wputenv_s",        "_putenv_s"),
	("_tremove",          "_wremove",          "remove"),
	("_trename",          "_wrename",          "rename"),
	("_trmdir",           "_wrmdir",           "_rmdir"),
	("_tscanf",           "wscanf",            "scanf"),
	("_tscanf_l",         "_wscanf_l",         "_scanf_l"),
	("_tscanf_s",         "wscanf_s",          "scanf_s"),
	("_tscanf_s_l",       "_wscanf_s_l",       "_scanf_s_l"),
	("_tsearchenv",       "_wsearchenv",       "_searchenv"),
	("_tsearchenv_s",     "_wsearchenv_s",     "_searchenv_s"),
	("_tsetlocale",       "_wsetlocale",       "setlocale"),
	("_tsopen",           "_wsopen",           "_sopen"),
	("_tsopen_s",         "_wsopen_s",         "_sopen_s"),
	("_tspawnl",          "_wspawnl",          "_spawnl"),
	("_tspawnle",         "_wspawnle",         "_spawnle"),
	("_tspawnlp",         "_wspawnlp",         "_spawnlp"),
	("_tspawnlpe",        "_wspawnlpe",        "_spawnlpe"),
	("_tspawnv",          "_wspawnv",          "_spawnv"),
	("_tspawnve",         "_wspawnve",         "_spawnve"),
	("_tspawnvp",         "_wspawnvp",         "_spawnvp"),
	("_tspawnvpe",        "_wspawnvpe",        "_spawnvpe"),
	("_tsplitpath",       "_wsplitpath",       "_splitpath"),
	("_tsplitpath_s",     "_wsplitpath_s",     "_splitpath_s"),
	("_tstat",            "_wstat",            "_stat"),
	("_tstat32",          "_wstat32",          "_stat32"),
	("_tstat32i64",       "_wstat32i64",       "_stat32i64"),
	("_tstat64",          "_wstat64",          "_stat64"),
	("_tstat64i32",       "_wstat64i32",       "_stat64i32"),
	("_tstati64",         "_wstati64",         "_stati64"),
	("_tstof",            "_wtof",             "atof"),
	("_tstof_l",          "_wtof_l",           "_atof_l"),
	("_tstoi",            "_wtoi",             "atoi"),
	("_tstoi64",          "_wtoi64",           "_atoi64"),
	("_tstoi64_l",        "_wtoi64_l",         "_atoi64_l"),
	("_tstoi_l",          "_wtoi_l",           "_atoi_l"),
	("_tstol",            "_wtol",             "atol"),
	("_tstol_l",          "_wtol_l",           "_atol_l"),
	("_tstoll",           "_wtoll",            "atoll"),
	("_tstoll_l",         "_wtoll_l",          "_atoll_l"),
	("_tstrdate",         "_wstrdate",         "_strdate"),
	("_tstrdate_s",       "_wstrdate_s",       "_strdate_s"),
	("_tstrtime",         "_wstrtime",         "_strtime"),
	("_tstrtime_s",       "_wstrtime_s",       "_strtime_s"),
	("_tsystem",          "_wsystem",          "system"),
	("_ttempnam",         "_wtempnam",         "_tempnam"),
	("_ttempnam_dbg",     "_wtempnam_dbg",     "_tempnam_dbg"),
	("_ttmpnam",          "_wtmpnam",          "tmpnam"),
	("_ttmpnam_s",        "_wtmpnam_s",        "tmpnam_s"),
	("_ttof",             "_wtof",             "atof"),
	("_ttoi",             "_wtoi",             "atoi"),
	("_ttoi64",           "_wtoi64",           "_atoi64"),
	("_ttol",             "_wtol",             "atol"),
	("_ttoll",            "_wtoll",            "atoll"),
	("_tunlink",          "_wunlink",          "_unlink"),
	("_tutime",           "_wutime",           "_utime"),
	("_tutime32",         "_wutime32",         "_utime32"),
	("_tutime64",         "_wutime64",         "_utime64"),
	("_ui64tot",          "_ui64tow",          "_ui64toa"),
	("_ui64tot_s",        "_ui64tow_s",        "_ui64toa_s"),
	("_ultot",            "_ultow",            "_ultoa"),
	("_ultot_s",          "_ultow_s",          "_ultoa_s"),
	("_ungettc",          "ungetwc",           "ungetc"),
	("_ungettc_nolock",   "_ungetwc_nolock",   "_ungetc_nolock"),
	("_ungettch",         "_ungetwch",         "_ungetch"),
	("_ungettch_nolock",  "_ungetwch_nolock",  "_ungetch_nolock"),
	("_vftprintf",        "vfwprintf",         "vfprintf"),
	("_vftprintf_l",      "_vfwprintf_l",      "_vfprintf_l"),
	("_vftprintf_p",      "_vfwprintf_p",      "_vfprintf_p"),
	("_vftprintf_p_l",    "_vfwprintf_p_l",    "_vfprintf_p_l"),
	("_vftprintf_s",      "vfwprintf_s",       "vfprintf_s"),
	("_vftprintf_s_l",    "_vfwprintf_s_l",    "_vfprintf_s_l"),
	("_vftscanf",         "vfwscanf",          "vfscanf"),
	("_vftscanf_s",       "vfwscanf_s",        "vfscanf_s"),
	("_vsctprintf",       "_vscwprintf",       "_vscprintf"),
	("_vsctprintf_l",     "_vscwprintf_l",     "_vscprintf_l"),
	("_vsctprintf_p",     "_vscwprintf_p",     "_vscprintf_p"),
	("_vsctprintf_p_l",   "_vscwprintf_p_l",   "_vscprintf_p_l"),
	("_vsntprintf",       "_vsnwprintf",       "_vsnprintf"),
	("_vsntprintf_l",     "_vsnwprintf_l",     "_vsnprintf_l"),
	("_vsntprintf_s",     "_vsnwprintf_s",     "_vsnprintf_s"),
	("_vsntprintf_s_l",   "_vsnwprintf_s_l",   "_vsnprintf_s_l"),
	("_vstprintf",        "vswprintf",         "vsprintf"),
	("_vstprintf_l",      "_vswprintf_l",      "_vsprintf_l"),
	("_vstprintf_p",      "_vswprintf_p",      "_vsprintf_p"),
	("_vstprintf_p_l",    "_vswprintf_p_l",    "_vsprintf_p_l"),
	("_vstprintf_s",      "vswprintf_s",       "vsprintf_s"),
	("_vstprintf_s_l",    "_vswprintf_s_l",    "_vsprintf_s_l"),
	("_vstscanf",         "vswscanf",          "vsscanf"),
	("_vstscanf_s",       "vswscanf_s",        "vsscanf_s"),
	("_vtcprintf",        "_vcwprintf",        "_vcprintf"),
	("_vtcprintf_l",      "_vcwprintf_l",      "_vcprintf_l"),
	("_vtcprintf_p",      "_vcwprintf_p",      "_vcprintf_p"),
	("_vtcprintf_p_l",    "_vcwprintf_p_l",    "_vcprintf_p_l"),
	("_vtcprintf_s",      "_vcwprintf_s",      "_vcprintf_s"),
	("_vtcprintf_s_l",    "_vcwprintf_s_l",    "_vcprintf_s_l"),
	("_vtprintf",         "vwprintf",          "vprintf"),
	("_vtprintf_l",       "_vwprintf_l",       "_vprintf_l"),
	("_vtprintf_p",       "_vwprintf_p",       "_vprintf_p"),
	("_vtprintf_p_l",     "_vwprintf_p_l",     "_vprintf_p_l"),
	("_vtprintf_s",       "vwprintf_s",        "vprintf_s"),
	("_vtprintf_s_l",     "_vwprintf_s_l",     "_vprintf_s_l"),
	("_vtscanf",          "vwscanf",           "vscanf"),
	("_vtscanf_s",        "vwscanf_s",         "vscanf_s"),
};

local MBCS = [];
local NOMBCS = [];

for (local x: MAPPINGS) {
	if (#x == 4) {
		MBCS.append(x);
	} else {
		NOMBCS.append(x);
	}
}

function printMappings(table, index) {
	local pairs = [];
	for (local x: table) {
		local name = x.first;
		local decl = x[index];
		if (decl.startswith("(")) {
			local a;
			a, none, decl = decl.partition(")")...;
			name = f"{name}{a})";
			decl = decl.lstrip();
		}
		pairs.append((name, decl));
	}
	local longestNameLen = pairs.each.first.length > ...;
	for (local lhs, rhs: pairs) {
		print("#define ", lhs.ljust(longestNameLen), " ", rhs);
	}
}

print("#ifdef _UNICODE");
printMappings(MAPPINGS, 1);
print("#else /" "* _UNICODE *" "/");
printMappings(NOMBCS, 2);
print("#ifdef _MBCS");
printMappings(MBCS, 3);
print("#else /" "* _MBCS *" "/");
printMappings(MBCS, 2);
print("#endif /" "* !_MBCS *" "/");
print("#endif /" "* !_UNICODE *" "/");

]]]*/
#ifdef _UNICODE
#define _TEOF                            WEOF
#define __T(x)                           L##x
#define __targv                          __wargv
#define __tcserror                       __wcserror
#define __tcserror_s                     __wcserror_s
#define _cgetts_s                        _cgetws_s
#define _cputts                          _cputws
#define _fgettc                          fgetwc
#define _fgettc_nolock                   _fgetwc_nolock
#define _fgettchar                       _fgetwchar
#define _fgetts                          fgetws
#define _fputtc                          fputwc
#define _fputtc_nolock                   _fputwc_nolock
#define _fputtchar                       _fputwchar
#define _fputts                          fputws
#define _ftprintf                        fwprintf
#define _ftprintf_l                      _fwprintf_l
#define _ftprintf_p                      _fwprintf_p
#define _ftprintf_p_l                    _fwprintf_p_l
#define _ftprintf_s                      fwprintf_s
#define _ftprintf_s_l                    _fwprintf_s_l
#define _ftscanf                         fwscanf
#define _ftscanf_l                       _fwscanf_l
#define _ftscanf_s                       fwscanf_s
#define _ftscanf_s_l                     _fwscanf_s_l
#define _get_tpgmptr                     _get_wpgmptr
#define _gettc                           getwc
#define _gettc_nolock                    _getwc_nolock
#define _gettch                          _getwch
#define _gettch_nolock                   _getwch_nolock
#define _gettchar                        getwchar
#define _gettchar_nolock                 _getwchar_nolock
#define _gettche                         _getwche
#define _gettche_nolock                  _getwche_nolock
#define _getts_s                         _getws_s
#define _i64tot                          _i64tow
#define _i64tot_s                        _i64tow_s
#define _istalnum                        iswalnum
#define _istalnum_l                      _iswalnum_l
#define _istalpha                        iswalpha
#define _istalpha_l                      _iswalpha_l
#define _istascii                        iswascii
#define _istblank                        iswblank
#define _istblank_l                      _iswblank_l
#define _istcntrl                        iswcntrl
#define _istcntrl_l                      _iswcntrl_l
#define _istdigit                        iswdigit
#define _istdigit_l                      _iswdigit_l
#define _istgraph                        iswgraph
#define _istgraph_l                      _iswgraph_l
#define _istlead(ch)                     0
#define _istleadbyte(ch)                 0
#define _istleadbyte_l(ch, locale)       0
#define _istlegal(ch)                    1
#define _istlegal_l(ch, locale)          1
#define _istlower                        iswlower
#define _istlower_l                      _iswlower_l
#define _istprint                        iswprint
#define _istprint_l                      _iswprint_l
#define _istpunct                        iswpunct
#define _istpunct_l                      _iswpunct_l
#define _istspace                        iswspace
#define _istspace_l                      _iswspace_l
#define _istupper                        iswupper
#define _istupper_l                      _iswupper_l
#define _istxdigit                       iswxdigit
#define _istxdigit_l                     _iswxdigit_l
#define _itot                            _itow
#define _itot_s                          _itow_s
#define _ltot                            _ltow
#define _ltot_s                          _ltow_s
#define _puttc                           putwc
#define _puttc_nolock                    _fputwc_nolock
#define _puttch                          _putwch
#define _puttch_nolock                   _putwch_nolock
#define _puttchar                        putwchar
#define _puttchar_nolock                 _putwchar_nolock
#define _putts                           _putws
#define _sctprintf                       _scwprintf
#define _sctprintf_l                     _scwprintf_l
#define _sctprintf_p                     _scwprintf_p
#define _sctprintf_p_l                   _scwprintf_p_l
#define _sntprintf                       _snwprintf
#define _sntprintf_l                     _snwprintf_l
#define _sntprintf_s                     _snwprintf_s
#define _sntprintf_s_l                   _snwprintf_s_l
#define _sntscanf                        _snwscanf
#define _sntscanf_l                      _snwscanf_l
#define _sntscanf_s                      _snwscanf_s
#define _sntscanf_s_l                    _snwscanf_s_l
#define _stprintf                        _swprintf
#define _stprintf_l                      __swprintf_l
#define _stprintf_p                      _swprintf_p
#define _stprintf_p_l                    _swprintf_p_l
#define _stprintf_s                      swprintf_s
#define _stprintf_s_l                    _swprintf_s_l
#define _stscanf                         swscanf
#define _stscanf_l                       _swscanf_l
#define _stscanf_s                       swscanf_s
#define _stscanf_s_l                     _swscanf_s_l
#define _tWinMain                        wWinMain
#define _taccess                         _waccess
#define _taccess_s                       _waccess_s
#define _tasctime                        _wasctime
#define _tasctime_s                      _wasctime_s
#define _tccmp(cpc1, cpc2)               (*(cpc1) - *(cpc2))
#define _tccpy(pc1, cpc2)                (*(pc1) = *(cpc2))
#define _tccpy_l(pc1, cpc2, locale)      _tccpy(pc1, cpc2)
#define _tchdir                          _wchdir
#define _tchmod                          _wchmod
#define _tclen(str)                      1
#define _tcprintf                        _cwprintf
#define _tcprintf_l                      _cwprintf_l
#define _tcprintf_p                      _cwprintf_p
#define _tcprintf_p_l                    _cwprintf_p_l
#define _tcprintf_s                      _cwprintf_s
#define _tcprintf_s_l                    _cwprintf_s_l
#define _tcreat                          _wcreat
#define _tcscanf                         _cwscanf
#define _tcscanf_l                       _cwscanf_l
#define _tcscanf_s                       _cwscanf_s
#define _tcscanf_s_l                     _cwscanf_s_l
#define _tcscat                          wcscat
#define _tcscat_s                        wcscat_s
#define _tcschr                          wcschr
#define _tcsclen                         wcslen
#define _tcsclen_l(str, locale)          wcslen(str)
#define _tcscmp                          wcscmp
#define _tcscnlen                        wcsnlen
#define _tcscnlen_l(str, maxlen, locale) wcsnlen(str, maxlen)
#define _tcscoll                         wcscoll
#define _tcscoll_l                       _wcscoll_l
#define _tcscpy                          wcscpy
#define _tcscpy_s                        wcscpy_s
#define _tcscspn                         wcscspn
#define _tcsdec                          _wcsdec
#define _tcsdup                          _wcsdup
#define _tcsdup_dbg                      _wcsdup_dbg
#define _tcserror                        _wcserror
#define _tcserror_s                      _wcserror_s
#define _tcsftime                        wcsftime
#define _tcsftime_l                      _wcsftime_l
#define _tcsicmp                         _wcsicmp
#define _tcsicmp_l                       _wcsicmp_l
#define _tcsicoll                        _wcsicoll
#define _tcsicoll_l                      _wcsicoll_l
#define _tcsinc                          _wcsinc
#define _tcslen                          wcslen
#define _tcslwr                          _wcslwr
#define _tcslwr_l                        _wcslwr_l
#define _tcslwr_s                        _wcslwr_s
#define _tcslwr_s_l                      _wcslwr_s_l
#define _tcsnbcnt                        _wcsncnt
#define _tcsncat                         wcsncat
#define _tcsncat_l                       _wcsncat_l
#define _tcsncat_s                       wcsncat_s
#define _tcsncat_s_l                     _wcsncat_s_l
#define _tcsnccat                        wcsncat
#define _tcsnccat_l                      _wcsncat_l
#define _tcsnccat_s                      wcsncat_s
#define _tcsnccat_s_l                    _wcsncat_s_l
#define _tcsnccmp                        wcsncmp
#define _tcsnccnt                        _wcsncnt
#define _tcsnccoll                       _wcsncoll
#define _tcsnccoll_l                     _wcsncoll_l
#define _tcsnccpy                        wcsncpy
#define _tcsnccpy_l                      _wcsncpy_l
#define _tcsnccpy_s                      wcsncpy_s
#define _tcsnccpy_s_l                    _wcsncpy_s_l
#define _tcsncicmp                       _wcsnicmp
#define _tcsncicmp_l                     _wcsnicmp_l
#define _tcsncicoll                      _wcsnicoll
#define _tcsncicoll_l                    _wcsnicoll_l
#define _tcsncmp                         wcsncmp
#define _tcsncoll                        _wcsncoll
#define _tcsncoll_l                      _wcsncoll_l
#define _tcsncpy                         wcsncpy
#define _tcsncpy_l                       _wcsncpy_l
#define _tcsncpy_s                       wcsncpy_s
#define _tcsncpy_s_l                     _wcsncpy_s_l
#define _tcsncset                        _wcsnset
#define _tcsncset_l                      _wcsnset_l
#define _tcsncset_s                      _wcsnset_s
#define _tcsncset_s_l                    _wcsnset_s_l
#define _tcsnextc                        _wcsnextc
#define _tcsnicmp                        _wcsnicmp
#define _tcsnicmp_l                      _wcsnicmp_l
#define _tcsnicoll                       _wcsnicoll
#define _tcsnicoll_l                     _wcsnicoll_l
#define _tcsninc                         _wcsninc
#define _tcsnlen                         wcsnlen
#define _tcsnset                         _wcsnset
#define _tcsnset_l                       _wcsnset_l
#define _tcsnset_s                       _wcsnset_s
#define _tcsnset_s_l                     _wcsnset_s_l
#define _tcspbrk                         wcspbrk
#define _tcsrchr                         wcsrchr
#define _tcsrev                          _wcsrev
#define _tcsset                          _wcsset
#define _tcsset_l                        _wcsset_l
#define _tcsset_s                        _wcsset_s
#define _tcsset_s_l                      _wcsset_s_l
#define _tcsspn                          wcsspn
#define _tcsspnp                         _wcsspnp
#define _tcsstr                          wcsstr
#define _tcstod                          wcstod
#define _tcstod_l                        _wcstod_l
#define _tcstof                          wcstof
#define _tcstof_l                        _wcstof_l
#define _tcstoi64                        _wcstoi64
#define _tcstoi64_l                      _wcstoi64_l
#define _tcstoimax                       wcstoimax
#define _tcstoimax_l                     _wcstoimax_l
#define _tcstok                          _wcstok
#define _tcstok_l                        _wcstok_l
#define _tcstok_s                        wcstok_s
#define _tcstok_s_l                      _wcstok_s_l
#define _tcstol                          wcstol
#define _tcstol_l                        _wcstol_l
#define _tcstold                         wcstold
#define _tcstold_l                       _wcstold_l
#define _tcstoll                         wcstoll
#define _tcstoll_l                       _wcstoll_l
#define _tcstoui64                       _wcstoui64
#define _tcstoui64_l                     _wcstoui64_l
#define _tcstoul                         wcstoul
#define _tcstoul_l                       _wcstoul_l
#define _tcstoull                        wcstoull
#define _tcstoull_l                      _wcstoull_l
#define _tcstoumax                       wcstoumax
#define _tcstoumax_l                     _wcstoumax_l
#define _tcsupr                          _wcsupr
#define _tcsupr_l                        _wcsupr_l
#define _tcsupr_s                        _wcsupr_s
#define _tcsupr_s_l                      _wcsupr_s_l
#define _tcsxfrm                         wcsxfrm
#define _tcsxfrm_l                       _wcsxfrm_l
#define _tctime                          _wctime
#define _tctime32                        _wctime32
#define _tctime32_s                      _wctime32_s
#define _tctime64                        _wctime64
#define _tctime64_s                      _wctime64_s
#define _tctime_s                        _wctime_s
#define _tdupenv_s                       _wdupenv_s
#define _tdupenv_s_dbg                   _wdupenv_s_dbg
#define _tenviron                        _wenviron
#define _texecl                          _wexecl
#define _texecle                         _wexecle
#define _texeclp                         _wexeclp
#define _texeclpe                        _wexeclpe
#define _texecv                          _wexecv
#define _texecve                         _wexecve
#define _texecvp                         _wexecvp
#define _texecvpe                        _wexecvpe
#define _tfdopen                         _wfdopen
#define _tfinddata32_t                   _wfinddata32_t
#define _tfinddata32i64_t                _wfinddata32i64_t
#define _tfinddata64_t                   _wfinddata64_t
#define _tfinddata64i32_t                _wfinddata64i32_t
#define _tfinddata_t                     _wfinddata_t
#define _tfinddatai64_t                  _wfinddatai64_t
#define _tfindfirst                      _wfindfirst
#define _tfindfirst32                    _wfindfirst32
#define _tfindfirst32i64                 _wfindfirst32i64
#define _tfindfirst64                    _wfindfirst64
#define _tfindfirst64i32                 _wfindfirst64i32
#define _tfindfirsti64                   _wfindfirsti64
#define _tfindnext                       _wfindnext
#define _tfindnext32                     _wfindnext32
#define _tfindnext32i64                  _wfindnext32i64
#define _tfindnext64                     _wfindnext64
#define _tfindnext64i32                  _wfindnext64i32
#define _tfindnexti64                    _wfindnexti64
#define _tfopen                          _wfopen
#define _tfopen_s                        _wfopen_s
#define _tfreopen                        _wfreopen
#define _tfreopen_s                      _wfreopen_s
#define _tfsopen                         _wfsopen
#define _tfullpath                       _wfullpath
#define _tfullpath_dbg                   _wfullpath_dbg
#define _tgetcwd                         _wgetcwd
#define _tgetcwd_dbg                     _wgetcwd_dbg
#define _tgetdcwd                        _wgetdcwd
#define _tgetdcwd_dbg                    _wgetdcwd_dbg
#define _tgetdcwd_lk_dbg                 _wgetdcwd_lk_dbg
#define _tgetdcwd_nolock                 _wgetdcwd_nolock
#define _tgetenv                         _wgetenv
#define _tgetenv_s                       _wgetenv_s
#define _tmain                           wmain
#define _tmakepath                       _wmakepath
#define _tmakepath_s                     _wmakepath_s
#define _tmkdir                          _wmkdir
#define _tmktemp                         _wmktemp
#define _tmktemp_s                       _wmktemp_s
#define _topen                           _wopen
#define _totlower                        towlower
#define _totlower_l                      _towlower_l
#define _totupper                        towupper
#define _totupper_l                      _towupper_l
#define _tperror                         _wperror
#define _tpgmptr                         _wpgmptr
#define _tpopen                          _wpopen
#define _tprintf                         wprintf
#define _tprintf_l                       _wprintf_l
#define _tprintf_p                       _wprintf_p
#define _tprintf_p_l                     _wprintf_p_l
#define _tprintf_s                       wprintf_s
#define _tprintf_s_l                     _wprintf_s_l
#define _tputenv                         _wputenv
#define _tputenv_s                       _wputenv_s
#define _tremove                         _wremove
#define _trename                         _wrename
#define _trmdir                          _wrmdir
#define _tscanf                          wscanf
#define _tscanf_l                        _wscanf_l
#define _tscanf_s                        wscanf_s
#define _tscanf_s_l                      _wscanf_s_l
#define _tsearchenv                      _wsearchenv
#define _tsearchenv_s                    _wsearchenv_s
#define _tsetlocale                      _wsetlocale
#define _tsopen                          _wsopen
#define _tsopen_s                        _wsopen_s
#define _tspawnl                         _wspawnl
#define _tspawnle                        _wspawnle
#define _tspawnlp                        _wspawnlp
#define _tspawnlpe                       _wspawnlpe
#define _tspawnv                         _wspawnv
#define _tspawnve                        _wspawnve
#define _tspawnvp                        _wspawnvp
#define _tspawnvpe                       _wspawnvpe
#define _tsplitpath                      _wsplitpath
#define _tsplitpath_s                    _wsplitpath_s
#define _tstat                           _wstat
#define _tstat32                         _wstat32
#define _tstat32i64                      _wstat32i64
#define _tstat64                         _wstat64
#define _tstat64i32                      _wstat64i32
#define _tstati64                        _wstati64
#define _tstof                           _wtof
#define _tstof_l                         _wtof_l
#define _tstoi                           _wtoi
#define _tstoi64                         _wtoi64
#define _tstoi64_l                       _wtoi64_l
#define _tstoi_l                         _wtoi_l
#define _tstol                           _wtol
#define _tstol_l                         _wtol_l
#define _tstoll                          _wtoll
#define _tstoll_l                        _wtoll_l
#define _tstrdate                        _wstrdate
#define _tstrdate_s                      _wstrdate_s
#define _tstrtime                        _wstrtime
#define _tstrtime_s                      _wstrtime_s
#define _tsystem                         _wsystem
#define _ttempnam                        _wtempnam
#define _ttempnam_dbg                    _wtempnam_dbg
#define _ttmpnam                         _wtmpnam
#define _ttmpnam_s                       _wtmpnam_s
#define _ttof                            _wtof
#define _ttoi                            _wtoi
#define _ttoi64                          _wtoi64
#define _ttol                            _wtol
#define _ttoll                           _wtoll
#define _tunlink                         _wunlink
#define _tutime                          _wutime
#define _tutime32                        _wutime32
#define _tutime64                        _wutime64
#define _ui64tot                         _ui64tow
#define _ui64tot_s                       _ui64tow_s
#define _ultot                           _ultow
#define _ultot_s                         _ultow_s
#define _ungettc                         ungetwc
#define _ungettc_nolock                  _ungetwc_nolock
#define _ungettch                        _ungetwch
#define _ungettch_nolock                 _ungetwch_nolock
#define _vftprintf                       vfwprintf
#define _vftprintf_l                     _vfwprintf_l
#define _vftprintf_p                     _vfwprintf_p
#define _vftprintf_p_l                   _vfwprintf_p_l
#define _vftprintf_s                     vfwprintf_s
#define _vftprintf_s_l                   _vfwprintf_s_l
#define _vftscanf                        vfwscanf
#define _vftscanf_s                      vfwscanf_s
#define _vsctprintf                      _vscwprintf
#define _vsctprintf_l                    _vscwprintf_l
#define _vsctprintf_p                    _vscwprintf_p
#define _vsctprintf_p_l                  _vscwprintf_p_l
#define _vsntprintf                      _vsnwprintf
#define _vsntprintf_l                    _vsnwprintf_l
#define _vsntprintf_s                    _vsnwprintf_s
#define _vsntprintf_s_l                  _vsnwprintf_s_l
#define _vstprintf                       vswprintf
#define _vstprintf_l                     _vswprintf_l
#define _vstprintf_p                     _vswprintf_p
#define _vstprintf_p_l                   _vswprintf_p_l
#define _vstprintf_s                     vswprintf_s
#define _vstprintf_s_l                   _vswprintf_s_l
#define _vstscanf                        vswscanf
#define _vstscanf_s                      vswscanf_s
#define _vtcprintf                       _vcwprintf
#define _vtcprintf_l                     _vcwprintf_l
#define _vtcprintf_p                     _vcwprintf_p
#define _vtcprintf_p_l                   _vcwprintf_p_l
#define _vtcprintf_s                     _vcwprintf_s
#define _vtcprintf_s_l                   _vcwprintf_s_l
#define _vtprintf                        vwprintf
#define _vtprintf_l                      _vwprintf_l
#define _vtprintf_p                      _vwprintf_p
#define _vtprintf_p_l                    _vwprintf_p_l
#define _vtprintf_s                      vwprintf_s
#define _vtprintf_s_l                    _vwprintf_s_l
#define _vtscanf                         vwscanf
#define _vtscanf_s                       vwscanf_s
#else /* _UNICODE */
#define _TEOF             EOF
#define __T(x)            x
#define __targv           __argv
#define __tcserror        _strerror
#define __tcserror_s      _strerror_s
#define _cgetts_s         _cgets_s
#define _cputts           _cputs
#define _fgettc           fgetc
#define _fgettc_nolock    _fgetc_nolock
#define _fgettchar        _fgetchar
#define _fgetts           fgets
#define _fputtc           fputc
#define _fputtc_nolock    _fputc_nolock
#define _fputtchar        _fputchar
#define _fputts           fputs
#define _ftprintf         fprintf
#define _ftprintf_l       _fprintf_l
#define _ftprintf_p       _fprintf_p
#define _ftprintf_p_l     _fprintf_p_l
#define _ftprintf_s       fprintf_s
#define _ftprintf_s_l     _fprintf_s_l
#define _ftscanf          fscanf
#define _ftscanf_l        _fscanf_l
#define _ftscanf_s        fscanf_s
#define _ftscanf_s_l      _fscanf_s_l
#define _get_tpgmptr      _get_pgmptr
#define _gettc            getc
#define _gettc_nolock     _getc_nolock
#define _gettch           _getch
#define _gettch_nolock    _getch_nolock
#define _gettchar         getchar
#define _gettchar_nolock  _getchar_nolock
#define _gettche          _getche
#define _gettche_nolock   _getche_nolock
#define _getts_s          gets_s
#define _i64tot           _i64toa
#define _i64tot_s         _i64toa_s
#define _istascii         __isascii
#define _istcntrl         iscntrl
#define _istcntrl_l       _iscntrl_l
#define _istxdigit        isxdigit
#define _istxdigit_l      _isxdigit_l
#define _itot             _itoa
#define _itot_s           _itoa_s
#define _ltot             _ltoa
#define _ltot_s           _ltoa_s
#define _puttc            putc
#define _puttc_nolock     _fputc_nolock
#define _puttch           _putch
#define _puttch_nolock    _putch_nolock
#define _puttchar         putchar
#define _puttchar_nolock  _putchar_nolock
#define _putts            puts
#define _sctprintf        _scprintf
#define _sctprintf_l      _scprintf_l
#define _sctprintf_p      _scprintf_p
#define _sctprintf_p_l    _scprintf_p_l
#define _sntprintf        _snprintf
#define _sntprintf_l      _snprintf_l
#define _sntprintf_s      _snprintf_s
#define _sntprintf_s_l    _snprintf_s_l
#define _sntscanf         _snscanf
#define _sntscanf_l       _snscanf_l
#define _sntscanf_s       _snscanf_s
#define _sntscanf_s_l     _snscanf_s_l
#define _stprintf         sprintf
#define _stprintf_l       _sprintf_l
#define _stprintf_p       _sprintf_p
#define _stprintf_p_l     _sprintf_p_l
#define _stprintf_s       sprintf_s
#define _stprintf_s_l     _sprintf_s_l
#define _stscanf          sscanf
#define _stscanf_l        _sscanf_l
#define _stscanf_s        sscanf_s
#define _stscanf_s_l      _sscanf_s_l
#define _tWinMain         WinMain
#define _taccess          _access
#define _taccess_s        _access_s
#define _tasctime         asctime
#define _tasctime_s       asctime_s
#define _tchdir           _chdir
#define _tchmod           _chmod
#define _tcprintf         _cprintf
#define _tcprintf_l       _cprintf_l
#define _tcprintf_p       _cprintf_p
#define _tcprintf_p_l     _cprintf_p_l
#define _tcprintf_s       _cprintf_s
#define _tcprintf_s_l     _cprintf_s_l
#define _tcreat           _creat
#define _tcscanf          _cscanf
#define _tcscanf_l        _cscanf_l
#define _tcscanf_s        _cscanf_s
#define _tcscanf_s_l      _cscanf_s_l
#define _tcscat           strcat
#define _tcscat_s         strcat_s
#define _tcscpy           strcpy
#define _tcscpy_s         strcpy_s
#define _tcsdup           _strdup
#define _tcsdup_dbg       _strdup_dbg
#define _tcserror         strerror
#define _tcserror_s       strerror_s
#define _tcsftime         strftime
#define _tcsftime_l       _strftime_l
#define _tcslen           strlen
#define _tcsnlen          strnlen
#define _tcstod           strtod
#define _tcstod_l         _strtod_l
#define _tcstof           strtof
#define _tcstof_l         _strtof_l
#define _tcstoi64         _strtoi64
#define _tcstoi64_l       _strtoi64_l
#define _tcstoimax        strtoimax
#define _tcstoimax_l      _strtoimax_l
#define _tcstol           strtol
#define _tcstol_l         _strtol_l
#define _tcstold          strtold
#define _tcstold_l        _strtold_l
#define _tcstoll          strtoll
#define _tcstoll_l        _strtoll_l
#define _tcstoui64        _strtoui64
#define _tcstoui64_l      _strtoui64_l
#define _tcstoul          strtoul
#define _tcstoul_l        _strtoul_l
#define _tcstoull         strtoull
#define _tcstoull_l       _strtoull_l
#define _tcstoumax        strtoumax
#define _tcstoumax_l      _strtoumax_l
#define _tcsxfrm          strxfrm
#define _tcsxfrm_l        _strxfrm_l
#define _tctime           ctime
#define _tctime32         _ctime32
#define _tctime32_s       _ctime32_s
#define _tctime64         _ctime64
#define _tctime64_s       _ctime64_s
#define _tctime_s         ctime_s
#define _tdupenv_s        _dupenv_s
#define _tdupenv_s_dbg    _dupenv_s_dbg
#define _tenviron         _environ
#define _texecl           _execl
#define _texecle          _execle
#define _texeclp          _execlp
#define _texeclpe         _execlpe
#define _texecv           _execv
#define _texecve          _execve
#define _texecvp          _execvp
#define _texecvpe         _execvpe
#define _tfdopen          _fdopen
#define _tfinddata32_t    _finddata32_t
#define _tfinddata32i64_t _finddata32i64_t
#define _tfinddata64_t    __finddata64_t
#define _tfinddata64i32_t _finddata64i32_t
#define _tfinddata_t      _finddata_t
#define _tfinddatai64_t   _finddatai64_t
#define _tfindfirst       _findfirst
#define _tfindfirst32     _findfirst32
#define _tfindfirst32i64  _findfirst32i64
#define _tfindfirst64     _findfirst64
#define _tfindfirst64i32  _findfirst64i32
#define _tfindfirsti64    _findfirsti64
#define _tfindnext        _findnext
#define _tfindnext32      _findnext32
#define _tfindnext32i64   _findnext32i64
#define _tfindnext64      _findnext64
#define _tfindnext64i32   _findnext64i32
#define _tfindnexti64     _findnexti64
#define _tfopen           fopen
#define _tfopen_s         fopen_s
#define _tfreopen         freopen
#define _tfreopen_s       freopen_s
#define _tfsopen          _fsopen
#define _tfullpath        _fullpath
#define _tfullpath_dbg    _fullpath_dbg
#define _tgetcwd          _getcwd
#define _tgetcwd_dbg      _getcwd_dbg
#define _tgetdcwd         _getdcwd
#define _tgetdcwd_dbg     _getdcwd_dbg
#define _tgetdcwd_lk_dbg  _getdcwd_lk_dbg
#define _tgetdcwd_nolock  _getdcwd_nolock
#define _tgetenv          getenv
#define _tgetenv_s        getenv_s
#define _tmain            main
#define _tmakepath        _makepath
#define _tmakepath_s      _makepath_s
#define _tmkdir           _mkdir
#define _tmktemp          _mktemp
#define _tmktemp_s        _mktemp_s
#define _topen            _open
#define _tperror          perror
#define _tpgmptr          _pgmptr
#define _tpopen           _popen
#define _tprintf          printf
#define _tprintf_l        _printf_l
#define _tprintf_p        _printf_p
#define _tprintf_p_l      _printf_p_l
#define _tprintf_s        printf_s
#define _tprintf_s_l      _printf_s_l
#define _tputenv          _putenv
#define _tputenv_s        _putenv_s
#define _tremove          remove
#define _trename          rename
#define _trmdir           _rmdir
#define _tscanf           scanf
#define _tscanf_l         _scanf_l
#define _tscanf_s         scanf_s
#define _tscanf_s_l       _scanf_s_l
#define _tsearchenv       _searchenv
#define _tsearchenv_s     _searchenv_s
#define _tsetlocale       setlocale
#define _tsopen           _sopen
#define _tsopen_s         _sopen_s
#define _tspawnl          _spawnl
#define _tspawnle         _spawnle
#define _tspawnlp         _spawnlp
#define _tspawnlpe        _spawnlpe
#define _tspawnv          _spawnv
#define _tspawnve         _spawnve
#define _tspawnvp         _spawnvp
#define _tspawnvpe        _spawnvpe
#define _tsplitpath       _splitpath
#define _tsplitpath_s     _splitpath_s
#define _tstat            _stat
#define _tstat32          _stat32
#define _tstat32i64       _stat32i64
#define _tstat64          _stat64
#define _tstat64i32       _stat64i32
#define _tstati64         _stati64
#define _tstof            atof
#define _tstof_l          _atof_l
#define _tstoi            atoi
#define _tstoi64          _atoi64
#define _tstoi64_l        _atoi64_l
#define _tstoi_l          _atoi_l
#define _tstol            atol
#define _tstol_l          _atol_l
#define _tstoll           atoll
#define _tstoll_l         _atoll_l
#define _tstrdate         _strdate
#define _tstrdate_s       _strdate_s
#define _tstrtime         _strtime
#define _tstrtime_s       _strtime_s
#define _tsystem          system
#define _ttempnam         _tempnam
#define _ttempnam_dbg     _tempnam_dbg
#define _ttmpnam          tmpnam
#define _ttmpnam_s        tmpnam_s
#define _ttof             atof
#define _ttoi             atoi
#define _ttoi64           _atoi64
#define _ttol             atol
#define _ttoll            atoll
#define _tunlink          _unlink
#define _tutime           _utime
#define _tutime32         _utime32
#define _tutime64         _utime64
#define _ui64tot          _ui64toa
#define _ui64tot_s        _ui64toa_s
#define _ultot            _ultoa
#define _ultot_s          _ultoa_s
#define _ungettc          ungetc
#define _ungettc_nolock   _ungetc_nolock
#define _ungettch         _ungetch
#define _ungettch_nolock  _ungetch_nolock
#define _vftprintf        vfprintf
#define _vftprintf_l      _vfprintf_l
#define _vftprintf_p      _vfprintf_p
#define _vftprintf_p_l    _vfprintf_p_l
#define _vftprintf_s      vfprintf_s
#define _vftprintf_s_l    _vfprintf_s_l
#define _vftscanf         vfscanf
#define _vftscanf_s       vfscanf_s
#define _vsctprintf       _vscprintf
#define _vsctprintf_l     _vscprintf_l
#define _vsctprintf_p     _vscprintf_p
#define _vsctprintf_p_l   _vscprintf_p_l
#define _vsntprintf       _vsnprintf
#define _vsntprintf_l     _vsnprintf_l
#define _vsntprintf_s     _vsnprintf_s
#define _vsntprintf_s_l   _vsnprintf_s_l
#define _vstprintf        vsprintf
#define _vstprintf_l      _vsprintf_l
#define _vstprintf_p      _vsprintf_p
#define _vstprintf_p_l    _vsprintf_p_l
#define _vstprintf_s      vsprintf_s
#define _vstprintf_s_l    _vsprintf_s_l
#define _vstscanf         vsscanf
#define _vstscanf_s       vsscanf_s
#define _vtcprintf        _vcprintf
#define _vtcprintf_l      _vcprintf_l
#define _vtcprintf_p      _vcprintf_p
#define _vtcprintf_p_l    _vcprintf_p_l
#define _vtcprintf_s      _vcprintf_s
#define _vtcprintf_s_l    _vcprintf_s_l
#define _vtprintf         vprintf
#define _vtprintf_l       _vprintf_l
#define _vtprintf_p       _vprintf_p
#define _vtprintf_p_l     _vprintf_p_l
#define _vtprintf_s       vprintf_s
#define _vtprintf_s_l     _vprintf_s_l
#define _vtscanf          vscanf
#define _vtscanf_s        vscanf_s
#ifdef _MBCS
#define _istalnum        _ismbcalnum
#define _istalnum_l      _ismbcalnum_l
#define _istalpha        _ismbcalpha
#define _istalpha_l      _ismbcalpha_l
#define _istblank        _ismbcblank
#define _istblank_l      _ismbcblank_l
#define _istdigit        _ismbcdigit
#define _istdigit_l      _ismbcdigit_l
#define _istgraph        _ismbcgraph
#define _istgraph_l      _ismbcgraph_l
#define _istlead         _ismbblead
#define _istleadbyte     isleadbyte
#define _istleadbyte_l   _isleadbyte_l
#define _istlegal        _ismbclegal
#define _istlegal_l      _ismbclegal_l
#define _istlower        _ismbclower
#define _istlower_l      _ismbclower_l
#define _istprint        _ismbcprint
#define _istprint_l      _ismbcprint_l
#define _istpunct        _ismbcpunct
#define _istpunct_l      _ismbcpunct_l
#define _istspace        _ismbcspace
#define _istspace_l      _ismbcspace_l
#define _istupper        _ismbcupper
#define _istupper_l      _ismbcupper_l
#define _tccmp(cp1, cp2) _tcsnccmp(cp1, cp2, 1)
#define _tccpy           _mbccpy
#define _tccpy_l         _mbccpy_l
#define _tclen           _mbclen
#define _tcschr          _mbschr
#define _tcsclen         _mbslen
#define _tcsclen_l       _mbslen_l
#define _tcscmp          _mbscmp
#define _tcscnlen        _mbsnlen
#define _tcscnlen_l      _mbsnlen_l
#define _tcscoll         _mbscoll
#define _tcscoll_l       _mbscoll_l
#define _tcscspn         _mbscspn
#define _tcsdec          _mbsdec
#define _tcsicmp         _mbsicmp
#define _tcsicmp_l       _mbsicmp_l
#define _tcsicoll        _mbsicoll
#define _tcsicoll_l      _mbsicoll_l
#define _tcsinc          _mbsinc
#define _tcslwr          _mbslwr
#define _tcslwr_l        _mbslwr_l
#define _tcslwr_s        _mbslwr_s
#define _tcslwr_s_l      _mbslwr_s_l
#define _tcsnbcnt        _mbsnbcnt
#define _tcsncat         _mbsnbcat
#define _tcsncat_l       _mbsnbcat_l
#define _tcsncat_s       _mbsnbcat_s
#define _tcsncat_s_l     _mbsnbcat_s_l
#define _tcsnccat        _mbsncat
#define _tcsnccat_l      _mbsncat_l
#define _tcsnccat_s      _mbsncat_s
#define _tcsnccat_s_l    _mbsncat_s_l
#define _tcsnccmp        _mbsncmp
#define _tcsnccnt        _mbsnccnt
#define _tcsnccoll       _mbsncoll
#define _tcsnccoll_l     _mbsncoll_l
#define _tcsnccpy        _mbsncpy
#define _tcsnccpy_l      _mbsncpy_l
#define _tcsnccpy_s      _mbsncpy_s
#define _tcsnccpy_s_l    _mbsncpy_s_l
#define _tcsncicmp       _mbsnicmp
#define _tcsncicmp_l     _mbsnicmp_l
#define _tcsncicoll      _mbsnicoll
#define _tcsncicoll_l    _mbsnicoll_l
#define _tcsncmp         _mbsnbcmp
#define _tcsncoll        _mbsnbcoll
#define _tcsncoll_l      _mbsnbcoll_l
#define _tcsncpy         _mbsnbcpy
#define _tcsncpy_l       _mbsnbcpy_l
#define _tcsncpy_s       _mbsnbcpy_s
#define _tcsncpy_s_l     _mbsnbcpy_s_l
#define _tcsncset        _mbsnset
#define _tcsncset_l      _mbsnset_l
#define _tcsncset_s      _mbsnset_s
#define _tcsncset_s_l    _mbsnset_s_l
#define _tcsnextc        _mbsnextc
#define _tcsnicmp        _mbsnbicmp
#define _tcsnicmp_l      _mbsnbicmp_l
#define _tcsnicoll       _mbsnbicoll
#define _tcsnicoll_l     _mbsnbicoll_l
#define _tcsninc         _mbsninc
#define _tcsnset         _mbsnbset
#define _tcsnset_l       _mbsnbset_l
#define _tcsnset_s       _mbsnbset_s
#define _tcsnset_s_l     _mbsnbset_s_l
#define _tcspbrk         _mbspbrk
#define _tcsrchr         _mbsrchr
#define _tcsrev          _mbsrev
#define _tcsset          _mbsset
#define _tcsset_l        _mbsset_l
#define _tcsset_s        _mbsset_s
#define _tcsset_s_l      _mbsset_s_l
#define _tcsspn          _mbsspn
#define _tcsspnp         _mbsspnp
#define _tcsstr          _mbsstr
#define _tcstok          _mbstok
#define _tcstok_l        _mbstok_l
#define _tcstok_s        _mbstok_s
#define _tcstok_s_l      _mbstok_s_l
#define _tcsupr          _mbsupr
#define _tcsupr_l        _mbsupr_l
#define _tcsupr_s        _mbsupr_s
#define _tcsupr_s_l      _mbsupr_s_l
#define _totlower        _mbctolower
#define _totlower_l      _mbctolower_l
#define _totupper        _mbctoupper
#define _totupper_l      _mbctoupper_l
#else /* _MBCS */
#define _istalnum                        isalnum
#define _istalnum_l                      _isalnum_l
#define _istalpha                        isalpha
#define _istalpha_l                      _isalpha_l
#define _istblank                        isblank
#define _istblank_l                      _isblank_l
#define _istdigit                        isdigit
#define _istdigit_l                      _isdigit_l
#define _istgraph                        isgraph
#define _istgraph_l                      _isgraph_l
#define _istlead(ch)                     0
#define _istleadbyte(ch)                 0
#define _istleadbyte_l(ch, locale)       0
#define _istlegal(ch)                    1
#define _istlegal_l(ch, locale)          1
#define _istlower                        islower
#define _istlower_l                      _islower_l
#define _istprint                        isprint
#define _istprint_l                      _isprint_l
#define _istpunct                        ispunct
#define _istpunct_l                      _ispunct_l
#define _istspace                        isspace
#define _istspace_l                      _isspace_l
#define _istupper                        isupper
#define _istupper_l                      _isupper_l
#define _tccmp(cpc1, cpc2)               ((unsigned char)*(cpc1) - (unsigned char)*(cpc2))
#define _tccpy(pc1, cpc2)                (*(pc1) = *(cpc2))
#define _tccpy_l(pc1, cpc2, locale)      _tccpy(pc1, cpc2)
#define _tclen(str)                      1
#define _tcschr                          strchr
#define _tcsclen                         strlen
#define _tcsclen_l(str, locale)          strlen(str)
#define _tcscmp                          strcmp
#define _tcscnlen                        strnlen
#define _tcscnlen_l(str, maxlen, locale) strnlen(str, maxlen)
#define _tcscoll                         strcoll
#define _tcscoll_l                       _strcoll_l
#define _tcscspn                         strcspn
#define _tcsdec                          _strdec
#define _tcsicmp                         _stricmp
#define _tcsicmp_l                       _stricmp_l
#define _tcsicoll                        _stricoll
#define _tcsicoll_l                      _stricoll_l
#define _tcsinc                          _strinc
#define _tcslwr                          _strlwr
#define _tcslwr_l                        _strlwr_l
#define _tcslwr_s                        _strlwr_s
#define _tcslwr_s_l                      _strlwr_s_l
#define _tcsnbcnt                        _strncnt
#define _tcsncat                         strncat
#define _tcsncat_l                       _strncat_l
#define _tcsncat_s                       strncat_s
#define _tcsncat_s_l                     _strncat_s_l
#define _tcsnccat                        strncat
#define _tcsnccat_l                      _strncat_l
#define _tcsnccat_s                      strncat_s
#define _tcsnccat_s_l                    _strncat_s_l
#define _tcsnccmp                        strncmp
#define _tcsnccnt                        _strncnt
#define _tcsnccoll                       _strncoll
#define _tcsnccoll_l                     _strncoll_l
#define _tcsnccpy                        strncpy
#define _tcsnccpy_l                      _strncpy_l
#define _tcsnccpy_s                      strncpy_s
#define _tcsnccpy_s_l                    _strncpy_s_l
#define _tcsncicmp                       _strnicmp
#define _tcsncicmp_l                     _strnicmp_l
#define _tcsncicoll                      _strnicoll
#define _tcsncicoll_l                    _strnicoll_l
#define _tcsncmp                         strncmp
#define _tcsncoll                        _strncoll
#define _tcsncoll_l                      _strncoll_l
#define _tcsncpy                         strncpy
#define _tcsncpy_l                       _strncpy_l
#define _tcsncpy_s                       strncpy_s
#define _tcsncpy_s_l                     _strncpy_s_l
#define _tcsncset                        _strnset
#define _tcsncset_l                      _strnset_l
#define _tcsncset_s                      _strnset_s
#define _tcsncset_s_l                    _strnset_s_l
#define _tcsnextc                        _strnextc
#define _tcsnicmp                        _strnicmp
#define _tcsnicmp_l                      _strnicmp_l
#define _tcsnicoll                       _strnicoll
#define _tcsnicoll_l                     _strnicoll_l
#define _tcsninc                         _strninc
#define _tcsnset                         _strnset
#define _tcsnset_l                       _strnset_l
#define _tcsnset_s                       _strnset_s
#define _tcsnset_s_l                     _strnset_s_l
#define _tcspbrk                         strpbrk
#define _tcsrchr                         strrchr
#define _tcsrev                          _strrev
#define _tcsset                          _strset
#define _tcsset_l                        _strset_l
#define _tcsset_s                        _strset_s
#define _tcsset_s_l                      _strset_s_l
#define _tcsspn                          strspn
#define _tcsspnp                         _strspnp
#define _tcsstr                          strstr
#define _tcstok                          strtok
#define _tcstok_l                        _strtok_l
#define _tcstok_s                        strtok_s
#define _tcstok_s_l                      _strtok_s_l
#define _tcsupr                          _strupr
#define _tcsupr_l                        _strupr_l
#define _tcsupr_s                        _strupr_s
#define _tcsupr_s_l                      _strupr_s_l
#define _totlower                        tolower
#define _totlower_l                      _tolower_l
#define _totupper                        toupper
#define _totupper_l                      _toupper_l
#endif /* !_MBCS */
#endif /* !_UNICODE */
/*[[[end]]]*/

#define _T(x)    __T(x)
#define _TEXT(x) __T(x)

#endif /* __CC__ */

#endif /* !_TCHAR_H */
