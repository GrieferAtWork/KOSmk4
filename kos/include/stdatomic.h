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
#ifndef _STDATOMIC_H
#define _STDATOMIC_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

#ifndef __CC__
#define memory_order_relaxed __ATOMIC_RELAXED
#define memory_order_consume __ATOMIC_CONSUME
#define memory_order_acquire __ATOMIC_ACQUIRE
#define memory_order_release __ATOMIC_RELEASE
#define memory_order_acq_rel __ATOMIC_ACQ_REL
#define memory_order_seq_cst __ATOMIC_SEQ_CST
#elif defined(__cplusplus)
#include <atomic>

__DECL_BEGIN
__NAMESPACE_STD_USING(memory_order)
__NAMESPACE_STD_USING(memory_order_relaxed)
__NAMESPACE_STD_USING(memory_order_consume)
__NAMESPACE_STD_USING(memory_order_acquire)
__NAMESPACE_STD_USING(memory_order_release)
__NAMESPACE_STD_USING(memory_order_acq_rel)
__NAMESPACE_STD_USING(memory_order_seq_cst)

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

#ifdef __USE_KOS
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
#endif /* __USE_KOS */

__NAMESPACE_STD_USING(atomic_flag)
__NAMESPACE_STD_USING(atomic_flag_test_and_set_explicit)
__NAMESPACE_STD_USING(atomic_flag_test_and_set)
__NAMESPACE_STD_USING(atomic_flag_clear_explicit)
__NAMESPACE_STD_USING(atomic_flag_clear)
__DECL_END

#else /* __cplusplus */

__DECL_BEGIN

typedef enum {
	memory_order_relaxed = __ATOMIC_RELAXED,
	memory_order_consume = __ATOMIC_CONSUME,
	memory_order_acquire = __ATOMIC_ACQUIRE,
	memory_order_release = __ATOMIC_RELEASE,
	memory_order_acq_rel = __ATOMIC_ACQ_REL,
	memory_order_seq_cst = __ATOMIC_SEQ_CST
} memory_order;

#if 0 /* ??? */
#define __atomic_var_field(x) *(x)
#define ATOMIC_VAR_INIT(x)     (x)
#define __COMPILER_ATOMIC(T)  _Atomic T
#elif 0
#define __atomic_var_field(x) (x)->__std_atom
#define ATOMIC_VAR_INIT(x)    { x }
#define __COMPILER_ATOMIC(T)  struct { T __std_atom; }
#else
#define __atomic_var_field(x) *(x)
#define ATOMIC_VAR_INIT(x)    (x)
#define __COMPILER_ATOMIC(T)  T
#endif

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
typedef __COMPILER_ATOMIC(__INT_LEAST64_TYPE__) atomic_int_least64_t;
typedef __COMPILER_ATOMIC(__UINT_LEAST64_TYPE__) atomic_uint_least64_t;
typedef __COMPILER_ATOMIC(__INT_FAST8_TYPE__) atomic_int_fast8_t;
typedef __COMPILER_ATOMIC(__UINT_FAST8_TYPE__) atomic_uint_fast8_t;
typedef __COMPILER_ATOMIC(__INT_FAST16_TYPE__) atomic_int_fast16_t;
typedef __COMPILER_ATOMIC(__UINT_FAST16_TYPE__) atomic_uint_fast16_t;
typedef __COMPILER_ATOMIC(__INT_FAST32_TYPE__) atomic_int_fast32_t;
typedef __COMPILER_ATOMIC(__UINT_FAST32_TYPE__) atomic_uint_fast32_t;
typedef __COMPILER_ATOMIC(__INT_FAST64_TYPE__) atomic_int_fast64_t;
typedef __COMPILER_ATOMIC(__UINT_FAST64_TYPE__) atomic_uint_fast64_t;
typedef __COMPILER_ATOMIC(__INTPTR_TYPE__) atomic_intptr_t;
typedef __COMPILER_ATOMIC(__UINTPTR_TYPE__) atomic_uintptr_t;
typedef __COMPILER_ATOMIC(__SIZE_TYPE__) atomic_size_t;
typedef __COMPILER_ATOMIC(__PTRDIFF_TYPE__) atomic_ptrdiff_t;
typedef __COMPILER_ATOMIC(__INTMAX_TYPE__) atomic_intmax_t;
typedef __COMPILER_ATOMIC(__UINTMAX_TYPE__) atomic_uintmax_t;

#define atomic_init(ptr, val) __hybrid_atomic_store(__atomic_var_field(ptr), val, __ATOMIC_RELAXED)
#define atomic_thread_fence(mo) __hybrid_atomic_thread_fence(mo)
#define atomic_signal_fence(mo) __hybrid_atomic_signal_fence(mo)
#define atomic_is_lock_free(obj) __hybrid_atomic_lockfree(__atomic_var_field(&(obj)))

