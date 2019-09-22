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
#ifndef __GUARD_HYBRID_LIMITCORE_H
#define __GUARD_HYBRID_LIMITCORE_H 1

#include <__stdinc.h>
#include "typecore.h"

#define __PRIVATE_MIN2_S(s) __PRIVATE_MIN_S##s
#define __PRIVATE_MAX2_S(s) __PRIVATE_MAX_S##s
#define __PRIVATE_MIN2_U(s) __PRIVATE_MIN_U##s
#define __PRIVATE_MAX2_U(s) __PRIVATE_MAX_U##s
#define __PRIVATE_MIN_S(s)  __PRIVATE_MIN2_S(s)
#define __PRIVATE_MAX_S(s)  __PRIVATE_MAX2_S(s)
#define __PRIVATE_MIN_U(s)  __PRIVATE_MIN2_U(s)
#define __PRIVATE_MAX_U(s)  __PRIVATE_MAX2_U(s)

#ifdef __CHAR_MIN__
#if __CHAR_MIN__ == 0 && !defined(__CHAR_UNSIGNED__)
#define __CHAR_UNSIGNED__ 1
#endif /* __CHAR_MIN__ == 0 && !__CHAR_UNSIGNED__ */
#elif defined(_CHAR_UNSIGNED) || defined(_CHAR_IS_UNSIGNED)
#ifndef __CHAR_UNSIGNED__
#define __CHAR_UNSIGNED__ 1
#endif /* !__CHAR_UNSIGNED__ */
#endif

#ifndef __CHAR_BIT__
#define __CHAR_BIT__ 8
#endif /* !__CHAR_BIT__ */
#ifndef __SCHAR_MIN__
#define __SCHAR_MIN__ __PRIVATE_MIN_S(__SIZEOF_CHAR__)
#endif /* !__SCHAR_MIN__ */
#ifndef __SCHAR_MAX__
#define __SCHAR_MAX__ __PRIVATE_MAX_S(__SIZEOF_CHAR__)
#endif /* !__SCHAR_MAX__ */
#ifndef __UCHAR_MAX__
#define __UCHAR_MAX__ __PRIVATE_MAX_U(__SIZEOF_CHAR__)
#endif /* !__UCHAR_MAX__ */
#ifndef __CHAR_MIN__
#ifdef __CHAR_UNSIGNED__
#   define __CHAR_MIN__ __PRIVATE_MIN_U(__SIZEOF_CHAR__)
#   define __CHAR_MAX__ __PRIVATE_MAX_U(__SIZEOF_CHAR__)
#else /* __CHAR_UNSIGNED__ */
#   define __CHAR_MIN__ __PRIVATE_MIN_S(__SIZEOF_CHAR__)
#   define __CHAR_MAX__ __PRIVATE_MAX_S(__SIZEOF_CHAR__)
#endif /* !__CHAR_UNSIGNED__ */
#endif /* !__CHAR_MIN__ */
#ifndef __SHRT_MIN__
#define __SHRT_MIN__ __PRIVATE_MIN_S(__SIZEOF_SHORT__)
#endif /* !__SHRT_MIN__ */
#ifndef __SHRT_MAX__
#define __SHRT_MAX__ __PRIVATE_MAX_S(__SIZEOF_SHORT__)
#endif /* !__SHRT_MAX__ */
#ifndef __USHRT_MAX__
#define __USHRT_MAX__ __PRIVATE_MAX_U(__SIZEOF_SHORT__)
#endif /* !__USHRT_MAX__ */
#ifndef __INT_MIN__
#define __INT_MIN__ __PRIVATE_MIN_S(__SIZEOF_INT__)
#endif /* !__INT_MIN__ */
#ifndef __INT_MAX__
#define __INT_MAX__ __PRIVATE_MAX_S(__SIZEOF_INT__)
#endif /* !__INT_MAX__ */
#ifndef __UINT_MAX__
#define __UINT_MAX__ __PRIVATE_MAX_U(__SIZEOF_INT__)
#endif /* !__UINT_MAX__ */
#ifndef __LONG_MIN__
#define __LONG_MIN__ __PRIVATE_MIN_S(__SIZEOF_LONG__)
#endif /* !__LONG_MIN__ */
#ifndef __LONG_MAX__
#define __LONG_MAX__ __PRIVATE_MAX_S(__SIZEOF_LONG__)
#endif /* !__LONG_MAX__ */
#ifndef __ULONG_MAX__
#define __ULONG_MAX__ __PRIVATE_MAX_U(__SIZEOF_LONG__)
#endif /* !__ULONG_MAX__ */
#ifndef __LONG_LONG_MIN__
#define __LONG_LONG_MIN__ __PRIVATE_MIN_S(__SIZEOF_LONG_LONG__)
#endif /* !__LONG_LONG_MIN__ */
#ifndef __LONG_LONG_MAX__
#define __LONG_LONG_MAX__ __PRIVATE_MAX_S(__SIZEOF_LONG_LONG__)
#endif /* !__LONG_LONG_MAX__ */
#ifndef __ULONG_LONG_MAX__
#define __ULONG_LONG_MAX__ __PRIVATE_MAX_U(__SIZEOF_LONG_LONG__)
#endif /* !__ULONG_LONG_MAX__ */

