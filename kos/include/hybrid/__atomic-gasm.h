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
#ifndef __GUARD_HYBRID___ATOMIC_GASM_H
#define __GUARD_HYBRID___ATOMIC_GASM_H 1

#include "../__stdinc.h"
#include "host.h"
#include "typecore.h"

#ifndef __GUARD_HYBRID___ATOMIC_H
#error "Never include this file directly. - Always include `<hybrid/__atomic.h>' instead"
#endif /* !__GUARD_HYBRID___ATOMIC_H */

#ifndef __COMPILER_HAVE_GCC_ASM
#error "GCC Inline assembly is not supported"
#endif /* !__COMPILER_HAVE_GCC_ASM */

/* Atomic base implementation using GCC inline assembly. */

__DECL_BEGIN

#if defined(__x86_64__)
#define __impl_hybrid_atomic_cmpxch_val_seqcst(x, oldv, newv)  \
	__XBLOCK({                                                 \
		register __typeof__(x) __ix_res;                       \
		if __untraced(sizeof(__ix_res) == 1) {                 \
			__asm__ __volatile__("lock; cmpxchgb %2, %0\n"     \
			                     : "+g" (x), "=a" (__ix_res)   \
			                     : "r" (newv), "1" (oldv)      \
			                     : "memory");                  \
		} else if __untraced(sizeof(__ix_res) == 2) {          \
			__asm__ __volatile__("lock; cmpxchgw %2, %0\n"     \
			                     : "+g" (x), "=a" (__ix_res)   \
			                     : "r" (newv), "1" (oldv)      \
			                     : "memory");                  \
		} else if __untraced(sizeof(__ix_res) == 4) {          \
			__asm__ __volatile__("lock; cmpxchgl %2, %0\n"     \
			                     : "+g" (x), "=a" (__ix_res)   \
			                     : "r" (newv), "1" (oldv)      \
			                     : "memory");                  \
		} else {                                               \
			__asm__ __volatile__("lock; cmpxchgq %2, %0\n"     \
			                     : "+g" (x), "=a" (__ix_res)   \
			                     : "r" (newv), "1" (oldv)      \
			                     : "memory");                  \
		}                                                      \
		__XRETURN __ix_res;                                    \
	})
#elif defined(__i386__)
#define __impl_hybrid_atomic_cmpxch_val_seqcst(x, oldv, newv)                             \
	__XBLOCK({                                                                            \
		register __typeof__(x) __ix_res;                                                  \
		if __untraced(sizeof(__ix_res) == 1) {                                            \
			__asm__ __volatile__("lock; cmpxchgb %2, %0\n"                                \
			                     : "+g" (x), "=a" (__ix_res)                              \
			                     : "r" (newv), "1" (oldv)                                 \
			                     : "memory");                                             \
		} else if __untraced(sizeof(__ix_res) == 2) {                                     \
			__asm__ __volatile__("lock; cmpxchgw %2, %0\n"                                \
			                     : "+g" (x), "=a" (__ix_res)                              \
			                     : "r" (newv), "1" (oldv)                                 \
			                     : "memory");                                             \
		} else if __untraced(sizeof(__ix_res) == 4) {                                     \
			__asm__ __volatile__("lock; cmpxchgl %2, %0\n"                                \
			                     : "+g" (x), "=a" (__ix_res)                              \
			                     : "r" (newv), "1" (oldv)                                 \
			                     : "memory");                                             \
		} else {                                                                          \
			__asm__ __volatile__("lock; cmpxchg8b %0\n"                                   \
			                     : "+m" (x), "=A" (__ix_res)                              \
			                     : "A" (oldv)                                             \
			                     , "c" ((__UINT32_TYPE__)((__UINT64_TYPE__)(newv) >> 32)) \
			                     , "b" ((__UINT32_TYPE__)(__UINT64_TYPE__)(newv))         \
			                     : "memory");                                             \
		}                                                                                 \
		__XRETURN __ix_res;                                                               \
	})
#else
#error "Unsupported Architecture"
#endif

__DECL_END

#endif /* !__GUARD_HYBRID___ATOMIC_MSVC_H */
