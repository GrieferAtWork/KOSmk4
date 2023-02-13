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
#ifndef __GUARD_HYBRID___ATOMIC_H
#define __GUARD_HYBRID___ATOMIC_H 1

#include "../__stdinc.h"
#include "typecore.h"

#ifndef __cplusplus
#ifdef __COMPILER_HAVE_TYPEOF
#define __ATOMIC_RECAST(p, y) ((__typeof__(*(p)))(y))
#elif 1
#define __ATOMIC_RECAST(p, y) (1 ? (y) : *(p))
#else /* ... */
#define __ATOMIC_RECAST(p, y) (y)
#endif /* !... */
#endif /* !__cplusplus */

#if defined(_MSC_VER) && !defined(__cplusplus)
#define __ATOMIC_DOWNCAST(T) (T)(__UINTPTR_TYPE__)
#else /* _MSC_VER && !__cplusplus */
#define __ATOMIC_DOWNCAST(T) (T)
#endif /* !_MSC_VER || __cplusplus */

/* Define atomic memory order constants. */
#ifndef __ATOMIC_RELAXED
#define __ATOMIC_RELAXED 0
#endif /* !__ATOMIC_RELAXED */
#ifndef __ATOMIC_CONSUME
#define __ATOMIC_CONSUME 1
#endif /* !__ATOMIC_CONSUME */
#ifndef __ATOMIC_ACQUIRE
#define __ATOMIC_ACQUIRE 2
#endif /* !__ATOMIC_ACQUIRE */
#ifndef __ATOMIC_RELEASE
#define __ATOMIC_RELEASE 3
#endif /* !__ATOMIC_RELEASE */
#ifndef __ATOMIC_ACQ_REL
#define __ATOMIC_ACQ_REL 4
#endif /* !__ATOMIC_ACQ_REL */
#ifndef __ATOMIC_SEQ_CST
#define __ATOMIC_SEQ_CST 5
#endif /* !__ATOMIC_SEQ_CST */

/* Figure out how to implement atomic operations.
 *
 * >> uintN_t __hybrid_atomic_loadN(uintN_t const *p, int order);
 * >> uintN_t __hybrid_atomic_storeN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_xchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchincN(uintN_t *p, int order);
 * >> uintN_t __hybrid_atomic_fetchdecN(uintN_t *p, int order);
 * >> uintN_t __hybrid_atomic_fetchaddN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchsubN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchandN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchxorN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchorN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_fetchnandN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_incfetchN(uintN_t *p, int order);
 * >> uintN_t __hybrid_atomic_decfetchN(uintN_t *p, int order);
 * >> uintN_t __hybrid_atomic_addfetchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_subfetchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_andfetchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_xorfetchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_orfetchN(uintN_t *p, uintN_t val, int order);
 * >> uintN_t __hybrid_atomic_nandfetchN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_incN(uintN_t *p, int order);
 * >> void    __hybrid_atomic_decN(uintN_t *p, int order);
 * >> void    __hybrid_atomic_addN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_subN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_andN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_xorN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_orN(uintN_t *p, uintN_t val, int order);
 * >> void    __hybrid_atomic_nandN(uintN_t *p, uintN_t val, int order);
 * >> bool    __hybrid_atomic_cmpxchN(uintN_t *p, uintN_t oldval, uintN_t newval, int succ, int fail);
 * >> bool    __hybrid_atomic_cmpxch_weakN(uintN_t *p, uintN_t oldval, uintN_t newval, int succ, int fail);
 * >> uintN_t __hybrid_atomic_cmpxch_valN(uintN_t *p, uintN_t oldval, uintN_t newval, int succ, int fail);
 *
 * >> T    __hybrid_atomic_load(T const *p, int order);
 * >> T    __hybrid_atomic_store(T *p, T val, int order);
 * >> T    __hybrid_atomic_xch(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchinc(T *p, int order);
 * >> T    __hybrid_atomic_fetchdec(T *p, int order);
 * >> T    __hybrid_atomic_fetchadd(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchsub(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchand(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchxor(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchor(T *p, T val, int order);
 * >> T    __hybrid_atomic_fetchnand(T *p, T val, int order);
 * >> T    __hybrid_atomic_incfetch(T *p, int order);
 * >> T    __hybrid_atomic_decfetch(T *p, int order);
 * >> T    __hybrid_atomic_addfetch(T *p, T val, int order);
 * >> T    __hybrid_atomic_subfetch(T *p, T val, int order);
 * >> T    __hybrid_atomic_andfetch(T *p, T val, int order);
 * >> T    __hybrid_atomic_xorfetch(T *p, T val, int order);
 * >> T    __hybrid_atomic_orfetch(T *p, T val, int order);
 * >> T    __hybrid_atomic_nandfetch(T *p, T val, int order);
 * >> void __hybrid_atomic_inc(T *p, int order);
 * >> void __hybrid_atomic_dec(T *p, int order);
 * >> void __hybrid_atomic_add(T *p, T val, int order);
 * >> void __hybrid_atomic_sub(T *p, T val, int order);
 * >> void __hybrid_atomic_and(T *p, T val, int order);
 * >> void __hybrid_atomic_xor(T *p, T val, int order);
 * >> void __hybrid_atomic_or(T *p, T val, int order);
 * >> void __hybrid_atomic_nand(T *p, T val, int order);
 * >> bool __hybrid_atomic_cmpxch(T *p, T oldval, T newval, int succ, int fail);
 * >> bool __hybrid_atomic_cmpxch_weak(T *p, T oldval, T newval, int succ, int fail);
 * >> T    __hybrid_atomic_cmpxch_val(T *p, T oldval, T newval, int succ, int fail);
 * >> void __hybrid_atomic_thread_fence(int order);
 * >> void __hybrid_atomic_signal_fence(int order);
 */


