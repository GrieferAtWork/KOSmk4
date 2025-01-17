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
#ifndef _I386_KOS_ASM_INTRIN_ARITH_H
#define _I386_KOS_ASM_INTRIN_ARITH_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>
#include <asm/cpu-flags.h>

/* Arithmetic operations as intrinsic functions. */
#ifdef __CC__
__DECL_BEGIN

/* `-fnon-call-exception' currently  requires  __asm__  to be  marked  as  volatile.
 * s.a. the following bug report: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=94357 */
#ifndef __asm_ncx_memop__
#ifdef __NON_CALL_EXCEPTIONS
#define __asm_ncx_memop__ __asm__ __volatile__
#else /* __NON_CALL_EXCEPTIONS */
#define __asm_ncx_memop__ __asm__
#endif /* !__NON_CALL_EXCEPTIONS */
#endif /* !__asm_ncx_memop__ */

#ifdef __x86_64__
#define __DEFINE_ARTH_BINARY(name, cc_mask, com)                                                                                                                                                                                                                                                                      \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __rhs) { __UINT8_TYPE__ __res; __asm_ncx_memop__(#name "b %b1, %b0" : "=qm" (__res) : com "q" (__rhs), "0" (__lhs) : "cc"); return __res; }                                                                                        \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w)(__UINT16_TYPE__ __lhs, __UINT16_TYPE__ __rhs) { __UINT16_TYPE__ __res; __asm_ncx_memop__(#name "w %w1, %w0" : "=g" (__res) : com "r" (__rhs), "0" (__lhs) : "cc"); return __res; }                                                                                     \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l)(__UINT32_TYPE__ __lhs, __UINT32_TYPE__ __rhs) { __UINT32_TYPE__ __res; __asm_ncx_memop__(#name "l %k1, %k0" : "=g" (__res) : com "r" (__rhs), "0" (__lhs) : "cc"); return __res; }                                                                                     \
	__FORCELOCAL __UINT64_TYPE__ (__##name##q)(__UINT64_TYPE__ __lhs, __UINT64_TYPE__ __rhs) { __UINT64_TYPE__ __res; __asm_ncx_memop__(#name "q %q1, %q0" : "=g" (__res) : com "r" (__rhs), "0" (__lhs) : "cc"); return __res; }                                                                                     \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b_f)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT8_TYPE__ __res; __asm_ncx_memop__(#name "b %b2, %b1\n\tpushfq\n\tpopq %q0" : "=g" (*__pflags), "=qm" (__res) : com "q" (__rhs), "1" (__lhs) : "cc"); return __res; }      \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w_f)(__UINT16_TYPE__ __lhs, __UINT16_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT16_TYPE__ __res; __asm_ncx_memop__(#name "w %w2, %w1\n\tpushfq\n\tpopq %q0" : "=g" (*__pflags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __res; }   \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l_f)(__UINT32_TYPE__ __lhs, __UINT32_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT32_TYPE__ __res; __asm_ncx_memop__(#name "l %k2, %k1\n\tpushfq\n\tpopq %q0" : "=g" (*__pflags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __res; }   \
	__FORCELOCAL __UINT64_TYPE__ (__##name##q_f)(__UINT64_TYPE__ __lhs, __UINT64_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT64_TYPE__ __res; __asm_ncx_memop__(#name "q %q2, %q1\n\tpushfq\n\tpopq %q0" : "=g" (*__pflags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __res; }   \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##b_ff)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __rhs) { __REGISTER_TYPE__ __flags; __UINT8_TYPE__ __res; __asm_ncx_memop__(#name "b %b2, %b1\n\tpushfq\n\tpopq %q0" : "=g" (__flags), "=qm" (__res) : com "q" (__rhs), "1" (__lhs) : "cc"); return __flags & (cc_mask); }   \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##w_ff)(__UINT16_TYPE__ __lhs, __UINT16_TYPE__ __rhs) { __REGISTER_TYPE__ __flags; __UINT16_TYPE__ __res; __asm_ncx_memop__(#name "w %w2, %w1\n\tpushfq\n\tpopq %q0" : "=g" (__flags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __flags & (cc_mask); } \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##l_ff)(__UINT32_TYPE__ __lhs, __UINT32_TYPE__ __rhs) { __REGISTER_TYPE__ __flags; __UINT32_TYPE__ __res; __asm_ncx_memop__(#name "l %k2, %k1\n\tpushfq\n\tpopq %q0" : "=g" (__flags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __flags & (cc_mask); } \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##q_ff)(__UINT64_TYPE__ __lhs, __UINT64_TYPE__ __rhs) { __REGISTER_TYPE__ __flags; __UINT64_TYPE__ __res; __asm_ncx_memop__(#name "q %q2, %q1\n\tpushfq\n\tpopq %q0" : "=g" (__flags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __flags & (cc_mask); }
#define __DEFINE_ARTH_BINARY_CC(name, com)                                                                                                                                                                                                                                                                                                 \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT8_TYPE__ __res; __asm_ncx_memop__("pushq %q0\n\tpopfq\n\t" #name "b %b2, %b1\n\tpushfq\n\tpopq %q0" : "+g" (*__pflags), "=qm" (__res) : com "q" (__rhs), "1" (__lhs) : "cc"); return __res; }    \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w)(__UINT16_TYPE__ __lhs, __UINT16_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT16_TYPE__ __res; __asm_ncx_memop__("pushq %q0\n\tpopfq\n\t" #name "w %w2, %w1\n\tpushfq\n\tpopq %q0" : "+g" (*__pflags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __res; } \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l)(__UINT32_TYPE__ __lhs, __UINT32_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT32_TYPE__ __res; __asm_ncx_memop__("pushq %q0\n\tpopfq\n\t" #name "l %k2, %k1\n\tpushfq\n\tpopq %q0" : "+g" (*__pflags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __res; } \
	__FORCELOCAL __UINT64_TYPE__ (__##name##q)(__UINT64_TYPE__ __lhs, __UINT64_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT64_TYPE__ __res; __asm_ncx_memop__("pushq %q0\n\tpopfq\n\t" #name "q %q2, %q1\n\tpushfq\n\tpopq %q0" : "+g" (*__pflags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __res; }
#define __DEFINE_ARTH_BINARY_FLAGS(name, cc_mask, com)                                                                                                                                                                                                                  \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##b)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __rhs) { __REGISTER_TYPE__ __res; __asm_ncx_memop__(#name "b %b2, %b1\n\tpushfq\n\tpopq %q0" : "=g" (__res) : com "qm" (__lhs), "q" (__rhs) : "cc"); return __res & (cc_mask); }  \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##w)(__UINT16_TYPE__ __lhs, __UINT16_TYPE__ __rhs) { __REGISTER_TYPE__ __res; __asm_ncx_memop__(#name "w %w2, %w1\n\tpushfq\n\tpopq %q0" : "=g" (__res) : com "g" (__lhs), "r" (__rhs) : "cc"); return __res & (cc_mask); } \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##l)(__UINT32_TYPE__ __lhs, __UINT32_TYPE__ __rhs) { __REGISTER_TYPE__ __res; __asm_ncx_memop__(#name "l %k2, %k1\n\tpushfq\n\tpopq %q0" : "=g" (__res) : com "g" (__lhs), "r" (__rhs) : "cc"); return __res & (cc_mask); } \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##q)(__UINT64_TYPE__ __lhs, __UINT64_TYPE__ __rhs) { __REGISTER_TYPE__ __res; __asm_ncx_memop__(#name "l %k2, %k1\n\tpushfq\n\tpopq %q0" : "=g" (__res) : com "g" (__lhs), "r" (__rhs) : "cc"); return __res & (cc_mask); }
#define __DEFINE_SHIFT(name)                                                                                                                                                                                                                                                                                        \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __shift) { __UINT8_TYPE__ __res; __asm_ncx_memop__(#name "b %b1, %b0" : "=qm" (__res) : "Nc" (__shift), "0" (__lhs) : "cc"); return __res; }                                                                                     \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w)(__UINT16_TYPE__ __lhs, __UINT8_TYPE__ __shift) { __UINT16_TYPE__ __res; __asm_ncx_memop__(#name "w %b1, %w0" : "=g" (__res) : "Nc" (__shift), "0" (__lhs) : "cc"); return __res; }                                                                                   \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l)(__UINT32_TYPE__ __lhs, __UINT8_TYPE__ __shift) { __UINT32_TYPE__ __res; __asm_ncx_memop__(#name "l %b1, %k0" : "=g" (__res) : "Nc" (__shift), "0" (__lhs) : "cc"); return __res; }                                                                                   \
	__FORCELOCAL __UINT64_TYPE__ (__##name##q)(__UINT64_TYPE__ __lhs, __UINT8_TYPE__ __shift) { __UINT64_TYPE__ __res; __asm_ncx_memop__(#name "q %b1, %q0" : "=g" (__res) : "Nc" (__shift), "0" (__lhs) : "cc"); return __res; }                                                                                   \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b_f)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT8_TYPE__ __res; __asm_ncx_memop__(#name "b %b2, %b1\n\tpushfq\n\tpopq %q0" : "=g" (*__pflags), "=qm" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; }   \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w_f)(__UINT16_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT16_TYPE__ __res; __asm_ncx_memop__(#name "w %b2, %w1\n\tpushfq\n\tpopq %q0" : "=g" (*__pflags), "=g" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; } \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l_f)(__UINT32_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT32_TYPE__ __res; __asm_ncx_memop__(#name "l %b2, %k1\n\tpushfq\n\tpopq %q0" : "=g" (*__pflags), "=g" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; } \
	__FORCELOCAL __UINT64_TYPE__ (__##name##q_f)(__UINT64_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT64_TYPE__ __res; __asm_ncx_memop__(#name "q %b2, %q1\n\tpushfq\n\tpopq %q0" : "=g" (*__pflags), "=g" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; }
#define __DEFINE_SHIFT_CC(name)                                                                                                                                                                                                                                                                                                            \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT8_TYPE__ __res; __asm_ncx_memop__("pushq %q0\n\tpopfq\n\t" #name "b %b2, %b1\n\tpushfq\n\tpopq %q0" : "+g" (*__pflags), "=qm" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; }   \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w)(__UINT16_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT16_TYPE__ __res; __asm_ncx_memop__("pushq %q0\n\tpopfq\n\t" #name "w %b2, %w1\n\tpushfq\n\tpopq %q0" : "+g" (*__pflags), "=g" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; } \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l)(__UINT32_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT32_TYPE__ __res; __asm_ncx_memop__("pushq %q0\n\tpopfq\n\t" #name "l %b2, %k1\n\tpushfq\n\tpopq %q0" : "+g" (*__pflags), "=g" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; } \
	__FORCELOCAL __UINT64_TYPE__ (__##name##q)(__UINT64_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT64_TYPE__ __res; __asm_ncx_memop__("pushq %q0\n\tpopfq\n\t" #name "q %b2, %q1\n\tpushfq\n\tpopq %q0" : "+g" (*__pflags), "=g" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; }
#else /* __x86_64__ */
#define __DEFINE_ARTH_BINARY(name, cc_mask, com)                                                                                                                                                                                                                                                                      \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __rhs) { __UINT8_TYPE__ __res; __asm_ncx_memop__(#name "b %b1, %b0" : "=qm" (__res) : com "q" (__rhs), "0" (__lhs) : "cc"); return __res; }                                                                                        \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w)(__UINT16_TYPE__ __lhs, __UINT16_TYPE__ __rhs) { __UINT16_TYPE__ __res; __asm_ncx_memop__(#name "w %w1, %w0" : "=g" (__res) : com "r" (__rhs), "0" (__lhs) : "cc"); return __res; }                                                                                     \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l)(__UINT32_TYPE__ __lhs, __UINT32_TYPE__ __rhs) { __UINT32_TYPE__ __res; __asm_ncx_memop__(#name "l %k1, %k0" : "=g" (__res) : com "r" (__rhs), "0" (__lhs) : "cc"); return __res; }                                                                                     \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b_f)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT8_TYPE__ __res; __asm_ncx_memop__(#name "b %b2, %b1\n\tpushfl\n\tpopl %k0" : "=g" (*__pflags), "=qm" (__res) : com "q" (__rhs), "1" (__lhs) : "cc"); return __res; }      \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w_f)(__UINT16_TYPE__ __lhs, __UINT16_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT16_TYPE__ __res; __asm_ncx_memop__(#name "w %w2, %w1\n\tpushfl\n\tpopl %k0" : "=g" (*__pflags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __res; }   \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l_f)(__UINT32_TYPE__ __lhs, __UINT32_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT32_TYPE__ __res; __asm_ncx_memop__(#name "l %k2, %k1\n\tpushfl\n\tpopl %k0" : "=g" (*__pflags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __res; }   \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##b_ff)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __rhs) { __REGISTER_TYPE__ __flags; __UINT8_TYPE__ __res; __asm_ncx_memop__(#name "b %b2, %b1\n\tpushfl\n\tpopl %k0" : "=g" (__flags), "=qm" (__res) : com "q" (__rhs), "1" (__lhs) : "cc"); return __flags & (cc_mask); }   \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##w_ff)(__UINT16_TYPE__ __lhs, __UINT16_TYPE__ __rhs) { __REGISTER_TYPE__ __flags; __UINT16_TYPE__ __res; __asm_ncx_memop__(#name "w %w2, %w1\n\tpushfl\n\tpopl %k0" : "=g" (__flags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __flags & (cc_mask); } \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##l_ff)(__UINT32_TYPE__ __lhs, __UINT32_TYPE__ __rhs) { __REGISTER_TYPE__ __flags; __UINT32_TYPE__ __res; __asm_ncx_memop__(#name "l %k2, %k1\n\tpushfl\n\tpopl %k0" : "=g" (__flags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __flags & (cc_mask); }
#define __DEFINE_ARTH_BINARY_CC(name, com)                                                                                                                                                                                                                                                                                                 \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT8_TYPE__ __res; __asm_ncx_memop__("pushl %k0\n\tpopfl\n\t" #name "b %b2, %b1\n\tpushfl\n\tpopl %k0" : "+g" (*__pflags), "=qm" (__res) : com "q" (__rhs), "1" (__lhs) : "cc"); return __res; }    \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w)(__UINT16_TYPE__ __lhs, __UINT16_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT16_TYPE__ __res; __asm_ncx_memop__("pushl %k0\n\tpopfl\n\t" #name "w %w2, %w1\n\tpushfl\n\tpopl %k0" : "+g" (*__pflags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __res; } \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l)(__UINT32_TYPE__ __lhs, __UINT32_TYPE__ __rhs, __REGISTER_TYPE__ *__restrict __pflags) { __UINT32_TYPE__ __res; __asm_ncx_memop__("pushl %k0\n\tpopfl\n\t" #name "l %k2, %k1\n\tpushfl\n\tpopl %k0" : "+g" (*__pflags), "=g" (__res) : com "r" (__rhs), "1" (__lhs) : "cc"); return __res; }
#define __DEFINE_ARTH_BINARY_FLAGS(name, cc_mask, com)                                                                                                                                                                                                                  \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##b)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __rhs) { __REGISTER_TYPE__ __res; __asm_ncx_memop__(#name "b %b2, %b1\n\tpushfl\n\tpopl %k0" : "=g" (__res) : com "qm" (__lhs), "q" (__rhs) : "cc"); return __res & (cc_mask); }  \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##w)(__UINT16_TYPE__ __lhs, __UINT16_TYPE__ __rhs) { __REGISTER_TYPE__ __res; __asm_ncx_memop__(#name "w %w2, %w1\n\tpushfl\n\tpopl %k0" : "=g" (__res) : com "g" (__lhs), "r" (__rhs) : "cc"); return __res & (cc_mask); } \
	__FORCELOCAL __REGISTER_TYPE__ (__##name##l)(__UINT32_TYPE__ __lhs, __UINT32_TYPE__ __rhs) { __REGISTER_TYPE__ __res; __asm_ncx_memop__(#name "l %k2, %k1\n\tpushfl\n\tpopl %k0" : "=g" (__res) : com "g" (__lhs), "r" (__rhs) : "cc"); return __res & (cc_mask); }
#define __DEFINE_SHIFT(name)                                                                                                                                                                                                                                                                                        \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __shift) { __UINT8_TYPE__ __res; __asm_ncx_memop__(#name "b %b1, %b0" : "=qm" (__res) : "Nc" (__shift), "0" (__lhs) : "cc"); return __res; }                                                                                     \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w)(__UINT16_TYPE__ __lhs, __UINT8_TYPE__ __shift) { __UINT16_TYPE__ __res; __asm_ncx_memop__(#name "w %b1, %w0" : "=g" (__res) : "Nc" (__shift), "0" (__lhs) : "cc"); return __res; }                                                                                   \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l)(__UINT32_TYPE__ __lhs, __UINT8_TYPE__ __shift) { __UINT32_TYPE__ __res; __asm_ncx_memop__(#name "l %b1, %k0" : "=g" (__res) : "Nc" (__shift), "0" (__lhs) : "cc"); return __res; }                                                                                   \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b_f)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT8_TYPE__ __res; __asm_ncx_memop__(#name "b %b2, %b1\n\tpushfl\n\tpopl %k0" : "=g" (*__pflags), "=qm" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; }   \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w_f)(__UINT16_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT16_TYPE__ __res; __asm_ncx_memop__(#name "w %b2, %w1\n\tpushfl\n\tpopl %k0" : "=g" (*__pflags), "=g" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; } \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l_f)(__UINT32_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT32_TYPE__ __res; __asm_ncx_memop__(#name "l %b2, %k1\n\tpushfl\n\tpopl %k0" : "=g" (*__pflags), "=g" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; }
#define __DEFINE_SHIFT_CC(name)                                                                                                                                                                                                                                                                                                            \
	__FORCELOCAL __UINT8_TYPE__ (__##name##b)(__UINT8_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT8_TYPE__ __res; __asm_ncx_memop__("pushl %k0\n\tpopfl\n\t" #name "b %b2, %b1\n\tpushfl\n\tpopl %k0" : "+g" (*__pflags), "=qm" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; }   \
	__FORCELOCAL __UINT16_TYPE__ (__##name##w)(__UINT16_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT16_TYPE__ __res; __asm_ncx_memop__("pushl %k0\n\tpopfl\n\t" #name "w %b2, %w1\n\tpushfl\n\tpopl %k0" : "+g" (*__pflags), "=g" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; } \
	__FORCELOCAL __UINT32_TYPE__ (__##name##l)(__UINT32_TYPE__ __lhs, __UINT8_TYPE__ __shift, __REGISTER_TYPE__ *__restrict __pflags) { __UINT32_TYPE__ __res; __asm_ncx_memop__("pushl %k0\n\tpopfl\n\t" #name "l %b2, %k1\n\tpushfl\n\tpopl %k0" : "+g" (*__pflags), "=g" (__res) : "Nc" (__shift), "1" (__lhs) : "cc"); return __res; }
#endif /* !__x86_64__ */
__DEFINE_ARTH_BINARY(add, EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_AF | EFLAGS_CF | EFLAGS_PF, "%")
__DEFINE_ARTH_BINARY(sub, EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_AF | EFLAGS_PF | EFLAGS_CF, "")
__DEFINE_ARTH_BINARY(and, EFLAGS_OF | EFLAGS_CF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF, "%")
__DEFINE_ARTH_BINARY(or, EFLAGS_OF | EFLAGS_CF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF, "%")
__DEFINE_ARTH_BINARY(xor, EFLAGS_OF | EFLAGS_CF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF, "%")
__DEFINE_ARTH_BINARY_FLAGS(cmp, EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_AF | EFLAGS_PF | EFLAGS_CF, "")
__DEFINE_ARTH_BINARY_FLAGS(test, EFLAGS_OF | EFLAGS_CF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF, "%")
__DEFINE_ARTH_BINARY_CC(adc, "%")
__DEFINE_ARTH_BINARY_CC(sbb, "")
__DEFINE_SHIFT(shl)
__DEFINE_SHIFT(shr)
__DEFINE_SHIFT(sar)
__DEFINE_SHIFT(rol)
__DEFINE_SHIFT(ror)
__DEFINE_SHIFT_CC(rcl)
__DEFINE_SHIFT_CC(rcr)
#ifdef __INTELLISENSE__
__DEFINE_SHIFT(sal)
#else /* __INTELLISENSE__ */
#define __salb   __shlb
#define __salw   __shlw
#define __sall   __shll
#define __salb_f __shlb_f
#define __salw_f __shlw_f
#define __sall_f __shll_f
#ifdef __x86_64__
#define __salq   __shlq
#define __salq_f __shlq_f
#endif /* __x86_64__ */
#endif /* !__INTELLISENSE__ */
#undef __DEFINE_SHIFT
#undef __DEFINE_SHIFT_CC
#undef __DEFINE_ARTH_BINARY_FLAGS
#undef __DEFINE_ARTH_BINARY_CC
#undef __DEFINE_ARTH_BINARY


/* Byte-order instructions */
__FORCELOCAL __ATTR_CONST __UINT16_TYPE__ (__bswapw)(__UINT16_TYPE__ __val) { __UINT16_TYPE__ __res; __asm_ncx_memop__("xchgb %b0, %h0" : "=q" (__res) : "0" (__val)); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__bswapl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("bswapl %k0" : "=r" (__res) : "0" (__val)); return __res; }
__FORCELOCAL __ATTR_PURE __UINT16_TYPE__ (__rdmovbew)(__UINT16_TYPE__ const *__restrict __src) { __UINT16_TYPE__ __res; __asm_ncx_memop__("movbew %w1, %w0" : "=r" (__res) : "m" (*__src)); return __res; }
__FORCELOCAL __ATTR_PURE __UINT32_TYPE__ (__rdmovbel)(__UINT32_TYPE__ const *__restrict __src) { __UINT32_TYPE__ __res; __asm_ncx_memop__("movbel %k1, %k0" : "=r" (__res) : "m" (*__src)); return __res; }
__FORCELOCAL void (__wrmovbew)(__UINT16_TYPE__ *__restrict __dst, __UINT16_TYPE__ __val) { __asm_ncx_memop__("movbew %w1, %w0" : : "m" (*__dst), "r" (__val)); }
__FORCELOCAL void (__wrmovbel)(__UINT32_TYPE__ *__restrict __dst, __UINT32_TYPE__ __val) { __asm_ncx_memop__("movbel %k1, %k0" : : "m" (*__dst), "r" (__val)); }
__FORCELOCAL __ATTR_CONST __UINT16_TYPE__ (__popcntw)(__UINT16_TYPE__ __val) { __UINT16_TYPE__ __res; __asm_ncx_memop__("popcntw %w1, %w0" : "=r" (__res) : "rm" (__val)); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__popcntl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("popcntl %k1, %k0" : "=r" (__res) : "rm" (__val)); return __res; }
__FORCELOCAL __ATTR_CONST __UINT16_TYPE__ (__tzcntw)(__UINT16_TYPE__ __val) { __UINT16_TYPE__ __res; __asm_ncx_memop__("tzcntw %w1, %w0" : "=r" (__res) : "rm" (__val)); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__tzcntl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("tzcntl %k1, %k0" : "=r" (__res) : "rm" (__val)); return __res; }
__FORCELOCAL __ATTR_CONST __UINT16_TYPE__ (__lzcntw)(__UINT16_TYPE__ __val) { __UINT16_TYPE__ __res; __asm_ncx_memop__("lzcntw %w1, %w0" : "=r" (__res) : "rm" (__val)); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__lzcntl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("lzcntl %k1, %k0" : "=r" (__res) : "rm" (__val)); return __res; }
#ifdef __x86_64__
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__bswapq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm__("bswapq %q0" : "=r" (__res) : "0" (__val)); return __res; }
__FORCELOCAL __ATTR_PURE __UINT64_TYPE__ (__rdmovbeq)(__UINT64_TYPE__ const *__restrict __src) { __UINT64_TYPE__ __res; __asm_ncx_memop__("movbeq %q1, %q0" : "=r" (__res) : "m" (*__src)); return __res; }
__FORCELOCAL void (__wrmovbeq)(__UINT64_TYPE__ *__restrict __dst, __UINT64_TYPE__ __val) { __asm_ncx_memop__("movbeq %q1, %q0" : : "m" (*__dst), "r" (__val)); }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__popcntq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("popcntq %q1, %q0" : "=r" (__res) : "rm" (__val)); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__tzcntq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("tzcntq %q1, %q0" : "=r" (__res) : "rm" (__val)); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__lzcntq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("lzcntq %q1, %q0" : "=r" (__res) : "rm" (__val)); return __res; }
#endif /* __x86_64__ */

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_ASM_INTRIN_ARITH_H */
