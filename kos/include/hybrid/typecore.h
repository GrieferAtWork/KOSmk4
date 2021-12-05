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
#ifndef __GUARD_HYBRID_TYPECORE_H
#define __GUARD_HYBRID_TYPECORE_H 1

#include "../__stdinc.h"

#ifndef __DEEMON__

/* Autocomplete gcc-style compiler intrinsic predefined macros. */
#ifndef __CHAR_BIT__
#define __CHAR_BIT__ 8
#endif /* !__CHAR_BIT__ */

#ifndef __SIZEOF_CHAR__
#define __SIZEOF_CHAR__  1
#endif /* !__SIZEOF_CHAR__ */

#ifndef __SIZEOF_SHORT__
#ifdef __sizeof_short
#define __SIZEOF_SHORT__ __sizeof_short
#elif defined(_SILP64) || defined(__SILP64__)
#define __SIZEOF_SHORT__ 8
#elif defined(_SILP32) || defined(__SILP32__)
#define __SIZEOF_SHORT__ 4
#else /* ... */
#define __SIZEOF_SHORT__ 2
#endif /* !... */
#endif /* !__SIZEOF_SHORT__ */

#ifndef __SIZEOF_INT__
#ifdef __sizeof_int
#define __SIZEOF_INT__ __sizeof_int
#elif defined(__pdp11_int)
#if (__pdp11_int + 0) == 16
#define __SIZEOF_INT__ 2
#else /* __pdp11_int == 16 */
#define __SIZEOF_INT__ 4
#endif /* __pdp11_int != 16 */
#elif (defined(_ILP64) || defined(__ILP64__) || \
       defined(_SILP64) || defined(__SILP64__))
#define __SIZEOF_INT__ 8
#else /* ... */
#define __SIZEOF_INT__ 4
#endif /* !... */
#endif /* !__SIZEOF_INT__ */

#ifndef __SIZEOF_LONG__
#ifdef __sizeof_long
#define __SIZEOF_LONG__ __sizeof_long
#elif (defined(_LP32) || defined(__LP32__) || defined(_ILP32) || \
       defined(__ILP32__) || defined(_SILP32) || defined(__SILP32__))
#define __SIZEOF_LONG__ 4
#elif (defined(_LP64) || defined(__LP64__) || defined(_ILP64) ||        \
       defined(__ILP64__) || defined(_SILP64) || defined(__SILP64__) || \
       defined(__LONG64))
#define __SIZEOF_LONG__ 8
#elif defined(_LLP64) || defined(__LLP64__)
#define __SIZEOF_LONG__ 4
#elif (defined(_WIN16) || defined(WIN16) || defined(_WIN32) || defined(WIN32) ||          \
       defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
       defined(_WIN32_WCE) || defined(WIN32_WCE))
#define __SIZEOF_LONG__ 4
#else /* ... */
#define __SIZEOF_LONG__ __SIZEOF_POINTER__
#endif /* !... */
#endif /* !__SIZEOF_LONG__ */

#ifndef __SIZEOF_LONG_LONG__
#ifdef __COMPILER_HAVE_LONGLONG
#ifdef __sizeof_long_long
#define __SIZEOF_LONG_LONG__ __sizeof_long_long
#else /* __sizeof_long_long */
#define __SIZEOF_LONG_LONG__ 8
#endif /* !__sizeof_long_long */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* !__SIZEOF_LONG_LONG__ */

#ifndef __UINT128_TYPE__
#if ((defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 128) || \
     (defined(__SIZEOF_INT128__) && __SIZEOF_INT128__ == 16))
#define __INT128_TYPE__  signed __int128
#define __UINT128_TYPE__ unsigned __int128
#endif /* ... */
#endif /* !__UINT128_TYPE__ */


#ifndef __INT8_C
#if defined(_MSC_VER) || __has_extension(tpp_msvc_integer_suffix)
#define __INT8_C_SUFFIX__    i8
#define __INT16_C_SUFFIX__   i16
#define __INT32_C_SUFFIX__   i32
#define __INT64_C_SUFFIX__   i64
#define __UINT8_C_SUFFIX__   ui8
#define __UINT16_C_SUFFIX__  ui16
#define __UINT32_C_SUFFIX__  ui32
#define __UINT64_C_SUFFIX__  ui64
#define __INTMAX_C_SUFFIX__  i64
#define __UINTMAX_C_SUFFIX__ ui64
#define __INT8_C(c)    c##i8
#define __INT16_C(c)   c##i16
#define __INT32_C(c)   c##i32
#define __INT64_C(c)   c##i64
#define __UINT8_C(c)   c##ui8
#define __UINT16_C(c)  c##ui16
#define __UINT32_C(c)  c##ui32
#define __UINT64_C(c)  c##ui64
#if defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 128
#define __INT128_C_SUFFIX__  i128
#define __UINT128_C_SUFFIX__ ui128
#define __INT128_C(c)  c##i128
#define __UINT128_C(c) c##ui128
#endif /* _INTEGRAL_MAX_BITS >= 128 */
#else /* _MSC_VER */
#ifdef __INT8_C_SUFFIX__
#define __INT8_C(c)    __PP_CAT2(c, __INT8_C_SUFFIX__)
#else /* __INT8_C_SUFFIX__ */
#define __INT8_C_SUFFIX__ /* nothing */
#define __INT8_C(c)    c
#endif /* !__INT8_C_SUFFIX__ */
#ifdef __UINT8_C_SUFFIX__
#define __UINT8_C(c)   __PP_CAT2(c, __UINT8_C_SUFFIX__)
#else /* __UINT8_C_SUFFIX__ */
#define __UINT8_C_SUFFIX__ u
#define __UINT8_C(c)   c##u
#endif /* !__UINT8_C_SUFFIX__ */
#ifdef __INT16_C_SUFFIX__
#define __INT16_C(c)   __PP_CAT2(c, __INT16_C_SUFFIX__)
#elif __SIZEOF_INT__ >= 2
#define __INT16_C_SUFFIX__ /* nothing */
#define __INT16_C(c)   c
#elif __SIZEOF_LONG__ >= 2
#define __INT16_C_SUFFIX__ l
#define __INT16_C(c)   c##l
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ >= 2
#define __INT16_C_SUFFIX__ ll
#define __INT16_C(c)   c##ll
#endif /* ... */
#ifdef __UINT16_C_SUFFIX__
#define __UINT16_C(c)   __PP_CAT2(c, __UINT16_C_SUFFIX__)
#elif __SIZEOF_INT__ >= 2
#define __UINT16_C_SUFFIX__ u
#define __UINT16_C(c)  c##u
#elif __SIZEOF_LONG__ >= 2
#define __UINT16_C_SUFFIX__ ul
#define __UINT16_C(c)  c##ul
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ >= 2
#define __UINT16_C_SUFFIX__ ull
#define __UINT16_C(c)  c##ull
#endif /* ... */
#ifdef __INT32_C_SUFFIX__
#define __INT32_C(c)   __PP_CAT2(c, __INT32_C_SUFFIX__)
#elif __SIZEOF_INT__ >= 4
#define __INT32_C_SUFFIX__ /* nothing */
#define __INT32_C(c)   c
#elif __SIZEOF_LONG__ >= 4
#define __INT32_C_SUFFIX__ l
#define __INT32_C(c)   c##l
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ >= 4
#define __INT32_C_SUFFIX__ ll
#define __INT32_C(c)   c##ll
#endif /* ... */
#ifdef __UINT32_C_SUFFIX__
#define __UINT32_C(c)  __PP_CAT2(c, __UINT32_C_SUFFIX__)
#elif __SIZEOF_INT__ >= 4
#define __UINT32_C_SUFFIX__ u
#define __UINT32_C(c)  c##u
#elif __SIZEOF_LONG__ >= 4
#define __UINT32_C_SUFFIX__ ul
#define __UINT32_C(c)  c##ul
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ >= 4
#define __UINT32_C_SUFFIX__ ull
#define __UINT32_C(c)  c##ull
#endif /* ... */
#ifdef __INT64_C_SUFFIX__
#define __INT64_C(c)   __PP_CAT2(c, __INT64_C_SUFFIX__)
#elif __SIZEOF_INT__ >= 8
#define __INT64_C_SUFFIX__ /* nothing */
#define __INT64_C(c)   c
#elif __SIZEOF_LONG__ >= 8
#define __INT64_C_SUFFIX__ l
#define __INT64_C(c)   c##l
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ >= 8
#define __INT64_C_SUFFIX__ ll
#define __INT64_C(c)   c##ll
#endif /* ... */
#ifdef __UINT64_C_SUFFIX__
#define __UINT64_C(c)  __PP_CAT2(c, __UINT64_C_SUFFIX__)
#elif __SIZEOF_INT__ >= 8
#define __UINT64_C_SUFFIX__ u
#define __UINT64_C(c)  c##u
#elif __SIZEOF_LONG__ >= 8
#define __UINT64_C_SUFFIX__ ul
#define __UINT64_C(c)  c##ul
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ >= 8
#define __UINT64_C_SUFFIX__ ull
#define __UINT64_C(c)  c##ull
#endif /* ... */
#endif /* ... */
#endif /* !__INT8_C */

#ifndef __CC__
/* Don't  append  anything  when not  hosting  by a
 * C-compiler (e.g.: A linker script, or assembler) */
#undef __INT8_C
#undef __INT16_C
#undef __INT32_C
#undef __UINT8_C
#undef __UINT16_C
#undef __UINT32_C
#undef __INT64_C
#undef __UINT64_C
#undef __INT128_C
#undef __UINT128_C
#define __INT8_C(c)    c
#define __INT16_C(c)   c
#define __INT32_C(c)   c
#define __UINT8_C(c)   c
#define __UINT16_C(c)  c
#define __UINT32_C(c)  c
#define __INT64_C(c)   c
#define __UINT64_C(c)  c
#define __INT128_C(c)  c
#define __UINT128_C(c) c
#undef __INT8_C_SUFFIX__
#undef __INT16_C_SUFFIX__
#undef __INT32_C_SUFFIX__
#undef __INT64_C_SUFFIX__
#undef __INT128_C_SUFFIX__
#undef __UINT8_C_SUFFIX__
#undef __UINT16_C_SUFFIX__
#undef __UINT32_C_SUFFIX__
#undef __UINT64_C_SUFFIX__
#undef __UINT128_C_SUFFIX__
#undef __INTMAX_C_SUFFIX__
#undef __UINTMAX_C_SUFFIX__
#define __INT8_C_SUFFIX__    /* nothing */
#define __INT16_C_SUFFIX__   /* nothing */
#define __INT32_C_SUFFIX__   /* nothing */
#define __INT64_C_SUFFIX__   /* nothing */
#define __INT128_C_SUFFIX__  /* nothing */
#define __UINT8_C_SUFFIX__   /* nothing */
#define __UINT16_C_SUFFIX__  /* nothing */
#define __UINT32_C_SUFFIX__  /* nothing */
#define __UINT64_C_SUFFIX__  /* nothing */
#define __UINT128_C_SUFFIX__ /* nothing */
#define __INTMAX_C_SUFFIX__  /* nothing */
#define __UINTMAX_C_SUFFIX__ /* nothing */
#endif /* !__CC__ */

#define __PRIVATE_MIN_S1  (-__INT8_C(127)-__INT8_C(1))
#define __PRIVATE_MAX_S1    __INT8_C(127)
#define __PRIVATE_MIN_U1    __UINT8_C(0)
#define __PRIVATE_MAX_U1    __UINT8_C(0xff) /* 255 */
#define __PRIVATE_MIN_S2  (-__INT16_C(32767)-__INT16_C(1))
#define __PRIVATE_MAX_S2    __INT16_C(32767)
#define __PRIVATE_MIN_U2    __UINT16_C(0)
#define __PRIVATE_MAX_U2    __UINT16_C(0xffff) /* 65535 */
#define __PRIVATE_MIN_S4  (-__INT32_C(2147483647)-__INT32_C(1))
#define __PRIVATE_MAX_S4    __INT32_C(2147483647)
#define __PRIVATE_MIN_U4    __UINT32_C(0)
#define __PRIVATE_MAX_U4    __UINT32_C(0xffffffff) /* 4294967295 */
#ifdef __INT64_C
#define __PRIVATE_MIN_S8  (-__INT64_C(9223372036854775807)-__INT64_C(1))
#define __PRIVATE_MAX_S8    __INT64_C(9223372036854775807)
#define __PRIVATE_MIN_U8    __UINT64_C(0)
#define __PRIVATE_MAX_U8    __UINT64_C(0xffffffffffffffff) /* 18446744073709551615 */
#endif /* __INT64_C */
#ifdef __INT128_C
#define __PRIVATE_MIN_S16 (-__INT128_C(170141183460469231731687303715884105727)-__INT128_C(1))
#define __PRIVATE_MAX_S16   __INT128_C(170141183460469231731687303715884105727)
#define __PRIVATE_MIN_U16   __UINT128_C(0)
#define __PRIVATE_MAX_U16   __UINT128_C(0xffffffffffffffffffffffffffffffff)
#endif /* __INT128_C */

#ifndef __INTMAX_C
#ifdef __INT64_C
#define __INTMAX_C  __INT64_C
#define __UINTMAX_C __UINT64_C
#else /* __INT64_C */
#define __INTMAX_C  __INT32_C
#define __UINTMAX_C __UINT32_C
#endif /* !__INT64_C */
#endif /* !__INTMAX_C */

#ifndef __SIZEOF_POINTER__
#ifdef __sizeof_ptr
#define __SIZEOF_POINTER__ __sizeof_ptr
#elif (defined(_LP32) || defined(__LP32__) || defined(_ILP32) || \
       defined(__ILP32__) || defined(_SILP32) || defined(__SILP32__))
#define __SIZEOF_POINTER__ 4
#elif (defined(_LP64) || defined(__LP64__) || defined(_ILP64) ||        \
       defined(__ILP64__) || defined(_SILP64) || defined(__SILP64__) || \
       defined(_LLP64) || defined(__LLP64__))
#define __SIZEOF_POINTER__ 8
#else /* ... */
#include "host.h"
#if (defined(__x86_64__) || defined(__aarch64__) ||   \
     defined(__alpha__) || defined(__ia64__) ||       \
     defined(__sparc64__) || defined(__sparc_v9__) || \
     defined(__s390x__) ||  defined(__powerpc64__) || \
     defined(__arch64__) || defined(_WIN64) ||        \
     defined(__mips64))