/* HINT: In order to have full atomic support, we need at least an cmpxch/cmpxch_weak function */
#ifdef __CC__
#ifdef __HYBRID_ATOMIC_USE_LIBATOMIC
#include "__atomic-libatomic.h" /* libatomic */
/**/
#include "__atomic-complete.h"
#elif ((defined(__GNUC__) && __GCC_VERSION_NUM >= 40700) || \
       defined(____INTELLISENSE_STDINC_COMMON_H) || defined(__clang__))
/* __atomic_xxx() */
#define __hybrid_atomic_load(p, order)                             __atomic_load_n(p, order)
#define __hybrid_atomic_store(p, val, order)                       __atomic_store_n(p, val, order)
#define __hybrid_atomic_xch(p, val, order)                         __atomic_exchange_n(p, val, order)
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail)      __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __XRETURN __atomic_compare_exchange_n(p, &__oldv, newval, 0, succ, fail); })
#define __hybrid_atomic_cmpxch_weak(p, oldval, newval, succ, fail) __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __XRETURN __atomic_compare_exchange_n(p, &__oldv, newval, 1, succ, fail); })
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail)  __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __atomic_compare_exchange_n(p, &__oldv, newval, 0, succ, fail); __XRETURN __oldv; })
#define __hybrid_atomic_incfetch(p, order)                         __atomic_add_fetch(p, 1, order)
#define __hybrid_atomic_decfetch(p, order)                         __atomic_sub_fetch(p, 1, order)
#define __hybrid_atomic_addfetch(p, val, order)                    __atomic_add_fetch(p, val, order)
#define __hybrid_atomic_subfetch(p, val, order)                    __atomic_sub_fetch(p, val, order)
#define __hybrid_atomic_andfetch(p, val, order)                    __atomic_and_fetch(p, val, order)
#define __hybrid_atomic_orfetch(p, val, order)                     __atomic_or_fetch(p, val, order)
#define __hybrid_atomic_xorfetch(p, val, order)                    __atomic_xor_fetch(p, val, order)
#define __hybrid_atomic_nandfetch(p, val, order)                   __atomic_nand_fetch(p, val, order)
#define __hybrid_atomic_fetchinc(p, order)                         __atomic_fetch_add(p, 1, order)
#define __hybrid_atomic_fetchdec(p, order)                         __atomic_fetch_sub(p, 1, order)
#define __hybrid_atomic_fetchadd(p, val, order)                    __atomic_fetch_add(p, val, order)
#define __hybrid_atomic_fetchsub(p, val, order)                    __atomic_fetch_sub(p, val, order)
#define __hybrid_atomic_fetchand(p, val, order)                    __atomic_fetch_and(p, val, order)
#define __hybrid_atomic_fetchor(p, val, order)                     __atomic_fetch_or(p, val, order)
#define __hybrid_atomic_fetchxor(p, val, order)                    __atomic_fetch_xor(p, val, order)
#define __hybrid_atomic_fetchnand(p, val, order)                   __atomic_fetch_nand(p, val, order)
#define __hybrid_atomic_thread_fence(order)                        __atomic_thread_fence(order)
#define __hybrid_atomic_signal_fence(order)                        __atomic_signal_fence(order)
#define __hybrid_atomic_inc(p, order)                              (void)__hybrid_atomic_fetchinc(p, order)
#define __hybrid_atomic_dec(p, order)                              (void)__hybrid_atomic_fetchdec(p, order)
#define __hybrid_atomic_add(p, val, order)                         (void)__hybrid_atomic_fetchadd(p, val, order)
#define __hybrid_atomic_sub(p, val, order)                         (void)__hybrid_atomic_fetchsub(p, val, order)
#define __hybrid_atomic_and(p, val, order)                         (void)__hybrid_atomic_fetchand(p, val, order)
#define __hybrid_atomic_or(p, val, order)                          (void)__hybrid_atomic_fetchor(p, val, order)
#define __hybrid_atomic_xor(p, val, order)                         (void)__hybrid_atomic_fetchxor(p, val, order)
#define __hybrid_atomic_nand(p, val, order)                        (void)__hybrid_atomic_fetchnand(p, val, order)
#define __hybrid_atomic_lockfree(p)                                __atomic_is_lock_free(sizeof(*(p)), p)
#elif __has_extension(c_atomic) || __has_extension(cxx_atomic) /* clang */
/* __c11_atomic_xxx() */
#define __hybrid_atomic_load(p, order)                             __c11_atomic_load(p, order)
#define __hybrid_atomic_store(p, val, order)                       __c11_atomic_store(p, val, order)
#define __hybrid_atomic_xch(p, val, order)                         __c11_atomic_exchange(p, val, order)
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail)      __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __XRETURN __c11_atomic_compare_exchange_strong(p, &__oldv, newval, succ, fail); })
#define __hybrid_atomic_cmpxch_weak(p, oldval, newval, succ, fail) __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __XRETURN __c11_atomic_compare_exchange_weak(p, &__oldv, newval, succ, fail); })
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail)  __XBLOCK({ __typeof__(*(p)) __oldv = (oldval); __c11_atomic_compare_exchange_strong(p, &__oldv, newval, succ, fail); __XRETURN __oldv; })
#define __hybrid_atomic_fetchinc(p, order)                         __c11_atomic_fetch_add(p, 1, order)
#define __hybrid_atomic_fetchdec(p, order)                         __c11_atomic_fetch_sub(p, 1, order)
#define __hybrid_atomic_fetchadd(p, val, order)                    __c11_atomic_fetch_add(p, val, order)
#define __hybrid_atomic_fetchsub(p, val, order)                    __c11_atomic_fetch_sub(p, val, order)
#define __hybrid_atomic_fetchand(p, val, order)                    __c11_atomic_fetch_and(p, val, order)
#define __hybrid_atomic_fetchor(p, val, order)                     __c11_atomic_fetch_or(p, val, order)
#define __hybrid_atomic_fetchxor(p, val, order)                    __c11_atomic_fetch_xor(p, val, order)
#define __hybrid_atomic_incfetch(p, order)                         (__hybrid_atomic_fetchinc(p, order) + 1)
#define __hybrid_atomic_decfetch(p, order)                         (__hybrid_atomic_fetchdec(p, order) - 1)
#define __hybrid_atomic_addfetch(p, val, order)                    __XBLOCK({ __typeof__(val) __val = (val); __XRETURN __hybrid_atomic_fetchadd(p, __val, order) + __val; })
#define __hybrid_atomic_subfetch(p, val, order)                    __XBLOCK({ __typeof__(val) __val = (val); __XRETURN __hybrid_atomic_fetchsub(p, __val, order) - __val; })
#define __hybrid_atomic_andfetch(p, val, order)                    __XBLOCK({ __typeof__(val) __val = (val); __XRETURN __hybrid_atomic_fetchand(p, __val, order) & __val; })
#define __hybrid_atomic_orfetch(p, val, order)                     __XBLOCK({ __typeof__(val) __val = (val); __XRETURN __hybrid_atomic_fetchor(p, __val, order) | __val; })
#define __hybrid_atomic_xorfetch(p, val, order)                    __XBLOCK({ __typeof__(val) __val = (val); __XRETURN __hybrid_atomic_fetchxor(p, __val, order) ^ __val; })
#define __hybrid_atomic_inc(p, order)                              (void)__hybrid_atomic_fetchinc(p, order)
#define __hybrid_atomic_dec(p, order)                              (void)__hybrid_atomic_fetchdec(p, order)
#define __hybrid_atomic_add(p, val, order)                         (void)__hybrid_atomic_fetchadd(p, val, order)
#define __hybrid_atomic_sub(p, val, order)                         (void)__hybrid_atomic_fetchsub(p, val, order)
#define __hybrid_atomic_and(p, val, order)                         (void)__hybrid_atomic_fetchand(p, val, order)
#define __hybrid_atomic_or(p, val, order)                          (void)__hybrid_atomic_fetchor(p, val, order)
#define __hybrid_atomic_xor(p, val, order)                         (void)__hybrid_atomic_fetchxor(p, val, order)
#define __hybrid_atomic_thread_fence(order)                        __c11_atomic_thread_fence(order)
#define __hybrid_atomic_signal_fence(order)                        __c11_atomic_signal_fence(order)
#define __hybrid_atomic_lockfree(p)                                __atomic_is_lock_free(sizeof(*(p)), p)
#elif defined(__GNUC__) || defined(__DCC_VERSION__)
/* __sync_xxx() */
#define __hybrid_atomic_addfetch_seq_cst(p, val)                  __sync_add_and_fetch(p, val)
#define __hybrid_atomic_subfetch_seq_cst(p, val)                  __sync_sub_and_fetch(p, val)
#define __hybrid_atomic_orfetch_seq_cst(p, val)                   __sync_or_and_fetch(p, val)
#define __hybrid_atomic_andfetch_seq_cst(p, val)                  __sync_and_and_fetch(p, val)
#define __hybrid_atomic_xorfetch_seq_cst(p, val)                  __sync_xor_and_fetch(p, val)
#define __hybrid_atomic_fetchadd_seq_cst(p, val)                  __sync_fetch_and_add(p, val)
#define __hybrid_atomic_fetchsub_seq_cst(p, val)                  __sync_fetch_and_sub(p, val)
#define __hybrid_atomic_fetchor_seq_cst(p, val)                   __sync_fetch_and_or(p, val)
#define __hybrid_atomic_fetchand_seq_cst(p, val)                  __sync_fetch_and_and(p, val)
#define __hybrid_atomic_fetchxor_seq_cst(p, val)                  __sync_fetch_and_xor(p, val)
#define __hybrid_atomic_cmpxch_seq_cst(p, oldval, newval)         __sync_bool_compare_and_swap(p, oldval, newval)
#define __hybrid_atomic_cmpxch_val_seq_cst(p, oldval, newval)     __sync_val_compare_and_swap(p, oldval, newval)
#define __hybrid_atomic_thread_fence_seq_cst()                    __sync_synchronize()
#define __hybrid_atomic_addfetch(p, val, order)                   __hybrid_atomic_addfetch_seq_cst(p, val)
#define __hybrid_atomic_subfetch(p, val, order)                   __hybrid_atomic_subfetch_seq_cst(p, val)
#define __hybrid_atomic_orfetch(p, val, order)                    __hybrid_atomic_orfetch_seq_cst(p, val)
#define __hybrid_atomic_andfetch(p, val, order)                   __hybrid_atomic_andfetch_seq_cst(p, val)
#define __hybrid_atomic_xorfetch(p, val, order)                   __hybrid_atomic_xorfetch_seq_cst(p, val)
#define __hybrid_atomic_fetchadd(p, val, order)                   __hybrid_atomic_fetchadd_seq_cst(p, val)
#define __hybrid_atomic_fetchsub(p, val, order)                   __hybrid_atomic_fetchsub_seq_cst(p, val)
#define __hybrid_atomic_fetchor(p, val, order)                    __hybrid_atomic_fetchor_seq_cst(p, val)
#define __hybrid_atomic_fetchand(p, val, order)                   __hybrid_atomic_fetchand_seq_cst(p, val)
#define __hybrid_atomic_fetchxor(p, val, order)                   __hybrid_atomic_fetchxor_seq_cst(p, val)
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail)     __hybrid_atomic_cmpxch_seq_cst(p, oldval, newval)
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_val_seq_cst(p, oldval, newval)
#define __hybrid_atomic_thread_fence(order)                       __hybrid_atomic_thread_fence_seq_cst()
#if !defined(__GNUC__) || __GCC_VERSION_NUM >= 40400
#define __hybrid_atomic_fetchnand_seq_cst(p, val) __sync_fetch_and_nand(p, val)
#define __hybrid_atomic_nandfetch_seq_cst(p, val) __sync_nand_and_fetch(p, val)
#define __hybrid_atomic_fetchnand(p, val, order)  __hybrid_atomic_fetchnand_seq_cst(p, val)
#define __hybrid_atomic_nandfetch(p, val, order)  __hybrid_atomic_nandfetch_seq_cst(p, val)
#endif /* GCC 4.4 */
/**/
#include "__atomic-complete.h"
#elif __has_builtin(__sync_bool_compare_and_swap) || __has_builtin(__sync_val_compare_and_swap)
/* __sync_xxx()  (compiler-detected)
 * Note that  for full  support, the  compiler must  at least  provide
 * `__sync_bool_compare_and_swap()' or `__sync_val_compare_and_swap()' */
