/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID___BIT_H
#define __GUARD_HYBRID___BIT_H 1

#include "../__stdinc.h"
#include "__assert.h"
#include "typecore.h"
#ifdef _MSC_VER
#include "host.h"
#endif /* _MSC_VER */

/* Bit-scanning / bit-manipulation functions. */

#ifdef __CC__
__DECL_BEGIN

/* Generic implementations. */
#define ____IMPL_DO_FFS(T, i)                         \
	{                                                 \
		__SHIFT_TYPE__ __result;                      \
		if __unlikely(!i)                             \
			return 0;                                 \
		for (__result = 1; !(((T)i) & 1); ++__result) \
			i = ((T)i >> 1);                          \
		return __result;                              \
	}
#define ____IMPL_DO_CLZ(T, i)                   \
	{                                           \
		__SHIFT_TYPE__ __result = 0;            \
		T __mask;                               \
		__hybrid_assert(i != 0);                \
		__mask = (T)1 << ((sizeof(T) * 8) - 1); \
		for (; !((T)i & __mask); __mask >>= 1)  \
			++__result;                         \
		return __result;                        \
	}
#define ____IMPL_DO_CTZ(T, i)                  \
	{                                          \
		__SHIFT_TYPE__ __result;               \
		T __mask;                              \
		__hybrid_assert(i != 0);               \
		__result = 0;                          \
		__mask   = 1;                          \
		for (; !((T)i & __mask); __mask <<= 1) \
			++__result;                        \
		return __result;                       \
	}
#define ____IMPL_DO_POPCOUNT(T, i)                                               \
	{                                                                            \
		__SHIFT_TYPE__ __result = 0;                                             \
		T __mask                = 1;                                             \
		for (;; __mask <<= 1) {                                                  \
			if (((T)i) & __mask)                                                 \
				++__result;                                                      \
			if (!(__mask < (T)i && !(__mask & ((T)1 << ((sizeof(T) * 8) - 1))))) \
				break;                                                           \
		}                                                                        \
		return __result;                                                         \
	}
#define ____IMPL_DO_PARITY(T, i)                                                 \
	{                                                                            \
		__SHIFT_TYPE__ __result = 0;                                             \
		T __mask                = 1;                                             \
		for (;; __mask <<= 1) {                                                  \
			if (((T)i) & __mask)                                                 \
				__result ^= 1;                                                   \
			if (!(__mask < (T)i && !(__mask & ((T)1 << ((sizeof(T) * 8) - 1))))) \
				break;                                                           \
		}                                                                        \
		return __result;                                                         \
	}
#define ____IMPL_DO_CLRSB(T, i)                   \
	{                                             \
		__SHIFT_TYPE__ __result;                  \
		T __mask, __sbit;                         \
		__mask   = (T)1 << ((sizeof(T) * 8) - 1); \
		__sbit   = (T)i & __mask;                 \
		__result = 0;                             \
		for (;;) {                                \
			__mask >>= 1;                         \
			if (!__mask)                          \
				break;                            \
			__sbit >>= 1;                         \
			if (((T)i & __mask) != __sbit)        \
				break;                            \
			++__result;                           \
		}                                         \
		return __result;                          \
	}

/* Parallel bit deposit (s.a. `https://www.felixcloutier.com/x86/pdep') */
#define ____IMPL_DO_PDEP(T, value, mask)                  \
	{                                                     \
		T __result             = 0;                       \
		__SHIFT_TYPE__ __shift = 0;                       \
		for (; mask; mask >>= 1, ++__shift) {             \
			if (mask & 1) {                               \
				__result |= (T)(value & (T)1) << __shift; \
				value >>= 1;                              \
			}                                             \
		}                                                 \
		return __result;                                  \
	}

/* Parallel bit extract (s.a. `https://www.felixcloutier.com/x86/pext') */
#define ____IMPL_DO_PEXT(T, value, mask)                  \
	{                                                     \
		T __result             = 0;                       \
		__SHIFT_TYPE__ __shift = 0;                       \
		for (; value && mask; value >>= 1, mask >>= 1) {  \
			if (mask & 1) {                               \
				__result |= (T)(value & (T)1) << __shift; \
				++__shift;                                \
			}                                             \
		}                                                 \
		return __result;                                  \
	}




/************************************************************************/
/* shift_t __hybrid_ffs[8|16|32|64](unsigned Integer X)                 */
/************************************************************************/
#ifndef __HYBRID_BIT_NO_BUILTIN
#ifdef __UINT64_TYPE__
#ifndef __hybrid_ffs64
#if __has_builtin(__builtin_ffs) && __SIZEOF_INT__ >= 8
#define __hybrid_ffs64(i) (__SHIFT_TYPE__)__builtin_ffs((int)(unsigned int)(__UINT64_TYPE__)(i))
#elif __has_builtin(__builtin_ffsl) && __SIZEOF_LONG__ >= 8
#define __hybrid_ffs64(i) (__SHIFT_TYPE__)__builtin_ffsl((long)(unsigned long)(__UINT64_TYPE__)(i))
#elif __has_builtin(__builtin_ffsll) && __SIZEOF_LONG_LONG__ >= 8
#define __hybrid_ffs64(i) (__SHIFT_TYPE__)__builtin_ffsll((__LONGLONG)(__ULONGLONG)(__UINT64_TYPE__)(i))
#elif __has_builtin(__builtin_ffsimax) && __SIZEOF_INTMAX_T__ >= 8
#define __hybrid_ffs64(i) (__SHIFT_TYPE__)__builtin_ffsimax((__INTMAX_TYPE__)(__UINTMAX_TYPE__)(__UINT64_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_ffs64 */
#endif /* __UINT64_TYPE__ */

#ifndef __hybrid_ffs32
#if __has_builtin(__builtin_ffs) && __SIZEOF_INT__ >= 4
#define __hybrid_ffs32(i) (__SHIFT_TYPE__)__builtin_ffs((int)(unsigned int)(__UINT32_TYPE__)(i))
#elif __has_builtin(__builtin_ffsl) && __SIZEOF_LONG__ >= 4
#define __hybrid_ffs32(i) (__SHIFT_TYPE__)__builtin_ffsl((long)(unsigned long)(__UINT32_TYPE__)(i))
#elif __has_builtin(__builtin_ffsll) && __SIZEOF_LONG_LONG__ >= 4
#define __hybrid_ffs32(i) (__SHIFT_TYPE__)__builtin_ffsll((__LONGLONG)(__ULONGLONG)(__UINT32_TYPE__)(i))
#elif __has_builtin(__builtin_ffsimax) && __SIZEOF_INTMAX_T__ >= 4
#define __hybrid_ffs32(i) (__SHIFT_TYPE__)__builtin_ffsimax((__INTMAX_TYPE__)(__UINTMAX_TYPE__)(__UINT32_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_ffs32 */

#ifndef __hybrid_ffs16
#if __has_builtin(__builtin_ffs) && __SIZEOF_INT__ >= 2
#define __hybrid_ffs16(i) (__SHIFT_TYPE__)__builtin_ffs((int)(unsigned int)(__UINT16_TYPE__)(i))
#elif __has_builtin(__builtin_ffsl) && __SIZEOF_LONG__ >= 2
#define __hybrid_ffs16(i) (__SHIFT_TYPE__)__builtin_ffsl((long)(unsigned long)(__UINT16_TYPE__)(i))
#elif __has_builtin(__builtin_ffsll) && __SIZEOF_LONG_LONG__ >= 2
#define __hybrid_ffs16(i) (__SHIFT_TYPE__)__builtin_ffsll((__LONGLONG)(__ULONGLONG)(__UINT16_TYPE__)(i))
#elif __has_builtin(__builtin_ffsimax) && __SIZEOF_INTMAX_T__ >= 2
#define __hybrid_ffs16(i) (__SHIFT_TYPE__)__builtin_ffsimax((__INTMAX_TYPE__)(__UINTMAX_TYPE__)(__UINT16_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_ffs16 */

