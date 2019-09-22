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
#ifndef ____INTELLISENSE_STDINC_SYNTAX_H
#define ____INTELLISENSE_STDINC_SYNTAX_H 1

/*
 * Always-include, wrapper header to re-configure Visual Studio's
 * Intellisense into something as much conforming to what the GCC
 * compiler does, as possible.
 * >> This header is never included by any production code,
 *    only ever included through the nmake forced include option,
 *    and functions defined here are never implemented.
 *   (So there's no need to go looking for them...)
 */

#include "intellisense-common.h"


#ifndef __GNUC__

#ifdef _M_ARM
#   define __arm__              1
#elif defined(_WIN64)
#   define _LP64                1
#   define __FXSR__             1
#   define __LP64__             1
#   define __MMX__              1
#   define __SIZEOF_INT128__    16
#   define __int128             long long
#   define __SSE2_MATH__        1
#   define __SSE2__             1
#   define __SSE_MATH__         1
#   define __SSE__              1
#   define __amd64              1
#   define __amd64__            1
#   define __code_model_small__ 1
#   define __k8                 1
#   define __k8__               1
//# define __x86_64             1
#   define __x86_64__           1
#else
#   define i386              1
#   define __i386            1
#   define __i386__          1
#   define __i686            1
#   define __i686__          1
#   define __pentiumpro      1
#   define __pentiumpro__    1
#   define __code_model_32__ 1
#endif

#define __STDC__ 1
#ifdef __KOS__
/* Hosted KOS development mode. */
#   define __kos      1
#   define __kos__    1
#   define __unix     1
#   define __unix__   1
#   define __ELF__    1
#elif defined(_WIN32) || defined(WIN32) || \
      defined(_WIN64) || defined(WIN64)
/* Assume hosted CYGWIN development mode.
 * NOTE: Hosted MSVC mode doesn't need be handled here, as in
 *       that case, this header should not be included at all! */
#   define unix       1
#   define __unix     1
#   define __unix__   1
#   define __CYGWIN__ 1
#else
/* Hosted GLibC development mode. */
#   define unix       1
#   define __unix     1
#   define __unix__   1
#   define linux      1
#   define __linux    1
#   define __linux__  1
#endif

/* Get rid of MSVC's predefined macros */
#undef WIN32
#undef WIN64
#undef _WIN32
#undef _WIN64
#undef _M_IX86
#undef _M_IX86_FP
#undef _MSC_VER
#undef _MSC_BUILD
#undef _MSC_EXTENSIONS
#undef _MT
#undef __BOOL_DEFINED

#define ____INTELLISENSE_ENDIAN  1234

#define __DATE_DAY__   1
#define __DATE_WDAY__  0
#define __DATE_YDAY__  1
#define __DATE_MONTH__ 1
#define __DATE_YEAR__  2019

#define __TIME_HOUR__  13
#define __TIME_MIN__   37
#define __TIME_SEC__   42

#define __GNUC__            6
#define __GNUC_MINOR__      2
#define __GNUC_PATCH__      0
#define __GNUC_PATCHLEVEL__ 0
#define __GXX_EXPERIMENTAL_CXX0X__ 1

#define __INT8_TYPE__           signed char
#define __INT16_TYPE__          signed short
#define __INT32_TYPE__          signed int
#define __INT64_TYPE__          signed long long
#define __UINT8_TYPE__        unsigned char
#define __UINT16_TYPE__       unsigned short
#define __UINT32_TYPE__       unsigned int
#define __UINT64_TYPE__       unsigned long long
#define __INT_LEAST8_TYPE__     signed char
#define __INT_LEAST16_TYPE__    signed short
#define __INT_LEAST32_TYPE__    signed int
#define __INT_LEAST64_TYPE__    signed long long
#define __UINT_LEAST8_TYPE__  unsigned char
#define __UINT_LEAST16_TYPE__ unsigned short
#define __UINT_LEAST32_TYPE__ unsigned int
#define __UINT_LEAST64_TYPE__ unsigned long long
#define __INT_FAST8_TYPE__      signed char
#define __INT_FAST16_TYPE__     signed short
#define __INT_FAST32_TYPE__     signed int
#define __INT_FAST64_TYPE__     signed long long
#define __UINT_FAST8_TYPE__   unsigned char
#define __UINT_FAST16_TYPE__  unsigned short
#define __UINT_FAST32_TYPE__  unsigned int
#define __UINT_FAST64_TYPE__  unsigned long long
#define __INTMAX_TYPE__         signed long long
#define __UINTMAX_TYPE__      unsigned long long

#if defined(__x86_64__)
#   define __INTPTR_TYPE__    signed long long
#   define __UINTPTR_TYPE__   unsigned long long
#   define __PTRDIFF_TYPE__   signed long long
#   define __SIZE_TYPE__      unsigned long long
#   define __SIZEOF_POINTER__ 8
#else
#   define __INTPTR_TYPE__    signed int
#   define __UINTPTR_TYPE__   unsigned int
#   define __PTRDIFF_TYPE__   signed long
#   define __SIZE_TYPE__      unsigned long
#   define __SIZEOF_POINTER__ 4
#endif

#define __SIZEOF_SHORT__       2
#define __SIZEOF_INT__         4
#define __SIZEOF_LONG__        __SIZEOF_POINTER__
#define __SIZEOF_LONG_LONG__   8
#define __SIZEOF_SIZE_T__      __SIZEOF_POINTER__
#define __SIZEOF_PTRDIFF_T__   __SIZEOF_POINTER__
#define __SIZEOF_FLOAT__       4
#define __SIZEOF_DOUBLE__      8
#define __SIZEOF_WINT_T__      4

#ifndef __arm__
#define __SIZEOF_LONG_DOUBLE__ 12
#define __SIZEOF_FLOAT128__    16
#define __SIZEOF_FLOAT80__     12
#else
#define __SIZEOF_LONG_DOUBLE__ 8
#endif

#define ____INTELLISENSE_MIN_S1  (-127i8-1i8)
#define ____INTELLISENSE_MAX_S1    127i8
#define ____INTELLISENSE_MIN_U1    0ui8
#define ____INTELLISENSE_MAX_U1    0xffui8
#define ____INTELLISENSE_MIN_S2  (-32767i16-1i16)
#define ____INTELLISENSE_MAX_S2    32767i16
#define ____INTELLISENSE_MIN_U2    0ui16
#define ____INTELLISENSE_MAX_U2    0xffffui16
#define ____INTELLISENSE_MIN_S4  (-2147483647i32-1i32)
#define ____INTELLISENSE_MAX_S4    2147483647i32
#define ____INTELLISENSE_MIN_U4    0ui32
#define ____INTELLISENSE_MAX_U4    0xffffffffui32
#define ____INTELLISENSE_MIN_S8  (-9223372036854775807i64-1i64)
#define ____INTELLISENSE_MAX_S8    9223372036854775807i64
#define ____INTELLISENSE_MIN_U8    0ui64
#define ____INTELLISENSE_MAX_U8    0xffffffffffffffffui64

#define ____INTELLISENSE_MIN2_S(s) ____INTELLISENSE_MIN_S##s
#define ____INTELLISENSE_MAX2_S(s) ____INTELLISENSE_MAX_S##s
#define ____INTELLISENSE_MIN2_U(s) ____INTELLISENSE_MIN_U##s
#define ____INTELLISENSE_MAX2_U(s) ____INTELLISENSE_MAX_U##s
#define ____INTELLISENSE_MIN_S(s)  ____INTELLISENSE_MIN2_S(s)
#define ____INTELLISENSE_MAX_S(s)  ____INTELLISENSE_MAX2_S(s)
#define ____INTELLISENSE_MIN_U(s)  ____INTELLISENSE_MIN2_U(s)
#define ____INTELLISENSE_MAX_U(s)  ____INTELLISENSE_MAX2_U(s)

#define __CHAR_BIT__   8
#define __SCHAR_MAX__       ____INTELLISENSE_MAX_S1

