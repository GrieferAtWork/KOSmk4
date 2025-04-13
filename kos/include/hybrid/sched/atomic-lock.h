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
#ifndef __GUARD_HYBRID_SCHED_ATOMIC_LOCK_H
#define __GUARD_HYBRID_SCHED_ATOMIC_LOCK_H 1

#include "../../__stdinc.h"
#include "../__assert.h"
#include "../__atomic.h"
#include "../typecore.h"
#include "__preemption.h"
#ifndef __INTELLISENSE__
#include "__yield.h"
#endif /* !__INTELLISENSE__ */

#ifdef __KOS_SYSTEM_HEADERS__
#include <kos/anno.h>
#endif /* __KOS_SYSTEM_HEADERS__ */

#ifndef __THROWS
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __THROWS(...)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __THROWS(e...)
#else /* ... */
#define __THROWS(e)
#endif /* !... */
#endif /* !__THROWS */

#ifndef __NOPREEMPT
#define __NOPREEMPT /* Annotation for functions that may only be called with preemption disabled. */
#endif /* !__NOPREEMPT */

#define __SIZEOF_ATOMIC_LOCK __SIZEOF_INT__

#if defined(__CC__) || defined(__DEEMON__)
__DECL_BEGIN

struct atomic_lock {
	unsigned int a_lock; /* Lock word. (non-zero if held) */
};

#define ATOMIC_LOCK_INIT                 { 0 }
#define ATOMIC_LOCK_INIT_ACQUIRED        { 1 }
#define atomic_lock_init(self)           (void)((self)->a_lock = 0)
#define atomic_lock_init_acquired(self)  (void)((self)->a_lock = 1)
#define atomic_lock_cinit(self)          __hybrid_assert((self)->a_lock == 0)
#define atomic_lock_cinit_acquired(self) (void)((self)->a_lock = 1)

#define atomic_lock_acquired(self)   (__hybrid_atomic_load(&(self)->a_lock, __ATOMIC_ACQUIRE) != 0)
#define atomic_lock_available(self)  (__hybrid_atomic_load(&(self)->a_lock, __ATOMIC_ACQUIRE) == 0)
#define atomic_lock_tryacquire(self) __likely(__hybrid_atomic_xch(&(self)->a_lock, 1, __ATOMIC_ACQUIRE) == 0)
#if defined(NDEBUG) || defined(NDEBUG_SYNC)
#define atomic_lock_release(self) _atomic_lock_release_NDEBUG(self)
#else /* NDEBUG || NDEBUG_SYNC */
#define atomic_lock_release(self) \
	(__hybrid_assert(atomic_lock_acquired(self)), _atomic_lock_release_NDEBUG(self))
#endif /* !NDEBUG || !NDEBUG_SYNC */
#define _atomic_lock_release_NDEBUG(self) \
	__hybrid_atomic_store(&(self)->a_lock, 0, __ATOMIC_RELEASE)


/* Acquire an exclusive lock. */
__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void __NOTHROW(atomic_lock_acquire_nopr)(struct atomic_lock *__restrict __self);
__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void __NOTHROW(atomic_lock_waitfor_nopr)(struct atomic_lock *__restrict __self);
#ifdef __HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD
/* No need to have duplicate code -- if `__hybrid_preemption_tryyield_nopr()'
 * is  the same as `__hybrid_yield()', the `*_nopr' variant behaves just like
 * the normal variant! */
#define atomic_lock_acquire(self) atomic_lock_acquire_nopr(self)
#define atomic_lock_waitfor(self) atomic_lock_waitfor_nopr(self)
#else /* __HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD */
__LOCAL __ATTR_NONNULL((1)) void (atomic_lock_acquire)(struct atomic_lock *__restrict __self) __THROWS(E_WOULDBLOCK_PREEMPTED);
__LOCAL __ATTR_NONNULL((1)) void (atomic_lock_waitfor)(struct atomic_lock *__restrict __self) __THROWS(E_WOULDBLOCK_PREEMPTED);
#endif /* !__HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD */

#define atomic_lock_release_nopr atomic_lock_release
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW(atomic_lock_acquire_nx)(struct atomic_lock *__restrict __self);
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW(atomic_lock_waitfor_nx)(struct atomic_lock *__restrict __self);
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