#ifndef __hybrid_ffs8
#if __has_builtin(__builtin_ffs) && __SIZEOF_INT__ >= 1
#define __hybrid_ffs8(i) (__SHIFT_TYPE__)__builtin_ffs((int)(unsigned int)(__UINT8_TYPE__)(i))
#elif __has_builtin(__builtin_ffsl) && __SIZEOF_LONG__ >= 1
#define __hybrid_ffs8(i) (__SHIFT_TYPE__)__builtin_ffsl((long)(unsigned long)(__UINT8_TYPE__)(i))
#elif __has_builtin(__builtin_ffsll) && __SIZEOF_LONG_LONG__ >= 1
#define __hybrid_ffs8(i) (__SHIFT_TYPE__)__builtin_ffsll((__LONGLONG)(__ULONGLONG)(__UINT8_TYPE__)(i))
#elif __has_builtin(__builtin_ffsimax) && __SIZEOF_INTMAX_T__ >= 1
#define __hybrid_ffs8(i) (__SHIFT_TYPE__)__builtin_ffsimax((__INTMAX_TYPE__)(__UINTMAX_TYPE__)(__UINT8_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_ffs8 */
#endif /* !__HYBRID_BIT_NO_BUILTIN */

#ifndef __hybrid_ffs8
#ifdef __hybrid_ffs16
#define __hybrid_ffs8 __hybrid_ffs16
#elif defined(__hybrid_ffs32)
#define __hybrid_ffs8 __hybrid_ffs32
#elif defined(__hybrid_ffs64)
#define __hybrid_ffs8 __hybrid_ffs64
#else /* ... */
#define __hybrid_ffs8(i) __hybrid_ffs8((__UINT8_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_ffs8)(__UINT8_TYPE__ __i) ____IMPL_DO_FFS(__UINT8_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_ffs8 */

#ifndef __hybrid_ffs16
#ifdef __hybrid_ffs32
#define __hybrid_ffs16 __hybrid_ffs32
#elif defined(__hybrid_ffs64)
#define __hybrid_ffs16 __hybrid_ffs64
#else /* ... */
#define __hybrid_ffs16(i) __hybrid_ffs16((__UINT16_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_ffs16)(__UINT16_TYPE__ __i) ____IMPL_DO_FFS(__UINT16_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_ffs16 */

#ifndef __hybrid_ffs32
#ifdef __hybrid_ffs64
#define __hybrid_ffs32 __hybrid_ffs64
#else /* __hybrid_ffs64 */
#define __hybrid_ffs32(i) __hybrid_ffs32((__UINT32_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_ffs32)(__UINT32_TYPE__ __i) ____IMPL_DO_FFS(__UINT32_TYPE__, __i)
#endif /* !__hybrid_ffs64 */
#endif /* !__hybrid_ffs32 */

#ifdef __UINT64_TYPE__
#ifndef __hybrid_ffs64
#define __hybrid_ffs64(i) __hybrid_ffs64((__UINT64_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_ffs64)(__UINT64_TYPE__ __i) ____IMPL_DO_FFS(__UINT64_TYPE__, __i)
#endif /* !__hybrid_ffs64 */
#endif /* __UINT64_TYPE__ */





/************************************************************************/
/* shift_t __hybrid_clz[8|16|32|64](unsigned Integer X)                 */
/************************************************************************/
#ifndef __HYBRID_BIT_NO_BUILTIN
#ifdef __UINT64_TYPE__
#ifndef __hybrid_clz64
#if __has_builtin(__builtin_clz) && __SIZEOF_INT__ == 8
#define __hybrid_clz64(i) (__SHIFT_TYPE__)__builtin_clz((unsigned int)(i))
#elif __has_builtin(__builtin_clzl) && __SIZEOF_LONG__ == 8
#define __hybrid_clz64(i) (__SHIFT_TYPE__)__builtin_clzl((unsigned long)(i))
#elif __has_builtin(__builtin_clzll) && __SIZEOF_LONG_LONG__ == 8
#define __hybrid_clz64(i) (__SHIFT_TYPE__)__builtin_clzll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_clzimax) && __SIZEOF_INTMAX_T__ == 8
#define __hybrid_clz64(i) (__SHIFT_TYPE__)__builtin_clzimax((__UINTMAX_TYPE__)(i))
#elif defined(_MSC_VER) && defined(__x86_64__)
extern unsigned char (__cdecl _BitScanReverse64)(unsigned long *__index, unsigned __int64 __mask);
#pragma intrinsic(_BitScanReverse64)
#define __hybrid_clz64(i) __hybrid_clz64((__UINT64_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_clz64)(__UINT64_TYPE__ __i) {
	unsigned long __res;
	_BitScanReverse64(&__res, (__UINT64_TYPE__)__i);
	return (__SHIFT_TYPE__)63 - (__SHIFT_TYPE__)__res;
}
#endif /* ... */
#endif /* !__hybrid_clz64 */
#endif /* __UINT64_TYPE__ */

#ifndef __hybrid_clz32
#if __has_builtin(__builtin_clz) && __SIZEOF_INT__ == 4
#define __hybrid_clz32(i) (__SHIFT_TYPE__)__builtin_clz((unsigned int)(i))
#elif __has_builtin(__builtin_clzl) && __SIZEOF_LONG__ == 4
#define __hybrid_clz32(i) (__SHIFT_TYPE__)__builtin_clzl((unsigned long)(i))
#elif __has_builtin(__builtin_clzll) && __SIZEOF_LONG_LONG__ == 4
#define __hybrid_clz32(i) (__SHIFT_TYPE__)__builtin_clzll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_clzimax) && __SIZEOF_INTMAX_T__ == 4
#define __hybrid_clz32(i) (__SHIFT_TYPE__)__builtin_clzimax((__UINTMAX_TYPE__)(i))
#elif defined(_MSC_VER)
extern unsigned char (__cdecl _BitScanReverse)(unsigned long *__index, unsigned long __mask);
#pragma intrinsic(_BitScanReverse)
#define __hybrid_clz32(i) __hybrid_clz32((__UINT32_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_clz32)(__UINT32_TYPE__ __i) {
	unsigned long __res;
	_BitScanReverse(&__res, (unsigned long)__i);
	return (__SHIFT_TYPE__)31 - (__SHIFT_TYPE__)__res;
}
#endif /* ... */
#endif /* !__hybrid_clz32 */

#ifndef __hybrid_clz16
#if __has_builtin(__builtin_clz) && __SIZEOF_INT__ == 2
#define __hybrid_clz16(i) (__SHIFT_TYPE__)__builtin_clz((unsigned int)(i))
#elif __has_builtin(__builtin_clzl) && __SIZEOF_LONG__ == 2
#define __hybrid_clz16(i) (__SHIFT_TYPE__)__builtin_clzl((unsigned long)(i))
#elif __has_builtin(__builtin_clzll) && __SIZEOF_LONG_LONG__ == 2
#define __hybrid_clz16(i) (__SHIFT_TYPE__)__builtin_clzll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_clzimax) && __SIZEOF_INTMAX_T__ == 2
#define __hybrid_clz16(i) (__SHIFT_TYPE__)__builtin_clzimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_clz16 */

