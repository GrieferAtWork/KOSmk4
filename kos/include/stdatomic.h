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
/* (>) Standard: ISO C11 (ISO/IEC 9899:2011) */
/* (#) Portability: Cygwin    (/newlib/libc/include/stdatomic.h) */
/* (#) Portability: Newlib    (/newlib/libc/include/stdatomic.h) */
/* (#) Portability: libstdc++ (/include/stdatomic.h) */
#ifndef _STDATOMIC_H
#define _STDATOMIC_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

#ifndef __CC__
#ifndef memory_order_relaxed
#define memory_order_relaxed __ATOMIC_RELAXED
#define memory_order_consume __ATOMIC_CONSUME
#define memory_order_acquire __ATOMIC_ACQUIRE
#define memory_order_release __ATOMIC_RELEASE
#define memory_order_acq_rel __ATOMIC_ACQ_REL
#define memory_order_seq_cst __ATOMIC_SEQ_CST
#endif /* !memory_order_relaxed */
#elif defined(__cplusplus)
#include <atomic>

/* For compatibility with C... */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __COMPILER_ATOMIC(...)  __NAMESPACE_STD_SYM atomic< __VA_ARGS__ >
#define _Atomic(...)            __NAMESPACE_STD_SYM atomic< __VA_ARGS__ >
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __COMPILER_ATOMIC(T...) __NAMESPACE_STD_SYM atomic< T >
#define _Atomic(T...)           __NAMESPACE_STD_SYM atomic< T >
#else /* ... */
#define __COMPILER_ATOMIC(T)    __NAMESPACE_STD_SYM atomic<T>
#define _Atomic(T)              __NAMESPACE_STD_SYM atomic<T>
#endif /* !... */


#ifdef __COMPILER_HAVE_BUG_BLOATY_CXX_USING
/* Everything's already implicitly imported by the `using namespace std;'
 * that's used when the `__COMPILER_HAVE_BUG_BLOATY_CXX_USING'  bug-check
 * is enabled. */
#ifndef __memory_order_defined
#define __memory_order_defined
#endif /* !__memory_order_defined */
#else /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING */
__DECL_BEGIN

#ifndef __memory_order_defined
#define __memory_order_defined
__NAMESPACE_STD_USING(memory_order)
__NAMESPACE_STD_USING(memory_order_relaxed)
__NAMESPACE_STD_USING(memory_order_consume)
__NAMESPACE_STD_USING(memory_order_acquire)
__NAMESPACE_STD_USING(memory_order_release)
__NAMESPACE_STD_USING(memory_order_acq_rel)
__NAMESPACE_STD_USING(memory_order_seq_cst)
#endif /* !__memory_order_defined */

__NAMESPACE_STD_USING(atomic_bool)
__NAMESPACE_STD_USING(atomic_char)
__NAMESPACE_STD_USING(atomic_schar)
__NAMESPACE_STD_USING(atomic_uchar)
__NAMESPACE_STD_USING(atomic_short)
__NAMESPACE_STD_USING(atomic_ushort)
__NAMESPACE_STD_USING(atomic_int)
__NAMESPACE_STD_USING(atomic_uint)
__NAMESPACE_STD_USING(atomic_long)
__NAMESPACE_STD_USING(atomic_ulong)
#ifdef __COMPILER_HAVE_LONGLONG
__NAMESPACE_STD_USING(atomic_llong)
__NAMESPACE_STD_USING(atomic_ullong)
#endif /* __COMPILER_HAVE_LONGLONG */
__NAMESPACE_STD_USING(atomic_char16_t)
__NAMESPACE_STD_USING(atomic_char32_t)
__NAMESPACE_STD_USING(atomic_wchar_t)
__NAMESPACE_STD_USING(atomic_int_least8_t)
__NAMESPACE_STD_USING(atomic_uint_least8_t)
__NAMESPACE_STD_USING(atomic_int_least16_t)
__NAMESPACE_STD_USING(atomic_uint_least16_t)
__NAMESPACE_STD_USING(atomic_int_least32_t)
__NAMESPACE_STD_USING(atomic_uint_least32_t)
__NAMESPACE_STD_USING(atomic_int_least64_t)
__NAMESPACE_STD_USING(atomic_uint_least64_t)
__NAMESPACE_STD_USING(atomic_int_fast8_t)
__NAMESPACE_STD_USING(atomic_uint_fast8_t)
__NAMESPACE_STD_USING(atomic_int_fast16_t)
__NAMESPACE_STD_USING(atomic_uint_fast16_t)
__NAMESPACE_STD_USING(atomic_int_fast32_t)
__NAMESPACE_STD_USING(atomic_uint_fast32_t)
__NAMESPACE_STD_USING(atomic_int_fast64_t)
__NAMESPACE_STD_USING(atomic_uint_fast64_t)
__NAMESPACE_STD_USING(atomic_intptr_t)
__NAMESPACE_STD_USING(atomic_uintptr_t)
__NAMESPACE_STD_USING(atomic_size_t)
__NAMESPACE_STD_USING(atomic_ptrdiff_t)
__NAMESPACE_STD_USING(atomic_intmax_t)
__NAMESPACE_STD_USING(atomic_uintmax_t)
__NAMESPACE_STD_USING(atomic_init)
__NAMESPACE_STD_USING(atomic_thread_fence)
__NAMESPACE_STD_USING(atomic_signal_fence)
__NAMESPACE_STD_USING(atomic_is_lock_free)
__NAMESPACE_STD_USING(atomic_store_explicit)
__NAMESPACE_STD_USING(atomic_store)
__NAMESPACE_STD_USING(atomic_load_explicit)
__NAMESPACE_STD_USING(atomic_load)
__NAMESPACE_STD_USING(atomic_exchange_explicit)
__NAMESPACE_STD_USING(atomic_exchange)
__NAMESPACE_STD_USING(atomic_compare_exchange_strong_explicit)
__NAMESPACE_STD_USING(atomic_compare_exchange_weak_explicit)
__NAMESPACE_STD_USING(atomic_compare_exchange_strong)
__NAMESPACE_STD_USING(atomic_compare_exchange_weak)
__NAMESPACE_STD_USING(atomic_fetch_add)
__NAMESPACE_STD_USING(atomic_fetch_add_explicit)
__NAMESPACE_STD_USING(atomic_fetch_sub)
__NAMESPACE_STD_USING(atomic_fetch_sub_explicit)
__NAMESPACE_STD_USING(atomic_fetch_or)
__NAMESPACE_STD_USING(atomic_fetch_or_explicit)
__NAMESPACE_STD_USING(atomic_fetch_xor)
__NAMESPACE_STD_USING(atomic_fetch_xor_explicit)
__NAMESPACE_STD_USING(atomic_fetch_and)
__NAMESPACE_STD_USING(atomic_fetch_and_explicit)