#ifndef __SIZE_MIN__
#define __SIZE_MIN__ __PRIVATE_MIN_U(__SIZEOF_SIZE_T__)
#endif /* !__SIZE_MIN__ */
#ifndef __SIZE_MAX__
#define __SIZE_MAX__ __PRIVATE_MAX_U(__SIZEOF_SIZE_T__)
#endif /* !__SIZE_MAX__ */
#ifndef __SSIZE_MIN__
#define __SSIZE_MIN__ __PRIVATE_MIN_S(__SIZEOF_SIZE_T__)
#endif /* !__SSIZE_MIN__ */
#ifndef __SSIZE_MAX__
#define __SSIZE_MAX__ __PRIVATE_MAX_S(__SIZEOF_SIZE_T__)
#endif /* !__SSIZE_MAX__ */

#ifndef __INTMAX_MIN__
#define __INTMAX_MIN__ __PRIVATE_MIN_S(__SIZEOF_INTMAX_T__)
#endif /* !__INTMAX_MIN__ */
#ifndef __INTMAX_MAX__
#define __INTMAX_MAX__ __PRIVATE_MAX_S(__SIZEOF_INTMAX_T__)
#endif /* !__INTMAX_MAX__ */
#ifndef __UINTMAX_MAX__
#define __UINTMAX_MAX__ __PRIVATE_MAX_U(__SIZEOF_INTMAX_T__)
#endif /* !__UINTMAX_MAX__ */

