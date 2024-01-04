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
#ifndef __GUARD_HYBRID___ATOMIC_GASM_X86_H
#define __GUARD_HYBRID___ATOMIC_GASM_X86_H 1

#include "../__stdinc.h"
/**/

#include "host.h"
#include "typecore.h"

#ifndef __GUARD_HYBRID___ATOMIC_H
#error "Never include this file directly. - Always include `<hybrid/__atomic.h>' instead"
#endif /* !__GUARD_HYBRID___ATOMIC_H */

#ifndef __COMPILER_HAVE_GCC_ASM
#error "GCC Inline assembly is not supported"
#endif /* !__COMPILER_HAVE_GCC_ASM */

#define __HYBRID_ATOMIC_LOCKFREE_MAX 8

#ifdef __CC__
__DECL_BEGIN

/* clang-format off */
/*[[[deemon
import * from deemon;
global yXBlockFile = File.Writer();
global nXBlockFile = File.Writer();

function flushFiles() {
	print("#ifndef __NO_XBLOCK");
	print(yXBlockFile.string),;
	print("#else /" "* __NO_XBLOCK *" "/");
	print(nXBlockFile.string),;
	print("#endif /" "* !__NO_XBLOCK *" "/");
	yXBlockFile = File.Writer();
	nXBlockFile = File.Writer();
}

function defineX86Asm(returnType: string, name: string, args: {(string, string)...}, asm: string) {
	local n = none;
	for (local xn: ["8", "16", "32", "64"]) {
		if (xn in name) {
			n = xn;
			break;
		}
	}
	print yXBlockFile: ("#define ", name, "(", ", ".join(args.each.first), ") \\");
	print yXBlockFile: ("	__XBLOCK({ "),;
	if (returnType != "void") {
		print yXBlockFile: ("__register ", returnType, " __hacx", n, "_res; \\");
		print yXBlockFile: ("	           "),;
	}
	print yXBlockFile: (asm.rstrip()
			.replace("\n", " \\\n\t           ")
			.rereplace(r"\bres\b", f"__hacx{n}_res"),
		"; \\");
	if (returnType != "void") {
		print yXBlockFile: ("	           __XRETURN __hacx", n, "_res; })");
	} else {
		print yXBlockFile: ("	           (void)0; })");
	}
	print nXBlockFile: ("#define ", name, " ", name);
	print nXBlockFile: ("__LOCAL "),;
	if (returnType != "void")
		print nXBlockFile: ("__ATTR_WUNUSED "),;
	print nXBlockFile: ("__ATTR_NONNULL((1)) ", returnType);
	print nXBlockFile: ("(", name, ")(",
		", ".join(for (local name, typ: args) f"{typ}{typ.endswith("*") ? "" : " "}__{name}"),
		") {");
	if (returnType != "void")
		print nXBlockFile: ("	__register ", returnType, " __res;");
	local funAsm = asm.rstrip()
			.replace("\n", "\n\t")
			.rereplace(r"\bres\b", "__res");
	for (local name, none: args) {
		funAsm = funAsm
			.rereplace(f"\\b{name}\\b", f"__{name}");
	}
	print nXBlockFile: ("	", funAsm, ";");
	if (returnType != "void")
		print nXBlockFile: ("	return __res;");
	print nXBlockFile: ("}");
}

function fillX86Template(text: string, N: int): string {
	return text.format({
		"N"    : N,
		"bwlq" : { 8: "b", 16: "w", 32: "l", 64: "q" }[N]
	});
}

function defineX86AsmT(N: int, returnType: string, name: string, args: {(string, string)...}, asm: string) {
	local order = "order";
	if ("oldval" in args.each.first)
		order = "succ, fail";
	returnType = fillX86Template(returnType, N);
	name = fillX86Template(name, N);
	args = Tuple(for (local n, t: args) (fillX86Template(n, N), fillX86Template(t, N)));
	asm = fillX86Template(asm, N);
	print("#define ", name, "(", ", ".join(args.each.first), ", ", order, ") \\");
	print("	", name, "_seq_cst(", ", ".join(args.each.first), ")");
	defineX86Asm(returnType, name + "_seq_cst", args, asm);
}

function defineX86AtomicMacros(N: int) {
	// cmpxch_val
	defineX86AsmT(N, "__UINT{N}_TYPE__", "__hybrid_atomic_cmpxch_val{N}", [
		("ptr", "__UINT{N}_TYPE__ *"),
		("oldval", "__UINT{N}_TYPE__"),
		("newval", "__UINT{N}_TYPE__"),
	],
	'__asm__ __volatile__("lock; cmpxchg{bwlq} %2, %0\\n"\n'
	'                     : "+m" (*(ptr)), "=a" (res)\n'
	'                     : "r" (newval), "1" (oldval)\n'
	'                     : "memory", "cc")');

	// cmpxch
	defineX86AsmT(N, "__BOOL", "__hybrid_atomic_cmpxch{N}", [
		("ptr", "__UINT{N}_TYPE__ *"),
		("oldval", "__UINT{N}_TYPE__"),
		("newval", "__UINT{N}_TYPE__"),
	],
	'__asm__ __volatile__("lock; cmpxchg{bwlq} %2, %0\\n"\n'
	'                     : "+m" (*(ptr)), "=@cceq" (res)\n'
	'                     : "r" (newval), "a" (oldval)\n'
	'                     : "memory", "cc")');

	// load
	defineX86AsmT(N, "__UINT{N}_TYPE__", "__hybrid_atomic_load{N}", [
		("ptr", "__UINT{N}_TYPE__ const *"),
	],
	'__COMPILER_READ_BARRIER();\n'
	'__asm__ __volatile__("mov{bwlq} %1, %0\\n"\n'
	'                     : "=r" (res)\n'
	'                     : "m" (*(ptr))\n'
	'                     : "memory")');

	// store
	defineX86AsmT(N, "void", "__hybrid_atomic_store{N}", [
		("ptr", "__UINT{N}_TYPE__ *"),
		("val", "__UINT{N}_TYPE__"),
	],
	'__asm__ __volatile__("mov{bwlq} %1, %0\\n"\n'
	'                     : "=m" (*(ptr))\n'
	'                     : "r" (val)\n'
	'                     : "memory");\n'
	'__COMPILER_WRITE_BARRIER()');

	// xch
	defineX86AsmT(N, "__UINT{N}_TYPE__", "__hybrid_atomic_xch{N}", [
		("ptr", "__UINT{N}_TYPE__ *"),
		("val", "__UINT{N}_TYPE__"),
	],
	'__asm__ __volatile__("xchg{bwlq} %1, %0\\n"\n' // A lock-prefix is unnecessary; xchg is always atomic
	'                     : "+m" (*(ptr))\n'
	'                     , "=r" (res)\n'
	'                     : "1" (val)\n'
	'                     : "memory")');

	// fetchadd
	defineX86AsmT(N, "__UINT{N}_TYPE__", "__hybrid_atomic_fetchadd{N}", [
		("ptr", "__UINT{N}_TYPE__ *"),
		("val", "__UINT{N}_TYPE__"),
	],
	'__asm__ __volatile__("lock; xadd{bwlq} %1, %0\\n"\n'
	'                     : "+m" (*(ptr))\n'
	'                     , "=r" (res)\n'
	'                     : "1" (val)\n'
	'                     : "memory", "cc")');

	function defineX86VoidUnaryOperation(name: string) {
		defineX86AsmT(N, "void", "__hybrid_atomic_" + name + "{N}", [
			("ptr", "__UINT{N}_TYPE__ *")
		],
		'__asm__ __volatile__("lock; ' + name + '{bwlq} %0\\n"\n'
		'                     : "+m" (*(ptr)) : : "memory", "cc")');
	}

	function defineX86VoidBinaryOperation(name: string) {
		defineX86AsmT(N, "void", "__hybrid_atomic_" + name + "{N}", [
			("ptr", "__UINT{N}_TYPE__ *"),
			("val", "__UINT{N}_TYPE__"),
		],
		'__asm__ __volatile__("lock; ' + name + '{bwlq} %1, %0\\n"\n'
		'                     : "+m" (*(ptr))\n'
		'                     : "r" (val)\n'
		'                     : "memory", "cc")');
	}

	defineX86VoidUnaryOperation("inc");
	defineX86VoidUnaryOperation("dec");
	defineX86VoidBinaryOperation("add");
	defineX86VoidBinaryOperation("sub");
	defineX86VoidBinaryOperation("and");
	defineX86VoidBinaryOperation("or");
	defineX86VoidBinaryOperation("xor");
}



defineX86AtomicMacros(8);
defineX86AtomicMacros(16);
defineX86AtomicMacros(32);
flushFiles();
print("#ifdef __x86_64__");
defineX86AtomicMacros(64);
flushFiles();
print("#else /" "* __x86_64__ *" "/");
print("#define __hybrid_atomic_cmpxch_val64(ptr, oldval, newval, succ, fail) \\");
print("	__hybrid_atomic_cmpxch_val64_seq_cst(ptr, oldval, newval)");
print("#define __hybrid_atomic_cmpxch64(ptr, oldval, newval, succ, fail) \\");
print("	__hybrid_atomic_cmpxch64_seq_cst(ptr, oldval, newval)");
print("#ifndef __NO_XBLOCK");
print("#define __hybrid_atomic_cmpxch_val64_seq_cst(ptr, oldval, newval) \\");
print("	__XBLOCK({ \\");
print("		__register __UINT64_TYPE__ __hacx64_res; \\");
print("		__register __UINT64_TYPE__ __hacx64_nv = (newval); \\");
print('		__asm__ __volatile__("lock; cmpxchg8b %0\\n" \\');
print('		                     : "+m" (*(ptr)), "=A" (__hacx64_res) \\');
print('		                     : "A" (oldval) \\');
print('		                     , "c" ((__UINT32_TYPE__)((__UINT64_TYPE__)__hacx64_nv >> 32)) \\');
print('		                     , "b" ((__UINT32_TYPE__)(__UINT64_TYPE__)__hacx64_nv) \\');
print('		                     : "memory", "cc"); \\');
print("		__XRETURN __hacx64_res; \\");
print("	})");
print("#define __hybrid_atomic_cmpxch64_seq_cst(ptr, oldval, newval) \\");
print("	__XBLOCK({ \\");
print("		__register __BOOL __hacx64_res; \\");
print("		__register __UINT64_TYPE__ __hacx64_nv = (newval); \\");
print('		__asm__ __volatile__("lock; cmpxchg8b %0\\n" \\');
print('		                     : "+m" (*(ptr)), "=@cceq" (__hacx64_res) \\');
print('		                     : "A" (oldval) \\');
print('		                     , "c" ((__UINT32_TYPE__)((__UINT64_TYPE__)__hacx64_nv >> 32)) \\');
print('		                     , "b" ((__UINT32_TYPE__)(__UINT64_TYPE__)__hacx64_nv) \\');
print('		                     : "memory", "cc"); \\');
print("		__XRETURN __hacx64_res; \\");
print("	})");
print("#else /" "* __NO_XBLOCK *" "/");
print("#define __hybrid_atomic_cmpxch_val64_seq_cst __hybrid_atomic_cmpxch_val64_seq_cst");
print("__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__");
print("(__hybrid_atomic_cmpxch_val64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval) {");
print("	__register __UINT64_TYPE__ __res;");
print('	__asm__ __volatile__("lock; cmpxchg8b %0\\n"');
print('	                     : "+m" (*__ptr)');
print('	                     : "=A" (__res)');
print('	                     : "1" (__oldval)');
print('	                     , "c" ((__UINT32_TYPE__)((__UINT64_TYPE__)__newval >> 32))');
print('	                     , "b" ((__UINT32_TYPE__)(__UINT64_TYPE__)__newval)');
print('	                     : "memory", "cc");');
print("	return __res;");
print("}");
print("#define __hybrid_atomic_cmpxch64_seq_cst __hybrid_atomic_cmpxch64_seq_cst");
print("__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL");
print("(__hybrid_atomic_cmpxch64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval) {");
print("	__register __BOOL __res;");
print('	__asm__ __volatile__("lock; cmpxchg8b %0\\n"');
print('	                     : "+m" (*__ptr), "=@cceq" (__res)');
print('	                     : "A" (__oldval)');
print('	                     : "c" ((__UINT32_TYPE__)((__UINT64_TYPE__)__newval >> 32))');
print('	                     , "b" ((__UINT32_TYPE__)(__UINT64_TYPE__)__newval)');
print('	                     : "memory", "cc");');
print("	return __res;");
print("}");
print("#endif /" "* !__NO_XBLOCK *" "/");
print("#endif /" "* !__x86_64__ *" "/");

]]]*/
#define __hybrid_atomic_cmpxch_val8(ptr, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch_val8_seq_cst(ptr, oldval, newval)
#define __hybrid_atomic_cmpxch8(ptr, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch8_seq_cst(ptr, oldval, newval)
#define __hybrid_atomic_load8(ptr, order) \
	__hybrid_atomic_load8_seq_cst(ptr)