#if defined(__USE_KOS) && defined(_CXX_ATOMIC)
__NAMESPACE_STD_USING(atomic_cmpxch_explicit)
__NAMESPACE_STD_USING(atomic_cmpxch)
__NAMESPACE_STD_USING(atomic_cmpxch_val_explicit)
__NAMESPACE_STD_USING(atomic_cmpxch_val)
__NAMESPACE_STD_USING(atomic_cmpxch_weak_explicit)
__NAMESPACE_STD_USING(atomic_cmpxch_weak)
__NAMESPACE_STD_USING(atomic_cmpxch_val_weak_explicit)
__NAMESPACE_STD_USING(atomic_cmpxch_val_weak)
__NAMESPACE_STD_USING(atomic_fetch_nand)
__NAMESPACE_STD_USING(atomic_fetch_nand_explicit)
#endif /* __USE_KOS && _CXX_ATOMIC */

__NAMESPACE_STD_USING(atomic_flag)
__NAMESPACE_STD_USING(atomic_flag_test_and_set_explicit)
__NAMESPACE_STD_USING(atomic_flag_test_and_set)
__NAMESPACE_STD_USING(atomic_flag_clear_explicit)
__NAMESPACE_STD_USING(atomic_flag_clear)

__DECL_END
#endif /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING */


#else /* __cplusplus */

__DECL_BEGIN

#ifndef __std_memory_order_defined
#define __std_memory_order_defined
__DECL_BEGIN
__NAMESPACE_STD_BEGIN
typedef enum {
	memory_order_relaxed = __ATOMIC_RELAXED,
	memory_order_consume = __ATOMIC_CONSUME,
	memory_order_acquire = __ATOMIC_ACQUIRE,
	memory_order_release = __ATOMIC_RELEASE,
	memory_order_acq_rel = __ATOMIC_ACQ_REL,
	memory_order_seq_cst = __ATOMIC_SEQ_CST
} memory_order;
__NAMESPACE_STD_END
__DECL_END
#endif /* !__std_memory_order_defined */

#ifndef __memory_order_defined
#define __memory_order_defined
#ifndef __COMPILER_HAVE_BUG_BLOATY_CXX_USING
__NAMESPACE_STD_USING(memory_order)
__NAMESPACE_STD_USING(memory_order_relaxed)
__NAMESPACE_STD_USING(memory_order_consume)
__NAMESPACE_STD_USING(memory_order_acquire)
__NAMESPACE_STD_USING(memory_order_release)
__NAMESPACE_STD_USING(memory_order_acq_rel)
__NAMESPACE_STD_USING(memory_order_seq_cst)
#endif /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING */
#endif /* !__memory_order_defined */

#if __has_feature(c_atomic) || __has_extension(c_atomic)
/* #undef __COMPILER_NO_STDC_ATOMICS */ /* Supported! */
#elif defined(__GNUC__) /* TODO: Which version? */
/* #undef __COMPILER_NO_STDC_ATOMICS */ /* Supported! */
#elif defined(__NO_has_feature) || defined(__NO_has_extension)
#define __COMPILER_NO_STDC_ATOMICS /* Compiler has feature test macros, but they didn't indicate support */
#elif !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112
#define __COMPILER_NO_STDC_ATOMICS /* STDC version too old --> Not supported */
#elif defined(__STDC_NO_ATOMICS__)
#define __COMPILER_NO_STDC_ATOMICS /* Explicitly marked as not supported */
#else /* ... */
/* #undef __COMPILER_NO_STDC_ATOMICS */ /* Nothing seemings to indicate a lack of support... */
#endif /* !... */


#ifdef __COMPILER_NO_STDC_ATOMICS
#define __COMPILER_ATOMIC(...) __VA_ARGS__
#else /* __COMPILER_NO_STDC_ATOMICS */
#define __COMPILER_ATOMIC _Atomic
#endif /* !__COMPILER_NO_STDC_ATOMICS */
#define ATOMIC_VAR_INIT(...) __VA_ARGS__

typedef __COMPILER_ATOMIC(__BOOL) atomic_bool;
typedef __COMPILER_ATOMIC(char) atomic_char;
typedef __COMPILER_ATOMIC(signed char) atomic_schar;
typedef __COMPILER_ATOMIC(unsigned char) atomic_uchar;
typedef __COMPILER_ATOMIC(short) atomic_short;
typedef __COMPILER_ATOMIC(unsigned short) atomic_ushort;
typedef __COMPILER_ATOMIC(int) atomic_int;
typedef __COMPILER_ATOMIC(unsigned int) atomic_uint;
typedef __COMPILER_ATOMIC(long) atomic_long;
typedef __COMPILER_ATOMIC(unsigned long) atomic_ulong;
#ifdef __COMPILER_HAVE_LONGLONG
typedef __COMPILER_ATOMIC(__LONGLONG) atomic_llong;
typedef __COMPILER_ATOMIC(__ULONGLONG) atomic_ullong;
#endif /* __COMPILER_HAVE_LONGLONG */
typedef __COMPILER_ATOMIC(__CHAR16_TYPE__) atomic_char16_t;
typedef __COMPILER_ATOMIC(__CHAR32_TYPE__) atomic_char32_t;
typedef __COMPILER_ATOMIC(__WCHAR_TYPE__) atomic_wchar_t;
typedef __COMPILER_ATOMIC(__INT_LEAST8_TYPE__) atomic_int_least8_t;
typedef __COMPILER_ATOMIC(__UINT_LEAST8_TYPE__) atomic_uint_least8_t;
typedef __COMPILER_ATOMIC(__INT_LEAST16_TYPE__) atomic_int_least16_t;
typedef __COMPILER_ATOMIC(__UINT_LEAST16_TYPE__) atomic_uint_least16_t;
typedef __COMPILER_ATOMIC(__INT_LEAST32_TYPE__) atomic_int_least32_t;
typedef __COMPILER_ATOMIC(__UINT_LEAST32_TYPE__) atomic_uint_least32_t;
#ifdef __UINT_LEAST64_TYPE__
typedef __COMPILER_ATOMIC(__INT_LEAST64_TYPE__) atomic_int_least64_t;
typedef __COMPILER_ATOMIC(__UINT_LEAST64_TYPE__) atomic_uint_least64_t;
#endif /* __UINT_LEAST64_TYPE__ */
typedef __COMPILER_ATOMIC(__INT_FAST8_TYPE__) atomic_int_fast8_t;
typedef __COMPILER_ATOMIC(__UINT_FAST8_TYPE__) atomic_uint_fast8_t;
typedef __COMPILER_ATOMIC(__INT_FAST16_TYPE__) atomic_int_fast16_t;
typedef __COMPILER_ATOMIC(__UINT_FAST16_TYPE__) atomic_uint_fast16_t;
typedef __COMPILER_ATOMIC(__INT_FAST32_TYPE__) atomic_int_fast32_t;
typedef __COMPILER_ATOMIC(__UINT_FAST32_TYPE__) atomic_uint_fast32_t;
#ifdef __UINT_FAST64_TYPE__
typedef __COMPILER_ATOMIC(__INT_FAST64_TYPE__) atomic_int_fast64_t;
typedef __COMPILER_ATOMIC(__UINT_FAST64_TYPE__) atomic_uint_fast64_t;
#endif /* __UINT_FAST64_TYPE__ */
typedef __COMPILER_ATOMIC(__INTPTR_TYPE__) atomic_intptr_t;
typedef __COMPILER_ATOMIC(__UINTPTR_TYPE__) atomic_uintptr_t;
typedef __COMPILER_ATOMIC(__SIZE_TYPE__) atomic_size_t;
typedef __COMPILER_ATOMIC(__PTRDIFF_TYPE__) atomic_ptrdiff_t;
typedef __COMPILER_ATOMIC(__INTMAX_TYPE__) atomic_intmax_t;
typedef __COMPILER_ATOMIC(__UINTMAX_TYPE__) atomic_uintmax_t;