#if __has_builtin(__sync_bool_compare_and_swap)
#define __hybrid_atomic_cmpxch_seq_cst(p, oldval, newval) \
	__sync_bool_compare_and_swap(p, oldval, newval)
#endif /* __has_builtin(__sync_bool_compare_and_swap) */
#if __has_builtin(__sync_val_compare_and_swap)
#define __hybrid_atomic_cmpxch_val_seq_cst(p, oldval, newval) \
	__sync_val_compare_and_swap(p, oldval, newval)
#endif /* __has_builtin(__sync_val_compare_and_swap) */

#if __has_builtin(__sync_swap)
#define __hybrid_atomic_xch_seq_cst(p, val) __sync_swap(p, val)
#endif /* __has_builtin(__sync_swap) */
#if __has_builtin(__sync_add_and_fetch)
#define __hybrid_atomic_addfetch_seq_cst(p, val) __sync_add_and_fetch(p, val)
#endif /* __has_builtin(__sync_add_and_fetch) */
#if __has_builtin(__sync_sub_and_fetch)
#define __hybrid_atomic_subfetch_seq_cst(p, val) __sync_sub_and_fetch(p, val)
#endif /* __has_builtin(__sync_sub_and_fetch) */
#if __has_builtin(__sync_or_and_fetch)
#define __hybrid_atomic_orfetch_seq_cst(p, val) __sync_or_and_fetch(p, val)
#endif /* __has_builtin(__sync_or_and_fetch) */
#if __has_builtin(__sync_and_and_fetch)
#define __hybrid_atomic_andfetch_seq_cst(p, val) __sync_and_and_fetch(p, val)
#endif /* __has_builtin(__sync_and_and_fetch) */
#if __has_builtin(__sync_xor_and_fetch)
#define __hybrid_atomic_xorfetch_seq_cst(p, val) __sync_xor_and_fetch(p, val)
#endif /* __has_builtin(__sync_xor_and_fetch) */
#if __has_builtin(__sync_fetch_and_add)
#define __hybrid_atomic_fetchadd_seq_cst(p, val) __sync_fetch_and_add(p, val)
#endif /* __has_builtin(__sync_fetch_and_add) */
#if __has_builtin(__sync_fetch_and_sub)
#define __hybrid_atomic_fetchsub_seq_cst(p, val) __sync_fetch_and_sub(p, val)
#endif /* __has_builtin(__sync_fetch_and_sub) */
#if __has_builtin(__sync_fetch_and_or)
#define __hybrid_atomic_fetchor_seq_cst(p, val) __sync_fetch_and_or(p, val)
#endif /* __has_builtin(__sync_fetch_and_or) */
#if __has_builtin(__sync_fetch_and_and)
#define __hybrid_atomic_fetchand_seq_cst(p, val) __sync_fetch_and_and(p, val)
#endif /* __has_builtin(__sync_fetch_and_and) */
#if __has_builtin(__sync_fetch_and_xor)
#define __hybrid_atomic_fetchxor_seq_cst(p, val) __sync_fetch_and_xor(p, val)
#endif /* __has_builtin(__sync_fetch_and_xor) */
#if __has_builtin(__sync_fetch_and_nand)
#define __hybrid_atomic_fetchnand_seq_cst(p, val) __sync_fetch_and_nand(p, val)
#endif /* __has_builtin(__sync_fetch_and_nand) */
#if __has_builtin(__sync_nand_and_fetch)
#define __hybrid_atomic_nandfetch_seq_cst(p, val) __sync_nand_and_fetch(p, val)
#endif /* __has_builtin(__sync_nand_and_fetch) */
#if __has_builtin(__sync_synchronize)
#define __hybrid_atomic_thread_fence(order) __sync_synchronize()
#endif /* __has_builtin(__sync_synchronize) */

