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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_FAULT_C
#define GUARD_APPS_SYSTEM_TEST_TEST_FAULT_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#if defined(__i386__) || defined(__x86_64__)
#include <hybrid/typecore.h> /* __REGISTER_TYPE__ */

#include <asm/intrin-arith.h>
#include <asm/intrin-tbm.h>
#include <asm/intrin.h>
#include <kos/except.h>
#include <kos/kernel/paging.h>
#include <kos/kernel/types.h>
#include <kos/types.h>
#include <sys/types.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <atomic.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

#define assert_except_code(code) \
	assertf(was_thrown(code), "except_code(): %#Ix", except_code())
#define assert_range(a, b, shift)                                      \
	assertf(((uintptr_t)(a) - (uintptr_t)(b)) <= (uintptr_t)(shift) || \
	        ((uintptr_t)(b) - (uintptr_t)(a)) <= (uintptr_t)(shift),   \
	        "%p <= %p <= %p",                                          \
	        (uintptr_t)((uintptr_t)(b) - (uintptr_t)(shift)),          \
	        (uintptr_t)(a),                                            \
	        (uintptr_t)((uintptr_t)(b) + (uintptr_t)(shift)))
#define assert_eq_msk(a, mask, flag) \
	assertf(((uintptr_t)(a) & (uintptr_t)(mask)) == (uintptr_t)(flag), "%p & %p != %p", \
	        (uintptr_t)(a), (uintptr_t)(mask), (uintptr_t)(flag))

/* Make sure that accessing both canonical  and non-canonical memory locations produces  segfaults,
 * as well as that accessing memory near the end of the address space is handled correctly as well! */

INTDEF uintptr_t volatile p ASMNAME("_tfp");
INTDEF __REGISTER_TYPE__ q ASMNAME("_tfq");

INTERN uintptr_t volatile p = 0;
INTERN __REGISTER_TYPE__ q = 0;

#define WORDMASK (sizeof(void *) - 1)