#define __SIZEOF_POINTER__ 8
#elif defined(__i386__) || defined(__arm__) || defined(__CYGWIN32__)
#define __SIZEOF_POINTER__ 4
#elif defined(__SIZEOF_SIZE_T__)
#define __SIZEOF_POINTER__ __SIZEOF_SIZE_T__
#elif defined(__SIZEOF_PTRDIFF_T__)
#define __SIZEOF_POINTER__ __SIZEOF_PTRDIFF_T__
#else /* ... */
#ifdef __UINTPTR_MAX__
#if __UINTPTR_MAX__ == __PRIVATE_MAX_U4
#define __SIZEOF_POINTER__ 4
#elif __UINTPTR_MAX__ == __PRIVATE_MAX_U8
#define __SIZEOF_POINTER__ 8
#elif __UINTPTR_MAX__ == __PRIVATE_MAX_U2
#define __SIZEOF_POINTER__ 2
#elif __UINTPTR_MAX__ == __PRIVATE_MAX_U1
#define __SIZEOF_POINTER__ 1
#endif /* __UINTPTR_MAX__ == ... */
#endif /* __UINTPTR_MAX__ */
#ifndef __SIZEOF_POINTER__
#ifdef __INTPTR_MAX__
#if __INTPTR_MAX__ == __PRIVATE_MAX_S4
#define __SIZEOF_POINTER__ 4
#elif __INTPTR_MAX__ == __PRIVATE_MAX_S8
#define __SIZEOF_POINTER__ 8
#elif __INTPTR_MAX__ == __PRIVATE_MAX_S2
#define __SIZEOF_POINTER__ 2
#elif __INTPTR_MAX__ == __PRIVATE_MAX_S1
#define __SIZEOF_POINTER__ 1
#endif /* __INTPTR_MAX__ == ... */
#endif /* __INTPTR_MAX__ */
#ifndef __SIZEOF_POINTER__
#ifndef __KOS_SYSTEM_HEADERS__
#include <stdint.h>
#ifdef UINTPTR_MAX
#if UINTPTR_MAX == __PRIVATE_MAX_U4
#define __SIZEOF_POINTER__ 4
#elif UINTPTR_MAX == __PRIVATE_MAX_U8
#define __SIZEOF_POINTER__ 8
#elif UINTPTR_MAX == __PRIVATE_MAX_U2
#define __SIZEOF_POINTER__ 2
#elif UINTPTR_MAX == __PRIVATE_MAX_U1
#define __SIZEOF_POINTER__ 1
#endif /* UINTPTR_MAX == ... */
#elif defined(INTPTR_MAX)
#if INTPTR_MAX == __PRIVATE_MAX_S4
#define __SIZEOF_POINTER__ 4
#elif INTPTR_MAX == __PRIVATE_MAX_S8
#define __SIZEOF_POINTER__ 8
#elif INTPTR_MAX == __PRIVATE_MAX_S2
#define __SIZEOF_POINTER__ 2
#elif INTPTR_MAX == __PRIVATE_MAX_S1
#define __SIZEOF_POINTER__ 1
#endif /* INTPTR_MAX == ... */
#elif defined(INTPTR_MIN)
#if INTPTR_MIN == __PRIVATE_MIN_S4
#define __SIZEOF_POINTER__ 4
#elif INTPTR_MIN == __PRIVATE_MIN_S8
#define __SIZEOF_POINTER__ 8
#elif INTPTR_MIN == __PRIVATE_MIN_S2
#define __SIZEOF_POINTER__ 2
#elif INTPTR_MIN == __PRIVATE_MIN_S1
#define __SIZEOF_POINTER__ 1
#endif /* INTPTR_MIN == ... */
#elif defined(SIZE_MAX)
#if SIZE_MAX == __PRIVATE_MAX_U4
#define __SIZEOF_POINTER__ 4
#elif SIZE_MAX == __PRIVATE_MAX_U8
#define __SIZEOF_POINTER__ 8
#elif SIZE_MAX == __PRIVATE_MAX_U2
#define __SIZEOF_POINTER__ 2
#elif SIZE_MAX == __PRIVATE_MAX_U1
#define __SIZEOF_POINTER__ 1
#endif /* SIZE_MAX == ... */
#elif defined(PTRDIFF_MAX)
#if PTRDIFF_MAX == __PRIVATE_MAX_S4
#define __SIZEOF_POINTER__ 4
#elif PTRDIFF_MAX == __PRIVATE_MAX_S8
#define __SIZEOF_POINTER__ 8
#elif PTRDIFF_MAX == __PRIVATE_MAX_S2
#define __SIZEOF_POINTER__ 2
#elif PTRDIFF_MAX == __PRIVATE_MAX_S1
#define __SIZEOF_POINTER__ 1
#endif /* PTRDIFF_MAX == ... */
#elif defined(PTRDIFF_MIN)
#if PTRDIFF_MIN == __PRIVATE_MIN_S4
#define __SIZEOF_POINTER__ 4
#elif PTRDIFF_MIN == __PRIVATE_MIN_S8
#define __SIZEOF_POINTER__ 8
#elif PTRDIFF_MIN == __PRIVATE_MIN_S2
#define __SIZEOF_POINTER__ 2
#elif PTRDIFF_MIN == __PRIVATE_MIN_S1
#define __SIZEOF_POINTER__ 1
#endif /* PTRDIFF_MIN == ... */
#endif /* ... */
#endif /* !__KOS_SYSTEM_HEADERS__ */

#ifndef __SIZEOF_POINTER__
#error "Cannot determine `__SIZEOF_POINTER__'"
#endif /* !__SIZEOF_POINTER__ */
#endif /* !__SIZEOF_POINTER__ */
#endif /* !__SIZEOF_POINTER__ */
#endif /* !... */
#endif /* !... */
#endif /* !__SIZEOF_POINTER__ */

#ifndef __SIZEOF_PTRDIFF_T__
#define __SIZEOF_PTRDIFF_T__ __SIZEOF_POINTER__
#endif /* !__SIZEOF_PTRDIFF_T__ */

#ifndef __SIZEOF_SIZE_T__
#define __SIZEOF_SIZE_T__ __SIZEOF_POINTER__
#endif /* !__SIZEOF_SIZE_T__ */


#if __SIZEOF_POINTER__ == 8
#define __INTPTR_C  __INT64_C
#define __UINTPTR_C __UINT64_C
#elif __SIZEOF_POINTER__ == 4
#define __INTPTR_C  __INT32_C
#define __UINTPTR_C __UINT32_C
#elif __SIZEOF_POINTER__ == 2
#define __INTPTR_C  __INT16_C
#define __UINTPTR_C __UINT16_C
#elif __SIZEOF_POINTER__ == 1
#define __INTPTR_C  __INT8_C
#define __UINTPTR_C __UINT8_C
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported sizeof(void *)"
#endif /* __SIZEOF_POINTER__ != ... */

#if __SIZEOF_SIZE_T__ == __SIZEOF_POINTER__
#define __SIZE_C  __UINTPTR_C
#define __SSIZE_C __INTPTR_C
#elif __SIZEOF_SIZE_T__ == 8
#define __SIZE_C  __INT64_C
#define __SSIZE_C __UINT64_C
#elif __SIZEOF_SIZE_T__ == 4
#define __SIZE_C  __INT32_C
#define __SSIZE_C __UINT32_C
#elif __SIZEOF_SIZE_T__ == 2
#define __SIZE_C  __INT16_C
#define __SSIZE_C __UINT16_C
#elif __SIZEOF_SIZE_T__ == 1
#define __SIZE_C  __INT8_C
#define __SSIZE_C __UINT8_C
#else /* __SIZEOF_SIZE_T__ == ... */
#error "Unsupported sizeof(size_t)"
#endif /* __SIZEOF_SIZE_T__ != ... */



#ifndef __SIZEOF_INT_FAST8_T__
#ifdef __INT_FAST8_MAX__
#if __INT_FAST8_MAX__ == __PRIVATE_MAX_S1
#define __SIZEOF_INT_FAST8_T__ 1
#elif __INT_FAST8_MAX__ == __PRIVATE_MAX_S2
#define __SIZEOF_INT_FAST8_T__ 2
#elif __INT_FAST8_MAX__ == __PRIVATE_MAX_S4
#define __SIZEOF_INT_FAST8_T__ 4
#elif __INT_FAST8_MAX__ == __PRIVATE_MAX_S8
#define __SIZEOF_INT_FAST8_T__ 8
#endif /* __INT_FAST8_MAX__ == ... */
#endif /* __INT_FAST8_MAX__ */
#ifndef __SIZEOF_INT_FAST8_T__
#ifdef __UINT_FAST8_MAX__
#if __UINT_FAST8_MAX__ == __PRIVATE_MAX_U1
#define __SIZEOF_INT_FAST8_T__ 1
#elif __UINT_FAST8_MAX__ == __PRIVATE_MAX_U2
#define __SIZEOF_INT_FAST8_T__ 2
#elif __UINT_FAST8_MAX__ == __PRIVATE_MAX_U4
#define __SIZEOF_INT_FAST8_T__ 4
#elif __UINT_FAST8_MAX__ == __PRIVATE_MAX_U8
#define __SIZEOF_INT_FAST8_T__ 8
#endif /* __UINT_FAST8_MAX__ == ... */
#endif /* __UINT_FAST8_MAX__ */
#ifndef __SIZEOF_INT_FAST8_T__
#ifdef __INT_FAST8_MIN__
#if __INT_FAST8_MIN__ == __PRIVATE_MIN_S1
#define __SIZEOF_INT_FAST8_T__ 1
#elif __INT_FAST8_MIN__ == __PRIVATE_MIN_S2
#define __SIZEOF_INT_FAST8_T__ 2
#elif __INT_FAST8_MIN__ == __PRIVATE_MIN_S4
#define __SIZEOF_INT_FAST8_T__ 4
#elif __INT_FAST8_MIN__ == __PRIVATE_MIN_S8
#define __SIZEOF_INT_FAST8_T__ 8
#endif /* __INT_FAST8_MIN__ == ... */
#endif /* __INT_FAST8_MIN__ */
#ifndef __SIZEOF_INT_FAST8_T__
#define __SIZEOF_INT_FAST8_T__ 1
#endif /* !__SIZEOF_INT_FAST8_T__ */
#endif /* !__SIZEOF_INT_FAST8_T__ */
#endif /* !__SIZEOF_INT_FAST8_T__ */
#endif /* !__SIZEOF_INT_FAST8_T__ */

#ifndef __SIZEOF_INT_FAST16_T__
#ifdef __INT_FAST16_MAX__
#if __INT_FAST16_MAX__ == __PRIVATE_MAX_S1
#define __SIZEOF_INT_FAST16_T__ 1
#elif __INT_FAST16_MAX__ == __PRIVATE_MAX_S2
#define __SIZEOF_INT_FAST16_T__ 2
#elif __INT_FAST16_MAX__ == __PRIVATE_MAX_S4
#define __SIZEOF_INT_FAST16_T__ 4
#elif __INT_FAST16_MAX__ == __PRIVATE_MAX_S8
#define __SIZEOF_INT_FAST16_T__ 8
#endif /* __INT_FAST16_MAX__ == ... */
#endif /* __INT_FAST16_MAX__ */
#ifndef __SIZEOF_INT_FAST16_T__
#ifdef __UINT_FAST16_MAX__
#if __UINT_FAST16_MAX__ == __PRIVATE_MAX_U1
#define __SIZEOF_INT_FAST16_T__ 1
#elif __UINT_FAST16_MAX__ == __PRIVATE_MAX_U2
#define __SIZEOF_INT_FAST16_T__ 2
#elif __UINT_FAST16_MAX__ == __PRIVATE_MAX_U4
#define __SIZEOF_INT_FAST16_T__ 4
#elif __UINT_FAST16_MAX__ == __PRIVATE_MAX_U8
#define __SIZEOF_INT_FAST16_T__ 8
#endif /* __UINT_FAST16_MAX__ == ... */
#endif /* __UINT_FAST16_MAX__ */
#ifndef __SIZEOF_INT_FAST16_T__
#ifdef __INT_FAST16_MIN__
#if __INT_FAST16_MIN__ == __PRIVATE_MIN_S1
#define __SIZEOF_INT_FAST16_T__ 1
#elif __INT_FAST16_MIN__ == __PRIVATE_MIN_S2
#define __SIZEOF_INT_FAST16_T__ 2
#elif __INT_FAST16_MIN__ == __PRIVATE_MIN_S4
#define __SIZEOF_INT_FAST16_T__ 4
#elif __INT_FAST16_MIN__ == __PRIVATE_MIN_S8
#define __SIZEOF_INT_FAST16_T__ 8
#endif /* __INT_FAST16_MIN__ == ... */
#endif /* __INT_FAST16_MIN__ */
#ifndef __SIZEOF_INT_FAST16_T__
#include "host.h"
#if defined(__i386__) || defined(__x86_64__)
#define __SIZEOF_INT_FAST16_T__ 4
#else /* __i386__ || __x86_64__ */
#define __SIZEOF_INT_FAST16_T__ 2
#endif /* __i386__ || __x86_64__ */
#endif /* !__SIZEOF_INT_FAST16_T__ */
#endif /* !__SIZEOF_INT_FAST16_T__ */
#endif /* !__SIZEOF_INT_FAST16_T__ */
#endif /* !__SIZEOF_INT_FAST16_T__ */