#ifdef __hybrid_atomic_cmpxch_seq_cst
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch_seq_cst(p, oldval, newval)
#endif /* __hybrid_atomic_cmpxch_seq_cst */
#ifdef __hybrid_atomic_cmpxch_val_seq_cst
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch_val_seq_cst(p, oldval, newval)
#endif /* __hybrid_atomic_cmpxch_val_seq_cst */
#ifdef __hybrid_atomic_addfetch_seq_cst
#define __hybrid_atomic_addfetch(p, val, order) __hybrid_atomic_addfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_addfetch_seq_cst */
#ifdef __hybrid_atomic_subfetch_seq_cst
#define __hybrid_atomic_subfetch(p, val, order) __hybrid_atomic_subfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_subfetch_seq_cst */
#ifdef __hybrid_atomic_orfetch_seq_cst
#define __hybrid_atomic_orfetch(p, val, order) __hybrid_atomic_orfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_orfetch_seq_cst */
#ifdef __hybrid_atomic_andfetch_seq_cst
#define __hybrid_atomic_andfetch(p, val, order) __hybrid_atomic_andfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_andfetch_seq_cst */
#ifdef __hybrid_atomic_xorfetch_seq_cst
#define __hybrid_atomic_xorfetch(p, val, order) __hybrid_atomic_xorfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_xorfetch_seq_cst */
#ifdef __hybrid_atomic_fetchadd_seq_cst
#define __hybrid_atomic_fetchadd(p, val, order) __hybrid_atomic_fetchadd_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchadd_seq_cst */
#ifdef __hybrid_atomic_fetchsub_seq_cst
#define __hybrid_atomic_fetchsub(p, val, order) __hybrid_atomic_fetchsub_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchsub_seq_cst */
#ifdef __hybrid_atomic_fetchor_seq_cst
#define __hybrid_atomic_fetchor(p, val, order) __hybrid_atomic_fetchor_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchor_seq_cst */
#ifdef __hybrid_atomic_fetchand_seq_cst
#define __hybrid_atomic_fetchand(p, val, order) __hybrid_atomic_fetchand_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchand_seq_cst */
#ifdef __hybrid_atomic_fetchxor_seq_cst
#define __hybrid_atomic_fetchxor(p, val, order) __hybrid_atomic_fetchxor_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchxor_seq_cst */
#ifdef __hybrid_atomic_fetchnand_seq_cst
#define __hybrid_atomic_fetchnand(p, val, order) __hybrid_atomic_fetchnand_seq_cst(p, val)
#endif /* __hybrid_atomic_fetchnand_seq_cst */
#ifdef __hybrid_atomic_nandfetch_seq_cst
#define __hybrid_atomic_nandfetch(p, val, order) __hybrid_atomic_nandfetch_seq_cst(p, val)
#endif /* __hybrid_atomic_nandfetch_seq_cst */
/**/
#include "__atomic-complete.h"
#elif defined(_MSC_VER)
/* _InterlockedXXX() */
#ifdef __cplusplus
#pragma warning(push) /* Keep `4197' disabled in C because of its use in macros. */
#endif /* __cplusplus */
#pragma warning(disable: 4197) /* Casting away `volatile' */
#pragma warning(disable: 4047) /* Differing number of dereferences. */
#pragma warning(disable: 4310) /* Cast truncates constant value */
#include "__atomic-msvc.h"
/**/
#include "__atomic-complete.h"
#ifdef __cplusplus
#pragma warning(pop)
#endif /* __cplusplus */
#else /* ... */
#ifdef __COMPILER_HAVE_GCC_ASM
#include "host.h"
#if defined(__x86_64__) || defined(__i386__)
/* __asm__("lock; cmpxchg") */
#include "__atomic-gasm-x86.h"
/**/
#include "__atomic-complete.h"
#endif /* __x86_64__ || __i386__ */
#endif /* __COMPILER_HAVE_GCC_ASM */

