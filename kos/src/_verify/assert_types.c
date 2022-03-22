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
#ifndef GUARD__VERIFY_ASSERT_TYPES_C
#define GUARD__VERIFY_ASSERT_TYPES_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _KOS_KERNEL_SOURCE 1
#define __WANT_FULL_STRUCT_STAT 1

#define __kos_stat_alias64 stat64

#include <hybrid/compiler.h>

#include <hybrid/floatcore.h>
#include <hybrid/limitcore.h>
#include <hybrid/typecore.h>

#include <kos/kernel/types.h>
#include <kos/types.h>
#include <sys/types.h>

#include <assert.h> /* static_assert() */
#include <signal.h>
#include <stdalign.h>
#include <stddef.h>

/* Assert type signs. */
#ifdef __CHAR_UNSIGNED__
static_assert((char)-1 > 0);
#else /* __CHAR_UNSIGNED__ */
static_assert((char)-1 < 0);
#endif /* !__CHAR_UNSIGNED__ */
#ifdef __WINT_UNSIGNED__
static_assert((wint_t)-1 > 0);
#else /* __WINT_UNSIGNED__ */
static_assert((wint_t)-1 < 0);
#endif /* !__WINT_UNSIGNED__ */
#ifdef __SIG_ATOMIC_UNSIGNED__
static_assert((sig_atomic_t)-1 > 0);
#else /* __SIG_ATOMIC_UNSIGNED__ */
static_assert((sig_atomic_t)-1 < 0);
#endif /* !__SIG_ATOMIC_UNSIGNED__ */

static_assert(__builtin_types_compatible_p(wint_t, __WINT_TYPE__));
static_assert(__builtin_types_compatible_p(sig_atomic_t, __SIG_ATOMIC_TYPE__));

static_assert(sizeof(char) == __SIZEOF_CHAR__);
static_assert(sizeof(signed char) == __SIZEOF_CHAR__);
static_assert(sizeof(unsigned char) == __SIZEOF_CHAR__);
static_assert(sizeof(short) == __SIZEOF_SHORT__);
static_assert(sizeof(signed short) == __SIZEOF_SHORT__);
static_assert(sizeof(unsigned short) == __SIZEOF_SHORT__);
static_assert(sizeof(int) == __SIZEOF_INT__);
static_assert(sizeof(signed int) == __SIZEOF_INT__);
static_assert(sizeof(unsigned int) == __SIZEOF_INT__);
static_assert(sizeof(long) == __SIZEOF_LONG__);
static_assert(sizeof(signed long) == __SIZEOF_LONG__);
static_assert(sizeof(unsigned long) == __SIZEOF_LONG__);
static_assert(alignof(char) == __ALIGNOF_CHAR__);
static_assert(alignof(signed char) == __ALIGNOF_CHAR__);
static_assert(alignof(unsigned char) == __ALIGNOF_CHAR__);
static_assert(alignof(short) == __ALIGNOF_SHORT__);
static_assert(alignof(signed short) == __ALIGNOF_SHORT__);
static_assert(alignof(unsigned short) == __ALIGNOF_SHORT__);
static_assert(alignof(int) == __ALIGNOF_INT__);
static_assert(alignof(signed int) == __ALIGNOF_INT__);
static_assert(alignof(unsigned int) == __ALIGNOF_INT__);
static_assert(alignof(long) == __ALIGNOF_LONG__);
static_assert(alignof(signed long) == __ALIGNOF_LONG__);
static_assert(alignof(unsigned long) == __ALIGNOF_LONG__);

#ifdef __COMPILER_HAVE_LONGLONG
static_assert(sizeof(long long) == __SIZEOF_LONG_LONG__);
static_assert(sizeof(signed long long) == __SIZEOF_LONG_LONG__);
static_assert(sizeof(unsigned long long) == __SIZEOF_LONG_LONG__);
static_assert(alignof(long long) == __ALIGNOF_LONG_LONG__);
static_assert(alignof(signed long long) == __ALIGNOF_LONG_LONG__);
static_assert(alignof(unsigned long long) == __ALIGNOF_LONG_LONG__);
#endif /* __COMPILER_HAVE_LONGLONG */

#ifndef __NO_FPU
static_assert(sizeof(float) == __SIZEOF_FLOAT__);
static_assert(sizeof(double) == __SIZEOF_DOUBLE__);
static_assert(alignof(float) == __ALIGNOF_FLOAT__);
static_assert(alignof(double) == __ALIGNOF_DOUBLE__);
#ifdef __COMPILER_HAVE_LONGDOUBLE
static_assert(sizeof(__LONGDOUBLE) == __SIZEOF_LONG_DOUBLE__);
static_assert(alignof(__LONGDOUBLE) == __ALIGNOF_LONG_DOUBLE__);
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */

#ifdef __native_wchar_t_defined
static_assert(__builtin_types_compatible_p(wchar_t, __WCHAR_TYPE__));
static_assert(sizeof(wchar_t) == __SIZEOF_WCHAR_T__);
static_assert(alignof(wchar_t) == __ALIGNOF_WCHAR_T__);
#ifdef __WCHAR_UNSIGNED__
static_assert((wchar_t)-1 > 0);
#else /* __WCHAR_UNSIGNED__ */
static_assert((wchar_t)-1 < 0);
#endif /* !__WCHAR_UNSIGNED__ */
#endif /* __native_wchar_t_defined */

#ifdef __native_char16_t_defined
static_assert(__builtin_types_compatible_p(char16_t, __CHAR16_TYPE__));
static_assert(__builtin_types_compatible_p(char32_t, __CHAR32_TYPE__));
static_assert(sizeof(char16_t) == 2);
static_assert(sizeof(char32_t) == 4);
static_assert(alignof(char16_t) == __ALIGNOF_INT16__);
static_assert(alignof(char32_t) == __ALIGNOF_INT32__);
#endif /* __native_char16_t_defined */

static_assert(__builtin_types_compatible_p(int8_t, __INT8_TYPE__));
static_assert(__builtin_types_compatible_p(uint8_t, __UINT8_TYPE__));
static_assert(__builtin_types_compatible_p(__int8_t, __INT8_TYPE__));
static_assert(__builtin_types_compatible_p(__uint8_t, __UINT8_TYPE__));
static_assert(__builtin_types_compatible_p(__s8, __INT8_TYPE__));
static_assert(__builtin_types_compatible_p(__u8, __UINT8_TYPE__));
static_assert(__builtin_types_compatible_p(s8, __INT8_TYPE__));
static_assert(__builtin_types_compatible_p(u8, __UINT8_TYPE__));

static_assert(__builtin_types_compatible_p(int16_t, __INT16_TYPE__));
static_assert(__builtin_types_compatible_p(uint16_t, __UINT16_TYPE__));
static_assert(__builtin_types_compatible_p(__int16_t, __INT16_TYPE__));
static_assert(__builtin_types_compatible_p(__uint16_t, __UINT16_TYPE__));
static_assert(__builtin_types_compatible_p(__s16, __INT16_TYPE__));
static_assert(__builtin_types_compatible_p(__u16, __UINT16_TYPE__));
static_assert(__builtin_types_compatible_p(s16, __INT16_TYPE__));
static_assert(__builtin_types_compatible_p(u16, __UINT16_TYPE__));

static_assert(__builtin_types_compatible_p(int32_t, __INT32_TYPE__));
static_assert(__builtin_types_compatible_p(uint32_t, __UINT32_TYPE__));
static_assert(__builtin_types_compatible_p(__int32_t, __INT32_TYPE__));
static_assert(__builtin_types_compatible_p(__uint32_t, __UINT32_TYPE__));
static_assert(__builtin_types_compatible_p(__s32, __INT32_TYPE__));
static_assert(__builtin_types_compatible_p(__u32, __UINT32_TYPE__));
static_assert(__builtin_types_compatible_p(s32, __INT32_TYPE__));
static_assert(__builtin_types_compatible_p(u32, __UINT32_TYPE__));

static_assert(sizeof(__INT8_TYPE__) == 1);
static_assert(sizeof(__UINT8_TYPE__) == 1);
static_assert(alignof(__INT8_TYPE__) == __ALIGNOF_INT8__);
static_assert(alignof(__UINT8_TYPE__) == __ALIGNOF_INT8__);

static_assert(sizeof(__INT16_TYPE__) == 2);
static_assert(sizeof(__UINT16_TYPE__) == 2);
static_assert(alignof(__INT16_TYPE__) == __ALIGNOF_INT16__);
static_assert(alignof(__UINT16_TYPE__) == __ALIGNOF_INT16__);

static_assert(sizeof(__INT32_TYPE__) == 4);
static_assert(sizeof(__UINT32_TYPE__) == 4);
static_assert(alignof(__INT32_TYPE__) == __ALIGNOF_INT32__);
static_assert(alignof(__UINT32_TYPE__) == __ALIGNOF_INT32__);

#ifdef __UINT64_TYPE__
static_assert(__builtin_types_compatible_p(int64_t, __INT64_TYPE__));
static_assert(__builtin_types_compatible_p(uint64_t, __UINT64_TYPE__));
static_assert(__builtin_types_compatible_p(__int64_t, __INT64_TYPE__));
static_assert(__builtin_types_compatible_p(__uint64_t, __UINT64_TYPE__));
static_assert(__builtin_types_compatible_p(__s64, __INT64_TYPE__));
static_assert(__builtin_types_compatible_p(__u64, __UINT64_TYPE__));
static_assert(__builtin_types_compatible_p(s64, __INT64_TYPE__));
static_assert(__builtin_types_compatible_p(u64, __UINT64_TYPE__));

static_assert(sizeof(__INT64_TYPE__) == 8);
static_assert(sizeof(__UINT64_TYPE__) == 8);
static_assert(alignof(__INT64_TYPE__) == __ALIGNOF_INT64__);
static_assert(alignof(__UINT64_TYPE__) == __ALIGNOF_INT64__);
#endif /* __UINT64_TYPE__ */

#ifdef __UINT128_TYPE__
#include <int128.h>
static_assert(__builtin_types_compatible_p(int128_t, __INT128_TYPE__));
static_assert(__builtin_types_compatible_p(uint128_t, __UINT128_TYPE__));

static_assert(sizeof(__INT128_TYPE__) == 16);
static_assert(sizeof(__UINT128_TYPE__) == 16);
static_assert(alignof(__INT128_TYPE__) == __ALIGNOF_INT128__);
static_assert(alignof(__UINT128_TYPE__) == __ALIGNOF_INT128__);
#endif /* __UINT128_TYPE__ */


#include <stdint.h>

static_assert(__builtin_types_compatible_p(intmax_t, __INTMAX_TYPE__));
static_assert(__builtin_types_compatible_p(uintmax_t, __UINTMAX_TYPE__));
static_assert(sizeof(intmax_t) == __SIZEOF_INTMAX_T__);
static_assert(sizeof(uintmax_t) == __SIZEOF_INTMAX_T__);

static_assert(__builtin_types_compatible_p(int_least8_t, __INT_LEAST8_TYPE__));
static_assert(__builtin_types_compatible_p(int_least16_t, __INT_LEAST16_TYPE__));
static_assert(__builtin_types_compatible_p(int_least32_t, __INT_LEAST32_TYPE__));
static_assert(__builtin_types_compatible_p(uint_least8_t, __UINT_LEAST8_TYPE__));
static_assert(__builtin_types_compatible_p(uint_least16_t, __UINT_LEAST16_TYPE__));
static_assert(__builtin_types_compatible_p(uint_least32_t, __UINT_LEAST32_TYPE__));
static_assert(sizeof(int_least8_t) == __SIZEOF_INT_LEAST8_T__);
static_assert(sizeof(int_least16_t) == __SIZEOF_INT_LEAST16_T__);
static_assert(sizeof(int_least32_t) == __SIZEOF_INT_LEAST32_T__);
static_assert(sizeof(uint_least8_t) == __SIZEOF_INT_LEAST8_T__);
static_assert(sizeof(uint_least16_t) == __SIZEOF_INT_LEAST16_T__);
static_assert(sizeof(uint_least32_t) == __SIZEOF_INT_LEAST32_T__);

static_assert(sizeof(int_least8_t) >= 1);
static_assert(sizeof(uint_least8_t) >= 1);
static_assert(sizeof(int_least16_t) >= 2);
static_assert(sizeof(uint_least16_t) >= 2);
static_assert(sizeof(int_least32_t) >= 4);
static_assert(sizeof(uint_least32_t) >= 4);

#ifdef __UINT_LEAST64_TYPE__
static_assert(__builtin_types_compatible_p(int_least64_t, __INT_LEAST64_TYPE__));
static_assert(__builtin_types_compatible_p(uint_least64_t, __UINT_LEAST64_TYPE__));
static_assert(sizeof(int_least64_t) == __SIZEOF_INT_LEAST64_T__);
static_assert(sizeof(uint_least64_t) == __SIZEOF_INT_LEAST64_T__);
static_assert(sizeof(int_least64_t) >= 8);
static_assert(sizeof(uint_least64_t) >= 8);
#endif /* __UINT_LEAST64_TYPE__ */

static_assert(__builtin_types_compatible_p(int_fast8_t, __INT_FAST8_TYPE__));
static_assert(__builtin_types_compatible_p(int_fast16_t, __INT_FAST16_TYPE__));
static_assert(__builtin_types_compatible_p(int_fast32_t, __INT_FAST32_TYPE__));
static_assert(__builtin_types_compatible_p(uint_fast8_t, __UINT_FAST8_TYPE__));
static_assert(__builtin_types_compatible_p(uint_fast16_t, __UINT_FAST16_TYPE__));
static_assert(__builtin_types_compatible_p(uint_fast32_t, __UINT_FAST32_TYPE__));
static_assert(sizeof(int_fast8_t) == __SIZEOF_INT_FAST8_T__);
static_assert(sizeof(int_fast16_t) == __SIZEOF_INT_FAST16_T__);
static_assert(sizeof(int_fast32_t) == __SIZEOF_INT_FAST32_T__);
static_assert(sizeof(uint_fast8_t) == __SIZEOF_INT_FAST8_T__);
static_assert(sizeof(uint_fast16_t) == __SIZEOF_INT_FAST16_T__);
static_assert(sizeof(uint_fast32_t) == __SIZEOF_INT_FAST32_T__);

#ifdef __UINT_FAST64_TYPE__
static_assert(__builtin_types_compatible_p(int_fast64_t, __INT_FAST64_TYPE__));
static_assert(__builtin_types_compatible_p(uint_fast64_t, __UINT_FAST64_TYPE__));
static_assert(sizeof(int_fast64_t) == __SIZEOF_INT_FAST64_T__);
static_assert(sizeof(uint_fast64_t) == __SIZEOF_INT_FAST64_T__);
#endif /* __UINT_FAST64_TYPE__ */

static_assert(sizeof(INT8_C(0x7f)) >= 1);
static_assert(sizeof(UINT8_C(0xff)) >= 1);
static_assert(sizeof(INT16_C(0x7fff)) >= 2);
static_assert(sizeof(UINT16_C(0xffff)) >= 2);
static_assert(sizeof(INT32_C(0x7fffffff)) >= 4);
static_assert(sizeof(UINT32_C(0xffffffff)) >= 4);
#ifdef INT64_C
static_assert(sizeof(INT64_C(0x7fffffffffffffff)) >= 8);
static_assert(sizeof(UINT64_C(0xffffffffffffffff)) >= 8);
#endif /* INT64_C */


static_assert(sizeof(__LONG32_TYPE__) == 4);
static_assert(sizeof(__ULONG32_TYPE__) == 4);
#if __SIZEOF_LONG__ == 4
static_assert(__builtin_types_compatible_p(__LONG32_TYPE__, signed long));
static_assert(__builtin_types_compatible_p(__ULONG32_TYPE__, unsigned long));
#endif /* __SIZEOF_LONG__ == 4 */

