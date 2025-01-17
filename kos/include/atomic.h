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
/* (#) Portability: FreeBSD       (/sys/[...]/include/atomic.h) */
/* (#) Portability: GNU C Library (/include/atomic.h) */
/* (#) Portability: NetBSD        (/include/atomic.h) */
/* (#) Portability: OpenBSD       (/sys/arch/[...]/include/atomic.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/atomic.h) */
/* (#) Portability: uClibc        (/include/atomic.h) */
#ifndef _ATOMIC_H
#define _ATOMIC_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

/* This header also exists on some other platforms. Emulate macros defined by them. */
#ifndef __USE_KOS_PURE
/************************************************************************/
/* OpenSolaris                                                          */
/************************************************************************/
#include <sys/atomic.h>


/************************************************************************/
/* uClibc / Glibc (intern-only)                                         */
/************************************************************************/
#include <hybrid/sched/__yield.h>

#define atomic_compare_and_exchange_val_acq(ptr, newval, oldval)   __hybrid_atomic_cmpxch_val(ptr, oldval, newval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#define atomic_compare_and_exchange_val_rel(ptr, newval, oldval)   __hybrid_atomic_cmpxch_val(ptr, oldval, newval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#define catomic_compare_and_exchange_val_acq(ptr, newval, oldval)  __hybrid_atomic_cmpxch_val(ptr, oldval, newval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#define catomic_compare_and_exchange_val_rel(ptr, newval, oldval)  __hybrid_atomic_cmpxch_val(ptr, oldval, newval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#define atomic_compare_and_exchange_bool_acq(ptr, newval, oldval)  __hybrid_atomic_cmpxch(ptr, oldval, newval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#define atomic_compare_and_exchange_bool_rel(ptr, newval, oldval)  __hybrid_atomic_cmpxch(ptr, oldval, newval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#define catomic_compare_and_exchange_bool_acq(ptr, newval, oldval) __hybrid_atomic_cmpxch(ptr, oldval, newval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#define catomic_compare_and_exchange_bool_rel(ptr, newval, oldval) __hybrid_atomic_cmpxch(ptr, oldval, newval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#define atomic_exchange_acq(ptr, value)                            __hybrid_atomic_xch(ptr, value, __ATOMIC_ACQUIRE)
#define atomic_exchange_rel(ptr, value)                            __hybrid_atomic_xch(ptr, value, __ATOMIC_RELEASE)
#define atomic_exchange_and_add(ptr, value)                        __hybrid_atomic_fetchadd(ptr, value, __ATOMIC_SEQ_CST)
#define catomic_exchange_and_add(ptr, value)                       __hybrid_atomic_fetchadd(ptr, value, __ATOMIC_SEQ_CST)
#define atomic_min(ptr, value)                                                      \
	do {                                                                            \
		__typeof__(*(ptr)) *_am_ptr = (ptr), _am_val = (value), _am_oldval;         \
		do {                                                                        \
			_am_oldval = __hybrid_atomic_load(_am_ptr, __ATOMIC_ACQUIRE);           \
			if (_am_oldval <= _am_val)                                              \
				break;                                                              \
		} while (!__hybrid_atomic_cmpxch_weak(_am_ptr, _am_oldval, _am_val,         \
		                                      __ATOMIC_RELEASE, __ATOMIC_RELEASE)); \
	}	__WHILE0
#define atomic_max(ptr, value)                                                      \
	do {                                                                            \
		__typeof__(*(ptr)) *_am_ptr = (ptr), _am_val = (value), _am_oldval;         \
		do {                                                                        \
			_am_oldval = __hybrid_atomic_load(_am_ptr, __ATOMIC_ACQUIRE);           \
			if (_am_oldval >= _am_val)                                              \
				break;                                                              \
		} while (!__hybrid_atomic_cmpxch_weak(_am_ptr, _am_oldval, _am_val,         \
		                                      __ATOMIC_RELEASE, __ATOMIC_RELEASE)); \
	}	__WHILE0