#define atomic_init(ptr, val)      __hybrid_atomic_store(ptr, val, __ATOMIC_RELAXED)
#define atomic_thread_fence(order) __hybrid_atomic_thread_fence(order)
#define atomic_signal_fence(order) __hybrid_atomic_signal_fence(order)
#define atomic_is_lock_free(ptr)   __hybrid_atomic_lockfree(ptr)

#define atomic_store(ptr, val)                    __hybrid_atomic_store(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_store_explicit(ptr, val, order)    __hybrid_atomic_store(ptr, val, order)
#define atomic_load(ptr)                          __hybrid_atomic_load(ptr, __ATOMIC_SEQ_CST)
#define atomic_load_explicit(ptr, order)          __hybrid_atomic_load(ptr, order)
#define atomic_exchange(ptr, val)                 __hybrid_atomic_xch(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_exchange_explicit(ptr, val, order) __hybrid_atomic_xch(ptr, val, order)
#if (!defined(__NO_XBLOCK) && \
     (defined(__COMPILER_HAVE_AUTOTYPE) || defined(__COMPILER_HAVE_TYPEOF)))
#ifdef __COMPILER_HAVE_AUTOTYPE
#define atomic_compare_exchange_strong_explicit(ptr, poldval, newval, succ, fail)          \
	__XBLOCK({                                                                             \
		__auto_type __acese_poldval = (poldval);                                           \
		__auto_type __acese_oldval  = *__acese_poldval;                                    \
		__XRETURN (*__acese_poldval = __hybrid_atomic_cmpxch_val(ptr, __acese_oldval,      \
		                                                         newval, succ,             \
		                                                         fail)) == __acese_oldval; \
	})
#define atomic_compare_exchange_weak_explicit(ptr, poldval, newval, succ, fail)        \
	__XBLOCK({                                                                         \
		__auto_type __acese_ptr     = (ptr);                                           \
		__auto_type __acese_poldval = (poldval);                                       \
		__BOOL __acese_ok = __hybrid_atomic_cmpxch_weak(__acese_ptr, *__acese_poldval, \
		                                                newval, succ, fail);           \
		if (!__acese_ok)                                                               \
			*__acese_poldval = __hybrid_atomic_load(__acese_ptr, __ATOMIC_ACQUIRE);    \
		__XRETURN __acese_ok;                                                          \
	})
#else /* __COMPILER_HAVE_AUTOTYPE */
#define atomic_compare_exchange_strong_explicit(ptr, poldval, newval, succ, fail)          \
	__XBLOCK({                                                                             \
		__typeof__(poldval) __acese_poldval = (poldval);                                   \
		__typeof__(*__acese_poldval) __acese_oldval = *__acese_poldval;                    \
		__XRETURN (*__acese_poldval = __hybrid_atomic_cmpxch_val(ptr, __acese_oldval,      \
		                                                         newval, succ,             \
		                                                         fail)) == __acese_oldval; \
	})
#define atomic_compare_exchange_weak_explicit(ptr, poldval, newval, succ, fail)        \
	__XBLOCK({                                                                         \
		__typeof__(ptr) __acese_ptr         = (ptr);                                   \
		__typeof__(poldval) __acese_poldval = (poldval);                               \
		__BOOL __acese_ok = __hybrid_atomic_cmpxch_weak(__acese_ptr, *__acese_poldval, \
		                                                newval, succ, fail);           \
		if (!__acese_ok)                                                               \
			*__acese_poldval = __hybrid_atomic_load(__acese_ptr, __ATOMIC_ACQUIRE);    \
		__XRETURN __acese_ok;                                                          \
	})
#endif /* !__COMPILER_HAVE_AUTOTYPE */
#else /* ... */
#ifndef __hybrid_atomic_cmpxch_val8
#define __hybrid_atomic_cmpxch_val8 __hybrid_atomic_cmpxch_val
#endif /* !__hybrid_atomic_cmpxch_val8 */
#ifndef __hybrid_atomic_cmpxch_val16
#define __hybrid_atomic_cmpxch_val16 __hybrid_atomic_cmpxch_val
#endif /* !__hybrid_atomic_cmpxch_val16 */
#ifndef __hybrid_atomic_cmpxch_val32
#define __hybrid_atomic_cmpxch_val32 __hybrid_atomic_cmpxch_val
#endif /* !__hybrid_atomic_cmpxch_val32 */
#ifndef __hybrid_atomic_load8
#define __hybrid_atomic_load8 __hybrid_atomic_load
#endif /* !__hybrid_atomic_load8 */
#ifndef __hybrid_atomic_load16
#define __hybrid_atomic_load16 __hybrid_atomic_load
#endif /* !__hybrid_atomic_load16 */
#ifndef __hybrid_atomic_load32
#define __hybrid_atomic_load32 __hybrid_atomic_load
#endif /* !__hybrid_atomic_load32 */

