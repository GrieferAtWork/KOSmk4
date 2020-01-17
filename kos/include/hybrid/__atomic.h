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
#ifndef __GUARD_HYBRID___ATOMIC_H
#define __GUARD_HYBRID___ATOMIC_H 1

#include "../__stdinc.h"
#include "typecore.h"

#ifdef __CC__

#ifndef __cplusplus
#ifndef __COMPILER_HAVE_TYPEOF
#if 1
#define __ATOMIC_RECAST(x, y) (1 ? (y) : (x))
#else
#define __ATOMIC_RECAST(x, y) (y)
#endif
#else /* !__COMPILER_HAVE_TYPEOF */
#define __ATOMIC_RECAST(x, y) ((__typeof__(x))(y))
#endif /* __COMPILER_HAVE_TYPEOF */
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

__SYSDECL_BEGIN

#if defined(__CC__) || defined(__DEEMON__)

#ifdef __HYBRID_ATOMIC_USE_LIBATOMIC

/************************************************************************/
/* libatomic:__atomic_xxx()                                             */
/************************************************************************/
__SYSDECL_END
#include "__atomic-libatomic.h"
__SYSDECL_BEGIN
#elif (defined(__GNUC__) && __GCC_VERSION_NUM >= 40700) || defined(____INTELLISENSE_STDINC_COMMON_H)

/************************************************************************/
/* __atomic_xxx()                                                       */
/************************************************************************/
#define __hybrid_atomic_load(x, order)                             __atomic_load_n(&(x), order)
#define __hybrid_atomic_store(x, v, order)                         __atomic_store_n(&(x), v, order)
#define __hybrid_atomic_xch(x, v, order)                           __atomic_exchange_n(&(x), v, order)
#define __hybrid_atomic_cmpxch(x, oldv, newv, succ, fail)          __XBLOCK({ __typeof__(x) __oldv=(oldv); __XRETURN __atomic_compare_exchange_n(&(x),&__oldv,newv,0,succ,fail); })
#define __hybrid_atomic_cmpxch_weak(x, oldv, newv, succ, fail)     __XBLOCK({ __typeof__(x) __oldv=(oldv); __XRETURN __atomic_compare_exchange_n(&(x),&__oldv,newv,1,succ,fail); })
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail)      __XBLOCK({ __typeof__(x) __oldv=(oldv); __atomic_compare_exchange_n(&(x),&__oldv,newv,0,succ,fail); __XRETURN __oldv; })
#define __hybrid_atomic_cmpxch_val_weak(x, oldv, newv, succ, fail) __XBLOCK({ __typeof__(x) __oldv=(oldv); __atomic_compare_exchange_n(&(x),&__oldv,newv,1,succ,fail); __XRETURN __oldv; })
#define __hybrid_atomic_addfetch(x, v, order)                      __atomic_add_fetch(&(x), v, order)
#define __hybrid_atomic_subfetch(x, v, order)                      __atomic_sub_fetch(&(x), v, order)
#define __hybrid_atomic_andfetch(x, v, order)                      __atomic_and_fetch(&(x), v, order)
#define __hybrid_atomic_orfetch(x, v, order)                       __atomic_or_fetch(&(x), v, order)
#define __hybrid_atomic_xorfetch(x, v, order)                      __atomic_xor_fetch(&(x), v, order)
#define __hybrid_atomic_nandfetch(x, v, order)                     __atomic_nand_fetch(&(x), v, order)
#define __hybrid_atomic_fetchadd(x, v, order)                      __atomic_fetch_add(&(x), v, order)
#define __hybrid_atomic_fetchsub(x, v, order)                      __atomic_fetch_sub(&(x), v, order)
#define __hybrid_atomic_fetchand(x, v, order)                      __atomic_fetch_and(&(x), v, order)
#define __hybrid_atomic_fetchor(x, v, order)                       __atomic_fetch_or(&(x), v, order)
#define __hybrid_atomic_fetchxor(x, v, order)                      __atomic_fetch_xor(&(x), v, order)
#define __hybrid_atomic_fetchnand(x, v, order)                     __atomic_fetch_nand(&(x), v, order)
#define __hybrid_atomic_thread_fence(order)                        __atomic_thread_fence(order)
#define __hybrid_atomic_signal_fence(order)                        __atomic_signal_fence(order)
#define __hybrid_atomic_lockfree(x)                                __atomic_is_lock_free(sizeof(x), &(x))
#elif __has_extension(c_atomic) || __has_extension(cxx_atomic) /* clang */