#if 1
#   define __WCHAR_MIN__       L'\0'
#   define __WCHAR_MAX__       L'\xffff'
#elif defined(__WCHAR_UNSIGNED__)
#   define __WCHAR_MIN__       ____INTELLISENSE_MIN_U(__SIZEOF_WCHAR_T__)
#   define __WCHAR_MAX__       ____INTELLISENSE_MAX_U(__SIZEOF_WCHAR_T__)
#else
#   define __WCHAR_MIN__       ____INTELLISENSE_MIN_S(__SIZEOF_WCHAR_T__)
#   define __WCHAR_MAX__       ____INTELLISENSE_MAX_S(__SIZEOF_WCHAR_T__)
#endif
#   define __SHRT_MAX__        ____INTELLISENSE_MAX_S(__SIZEOF_SHORT__)
#   define __INT_MAX__         ____INTELLISENSE_MAX_S(__SIZEOF_INT__)
#   define __LONG_MAX__        ____INTELLISENSE_MAX_S(__SIZEOF_LONG__)
#   define __LONG_LONG_MAX__   ____INTELLISENSE_MAX_S(__SIZEOF_LONG_LONG__)
#   define __WINT_MIN__        ____INTELLISENSE_MIN_U(__SIZEOF_INT__)
#   define __WINT_MAX__        ____INTELLISENSE_MAX_U(__SIZEOF_INT__)
#   define __SIZE_MAX__        ____INTELLISENSE_MAX_U(__SIZEOF_SIZE_T__)
#   define __PTRDIFF_MAX__     ____INTELLISENSE_MAX_S(__SIZEOF_PTRDIFF_T__)
#   define __INTMAX_MAX__      ____INTELLISENSE_MAX_S(__SIZEOF_INTMAX_T__)
#   define __UINTMAX_MAX__     ____INTELLISENSE_MAX_U(__SIZEOF_INTMAX_T__)
#   define __SIG_ATOMIC_MIN__  ____INTELLISENSE_MIN_S(__SIZEOF_INT__)
#   define __SIG_ATOMIC_MAX__  ____INTELLISENSE_MAX_S(__SIZEOF_INT__)
#   define __SIG_ATOMIC_TYPE__ int

#define __INT8_MAX__     ____INTELLISENSE_MAX_S1
#define __INT16_MAX__    ____INTELLISENSE_MAX_S2
#define __INT32_MAX__    ____INTELLISENSE_MAX_S4
#define __INT64_MAX__    ____INTELLISENSE_MAX_S8
#define __UINT8_MAX__    ____INTELLISENSE_MAX_U1
#define __UINT16_MAX__   ____INTELLISENSE_MAX_U2
#define __UINT32_MAX__   ____INTELLISENSE_MAX_U4
#define __UINT64_MAX__   ____INTELLISENSE_MAX_U8

#define __INT_LEAST8_MAX__    ____INTELLISENSE_MAX_S1
#define __INT_LEAST16_MAX__   ____INTELLISENSE_MAX_S2
#define __INT_LEAST32_MAX__   ____INTELLISENSE_MAX_S4
#define __INT_LEAST64_MAX__   ____INTELLISENSE_MAX_S8
#define __UINT_LEAST8_MAX__   ____INTELLISENSE_MAX_U1
#define __UINT_LEAST16_MAX__  ____INTELLISENSE_MAX_U2
#define __UINT_LEAST32_MAX__  ____INTELLISENSE_MAX_U4
#define __UINT_LEAST64_MAX__  ____INTELLISENSE_MAX_U8
#define __INT_FAST8_MAX__     ____INTELLISENSE_MAX_S1
#define __INT_FAST16_MAX__    ____INTELLISENSE_MAX_S2
#define __INT_FAST32_MAX__    ____INTELLISENSE_MAX_S4
#define __INT_FAST64_MAX__    ____INTELLISENSE_MAX_S8
#define __UINT_FAST8_MAX__    ____INTELLISENSE_MAX_U1
#define __UINT_FAST16_MAX__   ____INTELLISENSE_MAX_U2
#define __UINT_FAST32_MAX__   ____INTELLISENSE_MAX_U4
#define __UINT_FAST64_MAX__   ____INTELLISENSE_MAX_U8

#define __INTPTR_MAX__  ____INTELLISENSE_MAX_S(__SIZEOF_POINTER__)
#define __UINTPTR_MAX__ ____INTELLISENSE_MAX_U(__SIZEOF_POINTER__)

#define __INT8_C(c)    c##i8
#define __INT16_C(c)   c##i16
#define __INT32_C(c)   c##i32
#define __INT64_C(c)   c##i64
#define __UINT8_C(c)   c##ui8
#define __UINT16_C(c)  c##ui16
#define __UINT32_C(c)  c##ui32
#define __UINT64_C(c)  c##ui64
#define __INTMAX_C(c)  c##i64
#define __UINTMAX_C(c) c##ui64

#define __CHAR16_TYPE__     ::__intern::____INTELLISENSE_char16_t
#define __CHAR32_TYPE__     ::__intern::____INTELLISENSE_char32_t
#define __WCHAR_TYPE__      wchar_t
#define __WINT_TYPE__       unsigned int
#define __SIZEOF_WCHAR_T__  2 /* Psht... */
#define __native_wchar_t_defined 1 /* Psht... */
#define __wchar_t_defined   1 /* Psht... */

#define __DBL_DECIMAL_DIG__        17
#define __DBL_DENORM_MIN__       ((double)4.94065645841246544177e-324L)
#define __DBL_DIG__                15
#define __DBL_EPSILON__          ((double)2.22044604925031308085e-16L)
#define __DBL_HAS_DENORM__         1
#define __DBL_HAS_INFINITY__       1
#define __DBL_HAS_QUIET_NAN__      1
#define __DBL_MANT_DIG__           53
#define __DBL_MAX_10_EXP__         308
#define __DBL_MAX_EXP__            1024
#define __DBL_MAX__              ((double)1.79769313486231570815e+308L)
#define __DBL_MIN_10_EXP__       (-307)
#define __DBL_MIN_EXP__          (-1021)
#define __DBL_MIN__              ((double)2.22507385850720138309e-308L)
#define __DEC128_EPSILON__         1E-33DL
#define __DEC128_MANT_DIG__        34
#define __DEC128_MAX_EXP__         6145
#define __DEC128_MAX__             9.999999999999999999999999999999999E6144DL
#define __DEC128_MIN_EXP__       (-6142)
#define __DEC128_MIN__             1E-6143DL
#define __DEC128_SUBNORMAL_MIN__   0.000000000000000000000000000000001E-6143DL
#define __DEC32_EPSILON__          1E-6DF
#define __DEC32_MANT_DIG__         7
#define __DEC32_MAX_EXP__          97
#define __DEC32_MAX__              9.999999E96DF
#define __DEC32_MIN_EXP__        (-94)
#define __DEC32_MIN__              1E-95DF
#define __DEC32_SUBNORMAL_MIN__    0.000001E-95DF
#define __DEC64_EPSILON__          1E-15DD
#define __DEC64_MANT_DIG__         16
#define __DEC64_MAX_EXP__          385
#define __DEC64_MAX__              9.999999999999999E384DD
#define __DEC64_MIN_EXP__        (-382)
#define __DEC64_MIN__              1E-383DD
#define __DEC64_SUBNORMAL_MIN__    0.000000000000001E-383DD
#define __DECIMAL_DIG__            21
#define __DEC_EVAL_METHOD__        2
#define __FINITE_MATH_ONLY__       0
#define __FLT_DECIMAL_DIG__        9
#define __FLT_DENORM_MIN__         1.40129846432481707092e-45F
#define __FLT_DIG__                6
#define __FLT_EPSILON__            1.19209289550781250000e-7F
#define __FLT_EVAL_METHOD__        2
#define __FLT_HAS_DENORM__         1
#define __FLT_HAS_INFINITY__       1
#define __FLT_HAS_QUIET_NAN__      1
#define __FLT_MANT_DIG__           24
#define __FLT_MAX_10_EXP__         38
#define __FLT_MAX_EXP__            128
#define __FLT_MAX__                3.40282346638528859812e+38F
#define __FLT_MIN_10_EXP__       (-37)
#define __FLT_MIN_EXP__          (-125)
#define __FLT_MIN__                1.17549435082228750797e-38F
#define __FLT_RADIX__              2
#define __LDBL_DENORM_MIN__        3.64519953188247460253e-4951L
#define __LDBL_DIG__               18
#define __LDBL_EPSILON__           1.08420217248550443401e-19L
#define __LDBL_HAS_DENORM__        1
#define __LDBL_HAS_INFINITY__      1
#define __LDBL_HAS_QUIET_NAN__     1
#define __LDBL_MANT_DIG__          64
#define __LDBL_MAX_10_EXP__        4932
#define __LDBL_MAX_EXP__           16384
#define __LDBL_MAX__               1.18973149535723176502e+4932L
#define __LDBL_MIN_10_EXP__      (-4931)
#define __LDBL_MIN_EXP__         (-16381)
#define __LDBL_MIN__               3.36210314311209350626e-4932L