#ifndef __hybrid_clz8
#if __has_builtin(__builtin_clz) && __SIZEOF_INT__ == 1
#define __hybrid_clz8(i) (__SHIFT_TYPE__)__builtin_clz((unsigned int)(i))
#elif __has_builtin(__builtin_clzl) && __SIZEOF_LONG__ == 1
#define __hybrid_clz8(i) (__SHIFT_TYPE__)__builtin_clzl((unsigned long)(i))
#elif __has_builtin(__builtin_clzll) && __SIZEOF_LONG_LONG__ == 1
#define __hybrid_clz8(i) (__SHIFT_TYPE__)__builtin_clzll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_clzimax) && __SIZEOF_INTMAX_T__ == 1
#define __hybrid_clz8(i) (__SHIFT_TYPE__)__builtin_clzimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_clz8 */
#endif /* !__HYBRID_BIT_NO_BUILTIN */

#ifndef __hybrid_clz8
#ifdef __hybrid_clz16
#define __hybrid_clz8(i) (__SHIFT_TYPE__)(__hybrid_clz16((__UINT16_TYPE__)(__UINT8_TYPE__)(i)) - 8)
#elif defined(__hybrid_clz32)
#define __hybrid_clz8(i) (__SHIFT_TYPE__)(__hybrid_clz32((__UINT32_TYPE__)(__UINT8_TYPE__)(i)) - 24)
#elif defined(__hybrid_clz64)
#define __hybrid_clz8(i) (__SHIFT_TYPE__)(__hybrid_clz64((__UINT64_TYPE__)(__UINT8_TYPE__)(i)) - 56)
#else /* ... */
#define __hybrid_clz8(i) __hybrid_clz8((__UINT8_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_clz8)(__UINT8_TYPE__ __i) ____IMPL_DO_CLZ(__UINT8_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_clz8 */

#ifndef __hybrid_clz16
#ifdef __hybrid_clz32
#define __hybrid_clz16(i) (__SHIFT_TYPE__)(__hybrid_clz32((__UINT32_TYPE__)(__UINT16_TYPE__)(i)) - 16)
#elif defined(__hybrid_clz64)
#define __hybrid_clz16(i) (__SHIFT_TYPE__)(__hybrid_clz64((__UINT64_TYPE__)(__UINT16_TYPE__)(i)) - 48)
#else /* ... */
#define __hybrid_clz16(i) __hybrid_clz16((__UINT16_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_clz16)(__UINT16_TYPE__ __i) ____IMPL_DO_CLZ(__UINT16_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_clz16 */

#ifndef __hybrid_clz32
#ifdef __hybrid_clz64
#define __hybrid_clz32(i) (__SHIFT_TYPE__)(__hybrid_clz64((__UINT64_TYPE__)(__UINT32_TYPE__)(i)) - 32)
#else /* __hybrid_clz64 */
#define __hybrid_clz32(i) __hybrid_clz32((__UINT32_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_clz32)(__UINT32_TYPE__ __i) ____IMPL_DO_CLZ(__UINT32_TYPE__, __i)
#endif /* !__hybrid_clz64 */
#endif /* !__hybrid_clz32 */

#ifdef __UINT64_TYPE__
#ifndef __hybrid_clz64
#define __hybrid_clz64(i) __hybrid_clz64((__UINT64_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_clz64)(__UINT64_TYPE__ __i) ____IMPL_DO_CLZ(__UINT64_TYPE__, __i)
#endif /* !__hybrid_clz64 */
#endif /* __UINT64_TYPE__ */




/************************************************************************/
/* shift_t __hybrid_ctz[8|16|32|64](unsigned Integer X)                 */
/************************************************************************/
#ifndef __HYBRID_BIT_NO_BUILTIN
#ifdef __UINT64_TYPE__
#ifndef __hybrid_ctz64
#if __has_builtin(__builtin_ctz) && __SIZEOF_INT__ >= 8
#define __hybrid_ctz64(i) (__SHIFT_TYPE__)__builtin_ctz((unsigned int)(i))
#elif __has_builtin(__builtin_ctzl) && __SIZEOF_LONG__ >= 8
#define __hybrid_ctz64(i) (__SHIFT_TYPE__)__builtin_ctzl((unsigned long)(i))
#elif __has_builtin(__builtin_ctzll) && __SIZEOF_LONG_LONG__ >= 8
#define __hybrid_ctz64(i) (__SHIFT_TYPE__)__builtin_ctzll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_ctzimax) && __SIZEOF_INTMAX_T__ >= 8
#define __hybrid_ctz64(i) (__SHIFT_TYPE__)__builtin_ctzimax((__UINTMAX_TYPE__)(i))
#elif defined(_MSC_VER) && defined(__x86_64__)
extern unsigned char (__cdecl _BitScanForward64)(unsigned long *__index, unsigned __int64 __mask);
#pragma intrinsic(_BitScanForward64)
#define __hybrid_ctz64(i) __hybrid_ctz64((__UINT64_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_ctz64)(__UINT64_TYPE__ __i) {
	unsigned long __res;
	_BitScanForward64(&__res, (__UINT64_TYPE__)__i);
	return (__SHIFT_TYPE__)__res;
}
#endif /* ... */
#endif /* !__hybrid_ctz64 */
#endif /* __UINT64_TYPE__ */

#ifndef __hybrid_ctz32
#if __has_builtin(__builtin_ctz) && __SIZEOF_INT__ >= 4
#define __hybrid_ctz32(i) (__SHIFT_TYPE__)__builtin_ctz((unsigned int)(i))
#elif __has_builtin(__builtin_ctzl) && __SIZEOF_LONG__ >= 4
#define __hybrid_ctz32(i) (__SHIFT_TYPE__)__builtin_ctzl((unsigned long)(i))
#elif __has_builtin(__builtin_ctzll) && __SIZEOF_LONG_LONG__ >= 4
#define __hybrid_ctz32(i) (__SHIFT_TYPE__)__builtin_ctzll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_ctzimax) && __SIZEOF_INTMAX_T__ >= 4
#define __hybrid_ctz32(i) (__SHIFT_TYPE__)__builtin_ctzimax((__UINTMAX_TYPE__)(i))
#elif defined(_MSC_VER)
extern unsigned char (__cdecl _BitScanForward)(unsigned long *__index, unsigned long __mask);
#pragma intrinsic(_BitScanForward)
#define __hybrid_ctz32(i) __hybrid_ctz32((__UINT32_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_ctz32)(__UINT32_TYPE__ __i) {
	unsigned long __res;
	_BitScanForward(&__res, (unsigned long)__i);
	return (__SHIFT_TYPE__)__res;
}
#endif /* ... */
#endif /* !__hybrid_ctz32 */

#ifndef __hybrid_ctz16
#if __has_builtin(__builtin_ctz) && __SIZEOF_INT__ >= 2
#define __hybrid_ctz16(i) (__SHIFT_TYPE__)__builtin_ctz((unsigned int)(i))
#elif __has_builtin(__builtin_ctzl) && __SIZEOF_LONG__ >= 2
#define __hybrid_ctz16(i) (__SHIFT_TYPE__)__builtin_ctzl((unsigned long)(i))
#elif __has_builtin(__builtin_ctzll) && __SIZEOF_LONG_LONG__ >= 2
#define __hybrid_ctz16(i) (__SHIFT_TYPE__)__builtin_ctzll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_ctzimax) && __SIZEOF_INTMAX_T__ >= 2
#define __hybrid_ctz16(i) (__SHIFT_TYPE__)__builtin_ctzimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_ctz16 */