#define __hybrid_atomic_store8(ptr, val, order) \
	__hybrid_atomic_store8_seq_cst(ptr, val)
#define __hybrid_atomic_xch8(ptr, val, order) \
	__hybrid_atomic_xch8_seq_cst(ptr, val)
#define __hybrid_atomic_fetchadd8(ptr, val, order) \
	__hybrid_atomic_fetchadd8_seq_cst(ptr, val)
#define __hybrid_atomic_inc8(ptr, order) \
	__hybrid_atomic_inc8_seq_cst(ptr)
#define __hybrid_atomic_dec8(ptr, order) \
	__hybrid_atomic_dec8_seq_cst(ptr)
#define __hybrid_atomic_add8(ptr, val, order) \
	__hybrid_atomic_add8_seq_cst(ptr, val)
#define __hybrid_atomic_sub8(ptr, val, order) \
	__hybrid_atomic_sub8_seq_cst(ptr, val)
#define __hybrid_atomic_and8(ptr, val, order) \
	__hybrid_atomic_and8_seq_cst(ptr, val)
#define __hybrid_atomic_or8(ptr, val, order) \
	__hybrid_atomic_or8_seq_cst(ptr, val)
#define __hybrid_atomic_xor8(ptr, val, order) \
	__hybrid_atomic_xor8_seq_cst(ptr, val)