#ifdef __arm__
#define __ACCUM_EPSILON__ 0x1P-15K
#define __ACCUM_FBIT__ 15
#define __ACCUM_IBIT__ 16
#define __ACCUM_MAX__ 0X7FFFFFFFP-15K
#define __ACCUM_MIN__ (-0X1P15K-0X1P15K)
#define __APCS_32__ 1
#define __ARMEL__ 1
#define __ARM_32BIT_STATE 1
#define __ARM_ARCH 4
#define __ARM_ARCH_4T__ 1
#define __ARM_ARCH_ISA_ARM 1
#define __ARM_ARCH_ISA_THUMB 1
#define __ARM_EABI__ 1
#define __ARM_PCS 1
#define __ARM_SIZEOF_MINIMAL_ENUM 1
#define __ARM_SIZEOF_WCHAR_T 4
#define __CHAR_UNSIGNED__ 1
#define __DA_FBIT__ 31
#define __DA_IBIT__ 32
#define __DQ_FBIT__ 63
#define __DQ_IBIT__ 0
#define __FRACT_EPSILON__ 0x1P-15R
#define __FRACT_FBIT__ 15
#define __FRACT_IBIT__ 0
#define __FRACT_MAX__ 0X7FFFP-15R
#define __FRACT_MIN__ (-0.5R-0.5R)
#define __GXX_TYPEINFO_EQUALITY_INLINE 0
#define __HA_FBIT__ 7
#define __HA_IBIT__ 8
#define __HQ_FBIT__ 15
#define __HQ_IBIT__ 0
#define __LACCUM_EPSILON__ 0x1P-31LK
#define __LACCUM_FBIT__ 31
#define __LACCUM_IBIT__ 32
#define __LACCUM_MAX__ 0X7FFFFFFFFFFFFFFFP-31LK
#define __LACCUM_MIN__ (-0X1P31LK-0X1P31LK)
#define __LFRACT_EPSILON__ 0x1P-31LR
#define __LFRACT_FBIT__ 31
#define __LFRACT_IBIT__ 0
#define __LFRACT_MAX__ 0X7FFFFFFFP-31LR
#define __LFRACT_MIN__ (-0.5LR-0.5LR)
#define __LLACCUM_EPSILON__ 0x1P-31LLK
#define __LLACCUM_FBIT__ 31
#define __LLACCUM_IBIT__ 32
#define __LLACCUM_MAX__ 0X7FFFFFFFFFFFFFFFP-31LLK
#define __LLACCUM_MIN__ (-0X1P31LLK-0X1P31LLK)
#define __LLFRACT_EPSILON__ 0x1P-63LLR
#define __LLFRACT_FBIT__ 63
#define __LLFRACT_IBIT__ 0
#define __LLFRACT_MAX__ 0X7FFFFFFFFFFFFFFFP-63LLR
#define __LLFRACT_MIN__ (-0.5LLR-0.5LLR)
#define __QQ_FBIT__ 7
#define __QQ_IBIT__ 0
#define __REGISTER_PREFIX__
#define __SACCUM_EPSILON__ 0x1P-7HK
#define __SACCUM_FBIT__ 7
#define __SACCUM_IBIT__ 8
#define __SACCUM_MAX__ 0X7FFFP-7HK
#define __SACCUM_MIN__ (-0X1P7HK-0X1P7HK)
#define __SA_FBIT__ 15
#define __SA_IBIT__ 16
#define __SCHAR_MAX__ 0x7f
#define __SFRACT_EPSILON__ 0x1P-7HR
#define __SFRACT_FBIT__ 7
#define __SFRACT_IBIT__ 0
#define __SFRACT_MAX__ 0X7FP-7HR
#define __SFRACT_MIN__ (-0.5HR-0.5HR)
#define __SOFTFP__ 1
#define __SQ_FBIT__ 31
#define __SQ_IBIT__ 0
#define __TA_FBIT__ 63
#define __TA_IBIT__ 64
#define __THUMB_INTERWORK__ 1
#define __TQ_FBIT__ 127
#define __TQ_IBIT__ 0
#define __UACCUM_EPSILON__ 0x1P-16UK
#define __UACCUM_FBIT__ 16
#define __UACCUM_IBIT__ 16
#define __UACCUM_MAX__ 0XFFFFFFFFP-16UK
#define __UACCUM_MIN__ 0.0UK
#define __UDA_FBIT__ 32
#define __UDA_IBIT__ 32
#define __UDQ_FBIT__ 64
#define __UDQ_IBIT__ 0
#define __UFRACT_EPSILON__ 0x1P-16UR
#define __UFRACT_FBIT__ 16
#define __UFRACT_IBIT__ 0
#define __UFRACT_MAX__ 0XFFFFP-16UR
#define __UFRACT_MIN__ 0.0UR
#define __UHA_FBIT__ 8
#define __UHA_IBIT__ 8
#define __UHQ_FBIT__ 16
#define __UHQ_IBIT__ 0
#define __ULACCUM_EPSILON__ 0x1P-32ULK
#define __ULACCUM_FBIT__ 32
#define __ULACCUM_IBIT__ 32
#define __ULACCUM_MAX__ 0XFFFFFFFFFFFFFFFFP-32ULK
#define __ULACCUM_MIN__ 0.0ULK
#define __ULFRACT_EPSILON__ 0x1P-32ULR
#define __ULFRACT_FBIT__ 32
#define __ULFRACT_IBIT__ 0
#define __ULFRACT_MAX__ 0XFFFFFFFFP-32ULR
#define __ULFRACT_MIN__ 0.0ULR
#define __ULLACCUM_EPSILON__ 0x1P-32ULLK
#define __ULLACCUM_FBIT__ 32
#define __ULLACCUM_IBIT__ 32
#define __ULLACCUM_MAX__ 0XFFFFFFFFFFFFFFFFP-32ULLK
#define __ULLACCUM_MIN__ 0.0ULLK
#define __ULLFRACT_EPSILON__ 0x1P-64ULLR
#define __ULLFRACT_FBIT__ 64
#define __ULLFRACT_IBIT__ 0
#define __ULLFRACT_MAX__ 0XFFFFFFFFFFFFFFFFP-64ULLR
#define __ULLFRACT_MIN__ 0.0ULLR
#define __UQQ_FBIT__ 8
#define __UQQ_IBIT__ 0
#define __USACCUM_EPSILON__ 0x1P-8UHK
#define __USACCUM_FBIT__ 8
#define __USACCUM_IBIT__ 8
#define __USACCUM_MAX__ 0XFFFFP-8UHK
#define __USACCUM_MIN__ 0.0UHK
#define __USA_FBIT__ 16
#define __USA_IBIT__ 16
#define __USES_INITFINI__ 1
#define __USFRACT_EPSILON__ 0x1P-8UHR
#define __USFRACT_FBIT__ 8
#define __USFRACT_IBIT__ 0
#define __USFRACT_MAX__ 0XFFP-8UHR
#define __USFRACT_MIN__ 0.0UHR
#define __USQ_FBIT__ 32
#define __USQ_IBIT__ 0
#define __UTA_FBIT__ 64
#define __UTA_IBIT__ 64
#define __UTQ_FBIT__ 128
#define __UTQ_IBIT__ 0
#endif

#define __BYTE_ORDER__             __ORDER_LITTLE_ENDIAN__
#define __FLOAT_WORD_ORDER__       __ORDER_LITTLE_ENDIAN__
#define __ORDER_BIG_ENDIAN__       4321
#define __ORDER_LITTLE_ENDIAN__    1234
#define __ORDER_PDP_ENDIAN__       3412

#ifdef __arm__
#define __BIGGEST_ALIGNMENT__      8
#else
#define __BIGGEST_ALIGNMENT__      16
#endif

#define __GCC_ASM_FLAG_OUTPUTS__           1
#define __GCC_HAVE_DWARF2_CFI_ASM          1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 1
#define __GCC_IEC_559                      2
#define __GCC_IEC_559_COMPLEX              2
#define __GNUC_STDC_INLINE__               1
#define __GXX_ABI_VERSION                  1010
#define __NO_INLINE__                      1
#define __PRAGMA_REDEFINE_EXTNAME          1
#define __REGISTER_PREFIX__
//#define __SEG_FS 1
//#define __SEG_GS 1
#define __STDC_HOSTED__                    1
#define __STDC_UTF_16__                    1
#define __STDC_UTF_32__                    1
#define __STDC_VERSION__                   199901L
#define __USER_LABEL_PREFIX__
#define __VERSION__                       "6.2.0"