#ifdef __LONG64_TYPE__
static_assert(sizeof(__LONG64_TYPE__) == 8);
static_assert(sizeof(__ULONG64_TYPE__) == 8);
#if __SIZEOF_LONG__ == 8
static_assert(__builtin_types_compatible_p(__LONG64_TYPE__, signed long));
static_assert(__builtin_types_compatible_p(__ULONG64_TYPE__, unsigned long));
#endif /* __SIZEOF_LONG__ == 8 */
#endif /* __LONG64_TYPE__ */

static_assert(__builtin_types_compatible_p(int8_t, __INT8_TYPE__));
static_assert(__builtin_types_compatible_p(int16_t, __INT16_TYPE__));
static_assert(__builtin_types_compatible_p(int32_t, __INT32_TYPE__));
static_assert(__builtin_types_compatible_p(uint8_t, __UINT8_TYPE__));
static_assert(__builtin_types_compatible_p(uint16_t, __UINT16_TYPE__));
static_assert(__builtin_types_compatible_p(uint32_t, __UINT32_TYPE__));
static_assert(sizeof(int8_t) == 1);
static_assert(sizeof(int16_t) == 2);
static_assert(sizeof(int32_t) == 4);
static_assert(sizeof(uint8_t) == 1);
static_assert(sizeof(uint16_t) == 2);
static_assert(sizeof(uint32_t) == 4);
#ifdef __UINT64_TYPE__
static_assert(__builtin_types_compatible_p(int64_t, __INT64_TYPE__));
static_assert(__builtin_types_compatible_p(uint64_t, __UINT64_TYPE__));
static_assert(sizeof(int64_t) == 8);
static_assert(sizeof(uint64_t) == 8);
#endif /* __UINT64_TYPE__ */

static_assert(__builtin_types_compatible_p(intptr_t, __INTPTR_TYPE__));
static_assert(__builtin_types_compatible_p(uintptr_t, __UINTPTR_TYPE__));
static_assert(__builtin_types_compatible_p(longptr_t, __LONGPTR_TYPE__));
static_assert(__builtin_types_compatible_p(ulongptr_t, __ULONGPTR_TYPE__));
static_assert(sizeof(__INTPTR_TYPE__) == __SIZEOF_POINTER__);
static_assert(sizeof(__UINTPTR_TYPE__) == __SIZEOF_POINTER__);
static_assert(sizeof(__LONGPTR_TYPE__) == __SIZEOF_POINTER__);
static_assert(sizeof(__ULONGPTR_TYPE__) == __SIZEOF_POINTER__);
static_assert(sizeof(void *) == __SIZEOF_POINTER__);

static_assert(__builtin_types_compatible_p(size_t, __SIZE_TYPE__));
static_assert(__builtin_types_compatible_p(ssize_t, __SSIZE_TYPE__));
static_assert(sizeof(size_t) == __SIZEOF_SIZE_T__);
static_assert(sizeof(ssize_t) == __SIZEOF_SIZE_T__);


static_assert(INTMAX_MIN        == __INTMAX_MIN__);
static_assert(INTMAX_MAX        == __INTMAX_MAX__);
static_assert(UINTMAX_MAX       == __UINTMAX_MAX__);
static_assert(INT8_MIN          == __INT8_MIN__);
static_assert(INT16_MIN         == __INT16_MIN__);
static_assert(INT32_MIN         == __INT32_MIN__);
static_assert(INT64_MIN         == __INT64_MIN__);
static_assert(INT8_MAX          == __INT8_MAX__);
static_assert(INT16_MAX         == __INT16_MAX__);
static_assert(INT32_MAX         == __INT32_MAX__);
static_assert(INT64_MAX         == __INT64_MAX__);
static_assert(UINT8_MAX         == __UINT8_MAX__);
static_assert(UINT16_MAX        == __UINT16_MAX__);
static_assert(UINT32_MAX        == __UINT32_MAX__);
static_assert(UINT64_MAX        == __UINT64_MAX__);
static_assert(INT_LEAST8_MIN    == __INT_LEAST8_MIN__);
static_assert(INT_LEAST16_MIN   == __INT_LEAST16_MIN__);
static_assert(INT_LEAST32_MIN   == __INT_LEAST32_MIN__);
static_assert(INT_LEAST64_MIN   == __INT_LEAST64_MIN__);
static_assert(INT_LEAST8_MAX    == __INT_LEAST8_MAX__);
static_assert(INT_LEAST16_MAX   == __INT_LEAST16_MAX__);
static_assert(INT_LEAST32_MAX   == __INT_LEAST32_MAX__);
static_assert(INT_LEAST64_MAX   == __INT_LEAST64_MAX__);
static_assert(UINT_LEAST8_MAX   == __UINT_LEAST8_MAX__);
static_assert(UINT_LEAST16_MAX  == __UINT_LEAST16_MAX__);
static_assert(UINT_LEAST32_MAX  == __UINT_LEAST32_MAX__);
static_assert(UINT_LEAST64_MAX  == __UINT_LEAST64_MAX__);
static_assert(INT_FAST8_MIN     == __INT_FAST8_MIN__);
static_assert(INT_FAST16_MIN    == __INT_FAST16_MIN__);
static_assert(INT_FAST32_MIN    == __INT_FAST32_MIN__);
static_assert(INT_FAST64_MIN    == __INT_FAST64_MIN__);
static_assert(INT_FAST8_MAX     == __INT_FAST8_MAX__);
static_assert(INT_FAST16_MAX    == __INT_FAST16_MAX__);
static_assert(INT_FAST32_MAX    == __INT_FAST32_MAX__);
static_assert(INT_FAST64_MAX    == __INT_FAST64_MAX__);
static_assert(UINT_FAST8_MAX    == __UINT_FAST8_MAX__);
static_assert(UINT_FAST16_MAX   == __UINT_FAST16_MAX__);
static_assert(UINT_FAST32_MAX   == __UINT_FAST32_MAX__);
static_assert(UINT_FAST64_MAX   == __UINT_FAST64_MAX__);
static_assert(INTPTR_MIN        == __INTPTR_MIN__);
static_assert(INTPTR_MAX        == __INTPTR_MAX__);
static_assert(UINTPTR_MAX       == __UINTPTR_MAX__);
static_assert(SIZE_MAX          == __SIZE_MAX__);
static_assert(PTRDIFF_MIN       == __PTRDIFF_MIN__);
static_assert(PTRDIFF_MAX       == __PTRDIFF_MAX__);
static_assert(SIG_ATOMIC_MIN    == __SIG_ATOMIC_MIN__);
static_assert(SIG_ATOMIC_MAX    == __SIG_ATOMIC_MAX__);
static_assert(WCHAR_MIN         == __WCHAR_MIN__);
static_assert(WCHAR_MAX         == __WCHAR_MAX__);
static_assert(WINT_MIN          == __WINT_MIN__);
static_assert(WINT_MAX          == __WINT_MAX__);



#ifndef __DEEMON__
#if (defined(__SIZE_TYPE_IS_INT__) + \
     defined(__SIZE_TYPE_IS_LONG__) + \
     defined(__SIZE_TYPE_IS_LONG_LONG__)) != 1
#error "Badly configured feature macro: `__SIZE_TYPE_IS_XXX__'"
#endif

#if (defined(__PTRDIFF_TYPE_IS_INT__) + \
     defined(__PTRDIFF_TYPE_IS_LONG__) + \
     defined(__PTRDIFF_TYPE_IS_LONG_LONG__)) != 1
#error "Badly configured feature macro: `__PTRDIFF_TYPE_IS_XXX__'"
#endif
#endif /* !__DEEMON__ */

#ifdef __SIZE_TYPE_IS_INT__
static_assert(__builtin_types_compatible_p(size_t, unsigned int));
static_assert(__builtin_types_compatible_p(ssize_t, signed int));
#endif /* __SIZE_TYPE_IS_INT__ */
#ifdef __SIZE_TYPE_IS_LONG__
static_assert(__builtin_types_compatible_p(size_t, unsigned long));
static_assert(__builtin_types_compatible_p(ssize_t, signed long));
#endif /* __SIZE_TYPE_IS_LONG__ */
#ifdef __SIZE_TYPE_IS_LONG_LONG__
static_assert(__builtin_types_compatible_p(size_t, __ULONGLONG));
static_assert(__builtin_types_compatible_p(ssize_t, __LONGLONG));
#endif /* __SIZE_TYPE_IS_LONG_LONG__ */

#ifdef __PTRDIFF_TYPE_IS_INT__
static_assert(__builtin_types_compatible_p(ptrdiff_t, signed int));
#endif /* __PTRDIFF_TYPE_IS_INT__ */
#ifdef __PTRDIFF_TYPE_IS_LONG__
static_assert(__builtin_types_compatible_p(ptrdiff_t, signed long));
#endif /* __PTRDIFF_TYPE_IS_LONG__ */
#ifdef __PTRDIFF_TYPE_IS_LONG_LONG__
static_assert(__builtin_types_compatible_p(ptrdiff_t, __LONGLONG));
#endif /* __PTRDIFF_TYPE_IS_LONG_LONG__ */

#ifdef __INTPTR_TYPE_IS_INT__
static_assert(__builtin_types_compatible_p(intptr_t, signed int));
static_assert(__builtin_types_compatible_p(uintptr_t, unsigned int));
#endif /* __INTPTR_TYPE_IS_INT__ */
#ifdef __INTPTR_TYPE_IS_LONG__
static_assert(__builtin_types_compatible_p(intptr_t, signed long));
static_assert(__builtin_types_compatible_p(uintptr_t, unsigned long));
#endif /* __INTPTR_TYPE_IS_LONG__ */
#ifdef __INTPTR_TYPE_IS_LONG_LONG__
static_assert(__builtin_types_compatible_p(intptr_t, __LONGLONG));
static_assert(__builtin_types_compatible_p(uintptr_t, __ULONGLONG));
#endif /* __INTPTR_TYPE_IS_LONG_LONG__ */

/* Ensure that size_t and ptrdiff_t are actually what they're supposed to be. */
static_assert(__builtin_types_compatible_p(size_t, __typeof__(sizeof(42))));
static_assert(__builtin_types_compatible_p(ptrdiff_t, __typeof__((int *)42 - (int *)41)));

/* Ensure that our max_align_t is correctly chosen. */
static_assert(alignof(max_align_t) == __ALIGNOF_MAX_ALIGN_T__);
static_assert(__builtin_types_compatible_p(max_align_t, __MAX_ALIGN_TYPE__));
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_CHAR__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_CHAR__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_CHAR__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_SHORT__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_SHORT__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_SHORT__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_LONG__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_LONG__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_LONG__);
#ifdef __COMPILER_HAVE_LONGLONG
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_LONG_LONG__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_LONG_LONG__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_LONG_LONG__);
#endif /* __COMPILER_HAVE_LONGLONG */
#ifndef __NO_FPU
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_FLOAT__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_DOUBLE__);
#ifdef __COMPILER_HAVE_LONGDOUBLE
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_LONG_DOUBLE__);
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifdef __native_wchar_t_defined
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_WCHAR_T__);
#endif /* __native_wchar_t_defined */
#ifdef __native_char16_t_defined
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT16__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT32__);
#endif /* __native_char16_t_defined */
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT8__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT8__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT16__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT16__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT32__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT32__);
#ifdef __UINT64_TYPE__
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT64__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT64__);
#endif /* __UINT64_TYPE__ */
#ifdef __UINT128_TYPE__
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT128__);
static_assert(__ALIGNOF_MAX_ALIGN_T__ >= __ALIGNOF_INT128__);
#endif /* __UINT128_TYPE__ */


#include <pthread.h>
static_assert(sizeof(pthread_t) == __SIZEOF_PTHREAD_T);
static_assert(sizeof(pthread_key_t) == __SIZEOF_PTHREAD_KEY_T);
static_assert(sizeof(pthread_once_t) == __SIZEOF_PTHREAD_ONCE_T);
static_assert(sizeof(pthread_attr_t) == __SIZEOF_PTHREAD_ATTR_T);
static_assert(sizeof(pthread_mutex_t) == __SIZEOF_PTHREAD_MUTEX_T);
static_assert(sizeof(pthread_mutexattr_t) == __SIZEOF_PTHREAD_MUTEXATTR_T);
static_assert(sizeof(pthread_cond_t) == __SIZEOF_PTHREAD_COND_T);
static_assert(sizeof(pthread_condattr_t) == __SIZEOF_PTHREAD_CONDATTR_T);
static_assert(sizeof(pthread_rwlock_t) == __SIZEOF_PTHREAD_RWLOCK_T);
static_assert(sizeof(pthread_rwlockattr_t) == __SIZEOF_PTHREAD_RWLOCKATTR_T);
static_assert(sizeof(pthread_barrier_t) == __SIZEOF_PTHREAD_BARRIER_T);
static_assert(sizeof(pthread_barrierattr_t) == __SIZEOF_PTHREAD_BARRIERATTR_T);


#include <threads.h>
static_assert(sizeof(thrd_t) == __SIZEOF_PTHREAD_T);
static_assert(sizeof(tss_t) == __SIZEOF_PTHREAD_KEY_T);
static_assert(sizeof(once_flag) == __SIZEOF_PTHREAD_ONCE_T);
static_assert(sizeof(mtx_t) == __SIZEOF_PTHREAD_MUTEX_T);
static_assert(sizeof(cnd_t) == __SIZEOF_PTHREAD_COND_T);


#include <elf.h>
static_assert(sizeof(Elf32_Half) == __SIZEOF_ELF32_HALF__);
static_assert(sizeof(Elf64_Half) == __SIZEOF_ELF64_HALF__);
static_assert(sizeof(Elf32_Word) == __SIZEOF_ELF32_WORD__);
static_assert(sizeof(Elf64_Word) == __SIZEOF_ELF64_WORD__);
static_assert(sizeof(Elf32_Xword) == __SIZEOF_ELF32_XWORD__);
static_assert(sizeof(Elf64_Xword) == __SIZEOF_ELF64_XWORD__);
static_assert(sizeof(Elf32_Addr) == __SIZEOF_ELF32_ADDR__);
static_assert(sizeof(Elf64_Addr) == __SIZEOF_ELF64_ADDR__);
static_assert(sizeof(Elf32_Off) == __SIZEOF_ELF32_OFF__);
static_assert(sizeof(Elf64_Off) == __SIZEOF_ELF64_OFF__);
static_assert(sizeof(Elf32_Section) == __SIZEOF_ELF32_SECTION__);
static_assert(sizeof(Elf64_Section) == __SIZEOF_ELF64_SECTION__);
static_assert(sizeof(Elf32_Versym) == __SIZEOF_ELF32_VERSYM__);
static_assert(sizeof(Elf64_Versym) == __SIZEOF_ELF64_VERSYM__);