/* Fallback: just use libatomic. - If it's not there, we'll
 * get  link errors, but  for now it's the  best we can do. */
#ifndef __hybrid_atomic_cmpxch
#include "__atomic-libatomic.h"
/**/
#include "__atomic-complete.h"
#endif /* !__hybrid_atomic_cmpxch */
#endif /* !... */

#ifndef __hybrid_atomic_signal_fence
/* Fallback: Emit compiler barriers to implement atomic signal fencing.
 * HINT: If available, compiler barriers are implemented using intrinsic
 *       signal fences, meaning that they are literally the same  thing.
 * e.g.: When hosted by msvc, stuff like `_ReadWriteBarrier()' will appear below. */
#ifdef __COMPILER_BARRIERS_ALL_IDENTICAL
#define __hybrid_atomic_signal_fence(order) __COMPILER_BARRIER()
#else /* __COMPILER_BARRIERS_ALL_IDENTICAL */
#define __hybrid_atomic_signal_fence(order)                     \
	((order) >= __ATOMIC_ACQ_REL ? __COMPILER_BARRIER() :       \
	 (order) >= __ATOMIC_RELEASE ? __COMPILER_WRITE_BARRIER() : \
	 (order) >= __ATOMIC_ACQUIRE ? __COMPILER_READ_BARRIER() : (void)0)