enum {
	__asm__
};
//#define asm(...)           /* Nothing (Used for register variables) */
#define asm                __asm__
#define __asm              __asm__
#define __asm__(...)       ;enum{}
#define goto(...)          /* Nothing */
#define __attribute        __attribute__
#define __extension__      /* Nothing */
#define __inline__         inline
#define __const            const
//#define __const__        const
#define volatile(...)      /* Nothing */
#define __volatile         volatile
#define __volatile__       volatile
#define __signed           signed
#define __signed__         signed
#define __unsigned         unsigned
#define __unsigned__       unsigned
#define __restrict__       __restrict
#define __attribute__(...) ____INTELLISENSE_ATTR __VA_ARGS__
#define _Atomic            __declspec(thread)
#define __alignof__        __alignof
typedef bool _Bool;


// Visual-studio specific VA_NARGS implementation
// NOTE: Capable of detecting 0 arguments!
// HINT: This implementation works for intellisense, vc and vc++
#define ____INTELLISENSE_PP_FORCE_EXPAND(...) __VA_ARGS__
#define ____INTELLISENSE_PP_PRIVATE_VA_NARGS_I(x, _1, _2, _3, _4, _5, _6, _7, N, ...) N
#define ____INTELLISENSE_PP_PRIVATE_VA_NARGS_X(...) (~, __VA_ARGS__, 7, 6, 5, 4, 3, 2, 1, 0)
#define ____INTELLISENSE_PP_VA_NARGS(...) ____INTELLISENSE_PP_FORCE_EXPAND(____INTELLISENSE_PP_PRIVATE_VA_NARGS_I ____INTELLISENSE_PP_PRIVATE_VA_NARGS_X(__VA_ARGS__))

#define ____INTELLISENSE_ATTR_1(a) ____INTELLISENSE_attribute_##a
#define ____INTELLISENSE_ATTR_2(a, b) ____INTELLISENSE_attribute_##a ____INTELLISENSE_attribute_##b
#define ____INTELLISENSE_ATTR_3(a, b, c) ____INTELLISENSE_attribute_##a ____INTELLISENSE_attribute_##b ____INTELLISENSE_attribute_##c
#define ____INTELLISENSE_ATTR_4(a, b, c, d) ____INTELLISENSE_attribute_##a ____INTELLISENSE_attribute_##b ____INTELLISENSE_attribute_##c ____INTELLISENSE_attribute_##d
#define ____INTELLISENSE_ATTR_5(a, b, c, d, e) ____INTELLISENSE_attribute_##a ____INTELLISENSE_attribute_##b ____INTELLISENSE_attribute_##c ____INTELLISENSE_attribute_##d ____INTELLISENSE_attribute_##e
#define ____INTELLISENSE_ATTR_6(a, b, c, d, e, f) ____INTELLISENSE_attribute_##a ____INTELLISENSE_attribute_##b ____INTELLISENSE_attribute_##c ____INTELLISENSE_attribute_##d ____INTELLISENSE_attribute_##e ____INTELLISENSE_attribute_##f
#define ____INTELLISENSE_ATTR_7(a, b, c, d, e, f, g) ____INTELLISENSE_attribute_##a ____INTELLISENSE_attribute_##b ____INTELLISENSE_attribute_##c ____INTELLISENSE_attribute_##d ____INTELLISENSE_attribute_##e ____INTELLISENSE_attribute_##f ____INTELLISENSE_attribute_##g
#define ____INTELLISENSE_ATTR_N2(n, p) ____INTELLISENSE_ATTR_##n p
#define ____INTELLISENSE_ATTR_N(n, ...) ____INTELLISENSE_ATTR_N2(n, (__VA_ARGS__))
#define ____INTELLISENSE_ATTR(...) ____INTELLISENSE_ATTR_N(____INTELLISENSE_PP_VA_NARGS(__VA_ARGS__), __VA_ARGS__)


#define __thread    __declspec(thread)
#define ____INTELLISENSE_ATTR_FUNC        __declspec(nothrow)
#define ____INTELLISENSE_ATTR_FUNCDECL    /* ??? */
#define ____INTELLISENSE_ATTR_FUNC_STR(s) __declspec(nothrow,deprecated(s))
#define ____INTELLISENSE_ATTR_VAR         __declspec(allocate("~"))
#define ____INTELLISENSE_ATTR_FUNCORVAR   /* ??? */
#define ____INTELLISENSE_ATTR_TYPE        __declspec(align(4))

/* NOTE: These attribute are only meant to indicate invalid use, not to actually work correctly... */
#define ____INTELLISENSE_attribute_alias(target)              ____INTELLISENSE_ATTR_FUNCORVAR
#define ____INTELLISENSE_attribute___alias__(target)          ____INTELLISENSE_ATTR_FUNCORVAR
#ifdef __CYGWIN__
#define ____INTELLISENSE_attribute_dllimport                  __declspec(dllimport)
#define ____INTELLISENSE_attribute___dllimport__              __declspec(dllimport)
#define ____INTELLISENSE_attribute_dllexport                  __declspec(dllexport)
#define ____INTELLISENSE_attribute___dllexport__              __declspec(dllexport)
#endif /* __CYGWIN__ */
#define ____INTELLISENSE_attribute_aligned(x)                 __declspec(align(x))
#define ____INTELLISENSE_attribute___aligned__(x)             __declspec(align(x))
#define ____INTELLISENSE_attribute_alloc_align(...)           __declspec(restrict)
#define ____INTELLISENSE_attribute___alloc_align__(...)       __declspec(restrict)
#define ____INTELLISENSE_attribute_alloc_size(...)            __declspec(restrict)
#define ____INTELLISENSE_attribute___alloc_size__(...)        __declspec(restrict)
#define ____INTELLISENSE_attribute_always_inline              ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___always_inline__          ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_assume_aligned(...)        __declspec(restrict)
#define ____INTELLISENSE_attribute___assume_aligned__(...)    __declspec(restrict)
#define ____INTELLISENSE_attribute_cold                       ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___cold__                   ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_const                      ____INTELLISENSE_ATTR_FUNCDECL
#define ____INTELLISENSE_attribute___const__                  ____INTELLISENSE_ATTR_FUNCDECL
#define ____INTELLISENSE_attribute_constructor                ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___constructor__            ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_deprecated(reason)         __declspec(deprecated(reason))
#define ____INTELLISENSE_attribute___deprecated__(reason)     __declspec(deprecated(reason))
#define ____INTELLISENSE_attribute_destructor                 ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___destructor__             ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_error                      ____INTELLISENSE_ATTR_FUNC_STR
#define ____INTELLISENSE_attribute___error__                  ____INTELLISENSE_ATTR_FUNC_STR
#define ____INTELLISENSE_attribute_externally_visible         ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___externally_visible__     ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_format(name,fmt_idx,varargs_idx) ____INTELLISENSE_ATTR_FORMAT_##name
#define ____INTELLISENSE_attribute___format__(name,fmt_idx,varargs_idx) ____INTELLISENSE_ATTR_FORMAT_##name
#define ____INTELLISENSE_attribute_format_arg(argi)           ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___format_arg__(argi)       ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_hot                        ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___hot__                    ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_leaf                       ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___leaf__                   ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_malloc                     __declspec(restrict)
#define ____INTELLISENSE_attribute___malloc__                 __declspec(restrict)
#define ____INTELLISENSE_attribute_noclone                    __declspec(noinline)
#define ____INTELLISENSE_attribute___noclone__                __declspec(noinline)
#define ____INTELLISENSE_attribute_noinline                   __declspec(noinline)
#define ____INTELLISENSE_attribute___noinline__               __declspec(noinline)
#define ____INTELLISENSE_attribute_nonnull(...)               /*____INTELLISENSE_ATTR_FUNC*/
#define ____INTELLISENSE_attribute___nonnull__(...)           /*____INTELLISENSE_ATTR_FUNC*/
#define ____INTELLISENSE_attribute_noreturn                   __declspec(noreturn)
#define ____INTELLISENSE_attribute___noreturn__               __declspec(noreturn)
#define ____INTELLISENSE_attribute_optimize(opt)              ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___optimize__(opt)          ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_nothrow                    __declspec(nothrow)
#define ____INTELLISENSE_attribute___nothrow__                __declspec(nothrow)
#define ____INTELLISENSE_attribute_packed                     /* Nothing */
#define ____INTELLISENSE_attribute___packed__                 /* Nothing */
#define ____INTELLISENSE_attribute_pure                       __declspec(noalias)
#define ____INTELLISENSE_attribute___pure__                   __declspec(noalias)
#define ____INTELLISENSE_attribute_regparm(n)                 ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___regparm__(n)             ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_returns_nonnull            ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___returns_nonnull__        ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_returns_twice              ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___returns_twice__          ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_section(name)              ____INTELLISENSE_ATTR_FUNCORVAR
#define ____INTELLISENSE_attribute___section__(name)          ____INTELLISENSE_ATTR_FUNCORVAR
#define ____INTELLISENSE_attribute_sentinel                   ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___sentinel__               ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_transaction_pure           ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute___transaction_pure__       ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_attribute_unused                     /* Nothing */
#define ____INTELLISENSE_attribute___unused__                 /* Nothing */
#define ____INTELLISENSE_attribute_used                       /* Nothing */
#define ____INTELLISENSE_attribute___used__                   /* Nothing */
#define ____INTELLISENSE_attribute_visibility(v)              ____INTELLISENSE_ATTR_FUNCORVAR
#define ____INTELLISENSE_attribute___visibility__(v)          ____INTELLISENSE_ATTR_FUNCORVAR
#define ____INTELLISENSE_attribute_warn_unused_result         ____INTELLISENSE_ATTR_FUNCDECL
#define ____INTELLISENSE_attribute___warn_unused_result__     ____INTELLISENSE_ATTR_FUNCDECL
#define ____INTELLISENSE_attribute_warning                    ____INTELLISENSE_ATTR_FUNC_STR
#define ____INTELLISENSE_attribute___warning__                ____INTELLISENSE_ATTR_FUNC_STR
#define ____INTELLISENSE_attribute_weak                       ____INTELLISENSE_ATTR_FUNCORVAR
#define ____INTELLISENSE_attribute___weak__                   ____INTELLISENSE_ATTR_FUNCORVAR
#define ____INTELLISENSE_ATTR_FORMAT_asm_fprintf              ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT___asm_fprintf__          ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT_gcc_cdiag                ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT___gcc_cdiag__            ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT_gcc_cxxdiag              ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT___gcc_cxxdiag__          ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT_gcc_diag                 ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT___gcc_diag__             ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT_printf                   ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT___printf__               ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT_scanf                    ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT___scanf__                ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT_strfmon                  ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT___strfmon__              ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT_strftime                 ____INTELLISENSE_ATTR_FUNC
#define ____INTELLISENSE_ATTR_FORMAT___strftime__             ____INTELLISENSE_ATTR_FUNC