PRIVATE ATTR_NOINLINE bool
test_addr_op(unsigned int op, void *addr, bool is_canon, bool is_vio) {
	void *volatile addr2 = addr;
	uintptr_t exp_mask;
	uintptr_t exp_context;
	exp_mask = E_SEGFAULT_CONTEXT_EXEC | E_SEGFAULT_CONTEXT_NONCANON;
	exp_context = 0;
	if (!is_canon)
		exp_context |= E_SEGFAULT_CONTEXT_NONCANON;
	TRY {
		/* Because the way in which exception are generated in kernel-space
		 * depends  on the instruction  used, make use of  a whole bunch of
		 * different instructions here! */
		switch (op) {

#define RO  exp_mask |= E_SEGFAULT_CONTEXT_WRITING
#define WO  exp_context |= E_SEGFAULT_CONTEXT_WRITING, exp_mask |= E_SEGFAULT_CONTEXT_WRITING
#define XO  exp_context |= E_SEGFAULT_CONTEXT_EXEC, exp_mask |= (E_SEGFAULT_CONTEXT_WRITING | E_SEGFAULT_CONTEXT_EXEC)

#ifdef __x86_64__
#define I64(...) __VA_ARGS__
#else /* __x86_64__ */
#define I64(...) return true;
#endif /* !__x86_64__ */

		case 0x0000: RO; p = *(u8 const *)addr; break;
		case 0x0001: RO; p = *(u16 const *)addr; break;
		case 0x0002: RO; p = *(u32 const *)addr; break;
		case 0x0003: RO; I64(p = *(u64 const *)addr); break;

		case 0x0004: WO; *(u8 *)addr = (u8)p; break;
		case 0x0005: WO; *(u16 *)addr = (u16)p; break;
		case 0x0006: WO; *(u32 *)addr = (u32)p; break;
		case 0x0007: WO; I64(*(u64 *)addr = (u64)p); break;

		case 0x0008: atomic_inc((u8 *)addr); break;
		case 0x0009: atomic_inc((u16 *)addr); break;
		case 0x000a: atomic_inc((u32 *)addr); break;
		case 0x000b: I64(atomic_inc((u64 *)addr)); break;

		case 0x000c: atomic_dec((u8 *)addr); break;
		case 0x000d: atomic_dec((u16 *)addr); break;
		case 0x000e: atomic_dec((u32 *)addr); break;
		case 0x000f: I64(atomic_dec((u64 *)addr)); break;

		case 0x0010: atomic_add((u8 *)addr, (u8)p); break;
		case 0x0011: atomic_add((u16 *)addr, (u16)p); break;
		case 0x0012: atomic_add((u32 *)addr, (u32)p); break;
		case 0x0013: I64(atomic_add((u64 *)addr, (u64)p)); break;

		case 0x0014: atomic_sub((u8 *)addr, (u8)p); break;
		case 0x0015: atomic_sub((u16 *)addr, (u16)p); break;
		case 0x0016: atomic_sub((u32 *)addr, (u32)p); break;
		case 0x0017: I64(atomic_sub((u64 *)addr, (u64)p)); break;

		case 0x0018: atomic_and((u8 *)addr, (u8)p); break;
		case 0x0019: atomic_and((u16 *)addr, (u16)p); break;
		case 0x001a: atomic_and((u32 *)addr, (u32)p); break;
		case 0x001b: I64(atomic_and((u64 *)addr, (u64)p)); break;

		case 0x001c: atomic_or((u8 *)addr, (u8)p); break;
		case 0x001d: atomic_or((u16 *)addr, (u16)p); break;
		case 0x001e: atomic_or((u32 *)addr, (u32)p); break;
		case 0x001f: I64(atomic_or((u64 *)addr, (u64)p)); break;

		case 0x0020: atomic_xor((u8 *)addr, (u8)p); break;
		case 0x0021: atomic_xor((u16 *)addr, (u16)p); break;
		case 0x0022: atomic_xor((u32 *)addr, (u32)p); break;
		case 0x0023: I64(atomic_xor((u64 *)addr, (u64)p)); break;

		case 0x0024: atomic_xch((u8 *)addr, (u8)p); break;
		case 0x0025: atomic_xch((u16 *)addr, (u16)p); break;
		case 0x0026: atomic_xch((u32 *)addr, (u32)p); break;
		case 0x0027: I64(atomic_xch((u64 *)addr, (u64)p)); break;

		case 0x0028: *(u8 *)addr <<= (shift_t)p; break;
		case 0x0029: *(u16 *)addr <<= (shift_t)p; break;
		case 0x002a: *(u32 *)addr <<= (shift_t)p; break;
		case 0x002b: I64(*(u64 *)addr <<= (shift_t)p); break;

		case 0x002c: *(u8 *)addr >>= (shift_t)p; break;
		case 0x002d: *(u16 *)addr >>= (shift_t)p; break;
		case 0x002e: *(u32 *)addr >>= (shift_t)p; break;
		case 0x002f: I64(*(u64 *)addr >>= (shift_t)p); break;

		case 0x0030: *(s8 *)addr >>= (shift_t)p; break;
		case 0x0031: *(s16 *)addr >>= (shift_t)p; break;
		case 0x0032: *(s32 *)addr >>= (shift_t)p; break;
		case 0x0033: I64(*(s64 *)addr >>= (shift_t)p); break;

		case 0x0034: *(s8 *)addr *= (s8)p; break;
		case 0x0035: *(s16 *)addr *= (s16)p; break;
		case 0x0036: *(s32 *)addr *= (s32)p; break;
		case 0x0037: I64(*(s64 *)addr *= (s64)p); break;

		case 0x0038: if (!p) p = 42; *(s8 *)addr /= (s8)p; break;
		case 0x0039: if (!p) p = 42; *(s16 *)addr /= (s16)p; break;
		case 0x003a: if (!p) p = 42; *(s32 *)addr /= (s32)p; break;
		case 0x003b: I64(if (!p) p = 42; *(s64 *)addr /= (s64)p); break;

		case 0x003c: if (!p) p = 42; *(s8 *)addr %= (s8)p; break;
		case 0x003d: if (!p) p = 42; *(s16 *)addr %= (s16)p; break;
		case 0x003e: if (!p) p = 42; *(s32 *)addr %= (s32)p; break;
		case 0x003f: I64(if (!p) p = 42; *(s64 *)addr %= (s64)p); break;

		case 0x0040: *(u8 *)addr *= (u8)p; break;
		case 0x0041: *(u16 *)addr *= (u16)p; break;
		case 0x0042: *(u32 *)addr *= (u32)p; break;
		case 0x0043: I64(*(u64 *)addr *= (u64)p); break;

		case 0x0044: if (!p) p = 42; *(u8 *)addr /= (u8)p; break;
		case 0x0045: if (!p) p = 42; *(u16 *)addr /= (u16)p; break;
		case 0x0046: if (!p) p = 42; *(u32 *)addr /= (u32)p; break;
		case 0x0047: I64(if (!p) p = 42; *(u64 *)addr /= (u64)p); break;

		case 0x0048: if (!p) p = 42; *(u8 *)addr %= (u8)p; break;
		case 0x0049: if (!p) p = 42; *(u16 *)addr %= (u16)p; break;
		case 0x004a: if (!p) p = 42; *(u32 *)addr %= (u32)p; break;
		case 0x004b: I64(if (!p) p = 42; *(u64 *)addr %= (u64)p); break;

		case 0x004c: *(u8 *)addr = ~*(u8 *)addr; break;
		case 0x004d: *(u16 *)addr = ~*(u16 *)addr; break;
		case 0x004e: *(u32 *)addr = ~*(u32 *)addr; break;
		case 0x004f: I64(*(u64 *)addr = ~*(u64 *)addr); break;

		case 0x0050: *(u8 *)addr = !*(u8 *)addr; break;
		case 0x0051: *(u16 *)addr = !*(u16 *)addr; break;
		case 0x0052: *(u32 *)addr = !*(u32 *)addr; break;
		case 0x0053: I64(*(u64 *)addr = !*(u64 *)addr); break;

		case 0x0054: RO; p = (*(u8 *)addr & (u8)p) != 0; break;
		case 0x0055: RO; p = (*(u16 *)addr & (u16)p) != 0; break;
		case 0x0056: RO; p = (*(u32 *)addr & (u32)p) != 0; break;
		case 0x0057: RO; I64(p = (*(u64 *)addr & (u64)p) != 0); break;

		case 0x0058: RO; p = (*(u8 *)addr & 0x1) != 0; break;
		case 0x0059: RO; p = (*(u16 *)addr & 0x1) != 0; break;
		case 0x005a: RO; p = (*(u32 *)addr & 0x1) != 0; break;
		case 0x005b: RO; I64(p = (*(u64 *)addr & 0x1) != 0); break;

		case 0x005c: RO; /*p = __popcntb(*(u8 *)addr);*/ return true;
		case 0x005d: RO; p = __popcntw(*(u16 *)addr); break;
		case 0x005e: RO; p = __popcntl(*(u32 *)addr); break;
		case 0x005f: RO; I64(p = __popcntq(*(u64 *)addr)); break;

		case 0x0060: RO; /*p = __tzcntb(*(u8 *)addr);*/ return true;
		case 0x0061: RO; p = __tzcntw(*(u16 *)addr); break;
		case 0x0062: RO; p = __tzcntl(*(u32 *)addr); break;
		case 0x0063: RO; I64(p = __tzcntq(*(u64 *)addr)); break;

		case 0x0064: RO; /*p = __lzcntb(*(u8 *)addr);*/ return true;
		case 0x0065: RO; p = __lzcntw(*(u16 *)addr); break;
		case 0x0066: RO; p = __lzcntl(*(u32 *)addr); break;
		case 0x0067: RO; I64(p = __lzcntq(*(u64 *)addr)); break;

		case 0x0068: RO; /*p = __rdmovbeb((u8 *)addr);*/ return true;
		case 0x0069: RO; p = __rdmovbew((u16 *)addr); break;
		case 0x006a: RO; p = __rdmovbel((u32 *)addr); break;
		case 0x006b: RO; I64(p = __rdmovbeq((u64 *)addr)); break;

		case 0x006c: WO; /*__rdmovbeb((u8 *)addr, (u8)p);*/ return true;
		case 0x006d: WO; __wrmovbew((u16 *)addr, (u16)p); break;
		case 0x006e: WO; __wrmovbel((u32 *)addr, (u32)p); break;
		case 0x006f: WO; I64(__wrmovbeq((u64 *)addr, (u64)p)); break;

		case 0x0070: RO; p = __addb(*(u8 *)addr, (u8)p); break;
		case 0x0071: RO; p = __addw(*(u16 *)addr, (u16)p); break;
		case 0x0072: RO; p = __addl(*(u32 *)addr, (u32)p); break;
		case 0x0073: RO; I64(p = __addq(*(u64 *)addr, (u64)p)); break;

		case 0x0084: RO; p = __addb((u8)p, *(u8 *)addr); break;
		case 0x0085: RO; p = __addw((u16)p, *(u16 *)addr); break;
		case 0x0086: RO; p = __addl((u32)p, *(u32 *)addr); break;
		case 0x0087: RO; I64(p = __addq((u64)p, *(u64 *)addr)); break;

		case 0x0088: RO; p = __subb(*(u8 *)addr, (u8)p); break;
		case 0x0089: RO; p = __subw(*(u16 *)addr, (u16)p); break;
		case 0x008a: RO; p = __subl(*(u32 *)addr, (u32)p); break;
		case 0x008b: RO; I64(p = __subq(*(u64 *)addr, (u64)p)); break;

		case 0x008c: RO; p = __subb((u8)p, *(u8 *)addr); break;
		case 0x008d: RO; p = __subw((u16)p, *(u16 *)addr); break;
		case 0x008e: RO; p = __subl((u32)p, *(u32 *)addr); break;
		case 0x008f: RO; I64(p = __subq((u64)p, *(u64 *)addr)); break;

		case 0x0090: RO; p = __andb(*(u8 *)addr, (u8)p); break;
		case 0x0091: RO; p = __andw(*(u16 *)addr, (u16)p); break;
		case 0x0092: RO; p = __andl(*(u32 *)addr, (u32)p); break;
		case 0x0093: RO; I64(p = __andq(*(u64 *)addr, (u64)p)); break;

		case 0x0094: RO; p = __andb((u8)p, *(u8 *)addr); break;
		case 0x0095: RO; p = __andw((u16)p, *(u16 *)addr); break;
		case 0x0096: RO; p = __andl((u32)p, *(u32 *)addr); break;
		case 0x0097: RO; I64(p = __andq((u64)p, *(u64 *)addr)); break;

		case 0x0098: RO; p = __orb(*(u8 *)addr, (u8)p); break;
		case 0x0099: RO; p = __orw(*(u16 *)addr, (u16)p); break;
		case 0x009a: RO; p = __orl(*(u32 *)addr, (u32)p); break;
		case 0x009b: RO; I64(p = __orq(*(u64 *)addr, (u64)p)); break;

		case 0x009c: RO; p = __orb((u8)p, *(u8 *)addr); break;
		case 0x009d: RO; p = __orw((u16)p, *(u16 *)addr); break;
		case 0x009e: RO; p = __orl((u32)p, *(u32 *)addr); break;
		case 0x009f: RO; I64(p = __orq((u64)p, *(u64 *)addr)); break;

		case 0x00a0: RO; p = __xorb(*(u8 *)addr, (u8)p); break;
		case 0x00a1: RO; p = __xorw(*(u16 *)addr, (u16)p); break;
		case 0x00a2: RO; p = __xorl(*(u32 *)addr, (u32)p); break;
		case 0x00a3: RO; I64(p = __xorq(*(u64 *)addr, (u64)p)); break;

		case 0x00a4: RO; p = __xorb((u8)p, *(u8 *)addr); break;
		case 0x00a5: RO; p = __xorw((u16)p, *(u16 *)addr); break;
		case 0x00a6: RO; p = __xorl((u32)p, *(u32 *)addr); break;
		case 0x00a7: RO; I64(p = __xorq((u64)p, *(u64 *)addr)); break;

		case 0x00a8: RO; p = __testb(*(u8 *)addr, (u8)p); break;
		case 0x00a9: RO; p = __testw(*(u16 *)addr, (u16)p); break;
		case 0x00aa: RO; p = __testl(*(u32 *)addr, (u32)p); break;
		case 0x00ab: RO; I64(p = __testq(*(u64 *)addr, (u64)p)); break;

		case 0x00ac: RO; p = __testb((u8)p, *(u8 *)addr); break;
		case 0x00ad: RO; p = __testw((u16)p, *(u16 *)addr); break;
		case 0x00ae: RO; p = __testl((u32)p, *(u32 *)addr); break;
		case 0x00af: RO; I64(p = __testq((u64)p, *(u64 *)addr)); break;

		case 0x00b0: RO; p = __cmpb(*(u8 *)addr, (u8)p); break;
		case 0x00b1: RO; p = __cmpw(*(u16 *)addr, (u16)p); break;
		case 0x00b2: RO; p = __cmpl(*(u32 *)addr, (u32)p); break;
		case 0x00b3: RO; I64(p = __cmpq(*(u64 *)addr, (u64)p)); break;

		case 0x00b4: RO; p = __cmpb((u8)p, *(u8 *)addr); break;
		case 0x00b5: RO; p = __cmpw((u16)p, *(u16 *)addr); break;
		case 0x00b6: RO; p = __cmpl((u32)p, *(u32 *)addr); break;
		case 0x00b7: RO; I64(p = __cmpq((u64)p, *(u64 *)addr)); break;

		case 0x00b8: RO; p = __adcb(*(u8 *)addr, (u8)p, &q); break;
		case 0x00b9: RO; p = __adcw(*(u16 *)addr, (u16)p, &q); break;
		case 0x00ba: RO; p = __adcl(*(u32 *)addr, (u32)p, &q); break;
		case 0x00bb: RO; I64(p = __adcq(*(u64 *)addr, (u64)p, &q)); break;

		case 0x00bc: RO; p = __adcb((u8)p, *(u8 *)addr, &q); break;
		case 0x00bd: RO; p = __adcw((u16)p, *(u16 *)addr, &q); break;
		case 0x00be: RO; p = __adcl((u32)p, *(u32 *)addr, &q); break;
		case 0x00bf: RO; I64(p = __adcq((u64)p, *(u64 *)addr, &q)); break;

		case 0x00c0: RO; p = __sbbb(*(u8 *)addr, (u8)p, &q); break;
		case 0x00c1: RO; p = __sbbw(*(u16 *)addr, (u16)p, &q); break;
		case 0x00c2: RO; p = __sbbl(*(u32 *)addr, (u32)p, &q); break;
		case 0x00c3: RO; I64(p = __sbbq(*(u64 *)addr, (u64)p, &q)); break;

		case 0x00c4: RO; p = __sbbb((u8)p, *(u8 *)addr, &q); break;
		case 0x00c5: RO; p = __sbbw((u16)p, *(u16 *)addr, &q); break;
		case 0x00c6: RO; p = __sbbl((u32)p, *(u32 *)addr, &q); break;
		case 0x00c7: RO; I64(p = __sbbq((u64)p, *(u64 *)addr, &q)); break;

		case 0x00c8: RO; p = __shlb(*(u8 *)addr, (unsigned int)p); break;
		case 0x00c9: RO; p = __shlw(*(u16 *)addr, (unsigned int)p); break;
		case 0x00ca: RO; p = __shll(*(u32 *)addr, (unsigned int)p); break;
		case 0x00cb: RO; I64(p = __shlq(*(u64 *)addr, (unsigned int)p)); break;

		case 0x00cc: RO; p = __shrb(*(u8 *)addr, (unsigned int)p); break;
		case 0x00cd: RO; p = __shrw(*(u16 *)addr, (unsigned int)p); break;
		case 0x00ce: RO; p = __shrl(*(u32 *)addr, (unsigned int)p); break;
		case 0x00cf: RO; I64(p = __shrq(*(u64 *)addr, (unsigned int)p)); break;

		case 0x00d0: RO; p = __sarb(*(u8 *)addr, (unsigned int)p); break;
		case 0x00d1: RO; p = __sarw(*(u16 *)addr, (unsigned int)p); break;
		case 0x00d2: RO; p = __sarl(*(u32 *)addr, (unsigned int)p); break;
		case 0x00d3: RO; I64(p = __sarq(*(u64 *)addr, (unsigned int)p)); break;

		case 0x00d4: RO; p = __rolb(*(u8 *)addr, (unsigned int)p); break;
		case 0x00d5: RO; p = __rolw(*(u16 *)addr, (unsigned int)p); break;
		case 0x00d6: RO; p = __roll(*(u32 *)addr, (unsigned int)p); break;
		case 0x00d7: RO; I64(p = __rolq(*(u64 *)addr, (unsigned int)p)); break;

		case 0x00d8: RO; p = __rorb(*(u8 *)addr, (unsigned int)p); break;
		case 0x00d9: RO; p = __rorw(*(u16 *)addr, (unsigned int)p); break;
		case 0x00da: RO; p = __rorl(*(u32 *)addr, (unsigned int)p); break;
		case 0x00db: RO; I64(p = __rorq(*(u64 *)addr, (unsigned int)p)); break;

		case 0x00dc: RO; p = __rclb(*(u8 *)addr, (unsigned int)p, &q); break;
		case 0x00dd: RO; p = __rclw(*(u16 *)addr, (unsigned int)p, &q); break;
		case 0x00de: RO; p = __rcll(*(u32 *)addr, (unsigned int)p, &q); break;
		case 0x00df: RO; I64(p = __rclq(*(u64 *)addr, (unsigned int)p, &q)); break;

		case 0x00e0: RO; p = __rcrb(*(u8 *)addr, (unsigned int)p, &q); break;
		case 0x00e1: RO; p = __rcrw(*(u16 *)addr, (unsigned int)p, &q); break;
		case 0x00e2: RO; p = __rcrl(*(u32 *)addr, (unsigned int)p, &q); break;
		case 0x00e3: RO; I64(p = __rcrq(*(u64 *)addr, (unsigned int)p, &q)); break;

		case 0x00e4: RO; /*p = __andnb(*(u8 *)addr, (u8)p);*/ return true;
		case 0x00e5: RO; /*p = __andnw(*(u16 *)addr, (u16)p);*/ return true;
		case 0x00e6: RO; p = __andnl(*(u32 *)addr, (u32)p); break;
		case 0x00e7: RO; I64(p = __andnq(*(u64 *)addr, (u64)p)); break;

		case 0x00e8: XO; (*(void(*)(int, int))addr)(10, 20); break;
		case 0x00e9: XO; /*goto *addr;*/ return true; /* This cannot safely be tested... */
		case 0x00ea: RO; p = (unsigned int)memcmp(addr, addr2, 1); break;
		case 0x00eb: memcpy(addr, addr2, 1); break;
		case 0x00ec: memmove(addr, addr2, 1); break;
		case 0x00ed: memmoveup(addr2, addr, 1); break;
		case 0x00ee: memmovedown(addr, addr2, 1); break;
		case 0x00ef: memcpyw(addr, addr2, 1); break;
		case 0x00f0: memmovew(addr, addr2, 1); break;
		case 0x00f1: memmoveupw(addr2, addr, 1); break;
		case 0x00f2: memmovedownw(addr, addr2, 1); break;
		case 0x00f3: memcpyl(addr, addr2, 1); break;
		case 0x00f4: memmovel(addr, addr2, 1); break;
		case 0x00f5: memmoveupl(addr2, addr, 1); break;
		case 0x00f6: memmovedownl(addr, addr2, 1); break;
		case 0x00f7: I64(memcpyq(addr, addr2, 1)); break;
		case 0x00f8: I64(memmoveq(addr, addr2, 1)); break;
		case 0x00f9: I64(memmoveupq(addr2, addr, 1)); break;
		case 0x00fa: I64(memmovedownq(addr, addr2, 1)); break;
		case 0x00fb: WO; memset(addr, UINT8_C(0x42), 1); break;
		case 0x00fc: WO; memsetw(addr, UINT16_C(0x4242), 1); break;
		case 0x00fd: WO; memsetl(addr, UINT32_C(0x42424242), 1); break;
		case 0x00fe: WO; I64(memsetq(addr, UINT64_C(0x4242424242424242), 1)); break;
		case 0x00ff: RO; /* push r/m */ (*(void (*)(int, int, int, int, int, int, int, int, int, int, u8))addr)(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, *(u8 *)addr); break;
		case 0x0100: RO; /* push r/m */ (*(void (*)(int, int, int, int, int, int, int, int, int, int, u16))addr)(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, *(u16 *)addr); break;
		case 0x0101: RO; /* push r/m */ (*(void (*)(int, int, int, int, int, int, int, int, int, int, u32))addr)(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, *(u32 *)addr); break;
		case 0x0102: RO; I64(/* push r/m */ (*(void (*)(int, int, int, int, int, int, int, int, int, int, u64))addr)(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, *(u64 *)addr)); break;

		default:
			return false;
		}
		assert_failed("Shouldn't get here: %p (op:%u)\n", addr, op);
	} EXCEPT {
		assert_except_code(E_SEGFAULT);
		if (is_vio) {
			/* VIO dispatching may  try to access  multiple surrounding  bytes
			 * in order to service the request. Because of this, fault pointer
			 * may be scattered around the  actually accessed location by  the
			 * max # number of bytes on the data-bus minus 1 */
			assert_range(except_data()->e_args.e_segfault.s_addr, addr, WORDMASK);

			/* VIO  writes may first perform reads in order to then write-back
			 * a larger data word (e.g. `pokeb(addr, v)' may be dispatched as:
			 * >> a.word = peekw(addr & ~1);
			 * >> a.bytes[addr & 1] = v;
			 * >> pokew(addr & ~1, a.word);
			 * As such, the first operation can be a read, even when a write is
			 * being dispatched, so we can't assert that the faulting operation
			 * was actually a write! */
			exp_mask    &= ~(E_SEGFAULT_CONTEXT_WRITING);
			exp_context &= ~(E_SEGFAULT_CONTEXT_WRITING);

			/* We're expecting a VIO access */
			exp_mask    |= E_SEGFAULT_CONTEXT_VIO;
			exp_context |= E_SEGFAULT_CONTEXT_VIO;
		} else {
			EQ(addr, (void *)except_data()->e_args.e_segfault.s_addr);
		}
		assert_eq_msk(except_data()->e_args.e_segfault.s_context, exp_mask, exp_context);
	}
	return true;
}