#ifndef __SIZEOF_INT_FAST32_T__
#ifdef __INT_FAST32_MAX__
#if __INT_FAST32_MAX__ == __PRIVATE_MAX_S1
#define __SIZEOF_INT_FAST32_T__ 1
#elif __INT_FAST32_MAX__ == __PRIVATE_MAX_S2
#define __SIZEOF_INT_FAST32_T__ 2
#elif __INT_FAST32_MAX__ == __PRIVATE_MAX_S4
#define __SIZEOF_INT_FAST32_T__ 4
#elif __INT_FAST32_MAX__ == __PRIVATE_MAX_S8
#define __SIZEOF_INT_FAST32_T__ 8
#endif /* __INT_FAST32_MAX__ == ... */
#endif /* __INT_FAST32_MAX__ */
#ifndef __SIZEOF_INT_FAST32_T__
#ifdef __UINT_FAST32_MAX__
#if __UINT_FAST32_MAX__ == __PRIVATE_MAX_U1
#define __SIZEOF_INT_FAST32_T__ 1
#elif __UINT_FAST32_MAX__ == __PRIVATE_MAX_U2
#define __SIZEOF_INT_FAST32_T__ 2
#elif __UINT_FAST32_MAX__ == __PRIVATE_MAX_U4
#define __SIZEOF_INT_FAST32_T__ 4
#elif __UINT_FAST32_MAX__ == __PRIVATE_MAX_U8
#define __SIZEOF_INT_FAST32_T__ 8
#endif /* __UINT_FAST32_MAX__ == ... */
#endif /* __UINT_FAST32_MAX__ */
#ifndef __SIZEOF_INT_FAST32_T__
#ifdef __INT_FAST32_MIN__
#if __INT_FAST32_MIN__ == __PRIVATE_MIN_S1
#define __SIZEOF_INT_FAST32_T__ 1
#elif __INT_FAST32_MIN__ == __PRIVATE_MIN_S2
#define __SIZEOF_INT_FAST32_T__ 2
#elif __INT_FAST32_MIN__ == __PRIVATE_MIN_S4
#define __SIZEOF_INT_FAST32_T__ 4
#elif __INT_FAST32_MIN__ == __PRIVATE_MIN_S8
#define __SIZEOF_INT_FAST32_T__ 8
#endif /* __INT_FAST32_MIN__ == ... */
#endif /* __INT_FAST32_MIN__ */
#ifndef __SIZEOF_INT_FAST32_T__
#define __SIZEOF_INT_FAST32_T__ 4
#endif /* !__SIZEOF_INT_FAST32_T__ */
#endif /* !__SIZEOF_INT_FAST32_T__ */
#endif /* !__SIZEOF_INT_FAST32_T__ */
#endif /* !__SIZEOF_INT_FAST32_T__ */

#ifndef __SIZEOF_INT_FAST64_T__
#ifdef __INT_FAST64_MAX__
#if __INT_FAST64_MAX__ == __PRIVATE_MAX_S1
#define __SIZEOF_INT_FAST64_T__ 1
#elif __INT_FAST64_MAX__ == __PRIVATE_MAX_S2
#define __SIZEOF_INT_FAST64_T__ 2
#elif __INT_FAST64_MAX__ == __PRIVATE_MAX_S4
#define __SIZEOF_INT_FAST64_T__ 4
#elif __INT_FAST64_MAX__ == __PRIVATE_MAX_S8
#define __SIZEOF_INT_FAST64_T__ 8
#endif /* __INT_FAST64_MAX__ == ... */
#endif /* __INT_FAST64_MAX__ */
#ifndef __SIZEOF_INT_FAST64_T__
#ifdef __UINT_FAST64_MAX__
#if __UINT_FAST64_MAX__ == __PRIVATE_MAX_U1
#define __SIZEOF_INT_FAST64_T__ 1
#elif __UINT_FAST64_MAX__ == __PRIVATE_MAX_U2
#define __SIZEOF_INT_FAST64_T__ 2
#elif __UINT_FAST64_MAX__ == __PRIVATE_MAX_U4
#define __SIZEOF_INT_FAST64_T__ 4
#elif __UINT_FAST64_MAX__ == __PRIVATE_MAX_U8
#define __SIZEOF_INT_FAST64_T__ 8
#endif /* __UINT_FAST64_MAX__ == ... */
#endif /* __UINT_FAST64_MAX__ */
#ifndef __SIZEOF_INT_FAST64_T__
#ifdef __INT_FAST64_MIN__
#if __INT_FAST64_MIN__ == __PRIVATE_MIN_S1
#define __SIZEOF_INT_FAST64_T__ 1
#elif __INT_FAST64_MIN__ == __PRIVATE_MIN_S2
#define __SIZEOF_INT_FAST64_T__ 2
#elif __INT_FAST64_MIN__ == __PRIVATE_MIN_S4
#define __SIZEOF_INT_FAST64_T__ 4
#elif __INT_FAST64_MIN__ == __PRIVATE_MIN_S8
#define __SIZEOF_INT_FAST64_T__ 8
#endif /* __INT_FAST64_MIN__ == ... */
#endif /* __INT_FAST64_MIN__ */
#ifndef __SIZEOF_INT_FAST64_T__
#define __SIZEOF_INT_FAST64_T__ 8
#endif /* !__SIZEOF_INT_FAST64_T__ */
#endif /* !__SIZEOF_INT_FAST64_T__ */
#endif /* !__SIZEOF_INT_FAST64_T__ */
#endif /* !__SIZEOF_INT_FAST64_T__ */

#ifndef __SIZEOF_SIG_ATOMIC_T__
#ifdef __SIG_ATOMIC_MAX__
#if __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_S4
#define __SIZEOF_SIG_ATOMIC_T__ 4
#elif __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_S8
#define __SIZEOF_SIG_ATOMIC_T__ 8
#elif __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_S2
#define __SIZEOF_SIG_ATOMIC_T__ 2
#elif __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_S1
#define __SIZEOF_SIG_ATOMIC_T__ 1
#elif __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_U4
#define __SIG_ATOMIC_UNSIGNED__ 1
#define __SIZEOF_SIG_ATOMIC_T__ 4
#elif __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_U8
#define __SIG_ATOMIC_UNSIGNED__ 1
#define __SIZEOF_SIG_ATOMIC_T__ 8
#elif __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_U2
#define __SIG_ATOMIC_UNSIGNED__ 1
#define __SIZEOF_SIG_ATOMIC_T__ 2
#elif __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_U1
#define __SIG_ATOMIC_UNSIGNED__ 1
#define __SIZEOF_SIG_ATOMIC_T__ 1
#endif /* __SIG_ATOMIC_MAX__ == ... */
#endif /* __SIG_ATOMIC_MAX__ */
#if !defined(__SIZEOF_SIG_ATOMIC_T__) && defined(__SIG_ATOMIC_MIN__)
#undef __SIG_ATOMIC_UNSIGNED__
#if __SIG_ATOMIC_MIN__ == __PRIVATE_MIN_S4
#define __SIZEOF_SIG_ATOMIC_T__ 4
#elif __SIG_ATOMIC_MIN__ == __PRIVATE_MIN_S8
#define __SIZEOF_SIG_ATOMIC_T__ 8
#elif __SIG_ATOMIC_MIN__ == __PRIVATE_MIN_S2
#define __SIZEOF_SIG_ATOMIC_T__ 2
#elif __SIG_ATOMIC_MIN__ == __PRIVATE_MIN_S1
#define __SIZEOF_SIG_ATOMIC_T__ 1
#elif __SIG_ATOMIC_MIN__ == 0
#define __SIG_ATOMIC_UNSIGNED__ 1
#endif /* __SIG_ATOMIC_MIN__ == ... */
#endif /* __SIZEOF_SIG_ATOMIC_T__ && __SIG_ATOMIC_MIN__ */
#ifndef __SIZEOF_SIG_ATOMIC_T__
#define __SIZEOF_SIG_ATOMIC_T__ __SIZEOF_INT__
#endif /* !__SIZEOF_SIG_ATOMIC_T__ */
#else /* !__SIZEOF_SIG_ATOMIC_T__ */
#if ((defined(__SIG_ATOMIC_MIN__) && (__SIG_ATOMIC_MIN__ == 0)) || \
     (defined(__SIG_ATOMIC_MAX__) && (__SIG_ATOMIC_MAX__ == __PRIVATE_MAX_U4 || \
                                      __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_U8 || \
                                      __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_U2 || \
                                      __SIG_ATOMIC_MAX__ == __PRIVATE_MAX_U1)))
#define __SIG_ATOMIC_UNSIGNED__ 1
#endif /* ... */
#endif /* __SIZEOF_SIG_ATOMIC_T__ */

#ifndef __SIZEOF_WINT_T__
#ifdef __WINT_MIN__
#undef  __WINT_UNSIGNED__
#if __WINT_MIN__ == __PRIVATE_MIN_S4
#define __SIZEOF_WINT_T__ 4
#elif __WINT_MIN__ == __PRIVATE_MIN_S2
#define __SIZEOF_WINT_T__ 2
#elif __WINT_MIN__ == __PRIVATE_MIN_S8
#define __SIZEOF_WINT_T__ 8
#elif __WINT_MIN__ == __PRIVATE_MIN_S1
#define __SIZEOF_WINT_T__ 1
#elif __WINT_MIN__ == 0
#define __WINT_UNSIGNED__ 1
#endif /* __WINT_MIN__ == ... */
#endif /* __WINT_MIN__ */
#ifndef __SIZEOF_WINT_T__
#ifdef __WINT_MAX__
#if __WINT_MAX__ == __PRIVATE_MAX_S4
#define __SIZEOF_WINT_T__ 4
#elif __WINT_MAX__ == __PRIVATE_MAX_S2
#define __SIZEOF_WINT_T__ 2
#elif __WINT_MAX__ == __PRIVATE_MAX_S8
#define __SIZEOF_WINT_T__ 8
#elif __WINT_MAX__ == __PRIVATE_MAX_S1
#define __SIZEOF_WINT_T__ 1
#elif __WINT_MAX__ == __PRIVATE_MAX_U4
#undef  __WINT_UNSIGNED__
#define __WINT_UNSIGNED__ 1
#define __SIZEOF_WINT_T__ 4
#elif __WINT_MAX__ == __PRIVATE_MAX_U2
#undef  __WINT_UNSIGNED__
#define __WINT_UNSIGNED__ 1
#define __SIZEOF_WINT_T__ 2
#elif __WINT_MAX__ == __PRIVATE_MAX_U8
#undef  __WINT_UNSIGNED__
#define __WINT_UNSIGNED__ 1
#define __SIZEOF_WINT_T__ 8
#elif __WINT_MAX__ == __PRIVATE_MAX_U1
#undef  __WINT_UNSIGNED__
#define __WINT_UNSIGNED__ 1
#define __SIZEOF_WINT_T__ 1
#endif
#endif /* __WINT_MAX__ */
#ifndef __SIZEOF_WINT_T__
#if (defined(__CYGWIN__) || defined(__CYGWIN32__) || \
     defined(__MINGW32__) || defined(WIN32) || defined(_WIN32) || \
     defined(WIN64) || defined(_WIN64))
#define __SIZEOF_WINT_T__ 2
#define __WINT_UNSIGNED__ 1
#else /* ... */
#define __SIZEOF_WINT_T__ __SIZEOF_INT__
#endif /* !... */
#endif /* !__SIZEOF_WINT_T__ */
#endif /* !__SIZEOF_WINT_T__ */
#else /* !__SIZEOF_WINT_T__ */
#ifndef __WINT_UNSIGNED__
#if (defined(__WINT_MIN__) && (__WINT_MIN__ == 0)) || \
    (defined(__WINT_MAX__) && (__WINT_MAX__ == __PRIVATE_MAX_U4 || \
                               __WINT_MAX__ == __PRIVATE_MAX_U2 || \
                               __WINT_MAX__ == __PRIVATE_MAX_U1 || \
                               __WINT_MAX__ == __PRIVATE_MAX_U8))
#define __WINT_UNSIGNED__ 1
#endif /* ... */
#endif /* !__WINT_UNSIGNED__ */
#endif /* __SIZEOF_WINT_T__ */


#ifndef __SIZEOF_WCHAR_T__
#ifdef __WCHAR_MIN__
#undef __WCHAR_UNSIGNED__
#if __WCHAR_MIN__ == __PRIVATE_MIN_S4
#define __SIZEOF_WCHAR_T__ 4
#elif __WCHAR_MIN__ == __PRIVATE_MIN_S2
#define __SIZEOF_WCHAR_T__ 2
#elif __WCHAR_MIN__ == __PRIVATE_MIN_S8
#define __SIZEOF_WCHAR_T__ 8
#elif __WCHAR_MIN__ == __PRIVATE_MIN_S1
#define __SIZEOF_WCHAR_T__ 1
#elif __WCHAR_MIN__ == 0
#define __WCHAR_UNSIGNED__ 1
#endif /* __WCHAR_MIN__ == ... */
#endif /* __WCHAR_MIN__ */
#ifndef __SIZEOF_WCHAR_T__
#ifdef __WCHAR_MAX__
#if __WCHAR_MAX__ == __PRIVATE_MAX_S4
#define __SIZEOF_WCHAR_T__ 4
#elif __WCHAR_MAX__ == __PRIVATE_MAX_S2
#define __SIZEOF_WCHAR_T__ 2
#elif __WCHAR_MAX__ == __PRIVATE_MAX_S8
#define __SIZEOF_WCHAR_T__ 8
#elif __WCHAR_MAX__ == __PRIVATE_MAX_S1
#define __SIZEOF_WCHAR_T__ 1
#elif __WCHAR_MAX__ == __PRIVATE_MAX_U4
#undef  __WCHAR_UNSIGNED__
#define __WCHAR_UNSIGNED__ 1
#define __SIZEOF_WCHAR_T__ 4
#elif __WCHAR_MAX__ == __PRIVATE_MAX_U2
#undef  __WCHAR_UNSIGNED__
#define __WCHAR_UNSIGNED__ 1
#define __SIZEOF_WCHAR_T__ 2
#elif __WCHAR_MAX__ == __PRIVATE_MAX_U8
#undef  __WCHAR_UNSIGNED__
#define __WCHAR_UNSIGNED__ 1
#define __SIZEOF_WCHAR_T__ 8
#elif __WCHAR_MAX__ == __PRIVATE_MAX_U1
#undef  __WCHAR_UNSIGNED__
#define __WCHAR_UNSIGNED__ 1
#define __SIZEOF_WCHAR_T__ 1
#endif /* __WCHAR_MAX__ == ... */
#endif /* __WCHAR_MAX__ */
#ifndef __SIZEOF_WCHAR_T__
#if defined(__PE__)
#define __SIZEOF_WCHAR_T__ 2
#else /* __PE__ */
#define __SIZEOF_WCHAR_T__ 4
#endif /* !__PE__ */
#endif /* !__SIZEOF_WCHAR_T__ */
#endif /* !__SIZEOF_WCHAR_T__ */
#else /* !__SIZEOF_WCHAR_T__ */
#ifndef __WCHAR_UNSIGNED__
#if ((defined(__WCHAR_MIN__) && (__WCHAR_MIN__ == 0)) || \
     (defined(__WCHAR_MAX__) && (__WCHAR_MAX__ == __PRIVATE_MAX_U4 || \
                                 __WCHAR_MAX__ == __PRIVATE_MAX_U2 || \
                                 __WCHAR_MAX__ == __PRIVATE_MAX_U1 || \
                                 __WCHAR_MAX__ == __PRIVATE_MAX_U8)))