#ifdef __x86_64__
#define ____INTELLISENSE_attribute_ms_abi                     __cdecl
#define ____INTELLISENSE_attribute___ms_abi__                 __cdecl
#define ____INTELLISENSE_attribute_sysv_abi                   __cdecl
#define ____INTELLISENSE_attribute___sysv_abi__               __cdecl
#else /* __x86_64__ */
#define ____INTELLISENSE_attribute_cdecl                      __cdecl
#define ____INTELLISENSE_attribute___cdecl__                  __cdecl
#define ____INTELLISENSE_attribute_fastcall                   __fastcall
#define ____INTELLISENSE_attribute___fastcall__               __fastcall
#define ____INTELLISENSE_attribute_stdcall                    __stdcall
#define ____INTELLISENSE_attribute___stdcall__                __stdcall
#endif /* !__x86_64__ */


#if 1
enum { /* Highlight attributes in a different color */
	__alias__,              /* __attribute__((alias(target))); */
	__aligned__,            /* __attribute__((aligned(x))); */
	__alloc_align__,        /* __attribute__((alloc_align(...))); */
	__alloc_size__,         /* __attribute__((alloc_size(...))); */
	__always_inline__,      /* __attribute__((always_inline)); */
	__assume_aligned__,     /* __attribute__((assume_aligned(...))); */
	__cold__,               /* __attribute__((cold)); */
	__const__,              /* __attribute__((const)); */
	__constructor__,        /* __attribute__((constructor)); */
	__deprecated__,         /* __attribute__((deprecated(reason))); */
	__destructor__,         /* __attribute__((destructor)); */
	__error__,              /* __attribute__((error)); */
	__externally_visible__, /* __attribute__((externally_visible)); */
	__format__,             /* __attribute__((format(...,1,2))); */
	__format_arg__,         /* __attribute__((format_arg(2))); */
	__hot__,                /* __attribute__((hot)); */
	__leaf__,               /* __attribute__((leaf)); */
	__malloc__,             /* __attribute__((malloc)); */
	__noclone__,            /* __attribute__((noclone)); */
	__noinline__,           /* __attribute__((noinline)); */
	__nonnull__,            /* __attribute__((nonnull(...))); */
	__noreturn__,           /* __attribute__((noreturn)); */
	__nothrow__,            /* __attribute__((nothrow)); */
	__optimize__,           /* __attribute__((optimize(...))); */
	__packed__,             /* __attribute__((packed)); */
	__pure__,               /* __attribute__((pure)); */
	__regparm__,            /* __attribute__((regparm(n))); */
	__returns_nonnull__,    /* __attribute__((returns_nonnull)); */
	__returns_twice__,      /* __attribute__((returns_twice)); */
	__section__,            /* __attribute__((section(name))); */
	__sentinel__,           /* __attribute__((sentinel)); */
	__transaction_pure__,   /* __attribute__((transaction_pure)); */
	__unused__,             /* __attribute__((unused)); */
	__used__,               /* __attribute__((used)); */
	__visibility__,         /* __attribute__((visibility(v))); */
	__warn_unused_result__, /* __attribute__((warn_unused_result)); */
	__warning__,            /* __attribute__((warning)); */
	__weak__,               /* __attribute__((weak)); */
#ifdef __x86_64__
	__ms_abi__,             /* __attribute__((ms_abi)); */
	__sysv_abi__,           /* __attribute__((sysv_abi)); */
#else /* __x86_64__ */
	__cdecl__,              /* __attribute__((cdecl)); */
	__fastcall__,           /* __attribute__((fastcall)); */
	__stdcall__,            /* __attribute__((stdcall)); */
#endif /* !__x86_64__ */
#ifdef __CYGWIN__
	__dllimport__,          /* __attribute__((dllimport)); */
	__dllexport__,          /* __attribute__((dllexport)); */
#endif /* __CYGWIN__ */
	__printf__,             /* __attribute__((format(printf,1,2))); */
	__scanf__,              /* __attribute__((format(scanf,1,2))); */
	__strftime__,           /* __attribute__((format(strftime,1,1))); */
	__strfmon__,            /* __attribute__((format(strfmon,1,2))); */
	__asm_fprintf__,        /* __attribute__((format(asm_fprintf,1,2))); */
	__gcc_diag__,           /* __attribute__((format(gcc_diag,1,2))); */
	__gcc_cdiag__,          /* __attribute__((format(gcc_cdiag,1,2))); */
	__gcc_cxxdiag__,        /* __attribute__((format(gcc_cxxdiag,1,2))); */
};
#endif

#define ____INTELLISENSE_PRIVATE_ARG_PLACEHOLDER_     ,
#define ____INTELLISENSE_PRIVATE_ARG_PLACEHOLDER_1    ,
#define ____INTELLISENSE_PRIVATE_ARG_PLACEHOLDER_true ,
#define ____INTELLISENSE_PRIVATE_ARG_PLACEHOLDER_yes  ,
#define ____INTELLISENSE_PRIVATE_ARG_PLACEHOLDER_ok   ,
#define ____INTELLISENSE_PRIVATE_TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define ____INTELLISENSE_PRIVATE_TAKE_SECOND_ARG(x) ____INTELLISENSE_PRIVATE_TAKE_SECOND_ARG_IMPL x
#define ____INTELLISENSE_PRIVATE_IS_DEFINED2(x) ____INTELLISENSE_PRIVATE_TAKE_SECOND_ARG((x 1, 0))
#define ____INTELLISENSE_PRIVATE_IS_DEFINED(x) ____INTELLISENSE_PRIVATE_IS_DEFINED2(____INTELLISENSE_PRIVATE_ARG_PLACEHOLDER_##x)
#define ____INTELLISENSE_IS_DEFINED(x) ____INTELLISENSE_PRIVATE_IS_DEFINED(x)