#ifndef __hybrid_ctz8
#if __has_builtin(__builtin_ctz) && __SIZEOF_INT__ >= 1
#define __hybrid_ctz8(i) (__SHIFT_TYPE__)__builtin_ctz((unsigned int)(i))
#elif __has_builtin(__builtin_ctzl) && __SIZEOF_LONG__ >= 1
#define __hybrid_ctz8(i) (__SHIFT_TYPE__)__builtin_ctzl((unsigned long)(i))
#elif __has_builtin(__builtin_ctzll) && __SIZEOF_LONG_LONG__ >= 1
#define __hybrid_ctz8(i) (__SHIFT_TYPE__)__builtin_ctzll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_ctzimax) && __SIZEOF_INTMAX_T__ >= 1
#define __hybrid_ctz8(i) (__SHIFT_TYPE__)__builtin_ctzimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_ctz8 */
#endif /* !__HYBRID_BIT_NO_BUILTIN */

#ifndef __hybrid_ctz8
#ifdef __hybrid_ctz16
#define __hybrid_ctz8 __hybrid_ctz16
#elif defined(__hybrid_ctz32)
#define __hybrid_ctz8 __hybrid_ctz32
#elif defined(__hybrid_ctz64)
#define __hybrid_ctz8 __hybrid_ctz64
#else /* ... */
#define __hybrid_ctz8(i) __hybrid_ctz8((__UINT8_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_ctz8)(__UINT8_TYPE__ __i) ____IMPL_DO_CTZ(__UINT8_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_ctz8 */

#ifndef __hybrid_ctz16
#if defined(__hybrid_ctz32)
#define __hybrid_ctz16 __hybrid_ctz32
#elif defined(__hybrid_ctz64)
#define __hybrid_ctz16 __hybrid_ctz64
#else /* ... */
#define __hybrid_ctz16(i) __hybrid_ctz16((__UINT16_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_ctz16)(__UINT16_TYPE__ __i) ____IMPL_DO_CTZ(__UINT16_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_ctz16 */

#ifndef __hybrid_ctz32
#ifdef __hybrid_ctz64
#define __hybrid_ctz32 __hybrid_ctz64
#else /* __hybrid_ctz64 */
#define __hybrid_ctz32(i) __hybrid_ctz32((__UINT32_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_ctz32)(__UINT32_TYPE__ __i) ____IMPL_DO_CTZ(__UINT32_TYPE__, __i)
#endif /* !__hybrid_ctz64 */
#endif /* !__hybrid_ctz32 */

#ifdef __UINT64_TYPE__
#ifndef __hybrid_ctz64
#define __hybrid_ctz64(i) __hybrid_ctz64((__UINT64_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_ctz64)(__UINT64_TYPE__ __i) ____IMPL_DO_CTZ(__UINT64_TYPE__, __i)
#endif /* !__hybrid_ctz64 */
#endif /* __UINT64_TYPE__ */





/************************************************************************/
/* shift_t __hybrid_popcount[8|16|32|64](unsigned Integer X)            */
/************************************************************************/
#ifndef __HYBRID_BIT_NO_BUILTIN
#ifdef __UINT64_TYPE__
#ifndef __hybrid_popcount64
#if __has_builtin(__builtin_popcount) && __SIZEOF_INT__ >= 8
#define __hybrid_popcount64(i) (__SHIFT_TYPE__)__builtin_popcount((unsigned int)(i))
#elif __has_builtin(__builtin_popcountl) && __SIZEOF_LONG__ >= 8
#define __hybrid_popcount64(i) (__SHIFT_TYPE__)__builtin_popcountl((unsigned long)(i))
#elif __has_builtin(__builtin_popcountll) && __SIZEOF_LONG_LONG__ >= 8
#define __hybrid_popcount64(i) (__SHIFT_TYPE__)__builtin_popcountll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_popcountimax) && __SIZEOF_INTMAX_T__ >= 8
#define __hybrid_popcount64(i) (__SHIFT_TYPE__)__builtin_popcountimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_popcount64 */
#endif /* __UINT64_TYPE__ */

#ifndef __hybrid_popcount32
#if __has_builtin(__builtin_popcount) && __SIZEOF_INT__ >= 4
#define __hybrid_popcount32(i) (__SHIFT_TYPE__)__builtin_popcount((unsigned int)(i))
#elif __has_builtin(__builtin_popcountl) && __SIZEOF_LONG__ >= 4
#define __hybrid_popcount32(i) (__SHIFT_TYPE__)__builtin_popcountl((unsigned long)(i))
#elif __has_builtin(__builtin_popcountll) && __SIZEOF_LONG_LONG__ >= 4
#define __hybrid_popcount32(i) (__SHIFT_TYPE__)__builtin_popcountll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_popcountimax) && __SIZEOF_INTMAX_T__ >= 4
#define __hybrid_popcount32(i) (__SHIFT_TYPE__)__builtin_popcountimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_popcount32 */

#ifndef __hybrid_popcount16
#if __has_builtin(__builtin_popcount) && __SIZEOF_INT__ >= 2
#define __hybrid_popcount16(i) (__SHIFT_TYPE__)__builtin_popcount((unsigned int)(i))
#elif __has_builtin(__builtin_popcountl) && __SIZEOF_LONG__ >= 2
#define __hybrid_popcount16(i) (__SHIFT_TYPE__)__builtin_popcountl((unsigned long)(i))
#elif __has_builtin(__builtin_popcountll) && __SIZEOF_LONG_LONG__ >= 2
#define __hybrid_popcount16(i) (__SHIFT_TYPE__)__builtin_popcountll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_popcountimax) && __SIZEOF_INTMAX_T__ >= 2
#define __hybrid_popcount16(i) (__SHIFT_TYPE__)__builtin_popcountimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_popcount16 */

#ifndef __hybrid_popcount8
#if __has_builtin(__builtin_popcount) && __SIZEOF_INT__ >= 1
#define __hybrid_popcount8(i) (__SHIFT_TYPE__)__builtin_popcount((unsigned int)(i))
#elif __has_builtin(__builtin_popcountl) && __SIZEOF_LONG__ >= 1
#define __hybrid_popcount8(i) (__SHIFT_TYPE__)__builtin_popcountl((unsigned long)(i))
#elif __has_builtin(__builtin_popcountll) && __SIZEOF_LONG_LONG__ >= 1
#define __hybrid_popcount8(i) (__SHIFT_TYPE__)__builtin_popcountll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_popcountimax) && __SIZEOF_INTMAX_T__ >= 1
#define __hybrid_popcount8(i) (__SHIFT_TYPE__)__builtin_popcountimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_popcount8 */
#endif /* !__HYBRID_BIT_NO_BUILTIN */

#ifndef __hybrid_popcount8
#ifdef __hybrid_popcount16
#define __hybrid_popcount8 __hybrid_popcount16
#elif defined(__hybrid_popcount32)
#define __hybrid_popcount8 __hybrid_popcount32
#elif defined(__hybrid_popcount64)
#define __hybrid_popcount8 __hybrid_popcount64
#else /* ... */
#define __hybrid_popcount8(i) __hybrid_popcount8((__UINT8_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_popcount8)(__UINT8_TYPE__ __i) ____IMPL_DO_POPCOUNT(__UINT8_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_popcount8 */

#ifndef __hybrid_popcount16
#ifdef __hybrid_popcount32
#define __hybrid_popcount16 __hybrid_popcount32
#elif defined(__hybrid_popcount64)
#define __hybrid_popcount16 __hybrid_popcount64
#else /* ... */
#define __hybrid_popcount16(i) __hybrid_popcount16((__UINT16_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_popcount16)(__UINT16_TYPE__ __i) ____IMPL_DO_POPCOUNT(__UINT16_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_popcount16 */