#define __WCHAR_UNSIGNED__ 1
#endif /* ... */
#endif /* !__WCHAR_UNSIGNED__ */
#endif /* __SIZEOF_WCHAR_T__ */


#if defined(__INT8_TYPE__) && defined(__UINT8_TYPE__)
#define __TYPEFOR_INTIB1  __INT8_TYPE__
#define __TYPEFOR_UINTIB1 __UINT8_TYPE__
#elif __SIZEOF_CHAR__ == 1
#define __TYPEFOR_INTIB1  signed char
#define __TYPEFOR_UINTIB1 unsigned char
#elif __SIZEOF_SHORT__ == 1
#define __TYPEFOR_INTIB1  signed short
#define __TYPEFOR_UINTIB1 unsigned short
#elif __SIZEOF_INT__ == 1
#define __TYPEFOR_INTIB1  signed int
#define __TYPEFOR_UINTIB1 unsigned int
#elif __SIZEOF_LONG__ == 1
#define __TYPEFOR_INTIB1  signed long
#define __TYPEFOR_UINTIB1 unsigned long
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ == 1
#define __TYPEFOR_INTIB1  signed long long
#define __TYPEFOR_UINTIB1 unsigned long long
#endif /* ... == 1 */

#if defined(__INT16_TYPE__) && defined(__UINT16_TYPE__)
#define __TYPEFOR_INTIB2  __INT16_TYPE__
#define __TYPEFOR_UINTIB2 __UINT16_TYPE__
#elif __SIZEOF_SHORT__ == 2
#define __TYPEFOR_INTIB2  signed short
#define __TYPEFOR_UINTIB2 unsigned short
#elif __SIZEOF_INT__ == 2
#define __TYPEFOR_INTIB2  signed int
#define __TYPEFOR_UINTIB2 unsigned int
#elif __SIZEOF_LONG__ == 2
#define __TYPEFOR_INTIB2  signed long
#define __TYPEFOR_UINTIB2 unsigned long
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ == 2
#define __TYPEFOR_INTIB2  signed long long
#define __TYPEFOR_UINTIB2 unsigned long long
#elif __SIZEOF_CHAR__ == 2
#define __TYPEFOR_INTIB2  signed char
#define __TYPEFOR_UINTIB2 unsigned char
#endif /* ... == 2 */

#if defined(__INT32_TYPE__) && defined(__UINT32_TYPE__)
#define __TYPEFOR_INTIB4  __INT32_TYPE__
#define __TYPEFOR_UINTIB4 __UINT32_TYPE__
#elif __SIZEOF_INT__ == 4
#define __TYPEFOR_INTIB4  signed int
#define __TYPEFOR_UINTIB4 unsigned int
#elif __SIZEOF_LONG__ == 4
#define __TYPEFOR_INTIB4  signed long
#define __TYPEFOR_UINTIB4 unsigned long
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ == 4
#define __TYPEFOR_INTIB4  signed long long
#define __TYPEFOR_UINTIB4 unsigned long long
#elif __SIZEOF_SHORT__ == 4
#define __TYPEFOR_INTIB4  signed short
#define __TYPEFOR_UINTIB4 unsigned short
#elif __SIZEOF_CHAR__ == 4
#define __TYPEFOR_INTIB4  signed char
#define __TYPEFOR_UINTIB4 unsigned char
#endif /* ... == 4 */

#if defined(__INT64_TYPE__) && defined(__UINT64_TYPE__)
#define __TYPEFOR_INTIB8  __INT64_TYPE__
#define __TYPEFOR_UINTIB8 __UINT64_TYPE__
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ == 8
#define __TYPEFOR_INTIB8  signed long long
#define __TYPEFOR_UINTIB8 unsigned long long
#elif __SIZEOF_LONG__ == 8
#define __TYPEFOR_INTIB8  signed long
#define __TYPEFOR_UINTIB8 unsigned long
#elif __SIZEOF_INT__ == 8
#define __TYPEFOR_INTIB8  signed int
#define __TYPEFOR_UINTIB8 unsigned int
#elif __SIZEOF_SHORT__ == 8
#define __TYPEFOR_INTIB8  signed short
#define __TYPEFOR_UINTIB8 unsigned short
#elif __SIZEOF_CHAR__ == 8
#define __TYPEFOR_INTIB8  signed char
#define __TYPEFOR_UINTIB8 unsigned char
#endif /* ... == 8 */

#define __PRIVATE_TYPEFOR_INTIB(n)  __TYPEFOR_INTIB##n
#define __PRIVATE_TYPEFOR_UINTIB(n) __TYPEFOR_UINTIB##n
#define __TYPEFOR_INTIB(n)  __PRIVATE_TYPEFOR_INTIB(n)
#define __TYPEFOR_UINTIB(n) __PRIVATE_TYPEFOR_UINTIB(n)

#ifndef __CHAR8_TYPE__
#if __SIZEOF_CHAR__ == 1
#define __CHAR8_TYPE__ char
#elif defined(__CHAR_UNSIGNED__)
#define __CHAR8_TYPE__ __UINT8_TYPE__
#else /* ... */
#define __CHAR8_TYPE__ __INT8_TYPE__
#endif /* !... */
#endif /* !__CHAR8_TYPE__ */

#ifndef __INT8_TYPE__
#ifdef __TYPEFOR_INTIB1
#define __INT8_TYPE__ __TYPEFOR_INTIB1
#endif /* __TYPEFOR_INTIB1 */
#endif /* !__INT8_TYPE__ */
#ifndef __INT16_TYPE__
#ifdef __TYPEFOR_INTIB2
#define __INT16_TYPE__ __TYPEFOR_INTIB2
#endif /* __TYPEFOR_INTIB2 */
#endif /* !__INT16_TYPE__ */
#ifndef __INT32_TYPE__
#ifdef __TYPEFOR_INTIB4
#define __INT32_TYPE__ __TYPEFOR_INTIB4
#endif /* __TYPEFOR_INTIB4 */
#endif /* !__INT32_TYPE__ */
#ifndef __UINT8_TYPE__
#ifdef __TYPEFOR_UINTIB1
#define __UINT8_TYPE__ __TYPEFOR_UINTIB1
#endif /* __TYPEFOR_UINTIB1 */
#endif /* !__UINT8_TYPE__ */
#ifndef __UINT16_TYPE__
#ifdef __TYPEFOR_UINTIB2
#define __UINT16_TYPE__ __TYPEFOR_UINTIB2
#endif /* __TYPEFOR_UINTIB2 */
#endif /* !__UINT16_TYPE__ */
#ifndef __UINT32_TYPE__
#ifdef __TYPEFOR_UINTIB4
#define __UINT32_TYPE__ __TYPEFOR_UINTIB4
#endif /* __TYPEFOR_UINTIB4 */
#endif /* !__UINT32_TYPE__ */
#ifndef __INT64_TYPE__
#ifdef __TYPEFOR_INTIB8
#define __INT64_TYPE__ __TYPEFOR_INTIB8
#endif /* __TYPEFOR_INTIB8 */
#endif /* !__INT64_TYPE__ */
#ifndef __UINT64_TYPE__
#ifdef __TYPEFOR_UINTIB8
#define __UINT64_TYPE__ __TYPEFOR_UINTIB8
#endif /* __TYPEFOR_UINTIB8 */
#endif /* !__UINT64_TYPE__ */


#ifndef __SIZEOF_INT_LEAST64_T__
#ifdef __TYPEFOR_UINTIB8
#define __SIZEOF_INT_LEAST64_T__ 8
#endif /* __TYPEFOR_UINTIB8 */
#endif /* !__SIZEOF_INT_LEAST64_T__ */

#ifndef __SIZEOF_INT_LEAST32_T__
#ifdef __TYPEFOR_UINTIB4
#define __SIZEOF_INT_LEAST32_T__ 4
#elif defined(__SIZEOF_INT_LEAST64_T__)
#define __SIZEOF_INT_LEAST32_T__ __SIZEOF_INT_LEAST64_T__
#endif /* ... */
#endif /* !__SIZEOF_INT_LEAST32_T__ */

#ifndef __SIZEOF_INT_LEAST16_T__
#ifdef __TYPEFOR_UINTIB2
#define __SIZEOF_INT_LEAST16_T__ 2
#elif defined(__SIZEOF_INT_LEAST32_T__)
#define __SIZEOF_INT_LEAST16_T__ __SIZEOF_INT_LEAST32_T__
#endif /* ... */
#endif /* !__SIZEOF_INT_LEAST16_T__ */

#ifndef __SIZEOF_INT_LEAST8_T__
#ifdef __TYPEFOR_UINTIB1
#define __SIZEOF_INT_LEAST8_T__ 1
#elif defined(__SIZEOF_INT_LEAST16_T__)
#define __SIZEOF_INT_LEAST8_T__ __SIZEOF_INT_LEAST16_T__
#endif /* ... */
#endif /* !__SIZEOF_INT_LEAST8_T__ */


#ifndef __INT_LEAST8_TYPE__
#ifdef __SIZEOF_INT_LEAST8_T__
#define __INT_LEAST8_TYPE__   __TYPEFOR_INTIB(__SIZEOF_INT_LEAST8_T__)
#endif /* __SIZEOF_INT_LEAST8_T__ */
#endif /* !__INT_LEAST8_TYPE__ */
#ifndef __INT_LEAST16_TYPE__
#ifdef __SIZEOF_INT_LEAST16_T__
#define __INT_LEAST16_TYPE__ __TYPEFOR_INTIB(__SIZEOF_INT_LEAST16_T__)
#endif /* __SIZEOF_INT_LEAST16_T__ */
#endif /* !__INT_LEAST16_TYPE__ */
#ifndef __INT_LEAST32_TYPE__
#ifdef __SIZEOF_INT_LEAST32_T__
#define __INT_LEAST32_TYPE__ __TYPEFOR_INTIB(__SIZEOF_INT_LEAST32_T__)
#endif /* __SIZEOF_INT_LEAST32_T__ */
#endif /* !__INT_LEAST32_TYPE__ */
#ifndef __INT_LEAST64_TYPE__
#ifdef __SIZEOF_INT_LEAST64_T__
#define __INT_LEAST64_TYPE__ __TYPEFOR_INTIB(__SIZEOF_INT_LEAST64_T__)
#endif /* __SIZEOF_INT_LEAST64_T__ */
#endif /* !__INT_LEAST64_TYPE__ */
#ifndef __UINT_LEAST8_TYPE__
#ifdef __SIZEOF_INT_LEAST8_T__
#define __UINT_LEAST8_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_INT_LEAST8_T__)
#endif /* __SIZEOF_INT_LEAST8_T__ */
#endif /* !__UINT_LEAST8_TYPE__ */
#ifndef __UINT_LEAST16_TYPE__
#ifdef __SIZEOF_INT_LEAST16_T__
#define __UINT_LEAST16_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_INT_LEAST16_T__)
#endif /* __SIZEOF_INT_LEAST16_T__ */
#endif /* !__UINT_LEAST16_TYPE__ */
#ifndef __UINT_LEAST32_TYPE__
#ifdef __SIZEOF_INT_LEAST32_T__
#define __UINT_LEAST32_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_INT_LEAST32_T__)
#endif /* __SIZEOF_INT_LEAST32_T__ */
#endif /* !__UINT_LEAST32_TYPE__ */
#ifndef __UINT_LEAST64_TYPE__
#ifdef __SIZEOF_INT_LEAST64_T__
#define __UINT_LEAST64_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_INT_LEAST64_T__)
#endif /* __SIZEOF_INT_LEAST64_T__ */
#endif /* !__UINT_LEAST64_TYPE__ */
#ifndef __INT_FAST8_TYPE__
#ifdef __SIZEOF_INT_FAST8_T__
#define __INT_FAST8_TYPE__ __TYPEFOR_INTIB(__SIZEOF_INT_FAST8_T__)
#endif /* __SIZEOF_INT_FAST8_T__ */
#endif /* !__INT_FAST8_TYPE__ */
#ifndef __INT_FAST16_TYPE__
#ifdef __SIZEOF_INT_FAST16_T__
#define __INT_FAST16_TYPE__ __TYPEFOR_INTIB(__SIZEOF_INT_FAST16_T__)
#endif /* __SIZEOF_INT_FAST16_T__ */
#endif /* !__INT_FAST16_TYPE__ */
#ifndef __INT_FAST32_TYPE__
#ifdef __SIZEOF_INT_FAST32_T__
#define __INT_FAST32_TYPE__ __TYPEFOR_INTIB(__SIZEOF_INT_FAST32_T__)
#endif /* __SIZEOF_INT_FAST32_T__ */
#endif /* !__INT_FAST32_TYPE__ */
#ifndef __INT_FAST64_TYPE__
#ifdef __SIZEOF_INT_FAST64_T__
#define __INT_FAST64_TYPE__ __TYPEFOR_INTIB(__SIZEOF_INT_FAST64_T__)
#endif /* __SIZEOF_INT_FAST64_T__ */
#endif /* !__INT_FAST64_TYPE__ */
#ifndef __UINT_FAST8_TYPE__
#ifdef __SIZEOF_INT_FAST8_T__
#define __UINT_FAST8_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_INT_FAST8_T__)
#endif /* __SIZEOF_INT_FAST8_T__ */
#endif /* !__UINT_FAST8_TYPE__ */
#ifndef __UINT_FAST16_TYPE__
#ifdef __SIZEOF_INT_FAST16_T__
#define __UINT_FAST16_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_INT_FAST16_T__)
#endif /* __SIZEOF_INT_FAST16_T__ */
#endif /* !__UINT_FAST16_TYPE__ */
#ifndef __UINT_FAST32_TYPE__
#ifdef __SIZEOF_INT_FAST32_T__
#define __UINT_FAST32_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_INT_FAST32_T__)
#endif /* __SIZEOF_INT_FAST32_T__ */
#endif /* !__UINT_FAST32_TYPE__ */
#ifndef __UINT_FAST64_TYPE__
#ifdef __SIZEOF_INT_FAST64_T__
#define __UINT_FAST64_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_INT_FAST64_T__)
#endif /* __SIZEOF_INT_FAST64_T__ */
#endif /* !__UINT_FAST64_TYPE__ */