#define ____INTELLISENSE_HASATTR_alias                  1
#define ____INTELLISENSE_HASATTR___alias__              1
#define ____INTELLISENSE_HASATTR_aligned                1
#define ____INTELLISENSE_HASATTR___aligned__            1
#define ____INTELLISENSE_HASATTR_alloc_align            1
#define ____INTELLISENSE_HASATTR___alloc_align__        1
#define ____INTELLISENSE_HASATTR_alloc_size             1
#define ____INTELLISENSE_HASATTR___alloc_size__         1
#define ____INTELLISENSE_HASATTR_always_inline          1
#define ____INTELLISENSE_HASATTR___always_inline__      1
#define ____INTELLISENSE_HASATTR_assume_aligned         1
#define ____INTELLISENSE_HASATTR___assume_aligned__     1
#define ____INTELLISENSE_HASATTR_cold                   1
#define ____INTELLISENSE_HASATTR___cold__               1
#define ____INTELLISENSE_HASATTR_const                  1
#define ____INTELLISENSE_HASATTR___const__              1
#define ____INTELLISENSE_HASATTR_constructor            1
#define ____INTELLISENSE_HASATTR___constructor__        1
#define ____INTELLISENSE_HASATTR_deprecated             1
#define ____INTELLISENSE_HASATTR___deprecated__         1
#define ____INTELLISENSE_HASATTR_destructor             1
#define ____INTELLISENSE_HASATTR___destructor__         1
#define ____INTELLISENSE_HASATTR_error                  1
#define ____INTELLISENSE_HASATTR___error__              1
#define ____INTELLISENSE_HASATTR_externally_visible     1
#define ____INTELLISENSE_HASATTR___externally_visible__ 1
#define ____INTELLISENSE_HASATTR_format                 1
#define ____INTELLISENSE_HASATTR___format__             1
#define ____INTELLISENSE_HASATTR_format_arg             1
#define ____INTELLISENSE_HASATTR___format_arg__         1
#define ____INTELLISENSE_HASATTR_hot                    1
#define ____INTELLISENSE_HASATTR___hot__                1
#define ____INTELLISENSE_HASATTR_leaf                   1
#define ____INTELLISENSE_HASATTR___leaf__               1
#define ____INTELLISENSE_HASATTR_malloc                 1
#define ____INTELLISENSE_HASATTR___malloc__             1
#define ____INTELLISENSE_HASATTR_noclone                1
#define ____INTELLISENSE_HASATTR___noclone__            1
#define ____INTELLISENSE_HASATTR_noinline               1
#define ____INTELLISENSE_HASATTR___noinline__           1
#define ____INTELLISENSE_HASATTR_nonnull                1
#define ____INTELLISENSE_HASATTR___nonnull__            1
#define ____INTELLISENSE_HASATTR_noreturn               1
#define ____INTELLISENSE_HASATTR___noreturn__           1
#define ____INTELLISENSE_HASATTR_nothrow                1
#define ____INTELLISENSE_HASATTR___nothrow__            1
#define ____INTELLISENSE_HASATTR_optimize               1
#define ____INTELLISENSE_HASATTR___optimize__           1
#define ____INTELLISENSE_HASATTR_packed                 1
#define ____INTELLISENSE_HASATTR___packed__             1
#define ____INTELLISENSE_HASATTR_pure                   1
#define ____INTELLISENSE_HASATTR___pure__               1
#define ____INTELLISENSE_HASATTR_regparm                1
#define ____INTELLISENSE_HASATTR___regparm__            1
#define ____INTELLISENSE_HASATTR_returns_nonnull        1
#define ____INTELLISENSE_HASATTR___returns_nonnull__    1
#define ____INTELLISENSE_HASATTR_returns_twice          1
#define ____INTELLISENSE_HASATTR___returns_twice__      1
#define ____INTELLISENSE_HASATTR_section                1
#define ____INTELLISENSE_HASATTR___section__            1
#define ____INTELLISENSE_HASATTR_sentinel               1
#define ____INTELLISENSE_HASATTR___sentinel__           1
#define ____INTELLISENSE_HASATTR_transaction_pure       1
#define ____INTELLISENSE_HASATTR___transaction_pure__   1
#define ____INTELLISENSE_HASATTR_unused                 1
#define ____INTELLISENSE_HASATTR___unused__             1
#define ____INTELLISENSE_HASATTR_used                   1
#define ____INTELLISENSE_HASATTR___used__               1
#define ____INTELLISENSE_HASATTR_visibility             1
#define ____INTELLISENSE_HASATTR___visibility__         1
#define ____INTELLISENSE_HASATTR_warn_unused_result     1
#define ____INTELLISENSE_HASATTR___warn_unused_result__ 1
#define ____INTELLISENSE_HASATTR_warning                1
#define ____INTELLISENSE_HASATTR___warning__            1
#define ____INTELLISENSE_HASATTR_weak                   1
#define ____INTELLISENSE_HASATTR___weak__               1
#ifdef __x86_64__
#define ____INTELLISENSE_HASATTR_ms_abi                 1
#define ____INTELLISENSE_HASATTR___ms_abi__             1
#define ____INTELLISENSE_HASATTR_sysv_abi               1
#define ____INTELLISENSE_HASATTR___sysv_abi__           1
#else /* __x86_64__ */
#define ____INTELLISENSE_HASATTR_cdecl                  1
#define ____INTELLISENSE_HASATTR___cdecl__              1
#define ____INTELLISENSE_HASATTR_fastcall               1
#define ____INTELLISENSE_HASATTR___fastcall__           1
#define ____INTELLISENSE_HASATTR_stdcall                1
#define ____INTELLISENSE_HASATTR___stdcall__            1
#endif /* !__x86_64__ */
#ifdef __CYGWIN__
#define ____INTELLISENSE_HASATTR___dllimport__          1
#define ____INTELLISENSE_HASATTR___dllexport__          1
#endif /* __CYGWIN__ */
#define __has_attribute(x) ____INTELLISENSE_IS_DEFINED(____INTELLISENSE_HASATTR_##x)


/* Emulate: __typeof__() / __auto_type */
namespace __intern {
template<class __T> struct ____INTELLISENSE_remlval { typedef __T __type; };
template<class __T> struct ____INTELLISENSE_remlval<__T &> { typedef __T __type; };
struct ____INTELLISENSE_void_helper { };
template<class __T> __T operator , (__T &&,____INTELLISENSE_void_helper);
template<class __T> __T const operator , (__T const &&,____INTELLISENSE_void_helper);
template<class __T, __SIZE_TYPE__ N> __T(&operator , (__T(&&)[N],____INTELLISENSE_void_helper))[N];
template<class __T, __SIZE_TYPE__ N> __T const (&operator , (__T const (&&)[N],____INTELLISENSE_void_helper))[N];
void ____INTELLISENSE_typeof_helper(____INTELLISENSE_void_helper &&);
template<class __T> typename ____INTELLISENSE_remlval<__T>::__type ____INTELLISENSE_typeof_helper(__T&&);
template<class __T> typename ____INTELLISENSE_remlval<__T>::__type const ____INTELLISENSE_typeof_helper(__T const &&);
template<class __T, __SIZE_TYPE__ N> typename ____INTELLISENSE_remlval<__T[N]>::__type &____INTELLISENSE_typeof_helper(__T(&)[N]);
template<class __T, __SIZE_TYPE__ N> typename ____INTELLISENSE_remlval<__T[N]>::__type const &____INTELLISENSE_typeof_helper(__T const (&)[N]);
template<class __T, class ...Args> __T(__attribute__((__cdecl__)) &&____INTELLISENSE_typeof_helper(__T(__attribute__((__cdecl__)) &)(Args...)))(Args...);
template<class __T, class ...Args> __T(__attribute__((__cdecl__)) &&____INTELLISENSE_typeof_helper(__T(__attribute__((__cdecl__)) &)(Args...,...)))(Args...,...);
template<class __T, class ...Args> __T(__attribute__((__fastcall__)) &&____INTELLISENSE_typeof_helper(__T(__attribute__((__fastcall__)) &)(Args...)))(Args...);
template<class __T, class ...Args> __T(__attribute__((__fastcall__)) &&____INTELLISENSE_typeof_helper(__T(__attribute__((__fastcall__)) &)(Args...,...)))(Args...,...);
template<class __T, class ...Args> __T(__attribute__((__stdcall__)) &&____INTELLISENSE_typeof_helper(__T(__attribute__((__stdcall__)) &)(Args...)))(Args...);
template<class __T, class ...Args> __T(__attribute__((__stdcall__)) &&____INTELLISENSE_typeof_helper(__T(__attribute__((__stdcall__)) &)(Args...,...)))(Args...,...);
#define typeof(...)     decltype(::__intern::____INTELLISENSE_typeof_helper(((__VA_ARGS__),::__intern::____INTELLISENSE_void_helper())))
#define __typeof(...)   decltype(::__intern::____INTELLISENSE_typeof_helper(((__VA_ARGS__),::__intern::____INTELLISENSE_void_helper())))
#define __typeof__(...) decltype(::__intern::____INTELLISENSE_typeof_helper(((__VA_ARGS__),::__intern::____INTELLISENSE_void_helper())))
#define __auto_type     auto
}