/************************************************************************/
/* __c11_atomic_xxx()                                                   */
/************************************************************************/
#define __hybrid_atomic_load(x, order)                             __c11_atomic_load(&(x), order)
#define __hybrid_atomic_store(x, v, order)                         __c11_atomic_store(&(x), v, order)
#define __hybrid_atomic_xch(x, v, order)                           __c11_atomic_exchange(&(x), v, order)
#define __hybrid_atomic_cmpxch(x, oldv, newv, succ, fail)          __XBLOCK({ __typeof__(x) __oldv=(oldv); __XRETURN __c11_atomic_compare_exchange_strong(&(x),&__oldv,newv,succ,fail); })
#define __hybrid_atomic_cmpxch_weak(x, oldv, newv, succ, fail)     __XBLOCK({ __typeof__(x) __oldv=(oldv); __XRETURN __c11_atomic_compare_exchange_weak(&(x),&__oldv,newv,succ,fail); })
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail)      __XBLOCK({ __typeof__(x) __oldv=(oldv); __c11_atomic_compare_exchange_strong(&(x),&__oldv,newv,succ,fail); __XRETURN __oldv; })
#define __hybrid_atomic_cmpxch_val_weak(x, oldv, newv, succ, fail) __XBLOCK({ __typeof__(x) __oldv=(oldv); __c11_atomic_compare_exchange_weak(&(x),&__oldv,newv,succ,fail); __XRETURN __oldv; })
#define __hybrid_atomic_fetchadd(x, v, order)                      __c11_atomic_fetch_add(&(x), v, order)
#define __hybrid_atomic_fetchsub(x, v, order)                      __c11_atomic_fetch_sub(&(x), v, order)
#define __hybrid_atomic_fetchand(x, v, order)                      __c11_atomic_fetch_and(&(x), v, order)
#define __hybrid_atomic_fetchor(x, v, order)                       __c11_atomic_fetch_or(&(x), v, order)
#define __hybrid_atomic_fetchxor(x, v, order)                      __c11_atomic_fetch_xor(&(x), v, order)
#define __hybrid_atomic_thread_fence(order)                        __c11_atomic_thread_fence(order)
#define __hybrid_atomic_signal_fence(order)                        __c11_atomic_signal_fence(order)
#define __hybrid_atomic_lockfree(x)                                __atomic_is_lock_free(sizeof(x), &(x))
#else /* Modern GCC... */

#if defined(__GNUC__) || defined(__DCC_VERSION__)

/************************************************************************/
/* __sync_xxx()                                                         */
/************************************************************************/
#define __impl_hybrid_atomic_addfetch_seqcst(x, v)  __sync_add_and_fetch(&(x), v)
#define __impl_hybrid_atomic_subfetch_seqcst(x, v)  __sync_sub_and_fetch(&(x), v)
#define __impl_hybrid_atomic_orfetch_seqcst(x, v)   __sync_or_and_fetch(&(x), v)
#define __impl_hybrid_atomic_andfetch_seqcst(x, v)  __sync_and_and_fetch(&(x), v)
#define __impl_hybrid_atomic_xorfetch_seqcst(x, v)  __sync_xor_and_fetch(&(x), v)
#define __impl_hybrid_atomic_fetchadd_seqcst(x, v)  __sync_fetch_and_add(&(x), v)
#define __impl_hybrid_atomic_fetchsub_seqcst(x, v)  __sync_fetch_and_sub(&(x), v)
#define __impl_hybrid_atomic_fetchor_seqcst(x, v)   __sync_fetch_and_or(&(x), v)
#define __impl_hybrid_atomic_fetchand_seqcst(x, v)  __sync_fetch_and_and(&(x), v)
#define __impl_hybrid_atomic_fetchxor_seqcst(x, v)  __sync_fetch_and_xor(&(x), v)
#if !defined(__GNUC__) || __GCC_VERSION_NUM >= 40400
#define __impl_hybrid_atomic_fetchnand_seqcst(x, v) __sync_fetch_and_nand(&(x), v)
#define __impl_hybrid_atomic_nandfetch_seqcst(x, v) __sync_nand_and_fetch(&(x), v)
#endif /* GCC 4.4 */
#define __impl_hybrid_atomic_cmpxch_seqcst(x, oldv, newv) __sync_bool_compare_and_swap(&(x), oldv, newv)
#define __impl_hybrid_atomic_cmpxch_val_seqcst(x, oldv, newv) __sync_val_compare_and_swap(&(x), oldv, newv)
#define __hybrid_atomic_thread_fence(order) ((void)(order), __sync_synchronize())
#else
__SYSDECL_END
#ifdef __COMPILER_HAVE_GCC_ASM
#include "host.h"
#endif /* __COMPILER_HAVE_GCC_ASM */

#if defined(_MSC_VER)

/************************************************************************/
/* _InterlockedXXX()                                                    */
/************************************************************************/
#ifdef __cplusplus
#define __HYBRID_ATOMIC_DID_PUSH_MSVC_WARNINGS
#pragma warning(push)           /* Keep `4197' disabled in C because of its use in macros. */
#endif /* __cplusplus */
#pragma warning(disable : 4197) /* Casting away `volatile' */
#pragma warning(disable : 4047) /* Differing number of dereferences. */
#include "__atomic-msvc.h"
#elif defined(__COMPILER_HAVE_GCC_ASM) && (defined(__x86_64__) || defined(__i386__))

/************************************************************************/
/* __asm__("lock; cmpxchg")                                             */
/************************************************************************/
#include "__atomic-gasm.h"
#else

/************************************************************************/
/* libatomic:__atomic_xxx()                                             */
/************************************************************************/
#include "__atomic-libatomic.h"
#endif

__SYSDECL_BEGIN
#endif


#ifndef __impl_hybrid_atomic_cmpxch_seqcst
#ifdef __impl_hybrid_atomic_cmpxch_val_seqcst
#define __impl_hybrid_atomic_cmpxch_seqcst(x, oldv, newv) \
	(__impl_hybrid_atomic_cmpxch_val_seqcst(x, oldv, newv) == (oldv))
#endif /* __impl_hybrid_atomic_cmpxch_val_seqcst */
#endif /* !__impl_hybrid_atomic_cmpxch_seqcst */

#ifndef __hybrid_atomic_cmpxch
#ifdef __impl_hybrid_atomic_cmpxch_seqcst
#define __hybrid_atomic_cmpxch(x, oldv, newv, succ, fail) \
	__impl_hybrid_atomic_cmpxch_seqcst(x, oldv, newv)
#endif /* __impl_hybrid_atomic_cmpxch_seqcst */
#endif /* !__hybrid_atomic_cmpxch */