#ifndef __INTPTR_TYPE__
#define __INTPTR_TYPE__ __ATTR_W64 __TYPEFOR_INTIB(__SIZEOF_POINTER__)
#endif /* !__INTPTR_TYPE__ */

#ifndef __UINTPTR_TYPE__
#define __UINTPTR_TYPE__ __ATTR_W64 __TYPEFOR_UINTIB(__SIZEOF_POINTER__)
#endif /* !__UINTPTR_TYPE__ */

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ __ATTR_W64 __TYPEFOR_UINTIB(__SIZEOF_SIZE_T__)
#endif /* !__SIZE_TYPE__ */

#ifndef __SIZEOF_INTMAX_T__
#if defined(__UINT128_TYPE__) && 0
#define __SIZEOF_INTMAX_T__ 16
#elif defined(__UINT64_TYPE__)
#define __SIZEOF_INTMAX_T__ 8
#elif defined(__UINT32_TYPE__)
#define __SIZEOF_INTMAX_T__ 4
#elif defined(__UINT16_TYPE__)
#define __SIZEOF_INTMAX_T__ 2
#elif defined(__SIZEOF_LONG_LONG__)
#define __SIZEOF_INTMAX_T__ __SIZEOF_LONG_LONG__
#else /* ... */
#define __SIZEOF_INTMAX_T__ __SIZEOF_LONG__
#endif /* !... */
#endif /* !__SIZEOF_INTMAX_T__ */

#ifndef __UINTMAX_TYPE__
#if __SIZEOF_INTMAX_T__ == 16
#define __INTMAX_TYPE__  __INT128_TYPE__
#define __UINTMAX_TYPE__ __UINT128_TYPE__
#elif __SIZEOF_INTMAX_T__ == 8
#define __INTMAX_TYPE__  __INT64_TYPE__
#define __UINTMAX_TYPE__ __UINT64_TYPE__
#elif __SIZEOF_INTMAX_T__ == 4
#define __INTMAX_TYPE__  __INT32_TYPE__
#define __UINTMAX_TYPE__ __UINT32_TYPE__
#elif __SIZEOF_INTMAX_T__ == 2
#define __INTMAX_TYPE__  __INT16_TYPE__
#define __UINTMAX_TYPE__ __UINT16_TYPE__
#elif __SIZEOF_INTMAX_T__ == 1
#define __INTMAX_TYPE__  __INT8_TYPE__
#define __UINTMAX_TYPE__ __UINT8_TYPE__
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
#define __INTMAX_TYPE__  __LONGLONG
#define __UINTMAX_TYPE__ __ULONGLONG
#elif __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
#define __INTMAX_TYPE__  long
#define __UINTMAX_TYPE__ long
#else /* ... */
#error "Unsupported __SIZEOF_INTMAX_T__"
#endif /* !... */
#endif /* !__UINTMAX_TYPE__ */

#if ((__SIZEOF_LONG__ == __SIZEOF_POINTER__) && \
     (!defined(__x86_64__) || !defined(__INTELLISENSE__)))
#define __LONGPTR_TYPE__  __ATTR_W64 signed long
#define __ULONGPTR_TYPE__ __ATTR_W64 unsigned long
#else /* __SIZEOF_LONG__ == __SIZEOF_POINTER__ && ... */
#define __LONGPTR_TYPE__  __INTPTR_TYPE__
#define __ULONGPTR_TYPE__ __UINTPTR_TYPE__
#endif /* __SIZEOF_LONG__ != __SIZEOF_POINTER__ || !... */


#if __SIZEOF_POINTER__ <= 2
#define __SIZEOF_INTPTR_HALF_T__ 1
#define __INTPTR_HALF_TYPE__  __INT8_TYPE__
#define __UINTPTR_HALF_TYPE__ __UINT8_TYPE__
#elif __SIZEOF_POINTER__ <= 4
#define __SIZEOF_INTPTR_HALF_T__ 2
#define __SIZEOF_INTPTR_QUARTER_T__ 1
#define __INTPTR_HALF_TYPE__     __INT16_TYPE__
#define __UINTPTR_HALF_TYPE__    __UINT16_TYPE__
#define __INTPTR_QUARTER_TYPE__  __INT8_TYPE__
#define __UINTPTR_QUARTER_TYPE__ __UINT8_TYPE__
#else /* __SIZEOF_POINTER__ <= ... */
#define __SIZEOF_INTPTR_HALF_T__ 4
#define __SIZEOF_INTPTR_QUARTER_T__ 2
#define __INTPTR_HALF_TYPE__     __INT32_TYPE__
#define __UINTPTR_HALF_TYPE__    __UINT32_TYPE__
#define __INTPTR_QUARTER_TYPE__  __INT16_TYPE__
#define __UINTPTR_QUARTER_TYPE__ __UINT16_TYPE__
#endif /* __SIZEOF_POINTER__ > ... */

#ifndef __BYTE_TYPE__
#define __SBYTE_TYPE__ __TYPEFOR_INTIB1
#define __BYTE_TYPE__  __TYPEFOR_UINTIB1
#endif /* !__BYTE_TYPE__ */

#ifndef __WCHAR_TYPE__
#if defined(__native_wchar_t_defined) || defined(__cplusplus)
#define __WCHAR_TYPE__ wchar_t
#elif defined(__WCHAR_UNSIGNED__)
#define __WCHAR_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_WCHAR_T__)
#else /* ... */
#define __WCHAR_TYPE__ __TYPEFOR_INTIB(__SIZEOF_WCHAR_T__)
#endif /* !... */
#elif (defined(__cplusplus) &&              \
       defined(__native_wchar_t_defined) && \
       defined(__KOS_SYSTEM_HEADERS__))
/*  g++ Seems to pre-define `__WCHAR_TYPE__' incorrectly as its integral value
 * (the same way it does in C; `#define __WCHAR_TYPE__ int'), so fix it here... */
#undef __WCHAR_TYPE__
#define __WCHAR_TYPE__ wchar_t
#endif /* ... */

#ifndef __WCHAR16_TYPE__
#if __SIZEOF_WCHAR_T__ == 2
#define __WCHAR16_TYPE__ __WCHAR_TYPE__
#elif defined(__WCHAR_UNSIGNED__)
#define __WCHAR16_TYPE__ __UINT16_TYPE__
#else /* ... */
#define __WCHAR16_TYPE__ __INT16_TYPE__
#endif /* !... */
#endif /* !__WCHAR16_TYPE__ */

#ifndef __WCHAR32_TYPE__
#if __SIZEOF_WCHAR_T__ == 4
#define __WCHAR32_TYPE__ __WCHAR_TYPE__
#elif defined(__WCHAR_UNSIGNED__)
#define __WCHAR32_TYPE__ __UINT32_TYPE__
#else /* ... */
#define __WCHAR32_TYPE__ __INT32_TYPE__
#endif /* !... */
#endif /* !__WCHAR32_TYPE__ */

#ifndef __WINT_TYPE__
#ifdef __WINT_UNSIGNED__
#define __WINT_TYPE__  __TYPEFOR_UINTIB(__SIZEOF_WINT_T__)
#else /* __WINT_UNSIGNED__ */
#define __WINT_TYPE__  __TYPEFOR_INTIB(__SIZEOF_WINT_T__)
#endif /* !__WINT_UNSIGNED__ */
#endif /* !__WINT_TYPE__ */

#ifndef __WINT16_TYPE__
#if __SIZEOF_WINT_T__ == 2
#define __WINT16_TYPE__ __WINT_TYPE__
#elif defined(__WINT_UNSIGNED__)
#define __WINT16_TYPE__ __UINT16_TYPE__
#else /* ... */
#define __WINT16_TYPE__ __INT16_TYPE__
#endif /* !... */
#endif /* !__WINT16_TYPE__ */

#ifndef __WINT32_TYPE__
#if __SIZEOF_WINT_T__ == 4
#define __WINT32_TYPE__ __WINT_TYPE__
#elif defined(__WINT_UNSIGNED__)
#define __WINT32_TYPE__ __UINT32_TYPE__
#else /* ... */
#define __WINT32_TYPE__ __INT32_TYPE__
#endif /* !... */
#endif /* !__WINT32_TYPE__ */

#ifndef __CHAR16_TYPE__
#define __CHAR16_TYPE__ __UINT16_TYPE__
#endif /* !__CHAR16_TYPE__ */
#ifndef __CHAR32_TYPE__
#define __CHAR32_TYPE__ __UINT32_TYPE__
#endif /* !__CHAR32_TYPE__ */

/* Most efficient type to-be used as RHS-operator of shift operations. */
#ifndef __SHIFT_TYPE__
#define __SIZEOF_SHIFT_T__ 1
#define __SHIFT_TYPE__     __UINT8_TYPE__
#endif /* !__SHIFT_TYPE__ */

#ifndef __SIG_ATOMIC_TYPE__
#define __SIG_ATOMIC_TYPE__ int
#endif /* !__SIG_ATOMIC_TYPE__ */

#ifndef __SIZEOF_FLOAT__
#define __SIZEOF_FLOAT__  4
#endif /* !__SIZEOF_FLOAT__ */
#ifndef __SIZEOF_DOUBLE__
#define __SIZEOF_DOUBLE__ 8
#endif /* !__SIZEOF_DOUBLE__ */

#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#define __INTSIZE_TYPE__  __ATTR_W64 unsigned int
#define __INTSSIZE_TYPE__ __ATTR_W64 signed int
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
#define __INTSIZE_TYPE__  __SIZE_TYPE__
#define __INTSSIZE_TYPE__ __SSIZE_TYPE__
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */

#if __SIZEOF_LONG__ == __SIZEOF_SIZE_T__
#define __LONGSIZE_TYPE__  __ATTR_W64 unsigned long int
#define __LONGSSIZE_TYPE__ __ATTR_W64 signed long int
#else /* __SIZEOF_LONG__ == __SIZEOF_SIZE_T__ */
#define __LONGSIZE_TYPE__  __SIZE_TYPE__
#define __LONGSSIZE_TYPE__ __SSIZE_TYPE__
#endif /* __SIZEOF_LONG__ != __SIZEOF_SIZE_T__ */

#if __SIZEOF_LONG__ == 4
#define __LONG32_TYPE__  signed long int
#define __ULONG32_TYPE__ unsigned long int
#else /* __SIZEOF_LONG__ == 4 */
#define __LONG32_TYPE__  __INT32_TYPE__
#define __ULONG32_TYPE__ __UINT32_TYPE__
#endif /* __SIZEOF_LONG__ != 4 */

#if __SIZEOF_LONG__ == 8
#ifdef __INTELLISENSE_GCC__
#define __LONG64_TYPE__  signed long long int
#define __ULONG64_TYPE__ unsigned long long int
#else /* __INTELLISENSE_GCC__ */
#define __LONG64_TYPE__  signed long int
#define __ULONG64_TYPE__ unsigned long int
#endif /* !__INTELLISENSE_GCC__ */
#else /* __SIZEOF_LONG__ == 8 */
#define __LONG64_TYPE__  __INT64_TYPE__
#define __ULONG64_TYPE__ __UINT64_TYPE__
#endif /* __SIZEOF_LONG__ != 8 */

/* The max integral type that the target's main address bus is optimized for.
 * Currently,  that   is  equal   to   `sizeof(void *)'  for   all   targets. */
#ifndef __SIZEOF_BUSINT__
#define __SIZEOF_BUSINT__ __SIZEOF_POINTER__
#define __BUSINT_TYPE__   __INTPTR_TYPE__
#define __UBUSIINT_TYPE__ __UINTPTR_TYPE__
#endif /* !__SIZEOF_BUSINT__ */

/* General-purpose register type.
 * Currently, that is equal to `sizeof(void *)' for all targets. */
#ifndef __SIZEOF_REGISTER__
#define __SIZEOF_REGISTER__  __SIZEOF_POINTER__
#define __REGISTER_TYPE__    __ULONGPTR_TYPE__
#define __SREGISTER_TYPE__   __LONGPTR_TYPE__
#endif /* !__SIZEOF_REGISTER__ */

#ifdef __UINT128_TYPE__
#ifndef __ALIGNOF_INT128__
#define __ALIGNOF_INT128__ 16
#endif /* !__ALIGNOF_INT128__ */
#endif /* __UINT128_TYPE__ */

#ifdef __UINT64_TYPE__
#ifndef __ALIGNOF_INT64__
#if !defined(_MSC_VER) && !defined(__INTELLISENSE__)
#include "host.h"
#if defined(__i386__) && !defined(__x86_64__)
/* On i386,  `-mno-align-double' is  the ABI  default, which  causes  `long long'
 * and  `double'  to  have  4-byte  alignment,  rather  than  be  8-byte aligned!
 * s.a. `https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html#index-malign-double' */
#define __ALIGNOF_INT64__ 4
#endif /* __i386__ && !__x86_64__ */
#endif /* __GNUC__ && !__INTELLISENSE__ */
#ifndef __ALIGNOF_INT64__
#define __ALIGNOF_INT64__ 8
#endif /* !__ALIGNOF_INT64__ */
#endif /* !__ALIGNOF_INT64__ */
#endif /* __UINT64_TYPE__ */

#ifndef __ALIGNOF_INT32__
#define __ALIGNOF_INT32__ 4
#endif /* !__ALIGNOF_INT32__ */

#ifndef __ALIGNOF_INT16__
#if defined(__COMPILER_HAVE_DOUBLE_WIDE_REGISTERS) && __SIZEOF_REGISTER__ < 2
#define __ALIGNOF_INT16__ __SIZEOF_REGISTER__
#else /* __SIZEOF_REGISTER__ < 2 */
#define __ALIGNOF_INT16__ 2
#endif /* __SIZEOF_REGISTER__ >= 2 */
#endif /* !__ALIGNOF_INT16__ */

