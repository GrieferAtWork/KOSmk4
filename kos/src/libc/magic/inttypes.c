/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_ccompat_header("cinttypes")]
%[define_replacement(intmax_t  = __INTMAX_TYPE__)]
%[define_replacement(uintmax_t = __UINTMAX_TYPE__)]
%[define_replacement(wchar_t   = __WCHAR_TYPE__)]

%{
#include <features.h>
#include <stdint.h>
#include <hybrid/typecore.h>
#include <hybrid/__va_size.h>
#ifdef __USE_DOS
#include <xlocale.h>
#endif /* __USE_DOS */

__SYSDECL_BEGIN

#ifndef ____gwchar_t_defined
#define ____gwchar_t_defined 1
#define __gwchar_t __WCHAR_TYPE__
#endif /* !____gwchar_t_defined */

/* Since `__VA_SIZE >= sizeof(int)', and `sizeof(int) != 0',
 * we also know that `sizeof(int) >= 1', meaning that any 8-bit
 * data word will _always_ be promoted to an int, meaning in order
 * to print an 8-bit data word we never need any sort of prefix! */
#ifndef __PRI1_PREFIX
#define __PRI1_PREFIX /* nothing */
#endif /* !__PRI1_PREFIX */

#ifndef __PRI2_PREFIX
#if __VA_SIZE >= 2
#define __PRI2_PREFIX /* nothing */
#elif __SIZEOF_LONG__ == 2
#define __PRI2_PREFIX "l"
#elif __SIZEOF_SHORT__ == 2
#define __PRI2_PREFIX "h"
#elif (__SIZEOF_POINTER__ == 2 && (defined(__CRT_KOS) || defined(__CRT_DOS)))
#define __PRI2_PREFIX "I"
#elif __SIZEOF_CHAR__ == 2
#define __PRI2_PREFIX "hh"
#elif __SIZEOF_LONG_LONG__ == 2
#define __PRI2_PREFIX "ll"
#else
#define __PRI2_PREFIX "I16" /* XXX: non-portable */
#endif
#endif /* !__PRI2_PREFIX */

#ifndef __PRI4_PREFIX
#if __VA_SIZE >= 4
#define __PRI4_PREFIX /* nothing */
#elif __SIZEOF_LONG__ == 4
#define __PRI4_PREFIX "l"
#elif __SIZEOF_SHORT__ == 4
#define __PRI4_PREFIX "h"
#elif (__SIZEOF_POINTER__ == 4 && (defined(__CRT_KOS) || defined(__CRT_DOS)))
#define __PRI4_PREFIX "I"
#elif __SIZEOF_CHAR__ == 4
#define __PRI4_PREFIX "hh"
#elif __SIZEOF_LONG_LONG__ == 4
#define __PRI4_PREFIX "ll"
#else
#define __PRI4_PREFIX "I32" /* XXX: non-portable */
#endif
#endif /* !__PRI4_PREFIX */

#ifndef __PRI8_PREFIX
#if __VA_SIZE >= 8
#define __PRI8_PREFIX /* nothing */
#elif __SIZEOF_LONG__ == 8
#define __PRI8_PREFIX "l"
#elif __SIZEOF_INTMAX_T__ == 8
#define __PRI8_PREFIX "j"
#elif (__SIZEOF_POINTER__ == 8 && (defined(__CRT_KOS) || defined(__CRT_DOS)))
#define __PRI8_PREFIX "I"
#elif __SIZEOF_LONG_LONG__ == 8
#define __PRI8_PREFIX "ll"
#else
#define __PRI8_PREFIX "I64" /* XXX: non-portable */
#endif
#endif /* !__PRI8_PREFIX */

#ifndef __PRIP_PREFIX
#if __VA_SIZE >= __SIZEOF_POINTER__
#define __PRIP_PREFIX /* nothing */
#elif __SIZEOF_LONG__ == __SIZEOF_POINTER__
#define __PRIP_PREFIX "l"
#elif __SIZEOF_INTMAX_T__ == __SIZEOF_POINTER__
#define __PRIP_PREFIX "j"
#elif defined(__CRT_KOS) || defined(__CRT_DOS)
#define __PRIP_PREFIX "I"
#endif
#endif /* !__PRIP_PREFIX */

#define __PRIN2_PREFIX(n) __PRI##n##_PREFIX
#define __PRIN_PREFIX(n) __PRIN2_PREFIX(n)
#define __PRIL1_PREFIX __PRIN_PREFIX(__SIZEOF_INT_LEAST8_T__)
#define __PRIL2_PREFIX __PRIN_PREFIX(__SIZEOF_INT_LEAST16_T__)
#define __PRIL4_PREFIX __PRIN_PREFIX(__SIZEOF_INT_LEAST32_T__)
#define __PRIL8_PREFIX __PRIN_PREFIX(__SIZEOF_INT_LEAST64_T__)
#define __PRIF1_PREFIX __PRIN_PREFIX(__SIZEOF_INT_FAST8_T__)
#define __PRIF2_PREFIX __PRIN_PREFIX(__SIZEOF_INT_FAST16_T__)
#define __PRIF4_PREFIX __PRIN_PREFIX(__SIZEOF_INT_FAST32_T__)
#define __PRIF8_PREFIX __PRIN_PREFIX(__SIZEOF_INT_FAST64_T__)


#ifndef __SCA1_PREFIX
#if __SIZEOF_INT__ == 1
#define __SCA1_PREFIX /* nothing */
#elif __SIZEOF_SHORT__ == 1
#define __SCA1_PREFIX "h"
#elif __SIZEOF_CHAR__ == 1
#define __SCA1_PREFIX "hh"
#else
#define __SCA1_PREFIX "I8"
#endif
#endif /* !__SCA1_PREFIX */

#ifndef __SCA2_PREFIX
#if __SIZEOF_INT__ == 2
#define __SCA2_PREFIX /* nothing */
#elif __SIZEOF_SHORT__ == 2
#define __SCA2_PREFIX "h"
#elif __SIZEOF_LONG__ == 2
#define __SCA2_PREFIX "l"
#elif __SIZEOF_POINTER__ == 2
#define __SCA2_PREFIX "I"
#else
#define __SCA2_PREFIX "I16"
#endif
#endif /* !__SCA2_PREFIX */

#ifndef __SCA4_PREFIX
#if __SIZEOF_INT__ == 4
#define __SCA4_PREFIX /* nothing */
#elif __SIZEOF_SHORT__ == 4
#define __SCA4_PREFIX "h"
#elif __SIZEOF_LONG__ == 4
#define __SCA4_PREFIX "l"
#elif __SIZEOF_POINTER__ == 4 && \
     (defined(__CRT_KOS) || defined(__CRT_DOS))
#define __SCA4_PREFIX "I"
#elif __SIZEOF_LONG_LONG__ == 4
#define __SCA4_PREFIX "ll"
#else
#define __SCA4_PREFIX "I32"
#endif
#endif /* !__SCA4_PREFIX */

#ifndef __SCA8_PREFIX
#if __SIZEOF_INT__ == 8
#define __SCA8_PREFIX /* nothing */
#elif __SIZEOF_SHORT__ == 8
#define __SCA8_PREFIX "h"
#elif __SIZEOF_LONG__ == 8
#define __SCA8_PREFIX "l"
#elif __SIZEOF_POINTER__ == 8 && \
     (defined(__CRT_KOS) || defined(__CRT_DOS))
#define __SCA8_PREFIX "I"
#elif __SIZEOF_LONG_LONG__ == 8
#define __SCA8_PREFIX "ll"
#else
#define __SCA8_PREFIX "I64"
#endif
#endif /* !__SCA8_PREFIX */

#ifndef __SCAP_PREFIX
#if __SIZEOF_INT__ == __SIZEOF_POINTER__
#define __SCAP_PREFIX /* nothing */
#elif __SIZEOF_LONG__ == __SIZEOF_POINTER__
#define __SCAP_PREFIX "l"
#elif __SIZEOF_INTMAX_T__ == __SIZEOF_POINTER__
#define __SCAP_PREFIX "j"
#else
#define __SCAP_PREFIX "I"
#endif
#endif /* !__SCAP_PREFIX */

#define __SCAN2_PREFIX(n) __SCA##n##_PREFIX
#define __SCAN_PREFIX(n) __SCAN2_PREFIX(n)
#define __SCAL1_PREFIX __SCAN_PREFIX(__SIZEOF_INT_LEAST8_T__)
#define __SCAL2_PREFIX __SCAN_PREFIX(__SIZEOF_INT_LEAST16_T__)
#define __SCAL4_PREFIX __SCAN_PREFIX(__SIZEOF_INT_LEAST32_T__)
#define __SCAL8_PREFIX __SCAN_PREFIX(__SIZEOF_INT_LEAST64_T__)
#define __SCAF1_PREFIX __SCAN_PREFIX(__SIZEOF_INT_FAST8_T__)
#define __SCAF2_PREFIX __SCAN_PREFIX(__SIZEOF_INT_FAST16_T__)
#define __SCAF4_PREFIX __SCAN_PREFIX(__SIZEOF_INT_FAST32_T__)
#define __SCAF8_PREFIX __SCAN_PREFIX(__SIZEOF_INT_FAST64_T__)



/* printf(): (u)int8_t */
#define PRId8          __PRI1_PREFIX "d" /* I8d */
#define PRIi8          __PRI1_PREFIX "i" /* I8i */
#define PRIo8          __PRI1_PREFIX "o" /* I8o */
#define PRIu8          __PRI1_PREFIX "u" /* I8u */
#define PRIx8          __PRI1_PREFIX "x" /* I8x */
#define PRIX8          __PRI1_PREFIX "X" /* I8X */

/* printf(): (u)int16_t */
#define PRId16         __PRI2_PREFIX "d" /* I16d */
#define PRIi16         __PRI2_PREFIX "i" /* I16i */
#define PRIo16         __PRI2_PREFIX "o" /* I16o */
#define PRIu16         __PRI2_PREFIX "u" /* I16u */
#define PRIx16         __PRI2_PREFIX "x" /* I16x */
#define PRIX16         __PRI2_PREFIX "X" /* I16X */

/* printf(): (u)int32_t */
#define PRId32         __PRI4_PREFIX "d" /* I32d */
#define PRIi32         __PRI4_PREFIX "i" /* I32i */
#define PRIo32         __PRI4_PREFIX "o" /* I32o */
#define PRIu32         __PRI4_PREFIX "u" /* I32u */
#define PRIx32         __PRI4_PREFIX "x" /* I32x */
#define PRIX32         __PRI4_PREFIX "X" /* I32X */

/* printf(): (u)int64_t */
#define PRId64         __PRI8_PREFIX "d" /* I64d */
#define PRIi64         __PRI8_PREFIX "i" /* I64i */
#define PRIo64         __PRI8_PREFIX "o" /* I64o */
#define PRIu64         __PRI8_PREFIX "u" /* I64u */
#define PRIx64         __PRI8_PREFIX "x" /* I64x */
#define PRIX64         __PRI8_PREFIX "X" /* I64X */

/* printf(): (u)int_least8_t */
#define PRIdLEAST8     __PRIL1_PREFIX "d"
#define PRIiLEAST8     __PRIL1_PREFIX "i"
#define PRIoLEAST8     __PRIL1_PREFIX "o"
#define PRIuLEAST8     __PRIL1_PREFIX "u"
#define PRIxLEAST8     __PRIL1_PREFIX "x"
#define PRIXLEAST8     __PRIL1_PREFIX "X"

/* printf(): (u)int_least16_t */
#define PRIdLEAST16    __PRIL2_PREFIX "d"
#define PRIiLEAST16    __PRIL2_PREFIX "i"
#define PRIoLEAST16    __PRIL2_PREFIX "o"
#define PRIuLEAST16    __PRIL2_PREFIX "u"
#define PRIxLEAST16    __PRIL2_PREFIX "x"
#define PRIXLEAST16    __PRIL2_PREFIX "X"

/* printf(): (u)int_least32_t */
#define PRIdLEAST32    __PRIL4_PREFIX "d"
#define PRIiLEAST32    __PRIL4_PREFIX "i"
#define PRIoLEAST32    __PRIL4_PREFIX "o"
#define PRIuLEAST32    __PRIL4_PREFIX "u"
#define PRIxLEAST32    __PRIL4_PREFIX "x"
#define PRIXLEAST32    __PRIL4_PREFIX "X"

/* printf(): (u)int_least64_t */
#define PRIdLEAST64    __PRIL8_PREFIX "d"
#define PRIiLEAST64    __PRIL8_PREFIX "i"
#define PRIoLEAST64    __PRIL8_PREFIX "o"
#define PRIuLEAST64    __PRIL8_PREFIX "u"
#define PRIxLEAST64    __PRIL8_PREFIX "x"
#define PRIXLEAST64    __PRIL8_PREFIX "X"

/* printf(): (u)int_fast8_t */
#define PRIdFAST8      __PRIF1_PREFIX "d"
#define PRIiFAST8      __PRIF1_PREFIX "i"
#define PRIoFAST8      __PRIF1_PREFIX "o"
#define PRIuFAST8      __PRIF1_PREFIX "u"
#define PRIxFAST8      __PRIF1_PREFIX "x"
#define PRIXFAST8      __PRIF1_PREFIX "X"

/* printf(): (u)int_fast16_t */
#define PRIdFAST16     __PRIF2_PREFIX "d"
#define PRIiFAST16     __PRIF2_PREFIX "i"
#define PRIoFAST16     __PRIF2_PREFIX "o"
#define PRIuFAST16     __PRIF2_PREFIX "u"
#define PRIxFAST16     __PRIF2_PREFIX "x"
#define PRIXFAST16     __PRIF2_PREFIX "X"

/* printf(): (u)int_fast32_t */
#define PRIdFAST32     __PRIF4_PREFIX "d"
#define PRIiFAST32     __PRIF4_PREFIX "i"
#define PRIoFAST32     __PRIF4_PREFIX "o"
#define PRIuFAST32     __PRIF4_PREFIX "u"
#define PRIxFAST32     __PRIF4_PREFIX "x"
#define PRIXFAST32     __PRIF4_PREFIX "X"

/* printf(): (u)int_fast64_t */
#define PRIdFAST64     __PRIF8_PREFIX "d"
#define PRIiFAST64     __PRIF8_PREFIX "i"
#define PRIoFAST64     __PRIF8_PREFIX "o"
#define PRIuFAST64     __PRIF8_PREFIX "u"
#define PRIxFAST64     __PRIF8_PREFIX "x"
#define PRIXFAST64     __PRIF8_PREFIX "X"

/* printf(): (u)intmax_t */
#define PRIdMAX        __PRI8_PREFIX "d"
#define PRIiMAX        __PRI8_PREFIX "i"
#define PRIoMAX        __PRI8_PREFIX "o"
#define PRIuMAX        __PRI8_PREFIX "u"
#define PRIxMAX        __PRI8_PREFIX "x"
#define PRIXMAX        __PRI8_PREFIX "X"

/* printf(): (u)intptr_t / void * */
#ifdef __PRIP_PREFIX
#define PRIdPTR        __PRIP_PREFIX "d" /* Id */
#define PRIiPTR        __PRIP_PREFIX "i" /* Ii */
#define PRIoPTR        __PRIP_PREFIX "o" /* Io */
#define PRIuPTR        __PRIP_PREFIX "u" /* Iu */
#define PRIxPTR        __PRIP_PREFIX "x" /* Ix */
#define PRIXPTR        __PRIP_PREFIX "X" /* IX */
#else /* __PRIP_PREFIX */
#define PRIdPTR        "td" /* ptrdiff_t */
#define PRIiPTR        "ti" /* ptrdiff_t */
#define PRIoPTR        "zo" /* size_t */
#define PRIuPTR        "zu" /* size_t */
#define PRIxPTR        "zx" /* size_t */
#define PRIXPTR        "zX" /* size_t */
#endif /* !__PRIP_PREFIX */

#ifdef __USE_KOS
/* printf(): (s)size_t */
#ifdef __PRIP_PREFIX
#define PRIdSIZ        __PRIP_PREFIX "d" /* Id */
#define PRIiSIZ        __PRIP_PREFIX "i" /* Ii */
#define PRIoSIZ        __PRIP_PREFIX "o" /* Io */
#define PRIuSIZ        __PRIP_PREFIX "u" /* Iu */
#define PRIxSIZ        __PRIP_PREFIX "x" /* Ix */
#define PRIXSIZ        __PRIP_PREFIX "X" /* IX */
#else /* __PRIP_PREFIX */
#define PRIdSIZ        "td" /* ptrdiff_t */
#define PRIiSIZ        "ti" /* ptrdiff_t */
#define PRIoSIZ        "zo" /* size_t */
#define PRIuSIZ        "zu" /* size_t */
#define PRIxSIZ        "zx" /* size_t */
#define PRIXSIZ        "zX" /* size_t */
#endif /* !__PRIP_PREFIX */

/* printf(): Custom size (use __SIZEOF_xxx__ macros with these) */
#define PRIdN(sizeof)  __PRIN_PREFIX(sizeof) "d"
#define PRIiN(sizeof)  __PRIN_PREFIX(sizeof) "i"
#define PRIoN(sizeof)  __PRIN_PREFIX(sizeof) "o"
#define PRIuN(sizeof)  __PRIN_PREFIX(sizeof) "u"
#define PRIxN(sizeof)  __PRIN_PREFIX(sizeof) "x"
#define PRIXN(sizeof)  __PRIN_PREFIX(sizeof) "X"
#endif /* __USE_KOS */




/* scanf(): (u)int8_t */
#define SCNd8          __SCA1_PREFIX "d"
#define SCNi8          __SCA1_PREFIX "i"
#define SCNu8          __SCA1_PREFIX "u"
#define SCNo8          __SCA1_PREFIX "o"
#define SCNx8          __SCA1_PREFIX "x"

/* scanf(): (u)int16_t */
#define SCNd16         __SCA2_PREFIX "d"
#define SCNi16         __SCA2_PREFIX "i"
#define SCNu16         __SCA2_PREFIX "u"
#define SCNo16         __SCA2_PREFIX "o"
#define SCNx16         __SCA2_PREFIX "x"

/* scanf(): (u)int32_t */
#define SCNd32         __SCA4_PREFIX "d"
#define SCNi32         __SCA4_PREFIX "i"
#define SCNu32         __SCA4_PREFIX "u"
#define SCNo32         __SCA4_PREFIX "o"
#define SCNx32         __SCA4_PREFIX "x"

/* scanf(): (u)int64_t */
#define SCNd64         __SCA8_PREFIX "d"
#define SCNi64         __SCA8_PREFIX "i"
#define SCNu64         __SCA8_PREFIX "u"
#define SCNo64         __SCA8_PREFIX "o"
#define SCNx64         __SCA8_PREFIX "x"

/* scanf(): (u)int_least8_t */
#define SCNdLEAST8     __SCAL1_PREFIX "d"
#define SCNiLEAST8     __SCAL1_PREFIX "i"
#define SCNuLEAST8     __SCAL1_PREFIX "u"
#define SCNoLEAST8     __SCAL1_PREFIX "o"
#define SCNxLEAST8     __SCAL1_PREFIX "x"

/* scanf(): (u)int_least16_t */
#define SCNdLEAST16    __SCAL2_PREFIX "d"
#define SCNiLEAST16    __SCAL2_PREFIX "i"
#define SCNuLEAST16    __SCAL2_PREFIX "u"
#define SCNoLEAST16    __SCAL2_PREFIX "o"
#define SCNxLEAST16    __SCAL2_PREFIX "x"

/* scanf(): (u)int_least32_t */
#define SCNdLEAST32    __SCAL4_PREFIX "d"
#define SCNiLEAST32    __SCAL4_PREFIX "i"
#define SCNuLEAST32    __SCAL4_PREFIX "u"
#define SCNoLEAST32    __SCAL4_PREFIX "o"
#define SCNxLEAST32    __SCAL4_PREFIX "x"

/* scanf(): (u)int_least64_t */
#define SCNdLEAST64    __SCAL8_PREFIX "d"
#define SCNiLEAST64    __SCAL8_PREFIX "i"
#define SCNuLEAST64    __SCAL8_PREFIX "u"
#define SCNoLEAST64    __SCAL8_PREFIX "o"
#define SCNxLEAST64    __SCAL8_PREFIX "x"

/* scanf(): (u)int_fast8_t */
#define SCNdFAST8      __SCAF1_PREFIX "d"
#define SCNiFAST8      __SCAF1_PREFIX "i"
#define SCNuFAST8      __SCAF1_PREFIX "u"
#define SCNoFAST8      __SCAF1_PREFIX "o"
#define SCNxFAST8      __SCAF1_PREFIX "x"

/* scanf(): (u)int_fast16_t */
#define SCNdFAST16     __SCAF2_PREFIX "d"
#define SCNiFAST16     __SCAF2_PREFIX "i"
#define SCNuFAST16     __SCAF2_PREFIX "u"
#define SCNoFAST16     __SCAF2_PREFIX "o"
#define SCNxFAST16     __SCAF2_PREFIX "x"

/* scanf(): (u)int_fast32_t */
#define SCNdFAST32     __SCAF4_PREFIX "d"
#define SCNiFAST32     __SCAF4_PREFIX "i"
#define SCNuFAST32     __SCAF4_PREFIX "u"
#define SCNoFAST32     __SCAF4_PREFIX "o"
#define SCNxFAST32     __SCAF4_PREFIX "x"

/* scanf(): (u)int_fast64_t */
#define SCNdFAST64     __SCAF8_PREFIX "d"
#define SCNiFAST64     __SCAF8_PREFIX "i"
#define SCNuFAST64     __SCAF8_PREFIX "u"
#define SCNoFAST64     __SCAF8_PREFIX "o"
#define SCNxFAST64     __SCAF8_PREFIX "x"

/* scanf(): (u)intmax_t */
#define SCNdMAX        __SCA8_PREFIX "d"
#define SCNiMAX        __SCA8_PREFIX "i"
#define SCNuMAX        __SCA8_PREFIX "u"
#define SCNoMAX        __SCA8_PREFIX "o"
#define SCNxMAX        __SCA8_PREFIX "x"

/* scanf(): (u)intptr_t / void * */
#define SCNdPTR        __SCAP_PREFIX "d"
#define SCNiPTR        __SCAP_PREFIX "i"
#define SCNuPTR        __SCAP_PREFIX "u"
#define SCNoPTR        __SCAP_PREFIX "o"
#define SCNxPTR        __SCAP_PREFIX "x"

#ifdef __USE_KOS
/* scanf(): (s)size_t */
#define SCNdSIZ        __SCAP_PREFIX "d"
#define SCNiSIZ        __SCAP_PREFIX "i"
#define SCNuSIZ        __SCAP_PREFIX "u"
#define SCNoSIZ        __SCAP_PREFIX "o"
#define SCNxSIZ        __SCAP_PREFIX "x"

/* scanf(): Custom size (use __SIZEOF_xxx__ macros with these) */
#define SCNdN(sizeof)  __SCAN_PREFIX(sizeof) "d"
#define SCNiN(sizeof)  __SCAN_PREFIX(sizeof) "i"
#define SCNuN(sizeof)  __SCAN_PREFIX(sizeof) "u"
#define SCNoN(sizeof)  __SCAN_PREFIX(sizeof) "o"
#define SCNxN(sizeof)  __SCAN_PREFIX(sizeof) "x"

/* U-scan command:
 *    Unsigned integer, where the radix is automatically detected,
 *    using the same syntax as a C compiler would accept:
 *       "1234":      Decimal
 *       "0777":      Octal
 *       "0xDEAD":    Hex    (casing is ignored)
 *       "0b010011":  Binary (extension; casing is ignored) */
#define SCNU8          __SCA1_PREFIX "U"
#define SCNU16         __SCA2_PREFIX "U"
#define SCNU32         __SCA4_PREFIX "U"
#define SCNU64         __SCA8_PREFIX "U"
#define SCNULEAST8     __SCAL1_PREFIX "U"
#define SCNULEAST16    __SCAL2_PREFIX "U"
#define SCNULEAST32    __SCAL4_PREFIX "U"
#define SCNULEAST64    __SCAL8_PREFIX "U"
#define SCNUFAST8      __SCAF1_PREFIX "U"
#define SCNUFAST16     __SCAF2_PREFIX "U"
#define SCNUFAST32     __SCAF4_PREFIX "U"
#define SCNUFAST64     __SCAF8_PREFIX "U"
#define SCNUMAX        __SCA8_PREFIX "U"
#define SCNUPTR        __SCAP_PREFIX "U"
#define SCNUSIZ        __SCAP_PREFIX "U"
#define SCNUN(sizeof)  __SCAN_PREFIX(sizeof) "U"
#endif /* __USE_KOS */



#ifdef __CC__

}%[push_macro @undef { quot rem }]%{
struct __imaxdiv_struct {
	__INTMAX_TYPE__ quot; /* Quotient. */
	__INTMAX_TYPE__ rem;  /* Remainder. */
};
}%[pop_macro]
%[define_replacement(imaxdiv_t = "struct __imaxdiv_struct")]
%{

#ifndef __std_imaxdiv_t_defined
#define __std_imaxdiv_t_defined 1
__NAMESPACE_STD_BEGIN
typedef struct __imaxdiv_struct imaxdiv_t;
__NAMESPACE_STD_END
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


[[std, section(".text.crt.math.utility")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_INT__), alias("abs")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("labs")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("llabs")]]
[[nothrow, ATTR_CONST, crtbuiltin]]
$intmax_t imaxabs($intmax_t x) {
	return x < 0 ? -x : x;
}