/* Acquire/release a given atomic_lock as an smp-lock
 * @param: __hybrid_preemption_flag_t *p_flag: preemption control flag. */
#define atomic_lock_acquire_smp_r(self, p_flag) __hybrid_preemption_acquire_smp_r(atomic_lock_tryacquire(self), p_flag)
#define atomic_lock_release_smp_r(self, p_flag) __hybrid_preemption_release_smp_r(atomic_lock_release(self), p_flag)
#define atomic_lock_acquire_smp_b(self)         __hybrid_preemption_acquire_smp_b(atomic_lock_tryacquire(self))
#define atomic_lock_release_smp_b(self)         __hybrid_preemption_release_smp_b(atomic_lock_release(self))
#define atomic_lock_acquire_smp(self)           __hybrid_preemption_acquire_smp(atomic_lock_tryacquire(self))
#define atomic_lock_release_smp(self)           __hybrid_preemption_release_smp(atomic_lock_release(self))


#ifndef __INTELLISENSE__
#ifndef __HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD
__LOCAL __ATTR_NONNULL((1)) void
(atomic_lock_acquire)(struct atomic_lock *__restrict __self)
		__THROWS(E_WOULDBLOCK_PREEMPTED) {
	while (!atomic_lock_tryacquire(__self))
		__hybrid_yield();
	__COMPILER_READ_BARRIER();
}
__LOCAL __ATTR_NONNULL((1)) void
(atomic_lock_waitfor)(struct atomic_lock *__restrict __self)
		__THROWS(E_WOULDBLOCK_PREEMPTED) {
	while (!atomic_lock_available(__self))
		__hybrid_yield();
	__COMPILER_READ_BARRIER();
}
#endif /* !__HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD */

__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void
__NOTHROW(atomic_lock_acquire_nopr)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_tryacquire(__self))
		__hybrid_preemption_tryyield_nopr();
	__COMPILER_READ_BARRIER();
}
__LOCAL __NOPREEMPT __ATTR_NONNULL((1)) void
__NOTHROW(atomic_lock_waitfor_nopr)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_available(__self))
		__hybrid_preemption_tryyield_nopr();
	__COMPILER_READ_BARRIER();
}

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
#ifndef __NO_builtin_expect
#define atomic_lock_acquire_nx(self) __builtin_expect(atomic_lock_acquire_nx(self), 1)
#define atomic_lock_waitfor_nx(self) __builtin_expect(atomic_lock_waitfor_nx(self), 1)
#endif /* !__NO_builtin_expect */
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW(atomic_lock_acquire_nx)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_tryacquire(__self)) {
		if __unlikely(!__hybrid_yield_nx())
			return 0;
	}
	__COMPILER_READ_BARRIER();
	return 1;
}
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW(atomic_lock_waitfor_nx)(struct atomic_lock *__restrict __self) {
	while (!atomic_lock_available(__self)) {
		if __unlikely(!__hybrid_yield_nx())
			return 0;
	}
	__COMPILER_READ_BARRIER();
	return 1;
}
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
#endif /* !__INTELLISENSE__ */