#ifndef __INT8_MIN__
#define __INT8_MIN__         __PRIVATE_MIN_S1
#endif /* !__INT8_MIN__ */
#ifndef __INT16_MIN__
#define __INT16_MIN__        __PRIVATE_MIN_S2
#endif /* !__INT16_MIN__ */
#ifndef __INT32_MIN__
#define __INT32_MIN__        __PRIVATE_MIN_S4
#endif /* !__INT32_MIN__ */
#ifndef __INT64_MIN__
#define __INT64_MIN__        __PRIVATE_MIN_S8
#endif /* !__INT64_MIN__ */
#ifndef __INT8_MAX__
#define __INT8_MAX__         __PRIVATE_MAX_S1
#endif /* !__INT8_MAX__ */
#ifndef __INT16_MAX__
#define __INT16_MAX__        __PRIVATE_MAX_S2
#endif /* !__INT16_MAX__ */
#ifndef __INT32_MAX__
#define __INT32_MAX__        __PRIVATE_MAX_S4
#endif /* !__INT32_MAX__ */
#ifndef __INT64_MAX__
#define __INT64_MAX__        __PRIVATE_MAX_S8
#endif /* !__INT64_MAX__ */
#ifndef __UINT8_MAX__
#define __UINT8_MAX__        __PRIVATE_MAX_U1
#endif /* !__UINT8_MAX__ */
#ifndef __UINT16_MAX__
#define __UINT16_MAX__       __PRIVATE_MAX_U2
#endif /* !__UINT16_MAX__ */
#ifndef __UINT32_MAX__
#define __UINT32_MAX__       __PRIVATE_MAX_U4
#endif /* !__UINT32_MAX__ */
#ifndef __UINT64_MAX__
#define __UINT64_MAX__       __PRIVATE_MAX_U8
#endif /* !__UINT64_MAX__ */
#ifndef __INT_LEAST8_MIN__
#define __INT_LEAST8_MIN__   __PRIVATE_MIN_S(__SIZEOF_INT_LEAST8_T__)
#endif /* !__INT_LEAST8_MIN__ */
#ifndef __INT_LEAST16_MIN__
#define __INT_LEAST16_MIN__  __PRIVATE_MIN_S(__SIZEOF_INT_LEAST16_T__)
#endif /* !__INT_LEAST16_MIN__ */
#ifndef __INT_LEAST32_MIN__
#define __INT_LEAST32_MIN__  __PRIVATE_MIN_S(__SIZEOF_INT_LEAST32_T__)
#endif /* !__INT_LEAST32_MIN__ */
#ifndef __INT_LEAST64_MIN__
#define __INT_LEAST64_MIN__  __PRIVATE_MIN_S(__SIZEOF_INT_LEAST64_T__)
#endif /* !__INT_LEAST64_MIN__ */
#ifndef __INT_LEAST8_MAX__
#define __INT_LEAST8_MAX__   __PRIVATE_MAX_S(__SIZEOF_INT_LEAST8_T__)
#endif /* !__INT_LEAST8_MAX__ */
#ifndef __INT_LEAST16_MAX__
#define __INT_LEAST16_MAX__  __PRIVATE_MAX_S(__SIZEOF_INT_LEAST16_T__)
#endif /* !__INT_LEAST16_MAX__ */
#ifndef __INT_LEAST32_MAX__
#define __INT_LEAST32_MAX__  __PRIVATE_MAX_S(__SIZEOF_INT_LEAST32_T__)
#endif /* !__INT_LEAST32_MAX__ */
#ifndef __INT_LEAST64_MAX__
#define __INT_LEAST64_MAX__  __PRIVATE_MAX_S(__SIZEOF_INT_LEAST64_T__)
#endif /* !__INT_LEAST64_MAX__ */
#ifndef __UINT_LEAST8_MAX__
#define __UINT_LEAST8_MAX__  __PRIVATE_MAX_U(__SIZEOF_INT_LEAST8_T__)
#endif /* !__UINT_LEAST8_MAX__ */
#ifndef __UINT_LEAST16_MAX__
#define __UINT_LEAST16_MAX__ __PRIVATE_MAX_U(__SIZEOF_INT_LEAST16_T__)
#endif /* !__UINT_LEAST16_MAX__ */
#ifndef __UINT_LEAST32_MAX__
#define __UINT_LEAST32_MAX__ __PRIVATE_MAX_U(__SIZEOF_INT_LEAST32_T__)
#endif /* !__UINT_LEAST32_MAX__ */
#ifndef __UINT_LEAST64_MAX__
#define __UINT_LEAST64_MAX__ __PRIVATE_MAX_U(__SIZEOF_INT_LEAST64_T__)
#endif /* !__UINT_LEAST64_MAX__ */
#ifndef __INT_FAST8_MIN__
#define __INT_FAST8_MIN__    __PRIVATE_MIN_S(__SIZEOF_INT_FAST8_T__)
#endif /* !__INT_FAST8_MIN__ */
#ifndef __INT_FAST16_MIN__
#define __INT_FAST16_MIN__   __PRIVATE_MIN_S(__SIZEOF_INT_FAST16_T__)
#endif /* !__INT_FAST16_MIN__ */
#ifndef __INT_FAST32_MIN__
#define __INT_FAST32_MIN__   __PRIVATE_MIN_S(__SIZEOF_INT_FAST32_T__)
#endif /* !__INT_FAST32_MIN__ */
#ifndef __INT_FAST64_MIN__
#define __INT_FAST64_MIN__   __PRIVATE_MIN_S(__SIZEOF_INT_FAST64_T__)
#endif /* !__INT_FAST64_MIN__ */
#ifndef __INT_FAST8_MAX__
#define __INT_FAST8_MAX__    __PRIVATE_MAX_S(__SIZEOF_INT_FAST8_T__)
#endif /* !__INT_FAST8_MAX__ */
#ifndef __INT_FAST16_MAX__
#define __INT_FAST16_MAX__   __PRIVATE_MAX_S(__SIZEOF_INT_FAST16_T__)
#endif /* !__INT_FAST16_MAX__ */
#ifndef __INT_FAST32_MAX__
#define __INT_FAST32_MAX__   __PRIVATE_MAX_S(__SIZEOF_INT_FAST32_T__)
#endif /* !__INT_FAST32_MAX__ */
#ifndef __INT_FAST64_MAX__
#define __INT_FAST64_MAX__   __PRIVATE_MAX_S(__SIZEOF_INT_FAST64_T__)
#endif /* !__INT_FAST64_MAX__ */
#ifndef __UINT_FAST8_MAX__
#define __UINT_FAST8_MAX__   __PRIVATE_MAX_U(__SIZEOF_INT_FAST8_T__)
#endif /* !__UINT_FAST8_MAX__ */
#ifndef __UINT_FAST16_MAX__
#define __UINT_FAST16_MAX__  __PRIVATE_MAX_U(__SIZEOF_INT_FAST16_T__)
#endif /* !__UINT_FAST16_MAX__ */
#ifndef __UINT_FAST32_MAX__
#define __UINT_FAST32_MAX__  __PRIVATE_MAX_U(__SIZEOF_INT_FAST32_T__)
#endif /* !__UINT_FAST32_MAX__ */
#ifndef __UINT_FAST64_MAX__
#define __UINT_FAST64_MAX__  __PRIVATE_MAX_U(__SIZEOF_INT_FAST64_T__)
#endif /* !__UINT_FAST64_MAX__ */
#ifndef __INTPTR_MIN__
#define __INTPTR_MIN__       __PRIVATE_MIN_S(__SIZEOF_POINTER__)
#endif /* !__INTPTR_MIN__ */
#ifndef __INTPTR_MAX__
#define __INTPTR_MAX__       __PRIVATE_MAX_S(__SIZEOF_POINTER__)
#endif /* !__INTPTR_MAX__ */
#ifndef __UINTPTR_MAX__
#define __UINTPTR_MAX__      __PRIVATE_MAX_U(__SIZEOF_POINTER__)
#endif /* !__UINTPTR_MAX__ */
#ifndef __PTRDIFF_MIN__
#define __PTRDIFF_MIN__      __PRIVATE_MIN_S(__SIZEOF_PTRDIFF_T__)
#endif /* !__PTRDIFF_MIN__ */
#ifndef __PTRDIFF_MAX__
#define __PTRDIFF_MAX__      __PRIVATE_MAX_S(__SIZEOF_PTRDIFF_T__)
#endif /* !__PTRDIFF_MAX__ */