PRIVATE void test_addr(void *addr, bool is_canon, bool is_vio) {
	unsigned int op;
	uintptr_t exp_canon = 0;
	if (!is_canon)
		exp_canon = E_SEGFAULT_CONTEXT_NONCANON;
	if (is_vio)
		exp_canon = E_SEGFAULT_CONTEXT_VIO;
	/* Make sure that the address isn't mapped */
	ctest_substatf("%p:begin", addr);
	TRY {
		p = *(uintptr_t *)addr;
		return;
	} EXCEPT {
		assert_except_code(E_SEGFAULT);
#ifndef __x86_64__
		/* Special case: The access test  for `0xbfffffff'  behaves slightly  different
		 *               when a memory mapping exists at `0xbffff000' (which can happen
		 *               randomly as the result of ASLR).
		 * When this happens, the 4-byte  access to `0xbfffffff' will not  actually
		 * fault, before then faulting for real when trying to access `0xc0000000'!
		 * If this happens, then the error can match what is checked here. */
		if (addr == (void *)UINT32_C(0xbfffffff)) {
			if (except_data()->e_args.e_segfault.s_addr == UINT32_C(0xc0000000) &&
			    except_data()->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_VIO)
				return;
		}
#endif /* !__x86_64__ */
		if (is_vio) {
			/* VIO dispatching may  try to access  multiple surrounding  bytes
			 * in order to service the request. Because of this, fault pointer
			 * may be scattered around the  actually accessed location by  the
			 * max # number of bytes on the data-bus minus 1 */
			assert_range(except_data()->e_args.e_segfault.s_addr, addr, WORDMASK);
		} else {
			EQ(addr, (void *)except_data()->e_args.e_segfault.s_addr);
		}
		assert_eq_msk(except_data()->e_args.e_segfault.s_context,
		              E_SEGFAULT_CONTEXT_NONCANON |
		              E_SEGFAULT_CONTEXT_VIO,
		              exp_canon);
	}
	for (op = 0;; ++op) {
		ctest_substatf("%p:%#x", addr, op);
		if (!test_addr_op(op, addr, is_canon, is_vio))
			break;
	}
}