#define __hybrid_atomic_cmpxch_val16(ptr, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch_val16_seq_cst(ptr, oldval, newval)
#define __hybrid_atomic_cmpxch16(ptr, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch16_seq_cst(ptr, oldval, newval)
#define __hybrid_atomic_load16(ptr, order) \
	__hybrid_atomic_load16_seq_cst(ptr)
#define __hybrid_atomic_store16(ptr, val, order) \
	__hybrid_atomic_store16_seq_cst(ptr, val)
#define __hybrid_atomic_xch16(ptr, val, order) \
	__hybrid_atomic_xch16_seq_cst(ptr, val)
#define __hybrid_atomic_fetchadd16(ptr, val, order) \
	__hybrid_atomic_fetchadd16_seq_cst(ptr, val)
#define __hybrid_atomic_inc16(ptr, order) \
	__hybrid_atomic_inc16_seq_cst(ptr)
#define __hybrid_atomic_dec16(ptr, order) \
	__hybrid_atomic_dec16_seq_cst(ptr)
#define __hybrid_atomic_add16(ptr, val, order) \
	__hybrid_atomic_add16_seq_cst(ptr, val)
#define __hybrid_atomic_sub16(ptr, val, order) \
	__hybrid_atomic_sub16_seq_cst(ptr, val)
#define __hybrid_atomic_and16(ptr, val, order) \
	__hybrid_atomic_and16_seq_cst(ptr, val)
#define __hybrid_atomic_or16(ptr, val, order) \
	__hybrid_atomic_or16_seq_cst(ptr, val)
#define __hybrid_atomic_xor16(ptr, val, order) \
	__hybrid_atomic_xor16_seq_cst(ptr, val)
#define __hybrid_atomic_cmpxch_val32(ptr, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch_val32_seq_cst(ptr, oldval, newval)
#define __hybrid_atomic_cmpxch32(ptr, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch32_seq_cst(ptr, oldval, newval)
#define __hybrid_atomic_load32(ptr, order) \
	__hybrid_atomic_load32_seq_cst(ptr)
#define __hybrid_atomic_store32(ptr, val, order) \
	__hybrid_atomic_store32_seq_cst(ptr, val)
#define __hybrid_atomic_xch32(ptr, val, order) \
	__hybrid_atomic_xch32_seq_cst(ptr, val)
#define __hybrid_atomic_fetchadd32(ptr, val, order) \
	__hybrid_atomic_fetchadd32_seq_cst(ptr, val)
#define __hybrid_atomic_inc32(ptr, order) \
	__hybrid_atomic_inc32_seq_cst(ptr)
#define __hybrid_atomic_dec32(ptr, order) \
	__hybrid_atomic_dec32_seq_cst(ptr)
#define __hybrid_atomic_add32(ptr, val, order) \
	__hybrid_atomic_add32_seq_cst(ptr, val)
#define __hybrid_atomic_sub32(ptr, val, order) \
	__hybrid_atomic_sub32_seq_cst(ptr, val)
#define __hybrid_atomic_and32(ptr, val, order) \
	__hybrid_atomic_and32_seq_cst(ptr, val)
#define __hybrid_atomic_or32(ptr, val, order) \
	__hybrid_atomic_or32_seq_cst(ptr, val)
#define __hybrid_atomic_xor32(ptr, val, order) \
	__hybrid_atomic_xor32_seq_cst(ptr, val)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch_val8_seq_cst(ptr, oldval, newval) \
	__XBLOCK({ __register __UINT8_TYPE__ __hacx8_res; \
	           __asm__ __volatile__("lock; cmpxchgb %2, %0\n" \
	                                : "+m" (*(ptr)), "=a" (__hacx8_res) \
	                                : "r" (newval), "1" (oldval) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx8_res; })
#define __hybrid_atomic_cmpxch8_seq_cst(ptr, oldval, newval) \
	__XBLOCK({ __register __BOOL __hacx8_res; \
	           __asm__ __volatile__("lock; cmpxchgb %2, %0\n" \
	                                : "+m" (*(ptr)), "=@cceq" (__hacx8_res) \
	                                : "r" (newval), "a" (oldval) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx8_res; })
#define __hybrid_atomic_load8_seq_cst(ptr) \
	__XBLOCK({ __register __UINT8_TYPE__ __hacx8_res; \
	           __COMPILER_READ_BARRIER(); \
	           __asm__ __volatile__("movb %1, %0\n" \
	                                : "=r" (__hacx8_res) \
	                                : "m" (*(ptr)) \
	                                : "memory"); \
	           __XRETURN __hacx8_res; })
#define __hybrid_atomic_store8_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("movb %1, %0\n" \
	                                : "=m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory"); \
	           __COMPILER_WRITE_BARRIER(); \
	           (void)0; })
