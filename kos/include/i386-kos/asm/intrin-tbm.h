/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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

/* `-fnon-call-exception' currently  requires  __asm__  to be  marked  as  volatile.
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
 *  - __blcmskl  __blcmskq:  return  val ^ (val + 1);
 *  - __blsmskl  __blsmskq:  return  val ^ (val - 1);
 *  - __blsrl    __blsrq:    return  val & (val - 1);
 *  - __blcfilll __blcfillq: return  val & (val + 1);
 *  - __blsfilll __blsfillq: return  val | (val - 1);
 *  - __blcsl    __blcsq:    return  val | (val + 1);
 *  - __tzmskl   __tzmskq:   return ~val & (val - 1);
 *  - __blcicl   __blcicq:   return ~val & (val + 1);
 *  - __blsicl   __blsicq:   return ~val | (val - 1);
 *  - __t1mskcl  __t1mskcq:  return ~val | (val + 1);
 *  - __blcil    __blciq:    return  val | ~(val + 1);
 */


/* Technically,  Zg  would be  the correct  variant to  choose here  (at least  under KOS,
 * or when  unconditionally targeting  AMD processors),  since AMD  provides an  immediate
 * variant that is emulated under KOS. However (at least with QEMU), instruction emulation
 * is somewhat flawed,  in that  opcode 0x8f  is emulated  as pop  for _all_  modrm.mi_reg
 * values,   rather   than  only   being  emulated   for   0x8f/0  (modrm.mi_reg   ==  0).
 * Because  opcode 0x8f/{1-7} is the entry point for XOP opcodes, and because QEMU doesn't
 * natively emulate XOP opcodes, this makes it  impossible for KOS to emulate XOP  opcodes
 * when  running under QEMU. (it is unknown if,  but likely that real hardware exists with
 * the same problem)
 * As  such, keep `bextr' free of XOP (and  as a side-note, try to avoid instructions
 * annotated as `xop' below, as those are the ones that can't be emulated under QEMU) */
#if 0
#define __X86_BEXTR_STARTLEN_CONSTRAINTS "Zg" /* u32, modrm */
#else
#define __X86_BEXTR_STARTLEN_CONSTRAINTS "g" /* modrm */
#endif


__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*   */ (__bextrl)(__UINT32_TYPE__ __x, __UINT8_TYPE__ __start, __UINT8_TYPE__ __len) { __UINT32_TYPE__ __res; __asm_ncx_memop__("bextr %k2, %k1, %k0" : "=r" (__res) : "g" (__x), __X86_BEXTR_STARTLEN_CONSTRAINTS ((__UINT32_TYPE__)__start | ((__UINT32_TYPE__)__len << 8)) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*   */ (__andnl)(__UINT32_TYPE__ __x, __UINT32_TYPE__ __y) { __UINT32_TYPE__ __res; __asm_ncx_memop__("andn %k2, %k1, %k0" : "=r" (__res) : "r" (__x), "g" (__y) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*   */ (__blsil)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blsi %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*xop*/ (__blcmskl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blcmsk %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*   */ (__blsmskl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blsmsk %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*   */ (__blsrl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blsr %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*xop*/ (__blcfilll)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blcfill %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*xop*/ (__blsfilll)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blsfill %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*xop*/ (__blcsl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blcs %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*xop*/ (__tzmskl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("tzmsk %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*xop*/ (__blcicl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blcic %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*xop*/ (__blsicl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blsic %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*xop*/ (__t1mskcl)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("t1mskc %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT32_TYPE__ /*xop*/ (__blcil)(__UINT32_TYPE__ __val) { __UINT32_TYPE__ __res; __asm_ncx_memop__("blci %k1, %k0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }

#ifdef __x86_64__
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*   */ (__bextrq)(__UINT64_TYPE__ __x, __UINT8_TYPE__ __start, __UINT8_TYPE__ __len) { __UINT64_TYPE__ __res; __asm_ncx_memop__("bextr %q2, %q1, %q0" : "=r" (__res) : "g" (__x), __X86_BEXTR_STARTLEN_CONSTRAINTS ((__UINT64_TYPE__)__start | ((__UINT64_TYPE__)__len << 8)) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*   */ (__andnq)(__UINT64_TYPE__ __x, __UINT64_TYPE__ __y) { __UINT64_TYPE__ __res; __asm_ncx_memop__("andn %q2, %q1, %q0" : "=r" (__res) : "r" (__x), "g" (__y) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*   */ (__blsiq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blsi %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*xop*/ (__blcmskq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blcmsk %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*   */ (__blsmskq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blsmsk %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*   */ (__blsrq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blsr %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*xop*/ (__blcfillq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blcfill %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*xop*/ (__blsfillq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blsfill %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*xop*/ (__blcsq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blcs %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*xop*/ (__tzmskq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("tzmsk %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*xop*/ (__blcicq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blcic %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*xop*/ (__blsicq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blsic %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*xop*/ (__t1mskcq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("t1mskc %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
__FORCELOCAL __ATTR_CONST __UINT64_TYPE__ /*xop*/ (__blciq)(__UINT64_TYPE__ __val) { __UINT64_TYPE__ __res; __asm_ncx_memop__("blci %q1, %q0" : "=r" (__res) : "g" (__val) : "cc"); return __res; }
#endif /* __x86_64__ */

#undef __X86_BEXTR_STARTLEN_CONSTRAINTS

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_ASM_INTRIN_TBM_H */