#ifndef __hybrid_popcount32
#ifdef __hybrid_popcount64
#define __hybrid_popcount32 __hybrid_popcount64
#else /* __hybrid_popcount64 */
#define __hybrid_popcount32(i) __hybrid_popcount32((__UINT32_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_popcount32)(__UINT32_TYPE__ __i) ____IMPL_DO_POPCOUNT(__UINT32_TYPE__, __i)
#endif /* !__hybrid_popcount64 */
#endif /* !__hybrid_popcount32 */

#ifdef __UINT64_TYPE__
#ifndef __hybrid_popcount64
#define __hybrid_popcount64(i) __hybrid_popcount64((__UINT64_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_popcount64)(__UINT64_TYPE__ __i) ____IMPL_DO_POPCOUNT(__UINT64_TYPE__, __i)
#endif /* !__hybrid_popcount64 */
#endif /* __UINT64_TYPE__ */


/************************************************************************/
/* shift_t __hybrid_parity[8|16|32|64](unsigned Integer X)              */
/************************************************************************/
#ifndef __HYBRID_BIT_NO_BUILTIN
#ifdef __UINT64_TYPE__
#ifndef __hybrid_parity64
#if __has_builtin(__builtin_parity) && __SIZEOF_INT__ >= 8
#define __hybrid_parity64(i) (__SHIFT_TYPE__)__builtin_parity((unsigned int)(i))
#elif __has_builtin(__builtin_parityl) && __SIZEOF_LONG__ >= 8
#define __hybrid_parity64(i) (__SHIFT_TYPE__)__builtin_parityl((unsigned long)(i))
#elif __has_builtin(__builtin_parityll) && __SIZEOF_LONG_LONG__ >= 8
#define __hybrid_parity64(i) (__SHIFT_TYPE__)__builtin_parityll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_parityimax) && __SIZEOF_INTMAX_T__ >= 8
#define __hybrid_parity64(i) (__SHIFT_TYPE__)__builtin_parityimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_parity64 */
#endif /* __UINT64_TYPE__ */

#ifndef __hybrid_parity32
#if __has_builtin(__builtin_parity) && __SIZEOF_INT__ >= 4
#define __hybrid_parity32(i) (__SHIFT_TYPE__)__builtin_parity((unsigned int)(i))
#elif __has_builtin(__builtin_parityl) && __SIZEOF_LONG__ >= 4
#define __hybrid_parity32(i) (__SHIFT_TYPE__)__builtin_parityl((unsigned long)(i))
#elif __has_builtin(__builtin_parityll) && __SIZEOF_LONG_LONG__ >= 4
#define __hybrid_parity32(i) (__SHIFT_TYPE__)__builtin_parityll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_parityimax) && __SIZEOF_INTMAX_T__ >= 4
#define __hybrid_parity32(i) (__SHIFT_TYPE__)__builtin_parityimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_parity32 */

#ifndef __hybrid_parity16
#if __has_builtin(__builtin_parity) && __SIZEOF_INT__ >= 2
#define __hybrid_parity16(i) (__SHIFT_TYPE__)__builtin_parity((unsigned int)(i))
#elif __has_builtin(__builtin_parityl) && __SIZEOF_LONG__ >= 2
#define __hybrid_parity16(i) (__SHIFT_TYPE__)__builtin_parityl((unsigned long)(i))
#elif __has_builtin(__builtin_parityll) && __SIZEOF_LONG_LONG__ >= 2
#define __hybrid_parity16(i) (__SHIFT_TYPE__)__builtin_parityll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_parityimax) && __SIZEOF_INTMAX_T__ >= 2
#define __hybrid_parity16(i) (__SHIFT_TYPE__)__builtin_parityimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_parity16 */

#ifndef __hybrid_parity8
#if __has_builtin(__builtin_parity) && __SIZEOF_INT__ >= 1
#define __hybrid_parity8(i) (__SHIFT_TYPE__)__builtin_parity((unsigned int)(i))
#elif __has_builtin(__builtin_parityl) && __SIZEOF_LONG__ >= 1
#define __hybrid_parity8(i) (__SHIFT_TYPE__)__builtin_parityl((unsigned long)(i))
#elif __has_builtin(__builtin_parityll) && __SIZEOF_LONG_LONG__ >= 1
#define __hybrid_parity8(i) (__SHIFT_TYPE__)__builtin_parityll((__ULONGLONG)(i))
#elif __has_builtin(__builtin_parityimax) && __SIZEOF_INTMAX_T__ >= 1
#define __hybrid_parity8(i) (__SHIFT_TYPE__)__builtin_parityimax((__UINTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_parity8 */
#endif /* !__HYBRID_BIT_NO_BUILTIN */

#ifndef __hybrid_parity8
#ifdef __hybrid_parity16
#define __hybrid_parity8 __hybrid_parity16
#elif defined(__hybrid_parity32)
#define __hybrid_parity8 __hybrid_parity32
#elif defined(__hybrid_parity64)
#define __hybrid_parity8 __hybrid_parity64
#else /* ... */
#define __hybrid_parity8(i) __hybrid_parity8((__UINT8_TYPE__)i)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_parity8)(__UINT8_TYPE__ __i) ____IMPL_DO_PARITY(__UINT8_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_parity8 */

#ifndef __hybrid_parity16
#ifdef __hybrid_parity32
#define __hybrid_parity16 __hybrid_parity32
#elif defined(__hybrid_parity64)
#define __hybrid_parity16 __hybrid_parity64
#else /* ... */
#define __hybrid_parity16(i) __hybrid_parity16((__UINT16_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_parity16)(__UINT16_TYPE__ __i) ____IMPL_DO_PARITY(__UINT16_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_parity16 */

#ifndef __hybrid_parity32
#ifdef __hybrid_parity64
#define __hybrid_parity32 __hybrid_parity64
#else /* __hybrid_parity64 */
#define __hybrid_parity32(i) __hybrid_parity32((__UINT32_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_parity32)(__UINT32_TYPE__ __i) ____IMPL_DO_PARITY(__UINT32_TYPE__, __i)
#endif /* !__hybrid_parity64 */
#endif /* !__hybrid_parity32 */

#ifdef __UINT64_TYPE__
#ifndef __hybrid_parity64
#define __hybrid_parity64(i) __hybrid_parity64((__UINT64_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_parity64)(__UINT64_TYPE__ __i) ____IMPL_DO_PARITY(__UINT64_TYPE__, __i)
#endif /* !__hybrid_parity64 */
#endif /* __UINT64_TYPE__ */


/************************************************************************/
/* shift_t __hybrid_clrsb[8|16|32|64](signed Integer X)                 */
/************************************************************************/
#ifndef __HYBRID_BIT_NO_BUILTIN
#ifdef __UINT64_TYPE__
#ifndef __hybrid_clrsb64
#if __has_builtin(__builtin_clrsb) && __SIZEOF_INT__ == 8
#define __hybrid_clrsb64(i) (__SHIFT_TYPE__)__builtin_clrsb((int)(i))
#elif __has_builtin(__builtin_clrsbl) && __SIZEOF_LONG__ == 8
#define __hybrid_clrsb64(i) (__SHIFT_TYPE__)__builtin_clrsbl((long)(i))
#elif __has_builtin(__builtin_clrsbll) && __SIZEOF_LONG_LONG__ == 8
#define __hybrid_clrsb64(i) (__SHIFT_TYPE__)__builtin_clrsbll((__LONGLONG)(i))
#elif __has_builtin(__builtin_clrsbimax) && __SIZEOF_INTMAX_T__ == 8
#define __hybrid_clrsb64(i) (__SHIFT_TYPE__)__builtin_clrsbimax((__INTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_clrsb64 */
#endif /* __UINT64_TYPE__ */