#ifndef __ALIGNOF_INT8__
#define __ALIGNOF_INT8__ 1
#endif /* !__ALIGNOF_INT8__ */

#ifndef __ALIGNOF_FLOAT__
#define __ALIGNOF_FLOAT__ __SIZEOF_FLOAT__
#endif /* !__ALIGNOF_FLOAT__ */

#if !defined(__ALIGNOF_DOUBLE__) && defined(__SIZEOF_DOUBLE__)
#ifdef _DOUBLE_ALIGNMENT
#define __ALIGNOF_DOUBLE__ _DOUBLE_ALIGNMENT
#elif __SIZEOF_DOUBLE__ == 8
#define __ALIGNOF_DOUBLE__ __ALIGNOF_INT64__
#else /* __SIZEOF_DOUBLE__ == 8 */
#define __ALIGNOF_DOUBLE__ __SIZEOF_DOUBLE__
#endif /* __SIZEOF_DOUBLE__ != 8 */
#endif /* !__ALIGNOF_DOUBLE__ && __SIZEOF_DOUBLE__ */

#ifndef __SIZEOF_LONG_DOUBLE__
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef _MSC_VER
#define __SIZEOF_LONG_DOUBLE__ 8
#elif (defined(__C67__) || defined(__i386__) || \
       defined(__i386) || defined(i386) ||      \
       defined(__I86__) || defined(_M_IX86) ||  \
       defined(__X86__) || defined(_X86_) ||    \
       defined(__THW_INTEL__) || defined(__INTEL__))
#define __SIZEOF_LONG_DOUBLE__ 12
#elif (defined(__X86_64__) || defined(__amd64__) || \
       defined(__amd64) || defined(__x86_64) || \
       defined(_M_X64) || defined(_M_AMD64) || \
       defined(_WIN64) || defined(WIN64))
#define __SIZEOF_LONG_DOUBLE__ 16
#elif (defined(__arm__) || defined(_M_ARM) || \
       defined(_M_ARMT) || defined(_M_ARM_NT))
#define __SIZEOF_LONG_DOUBLE__ 8
#else /* ... */
#define __SIZEOF_LONG_DOUBLE__ 8
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__SIZEOF_LONG_DOUBLE__ */


#ifdef __SIZEOF_LONG_DOUBLE__
#undef __ARCH_LONG_DOUBLE_IS_DOUBLE
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
#define __ARCH_LONG_DOUBLE_IS_DOUBLE
#endif /* __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__ */

#ifndef __ALIGNOF_LONG_DOUBLE__
#ifdef _LONG_DOUBLE_ALIGNMENT
#define __ALIGNOF_LONG_DOUBLE__ _LONG_DOUBLE_ALIGNMENT
#elif __ALIGNOF_INT64__ < 8
#define __ALIGNOF_LONG_DOUBLE__ __ALIGNOF_INT64__
#elif defined(__INTELLISENSE_GCC__) && defined(__i386__)
#define __ALIGNOF_LONG_DOUBLE__ 4
#elif __SIZEOF_LONG_DOUBLE__ == 12
#define __ALIGNOF_LONG_DOUBLE__ 16
#else /* __SIZEOF_LONG_DOUBLE__ == 12 */
#define __ALIGNOF_LONG_DOUBLE__ __SIZEOF_LONG_DOUBLE__
#endif /* __SIZEOF_LONG_DOUBLE__ != 12 */
#endif /* !__ALIGNOF_LONG_DOUBLE__ */
#endif /* __SIZEOF_LONG_DOUBLE__ */

#if !defined(__ALIGNOF_LONG_LONG__) && defined(__SIZEOF_LONG_LONG__)
#ifdef _LONG_LONG_ALIGNMENT
#define __ALIGNOF_LONG_LONG__ _LONG_LONG_ALIGNMENT
#elif __SIZEOF_LONG_LONG__ == 8
#define __ALIGNOF_LONG_LONG__ __ALIGNOF_INT64__
#elif __SIZEOF_LONG_LONG__ == 4
#define __ALIGNOF_LONG_LONG__ __ALIGNOF_INT32__
#elif __SIZEOF_LONG_LONG__ == 2
#define __ALIGNOF_LONG_LONG__ __ALIGNOF_INT16__
#else /* __SIZEOF_LONG_LONG__ == ... */
#define __ALIGNOF_LONG_LONG__ __SIZEOF_LONG_LONG__
#endif /* __SIZEOF_LONG_LONG__ != ... */
#endif /* !__ALIGNOF_LONG_LONG__ && __SIZEOF_LONG_LONG__ */

#ifndef __ALIGNOF_LONG__
#ifdef _LONG_ALIGNMENT
#define __ALIGNOF_LONG__ _LONG_ALIGNMENT
#elif __SIZEOF_LONG__ == 8
#define __ALIGNOF_LONG__ __ALIGNOF_INT64__
#elif __SIZEOF_LONG__ == 4
#define __ALIGNOF_LONG__ __ALIGNOF_INT32__
#elif __SIZEOF_LONG__ == 2
#define __ALIGNOF_LONG__ __ALIGNOF_INT16__
#else /* __SIZEOF_LONG__ == ... */
#define __ALIGNOF_LONG__ __SIZEOF_LONG__
#endif /* __SIZEOF_LONG__ != ... */
#endif /* !__ALIGNOF_LONG__ */

#ifndef __ALIGNOF_INT__
#ifdef _INT_ALIGNMENT
#define __ALIGNOF_INT__ _INT_ALIGNMENT
#elif __SIZEOF_INT__ == 4
#define __ALIGNOF_INT__ __ALIGNOF_INT32__
#elif __SIZEOF_INT__ == 2
#define __ALIGNOF_INT__ __ALIGNOF_INT16__
#elif __SIZEOF_INT__ == 8
#define __ALIGNOF_INT__ __ALIGNOF_INT64__
#else /* __SIZEOF_INT__ == ... */
#define __ALIGNOF_INT__ __SIZEOF_INT__
#endif /* __SIZEOF_INT__ != ... */
#endif /* !__ALIGNOF_INT__ */

#ifndef __ALIGNOF_SHORT__
#ifdef _SHORT_ALIGNMENT
#define __ALIGNOF_SHORT__ _SHORT_ALIGNMENT
#elif __SIZEOF_SHORT__ == 2
#define __ALIGNOF_SHORT__ __ALIGNOF_INT16__
#elif __SIZEOF_SHORT__ == 4
#define __ALIGNOF_SHORT__ __ALIGNOF_INT32__
#elif __SIZEOF_SHORT__ == 8
#define __ALIGNOF_SHORT__ __ALIGNOF_INT64__
#else /* __SIZEOF_SHORT__ == ... */
#define __ALIGNOF_SHORT__ __SIZEOF_SHORT__
#endif /* __SIZEOF_SHORT__ != ... */
#endif /* !__ALIGNOF_SHORT__ */

#ifndef __ALIGNOF_CHAR__
#ifdef _CHAR_ALIGNMENT
#define __ALIGNOF_CHAR__ _CHAR_ALIGNMENT
#else /* _CHAR_ALIGNMENT */
#define __ALIGNOF_CHAR__ __SIZEOF_CHAR__
#endif /* !_CHAR_ALIGNMENT */
#endif /* !__ALIGNOF_CHAR__ */

#ifndef __ALIGNOF_POINTER__
#ifdef _POINTER_ALIGNMENT
#define __ALIGNOF_POINTER__ _POINTER_ALIGNMENT
#else /* _POINTER_ALIGNMENT */
#define __ALIGNOF_POINTER__ __SIZEOF_POINTER__
#endif /* !_POINTER_ALIGNMENT */
#endif /* !__ALIGNOF_POINTER__ */

#ifndef __ALIGNOF_WCHAR_T__
#if __SIZEOF_WCHAR_T__ == 2
#define __ALIGNOF_WCHAR_T__ __ALIGNOF_INT16__
#elif __SIZEOF_WCHAR_T__ == 4
#define __ALIGNOF_WCHAR_T__ __ALIGNOF_INT32__
#elif __SIZEOF_WCHAR_T__ == 8
#define __ALIGNOF_WCHAR_T__ __ALIGNOF_INT64__
#else /* __SIZEOF_WCHAR_T__ == ... */
#define __ALIGNOF_WCHAR_T__ __SIZEOF_WCHAR_T__
#endif /* __SIZEOF_WCHAR_T__ != ... */
#endif /* !__ALIGNOF_WCHAR_T__ */






#ifndef __MAX_ALIGN_TYPE__
#define __MAX_ALIGN_TYPE__ __LONGDOUBLE
#ifdef _MAX_ALIGNMENT
#define __ALIGNOF_MAX_ALIGN_T__ _MAX_ALIGNMENT
#define __SIZEOF_MAX_ALIGN_T__  _MAX_ALIGNMENT
#elif defined(__BIGGEST_ALIGNMENT__)
#define __ALIGNOF_MAX_ALIGN_T__ __BIGGEST_ALIGNMENT__
#define __SIZEOF_MAX_ALIGN_T__  __BIGGEST_ALIGNMENT__
#elif defined(__ALIGNOF_LONG_DOUBLE__)
#define __ALIGNOF_MAX_ALIGN_T__ __ALIGNOF_LONG_DOUBLE__
#define __SIZEOF_MAX_ALIGN_T__  __ALIGNOF_LONG_DOUBLE__
#else /* ... */
#define __ALIGNOF_MAX_ALIGN_T__ 8
#define __SIZEOF_MAX_ALIGN_T__  8
#endif /* !... */
#endif /* !__MAX_ALIGN_TYPE__ */



#define __ALIGNOF_INTN_1 __ALIGNOF_INT8__
#define __ALIGNOF_INTN_2 __ALIGNOF_INT16__
#define __ALIGNOF_INTN_4 __ALIGNOF_INT32__
#ifdef __ALIGNOF_INT64__
#define __ALIGNOF_INTN_8 __ALIGNOF_INT64__
#endif /* __ALIGNOF_INT64__ */
#ifdef __ALIGNOF_INT128__
#define __ALIGNOF_INTN_16 __ALIGNOF_INT128__
#endif /* __ALIGNOF_INT128__ */
#define __ALIGNOF_INTN2(sizeof) __ALIGNOF_INTN_##sizeof
#define __ALIGNOF_INTN(sizeof) __ALIGNOF_INTN2(sizeof)


#if (defined(_NATIVE_CHAR16_T_DEFINED) ||                                                                               \
     (defined(__cpp_unicode_characters) && __cpp_unicode_characters + 0 >= 200704) ||                                   \
     (defined(_HAS_CHAR16_T_LANGUAGE_SUPPORT) && _HAS_CHAR16_T_LANGUAGE_SUPPORT + 0) ||                                 \
     (defined(__cplusplus) &&                                                                                           \
      (defined(__CODEGEARC__) || (defined(_MSC_VER) && _MSC_VER + 0 >= 1900) ||                                         \
       (defined(__clang__) && !defined(_MSC_VER) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)) || \
       (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GCC_VERSION_NUM >= 40400) ||                                           \
       (defined(__BORLANDC__) && defined(__CODEGEAR_0X_SUPPORT__) && __BORLANDC__ + 0 >= 0x610) ||                      \
       (defined(__IBMCPP_UTF_LITERAL__) && __IBMCPP_UTF_LITERAL__))))
/* The compiler is pre-defining the `char16_t' / `char32_t' types. */
#undef __CHAR16_TYPE__
#undef __CHAR32_TYPE__
#define __CHAR16_TYPE__ char16_t
#define __CHAR32_TYPE__ char32_t
#define __char16_t_defined
#define __native_char16_t_defined
#endif /* ... */


#ifdef __INTELLISENSE__
/* Don't  #define   builtin   keywords   with   Intellisense.
 * Sometimes, Intellisense doesn't  notice when those  macros
 * get deleted  and will  continue chugging  along as  though
 * they were still defined (leading to sporadic syntax errors
 * in arbitrary source files...) */

#ifdef __x86_64__
#define __SIZE_TYPE_IS_LONG_LONG__ /* Should be `long' for elf, but isn't */
#define __PTRDIFF_TYPE_IS_LONG_LONG__
#define __INTPTR_TYPE_IS_LONG_LONG__ /* Should be `long' for elf, but isn't */
#elif defined(__i386__)
#define __SIZE_TYPE_IS_INT__ /* Should be `long' for elf, but isn't */
#define __PTRDIFF_TYPE_IS_INT__
#define __INTPTR_TYPE_IS_INT__ /* Should be `long' for elf, but isn't */
#elif __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#define __SIZE_TYPE_IS_INT__
#define __PTRDIFF_TYPE_IS_INT__
#define __INTPTR_TYPE_IS_INT__
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
#define __SIZE_TYPE_IS_LONG_LONG__
#define __PTRDIFF_TYPE_IS_LONG__
#define __INTPTR_TYPE_IS_LONG__
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */

#define __INT8_TYPE_IS_CHAR__
#define __INT16_TYPE_IS_SHORT__
#if __SIZEOF_INT__ == 4
#define __INT32_TYPE_IS_INT__
#elif __SIZEOF_LONG__ == 4
#define __INT32_TYPE_IS_LONG__
#endif /* ... */
#if __SIZEOF_LONG__ == 8
#define __INT64_TYPE_IS_LONG__
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ == 8
#define __INT64_TYPE_IS_LONG_LONG__
#endif /* ... */

#else /* __INTELLISENSE__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("char")
#pragma push_macro("short")
#pragma push_macro("int")
#pragma push_macro("long")
#pragma push_macro("signed")
#pragma push_macro("unsigned")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef char
#undef short
#undef int
#undef long
#undef signed
#undef unsigned
#undef __longlong_t
#undef __ulonglong_t
#ifndef __NO_ATTR_W64
#undef __w64
#endif /* !__NO_ATTR_W64 */