#ifdef __PRIVATE_MIN_S16
#ifndef __INT128_MIN__
#define __INT128_MIN__       __PRIVATE_MIN_S16
#endif /* !__INT128_MIN__ */
#ifndef __INT128_MAX__
#define __INT128_MAX__       __PRIVATE_MAX_S16
#endif /* !__INT128_MAX__ */
#ifndef __UINT128_MAX__
#define __UINT128_MAX__      __PRIVATE_MAX_U16
#endif /* !__UINT128_MAX__ */
#endif /* __PRIVATE_MIN_S16 */


#ifndef __SIG_ATOMIC_MIN__
#ifdef __SIG_ATOMIC_UNSIGNED__
#define __SIG_ATOMIC_MIN__   __PRIVATE_MIN_U(__SIZEOF_SIG_ATOMIC_T__)
#else /* __SIG_ATOMIC_UNSIGNED__ */
#define __SIG_ATOMIC_MIN__   __PRIVATE_MIN_S(__SIZEOF_SIG_ATOMIC_T__)
#endif /* !__SIG_ATOMIC_UNSIGNED__ */
#endif /* !__SIG_ATOMIC_MIN__ */
#ifndef __SIG_ATOMIC_MAX__
#ifdef __SIG_ATOMIC_UNSIGNED__
#define __SIG_ATOMIC_MAX__   __PRIVATE_MAX_U(__SIZEOF_SIG_ATOMIC_T__)
#else /* __SIG_ATOMIC_UNSIGNED__ */
#define __SIG_ATOMIC_MAX__   __PRIVATE_MAX_S(__SIZEOF_SIG_ATOMIC_T__)
#endif /* !__SIG_ATOMIC_UNSIGNED__ */
#endif /* !__SIG_ATOMIC_MAX__ */

#ifndef __WCHAR_MIN__
#ifdef __WCHAR_UNSIGNED__
#   define __WCHAR_MIN__        __PRIVATE_MIN_U(__SIZEOF_WCHAR_T__)
#else /* __WCHAR_UNSIGNED__ */
#   define __WCHAR_MIN__        __PRIVATE_MIN_S(__SIZEOF_WCHAR_T__)
#endif /* !__WCHAR_UNSIGNED__ */
#endif /* !__WCHAR_MIN__ */
#ifndef __WCHAR_MAX__
#ifndef __WCHAR_UNSIGNED__
#   define __WCHAR_MAX__        __PRIVATE_MIN_S(__SIZEOF_WCHAR_T__)
#else /* __WCHAR_UNSIGNED__ */
#   define __WCHAR_MAX__        __PRIVATE_MIN_S(__SIZEOF_WCHAR_T__)
#endif /* !__WCHAR_UNSIGNED__ */
#endif /* !__WCHAR_MAX__ */
#ifndef __WINT_MIN__
#   define __WINT_MIN__         __PRIVATE_MIN_S(__SIZEOF_WINT_T__)
#endif /* !__WINT_MIN__ */
#ifndef __WINT_MAX__
#   define __WINT_MAX__         __PRIVATE_MIN_S(__SIZEOF_WINT_T__)
#endif /* !__WINT_MAX__ */


#endif /* !__GUARD_HYBRID_LIMITCORE_H */