/* Emulate: __builtin_types_compatible_p() */
namespace __intern {
template<class __T> struct ____INTELLISENSE_remcv { typedef __T __type; };
template<class __T> struct ____INTELLISENSE_remcv<__T const> { typedef __T __type; };
template<class __T> struct ____INTELLISENSE_remcv<__T volatile> { typedef __T __type; };
template<class __T> struct ____INTELLISENSE_remcv<__T const volatile> { typedef __T __type; };
template<class T1, class T2> struct ____INTELLISENSE_sametype_impl { enum { __val = false }; };
template<class T1> struct ____INTELLISENSE_sametype_impl<T1,T1> { enum { __val = true }; };
template<class T1, class T2> struct ____INTELLISENSE_sametype:
	____INTELLISENSE_sametype_impl<typename ____INTELLISENSE_remcv<T1>::__type,
	typename ____INTELLISENSE_remcv<T2>::__type> { };
#define __builtin_types_compatible_p(...) (::__intern::____INTELLISENSE_sametype< __VA_ARGS__ >::__val)
}


/* Emulate: __builtin_classify_type() */
namespace __intern {
template<class __T> struct ____INTELLISENSE_classify { enum { __val = __is_enum(__T) ? 3 : __is_class(__T) ? 12 : __is_union(__T) ? 13 : -1 }; };
template<> struct ____INTELLISENSE_classify<void> { enum { __val = 0 }; };
template<> struct ____INTELLISENSE_classify<signed char> { enum { __val = 1 }; };
template<> struct ____INTELLISENSE_classify<unsigned char> { enum { __val = 1 }; };
template<> struct ____INTELLISENSE_classify<short> { enum { __val = 1 }; };
template<> struct ____INTELLISENSE_classify<unsigned short> { enum { __val = 1 }; };
template<> struct ____INTELLISENSE_classify<int> { enum { __val = 1 }; };
template<> struct ____INTELLISENSE_classify<unsigned int> { enum { __val = 1 }; };
template<> struct ____INTELLISENSE_classify<long> { enum { __val = 1 }; };
template<> struct ____INTELLISENSE_classify<unsigned long> { enum { __val = 1 }; };
template<> struct ____INTELLISENSE_classify<long long> { enum { __val = 1 }; };
template<> struct ____INTELLISENSE_classify<unsigned long long> { enum { __val = 1 }; };
template<> struct ____INTELLISENSE_classify<char> { enum { __val = 2 }; };
template<> struct ____INTELLISENSE_classify<bool> { enum { __val = 4 }; };
template<> struct ____INTELLISENSE_classify<float> { enum { __val = 8 }; };
template<> struct ____INTELLISENSE_classify<double> { enum { __val = 8 }; };
template<> struct ____INTELLISENSE_classify<long double> { enum { __val = 8 }; };
template<__SIZE_TYPE__ s> struct ____INTELLISENSE_classify<char[s]> { enum { __val = 15 }; };
template<class __T, __SIZE_TYPE__ s> struct ____INTELLISENSE_classify<__T[s]> { enum { __val = 14 }; };
template<class __T, __SIZE_TYPE__ s> struct ____INTELLISENSE_classify<__T[s]> { enum { __val = 14 }; };
template<class __T> struct ____INTELLISENSE_classify<__T *> { enum { __val = 5 }; };
template<class __T> struct ____INTELLISENSE_classify<__T &> { enum { __val = 6 }; };
//template<class __T> struct ____INTELLISENSE_classify<__T::*> { enum { __val = 7 }; };
template<class __T, class ...Args> struct ____INTELLISENSE_classify<__T(Args...)> { enum { __val = 10 }; };
template<class __T, class ...Args> struct ____INTELLISENSE_classify<__T(Args...,...)> { enum { __val = 10 }; };
template<class __T, class C, class ...Args> struct ____INTELLISENSE_classify<__T(C::*)(Args...)> { enum { __val = 11 }; };
template<class __T, class C, class ...Args> struct ____INTELLISENSE_classify<__T(C::*)(Args...,...)> { enum { __val = 11 }; };
#define __builtin_classify_type(...) (::__intern::____INTELLISENSE_classify<__typeof__(__VA_ARGS__)>::__val)
}


/* Misc builtins */
int __builtin_va_arg_pack(void);
__attribute__((__noreturn__)) void __builtin_abort(void);
__attribute__((__noreturn__)) void __builtin_unreachable(void);
__attribute__((__noreturn__)) void __builtin_trap(void);
__attribute__((__noreturn__)) void __builtin_exit(void);
__attribute__((__noreturn__)) void __builtin__exit(void);
__attribute__((__noreturn__)) void __builtin__Exit(void);

__SIZE_TYPE__ __builtin_strlen(char const *s);
int __builtin_strcmp(char const *a,char const *b);
int __builtin_strncmp(char const *a,char const *b, __SIZE_TYPE__ maxchars);
char *__builtin_strchr(char const *s, int needle);
char *__builtin_strrchr(char const *s, int needle);


void *__builtin_alloca(__SIZE_TYPE__ s);
long __builtin_expect(long val,long expect);
int __builtin_ffs(int x);
int __builtin_clz(unsigned int x);
int __builtin_ctz(unsigned int x);
int __builtin_clrsb(int x);
int __builtin_popcount(unsigned int x);
int __builtin_parity(unsigned int x);
int __builtin_ffsl(long);
int __builtin_clzl(unsigned long);
int __builtin_ctzl(unsigned long);
int __builtin_clrsbl(long);
int __builtin_popcountl(unsigned long);
int __builtin_parityl(unsigned long);
int __builtin_ffsll(long long);
int __builtin_clzll(unsigned long long);
int __builtin_ctzll(unsigned long long);
int __builtin_clrsbll(long long);
int __builtin_popcountll(unsigned long long);
int __builtin_parityll(unsigned long long);
unsigned short __builtin_bswap16(unsigned short);
unsigned int __builtin_bswap32(unsigned int);
unsigned long long __builtin_bswap64(unsigned long long);
char const *__builtin_FUNCTION(void);
char const *__builtin_FILE(void);
int __builtin_LINE(void);
void __builtin_prefetch(void const *addr,...);
void *__builtin_return_address(int level);

int __builtin_setjmp(void *);
__attribute__((__noreturn__)) void __builtin_longjmp(void *, int);


#define __builtin_offsetof(s,m) ((__SIZE_TYPE__)&((s*)0)->m)
#define __builtin_constant_p(x) ((void)(x),0)

#ifndef __cplusplus
#if 1
#define __builtin_choose_expr(c,tt,ff) ((c) ? (tt) : (ff))
#else
namespace __intern {
template<bool> struct ____INTELLISENSE_static_if_helper { };
template<> struct ____INTELLISENSE_static_if_helper<true> { bool __is_true__(); };
}
#define __builtin_choose_expr(c,tt,ff)                                                 \
	__if_exists(::__intern::____INTELLISENSE_static_if_helper<((c))>::__is_true__){tt} \
	__if_not_exists(::__intern::____INTELLISENSE_static_if_helper<((c))>::__is_true__){ff}
#endif
#endif /* __cplusplus */

#ifdef __x86_64__
typedef char *__builtin_va_list[1],*__gnuc_va_list[1];
namespace __intern {
template<class __T> __T ____INTELLISENSE_va_arg_heper(char *(&)[1]);
template<class __T> __T ____INTELLISENSE_va_arg_heper(char **&);
}
#else /* __x86_64__ */
typedef char *__builtin_va_list,*__gnuc_va_list;
namespace __intern {
template<class __T> __T ____INTELLISENSE_va_arg_heper(__builtin_va_list &);
}
#endif /* !__x86_64__ */
template<class __T> void __builtin_va_start(__builtin_va_list &ap, __T &before_start);
void __builtin_va_end(__builtin_va_list &ap);
void __builtin_va_copy(__builtin_va_list &dst_ap,__builtin_va_list &src_ap);
#define __builtin_va_arg(ap, __T) (::__intern::____INTELLISENSE_va_arg_heper<__T>(ap))