#define __PRIVATE_DEFINE_atomic_compare_exchange_x_explicit(N)                                                        \
	__LOCAL __ATTR_NONNULL((1, 2)) __BOOL                                                                             \
	(__PRIVATE_atomic_compare_exchange_strong_explicit_##N)(__UINT##N##_TYPE__ *__ptr, __UINT##N##_TYPE__ *__poldval, \
	                                                        __UINT##N##_TYPE__ newval, memory_order __succ,           \
	                                                        memory_order __fail) {                                    \
		__UINT##N##_TYPE__ __want_oldval, __real_oldval;                                                              \
		(void)__succ, (void)__fail;                                                                                   \
		__want_oldval = *__poldval;                                                                                   \
		__real_oldval = __hybrid_atomic_cmpxch_val##N(__ptr, __want_oldval, __newval, __succ, __fail);                \
		*__poldval    = __real_oldval;                                                                                \
		return __want_oldval == __real_oldval;                                                                        \
	}                                                                                                                 \
	__LOCAL __ATTR_NONNULL((1, 2)) __BOOL                                                                             \
	(__PRIVATE_atomic_compare_exchange_weak_explicit_##N)(__UINT##N##_TYPE__ *__ptr, __UINT##N##_TYPE__ *__poldval,   \
	                                                      __UINT##N##_TYPE__ newval, memory_order __succ,             \
	                                                      memory_order __fail) {                                      \
		__BOOL __res;                                                                                                 \
		(void)__succ, (void)__fail;                                                                                   \
		__res = __hybrid_atomic_cmpxch_weak##N(__ptr, *__poldval, __newval, __succ, __fail);                          \
		if (!__res)                                                                                                   \
			*__poldval = __hybrid_atomic_load##N(__ptr, __fail);                                                      \
		return __res;                                                                                                 \
	}
__PRIVATE_DEFINE_atomic_compare_exchange_x_explicit(8)
__PRIVATE_DEFINE_atomic_compare_exchange_x_explicit(16)
__PRIVATE_DEFINE_atomic_compare_exchange_x_explicit(32)
#ifdef __UINT64_TYPE__
#ifndef __hybrid_atomic_cmpxch_val64
#define __hybrid_atomic_cmpxch_val64 __hybrid_atomic_cmpxch_val
#endif /* !__hybrid_atomic_cmpxch_val64 */
#ifndef __hybrid_atomic_load64
#define __hybrid_atomic_load64 __hybrid_atomic_load
#endif /* !__hybrid_atomic_load64 */
__PRIVATE_DEFINE_atomic_compare_exchange_x_explicit(64)
#endif /* __UINT64_TYPE__ */
#ifdef __UINT128_TYPE__
#ifndef __hybrid_atomic_cmpxch_val128
#define __hybrid_atomic_cmpxch_val128 __hybrid_atomic_cmpxch_val
#endif /* !__hybrid_atomic_cmpxch_val128 */
#ifndef __hybrid_atomic_load128
#define __hybrid_atomic_load128 __hybrid_atomic_load
#endif /* !__hybrid_atomic_load128 */
__PRIVATE_DEFINE_atomic_compare_exchange_x_explicit(128)
#endif /* __UINT128_TYPE__ */
#undef __PRIVATE_DEFINE_atomic_compare_exchange_x_explicit