#define atomic_store_explicit(ptr, val, mo)     __hybrid_atomic_store(__atomic_var_field(ptr), val, mo)
#define atomic_store(ptr, val)                  __hybrid_atomic_store(__atomic_var_field(ptr), val, __ATOMIC_SEQ_CST)
#define atomic_load_explicit(ptr, mo)           __hybrid_atomic_load(__atomic_var_field(ptr), mo)
#define atomic_load(ptr)                        __hybrid_atomic_load(__atomic_var_field(ptr), __ATOMIC_SEQ_CST)
#define atomic_exchange_explicit(ptr, val, mo)  __hybrid_atomic_xch(__atomic_var_field(ptr), val, mo)
#define atomic_exchange(ptr, val)               __hybrid_atomic_xch(__atomic_var_field(ptr), val, __ATOMIC_SEQ_CST)
#if (!defined(__NO_XBLOCK) && \
     (defined(__COMPILER_HAVE_AUTOTYPE) || defined(__COMPILER_HAVE_TYPEOF)))
#ifdef __COMPILER_HAVE_AUTOTYPE
#define atomic_compare_exchange_strong_explicit(ptr, poldval, newval, succ, fail)          \
	__XBLOCK({                                                                             \
		__auto_type __acese_poldval = (poldval);                                           \
		__auto_type __acese_newval  = (newval);                                            \
		__XRETURN (*__acese_poldval = __hybrid_atomic_cmpxch_val(__atomic_var_field(ptr),  \
		                                                         *__acese_poldval,         \
		                                                         __acese_newval, succ,     \
		                                                         fail)) == __acese_newval; \
	})
#define atomic_compare_exchange_weak_explicit(ptr, poldval, newval, succ, fail)                 \
	__XBLOCK({                                                                                  \
		__auto_type __acese_poldval = (poldval);                                                \
		__auto_type __acese_newval  = (newval);                                                 \
		__XRETURN (*__acese_poldval = __hybrid_atomic_cmpxch_val_weak(__atomic_var_field(ptr),  \
		                                                              *__acese_poldval,         \
		                                                              __acese_newval, succ,     \
		                                                              fail)) == __acese_newval; \
	})
#else /* __COMPILER_HAVE_AUTOTYPE */
#define atomic_compare_exchange_strong_explicit(ptr, poldval, newval, succ, fail)          \
	__XBLOCK({                                                                             \
		__typeof__(poldval) __acese_poldval = (poldval);                                   \
		__typeof__(newval) __acese_newval  = (newval);                                     \
		__XRETURN (*__acese_poldval = __hybrid_atomic_cmpxch_val(__atomic_var_field(ptr),  \
		                                                         *__acese_poldval,         \
		                                                         __acese_newval, succ,     \
		                                                         fail)) == __acese_newval; \
	})
#define atomic_compare_exchange_weak_explicit(ptr, poldval, newval, succ, fail)                 \
	__XBLOCK({                                                                                  \
		__typeof__(poldval) __acese_poldval = (poldval);                                        \
		__typeof__(newval) __acese_newval  = (newval);                                          \
		__XRETURN (*__acese_poldval = __hybrid_atomic_cmpxch_val_weak(__atomic_var_field(ptr),  \
		                                                              *__acese_poldval,         \
		                                                              __acese_newval, succ,     \
		                                                              fail)) == __acese_newval; \
	})
#endif /* !__COMPILER_HAVE_AUTOTYPE */
#else /* ... */
#define atomic_compare_exchange_strong_explicit(ptr, poldval, newval, succ, fail) \
	((*(poldval) = __hybrid_atomic_cmpxch_val(__atomic_var_field(ptr), *(poldval), newval, succ, fail)) == (newval))
#define atomic_compare_exchange_weak_explicit(ptr, poldval, newval, succ, fail) \
	((*(poldval) = __hybrid_atomic_cmpxch_val_weak(__atomic_var_field(ptr), *(poldval), newval, succ, fail)) == (newval))