#ifndef __hybrid_atomic_cmpxch_val
#ifdef __impl_hybrid_atomic_cmpxch_val_seqcst
#ifdef __COMPILER_HAVE_TYPEOF
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail) \
	((__typeof__(__xv_res))__impl_hybrid_atomic_cmpxch_val_seqcst(x, oldv, newv))
#else /* __COMPILER_HAVE_TYPEOF */
#undef __DEFINE_WRAPPER
#ifdef __cplusplus
extern "C++" {

template<class __T, class __OV, class __NV>
#define __hybrid_atomic_cmpxch_val __hybrid_atomic_cmpxch_val
__FORCELOCAL __T __NOTHROW_NCX(__hybrid_atomic_cmpxch_val)(__T &__x, __OV __oldv, __NV __newv,
                                                           int __UNUSED(__succ), int __UNUSED(__fail)) {
	return (__T)__impl_hybrid_atomic_cmpxch_val_seqcst(__x, __oldv, __newv);
}

}
#else /* __cplusplus */
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail) \
	__ATOMIC_RECAST(x, __impl_hybrid_atomic_cmpxch_val_seqcst(x, oldv, newv))
#endif /* !__cplusplus */
#endif /* !__COMPILER_HAVE_TYPEOF */
#endif /* __impl_hybrid_atomic_cmpxch_val_seqcst */
#endif /* !__hybrid_atomic_cmpxch */

#ifndef __hybrid_atomic_cmpxch
#ifdef __hybrid_atomic_cmpxch_val
#define __hybrid_atomic_cmpxch(x, oldv, newv, succ, fail) \
	(__hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail) == (oldv))
#else /* __hybrid_atomic_cmpxch_val */
/* Need at least `__hybrid_atomic_cmpxch()' or `__hybrid_atomic_cmpxch_val()' */
#error "ERROR: No atomic support with this compiler/on this platform."
#endif /* !__hybrid_atomic_cmpxch_val */
#endif /* !__hybrid_atomic_cmpxch */
#endif /* !GCC... */



/* Define value-based atomic compare-exchange operations. */
#ifndef __hybrid_atomic_cmpxch_val
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail) \
	__XBLOCK({                                                \
		__register __typeof__(x) __xv_res;                    \
		do {                                                  \
			__COMPILER_READ_BARRIER();                        \
			__xv_res = (x); /* __ATOMIC_ACQUIRE */            \
			if (__hybrid_atomic_cmpxch(x, __xv_res,           \
			                           __xv_res == (oldv)     \
			                           ? (newv)               \
			                           : __xv_res,            \
			                           succ, fail))           \
				break;                                        \
		} __WHILE1;                                           \
		__XRETURN __xv_res;                                   \
	})
#else /* __NO_XBLOCK */
#define __DEFINE_WRAPPER(n)                                                      \
	__FORCELOCAL __UINT##n##_TYPE__                                              \
	__NOTHROW_NCX(__impl_hybrid_atomic_cmpxch_val##n)(void *__x,                 \
	                                                  __UINT##n##_TYPE__ __oldv, \
	                                                  __UINT##n##_TYPE__ __newv, \
	                                                  int __succ, int __fail) {  \
		__register __UINT##n##_TYPE__ __res;                                     \
		do {                                                                     \
			__COMPILER_READ_BARRIER();                                           \
			__res = *(__UINT##n##_TYPE__ *)__x; /* __ATOMIC_ACQUIRE */           \
			if (__hybrid_atomic_cmpxch(*(__UINT##n##_TYPE__ *)__x, __res,        \
			                           __res == __oldv                           \
			                           ? __newv                                  \
			                           : __res,                                  \
			                           __succ, __fail))                          \
				break;                                                           \
		} __WHILE1;                                                              \
		return __res;                                                            \
	}
__NAMESPACE_INT_BEGIN
__DEFINE_WRAPPER(8)
__DEFINE_WRAPPER(16)
__DEFINE_WRAPPER(32)
__DEFINE_WRAPPER(64)
__NAMESPACE_INT_END
#undef __DEFINE_WRAPPER
#ifdef __cplusplus
extern "C++" {

template<class __T, class __V>
__FORCELOCAL __T __NOTHROW_NCX(__hybrid_atomic_cmpxch_val)(__T &__x, __V __oldv, __V __newv, int __succ, int __fail) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val8((void *)&__x, (__UINT8_TYPE__)__oldv, (__UINT8_TYPE__)__newv, __succ, __fail);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val16((void *)&__x, (__UINT16_TYPE__)__oldv, (__UINT16_TYPE__)__newv, __succ, __fail);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val32((void *)&__x, (__UINT32_TYPE__)__oldv, (__UINT32_TYPE__)__newv, __succ, __fail);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val64((void *)&__x, (__UINT64_TYPE__)__oldv, (__UINT64_TYPE__)__newv, __succ, __fail);
			}
		}
	}
}

}
#else /* __cplusplus */
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail)                                                                                                                                                 \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? __NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val8((void *)&(x), __ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldv), __ATOMIC_DOWNCAST(__UINT8_TYPE__)(newv), succ, fail) :    \
	                   sizeof(x) == 2 ? __NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val16((void *)&(x), __ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldv), __ATOMIC_DOWNCAST(__UINT16_TYPE__)(newv), succ, fail) : \
	                   sizeof(x) == 4 ? __NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val32((void *)&(x), __ATOMIC_DOWNCAST(__UINT32_TYPE__)(oldv), __ATOMIC_DOWNCAST(__UINT32_TYPE__)(newv), succ, fail) : \
	                                    __NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val64((void *)&(x), __ATOMIC_DOWNCAST(__UINT64_TYPE__)(oldv), __ATOMIC_DOWNCAST(__UINT64_TYPE__)(newv), succ, fail))