DEFINE_TEST(segfault_special_addresses) {
	/* Prevent the UKERN segment from interfering. */
#if 0 /* QEMU  appears  to   emulate  _all_  0x8f   instructions  as   `pop'
       * (even  when  `modrm.mi_reg != 0'),  so the  kernel  can't intercept
       * any exception to  emulate the instruction,  and %cs:%(r)ip  becomes
       * unaligned since pop:0x8f/0 is shorter than the XOP that is actually
       * hidden within...
       * ... After  investigating the  issue, QEMU  does appear  to simply ignore
       *     the MODRM.REG field of the 0x8f opcode (and does so unconditionally)
       *     Furthermore a real machine (mine) raises a #UD exception when trying
       *     to execute something like 0x8f/1 (which is what the correct behavior
       *     would be, so on my machine KOS would emulate XOP).
       *     Sadly, I don't have an account for the QEMU bug tracker, and I don't
       *     feel like making one right now, so I'm going to leave it at that for
       *     the time being... */
	{
		unsigned int i;
		for (i = 0; i < 0xff; ++i) {
			unsigned int a, b;
			a = i & (i + 1);
			b = __blcfilll(i);
			assertf(a == b, "%#x == %#x", a, b);
		}
	}
#endif

#ifdef __x86_64__
	__wrgsbase((void *)UINT64_C(0xffff8000000ff000));
#else /* __x86_64__ */
	__wrfsbase((void *)UINT32_C(0xc00ff000));
#endif /* !__x86_64__ */

	/* Test memory access at the limits of user-, non-canon, and kernel-space. */
#ifdef __x86_64__
	test_addr((void *)UINT64_C(0x0000000000000000), true, false);  /* Min user-space address */
	test_addr((void *)UINT64_C(0x00007fffffffffff), true, false);  /* Max user-space address */
	test_addr((void *)UINT64_C(0x0000800000000000), false, false); /* Min non-canon address */
	test_addr((void *)UINT64_C(0xffff7fffffffffff), false, false); /* Max non-canon address */
	test_addr((void *)UINT64_C(0xffff800000000000), true, true);   /* Min kernel-space address */
	test_addr((void *)UINT64_C(0xffffffffffffffff), true, true);   /* Max kernel-space address */
#else /* __x86_64__ */
	test_addr((void *)UINT32_C(0x00000000), true, false); /* Min user-space address */
	test_addr((void *)UINT32_C(0xbfffffff), true, false); /* Max user-space address */
	test_addr((void *)UINT32_C(0xc0000000), true, true);  /* Min kernel-space address */
	test_addr((void *)UINT32_C(0xffffffff), true, true);  /* Max kernel-space address */
#endif /* !__x86_64__ */
}

DECL_END

#endif /* __x86_64__ || __i386__ */

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_FAULT_C */
