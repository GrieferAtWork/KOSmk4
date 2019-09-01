/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_ccompat_header(cinttypes)]
%[define_replacement(intmax_t  = __INTMAX_TYPE__)]
%[define_replacement(uintmax_t = __UINTMAX_TYPE__)]
%[define_replacement(wchar_t   = __WCHAR_TYPE__)]

%{
#include <features.h>
#include <stdint.h>
#include <hybrid/typecore.h>
#ifdef __USE_DOS
#include <xlocale.h>
#endif /* __USE_DOS */

__SYSDECL_BEGIN

#ifndef ____gwchar_t_defined
#define ____gwchar_t_defined 1
#define __gwchar_t __WCHAR_TYPE__
#endif

#if __SIZEOF_LONG__ == 8
#   define __PRI64_PREFIX  "l"
#   define __PRIPTR_PREFIX "l"
#else
#   define __PRI64_PREFIX  "ll"
#   define __PRIPTR_PREFIX
#endif

#define PRId8          "d"
#define PRId16         "d"
#define PRId32         "d"
#define PRId64         __PRI64_PREFIX "d"
#define PRIdLEAST8     "d"
#define PRIdLEAST16    "d"
#define PRIdLEAST32    "d"
#define PRIdLEAST64    __PRI64_PREFIX "d"
#define PRIdFAST8      "d"
#define PRIdFAST16     __PRIPTR_PREFIX "d"
#define PRIdFAST32     __PRIPTR_PREFIX "d"
#define PRIdFAST64     __PRI64_PREFIX "d"
#define PRIi8          "i"
#define PRIi16         "i"
#define PRIi32         "i"
#define PRIi64         __PRI64_PREFIX "i"
#define PRIiLEAST8     "i"
#define PRIiLEAST16    "i"
#define PRIiLEAST32    "i"
#define PRIiLEAST64    __PRI64_PREFIX "i"
#define PRIiFAST8      "i"
#define PRIiFAST16     __PRIPTR_PREFIX "i"
#define PRIiFAST32     __PRIPTR_PREFIX "i"
#define PRIiFAST64     __PRI64_PREFIX "i"
#define PRIo8          "o"
#define PRIo16         "o"
#define PRIo32         "o"
#define PRIo64         __PRI64_PREFIX "o"
#define PRIoLEAST8     "o"
#define PRIoLEAST16    "o"
#define PRIoLEAST32    "o"
#define PRIoLEAST64    __PRI64_PREFIX "o"
#define PRIoFAST8      "o"
#define PRIoFAST16     __PRIPTR_PREFIX "o"
#define PRIoFAST32     __PRIPTR_PREFIX "o"
#define PRIoFAST64     __PRI64_PREFIX "o"
#define PRIu8          "u"
#define PRIu16         "u"
#define PRIu32         "u"
#define PRIu64         __PRI64_PREFIX "u"
#define PRIuLEAST8     "u"
#define PRIuLEAST16    "u"
#define PRIuLEAST32    "u"
#define PRIuLEAST64    __PRI64_PREFIX "u"
#define PRIuFAST8      "u"
#define PRIuFAST16     __PRIPTR_PREFIX "u"
#define PRIuFAST32     __PRIPTR_PREFIX "u"
#define PRIuFAST64     __PRI64_PREFIX "u"
#define PRIx8          "x"
#define PRIx16         "x"
#define PRIx32         "x"
#define PRIx64         __PRI64_PREFIX "x"
#define PRIxLEAST8     "x"
#define PRIxLEAST16    "x"
#define PRIxLEAST32    "x"
#define PRIxLEAST64    __PRI64_PREFIX "x"
#define PRIxFAST8      "x"
#define PRIxFAST16     __PRIPTR_PREFIX "x"
#define PRIxFAST32     __PRIPTR_PREFIX "x"
#define PRIxFAST64     __PRI64_PREFIX "x"
#define PRIX8          "X"
#define PRIX16         "X"
#define PRIX32         "X"
#define PRIX64         __PRI64_PREFIX "X"
#define PRIXLEAST8     "X"
#define PRIXLEAST16    "X"
#define PRIXLEAST32    "X"
#define PRIXLEAST64    __PRI64_PREFIX "X"
#define PRIXFAST8      "X"
#define PRIXFAST16     __PRIPTR_PREFIX "X"
#define PRIXFAST32     __PRIPTR_PREFIX "X"
#define PRIXFAST64     __PRI64_PREFIX "X"
#define PRIdMAX        __PRI64_PREFIX "d"
#define PRIiMAX        __PRI64_PREFIX "i"
#define PRIoMAX        __PRI64_PREFIX "o"
#define PRIuMAX        __PRI64_PREFIX "u"
#define PRIxMAX        __PRI64_PREFIX "x"
#define PRIXMAX        __PRI64_PREFIX "X"
#define PRIdPTR        __PRIPTR_PREFIX "d"
#define PRIiPTR        __PRIPTR_PREFIX "i"
#define PRIoPTR        __PRIPTR_PREFIX "o"
#define PRIuPTR        __PRIPTR_PREFIX "u"
#define PRIxPTR        __PRIPTR_PREFIX "x"
#define PRIXPTR        __PRIPTR_PREFIX "X"

#define SCNd8          "hhd"
#define SCNd16         "hd"
#define SCNd32         "d"
#define SCNd64         __PRI64_PREFIX "d"
#define SCNdLEAST8     "hhd"
#define SCNdLEAST16    "hd"
#define SCNdLEAST32    "d"
#define SCNdLEAST64    __PRI64_PREFIX "d"
#define SCNdFAST8      "hhd"
#define SCNdFAST16     __PRIPTR_PREFIX "d"
#define SCNdFAST32     __PRIPTR_PREFIX "d"
#define SCNdFAST64     __PRI64_PREFIX "d"
#define SCNi8          "hhi"
#define SCNi16         "hi"
#define SCNi32         "i"
#define SCNi64         __PRI64_PREFIX "i"
#define SCNiLEAST8     "hhi"
#define SCNiLEAST16    "hi"
#define SCNiLEAST32    "i"
#define SCNiLEAST64    __PRI64_PREFIX "i"
#define SCNiFAST8      "hhi"
#define SCNiFAST16     __PRIPTR_PREFIX "i"
#define SCNiFAST32     __PRIPTR_PREFIX "i"
#define SCNiFAST64     __PRI64_PREFIX "i"
#define SCNu8          "hhu"
#define SCNu16         "hu"
#define SCNu32         "u"
#define SCNu64         __PRI64_PREFIX "u"
#define SCNuLEAST8     "hhu"
#define SCNuLEAST16    "hu"
#define SCNuLEAST32    "u"
#define SCNuLEAST64    __PRI64_PREFIX "u"
#define SCNuFAST8      "hhu"
#define SCNuFAST16     __PRIPTR_PREFIX "u"
#define SCNuFAST32     __PRIPTR_PREFIX "u"
#define SCNuFAST64     __PRI64_PREFIX "u"
#define SCNo8          "hho"
#define SCNo16         "ho"
#define SCNo32         "o"
#define SCNo64         __PRI64_PREFIX "o"
#define SCNoLEAST8     "hho"
#define SCNoLEAST16    "ho"
#define SCNoLEAST32    "o"
#define SCNoLEAST64    __PRI64_PREFIX "o"
#define SCNoFAST8      "hho"
#define SCNoFAST16     __PRIPTR_PREFIX "o"
#define SCNoFAST32     __PRIPTR_PREFIX "o"
#define SCNoFAST64     __PRI64_PREFIX "o"
#define SCNx8          "hhx"
#define SCNx16         "hx"
#define SCNx32         "x"
#define SCNx64         __PRI64_PREFIX "x"
#define SCNxLEAST8     "hhx"
#define SCNxLEAST16    "hx"
#define SCNxLEAST32    "x"
#define SCNxLEAST64    __PRI64_PREFIX "x"
#define SCNxFAST8      "hhx"
#define SCNxFAST16     __PRIPTR_PREFIX "x"
#define SCNxFAST32     __PRIPTR_PREFIX "x"
#define SCNxFAST64     __PRI64_PREFIX "x"
#define SCNdMAX        __PRI64_PREFIX "d"
#define SCNiMAX        __PRI64_PREFIX "i"
#define SCNoMAX        __PRI64_PREFIX "o"
#define SCNuMAX        __PRI64_PREFIX "u"
#define SCNxMAX        __PRI64_PREFIX "x"
#define SCNdPTR        __PRIPTR_PREFIX "d"
#define SCNiPTR        __PRIPTR_PREFIX "i"
#define SCNoPTR        __PRIPTR_PREFIX "o"
#define SCNuPTR        __PRIPTR_PREFIX "u"
#define SCNxPTR        __PRIPTR_PREFIX "x"

#ifdef __CC__

#ifndef __std_imaxdiv_t_defined
#define __std_imaxdiv_t_defined 1
}%[push_macro @undef { quot rem }]%{

__NAMESPACE_STD_BEGIN
#ifdef __imaxdiv_t_defined
__NAMESPACE_GLB_USING(imaxdiv_t)
#else /* __imaxdiv_t_defined */
typedef struct {
	__INTMAX_TYPE__ quot; /* Quotient. */
	__INTMAX_TYPE__ rem;  /* Remainder. */
} imaxdiv_t;
#endif /* !__imaxdiv_t_defined */
__NAMESPACE_STD_END

}%[pop_macro]%{
#endif /* !__std_imaxdiv_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __imaxdiv_t_defined
#define __imaxdiv_t_defined 1
__NAMESPACE_STD_USING(imaxdiv_t)
#endif /* !__imaxdiv_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

}