#define catomic_min(ptr, value)        atomic_min(ptr, value)
#define catomic_max(ptr, value)        atomic_max(ptr, value)
#define atomic_add(ptr, value)         __hybrid_atomic_add(ptr, value, __ATOMIC_SEQ_CST)
#define catomic_add(ptr, value)        __hybrid_atomic_add(ptr, value, __ATOMIC_SEQ_CST)
#define atomic_increment(ptr)          __hybrid_atomic_fetchinc(ptr, __ATOMIC_SEQ_CST)
#define catomic_increment(ptr)         __hybrid_atomic_fetchinc(ptr, __ATOMIC_SEQ_CST)
#define atomic_increment_val(ptr)      __hybrid_atomic_incfetch(ptr, __ATOMIC_SEQ_CST)
#define catomic_increment_val(ptr)     __hybrid_atomic_incfetch(ptr, __ATOMIC_SEQ_CST)
#define atomic_increment_and_test(ptr) (__hybrid_atomic_incfetch(ptr, __ATOMIC_SEQ_CST) == 0)
#define atomic_decrement(ptr)          __hybrid_atomic_fetchdec(ptr, __ATOMIC_SEQ_CST)
#define catomic_decrement(ptr)         __hybrid_atomic_fetchdec(ptr, __ATOMIC_SEQ_CST)
#define atomic_decrement_val(ptr)      __hybrid_atomic_decfetch(ptr, __ATOMIC_SEQ_CST)
#define catomic_decrement_val(ptr)     __hybrid_atomic_decfetch(ptr, __ATOMIC_SEQ_CST)
#define atomic_decrement_and_test(ptr) (__hybrid_atomic_decfetch(ptr, __ATOMIC_SEQ_CST) == 0)
#define atomic_decrement_if_positive(ptr)                                                \
	__XBLOCK({                                                                           \
		__typeof__(*(ptr)) *_adip_ptr = (ptr), _adip_oldval;                             \
		do {                                                                             \
			_adip_oldval = __hybrid_atomic_load(_am_ptr, __ATOMIC_ACQUIRE);              \
			if (_adip_oldval <= 0)                                                       \
				break;                                                                   \
		} while (!__hybrid_atomic_cmpxch_weak(_adip_ptr, _adip_oldval, _adip_oldval - 1, \
		                                      __ATOMIC_RELEASE, __ATOMIC_RELEASE));      \
		__XRETURN _adip_oldval;                                                          \
	})
#define atomic_add_negative(ptr, value)                                                        \
	__XBLOCK({                                                                                 \
		__typeof__(value) __aan_value = (value);                                               \
		__XRETURN __hybrid_atomic_fetchadd(ptr, __aan_value, __ATOMIC_SEQ_CST) < -__aan_value; \
	})
#define atomic_add_zero(ptr, value)                                                             \
	__XBLOCK({                                                                                  \
		__typeof__(value) __aan_value = (value);                                                \
		__XRETURN __hybrid_atomic_fetchadd(ptr, __aan_value, __ATOMIC_SEQ_CST) == -__aan_value; \
	})
#define atomic_bit_test_set(ptr, bit)                                                        \
	__XBLOCK({                                                                               \
		__typeof__(*(ptr)) __abts_mask = (__typeof__(*(ptr)))1 << (bit);                     \
		__XRETURN __hybrid_atomic_fetchor(ptr, __abts_mask, __ATOMIC_SEQ_CST) & __abts_mask; \
	})
#define atomic_bit_set(ptr, bit)  __hybrid_atomic_or(ptr, __typeof__(*(ptr))1 << (bit), __ATOMIC_SEQ_CST)
#define atomic_and(ptr, mask)     __hybrid_atomic_and(ptr, mask, __ATOMIC_SEQ_CST)
#define catomic_and(ptr, mask)    __hybrid_atomic_and(ptr, mask, __ATOMIC_SEQ_CST)
#define atomic_and_val(ptr, mask) __hybrid_atomic_fetchand(ptr, mask, __ATOMIC_SEQ_CST)
#define atomic_or(ptr, mask)      __hybrid_atomic_or(ptr, mask, __ATOMIC_SEQ_CST)
#define catomic_or(ptr, mask)     __hybrid_atomic_or(ptr, mask, __ATOMIC_SEQ_CST)
#define atomic_or_val(ptr, mask)  __hybrid_atomic_fetchor(ptr, mask, __ATOMIC_SEQ_CST)
#define atomic_full_barrier()     __hybrid_atomic_signal_fence(__ATOMIC_SEQ_CST)
#define atomic_read_barrier()     __hybrid_atomic_signal_fence(__ATOMIC_ACQUIRE)
#define atomic_write_barrier()    __hybrid_atomic_signal_fence(__ATOMIC_RELEASE)
#define atomic_forced_read(var) \
	__XBLOCK({                  \
		__typeof__(var) __res;  \
		__asm__(""              \
		        : "=r"(__res)   \
		        : "0"(var));    \
		__XRETURN __res;        \
	})