/*[[[deemon
import * from ...misc.libgen.assert_offsetof;
local files = {
	"../../include/bits/os/cygwin/sigaction.h",
	"../../include/bits/os/cygwin/stat.h",
	"../../include/bits/os/dos/stat.h",
	"../../include/bits/os/generic/iovec.h",
	"../../include/bits/os/generic/itimerspec.h",
	"../../include/bits/os/generic/itimerval.h",
	"../../include/bits/os/generic/timespec.h",
	"../../include/bits/os/generic/timeval.h",
	"../../include/bits/os/generic/stat.h",
	"../../include/bits/os/generic/sockaddr_storage.h",
	"../../include/bits/os/generic/sockaddr.h",
	"../../include/bits/os/kos/cmsghdr.h",
	"../../include/bits/os/kos/flock.h",
	"../../include/bits/os/mcontext.h",
	"../../include/bits/os/kos/mmsghdr.h",
	"../../include/bits/os/kos/msghdr.h",
	"../../include/bits/os/kos/pollfd.h",
	"../../include/bits/os/kos/rusage.h",
	"../../include/bits/os/kos/sched.h",
	"../../include/bits/os/kos/sigaction.h",
	"../../include/bits/os/kos/siginfo.h",
	"../../include/bits/os/kos/stat.h",
	"../../include/bits/os/kos/statfs.h",
	"../../include/bits/os/kos/timeb.h",
	"../../include/bits/os/kos/ustat.h",
	"../../include/bits/os/kos/utimbuf.h",
	"../../include/bits/os/kos/utsname.h",
	"../../include/bits/crt/ntptimeval.h",
	"../../include/bits/os/kos/timex.h",
	"../../include/bits/os/kos/tms.h",
	"../../include/bits/os/linux/stat.h",
	"../../include/elf.h",
	"../../include/kos/bits/debugtrap.h",
	"../../include/kos/bits/ukern-struct.h",
	"../../include/kos/bits/userprocmask.h",
	"../../include/kos/exec/bits/peb.h",
	"../../include/kos/exec/elf.h",
	"../../include/kos/ioctl/_openfd.h",
	"../../include/kos/ksysctl.h",
	"../../include/linux/if_arp.h",
	"../../include/linux/if_ether.h",
	"../../include/netinet/ip.h",
	"../../include/netinet/udp.h",
};

local include_prefixes = {
	"../../include",
};

function genAsserts(f) {
	for (local pfx: include_prefixes) {
		if (f.startswith(pfx)) {
			print "#include <" + f[#pfx:].lstrip("/") + ">";
			goto do_gen_asserts;
		}
	}
	print "#include", repr(f);
do_gen_asserts:
	generateAssertions(f);
	print;
	print;
	print;
	print;
	print;
}

for (local f: files)
	genAsserts(f);

print "#undef sigev_value";
print "#undef sigev_signo";
print "#undef sigev_notify";
print "#undef sigev_notify_function";
print "#undef sigev_notify_attributes";
genAsserts("../../include/bits/os/cygwin/sigevent.h");

print "#undef si_signo";
print "#undef si_code";
print "#undef si_pid";
print "#undef si_uid";
print "#undef si_errno";
print "#undef _si_data";
print "#undef _si_commune";
print "#undef si_sigval";
print "#undef si_value";
print "#undef si_tid";
print "#undef si_overrun";
print "#undef si_status";
print "#undef si_utime";
print "#undef si_stime";
print "#undef si_addr";
genAsserts("../../include/bits/os/cygwin/siginfo.h");

]]]*/
#include <bits/os/cygwin/sigaction.h>

/* struct __sigaction_cygwin */
static_assert(offsetof(struct __sigaction_cygwin, sa_flags) == __OFFSET_SIGACTION_CYGWIN_FLAGS);
static_assert(offsetof(struct __sigaction_cygwin, sa_handler) == __OFFSET_SIGACTION_CYGWIN_HANDLER);
static_assert(offsetof(struct __sigaction_cygwin, sa_mask) == __OFFSET_SIGACTION_CYGWIN_MASK);
static_assert(offsetof(struct __sigaction_cygwin, sa_sigaction) == __OFFSET_SIGACTION_CYGWIN_SIGACTION);
static_assert(sizeof(struct __sigaction_cygwin) == __SIZEOF_SIGACTION_CYGWIN);
static_assert(alignof(struct __sigaction_cygwin) == __ALIGNOF_SIGACTION_CYGWIN);





#include <bits/os/cygwin/stat.h>

/* struct __cyg_stat */
/* ... */

/* struct __cyg_stat_alias64 */
/* ... */





#include <bits/os/dos/stat.h>

/* struct __dos_bstat */
/* ... */

/* struct __dos_bstat64 */
/* ... */

/* struct __dos_stat32 */
/* ... */

/* struct __dos_stat32i64 */
/* ... */

/* struct __dos_stat64i32 */
/* ... */

/* struct __dos_stat64 */
/* ... */





#include <bits/os/generic/iovec.h>

/* struct iovec */
static_assert(offsetof(struct iovec, iov_base) == __OFFSET_IOVEC_BASE);
static_assert(offsetof(struct iovec, iov_len) == __OFFSET_IOVEC_LEN);
static_assert(sizeof(struct iovec) == __SIZEOF_IOVEC);





#include <bits/os/generic/itimerspec.h>

/* struct itimerspec */
static_assert(offsetof(struct itimerspec, it_interval) == __OFFSET_ITIMERSPEC_INTERVAL);
static_assert(offsetof(struct itimerspec, it_value) == __OFFSET_ITIMERSPEC_VALUE);
static_assert(sizeof(struct itimerspec) == __SIZEOF_ITIMERSPEC);

/* struct __itimerspec64 */
static_assert(offsetof(struct __itimerspec64, it_interval) == __OFFSET_ITIMERSPEC64_INTERVAL);
static_assert(offsetof(struct __itimerspec64, it_value) == __OFFSET_ITIMERSPEC64_VALUE);
static_assert(sizeof(struct __itimerspec64) == __SIZEOF_ITIMERSPEC64);

/* struct __itimerspec32 */
static_assert(offsetof(struct __itimerspec32, it_interval) == __OFFSET_ITIMERSPEC32_INTERVAL);
static_assert(offsetof(struct __itimerspec32, it_value) == __OFFSET_ITIMERSPEC32_VALUE);
static_assert(sizeof(struct __itimerspec32) == __SIZEOF_ITIMERSPEC32);





#include <bits/os/generic/itimerval.h>

/* struct itimerval */
static_assert(offsetof(struct itimerval, it_interval) == __OFFSET_ITIMERVAL_INTERVAL);
static_assert(offsetof(struct itimerval, it_value) == __OFFSET_ITIMERVAL_VALUE);
static_assert(sizeof(struct itimerval) == __SIZEOF_ITIMERVAL);

/* struct __itimerval64 */
static_assert(offsetof(struct __itimerval64, it_interval) == __OFFSET_ITIMERVAL64_INTERVAL);
static_assert(offsetof(struct __itimerval64, it_value) == __OFFSET_ITIMERVAL64_VALUE);
static_assert(sizeof(struct __itimerval64) == __SIZEOF_ITIMERVAL64);

/* struct __itimerval32 */
static_assert(offsetof(struct __itimerval32, it_interval) == __OFFSET_ITIMERVAL32_INTERVAL);
static_assert(offsetof(struct __itimerval32, it_value) == __OFFSET_ITIMERVAL32_VALUE);
static_assert(sizeof(struct __itimerval32) == __SIZEOF_ITIMERVAL32);





#include <bits/os/generic/timespec.h>

/* struct timespec */
static_assert(offsetof(struct timespec, tv_nsec) == __OFFSET_TIMESPEC_NSEC);
static_assert(offsetof(struct timespec, tv_sec) == __OFFSET_TIMESPEC_SEC);
static_assert(sizeof(struct timespec) == __SIZEOF_TIMESPEC);

/* struct __timespec64 */
static_assert(offsetof(struct __timespec64, tv_nsec) == __OFFSET_TIMESPEC64_NSEC);
static_assert(offsetof(struct __timespec64, tv_sec) == __OFFSET_TIMESPEC64_SEC);
static_assert(sizeof(struct __timespec64) == __SIZEOF_TIMESPEC64);

/* struct __timespec32 */
static_assert(offsetof(struct __timespec32, tv_nsec) == __OFFSET_TIMESPEC32_NSEC);
static_assert(offsetof(struct __timespec32, tv_sec) == __OFFSET_TIMESPEC32_SEC);
static_assert(sizeof(struct __timespec32) == __SIZEOF_TIMESPEC32);





#include <bits/os/generic/timeval.h>

/* struct timeval */
static_assert(offsetof(struct timeval, tv_sec) == __OFFSET_TIMEVAL_SEC);
static_assert(offsetof(struct timeval, tv_usec) == __OFFSET_TIMEVAL_USEC);
static_assert(sizeof(struct timeval) == __SIZEOF_TIMEVAL);

/* struct __timeval64 */
static_assert(offsetof(struct __timeval64, tv_sec) == __OFFSET_TIMEVAL64_SEC);
static_assert(offsetof(struct __timeval64, tv_usec) == __OFFSET_TIMEVAL64_USEC);
static_assert(sizeof(struct __timeval64) == __SIZEOF_TIMEVAL64);

/* struct __timeval32 */
static_assert(offsetof(struct __timeval32, tv_sec) == __OFFSET_TIMEVAL32_SEC);
static_assert(offsetof(struct __timeval32, tv_usec) == __OFFSET_TIMEVAL32_USEC);
static_assert(sizeof(struct __timeval32) == __SIZEOF_TIMEVAL32);





#include <bits/os/generic/stat.h>

/* struct __gen_stat */
/* ... */

/* struct __gen_stat64 */
/* ... */





#include <bits/os/generic/sockaddr_storage.h>

/* struct sockaddr_storage */
static_assert(sizeof(struct sockaddr_storage) == __SIZEOF_SOCKADDR_STORAGE);
static_assert(alignof(struct sockaddr_storage) == __ALIGNOF_SOCKADDR_STORAGE);





#include <bits/os/generic/sockaddr.h>

/* struct sockaddr */
static_assert(sizeof(struct sockaddr) == __SIZEOF_SOCKADDR);
static_assert(alignof(struct sockaddr) == __ALIGNOF_SOCKADDR);





#include <bits/os/kos/cmsghdr.h>

/* struct cmsghdr */
static_assert(offsetof(struct cmsghdr, cmsg_data) == __OFFSET_CMSGHDR_DATA);
static_assert(offsetof(struct cmsghdr, cmsg_len) == __OFFSET_CMSGHDR_LEN);
static_assert(offsetof(struct cmsghdr, cmsg_level) == __OFFSET_CMSGHDR_LEVEL);
static_assert(offsetof(struct cmsghdr, cmsg_type) == __OFFSET_CMSGHDR_TYPE);
static_assert(alignof(struct cmsghdr) == __ALIGNOF_CMSGHDR);





#include <bits/os/kos/flock.h>

/* struct flock */
static_assert(offsetof(struct flock, l_len) == __OFFSET_FLOCK_LEN);
static_assert(offsetof(struct flock, l_pid) == __OFFSET_FLOCK_PID);
static_assert(offsetof(struct flock, l_start) == __OFFSET_FLOCK_START);
static_assert(offsetof(struct flock, l_type) == __OFFSET_FLOCK_TYPE);
static_assert(offsetof(struct flock, l_whence) == __OFFSET_FLOCK_WHENCE);
static_assert(sizeof(struct flock) == __SIZEOF_FLOCK);

/* struct __flock64 */
static_assert(offsetof(struct __flock64, l_len) == __OFFSET_FLOCK64_LEN);
static_assert(offsetof(struct __flock64, l_pid) == __OFFSET_FLOCK64_PID);
static_assert(offsetof(struct __flock64, l_start) == __OFFSET_FLOCK64_START);
static_assert(offsetof(struct __flock64, l_type) == __OFFSET_FLOCK64_TYPE);
static_assert(offsetof(struct __flock64, l_whence) == __OFFSET_FLOCK64_WHENCE);
static_assert(sizeof(struct __flock64) == __SIZEOF_FLOCK64);

/* struct __flock32 */
static_assert(offsetof(struct __flock32, l_len) == __OFFSET_FLOCK32_LEN);
static_assert(offsetof(struct __flock32, l_pid) == __OFFSET_FLOCK32_PID);
static_assert(offsetof(struct __flock32, l_start) == __OFFSET_FLOCK32_START);
static_assert(offsetof(struct __flock32, l_type) == __OFFSET_FLOCK32_TYPE);
static_assert(offsetof(struct __flock32, l_whence) == __OFFSET_FLOCK32_WHENCE);
static_assert(sizeof(struct __flock32) == __SIZEOF_FLOCK32);





#include <bits/os/mcontext.h>

/* struct mcontext */
static_assert(sizeof(struct mcontext) == __SIZEOF_MCONTEXT);
static_assert(alignof(struct mcontext) == __ALIGNOF_MCONTEXT);





#include <bits/os/kos/mmsghdr.h>

/* struct mmsghdr */
static_assert(offsetof(struct mmsghdr, msg_hdr) == __OFFSET_MMSGHDR_HDR);
static_assert(offsetof(struct mmsghdr, msg_len) == __OFFSET_MMSGHDR_LEN);
static_assert(sizeof(struct mmsghdr) == __SIZEOF_MMSGHDR);
static_assert(alignof(struct mmsghdr) == __ALIGNOF_MMSGHDR);





#include <bits/os/kos/msghdr.h>

/* struct msghdr */
static_assert(offsetof(struct msghdr, msg_control) == __OFFSET_MSGHDR_CONTROL);
static_assert(offsetof(struct msghdr, msg_controllen) == __OFFSET_MSGHDR_CONTROLLEN);
static_assert(offsetof(struct msghdr, msg_flags) == __OFFSET_MSGHDR_FLAGS);
static_assert(offsetof(struct msghdr, msg_iov) == __OFFSET_MSGHDR_IOV);
static_assert(offsetof(struct msghdr, msg_iovlen) == __OFFSET_MSGHDR_IOVLEN);
static_assert(offsetof(struct msghdr, msg_name) == __OFFSET_MSGHDR_NAME);
static_assert(offsetof(struct msghdr, msg_namelen) == __OFFSET_MSGHDR_NAMELEN);
static_assert(sizeof(struct msghdr) == __SIZEOF_MSGHDR);
static_assert(alignof(struct msghdr) == __ALIGNOF_MSGHDR);





#include <bits/os/kos/pollfd.h>

/* struct pollfd */
static_assert(offsetof(struct pollfd, events) == __OFFSET_POLLFD_EVENTS);
static_assert(offsetof(struct pollfd, fd) == __OFFSET_POLLFD_FD);
static_assert(offsetof(struct pollfd, revents) == __OFFSET_POLLFD_REVENTS);
static_assert(sizeof(struct pollfd) == __SIZEOF_POLLFD);
static_assert(alignof(struct pollfd) == __ALIGNOF_POLLFD);





#include <bits/os/kos/rusage.h>

/* struct rusage */
static_assert(offsetof(struct rusage, ru_idrss) == __OFFSET_RUSAGE_IDRSS);
static_assert(offsetof(struct rusage, ru_inblock) == __OFFSET_RUSAGE_INBLOCK);
static_assert(offsetof(struct rusage, ru_isrss) == __OFFSET_RUSAGE_ISRSS);
static_assert(offsetof(struct rusage, ru_ixrss) == __OFFSET_RUSAGE_IXRSS);
static_assert(offsetof(struct rusage, ru_majflt) == __OFFSET_RUSAGE_MAJFLT);
static_assert(offsetof(struct rusage, ru_maxrss) == __OFFSET_RUSAGE_MAXRSS);
static_assert(offsetof(struct rusage, ru_minflt) == __OFFSET_RUSAGE_MINFLT);
static_assert(offsetof(struct rusage, ru_msgrcv) == __OFFSET_RUSAGE_MSGRCV);
static_assert(offsetof(struct rusage, ru_msgsnd) == __OFFSET_RUSAGE_MSGSND);
static_assert(offsetof(struct rusage, ru_nivcsw) == __OFFSET_RUSAGE_NIVCSW);
static_assert(offsetof(struct rusage, ru_nsignals) == __OFFSET_RUSAGE_NSIGNALS);
static_assert(offsetof(struct rusage, ru_nswap) == __OFFSET_RUSAGE_NSWAP);
static_assert(offsetof(struct rusage, ru_nvcsw) == __OFFSET_RUSAGE_NVCSW);
static_assert(offsetof(struct rusage, ru_oublock) == __OFFSET_RUSAGE_OUBLOCK);
static_assert(offsetof(struct rusage, ru_stime) == __OFFSET_RUSAGE_STIME);
static_assert(offsetof(struct rusage, ru_utime) == __OFFSET_RUSAGE_UTIME);
static_assert(sizeof(struct rusage) == __SIZEOF_RUSAGE);