#ifdef __UINT128_TYPE__
#define __PRIVATE_select_atomic_compare_exchange_x_explicit(func, ptr, poldval, newval, succ, fail)                                  \
	(sizeof(*(ptr)) == 1 ? (func##8)((__UINT8_TYPE__ *)(ptr), (__UINT8_TYPE__)(poldval), (__UINT8_TYPE__)(newval), succ, fail) :     \
	 sizeof(*(ptr)) == 2 ? (func##16)((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(poldval), (__UINT16_TYPE__)(newval), succ, fail) : \
	 sizeof(*(ptr)) == 4 ? (func##32)((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(poldval), (__UINT32_TYPE__)(newval), succ, fail) : \
	 sizeof(*(ptr)) == 8 ? (func##64)((__UINT64_TYPE__ *)(ptr), (__UINT64_TYPE__)(poldval), (__UINT64_TYPE__)(newval), succ, fail) : \
	                       (func##128)((__UINT128_TYPE__ *)(ptr), (__UINT128_TYPE__)(poldval), (__UINT128_TYPE__)(newval), succ, fail))
#elif defined(__UINT64_TYPE__)
#define __PRIVATE_select_atomic_compare_exchange_x_explicit(func, ptr, poldval, newval, succ, fail)                                  \
	(sizeof(*(ptr)) == 1 ? (func##8)((__UINT8_TYPE__ *)(ptr), (__UINT8_TYPE__)(poldval), (__UINT8_TYPE__)(newval), succ, fail) :     \
	 sizeof(*(ptr)) == 2 ? (func##16)((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(poldval), (__UINT16_TYPE__)(newval), succ, fail) : \
	 sizeof(*(ptr)) == 4 ? (func##32)((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(poldval), (__UINT32_TYPE__)(newval), succ, fail) : \
	                       (func##64)((__UINT64_TYPE__ *)(ptr), (__UINT64_TYPE__)(poldval), (__UINT64_TYPE__)(newval), succ, fail))
#else /* ... */
#define __PRIVATE_select_atomic_compare_exchange_x_explicit(func, ptr, poldval, newval, succ, fail)                                  \
	(sizeof(*(ptr)) == 1 ? (func##8)((__UINT8_TYPE__ *)(ptr), (__UINT8_TYPE__)(poldval), (__UINT8_TYPE__)(newval), succ, fail) :     \
	 sizeof(*(ptr)) == 2 ? (func##16)((__UINT16_TYPE__ *)(ptr), (__UINT16_TYPE__)(poldval), (__UINT16_TYPE__)(newval), succ, fail) : \
	                       (func##32)((__UINT32_TYPE__ *)(ptr), (__UINT32_TYPE__)(poldval), (__UINT32_TYPE__)(newval), succ, fail))
#endif /* !... */
#define atomic_compare_exchange_strong_explicit(ptr, poldval, newval, succ, fail) \
	__PRIVATE_select_atomic_compare_exchange_x_explicit(__PRIVATE_atomic_compare_exchange_strong_explicit_, ptr, poldval, newval, succ, fail)
#define atomic_compare_exchange_weak_explicit(ptr, poldval, newval, succ, fail) \
	__PRIVATE_select_atomic_compare_exchange_x_explicit(__PRIVATE_atomic_compare_exchange_weak_explicit_, ptr, poldval, newval, succ, fail)
#endif /* !... */
#define atomic_compare_exchange_strong(ptr, poldval, newval) \
	atomic_compare_exchange_strong_explicit(ptr, poldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_weak(ptr, poldval, newval) \
	atomic_compare_exchange_weak_explicit(ptr, poldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_fetch_add(ptr, val)                 __hybrid_atomic_fetchadd(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_add_explicit(ptr, val, order) __hybrid_atomic_fetchadd(ptr, val, order)
#define atomic_fetch_sub(ptr, val)                 __hybrid_atomic_fetchsub(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_sub_explicit(ptr, val, order) __hybrid_atomic_fetchsub(ptr, val, order)
#define atomic_fetch_or(ptr, val)                  __hybrid_atomic_fetchor(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_or_explicit(ptr, val, order)  __hybrid_atomic_fetchor(ptr, val, order)
#define atomic_fetch_xor(ptr, val)                 __hybrid_atomic_fetchxor(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_xor_explicit(ptr, val, order) __hybrid_atomic_fetchxor(ptr, val, order)
#define atomic_fetch_and(ptr, val)                 __hybrid_atomic_fetchand(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_and_explicit(ptr, val, order) __hybrid_atomic_fetchand(ptr, val, order)

#ifdef __USE_KOS
#define atomic_cmpxch(ptr, oldval, newval)                           __hybrid_atomic_cmpxch(ptr, oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cmpxch_explicit(ptr, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch(ptr, oldval, newval, succ, fail)
#define atomic_cmpxch_val(ptr, oldval, newval)                       __hybrid_atomic_cmpxch_val(ptr, oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cmpxch_val_explicit(ptr, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val(ptr, oldval, newval, succ, fail)
#define atomic_cmpxch_weak(ptr, oldval, newval)                      __hybrid_atomic_cmpxch_weak(ptr, oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cmpxch_weak_explicit(ptr, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak(ptr, oldval, newval, succ, fail)
#define atomic_fetch_nand(ptr, val)                                  __hybrid_atomic_fetchnand(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_nand_explicit(ptr, val, order)                  __hybrid_atomic_fetchnand(ptr, val, order)
#endif /* __USE_KOS */

typedef struct {
	atomic_bool __val;
} atomic_flag;
#define ATOMIC_FLAG_INIT { 0 }

#define atomic_flag_test_and_set(ptr)                 __hybrid_atomic_xch(&(ptr)->__val, 1, __ATOMIC_SEQ_CST)
#define atomic_flag_test_and_set_explicit(ptr, order) __hybrid_atomic_xch(&(ptr)->__val, 1, order)
#define atomic_flag_clear(ptr)                        __hybrid_atomic_store(&(ptr)->__val, 0, __ATOMIC_SEQ_CST)
#define atomic_flag_clear_explicit(ptr, order)        __hybrid_atomic_store(&(ptr)->__val, 0, order)

__DECL_END
#endif /* !__cplusplus */



#ifdef __CC__

#ifdef __USE_KOS
/* KOS-extension: allow use of atomic operations with stuff that wasn't declared as `_Atomic'
 * -> Also expose a bunch of extra functions which may be used to do atomic operations. */
#undef atomic_thread_fence
#undef atomic_signal_fence
#define atomic_thread_fence(order) __hybrid_atomic_thread_fence(order)
#define atomic_signal_fence(order) __hybrid_atomic_signal_fence(order)

#undef atomic_load_explicit
#undef atomic_store_explicit
#undef atomic_xch_explicit
#undef atomic_fetchinc_explicit
#undef atomic_fetchdec_explicit
#undef atomic_fetchadd_explicit
#undef atomic_fetchsub_explicit
#undef atomic_fetchand_explicit
#undef atomic_fetchxor_explicit
#undef atomic_fetchor_explicit
#undef atomic_fetchnand_explicit
#undef atomic_incfetch_explicit
#undef atomic_decfetch_explicit
#undef atomic_addfetch_explicit
#undef atomic_subfetch_explicit
#undef atomic_andfetch_explicit
#undef atomic_xorfetch_explicit
#undef atomic_orfetch_explicit
#undef atomic_nandfetch_explicit
#undef atomic_inc_explicit
#undef atomic_dec_explicit
#undef atomic_add_explicit
#undef atomic_sub_explicit
#undef atomic_and_explicit
#undef atomic_xor_explicit
#undef atomic_or_explicit
#undef atomic_nand_explicit
#undef atomic_cmpxch_explicit
#undef atomic_cmpxch_weak_explicit
#undef atomic_cmpxch_val_explicit
#ifdef __cplusplus
/* Need some extra hacking so that something like `std::atomic_load_explicit()' isn't
 * a compiler error. We also  don't want to generate  any extra debug information  in
 * regards to extra stack frames! */
__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN
template<class __T> struct __PRIVATE_stdatomic_rt;
template<class __T> struct __PRIVATE_stdatomic_rt<__T *> { typedef __T __type; };
#ifdef __COMPILER_HAVE_CXX_TEMPLATE_USING
template<class __T> using __PRIVATE_stdatomic_rt_t = typename __PRIVATE_stdatomic_rt<__T>::__type;
#define __PRIVATE_STDATOMIC_RT(...) __PRIVATE_stdatomic_rt_t<__VA_ARGS__>
#else /* __COMPILER_HAVE_CXX_TEMPLATE_USING */
#define __PRIVATE_STDATOMIC_RT(...) /*typename*/ __PRIVATE_stdatomic_rt<__VA_ARGS__>::__type
#endif /* __COMPILER_HAVE_CXX_TEMPLATE_USING */
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
template<class __T> struct __atomic_valptr { typedef __T __type; };
template<class __T> struct __atomic_valptr< __NAMESPACE_STD_SYM atomic<__T> > { typedef __T *__type; };
template<class __T> struct __atomic_valptr< __NAMESPACE_STD_SYM atomic<__T> const> { typedef __T const *__type; };
template<class __T> struct __atomic_valptr< __NAMESPACE_STD_SYM atomic<__T> volatile> { typedef __T volatile *__type; };
template<class __T> struct __atomic_valptr< __NAMESPACE_STD_SYM atomic<__T> const volatile> { typedef __T const volatile *__type; };
template<class __T> struct __atomic_valptr< __NAMESPACE_INT_SYM __atomic_int<__T> > { typedef __T *__type; };
template<class __T> struct __atomic_valptr< __NAMESPACE_INT_SYM __atomic_int<__T> const> { typedef __T const *__type; };
template<class __T> struct __atomic_valptr< __NAMESPACE_INT_SYM __atomic_int<__T> volatile> { typedef __T volatile *__type; };
template<class __T> struct __atomic_valptr< __NAMESPACE_INT_SYM __atomic_int<__T> const volatile> { typedef __T const volatile *__type; };
template<> struct __atomic_valptr< __NAMESPACE_STD_SYM atomic_flag> { typedef __BYTE_TYPE__ *__type; };
template<> struct __atomic_valptr< __NAMESPACE_STD_SYM atomic_flag const> { typedef __BYTE_TYPE__ const *__type; };
template<> struct __atomic_valptr< __NAMESPACE_STD_SYM atomic_flag volatile> { typedef __BYTE_TYPE__ volatile *__type; };
template<> struct __atomic_valptr< __NAMESPACE_STD_SYM atomic_flag const volatile> { typedef __BYTE_TYPE__ const volatile *__type; };
template<class __T> struct __atomic_valptr<__T &>: public __atomic_valptr<__T> {};
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T> struct __atomic_valptr<__T &&>: public __atomic_valptr<__T> {};
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
#ifdef __COMPILER_HAVE_CXX_TEMPLATE_USING
template<class __T> using __atomic_valptr_t = typename __atomic_valptr<__T>::__type;
#define __PRIVATE_ATOMIC_VALPTR(p) ((__NAMESPACE_INT_SYM __atomic_valptr_t<decltype(p)>)(p))
#define __PRIVATE_ATOMIC_VALTYP(p) __NAMESPACE_INT_SYM __atomic_valptr_t<decltype(p)>
#else /* __COMPILER_HAVE_CXX_TEMPLATE_USING */
#define __PRIVATE_ATOMIC_VALPTR(p) ((/*typename*/ __NAMESPACE_INT_SYM __atomic_valptr<decltype(p)>::__type)(p))
#define __PRIVATE_ATOMIC_VALTYP(p) /*typename*/ __NAMESPACE_INT_SYM __atomic_valptr<decltype(p)>::__type
#endif /* !__COMPILER_HAVE_CXX_TEMPLATE_USING */
__NAMESPACE_INT_END
#ifndef __COMPILER_HAVE_BUG_BLOATY_CXX_USING
#ifdef __COMPILER_HAVE_CXX_TEMPLATE_USING
using __NAMESPACE_STD_SYM __PRIVATE_stdatomic_rt_t;
#else /* __COMPILER_HAVE_CXX_TEMPLATE_USING */
using __NAMESPACE_STD_SYM __PRIVATE_stdatomic_rt;
#endif /* __COMPILER_HAVE_CXX_TEMPLATE_USING */
#endif /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING */
__CXXDECL_END

#define atomic_load_explicit(ptr, order)                             __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_load(__PRIVATE_ATOMIC_VALPTR(ptr), order))
#define atomic_store_explicit(ptr, val, order)                       __PRIVATE_STDATOMIC_RT(void *)(__hybrid_atomic_store(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_xch_explicit(ptr, val, order)                         __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_xch(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_fetchinc_explicit(ptr, order)                         __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_fetchinc(__PRIVATE_ATOMIC_VALPTR(ptr), order))
#define atomic_fetchdec_explicit(ptr, order)                         __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_fetchdec(__PRIVATE_ATOMIC_VALPTR(ptr), order))
#define atomic_fetchadd_explicit(ptr, val, order)                    __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_fetchadd(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_fetchsub_explicit(ptr, val, order)                    __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_fetchsub(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_fetchand_explicit(ptr, val, order)                    __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_fetchand(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_fetchxor_explicit(ptr, val, order)                    __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_fetchxor(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_fetchor_explicit(ptr, val, order)                     __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_fetchor(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_fetchnand_explicit(ptr, val, order)                   __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_fetchnand(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_incfetch_explicit(ptr, order)                         __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_incfetch(__PRIVATE_ATOMIC_VALPTR(ptr), order))
#define atomic_decfetch_explicit(ptr, order)                         __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_decfetch(__PRIVATE_ATOMIC_VALPTR(ptr), order))
#define atomic_addfetch_explicit(ptr, val, order)                    __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_addfetch(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_subfetch_explicit(ptr, val, order)                    __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_subfetch(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_andfetch_explicit(ptr, val, order)                    __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_andfetch(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_xorfetch_explicit(ptr, val, order)                    __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_xorfetch(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_orfetch_explicit(ptr, val, order)                     __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_orfetch(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_nandfetch_explicit(ptr, val, order)                   __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_nandfetch(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_inc_explicit(ptr, order)                              __PRIVATE_STDATOMIC_RT(void *)(__hybrid_atomic_inc(__PRIVATE_ATOMIC_VALPTR(ptr), order))
#define atomic_dec_explicit(ptr, order)                              __PRIVATE_STDATOMIC_RT(void *)(__hybrid_atomic_dec(__PRIVATE_ATOMIC_VALPTR(ptr), order))
#define atomic_add_explicit(ptr, val, order)                         __PRIVATE_STDATOMIC_RT(void *)(__hybrid_atomic_add(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_sub_explicit(ptr, val, order)                         __PRIVATE_STDATOMIC_RT(void *)(__hybrid_atomic_sub(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_and_explicit(ptr, val, order)                         __PRIVATE_STDATOMIC_RT(void *)(__hybrid_atomic_and(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_xor_explicit(ptr, val, order)                         __PRIVATE_STDATOMIC_RT(void *)(__hybrid_atomic_xor(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_or_explicit(ptr, val, order)                          __PRIVATE_STDATOMIC_RT(void *)(__hybrid_atomic_or(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_nand_explicit(ptr, val, order)                        __PRIVATE_STDATOMIC_RT(void *)(__hybrid_atomic_nand(__PRIVATE_ATOMIC_VALPTR(ptr), val, order))
#define atomic_cmpxch_explicit(ptr, oldval, newval, succ, fail)      __PRIVATE_STDATOMIC_RT(bool *)(__hybrid_atomic_cmpxch(__PRIVATE_ATOMIC_VALPTR(ptr), oldval, newval, succ, fail))
#define atomic_cmpxch_weak_explicit(ptr, oldval, newval, succ, fail) __PRIVATE_STDATOMIC_RT(bool *)(__hybrid_atomic_cmpxch_weak(__PRIVATE_ATOMIC_VALPTR(ptr), oldval, newval, succ, fail))
#define atomic_cmpxch_val_explicit(ptr, oldval, newval, succ, fail)  __PRIVATE_STDATOMIC_RT(__PRIVATE_ATOMIC_VALTYP(ptr))(__hybrid_atomic_cmpxch_val(__PRIVATE_ATOMIC_VALPTR(ptr), oldval, newval, succ, fail))
#else /* __cplusplus */
#define atomic_load_explicit(ptr, order)                             __hybrid_atomic_load(ptr, order)
#define atomic_store_explicit(ptr, val, order)                       __hybrid_atomic_store(ptr, val, order)
#define atomic_xch_explicit(ptr, val, order)                         __hybrid_atomic_xch(ptr, val, order)
#define atomic_fetchinc_explicit(ptr, order)                         __hybrid_atomic_fetchinc(ptr, order)
#define atomic_fetchdec_explicit(ptr, order)                         __hybrid_atomic_fetchdec(ptr, order)
#define atomic_fetchadd_explicit(ptr, val, order)                    __hybrid_atomic_fetchadd(ptr, val, order)
#define atomic_fetchsub_explicit(ptr, val, order)                    __hybrid_atomic_fetchsub(ptr, val, order)
#define atomic_fetchand_explicit(ptr, val, order)                    __hybrid_atomic_fetchand(ptr, val, order)
#define atomic_fetchxor_explicit(ptr, val, order)                    __hybrid_atomic_fetchxor(ptr, val, order)
#define atomic_fetchor_explicit(ptr, val, order)                     __hybrid_atomic_fetchor(ptr, val, order)
#define atomic_fetchnand_explicit(ptr, val, order)                   __hybrid_atomic_fetchnand(ptr, val, order)
#define atomic_incfetch_explicit(ptr, order)                         __hybrid_atomic_incfetch(ptr, order)
#define atomic_decfetch_explicit(ptr, order)                         __hybrid_atomic_decfetch(ptr, order)
#define atomic_addfetch_explicit(ptr, val, order)                    __hybrid_atomic_addfetch(ptr, val, order)
#define atomic_subfetch_explicit(ptr, val, order)                    __hybrid_atomic_subfetch(ptr, val, order)
#define atomic_andfetch_explicit(ptr, val, order)                    __hybrid_atomic_andfetch(ptr, val, order)
#define atomic_xorfetch_explicit(ptr, val, order)                    __hybrid_atomic_xorfetch(ptr, val, order)
#define atomic_orfetch_explicit(ptr, val, order)                     __hybrid_atomic_orfetch(ptr, val, order)
#define atomic_nandfetch_explicit(ptr, val, order)                   __hybrid_atomic_nandfetch(ptr, val, order)
#define atomic_inc_explicit(ptr, order)                              __hybrid_atomic_inc(ptr, order)
#define atomic_dec_explicit(ptr, order)                              __hybrid_atomic_dec(ptr, order)
#define atomic_add_explicit(ptr, val, order)                         __hybrid_atomic_add(ptr, val, order)
#define atomic_sub_explicit(ptr, val, order)                         __hybrid_atomic_sub(ptr, val, order)
#define atomic_and_explicit(ptr, val, order)                         __hybrid_atomic_and(ptr, val, order)
#define atomic_xor_explicit(ptr, val, order)                         __hybrid_atomic_xor(ptr, val, order)
#define atomic_or_explicit(ptr, val, order)                          __hybrid_atomic_or(ptr, val, order)
#define atomic_nand_explicit(ptr, val, order)                        __hybrid_atomic_nand(ptr, val, order)
#define atomic_cmpxch_explicit(ptr, oldval, newval, succ, fail)      __hybrid_atomic_cmpxch(ptr, oldval, newval, succ, fail)
#define atomic_cmpxch_weak_explicit(ptr, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_weak(ptr, oldval, newval, succ, fail)
#define atomic_cmpxch_val_explicit(ptr, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val(ptr, oldval, newval, succ, fail)
#endif /* !__cplusplus */

#undef atomic_load
#undef atomic_store
#undef atomic_xch
#undef atomic_fetchinc
#undef atomic_fetchdec
#undef atomic_fetchadd
#undef atomic_fetchsub
#undef atomic_fetchand
#undef atomic_fetchxor
#undef atomic_fetchor
#undef atomic_fetchnand
#undef atomic_incfetch
#undef atomic_decfetch
#undef atomic_addfetch
#undef atomic_subfetch
#undef atomic_andfetch
#undef atomic_xorfetch
#undef atomic_orfetch
#undef atomic_nandfetch
#undef atomic_inc
#undef atomic_dec
#undef atomic_add
#undef atomic_sub
#undef atomic_and
#undef atomic_xor
#undef atomic_or
#undef atomic_nand
#undef atomic_cmpxch
#undef atomic_cmpxch_weak
#undef atomic_cmpxch_val
#define atomic_load(ptr)                        atomic_load_explicit(ptr, __ATOMIC_SEQ_CST)
#define atomic_store(ptr, val)                  atomic_store_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_xch(ptr, val)                    atomic_xch_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetchinc(ptr)                    atomic_fetchinc_explicit(ptr, __ATOMIC_SEQ_CST)
#define atomic_fetchdec(ptr)                    atomic_fetchdec_explicit(ptr, __ATOMIC_SEQ_CST)
#define atomic_fetchadd(ptr, val)               atomic_fetchadd_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetchsub(ptr, val)               atomic_fetchsub_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetchand(ptr, val)               atomic_fetchand_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetchxor(ptr, val)               atomic_fetchxor_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetchor(ptr, val)                atomic_fetchor_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetchnand(ptr, val)              atomic_fetchnand_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_incfetch(ptr)                    atomic_incfetch_explicit(ptr, __ATOMIC_SEQ_CST)
#define atomic_decfetch(ptr)                    atomic_decfetch_explicit(ptr, __ATOMIC_SEQ_CST)
#define atomic_addfetch(ptr, val)               atomic_addfetch_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_subfetch(ptr, val)               atomic_subfetch_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_andfetch(ptr, val)               atomic_andfetch_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_xorfetch(ptr, val)               atomic_xorfetch_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_orfetch(ptr, val)                atomic_orfetch_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_nandfetch(ptr, val)              atomic_nandfetch_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_inc(ptr)                         atomic_inc_explicit(ptr, __ATOMIC_SEQ_CST)
#define atomic_dec(ptr)                         atomic_dec_explicit(ptr, __ATOMIC_SEQ_CST)
#define atomic_add(ptr, val)                    atomic_add_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_sub(ptr, val)                    atomic_sub_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_and(ptr, val)                    atomic_and_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_xor(ptr, val)                    atomic_xor_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_or(ptr, val)                     atomic_or_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_nand(ptr, val)                   atomic_nand_explicit(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_cmpxch(ptr, oldval, newval)      atomic_cmpxch_explicit(ptr, oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cmpxch_weak(ptr, oldval, newval) atomic_cmpxch_weak_explicit(ptr, oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cmpxch_val(ptr, oldval, newval)  atomic_cmpxch_val_explicit(ptr, oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

/* Define aliases for actual stdc/stdc++ functions (which like to have an '_' between `fetch' and the operation-name) */
#undef atomic_fetch_add
#undef atomic_fetch_add_explicit
#undef atomic_fetch_sub
#undef atomic_fetch_sub_explicit
#undef atomic_fetch_or
#undef atomic_fetch_or_explicit
#undef atomic_fetch_xor
#undef atomic_fetch_xor_explicit
#undef atomic_fetch_and
#undef atomic_fetch_and_explicit
#define atomic_fetch_add(ptr, val)                 atomic_fetchadd(ptr, val)
#define atomic_fetch_add_explicit(ptr, val, order) atomic_fetchadd_explicit(ptr, val, order)
#define atomic_fetch_sub(ptr, val)                 atomic_fetchsub(ptr, val)
#define atomic_fetch_sub_explicit(ptr, val, order) atomic_fetchsub_explicit(ptr, val, order)
#define atomic_fetch_or(ptr, val)                  atomic_fetchor(ptr, val)
#define atomic_fetch_or_explicit(ptr, val, order)  atomic_fetchor_explicit(ptr, val, order)
#define atomic_fetch_xor(ptr, val)                 atomic_fetchxor(ptr, val)
#define atomic_fetch_xor_explicit(ptr, val, order) atomic_fetchxor_explicit(ptr, val, order)
#define atomic_fetch_and(ptr, val)                 atomic_fetchand(ptr, val)
#define atomic_fetch_and_explicit(ptr, val, order) atomic_fetchand_explicit(ptr, val, order)

/* Finally, have some useful helper macros to do atomic read/write with ACQUIRE/RELEASE semantics. */
#define atomic_read(ptr)       atomic_load_explicit(ptr, __ATOMIC_ACQUIRE)
#define atomic_write(ptr, val) atomic_store_explicit(ptr, val, __ATOMIC_RELEASE)
#endif /* __USE_KOS */

#ifndef kill_dependency
#ifndef __NO_XBLOCK
#if defined(__COMPILER_HAVE_AUTOTYPE)
#define kill_dependency(x)                       \
	__XBLOCK({                                   \
		__auto_type __kill_dependency_tmp = (x); \
		__XRETURN __kill_dependency_tmp;         \
	})
#elif defined(__COMPILER_HAVE_TYPEOF)
#define kill_dependency(x)                         \
	__XBLOCK({                                     \
		__typeof__(x) __kill_dependency_tmp = (x); \
		__XRETURN __kill_dependency_tmp;           \
	})
#endif
#endif /* !__NO_XBLOCK */
#ifndef kill_dependency
#define kill_dependency(x) (x)
#endif /* !kill_dependency */
#endif /* !kill_dependency */

#endif /* __CC__ */

#if !defined(ATOMIC_BOOL_LOCK_FREE) && defined(__GCC_ATOMIC_BOOL_LOCK_FREE)
#define ATOMIC_BOOL_LOCK_FREE __GCC_ATOMIC_BOOL_LOCK_FREE
#endif /* !ATOMIC_BOOL_LOCK_FREE && __GCC_ATOMIC_BOOL_LOCK_FREE */
#if !defined(ATOMIC_CHAR_LOCK_FREE) && defined(__GCC_ATOMIC_CHAR_LOCK_FREE)
#define ATOMIC_CHAR_LOCK_FREE __GCC_ATOMIC_CHAR_LOCK_FREE
#endif /* !ATOMIC_CHAR_LOCK_FREE && __GCC_ATOMIC_CHAR_LOCK_FREE */
#if !defined(ATOMIC_CHAR8_T_LOCK_FREE) && defined(__GCC_ATOMIC_CHAR8_T_LOCK_FREE)
#define ATOMIC_CHAR8_T_LOCK_FREE __GCC_ATOMIC_CHAR8_T_LOCK_FREE
#endif /* !ATOMIC_CHAR8_T_LOCK_FREE && __GCC_ATOMIC_CHAR8_T_LOCK_FREE */
#if !defined(ATOMIC_CHAR16_T_LOCK_FREE) && defined(__GCC_ATOMIC_CHAR16_T_LOCK_FREE)
#define ATOMIC_CHAR16_T_LOCK_FREE __GCC_ATOMIC_CHAR16_T_LOCK_FREE
#endif /* !ATOMIC_CHAR16_T_LOCK_FREE && __GCC_ATOMIC_CHAR16_T_LOCK_FREE */
#if !defined(ATOMIC_CHAR32_T_LOCK_FREE) && defined(__GCC_ATOMIC_CHAR32_T_LOCK_FREE)
#define ATOMIC_CHAR32_T_LOCK_FREE __GCC_ATOMIC_CHAR32_T_LOCK_FREE
#endif /* !ATOMIC_CHAR32_T_LOCK_FREE && __GCC_ATOMIC_CHAR32_T_LOCK_FREE */
#if !defined(ATOMIC_WCHAR_T_LOCK_FREE) && defined(__GCC_ATOMIC_WCHAR_T_LOCK_FREE)
#define ATOMIC_WCHAR_T_LOCK_FREE __GCC_ATOMIC_WCHAR_T_LOCK_FREE
#endif /* !ATOMIC_WCHAR_T_LOCK_FREE && __GCC_ATOMIC_WCHAR_T_LOCK_FREE */
#if !defined(ATOMIC_SHORT_LOCK_FREE) && defined(__GCC_ATOMIC_SHORT_LOCK_FREE)
#define ATOMIC_SHORT_LOCK_FREE __GCC_ATOMIC_SHORT_LOCK_FREE
#endif /* !ATOMIC_SHORT_LOCK_FREE && __GCC_ATOMIC_SHORT_LOCK_FREE */
#if !defined(ATOMIC_INT_LOCK_FREE) && defined(__GCC_ATOMIC_INT_LOCK_FREE)
#define ATOMIC_INT_LOCK_FREE __GCC_ATOMIC_INT_LOCK_FREE
#endif /* !ATOMIC_INT_LOCK_FREE && __GCC_ATOMIC_INT_LOCK_FREE */
#if !defined(ATOMIC_LONG_LOCK_FREE) && defined(__GCC_ATOMIC_LONG_LOCK_FREE)
#define ATOMIC_LONG_LOCK_FREE __GCC_ATOMIC_LONG_LOCK_FREE
#endif /* !ATOMIC_LONG_LOCK_FREE && __GCC_ATOMIC_LONG_LOCK_FREE */
#if !defined(ATOMIC_LLONG_LOCK_FREE) && defined(__GCC_ATOMIC_LLONG_LOCK_FREE)
#define ATOMIC_LLONG_LOCK_FREE __GCC_ATOMIC_LLONG_LOCK_FREE
#endif /* !ATOMIC_LLONG_LOCK_FREE && __GCC_ATOMIC_LLONG_LOCK_FREE */
#if !defined(ATOMIC_POINTER_LOCK_FREE) && defined(__GCC_ATOMIC_POINTER_LOCK_FREE)
#define ATOMIC_POINTER_LOCK_FREE __GCC_ATOMIC_POINTER_LOCK_FREE
#endif /* !ATOMIC_POINTER_LOCK_FREE && __GCC_ATOMIC_POINTER_LOCK_FREE */

#endif /* !_STDATOMIC_H */