#define atomic_delay() (void)__hybrid_yield_nx()
#endif /* !__USE_KOS_PURE */


/* Simplified header that only exposes the KOS-specific extensions found in <stdatomic.h>,
 * without the need of also defining everything  that is specified by the C/C++  standard,
 * which in the later case includes a whole bunch of template surrounding `std::atomic<T>' */
#if defined(__USE_KOS_PURE) || defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#ifndef __CC__
#ifndef memory_order_relaxed
#define memory_order_relaxed __ATOMIC_RELAXED
#define memory_order_consume __ATOMIC_CONSUME
#define memory_order_acquire __ATOMIC_ACQUIRE
#define memory_order_release __ATOMIC_RELEASE
#define memory_order_acq_rel __ATOMIC_ACQ_REL
#define memory_order_seq_cst __ATOMIC_SEQ_CST
#endif /* !memory_order_relaxed */
#else /* !__CC__ */
#if defined(_CXX_ATOMIC) || defined(_STDATOMIC_H)
#include <stdatomic.h>

/* <stdatomic.h> only defines this stuff when `__USE_KOS' is  enabled.
 * Since we want to define it always, only do so when that wasn't done
 * already. */
#ifndef __USE_KOS
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
#endif /* !__USE_KOS */
#else /* _CXX_ATOMIC || _STDATOMIC_H */

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
#endif /* !_CXX_ATOMIC && !_STDATOMIC_H */

#undef atomic_thread_fence
#undef atomic_signal_fence
#define atomic_thread_fence(order) __hybrid_atomic_thread_fence(order)
#define atomic_signal_fence(order) __hybrid_atomic_signal_fence(order)

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