/* struct __rusage64 */
static_assert(offsetof(struct __rusage64, ru_idrss) == __OFFSET_RUSAGE64_IDRSS);
static_assert(offsetof(struct __rusage64, ru_inblock) == __OFFSET_RUSAGE64_INBLOCK);
static_assert(offsetof(struct __rusage64, ru_isrss) == __OFFSET_RUSAGE64_ISRSS);
static_assert(offsetof(struct __rusage64, ru_ixrss) == __OFFSET_RUSAGE64_IXRSS);
static_assert(offsetof(struct __rusage64, ru_majflt) == __OFFSET_RUSAGE64_MAJFLT);
static_assert(offsetof(struct __rusage64, ru_maxrss) == __OFFSET_RUSAGE64_MAXRSS);
static_assert(offsetof(struct __rusage64, ru_minflt) == __OFFSET_RUSAGE64_MINFLT);
static_assert(offsetof(struct __rusage64, ru_msgrcv) == __OFFSET_RUSAGE64_MSGRCV);
static_assert(offsetof(struct __rusage64, ru_msgsnd) == __OFFSET_RUSAGE64_MSGSND);
static_assert(offsetof(struct __rusage64, ru_nivcsw) == __OFFSET_RUSAGE64_NIVCSW);
static_assert(offsetof(struct __rusage64, ru_nsignals) == __OFFSET_RUSAGE64_NSIGNALS);
static_assert(offsetof(struct __rusage64, ru_nswap) == __OFFSET_RUSAGE64_NSWAP);
static_assert(offsetof(struct __rusage64, ru_nvcsw) == __OFFSET_RUSAGE64_NVCSW);
static_assert(offsetof(struct __rusage64, ru_oublock) == __OFFSET_RUSAGE64_OUBLOCK);
static_assert(offsetof(struct __rusage64, ru_stime) == __OFFSET_RUSAGE64_STIME);
static_assert(offsetof(struct __rusage64, ru_utime) == __OFFSET_RUSAGE64_UTIME);
static_assert(sizeof(struct __rusage64) == __SIZEOF_RUSAGE64);

/* struct __rusage32 */
static_assert(offsetof(struct __rusage32, ru_idrss) == __OFFSET_RUSAGE32_IDRSS);
static_assert(offsetof(struct __rusage32, ru_inblock) == __OFFSET_RUSAGE32_INBLOCK);
static_assert(offsetof(struct __rusage32, ru_isrss) == __OFFSET_RUSAGE32_ISRSS);
static_assert(offsetof(struct __rusage32, ru_ixrss) == __OFFSET_RUSAGE32_IXRSS);
static_assert(offsetof(struct __rusage32, ru_majflt) == __OFFSET_RUSAGE32_MAJFLT);
static_assert(offsetof(struct __rusage32, ru_maxrss) == __OFFSET_RUSAGE32_MAXRSS);
static_assert(offsetof(struct __rusage32, ru_minflt) == __OFFSET_RUSAGE32_MINFLT);
static_assert(offsetof(struct __rusage32, ru_msgrcv) == __OFFSET_RUSAGE32_MSGRCV);
static_assert(offsetof(struct __rusage32, ru_msgsnd) == __OFFSET_RUSAGE32_MSGSND);
static_assert(offsetof(struct __rusage32, ru_nivcsw) == __OFFSET_RUSAGE32_NIVCSW);
static_assert(offsetof(struct __rusage32, ru_nsignals) == __OFFSET_RUSAGE32_NSIGNALS);
static_assert(offsetof(struct __rusage32, ru_nswap) == __OFFSET_RUSAGE32_NSWAP);
static_assert(offsetof(struct __rusage32, ru_nvcsw) == __OFFSET_RUSAGE32_NVCSW);
static_assert(offsetof(struct __rusage32, ru_oublock) == __OFFSET_RUSAGE32_OUBLOCK);
static_assert(offsetof(struct __rusage32, ru_stime) == __OFFSET_RUSAGE32_STIME);
static_assert(offsetof(struct __rusage32, ru_utime) == __OFFSET_RUSAGE32_UTIME);
static_assert(sizeof(struct __rusage32) == __SIZEOF_RUSAGE32);





#include <bits/os/kos/sched.h>

/* struct sched_param */
static_assert(offsetof(struct sched_param, sched_priority) == __OFFSET_SCHED_PARAM_SCHED_PRIORITY);
static_assert(sizeof(struct sched_param) == __SIZEOF_SCHED_PARAM);
static_assert(alignof(struct sched_param) == __ALIGNOF_SCHED_PARAM);





#include <bits/os/kos/sigaction.h>

/* struct sigaction */
static_assert(offsetof(struct sigaction, sa_flags) == __OFFSET_SIGACTION_FLAGS);
static_assert(offsetof(struct sigaction, sa_handler) == __OFFSET_SIGACTION_HANDLER);
static_assert(offsetof(struct sigaction, sa_mask) == __OFFSET_SIGACTION_MASK);
static_assert(offsetof(struct sigaction, sa_restorer) == __OFFSET_SIGACTION_RESTORER);
static_assert(offsetof(struct sigaction, sa_sigaction) == __OFFSET_SIGACTION_SIGACTION);
static_assert(sizeof(struct sigaction) == __SIZEOF_SIGACTION);
static_assert(alignof(struct sigaction) == __ALIGNOF_SIGACTION);

/* struct __kernel_sigaction */
static_assert(offsetof(struct __kernel_sigaction, sa_flags) == __OFFSET_KERNEL_SIGACTION_FLAGS);
static_assert(offsetof(struct __kernel_sigaction, sa_handler) == __OFFSET_KERNEL_SIGACTION_HANDLER);
static_assert(offsetof(struct __kernel_sigaction, sa_mask) == __OFFSET_KERNEL_SIGACTION_MASK);
static_assert(offsetof(struct __kernel_sigaction, sa_restorer) == __OFFSET_KERNEL_SIGACTION_RESTORER);
static_assert(alignof(struct __kernel_sigaction) == __ALIGNOF_KERNEL_SIGACTION);

/* struct __old_kernel_sigaction */
/* ... */





#include <bits/os/kos/siginfo.h>

/* struct __siginfo_struct */
static_assert(offsetof(struct __siginfo_struct, si_addr) == __OFFSET_SIGINFO_ADDR);
static_assert(offsetof(struct __siginfo_struct, si_addr_lsb) == __OFFSET_SIGINFO_ADDR_LSB);
static_assert(offsetof(struct __siginfo_struct, si_arch) == __OFFSET_SIGINFO_ARCH);
static_assert(offsetof(struct __siginfo_struct, si_band) == __OFFSET_SIGINFO_BAND);
static_assert(offsetof(struct __siginfo_struct, si_call_addr) == __OFFSET_SIGINFO_CALL_ADDR);
static_assert(offsetof(struct __siginfo_struct, si_code) == __OFFSET_SIGINFO_CODE);
static_assert(offsetof(struct __siginfo_struct, si_errno) == __OFFSET_SIGINFO_ERRNO);
static_assert(offsetof(struct __siginfo_struct, si_fd) == __OFFSET_SIGINFO_FD);
static_assert(offsetof(struct __siginfo_struct, si_int) == __OFFSET_SIGINFO_INT);
static_assert(offsetof(struct __siginfo_struct, si_lower) == __OFFSET_SIGINFO_LOWER);
static_assert(offsetof(struct __siginfo_struct, si_overrun) == __OFFSET_SIGINFO_OVERRUN);
static_assert(offsetof(struct __siginfo_struct, si_pid) == __OFFSET_SIGINFO_PID);
static_assert(offsetof(struct __siginfo_struct, si_ptr) == __OFFSET_SIGINFO_PTR);
static_assert(offsetof(struct __siginfo_struct, si_signo) == __OFFSET_SIGINFO_SIGNO);
static_assert(offsetof(struct __siginfo_struct, si_status) == __OFFSET_SIGINFO_STATUS);
static_assert(offsetof(struct __siginfo_struct, si_stime) == __OFFSET_SIGINFO_STIME);
static_assert(offsetof(struct __siginfo_struct, si_syscall) == __OFFSET_SIGINFO_SYSCALL);
static_assert(offsetof(struct __siginfo_struct, si_timerid) == __OFFSET_SIGINFO_TIMERID);
static_assert(offsetof(struct __siginfo_struct, si_uid) == __OFFSET_SIGINFO_UID);
static_assert(offsetof(struct __siginfo_struct, si_upper) == __OFFSET_SIGINFO_UPPER);
static_assert(offsetof(struct __siginfo_struct, si_utime) == __OFFSET_SIGINFO_UTIME);
static_assert(offsetof(struct __siginfo_struct, si_value) == __OFFSET_SIGINFO_VALUE);
static_assert(sizeof(struct __siginfo_struct) == __SIZEOF_SIGINFO);





#include <bits/os/kos/stat.h>

/* struct __stat_timespec32 */
/* ... */

/* struct __kos_stat */
static_assert(offsetof(struct __kos_stat, st_atime) == __OFFSET_KOS_STAT_ATIME);
static_assert(offsetof(struct __kos_stat, st_atimensec) == __OFFSET_KOS_STAT_ATIMENSEC);
static_assert(offsetof(struct __kos_stat, st_atimespec) == __OFFSET_KOS_STAT_ATIMESPEC);
static_assert(offsetof(struct __kos_stat, st_blksize) == __OFFSET_KOS_STAT_BLKSIZE);
static_assert(offsetof(struct __kos_stat, st_blocks) == __OFFSET_KOS_STAT_BLOCKS);
static_assert(offsetof(struct __kos_stat, st_btime) == __OFFSET_KOS_STAT_BTIME);
static_assert(offsetof(struct __kos_stat, st_btimensec) == __OFFSET_KOS_STAT_BTIMENSEC);
static_assert(offsetof(struct __kos_stat, st_btimespec) == __OFFSET_KOS_STAT_BTIMESPEC);
static_assert(offsetof(struct __kos_stat, st_ctime) == __OFFSET_KOS_STAT_CTIME);
static_assert(offsetof(struct __kos_stat, st_ctimensec) == __OFFSET_KOS_STAT_CTIMENSEC);
static_assert(offsetof(struct __kos_stat, st_ctimespec) == __OFFSET_KOS_STAT_CTIMESPEC);
static_assert(offsetof(struct __kos_stat, st_dev) == __OFFSET_KOS_STAT_DEV);
static_assert(offsetof(struct __kos_stat, st_gid) == __OFFSET_KOS_STAT_GID);
static_assert(offsetof(struct __kos_stat, st_ino) == __OFFSET_KOS_STAT_INO);
static_assert(offsetof(struct __kos_stat, st_mode) == __OFFSET_KOS_STAT_MODE);
static_assert(offsetof(struct __kos_stat, st_mtime) == __OFFSET_KOS_STAT_MTIME);
static_assert(offsetof(struct __kos_stat, st_mtimensec) == __OFFSET_KOS_STAT_MTIMENSEC);
static_assert(offsetof(struct __kos_stat, st_mtimespec) == __OFFSET_KOS_STAT_MTIMESPEC);
static_assert(offsetof(struct __kos_stat, st_nlink) == __OFFSET_KOS_STAT_NLINK);
static_assert(offsetof(struct __kos_stat, st_rdev) == __OFFSET_KOS_STAT_RDEV);
static_assert(offsetof(struct __kos_stat, st_size) == __OFFSET_KOS_STAT_SIZE);
static_assert(offsetof(struct __kos_stat, st_uid) == __OFFSET_KOS_STAT_UID);
static_assert(sizeof(struct __kos_stat) == __SIZEOF_KOS_STAT);
static_assert(alignof(struct __kos_stat) == __ALIGNOF_KOS_STAT);

/* struct __kos_stat_alias64 */
/* ... */





#include <bits/os/kos/statfs.h>

/* struct statfs */
static_assert(offsetof(struct statfs, f_bavail) == __OFFSET_STATFS_BAVAIL);
static_assert(offsetof(struct statfs, f_bfree) == __OFFSET_STATFS_BFREE);
static_assert(offsetof(struct statfs, f_blocks) == __OFFSET_STATFS_BLOCKS);
static_assert(offsetof(struct statfs, f_bsize) == __OFFSET_STATFS_BSIZE);
static_assert(offsetof(struct statfs, f_ffree) == __OFFSET_STATFS_FFREE);
static_assert(offsetof(struct statfs, f_files) == __OFFSET_STATFS_FILES);
static_assert(offsetof(struct statfs, f_flags) == __OFFSET_STATFS_FLAGS);
static_assert(offsetof(struct statfs, f_frsize) == __OFFSET_STATFS_FRSIZE);
static_assert(offsetof(struct statfs, f_fsid) == __OFFSET_STATFS_FSID);
static_assert(offsetof(struct statfs, f_namelen) == __OFFSET_STATFS_NAMELEN);
static_assert(offsetof(struct statfs, f_spare) == __OFFSET_STATFS_SPARE);
static_assert(offsetof(struct statfs, f_type) == __OFFSET_STATFS_TYPE);
static_assert(sizeof(struct statfs) == __SIZEOF_STATFS);
static_assert(alignof(struct statfs) == __ALIGNOF_STATFS);

/* struct statfs32 */
static_assert(offsetof(struct statfs32, f_bavail) == __OFFSET_STATFS32_BAVAIL);
static_assert(offsetof(struct statfs32, f_bfree) == __OFFSET_STATFS32_BFREE);
static_assert(offsetof(struct statfs32, f_blocks) == __OFFSET_STATFS32_BLOCKS);
static_assert(offsetof(struct statfs32, f_bsize) == __OFFSET_STATFS32_BSIZE);
static_assert(offsetof(struct statfs32, f_ffree) == __OFFSET_STATFS32_FFREE);
static_assert(offsetof(struct statfs32, f_files) == __OFFSET_STATFS32_FILES);
static_assert(offsetof(struct statfs32, f_flags) == __OFFSET_STATFS32_FLAGS);
static_assert(offsetof(struct statfs32, f_frsize) == __OFFSET_STATFS32_FRSIZE);
static_assert(offsetof(struct statfs32, f_fsid) == __OFFSET_STATFS32_FSID);
static_assert(offsetof(struct statfs32, f_namelen) == __OFFSET_STATFS32_NAMELEN);
static_assert(offsetof(struct statfs32, f_spare) == __OFFSET_STATFS32_SPARE);
static_assert(offsetof(struct statfs32, f_type) == __OFFSET_STATFS32_TYPE);
static_assert(sizeof(struct statfs32) == __SIZEOF_STATFS32);
static_assert(alignof(struct statfs32) == __ALIGNOF_STATFS32);

/* struct statfs64 */
static_assert(offsetof(struct statfs64, f_bavail) == __OFFSET_STATFS64_BAVAIL);
static_assert(offsetof(struct statfs64, f_bfree) == __OFFSET_STATFS64_BFREE);
static_assert(offsetof(struct statfs64, f_blocks) == __OFFSET_STATFS64_BLOCKS);
static_assert(offsetof(struct statfs64, f_bsize) == __OFFSET_STATFS64_BSIZE);
static_assert(offsetof(struct statfs64, f_ffree) == __OFFSET_STATFS64_FFREE);
static_assert(offsetof(struct statfs64, f_files) == __OFFSET_STATFS64_FILES);
static_assert(offsetof(struct statfs64, f_flags) == __OFFSET_STATFS64_FLAGS);
static_assert(offsetof(struct statfs64, f_frsize) == __OFFSET_STATFS64_FRSIZE);
static_assert(offsetof(struct statfs64, f_fsid) == __OFFSET_STATFS64_FSID);
static_assert(offsetof(struct statfs64, f_namelen) == __OFFSET_STATFS64_NAMELEN);
static_assert(offsetof(struct statfs64, f_spare) == __OFFSET_STATFS64_SPARE);
static_assert(offsetof(struct statfs64, f_type) == __OFFSET_STATFS64_TYPE);
static_assert(sizeof(struct statfs64) == __SIZEOF_STATFS64);
static_assert(alignof(struct statfs64) == __ALIGNOF_STATFS64);