#define unsigned +1
#define signed   +1
#define int      +2
#define long     +4
#define short    +16
#define char     +32
#define __longlong_t  +9 /* signed long long */
#define __ulonglong_t +9 /* unsigned long long */
#ifndef __int8
#define __HYBRID_TYPECORE_DEFINES_INT8
#define __int8   +64
#endif /* !__int8 */
#ifndef __int16
#define __HYBRID_TYPECORE_DEFINES_INT16
#define __int16  +128
#endif /* !__int16 */
#ifndef __int32
#define __HYBRID_TYPECORE_DEFINES_INT32
#define __int32  +256
#endif /* !__int32 */
#ifndef __int64
#define __HYBRID_TYPECORE_DEFINES_INT64
#define __int64  +512
#endif /* !__int64 */
#ifndef __int128
#define __HYBRID_TYPECORE_DEFINES_INT128
#define __int128 +1024
#endif /* !__int128 */
#ifndef __NO_ATTR_W64
#define __w64 +0
#endif /* !__NO_ATTR_W64 */

#define __T_ISCHAR(T)   ((0 T) & ~1) == 32         /* [signed|unsigned] char */
#define __T_ISSHORT(T)  ((0 T) & ~3) == 16         /* [signed|unsigned] short [int] */
#define __T_ISINT(T)    ((0 T) >= 1 && (0 T) <= 3) /* signed | unsigned | int | signed int | unsigned int */
#define __T_ISLONG(T)   ((0 T) & ~3) == 4          /* [signed|unsigned] long [int] */
#define __T_ISLLONG(T)  ((0 T) & ~3) == 8          /* [signed|unsigned] long long [int] */
#define __T_ISINT8(T)   ((0 T) & ~1) == 64         /* [signed|unsigned] __int8 */
#define __T_ISINT16(T)  ((0 T) & ~1) == 128        /* [signed|unsigned] __int16 */
#define __T_ISINT32(T)  ((0 T) & ~1) == 256        /* [signed|unsigned] __int32 */
#define __T_ISINT64(T)  ((0 T) & ~1) == 512        /* [signed|unsigned] __int64 */
#define __T_ISINT128(T) ((0 T) & ~1) == 1024       /* [signed|unsigned] __int128 */

#ifdef __INT8_TYPE__
#if __T_ISCHAR(__INT8_TYPE__)
#define __INT8_TYPE_IS_CHAR__
#elif __T_ISSHORT(__INT8_TYPE__)
#define __INT8_TYPE_IS_SHORT__
#elif __T_ISINT(__INT8_TYPE__)
#define __INT8_TYPE_IS_INT__
#elif __T_ISLONG(__INT8_TYPE__)
#define __INT8_TYPE_IS_LONG__
#elif __T_ISLLONG(__INT8_TYPE__)
#define __INT8_TYPE_IS_LONG_LONG__
#elif __T_ISINT8(__INT8_TYPE__)
#ifndef __COMPILER_INT8_IS_UNIQUE_TYPE
/* Must guess the most likely type */
#if __SIZEOF_CHAR__ == 1
#define __INT8_TYPE_IS_CHAR__
#elif __SIZEOF_SHORT__ == 1
#define __INT8_TYPE_IS_SHORT__
#elif __SIZEOF_INT__ == 1
#define __INT8_TYPE_IS_INT__
#elif __SIZEOF_LONG__ == 1
#define __INT8_TYPE_IS_LONG__
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ == 1
#define __INT8_TYPE_IS_LONG_LONG__
#endif /* __SIZEOF_...__ == 1 */
#endif /* !__COMPILER_INT8_IS_UNIQUE_TYPE */
#endif /* ... */
#endif /* __INT8_TYPE__ */

#ifdef __INT16_TYPE__
#if __T_ISSHORT(__INT16_TYPE__)
#define __INT16_TYPE_IS_SHORT__
#elif __T_ISINT(__INT16_TYPE__)
#define __INT16_TYPE_IS_INT__
#elif __T_ISLONG(__INT16_TYPE__)
#define __INT16_TYPE_IS_LONG__
#elif __T_ISLLONG(__INT16_TYPE__)
#define __INT16_TYPE_IS_LONG_LONG__
#elif __T_ISCHAR(__INT16_TYPE__)
#define __INT16_TYPE_IS_CHAR__
#elif __T_ISINT16(__INT16_TYPE__)
#ifndef __COMPILER_INT16_IS_UNIQUE_TYPE
/* Must guess the most likely type */
#if __SIZEOF_SHORT__ == 2
#define __INT16_TYPE_IS_SHORT__
#elif __SIZEOF_INT__ == 2
#define __INT16_TYPE_IS_INT__
#elif __SIZEOF_LONG__ == 2
#define __INT16_TYPE_IS_LONG__
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ == 2
#define __INT16_TYPE_IS_LONG_LONG__
#elif __SIZEOF_CHAR__ == 2
#define __INT16_TYPE_IS_CHAR__
#endif /* __SIZEOF_...__ == 2 */
#endif /* !__COMPILER_INT16_IS_UNIQUE_TYPE */
#endif /* ... */
#endif /* __INT16_TYPE__ */

#ifdef __INT32_TYPE__
#if __T_ISINT(__INT32_TYPE__)
#define __INT32_TYPE_IS_INT__
#elif __T_ISLONG(__INT32_TYPE__)
#define __INT32_TYPE_IS_LONG__
#elif __T_ISLLONG(__INT32_TYPE__)
#define __INT32_TYPE_IS_LONG_LONG__
#elif __T_ISSHORT(__INT32_TYPE__)
#define __INT32_TYPE_IS_SHORT__
#elif __T_ISCHAR(__INT32_TYPE__)
#define __INT32_TYPE_IS_CHAR__
#elif __T_ISINT32(__INT32_TYPE__)
#ifndef __COMPILER_INT32_IS_UNIQUE_TYPE
/* Must guess the most likely type */
#if __SIZEOF_INT__ == 4
#define __INT32_TYPE_IS_INT__
#elif __SIZEOF_LONG__ == 4
#define __INT32_TYPE_IS_LONG__
#elif __SIZEOF_SHORT__ == 4
#define __INT32_TYPE_IS_SHORT__
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ == 4
#define __INT32_TYPE_IS_LONG_LONG__
#elif __SIZEOF_CHAR__ == 4
#define __INT32_TYPE_IS_CHAR__
#endif /* __SIZEOF_...__ == 4 */
#endif /* !__COMPILER_INT32_IS_UNIQUE_TYPE */
#endif /* ... */
#endif /* __INT32_TYPE__ */

#ifdef __INT64_TYPE__
#if __T_ISLONG(__INT64_TYPE__)
#define __INT64_TYPE_IS_LONG__
#elif __T_ISLLONG(__INT64_TYPE__)
#define __INT64_TYPE_IS_LONG_LONG__
#elif __T_ISINT(__INT64_TYPE__)
#define __INT64_TYPE_IS_INT__
#elif __T_ISSHORT(__INT64_TYPE__)
#define __INT64_TYPE_IS_SHORT__
#elif __T_ISCHAR(__INT64_TYPE__)
#define __INT64_TYPE_IS_CHAR__
#elif __T_ISINT64(__INT64_TYPE__)
#ifndef __COMPILER_INT64_IS_UNIQUE_TYPE
/* Must guess the most likely type */
#if __SIZEOF_LONG__ == 8
#define __INT64_TYPE_IS_LONG__
#elif defined(__SIZEOF_LONG_LONG__) && __SIZEOF_LONG_LONG__ == 8
#define __INT64_TYPE_IS_LONG_LONG__
#elif __SIZEOF_INT__ == 8
#define __INT64_TYPE_IS_INT__
#elif __SIZEOF_SHORT__ == 8
#define __INT64_TYPE_IS_SHORT__
#elif __SIZEOF_CHAR__ == 8
#define __INT64_TYPE_IS_CHAR__
#endif /* __SIZEOF_...__ == 8 */
#endif /* !__COMPILER_INT64_IS_UNIQUE_TYPE */
#endif /* ... */
#endif /* __INT64_TYPE__ */

#if __T_ISINT(__SIZE_TYPE__)
#define __SIZE_TYPE_IS_INT__
#elif __T_ISLONG(__SIZE_TYPE__)
#define __SIZE_TYPE_IS_LONG__
#elif __T_ISLLONG(__SIZE_TYPE__)
#define __SIZE_TYPE_IS_LONG_LONG__
#elif __T_ISSHORT(__SIZE_TYPE__)
#define __SIZE_TYPE_IS_SHORT__
#elif __T_ISCHAR(__SIZE_TYPE__)
#define __SIZE_TYPE_IS_CHAR__
#elif __T_ISINT8(__SIZE_TYPE__)
#ifdef __INT8_TYPE_IS_CHAR__
#define __SIZE_TYPE_IS_CHAR__
#elif defined(__INT8_TYPE_IS_SHORT__)
#define __SIZE_TYPE_IS_SHORT__
#elif defined(__INT8_TYPE_IS_INT__)
#define __SIZE_TYPE_IS_INT__
#elif defined(__INT8_TYPE_IS_LONG__)
#define __SIZE_TYPE_IS_LONG__
#elif defined(__INT8_TYPE_IS_LONG_LONG__)
#define __SIZE_TYPE_IS_LONG_LONG__
#endif /* __INT8_TYPE_IS_...__ */
#elif __T_ISINT16(__SIZE_TYPE__)
#ifdef __INT16_TYPE_IS_SHORT__
#define __SIZE_TYPE_IS_SHORT__
#elif defined(__INT16_TYPE_IS_INT__)
#define __SIZE_TYPE_IS_INT__
#elif defined(__INT16_TYPE_IS_CHAR__)
#define __SIZE_TYPE_IS_CHAR__
#elif defined(__INT16_TYPE_IS_LONG__)
#define __SIZE_TYPE_IS_LONG__
#elif defined(__INT16_TYPE_IS_LONG_LONG__)
#define __SIZE_TYPE_IS_LONG_LONG__
#endif /* __INT16_TYPE_IS_...__ */
#elif __T_ISINT32(__SIZE_TYPE__)
#ifdef __INT32_TYPE_IS_INT__
#define __SIZE_TYPE_IS_INT__
#elif defined(__INT32_TYPE_IS_LONG__)
#define __SIZE_TYPE_IS_LONG__
#elif defined(__INT32_TYPE_IS_SHORT__)
#define __SIZE_TYPE_IS_SHORT__
#elif defined(__INT32_TYPE_IS_CHAR__)
#define __SIZE_TYPE_IS_CHAR__
#elif defined(__INT32_TYPE_IS_LONG_LONG__)
#define __SIZE_TYPE_IS_LONG_LONG__
#endif /* __INT32_TYPE_IS_...__ */
#elif __T_ISINT64(__SIZE_TYPE__)
#ifdef __INT64_TYPE_IS_LONG__
#define __SIZE_TYPE_IS_LONG__
#elif defined(__INT64_TYPE_IS_LONG_LONG__)
#define __SIZE_TYPE_IS_LONG_LONG__
#elif defined(__INT64_TYPE_IS_INT__)
#define __SIZE_TYPE_IS_INT__
#elif defined(__INT64_TYPE_IS_SHORT__)
#define __SIZE_TYPE_IS_SHORT__
#elif defined(__INT64_TYPE_IS_CHAR__)
#define __SIZE_TYPE_IS_CHAR__
#endif /* __INT64_TYPE_IS_...__ */
#endif /* ... */

#ifdef __PTRDIFF_TYPE__
#if __T_ISINT(__PTRDIFF_TYPE__)
#define __PTRDIFF_TYPE_IS_INT__
#elif __T_ISLONG(__PTRDIFF_TYPE__)
#define __PTRDIFF_TYPE_IS_LONG__
#elif __T_ISLLONG(__PTRDIFF_TYPE__)
#define __PTRDIFF_TYPE_IS_LONG_LONG__
#elif __T_ISSHORT(__PTRDIFF_TYPE__)
#define __PTRDIFF_TYPE_IS_SHORT__
#elif __T_ISCHAR(__PTRDIFF_TYPE__)
#define __PTRDIFF_TYPE_IS_CHAR__
#elif __T_ISINT8(__PTRDIFF_TYPE__)
#ifdef __INT8_TYPE_IS_CHAR__
#define __PTRDIFF_TYPE_IS_CHAR__
#elif defined(__INT8_TYPE_IS_SHORT__)
#define __PTRDIFF_TYPE_IS_SHORT__
#elif defined(__INT8_TYPE_IS_INT__)
#define __PTRDIFF_TYPE_IS_INT__
#elif defined(__INT8_TYPE_IS_LONG__)
#define __PTRDIFF_TYPE_IS_LONG__
#elif defined(__INT8_TYPE_IS_LONG_LONG__)
#define __PTRDIFF_TYPE_IS_LONG_LONG__
#endif /* __INT8_TYPE_IS_...__ */
#elif __T_ISINT16(__PTRDIFF_TYPE__)
#ifdef __INT16_TYPE_IS_SHORT__
#define __PTRDIFF_TYPE_IS_SHORT__
#elif defined(__INT16_TYPE_IS_INT__)
#define __PTRDIFF_TYPE_IS_INT__
#elif defined(__INT16_TYPE_IS_CHAR__)
#define __PTRDIFF_TYPE_IS_CHAR__
#elif defined(__INT16_TYPE_IS_LONG__)
#define __PTRDIFF_TYPE_IS_LONG__
#elif defined(__INT16_TYPE_IS_LONG_LONG__)
#define __PTRDIFF_TYPE_IS_LONG_LONG__
#endif /* __INT16_TYPE_IS_...__ */
#elif __T_ISINT32(__PTRDIFF_TYPE__)
#ifdef __INT32_TYPE_IS_INT__
#define __PTRDIFF_TYPE_IS_INT__
#elif defined(__INT32_TYPE_IS_LONG__)
#define __PTRDIFF_TYPE_IS_LONG__
#elif defined(__INT32_TYPE_IS_SHORT__)
#define __PTRDIFF_TYPE_IS_SHORT__
#elif defined(__INT32_TYPE_IS_CHAR__)
#define __PTRDIFF_TYPE_IS_CHAR__
#elif defined(__INT32_TYPE_IS_LONG_LONG__)
#define __PTRDIFF_TYPE_IS_LONG_LONG__
#endif /* __INT32_TYPE_IS_...__ */
#elif __T_ISINT64(__PTRDIFF_TYPE__)
#ifdef __INT64_TYPE_IS_LONG__
#define __PTRDIFF_TYPE_IS_LONG__
#elif defined(__INT64_TYPE_IS_LONG_LONG__)
#define __PTRDIFF_TYPE_IS_LONG_LONG__
#elif defined(__INT64_TYPE_IS_INT__)
#define __PTRDIFF_TYPE_IS_INT__
#elif defined(__INT64_TYPE_IS_SHORT__)
#define __PTRDIFF_TYPE_IS_SHORT__
#elif defined(__INT64_TYPE_IS_CHAR__)
#define __PTRDIFF_TYPE_IS_CHAR__
#endif /* __INT64_TYPE_IS_...__ */
#endif /* ... */
#endif /* __PTRDIFF_TYPE__ */