%[insert:std]


[std]
[section(.text.crt.math.utility)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_INT__), alias(abs)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias(labs)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias(llabs)]
[ATTR_CONST][nothrow][crtbuiltin] imaxabs:($intmax_t x) -> $intmax_t {
	return x < 0 ? -x : x;
}

[std][section(.text.crt.math.utility)]
[ATTR_CONST][nothrow] imaxdiv:($intmax_t numer, $intmax_t denom) -> imaxdiv_t {
	@imaxdiv_t@ result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}


[std][ATTR_PURE][section(.text.crt.unicode.static.convert)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias(strtol)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias(strtoll), alias(strtoq)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(strto64)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(strto32)]
strtoimax:([nonnull] char const *__restrict nptr, char **endptr, int base) -> $intmax_t {
#if __SIZEOF_INTMAX_T__ <= 4
	return (intmax_t)strto32(nptr, endptr, base);
#else
	return (intmax_t)strto64(nptr, endptr, base);
#endif
}


[std][ATTR_PURE][section(.text.crt.unicode.static.convert)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias(strtoul)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias(strtoull), alias(strtouq)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(strtou64)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(strtou32)]
strtoumax:([nonnull] char const *__restrict nptr, char ** endptr, int base) -> $uintmax_t {
#if __SIZEOF_INTMAX_T__ <= 4
	return (uintmax_t)strtou32(nptr, endptr, base);
#else
	return (uintmax_t)strtou64(nptr, endptr, base);
#endif
}