/* struct __statfs32 */
static_assert(offsetof(struct __statfs32, f_bavail) == __OFFSET_STATFS32_BAVAIL);
static_assert(offsetof(struct __statfs32, f_bfree) == __OFFSET_STATFS32_BFREE);
static_assert(offsetof(struct __statfs32, f_blocks) == __OFFSET_STATFS32_BLOCKS);
static_assert(offsetof(struct __statfs32, f_bsize) == __OFFSET_STATFS32_BSIZE);
static_assert(offsetof(struct __statfs32, f_ffree) == __OFFSET_STATFS32_FFREE);
static_assert(offsetof(struct __statfs32, f_files) == __OFFSET_STATFS32_FILES);
static_assert(offsetof(struct __statfs32, f_flags) == __OFFSET_STATFS32_FLAGS);
static_assert(offsetof(struct __statfs32, f_frsize) == __OFFSET_STATFS32_FRSIZE);
static_assert(offsetof(struct __statfs32, f_fsid) == __OFFSET_STATFS32_FSID);
static_assert(offsetof(struct __statfs32, f_namelen) == __OFFSET_STATFS32_NAMELEN);
static_assert(offsetof(struct __statfs32, f_spare) == __OFFSET_STATFS32_SPARE);
static_assert(offsetof(struct __statfs32, f_type) == __OFFSET_STATFS32_TYPE);
static_assert(sizeof(struct __statfs32) == __SIZEOF_STATFS32);
static_assert(alignof(struct __statfs32) == __ALIGNOF_STATFS32);

/* struct __statfs64 */
static_assert(offsetof(struct __statfs64, f_bavail) == __OFFSET_STATFS64_BAVAIL);
static_assert(offsetof(struct __statfs64, f_bfree) == __OFFSET_STATFS64_BFREE);
static_assert(offsetof(struct __statfs64, f_blocks) == __OFFSET_STATFS64_BLOCKS);
static_assert(offsetof(struct __statfs64, f_bsize) == __OFFSET_STATFS64_BSIZE);
static_assert(offsetof(struct __statfs64, f_ffree) == __OFFSET_STATFS64_FFREE);
static_assert(offsetof(struct __statfs64, f_files) == __OFFSET_STATFS64_FILES);
static_assert(offsetof(struct __statfs64, f_flags) == __OFFSET_STATFS64_FLAGS);
static_assert(offsetof(struct __statfs64, f_frsize) == __OFFSET_STATFS64_FRSIZE);
static_assert(offsetof(struct __statfs64, f_fsid) == __OFFSET_STATFS64_FSID);
static_assert(offsetof(struct __statfs64, f_namelen) == __OFFSET_STATFS64_NAMELEN);
static_assert(offsetof(struct __statfs64, f_spare) == __OFFSET_STATFS64_SPARE);
static_assert(offsetof(struct __statfs64, f_type) == __OFFSET_STATFS64_TYPE);
static_assert(sizeof(struct __statfs64) == __SIZEOF_STATFS64);
static_assert(alignof(struct __statfs64) == __ALIGNOF_STATFS64);





#include <bits/os/kos/timeb.h>

/* struct timeb */
static_assert(offsetof(struct timeb, dstflag) == __OFFSET_TIMEB_DSTFLAG);
static_assert(offsetof(struct timeb, millitm) == __OFFSET_TIMEB_MILLITM);
static_assert(offsetof(struct timeb, time) == __OFFSET_TIMEB_TIME);
static_assert(offsetof(struct timeb, timezone) == __OFFSET_TIMEB_TIMEZONE);
static_assert(sizeof(struct timeb) == __SIZEOF_TIMEB);

/* struct __timeb64 */
static_assert(offsetof(struct __timeb64, dstflag) == __OFFSET_TIMEB64_DSTFLAG);
static_assert(offsetof(struct __timeb64, millitm) == __OFFSET_TIMEB64_MILLITM);
static_assert(offsetof(struct __timeb64, time) == __OFFSET_TIMEB64_TIME);
static_assert(offsetof(struct __timeb64, timezone) == __OFFSET_TIMEB64_TIMEZONE);
static_assert(sizeof(struct __timeb64) == __SIZEOF_TIMEB64);

/* struct __timeb32 */
static_assert(offsetof(struct __timeb32, dstflag) == __OFFSET_TIMEB32_DSTFLAG);
static_assert(offsetof(struct __timeb32, millitm) == __OFFSET_TIMEB32_MILLITM);
static_assert(offsetof(struct __timeb32, time) == __OFFSET_TIMEB32_TIME);
static_assert(offsetof(struct __timeb32, timezone) == __OFFSET_TIMEB32_TIMEZONE);
static_assert(sizeof(struct __timeb32) == __SIZEOF_TIMEB32);





#include <bits/os/kos/ustat.h>

/* struct ustat */
static_assert(offsetof(struct ustat, f_fname) == __OFFSET_USTAT_FNAME);
static_assert(offsetof(struct ustat, f_fpack) == __OFFSET_USTAT_FPACK);
static_assert(offsetof(struct ustat, f_tfree) == __OFFSET_USTAT_TFREE);
static_assert(offsetof(struct ustat, f_tinode) == __OFFSET_USTAT_TINODE);
static_assert(sizeof(struct ustat) == __SIZEOF_USTAT);
static_assert(alignof(struct ustat) == __ALIGNOF_USTAT);





#include <bits/os/kos/utimbuf.h>

/* struct utimbuf */
static_assert(offsetof(struct utimbuf, actime) == __OFFSET_UTIMBUF_ACTIME);
static_assert(offsetof(struct utimbuf, modtime) == __OFFSET_UTIMBUF_MODTIME);
static_assert(sizeof(struct utimbuf) == __SIZEOF_UTIMBUF);
static_assert(alignof(struct utimbuf) == __ALIGNOF_UTIMBUF);

/* struct __utimbuf64 */
static_assert(offsetof(struct __utimbuf64, actime) == __OFFSET_UTIMBUF64_ACTIME);
static_assert(offsetof(struct __utimbuf64, modtime) == __OFFSET_UTIMBUF64_MODTIME);
static_assert(sizeof(struct __utimbuf64) == __SIZEOF_UTIMBUF64);
static_assert(alignof(struct __utimbuf64) == __ALIGNOF_UTIMBUF64);

/* struct __utimbuf32 */
static_assert(offsetof(struct __utimbuf32, actime) == __OFFSET_UTIMBUF32_ACTIME);
static_assert(offsetof(struct __utimbuf32, modtime) == __OFFSET_UTIMBUF32_MODTIME);
static_assert(sizeof(struct __utimbuf32) == __SIZEOF_UTIMBUF32);
static_assert(alignof(struct __utimbuf32) == __ALIGNOF_UTIMBUF32);





#include <bits/os/kos/utsname.h>

/* struct utsname */
static_assert(offsetof(struct utsname, domainname) == __OFFSET_UTSNAME_DOMAINNAME);
static_assert(offsetof(struct utsname, machine) == __OFFSET_UTSNAME_MACHINE);
static_assert(offsetof(struct utsname, nodename) == __OFFSET_UTSNAME_NODENAME);
static_assert(offsetof(struct utsname, release) == __OFFSET_UTSNAME_RELEASE);
static_assert(offsetof(struct utsname, sysname) == __OFFSET_UTSNAME_SYSNAME);
static_assert(offsetof(struct utsname, version) == __OFFSET_UTSNAME_VERSION);
static_assert(sizeof(struct utsname) == __SIZEOF_UTSNAME);
static_assert(alignof(struct utsname) == __ALIGNOF_UTSNAME);





#include <bits/crt/ntptimeval.h>

/* struct ntptimeval */
static_assert(offsetof(struct ntptimeval, esterror) == __OFFSET_NTPTIMEVAL_ESTERROR);
static_assert(offsetof(struct ntptimeval, maxerror) == __OFFSET_NTPTIMEVAL_MAXERROR);
static_assert(offsetof(struct ntptimeval, tai) == __OFFSET_NTPTIMEVAL_TAI);
static_assert(offsetof(struct ntptimeval, time) == __OFFSET_NTPTIMEVAL_TIME);
static_assert(sizeof(struct ntptimeval) == __SIZEOF_NTPTIMEVAL);
static_assert(alignof(struct ntptimeval) == __ALIGNOF_NTPTIMEVAL);

/* struct __ntptimeval64 */
static_assert(offsetof(struct __ntptimeval64, esterror) == __OFFSET_NTPTIMEVAL64_ESTERROR);
static_assert(offsetof(struct __ntptimeval64, maxerror) == __OFFSET_NTPTIMEVAL64_MAXERROR);
static_assert(offsetof(struct __ntptimeval64, tai) == __OFFSET_NTPTIMEVAL64_TAI);
static_assert(offsetof(struct __ntptimeval64, time) == __OFFSET_NTPTIMEVAL64_TIME);
static_assert(sizeof(struct __ntptimeval64) == __SIZEOF_NTPTIMEVAL64);
static_assert(alignof(struct __ntptimeval64) == __ALIGNOF_NTPTIMEVAL64);

/* struct __ntptimeval32 */
static_assert(offsetof(struct __ntptimeval32, esterror) == __OFFSET_NTPTIMEVAL32_ESTERROR);
static_assert(offsetof(struct __ntptimeval32, maxerror) == __OFFSET_NTPTIMEVAL32_MAXERROR);
static_assert(offsetof(struct __ntptimeval32, tai) == __OFFSET_NTPTIMEVAL32_TAI);
static_assert(offsetof(struct __ntptimeval32, time) == __OFFSET_NTPTIMEVAL32_TIME);
static_assert(sizeof(struct __ntptimeval32) == __SIZEOF_NTPTIMEVAL32);
static_assert(alignof(struct __ntptimeval32) == __ALIGNOF_NTPTIMEVAL32);





#include <bits/os/kos/timex.h>

/* struct timex */
static_assert(offsetof(struct timex, calcnt) == __OFFSET_TIMEX_CALCNT);
static_assert(offsetof(struct timex, constant) == __OFFSET_TIMEX_CONSTANT);
static_assert(offsetof(struct timex, errcnt) == __OFFSET_TIMEX_ERRCNT);
static_assert(offsetof(struct timex, esterror) == __OFFSET_TIMEX_ESTERROR);
static_assert(offsetof(struct timex, freq) == __OFFSET_TIMEX_FREQ);
static_assert(offsetof(struct timex, jitcnt) == __OFFSET_TIMEX_JITCNT);
static_assert(offsetof(struct timex, jitter) == __OFFSET_TIMEX_JITTER);
static_assert(offsetof(struct timex, maxerror) == __OFFSET_TIMEX_MAXERROR);
static_assert(offsetof(struct timex, modes) == __OFFSET_TIMEX_MODES);
static_assert(offsetof(struct timex, offset) == __OFFSET_TIMEX_OFFSET);
static_assert(offsetof(struct timex, ppsfreq) == __OFFSET_TIMEX_PPSFREQ);
static_assert(offsetof(struct timex, precision) == __OFFSET_TIMEX_PRECISION);
static_assert(offsetof(struct timex, shift) == __OFFSET_TIMEX_SHIFT);
static_assert(offsetof(struct timex, stabil) == __OFFSET_TIMEX_STABIL);
static_assert(offsetof(struct timex, status) == __OFFSET_TIMEX_STATUS);
static_assert(offsetof(struct timex, stbcnt) == __OFFSET_TIMEX_STBCNT);
static_assert(offsetof(struct timex, tai) == __OFFSET_TIMEX_TAI);
static_assert(offsetof(struct timex, tick) == __OFFSET_TIMEX_TICK);
static_assert(offsetof(struct timex, time) == __OFFSET_TIMEX_TIME);
static_assert(offsetof(struct timex, tolerance) == __OFFSET_TIMEX_TOLERANCE);
static_assert(offsetof(struct timex, __pad) == __OFFSET_TIMEX___PAD);
static_assert(sizeof(struct timex) == __SIZEOF_TIMEX);
static_assert(alignof(struct timex) == __ALIGNOF_TIMEX);

/* struct __timex64 */
static_assert(offsetof(struct __timex64, calcnt) == __OFFSET_TIMEX64_CALCNT);
static_assert(offsetof(struct __timex64, constant) == __OFFSET_TIMEX64_CONSTANT);
static_assert(offsetof(struct __timex64, errcnt) == __OFFSET_TIMEX64_ERRCNT);
static_assert(offsetof(struct __timex64, esterror) == __OFFSET_TIMEX64_ESTERROR);
static_assert(offsetof(struct __timex64, freq) == __OFFSET_TIMEX64_FREQ);
static_assert(offsetof(struct __timex64, jitcnt) == __OFFSET_TIMEX64_JITCNT);
static_assert(offsetof(struct __timex64, jitter) == __OFFSET_TIMEX64_JITTER);
static_assert(offsetof(struct __timex64, maxerror) == __OFFSET_TIMEX64_MAXERROR);
static_assert(offsetof(struct __timex64, modes) == __OFFSET_TIMEX64_MODES);
static_assert(offsetof(struct __timex64, offset) == __OFFSET_TIMEX64_OFFSET);
static_assert(offsetof(struct __timex64, ppsfreq) == __OFFSET_TIMEX64_PPSFREQ);
static_assert(offsetof(struct __timex64, precision) == __OFFSET_TIMEX64_PRECISION);
static_assert(offsetof(struct __timex64, shift) == __OFFSET_TIMEX64_SHIFT);
static_assert(offsetof(struct __timex64, stabil) == __OFFSET_TIMEX64_STABIL);
static_assert(offsetof(struct __timex64, status) == __OFFSET_TIMEX64_STATUS);
static_assert(offsetof(struct __timex64, stbcnt) == __OFFSET_TIMEX64_STBCNT);
static_assert(offsetof(struct __timex64, tai) == __OFFSET_TIMEX64_TAI);
static_assert(offsetof(struct __timex64, tick) == __OFFSET_TIMEX64_TICK);
static_assert(offsetof(struct __timex64, time) == __OFFSET_TIMEX64_TIME);
static_assert(offsetof(struct __timex64, tolerance) == __OFFSET_TIMEX64_TOLERANCE);
static_assert(offsetof(struct __timex64, __pad) == __OFFSET_TIMEX64___PAD);
static_assert(sizeof(struct __timex64) == __SIZEOF_TIMEX64);
static_assert(alignof(struct __timex64) == __ALIGNOF_TIMEX64);

/* struct __timex32 */
static_assert(offsetof(struct __timex32, calcnt) == __OFFSET_TIMEX32_CALCNT);
static_assert(offsetof(struct __timex32, constant) == __OFFSET_TIMEX32_CONSTANT);
static_assert(offsetof(struct __timex32, errcnt) == __OFFSET_TIMEX32_ERRCNT);
static_assert(offsetof(struct __timex32, esterror) == __OFFSET_TIMEX32_ESTERROR);
static_assert(offsetof(struct __timex32, freq) == __OFFSET_TIMEX32_FREQ);
static_assert(offsetof(struct __timex32, jitcnt) == __OFFSET_TIMEX32_JITCNT);
static_assert(offsetof(struct __timex32, jitter) == __OFFSET_TIMEX32_JITTER);
static_assert(offsetof(struct __timex32, maxerror) == __OFFSET_TIMEX32_MAXERROR);
static_assert(offsetof(struct __timex32, modes) == __OFFSET_TIMEX32_MODES);
static_assert(offsetof(struct __timex32, offset) == __OFFSET_TIMEX32_OFFSET);
static_assert(offsetof(struct __timex32, ppsfreq) == __OFFSET_TIMEX32_PPSFREQ);
static_assert(offsetof(struct __timex32, precision) == __OFFSET_TIMEX32_PRECISION);
static_assert(offsetof(struct __timex32, shift) == __OFFSET_TIMEX32_SHIFT);
static_assert(offsetof(struct __timex32, stabil) == __OFFSET_TIMEX32_STABIL);
static_assert(offsetof(struct __timex32, status) == __OFFSET_TIMEX32_STATUS);
static_assert(offsetof(struct __timex32, stbcnt) == __OFFSET_TIMEX32_STBCNT);
static_assert(offsetof(struct __timex32, tai) == __OFFSET_TIMEX32_TAI);
static_assert(offsetof(struct __timex32, tick) == __OFFSET_TIMEX32_TICK);
static_assert(offsetof(struct __timex32, time) == __OFFSET_TIMEX32_TIME);
static_assert(offsetof(struct __timex32, tolerance) == __OFFSET_TIMEX32_TOLERANCE);
static_assert(offsetof(struct __timex32, __pad) == __OFFSET_TIMEX32___PAD);
static_assert(sizeof(struct __timex32) == __SIZEOF_TIMEX32);
static_assert(alignof(struct __timex32) == __ALIGNOF_TIMEX32);