#endif /* !__COMPILER_BARRIERS_ALL_IDENTICAL */
#endif /* !__hybrid_atomic_signal_fence */

#ifndef __hybrid_atomic_thread_fence
#define __hybrid_atomic_thread_fence __hybrid_atomic_signal_fence
#endif /* !__hybrid_atomic_thread_fence */

#ifndef __hybrid_atomic_lockfree
#define __hybrid_atomic_lockfree(p) (__HYBRID_ATOMIC_LOCKFREE(sizeof(*(p))) == 2)
#endif /* !__hybrid_atomic_lockfree */
#endif /* __CC__ */

/* Determine the lock-free-ness of a type with size `x'
 * @return: 0: Never lock-free
 * @return: 1: Sometimes lock-free
 * @return: 2: Always lock-free */
#ifndef __HYBRID_ATOMIC_LOCKFREE
#ifndef __HYBRID_ATOMIC_LOCKFREE_MAX
#define __HYBRID_ATOMIC_LOCKFREE_MAX __SIZEOF_POINTER__
#if defined(__GCC_ATOMIC_LLONG_LOCK_FREE) && defined(__SIZEOF_LONG_LONG__)
#if __HYBRID_ATOMIC_LOCKFREE_MAX < __SIZEOF_LONG_LONG__
#undef __HYBRID_ATOMIC_LOCKFREE_MAX
#define __HYBRID_ATOMIC_LOCKFREE_MAX __SIZEOF_LONG_LONG__
#endif /* __HYBRID_ATOMIC_LOCKFREE_MAX < __SIZEOF_LONG_LONG__ */
#endif /* __GCC_ATOMIC_LLONG_LOCK_FREE && __SIZEOF_LONG_LONG__ */
#endif /* !__HYBRID_ATOMIC_LOCKFREE_MAX */
#define __HYBRID_ATOMIC_LOCKFREE(x) ((x) <= __HYBRID_ATOMIC_LOCKFREE_MAX ? 2 : 0)
#endif /* !__HYBRID_ATOMIC_LOCKFREE */