#endif /* __cplusplus */
#endif /* !__NO_XBLOCK */
#endif /* !__hybrid_atomic_cmpxch_val */
#ifndef __hybrid_atomic_cmpxch_weak
#define __hybrid_atomic_cmpxch_weak(x, oldv, newv, succ, fail) \
	__hybrid_atomic_cmpxch(x, oldv, newv, succ, fail)
#endif /* !__hybrid_atomic_cmpxch_weak */
#ifndef __hybrid_atomic_cmpxch_val_weak
#define __hybrid_atomic_cmpxch_val_weak(x, oldv, newv, succ, fail) \
	__hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail)
#endif /* !__hybrid_atomic_cmpxch_val_weak */


/* Define atomic load/store operations. */

#ifndef __hybrid_atomic_load
#ifdef __impl_hybrid_atomic_fetchadd_seqcst
#define __impl_hybrid_atomic_load_seqcst(x) __impl_hybrid_atomic_fetchadd_seqcst(x, 0)
#elif defined(__impl_hybrid_atomic_fetchsub_seqcst)
#define __impl_hybrid_atomic_load_seqcst(x) __impl_hybrid_atomic_fetchsub_seqcst(x, 0)
#elif defined(__impl_hybrid_atomic_fetchor_seqcst)
#define __impl_hybrid_atomic_load_seqcst(x) __impl_hybrid_atomic_fetchor_seqcst(x, 0)
#elif defined(__impl_hybrid_atomic_cmpxch_val_seqcst)
#define __impl_hybrid_atomic_load_seqcst(x) __impl_hybrid_atomic_cmpxch_val_seqcst(x, 0, 0)
#else
#define __impl_hybrid_atomic_load_seqcst(x) __hybrid_atomic_cmpxch_val(x, 0, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __hybrid_atomic_load(x, order)                      \
	__XBLOCK({                                              \
		register __typeof__(x) __ld_res;                    \
		if ((order) >= __ATOMIC_SEQ_CST)                    \
			__ld_res = __impl_hybrid_atomic_load_seqcst(x); \
		else {                                              \
			if ((order) == __ATOMIC_ACQUIRE ||              \
			    (order) == __ATOMIC_ACQ_REL)                \
				__COMPILER_READ_BARRIER();                  \
			__ld_res = (x);                                 \
			if ((order) >= __ATOMIC_RELEASE)                \
				__COMPILER_WRITE_BARRIER();                 \
		}                                                   \
		__XRETURN __ld_res;                                 \
	})
#else /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
#define __DEFINE_WRAPPER(n)                                                                           \
	__FORCELOCAL __UINT##n##_TYPE__                                                                   \
	__NOTHROW_NCX(__impl_hybrid_atomic_load##n)(void *__x, int __order) {                             \
		register __UINT##n##_TYPE__ __res;                                                            \
		if (__order >= __ATOMIC_SEQ_CST)                                                              \
			__res = (__UINT##n##_TYPE__)__impl_hybrid_atomic_load_seqcst(*(__UINT##n##_TYPE__ *)__x); \
		else {                                                                                        \
			if (__order == __ATOMIC_ACQUIRE ||                                                        \
			    __order == __ATOMIC_ACQ_REL)                                                          \
				__COMPILER_READ_BARRIER();                                                            \
			__res = *(__UINT##n##_TYPE__ *)__x;                                                       \
			if (__order >= __ATOMIC_RELEASE)                                                          \
				__COMPILER_WRITE_BARRIER();                                                           \
		}                                                                                             \
		return __res;                                                                                 \
	}
__NAMESPACE_INT_BEGIN
__DEFINE_WRAPPER(8)
__DEFINE_WRAPPER(16)
__DEFINE_WRAPPER(32)
__DEFINE_WRAPPER(64)
__NAMESPACE_INT_END
#undef __DEFINE_WRAPPER
#ifdef __cplusplus
extern "C++" {

template<class __T>
#define __hybrid_atomic_load __hybrid_atomic_load
__FORCELOCAL __T __NOTHROW_NCX(__hybrid_atomic_load)(__T &__x, int __order) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_load8((void *)&__x, __order);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_load16((void *)&__x, __order);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_load32((void *)&__x, __order);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_load64((void *)&__x, __order);
			}
		}
	}
}

}
#else /* __cplusplus */
#define __hybrid_atomic_load(x, order)                                                                         \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? __NAMESPACE_INT_SYM __impl_hybrid_atomic_load8((void *)&(x), order) :  \
	                   sizeof(x) == 2 ? __NAMESPACE_INT_SYM __impl_hybrid_atomic_load16((void *)&(x), order) : \
	                   sizeof(x) == 4 ? __NAMESPACE_INT_SYM __impl_hybrid_atomic_load32((void *)&(x), order) : \
	                                    __NAMESPACE_INT_SYM __impl_hybrid_atomic_load64((void *)&(x), order))
#endif /* !__cplusplus */
#endif /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */
#endif /* !__hybrid_atomic_load */

#ifndef __hybrid_atomic_store
#ifdef __impl_hybrid_atomic_xch_seqcst
#define __impl_hybrid_atomic_store_seqcst(x, v) \
	__impl_hybrid_atomic_xch_seqcst(x, v)
#else /* __impl_hybrid_atomic_xch_seqcst */
#define __impl_hybrid_atomic_store_seqcst(x, v) \
	__hybrid_atomic_xch(x, v, __ATOMIC_SEQ_CST)