#include <bits/os/kos/tms.h>

/* struct tms */
static_assert(offsetof(struct tms, tms_cstime) == __OFFSET_TMS_CSTIME);
static_assert(offsetof(struct tms, tms_cutime) == __OFFSET_TMS_CUTIME);
static_assert(offsetof(struct tms, tms_stime) == __OFFSET_TMS_STIME);
static_assert(offsetof(struct tms, tms_utime) == __OFFSET_TMS_UTIME);
static_assert(sizeof(struct tms) == __SIZEOF_TMS);
static_assert(alignof(struct tms) == __ALIGNOF_TMS);





#include <bits/os/linux/stat.h>

/* struct __glc_stat */
/* ... */

/* struct __glc_stat64 */
/* ... */





#include <elf.h>

/* struct elf32_ehdr */
static_assert(offsetof(struct elf32_ehdr, e_ehsize) == __OFFSET_ELF32_EHDR_EHSIZE);
static_assert(offsetof(struct elf32_ehdr, e_entry) == __OFFSET_ELF32_EHDR_ENTRY);
static_assert(offsetof(struct elf32_ehdr, e_flags) == __OFFSET_ELF32_EHDR_FLAGS);
static_assert(offsetof(struct elf32_ehdr, e_ident) == __OFFSET_ELF32_EHDR_IDENT);
static_assert(offsetof(struct elf32_ehdr, e_machine) == __OFFSET_ELF32_EHDR_MACHINE);
static_assert(offsetof(struct elf32_ehdr, e_phentsize) == __OFFSET_ELF32_EHDR_PHENTSIZE);
static_assert(offsetof(struct elf32_ehdr, e_phnum) == __OFFSET_ELF32_EHDR_PHNUM);
static_assert(offsetof(struct elf32_ehdr, e_phoff) == __OFFSET_ELF32_EHDR_PHOFF);
static_assert(offsetof(struct elf32_ehdr, e_shentsize) == __OFFSET_ELF32_EHDR_SHENTSIZE);
static_assert(offsetof(struct elf32_ehdr, e_shnum) == __OFFSET_ELF32_EHDR_SHNUM);
static_assert(offsetof(struct elf32_ehdr, e_shoff) == __OFFSET_ELF32_EHDR_SHOFF);
static_assert(offsetof(struct elf32_ehdr, e_shstrndx) == __OFFSET_ELF32_EHDR_SHSTRNDX);
static_assert(offsetof(struct elf32_ehdr, e_type) == __OFFSET_ELF32_EHDR_TYPE);
static_assert(offsetof(struct elf32_ehdr, e_version) == __OFFSET_ELF32_EHDR_VERSION);
static_assert(sizeof(struct elf32_ehdr) == __SIZEOF_ELF32_EHDR);
static_assert(alignof(struct elf32_ehdr) == __ALIGNOF_ELF32_EHDR);

/* struct elf64_ehdr */
static_assert(offsetof(struct elf64_ehdr, e_ehsize) == __OFFSET_ELF64_EHDR_EHSIZE);
static_assert(offsetof(struct elf64_ehdr, e_entry) == __OFFSET_ELF64_EHDR_ENTRY);
static_assert(offsetof(struct elf64_ehdr, e_flags) == __OFFSET_ELF64_EHDR_FLAGS);
static_assert(offsetof(struct elf64_ehdr, e_ident) == __OFFSET_ELF64_EHDR_IDENT);
static_assert(offsetof(struct elf64_ehdr, e_machine) == __OFFSET_ELF64_EHDR_MACHINE);
static_assert(offsetof(struct elf64_ehdr, e_phentsize) == __OFFSET_ELF64_EHDR_PHENTSIZE);
static_assert(offsetof(struct elf64_ehdr, e_phnum) == __OFFSET_ELF64_EHDR_PHNUM);
static_assert(offsetof(struct elf64_ehdr, e_phoff) == __OFFSET_ELF64_EHDR_PHOFF);
static_assert(offsetof(struct elf64_ehdr, e_shentsize) == __OFFSET_ELF64_EHDR_SHENTSIZE);
static_assert(offsetof(struct elf64_ehdr, e_shnum) == __OFFSET_ELF64_EHDR_SHNUM);
static_assert(offsetof(struct elf64_ehdr, e_shoff) == __OFFSET_ELF64_EHDR_SHOFF);
static_assert(offsetof(struct elf64_ehdr, e_shstrndx) == __OFFSET_ELF64_EHDR_SHSTRNDX);
static_assert(offsetof(struct elf64_ehdr, e_type) == __OFFSET_ELF64_EHDR_TYPE);
static_assert(offsetof(struct elf64_ehdr, e_version) == __OFFSET_ELF64_EHDR_VERSION);
static_assert(sizeof(struct elf64_ehdr) == __SIZEOF_ELF64_EHDR);
static_assert(alignof(struct elf64_ehdr) == __ALIGNOF_ELF64_EHDR);

/* struct elf32_shdr */
static_assert(offsetof(struct elf32_shdr, sh_addr) == __OFFSET_ELF32_SHDR_ADDR);
static_assert(offsetof(struct elf32_shdr, sh_addralign) == __OFFSET_ELF32_SHDR_ADDRALIGN);
static_assert(offsetof(struct elf32_shdr, sh_entsize) == __OFFSET_ELF32_SHDR_ENTSIZE);
static_assert(offsetof(struct elf32_shdr, sh_flags) == __OFFSET_ELF32_SHDR_FLAGS);
static_assert(offsetof(struct elf32_shdr, sh_info) == __OFFSET_ELF32_SHDR_INFO);
static_assert(offsetof(struct elf32_shdr, sh_link) == __OFFSET_ELF32_SHDR_LINK);
static_assert(offsetof(struct elf32_shdr, sh_name) == __OFFSET_ELF32_SHDR_NAME);
static_assert(offsetof(struct elf32_shdr, sh_offset) == __OFFSET_ELF32_SHDR_OFFSET);
static_assert(offsetof(struct elf32_shdr, sh_size) == __OFFSET_ELF32_SHDR_SIZE);
static_assert(offsetof(struct elf32_shdr, sh_type) == __OFFSET_ELF32_SHDR_TYPE);
static_assert(sizeof(struct elf32_shdr) == __SIZEOF_ELF32_SHDR);
static_assert(alignof(struct elf32_shdr) == __ALIGNOF_ELF32_SHDR);

/* struct elf64_shdr */
static_assert(offsetof(struct elf64_shdr, sh_addr) == __OFFSET_ELF64_SHDR_ADDR);
static_assert(offsetof(struct elf64_shdr, sh_addralign) == __OFFSET_ELF64_SHDR_ADDRALIGN);
static_assert(offsetof(struct elf64_shdr, sh_entsize) == __OFFSET_ELF64_SHDR_ENTSIZE);
static_assert(offsetof(struct elf64_shdr, sh_flags) == __OFFSET_ELF64_SHDR_FLAGS);
static_assert(offsetof(struct elf64_shdr, sh_info) == __OFFSET_ELF64_SHDR_INFO);
static_assert(offsetof(struct elf64_shdr, sh_link) == __OFFSET_ELF64_SHDR_LINK);
static_assert(offsetof(struct elf64_shdr, sh_name) == __OFFSET_ELF64_SHDR_NAME);
static_assert(offsetof(struct elf64_shdr, sh_offset) == __OFFSET_ELF64_SHDR_OFFSET);
static_assert(offsetof(struct elf64_shdr, sh_size) == __OFFSET_ELF64_SHDR_SIZE);
static_assert(offsetof(struct elf64_shdr, sh_type) == __OFFSET_ELF64_SHDR_TYPE);
static_assert(sizeof(struct elf64_shdr) == __SIZEOF_ELF64_SHDR);
static_assert(alignof(struct elf64_shdr) == __ALIGNOF_ELF64_SHDR);

/* struct elf32_sym */
static_assert(offsetof(struct elf32_sym, st_info) == __OFFSET_ELF32_SYM_INFO);
static_assert(offsetof(struct elf32_sym, st_name) == __OFFSET_ELF32_SYM_NAME);
static_assert(offsetof(struct elf32_sym, st_other) == __OFFSET_ELF32_SYM_OTHER);
static_assert(offsetof(struct elf32_sym, st_shndx) == __OFFSET_ELF32_SYM_SHNDX);
static_assert(offsetof(struct elf32_sym, st_size) == __OFFSET_ELF32_SYM_SIZE);
static_assert(offsetof(struct elf32_sym, st_value) == __OFFSET_ELF32_SYM_VALUE);
static_assert(sizeof(struct elf32_sym) == __SIZEOF_ELF32_SYM);
static_assert(alignof(struct elf32_sym) == __ALIGNOF_ELF32_SYM);

/* struct elf64_sym */
static_assert(offsetof(struct elf64_sym, st_info) == __OFFSET_ELF64_SYM_INFO);
static_assert(offsetof(struct elf64_sym, st_name) == __OFFSET_ELF64_SYM_NAME);
static_assert(offsetof(struct elf64_sym, st_other) == __OFFSET_ELF64_SYM_OTHER);
static_assert(offsetof(struct elf64_sym, st_shndx) == __OFFSET_ELF64_SYM_SHNDX);
static_assert(offsetof(struct elf64_sym, st_size) == __OFFSET_ELF64_SYM_SIZE);
static_assert(offsetof(struct elf64_sym, st_value) == __OFFSET_ELF64_SYM_VALUE);
static_assert(sizeof(struct elf64_sym) == __SIZEOF_ELF64_SYM);
static_assert(alignof(struct elf64_sym) == __ALIGNOF_ELF64_SYM);

/* struct elf32_syminfo */
static_assert(offsetof(struct elf32_syminfo, si_boundto) == __OFFSET_ELF32_SYMINFO_BOUNDTO);
static_assert(offsetof(struct elf32_syminfo, si_flags) == __OFFSET_ELF32_SYMINFO_FLAGS);
static_assert(sizeof(struct elf32_syminfo) == __SIZEOF_ELF32_SYMINFO);
static_assert(alignof(struct elf32_syminfo) == __ALIGNOF_ELF32_SYMINFO);

/* struct elf64_syminfo */
static_assert(offsetof(struct elf64_syminfo, si_boundto) == __OFFSET_ELF64_SYMINFO_BOUNDTO);
static_assert(offsetof(struct elf64_syminfo, si_flags) == __OFFSET_ELF64_SYMINFO_FLAGS);
static_assert(sizeof(struct elf64_syminfo) == __SIZEOF_ELF64_SYMINFO);
static_assert(alignof(struct elf64_syminfo) == __ALIGNOF_ELF64_SYMINFO);

/* struct elf32_rel */
static_assert(offsetof(struct elf32_rel, r_info) == __OFFSET_ELF32_REL_INFO);
static_assert(offsetof(struct elf32_rel, r_offset) == __OFFSET_ELF32_REL_OFFSET);
static_assert(sizeof(struct elf32_rel) == __SIZEOF_ELF32_REL);
static_assert(alignof(struct elf32_rel) == __ALIGNOF_ELF32_REL);

/* struct elf64_rel */
static_assert(offsetof(struct elf64_rel, r_info) == __OFFSET_ELF64_REL_INFO);
static_assert(offsetof(struct elf64_rel, r_offset) == __OFFSET_ELF64_REL_OFFSET);
static_assert(sizeof(struct elf64_rel) == __SIZEOF_ELF64_REL);
static_assert(alignof(struct elf64_rel) == __ALIGNOF_ELF64_REL);

/* struct elf32_rela */
static_assert(offsetof(struct elf32_rela, r_addend) == __OFFSET_ELF32_RELA_ADDEND);
static_assert(offsetof(struct elf32_rela, r_info) == __OFFSET_ELF32_RELA_INFO);
static_assert(offsetof(struct elf32_rela, r_offset) == __OFFSET_ELF32_RELA_OFFSET);
static_assert(sizeof(struct elf32_rela) == __SIZEOF_ELF32_RELA);
static_assert(alignof(struct elf32_rela) == __ALIGNOF_ELF32_RELA);

/* struct elf64_rela */
static_assert(offsetof(struct elf64_rela, r_addend) == __OFFSET_ELF64_RELA_ADDEND);
static_assert(offsetof(struct elf64_rela, r_info) == __OFFSET_ELF64_RELA_INFO);
static_assert(offsetof(struct elf64_rela, r_offset) == __OFFSET_ELF64_RELA_OFFSET);
static_assert(sizeof(struct elf64_rela) == __SIZEOF_ELF64_RELA);
static_assert(alignof(struct elf64_rela) == __ALIGNOF_ELF64_RELA);

/* struct elf32_phdr */
static_assert(offsetof(struct elf32_phdr, p_align) == __OFFSET_ELF32_PHDR_ALIGN);
static_assert(offsetof(struct elf32_phdr, p_filesz) == __OFFSET_ELF32_PHDR_FILESZ);
static_assert(offsetof(struct elf32_phdr, p_flags) == __OFFSET_ELF32_PHDR_FLAGS);
static_assert(offsetof(struct elf32_phdr, p_memsz) == __OFFSET_ELF32_PHDR_MEMSZ);
static_assert(offsetof(struct elf32_phdr, p_offset) == __OFFSET_ELF32_PHDR_OFFSET);
static_assert(offsetof(struct elf32_phdr, p_paddr) == __OFFSET_ELF32_PHDR_PADDR);
static_assert(offsetof(struct elf32_phdr, p_type) == __OFFSET_ELF32_PHDR_TYPE);
static_assert(offsetof(struct elf32_phdr, p_vaddr) == __OFFSET_ELF32_PHDR_VADDR);
static_assert(sizeof(struct elf32_phdr) == __SIZEOF_ELF32_PHDR);
static_assert(alignof(struct elf32_phdr) == __ALIGNOF_ELF32_PHDR);

/* struct elf64_phdr */
static_assert(offsetof(struct elf64_phdr, p_align) == __OFFSET_ELF64_PHDR_ALIGN);
static_assert(offsetof(struct elf64_phdr, p_filesz) == __OFFSET_ELF64_PHDR_FILESZ);
static_assert(offsetof(struct elf64_phdr, p_flags) == __OFFSET_ELF64_PHDR_FLAGS);
static_assert(offsetof(struct elf64_phdr, p_memsz) == __OFFSET_ELF64_PHDR_MEMSZ);
static_assert(offsetof(struct elf64_phdr, p_offset) == __OFFSET_ELF64_PHDR_OFFSET);
static_assert(offsetof(struct elf64_phdr, p_paddr) == __OFFSET_ELF64_PHDR_PADDR);
static_assert(offsetof(struct elf64_phdr, p_type) == __OFFSET_ELF64_PHDR_TYPE);
static_assert(offsetof(struct elf64_phdr, p_vaddr) == __OFFSET_ELF64_PHDR_VADDR);
static_assert(sizeof(struct elf64_phdr) == __SIZEOF_ELF64_PHDR);
static_assert(alignof(struct elf64_phdr) == __ALIGNOF_ELF64_PHDR);

/* struct elf32_dyn */
static_assert(offsetof(struct elf32_dyn, d_un.d_ptr) == __OFFSET_ELF32_DYN_PTR);
static_assert(offsetof(struct elf32_dyn, d_tag) == __OFFSET_ELF32_DYN_TAG);
static_assert(offsetof(struct elf32_dyn, d_un.d_val) == __OFFSET_ELF32_DYN_VAL);
static_assert(sizeof(struct elf32_dyn) == __SIZEOF_ELF32_DYN);
static_assert(alignof(struct elf32_dyn) == __ALIGNOF_ELF32_DYN);