#ifndef __GCC_ATOMIC_BOOL_LOCK_FREE
#ifndef __SIZEOF_BOOL__
#define __SIZEOF_BOOL__ __SIZEOF_CHAR__
#endif /* !__SIZEOF_BOOL__ */
#define __GCC_ATOMIC_BOOL_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_BOOL__)
#endif /* !__GCC_ATOMIC_BOOL_LOCK_FREE */

#ifndef __GCC_ATOMIC_CHAR_LOCK_FREE
#define __GCC_ATOMIC_CHAR_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_CHAR__)
#endif /* !__GCC_ATOMIC_CHAR_LOCK_FREE */

#ifndef __GCC_ATOMIC_CHAR8_T_LOCK_FREE
#define __GCC_ATOMIC_CHAR8_T_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(1)
#endif /* !__GCC_ATOMIC_CHAR8_T_LOCK_FREE */

#ifndef __GCC_ATOMIC_CHAR16_T_LOCK_FREE
#define __GCC_ATOMIC_CHAR16_T_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(2)
#endif /* !__GCC_ATOMIC_CHAR16_T_LOCK_FREE */

#ifndef __GCC_ATOMIC_CHAR32_T_LOCK_FREE
#define __GCC_ATOMIC_CHAR32_T_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(4)
#endif /* !__GCC_ATOMIC_CHAR32_T_LOCK_FREE */