template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_fetch_and_add(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_fetch_and_sub(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_fetch_and_or(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_fetch_and_and(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_fetch_and_xor(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_fetch_and_nand(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_add_and_fetch(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_sub_and_fetch(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_or_and_fetch(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_and_and_fetch(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_xor_and_fetch(__T volatile *ptr, __S value,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_nand_and_fetch(__T volatile *ptr, __S value,...);
template<class __T, class __S, class N> typename ::__intern::____INTELLISENSE_enableif_arith<__T,bool>::__type __sync_bool_compare_and_swap(__T volatile *ptr, __S oldval,N newval,...);
template<class __T, class __S, class N> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_val_compare_and_swap(__T volatile *ptr, __S oldval,N newval,...);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif_arith<__T,__T>::__type __sync_lock_test_and_set(__T *ptr, __S value,...);
template<class __T> typename ::__intern::____INTELLISENSE_enableif_arith<__T,void>::__type __sync_lock_release(__T *ptr,...);
void __sync_synchronize(...);


#endif /* !__GNUC__ */


#ifndef __ATOMIC_RELAXED
#define __ATOMIC_RELAXED 0
#define __ATOMIC_CONSUME 1
#define __ATOMIC_ACQUIRE 2
#define __ATOMIC_RELEASE 3
#define __ATOMIC_ACQ_REL 4
#define __ATOMIC_SEQ_CST 5
#define __ATOMIC_HLE_ACQUIRE 65536
#define __ATOMIC_HLE_RELEASE 131072

#define __GCC_ATOMIC_BOOL_LOCK_FREE     1
#define __GCC_ATOMIC_CHAR_LOCK_FREE     1
#define __GCC_ATOMIC_CHAR16_T_LOCK_FREE 1
#define __GCC_ATOMIC_CHAR32_T_LOCK_FREE 1
#define __GCC_ATOMIC_WCHAR_T_LOCK_FREE  1
#define __GCC_ATOMIC_SHORT_LOCK_FREE    1
#define __GCC_ATOMIC_INT_LOCK_FREE      1
#define __GCC_ATOMIC_LONG_LOCK_FREE     1
#define __GCC_ATOMIC_LLONG_LOCK_FREE    1
#define __GCC_ATOMIC_POINTER_LOCK_FREE  1

template<class __T> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value,__T>::__type __atomic_load_n(__T const volatile *ptr, int memorder);
template<class __T> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value,void>::__type __atomic_load(__T const volatile *ptr, __T *ret, int memorder);
template<class __T> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value,void>::__type __atomic_load(__T const volatile *ptr, __T volatile *ret, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,void>::__type __atomic_store_n(__T volatile *ptr, __S val, int memorder);
template<class __T> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value,void>::__type __atomic_store(__T volatile *ptr, __T *val, int memorder);
template<class __T> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value,void>::__type __atomic_store(__T volatile *ptr, __T volatile *val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_exchange_n(__T volatile *ptr, __S val, int memorder);
template<class __T> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value,void>::__type __atomic_exchange(__T volatile *ptr, __T *val, __T *ret, int memorder);
template<class __T> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value,void>::__type __atomic_exchange(__T volatile *ptr, __T volatile *val, __T volatile *ret, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__S,bool>::__type __atomic_compare_exchange_n(__T volatile *ptr, __T *expected, __S desired, bool weak, int success_memorder, int failure_memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__S,bool>::__type __atomic_compare_exchange_n(__T volatile *ptr, __T volatile *expected, __S desired, bool weak, int success_memorder, int failure_memorder);
template<class __T> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value,bool>::__type __atomic_compare_exchange(__T volatile *ptr, __T *expected, __T *desired, bool weak, int success_memorder, int failure_memorder);
template<class __T> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value,bool>::__type __atomic_compare_exchange(__T volatile *ptr, __T volatile *expected, __T volatile *desired, bool weak, int success_memorder, int failure_memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_add_fetch(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_sub_fetch(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_and_fetch(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_xor_fetch(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_or_fetch(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_nand_fetch(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_fetch_add(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_fetch_sub(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_fetch_and(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_fetch_xor(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_fetch_or(__T volatile *ptr, __S val, int memorder);
template<class __T, class __S> typename ::__intern::____INTELLISENSE_enableif<::__intern::____INTELLISENSE_isarith<__T>::__value && ::__intern::____INTELLISENSE_isarith<__S>::__value,__T>::__type __atomic_fetch_nand(__T volatile *ptr, __S val, int memorder);

bool __atomic_test_and_set(void *ptr, int memorder);
void __atomic_clear(bool *ptr, int memorder);
void __atomic_thread_fence(int memorder);
void __atomic_signal_fence(int memorder);
bool __atomic_always_lock_free(__SIZE_TYPE__ size, void const volatile *ptr);
bool __atomic_is_lock_free(__SIZE_TYPE__ size, void const volatile *ptr);
#endif /* !__ATOMIC_RELAXED */

namespace __intern {
#ifndef __CHAR16_TYPE__
class ____INTELLISENSE_char16_t {
	unsigned short __v;
public:
	operator unsigned short & (void) throw();
	operator unsigned short const & (void) const throw();
	____INTELLISENSE_char16_t();
	____INTELLISENSE_char16_t(char16_t const &);
	____INTELLISENSE_char16_t(unsigned short);
};
#endif /* !__CHAR16_TYPE__ */
#ifndef __CHAR32_TYPE__
class ____INTELLISENSE_char32_t {
	unsigned int __v;
public:
	operator unsigned int & (void) throw();
	operator unsigned int const & (void) const throw();
	____INTELLISENSE_char32_t();
	____INTELLISENSE_char32_t(char32_t const &);
	____INTELLISENSE_char32_t(unsigned int);
};
#endif /* !__CHAR32_TYPE__ */

}

#ifdef __cplusplus
#ifndef __CHAR16_TYPE__
#define __CHAR16_TYPE__ ::__intern::____INTELLISENSE_char16_t
typedef __CHAR16_TYPE__ char16_t;
#endif /* !__CHAR16_TYPE__ */
#ifndef __CHAR32_TYPE__
#define __CHAR32_TYPE__ ::__intern::____INTELLISENSE_char32_t
typedef __CHAR32_TYPE__ char32_t;
#endif /* !__CHAR32_TYPE__ */
#endif /* !__cplusplus */

template<unsigned int __uid, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator + (__S,__intern::____intellisense_altint<__uid, __T>);
template<unsigned int __uid, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator - (__S,__intern::____intellisense_altint<__uid, __T>);
template<unsigned int __uid, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator * (__S,__intern::____intellisense_altint<__uid, __T>);
template<unsigned int __uid, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator / (__S,__intern::____intellisense_altint<__uid, __T>);
template<unsigned int __uid, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator % (__S,__intern::____intellisense_altint<__uid, __T>);
template<unsigned int __uid, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator & (__S,__intern::____intellisense_altint<__uid, __T>);
template<unsigned int __uid, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator | (__S,__intern::____intellisense_altint<__uid, __T>);
template<unsigned int __uid, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator ^ (__S,__intern::____intellisense_altint<__uid, __T>);



/* Sparse emulation */
#define __CHECKER__    1
#if 1
#define ____INTELLISENSE_attribute_noderef          /* Nothing */
#define ____INTELLISENSE_attribute_address_space(x) /* Nothing */
#else
#define ____INTELLISENSE_attribute_noderef          __declspec(restrict)
#define ____INTELLISENSE_attribute_address_space(x) __declspec(restrict)
#endif
#define ____INTELLISENSE_attribute_safe             /* What is this even supposed to do? */
#define ____INTELLISENSE_attribute_force            ____INTELLISENSE_ATTR_TYPE
#define ____INTELLISENSE_attribute_nocast           ____INTELLISENSE_ATTR_TYPE
#define ____INTELLISENSE_attribute_bitwise          ____INTELLISENSE_ATTR_TYPE
#define ____INTELLISENSE_attribute_context          ____INTELLISENSE_ATTR_FUNC
void __context__(void const volatile *expr, int mode);

#endif /* !____INTELLISENSE_STDINC_SYNTAX_H */