/* struct elf64_dyn */
static_assert(offsetof(struct elf64_dyn, d_un.d_ptr) == __OFFSET_ELF64_DYN_PTR);
static_assert(offsetof(struct elf64_dyn, d_tag) == __OFFSET_ELF64_DYN_TAG);
static_assert(offsetof(struct elf64_dyn, d_un.d_val) == __OFFSET_ELF64_DYN_VAL);
static_assert(sizeof(struct elf64_dyn) == __SIZEOF_ELF64_DYN);
static_assert(alignof(struct elf64_dyn) == __ALIGNOF_ELF64_DYN);

/* struct elf32_chdr */
static_assert(offsetof(struct elf32_chdr, ch_addralign) == __OFFSET_ELF32_CHDR_ADDRALIGN);
static_assert(offsetof(struct elf32_chdr, ch_size) == __OFFSET_ELF32_CHDR_SIZE);
static_assert(offsetof(struct elf32_chdr, ch_type) == __OFFSET_ELF32_CHDR_TYPE);
static_assert(sizeof(struct elf32_chdr) == __SIZEOF_ELF32_CHDR);
static_assert(alignof(struct elf32_chdr) == __ALIGNOF_ELF32_CHDR);

/* struct elf64_chdr */
static_assert(offsetof(struct elf64_chdr, ch_addralign) == __OFFSET_ELF64_CHDR_ADDRALIGN);
static_assert(offsetof(struct elf64_chdr, ch_size) == __OFFSET_ELF64_CHDR_SIZE);
static_assert(offsetof(struct elf64_chdr, ch_type) == __OFFSET_ELF64_CHDR_TYPE);
static_assert(sizeof(struct elf64_chdr) == __SIZEOF_ELF64_CHDR);
static_assert(alignof(struct elf64_chdr) == __ALIGNOF_ELF64_CHDR);

/* struct elf32_verdef */
static_assert(offsetof(struct elf32_verdef, vd_aux) == __OFFSET_ELF32_VERDEF_AUX);
static_assert(offsetof(struct elf32_verdef, vd_cnt) == __OFFSET_ELF32_VERDEF_CNT);
static_assert(offsetof(struct elf32_verdef, vd_flags) == __OFFSET_ELF32_VERDEF_FLAGS);
static_assert(offsetof(struct elf32_verdef, vd_hash) == __OFFSET_ELF32_VERDEF_HASH);
static_assert(offsetof(struct elf32_verdef, vd_ndx) == __OFFSET_ELF32_VERDEF_NDX);
static_assert(offsetof(struct elf32_verdef, vd_next) == __OFFSET_ELF32_VERDEF_NEXT);
static_assert(offsetof(struct elf32_verdef, vd_version) == __OFFSET_ELF32_VERDEF_VERSION);
static_assert(sizeof(struct elf32_verdef) == __SIZEOF_ELF32_VERDEF);
static_assert(alignof(struct elf32_verdef) == __ALIGNOF_ELF32_VERDEF);

/* struct elf64_verdef */
static_assert(offsetof(struct elf64_verdef, vd_aux) == __OFFSET_ELF64_VERDEF_AUX);
static_assert(offsetof(struct elf64_verdef, vd_cnt) == __OFFSET_ELF64_VERDEF_CNT);
static_assert(offsetof(struct elf64_verdef, vd_flags) == __OFFSET_ELF64_VERDEF_FLAGS);
static_assert(offsetof(struct elf64_verdef, vd_hash) == __OFFSET_ELF64_VERDEF_HASH);
static_assert(offsetof(struct elf64_verdef, vd_ndx) == __OFFSET_ELF64_VERDEF_NDX);
static_assert(offsetof(struct elf64_verdef, vd_next) == __OFFSET_ELF64_VERDEF_NEXT);
static_assert(offsetof(struct elf64_verdef, vd_version) == __OFFSET_ELF64_VERDEF_VERSION);
static_assert(sizeof(struct elf64_verdef) == __SIZEOF_ELF64_VERDEF);
static_assert(alignof(struct elf64_verdef) == __ALIGNOF_ELF64_VERDEF);

/* struct elf32_verdaux */
static_assert(offsetof(struct elf32_verdaux, vda_name) == __OFFSET_ELF32_VERDAUX_NAME);
static_assert(offsetof(struct elf32_verdaux, vda_next) == __OFFSET_ELF32_VERDAUX_NEXT);
static_assert(sizeof(struct elf32_verdaux) == __SIZEOF_ELF32_VERDAUX);
static_assert(alignof(struct elf32_verdaux) == __ALIGNOF_ELF32_VERDAUX);

/* struct elf64_verdaux */
static_assert(offsetof(struct elf64_verdaux, vda_name) == __OFFSET_ELF64_VERDAUX_NAME);
static_assert(offsetof(struct elf64_verdaux, vda_next) == __OFFSET_ELF64_VERDAUX_NEXT);
static_assert(sizeof(struct elf64_verdaux) == __SIZEOF_ELF64_VERDAUX);
static_assert(alignof(struct elf64_verdaux) == __ALIGNOF_ELF64_VERDAUX);

/* struct elf32_verneed */
static_assert(offsetof(struct elf32_verneed, vn_aux) == __OFFSET_ELF32_VERNEED_AUX);
static_assert(offsetof(struct elf32_verneed, vn_cnt) == __OFFSET_ELF32_VERNEED_CNT);
static_assert(offsetof(struct elf32_verneed, vn_file) == __OFFSET_ELF32_VERNEED_FILE);
static_assert(offsetof(struct elf32_verneed, vn_next) == __OFFSET_ELF32_VERNEED_NEXT);
static_assert(offsetof(struct elf32_verneed, vn_version) == __OFFSET_ELF32_VERNEED_VERSION);
static_assert(sizeof(struct elf32_verneed) == __SIZEOF_ELF32_VERNEED);
static_assert(alignof(struct elf32_verneed) == __ALIGNOF_ELF32_VERNEED);

/* struct elf64_verneed */
static_assert(offsetof(struct elf64_verneed, vn_aux) == __OFFSET_ELF64_VERNEED_AUX);
static_assert(offsetof(struct elf64_verneed, vn_cnt) == __OFFSET_ELF64_VERNEED_CNT);
static_assert(offsetof(struct elf64_verneed, vn_file) == __OFFSET_ELF64_VERNEED_FILE);
static_assert(offsetof(struct elf64_verneed, vn_next) == __OFFSET_ELF64_VERNEED_NEXT);
static_assert(offsetof(struct elf64_verneed, vn_version) == __OFFSET_ELF64_VERNEED_VERSION);
static_assert(sizeof(struct elf64_verneed) == __SIZEOF_ELF64_VERNEED);
static_assert(alignof(struct elf64_verneed) == __ALIGNOF_ELF64_VERNEED);

/* struct elf32_vernaux */
static_assert(offsetof(struct elf32_vernaux, vna_flags) == __OFFSET_ELF32_VERNAUX_FLAGS);
static_assert(offsetof(struct elf32_vernaux, vna_hash) == __OFFSET_ELF32_VERNAUX_HASH);
static_assert(offsetof(struct elf32_vernaux, vna_name) == __OFFSET_ELF32_VERNAUX_NAME);
static_assert(offsetof(struct elf32_vernaux, vna_next) == __OFFSET_ELF32_VERNAUX_NEXT);
static_assert(offsetof(struct elf32_vernaux, vna_other) == __OFFSET_ELF32_VERNAUX_OTHER);
static_assert(sizeof(struct elf32_vernaux) == __SIZEOF_ELF32_VERNAUX);
static_assert(alignof(struct elf32_vernaux) == __ALIGNOF_ELF32_VERNAUX);

/* struct elf64_vernaux */
static_assert(offsetof(struct elf64_vernaux, vna_flags) == __OFFSET_ELF64_VERNAUX_FLAGS);
static_assert(offsetof(struct elf64_vernaux, vna_hash) == __OFFSET_ELF64_VERNAUX_HASH);
static_assert(offsetof(struct elf64_vernaux, vna_name) == __OFFSET_ELF64_VERNAUX_NAME);
static_assert(offsetof(struct elf64_vernaux, vna_next) == __OFFSET_ELF64_VERNAUX_NEXT);
static_assert(offsetof(struct elf64_vernaux, vna_other) == __OFFSET_ELF64_VERNAUX_OTHER);
static_assert(sizeof(struct elf64_vernaux) == __SIZEOF_ELF64_VERNAUX);
static_assert(alignof(struct elf64_vernaux) == __ALIGNOF_ELF64_VERNAUX);

/* struct elf32_auxv_t */
static_assert(offsetof(struct elf32_auxv_t, a_type) == __OFFSET_ELF32_AUXV_TYPE);
static_assert(offsetof(struct elf32_auxv_t, a_un.a_val) == __OFFSET_ELF32_AUXV_VAL);
static_assert(sizeof(struct elf32_auxv_t) == __SIZEOF_ELF32_AUXV);
static_assert(alignof(struct elf32_auxv_t) == __ALIGNOF_ELF32_AUXV);

/* struct elf64_auxv_t */
static_assert(offsetof(struct elf64_auxv_t, a_type) == __OFFSET_ELF64_AUXV_TYPE);
static_assert(offsetof(struct elf64_auxv_t, a_un.a_val) == __OFFSET_ELF64_AUXV_VAL);
static_assert(sizeof(struct elf64_auxv_t) == __SIZEOF_ELF64_AUXV);
static_assert(alignof(struct elf64_auxv_t) == __ALIGNOF_ELF64_AUXV);

/* struct elf32_nhdr */
static_assert(offsetof(struct elf32_nhdr, n_descsz) == __OFFSET_ELF32_NHDR_DESCSZ);
static_assert(offsetof(struct elf32_nhdr, n_namesz) == __OFFSET_ELF32_NHDR_NAMESZ);
static_assert(offsetof(struct elf32_nhdr, n_type) == __OFFSET_ELF32_NHDR_TYPE);
static_assert(sizeof(struct elf32_nhdr) == __SIZEOF_ELF32_NHDR);
static_assert(alignof(struct elf32_nhdr) == __ALIGNOF_ELF32_NHDR);

/* struct elf64_nhdr */
static_assert(offsetof(struct elf64_nhdr, n_descsz) == __OFFSET_ELF64_NHDR_DESCSZ);
static_assert(offsetof(struct elf64_nhdr, n_namesz) == __OFFSET_ELF64_NHDR_NAMESZ);
static_assert(offsetof(struct elf64_nhdr, n_type) == __OFFSET_ELF64_NHDR_TYPE);
static_assert(sizeof(struct elf64_nhdr) == __SIZEOF_ELF64_NHDR);
static_assert(alignof(struct elf64_nhdr) == __ALIGNOF_ELF64_NHDR);

/* struct elf32_move */
static_assert(offsetof(struct elf32_move, m_info) == __OFFSET_ELF32_MOVE_INFO);
static_assert(offsetof(struct elf32_move, m_poffset) == __OFFSET_ELF32_MOVE_POFFSET);
static_assert(offsetof(struct elf32_move, m_repeat) == __OFFSET_ELF32_MOVE_REPEAT);
static_assert(offsetof(struct elf32_move, m_stride) == __OFFSET_ELF32_MOVE_STRIDE);
static_assert(offsetof(struct elf32_move, m_value) == __OFFSET_ELF32_MOVE_VALUE);
static_assert(alignof(struct elf32_move) == __ALIGNOF_ELF32_MOVE);

/* struct elf64_move */
static_assert(offsetof(struct elf64_move, m_info) == __OFFSET_ELF64_MOVE_INFO);
static_assert(offsetof(struct elf64_move, m_poffset) == __OFFSET_ELF64_MOVE_POFFSET);
static_assert(offsetof(struct elf64_move, m_repeat) == __OFFSET_ELF64_MOVE_REPEAT);
static_assert(offsetof(struct elf64_move, m_stride) == __OFFSET_ELF64_MOVE_STRIDE);
static_assert(offsetof(struct elf64_move, m_value) == __OFFSET_ELF64_MOVE_VALUE);
static_assert(alignof(struct elf64_move) == __ALIGNOF_ELF64_MOVE);

/* union elf32_gptab */
static_assert(offsetof(union elf32_gptab, gt_entry.gt_bytes) == __OFFSET_ELF32_GPTAB_ENTRY_BYTES);
static_assert(offsetof(union elf32_gptab, gt_entry.gt_g_value) == __OFFSET_ELF32_GPTAB_ENTRY_G_VALUE);
static_assert(offsetof(union elf32_gptab, gt_header.gt_current_g_value) == __OFFSET_ELF32_GPTAB_HEADER_CURRENT_G_VALUE);
static_assert(sizeof(union elf32_gptab) == __SIZEOF_ELF32_GPTAB);
static_assert(alignof(union elf32_gptab) == __ALIGNOF_ELF32_GPTAB);

/* struct elf32_reginfo */
static_assert(offsetof(struct elf32_reginfo, ri_cprmask) == __OFFSET_ELF32_REGINFO_CPRMASK);
static_assert(offsetof(struct elf32_reginfo, ri_gprmask) == __OFFSET_ELF32_REGINFO_GPRMASK);
static_assert(offsetof(struct elf32_reginfo, ri_gp_value) == __OFFSET_ELF32_REGINFO_GP_VALUE);
static_assert(sizeof(struct elf32_reginfo) == __SIZEOF_ELF32_REGINFO);
static_assert(alignof(struct elf32_reginfo) == __ALIGNOF_ELF32_REGINFO);

/* struct elf_options */
static_assert(offsetof(struct elf_options, info) == __OFFSET_ELF_OPTIONS_INFO);
static_assert(offsetof(struct elf_options, kind) == __OFFSET_ELF_OPTIONS_KIND);
static_assert(offsetof(struct elf_options, section) == __OFFSET_ELF_OPTIONS_SECTION);
static_assert(offsetof(struct elf_options, size) == __OFFSET_ELF_OPTIONS_SIZE);
static_assert(sizeof(struct elf_options) == __SIZEOF_ELF_OPTIONS);
static_assert(alignof(struct elf_options) == __ALIGNOF_ELF_OPTIONS);

/* struct elf_options_hw */
static_assert(offsetof(struct elf_options_hw, hwp_flags1) == __OFFSET_ELF_OPTIONS_HW_FLAGS1);
static_assert(offsetof(struct elf_options_hw, hwp_flags2) == __OFFSET_ELF_OPTIONS_HW_FLAGS2);
static_assert(sizeof(struct elf_options_hw) == __SIZEOF_ELF_OPTIONS_HW);
static_assert(alignof(struct elf_options_hw) == __ALIGNOF_ELF_OPTIONS_HW);

/* struct elf32_lib */
static_assert(offsetof(struct elf32_lib, l_checksum) == __OFFSET_ELF32_LIB_CHECKSUM);
static_assert(offsetof(struct elf32_lib, l_flags) == __OFFSET_ELF32_LIB_FLAGS);
static_assert(offsetof(struct elf32_lib, l_name) == __OFFSET_ELF32_LIB_NAME);
static_assert(offsetof(struct elf32_lib, l_time_stamp) == __OFFSET_ELF32_LIB_TIME_STAMP);
static_assert(offsetof(struct elf32_lib, l_version) == __OFFSET_ELF32_LIB_VERSION);
static_assert(sizeof(struct elf32_lib) == __SIZEOF_ELF32_LIB);
static_assert(alignof(struct elf32_lib) == __ALIGNOF_ELF32_LIB);

/* struct elf64_lib */
static_assert(offsetof(struct elf64_lib, l_checksum) == __OFFSET_ELF64_LIB_CHECKSUM);
static_assert(offsetof(struct elf64_lib, l_flags) == __OFFSET_ELF64_LIB_FLAGS);
static_assert(offsetof(struct elf64_lib, l_name) == __OFFSET_ELF64_LIB_NAME);
static_assert(offsetof(struct elf64_lib, l_time_stamp) == __OFFSET_ELF64_LIB_TIME_STAMP);
static_assert(offsetof(struct elf64_lib, l_version) == __OFFSET_ELF64_LIB_VERSION);
static_assert(sizeof(struct elf64_lib) == __SIZEOF_ELF64_LIB);
static_assert(alignof(struct elf64_lib) == __ALIGNOF_ELF64_LIB);

/* struct elf_mips_abiflags_v0 */
/* ... */