#endif /* !... */
#define atomic_compare_exchange_strong(ptr, poldval, newval) \
	atomic_compare_exchange_strong_explicit(ptr, poldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_weak(ptr, poldval, newval) \
	atomic_compare_exchange_weak_explicit(ptr, poldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_fetch_add(ptr, val)               __hybrid_atomic_fetchadd(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_add_explicit(ptr, val, mo)  __hybrid_atomic_fetchadd(ptr, val, mo)
#define atomic_fetch_sub(ptr, val)               __hybrid_atomic_fetchsub(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_sub_explicit(ptr, val, mo)  __hybrid_atomic_fetchsub(ptr, val, mo)
#define atomic_fetch_or(ptr, val)                __hybrid_atomic_fetchor(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_or_explicit(ptr, val, mo)   __hybrid_atomic_fetchor(ptr, val, mo)
#define atomic_fetch_xor(ptr, val)               __hybrid_atomic_fetchxor(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_xor_explicit(ptr, val, mo)  __hybrid_atomic_fetchxor(ptr, val, mo)
#define atomic_fetch_and(ptr, val)               __hybrid_atomic_fetchand(ptr, val, __ATOMIC_SEQ_CST)
#define atomic_fetch_and_explicit(ptr, val, mo)  __hybrid_atomic_fetchand(ptr, val, mo)

#ifdef __USE_KOS
#define atomic_cmpxch_explicit(ptr, oldv, newv, succ, fail)          __hybrid_atomic_cmpxch(__atomic_var_field(ptr), oldv, newv, succ, fail)
#define atomic_cmpxch(ptr, oldv, newv)                               __hybrid_atomic_cmpxch(__atomic_var_field(ptr), oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cmpxch_val_explicit(ptr, oldv, newv, succ, fail)      __hybrid_atomic_cmpxch_val(__atomic_var_field(ptr), oldv, newv, succ, fail)
#define atomic_cmpxch_val(ptr, oldv, newv)                           __hybrid_atomic_cmpxch_val(__atomic_var_field(ptr), oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cmpxch_weak_explicit(ptr, oldv, newv, succ, fail)     __hybrid_atomic_cmpxch_weak(__atomic_var_field(ptr), oldv, newv, succ, fail)
#define atomic_cmpxch_weak(ptr, oldv, newv)                          __hybrid_atomic_cmpxch_weak(__atomic_var_field(ptr), oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_cmpxch_val_weak_explicit(ptr, oldv, newv, succ, fail) __hybrid_atomic_cmpxch_val_weak(__atomic_var_field(ptr), oldv, newv, succ, fail)
#define atomic_cmpxch_val_weak(ptr, oldv, newv)                      __hybrid_atomic_cmpxch_val_weak(__atomic_var_field(ptr), oldv, newv, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_fetch_nand(ptr, val)                                  __hybrid_atomic_fetchnand(__atomic_var_field(ptr), val, __ATOMIC_SEQ_CST)
#define atomic_fetch_nand_explicit(ptr, val, mo)                     __hybrid_atomic_fetchnand(__atomic_var_field(ptr), val, mo)
#endif /* __USE_KOS */

typedef struct {
	atomic_bool __val;
} atomic_flag;
#define ATOMIC_FLAG_INIT { 0 }

#define atomic_flag_test_and_set_explicit(ptr, mo) __hybrid_atomic_xch(__atomic_var_field(&(ptr)->__val), 1, mo)
#define atomic_flag_test_and_set(ptr)              __hybrid_atomic_xch(__atomic_var_field(&(ptr)->__val), 1, __ATOMIC_SEQ_CST)
#define atomic_flag_clear_explicit(ptr, mo)        __hybrid_atomic_store(__atomic_var_field(&(ptr)->__val), 0, mo)
#define atomic_flag_clear(ptr)                     __hybrid_atomic_store(__atomic_var_field(&(ptr)->__val), 0, __ATOMIC_SEQ_CST)

__DECL_END
#endif /* !__cplusplus */


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

#define ATOMIC_BOOL_LOCK_FREE     __GCC_ATOMIC_BOOL_LOCK_FREE
#define ATOMIC_CHAR_LOCK_FREE     __GCC_ATOMIC_CHAR_LOCK_FREE
#define ATOMIC_CHAR16_T_LOCK_FREE __GCC_ATOMIC_CHAR16_T_LOCK_FREE
#define ATOMIC_CHAR32_T_LOCK_FREE __GCC_ATOMIC_CHAR32_T_LOCK_FREE
#define ATOMIC_WCHAR_T_LOCK_FREE  __GCC_ATOMIC_WCHAR_T_LOCK_FREE
#define ATOMIC_SHORT_LOCK_FREE    __GCC_ATOMIC_SHORT_LOCK_FREE
#define ATOMIC_INT_LOCK_FREE      __GCC_ATOMIC_INT_LOCK_FREE
#define ATOMIC_LONG_LOCK_FREE     __GCC_ATOMIC_LONG_LOCK_FREE
#define ATOMIC_LLONG_LOCK_FREE    __GCC_ATOMIC_LLONG_LOCK_FREE
#define ATOMIC_POINTER_LOCK_FREE  __GCC_ATOMIC_POINTER_LOCK_FREE

#endif /* !_STDATOMIC_H */