/*[[[deemon
for (local S, N: {
	(1, 8),
	(2, 16),
	(4, 32),
	(8, 64),
	(16, 128),
}) {
	local T = f"__UINT{N}_TYPE__";
	if (N >= 64)
		print("#ifdef ", T);
	print("#if __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= ", S);
	print("#define __hybrid_atomic_load", N, "_with_atomic_lock(p, order, self) __hybrid_atomic_load", N, "(p, order)");
	print("#else /" "* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= ", S, " *" "/");
	print("#define __hybrid_atomic_load", N, "_with_atomic_lock __hybrid_atomic_load", N, "_with_atomic_lock");
	print("__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) ", T);
	print("__NOTHROW(__hybrid_atomic_load", N, "_with_atomic_lock)(", T, " const *__restrict __p, int __order,");
	print("                                                  struct atomic_lock *__restrict __self) {");
	print("	", T, " __result;");
	print("	atomic_lock_acquire(__self);");
	print("	__result = __hybrid_atomic_load", N, "(__p, __order);");
	print("	atomic_lock_release(__self);");
	print("	return __result;");
	print("}");
	print("#endif /" "* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC < ", S, " *" "/");
	if (N >= 64)
		print("#endif /" "* ", T, " *" "/");
}
]]]*/
#if __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= 1
#define __hybrid_atomic_load8_with_atomic_lock(p, order, self) __hybrid_atomic_load8(p, order)
#else /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= 1 */
#define __hybrid_atomic_load8_with_atomic_lock __hybrid_atomic_load8_with_atomic_lock
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __UINT8_TYPE__
__NOTHROW(__hybrid_atomic_load8_with_atomic_lock)(__UINT8_TYPE__ const *__restrict __p, int __order,
                                                  struct atomic_lock *__restrict __self) {
	__UINT8_TYPE__ __result;
	atomic_lock_acquire(__self);
	__result = __hybrid_atomic_load8(__p, __order);
	atomic_lock_release(__self);
	return __result;
}
#endif /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC < 1 */
#if __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= 2
#define __hybrid_atomic_load16_with_atomic_lock(p, order, self) __hybrid_atomic_load16(p, order)
#else /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= 2 */
#define __hybrid_atomic_load16_with_atomic_lock __hybrid_atomic_load16_with_atomic_lock
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __UINT16_TYPE__
__NOTHROW(__hybrid_atomic_load16_with_atomic_lock)(__UINT16_TYPE__ const *__restrict __p, int __order,
                                                  struct atomic_lock *__restrict __self) {
	__UINT16_TYPE__ __result;
	atomic_lock_acquire(__self);
	__result = __hybrid_atomic_load16(__p, __order);
	atomic_lock_release(__self);
	return __result;
}
#endif /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC < 2 */
#if __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= 4
#define __hybrid_atomic_load32_with_atomic_lock(p, order, self) __hybrid_atomic_load32(p, order)
#else /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= 4 */
#define __hybrid_atomic_load32_with_atomic_lock __hybrid_atomic_load32_with_atomic_lock
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __UINT32_TYPE__
__NOTHROW(__hybrid_atomic_load32_with_atomic_lock)(__UINT32_TYPE__ const *__restrict __p, int __order,
                                                  struct atomic_lock *__restrict __self) {
	__UINT32_TYPE__ __result;
	atomic_lock_acquire(__self);
	__result = __hybrid_atomic_load32(__p, __order);
	atomic_lock_release(__self);
	return __result;
}
#endif /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC < 4 */
#ifdef __UINT64_TYPE__
#if __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= 8
#define __hybrid_atomic_load64_with_atomic_lock(p, order, self) __hybrid_atomic_load64(p, order)
#else /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= 8 */
#define __hybrid_atomic_load64_with_atomic_lock __hybrid_atomic_load64_with_atomic_lock
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __UINT64_TYPE__
__NOTHROW(__hybrid_atomic_load64_with_atomic_lock)(__UINT64_TYPE__ const *__restrict __p, int __order,
                                                  struct atomic_lock *__restrict __self) {
	__UINT64_TYPE__ __result;
	atomic_lock_acquire(__self);
	__result = __hybrid_atomic_load64(__p, __order);
	atomic_lock_release(__self);
	return __result;
}
#endif /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC < 8 */
#endif /* __UINT64_TYPE__ */
#ifdef __UINT128_TYPE__
#if __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= 16
#define __hybrid_atomic_load128_with_atomic_lock(p, order, self) __hybrid_atomic_load128(p, order)
#else /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= 16 */
#define __hybrid_atomic_load128_with_atomic_lock __hybrid_atomic_load128_with_atomic_lock
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __UINT128_TYPE__
__NOTHROW(__hybrid_atomic_load128_with_atomic_lock)(__UINT128_TYPE__ const *__restrict __p, int __order,
                                                  struct atomic_lock *__restrict __self) {
	__UINT128_TYPE__ __result;
	atomic_lock_acquire(__self);
	__result = __hybrid_atomic_load128(__p, __order);
	atomic_lock_release(__self);
	return __result;
}
#endif /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC < 16 */
#endif /* __UINT128_TYPE__ */
/*[[[end]]]*/

/* Helper for doing  atomic reads of  aligned works, either  through
 * use of CPU-intrinsic atomics, or (if regular writes to such words
 * are  not atomic on  the host CPU, acquire  the mentioned lock and
 * perform a normal reading while said lock is being held. */