#ifndef __hybrid_clrsb32
#if __has_builtin(__builtin_clrsb) && __SIZEOF_INT__ == 4
#define __hybrid_clrsb32(i) (__SHIFT_TYPE__)__builtin_clrsb((int)(i))
#elif __has_builtin(__builtin_clrsbl) && __SIZEOF_LONG__ == 4
#define __hybrid_clrsb32(i) (__SHIFT_TYPE__)__builtin_clrsbl((long)(i))
#elif __has_builtin(__builtin_clrsbll) && __SIZEOF_LONG_LONG__ == 4
#define __hybrid_clrsb32(i) (__SHIFT_TYPE__)__builtin_clrsbll((__LONGLONG)(i))
#elif __has_builtin(__builtin_clrsbimax) && __SIZEOF_INTMAX_T__ == 4
#define __hybrid_clrsb32(i) (__SHIFT_TYPE__)__builtin_clrsbimax((__INTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_clrsb32 */

#ifndef __hybrid_clrsb16
#if __has_builtin(__builtin_clrsb) && __SIZEOF_INT__ == 2
#define __hybrid_clrsb16(i) (__SHIFT_TYPE__)__builtin_clrsb((int)(i))
#elif __has_builtin(__builtin_clrsbl) && __SIZEOF_LONG__ == 2
#define __hybrid_clrsb16(i) (__SHIFT_TYPE__)__builtin_clrsbl((long)(i))
#elif __has_builtin(__builtin_clrsbll) && __SIZEOF_LONG_LONG__ == 2
#define __hybrid_clrsb16(i) (__SHIFT_TYPE__)__builtin_clrsbll((__LONGLONG)(i))
#elif __has_builtin(__builtin_clrsbimax) && __SIZEOF_INTMAX_T__ == 2
#define __hybrid_clrsb16(i) (__SHIFT_TYPE__)__builtin_clrsbimax((__INTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_clrsb16 */

#ifndef __hybrid_clrsb8
#if __has_builtin(__builtin_clrsb) && __SIZEOF_INT__ == 1
#define __hybrid_clrsb8(i) (__SHIFT_TYPE__)__builtin_clrsb((int)(i))
#elif __has_builtin(__builtin_clrsbl) && __SIZEOF_LONG__ == 1
#define __hybrid_clrsb8(i) (__SHIFT_TYPE__)__builtin_clrsbl((long)(i))
#elif __has_builtin(__builtin_clrsbll) && __SIZEOF_LONG_LONG__ == 1
#define __hybrid_clrsb8(i) (__SHIFT_TYPE__)__builtin_clrsbll((__LONGLONG)(i))
#elif __has_builtin(__builtin_clrsbimax) && __SIZEOF_INTMAX_T__ == 1
#define __hybrid_clrsb8(i) (__SHIFT_TYPE__)__builtin_clrsbimax((__INTMAX_TYPE__)(i))
#endif /* ... */
#endif /* !__hybrid_clrsb8 */
#endif /* !__HYBRID_BIT_NO_BUILTIN */

#ifndef __hybrid_clrsb8
#ifdef __hybrid_clrsb16
#define __hybrid_clrsb8(i) (__SHIFT_TYPE__)(__hybrid_clrsb16((__INT16_TYPE__)(__INT8_TYPE__)(i)) - 8)
#elif defined(__hybrid_clrsb32)
#define __hybrid_clrsb8(i) (__SHIFT_TYPE__)(__hybrid_clrsb32((__INT32_TYPE__)(__INT8_TYPE__)(i)) - 24)
#elif defined(__hybrid_clrsb64)
#define __hybrid_clrsb8(i) (__SHIFT_TYPE__)(__hybrid_clrsb64((__INT64_TYPE__)(__INT8_TYPE__)(i)) - 56)
#else /* ... */
#define __hybrid_clrsb8(i) __hybrid_clrsb8((__INT8_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_clrsb8)(__INT8_TYPE__ __i) ____IMPL_DO_CLRSB(__UINT8_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_clrsb8 */

#ifndef __hybrid_clrsb16
#ifdef __hybrid_clrsb32
#define __hybrid_clrsb16(i) (__SHIFT_TYPE__)(__hybrid_clrsb32((__INT32_TYPE__)(__INT16_TYPE__)(i)) - 16)
#elif defined(__hybrid_clrsb64)
#define __hybrid_clrsb16(i) (__SHIFT_TYPE__)(__hybrid_clrsb64((__INT64_TYPE__)(__INT16_TYPE__)(i)) - 48)
#else /* ... */
#define __hybrid_clrsb16(i) __hybrid_clrsb16((__INT16_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_clrsb16)(__INT16_TYPE__ __i) ____IMPL_DO_CLRSB(__UINT16_TYPE__, __i)
#endif /* !... */
#endif /* !__hybrid_clrsb16 */

#ifndef __hybrid_clrsb32
#ifdef __hybrid_clrsb64
#define __hybrid_clrsb32(i) (__SHIFT_TYPE__)(__hybrid_clrsb64((__INT64_TYPE__)(__INT32_TYPE__)(i)) - 32)
#else /* __hybrid_clrsb64 */
#define __hybrid_clrsb32(i) __hybrid_clrsb32((__INT32_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_clrsb32)(__INT32_TYPE__ __i) ____IMPL_DO_CLRSB(__UINT32_TYPE__, __i)
#endif /* !__hybrid_clrsb64 */
#endif /* !__hybrid_clrsb32 */

#ifdef __UINT64_TYPE__
#ifndef __hybrid_clrsb64
#define __hybrid_clrsb64(i) __hybrid_clrsb64((__INT64_TYPE__)(i))
__LOCAL __ATTR_WUNUSED __ATTR_CONST __SHIFT_TYPE__ __NOTHROW(__hybrid_clrsb64)(__INT64_TYPE__ __i) ____IMPL_DO_CLRSB(__UINT64_TYPE__, __i)
#endif /* !__hybrid_clrsb64 */
#endif /* __UINT64_TYPE__ */





