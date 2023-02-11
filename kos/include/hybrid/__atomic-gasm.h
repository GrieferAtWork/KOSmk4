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

#if defined(__x86_64__) || defined(__i386__)
#define __hybrid_atomic_cmpxch_val8(x, oldval, newval, order) \
	__hybrid_atomic_cmpxch_val8_seq_cst(x, oldval, newval)
#define __hybrid_atomic_cmpxch_val8_seq_cst(x, oldval, newval) \
	__XBLOCK({                                                 \
		register __UINT8_TYPE__ __hacx8_res;                   \
		__asm__ __volatile__("lock; cmpxchgb %2, %0\n"         \
		                     : "+m" (*(x)), "=a" (__hacx8_res) \
		                     : "r" (newval), "1" (oldval)      \
		                     : "memory", "cc");                \
		__XRETURN __hacx8_res;                                 \
	})
#define __hybrid_atomic_cmpxch_val16(x, oldval, newval, order) \
	__hybrid_atomic_cmpxch_val16_seq_cst(x, oldval, newval)
#define __hybrid_atomic_cmpxch_val16_seq_cst(x, oldval, newval) \
	__XBLOCK({                                                  \
		register __UINT16_TYPE__ __hacx16_res;                  \
		__asm__ __volatile__("lock; cmpxchgw %2, %0\n"          \
		                     : "+m" (*(x)), "=a" (__hacx16_res) \
		                     : "r" (newval), "1" (oldval)       \
		                     : "memory", "cc");                 \
		__XRETURN __hacx16_res;                                 \
	})
#define __hybrid_atomic_cmpxch_val32(x, oldval, newval, order) \
	__hybrid_atomic_cmpxch_val32_seq_cst(x, oldval, newval)
#define __hybrid_atomic_cmpxch_val32_seq_cst(x, oldval, newval) \
	__XBLOCK({                                                  \
		register __UINT32_TYPE__ __hacx32_res;                  \
		__asm__ __volatile__("lock; cmpxchgl %2, %0\n"          \
		                     : "+m" (*(x)), "=a" (__hacx32_res) \
		                     : "r" (newval), "1" (oldval)       \
		                     : "memory", "cc");                 \
		__XRETURN __hacx32_res;                                 \
	})
#define __hybrid_atomic_cmpxch_val64(x, oldval, newval, order) \
	__hybrid_atomic_cmpxch_val64_seq_cst(x, oldval, newval)
#ifdef __x86_64__
#define __hybrid_atomic_cmpxch_val64_seq_cst(x, oldval, newval) \
	__XBLOCK({                                                  \
		register __UINT64_TYPE__ __hacx64_res;                  \
		__asm__ __volatile__("lock; cmpxchgq %2, %0\n"          \
		                     : "+m" (*(x)), "=a" (__hacx64_res) \
		                     : "r" (newval), "1" (oldval)       \
		                     : "memory", "cc");                 \
		__XRETURN __hacx64_res;                                 \
	})
#else /* __x86_64__ */
#define __hybrid_atomic_cmpxch_val64_seq_cst(x, oldval, newval)                            \
	__XBLOCK({                                                                             \
		register __UINT64_TYPE__ __hacx64_res;                                             \
		register __UINT64_TYPE__ __hacx64_nv = (newval);                                   \
		__asm__ __volatile__("lock; cmpxchg8b %0\n"                                        \
		                     : "+m" (x), "=A" (__hacx64_res)                               \
		                     : "A" (oldval)                                                \
		                     , "c" ((__UINT32_TYPE__)((__UINT64_TYPE__)__hacx64_nv >> 32)) \
		                     , "b" ((__UINT32_TYPE__)(__UINT64_TYPE__)__hacx64_nv)         \
		                     : "memory", "cc");                                            \
		__XRETURN __hacx64_res;                                                            \
	})
#endif /* !__x86_64__ */
#else /* ... */
#error "Unsupported Architecture"
#endif /* !... */

#endif /* !__GUARD_HYBRID___ATOMIC_MSVC_H */