#if __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= (defined(__UINT128_TYPE__) ? 16 : (defined(__UINT64_TYPE__) ? 8 : 4))
#define __hybrid_atomic_load_with_atomic_lock(p, order, lock) __hybrid_atomic_load(p, order)
#else /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC >= ... */
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_load_with_atomic_lock __hybrid_atomic_load_with_atomic_lock
template<class __T> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
	|| sizeof(__T) == 1
	|| sizeof(__T) == 2
	|| sizeof(__T) == 4
#ifdef __hybrid_atomic_load64_with_atomic_lock
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_load64_with_atomic_lock */
#ifdef __hybrid_atomic_load128_with_atomic_lock
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_load128_with_atomic_lock */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_load_with_atomic_lock)(__T const *__p, int __order, struct atomic_lock *__restrict __self) {
	(void)__order;
	(void)__self;
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_load8_with_atomic_lock((__UINT8_TYPE__ const *)__p, __order, __self); }
	__STATIC_ELSE(sizeof(__T) == 1) {
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_load16_with_atomic_lock((__UINT16_TYPE__ const *)__p, __order, __self); }
	__STATIC_ELSE(sizeof(__T) == 2) {
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_load32_with_atomic_lock((__UINT32_TYPE__ const *)__p, __order, __self); }
	__STATIC_ELSE(sizeof(__T) == 4) {
#ifdef __hybrid_atomic_load64_with_atomic_lock
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_load64_with_atomic_lock((__UINT64_TYPE__ const *)__p, __order, __self); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_load64_with_atomic_lock */
	{
#ifdef __hybrid_atomic_load128_with_atomic_lock
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_load128_with_atomic_lock((__UINT128_TYPE__ const *)__p, __order, __self); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_load128_with_atomic_lock */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifndef __HYBRID_ATOMIC_RECAST
#ifdef __COMPILER_HAVE_TYPEOF
#define __HYBRID_ATOMIC_RECAST(p, y) ((__typeof__(*(p)))(y))
#elif 1
#define __HYBRID_ATOMIC_RECAST(p, y) (1 ? (y) : *(p))
#else /* ... */
#define __HYBRID_ATOMIC_RECAST(p, y) (y)
#endif /* !... */
#endif /* !__HYBRID_ATOMIC_RECAST */
#ifdef __hybrid_atomic_load128_with_atomic_lock
#ifdef __NO_builtin_choose_expr
#define __hybrid_atomic_load_with_atomic_lock(p, order, self) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) <= 1 ? __hybrid_atomic_load8_with_atomic_lock((__UINT8_TYPE__ const *)(p), order, self) : \
	                          sizeof(*(p)) <= 2 ? __hybrid_atomic_load16_with_atomic_lock((__UINT16_TYPE__ const *)(p), order, self) : \
	                          sizeof(*(p)) <= 4 ? __hybrid_atomic_load32_with_atomic_lock((__UINT32_TYPE__ const *)(p), order, self) : \
	                          sizeof(*(p)) <= 8 ? __hybrid_atomic_load64_with_atomic_lock((__UINT64_TYPE__ const *)(p), order, self) : \
	                                              __hybrid_atomic_load128_with_atomic_lock((__UINT128_TYPE__ const *)(p), order, self))
#else /* __NO_builtin_choose_expr */
#define __hybrid_atomic_load_with_atomic_lock(p, order, self) \
	__HYBRID_ATOMIC_RECAST(p, __builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_atomic_load8_with_atomic_lock((__UINT8_TYPE__ const *)(p), order, self), \
	                          __builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_atomic_load16_with_atomic_lock((__UINT16_TYPE__ const *)(p), order, self), \
	                          __builtin_choose_expr(sizeof(*(p)) <= 4, __hybrid_atomic_load32_with_atomic_lock((__UINT32_TYPE__ const *)(p), order, self), \
	                          __builtin_choose_expr(sizeof(*(p)) <= 8, __hybrid_atomic_load64_with_atomic_lock((__UINT64_TYPE__ const *)(p), order, self), \
	                                                                   __hybrid_atomic_load128_with_atomic_lock((__UINT128_TYPE__ const *)(p), order, self))))))