#if defined(__cplusplus) && !defined(__INTELLISENSE__)
extern "C++" {
#define __hybrid_pdep   __hybrid_pdep
#define __hybrid_pdep8  __hybrid_pdep
#define __hybrid_pdep16 __hybrid_pdep
#define __hybrid_pdep32 __hybrid_pdep
#define __hybrid_pext   __hybrid_pext
#define __hybrid_pext8  __hybrid_pext
#define __hybrid_pext16 __hybrid_pext
#define __hybrid_pext32 __hybrid_pext
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT8_TYPE__ __NOTHROW(__hybrid_pdep)(__UINT8_TYPE__ __val, __UINT8_TYPE__ __mask) ____IMPL_DO_PDEP(__UINT8_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT8_TYPE__ __NOTHROW(__hybrid_pext)(__UINT8_TYPE__ __val, __UINT8_TYPE__ __mask) ____IMPL_DO_PEXT(__UINT8_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT16_TYPE__ __NOTHROW(__hybrid_pdep)(__UINT16_TYPE__ __val, __UINT16_TYPE__ __mask) ____IMPL_DO_PDEP(__UINT16_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT16_TYPE__ __NOTHROW(__hybrid_pext)(__UINT16_TYPE__ __val, __UINT16_TYPE__ __mask) ____IMPL_DO_PEXT(__UINT16_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT32_TYPE__ __NOTHROW(__hybrid_pdep)(__UINT32_TYPE__ __val, __UINT32_TYPE__ __mask) ____IMPL_DO_PDEP(__UINT32_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT32_TYPE__ __NOTHROW(__hybrid_pext)(__UINT32_TYPE__ __val, __UINT32_TYPE__ __mask) ____IMPL_DO_PEXT(__UINT32_TYPE__, __val, __mask)
#ifdef __UINT64_TYPE__
#define __hybrid_pdep64 __hybrid_pdep
#define __hybrid_pext64 __hybrid_pext
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT64_TYPE__ __NOTHROW(__hybrid_pdep)(__UINT64_TYPE__ __val, __UINT64_TYPE__ __mask) ____IMPL_DO_PDEP(__UINT64_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT64_TYPE__ __NOTHROW(__hybrid_pext)(__UINT64_TYPE__ __val, __UINT64_TYPE__ __mask) ____IMPL_DO_PEXT(__UINT64_TYPE__, __val, __mask)
#endif /* __UINT64_TYPE__ */
} /* extern "C++" */
#else /* __cplusplus */
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT8_TYPE__ __NOTHROW(__hybrid_pdep8)(__UINT8_TYPE__ __val, __UINT8_TYPE__ __mask) ____IMPL_DO_PDEP(__UINT8_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT8_TYPE__ __NOTHROW(__hybrid_pext8)(__UINT8_TYPE__ __val, __UINT8_TYPE__ __mask) ____IMPL_DO_PEXT(__UINT8_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT16_TYPE__ __NOTHROW(__hybrid_pdep16)(__UINT16_TYPE__ __val, __UINT16_TYPE__ __mask) ____IMPL_DO_PDEP(__UINT16_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT16_TYPE__ __NOTHROW(__hybrid_pext16)(__UINT16_TYPE__ __val, __UINT16_TYPE__ __mask) ____IMPL_DO_PEXT(__UINT16_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT32_TYPE__ __NOTHROW(__hybrid_pdep32)(__UINT32_TYPE__ __val, __UINT32_TYPE__ __mask) ____IMPL_DO_PDEP(__UINT32_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT32_TYPE__ __NOTHROW(__hybrid_pext32)(__UINT32_TYPE__ __val, __UINT32_TYPE__ __mask) ____IMPL_DO_PEXT(__UINT32_TYPE__, __val, __mask)
#ifdef __UINT64_TYPE__
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT64_TYPE__ __NOTHROW(__hybrid_pdep64)(__UINT64_TYPE__ __val, __UINT64_TYPE__ __mask) ____IMPL_DO_PDEP(__UINT64_TYPE__, __val, __mask)
__LOCAL __ATTR_WUNUSED __ATTR_CONST __UINT64_TYPE__ __NOTHROW(__hybrid_pext64)(__UINT64_TYPE__ __val, __UINT64_TYPE__ __mask) ____IMPL_DO_PEXT(__UINT64_TYPE__, __val, __mask)
#endif /* __UINT64_TYPE__ */
#endif /* !__cplusplus */


#undef ____IMPL_DO_PDEP
#undef ____IMPL_DO_FFS
#undef ____IMPL_DO_CLZ
#undef ____IMPL_DO_CTZ
#undef ____IMPL_DO_POPCOUNT
#undef ____IMPL_DO_PARITY
#undef ____IMPL_DO_CLRSB


#ifdef __UINT64_TYPE__
#ifndef __NO_builtin_choose_expr
#define __hybrid_ffs(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_ffs32(i), \
	__builtin_choose_expr(sizeof(i) == 8, __hybrid_ffs64(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_ffs16(i), \
	                                      __hybrid_ffs8(i))))
#define __hybrid_clz(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_clz32(i), \
	__builtin_choose_expr(sizeof(i) == 8, __hybrid_clz64(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_clz16(i), \
	                                      __hybrid_clz8(i))))
#define __hybrid_ctz(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_ctz32(i), \
	__builtin_choose_expr(sizeof(i) == 8, __hybrid_ctz64(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_ctz16(i), \
	                                      __hybrid_ctz8(i))))
#define __hybrid_popcount(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_popcount32(i), \
	__builtin_choose_expr(sizeof(i) == 8, __hybrid_popcount64(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_popcount16(i), \
	                                      __hybrid_popcount8(i))))
#define __hybrid_parity(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_parity32(i), \
	__builtin_choose_expr(sizeof(i) == 8, __hybrid_parity64(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_parity16(i), \
	                                      __hybrid_parity8(i))))
#define __hybrid_clrsb(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_clrsb32(i), \
	__builtin_choose_expr(sizeof(i) == 8, __hybrid_clrsb64(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_clrsb16(i), \
	                                      __hybrid_clrsb8(i))))
#ifndef __hybrid_pdep
#define __hybrid_pdep(value, mask)                                                                                                \
	__builtin_choose_expr(sizeof(mask) == 4, (__UINT32_TYPE__)__hybrid_pdep32((__UINT32_TYPE__)(value), (__UINT32_TYPE__)(mask)), \
	__builtin_choose_expr(sizeof(mask) == 8, (__UINT64_TYPE__)__hybrid_pdep64((__UINT64_TYPE__)(value), (__UINT64_TYPE__)(mask)), \
	__builtin_choose_expr(sizeof(mask) == 2, (__UINT16_TYPE__)__hybrid_pdep16((__UINT16_TYPE__)(value), (__UINT16_TYPE__)(mask)), \
	                                         (__UINT8_TYPE__)__hybrid_pdep8((__UINT8_TYPE__)(value), (__UINT8_TYPE__)(mask)))))
#endif /* !__hybrid_pdep */
#ifndef __hybrid_pext
#define __hybrid_pext(value, mask)                                                                                                \
	__builtin_choose_expr(sizeof(mask) == 4, (__UINT32_TYPE__)__hybrid_pext32((__UINT32_TYPE__)(value), (__UINT32_TYPE__)(mask)), \
	__builtin_choose_expr(sizeof(mask) == 8, (__UINT64_TYPE__)__hybrid_pext64((__UINT64_TYPE__)(value), (__UINT64_TYPE__)(mask)), \
	__builtin_choose_expr(sizeof(mask) == 2, (__UINT16_TYPE__)__hybrid_pext16((__UINT16_TYPE__)(value), (__UINT16_TYPE__)(mask)), \
	                                         (__UINT8_TYPE__)__hybrid_pext8((__UINT8_TYPE__)(value), (__UINT8_TYPE__)(mask)))))
#endif /* !__hybrid_pext */
#else /* !__NO_builtin_choose_expr */
#define __hybrid_ffs(i)                   \
	(sizeof(i) == 4 ? __hybrid_ffs32(i) : \
	 sizeof(i) == 8 ? __hybrid_ffs64(i) : \
	 sizeof(i) == 2 ? __hybrid_ffs16(i) : \
	                  __hybrid_ffs8(i))
#define __hybrid_clz(i)                   \
	(sizeof(i) == 4 ? __hybrid_clz32(i) : \
	 sizeof(i) == 8 ? __hybrid_clz64(i) : \
	 sizeof(i) == 2 ? __hybrid_clz16(i) : \
	                  __hybrid_clz8(i))
#define __hybrid_ctz(i)                   \
	(sizeof(i) == 4 ? __hybrid_ctz32(i) : \
	 sizeof(i) == 8 ? __hybrid_ctz64(i) : \
	 sizeof(i) == 2 ? __hybrid_ctz16(i) : \
	                  __hybrid_ctz8(i))
#define __hybrid_popcount(i)                   \
	(sizeof(i) == 4 ? __hybrid_popcount32(i) : \
	 sizeof(i) == 8 ? __hybrid_popcount64(i) : \
	 sizeof(i) == 2 ? __hybrid_popcount16(i) : \
	                  __hybrid_popcount8(i))
#define __hybrid_parity(i)                   \
	(sizeof(i) == 4 ? __hybrid_parity32(i) : \
	 sizeof(i) == 8 ? __hybrid_parity64(i) : \
	 sizeof(i) == 2 ? __hybrid_parity16(i) : \
	                  __hybrid_parity8(i))
#define __hybrid_clrsb(i)                   \
	(sizeof(i) == 4 ? __hybrid_clrsb32(i) : \
	 sizeof(i) == 8 ? __hybrid_clrsb64(i) : \
	 sizeof(i) == 2 ? __hybrid_clrsb16(i) : \
	                  __hybrid_clrsb8(i))
#ifndef __hybrid_pdep
#define __hybrid_pdep(value, mask)                                                                             \
	(sizeof(mask) == 4 ? (__UINT32_TYPE__)__hybrid_pdep32((__UINT32_TYPE__)(value), (__UINT32_TYPE__)(mask)) : \
	 sizeof(mask) == 8 ? (__UINT64_TYPE__)__hybrid_pdep64((__UINT64_TYPE__)(value), (__UINT64_TYPE__)(mask)) : \
	 sizeof(mask) == 2 ? (__UINT16_TYPE__)__hybrid_pdep16((__UINT16_TYPE__)(value), (__UINT16_TYPE__)(mask)) : \
	                     (__UINT8_TYPE__)__hybrid_pdep8((__UINT8_TYPE__)(value), (__UINT8_TYPE__)(mask)))
#endif /* !__hybrid_pdep */
#ifndef __hybrid_pext
#define __hybrid_pext(value, mask)                                                                             \
	(sizeof(mask) == 4 ? (__UINT32_TYPE__)__hybrid_pext32((__UINT32_TYPE__)(value), (__UINT32_TYPE__)(mask)) : \
	 sizeof(mask) == 8 ? (__UINT64_TYPE__)__hybrid_pext64((__UINT64_TYPE__)(value), (__UINT64_TYPE__)(mask)) : \
	 sizeof(mask) == 2 ? (__UINT16_TYPE__)__hybrid_pext16((__UINT16_TYPE__)(value), (__UINT16_TYPE__)(mask)) : \
	                     (__UINT8_TYPE__)__hybrid_pext8((__UINT8_TYPE__)(value), (__UINT8_TYPE__)(mask)))
#endif /* !__hybrid_pext */
#endif /* __NO_builtin_choose_expr */
#else /* __UINT64_TYPE__ */
#ifndef __NO_builtin_choose_expr
#define __hybrid_ffs(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_ffs32(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_ffs16(i), \
	                                      __hybrid_ffs8(i)))
#define __hybrid_clz(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_clz32(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_clz16(i), \
	                                      __hybrid_clz8(i)))
#define __hybrid_ctz(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_ctz32(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_ctz16(i), \
	                                      __hybrid_ctz8(i)))