#ifndef __GCC_ATOMIC_WCHAR_T_LOCK_FREE
#define __GCC_ATOMIC_WCHAR_T_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_WCHAR_T__)
#endif /* !__GCC_ATOMIC_WCHAR_T_LOCK_FREE */

#ifndef __GCC_ATOMIC_SHORT_LOCK_FREE
#define __GCC_ATOMIC_SHORT_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_SHORT__)
#endif /* !__GCC_ATOMIC_SHORT_LOCK_FREE */

#ifndef __GCC_ATOMIC_INT_LOCK_FREE
#define __GCC_ATOMIC_INT_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_INT__)
#endif /* !__GCC_ATOMIC_INT_LOCK_FREE */

#ifndef __GCC_ATOMIC_LONG_LOCK_FREE
#define __GCC_ATOMIC_LONG_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_LONG__)
#endif /* !__GCC_ATOMIC_LONG_LOCK_FREE */

#ifndef __GCC_ATOMIC_LLONG_LOCK_FREE
#ifdef __SIZEOF_LONG_LONG__
#define __GCC_ATOMIC_LLONG_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_LONG_LONG__)
#endif /* __SIZEOF_LONG_LONG__ */
#endif /* !__GCC_ATOMIC_LLONG_LOCK_FREE */

#ifndef __GCC_ATOMIC_POINTER_LOCK_FREE
#define __GCC_ATOMIC_POINTER_LOCK_FREE __HYBRID_ATOMIC_LOCKFREE(__SIZEOF_POINTER__)
#endif /* !__GCC_ATOMIC_POINTER_LOCK_FREE */

#endif /* !__GUARD_HYBRID___ATOMIC_H */