#ifdef __INTPTR_TYPE__
#if __T_ISINT(__INTPTR_TYPE__)
#define __INTPTR_TYPE_IS_INT__
#elif __T_ISLONG(__INTPTR_TYPE__)
#define __INTPTR_TYPE_IS_LONG__
#elif __T_ISLLONG(__INTPTR_TYPE__)
#define __INTPTR_TYPE_IS_LONG_LONG__
#elif __T_ISSHORT(__INTPTR_TYPE__)
#define __INTPTR_TYPE_IS_SHORT__
#elif __T_ISCHAR(__INTPTR_TYPE__)
#define __INTPTR_TYPE_IS_CHAR__
#elif __T_ISINT8(__INTPTR_TYPE__)
#ifdef __INT8_TYPE_IS_CHAR__
#define __INTPTR_TYPE_IS_CHAR__
#elif defined(__INT8_TYPE_IS_SHORT__)
#define __INTPTR_TYPE_IS_SHORT__
#elif defined(__INT8_TYPE_IS_INT__)
#define __INTPTR_TYPE_IS_INT__
#elif defined(__INT8_TYPE_IS_LONG__)
#define __INTPTR_TYPE_IS_LONG__
#elif defined(__INT8_TYPE_IS_LONG_LONG__)
#define __INTPTR_TYPE_IS_LONG_LONG__
#endif /* __INT8_TYPE_IS_...__ */
#elif __T_ISINT16(__INTPTR_TYPE__)
#ifdef __INT16_TYPE_IS_SHORT__
#define __INTPTR_TYPE_IS_SHORT__
#elif defined(__INT16_TYPE_IS_INT__)
#define __INTPTR_TYPE_IS_INT__
#elif defined(__INT16_TYPE_IS_CHAR__)
#define __INTPTR_TYPE_IS_CHAR__
#elif defined(__INT16_TYPE_IS_LONG__)
#define __INTPTR_TYPE_IS_LONG__
#elif defined(__INT16_TYPE_IS_LONG_LONG__)
#define __INTPTR_TYPE_IS_LONG_LONG__
#endif /* __INT16_TYPE_IS_...__ */
#elif __T_ISINT32(__INTPTR_TYPE__)
#ifdef __INT32_TYPE_IS_INT__
#define __INTPTR_TYPE_IS_INT__
#elif defined(__INT32_TYPE_IS_LONG__)
#define __INTPTR_TYPE_IS_LONG__
#elif defined(__INT32_TYPE_IS_SHORT__)
#define __INTPTR_TYPE_IS_SHORT__
#elif defined(__INT32_TYPE_IS_CHAR__)
#define __INTPTR_TYPE_IS_CHAR__
#elif defined(__INT32_TYPE_IS_LONG_LONG__)
#define __INTPTR_TYPE_IS_LONG_LONG__
#endif /* __INT32_TYPE_IS_...__ */
#elif __T_ISINT64(__INTPTR_TYPE__)
#ifdef __INT64_TYPE_IS_LONG__
#define __INTPTR_TYPE_IS_LONG__
#elif defined(__INT64_TYPE_IS_LONG_LONG__)
#define __INTPTR_TYPE_IS_LONG_LONG__
#elif defined(__INT64_TYPE_IS_INT__)
#define __INTPTR_TYPE_IS_INT__
#elif defined(__INT64_TYPE_IS_SHORT__)
#define __INTPTR_TYPE_IS_SHORT__
#elif defined(__INT64_TYPE_IS_CHAR__)
#define __INTPTR_TYPE_IS_CHAR__
#endif /* __INT64_TYPE_IS_...__ */
#endif /* ... */
#endif /* __INTPTR_TYPE__ */

#undef __T_ISINT128
#undef __T_ISINT64
#undef __T_ISINT32
#undef __T_ISINT16
#undef __T_ISINT8
#undef __T_ISLLONG
#undef __T_ISLONG
#undef __T_ISINT
#undef __T_ISSHORT
#undef __T_ISCHAR

#ifdef __HYBRID_TYPECORE_DEFINES_INT8
#undef __HYBRID_TYPECORE_DEFINES_INT8
#undef __int8
#endif /* __HYBRID_TYPECORE_DEFINES_INT8 */
#ifdef __HYBRID_TYPECORE_DEFINES_INT16
#undef __HYBRID_TYPECORE_DEFINES_INT16
#undef __int16
#endif /* __HYBRID_TYPECORE_DEFINES_INT16 */
#ifdef __HYBRID_TYPECORE_DEFINES_INT32
#undef __HYBRID_TYPECORE_DEFINES_INT32
#undef __int32
#endif /* __HYBRID_TYPECORE_DEFINES_INT32 */
#ifdef __HYBRID_TYPECORE_DEFINES_INT64
#undef __HYBRID_TYPECORE_DEFINES_INT64
#undef __int64
#endif /* __HYBRID_TYPECORE_DEFINES_INT64 */
#ifdef __HYBRID_TYPECORE_DEFINES_INT128
#undef __HYBRID_TYPECORE_DEFINES_INT128
#undef __int128
#endif /* __HYBRID_TYPECORE_DEFINES_INT128 */
#ifndef __NO_ATTR_W64
#undef __w64
#endif /* !__NO_ATTR_W64 */
#undef char
#undef short
#undef int
#undef long
#undef signed
#undef unsigned
#undef __longlong_t
#undef __ulonglong_t
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("unsigned")
#pragma pop_macro("signed")
#pragma pop_macro("long")
#pragma pop_macro("int")
#pragma pop_macro("short")
#pragma pop_macro("char")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__INTELLISENSE__ */


/* Since C defines 5  integer types (char, short,  int, long, long long),  which
 * usually only map to 4 types (int8, int16, int32, int64), this macro describes
 * the C name of that fifth type:
 *   - __SIZEOF_FIFTHINT__      (e.g. `8')          The size of the fifth integer
 *   - __FIFTHINT_TYPE__        (e.g. `long long')  The C type for the fifth integer
 *   - __FIFTHINT_ALIAS_TYPE__  (e.g. `long')       The alias of the fifth integer used by one of `__INTn_TYPE__'
 */
#if (defined(__INT8_TYPE_IS_CHAR__) || defined(__INT16_TYPE_IS_CHAR__) || \
     defined(__INT32_TYPE_IS_CHAR__) || defined(__INT64_TYPE_IS_CHAR__))
#define ____FIFTHINT_TYPE_IS_NOT_CHAR
#endif /* __INTn_TYPE_IS_CHAR__ */
#if (defined(__INT8_TYPE_IS_SHORT__) || defined(__INT16_TYPE_IS_SHORT__) || \
     defined(__INT32_TYPE_IS_SHORT__) || defined(__INT64_TYPE_IS_SHORT__))
#define ____FIFTHINT_TYPE_IS_NOT_SHORT
#endif /* __INTn_TYPE_IS_SHORT__ */
#if (defined(__INT8_TYPE_IS_INT__) || defined(__INT16_TYPE_IS_INT__) || \
     defined(__INT32_TYPE_IS_INT__) || defined(__INT64_TYPE_IS_INT__))
#define ____FIFTHINT_TYPE_IS_NOT_INT
#endif /* __INTn_TYPE_IS_INT__ */
#if (defined(__INT8_TYPE_IS_LONG__) || defined(__INT16_TYPE_IS_LONG__) || \
     defined(__INT32_TYPE_IS_LONG__) || defined(__INT64_TYPE_IS_LONG__))
#define ____FIFTHINT_TYPE_IS_NOT_LONG
#endif /* __INTn_TYPE_IS_LONG__ */
#if (defined(__INT8_TYPE_IS_LONG_LONG__) || defined(__INT16_TYPE_IS_LONG_LONG__) || \
     defined(__INT32_TYPE_IS_LONG_LONG__) || defined(__INT64_TYPE_IS_LONG_LONG__))
#define ____FIFTHINT_TYPE_IS_NOT_LONG_LONG
#endif /* __INTn_TYPE_IS_LONG_LONG__ */


/* Check if there is a fifth integer type. */
#ifndef ____FIFTHINT_TYPE_IS_NOT_LONG
#define __SIZEOF_FIFTHINT__      __SIZEOF_LONG__
#define __FIFTHINT_TYPE__        signed long int
#define __UFIFTHINT_TYPE__       unsigned long int
#define __FIFTHINT_ALIAS_TYPE__  __TYPEFOR_INTIB(__SIZEOF_LONG__)
#define __UFIFTHINT_ALIAS_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_LONG__)
#elif defined(__SIZEOF_LONG_LONG__) && !defined(____FIFTHINT_TYPE_IS_NOT_LONG_LONG)
#define __SIZEOF_FIFTHINT__      __SIZEOF_LONG_LONG__
#define __FIFTHINT_TYPE__        __LONGLONG
#define __UFIFTHINT_TYPE__       __ULONGLONG
#define __FIFTHINT_ALIAS_TYPE__  __TYPEFOR_INTIB(__SIZEOF_LONG_LONG__)
#define __UFIFTHINT_ALIAS_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_LONG_LONG__)
#elif !defined(____FIFTHINT_TYPE_IS_NOT_INT)
#define __SIZEOF_FIFTHINT__      __SIZEOF_INT__
#define __FIFTHINT_TYPE__        signed int
#define __UFIFTHINT_TYPE__       unsigned int
#define __FIFTHINT_ALIAS_TYPE__  __TYPEFOR_INTIB(__SIZEOF_INT__)
#define __UFIFTHINT_ALIAS_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_INT__)
#elif !defined(____FIFTHINT_TYPE_IS_NOT_SHORT)
#define __SIZEOF_FIFTHINT__      __SIZEOF_SHORT__
#define __FIFTHINT_TYPE__        signed short
#define __UFIFTHINT_TYPE__       unsigned short
#define __FIFTHINT_ALIAS_TYPE__  __TYPEFOR_INTIB(__SIZEOF_SHORT__)
#define __UFIFTHINT_ALIAS_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_SHORT__)
#elif !defined(____FIFTHINT_TYPE_IS_NOT_CHAR)
#define __SIZEOF_FIFTHINT__      __SIZEOF_CHAR__
#define __FIFTHINT_TYPE__        signed char
#define __UFIFTHINT_TYPE__       unsigned char
#define __FIFTHINT_ALIAS_TYPE__  __TYPEFOR_INTIB(__SIZEOF_CHAR__)
#define __UFIFTHINT_ALIAS_TYPE__ __TYPEFOR_UINTIB(__SIZEOF_CHAR__)
#endif


#undef ____FIFTHINT_TYPE_IS_NOT_CHAR
#undef ____FIFTHINT_TYPE_IS_NOT_SHORT
#undef ____FIFTHINT_TYPE_IS_NOT_INT
#undef ____FIFTHINT_TYPE_IS_NOT_LONG
#undef ____FIFTHINT_TYPE_IS_NOT_LONG_LONG


#ifndef __SSIZE_TYPE__
#ifdef __SIZE_TYPE_IS_INT__
#define __SSIZE_TYPE__ __ATTR_W64 signed int
#elif defined(__SIZE_TYPE_IS_LONG__)
#define __SSIZE_TYPE__ __ATTR_W64 signed long
#elif defined(__SIZE_TYPE_IS_LONG_LONG__)
#define __SSIZE_TYPE__ __ATTR_W64 __LONGLONG
#elif defined(__SIZE_TYPE_IS_SHORT__)
#define __SSIZE_TYPE__ __ATTR_W64 signed short
#elif defined(__SIZE_TYPE_IS_CHAR__)
#define __SSIZE_TYPE__ __ATTR_W64 signed char
#else /* ... */
#define __SSIZE_TYPE__ __ATTR_W64 __TYPEFOR_INTIB(__SIZEOF_SIZE_T__)
#endif /* !... */
#endif /* !__SSIZE_TYPE__ */

#ifndef __PTRDIFF_TYPE__
#ifdef __PTRDIFF_TYPE_IS_INT__
#define __PTRDIFF_TYPE__ __ATTR_W64 signed int
#elif defined(__PTRDIFF_TYPE_IS_LONG__)
#define __PTRDIFF_TYPE__ __ATTR_W64 signed long
#elif defined(__PTRDIFF_TYPE_IS_LONG_LONG__)
#define __PTRDIFF_TYPE__ __ATTR_W64 __LONGLONG
#elif defined(__PTRDIFF_TYPE_IS_SHORT__)
#define __PTRDIFF_TYPE__ __ATTR_W64 signed short
#elif defined(__PTRDIFF_TYPE_IS_CHAR__)
#define __PTRDIFF_TYPE__ __ATTR_W64 signed char
#else /* ... */
#define __PTRDIFF_TYPE__ __SSIZE_TYPE__
#ifdef __SIZE_TYPE_IS_INT__
#define __PTRDIFF_TYPE_IS_INT__
#elif defined(__SIZE_TYPE_IS_LONG__)
#define __PTRDIFF_TYPE_IS_LONG__
#elif defined(__SIZE_TYPE_IS_LONG_LONG__)
#define __PTRDIFF_TYPE_IS_LONG_LONG__
#elif defined(__SIZE_TYPE_IS_SHORT__)
#define __PTRDIFF_TYPE_IS_SHORT__
#elif defined(__SIZE_TYPE_IS_CHAR__)
#define __PTRDIFF_TYPE_IS_CHAR__
#endif /* ... */
#endif /* !... */
#endif /* !__PTRDIFF_TYPE__ */
#endif /* !__DEEMON__ */


#endif /* !__GUARD_HYBRID_TYPECORE_H */