[std][wchar][ATTR_PURE]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias(wcstol)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias(wcstoll), alias(wcstoq)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(wcsto32)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(wcsto64)]
wcstoimax:([nonnull] $wchar_t const *__restrict nptr, $wchar_t **endptr, int base) -> $intmax_t
	%{copy(%auto, str2wcs)}

[std][wchar][ATTR_PURE]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias(wcstoul)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias(wcstoull), alias(wcstouq)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(wcstou64)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(wcstou32)]
wcstoumax:([nonnull] $wchar_t const *__restrict nptr, $wchar_t **endptr, int base) -> $uintmax_t
	%{copy(%auto, str2wcs)}

%
%
%
%

%#ifdef __USE_KOS
%#ifdef __USE_XOPEN2K8

[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias(strtol_l, _strtol_l)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias(strtoll_l, _strtoll_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(_strtoi64_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(strto64_l)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(strto32_l)]
[ATTR_LEAF][alias(_strtoimax_l)]
[section({.text.crt.unicode.locale.convert|.text.crt.dos.unicode.locale.convert})]
strtoimax_l:([nonnull] char const *__restrict nptr, char **endptr, int base, $locale_t locale) -> $intmax_t {
	(void)locale;
	return strtoimax(nptr, endptr, base);
}


[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias(strtoul_l, _strtoul_l)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias(strtoull_l, _strtoull_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(_strtoui64_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(strtou64_l)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(strtou32_l)]
[ATTR_LEAF][alias(_strtoumax_l)]
[section({.text.crt.unicode.locale.convert|.text.crt.dos.unicode.locale.convert})]
strtoumax_l:([nonnull] char const *__restrict nptr, char **endptr, int base, $locale_t locale) -> $uintmax_t {
	(void)locale;
	return strtoumax(nptr, endptr, base);
}

[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias(wcstol_l, _wcstol_l)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias(wcstoll_l, _wcstoll_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(_wcstoi64_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(wcsto64_l)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(wcsto32_l)]
[wchar][ATTR_LEAF][alias(_wcstoimax_l)]
[section({.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert})]
wcstoimax_l:([nonnull] $wchar_t const *__restrict nptr, $wchar_t **endptr, int base, $locale_t locale) -> $intmax_t
	%{copy(%auto, str2wcs)}

[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias(wcstoul_l, _wcstoul_l)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias(wcstoull_l, _wcstoull_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(_wcstoui64_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(wcstou64_l)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(wcstou32_l)]
[wchar][ATTR_LEAF][alias(_wcstoumax_l)]
[section({.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert})]
wcstoumax_l:([nonnull] $wchar_t const *__restrict nptr, $wchar_t **endptr, int base, $locale_t locale) -> $uintmax_t
	%{copy(%auto, str2wcs)}


%#endif /* __USE_XOPEN2K8 */
%#endif /* __USE_KOS */


%
%
%
%#ifdef __USE_DOS
[alias(*)] _strtoimax_l:(*) = strtoimax_l;
[alias(*)] _strtoumax_l:(*) = strtoumax_l;
[alias(*)] _wcstoimax_l:(*) = wcstoimax_l;
[alias(*)] _wcstoumax_l:(*) = wcstoumax_l;
%#endif /* __USE_DOS */

%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif
#endif /* __USE_UTF */

}