#define atomic_xch_acquire(ptr, val)                    atomic_xch_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_fetchinc_acquire(ptr)                    atomic_fetchinc_explicit(ptr, __ATOMIC_ACQUIRE)
#define atomic_fetchdec_acquire(ptr)                    atomic_fetchdec_explicit(ptr, __ATOMIC_ACQUIRE)
#define atomic_fetchadd_acquire(ptr, val)               atomic_fetchadd_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_fetchsub_acquire(ptr, val)               atomic_fetchsub_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_fetchand_acquire(ptr, val)               atomic_fetchand_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_fetchxor_acquire(ptr, val)               atomic_fetchxor_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_fetchor_acquire(ptr, val)                atomic_fetchor_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_fetchnand_acquire(ptr, val)              atomic_fetchnand_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_incfetch_acquire(ptr)                    atomic_incfetch_explicit(ptr, __ATOMIC_ACQUIRE)
#define atomic_decfetch_acquire(ptr)                    atomic_decfetch_explicit(ptr, __ATOMIC_ACQUIRE)
#define atomic_addfetch_acquire(ptr, val)               atomic_addfetch_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_subfetch_acquire(ptr, val)               atomic_subfetch_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_andfetch_acquire(ptr, val)               atomic_andfetch_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_xorfetch_acquire(ptr, val)               atomic_xorfetch_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_orfetch_acquire(ptr, val)                atomic_orfetch_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_nandfetch_acquire(ptr, val)              atomic_nandfetch_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_inc_acquire(ptr)                         atomic_inc_explicit(ptr, __ATOMIC_ACQUIRE)
#define atomic_dec_acquire(ptr)                         atomic_dec_explicit(ptr, __ATOMIC_ACQUIRE)
#define atomic_add_acquire(ptr, val)                    atomic_add_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_sub_acquire(ptr, val)                    atomic_sub_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_and_acquire(ptr, val)                    atomic_and_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_xor_acquire(ptr, val)                    atomic_xor_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_or_acquire(ptr, val)                     atomic_or_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_nand_acquire(ptr, val)                   atomic_nand_explicit(ptr, val, __ATOMIC_ACQUIRE)
#define atomic_cmpxch_acquire(ptr, oldval, newval)      atomic_cmpxch_explicit(ptr, oldval, newval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#define atomic_cmpxch_weak_acquire(ptr, oldval, newval) atomic_cmpxch_weak_explicit(ptr, oldval, newval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#define atomic_cmpxch_val_acquire(ptr, oldval, newval)  atomic_cmpxch_val_explicit(ptr, oldval, newval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define atomic_xch_release(ptr, val)                    atomic_xch_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_fetchinc_release(ptr)                    atomic_fetchinc_explicit(ptr, __ATOMIC_RELEASE)
#define atomic_fetchdec_release(ptr)                    atomic_fetchdec_explicit(ptr, __ATOMIC_RELEASE)
#define atomic_fetchadd_release(ptr, val)               atomic_fetchadd_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_fetchsub_release(ptr, val)               atomic_fetchsub_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_fetchand_release(ptr, val)               atomic_fetchand_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_fetchxor_release(ptr, val)               atomic_fetchxor_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_fetchor_release(ptr, val)                atomic_fetchor_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_fetchnand_release(ptr, val)              atomic_fetchnand_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_incfetch_release(ptr)                    atomic_incfetch_explicit(ptr, __ATOMIC_RELEASE)
#define atomic_decfetch_release(ptr)                    atomic_decfetch_explicit(ptr, __ATOMIC_RELEASE)
#define atomic_addfetch_release(ptr, val)               atomic_addfetch_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_subfetch_release(ptr, val)               atomic_subfetch_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_andfetch_release(ptr, val)               atomic_andfetch_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_xorfetch_release(ptr, val)               atomic_xorfetch_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_orfetch_release(ptr, val)                atomic_orfetch_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_nandfetch_release(ptr, val)              atomic_nandfetch_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_inc_release(ptr)                         atomic_inc_explicit(ptr, __ATOMIC_RELEASE)
#define atomic_dec_release(ptr)                         atomic_dec_explicit(ptr, __ATOMIC_RELEASE)
#define atomic_add_release(ptr, val)                    atomic_add_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_sub_release(ptr, val)                    atomic_sub_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_and_release(ptr, val)                    atomic_and_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_xor_release(ptr, val)                    atomic_xor_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_or_release(ptr, val)                     atomic_or_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_nand_release(ptr, val)                   atomic_nand_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_cmpxch_release(ptr, oldval, newval)      atomic_cmpxch_explicit(ptr, oldval, newval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#define atomic_cmpxch_weak_release(ptr, oldval, newval) atomic_cmpxch_weak_explicit(ptr, oldval, newval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#define atomic_cmpxch_val_release(ptr, oldval, newval)  atomic_cmpxch_val_explicit(ptr, oldval, newval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)

/* Finally, have some useful helper macros to do atomic read/write with ACQUIRE/RELEASE semantics. */
#undef atomic_read
#undef atomic_write
#undef atomic_read_relaxed
#undef atomic_write_relaxed
#define atomic_read(ptr)               atomic_load_explicit(ptr, __ATOMIC_ACQUIRE)
#define atomic_write(ptr, val)         atomic_store_explicit(ptr, val, __ATOMIC_RELEASE)
#define atomic_read_relaxed(ptr)       atomic_load_explicit(ptr, __ATOMIC_RELAXED)
#define atomic_write_relaxed(ptr, val) atomic_store_explicit(ptr, val, __ATOMIC_RELAXED)

/* TODO: Allowed to be non-atomic, but needs compiler read barrier! */
#undef read_once
#define read_once(ptr) atomic_read(ptr)

/* TODO: Allowed to be non-atomic, but needs compiler write barrier! */
#undef write_once
#define write_once(ptr, val) atomic_write(ptr, val)
#endif /* __CC__ */
#endif /* __USE_KOS_PURE || __USE_KOS || __USE_KOS_KERNEL */

#endif /* !_ATOMIC_H */