[[std, nothrow, ATTR_CONST]]
[[section(".text.crt.math.utility")]]
imaxdiv_t imaxdiv($intmax_t numer, $intmax_t denom) {
	imaxdiv_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}


[[std, ATTR_LEAF, section(".text.crt.unicode.static.convert")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("strtol")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoll", "strtoq")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("strto64", "_strtoi64")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("strto32")]]
$intmax_t strtoimax([[nonnull]] char const *__restrict nptr,
                    [[nullable]] char **endptr, int base) {
@@pp_if __SIZEOF_INTMAX_T__ <= 4@@
	return (intmax_t)strto32(nptr, endptr, base);
@@pp_else@@
	return (intmax_t)strto64(nptr, endptr, base);
@@pp_endif@@
}


[[std, ATTR_LEAF, section(".text.crt.unicode.static.convert")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("strtoul")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoull", "strtouq")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("strtou64", "_strtoui64")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("strtou32")]]
$uintmax_t strtoumax([[nonnull]] char const *__restrict nptr,
                     [[nullable]] char ** endptr, int base) {
@@pp_if __SIZEOF_INTMAX_T__ <= 4@@
	return (uintmax_t)strtou32(nptr, endptr, base);
@@pp_else@@
	return (uintmax_t)strtou64(nptr, endptr, base);
@@pp_endif@@
}


[[std, wchar, ATTR_LEAF]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("wcstol")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoll", "wcstoq")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("wcsto64", "_wcstoi64")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("wcsto32")]]
$intmax_t wcstoimax([[nonnull]] $wchar_t const *__restrict nptr,
                    [[nullable]] $wchar_t **endptr, int base)
	%{generate(str2wcs("strtoimax"))}

[[std, wchar, ATTR_LEAF]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("wcstoul")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoull", "wcstouq")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("wcstou64", "_wcstoui64")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("wcstou32")]]
$uintmax_t wcstoumax([[nonnull]] $wchar_t const *__restrict nptr,
                     [[nullable]] $wchar_t **endptr, int base)
	%{generate(str2wcs("strtoumax"))}

%
%
%
%

%#ifdef __USE_KOS
%#ifdef __USE_XOPEN2K8

[[ATTR_LEAF, export_alias("_strtoimax_l")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("strtol_l", "_strtol_l", "__strtol_l")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoll_l", "_strtoll_l", "__strtoll_l")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("strto64_l", "_strtoi64_l")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("strto32_l")]]
[[section(".text.crt{|.dos}.unicode.locale.convert")]]
$intmax_t strtoimax_l([[nonnull]] char const *__restrict nptr,
                      [[nullable]] char **endptr, int base,
                      $locale_t locale) {
	(void)locale;
	return strtoimax(nptr, endptr, base);
}


[[ATTR_LEAF, export_alias("_strtoumax_l")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("strtoul_l", "_strtoul_l", "__strtoul_l")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoull_l", "_strtoull_l", "__strtoull_l")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("strtou64_l", "_strtoui64_l")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("strtou32_l")]]
[[section(".text.crt{|.dos}.unicode.locale.convert")]]
$uintmax_t strtoumax_l([[nonnull]] char const *__restrict nptr,
                       [[nullable]] char **endptr, int base,
                       $locale_t locale) {
	(void)locale;
	return strtoumax(nptr, endptr, base);
}

[[wchar, ATTR_LEAF, dos_export_alias("_wcstoimax_l")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("wcstol_l", "_wcstol_l", "__wcstol_l")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoll_l", "_wcstoll_l", "__wcstoll_l")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("wcsto64_l", "_wcstoi64_l")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("wcsto32_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
$intmax_t wcstoimax_l([[nonnull]] $wchar_t const *__restrict nptr,
                      [[nullable]] $wchar_t **endptr, int base,
                      $locale_t locale)
	%{generate(str2wcs("strtoimax_l"))}

[[wchar, ATTR_LEAF, dos_export_alias("_wcstoumax_l")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("wcstoul_l", "_wcstoul_l", "__wcstoul_l")]]
[[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoull_l", "_wcstoull_l", "__wcstoull_l")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("wcstou64_l", "_wcstoui64_l")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("wcstou32_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
$uintmax_t wcstoumax_l([[nonnull]] $wchar_t const *__restrict nptr,
                       [[nullable]] $wchar_t **endptr, int base,
                       $locale_t locale)
	%{generate(str2wcs("strtoumax_l"))}


%#endif /* __USE_XOPEN2K8 */
%#endif /* __USE_KOS */


%
%
%
%#ifdef __USE_DOS
%[insert:function(_strtoimax_l = strtoimax_l)]
%[insert:function(_strtoumax_l = strtoumax_l)]
%[insert:function(_wcstoimax_l = wcstoimax_l)]
%[insert:function(_wcstoumax_l = wcstoumax_l)]
%#endif /* __USE_DOS */

%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_INTTYPES_H */
#endif /* __USE_UTF */

}