#define __hybrid_popcount(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_popcount32(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_popcount16(i), \
	                                      __hybrid_popcount8(i)))
#define __hybrid_parity(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_parity32(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_parity16(i), \
	                                      __hybrid_parity8(i)))
#define __hybrid_clrsb(i)                                      \
	__builtin_choose_expr(sizeof(i) == 4, __hybrid_clrsb32(i), \
	__builtin_choose_expr(sizeof(i) == 2, __hybrid_clrsb16(i), \
	                                      __hybrid_clrsb8(i)))
#ifndef __hybrid_pdep
#define __hybrid_pdep(value, mask)                                                                                                \
	__builtin_choose_expr(sizeof(mask) == 4, (__UINT32_TYPE__)__hybrid_pdep32((__UINT32_TYPE__)(value), (__UINT32_TYPE__)(mask)), \
	__builtin_choose_expr(sizeof(mask) == 2, (__UINT16_TYPE__)__hybrid_pdep16((__UINT16_TYPE__)(value), (__UINT16_TYPE__)(mask)), \
	                                         (__UINT8_TYPE__)__hybrid_pdep8((__UINT8_TYPE__)(value), (__UINT8_TYPE__)(mask))))
#endif /* !__hybrid_pdep */
#ifndef __hybrid_pext
#define __hybrid_pext(value, mask)                                                                                                \
	__builtin_choose_expr(sizeof(mask) == 4, (__UINT32_TYPE__)__hybrid_pext32((__UINT32_TYPE__)(value), (__UINT32_TYPE__)(mask)), \
	__builtin_choose_expr(sizeof(mask) == 2, (__UINT16_TYPE__)__hybrid_pext16((__UINT16_TYPE__)(value), (__UINT16_TYPE__)(mask)), \
	                                         (__UINT8_TYPE__)__hybrid_pext8((__UINT8_TYPE__)(value), (__UINT8_TYPE__)(mask))))
#endif /* !__hybrid_pext */
#else /* !__NO_builtin_choose_expr */
#define __hybrid_ffs(i)                   \
	(sizeof(i) == 4 ? __hybrid_ffs32(i) : \
	 sizeof(i) == 2 ? __hybrid_ffs16(i) : \
	                  __hybrid_ffs8(i))
#define __hybrid_clz(i)                   \
	(sizeof(i) == 4 ? __hybrid_clz32(i) : \
	 sizeof(i) == 2 ? __hybrid_clz16(i) : \
	                  __hybrid_clz8(i))
#define __hybrid_ctz(i)                   \
	(sizeof(i) == 4 ? __hybrid_ctz32(i) : \
	 sizeof(i) == 2 ? __hybrid_ctz16(i) : \
	                  __hybrid_ctz8(i))
#define __hybrid_popcount(i)                   \
	(sizeof(i) == 4 ? __hybrid_popcount32(i) : \
	 sizeof(i) == 2 ? __hybrid_popcount16(i) : \
	                  __hybrid_popcount8(i))
#define __hybrid_parity(i)                   \
	(sizeof(i) == 4 ? __hybrid_parity32(i) : \
	 sizeof(i) == 2 ? __hybrid_parity16(i) : \
	                  __hybrid_parity8(i))
#define __hybrid_clrsb(i)                   \
	(sizeof(i) == 4 ? __hybrid_clrsb32(i) : \
	 sizeof(i) == 2 ? __hybrid_clrsb16(i) : \
	                  __hybrid_clrsb8(i))
#ifndef __hybrid_pdep
#define __hybrid_pdep(value, mask)                                                                             \
	(sizeof(mask) == 4 ? (__UINT32_TYPE__)__hybrid_pdep32((__UINT32_TYPE__)(value), (__UINT32_TYPE__)(mask)) : \
	 sizeof(mask) == 2 ? (__UINT16_TYPE__)__hybrid_pdep16((__UINT16_TYPE__)(value), (__UINT16_TYPE__)(mask)) : \
	                     (__UINT8_TYPE__)__hybrid_pdep8((__UINT8_TYPE__)(value), (__UINT8_TYPE__)(mask)))
#endif /* !__hybrid_pdep */
#ifndef __hybrid_pext
#define __hybrid_pext(value, mask)                                                                             \
	(sizeof(mask) == 4 ? (__UINT32_TYPE__)__hybrid_pext32((__UINT32_TYPE__)(value), (__UINT32_TYPE__)(mask)) : \
	 sizeof(mask) == 2 ? (__UINT16_TYPE__)__hybrid_pext16((__UINT16_TYPE__)(value), (__UINT16_TYPE__)(mask)) : \
	                     (__UINT8_TYPE__)__hybrid_pext8((__UINT8_TYPE__)(value), (__UINT8_TYPE__)(mask)))
#endif /* !__hybrid_pext */
#endif /* __NO_builtin_choose_expr */
#endif /* !__UINT64_TYPE__ */

__DECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID___BIT_H */