#define __hybrid_atomic_xch8_seq_cst(ptr, val) \
	__XBLOCK({ __register __UINT8_TYPE__ __hacx8_res; \
	           __asm__ __volatile__("xchgb %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                , "=r" (__hacx8_res) \
	                                : "1" (val) \
	                                : "memory"); \
	           __XRETURN __hacx8_res; })
#define __hybrid_atomic_fetchadd8_seq_cst(ptr, val) \
	__XBLOCK({ __register __UINT8_TYPE__ __hacx8_res; \
	           __asm__ __volatile__("lock; xaddb %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                , "=r" (__hacx8_res) \
	                                : "1" (val) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx8_res; })
#define __hybrid_atomic_inc8_seq_cst(ptr) \
	__XBLOCK({ __asm__ __volatile__("lock; incb %0\n" \
	                                : "+m" (*(ptr)) : : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_dec8_seq_cst(ptr) \
	__XBLOCK({ __asm__ __volatile__("lock; decb %0\n" \
	                                : "+m" (*(ptr)) : : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_add8_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; addb %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_sub8_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; subb %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_and8_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; andb %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_or8_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; orb %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_xor8_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; xorb %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_cmpxch_val16_seq_cst(ptr, oldval, newval) \
	__XBLOCK({ __register __UINT16_TYPE__ __hacx16_res; \
	           __asm__ __volatile__("lock; cmpxchgw %2, %0\n" \
	                                : "+m" (*(ptr)), "=a" (__hacx16_res) \
	                                : "r" (newval), "1" (oldval) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx16_res; })
#define __hybrid_atomic_cmpxch16_seq_cst(ptr, oldval, newval) \
	__XBLOCK({ __register __BOOL __hacx16_res; \
	           __asm__ __volatile__("lock; cmpxchgw %2, %0\n" \
	                                : "+m" (*(ptr)), "=@cceq" (__hacx16_res) \
	                                : "r" (newval), "a" (oldval) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx16_res; })
#define __hybrid_atomic_load16_seq_cst(ptr) \
	__XBLOCK({ __register __UINT16_TYPE__ __hacx16_res; \
	           __COMPILER_READ_BARRIER(); \
	           __asm__ __volatile__("movw %1, %0\n" \
	                                : "=r" (__hacx16_res) \
	                                : "m" (*(ptr)) \
	                                : "memory"); \
	           __XRETURN __hacx16_res; })
#define __hybrid_atomic_store16_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("movw %1, %0\n" \
	                                : "=m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory"); \
	           __COMPILER_WRITE_BARRIER(); \
	           (void)0; })
#define __hybrid_atomic_xch16_seq_cst(ptr, val) \
	__XBLOCK({ __register __UINT16_TYPE__ __hacx16_res; \
	           __asm__ __volatile__("xchgw %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                , "=r" (__hacx16_res) \
	                                : "1" (val) \
	                                : "memory"); \
	           __XRETURN __hacx16_res; })
#define __hybrid_atomic_fetchadd16_seq_cst(ptr, val) \
	__XBLOCK({ __register __UINT16_TYPE__ __hacx16_res; \
	           __asm__ __volatile__("lock; xaddw %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                , "=r" (__hacx16_res) \
	                                : "1" (val) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx16_res; })
#define __hybrid_atomic_inc16_seq_cst(ptr) \
	__XBLOCK({ __asm__ __volatile__("lock; incw %0\n" \
	                                : "+m" (*(ptr)) : : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_dec16_seq_cst(ptr) \
	__XBLOCK({ __asm__ __volatile__("lock; decw %0\n" \
	                                : "+m" (*(ptr)) : : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_add16_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; addw %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_sub16_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; subw %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_and16_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; andw %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_or16_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; orw %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_xor16_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; xorw %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_cmpxch_val32_seq_cst(ptr, oldval, newval) \
	__XBLOCK({ __register __UINT32_TYPE__ __hacx32_res; \
	           __asm__ __volatile__("lock; cmpxchgl %2, %0\n" \
	                                : "+m" (*(ptr)), "=a" (__hacx32_res) \
	                                : "r" (newval), "1" (oldval) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx32_res; })
#define __hybrid_atomic_cmpxch32_seq_cst(ptr, oldval, newval) \
	__XBLOCK({ __register __BOOL __hacx32_res; \
	           __asm__ __volatile__("lock; cmpxchgl %2, %0\n" \
	                                : "+m" (*(ptr)), "=@cceq" (__hacx32_res) \
	                                : "r" (newval), "a" (oldval) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx32_res; })
#define __hybrid_atomic_load32_seq_cst(ptr) \
	__XBLOCK({ __register __UINT32_TYPE__ __hacx32_res; \
	           __COMPILER_READ_BARRIER(); \
	           __asm__ __volatile__("movl %1, %0\n" \
	                                : "=r" (__hacx32_res) \
	                                : "m" (*(ptr)) \
	                                : "memory"); \
	           __XRETURN __hacx32_res; })
#define __hybrid_atomic_store32_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("movl %1, %0\n" \
	                                : "=m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory"); \
	           __COMPILER_WRITE_BARRIER(); \
	           (void)0; })
#define __hybrid_atomic_xch32_seq_cst(ptr, val) \
	__XBLOCK({ __register __UINT32_TYPE__ __hacx32_res; \
	           __asm__ __volatile__("xchgl %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                , "=r" (__hacx32_res) \
	                                : "1" (val) \
	                                : "memory"); \
	           __XRETURN __hacx32_res; })
#define __hybrid_atomic_fetchadd32_seq_cst(ptr, val) \
	__XBLOCK({ __register __UINT32_TYPE__ __hacx32_res; \
	           __asm__ __volatile__("lock; xaddl %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                , "=r" (__hacx32_res) \
	                                : "1" (val) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx32_res; })
#define __hybrid_atomic_inc32_seq_cst(ptr) \
	__XBLOCK({ __asm__ __volatile__("lock; incl %0\n" \
	                                : "+m" (*(ptr)) : : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_dec32_seq_cst(ptr) \
	__XBLOCK({ __asm__ __volatile__("lock; decl %0\n" \
	                                : "+m" (*(ptr)) : : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_add32_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; addl %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_sub32_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; subl %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_and32_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; andl %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_or32_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; orl %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_xor32_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; xorl %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch_val8_seq_cst __hybrid_atomic_cmpxch_val8_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__
(__hybrid_atomic_cmpxch_val8_seq_cst)(__UINT8_TYPE__ *__ptr, __UINT8_TYPE__ __oldval, __UINT8_TYPE__ __newval) {
	__register __UINT8_TYPE__ __res;
	__asm__ __volatile__("lock; cmpxchgb %2, %0\n"
	                     : "+m" (*(__ptr)), "=a" (__res)
	                     : "r" (__newval), "1" (__oldval)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_cmpxch8_seq_cst __hybrid_atomic_cmpxch8_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
(__hybrid_atomic_cmpxch8_seq_cst)(__UINT8_TYPE__ *__ptr, __UINT8_TYPE__ __oldval, __UINT8_TYPE__ __newval) {
	__register __BOOL __res;
	__asm__ __volatile__("lock; cmpxchgb %2, %0\n"
	                     : "+m" (*(__ptr)), "=@cceq" (__res)
	                     : "r" (__newval), "a" (__oldval)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_load8_seq_cst __hybrid_atomic_load8_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__
(__hybrid_atomic_load8_seq_cst)(__UINT8_TYPE__ const *__ptr) {
	__register __UINT8_TYPE__ __res;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movb %1, %0\n"
	                     : "=r" (__res)
	                     : "m" (*(__ptr))
	                     : "memory");
	return __res;
}
#define __hybrid_atomic_store8_seq_cst __hybrid_atomic_store8_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_store8_seq_cst)(__UINT8_TYPE__ *__ptr, __UINT8_TYPE__ __val) {
	__asm__ __volatile__("movb %1, %0\n"
	                     : "=m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory");
	__COMPILER_WRITE_BARRIER();
}
#define __hybrid_atomic_xch8_seq_cst __hybrid_atomic_xch8_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__
(__hybrid_atomic_xch8_seq_cst)(__UINT8_TYPE__ *__ptr, __UINT8_TYPE__ __val) {
	__register __UINT8_TYPE__ __res;
	__asm__ __volatile__("xchgb %1, %0\n"
	                     : "+m" (*(__ptr))
	                     , "=r" (__res)
	                     : "1" (__val)
	                     : "memory");
	return __res;
}
#define __hybrid_atomic_fetchadd8_seq_cst __hybrid_atomic_fetchadd8_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__
(__hybrid_atomic_fetchadd8_seq_cst)(__UINT8_TYPE__ *__ptr, __UINT8_TYPE__ __val) {
	__register __UINT8_TYPE__ __res;
	__asm__ __volatile__("lock; xaddb %1, %0\n"
	                     : "+m" (*(__ptr))
	                     , "=r" (__res)
	                     : "1" (__val)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_inc8_seq_cst __hybrid_atomic_inc8_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_inc8_seq_cst)(__UINT8_TYPE__ *__ptr) {
	__asm__ __volatile__("lock; incb %0\n"
	                     : "+m" (*(__ptr)) : : "memory", "cc");
}
#define __hybrid_atomic_dec8_seq_cst __hybrid_atomic_dec8_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_dec8_seq_cst)(__UINT8_TYPE__ *__ptr) {
	__asm__ __volatile__("lock; decb %0\n"
	                     : "+m" (*(__ptr)) : : "memory", "cc");
}
#define __hybrid_atomic_add8_seq_cst __hybrid_atomic_add8_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_add8_seq_cst)(__UINT8_TYPE__ *__ptr, __UINT8_TYPE__ __val) {
	__asm__ __volatile__("lock; addb %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_sub8_seq_cst __hybrid_atomic_sub8_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_sub8_seq_cst)(__UINT8_TYPE__ *__ptr, __UINT8_TYPE__ __val) {
	__asm__ __volatile__("lock; subb %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_and8_seq_cst __hybrid_atomic_and8_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_and8_seq_cst)(__UINT8_TYPE__ *__ptr, __UINT8_TYPE__ __val) {
	__asm__ __volatile__("lock; andb %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_or8_seq_cst __hybrid_atomic_or8_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_or8_seq_cst)(__UINT8_TYPE__ *__ptr, __UINT8_TYPE__ __val) {
	__asm__ __volatile__("lock; orb %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_xor8_seq_cst __hybrid_atomic_xor8_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_xor8_seq_cst)(__UINT8_TYPE__ *__ptr, __UINT8_TYPE__ __val) {
	__asm__ __volatile__("lock; xorb %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_cmpxch_val16_seq_cst __hybrid_atomic_cmpxch_val16_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
(__hybrid_atomic_cmpxch_val16_seq_cst)(__UINT16_TYPE__ *__ptr, __UINT16_TYPE__ __oldval, __UINT16_TYPE__ __newval) {
	__register __UINT16_TYPE__ __res;
	__asm__ __volatile__("lock; cmpxchgw %2, %0\n"
	                     : "+m" (*(__ptr)), "=a" (__res)
	                     : "r" (__newval), "1" (__oldval)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_cmpxch16_seq_cst __hybrid_atomic_cmpxch16_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
(__hybrid_atomic_cmpxch16_seq_cst)(__UINT16_TYPE__ *__ptr, __UINT16_TYPE__ __oldval, __UINT16_TYPE__ __newval) {
	__register __BOOL __res;
	__asm__ __volatile__("lock; cmpxchgw %2, %0\n"
	                     : "+m" (*(__ptr)), "=@cceq" (__res)
	                     : "r" (__newval), "a" (__oldval)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_load16_seq_cst __hybrid_atomic_load16_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
(__hybrid_atomic_load16_seq_cst)(__UINT16_TYPE__ const *__ptr) {
	__register __UINT16_TYPE__ __res;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movw %1, %0\n"
	                     : "=r" (__res)
	                     : "m" (*(__ptr))
	                     : "memory");
	return __res;
}
#define __hybrid_atomic_store16_seq_cst __hybrid_atomic_store16_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_store16_seq_cst)(__UINT16_TYPE__ *__ptr, __UINT16_TYPE__ __val) {
	__asm__ __volatile__("movw %1, %0\n"
	                     : "=m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory");
	__COMPILER_WRITE_BARRIER();
}
#define __hybrid_atomic_xch16_seq_cst __hybrid_atomic_xch16_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
(__hybrid_atomic_xch16_seq_cst)(__UINT16_TYPE__ *__ptr, __UINT16_TYPE__ __val) {
	__register __UINT16_TYPE__ __res;
	__asm__ __volatile__("xchgw %1, %0\n"
	                     : "+m" (*(__ptr))
	                     , "=r" (__res)
	                     : "1" (__val)
	                     : "memory");
	return __res;
}
#define __hybrid_atomic_fetchadd16_seq_cst __hybrid_atomic_fetchadd16_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__
(__hybrid_atomic_fetchadd16_seq_cst)(__UINT16_TYPE__ *__ptr, __UINT16_TYPE__ __val) {
	__register __UINT16_TYPE__ __res;
	__asm__ __volatile__("lock; xaddw %1, %0\n"
	                     : "+m" (*(__ptr))
	                     , "=r" (__res)
	                     : "1" (__val)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_inc16_seq_cst __hybrid_atomic_inc16_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_inc16_seq_cst)(__UINT16_TYPE__ *__ptr) {
	__asm__ __volatile__("lock; incw %0\n"
	                     : "+m" (*(__ptr)) : : "memory", "cc");
}
#define __hybrid_atomic_dec16_seq_cst __hybrid_atomic_dec16_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_dec16_seq_cst)(__UINT16_TYPE__ *__ptr) {
	__asm__ __volatile__("lock; decw %0\n"
	                     : "+m" (*(__ptr)) : : "memory", "cc");
}
#define __hybrid_atomic_add16_seq_cst __hybrid_atomic_add16_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_add16_seq_cst)(__UINT16_TYPE__ *__ptr, __UINT16_TYPE__ __val) {
	__asm__ __volatile__("lock; addw %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_sub16_seq_cst __hybrid_atomic_sub16_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_sub16_seq_cst)(__UINT16_TYPE__ *__ptr, __UINT16_TYPE__ __val) {
	__asm__ __volatile__("lock; subw %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_and16_seq_cst __hybrid_atomic_and16_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_and16_seq_cst)(__UINT16_TYPE__ *__ptr, __UINT16_TYPE__ __val) {
	__asm__ __volatile__("lock; andw %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_or16_seq_cst __hybrid_atomic_or16_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_or16_seq_cst)(__UINT16_TYPE__ *__ptr, __UINT16_TYPE__ __val) {
	__asm__ __volatile__("lock; orw %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_xor16_seq_cst __hybrid_atomic_xor16_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_xor16_seq_cst)(__UINT16_TYPE__ *__ptr, __UINT16_TYPE__ __val) {
	__asm__ __volatile__("lock; xorw %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_cmpxch_val32_seq_cst __hybrid_atomic_cmpxch_val32_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
(__hybrid_atomic_cmpxch_val32_seq_cst)(__UINT32_TYPE__ *__ptr, __UINT32_TYPE__ __oldval, __UINT32_TYPE__ __newval) {
	__register __UINT32_TYPE__ __res;
	__asm__ __volatile__("lock; cmpxchgl %2, %0\n"
	                     : "+m" (*(__ptr)), "=a" (__res)
	                     : "r" (__newval), "1" (__oldval)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_cmpxch32_seq_cst __hybrid_atomic_cmpxch32_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
(__hybrid_atomic_cmpxch32_seq_cst)(__UINT32_TYPE__ *__ptr, __UINT32_TYPE__ __oldval, __UINT32_TYPE__ __newval) {
	__register __BOOL __res;
	__asm__ __volatile__("lock; cmpxchgl %2, %0\n"
	                     : "+m" (*(__ptr)), "=@cceq" (__res)
	                     : "r" (__newval), "a" (__oldval)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_load32_seq_cst __hybrid_atomic_load32_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
(__hybrid_atomic_load32_seq_cst)(__UINT32_TYPE__ const *__ptr) {
	__register __UINT32_TYPE__ __res;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movl %1, %0\n"
	                     : "=r" (__res)
	                     : "m" (*(__ptr))
	                     : "memory");
	return __res;
}
#define __hybrid_atomic_store32_seq_cst __hybrid_atomic_store32_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_store32_seq_cst)(__UINT32_TYPE__ *__ptr, __UINT32_TYPE__ __val) {
	__asm__ __volatile__("movl %1, %0\n"
	                     : "=m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory");
	__COMPILER_WRITE_BARRIER();
}
#define __hybrid_atomic_xch32_seq_cst __hybrid_atomic_xch32_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
(__hybrid_atomic_xch32_seq_cst)(__UINT32_TYPE__ *__ptr, __UINT32_TYPE__ __val) {
	__register __UINT32_TYPE__ __res;
	__asm__ __volatile__("xchgl %1, %0\n"
	                     : "+m" (*(__ptr))
	                     , "=r" (__res)
	                     : "1" (__val)
	                     : "memory");
	return __res;
}
#define __hybrid_atomic_fetchadd32_seq_cst __hybrid_atomic_fetchadd32_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__
(__hybrid_atomic_fetchadd32_seq_cst)(__UINT32_TYPE__ *__ptr, __UINT32_TYPE__ __val) {
	__register __UINT32_TYPE__ __res;
	__asm__ __volatile__("lock; xaddl %1, %0\n"
	                     : "+m" (*(__ptr))
	                     , "=r" (__res)
	                     : "1" (__val)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_inc32_seq_cst __hybrid_atomic_inc32_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_inc32_seq_cst)(__UINT32_TYPE__ *__ptr) {
	__asm__ __volatile__("lock; incl %0\n"
	                     : "+m" (*(__ptr)) : : "memory", "cc");
}
#define __hybrid_atomic_dec32_seq_cst __hybrid_atomic_dec32_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_dec32_seq_cst)(__UINT32_TYPE__ *__ptr) {
	__asm__ __volatile__("lock; decl %0\n"
	                     : "+m" (*(__ptr)) : : "memory", "cc");
}
#define __hybrid_atomic_add32_seq_cst __hybrid_atomic_add32_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_add32_seq_cst)(__UINT32_TYPE__ *__ptr, __UINT32_TYPE__ __val) {
	__asm__ __volatile__("lock; addl %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_sub32_seq_cst __hybrid_atomic_sub32_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_sub32_seq_cst)(__UINT32_TYPE__ *__ptr, __UINT32_TYPE__ __val) {
	__asm__ __volatile__("lock; subl %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_and32_seq_cst __hybrid_atomic_and32_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_and32_seq_cst)(__UINT32_TYPE__ *__ptr, __UINT32_TYPE__ __val) {
	__asm__ __volatile__("lock; andl %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_or32_seq_cst __hybrid_atomic_or32_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_or32_seq_cst)(__UINT32_TYPE__ *__ptr, __UINT32_TYPE__ __val) {
	__asm__ __volatile__("lock; orl %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_xor32_seq_cst __hybrid_atomic_xor32_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_xor32_seq_cst)(__UINT32_TYPE__ *__ptr, __UINT32_TYPE__ __val) {
	__asm__ __volatile__("lock; xorl %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#endif /* !__NO_XBLOCK */
#ifdef __x86_64__
#define __hybrid_atomic_cmpxch_val64(ptr, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch_val64_seq_cst(ptr, oldval, newval)
#define __hybrid_atomic_cmpxch64(ptr, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch64_seq_cst(ptr, oldval, newval)
#define __hybrid_atomic_load64(ptr, order) \
	__hybrid_atomic_load64_seq_cst(ptr)
#define __hybrid_atomic_store64(ptr, val, order) \
	__hybrid_atomic_store64_seq_cst(ptr, val)
#define __hybrid_atomic_xch64(ptr, val, order) \
	__hybrid_atomic_xch64_seq_cst(ptr, val)
#define __hybrid_atomic_fetchadd64(ptr, val, order) \
	__hybrid_atomic_fetchadd64_seq_cst(ptr, val)
#define __hybrid_atomic_inc64(ptr, order) \
	__hybrid_atomic_inc64_seq_cst(ptr)
#define __hybrid_atomic_dec64(ptr, order) \
	__hybrid_atomic_dec64_seq_cst(ptr)
#define __hybrid_atomic_add64(ptr, val, order) \
	__hybrid_atomic_add64_seq_cst(ptr, val)
#define __hybrid_atomic_sub64(ptr, val, order) \
	__hybrid_atomic_sub64_seq_cst(ptr, val)
#define __hybrid_atomic_and64(ptr, val, order) \
	__hybrid_atomic_and64_seq_cst(ptr, val)
#define __hybrid_atomic_or64(ptr, val, order) \
	__hybrid_atomic_or64_seq_cst(ptr, val)
#define __hybrid_atomic_xor64(ptr, val, order) \
	__hybrid_atomic_xor64_seq_cst(ptr, val)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch_val64_seq_cst(ptr, oldval, newval) \
	__XBLOCK({ __register __UINT64_TYPE__ __hacx64_res; \
	           __asm__ __volatile__("lock; cmpxchgq %2, %0\n" \
	                                : "+m" (*(ptr)), "=a" (__hacx64_res) \
	                                : "r" (newval), "1" (oldval) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx64_res; })
#define __hybrid_atomic_cmpxch64_seq_cst(ptr, oldval, newval) \
	__XBLOCK({ __register __BOOL __hacx64_res; \
	           __asm__ __volatile__("lock; cmpxchgq %2, %0\n" \
	                                : "+m" (*(ptr)), "=@cceq" (__hacx64_res) \
	                                : "r" (newval), "a" (oldval) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx64_res; })
#define __hybrid_atomic_load64_seq_cst(ptr) \
	__XBLOCK({ __register __UINT64_TYPE__ __hacx64_res; \
	           __COMPILER_READ_BARRIER(); \
	           __asm__ __volatile__("movq %1, %0\n" \
	                                : "=r" (__hacx64_res) \
	                                : "m" (*(ptr)) \
	                                : "memory"); \
	           __XRETURN __hacx64_res; })
#define __hybrid_atomic_store64_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("movq %1, %0\n" \
	                                : "=m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory"); \
	           __COMPILER_WRITE_BARRIER(); \
	           (void)0; })
#define __hybrid_atomic_xch64_seq_cst(ptr, val) \
	__XBLOCK({ __register __UINT64_TYPE__ __hacx64_res; \
	           __asm__ __volatile__("xchgq %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                , "=r" (__hacx64_res) \
	                                : "1" (val) \
	                                : "memory"); \
	           __XRETURN __hacx64_res; })
#define __hybrid_atomic_fetchadd64_seq_cst(ptr, val) \
	__XBLOCK({ __register __UINT64_TYPE__ __hacx64_res; \
	           __asm__ __volatile__("lock; xaddq %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                , "=r" (__hacx64_res) \
	                                : "1" (val) \
	                                : "memory", "cc"); \
	           __XRETURN __hacx64_res; })
#define __hybrid_atomic_inc64_seq_cst(ptr) \
	__XBLOCK({ __asm__ __volatile__("lock; incq %0\n" \
	                                : "+m" (*(ptr)) : : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_dec64_seq_cst(ptr) \
	__XBLOCK({ __asm__ __volatile__("lock; decq %0\n" \
	                                : "+m" (*(ptr)) : : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_add64_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; addq %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_sub64_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; subq %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_and64_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; andq %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_or64_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; orq %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#define __hybrid_atomic_xor64_seq_cst(ptr, val) \
	__XBLOCK({ __asm__ __volatile__("lock; xorq %1, %0\n" \
	                                : "+m" (*(ptr)) \
	                                : "r" (val) \
	                                : "memory", "cc"); \
	           (void)0; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch_val64_seq_cst __hybrid_atomic_cmpxch_val64_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
(__hybrid_atomic_cmpxch_val64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval) {
	__register __UINT64_TYPE__ __res;
	__asm__ __volatile__("lock; cmpxchgq %2, %0\n"
	                     : "+m" (*(__ptr)), "=a" (__res)
	                     : "r" (__newval), "1" (__oldval)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_cmpxch64_seq_cst __hybrid_atomic_cmpxch64_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
(__hybrid_atomic_cmpxch64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval) {
	__register __BOOL __res;
	__asm__ __volatile__("lock; cmpxchgq %2, %0\n"
	                     : "+m" (*(__ptr)), "=@cceq" (__res)
	                     : "r" (__newval), "a" (__oldval)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_load64_seq_cst __hybrid_atomic_load64_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
(__hybrid_atomic_load64_seq_cst)(__UINT64_TYPE__ const *__ptr) {
	__register __UINT64_TYPE__ __res;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movq %1, %0\n"
	                     : "=r" (__res)
	                     : "m" (*(__ptr))
	                     : "memory");
	return __res;
}
#define __hybrid_atomic_store64_seq_cst __hybrid_atomic_store64_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_store64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __val) {
	__asm__ __volatile__("movq %1, %0\n"
	                     : "=m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory");
	__COMPILER_WRITE_BARRIER();
}
#define __hybrid_atomic_xch64_seq_cst __hybrid_atomic_xch64_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
(__hybrid_atomic_xch64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __val) {
	__register __UINT64_TYPE__ __res;
	__asm__ __volatile__("xchgq %1, %0\n"
	                     : "+m" (*(__ptr))
	                     , "=r" (__res)
	                     : "1" (__val)
	                     : "memory");
	return __res;
}
#define __hybrid_atomic_fetchadd64_seq_cst __hybrid_atomic_fetchadd64_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
(__hybrid_atomic_fetchadd64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __val) {
	__register __UINT64_TYPE__ __res;
	__asm__ __volatile__("lock; xaddq %1, %0\n"
	                     : "+m" (*(__ptr))
	                     , "=r" (__res)
	                     : "1" (__val)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_inc64_seq_cst __hybrid_atomic_inc64_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_inc64_seq_cst)(__UINT64_TYPE__ *__ptr) {
	__asm__ __volatile__("lock; incq %0\n"
	                     : "+m" (*(__ptr)) : : "memory", "cc");
}
#define __hybrid_atomic_dec64_seq_cst __hybrid_atomic_dec64_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_dec64_seq_cst)(__UINT64_TYPE__ *__ptr) {
	__asm__ __volatile__("lock; decq %0\n"
	                     : "+m" (*(__ptr)) : : "memory", "cc");
}
#define __hybrid_atomic_add64_seq_cst __hybrid_atomic_add64_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_add64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __val) {
	__asm__ __volatile__("lock; addq %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_sub64_seq_cst __hybrid_atomic_sub64_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_sub64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __val) {
	__asm__ __volatile__("lock; subq %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_and64_seq_cst __hybrid_atomic_and64_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_and64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __val) {
	__asm__ __volatile__("lock; andq %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_or64_seq_cst __hybrid_atomic_or64_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_or64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __val) {
	__asm__ __volatile__("lock; orq %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#define __hybrid_atomic_xor64_seq_cst __hybrid_atomic_xor64_seq_cst
__LOCAL __ATTR_NONNULL((1)) void
(__hybrid_atomic_xor64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __val) {
	__asm__ __volatile__("lock; xorq %1, %0\n"
	                     : "+m" (*(__ptr))
	                     : "r" (__val)
	                     : "memory", "cc");
}
#endif /* !__NO_XBLOCK */
#else /* __x86_64__ */
#define __hybrid_atomic_cmpxch_val64(ptr, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch_val64_seq_cst(ptr, oldval, newval)
#define __hybrid_atomic_cmpxch64(ptr, oldval, newval, succ, fail) \
	__hybrid_atomic_cmpxch64_seq_cst(ptr, oldval, newval)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch_val64_seq_cst(ptr, oldval, newval) \
	__XBLOCK({ \
		__register __UINT64_TYPE__ __hacx64_res; \
		__register __UINT64_TYPE__ __hacx64_nv = (newval); \
		__asm__ __volatile__("lock; cmpxchg8b %0\n" \
		                     : "+m" (*(ptr)), "=A" (__hacx64_res) \
		                     : "A" (oldval) \
		                     , "c" ((__UINT32_TYPE__)((__UINT64_TYPE__)__hacx64_nv >> 32)) \
		                     , "b" ((__UINT32_TYPE__)(__UINT64_TYPE__)__hacx64_nv) \
		                     : "memory", "cc"); \
		__XRETURN __hacx64_res; \
	})
#define __hybrid_atomic_cmpxch64_seq_cst(ptr, oldval, newval) \
	__XBLOCK({ \
		__register __BOOL __hacx64_res; \
		__register __UINT64_TYPE__ __hacx64_nv = (newval); \
		__asm__ __volatile__("lock; cmpxchg8b %0\n" \
		                     : "+m" (*(ptr)), "=@cceq" (__hacx64_res) \
		                     : "A" (oldval) \
		                     , "c" ((__UINT32_TYPE__)((__UINT64_TYPE__)__hacx64_nv >> 32)) \
		                     , "b" ((__UINT32_TYPE__)(__UINT64_TYPE__)__hacx64_nv) \
		                     : "memory", "cc"); \
		__XRETURN __hacx64_res; \
	})
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch_val64_seq_cst __hybrid_atomic_cmpxch_val64_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
(__hybrid_atomic_cmpxch_val64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval) {
	__register __UINT64_TYPE__ __res;
	__asm__ __volatile__("lock; cmpxchg8b %0\n"
	                     : "+m" (*__ptr)
	                     : "=A" (__res)
	                     : "1" (__oldval)
	                     , "c" ((__UINT32_TYPE__)((__UINT64_TYPE__)__newval >> 32))
	                     , "b" ((__UINT32_TYPE__)(__UINT64_TYPE__)__newval)
	                     : "memory", "cc");
	return __res;
}
#define __hybrid_atomic_cmpxch64_seq_cst __hybrid_atomic_cmpxch64_seq_cst
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
(__hybrid_atomic_cmpxch64_seq_cst)(__UINT64_TYPE__ *__ptr, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval) {
	__register __BOOL __res;
	__asm__ __volatile__("lock; cmpxchg8b %0\n"
	                     : "+m" (*__ptr), "=@cceq" (__res)
	                     : "A" (__oldval)
	                     : "c" ((__UINT32_TYPE__)((__UINT64_TYPE__)__newval >> 32))
	                     , "b" ((__UINT32_TYPE__)(__UINT64_TYPE__)__newval)
	                     : "memory", "cc");
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* !__x86_64__ */
/*[[[end]]]*/
/* clang-format on */

__DECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID___ATOMIC_GASM_X86_H */