#endif /* !__impl_hybrid_atomic_xch_seqcst */
#ifndef __NO_XBLOCK
#define __hybrid_atomic_store(x, v, order)           \
	__XBLOCK({                                       \
		if ((order) >= __ATOMIC_SEQ_CST)             \
			__impl_hybrid_atomic_store_seqcst(x, v); \
		else {                                       \
			if ((order) == __ATOMIC_ACQUIRE ||       \
			    (order) == __ATOMIC_ACQ_REL)         \
				__COMPILER_READ_BARRIER();           \
			(x) = (v);                               \
			if ((order) >= __ATOMIC_RELEASE)         \
				__COMPILER_WRITE_BARRIER();          \
		}                                            \
		(void)0;                                     \
	})
#else /* !__NO_XBLOCK */
#define __DEFINE_WRAPPER(n)                                                                        \
	__FORCELOCAL void                                                                              \
	__NOTHROW_NCX(__impl_hybrid_atomic_store##n)(void *__x, __UINT##n##_TYPE__ __v, int __order) { \
		if (__order >= __ATOMIC_SEQ_CST)                                                           \
			__impl_hybrid_atomic_store_seqcst(*(__UINT##n##_TYPE__ *)__x, __v);                    \
		else {                                                                                     \
			if (__order == __ATOMIC_ACQUIRE ||                                                     \
			    __order == __ATOMIC_ACQ_REL)                                                       \
				__COMPILER_READ_BARRIER();                                                         \
			*(__UINT##n##_TYPE__ *)__x = __v;                                                      \
			if (__order >= __ATOMIC_RELEASE)                                                       \
				__COMPILER_WRITE_BARRIER();                                                        \
		}                                                                                          \
	}
__NAMESPACE_INT_BEGIN
__DEFINE_WRAPPER(8)
__DEFINE_WRAPPER(16)
__DEFINE_WRAPPER(32)
__DEFINE_WRAPPER(64)
__NAMESPACE_INT_END
#undef __DEFINE_WRAPPER
#ifdef __cplusplus
extern "C++" {
template<class __T, class __V>
#define __hybrid_atomic_store __hybrid_atomic_store
__FORCELOCAL void __NOTHROW_NCX(__hybrid_atomic_store)(__T &__x, __V __v, int __order) {
	__STATIC_IF(sizeof(__T) == 1) {
		__NAMESPACE_INT_SYM __impl_hybrid_atomic_store8((void *)&__x, (__UINT8_TYPE__)__v, __order);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			__NAMESPACE_INT_SYM __impl_hybrid_atomic_store16((void *)&__x, (__UINT16_TYPE__)__v, __order);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				__NAMESPACE_INT_SYM __impl_hybrid_atomic_store32((void *)&__x, (__UINT32_TYPE__)__v, __order);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				__NAMESPACE_INT_SYM __impl_hybrid_atomic_store64((void *)&__x, (__UINT64_TYPE__)__v, __order);
			}
		}
	}
}
}
#else /* __cplusplus */
#define __hybrid_atomic_store(x, v, order) \
	(sizeof(x) == 1 ? __NAMESPACE_INT_SYM __impl_hybrid_atomic_store8((void *)&(x), __ATOMIC_DOWNCAST(__UINT8_TYPE__)(v), order) : sizeof(x) == 2 ? __NAMESPACE_INT_SYM __impl_hybrid_atomic_store16((void *)&(x), __ATOMIC_DOWNCAST(__UINT16_TYPE__)(v), order) : sizeof(x) == 4 ? __NAMESPACE_INT_SYM __impl_hybrid_atomic_store32((void *)&(x), __ATOMIC_DOWNCAST(__UINT32_TYPE__)(v), order) : __NAMESPACE_INT_SYM __impl_hybrid_atomic_store64((void *)&(x), __ATOMIC_DOWNCAST(__UINT64_TYPE__)(v), order))
#endif /* !__cplusplus */
#endif /* __NO_XBLOCK */
#endif /* !__hybrid_atomic_store */


#ifndef __impl_hybrid_atomic_fetchadd_seqcst
#ifdef __impl_hybrid_atomic_fetchsub_seqcst
#define __impl_hybrid_atomic_fetchadd_seqcst(x, v) \
	__impl_hybrid_atomic_fetchsub_seqcst(x, 0 - (v))
#endif /* __impl_hybrid_atomic_fetchsub_seqcst */
#else /* !__impl_hybrid_atomic_fetchadd_seqcst */
#ifndef __impl_hybrid_atomic_fetchsub_seqcst
#define __impl_hybrid_atomic_fetchsub_seqcst(x, v) \
	__impl_hybrid_atomic_fetchadd_seqcst(x, 0 - (v))
#endif /* !__impl_hybrid_atomic_fetchsub_seqcst */
#endif /* __impl_hybrid_atomic_fetchadd_seqcst */


#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __INLINE_hybrid_atomic_fetchop_seqcst(name, opfun) /* nothing */
#define __CALL_hybrid_atomic_fetchop_seqcst(name, opfun, x, v)                          \
	__XBLOCK({                                                                          \
		__register __typeof__(x) __sc_res;                                              \
		do {                                                                            \
			__COMPILER_READ_BARRIER();                                                  \
			__sc_res = (x);                                                             \
		} while (!__hybrid_atomic_cmpxch_weak(x, __sc_res,                              \
		                                      (__typeof__(__sc_res))opfun(__sc_res, v), \
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));     \
		__XRETURN __sc_res;                                                             \
	})
#else /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
#define __DO_DECL_INLINE_hybrid_atomic_fetchop_seqcst(name, n, opfun)                           \
	__FORCELOCAL __UINT##n##_TYPE__                                                             \
	__NOTHROW_NCX(__impl_hybrid_atomic_##name##n##_seqcst)(void *__x, __UINT##n##_TYPE__ __v) { \
		__register __UINT##n##_TYPE__ __res;                                                    \
		do {                                                                                    \
			__COMPILER_READ_BARRIER();                                                          \
			__res = *(__UINT##n##_TYPE__ *)__x;                                                 \
		} while (!__hybrid_atomic_cmpxch_weak(*(__UINT##n##_TYPE__ *)__x, __res,                \
		                                      (__UINT##n##_TYPE__)opfun(__res, __v),            \
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));             \
		return __res;                                                                           \
	}
#ifndef __cplusplus
#define __INLINE_hybrid_atomic_fetchop_seqcst(name, opfun)         \
	__DO_DECL_INLINE_hybrid_atomic_fetchop_seqcst(name, 8, opfun)  \
	__DO_DECL_INLINE_hybrid_atomic_fetchop_seqcst(name, 16, opfun) \
	__DO_DECL_INLINE_hybrid_atomic_fetchop_seqcst(name, 32, opfun) \
	__DO_DECL_INLINE_hybrid_atomic_fetchop_seqcst(name, 64, opfun)
#define __CALL_hybrid_atomic_fetchop_seqcst(name, opfun, x, v) \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? __impl_hybrid_atomic_fetch##name##8_seqcst((void *)&(x), __ATOMIC_DOWNCAST(__UINT8_TYPE__)(v)) : sizeof(x) == 2 ? __impl_hybrid_atomic_fetch##name##16_seqcst((void *)&(x), __ATOMIC_DOWNCAST(__UINT16_TYPE__)(v)) : sizeof(x) == 4 ? __impl_hybrid_atomic_fetch##name##32_seqcst((void *)&(x), __ATOMIC_DOWNCAST(__UINT32_TYPE__)(v)) : __impl_hybrid_atomic_fetch##name##64_seqcst((void *)&(x), __ATOMIC_DOWNCAST(__UINT64_TYPE__)(v)))
#else /* !__cplusplus */
#define __INLINE_hybrid_atomic_fetchop_seqcst(name, opfun)                                                                               \
	__NAMESPACE_INT_BEGIN                                                                                                                \
	__DO_DECL_INLINE_hybrid_atomic_fetchop_seqcst(name, 8, opfun)                                                                        \
	__DO_DECL_INLINE_hybrid_atomic_fetchop_seqcst(name, 16, opfun)                                                                       \
	__DO_DECL_INLINE_hybrid_atomic_fetchop_seqcst(name, 32, opfun)                                                                       \
	__DO_DECL_INLINE_hybrid_atomic_fetchop_seqcst(name, 64, opfun)                                                                       \
	__NAMESPACE_INT_END extern "C++" {                                                                                                   \
		template<class __T, class __V>                                                                                                   \
		__FORCELOCAL __T __NOTHROW_NCX(__impl_hybrid_atomic_fetch##name##_seqcst)(__T & __x, __V __v) {                                  \
			__STATIC_IF(sizeof(__T) == 1) {                                                                                              \
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetch##name##8_seqcst((void *)&__x, (__UINT8_TYPE__)__v);           \
			}                                                                                                                            \
			__STATIC_ELSE(sizeof(__T) == 1) {                                                                                            \
				__STATIC_IF(sizeof(__T) == 2) {                                                                                          \
					return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetch##name##16_seqcst((void *)&__x, (__UINT16_TYPE__)__v);     \
				}                                                                                                                        \
				__STATIC_ELSE(sizeof(__T) == 2) {                                                                                        \
					__STATIC_IF(sizeof(__T) == 4) {                                                                                      \
						return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetch##name##32_seqcst((void *)&__x, (__UINT64_TYPE__)__v); \
					}                                                                                                                    \
					__STATIC_ELSE(sizeof(__T) == 4) {                                                                                    \
						return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetch##name##64_seqcst((void *)&__x, (__UINT64_TYPE__)__v); \
					}                                                                                                                    \
				}                                                                                                                        \
			}                                                                                                                            \
		}                                                                                                                                \
	}
#define __CALL_hybrid_atomic_fetchop_seqcst(name, opfun, x, v) \
	__impl_hybrid_atomic_fetch##name##_seqcst(x, v)
#endif /* __cplusplus */
#endif /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */



/* Perform logical substitution. */
#ifndef __hybrid_atomic_xch
#ifdef __impl_hybrid_atomic_xch_seqcst
#define __hybrid_atomic_xch(x, v, order) __impl_hybrid_atomic_xch_seqcst(x, v)
#else /* __impl_hybrid_atomic_xch_seqcst */
#define __hybrid_opfun_xch(x, y) (y)
__INLINE_hybrid_atomic_fetchop_seqcst(xch, __hybrid_opfun_xch)
#define __hybrid_atomic_xch(x, v, order) __CALL_hybrid_atomic_fetchop_seqcst(xch, __hybrid_opfun_xch, x, v)
#endif /* !__impl_hybrid_atomic_xch_seqcst */
#endif /* !__hybrid_atomic_xch */

#ifndef __hybrid_atomic_fetchadd
#ifdef __impl_hybrid_atomic_fetchadd_seqcst
#define __hybrid_atomic_fetchadd(x, v, order) __impl_hybrid_atomic_fetchadd_seqcst(x, v)
#else /* __impl_hybrid_atomic_fetchadd_seqcst */
#define __hybrid_opfun_add(x, y) ((x) + (y))
__INLINE_hybrid_atomic_fetchop_seqcst(fetchadd, __hybrid_opfun_add)
#define __hybrid_atomic_fetchadd(x, v, order) __CALL_hybrid_atomic_fetchop_seqcst(fetchadd, __hybrid_opfun_add, x, v)
#endif /* !__impl_hybrid_atomic_fetchadd_seqcst */
#endif /* !__hybrid_atomic_fetchadd */

#ifndef __hybrid_atomic_fetchsub
#ifdef __impl_hybrid_atomic_fetchsub_seqcst
#define __hybrid_atomic_fetchsub(x, v, order) __impl_hybrid_atomic_fetchsub_seqcst(x, v)
#else /* __impl_hybrid_atomic_fetchsub_seqcst */
#define __hybrid_opfun_sub(x, y) ((x) - (y))
__INLINE_hybrid_atomic_fetchop_seqcst(fetchsub, __hybrid_opfun_sub)
#define __hybrid_atomic_fetchsub(x, v, order) __CALL_hybrid_atomic_fetchop_seqcst(fetchsub, __hybrid_opfun_sub, x, v)
#endif /* !__impl_hybrid_atomic_fetchsub_seqcst */
#endif /* !__hybrid_atomic_fetchsub */

#ifndef __hybrid_atomic_fetchand
#ifdef __impl_hybrid_atomic_fetchand_seqcst
#define __hybrid_atomic_fetchand(x, v, order) __impl_hybrid_atomic_fetchand_seqcst(x, v)
#else /* __impl_hybrid_atomic_fetchand_seqcst */
#define __hybrid_opfun_and(x, y) ((x) & (y))
__INLINE_hybrid_atomic_fetchop_seqcst(fetchand, __hybrid_opfun_and)
#define __hybrid_atomic_fetchand(x, v, order) __CALL_hybrid_atomic_fetchop_seqcst(fetchand, __hybrid_opfun_and, x, v)
#endif /* !__impl_hybrid_atomic_fetchand_seqcst */
#endif /* !__hybrid_atomic_fetchand */

#ifndef __hybrid_atomic_fetchor
#ifdef __impl_hybrid_atomic_fetchor_seqcst
#define __hybrid_atomic_fetchor(x, v, order) __impl_hybrid_atomic_fetchor_seqcst(x, v)
#else /* __impl_hybrid_atomic_fetchor_seqcst */
#define __hybrid_opfun_or(x, y) ((x) | (y))
__INLINE_hybrid_atomic_fetchop_seqcst(fetchor, __hybrid_opfun_or)
#define __hybrid_atomic_fetchor(x, v, order) __CALL_hybrid_atomic_fetchop_seqcst(fetchor, __hybrid_opfun_or, x, v)
#endif /* !__impl_hybrid_atomic_fetchor_seqcst */
#endif /* !__hybrid_atomic_fetchor */

#ifndef __hybrid_atomic_fetchxor
#ifdef __impl_hybrid_atomic_fetchxor_seqcst
#define __hybrid_atomic_fetchxor(x, v, order) __impl_hybrid_atomic_fetchxor_seqcst(x, v)
#else /* __impl_hybrid_atomic_fetchxor_seqcst */
#define __hybrid_opfun_xor(x, y) ((x) ^ (y))
__INLINE_hybrid_atomic_fetchop_seqcst(fetchxor, __hybrid_opfun_xor)
#define __hybrid_atomic_fetchxor(x, v, order) __CALL_hybrid_atomic_fetchop_seqcst(fetchxor, __hybrid_opfun_xor, x, v)
#endif /* !__impl_hybrid_atomic_fetchxor_seqcst */
#endif /* !__hybrid_atomic_fetchxor */

#ifndef __hybrid_atomic_fetchnand
#ifdef __impl_hybrid_atomic_fetchnand_seqcst
#define __hybrid_atomic_fetchnand(x, v, order) __impl_hybrid_atomic_fetchnand_seqcst(x, v)
#else /* __impl_hybrid_atomic_fetchnand_seqcst */
#define __hybrid_opfun_nand(x, y) (~((x) & (y)))
__INLINE_hybrid_atomic_fetchop_seqcst(fetchnand, __hybrid_opfun_nand)
#define __hybrid_atomic_fetchnand(x, v, order) __CALL_hybrid_atomic_fetchop_seqcst(fetchnand, __hybrid_opfun_nand, x, v)
#endif /* !__impl_hybrid_atomic_fetchnand_seqcst */
#endif /* !__hybrid_atomic_fetchnand */

#undef __INLINE_hybrid_atomic_fetchop_seqcst

#ifndef __hybrid_atomic_addfetch
#define __hybrid_atomic_addfetch(x, v, order) (__hybrid_atomic_fetchadd(x, v, order) + (v))
#endif /* !__hybrid_atomic_addfetch */
#ifndef __hybrid_atomic_subfetch
#define __hybrid_atomic_subfetch(x, v, order) (__hybrid_atomic_fetchsub(x, v, order) - (v))
#endif /* !__hybrid_atomic_subfetch */
#ifndef __hybrid_atomic_andfetch
#define __hybrid_atomic_andfetch(x, v, order) (__hybrid_atomic_fetchand(x, v, order) & (v))
#endif /* !__hybrid_atomic_andfetch */
#ifndef __hybrid_atomic_orfetch
#define __hybrid_atomic_orfetch(x, v, order) (__hybrid_atomic_fetchor(x, v, order) | (v))
#endif /* !__hybrid_atomic_orfetch */
#ifndef __hybrid_atomic_xorfetch
#define __hybrid_atomic_xorfetch(x, v, order) (__hybrid_atomic_fetchxor(x, v, order) ^ (v))
#endif /* !__hybrid_atomic_xorfetch */
#ifndef __hybrid_atomic_nandfetch
#define __hybrid_atomic_nandfetch(x, v, order) (~(__hybrid_atomic_fetchnand(x, v, order) & (v)))
#endif /* !__hybrid_atomic_nandfetch */

#ifndef __hybrid_atomic_incfetch
#define __hybrid_atomic_incfetch(x, order) __hybrid_atomic_addfetch(x, 1, order)
#define __hybrid_atomic_fetchinc(x, order) __hybrid_atomic_fetchadd(x, 1, order)
#endif /* !__hybrid_atomic_fetchinc */

#ifndef __hybrid_atomic_decfetch
#define __hybrid_atomic_decfetch(x, order) __hybrid_atomic_subfetch(x, 1, order)
#define __hybrid_atomic_fetchdec(x, order) __hybrid_atomic_fetchsub(x, 1, order)
#endif /* !__hybrid_atomic_decfetch */

#endif /* __CC__ */

#ifndef __GCC_ATOMIC_BOOL_LOCK_FREE
#define __GCC_ATOMIC_BOOL_LOCK_FREE 1
#endif /* !__GCC_ATOMIC_BOOL_LOCK_FREE */
#ifndef __GCC_ATOMIC_CHAR_LOCK_FREE
#define __GCC_ATOMIC_CHAR_LOCK_FREE 1
#endif /* !__GCC_ATOMIC_CHAR_LOCK_FREE */
#ifndef __GCC_ATOMIC_CHAR16_T_LOCK_FREE
#define __GCC_ATOMIC_CHAR16_T_LOCK_FREE 1
#endif /* !__GCC_ATOMIC_CHAR16_T_LOCK_FREE */
#ifndef __GCC_ATOMIC_CHAR32_T_LOCK_FREE
#define __GCC_ATOMIC_CHAR32_T_LOCK_FREE 1
#endif /* !__GCC_ATOMIC_CHAR32_T_LOCK_FREE */
#ifndef __GCC_ATOMIC_WCHAR_T_LOCK_FREE
#define __GCC_ATOMIC_WCHAR_T_LOCK_FREE 1
#endif /* !__GCC_ATOMIC_WCHAR_T_LOCK_FREE */
#ifndef __GCC_ATOMIC_SHORT_LOCK_FREE
#define __GCC_ATOMIC_SHORT_LOCK_FREE 1
#endif /* !__GCC_ATOMIC_SHORT_LOCK_FREE */
#ifndef __GCC_ATOMIC_INT_LOCK_FREE
#define __GCC_ATOMIC_INT_LOCK_FREE 1
#endif /* !__GCC_ATOMIC_INT_LOCK_FREE */
#ifndef __GCC_ATOMIC_LONG_LOCK_FREE
#define __GCC_ATOMIC_LONG_LOCK_FREE 1
#endif /* !__GCC_ATOMIC_LONG_LOCK_FREE */
#ifndef __GCC_ATOMIC_LLONG_LOCK_FREE
#define __GCC_ATOMIC_LLONG_LOCK_FREE 1
#endif /* !__GCC_ATOMIC_LLONG_LOCK_FREE */
#ifndef __GCC_ATOMIC_POINTER_LOCK_FREE
#define __GCC_ATOMIC_POINTER_LOCK_FREE 1
#endif /* !__GCC_ATOMIC_POINTER_LOCK_FREE */

#ifndef __hybrid_atomic_lockfree
#ifdef __SIZEOF_POINTER__
#define __hybrid_atomic_lockfree(x) (sizeof(x) <= __SIZEOF_POINTER__)
#else /* __SIZEOF_POINTER__ */
#define __hybrid_atomic_lockfree(x) (sizeof(x) <= sizeof(void *))
#endif /* !__SIZEOF_POINTER__ */
#endif /* !__hybrid_atomic_lockfree */

#ifndef __hybrid_atomic_signal_fence
#ifdef __COMPILER_BARRIERS_ALL_IDENTICAL
#define __hybrid_atomic_signal_fence(order) ((void)(order), __COMPILER_BARRIER())
#else /* __COMPILER_BARRIERS_ALL_IDENTICAL */
#define __hybrid_atomic_signal_fence(order) \
	(__NAMESPACE_INT_SYM __impl_hybrid_atomic_signal_fence(order))
__NAMESPACE_INT_BEGIN
__FORCELOCAL void __NOTHROW_NCX(__impl_hybrid_atomic_signal_fence)(int __order) {
	/* Fallback: Emit compiler barriers to implement atomic signal fencing.
	 * HINT: If available, compiler barriers are implemented using intrinsic
	 *       signal fences, meaning that they are literally the same thing.
	 * e.g.: When hosted by msvc, stuff like `_ReadWriteBarrier()' will appear below. */
	if (__order >= __ATOMIC_ACQ_REL)
		__COMPILER_BARRIER();
	else if (__order >= __ATOMIC_RELEASE)
		__COMPILER_WRITE_BARRIER();
	else if (__order >= __ATOMIC_ACQUIRE) {
		__COMPILER_READ_BARRIER();
	}
}
#endif /* !__COMPILER_BARRIERS_ALL_IDENTICAL */
__NAMESPACE_INT_END
#endif /* !__hybrid_atomic_signal_fence */

#ifndef __hybrid_atomic_thread_fence
/* Shouldn't get here, but may be right on ~some~ platforms? */
#define __hybrid_atomic_thread_fence(order) \
	__hybrid_atomic_signal_fence(order)
#endif /* !__hybrid_atomic_thread_fence */

__SYSDECL_END

#ifdef __HYBRID_ATOMIC_DID_PUSH_MSVC_WARNINGS
#undef __HYBRID_ATOMIC_DID_PUSH_MSVC_WARNINGS
#pragma warning(pop)
#endif /* __HYBRID_ATOMIC_DID_PUSH_MSVC_WARNINGS */

#endif /* __CC__ */

#endif /* !__GUARD_HYBRID___ATOMIC_H */