#include <kos/bits/debugtrap.h>

/* struct debugtrap_reason */
static_assert(offsetof(struct debugtrap_reason, dtr_intarg) == __OFFSET_DEBUGTRAP_REASON_INTARG);
static_assert(offsetof(struct debugtrap_reason, dtr_ptrarg) == __OFFSET_DEBUGTRAP_REASON_PTRARG);
static_assert(offsetof(struct debugtrap_reason, dtr_reason) == __OFFSET_DEBUGTRAP_REASON_REASON);
static_assert(offsetof(struct debugtrap_reason, dtr_signo) == __OFFSET_DEBUGTRAP_REASON_SIGNO);
static_assert(offsetof(struct debugtrap_reason, dtr_strarg) == __OFFSET_DEBUGTRAP_REASON_STRARG);
static_assert(sizeof(struct debugtrap_reason) == __SIZEOF_DEBUGTRAP_REASON);





#include <kos/bits/ukern-struct.h>

/* struct userkern */
static_assert(offsetof(struct userkern, uk_base) == OFFSET_USERKERN_BASE);
static_assert(offsetof(struct userkern, uk_egid) == OFFSET_USERKERN_EGID);
static_assert(offsetof(struct userkern, uk_euid) == OFFSET_USERKERN_EUID);
static_assert(offsetof(struct userkern, uk_gid) == OFFSET_USERKERN_GID);
static_assert(offsetof(struct userkern, uk_pgid) == OFFSET_USERKERN_PGID);
static_assert(offsetof(struct userkern, uk_pid) == OFFSET_USERKERN_PID);
static_assert(offsetof(struct userkern, uk_ppid) == OFFSET_USERKERN_PPID);
static_assert(offsetof(struct userkern, uk_regs) == OFFSET_USERKERN_REGS);
static_assert(offsetof(struct userkern, uk_sgid) == OFFSET_USERKERN_SGID);
static_assert(offsetof(struct userkern, uk_sid) == OFFSET_USERKERN_SID);
static_assert(offsetof(struct userkern, uk_suid) == OFFSET_USERKERN_SUID);
static_assert(offsetof(struct userkern, uk_tid) == OFFSET_USERKERN_TID);
static_assert(offsetof(struct userkern, uk_uid) == OFFSET_USERKERN_UID);
static_assert(sizeof(struct userkern) == SIZEOF_USERKERN);





#include <kos/bits/userprocmask.h>

/* struct userprocmask */
static_assert(offsetof(struct userprocmask, pm_flags) == __OFFSET_USERPROCMASK_FLAGS);
static_assert(offsetof(struct userprocmask, pm_mytid) == __OFFSET_USERPROCMASK_MYTID);
static_assert(offsetof(struct userprocmask, pm_pending) == __OFFSET_USERPROCMASK_PENDING);
static_assert(offsetof(struct userprocmask, pm_sigmask) == __OFFSET_USERPROCMASK_SIGMASK);
static_assert(offsetof(struct userprocmask, pm_sigsize) == __OFFSET_USERPROCMASK_SIGSIZE);
static_assert(sizeof(struct userprocmask) == __SIZEOF_USERPROCMASK);





#include <kos/exec/bits/peb.h>

/* struct process_peb */
static_assert(offsetof(struct process_peb, pp_argc) == OFFSET_PROCESS_PEB_ARGC);
static_assert(offsetof(struct process_peb, pp_argv) == OFFSET_PROCESS_PEB_ARGV);
static_assert(offsetof(struct process_peb, pp_envc) == OFFSET_PROCESS_PEB_ENVC);
static_assert(offsetof(struct process_peb, pp_envp) == OFFSET_PROCESS_PEB_ENVP);





#include <kos/exec/elf.h>

/* struct elfexec_info */
/* ... */





#include <kos/ioctl/_openfd.h>

/* struct openfd */
static_assert(offsetof(struct openfd, of_flags) == __OFFSET_OPENFD_FLAGS);
static_assert(offsetof(struct openfd, of_hint) == __OFFSET_OPENFD_HINT);
static_assert(offsetof(struct openfd, of_mode) == __OFFSET_OPENFD_MODE);
static_assert(sizeof(struct openfd) == __SIZEOF_OPENFD);





#include <kos/ksysctl.h>

/* struct ksysctl_driver_insmod */
static_assert(offsetof(struct ksysctl_driver_insmod, im_blob.b_base) == __OFFSET_KSYSCTL_DRIVER_INSMOD_BLOB_BASE);
static_assert(offsetof(struct ksysctl_driver_insmod, im_blob.b_size) == __OFFSET_KSYSCTL_DRIVER_INSMOD_BLOB_SIZE);
static_assert(offsetof(struct ksysctl_driver_insmod, im_cmdline) == __OFFSET_KSYSCTL_DRIVER_INSMOD_CMDLINE);
static_assert(offsetof(struct ksysctl_driver_insmod, im_driver) == __OFFSET_KSYSCTL_DRIVER_INSMOD_DRIVER);
static_assert(offsetof(struct ksysctl_driver_insmod, im_file.f_dentry) == __OFFSET_KSYSCTL_DRIVER_INSMOD_FILE_DENTRY);
static_assert(offsetof(struct ksysctl_driver_insmod, im_file.f_node) == __OFFSET_KSYSCTL_DRIVER_INSMOD_FILE_NODE);
static_assert(offsetof(struct ksysctl_driver_insmod, im_file.f_path) == __OFFSET_KSYSCTL_DRIVER_INSMOD_FILE_PATH);
static_assert(offsetof(struct ksysctl_driver_insmod, im_flags) == __OFFSET_KSYSCTL_DRIVER_INSMOD_FLAGS);
static_assert(offsetof(struct ksysctl_driver_insmod, im_format) == __OFFSET_KSYSCTL_DRIVER_INSMOD_FORMAT);
static_assert(offsetof(struct ksysctl_driver_insmod, im_name) == __OFFSET_KSYSCTL_DRIVER_INSMOD_NAME);
static_assert(offsetof(struct ksysctl_driver_insmod, im_newdriver) == __OFFSET_KSYSCTL_DRIVER_INSMOD_NEWDRIVER);
static_assert(offsetof(struct ksysctl_driver_insmod, im_struct_size) == __OFFSET_KSYSCTL_DRIVER_INSMOD_STRUCT_SIZE);
static_assert(sizeof(struct ksysctl_driver_insmod) == __SIZEOF_KSYSCTL_DRIVER_INSMOD);

/* struct ksysctl_driver_delmod */
static_assert(offsetof(struct ksysctl_driver_delmod, dm_file) == __OFFSET_KSYSCTL_DRIVER_DELMOD_FILE);
static_assert(offsetof(struct ksysctl_driver_delmod, dm_flags) == __OFFSET_KSYSCTL_DRIVER_DELMOD_FLAGS);
static_assert(offsetof(struct ksysctl_driver_delmod, dm_format) == __OFFSET_KSYSCTL_DRIVER_DELMOD_FORMAT);
static_assert(offsetof(struct ksysctl_driver_delmod, dm_name) == __OFFSET_KSYSCTL_DRIVER_DELMOD_NAME);
static_assert(offsetof(struct ksysctl_driver_delmod, dm_struct_size) == __OFFSET_KSYSCTL_DRIVER_DELMOD_STRUCT_SIZE);
static_assert(sizeof(struct ksysctl_driver_delmod) == __SIZEOF_KSYSCTL_DRIVER_DELMOD);

/* struct ksysctl_driver_getmod */
static_assert(offsetof(struct ksysctl_driver_getmod, gm_addr) == __OFFSET_KSYSCTL_DRIVER_GETMOD_ADDR);
static_assert(offsetof(struct ksysctl_driver_getmod, gm_driver) == __OFFSET_KSYSCTL_DRIVER_GETMOD_DRIVER);
static_assert(offsetof(struct ksysctl_driver_getmod, gm_file) == __OFFSET_KSYSCTL_DRIVER_GETMOD_FILE);
static_assert(offsetof(struct ksysctl_driver_getmod, gm_format) == __OFFSET_KSYSCTL_DRIVER_GETMOD_FORMAT);
static_assert(offsetof(struct ksysctl_driver_getmod, gm_name) == __OFFSET_KSYSCTL_DRIVER_GETMOD_NAME);
static_assert(offsetof(struct ksysctl_driver_getmod, gm_struct_size) == __OFFSET_KSYSCTL_DRIVER_GETMOD_STRUCT_SIZE);
static_assert(sizeof(struct ksysctl_driver_getmod) == __SIZEOF_KSYSCTL_DRIVER_GETMOD);

/* struct ksysctl_driver_get_library_path */
static_assert(offsetof(struct ksysctl_driver_get_library_path, glp_buf) == __OFFSET_KSYSCTL_DRIVER_GET_LIBRARY_PATH_BUF);
static_assert(offsetof(struct ksysctl_driver_get_library_path, glp_size) == __OFFSET_KSYSCTL_DRIVER_GET_LIBRARY_PATH_SIZE);
static_assert(offsetof(struct ksysctl_driver_get_library_path, glp_struct_size) == __OFFSET_KSYSCTL_DRIVER_GET_LIBRARY_PATH_STRUCT_SIZE);
static_assert(sizeof(struct ksysctl_driver_get_library_path) == __SIZEOF_KSYSCTL_DRIVER_GET_LIBRARY_PATH);

/* struct ksysctl_driver_set_library_path */
static_assert(offsetof(struct ksysctl_driver_set_library_path, slp_newpath) == __OFFSET_KSYSCTL_DRIVER_SET_LIBRARY_PATH_NEWPATH);
static_assert(offsetof(struct ksysctl_driver_set_library_path, slp_oldpath) == __OFFSET_KSYSCTL_DRIVER_SET_LIBRARY_PATH_OLDPATH);
static_assert(offsetof(struct ksysctl_driver_set_library_path, slp_struct_size) == __OFFSET_KSYSCTL_DRIVER_SET_LIBRARY_PATH_STRUCT_SIZE);
static_assert(sizeof(struct ksysctl_driver_set_library_path) == __SIZEOF_KSYSCTL_DRIVER_SET_LIBRARY_PATH);





#include <linux/if_arp.h>

/* struct arphdr */
static_assert(offsetof(struct arphdr, ar_hln) == __OFFSET_ARPHDR_HLN);
static_assert(offsetof(struct arphdr, ar_hrd) == __OFFSET_ARPHDR_HRD);
static_assert(offsetof(struct arphdr, ar_op) == __OFFSET_ARPHDR_OP);
static_assert(offsetof(struct arphdr, ar_pln) == __OFFSET_ARPHDR_PLN);
static_assert(offsetof(struct arphdr, ar_pro) == __OFFSET_ARPHDR_PRO);
static_assert(alignof(struct arphdr) == __ALIGNOF_ARPHDR);

/* struct arpreq */
/* ... */

/* struct arpreq_old */
/* ... */





#include <linux/if_ether.h>

/* struct ethhdr */
static_assert(offsetof(struct ethhdr, h_dest) == __OFFSET_ETHHDR_DEST);
static_assert(offsetof(struct ethhdr, h_proto) == __OFFSET_ETHHDR_PROTO);
static_assert(offsetof(struct ethhdr, h_source) == __OFFSET_ETHHDR_SOURCE);
static_assert(sizeof(struct ethhdr) == __SIZEOF_ETHHDR);
static_assert(alignof(struct ethhdr) == __ALIGNOF_ETHHDR);





#include <netinet/ip.h>

/* struct timestamp */
/* ... */

/* struct iphdr */
static_assert(offsetof(struct iphdr, ip_dst) == __OFFSET_IPHDR_DST);
static_assert(offsetof(struct iphdr, ip_id) == __OFFSET_IPHDR_ID);
static_assert(offsetof(struct iphdr, ip_len) == __OFFSET_IPHDR_LEN);
static_assert(offsetof(struct iphdr, ip_off) == __OFFSET_IPHDR_OFF);
static_assert(offsetof(struct iphdr, ip_p) == __OFFSET_IPHDR_P);
static_assert(offsetof(struct iphdr, ip_src) == __OFFSET_IPHDR_SRC);
static_assert(offsetof(struct iphdr, ip_sum) == __OFFSET_IPHDR_SUM);
static_assert(offsetof(struct iphdr, ip_tos) == __OFFSET_IPHDR_TOS);
static_assert(offsetof(struct iphdr, ip_ttl) == __OFFSET_IPHDR_TTL);
static_assert(sizeof(struct iphdr) == __SIZEOF_IPHDR);
static_assert(alignof(struct iphdr) == __ALIGNOF_IPHDR);

/* struct ip */
/* ... */

/* struct ip_timestamp */
/* ... */





#include <netinet/udp.h>

/* struct udphdr */
static_assert(offsetof(struct udphdr, uh_dport) == __OFFSET_UDPHDR_DPORT);
static_assert(offsetof(struct udphdr, uh_sport) == __OFFSET_UDPHDR_SPORT);
static_assert(offsetof(struct udphdr, uh_sum) == __OFFSET_UDPHDR_SUM);
static_assert(offsetof(struct udphdr, uh_ulen) == __OFFSET_UDPHDR_ULEN);
static_assert(sizeof(struct udphdr) == __SIZEOF_UDPHDR);





#undef sigev_value
#undef sigev_signo
#undef sigev_notify
#undef sigev_notify_function
#undef sigev_notify_attributes
#include <bits/os/cygwin/sigevent.h>

/* struct __sigevent_cygwin */
static_assert(offsetof(struct __sigevent_cygwin, sigev_notify) == __OFFSET_SIGEVENT_CYGWIN_NOTIFY);
static_assert(offsetof(struct __sigevent_cygwin, sigev_notify_attributes) == __OFFSET_SIGEVENT_CYGWIN_NOTIFY_ATTRIBUTES);
static_assert(offsetof(struct __sigevent_cygwin, sigev_notify_function) == __OFFSET_SIGEVENT_CYGWIN_NOTIFY_FUNCTION);
static_assert(offsetof(struct __sigevent_cygwin, sigev_signo) == __OFFSET_SIGEVENT_CYGWIN_SIGNO);
static_assert(offsetof(struct __sigevent_cygwin, sigev_value) == __OFFSET_SIGEVENT_CYGWIN_VALUE);
static_assert(sizeof(struct __sigevent_cygwin) == __SIZEOF_SIGEVENT_CYGWIN);





#undef si_signo
#undef si_code
#undef si_pid
#undef si_uid
#undef si_errno
#undef _si_data
#undef _si_commune
#undef si_sigval
#undef si_value
#undef si_tid
#undef si_overrun
#undef si_status
#undef si_utime
#undef si_stime
#undef si_addr
#include <bits/os/cygwin/siginfo.h>

/* struct _sigcommune */
/* ... */

/* struct __siginfo_cygwin_struct */
/* ... */
//[[[end]]]


#include <kos/except.h>

/* Make sure that none of the exception-structs cause the
 * exception-data-pointer-union to grow beyond its  arch-
 * specific pointer-count-limit */
static_assert(sizeof(union exception_data_pointers) ==
              EXCEPTION_DATA_POINTERS * sizeof(void *));



#include <bits/os/dirent.h>

static_assert(offsetof(struct dirent, d_ino) == __OFFSET_DIRENT_INO);
static_assert(offsetof(struct dirent, d_namlen) == __OFFSET_DIRENT_NAMLEN);
static_assert(offsetof(struct dirent, d_type) == __OFFSET_DIRENT_TYPE);
static_assert(offsetof(struct dirent, d_name) == __OFFSET_DIRENT_NAME);
static_assert(offsetof(struct dirent64, d_ino) == __OFFSET_DIRENT64_INO);
static_assert(offsetof(struct dirent64, d_namlen) == __OFFSET_DIRENT64_NAMLEN);
static_assert(offsetof(struct dirent64, d_type) == __OFFSET_DIRENT64_TYPE);
static_assert(offsetof(struct dirent64, d_name) == __OFFSET_DIRENT64_NAME);

#endif /* !GUARD__VERIFY_ASSERT_TYPES_C */
