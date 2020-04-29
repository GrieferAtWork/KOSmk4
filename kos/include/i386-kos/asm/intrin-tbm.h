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
#ifndef _I386_KOS_ASM_INTRIN_TBM_H
#define _I386_KOS_ASM_INTRIN_TBM_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

/* Arithmetic operations as intrinsic functions. */
#ifdef __CC__
__DECL_BEGIN

/* `-fnon-call-exception' currently requires __asm__ to be marked as volatile.
 * s.a. the following bug report: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=94357 */
#ifndef __asm_ncx_memop__
#ifdef __NON_CALL_EXCEPTIONS
#define __asm_ncx_memop__ __asm__ __volatile__
#else /* __NON_CALL_EXCEPTIONS */
#define __asm_ncx_memop__ __asm__
#endif /* !__NON_CALL_EXCEPTIONS */
#endif /* !__asm_ncx_memop__ */


/* Instruction behavior:
 *  - __bextrl   __bextrq:   return  (x >> start) & ((1 << len) - 1);
 *  - __andnl    __andnq:    return  ~x & y;
 *  - __blsil    __blsiq:    return  val & -val;      // aka. `val & ~(val - 1)'
 *  - __blsmskl  __blsmskq:  return  val ^ (val - 1);
 *  - __blsrl    __blsrq:    return  val & (val - 1);
 *  - __blcfilll __blcfillq: return  val & (val + 1);
 *  - __blsfilll __blsfillq: return  val | (val - 1);
 *  - __blcsl    __blcsq:    return  val | (val + 1);
 *  - __tzmskl   __tzmskq:   return ~val & (val - 1);
 *  - __blcicl   __blcicq:   return ~val & (val + 1);
 *  - __blsicl   __blsicq:   return ~val | (val - 1);
 *  - __t1mskcl  __t1mskcq:  return ~val | (val + 1); */

__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__bextrl)(__UINT32_TYPE__ __x, __UINT8_TYPE__ __start, __UINT8_TYPE__ __len) { __UINT32_TYPE__ __res; __asm_ncx_memop__("bextr %k2, %k1, %k0" : "=r" (__res) : "g" (__x), "g" ((__UINT32_TYPE__)__start | ((__UINT32_TYPE__)__len << 8)) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__andnl)(__UINT32_TYPE__ __x, __UINT32_TYPE__ __y) { __UINT32_TYPE__ __res; __asm_ncx_memop__("andn %k2, %k1, %k0" : "=r" (__res) : "g" (__x), "g" (__y) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__blsil)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blsi %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__blsmskl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blsmsk %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__blsrl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blsr %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__blcfilll)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blcfill %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__blsfilll)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blsfill %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__blcsl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blcs %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__tzmskl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("tzmsk %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__blcicl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blcic %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__blsicl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blsic %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ (__t1mskcl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("t1mskc %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }

#ifdef __x86_64__
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__bextrl)(__UINT64_TYPE__ __x, __UINT8_TYPE__ __start, __UINT8_TYPE__ __len) { __UINT64_TYPE__ __res; __asm_ncx_memop__("bextr %q2, %q1, %q0" : "=r" (__res) : "g" (__x), "g" ((__UINT64_TYPE__)__start | ((__UINT64_TYPE__)__len << 8)) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__andnq)(__UINT64_TYPE__ __x, __UINT64_TYPE__ __y) { __UINT64_TYPE__ __res; __asm_ncx_memop__("andn %q2, %q1, %q0" : "=r" (__res) : "g" (__x), "g" (__y) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__blsiq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blsi %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__blsmskq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blsmsk %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__blsrq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blsr %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__blcfillq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blcfill %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__blsfillq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blsfill %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__blcsq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blcs %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__tzmskq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("tzmsk %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__blcicq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blcic %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__blsicq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blsic %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ (__t1mskcq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("t1mskc %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
#endif /* __x86_64__ */


__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_ASM_INTRIN_TBM_H */
