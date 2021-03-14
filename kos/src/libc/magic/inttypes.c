/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: ISO C99 (ISO/IEC 9899:1999) */
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/newlib/libc/include/inttypes.h) */
/* (#) Portability: DJGPP         (/include/inttypes.h) */
/* (#) Portability: FreeBSD       (/include/inttypes.h) */
/* (#) Portability: GNU C Library (/stdlib/inttypes.h) */
/* (#) Portability: MSVC          (/include/inttypes.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/inttypes.h) */
/* (#) Portability: NetBSD        (/include/inttypes.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/inttypes.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/inttypes.h) */
/* (#) Portability: diet libc     (/include/inttypes.h) */
/* (#) Portability: musl libc     (/include/inttypes.h) */
/* (#) Portability: uClibc        (/include/inttypes.h) */
}

%[define_ccompat_header("cinttypes")]
%[define_replacement(intmax_t  = __INTMAX_TYPE__)]
%[define_replacement(uintmax_t = __UINTMAX_TYPE__)]
%[define_replacement(wchar_t   = __WCHAR_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/__va_size.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

}%[insert:prefix(
#include <bits/crt/inttypes.h>
)]%{

}%[insert:prefix(
#include <stdint.h>
)]%{

#if defined(__USE_DOS) || defined(__USE_NETBSD)
#include <xlocale.h>
#endif /* __USE_DOS || __USE_NETBSD */


/* printf(): (u)int8_t */
#ifdef __PRI1_PREFIX
#define PRId8          __PRI1_PREFIX "d" /* I8d */
#define PRIi8          __PRI1_PREFIX "i" /* I8i */
#define PRIo8          __PRI1_PREFIX "o" /* I8o */
#define PRIu8          __PRI1_PREFIX "u" /* I8u */
#define PRIx8          __PRI1_PREFIX "x" /* I8x */
#define PRIX8          __PRI1_PREFIX "X" /* I8X */
#endif /* __PRI1_PREFIX */

/* printf(): (u)int16_t */
#ifdef __PRI2_PREFIX
#define PRId16         __PRI2_PREFIX "d" /* I16d */
#define PRIi16         __PRI2_PREFIX "i" /* I16i */
#define PRIo16         __PRI2_PREFIX "o" /* I16o */
#define PRIu16         __PRI2_PREFIX "u" /* I16u */
#define PRIx16         __PRI2_PREFIX "x" /* I16x */
#define PRIX16         __PRI2_PREFIX "X" /* I16X */
#endif /* __PRI2_PREFIX */

/* printf(): (u)int32_t */
#ifdef __PRI4_PREFIX
#define PRId32         __PRI4_PREFIX "d" /* I32d */
#define PRIi32         __PRI4_PREFIX "i" /* I32i */
#define PRIo32         __PRI4_PREFIX "o" /* I32o */
#define PRIu32         __PRI4_PREFIX "u" /* I32u */
#define PRIx32         __PRI4_PREFIX "x" /* I32x */
#define PRIX32         __PRI4_PREFIX "X" /* I32X */
#endif /* __PRI4_PREFIX */

/* printf(): (u)int64_t */
#ifdef __PRI8_PREFIX
#define PRId64         __PRI8_PREFIX "d" /* I64d */
#define PRIi64         __PRI8_PREFIX "i" /* I64i */
#define PRIo64         __PRI8_PREFIX "o" /* I64o */
#define PRIu64         __PRI8_PREFIX "u" /* I64u */
#define PRIx64         __PRI8_PREFIX "x" /* I64x */
#define PRIX64         __PRI8_PREFIX "X" /* I64X */
#endif /* __PRI8_PREFIX */

/* printf(): (u)int_least8_t */
#ifdef __PRIL1_PREFIX
#define PRIdLEAST8     __PRIL1_PREFIX "d"
#define PRIiLEAST8     __PRIL1_PREFIX "i"
#define PRIoLEAST8     __PRIL1_PREFIX "o"
#define PRIuLEAST8     __PRIL1_PREFIX "u"
#define PRIxLEAST8     __PRIL1_PREFIX "x"
#define PRIXLEAST8     __PRIL1_PREFIX "X"
#endif /* __PRIL1_PREFIX */

/* printf(): (u)int_least16_t */
#ifdef __PRIL2_PREFIX
#define PRIdLEAST16    __PRIL2_PREFIX "d"
#define PRIiLEAST16    __PRIL2_PREFIX "i"
#define PRIoLEAST16    __PRIL2_PREFIX "o"
#define PRIuLEAST16    __PRIL2_PREFIX "u"
#define PRIxLEAST16    __PRIL2_PREFIX "x"
#define PRIXLEAST16    __PRIL2_PREFIX "X"
#endif /* __PRIL2_PREFIX */

/* printf(): (u)int_least32_t */
#ifdef __PRIL4_PREFIX
#define PRIdLEAST32    __PRIL4_PREFIX "d"
#define PRIiLEAST32    __PRIL4_PREFIX "i"
#define PRIoLEAST32    __PRIL4_PREFIX "o"
#define PRIuLEAST32    __PRIL4_PREFIX "u"
#define PRIxLEAST32    __PRIL4_PREFIX "x"
#define PRIXLEAST32    __PRIL4_PREFIX "X"
#endif /* __PRIL4_PREFIX */

/* printf(): (u)int_least64_t */
#ifdef __PRIL8_PREFIX
#define PRIdLEAST64    __PRIL8_PREFIX "d"
#define PRIiLEAST64    __PRIL8_PREFIX "i"
#define PRIoLEAST64    __PRIL8_PREFIX "o"
#define PRIuLEAST64    __PRIL8_PREFIX "u"
#define PRIxLEAST64    __PRIL8_PREFIX "x"
#define PRIXLEAST64    __PRIL8_PREFIX "X"
#endif /* __PRIL8_PREFIX */

/* printf(): (u)int_fast8_t */
#ifdef __PRIF1_PREFIX
#define PRIdFAST8      __PRIF1_PREFIX "d"
#define PRIiFAST8      __PRIF1_PREFIX "i"
#define PRIoFAST8      __PRIF1_PREFIX "o"
#define PRIuFAST8      __PRIF1_PREFIX "u"
#define PRIxFAST8      __PRIF1_PREFIX "x"
#define PRIXFAST8      __PRIF1_PREFIX "X"
#endif /* __PRIF1_PREFIX */

/* printf(): (u)int_fast16_t */
#ifdef __PRIF2_PREFIX
#define PRIdFAST16     __PRIF2_PREFIX "d"
#define PRIiFAST16     __PRIF2_PREFIX "i"
#define PRIoFAST16     __PRIF2_PREFIX "o"
#define PRIuFAST16     __PRIF2_PREFIX "u"
#define PRIxFAST16     __PRIF2_PREFIX "x"
#define PRIXFAST16     __PRIF2_PREFIX "X"
#endif /* __PRIF2_PREFIX */

/* printf(): (u)int_fast32_t */
#ifdef __PRIF4_PREFIX
#define PRIdFAST32     __PRIF4_PREFIX "d"
#define PRIiFAST32     __PRIF4_PREFIX "i"
#define PRIoFAST32     __PRIF4_PREFIX "o"
#define PRIuFAST32     __PRIF4_PREFIX "u"
#define PRIxFAST32     __PRIF4_PREFIX "x"
#define PRIXFAST32     __PRIF4_PREFIX "X"
#endif /* __PRIF4_PREFIX */

/* printf(): (u)int_fast64_t */
#ifdef __PRIF8_PREFIX
#define PRIdFAST64     __PRIF8_PREFIX "d"
#define PRIiFAST64     __PRIF8_PREFIX "i"
#define PRIoFAST64     __PRIF8_PREFIX "o"
#define PRIuFAST64     __PRIF8_PREFIX "u"
#define PRIxFAST64     __PRIF8_PREFIX "x"
#define PRIXFAST64     __PRIF8_PREFIX "X"
#endif /* __PRIF8_PREFIX */

/* printf(): (u)intmax_t */
#if __SIZEOF_INTMAX_T__ == 8
#ifdef __PRI8_PREFIX
#define PRIdMAX        __PRI8_PREFIX "d"
#define PRIiMAX        __PRI8_PREFIX "i"
#define PRIoMAX        __PRI8_PREFIX "o"
#define PRIuMAX        __PRI8_PREFIX "u"
#define PRIxMAX        __PRI8_PREFIX "x"
#define PRIXMAX        __PRI8_PREFIX "X"
#endif /* __PRI8_PREFIX */
#else /* __SIZEOF_INTMAX_T__ == 8 */
#define PRIdMAX        __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "d"
#define PRIiMAX        __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "i"
#define PRIoMAX        __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "o"
#define PRIuMAX        __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "u"
#define PRIxMAX        __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "x"
#define PRIXMAX        __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "X"
#endif /* __SIZEOF_INTMAX_T__ != 8 */

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
/* printf(): fixed-width  pointer  (same  as  `X',  but
 *           with a fixed precision of `ELEM_SIZE * 2',
 *           meaning  that  a 32-bit  pointer  would be
 *           printed  as  C123007,  the  equivalent  of
 *           `%.8I32X') */
#ifdef __PRINP_1
#define PRIp8         __PRINP_1
#endif /* __PRINP_1 */
#ifdef __PRINP_2
#define PRIp16        __PRINP_2
#endif /* __PRINP_2 */
#ifdef __PRINP_4
#define PRIp32        __PRINP_4
#endif /* __PRINP_4 */
#ifdef __PRINP_8
#define PRIp64        __PRINP_8
#endif /* __PRINP_8 */
#ifdef __SIZEOF_INT_LEAST8_T__
#define PRIpLEAST8    __PRINP(__SIZEOF_INT_LEAST8_T__)
#endif /* __SIZEOF_INT_LEAST8_T__ */
#ifdef __SIZEOF_INT_LEAST16_T__
#define PRIpLEAST16   __PRINP(__SIZEOF_INT_LEAST16_T__)
#endif /* __SIZEOF_INT_LEAST16_T__ */
#ifdef __SIZEOF_INT_LEAST32_T__
#define PRIpLEAST32   __PRINP(__SIZEOF_INT_LEAST32_T__)
#endif /* __SIZEOF_INT_LEAST32_T__ */
#ifdef __SIZEOF_INT_LEAST64_T__
#define PRIpLEAST64   __PRINP(__SIZEOF_INT_LEAST64_T__)
#endif /* __SIZEOF_INT_LEAST64_T__ */
#ifdef __SIZEOF_INT_FAST8_T__
#define PRIpFAST8     __PRINP(__SIZEOF_INT_FAST8_T__)
#endif /* __SIZEOF_INT_FAST8_T__ */
#ifdef __SIZEOF_INT_FAST16_T__
#define PRIpFAST16    __PRINP(__SIZEOF_INT_FAST16_T__)
#endif /* __SIZEOF_INT_FAST16_T__ */
#ifdef __SIZEOF_INT_FAST32_T__
#define PRIpFAST32    __PRINP(__SIZEOF_INT_FAST32_T__)
#endif /* __SIZEOF_INT_FAST32_T__ */
#ifdef __SIZEOF_INT_FAST64_T__
#define PRIpFAST64    __PRINP(__SIZEOF_INT_FAST64_T__)
#endif /* __SIZEOF_INT_FAST64_T__ */
#ifdef __SIZEOF_INTMAX_T__
#define PRIpMAX       __PRINP(__SIZEOF_INTMAX_T__)
#endif /* __SIZEOF_INTMAX_T__ */
#define PRIpPTR       __PRINP(__SIZEOF_POINTER__) /* %p */
#define PRIpSIZ       __PRINP(__SIZEOF_SIZE_T__)
#define PRIpN(sizeof) __PRINP(sizeof)


/* printf(): (s)size_t */
#ifdef __PRIP_PREFIX
#define PRIdSIZ       __PRIP_PREFIX "d" /* Id */
#define PRIiSIZ       __PRIP_PREFIX "i" /* Ii */
#define PRIoSIZ       __PRIP_PREFIX "o" /* Io */
#define PRIuSIZ       __PRIP_PREFIX "u" /* Iu */
#define PRIxSIZ       __PRIP_PREFIX "x" /* Ix */
#define PRIXSIZ       __PRIP_PREFIX "X" /* IX */
#else /* __PRIP_PREFIX */
#define PRIdSIZ       "td" /* ptrdiff_t */
#define PRIiSIZ       "ti" /* ptrdiff_t */
#define PRIoSIZ       "zo" /* size_t */
#define PRIuSIZ       "zu" /* size_t */
#define PRIxSIZ       "zx" /* size_t */
#define PRIXSIZ       "zX" /* size_t */
#endif /* !__PRIP_PREFIX */

/* printf(): Custom size (use __SIZEOF_xxx__ macros with these) */
#define PRIdN(sizeof) __PRIN_PREFIX(sizeof) "d"
#define PRIiN(sizeof) __PRIN_PREFIX(sizeof) "i"
#define PRIoN(sizeof) __PRIN_PREFIX(sizeof) "o"
#define PRIuN(sizeof) __PRIN_PREFIX(sizeof) "u"
#define PRIxN(sizeof) __PRIN_PREFIX(sizeof) "x"
#define PRIXN(sizeof) __PRIN_PREFIX(sizeof) "X"
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
 *    using  the  same  syntax  as  a  C  compiler  would  accept:
 *       "1234":      Decimal
 *       "0777":      Octal
 *       "0xDEAD":    Hex    (casing is ignored)
 *       "0b010011":  Binary (extension; casing is ignored (on the `b' / `B')) */
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
__SYSDECL_BEGIN

#ifndef ____imaxdiv_struct_defined
#define ____imaxdiv_struct_defined 1
}%[push_macro @undef { quot rem }]%{
struct __imaxdiv_struct {
	__INTMAX_TYPE__ quot; /* Quotient. */
	__INTMAX_TYPE__ rem;  /* Remainder. */
};
}%[pop_macro]%{
#endif /* !____imaxdiv_struct_defined */
}

%[define_replacement(imaxdiv_t = "struct __imaxdiv_struct")]

%[define(DEFINE_IMAXDIV_STRUCT =
#ifndef ____imaxdiv_struct_defined
#define ____imaxdiv_struct_defined 1
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("quot")
#pragma @push_macro@("rem")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @quot@
#undef @rem@
struct __imaxdiv_struct {
	__INTMAX_TYPE__ @quot@; /* Quotient. */
	__INTMAX_TYPE__ @rem@;  /* Remainder. */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("rem")
#pragma @pop_macro@("quot")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !____imaxdiv_struct_defined */
)]

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

%[define_type_class(imaxdiv_t = "TS(__SIZEOF_IMAXDIV_STRUCT)")]

%[insert:std]


[[std, nothrow, ATTR_CONST, crtbuiltin, section(".text.crt{|.dos}.math.utility")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_INT__),       alias("abs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("labs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("llabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    alias("_abs64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_INT__),       bind_local_function(abs)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      bind_local_function(labs)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), bind_local_function(llabs)]]
[[decl_include("<hybrid/typecore.h>")]]
$intmax_t imaxabs($intmax_t x) {
	return x < 0 ? -x : x;
}

[[std, nothrow, ATTR_CONST, section(".text.crt{|.dos}.math.utility")]]
[[decl_include("<hybrid/typecore.h>"), decl_prefix(DEFINE_IMAXDIV_STRUCT)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_INT__),       alias("div")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("ldiv")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("lldiv")]]
$imaxdiv_t imaxdiv($intmax_t numer, $intmax_t denom) {
	imaxdiv_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}


[[std, ATTR_LEAF, section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("strtol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoll", "strtoq")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    alias("strto64", "_strtoi64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    alias("strto32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    bind_local_function(strto64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    bind_local_function(strto32)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
$intmax_t strtoimax([[nonnull]] char const *__restrict nptr,
                    [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_INTMAX_T__ <= 4@@
	return (intmax_t)strto32(nptr, endptr, base);
@@pp_else@@
	return (intmax_t)strto64(nptr, endptr, base);
@@pp_endif@@
}


[[std, ATTR_LEAF, section(".text.crt{|.dos}.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("strtoul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoull", "strtouq")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    alias("strtou64", "_strtoui64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    alias("strtou32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    bind_local_function(strtou64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    bind_local_function(strtou32)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
$uintmax_t strtoumax([[nonnull]] char const *__restrict nptr,
                     [[nullable]] char ** endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_INTMAX_T__ <= 4@@
	return (uintmax_t)strtou32(nptr, endptr, base);
@@pp_else@@
	return (uintmax_t)strtou64(nptr, endptr, base);
@@pp_endif@@
}


[[std, wchar, ATTR_LEAF, section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("wcstol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoll", "wcstoq")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    alias("wcsto64", "_wcstoi64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    alias("wcsto32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    bind_local_function(wcsto64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    bind_local_function(wcsto32)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
$intmax_t wcstoimax([[nonnull]] $wchar_t const *__restrict nptr,
                    [[nullable]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base)
	%{generate(str2wcs("strtoimax"))}

[[std, wchar, ATTR_LEAF, section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("wcstoul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoull", "wcstouq")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    alias("wcstou64", "_wcstoui64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    alias("wcstou32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    bind_local_function(wcstou64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    bind_local_function(wcstou32)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
$uintmax_t wcstoumax([[nonnull]] $wchar_t const *__restrict nptr,
                     [[nullable]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base)
	%{generate(str2wcs("strtoumax"))}

%
%
%
%

%#ifdef __USE_KOS
/************************************************************************/
/* WARNING: The following functions aren't exported by-name from libc!  */
/************************************************************************/
[[nocrt, ATTR_LEAF, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("strto64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("strto32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(strto64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(strto32_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
$intmax_t strtoimax_r([[nonnull]] char const *__restrict nptr,
                      [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                      [[nullable]] $errno_t *error) {
@@pp_if __SIZEOF_INTMAX_T__ >= 8@@
	return (intmax_t)strto64_r(nptr, endptr, base, error);
@@pp_elif __SIZEOF_INTMAX_T__ >= 4@@
	return (intmax_t)strto32_r(nptr, endptr, base, error);
@@pp_else@@
	s32 result = strto32_r(nptr, endptr, base, error);
	if (result > __INTMAX_MAX__) {
		if (error) {
@@pp_ifdef __ERANGE@@
			*error = __ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __INTMAX_MAX__;
	} else if (result < __INTMAX_MIN__) {
		if (error) {
@@pp_ifdef __ERANGE@@
			*error = __ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __INTMAX_MIN__;
	}
	return (intmax_t)result;
@@pp_endif@@
}

[[nocrt, ATTR_LEAF, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("strtou64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("strtou32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(strtou64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(strtou32_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
$uintmax_t strtoumax_r([[nonnull]] char const *__restrict nptr,
                       [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                       [[nullable]] $errno_t *error) {
@@pp_if __SIZEOF_INTMAX_T__ >= 8@@
	return (uintmax_t)strtou64_r(nptr, endptr, base, error);
@@pp_elif __SIZEOF_INTMAX_T__ >= 4@@
	return (uintmax_t)strtou32_r(nptr, endptr, base, error);
@@pp_else@@
	u32 result = strtou32_r(nptr, endptr, base, error);
	if (result > __UINTMAX_MAX__) {
		if (error) {
@@pp_ifdef __ERANGE@@
			*error = __ERANGE;
@@pp_else@@
			*error = 1;
@@pp_endif@@
		}
		result = __UINTMAX_MAX__;
	}
	return (uintmax_t)result;
@@pp_endif@@
}

[[wchar, nocrt, ATTR_LEAF, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("wcsto64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("wcsto32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(wcsto64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(wcsto32_r)]]
$intmax_t wcstoimax_r([[nonnull]] $wchar_t const *__restrict nptr,
                      [[nullable]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base,
                      [[nullable]] $errno_t *error)
	%{generate(str2wcs("strtoimax_r"))}

[[wchar, nocrt, ATTR_LEAF, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("wcstou64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("wcstou32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(wcstou64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(wcstou32_r)]]
$uintmax_t wcstoumax_r([[nonnull]] $wchar_t const *__restrict nptr,
                       [[nullable]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base,
                       [[nullable]] $errno_t *error)
	%{generate(str2wcs("strtoumax_r"))}
/************************************************************************/
%#endif /* __USE_KOS */

%
%#ifdef __USE_XOPEN2K8

[[ATTR_LEAF, dos_only_export_alias("_strtoimax_l"), section(".text.crt{|.dos}.unicode.locale.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("strtol_l", "_strtol_l", "__strtol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoll_l", "_strtoll_l", "__strtoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("strto64_l", "_strtoi64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("strto32_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(strto64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(strto32_l)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
$intmax_t strtoimax_l([[nonnull]] char const *__restrict nptr,
                      [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                      $locale_t locale) {
	(void)locale;
	return strtoimax(nptr, endptr, base);
}


[[ATTR_LEAF, dos_only_export_alias("_strtoumax_l"), section(".text.crt{|.dos}.unicode.locale.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("strtoul_l", "_strtoul_l", "__strtoul_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoull_l", "_strtoull_l", "__strtoull_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("strtou64_l", "_strtoui64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("strtou32_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(strtou64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(strtou32_l)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
$uintmax_t strtoumax_l([[nonnull]] char const *__restrict nptr,
                       [[nullable]] char **endptr, __STDC_INT_AS_UINT_T base,
                       $locale_t locale) {
	(void)locale;
	return strtoumax(nptr, endptr, base);
}

[[wchar, ATTR_LEAF, dos_export_alias("_wcstoimax_l"), section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("wcstol_l", "_wcstol_l", "__wcstol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoll_l", "_wcstoll_l", "__wcstoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("wcsto64_l", "_wcstoi64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("wcsto32_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(wcsto64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(wcsto32_l)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
$intmax_t wcstoimax_l([[nonnull]] $wchar_t const *__restrict nptr,
                      [[nullable]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base,
                      $locale_t locale)
	%{generate(str2wcs("strtoimax_l"))}

[[wchar, ATTR_LEAF, dos_export_alias("_wcstoumax_l"), section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("wcstoul_l", "_wcstoul_l", "__wcstoul_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoull_l", "_wcstoull_l", "__wcstoull_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("wcstou64_l", "_wcstoui64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("wcstou32_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(wcstou64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(wcstou32_l)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
$uintmax_t wcstoumax_l([[nonnull]] $wchar_t const *__restrict nptr,
                       [[nullable]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base,
                       $locale_t locale)
	%{generate(str2wcs("strtoumax_l"))}


%#endif /* __USE_XOPEN2K8 */


%
%
%
%#ifdef __USE_NETBSD

@@>> strtoi(3), strtou(3), strtoi_l(3), strtou_l(3)
@@Safely convert `nptr' to an integer which is then returned.
@@If no integer could be read, set `*rstatus' (if non-`NULL') to `ECANCELED'
@@If non-`NULL', `*endptr' is made to point past the read integer, and if
@@it points to a non-'\0'-character, `*rstatus' (if non-`NULL') to `ENOTSUP'
@@Also make sure that the returned integer lies within the
@@bounds of `[lo,hi]' (inclusively). If it does not, clamp it
@@to those bounds and set `*rstatus' (if non-`NULL') to `ERANGE'
@@@param: lo, hi:  Lo/Hi-bounds for the to-be returned integer.
@@@param: rstatus: When non-`NULL', set to a conversion error (if any)
[[ATTR_LEAF, section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[guard, impl_include("<libc/errno.h>")]]
$intmax_t strtoi([[nonnull]] char const *__restrict nptr,
                 [[nullable]] char **__restrict endptr,
                 __STDC_INT_AS_UINT_T base,
                 $intmax_t lo, $intmax_t hi,
                 [[nullable]] $errno_t *rstatus) {
	char *used_endptr;
	intmax_t result;
	result = strtoimax_r(nptr, &used_endptr, base, rstatus);
	if (endptr)
		*endptr = used_endptr;
	if (rstatus && *rstatus == 0) {
		if (*used_endptr != '\0') {
@@pp_ifdef ENOTSUP@@
			*rstatus = ENOTSUP;
@@pp_elif defined(EINVAL)@@
			*rstatus = EINVAL;
@@pp_else@@
			*rstatus = 1;
@@pp_endif@@
		} else if (result < lo) {
@@pp_ifdef ERANGE@@
			*rstatus = ERANGE;
@@pp_else@@
			*rstatus = 1;
@@pp_endif@@
			result = lo;
		} else if (result > hi) {
@@pp_ifdef ERANGE@@
			*rstatus = ERANGE;
@@pp_else@@
			*rstatus = 1;
@@pp_endif@@
			result = hi;
		} else {
			*rstatus = 0;
		}
	} else {
		if (result < lo) {
			result = lo;
		} else if (result > hi) {
			result = hi;
		}
	}
	return result;
}

[[ATTR_LEAF, section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<bits/types.h>"), doc_alias("strtoi")]]
[[guard, impl_include("<libc/errno.h>")]]
$uintmax_t strtou([[nonnull]] char const *__restrict nptr,
                  [[nullable]] char **__restrict endptr,
                  __STDC_INT_AS_UINT_T base,
                  $uintmax_t lo, $uintmax_t hi,
                  [[nullable]] $errno_t *rstatus) {
	char *used_endptr;
	uintmax_t result;
	result = strtoumax_r(nptr, &used_endptr, base, rstatus);
	if (endptr)
		*endptr = used_endptr;
	if (rstatus && *rstatus == 0) {
		if (*used_endptr != '\0') {
@@pp_ifdef ENOTSUP@@
			*rstatus = ENOTSUP;
@@pp_elif defined(EINVAL)@@
			*rstatus = EINVAL;
@@pp_else@@
			*rstatus = 1;
@@pp_endif@@
		} else if (result < lo) {
@@pp_ifdef ERANGE@@
			*rstatus = ERANGE;
@@pp_else@@
			*rstatus = 1;
@@pp_endif@@
			result = lo;
		} else if (result > hi) {
@@pp_ifdef ERANGE@@
			*rstatus = ERANGE;
@@pp_else@@
			*rstatus = 1;
@@pp_endif@@
			result = hi;
		} else {
			*rstatus = 0;
		}
	} else {
		if (result < lo) {
			result = lo;
		} else if (result > hi) {
			result = hi;
		}
	}
	return result;
}

[[ATTR_LEAF, section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<bits/types.h>"), doc_alias("strtoi")]]
[[impl_include("<libc/errno.h>")]]
$intmax_t strtoi_l([[nonnull]] char const *__restrict nptr,
                   [[nullable]] char **__restrict endptr,
                   __STDC_INT_AS_UINT_T base,
                   $intmax_t lo, $intmax_t hi,
                   [[nullable]] $errno_t *rstatus, $locale_t locale) {
	(void)locale;
	return strtoi(nptr, endptr, base, lo, hi, rstatus);
}

[[ATTR_LEAF, section(".text.crt{|.dos}.unicode.static.convert")]]
[[decl_include("<features.h>", "<bits/types.h>"), doc_alias("strtoi")]]
[[impl_include("<libc/errno.h>")]]
$uintmax_t strtou_l([[nonnull]] char const *__restrict nptr,
                    [[nullable]] char **__restrict endptr,
                    __STDC_INT_AS_UINT_T base,
                    $uintmax_t lo, $uintmax_t hi,
                    [[nullable]] $errno_t *rstatus, $locale_t locale) {
	(void)locale;
	return strtou(nptr, endptr, base, lo, hi, rstatus);
}
%#endif /* __USE_NETBSD */



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

#ifndef __INTELLISENSE__
#ifndef ____gwchar_t_defined
#define ____gwchar_t_defined 1
#define __gwchar_t __WCHAR_TYPE__
#endif /* !____gwchar_t_defined */
#endif /* !__INTELLISENSE__ */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_INTTYPES_H */
#endif /* __USE_UTF */

}