#endif /* !__NO_builtin_choose_expr */
#elif defined(__hybrid_atomic_load64_with_atomic_lock)
#ifdef __NO_builtin_choose_expr
#define __hybrid_atomic_load_with_atomic_lock(p, order, self) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) <= 1 ? __hybrid_atomic_load8_with_atomic_lock((__UINT8_TYPE__ const *)(p), order, self) : \
	                          sizeof(*(p)) <= 2 ? __hybrid_atomic_load16_with_atomic_lock((__UINT16_TYPE__ const *)(p), order, self) : \
	                          sizeof(*(p)) <= 4 ? __hybrid_atomic_load32_with_atomic_lock((__UINT32_TYPE__ const *)(p), order, self) : \
	                                              __hybrid_atomic_load64_with_atomic_lock((__UINT64_TYPE__ const *)(p), order, self))
#else /* __NO_builtin_choose_expr */
#define __hybrid_atomic_load_with_atomic_lock(p, order, self) \
	__HYBRID_ATOMIC_RECAST(p, __builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_atomic_load8_with_atomic_lock((__UINT8_TYPE__ const *)(p), order, self), \
	                          __builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_atomic_load16_with_atomic_lock((__UINT16_TYPE__ const *)(p), order, self), \
	                          __builtin_choose_expr(sizeof(*(p)) <= 4, __hybrid_atomic_load32_with_atomic_lock((__UINT32_TYPE__ const *)(p), order, self), \
	                                                                   __hybrid_atomic_load64_with_atomic_lock((__UINT64_TYPE__ const *)(p), order, self)))))
#endif /* !__NO_builtin_choose_expr */
#elif defined(__hybrid_atomic_load32_with_atomic_lock)
#ifdef __NO_builtin_choose_expr
#define __hybrid_atomic_load_with_atomic_lock(p, order, self) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) <= 1 ? __hybrid_atomic_load8_with_atomic_lock((__UINT8_TYPE__ const *)(p), order, self) : \
	                          sizeof(*(p)) <= 2 ? __hybrid_atomic_load16_with_atomic_lock((__UINT16_TYPE__ const *)(p), order, self) : \
	                                              __hybrid_atomic_load32_with_atomic_lock((__UINT32_TYPE__ const *)(p), order, self))
#else /* __NO_builtin_choose_expr */
#define __hybrid_atomic_load_with_atomic_lock(p, order, self) \
	__HYBRID_ATOMIC_RECAST(p, __builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_atomic_load8_with_atomic_lock((__UINT8_TYPE__ const *)(p), order, self), \
	                          __builtin_choose_expr(sizeof(*(p)) <= 2, __hybrid_atomic_load16_with_atomic_lock((__UINT16_TYPE__ const *)(p), order, self), \
	                                                                   __hybrid_atomic_load32_with_atomic_lock((__UINT32_TYPE__ const *)(p), order, self))))
#endif /* !__NO_builtin_choose_expr */
#elif defined(__hybrid_atomic_load16_with_atomic_lock)
#ifdef __NO_builtin_choose_expr
#define __hybrid_atomic_load_with_atomic_lock(p, order, self) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) <= 1 ? __hybrid_atomic_load8_with_atomic_lock((__UINT8_TYPE__ const *)(p), order, self) : \
	                                              __hybrid_atomic_load16_with_atomic_lock((__UINT16_TYPE__ const *)(p), order, self))
#else /* __NO_builtin_choose_expr */
#define __hybrid_atomic_load_with_atomic_lock(p, order, self) \
	__HYBRID_ATOMIC_RECAST(p, __builtin_choose_expr(sizeof(*(p)) <= 1, __hybrid_atomic_load8_with_atomic_lock((__UINT8_TYPE__ const *)(p), order, self), \
	                                                                   __hybrid_atomic_load16_with_atomic_lock((__UINT16_TYPE__ const *)(p), order, self)))
#endif /* !__NO_builtin_choose_expr */
#else /* ... */
#define __hybrid_atomic_load_with_atomic_lock(p, order, self) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_load8_with_atomic_lock((__UINT8_TYPE__ const *)(p), order, self))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __ARCH_HAVE_ALIGNED_WRITES_ARE_ATOMIC < ... */

__DECL_END
#endif /* __CC__ */


#endif /* !__GUARD_HYBRID_SCHED_ATOMIC_LOCK_H */
