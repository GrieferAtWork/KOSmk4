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
#ifndef _I386_KOS_ASM_INTRIN_LOCK_H
#define _I386_KOS_ASM_INTRIN_LOCK_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __x86_64__
#define __INTRIN_LOCK_IF_X86_64(...) __VA_ARGS__
#else /* __x86_64__ */
#define __INTRIN_LOCK_IF_X86_64(...) /* nothing */
#endif /* !__x86_64__ */


/* NOTE: The  weird types (signed?!?) are used because this header isn't actually meant to be used.
 *       The reason it exists is so we can implement msvc's <intrin.h> header more closely matching
 *       the original. */
#define __DEFINE_UNARY_LOCK_OPERATION(__lock_name, __hybrid_atomic_fetchname) \
	__FORCELOCAL __INT8_TYPE__ (__lock_name##b)(__INT8_TYPE__ volatile *__paddr) {       \
		return __hybrid_atomic_fetchname(*(__INT8_TYPE__ *)__paddr, __ATOMIC_SEQ_CST);   \
	}                                                                                    \
	__FORCELOCAL __INT16_TYPE__ (__lock_name##w)(__INT16_TYPE__ volatile *__paddr) {     \
		return __hybrid_atomic_fetchname(*(__INT16_TYPE__ *)__paddr, __ATOMIC_SEQ_CST);  \
	}                                                                                    \
	__FORCELOCAL __LONG32_TYPE__ (__lock_name##l)(__LONG32_TYPE__ volatile *__paddr) {   \
		return __hybrid_atomic_fetchname(*(__LONG32_TYPE__ *)__paddr, __ATOMIC_SEQ_CST); \
	}                                                                                    \
	__INTRIN_LOCK_IF_X86_64(                                                             \
	__FORCELOCAL __INT64_TYPE__ (__lock_name##q)(__INT64_TYPE__ volatile *__paddr) {     \
		return __hybrid_atomic_fetchname(*(__INT64_TYPE__ *)__paddr, __ATOMIC_SEQ_CST);  \
	})

#define __DEFINE_BINARY_LOCK_OPERATION(__lock_name, __hybrid_atomic_fetchname) \
	__FORCELOCAL __INT8_TYPE__ (__lock_name##b)(__INT8_TYPE__ volatile *__paddr, __INT8_TYPE__ __val) {       \
		return __hybrid_atomic_fetchname(*(__INT8_TYPE__ *)__paddr, __val, __ATOMIC_SEQ_CST);                 \
	}                                                                                                         \
	__FORCELOCAL __INT16_TYPE__ (__lock_name##w)(__INT16_TYPE__ volatile *__paddr, __INT16_TYPE__ __val) {    \
		return __hybrid_atomic_fetchname(*(__INT16_TYPE__ *)__paddr, __val, __ATOMIC_SEQ_CST);                \
	}                                                                                                         \
	__FORCELOCAL __LONG32_TYPE__ (__lock_name##l)(__LONG32_TYPE__ volatile *__paddr, __LONG32_TYPE__ __val) { \
		return __hybrid_atomic_fetchname(*(__LONG32_TYPE__ *)__paddr, __val, __ATOMIC_SEQ_CST);               \
	}                                                                                                         \
	__INTRIN_LOCK_IF_X86_64(                                                                                  \
	__FORCELOCAL __INT64_TYPE__ (__lock_name##q)(__INT64_TYPE__ volatile *__paddr, __INT64_TYPE__ __val) {    \
		return __hybrid_atomic_fetchname(*(__INT64_TYPE__ *)__paddr, __val, __ATOMIC_SEQ_CST);                \
	})

__DEFINE_UNARY_LOCK_OPERATION(__lock_inc_result, __hybrid_atomic_incfetch)
__DEFINE_UNARY_LOCK_OPERATION(__lock_dec_result, __hybrid_atomic_decfetch)
__DEFINE_BINARY_LOCK_OPERATION(__lock_add, __hybrid_atomic_fetchadd)
__DEFINE_BINARY_LOCK_OPERATION(__lock_add_result, __hybrid_atomic_addfetch)
__DEFINE_BINARY_LOCK_OPERATION(__lock_sub, __hybrid_atomic_fetchsub)
__DEFINE_BINARY_LOCK_OPERATION(__lock_and, __hybrid_atomic_fetchand)
__DEFINE_BINARY_LOCK_OPERATION(__lock_or, __hybrid_atomic_fetchor)
__DEFINE_BINARY_LOCK_OPERATION(__lock_xor, __hybrid_atomic_fetchxor)
__DEFINE_BINARY_LOCK_OPERATION(__lock_nand, __hybrid_atomic_fetchnand)
__DEFINE_BINARY_LOCK_OPERATION(__lock_xchg, __hybrid_atomic_xch)

__FORCELOCAL void *__lock_addp(void *volatile * __paddr, void *__val) {
	return (void *)__hybrid_atomic_fetchadd(*(__UINTPTR_TYPE__ volatile *)__paddr, (__UINTPTR_TYPE__)__val, __ATOMIC_SEQ_CST);
}

__FORCELOCAL __INT8_TYPE__ __lock_cmpxchgb(__INT8_TYPE__ volatile * __paddr, __INT8_TYPE__ __oldval, __INT8_TYPE__ __newval) {
	return __hybrid_atomic_cmpxch_val(*(__INT8_TYPE__ *)__paddr, __oldval, __newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}
__FORCELOCAL __INT16_TYPE__ __lock_cmpxchgw(__INT16_TYPE__ volatile * __paddr, __INT16_TYPE__ __oldval, __INT16_TYPE__ __newval) {
	return __hybrid_atomic_cmpxch_val(*(__INT16_TYPE__ *)__paddr, __oldval, __newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}
__FORCELOCAL __LONG32_TYPE__ __lock_cmpxchgl(__LONG32_TYPE__ volatile * __paddr, __LONG32_TYPE__ __oldval, __LONG32_TYPE__ __newval) {
	return __hybrid_atomic_cmpxch_val(*(__LONG32_TYPE__ *)__paddr, __oldval, __newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}
__FORCELOCAL void *__lock_cmpxchgp(void *volatile * __paddr, void *__oldval, void *__newval) {
	return __hybrid_atomic_cmpxch_val(*(void **)__paddr, __oldval, __newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}
#if defined(__x86_64__) || 1 /* MSVC _always_ defines `_InterlockedCompareExchange64()' (THIS IS NOT PORTABLE AS FAR AS KOS IS CONCERNED!) */
__FORCELOCAL __INT64_TYPE__ __lock_cmpxchgq(__INT64_TYPE__ volatile * __paddr, __INT64_TYPE__ __oldval, __INT64_TYPE__ __newval) {
	return __hybrid_atomic_cmpxch_val(*(__INT64_TYPE__ *)__paddr, __oldval, __newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}
#endif /* __x86_64__ || 1 */

#undef __DEFINE_BINARY_LOCK_OPERATION
#undef __DEFINE_UNARY_LOCK_OPERATION
#undef __INTRIN_LOCK_IF_X86_64

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_ASM_INTRIN_LOCK_H */
