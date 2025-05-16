/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: ISO C99 (ISO/IEC 9899:1999) */
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/newlib/libc/include/inttypes.h) */
/* (#) Portability: DJGPP         (/include/inttypes.h) */
/* (#) Portability: DragonFly BSD (/include/inttypes.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/inttypes.h) */
/* (#) Portability: FreeBSD       (/include/inttypes.h) */
/* (#) Portability: GNU C Library (/stdlib/inttypes.h) */
/* (#) Portability: GNU Hurd      (/usr/include/inttypes.h) */
/* (#) Portability: MSVC          (/include/inttypes.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/inttypes.h) */
/* (#) Portability: NetBSD        (/include/inttypes.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/inttypes.h) */
/* (#) Portability: OpenBSD       (/include/inttypes.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/inttypes.h) */
/* (#) Portability: PDCLib        (/include/inttypes.h) */
/* (#) Portability: Windows Kits  (/ucrt/inttypes.h) */
/* (#) Portability: avr-libc      (/include/inttypes.h) */
/* (#) Portability: diet libc     (/include/inttypes.h) */
/* (#) Portability: libbsd        (/include/bsd/inttypes.h) */
/* (#) Portability: libc6         (/include/inttypes.h) */
/* (#) Portability: mintlib       (/include/inttypes.h) */
/* (#) Portability: musl libc     (/include/inttypes.h) */
/* (#) Portability: uClibc        (/include/inttypes.h) */
/*!always_includes <stdint.h>*/
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
)]%[insert:prefix(
#include <bits/types.h>
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
#define PRId8 __PRI1_PREFIX "d" /* I8d */
#define PRIi8 __PRI1_PREFIX "i" /* I8i */
#define PRIo8 __PRI1_PREFIX "o" /* I8o */
#define PRIu8 __PRI1_PREFIX "u" /* I8u */
#define PRIx8 __PRI1_PREFIX "x" /* I8x */
#define PRIX8 __PRI1_PREFIX "X" /* I8X */
#endif /* __PRI1_PREFIX */

/* printf(): (u)int16_t */
#ifdef __PRI2_PREFIX
#define PRId16 __PRI2_PREFIX "d" /* I16d */
#define PRIi16 __PRI2_PREFIX "i" /* I16i */
#define PRIo16 __PRI2_PREFIX "o" /* I16o */
#define PRIu16 __PRI2_PREFIX "u" /* I16u */
#define PRIx16 __PRI2_PREFIX "x" /* I16x */
#define PRIX16 __PRI2_PREFIX "X" /* I16X */
#endif /* __PRI2_PREFIX */

/* printf(): (u)int32_t */
#ifdef __PRI4_PREFIX
#define PRId32 __PRI4_PREFIX "d" /* I32d */
#define PRIi32 __PRI4_PREFIX "i" /* I32i */
#define PRIo32 __PRI4_PREFIX "o" /* I32o */
#define PRIu32 __PRI4_PREFIX "u" /* I32u */
#define PRIx32 __PRI4_PREFIX "x" /* I32x */
#define PRIX32 __PRI4_PREFIX "X" /* I32X */
#endif /* __PRI4_PREFIX */

/* printf(): (u)int64_t */
#ifdef __PRI8_PREFIX
#define PRId64 __PRI8_PREFIX "d" /* I64d */
#define PRIi64 __PRI8_PREFIX "i" /* I64i */
#define PRIo64 __PRI8_PREFIX "o" /* I64o */
#define PRIu64 __PRI8_PREFIX "u" /* I64u */
#define PRIx64 __PRI8_PREFIX "x" /* I64x */
#define PRIX64 __PRI8_PREFIX "X" /* I64X */
#endif /* __PRI8_PREFIX */

/* printf(): (u)int_least8_t */
#ifdef __PRIL1_PREFIX
#define PRIdLEAST8 __PRIL1_PREFIX "d"
#define PRIiLEAST8 __PRIL1_PREFIX "i"
#define PRIoLEAST8 __PRIL1_PREFIX "o"
#define PRIuLEAST8 __PRIL1_PREFIX "u"
#define PRIxLEAST8 __PRIL1_PREFIX "x"
#define PRIXLEAST8 __PRIL1_PREFIX "X"
#endif /* __PRIL1_PREFIX */

/* printf(): (u)int_least16_t */
#ifdef __PRIL2_PREFIX
#define PRIdLEAST16 __PRIL2_PREFIX "d"
#define PRIiLEAST16 __PRIL2_PREFIX "i"
#define PRIoLEAST16 __PRIL2_PREFIX "o"
#define PRIuLEAST16 __PRIL2_PREFIX "u"
#define PRIxLEAST16 __PRIL2_PREFIX "x"
#define PRIXLEAST16 __PRIL2_PREFIX "X"
#endif /* __PRIL2_PREFIX */

/* printf(): (u)int_least32_t */
#ifdef __PRIL4_PREFIX
#define PRIdLEAST32 __PRIL4_PREFIX "d"
#define PRIiLEAST32 __PRIL4_PREFIX "i"
#define PRIoLEAST32 __PRIL4_PREFIX "o"
#define PRIuLEAST32 __PRIL4_PREFIX "u"
#define PRIxLEAST32 __PRIL4_PREFIX "x"
#define PRIXLEAST32 __PRIL4_PREFIX "X"
#endif /* __PRIL4_PREFIX */

/* printf(): (u)int_least64_t */
#ifdef __PRIL8_PREFIX
#define PRIdLEAST64 __PRIL8_PREFIX "d"
#define PRIiLEAST64 __PRIL8_PREFIX "i"
#define PRIoLEAST64 __PRIL8_PREFIX "o"
#define PRIuLEAST64 __PRIL8_PREFIX "u"
#define PRIxLEAST64 __PRIL8_PREFIX "x"
#define PRIXLEAST64 __PRIL8_PREFIX "X"
#endif /* __PRIL8_PREFIX */

/* printf(): (u)int_fast8_t */
#ifdef __PRIF1_PREFIX
#define PRIdFAST8 __PRIF1_PREFIX "d"
#define PRIiFAST8 __PRIF1_PREFIX "i"
#define PRIoFAST8 __PRIF1_PREFIX "o"
#define PRIuFAST8 __PRIF1_PREFIX "u"
#define PRIxFAST8 __PRIF1_PREFIX "x"
#define PRIXFAST8 __PRIF1_PREFIX "X"
#endif /* __PRIF1_PREFIX */

/* printf(): (u)int_fast16_t */
#ifdef __PRIF2_PREFIX
#define PRIdFAST16 __PRIF2_PREFIX "d"
#define PRIiFAST16 __PRIF2_PREFIX "i"
#define PRIoFAST16 __PRIF2_PREFIX "o"
#define PRIuFAST16 __PRIF2_PREFIX "u"
#define PRIxFAST16 __PRIF2_PREFIX "x"
#define PRIXFAST16 __PRIF2_PREFIX "X"
#endif /* __PRIF2_PREFIX */

/* printf(): (u)int_fast32_t */
#ifdef __PRIF4_PREFIX
#define PRIdFAST32 __PRIF4_PREFIX "d"
#define PRIiFAST32 __PRIF4_PREFIX "i"
#define PRIoFAST32 __PRIF4_PREFIX "o"
#define PRIuFAST32 __PRIF4_PREFIX "u"
#define PRIxFAST32 __PRIF4_PREFIX "x"
#define PRIXFAST32 __PRIF4_PREFIX "X"
#endif /* __PRIF4_PREFIX */

/* printf(): (u)int_fast64_t */
#ifdef __PRIF8_PREFIX
#define PRIdFAST64 __PRIF8_PREFIX "d"
#define PRIiFAST64 __PRIF8_PREFIX "i"
#define PRIoFAST64 __PRIF8_PREFIX "o"
#define PRIuFAST64 __PRIF8_PREFIX "u"
#define PRIxFAST64 __PRIF8_PREFIX "x"
#define PRIXFAST64 __PRIF8_PREFIX "X"
#endif /* __PRIF8_PREFIX */

/* printf(): (u)intmax_t */
#if __SIZEOF_INTMAX_T__ == 8
#ifdef __PRI8_PREFIX
#define PRIdMAX __PRI8_PREFIX "d"
#define PRIiMAX __PRI8_PREFIX "i"
#define PRIoMAX __PRI8_PREFIX "o"
#define PRIuMAX __PRI8_PREFIX "u"
#define PRIxMAX __PRI8_PREFIX "x"
#define PRIXMAX __PRI8_PREFIX "X"
#endif /* __PRI8_PREFIX */
#else /* __SIZEOF_INTMAX_T__ == 8 */
#define PRIdMAX __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "d"
#define PRIiMAX __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "i"
#define PRIoMAX __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "o"
#define PRIuMAX __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "u"
#define PRIxMAX __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "x"
#define PRIXMAX __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "X"
#endif /* __SIZEOF_INTMAX_T__ != 8 */

/* printf(): (u)intptr_t / void * */
#ifdef __PRIP_PREFIX
#define PRIdPTR __PRIP_PREFIX "d" /* Id */
#define PRIiPTR __PRIP_PREFIX "i" /* Ii */
#define PRIoPTR __PRIP_PREFIX "o" /* Io */
#define PRIuPTR __PRIP_PREFIX "u" /* Iu */
#define PRIxPTR __PRIP_PREFIX "x" /* Ix */
#define PRIXPTR __PRIP_PREFIX "X" /* IX */
#else /* __PRIP_PREFIX */
#define PRIdPTR "td" /* ptrdiff_t */
#define PRIiPTR "ti" /* ptrdiff_t */
#define PRIoPTR "zo" /* size_t */
#define PRIuPTR "zu" /* size_t */
#define PRIxPTR "zx" /* size_t */
#define PRIXPTR "zX" /* size_t */
#endif /* !__PRIP_PREFIX */

#ifdef __USE_KOS
/* printf(): fixed-width  pointer  (same  as  `X',  but
 *           with a fixed precision of `ELEM_SIZE * 2',
 *           meaning  that  a 32-bit  pointer  would be
 *           printed  as  C123007,  the  equivalent  of
 *           `%.8I32X') */
#ifdef __PRINP_1
#define PRIp8 __PRINP_1
#endif /* __PRINP_1 */
#ifdef __PRINP_2
#define PRIp16 __PRINP_2
#endif /* __PRINP_2 */
#ifdef __PRINP_4
#define PRIp32 __PRINP_4
#endif /* __PRINP_4 */
#ifdef __PRINP_8
#define PRIp64 __PRINP_8
#endif /* __PRINP_8 */
#ifdef __SIZEOF_INT_LEAST8_T__
#define PRIpLEAST8 __PRINP(__SIZEOF_INT_LEAST8_T__)
#endif /* __SIZEOF_INT_LEAST8_T__ */
#ifdef __SIZEOF_INT_LEAST16_T__
#define PRIpLEAST16 __PRINP(__SIZEOF_INT_LEAST16_T__)
#endif /* __SIZEOF_INT_LEAST16_T__ */
#ifdef __SIZEOF_INT_LEAST32_T__
#define PRIpLEAST32 __PRINP(__SIZEOF_INT_LEAST32_T__)
#endif /* __SIZEOF_INT_LEAST32_T__ */
#ifdef __SIZEOF_INT_LEAST64_T__
#define PRIpLEAST64 __PRINP(__SIZEOF_INT_LEAST64_T__)
#endif /* __SIZEOF_INT_LEAST64_T__ */
#ifdef __SIZEOF_INT_FAST8_T__
#define PRIpFAST8 __PRINP(__SIZEOF_INT_FAST8_T__)
#endif /* __SIZEOF_INT_FAST8_T__ */
#ifdef __SIZEOF_INT_FAST16_T__
#define PRIpFAST16 __PRINP(__SIZEOF_INT_FAST16_T__)
#endif /* __SIZEOF_INT_FAST16_T__ */
#ifdef __SIZEOF_INT_FAST32_T__
#define PRIpFAST32 __PRINP(__SIZEOF_INT_FAST32_T__)
#endif /* __SIZEOF_INT_FAST32_T__ */
#ifdef __SIZEOF_INT_FAST64_T__
#define PRIpFAST64 __PRINP(__SIZEOF_INT_FAST64_T__)
#endif /* __SIZEOF_INT_FAST64_T__ */
#ifdef __SIZEOF_INTMAX_T__
#define PRIpMAX __PRINP(__SIZEOF_INTMAX_T__)
#endif  /* __SIZEOF_INTMAX_T__ */
#define PRIpPTR       __PRINP(__SIZEOF_POINTER__) /* %p */
#define PRIpSIZ       __PRINP(__SIZEOF_SIZE_T__)
#define PRIpN(sizeof) __PRINP(sizeof)

#ifdef __PRI1_PREFIX
#define PRIb8 __PRI1_PREFIX "b" /* I8b */
#endif /* __PRI1_PREFIX */
#ifdef __PRI2_PREFIX
#define PRIb16 __PRI2_PREFIX "b" /* I16b */
#endif /* __PRI2_PREFIX */
#ifdef __PRI4_PREFIX
#define PRIb32 __PRI4_PREFIX "b" /* I32b */
#endif /* __PRI4_PREFIX */
#ifdef __PRI8_PREFIX
#define PRIb64 __PRI8_PREFIX "b" /* I64b */
#endif /* __PRI8_PREFIX */
#ifdef __PRIL1_PREFIX
#define PRIbLEAST8 __PRIL1_PREFIX "b"
#endif /* __PRIL1_PREFIX */
#ifdef __PRIL2_PREFIX
#define PRIbLEAST16 __PRIL2_PREFIX "b"
#endif /* __PRIL2_PREFIX */
#ifdef __PRIL4_PREFIX
#define PRIbLEAST32 __PRIL4_PREFIX "b"
#endif /* __PRIL4_PREFIX */
#ifdef __PRIL8_PREFIX
#define PRIbLEAST64 __PRIL8_PREFIX "b"
#endif /* __PRIL8_PREFIX */
#ifdef __PRIF1_PREFIX
#define PRIbFAST8 __PRIF1_PREFIX "b"
#endif /* __PRIF1_PREFIX */
#ifdef __PRIF2_PREFIX
#define PRIbFAST16 __PRIF2_PREFIX "b"
#endif /* __PRIF2_PREFIX */
#ifdef __PRIF4_PREFIX
#define PRIbFAST32 __PRIF4_PREFIX "b"
#endif /* __PRIF4_PREFIX */
#ifdef __PRIF8_PREFIX
#define PRIbFAST64 __PRIF8_PREFIX "b"
#endif /* __PRIF8_PREFIX */
#if __SIZEOF_INTMAX_T__ == 8
#ifdef __PRI8_PREFIX
#define PRIbMAX __PRI8_PREFIX "b"
#endif /* __PRI8_PREFIX */
#else /* __SIZEOF_INTMAX_T__ == 8 */
#define PRIbMAX __PRIN_PREFIX(__SIZEOF_INTMAX_T__) "b"
#endif /* __SIZEOF_INTMAX_T__ != 8 */


/* printf(): char8_t / char16_t / char32_t */
#ifdef __CRT_KOS
#define PRIc7  "c"    /* ASCII character (by ordinal: U+0000 - U+007F) */
#define PRIc8  "I8c"  /* 8-bit character (by ordinal: U+0000 - U+00FF; iow: LATIN-1) */
#if __SIZEOF_SHORT__ == 2
#define PRIc16 "hc"   /* 16-bit character (by ordinal: U+0000 - U+FFFF) */
#else /* __SIZEOF_SHORT__ == 2 */
#define PRIc16 "I16c" /* 16-bit character (by ordinal: U+0000 - U+FFFF) */
#endif /* __SIZEOF_SHORT__ != 2 */
#if __SIZEOF_LONG__ == 4
#define PRIc32 "lc"   /* 32-bit character (by ordinal: U+00000000 - U+FFFFFFFF) */
#else /* __SIZEOF_LONG__ == 4 */
#define PRIc32 "I32c" /* 32-bit character (by ordinal: U+00000000 - U+FFFFFFFF) */
#endif /* __SIZEOF_LONG__ != 4 */
#endif /* __PRI4_PREFIX */


/* printf(): (s)size_t */
#ifdef __PRIP_PREFIX
#define PRIdSIZ __PRIP_PREFIX "d" /* Id */
#define PRIiSIZ __PRIP_PREFIX "i" /* Ii */
#define PRIoSIZ __PRIP_PREFIX "o" /* Io */
#define PRIuSIZ __PRIP_PREFIX "u" /* Iu */
#define PRIxSIZ __PRIP_PREFIX "x" /* Ix */
#define PRIXSIZ __PRIP_PREFIX "X" /* IX */
#define PRIbSIZ __PRIP_PREFIX "b" /* Ib */
#define PRIbPTR __PRIP_PREFIX "b" /* Ib */
#else /* __PRIP_PREFIX */
#define PRIdSIZ "td" /* ptrdiff_t */
#define PRIiSIZ "ti" /* ptrdiff_t */
#define PRIoSIZ "zo" /* size_t */
#define PRIuSIZ "zu" /* size_t */
#define PRIxSIZ "zx" /* size_t */
#define PRIXSIZ "zX" /* size_t */
#define PRIbSIZ "tb" /* size_t */
#define PRIbPTR "zb" /* uintptr_t */
#endif /* !__PRIP_PREFIX */

/* printf(): Custom size (use __SIZEOF_xxx__ macros with these) */
#define PRIdN(sizeof) __PRIN_PREFIX(sizeof) "d"
#define PRIiN(sizeof) __PRIN_PREFIX(sizeof) "i"
#define PRIoN(sizeof) __PRIN_PREFIX(sizeof) "o"
#define PRIuN(sizeof) __PRIN_PREFIX(sizeof) "u"
#define PRIxN(sizeof) __PRIN_PREFIX(sizeof) "x"
#define PRIXN(sizeof) __PRIN_PREFIX(sizeof) "X"
#define PRIbN(sizeof) __PRIN_PREFIX(sizeof) "b"


/************************************************************************/
/* PRIMAX[duoxX][...]  -- Longest strings produced by PRI[duoxX][...] modifies.
 * These can be used to safely determine required buffer sizes for `sprintf(3)'
 * >> char buf[COMPILER_LENOF(PRIMAXd)];
 * >> sprintf(buf, "%d", any_value); // Never overflows, and doesn't waste stack memory! */
/************************************************************************/
#define __PRIMAXd1 "-128"                                                             /* "%" PRId8 */
#define __PRIMAXi1 "-128"                                                             /* "%" PRIi8 */
#define __PRIMAXo1 "377"                                                              /* "%" PRIo8 */
#define __PRIMAXu1 "255"                                                              /* "%" PRIu8 */
#define __PRIMAXx1 "ff"                                                               /* "%" PRIx8 */
#define __PRIMAXX1 "FF"                                                               /* "%" PRIX8 */
#define __PRIMAXb1 "11111111"                                                         /* "%" PRIb8 */
#define __PRIMAXd2 "-32768"                                                           /* "%" PRId16 */
#define __PRIMAXi2 "-32768"                                                           /* "%" PRIi16 */
#define __PRIMAXo2 "177777"                                                           /* "%" PRIo16 */
#define __PRIMAXu2 "65535"                                                            /* "%" PRIu16 */
#define __PRIMAXx2 "ffff"                                                             /* "%" PRIx16 */
#define __PRIMAXX2 "FFFF"                                                             /* "%" PRIX16 */
#define __PRIMAXb2 "1111111111111111"                                                 /* "%" PRIb16 */
#define __PRIMAXd4 "-2147483648"                                                      /* "%" PRId32 */
#define __PRIMAXi4 "-2147483648"                                                      /* "%" PRIi32 */
#define __PRIMAXo4 "37777777777"                                                      /* "%" PRIo32 */
#define __PRIMAXu4 "4294967295"                                                       /* "%" PRIu32 */
#define __PRIMAXx4 "ffffffff"                                                         /* "%" PRIx32 */
#define __PRIMAXX4 "FFFFFFFF"                                                         /* "%" PRIX32 */
#define __PRIMAXb4 "11111111111111111111111111111111"                                 /* "%" PRIb32 */
#define __PRIMAXd8 "-9223372036854775808"                                             /* "%" PRId64 */
#define __PRIMAXi8 "-9223372036854775808"                                             /* "%" PRIi64 */
#define __PRIMAXo8 "1777777777777777777777"                                           /* "%" PRIo64 */
#define __PRIMAXu8 "18446744073709551615"                                             /* "%" PRIu64 */
#define __PRIMAXx8 "ffffffffffffffff"                                                 /* "%" PRIx64 */
#define __PRIMAXX8 "FFFFFFFFFFFFFFFF"                                                 /* "%" PRIX64 */
#define __PRIMAXb8 "1111111111111111111111111111111111111111111111111111111111111111" /* "%" PRIb64 */

#define __PRIMAXdN(sizeof) __PRIMAXd##sizeof
#define __PRIMAXiN(sizeof) __PRIMAXi##sizeof
#define __PRIMAXoN(sizeof) __PRIMAXo##sizeof
#define __PRIMAXuN(sizeof) __PRIMAXu##sizeof
#define __PRIMAXxN(sizeof) __PRIMAXx##sizeof
#define __PRIMAXXN(sizeof) __PRIMAXX##sizeof
#define __PRIMAXbN(sizeof) __PRIMAXb##sizeof

#define PRIMAXdN(sizeof) __PRIMAXdN(sizeof)
#define PRIMAXiN(sizeof) __PRIMAXiN(sizeof)
#define PRIMAXoN(sizeof) __PRIMAXoN(sizeof)
#define PRIMAXuN(sizeof) __PRIMAXuN(sizeof)
#define PRIMAXxN(sizeof) __PRIMAXxN(sizeof)
#define PRIMAXXN(sizeof) __PRIMAXXN(sizeof)
#define PRIMAXbN(sizeof) __PRIMAXbN(sizeof)

#define PRIMAXd8  __PRIMAXd1 /* "%" PRId8  -- "-128" */
#define PRIMAXi8  __PRIMAXi1 /* "%" PRIi8  -- "-128" */
#define PRIMAXo8  __PRIMAXo1 /* "%" PRIo8  -- "377" */
#define PRIMAXu8  __PRIMAXu1 /* "%" PRIu8  -- "255" */
#define PRIMAXx8  __PRIMAXx1 /* "%" PRIx8  -- "ff" */
#define PRIMAXX8  __PRIMAXX1 /* "%" PRIX8  -- "FF" */
#define PRIMAXb8  __PRIMAXb1 /* "%" PRIb8  -- "11111111" */
#define PRIMAXd16 __PRIMAXd2 /* "%" PRId16 -- "-32768" */
#define PRIMAXi16 __PRIMAXi2 /* "%" PRIi16 -- "-32768" */
#define PRIMAXo16 __PRIMAXo2 /* "%" PRIo16 -- "177777" */
#define PRIMAXu16 __PRIMAXu2 /* "%" PRIu16 -- "65535" */
#define PRIMAXx16 __PRIMAXx2 /* "%" PRIx16 -- "ffff" */
#define PRIMAXX16 __PRIMAXX2 /* "%" PRIX16 -- "FFFF" */
#define PRIMAXb16 __PRIMAXb2 /* "%" PRIb16 -- "1111111111111111" */
#define PRIMAXd32 __PRIMAXd4 /* "%" PRId32 -- "-2147483648" */
#define PRIMAXi32 __PRIMAXi4 /* "%" PRIi32 -- "-2147483648" */
#define PRIMAXo32 __PRIMAXo4 /* "%" PRIo32 -- "37777777777" */
#define PRIMAXu32 __PRIMAXu4 /* "%" PRIu32 -- "4294967295" */
#define PRIMAXx32 __PRIMAXx4 /* "%" PRIx32 -- "ffffffff" */
#define PRIMAXX32 __PRIMAXX4 /* "%" PRIX32 -- "FFFFFFFF" */
#define PRIMAXb32 __PRIMAXb4 /* "%" PRIb32 -- "11111111111111111111111111111111" */
#define PRIMAXd64 __PRIMAXd8 /* "%" PRId64 -- "-9223372036854775808" */
#define PRIMAXi64 __PRIMAXi8 /* "%" PRIi64 -- "-9223372036854775808" */
#define PRIMAXo64 __PRIMAXo8 /* "%" PRIo64 -- "1777777777777777777777" */
#define PRIMAXu64 __PRIMAXu8 /* "%" PRIu64 -- "18446744073709551615" */
#define PRIMAXx64 __PRIMAXx8 /* "%" PRIx64 -- "ffffffffffffffff" */
#define PRIMAXX64 __PRIMAXX8 /* "%" PRIX64 -- "FFFFFFFFFFFFFFFF" */
#define PRIMAXb64 __PRIMAXb8 /* "%" PRIb64 -- "1111111111111111111111111111111111111111111111111111111111111111" */

#define PRIMAXd        PRIMAXdN(__SIZEOF_INT__)           /* "%d" */
#define PRIMAXi        PRIMAXiN(__SIZEOF_INT__)           /* "%i" */
#define PRIMAXo        PRIMAXoN(__SIZEOF_INT__)           /* "%o" */
#define PRIMAXu        PRIMAXuN(__SIZEOF_INT__)           /* "%u" */
#define PRIMAXx        PRIMAXxN(__SIZEOF_INT__)           /* "%x" */
#define PRIMAXX        PRIMAXXN(__SIZEOF_INT__)           /* "%X" */
#define PRIMAXb        PRIMAXbN(__SIZEOF_INT__)           /* "%X" *b
#define PRIMAXdSIZ     PRIMAXdN(__SIZEOF_SIZE_T__)        /* "%" PRIdSIZ */
#define PRIMAXiSIZ     PRIMAXiN(__SIZEOF_SIZE_T__)        /* "%" PRIiSIZ */
#define PRIMAXoSIZ     PRIMAXoN(__SIZEOF_SIZE_T__)        /* "%" PRIoSIZ */
#define PRIMAXuSIZ     PRIMAXuN(__SIZEOF_SIZE_T__)        /* "%" PRIuSIZ */
#define PRIMAXxSIZ     PRIMAXxN(__SIZEOF_SIZE_T__)        /* "%" PRIxSIZ */
#define PRIMAXXSIZ     PRIMAXXN(__SIZEOF_SIZE_T__)        /* "%" PRIXSIZ */
#define PRIMAXbSIZ     PRIMAXbN(__SIZEOF_SIZE_T__)        /* "%" PRIbSIZ */
#define PRIMAXdPTR     PRIMAXdN(__SIZEOF_POINTER__)       /* "%" PRIdSIZ */
#define PRIMAXiPTR     PRIMAXiN(__SIZEOF_POINTER__)       /* "%" PRIiSIZ */
#define PRIMAXoPTR     PRIMAXoN(__SIZEOF_POINTER__)       /* "%" PRIoSIZ */
#define PRIMAXuPTR     PRIMAXuN(__SIZEOF_POINTER__)       /* "%" PRIuSIZ */
#define PRIMAXxPTR     PRIMAXxN(__SIZEOF_POINTER__)       /* "%" PRIxSIZ */
#define PRIMAXXPTR     PRIMAXXN(__SIZEOF_POINTER__)       /* "%" PRIXSIZ */
#define PRIMAXbPTR     PRIMAXbN(__SIZEOF_POINTER__)       /* "%" PRIbSIZ */
#define PRIMAXdMAX     PRIMAXdN(__SIZEOF_INTMAX_T__)      /* "%" PRIdMAX */
#define PRIMAXiMAX     PRIMAXiN(__SIZEOF_INTMAX_T__)      /* "%" PRIiMAX */
#define PRIMAXoMAX     PRIMAXoN(__SIZEOF_INTMAX_T__)      /* "%" PRIoMAX */
#define PRIMAXuMAX     PRIMAXuN(__SIZEOF_INTMAX_T__)      /* "%" PRIuMAX */
#define PRIMAXxMAX     PRIMAXxN(__SIZEOF_INTMAX_T__)      /* "%" PRIxMAX */
#define PRIMAXXMAX     PRIMAXXN(__SIZEOF_INTMAX_T__)      /* "%" PRIXMAX */
#define PRIMAXbMAX     PRIMAXbN(__SIZEOF_INTMAX_T__)      /* "%" PRIbMAX */
#ifdef __SIZEOF_INT_LEAST8_T__
#define PRIMAXdLEAST8  PRIMAXdN(__SIZEOF_INT_LEAST8_T__)  /* "%" PRIdLEAST8 */
#define PRIMAXiLEAST8  PRIMAXiN(__SIZEOF_INT_LEAST8_T__)  /* "%" PRIiLEAST8 */
#define PRIMAXoLEAST8  PRIMAXoN(__SIZEOF_INT_LEAST8_T__)  /* "%" PRIoLEAST8 */
#define PRIMAXuLEAST8  PRIMAXuN(__SIZEOF_INT_LEAST8_T__)  /* "%" PRIuLEAST8 */
#define PRIMAXxLEAST8  PRIMAXxN(__SIZEOF_INT_LEAST8_T__)  /* "%" PRIxLEAST8 */
#define PRIMAXXLEAST8  PRIMAXXN(__SIZEOF_INT_LEAST8_T__)  /* "%" PRIXLEAST8 */
#define PRIMAXbLEAST8  PRIMAXbN(__SIZEOF_INT_LEAST8_T__)  /* "%" PRIbLEAST8 */
#endif /* __SIZEOF_INT_LEAST8_T__ */
#ifdef __SIZEOF_INT_LEAST16_T__
#define PRIMAXdLEAST16 PRIMAXdN(__SIZEOF_INT_LEAST16_T__) /* "%" PRIdLEAST16 */
#define PRIMAXiLEAST16 PRIMAXiN(__SIZEOF_INT_LEAST16_T__) /* "%" PRIiLEAST16 */
#define PRIMAXoLEAST16 PRIMAXoN(__SIZEOF_INT_LEAST16_T__) /* "%" PRIoLEAST16 */
#define PRIMAXuLEAST16 PRIMAXuN(__SIZEOF_INT_LEAST16_T__) /* "%" PRIuLEAST16 */
#define PRIMAXxLEAST16 PRIMAXxN(__SIZEOF_INT_LEAST16_T__) /* "%" PRIxLEAST16 */
#define PRIMAXXLEAST16 PRIMAXXN(__SIZEOF_INT_LEAST16_T__) /* "%" PRIXLEAST16 */
#define PRIMAXbLEAST16 PRIMAXbN(__SIZEOF_INT_LEAST16_T__) /* "%" PRIbLEAST16 */
#endif /* __SIZEOF_INT_LEAST16_T__ */
#ifdef __SIZEOF_INT_LEAST32_T__
#define PRIMAXdLEAST32 PRIMAXdN(__SIZEOF_INT_LEAST32_T__) /* "%" PRIdLEAST32 */
#define PRIMAXiLEAST32 PRIMAXiN(__SIZEOF_INT_LEAST32_T__) /* "%" PRIiLEAST32 */
#define PRIMAXoLEAST32 PRIMAXoN(__SIZEOF_INT_LEAST32_T__) /* "%" PRIoLEAST32 */
#define PRIMAXuLEAST32 PRIMAXuN(__SIZEOF_INT_LEAST32_T__) /* "%" PRIuLEAST32 */
#define PRIMAXxLEAST32 PRIMAXxN(__SIZEOF_INT_LEAST32_T__) /* "%" PRIxLEAST32 */
#define PRIMAXXLEAST32 PRIMAXXN(__SIZEOF_INT_LEAST32_T__) /* "%" PRIXLEAST32 */
#define PRIMAXbLEAST32 PRIMAXbN(__SIZEOF_INT_LEAST32_T__) /* "%" PRIbLEAST32 */
#endif /* __SIZEOF_INT_LEAST32_T__ */
#ifdef __SIZEOF_INT_LEAST64_T__
#define PRIMAXdLEAST64 PRIMAXdN(__SIZEOF_INT_LEAST64_T__) /* "%" PRIdLEAST64 */
#define PRIMAXiLEAST64 PRIMAXiN(__SIZEOF_INT_LEAST64_T__) /* "%" PRIiLEAST64 */
#define PRIMAXoLEAST64 PRIMAXoN(__SIZEOF_INT_LEAST64_T__) /* "%" PRIoLEAST64 */
#define PRIMAXuLEAST64 PRIMAXuN(__SIZEOF_INT_LEAST64_T__) /* "%" PRIuLEAST64 */
#define PRIMAXxLEAST64 PRIMAXxN(__SIZEOF_INT_LEAST64_T__) /* "%" PRIxLEAST64 */
#define PRIMAXXLEAST64 PRIMAXXN(__SIZEOF_INT_LEAST64_T__) /* "%" PRIXLEAST64 */
#define PRIMAXbLEAST64 PRIMAXbN(__SIZEOF_INT_LEAST64_T__) /* "%" PRIbLEAST64 */
#endif /* __SIZEOF_INT_LEAST64_T__ */
#ifdef __SIZEOF_INT_FAST8_T__
#define PRIMAXdFAST8   PRIMAXdN(__SIZEOF_INT_FAST8_T__)   /* "%" PRIdFAST8 */
#define PRIMAXiFAST8   PRIMAXiN(__SIZEOF_INT_FAST8_T__)   /* "%" PRIiFAST8 */
#define PRIMAXoFAST8   PRIMAXoN(__SIZEOF_INT_FAST8_T__)   /* "%" PRIoFAST8 */
#define PRIMAXuFAST8   PRIMAXuN(__SIZEOF_INT_FAST8_T__)   /* "%" PRIuFAST8 */
#define PRIMAXxFAST8   PRIMAXxN(__SIZEOF_INT_FAST8_T__)   /* "%" PRIxFAST8 */
#define PRIMAXXFAST8   PRIMAXXN(__SIZEOF_INT_FAST8_T__)   /* "%" PRIXFAST8 */
#define PRIMAXbFAST8   PRIMAXbN(__SIZEOF_INT_FAST8_T__)   /* "%" PRIbFAST8 */
#endif /* __SIZEOF_INT_FAST8_T__ */
#ifdef __SIZEOF_INT_FAST16_T__
#define PRIMAXdFAST16  PRIMAXdN(__SIZEOF_INT_FAST16_T__)  /* "%" PRIdFAST16 */
#define PRIMAXiFAST16  PRIMAXiN(__SIZEOF_INT_FAST16_T__)  /* "%" PRIiFAST16 */
#define PRIMAXoFAST16  PRIMAXoN(__SIZEOF_INT_FAST16_T__)  /* "%" PRIoFAST16 */
#define PRIMAXuFAST16  PRIMAXuN(__SIZEOF_INT_FAST16_T__)  /* "%" PRIuFAST16 */
#define PRIMAXxFAST16  PRIMAXxN(__SIZEOF_INT_FAST16_T__)  /* "%" PRIxFAST16 */
#define PRIMAXXFAST16  PRIMAXXN(__SIZEOF_INT_FAST16_T__)  /* "%" PRIXFAST16 */
#define PRIMAXbFAST16  PRIMAXbN(__SIZEOF_INT_FAST16_T__)  /* "%" PRIbFAST16 */
#endif /* __SIZEOF_INT_FAST16_T__ */
#ifdef __SIZEOF_INT_FAST32_T__
#define PRIMAXdFAST32  PRIMAXdN(__SIZEOF_INT_FAST32_T__)  /* "%" PRIdFAST32 */
#define PRIMAXiFAST32  PRIMAXiN(__SIZEOF_INT_FAST32_T__)  /* "%" PRIiFAST32 */
#define PRIMAXoFAST32  PRIMAXoN(__SIZEOF_INT_FAST32_T__)  /* "%" PRIoFAST32 */
#define PRIMAXuFAST32  PRIMAXuN(__SIZEOF_INT_FAST32_T__)  /* "%" PRIuFAST32 */
#define PRIMAXxFAST32  PRIMAXxN(__SIZEOF_INT_FAST32_T__)  /* "%" PRIxFAST32 */
#define PRIMAXXFAST32  PRIMAXXN(__SIZEOF_INT_FAST32_T__)  /* "%" PRIXFAST32 */
#define PRIMAXbFAST32  PRIMAXbN(__SIZEOF_INT_FAST32_T__)  /* "%" PRIbFAST32 */
#endif /* __SIZEOF_INT_FAST32_T__ */
#ifdef __SIZEOF_INT_FAST64_T__
#define PRIMAXdFAST64  PRIMAXdN(__SIZEOF_INT_FAST64_T__)  /* "%" PRIdFAST64 */
#define PRIMAXiFAST64  PRIMAXiN(__SIZEOF_INT_FAST64_T__)  /* "%" PRIiFAST64 */
#define PRIMAXoFAST64  PRIMAXoN(__SIZEOF_INT_FAST64_T__)  /* "%" PRIoFAST64 */
#define PRIMAXuFAST64  PRIMAXuN(__SIZEOF_INT_FAST64_T__)  /* "%" PRIuFAST64 */
#define PRIMAXxFAST64  PRIMAXxN(__SIZEOF_INT_FAST64_T__)  /* "%" PRIxFAST64 */
#define PRIMAXXFAST64  PRIMAXXN(__SIZEOF_INT_FAST64_T__)  /* "%" PRIXFAST64 */
#define PRIMAXbFAST64  PRIMAXbN(__SIZEOF_INT_FAST64_T__)  /* "%" PRIbFAST64 */
#endif /* __SIZEOF_INT_FAST64_T__ */

#endif /* __USE_KOS */




/* scanf(): (u)int8_t */
#define SCNd8 __SCA1_PREFIX "d"
#define SCNi8 __SCA1_PREFIX "i"
#define SCNu8 __SCA1_PREFIX "u"
#define SCNo8 __SCA1_PREFIX "o"
#define SCNx8 __SCA1_PREFIX "x"

/* scanf(): (u)int16_t */
#define SCNd16 __SCA2_PREFIX "d"
#define SCNi16 __SCA2_PREFIX "i"
#define SCNu16 __SCA2_PREFIX "u"
#define SCNo16 __SCA2_PREFIX "o"
#define SCNx16 __SCA2_PREFIX "x"

/* scanf(): (u)int32_t */
#define SCNd32 __SCA4_PREFIX "d"
#define SCNi32 __SCA4_PREFIX "i"
#define SCNu32 __SCA4_PREFIX "u"
#define SCNo32 __SCA4_PREFIX "o"
#define SCNx32 __SCA4_PREFIX "x"

/* scanf(): (u)int64_t */
#define SCNd64 __SCA8_PREFIX "d"
#define SCNi64 __SCA8_PREFIX "i"
#define SCNu64 __SCA8_PREFIX "u"
#define SCNo64 __SCA8_PREFIX "o"
#define SCNx64 __SCA8_PREFIX "x"

/* scanf(): (u)int_least8_t */
#define SCNdLEAST8 __SCAL1_PREFIX "d"
#define SCNiLEAST8 __SCAL1_PREFIX "i"
#define SCNuLEAST8 __SCAL1_PREFIX "u"
#define SCNoLEAST8 __SCAL1_PREFIX "o"
#define SCNxLEAST8 __SCAL1_PREFIX "x"

/* scanf(): (u)int_least16_t */
#define SCNdLEAST16 __SCAL2_PREFIX "d"
#define SCNiLEAST16 __SCAL2_PREFIX "i"
#define SCNuLEAST16 __SCAL2_PREFIX "u"
#define SCNoLEAST16 __SCAL2_PREFIX "o"
#define SCNxLEAST16 __SCAL2_PREFIX "x"

/* scanf(): (u)int_least32_t */
#define SCNdLEAST32 __SCAL4_PREFIX "d"
#define SCNiLEAST32 __SCAL4_PREFIX "i"
#define SCNuLEAST32 __SCAL4_PREFIX "u"
#define SCNoLEAST32 __SCAL4_PREFIX "o"
#define SCNxLEAST32 __SCAL4_PREFIX "x"

/* scanf(): (u)int_least64_t */
#define SCNdLEAST64 __SCAL8_PREFIX "d"
#define SCNiLEAST64 __SCAL8_PREFIX "i"
#define SCNuLEAST64 __SCAL8_PREFIX "u"
#define SCNoLEAST64 __SCAL8_PREFIX "o"
#define SCNxLEAST64 __SCAL8_PREFIX "x"

/* scanf(): (u)int_fast8_t */
#define SCNdFAST8 __SCAF1_PREFIX "d"
#define SCNiFAST8 __SCAF1_PREFIX "i"
#define SCNuFAST8 __SCAF1_PREFIX "u"
#define SCNoFAST8 __SCAF1_PREFIX "o"
#define SCNxFAST8 __SCAF1_PREFIX "x"

/* scanf(): (u)int_fast16_t */
#define SCNdFAST16 __SCAF2_PREFIX "d"
#define SCNiFAST16 __SCAF2_PREFIX "i"
#define SCNuFAST16 __SCAF2_PREFIX "u"
#define SCNoFAST16 __SCAF2_PREFIX "o"
#define SCNxFAST16 __SCAF2_PREFIX "x"

/* scanf(): (u)int_fast32_t */
#define SCNdFAST32 __SCAF4_PREFIX "d"
#define SCNiFAST32 __SCAF4_PREFIX "i"
#define SCNuFAST32 __SCAF4_PREFIX "u"
#define SCNoFAST32 __SCAF4_PREFIX "o"
#define SCNxFAST32 __SCAF4_PREFIX "x"

/* scanf(): (u)int_fast64_t */
#define SCNdFAST64 __SCAF8_PREFIX "d"
#define SCNiFAST64 __SCAF8_PREFIX "i"
#define SCNuFAST64 __SCAF8_PREFIX "u"
#define SCNoFAST64 __SCAF8_PREFIX "o"
#define SCNxFAST64 __SCAF8_PREFIX "x"

/* scanf(): (u)intmax_t */
#define SCNdMAX __SCA8_PREFIX "d"
#define SCNiMAX __SCA8_PREFIX "i"
#define SCNuMAX __SCA8_PREFIX "u"
#define SCNoMAX __SCA8_PREFIX "o"
#define SCNxMAX __SCA8_PREFIX "x"

/* scanf(): (u)intptr_t / void * */
#define SCNdPTR __SCAP_PREFIX "d"
#define SCNiPTR __SCAP_PREFIX "i"
#define SCNuPTR __SCAP_PREFIX "u"
#define SCNoPTR __SCAP_PREFIX "o"
#define SCNxPTR __SCAP_PREFIX "x"

#ifdef __USE_KOS
/* scanf(): (s)size_t */
#define SCNdSIZ __SCAP_PREFIX "d"
#define SCNiSIZ __SCAP_PREFIX "i"
#define SCNuSIZ __SCAP_PREFIX "u"
#define SCNoSIZ __SCAP_PREFIX "o"
#define SCNxSIZ __SCAP_PREFIX "x"

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
#define SCNU8         __SCA1_PREFIX "U"
#define SCNU16        __SCA2_PREFIX "U"
#define SCNU32        __SCA4_PREFIX "U"
#define SCNU64        __SCA8_PREFIX "U"
#define SCNULEAST8    __SCAL1_PREFIX "U"
#define SCNULEAST16   __SCAL2_PREFIX "U"
#define SCNULEAST32   __SCAL4_PREFIX "U"
#define SCNULEAST64   __SCAL8_PREFIX "U"
#define SCNUFAST8     __SCAF1_PREFIX "U"
#define SCNUFAST16    __SCAF2_PREFIX "U"
#define SCNUFAST32    __SCAF4_PREFIX "U"
#define SCNUFAST64    __SCAF8_PREFIX "U"
#define SCNUMAX       __SCA8_PREFIX "U"
#define SCNUPTR       __SCAP_PREFIX "U"
#define SCNUSIZ       __SCAP_PREFIX "U"
#define SCNUN(sizeof) __SCAN_PREFIX(sizeof) "U"
#endif /* __USE_KOS */



#ifdef __CC__
__SYSDECL_BEGIN

#ifndef ____imaxdiv_struct_defined
#define ____imaxdiv_struct_defined
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
#define ____imaxdiv_struct_defined
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
#define __std_imaxdiv_t_defined
__NAMESPACE_STD_BEGIN
typedef struct __imaxdiv_struct imaxdiv_t;
__NAMESPACE_STD_END
#endif /* !__std_imaxdiv_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __imaxdiv_t_defined
#define __imaxdiv_t_defined
__NAMESPACE_STD_USING(imaxdiv_t)
#endif /* !__imaxdiv_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

}

%[define_type_class(imaxdiv_t = "TS(__SIZEOF_IMAXDIV_STRUCT)")]

%[insert:std]


[[std, const, nothrow, crtbuiltin, decl_include("<hybrid/typecore.h>"), extern_inline]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_INT__),       alias("abs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("labs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("llabs")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    alias("_abs64")]]
/* -- local functions don't exist for `abs(3)' & friends because of extern_inline -- */
/*[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_INT__),       bind_local_function(abs)]]*/
/*[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      bind_local_function(labs)]]*/
/*[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), bind_local_function(llabs)]]*/
/* -- */
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ && __SIZEOF_INTMAX_T__ != 8)]]
[[section(".text.crt{|.dos}.math.utility")]]
$intmax_t imaxabs($intmax_t x) {
	return x < 0 ? -x : x;
}

[[std, attribute("__ATTR_CONST"), decl_include("<hybrid/typecore.h>"), decl_prefix(DEFINE_IMAXDIV_STRUCT)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_INT__),       alias("div")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("ldiv")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("lldiv")]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__)]]
[[section(".text.crt{|.dos}.math.utility")]]
$imaxdiv_t imaxdiv($intmax_t numer, $intmax_t denom) {
	imaxdiv_t result;
	result.@quot@ = numer / denom;
	result.@rem@  = numer % denom;
	return result;
}


[[std, leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("strtol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoll", "strtoq")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    alias("strto64", "_strtoi64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    alias("strto32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    bind_local_function(strto64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    bind_local_function(strto32)]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ &&
              __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$intmax_t strtoimax([[in]] char const *__restrict nptr,
                    [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_INTMAX_T__ <= 4@@
	return (intmax_t)strto32(nptr, endptr, base);
@@pp_else@@
	return (intmax_t)strto64(nptr, endptr, base);
@@pp_endif@@
}


[[std, leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("strtoul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoull", "strtouq")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    alias("strtou64", "_strtoui64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    alias("strtou32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    bind_local_function(strtou64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    bind_local_function(strtou32)]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ &&
              __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8)]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$uintmax_t strtoumax([[in]] char const *__restrict nptr,
                     [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base) {
@@pp_if __SIZEOF_INTMAX_T__ <= 4@@
	return (uintmax_t)strtou32(nptr, endptr, base);
@@pp_else@@
	return (uintmax_t)strtou64(nptr, endptr, base);
@@pp_endif@@
}


[[std, wchar, leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("wcstol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoll", "wcstoq")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    alias("wcsto64", "_wcstoi64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    alias("wcsto32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    bind_local_function(wcsto64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    bind_local_function(wcsto32)]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ &&
              __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8)]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
$intmax_t wcstoimax([[in]] $wchar_t const *__restrict nptr,
                    [[out_opt]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base)
	%{generate(str2wcs("strtoimax"))}

[[std, wchar, leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),      alias("wcstoul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoull", "wcstouq")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    alias("wcstou64", "_wcstoui64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    alias("wcstou32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),                    bind_local_function(wcstou64)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),                    bind_local_function(wcstou32)]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ &&
              __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8)]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
$uintmax_t wcstoumax([[in]] $wchar_t const *__restrict nptr,
                     [[out_opt]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base)
	%{generate(str2wcs("strtoumax"))}

%
%
%
%

%#ifdef __USE_KOS
/************************************************************************/
/* WARNING: The following functions aren't exported by-name from libc!  */
/************************************************************************/
[[nocrt, leaf, decl_include("<features.h>", "<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("strto64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("strto32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(strto64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(strto32_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
$intmax_t strtoimax_r([[in]] char const *__restrict nptr,
                      [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                      [[out_opt]] $errno_t *error) {
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

[[nocrt, leaf, decl_include("<features.h>", "<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("strtou64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("strtou32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(strtou64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(strtou32_r)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/limitcore.h>", "<asm/os/errno.h>")]]
$uintmax_t strtoumax_r([[in]] char const *__restrict nptr,
                       [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                       [[out_opt]] $errno_t *error) {
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

[[wchar, nocrt, leaf, decl_include("<features.h>", "<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("wcsto64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("wcsto32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(wcsto64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(wcsto32_r)]]
$intmax_t wcstoimax_r([[in]] $wchar_t const *__restrict nptr,
                      [[out_opt]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base,
                      [[out_opt]] $errno_t *error)
	%{generate(str2wcs("strtoimax_r"))}

[[wchar, nocrt, leaf, decl_include("<features.h>", "<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("wcstou64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("wcstou32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(wcstou64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(wcstou32_r)]]
$uintmax_t wcstoumax_r([[in]] $wchar_t const *__restrict nptr,
                       [[out_opt]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base,
                       [[out_opt]] $errno_t *error)
	%{generate(str2wcs("strtoumax_r"))}
/************************************************************************/
%#endif /* __USE_KOS */

%
%#ifdef __USE_XOPEN2K8

[[leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[dos_only_export_alias("_strtoimax_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("strtol_l", "_strtol_l", "__strtol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoll_l", "_strtoll_l", "__strtoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("strto64_l", "_strtoi64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("strto32_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(strto64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(strto32_l)]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ &&
              __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8)]]
[[section(".text.crt{|.dos}.unicode.locale.convert")]]
$intmax_t strtoimax_l([[in]] char const *__restrict nptr,
                      [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                      $locale_t locale) {
@@pp_if __SIZEOF_INTMAX_T__ <= 4@@
	return (intmax_t)strto32_l(nptr, endptr, base, locale);
@@pp_else@@
	return (intmax_t)strto64_l(nptr, endptr, base, locale);
@@pp_endif@@
}


[[leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[dos_only_export_alias("_strtoumax_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("strtoul_l", "_strtoul_l", "__strtoul_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("strtoull_l", "_strtoull_l", "__strtoull_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("strtou64_l", "_strtoui64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("strtou32_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(strtou64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(strtou32_l)]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ &&
              __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8)]]
[[section(".text.crt{|.dos}.unicode.locale.convert")]]
$uintmax_t strtoumax_l([[in]] char const *__restrict nptr,
                       [[out_opt]] char **endptr, __STDC_INT_AS_UINT_T base,
                       $locale_t locale) {
@@pp_if __SIZEOF_INTMAX_T__ <= 4@@
	return (uintmax_t)strtou32_l(nptr, endptr, base, locale);
@@pp_else@@
	return (uintmax_t)strtou64_l(nptr, endptr, base, locale);
@@pp_endif@@
}

[[wchar, leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[dos_export_alias("_wcstoimax_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("wcstol_l", "_wcstol_l", "__wcstol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoll_l", "_wcstoll_l", "__wcstoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("wcsto64_l", "_wcstoi64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("wcsto32_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(wcsto64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(wcsto32_l)]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ &&
              __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8)]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
$intmax_t wcstoimax_l([[in]] $wchar_t const *__restrict nptr,
                      [[out_opt]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base,
                      $locale_t locale)
	%{generate(str2wcs("strtoimax_l"))}

[[wchar, leaf, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[dos_export_alias("_wcstoumax_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), alias("wcstoul_l", "_wcstoul_l", "__wcstoul_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), alias("wcstoull_l", "_wcstoull_l", "__wcstoull_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), alias("wcstou64_l", "_wcstoui64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), alias("wcstou32_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), bind_local_function(wcstou64_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), bind_local_function(wcstou32_l)]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>")!defined(__KERNEL__) &&
              __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ &&
              __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8)]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
$uintmax_t wcstoumax_l([[in]] $wchar_t const *__restrict nptr,
                       [[out_opt]] $wchar_t **endptr, __STDC_INT_AS_UINT_T base,
                       $locale_t locale)
	%{generate(str2wcs("strtoumax_l"))}


%#endif /* __USE_XOPEN2K8 */


%
%
%
%#ifdef __USE_NETBSD

@@>> strtoi(3), strtou(3), strtoi_l(3), strtou_l(3)
@@Safely convert `nptr'  to an integer  which is then  returned.
@@If no integer  could be read,  set `*rstatus' (if  non-`NULL')
@@to `ECANCELED'.  If non-`NULL',  `*endptr'  is made  to  point
@@past the  read  integer,  and  if it  points  to  a  non-'\0'-
@@character,  `*rstatus'  (if non-`NULL')  is set  to `ENOTSUP'.
@@Also  make  sure that  the  returned integer  lies  within the
@@bounds of `[lo,hi]'  (inclusively). If it  does not, clamp  it
@@to those bounds and set `*rstatus' (if non-`NULL') to `ERANGE'
@@@param: lo, hi:  Lo/Hi-bounds for the to-be returned integer.
@@@param: rstatus: When non-`NULL', set to a conversion error (if any)
[[leaf, guard]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$intmax_t strtoi([[in]] char const *__restrict nptr,
                 [[out_opt]] char **__restrict endptr,
                 __STDC_INT_AS_UINT_T base,
                 $intmax_t lo, $intmax_t hi,
                 [[out_opt]] $errno_t *rstatus) {
	char *used_endptr;
	intmax_t result;
	result = strtoimax_r(nptr, &used_endptr, base, rstatus);
	if (endptr)
		*endptr = used_endptr;
	if (rstatus && *rstatus == 0) {
		if (*used_endptr != '\0') {
@@pp_ifdef ENOTSUP@@
			*rstatus = ENOTSUP;
@@pp_elif defined(EOPNOTSUPP)@@
			*rstatus = EOPNOTSUPP;
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

[[leaf, guard, doc_alias("strtoi")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$uintmax_t strtou([[in]] char const *__restrict nptr,
                  [[out_opt]] char **__restrict endptr,
                  __STDC_INT_AS_UINT_T base,
                  $uintmax_t lo, $uintmax_t hi,
                  [[out_opt]] $errno_t *rstatus) {
	char *used_endptr;
	uintmax_t result;
	result = strtoumax_r(nptr, &used_endptr, base, rstatus);
	if (endptr)
		*endptr = used_endptr;
	if (rstatus && *rstatus == 0) {
		if (*used_endptr != '\0') {
@@pp_ifdef ENOTSUP@@
			*rstatus = ENOTSUP;
@@pp_elif defined(EOPNOTSUPP)@@
			*rstatus = EOPNOTSUPP;
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

[[leaf, doc_alias("strtoi")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$intmax_t strtoi_l([[in]] char const *__restrict nptr,
                   [[out_opt]] char **__restrict endptr,
                   __STDC_INT_AS_UINT_T base,
                   $intmax_t lo, $intmax_t hi,
                   [[out_opt]] $errno_t *rstatus, $locale_t locale) {
	(void)locale;
	return strtoi(nptr, endptr, base, lo, hi, rstatus);
}

[[leaf, doc_alias("strtoi")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.unicode.static.convert")]]
$uintmax_t strtou_l([[in]] char const *__restrict nptr,
                    [[out_opt]] char **__restrict endptr,
                    __STDC_INT_AS_UINT_T base,
                    $uintmax_t lo, $uintmax_t hi,
                    [[out_opt]] $errno_t *rstatus, $locale_t locale) {
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
#define ____gwchar_t_defined
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
