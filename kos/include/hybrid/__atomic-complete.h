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
#ifndef __GUARD_HYBRID___ATOMIC_COMPLETE_H
#define __GUARD_HYBRID___ATOMIC_COMPLETE_H 1

#include "../__stdinc.h"

#ifndef __GUARD_HYBRID___ATOMIC_H
#error "Never include this file directly. - Always include `<hybrid/__atomic.h>' instead"
#endif /* !__GUARD_HYBRID___ATOMIC_H */

/* Substitute atomic operations for one-another */

/* clang-format off */
/*[[[deemon
import * from deemon;
global final OP_FUNCTIONS: {string: Callable} = {
	"add"  : (a, b) -> f"{a} + {b}",
	"sub"  : (a, b) -> f"{a} - {b}",
	"and"  : (a, b) -> f"{a} & {b}",
	"xor"  : (a, b) -> f"{a} ^ {b}",
	"or"   : (a, b) -> f"{a} | {b}",
	"nand" : (a, b) -> f"~({a} & {b})",
};

for (local op: ["add", "sub", "and", "xor", "or", "nand"]) {
	print("#ifndef __hybrid_atomic_", op);
	print("#ifdef __hybrid_atomic_fetch", op);
	print("#define __hybrid_atomic_", op, "(p, val, order) (void)__hybrid_atomic_fetch", op, "(p, val, order)");
	print("#elif defined(__hybrid_atomic_", op, "fetch)");
	print("#define __hybrid_atomic_", op, "(p, val, order) (void)__hybrid_atomic_", op, "fetch(p, val, order)");
	print("#endif /" "* ... *" "/");
	print("#endif /" "* __hybrid_atomic_", op, " *" "/");
	print;
}

function sub(n: string) {
	print("#ifndef __hybrid_atomic_cmpxch", n);
	print("#ifdef __hybrid_atomic_cmpxch");
	print("#define __hybrid_atomic_cmpxch", n, " __hybrid_atomic_cmpxch");
	print("#elif defined(__hybrid_atomic_cmpxch_val", n, ")");
	print("#ifndef __NO_XBLOCK");
	print("#define __hybrid_atomic_cmpxch", n, "(p, oldval, newval, succ, fail) \\");
	print("	__XBLOCK({ __UINT", n, "_TYPE__ __hacx", n, "_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val", n, "(p, __hacx", n, "_ov, newval, succ, fail) == __hacx", n, "_ov; })");
	print("#else /" "* __NO_XBLOCK *" "/");
	print("#define __hybrid_atomic_cmpxch", n, " __hybrid_atomic_cmpxch", n);
	print("__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch", n, ")(__UINT", n, "_TYPE__ *__p, __UINT", n, "_TYPE__ __oldval, __UINT", n, "_TYPE__ __newval, int __succ, int __fail) {");
	print("	(void)__succ, (void)__fail;");
	print("	return __hybrid_atomic_cmpxch_val", n, "(__p, __oldval, __newval, __succ, __fail) == __oldval;");
	print("}");
	print("#endif /" "* !__NO_XBLOCK *" "/");
	print("#endif /" "* ... *" "/");
	print("#endif /" "* !__hybrid_atomic_cmpxch", n, " *" "/");
	print;

	print("#ifndef __hybrid_atomic_cmpxch_weak", n);
	print("#ifdef __hybrid_atomic_cmpxch_weak");
	print("#define __hybrid_atomic_cmpxch_weak", n, " __hybrid_atomic_cmpxch_weak");
	print("#elif defined(__hybrid_atomic_cmpxch", n, ")");
	print("#define __hybrid_atomic_cmpxch_weak", n, " __hybrid_atomic_cmpxch", n);
	print("#endif /" "* ... *" "/");
	print("#endif /" "* !__hybrid_atomic_cmpxch_weak", n, " *" "/");
	print;

	print("#ifndef __hybrid_atomic_load", n);
	print("#ifdef __hybrid_atomic_load");
	print("#define __hybrid_atomic_load", n, " __hybrid_atomic_load");
	print("#elif defined(__hybrid_atomic_fetchadd", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_fetchadd", n, "(p, 0, order)");
	print("#elif defined(__hybrid_atomic_addfetch", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_addfetch", n, "(p, 0, order)");
	print("#elif defined(__hybrid_atomic_fetchsub", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_fetchsub", n, "(p, 0, order)");
	print("#elif defined(__hybrid_atomic_subfetch", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_subfetch", n, "(p, 0, order)");
	print("#elif defined(__hybrid_atomic_fetchand", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_fetchand", n, "(p, (__UINT", n, "_TYPE__)-1, order)");
	print("#elif defined(__hybrid_atomic_andfetch", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_andfetch", n, "(p, (__UINT", n, "_TYPE__)-1, order)");
	print("#elif defined(__hybrid_atomic_fetchor", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_fetchor", n, "(p, 0, order)");
	print("#elif defined(__hybrid_atomic_orfetch", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_orfetch", n, "(p, 0, order)");
	print("#elif defined(__hybrid_atomic_fetchxor", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_fetchxor", n, "(p, 0, order)");
	print("#elif defined(__hybrid_atomic_xorfetch", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_xorfetch", n, "(p, 0, order)");
	print("#elif defined(__hybrid_atomic_cmpxch_val", n, ")");
	print("#define __hybrid_atomic_load", n, "(p, order) __hybrid_atomic_cmpxch_val", n, "(p, 0, 0, order, order)");
	print("#elif defined(__hybrid_atomic_cmpxch_weak", n, ")");
	print("#ifndef __NO_XBLOCK");
	print("#define __hybrid_atomic_load", n, "(p, order) \\");
	print("	__XBLOCK({ __UINT", n, "_TYPE__ const *__hal", n, "_p = (p); __UINT", n, "_TYPE__ __hal", n, "_res; \\");
	print("	           do { __hal", n, "_res = *__hal", n, "_p; __COMPILER_READ_BARRIER(); \\");
	print("	           } while (!__hybrid_atomic_cmpxch_weak((__UINT", n, "_TYPE__ *)__hal", n, "_p, __hal", n, "_res, __hal", n, "_res, order, order)); \\");
	print("	           __XRETURN __hal", n, "_res; })");
	print("#else /" "* __NO_XBLOCK *" "/");
	print("#define __hybrid_atomic_load", n, " __hybrid_atomic_load", n);
	print("__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT", n, "_TYPE__ __NOTHROW_NCX(__hybrid_atomic_load", n, ")(__UINT", n, "_TYPE__ const *__p, int __order) {");
	print("	__UINT", n, "_TYPE__ __res;");
	print("	(void)__order;");
	print("	do { __res = *__p; __COMPILER_READ_BARRIER();");
	print("	} while (!__hybrid_atomic_cmpxch_weak((__UINT", n, "_TYPE__ *)__p, __res, __res, __order, __order));");
	print("	return __res;");
	print("}");
	print("#endif /" "* !__NO_XBLOCK *" "/");
	print("#endif /" "* ... *" "/");
	print("#endif /" "* !__hybrid_atomic_load", n, " *" "/");
	print;

	print("#ifndef __hybrid_atomic_cmpxch_val", n);
	print("#ifdef __hybrid_atomic_cmpxch_val");
	print("#define __hybrid_atomic_cmpxch_val", n, " __hybrid_atomic_cmpxch_val");
	print("#elif defined(__hybrid_atomic_cmpxch_weak", n, ")");
	print("#ifndef __NO_XBLOCK");
	print("#define __hybrid_atomic_cmpxch_val", n, "(p, oldval, newval, succ, fail) \\");
	print("	__XBLOCK({ __UINT", n, "_TYPE__ __hacxv", n, "_p = (p), __hacxv", n, "_ov = (oldval), __hacxv", n, "_nv = (newval), __hacxv", n, "_res; \\");
	print("	           do if ((__hacxv", n, "_res = __hybrid_atomic_load", n, "(__hacxv", n, "_p, __ATOMIC_ACQUIRE)) != __hacxv", n, "_ov) break; \\");
	print("	           while (!__hybrid_atomic_cmpxch_weak", n, "(__hacxv", n, "_p, __hacxv", n, "_res, __hacxv", n, "_nv, succ, fail)); \\");
	print("	           __XRETURN __hacxv", n, "_res; })");
	print("#else /" "* __NO_XBLOCK *" "/");
	print("#define __hybrid_atomic_cmpxch_val", n, " __hybrid_atomic_cmpxch_val", n);
	print("__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT", n, "_TYPE__ __NOTHROW_NCX(__hybrid_atomic_cmpxch_val", n, ")(__UINT", n, "_TYPE__ *__p, __UINT", n, "_TYPE__ __oldval, __UINT", n, "_TYPE__ __newval, int __succ, int __fail) {");
	print("	__UINT", n, "_TYPE__ __res;");
	print("	(void)__succ, (void)__fail;");
	print("	do if ((__res = __hybrid_atomic_load", n, "(__p, __ATOMIC_ACQUIRE)) != __oldval) break;");
	print("	while (!__hybrid_atomic_cmpxch_weak", n, "(__p, __res, __newval, __succ, __fail));");
	print("	return __res;");
	print("}");
	print("#endif /" "* !__NO_XBLOCK *" "/");
	print("#endif /" "* ... *" "/");
	print("#endif /" "* !__hybrid_atomic_cmpxch_val", n, " *" "/");
	print;

	print("#if !defined(__hybrid_atomic_cmpxch", n, ") && defined(__hybrid_atomic_cmpxch_val", n, ")");
	print("#ifndef __NO_XBLOCK");
	print("#define __hybrid_atomic_cmpxch", n, "(p, oldval, newval, succ, fail) \\");
	print("	__XBLOCK({ __UINT", n, "_TYPE__ __hacx", n, "_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val", n, "(p, __hacx", n, "_ov, newval, succ, fail) == __hacx", n, "_ov; })");
	print("#else /" "* __NO_XBLOCK *" "/");
	print("__LOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch", n, ")(__UINT", n, "_TYPE__ *__p, __UINT", n, "_TYPE__ __oldval, __UINT", n, "_TYPE__ __newval, int __succ, int __fail) {");
	print("	(void)__succ, (void)__fail;");
	print("	return __hybrid_atomic_cmpxch_val", n, "(__p, __oldval, __newval, __succ, __fail) == __oldval;");
	print("}");
	print("#endif /" "* !__NO_XBLOCK *" "/");
	print("#endif /" "* !__hybrid_atomic_cmpxch", n, " && __hybrid_atomic_cmpxch_val", n, " *" "/");
	print;

	print("#if !defined(__hybrid_atomic_cmpxch_weak", n, ") && defined(__hybrid_atomic_cmpxch", n, ")");
	print("#define __hybrid_atomic_cmpxch_weak", n, " __hybrid_atomic_cmpxch", n);
	print("#endif /" "* !__hybrid_atomic_cmpxch_weak", n, " && __hybrid_atomic_cmpxch", n, " *" "/");
	print;

	print("#ifndef __hybrid_atomic_xch", n);
	print("#ifdef __hybrid_atomic_xch");
	print("#define __hybrid_atomic_xch", n, " __hybrid_atomic_xch");
	print("#elif defined(__hybrid_atomic_load", n, ") && defined(__hybrid_atomic_cmpxch_weak", n, ")");
	print("#ifndef __NO_XBLOCK");
	print("#define __hybrid_atomic_xch", n, "(p, val, order) \\");
	print("	__XBLOCK({ __UINT", n, "_TYPE__ *__hal", n, "_p = (p); __UINT", n, "_TYPE__ __hal", n, "_res, __hal", n, "_val = (val); \\");
	print("	           do __hal", n, "_res = __hybrid_atomic_load(__hal", n, "_p, __ATOMIC_ACQUIRE); \\");
	print("	           while (!__hybrid_atomic_cmpxch_weak(__hal", n, "_p, __hal", n, "_res, __hal", n, "_val, order, order)); \\");
	print("	           __XRETURN __hal", n, "_res; })");
	print("#else /" "* __NO_XBLOCK *" "/");
	print("#define __hybrid_atomic_xch", n, " __hybrid_atomic_xch", n);
	print("__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT", n, "_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xch", n, ")(__UINT", n, "_TYPE__ *__p, __UINT", n, "_TYPE__ __val, int __order) {");
	print("	__UINT", n, "_TYPE__ __res;");
	print("	(void)__order;");
	print("	do __res = __hybrid_atomic_load(__p, __ATOMIC_ACQUIRE);");
	print("	while (!__hybrid_atomic_cmpxch_weak(__p, __res, __val, __order, __order));");
	print("	return __res;");
	print("}");
	print("#endif /" "* !__NO_XBLOCK *" "/");
	print("#endif /" "* ... *" "/");
	print("#endif /" "* !__hybrid_atomic_xch", n, " *" "/");
	print;

	print("#ifndef __hybrid_atomic_store", n);
	print("#ifdef __hybrid_atomic_store");
	print("#define __hybrid_atomic_store", n, " __hybrid_atomic_store");
	print("#elif defined(__hybrid_atomic_xch", n, ")");
	print("#define __hybrid_atomic_store", n, " (void)__hybrid_atomic_xch", n);
	print("#endif /" "* ... *" "/");
	print("#endif /" "* !__hybrid_atomic_store", n, " *" "/");
	print;

	for (local op: ["add", "sub", "and", "xor", "or", "nand", "inc", "dec"]) {
		print("#ifndef __hybrid_atomic_fetch", op, n);
		print("#ifdef __hybrid_atomic_fetch", op);
		print("#define __hybrid_atomic_fetch", op, n, " __hybrid_atomic_fetch", op);
		if (op in ["inc", "dec"]) {
			local subop = op == "inc" ? "add" : "sub";
			print("#elif defined(__hybrid_atomic_fetch", subop, n, ")");
			print("#define __hybrid_atomic_fetch", op, n, "(p, order) __hybrid_atomic_fetch", subop, n, "(p, 1, order)");
			local subop = op == "inc" ? "sub" : "add";
			print("#elif defined(__hybrid_atomic_fetch", subop, n, ")");
			print("#define __hybrid_atomic_fetch", op, n, "(p, order) __hybrid_atomic_fetch", subop, n, "(p, (__UINT", n, "_TYPE__)-1, order)");
		}
		if (op in ["add", "sub"]) {
			local subop = op == "add" ? "sub" : "add";
			print("#elif defined(__hybrid_atomic_fetch", subop, ")");
			print("#define __hybrid_atomic_fetch", op, n, "(p, val, order) __hybrid_atomic_fetch", subop, "(p, (__UINT", n, "_TYPE__)(-(__INT", n, "_TYPE__)(val)), order)");
			print("#elif defined(__hybrid_atomic_fetch", subop, n, ")");
			print("#define __hybrid_atomic_fetch", op, n, "(p, val, order) __hybrid_atomic_fetch", subop, n, "(p, (__UINT", n, "_TYPE__)(-(__INT", n, "_TYPE__)(val)), order)");
		}
		if (op in ["inc", "dec"]) {
			print("#elif defined(__hybrid_atomic_", op, "fetch", n, ")");
			print("#define __hybrid_atomic_fetch", op, n, "(p, order) (__hybrid_atomic_", op, "fetch", n, "(p, val, order) ", op == "inc" ? "-" : "+", " 1)");
		} else if (op in ["add", "sub", "xor"]) {
			local revop = op == "add" ? "-" : op == "sub" ? "+" : "^";
			print("#elif defined(__hybrid_atomic_", op, "fetch", n, ")");
			print("#ifndef __NO_XBLOCK");
			print("#define __hybrid_atomic_fetch", op, n, "(p, val, order) \\");
			print("	__XBLOCK({ __UINT", n, "_TYPE__ __hafx", n, "_val = (val); __XRETURN __hybrid_atomic_", op, "fetch", n, "(p, __hafx", n, "_val, order) ", revop, " __hafx", n, "_val; })");
			print("#else /" "* !__NO_XBLOCK *" "/");
			print("#define __hybrid_atomic_fetch", op, n, " __hybrid_atomic_fetch", op, n);
			print("__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT", n, "_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetch", op, n, ")(__UINT", n, "_TYPE__ *__p, __UINT", n, "_TYPE__ __val, int __order) {");
			print("	(void)__order;");
			print("	return __hybrid_atomic_", op, "fetch", n, "(__p, __val, __order) ", revop, " __val;");
			print("}");
			print("#endif /" "* __NO_XBLOCK *" "/");
		}
		if (op !in ["inc", "dec"]) {
			local opfun = OP_FUNCTIONS[op];
			print("#elif defined(__hybrid_atomic_load", n, ") && defined(__hybrid_atomic_cmpxch_weak", n, ")");
			print("#ifndef __NO_XBLOCK");
			print("#define __hybrid_atomic_fetch", op, n, "(p, val, order) \\");
			print("	__XBLOCK({ __UINT", n, "_TYPE__ __hacxv", n, "_p = (p), __hacxv", n, "_val = (val), __hacxv", n, "_res; \\");
			print("	           do __hacxv", n, "_res = __hybrid_atomic_load", n, "(__hacxv", n, "_p, __ATOMIC_ACQUIRE); \\");
			print("	           while (!__hybrid_atomic_cmpxch_weak", n, "(__hacxv", n, "_p, __hacxv", n, "_res, ", opfun(f"__hacxv{n}_res", f"__hacxv{n}_val"), ", order, order)); \\");
			print("	           __XRETURN __hacxv", n, "_res; })");
			print("#else /" "* __NO_XBLOCK *" "/");
			print("#define __hybrid_atomic_fetch", op, n, " __hybrid_atomic_fetch", op, n);
			print("__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT", n, "_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetch", op, n, ")(__UINT", n, "_TYPE__ *__p, __UINT", n, "_TYPE__ __val, int __order) {");
			print("	__UINT", n, "_TYPE__ __res;");
			print("	(void)__order;");
			print("	do __res = __hybrid_atomic_load", n, "(__p, __ATOMIC_ACQUIRE);");
			print("	while (!__hybrid_atomic_cmpxch_weak", n, "(__p, __res, ", opfun("__res", "__val"), ", __order, __order));");
			print("	return __res;");
			print("}");
			print("#endif /" "* !__NO_XBLOCK *" "/");
		}
		print("#endif /" "* ... *" "/");
		print("#endif /" "* !__hybrid_atomic_", op, n, " *" "/");
		print;
	}

	for (local op: ["add", "sub", "and", "xor", "or", "nand", "inc", "dec"]) {
		print("#ifndef __hybrid_atomic_", op, "fetch", n);
		print("#ifdef __hybrid_atomic_", op, "fetch");
		print("#define __hybrid_atomic_", op, "fetch", n, " __hybrid_atomic_", op, "fetch");
		if (op in ["inc", "dec"]) {
			local subop = op == "inc" ? "add" : "sub";
			print("#elif defined(__hybrid_atomic_", subop, "fetch", n, ")");
			print("#define __hybrid_atomic_", op, "fetch", n, "(p, order) __hybrid_atomic_", subop, "fetch", n, "(p, 1, order)");
			local subop = op == "inc" ? "sub" : "add";
			print("#elif defined(__hybrid_atomic_", subop, "fetch", n, ")");
			print("#define __hybrid_atomic_", op, "fetch", n, "(p, order) __hybrid_atomic_", subop, "fetch", n, "(p, (__UINT", n, "_TYPE__)-1, order)");
		}
		if (op in ["add", "sub"]) {
			local subop = op == "add" ? "sub" : "add";
			print("#elif defined(__hybrid_atomic_", subop, "fetch)");
			print("#define __hybrid_atomic_", op, "fetch", n, "(p, val, order) __hybrid_atomic_", subop, "fetch(p, (__UINT", n, "_TYPE__)(-(__INT", n, "_TYPE__)(val)), order)");
			print("#elif defined(__hybrid_atomic_", subop, "fetch", n, ")");
			print("#define __hybrid_atomic_", op, "fetch", n, "(p, val, order) __hybrid_atomic_", subop, "fetch", n, "(p, (__UINT", n, "_TYPE__)(-(__INT", n, "_TYPE__)(val)), order)");
		}
		if (op !in ["inc", "dec"]) {
			local opfun = OP_FUNCTIONS[op];
			print("#elif defined(__hybrid_atomic_fetch", op, n, ")");
			print("#ifndef __NO_XBLOCK");
			print("#define __hybrid_atomic_", op, "fetch", n, "(p, val, order) \\");
			print("	__XBLOCK({ __UINT", n, "_TYPE__ __haxf", n, "_val = (val); __XRETURN ", opfun(f"__hybrid_atomic_fetch{op}{n}(p, __haxf{n}_val, order)", f"__haxf{n}_val"), "; })");
			print("#else /" "* __NO_XBLOCK *" "/");
			print("#define __hybrid_atomic_", op, "fetch", n, " __hybrid_atomic_", op, "fetch", n);
			print("__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT", n, "_TYPE__ __NOTHROW_NCX(__hybrid_atomic_", op, "fetch", n, ")(__UINT", n, "_TYPE__ *__p, __UINT", n, "_TYPE__ __val, int __order) {");
			print("	(void)__order;");
			print("	return ", opfun(f"__hybrid_atomic_fetch{op}{n}(__p, __val, __order)", "__val"), ";");
			print("}");
			print("#endif /" "* !__NO_XBLOCK *" "/");
		}
		print("#endif /" "* ... *" "/");
		print("#endif /" "* !__hybrid_atomic_", op, "fetch", n, " *" "/");
		print;
	}

	for (local op: ["inc", "dec", "add", "sub", "and", "xor", "or", "nand"]) {
		print("#ifndef __hybrid_atomic_", op, n);
		print("#ifdef __hybrid_atomic_", op);
		print("#define __hybrid_atomic_", op, n, " __hybrid_atomic_", op);
		if (op in ["inc", "dec"]) {
			local subop = op == "inc" ? "add" : "sub";
			print("#elif defined(__hybrid_atomic_", subop, n, ")");
			print("#define __hybrid_atomic_", op, n, "(p, order) __hybrid_atomic_", subop, n, "(p, 1, order)");
		}
		print("#elif defined(__hybrid_atomic_fetch", op, n, ")");
		print("#define __hybrid_atomic_", op, n, " (void)__hybrid_atomic_fetch", op, n);
		print("#elif defined(__hybrid_atomic_", op, "fetch", n, ")");
		print("#define __hybrid_atomic_", op, n, " (void)__hybrid_atomic_", op, "fetch", n);
		print("#endif /" "* ... *" "/");
		print("#endif /" "* !__hybrid_atomic_", op, n, " *" "/");
		print;
	}
}

sub("8");
sub("16");
sub("32");
print("#ifdef __UINT64_TYPE__");
sub("64");
print("#endif /" "* __UINT64_TYPE__ *" "/");
print("#ifdef __UINT128_TYPE__");
sub("128");
print("#endif /" "* __UINT128_TYPE__ *" "/");
]]]*/
#ifndef __hybrid_atomic_add
#ifdef __hybrid_atomic_fetchadd
#define __hybrid_atomic_add(p, val, order) (void)__hybrid_atomic_fetchadd(p, val, order)
#elif defined(__hybrid_atomic_addfetch)
#define __hybrid_atomic_add(p, val, order) (void)__hybrid_atomic_addfetch(p, val, order)
#endif /* ... */
#endif /* __hybrid_atomic_add */

#ifndef __hybrid_atomic_sub
#ifdef __hybrid_atomic_fetchsub
#define __hybrid_atomic_sub(p, val, order) (void)__hybrid_atomic_fetchsub(p, val, order)
#elif defined(__hybrid_atomic_subfetch)
#define __hybrid_atomic_sub(p, val, order) (void)__hybrid_atomic_subfetch(p, val, order)
#endif /* ... */
#endif /* __hybrid_atomic_sub */

#ifndef __hybrid_atomic_and
#ifdef __hybrid_atomic_fetchand
#define __hybrid_atomic_and(p, val, order) (void)__hybrid_atomic_fetchand(p, val, order)
#elif defined(__hybrid_atomic_andfetch)
#define __hybrid_atomic_and(p, val, order) (void)__hybrid_atomic_andfetch(p, val, order)
#endif /* ... */
#endif /* __hybrid_atomic_and */

#ifndef __hybrid_atomic_xor
#ifdef __hybrid_atomic_fetchxor
#define __hybrid_atomic_xor(p, val, order) (void)__hybrid_atomic_fetchxor(p, val, order)
#elif defined(__hybrid_atomic_xorfetch)
#define __hybrid_atomic_xor(p, val, order) (void)__hybrid_atomic_xorfetch(p, val, order)
#endif /* ... */
#endif /* __hybrid_atomic_xor */

#ifndef __hybrid_atomic_or
#ifdef __hybrid_atomic_fetchor
#define __hybrid_atomic_or(p, val, order) (void)__hybrid_atomic_fetchor(p, val, order)
#elif defined(__hybrid_atomic_orfetch)
#define __hybrid_atomic_or(p, val, order) (void)__hybrid_atomic_orfetch(p, val, order)
#endif /* ... */
#endif /* __hybrid_atomic_or */

#ifndef __hybrid_atomic_nand
#ifdef __hybrid_atomic_fetchnand
#define __hybrid_atomic_nand(p, val, order) (void)__hybrid_atomic_fetchnand(p, val, order)
#elif defined(__hybrid_atomic_nandfetch)
#define __hybrid_atomic_nand(p, val, order) (void)__hybrid_atomic_nandfetch(p, val, order)
#endif /* ... */
#endif /* __hybrid_atomic_nand */

#ifndef __hybrid_atomic_cmpxch8
#ifdef __hybrid_atomic_cmpxch
#define __hybrid_atomic_cmpxch8 __hybrid_atomic_cmpxch
#elif defined(__hybrid_atomic_cmpxch_val8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch8(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT8_TYPE__ __hacx8_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val8(p, __hacx8_ov, newval, succ, fail) == __hacx8_ov; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch8 __hybrid_atomic_cmpxch8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __oldval, __UINT8_TYPE__ __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
	return __hybrid_atomic_cmpxch_val8(__p, __oldval, __newval, __succ, __fail) == __oldval;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch8 */

#ifndef __hybrid_atomic_cmpxch_weak8
#ifdef __hybrid_atomic_cmpxch_weak
#define __hybrid_atomic_cmpxch_weak8 __hybrid_atomic_cmpxch_weak
#elif defined(__hybrid_atomic_cmpxch8)
#define __hybrid_atomic_cmpxch_weak8 __hybrid_atomic_cmpxch8
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch_weak8 */

#ifndef __hybrid_atomic_load8
#ifdef __hybrid_atomic_load
#define __hybrid_atomic_load8 __hybrid_atomic_load
#elif defined(__hybrid_atomic_fetchadd8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_fetchadd8(p, 0, order)
#elif defined(__hybrid_atomic_addfetch8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_addfetch8(p, 0, order)
#elif defined(__hybrid_atomic_fetchsub8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_fetchsub8(p, 0, order)
#elif defined(__hybrid_atomic_subfetch8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_subfetch8(p, 0, order)
#elif defined(__hybrid_atomic_fetchand8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_fetchand8(p, (__UINT8_TYPE__)-1, order)
#elif defined(__hybrid_atomic_andfetch8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_andfetch8(p, (__UINT8_TYPE__)-1, order)
#elif defined(__hybrid_atomic_fetchor8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_fetchor8(p, 0, order)
#elif defined(__hybrid_atomic_orfetch8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_orfetch8(p, 0, order)
#elif defined(__hybrid_atomic_fetchxor8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_fetchxor8(p, 0, order)
#elif defined(__hybrid_atomic_xorfetch8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_xorfetch8(p, 0, order)
#elif defined(__hybrid_atomic_cmpxch_val8)
#define __hybrid_atomic_load8(p, order) __hybrid_atomic_cmpxch_val8(p, 0, 0, order, order)
#elif defined(__hybrid_atomic_cmpxch_weak8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_load8(p, order) \
	__XBLOCK({ __UINT8_TYPE__ const *__hal8_p = (p); __UINT8_TYPE__ __hal8_res; \
	           do { __hal8_res = *__hal8_p; __COMPILER_READ_BARRIER(); \
	           } while (!__hybrid_atomic_cmpxch_weak((__UINT8_TYPE__ *)__hal8_p, __hal8_res, __hal8_res, order, order)); \
	           __XRETURN __hal8_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_load8 __hybrid_atomic_load8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_load8)(__UINT8_TYPE__ const *__p, int __order) {
	__UINT8_TYPE__ __res;
	(void)__order;
	do { __res = *__p; __COMPILER_READ_BARRIER();
	} while (!__hybrid_atomic_cmpxch_weak((__UINT8_TYPE__ *)__p, __res, __res, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_load8 */

#ifndef __hybrid_atomic_cmpxch_val8
#ifdef __hybrid_atomic_cmpxch_val
#define __hybrid_atomic_cmpxch_val8 __hybrid_atomic_cmpxch_val
#elif defined(__hybrid_atomic_cmpxch_weak8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch_val8(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT8_TYPE__ __hacxv8_p = (p), __hacxv8_ov = (oldval), __hacxv8_nv = (newval), __hacxv8_res; \
	           do if ((__hacxv8_res = __hybrid_atomic_load8(__hacxv8_p, __ATOMIC_ACQUIRE)) != __hacxv8_ov) break; \
	           while (!__hybrid_atomic_cmpxch_weak8(__hacxv8_p, __hacxv8_res, __hacxv8_nv, succ, fail)); \
	           __XRETURN __hacxv8_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch_val8 __hybrid_atomic_cmpxch_val8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_cmpxch_val8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __oldval, __UINT8_TYPE__ __newval, int __succ, int __fail) {
	__UINT8_TYPE__ __res;
	(void)__succ, (void)__fail;
	do if ((__res = __hybrid_atomic_load8(__p, __ATOMIC_ACQUIRE)) != __oldval) break;
	while (!__hybrid_atomic_cmpxch_weak8(__p, __res, __newval, __succ, __fail));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch_val8 */

#if !defined(__hybrid_atomic_cmpxch8) && defined(__hybrid_atomic_cmpxch_val8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch8(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT8_TYPE__ __hacx8_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val8(p, __hacx8_ov, newval, succ, fail) == __hacx8_ov; })
#else /* __NO_XBLOCK */
__LOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __oldval, __UINT8_TYPE__ __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
	return __hybrid_atomic_cmpxch_val8(__p, __oldval, __newval, __succ, __fail) == __oldval;
}
#endif /* !__NO_XBLOCK */
#endif /* !__hybrid_atomic_cmpxch8 && __hybrid_atomic_cmpxch_val8 */

#if !defined(__hybrid_atomic_cmpxch_weak8) && defined(__hybrid_atomic_cmpxch8)
#define __hybrid_atomic_cmpxch_weak8 __hybrid_atomic_cmpxch8
#endif /* !__hybrid_atomic_cmpxch_weak8 && __hybrid_atomic_cmpxch8 */

#ifndef __hybrid_atomic_xch8
#ifdef __hybrid_atomic_xch
#define __hybrid_atomic_xch8 __hybrid_atomic_xch
#elif defined(__hybrid_atomic_load8) && defined(__hybrid_atomic_cmpxch_weak8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_xch8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ *__hal8_p = (p); __UINT8_TYPE__ __hal8_res, __hal8_val = (val); \
	           do __hal8_res = __hybrid_atomic_load(__hal8_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak(__hal8_p, __hal8_res, __hal8_val, order, order)); \
	           __XRETURN __hal8_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_xch8 __hybrid_atomic_xch8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xch8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	__UINT8_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak(__p, __res, __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xch8 */

#ifndef __hybrid_atomic_store8
#ifdef __hybrid_atomic_store
#define __hybrid_atomic_store8 __hybrid_atomic_store
#elif defined(__hybrid_atomic_xch8)
#define __hybrid_atomic_store8 (void)__hybrid_atomic_xch8
#endif /* ... */
#endif /* !__hybrid_atomic_store8 */

#ifndef __hybrid_atomic_fetchadd8
#ifdef __hybrid_atomic_fetchadd
#define __hybrid_atomic_fetchadd8 __hybrid_atomic_fetchadd
#elif defined(__hybrid_atomic_fetchsub)
#define __hybrid_atomic_fetchadd8(p, val, order) __hybrid_atomic_fetchsub(p, (__UINT8_TYPE__)(-(__INT8_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchsub8)
#define __hybrid_atomic_fetchadd8(p, val, order) __hybrid_atomic_fetchsub8(p, (__UINT8_TYPE__)(-(__INT8_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_addfetch8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchadd8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __hafx8_val = (val); __XRETURN __hybrid_atomic_addfetch8(p, __hafx8_val, order) - __hafx8_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchadd8 __hybrid_atomic_fetchadd8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchadd8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_addfetch8(__p, __val, __order) - __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load8) && defined(__hybrid_atomic_cmpxch_weak8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchadd8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __hacxv8_p = (p), __hacxv8_val = (val), __hacxv8_res; \
	           do __hacxv8_res = __hybrid_atomic_load8(__hacxv8_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak8(__hacxv8_p, __hacxv8_res, __hacxv8_res + __hacxv8_val, order, order)); \
	           __XRETURN __hacxv8_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchadd8 __hybrid_atomic_fetchadd8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchadd8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	__UINT8_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load8(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak8(__p, __res, __res + __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_add8 */

#ifndef __hybrid_atomic_fetchsub8
#ifdef __hybrid_atomic_fetchsub
#define __hybrid_atomic_fetchsub8 __hybrid_atomic_fetchsub
#elif defined(__hybrid_atomic_fetchadd)
#define __hybrid_atomic_fetchsub8(p, val, order) __hybrid_atomic_fetchadd(p, (__UINT8_TYPE__)(-(__INT8_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchadd8)
#define __hybrid_atomic_fetchsub8(p, val, order) __hybrid_atomic_fetchadd8(p, (__UINT8_TYPE__)(-(__INT8_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_subfetch8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchsub8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __hafx8_val = (val); __XRETURN __hybrid_atomic_subfetch8(p, __hafx8_val, order) + __hafx8_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchsub8 __hybrid_atomic_fetchsub8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchsub8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_subfetch8(__p, __val, __order) + __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load8) && defined(__hybrid_atomic_cmpxch_weak8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchsub8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __hacxv8_p = (p), __hacxv8_val = (val), __hacxv8_res; \
	           do __hacxv8_res = __hybrid_atomic_load8(__hacxv8_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak8(__hacxv8_p, __hacxv8_res, __hacxv8_res - __hacxv8_val, order, order)); \
	           __XRETURN __hacxv8_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchsub8 __hybrid_atomic_fetchsub8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchsub8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	__UINT8_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load8(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak8(__p, __res, __res - __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_sub8 */

#ifndef __hybrid_atomic_fetchand8
#ifdef __hybrid_atomic_fetchand
#define __hybrid_atomic_fetchand8 __hybrid_atomic_fetchand
#elif defined(__hybrid_atomic_load8) && defined(__hybrid_atomic_cmpxch_weak8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchand8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __hacxv8_p = (p), __hacxv8_val = (val), __hacxv8_res; \
	           do __hacxv8_res = __hybrid_atomic_load8(__hacxv8_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak8(__hacxv8_p, __hacxv8_res, __hacxv8_res & __hacxv8_val, order, order)); \
	           __XRETURN __hacxv8_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchand8 __hybrid_atomic_fetchand8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchand8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	__UINT8_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load8(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak8(__p, __res, __res & __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_and8 */

#ifndef __hybrid_atomic_fetchxor8
#ifdef __hybrid_atomic_fetchxor
#define __hybrid_atomic_fetchxor8 __hybrid_atomic_fetchxor
#elif defined(__hybrid_atomic_xorfetch8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchxor8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __hafx8_val = (val); __XRETURN __hybrid_atomic_xorfetch8(p, __hafx8_val, order) ^ __hafx8_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchxor8 __hybrid_atomic_fetchxor8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchxor8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_xorfetch8(__p, __val, __order) ^ __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load8) && defined(__hybrid_atomic_cmpxch_weak8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchxor8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __hacxv8_p = (p), __hacxv8_val = (val), __hacxv8_res; \
	           do __hacxv8_res = __hybrid_atomic_load8(__hacxv8_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak8(__hacxv8_p, __hacxv8_res, __hacxv8_res ^ __hacxv8_val, order, order)); \
	           __XRETURN __hacxv8_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchxor8 __hybrid_atomic_fetchxor8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchxor8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	__UINT8_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load8(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak8(__p, __res, __res ^ __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xor8 */

#ifndef __hybrid_atomic_fetchor8
#ifdef __hybrid_atomic_fetchor
#define __hybrid_atomic_fetchor8 __hybrid_atomic_fetchor
#elif defined(__hybrid_atomic_load8) && defined(__hybrid_atomic_cmpxch_weak8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchor8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __hacxv8_p = (p), __hacxv8_val = (val), __hacxv8_res; \
	           do __hacxv8_res = __hybrid_atomic_load8(__hacxv8_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak8(__hacxv8_p, __hacxv8_res, __hacxv8_res | __hacxv8_val, order, order)); \
	           __XRETURN __hacxv8_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchor8 __hybrid_atomic_fetchor8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchor8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	__UINT8_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load8(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak8(__p, __res, __res | __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_or8 */

#ifndef __hybrid_atomic_fetchnand8
#ifdef __hybrid_atomic_fetchnand
#define __hybrid_atomic_fetchnand8 __hybrid_atomic_fetchnand
#elif defined(__hybrid_atomic_load8) && defined(__hybrid_atomic_cmpxch_weak8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchnand8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __hacxv8_p = (p), __hacxv8_val = (val), __hacxv8_res; \
	           do __hacxv8_res = __hybrid_atomic_load8(__hacxv8_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak8(__hacxv8_p, __hacxv8_res, ~(__hacxv8_res & __hacxv8_val), order, order)); \
	           __XRETURN __hacxv8_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchnand8 __hybrid_atomic_fetchnand8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchnand8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	__UINT8_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load8(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak8(__p, __res, ~(__res & __val), __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_nand8 */

#ifndef __hybrid_atomic_fetchinc8
#ifdef __hybrid_atomic_fetchinc
#define __hybrid_atomic_fetchinc8 __hybrid_atomic_fetchinc
#elif defined(__hybrid_atomic_fetchadd8)
#define __hybrid_atomic_fetchinc8(p, order) __hybrid_atomic_fetchadd8(p, 1, order)
#elif defined(__hybrid_atomic_fetchsub8)
#define __hybrid_atomic_fetchinc8(p, order) __hybrid_atomic_fetchsub8(p, (__UINT8_TYPE__)-1, order)
#elif defined(__hybrid_atomic_incfetch8)
#define __hybrid_atomic_fetchinc8(p, order) (__hybrid_atomic_incfetch8(p, val, order) - 1)
#endif /* ... */
#endif /* !__hybrid_atomic_inc8 */

#ifndef __hybrid_atomic_fetchdec8
#ifdef __hybrid_atomic_fetchdec
#define __hybrid_atomic_fetchdec8 __hybrid_atomic_fetchdec
#elif defined(__hybrid_atomic_fetchsub8)
#define __hybrid_atomic_fetchdec8(p, order) __hybrid_atomic_fetchsub8(p, 1, order)
#elif defined(__hybrid_atomic_fetchadd8)
#define __hybrid_atomic_fetchdec8(p, order) __hybrid_atomic_fetchadd8(p, (__UINT8_TYPE__)-1, order)
#elif defined(__hybrid_atomic_decfetch8)
#define __hybrid_atomic_fetchdec8(p, order) (__hybrid_atomic_decfetch8(p, val, order) + 1)
#endif /* ... */
#endif /* !__hybrid_atomic_dec8 */

#ifndef __hybrid_atomic_addfetch8
#ifdef __hybrid_atomic_addfetch
#define __hybrid_atomic_addfetch8 __hybrid_atomic_addfetch
#elif defined(__hybrid_atomic_subfetch)
#define __hybrid_atomic_addfetch8(p, val, order) __hybrid_atomic_subfetch(p, (__UINT8_TYPE__)(-(__INT8_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_subfetch8)
#define __hybrid_atomic_addfetch8(p, val, order) __hybrid_atomic_subfetch8(p, (__UINT8_TYPE__)(-(__INT8_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchadd8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_addfetch8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __haxf8_val = (val); __XRETURN __hybrid_atomic_fetchadd8(p, __haxf8_val, order) + __haxf8_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_addfetch8 __hybrid_atomic_addfetch8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_addfetch8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchadd8(__p, __val, __order) + __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_addfetch8 */

#ifndef __hybrid_atomic_subfetch8
#ifdef __hybrid_atomic_subfetch
#define __hybrid_atomic_subfetch8 __hybrid_atomic_subfetch
#elif defined(__hybrid_atomic_addfetch)
#define __hybrid_atomic_subfetch8(p, val, order) __hybrid_atomic_addfetch(p, (__UINT8_TYPE__)(-(__INT8_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_addfetch8)
#define __hybrid_atomic_subfetch8(p, val, order) __hybrid_atomic_addfetch8(p, (__UINT8_TYPE__)(-(__INT8_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchsub8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_subfetch8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __haxf8_val = (val); __XRETURN __hybrid_atomic_fetchsub8(p, __haxf8_val, order) - __haxf8_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_subfetch8 __hybrid_atomic_subfetch8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_subfetch8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchsub8(__p, __val, __order) - __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_subfetch8 */

#ifndef __hybrid_atomic_andfetch8
#ifdef __hybrid_atomic_andfetch
#define __hybrid_atomic_andfetch8 __hybrid_atomic_andfetch
#elif defined(__hybrid_atomic_fetchand8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_andfetch8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __haxf8_val = (val); __XRETURN __hybrid_atomic_fetchand8(p, __haxf8_val, order) & __haxf8_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_andfetch8 __hybrid_atomic_andfetch8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_andfetch8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchand8(__p, __val, __order) & __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_andfetch8 */

#ifndef __hybrid_atomic_xorfetch8
#ifdef __hybrid_atomic_xorfetch
#define __hybrid_atomic_xorfetch8 __hybrid_atomic_xorfetch
#elif defined(__hybrid_atomic_fetchxor8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_xorfetch8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __haxf8_val = (val); __XRETURN __hybrid_atomic_fetchxor8(p, __haxf8_val, order) ^ __haxf8_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_xorfetch8 __hybrid_atomic_xorfetch8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xorfetch8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchxor8(__p, __val, __order) ^ __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xorfetch8 */

#ifndef __hybrid_atomic_orfetch8
#ifdef __hybrid_atomic_orfetch
#define __hybrid_atomic_orfetch8 __hybrid_atomic_orfetch
#elif defined(__hybrid_atomic_fetchor8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_orfetch8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __haxf8_val = (val); __XRETURN __hybrid_atomic_fetchor8(p, __haxf8_val, order) | __haxf8_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_orfetch8 __hybrid_atomic_orfetch8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_orfetch8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchor8(__p, __val, __order) | __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_orfetch8 */

#ifndef __hybrid_atomic_nandfetch8
#ifdef __hybrid_atomic_nandfetch
#define __hybrid_atomic_nandfetch8 __hybrid_atomic_nandfetch
#elif defined(__hybrid_atomic_fetchnand8)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_nandfetch8(p, val, order) \
	__XBLOCK({ __UINT8_TYPE__ __haxf8_val = (val); __XRETURN ~(__hybrid_atomic_fetchnand8(p, __haxf8_val, order) & __haxf8_val); })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_nandfetch8 __hybrid_atomic_nandfetch8
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ __NOTHROW_NCX(__hybrid_atomic_nandfetch8)(__UINT8_TYPE__ *__p, __UINT8_TYPE__ __val, int __order) {
	(void)__order;
	return ~(__hybrid_atomic_fetchnand8(__p, __val, __order) & __val);
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_nandfetch8 */

#ifndef __hybrid_atomic_incfetch8
#ifdef __hybrid_atomic_incfetch
#define __hybrid_atomic_incfetch8 __hybrid_atomic_incfetch
#elif defined(__hybrid_atomic_addfetch8)
#define __hybrid_atomic_incfetch8(p, order) __hybrid_atomic_addfetch8(p, 1, order)
#elif defined(__hybrid_atomic_subfetch8)
#define __hybrid_atomic_incfetch8(p, order) __hybrid_atomic_subfetch8(p, (__UINT8_TYPE__)-1, order)
#endif /* ... */
#endif /* !__hybrid_atomic_incfetch8 */

#ifndef __hybrid_atomic_decfetch8
#ifdef __hybrid_atomic_decfetch
#define __hybrid_atomic_decfetch8 __hybrid_atomic_decfetch
#elif defined(__hybrid_atomic_subfetch8)
#define __hybrid_atomic_decfetch8(p, order) __hybrid_atomic_subfetch8(p, 1, order)
#elif defined(__hybrid_atomic_addfetch8)
#define __hybrid_atomic_decfetch8(p, order) __hybrid_atomic_addfetch8(p, (__UINT8_TYPE__)-1, order)
#endif /* ... */
#endif /* !__hybrid_atomic_decfetch8 */

#ifndef __hybrid_atomic_inc8
#ifdef __hybrid_atomic_inc
#define __hybrid_atomic_inc8 __hybrid_atomic_inc
#elif defined(__hybrid_atomic_add8)
#define __hybrid_atomic_inc8(p, order) __hybrid_atomic_add8(p, 1, order)
#elif defined(__hybrid_atomic_fetchinc8)
#define __hybrid_atomic_inc8 (void)__hybrid_atomic_fetchinc8
#elif defined(__hybrid_atomic_incfetch8)
#define __hybrid_atomic_inc8 (void)__hybrid_atomic_incfetch8
#endif /* ... */
#endif /* !__hybrid_atomic_inc8 */

#ifndef __hybrid_atomic_dec8
#ifdef __hybrid_atomic_dec
#define __hybrid_atomic_dec8 __hybrid_atomic_dec
#elif defined(__hybrid_atomic_sub8)
#define __hybrid_atomic_dec8(p, order) __hybrid_atomic_sub8(p, 1, order)
#elif defined(__hybrid_atomic_fetchdec8)
#define __hybrid_atomic_dec8 (void)__hybrid_atomic_fetchdec8
#elif defined(__hybrid_atomic_decfetch8)
#define __hybrid_atomic_dec8 (void)__hybrid_atomic_decfetch8
#endif /* ... */
#endif /* !__hybrid_atomic_dec8 */

#ifndef __hybrid_atomic_add8
#ifdef __hybrid_atomic_add
#define __hybrid_atomic_add8 __hybrid_atomic_add
#elif defined(__hybrid_atomic_fetchadd8)
#define __hybrid_atomic_add8 (void)__hybrid_atomic_fetchadd8
#elif defined(__hybrid_atomic_addfetch8)
#define __hybrid_atomic_add8 (void)__hybrid_atomic_addfetch8
#endif /* ... */
#endif /* !__hybrid_atomic_add8 */

#ifndef __hybrid_atomic_sub8
#ifdef __hybrid_atomic_sub
#define __hybrid_atomic_sub8 __hybrid_atomic_sub
#elif defined(__hybrid_atomic_fetchsub8)
#define __hybrid_atomic_sub8 (void)__hybrid_atomic_fetchsub8
#elif defined(__hybrid_atomic_subfetch8)
#define __hybrid_atomic_sub8 (void)__hybrid_atomic_subfetch8
#endif /* ... */
#endif /* !__hybrid_atomic_sub8 */

#ifndef __hybrid_atomic_and8
#ifdef __hybrid_atomic_and
#define __hybrid_atomic_and8 __hybrid_atomic_and
#elif defined(__hybrid_atomic_fetchand8)
#define __hybrid_atomic_and8 (void)__hybrid_atomic_fetchand8
#elif defined(__hybrid_atomic_andfetch8)
#define __hybrid_atomic_and8 (void)__hybrid_atomic_andfetch8
#endif /* ... */
#endif /* !__hybrid_atomic_and8 */

#ifndef __hybrid_atomic_xor8
#ifdef __hybrid_atomic_xor
#define __hybrid_atomic_xor8 __hybrid_atomic_xor
#elif defined(__hybrid_atomic_fetchxor8)
#define __hybrid_atomic_xor8 (void)__hybrid_atomic_fetchxor8
#elif defined(__hybrid_atomic_xorfetch8)
#define __hybrid_atomic_xor8 (void)__hybrid_atomic_xorfetch8
#endif /* ... */
#endif /* !__hybrid_atomic_xor8 */

#ifndef __hybrid_atomic_or8
#ifdef __hybrid_atomic_or
#define __hybrid_atomic_or8 __hybrid_atomic_or
#elif defined(__hybrid_atomic_fetchor8)
#define __hybrid_atomic_or8 (void)__hybrid_atomic_fetchor8
#elif defined(__hybrid_atomic_orfetch8)
#define __hybrid_atomic_or8 (void)__hybrid_atomic_orfetch8
#endif /* ... */
#endif /* !__hybrid_atomic_or8 */

#ifndef __hybrid_atomic_nand8
#ifdef __hybrid_atomic_nand
#define __hybrid_atomic_nand8 __hybrid_atomic_nand
#elif defined(__hybrid_atomic_fetchnand8)
#define __hybrid_atomic_nand8 (void)__hybrid_atomic_fetchnand8
#elif defined(__hybrid_atomic_nandfetch8)
#define __hybrid_atomic_nand8 (void)__hybrid_atomic_nandfetch8
#endif /* ... */
#endif /* !__hybrid_atomic_nand8 */

#ifndef __hybrid_atomic_cmpxch16
#ifdef __hybrid_atomic_cmpxch
#define __hybrid_atomic_cmpxch16 __hybrid_atomic_cmpxch
#elif defined(__hybrid_atomic_cmpxch_val16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch16(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT16_TYPE__ __hacx16_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val16(p, __hacx16_ov, newval, succ, fail) == __hacx16_ov; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch16 __hybrid_atomic_cmpxch16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __oldval, __UINT16_TYPE__ __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
	return __hybrid_atomic_cmpxch_val16(__p, __oldval, __newval, __succ, __fail) == __oldval;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch16 */

#ifndef __hybrid_atomic_cmpxch_weak16
#ifdef __hybrid_atomic_cmpxch_weak
#define __hybrid_atomic_cmpxch_weak16 __hybrid_atomic_cmpxch_weak
#elif defined(__hybrid_atomic_cmpxch16)
#define __hybrid_atomic_cmpxch_weak16 __hybrid_atomic_cmpxch16
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch_weak16 */

#ifndef __hybrid_atomic_load16
#ifdef __hybrid_atomic_load
#define __hybrid_atomic_load16 __hybrid_atomic_load
#elif defined(__hybrid_atomic_fetchadd16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_fetchadd16(p, 0, order)
#elif defined(__hybrid_atomic_addfetch16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_addfetch16(p, 0, order)
#elif defined(__hybrid_atomic_fetchsub16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_fetchsub16(p, 0, order)
#elif defined(__hybrid_atomic_subfetch16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_subfetch16(p, 0, order)
#elif defined(__hybrid_atomic_fetchand16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_fetchand16(p, (__UINT16_TYPE__)-1, order)
#elif defined(__hybrid_atomic_andfetch16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_andfetch16(p, (__UINT16_TYPE__)-1, order)
#elif defined(__hybrid_atomic_fetchor16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_fetchor16(p, 0, order)
#elif defined(__hybrid_atomic_orfetch16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_orfetch16(p, 0, order)
#elif defined(__hybrid_atomic_fetchxor16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_fetchxor16(p, 0, order)
#elif defined(__hybrid_atomic_xorfetch16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_xorfetch16(p, 0, order)
#elif defined(__hybrid_atomic_cmpxch_val16)
#define __hybrid_atomic_load16(p, order) __hybrid_atomic_cmpxch_val16(p, 0, 0, order, order)
#elif defined(__hybrid_atomic_cmpxch_weak16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_load16(p, order) \
	__XBLOCK({ __UINT16_TYPE__ const *__hal16_p = (p); __UINT16_TYPE__ __hal16_res; \
	           do { __hal16_res = *__hal16_p; __COMPILER_READ_BARRIER(); \
	           } while (!__hybrid_atomic_cmpxch_weak((__UINT16_TYPE__ *)__hal16_p, __hal16_res, __hal16_res, order, order)); \
	           __XRETURN __hal16_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_load16 __hybrid_atomic_load16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_load16)(__UINT16_TYPE__ const *__p, int __order) {
	__UINT16_TYPE__ __res;
	(void)__order;
	do { __res = *__p; __COMPILER_READ_BARRIER();
	} while (!__hybrid_atomic_cmpxch_weak((__UINT16_TYPE__ *)__p, __res, __res, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_load16 */

#ifndef __hybrid_atomic_cmpxch_val16
#ifdef __hybrid_atomic_cmpxch_val
#define __hybrid_atomic_cmpxch_val16 __hybrid_atomic_cmpxch_val
#elif defined(__hybrid_atomic_cmpxch_weak16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch_val16(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT16_TYPE__ __hacxv16_p = (p), __hacxv16_ov = (oldval), __hacxv16_nv = (newval), __hacxv16_res; \
	           do if ((__hacxv16_res = __hybrid_atomic_load16(__hacxv16_p, __ATOMIC_ACQUIRE)) != __hacxv16_ov) break; \
	           while (!__hybrid_atomic_cmpxch_weak16(__hacxv16_p, __hacxv16_res, __hacxv16_nv, succ, fail)); \
	           __XRETURN __hacxv16_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch_val16 __hybrid_atomic_cmpxch_val16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_cmpxch_val16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __oldval, __UINT16_TYPE__ __newval, int __succ, int __fail) {
	__UINT16_TYPE__ __res;
	(void)__succ, (void)__fail;
	do if ((__res = __hybrid_atomic_load16(__p, __ATOMIC_ACQUIRE)) != __oldval) break;
	while (!__hybrid_atomic_cmpxch_weak16(__p, __res, __newval, __succ, __fail));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch_val16 */

#if !defined(__hybrid_atomic_cmpxch16) && defined(__hybrid_atomic_cmpxch_val16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch16(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT16_TYPE__ __hacx16_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val16(p, __hacx16_ov, newval, succ, fail) == __hacx16_ov; })
#else /* __NO_XBLOCK */
__LOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __oldval, __UINT16_TYPE__ __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
	return __hybrid_atomic_cmpxch_val16(__p, __oldval, __newval, __succ, __fail) == __oldval;
}
#endif /* !__NO_XBLOCK */
#endif /* !__hybrid_atomic_cmpxch16 && __hybrid_atomic_cmpxch_val16 */

#if !defined(__hybrid_atomic_cmpxch_weak16) && defined(__hybrid_atomic_cmpxch16)
#define __hybrid_atomic_cmpxch_weak16 __hybrid_atomic_cmpxch16
#endif /* !__hybrid_atomic_cmpxch_weak16 && __hybrid_atomic_cmpxch16 */

#ifndef __hybrid_atomic_xch16
#ifdef __hybrid_atomic_xch
#define __hybrid_atomic_xch16 __hybrid_atomic_xch
#elif defined(__hybrid_atomic_load16) && defined(__hybrid_atomic_cmpxch_weak16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_xch16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ *__hal16_p = (p); __UINT16_TYPE__ __hal16_res, __hal16_val = (val); \
	           do __hal16_res = __hybrid_atomic_load(__hal16_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak(__hal16_p, __hal16_res, __hal16_val, order, order)); \
	           __XRETURN __hal16_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_xch16 __hybrid_atomic_xch16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xch16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	__UINT16_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak(__p, __res, __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xch16 */

#ifndef __hybrid_atomic_store16
#ifdef __hybrid_atomic_store
#define __hybrid_atomic_store16 __hybrid_atomic_store
#elif defined(__hybrid_atomic_xch16)
#define __hybrid_atomic_store16 (void)__hybrid_atomic_xch16
#endif /* ... */
#endif /* !__hybrid_atomic_store16 */

#ifndef __hybrid_atomic_fetchadd16
#ifdef __hybrid_atomic_fetchadd
#define __hybrid_atomic_fetchadd16 __hybrid_atomic_fetchadd
#elif defined(__hybrid_atomic_fetchsub)
#define __hybrid_atomic_fetchadd16(p, val, order) __hybrid_atomic_fetchsub(p, (__UINT16_TYPE__)(-(__INT16_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchsub16)
#define __hybrid_atomic_fetchadd16(p, val, order) __hybrid_atomic_fetchsub16(p, (__UINT16_TYPE__)(-(__INT16_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_addfetch16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchadd16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __hafx16_val = (val); __XRETURN __hybrid_atomic_addfetch16(p, __hafx16_val, order) - __hafx16_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchadd16 __hybrid_atomic_fetchadd16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchadd16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_addfetch16(__p, __val, __order) - __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load16) && defined(__hybrid_atomic_cmpxch_weak16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchadd16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __hacxv16_p = (p), __hacxv16_val = (val), __hacxv16_res; \
	           do __hacxv16_res = __hybrid_atomic_load16(__hacxv16_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak16(__hacxv16_p, __hacxv16_res, __hacxv16_res + __hacxv16_val, order, order)); \
	           __XRETURN __hacxv16_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchadd16 __hybrid_atomic_fetchadd16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchadd16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	__UINT16_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load16(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak16(__p, __res, __res + __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_add16 */

#ifndef __hybrid_atomic_fetchsub16
#ifdef __hybrid_atomic_fetchsub
#define __hybrid_atomic_fetchsub16 __hybrid_atomic_fetchsub
#elif defined(__hybrid_atomic_fetchadd)
#define __hybrid_atomic_fetchsub16(p, val, order) __hybrid_atomic_fetchadd(p, (__UINT16_TYPE__)(-(__INT16_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchadd16)
#define __hybrid_atomic_fetchsub16(p, val, order) __hybrid_atomic_fetchadd16(p, (__UINT16_TYPE__)(-(__INT16_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_subfetch16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchsub16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __hafx16_val = (val); __XRETURN __hybrid_atomic_subfetch16(p, __hafx16_val, order) + __hafx16_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchsub16 __hybrid_atomic_fetchsub16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchsub16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_subfetch16(__p, __val, __order) + __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load16) && defined(__hybrid_atomic_cmpxch_weak16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchsub16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __hacxv16_p = (p), __hacxv16_val = (val), __hacxv16_res; \
	           do __hacxv16_res = __hybrid_atomic_load16(__hacxv16_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak16(__hacxv16_p, __hacxv16_res, __hacxv16_res - __hacxv16_val, order, order)); \
	           __XRETURN __hacxv16_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchsub16 __hybrid_atomic_fetchsub16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchsub16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	__UINT16_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load16(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak16(__p, __res, __res - __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_sub16 */

#ifndef __hybrid_atomic_fetchand16
#ifdef __hybrid_atomic_fetchand
#define __hybrid_atomic_fetchand16 __hybrid_atomic_fetchand
#elif defined(__hybrid_atomic_load16) && defined(__hybrid_atomic_cmpxch_weak16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchand16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __hacxv16_p = (p), __hacxv16_val = (val), __hacxv16_res; \
	           do __hacxv16_res = __hybrid_atomic_load16(__hacxv16_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak16(__hacxv16_p, __hacxv16_res, __hacxv16_res & __hacxv16_val, order, order)); \
	           __XRETURN __hacxv16_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchand16 __hybrid_atomic_fetchand16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchand16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	__UINT16_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load16(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak16(__p, __res, __res & __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_and16 */

#ifndef __hybrid_atomic_fetchxor16
#ifdef __hybrid_atomic_fetchxor
#define __hybrid_atomic_fetchxor16 __hybrid_atomic_fetchxor
#elif defined(__hybrid_atomic_xorfetch16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchxor16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __hafx16_val = (val); __XRETURN __hybrid_atomic_xorfetch16(p, __hafx16_val, order) ^ __hafx16_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchxor16 __hybrid_atomic_fetchxor16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchxor16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_xorfetch16(__p, __val, __order) ^ __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load16) && defined(__hybrid_atomic_cmpxch_weak16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchxor16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __hacxv16_p = (p), __hacxv16_val = (val), __hacxv16_res; \
	           do __hacxv16_res = __hybrid_atomic_load16(__hacxv16_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak16(__hacxv16_p, __hacxv16_res, __hacxv16_res ^ __hacxv16_val, order, order)); \
	           __XRETURN __hacxv16_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchxor16 __hybrid_atomic_fetchxor16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchxor16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	__UINT16_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load16(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak16(__p, __res, __res ^ __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xor16 */

#ifndef __hybrid_atomic_fetchor16
#ifdef __hybrid_atomic_fetchor
#define __hybrid_atomic_fetchor16 __hybrid_atomic_fetchor
#elif defined(__hybrid_atomic_load16) && defined(__hybrid_atomic_cmpxch_weak16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchor16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __hacxv16_p = (p), __hacxv16_val = (val), __hacxv16_res; \
	           do __hacxv16_res = __hybrid_atomic_load16(__hacxv16_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak16(__hacxv16_p, __hacxv16_res, __hacxv16_res | __hacxv16_val, order, order)); \
	           __XRETURN __hacxv16_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchor16 __hybrid_atomic_fetchor16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchor16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	__UINT16_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load16(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak16(__p, __res, __res | __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_or16 */

#ifndef __hybrid_atomic_fetchnand16
#ifdef __hybrid_atomic_fetchnand
#define __hybrid_atomic_fetchnand16 __hybrid_atomic_fetchnand
#elif defined(__hybrid_atomic_load16) && defined(__hybrid_atomic_cmpxch_weak16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchnand16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __hacxv16_p = (p), __hacxv16_val = (val), __hacxv16_res; \
	           do __hacxv16_res = __hybrid_atomic_load16(__hacxv16_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak16(__hacxv16_p, __hacxv16_res, ~(__hacxv16_res & __hacxv16_val), order, order)); \
	           __XRETURN __hacxv16_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchnand16 __hybrid_atomic_fetchnand16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchnand16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	__UINT16_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load16(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak16(__p, __res, ~(__res & __val), __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_nand16 */

#ifndef __hybrid_atomic_fetchinc16
#ifdef __hybrid_atomic_fetchinc
#define __hybrid_atomic_fetchinc16 __hybrid_atomic_fetchinc
#elif defined(__hybrid_atomic_fetchadd16)
#define __hybrid_atomic_fetchinc16(p, order) __hybrid_atomic_fetchadd16(p, 1, order)
#elif defined(__hybrid_atomic_fetchsub16)
#define __hybrid_atomic_fetchinc16(p, order) __hybrid_atomic_fetchsub16(p, (__UINT16_TYPE__)-1, order)
#elif defined(__hybrid_atomic_incfetch16)
#define __hybrid_atomic_fetchinc16(p, order) (__hybrid_atomic_incfetch16(p, val, order) - 1)
#endif /* ... */
#endif /* !__hybrid_atomic_inc16 */

#ifndef __hybrid_atomic_fetchdec16
#ifdef __hybrid_atomic_fetchdec
#define __hybrid_atomic_fetchdec16 __hybrid_atomic_fetchdec
#elif defined(__hybrid_atomic_fetchsub16)
#define __hybrid_atomic_fetchdec16(p, order) __hybrid_atomic_fetchsub16(p, 1, order)
#elif defined(__hybrid_atomic_fetchadd16)
#define __hybrid_atomic_fetchdec16(p, order) __hybrid_atomic_fetchadd16(p, (__UINT16_TYPE__)-1, order)
#elif defined(__hybrid_atomic_decfetch16)
#define __hybrid_atomic_fetchdec16(p, order) (__hybrid_atomic_decfetch16(p, val, order) + 1)
#endif /* ... */
#endif /* !__hybrid_atomic_dec16 */

#ifndef __hybrid_atomic_addfetch16
#ifdef __hybrid_atomic_addfetch
#define __hybrid_atomic_addfetch16 __hybrid_atomic_addfetch
#elif defined(__hybrid_atomic_subfetch)
#define __hybrid_atomic_addfetch16(p, val, order) __hybrid_atomic_subfetch(p, (__UINT16_TYPE__)(-(__INT16_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_subfetch16)
#define __hybrid_atomic_addfetch16(p, val, order) __hybrid_atomic_subfetch16(p, (__UINT16_TYPE__)(-(__INT16_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchadd16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_addfetch16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __haxf16_val = (val); __XRETURN __hybrid_atomic_fetchadd16(p, __haxf16_val, order) + __haxf16_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_addfetch16 __hybrid_atomic_addfetch16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_addfetch16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchadd16(__p, __val, __order) + __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_addfetch16 */

#ifndef __hybrid_atomic_subfetch16
#ifdef __hybrid_atomic_subfetch
#define __hybrid_atomic_subfetch16 __hybrid_atomic_subfetch
#elif defined(__hybrid_atomic_addfetch)
#define __hybrid_atomic_subfetch16(p, val, order) __hybrid_atomic_addfetch(p, (__UINT16_TYPE__)(-(__INT16_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_addfetch16)
#define __hybrid_atomic_subfetch16(p, val, order) __hybrid_atomic_addfetch16(p, (__UINT16_TYPE__)(-(__INT16_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchsub16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_subfetch16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __haxf16_val = (val); __XRETURN __hybrid_atomic_fetchsub16(p, __haxf16_val, order) - __haxf16_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_subfetch16 __hybrid_atomic_subfetch16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_subfetch16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchsub16(__p, __val, __order) - __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_subfetch16 */

#ifndef __hybrid_atomic_andfetch16
#ifdef __hybrid_atomic_andfetch
#define __hybrid_atomic_andfetch16 __hybrid_atomic_andfetch
#elif defined(__hybrid_atomic_fetchand16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_andfetch16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __haxf16_val = (val); __XRETURN __hybrid_atomic_fetchand16(p, __haxf16_val, order) & __haxf16_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_andfetch16 __hybrid_atomic_andfetch16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_andfetch16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchand16(__p, __val, __order) & __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_andfetch16 */

#ifndef __hybrid_atomic_xorfetch16
#ifdef __hybrid_atomic_xorfetch
#define __hybrid_atomic_xorfetch16 __hybrid_atomic_xorfetch
#elif defined(__hybrid_atomic_fetchxor16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_xorfetch16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __haxf16_val = (val); __XRETURN __hybrid_atomic_fetchxor16(p, __haxf16_val, order) ^ __haxf16_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_xorfetch16 __hybrid_atomic_xorfetch16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xorfetch16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchxor16(__p, __val, __order) ^ __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xorfetch16 */

#ifndef __hybrid_atomic_orfetch16
#ifdef __hybrid_atomic_orfetch
#define __hybrid_atomic_orfetch16 __hybrid_atomic_orfetch
#elif defined(__hybrid_atomic_fetchor16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_orfetch16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __haxf16_val = (val); __XRETURN __hybrid_atomic_fetchor16(p, __haxf16_val, order) | __haxf16_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_orfetch16 __hybrid_atomic_orfetch16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_orfetch16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchor16(__p, __val, __order) | __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_orfetch16 */

#ifndef __hybrid_atomic_nandfetch16
#ifdef __hybrid_atomic_nandfetch
#define __hybrid_atomic_nandfetch16 __hybrid_atomic_nandfetch
#elif defined(__hybrid_atomic_fetchnand16)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_nandfetch16(p, val, order) \
	__XBLOCK({ __UINT16_TYPE__ __haxf16_val = (val); __XRETURN ~(__hybrid_atomic_fetchnand16(p, __haxf16_val, order) & __haxf16_val); })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_nandfetch16 __hybrid_atomic_nandfetch16
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(__hybrid_atomic_nandfetch16)(__UINT16_TYPE__ *__p, __UINT16_TYPE__ __val, int __order) {
	(void)__order;
	return ~(__hybrid_atomic_fetchnand16(__p, __val, __order) & __val);
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_nandfetch16 */

#ifndef __hybrid_atomic_incfetch16
#ifdef __hybrid_atomic_incfetch
#define __hybrid_atomic_incfetch16 __hybrid_atomic_incfetch
#elif defined(__hybrid_atomic_addfetch16)
#define __hybrid_atomic_incfetch16(p, order) __hybrid_atomic_addfetch16(p, 1, order)
#elif defined(__hybrid_atomic_subfetch16)
#define __hybrid_atomic_incfetch16(p, order) __hybrid_atomic_subfetch16(p, (__UINT16_TYPE__)-1, order)
#endif /* ... */
#endif /* !__hybrid_atomic_incfetch16 */

#ifndef __hybrid_atomic_decfetch16
#ifdef __hybrid_atomic_decfetch
#define __hybrid_atomic_decfetch16 __hybrid_atomic_decfetch
#elif defined(__hybrid_atomic_subfetch16)
#define __hybrid_atomic_decfetch16(p, order) __hybrid_atomic_subfetch16(p, 1, order)
#elif defined(__hybrid_atomic_addfetch16)
#define __hybrid_atomic_decfetch16(p, order) __hybrid_atomic_addfetch16(p, (__UINT16_TYPE__)-1, order)
#endif /* ... */
#endif /* !__hybrid_atomic_decfetch16 */

#ifndef __hybrid_atomic_inc16
#ifdef __hybrid_atomic_inc
#define __hybrid_atomic_inc16 __hybrid_atomic_inc
#elif defined(__hybrid_atomic_add16)
#define __hybrid_atomic_inc16(p, order) __hybrid_atomic_add16(p, 1, order)
#elif defined(__hybrid_atomic_fetchinc16)
#define __hybrid_atomic_inc16 (void)__hybrid_atomic_fetchinc16
#elif defined(__hybrid_atomic_incfetch16)
#define __hybrid_atomic_inc16 (void)__hybrid_atomic_incfetch16
#endif /* ... */
#endif /* !__hybrid_atomic_inc16 */

#ifndef __hybrid_atomic_dec16
#ifdef __hybrid_atomic_dec
#define __hybrid_atomic_dec16 __hybrid_atomic_dec
#elif defined(__hybrid_atomic_sub16)
#define __hybrid_atomic_dec16(p, order) __hybrid_atomic_sub16(p, 1, order)
#elif defined(__hybrid_atomic_fetchdec16)
#define __hybrid_atomic_dec16 (void)__hybrid_atomic_fetchdec16
#elif defined(__hybrid_atomic_decfetch16)
#define __hybrid_atomic_dec16 (void)__hybrid_atomic_decfetch16
#endif /* ... */
#endif /* !__hybrid_atomic_dec16 */

#ifndef __hybrid_atomic_add16
#ifdef __hybrid_atomic_add
#define __hybrid_atomic_add16 __hybrid_atomic_add
#elif defined(__hybrid_atomic_fetchadd16)
#define __hybrid_atomic_add16 (void)__hybrid_atomic_fetchadd16
#elif defined(__hybrid_atomic_addfetch16)
#define __hybrid_atomic_add16 (void)__hybrid_atomic_addfetch16
#endif /* ... */
#endif /* !__hybrid_atomic_add16 */

#ifndef __hybrid_atomic_sub16
#ifdef __hybrid_atomic_sub
#define __hybrid_atomic_sub16 __hybrid_atomic_sub
#elif defined(__hybrid_atomic_fetchsub16)
#define __hybrid_atomic_sub16 (void)__hybrid_atomic_fetchsub16
#elif defined(__hybrid_atomic_subfetch16)
#define __hybrid_atomic_sub16 (void)__hybrid_atomic_subfetch16
#endif /* ... */
#endif /* !__hybrid_atomic_sub16 */

#ifndef __hybrid_atomic_and16
#ifdef __hybrid_atomic_and
#define __hybrid_atomic_and16 __hybrid_atomic_and
#elif defined(__hybrid_atomic_fetchand16)
#define __hybrid_atomic_and16 (void)__hybrid_atomic_fetchand16
#elif defined(__hybrid_atomic_andfetch16)
#define __hybrid_atomic_and16 (void)__hybrid_atomic_andfetch16
#endif /* ... */
#endif /* !__hybrid_atomic_and16 */

#ifndef __hybrid_atomic_xor16
#ifdef __hybrid_atomic_xor
#define __hybrid_atomic_xor16 __hybrid_atomic_xor
#elif defined(__hybrid_atomic_fetchxor16)
#define __hybrid_atomic_xor16 (void)__hybrid_atomic_fetchxor16
#elif defined(__hybrid_atomic_xorfetch16)
#define __hybrid_atomic_xor16 (void)__hybrid_atomic_xorfetch16
#endif /* ... */
#endif /* !__hybrid_atomic_xor16 */

#ifndef __hybrid_atomic_or16
#ifdef __hybrid_atomic_or
#define __hybrid_atomic_or16 __hybrid_atomic_or
#elif defined(__hybrid_atomic_fetchor16)
#define __hybrid_atomic_or16 (void)__hybrid_atomic_fetchor16
#elif defined(__hybrid_atomic_orfetch16)
#define __hybrid_atomic_or16 (void)__hybrid_atomic_orfetch16
#endif /* ... */
#endif /* !__hybrid_atomic_or16 */

#ifndef __hybrid_atomic_nand16
#ifdef __hybrid_atomic_nand
#define __hybrid_atomic_nand16 __hybrid_atomic_nand
#elif defined(__hybrid_atomic_fetchnand16)
#define __hybrid_atomic_nand16 (void)__hybrid_atomic_fetchnand16
#elif defined(__hybrid_atomic_nandfetch16)
#define __hybrid_atomic_nand16 (void)__hybrid_atomic_nandfetch16
#endif /* ... */
#endif /* !__hybrid_atomic_nand16 */

#ifndef __hybrid_atomic_cmpxch32
#ifdef __hybrid_atomic_cmpxch
#define __hybrid_atomic_cmpxch32 __hybrid_atomic_cmpxch
#elif defined(__hybrid_atomic_cmpxch_val32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch32(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT32_TYPE__ __hacx32_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val32(p, __hacx32_ov, newval, succ, fail) == __hacx32_ov; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch32 __hybrid_atomic_cmpxch32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __oldval, __UINT32_TYPE__ __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
	return __hybrid_atomic_cmpxch_val32(__p, __oldval, __newval, __succ, __fail) == __oldval;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch32 */

#ifndef __hybrid_atomic_cmpxch_weak32
#ifdef __hybrid_atomic_cmpxch_weak
#define __hybrid_atomic_cmpxch_weak32 __hybrid_atomic_cmpxch_weak
#elif defined(__hybrid_atomic_cmpxch32)
#define __hybrid_atomic_cmpxch_weak32 __hybrid_atomic_cmpxch32
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch_weak32 */

#ifndef __hybrid_atomic_load32
#ifdef __hybrid_atomic_load
#define __hybrid_atomic_load32 __hybrid_atomic_load
#elif defined(__hybrid_atomic_fetchadd32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_fetchadd32(p, 0, order)
#elif defined(__hybrid_atomic_addfetch32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_addfetch32(p, 0, order)
#elif defined(__hybrid_atomic_fetchsub32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_fetchsub32(p, 0, order)
#elif defined(__hybrid_atomic_subfetch32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_subfetch32(p, 0, order)
#elif defined(__hybrid_atomic_fetchand32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_fetchand32(p, (__UINT32_TYPE__)-1, order)
#elif defined(__hybrid_atomic_andfetch32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_andfetch32(p, (__UINT32_TYPE__)-1, order)
#elif defined(__hybrid_atomic_fetchor32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_fetchor32(p, 0, order)
#elif defined(__hybrid_atomic_orfetch32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_orfetch32(p, 0, order)
#elif defined(__hybrid_atomic_fetchxor32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_fetchxor32(p, 0, order)
#elif defined(__hybrid_atomic_xorfetch32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_xorfetch32(p, 0, order)
#elif defined(__hybrid_atomic_cmpxch_val32)
#define __hybrid_atomic_load32(p, order) __hybrid_atomic_cmpxch_val32(p, 0, 0, order, order)
#elif defined(__hybrid_atomic_cmpxch_weak32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_load32(p, order) \
	__XBLOCK({ __UINT32_TYPE__ const *__hal32_p = (p); __UINT32_TYPE__ __hal32_res; \
	           do { __hal32_res = *__hal32_p; __COMPILER_READ_BARRIER(); \
	           } while (!__hybrid_atomic_cmpxch_weak((__UINT32_TYPE__ *)__hal32_p, __hal32_res, __hal32_res, order, order)); \
	           __XRETURN __hal32_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_load32 __hybrid_atomic_load32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_load32)(__UINT32_TYPE__ const *__p, int __order) {
	__UINT32_TYPE__ __res;
	(void)__order;
	do { __res = *__p; __COMPILER_READ_BARRIER();
	} while (!__hybrid_atomic_cmpxch_weak((__UINT32_TYPE__ *)__p, __res, __res, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_load32 */

#ifndef __hybrid_atomic_cmpxch_val32
#ifdef __hybrid_atomic_cmpxch_val
#define __hybrid_atomic_cmpxch_val32 __hybrid_atomic_cmpxch_val
#elif defined(__hybrid_atomic_cmpxch_weak32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch_val32(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT32_TYPE__ __hacxv32_p = (p), __hacxv32_ov = (oldval), __hacxv32_nv = (newval), __hacxv32_res; \
	           do if ((__hacxv32_res = __hybrid_atomic_load32(__hacxv32_p, __ATOMIC_ACQUIRE)) != __hacxv32_ov) break; \
	           while (!__hybrid_atomic_cmpxch_weak32(__hacxv32_p, __hacxv32_res, __hacxv32_nv, succ, fail)); \
	           __XRETURN __hacxv32_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch_val32 __hybrid_atomic_cmpxch_val32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_cmpxch_val32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __oldval, __UINT32_TYPE__ __newval, int __succ, int __fail) {
	__UINT32_TYPE__ __res;
	(void)__succ, (void)__fail;
	do if ((__res = __hybrid_atomic_load32(__p, __ATOMIC_ACQUIRE)) != __oldval) break;
	while (!__hybrid_atomic_cmpxch_weak32(__p, __res, __newval, __succ, __fail));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch_val32 */

#if !defined(__hybrid_atomic_cmpxch32) && defined(__hybrid_atomic_cmpxch_val32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch32(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT32_TYPE__ __hacx32_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val32(p, __hacx32_ov, newval, succ, fail) == __hacx32_ov; })
#else /* __NO_XBLOCK */
__LOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __oldval, __UINT32_TYPE__ __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
	return __hybrid_atomic_cmpxch_val32(__p, __oldval, __newval, __succ, __fail) == __oldval;
}
#endif /* !__NO_XBLOCK */
#endif /* !__hybrid_atomic_cmpxch32 && __hybrid_atomic_cmpxch_val32 */

#if !defined(__hybrid_atomic_cmpxch_weak32) && defined(__hybrid_atomic_cmpxch32)
#define __hybrid_atomic_cmpxch_weak32 __hybrid_atomic_cmpxch32
#endif /* !__hybrid_atomic_cmpxch_weak32 && __hybrid_atomic_cmpxch32 */

#ifndef __hybrid_atomic_xch32
#ifdef __hybrid_atomic_xch
#define __hybrid_atomic_xch32 __hybrid_atomic_xch
#elif defined(__hybrid_atomic_load32) && defined(__hybrid_atomic_cmpxch_weak32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_xch32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ *__hal32_p = (p); __UINT32_TYPE__ __hal32_res, __hal32_val = (val); \
	           do __hal32_res = __hybrid_atomic_load(__hal32_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak(__hal32_p, __hal32_res, __hal32_val, order, order)); \
	           __XRETURN __hal32_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_xch32 __hybrid_atomic_xch32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xch32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	__UINT32_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak(__p, __res, __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xch32 */

#ifndef __hybrid_atomic_store32
#ifdef __hybrid_atomic_store
#define __hybrid_atomic_store32 __hybrid_atomic_store
#elif defined(__hybrid_atomic_xch32)
#define __hybrid_atomic_store32 (void)__hybrid_atomic_xch32
#endif /* ... */
#endif /* !__hybrid_atomic_store32 */

#ifndef __hybrid_atomic_fetchadd32
#ifdef __hybrid_atomic_fetchadd
#define __hybrid_atomic_fetchadd32 __hybrid_atomic_fetchadd
#elif defined(__hybrid_atomic_fetchsub)
#define __hybrid_atomic_fetchadd32(p, val, order) __hybrid_atomic_fetchsub(p, (__UINT32_TYPE__)(-(__INT32_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchsub32)
#define __hybrid_atomic_fetchadd32(p, val, order) __hybrid_atomic_fetchsub32(p, (__UINT32_TYPE__)(-(__INT32_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_addfetch32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchadd32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __hafx32_val = (val); __XRETURN __hybrid_atomic_addfetch32(p, __hafx32_val, order) - __hafx32_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchadd32 __hybrid_atomic_fetchadd32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchadd32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_addfetch32(__p, __val, __order) - __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load32) && defined(__hybrid_atomic_cmpxch_weak32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchadd32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __hacxv32_p = (p), __hacxv32_val = (val), __hacxv32_res; \
	           do __hacxv32_res = __hybrid_atomic_load32(__hacxv32_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak32(__hacxv32_p, __hacxv32_res, __hacxv32_res + __hacxv32_val, order, order)); \
	           __XRETURN __hacxv32_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchadd32 __hybrid_atomic_fetchadd32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchadd32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	__UINT32_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load32(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak32(__p, __res, __res + __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_add32 */

#ifndef __hybrid_atomic_fetchsub32
#ifdef __hybrid_atomic_fetchsub
#define __hybrid_atomic_fetchsub32 __hybrid_atomic_fetchsub
#elif defined(__hybrid_atomic_fetchadd)
#define __hybrid_atomic_fetchsub32(p, val, order) __hybrid_atomic_fetchadd(p, (__UINT32_TYPE__)(-(__INT32_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchadd32)
#define __hybrid_atomic_fetchsub32(p, val, order) __hybrid_atomic_fetchadd32(p, (__UINT32_TYPE__)(-(__INT32_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_subfetch32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchsub32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __hafx32_val = (val); __XRETURN __hybrid_atomic_subfetch32(p, __hafx32_val, order) + __hafx32_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchsub32 __hybrid_atomic_fetchsub32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchsub32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_subfetch32(__p, __val, __order) + __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load32) && defined(__hybrid_atomic_cmpxch_weak32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchsub32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __hacxv32_p = (p), __hacxv32_val = (val), __hacxv32_res; \
	           do __hacxv32_res = __hybrid_atomic_load32(__hacxv32_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak32(__hacxv32_p, __hacxv32_res, __hacxv32_res - __hacxv32_val, order, order)); \
	           __XRETURN __hacxv32_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchsub32 __hybrid_atomic_fetchsub32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchsub32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	__UINT32_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load32(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak32(__p, __res, __res - __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_sub32 */

#ifndef __hybrid_atomic_fetchand32
#ifdef __hybrid_atomic_fetchand
#define __hybrid_atomic_fetchand32 __hybrid_atomic_fetchand
#elif defined(__hybrid_atomic_load32) && defined(__hybrid_atomic_cmpxch_weak32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchand32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __hacxv32_p = (p), __hacxv32_val = (val), __hacxv32_res; \
	           do __hacxv32_res = __hybrid_atomic_load32(__hacxv32_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak32(__hacxv32_p, __hacxv32_res, __hacxv32_res & __hacxv32_val, order, order)); \
	           __XRETURN __hacxv32_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchand32 __hybrid_atomic_fetchand32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchand32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	__UINT32_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load32(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak32(__p, __res, __res & __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_and32 */

#ifndef __hybrid_atomic_fetchxor32
#ifdef __hybrid_atomic_fetchxor
#define __hybrid_atomic_fetchxor32 __hybrid_atomic_fetchxor
#elif defined(__hybrid_atomic_xorfetch32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchxor32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __hafx32_val = (val); __XRETURN __hybrid_atomic_xorfetch32(p, __hafx32_val, order) ^ __hafx32_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchxor32 __hybrid_atomic_fetchxor32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchxor32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_xorfetch32(__p, __val, __order) ^ __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load32) && defined(__hybrid_atomic_cmpxch_weak32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchxor32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __hacxv32_p = (p), __hacxv32_val = (val), __hacxv32_res; \
	           do __hacxv32_res = __hybrid_atomic_load32(__hacxv32_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak32(__hacxv32_p, __hacxv32_res, __hacxv32_res ^ __hacxv32_val, order, order)); \
	           __XRETURN __hacxv32_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchxor32 __hybrid_atomic_fetchxor32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchxor32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	__UINT32_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load32(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak32(__p, __res, __res ^ __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xor32 */

#ifndef __hybrid_atomic_fetchor32
#ifdef __hybrid_atomic_fetchor
#define __hybrid_atomic_fetchor32 __hybrid_atomic_fetchor
#elif defined(__hybrid_atomic_load32) && defined(__hybrid_atomic_cmpxch_weak32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchor32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __hacxv32_p = (p), __hacxv32_val = (val), __hacxv32_res; \
	           do __hacxv32_res = __hybrid_atomic_load32(__hacxv32_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak32(__hacxv32_p, __hacxv32_res, __hacxv32_res | __hacxv32_val, order, order)); \
	           __XRETURN __hacxv32_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchor32 __hybrid_atomic_fetchor32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchor32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	__UINT32_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load32(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak32(__p, __res, __res | __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_or32 */

#ifndef __hybrid_atomic_fetchnand32
#ifdef __hybrid_atomic_fetchnand
#define __hybrid_atomic_fetchnand32 __hybrid_atomic_fetchnand
#elif defined(__hybrid_atomic_load32) && defined(__hybrid_atomic_cmpxch_weak32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchnand32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __hacxv32_p = (p), __hacxv32_val = (val), __hacxv32_res; \
	           do __hacxv32_res = __hybrid_atomic_load32(__hacxv32_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak32(__hacxv32_p, __hacxv32_res, ~(__hacxv32_res & __hacxv32_val), order, order)); \
	           __XRETURN __hacxv32_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchnand32 __hybrid_atomic_fetchnand32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchnand32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	__UINT32_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load32(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak32(__p, __res, ~(__res & __val), __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_nand32 */

#ifndef __hybrid_atomic_fetchinc32
#ifdef __hybrid_atomic_fetchinc
#define __hybrid_atomic_fetchinc32 __hybrid_atomic_fetchinc
#elif defined(__hybrid_atomic_fetchadd32)
#define __hybrid_atomic_fetchinc32(p, order) __hybrid_atomic_fetchadd32(p, 1, order)
#elif defined(__hybrid_atomic_fetchsub32)
#define __hybrid_atomic_fetchinc32(p, order) __hybrid_atomic_fetchsub32(p, (__UINT32_TYPE__)-1, order)
#elif defined(__hybrid_atomic_incfetch32)
#define __hybrid_atomic_fetchinc32(p, order) (__hybrid_atomic_incfetch32(p, val, order) - 1)
#endif /* ... */
#endif /* !__hybrid_atomic_inc32 */

#ifndef __hybrid_atomic_fetchdec32
#ifdef __hybrid_atomic_fetchdec
#define __hybrid_atomic_fetchdec32 __hybrid_atomic_fetchdec
#elif defined(__hybrid_atomic_fetchsub32)
#define __hybrid_atomic_fetchdec32(p, order) __hybrid_atomic_fetchsub32(p, 1, order)
#elif defined(__hybrid_atomic_fetchadd32)
#define __hybrid_atomic_fetchdec32(p, order) __hybrid_atomic_fetchadd32(p, (__UINT32_TYPE__)-1, order)
#elif defined(__hybrid_atomic_decfetch32)
#define __hybrid_atomic_fetchdec32(p, order) (__hybrid_atomic_decfetch32(p, val, order) + 1)
#endif /* ... */
#endif /* !__hybrid_atomic_dec32 */

#ifndef __hybrid_atomic_addfetch32
#ifdef __hybrid_atomic_addfetch
#define __hybrid_atomic_addfetch32 __hybrid_atomic_addfetch
#elif defined(__hybrid_atomic_subfetch)
#define __hybrid_atomic_addfetch32(p, val, order) __hybrid_atomic_subfetch(p, (__UINT32_TYPE__)(-(__INT32_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_subfetch32)
#define __hybrid_atomic_addfetch32(p, val, order) __hybrid_atomic_subfetch32(p, (__UINT32_TYPE__)(-(__INT32_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchadd32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_addfetch32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __haxf32_val = (val); __XRETURN __hybrid_atomic_fetchadd32(p, __haxf32_val, order) + __haxf32_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_addfetch32 __hybrid_atomic_addfetch32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_addfetch32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchadd32(__p, __val, __order) + __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_addfetch32 */

#ifndef __hybrid_atomic_subfetch32
#ifdef __hybrid_atomic_subfetch
#define __hybrid_atomic_subfetch32 __hybrid_atomic_subfetch
#elif defined(__hybrid_atomic_addfetch)
#define __hybrid_atomic_subfetch32(p, val, order) __hybrid_atomic_addfetch(p, (__UINT32_TYPE__)(-(__INT32_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_addfetch32)
#define __hybrid_atomic_subfetch32(p, val, order) __hybrid_atomic_addfetch32(p, (__UINT32_TYPE__)(-(__INT32_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchsub32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_subfetch32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __haxf32_val = (val); __XRETURN __hybrid_atomic_fetchsub32(p, __haxf32_val, order) - __haxf32_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_subfetch32 __hybrid_atomic_subfetch32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_subfetch32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchsub32(__p, __val, __order) - __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_subfetch32 */

#ifndef __hybrid_atomic_andfetch32
#ifdef __hybrid_atomic_andfetch
#define __hybrid_atomic_andfetch32 __hybrid_atomic_andfetch
#elif defined(__hybrid_atomic_fetchand32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_andfetch32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __haxf32_val = (val); __XRETURN __hybrid_atomic_fetchand32(p, __haxf32_val, order) & __haxf32_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_andfetch32 __hybrid_atomic_andfetch32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_andfetch32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchand32(__p, __val, __order) & __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_andfetch32 */

#ifndef __hybrid_atomic_xorfetch32
#ifdef __hybrid_atomic_xorfetch
#define __hybrid_atomic_xorfetch32 __hybrid_atomic_xorfetch
#elif defined(__hybrid_atomic_fetchxor32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_xorfetch32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __haxf32_val = (val); __XRETURN __hybrid_atomic_fetchxor32(p, __haxf32_val, order) ^ __haxf32_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_xorfetch32 __hybrid_atomic_xorfetch32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xorfetch32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchxor32(__p, __val, __order) ^ __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xorfetch32 */

#ifndef __hybrid_atomic_orfetch32
#ifdef __hybrid_atomic_orfetch
#define __hybrid_atomic_orfetch32 __hybrid_atomic_orfetch
#elif defined(__hybrid_atomic_fetchor32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_orfetch32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __haxf32_val = (val); __XRETURN __hybrid_atomic_fetchor32(p, __haxf32_val, order) | __haxf32_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_orfetch32 __hybrid_atomic_orfetch32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_orfetch32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchor32(__p, __val, __order) | __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_orfetch32 */

#ifndef __hybrid_atomic_nandfetch32
#ifdef __hybrid_atomic_nandfetch
#define __hybrid_atomic_nandfetch32 __hybrid_atomic_nandfetch
#elif defined(__hybrid_atomic_fetchnand32)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_nandfetch32(p, val, order) \
	__XBLOCK({ __UINT32_TYPE__ __haxf32_val = (val); __XRETURN ~(__hybrid_atomic_fetchnand32(p, __haxf32_val, order) & __haxf32_val); })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_nandfetch32 __hybrid_atomic_nandfetch32
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__hybrid_atomic_nandfetch32)(__UINT32_TYPE__ *__p, __UINT32_TYPE__ __val, int __order) {
	(void)__order;
	return ~(__hybrid_atomic_fetchnand32(__p, __val, __order) & __val);
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_nandfetch32 */

#ifndef __hybrid_atomic_incfetch32
#ifdef __hybrid_atomic_incfetch
#define __hybrid_atomic_incfetch32 __hybrid_atomic_incfetch
#elif defined(__hybrid_atomic_addfetch32)
#define __hybrid_atomic_incfetch32(p, order) __hybrid_atomic_addfetch32(p, 1, order)
#elif defined(__hybrid_atomic_subfetch32)
#define __hybrid_atomic_incfetch32(p, order) __hybrid_atomic_subfetch32(p, (__UINT32_TYPE__)-1, order)
#endif /* ... */
#endif /* !__hybrid_atomic_incfetch32 */

#ifndef __hybrid_atomic_decfetch32
#ifdef __hybrid_atomic_decfetch
#define __hybrid_atomic_decfetch32 __hybrid_atomic_decfetch
#elif defined(__hybrid_atomic_subfetch32)
#define __hybrid_atomic_decfetch32(p, order) __hybrid_atomic_subfetch32(p, 1, order)
#elif defined(__hybrid_atomic_addfetch32)
#define __hybrid_atomic_decfetch32(p, order) __hybrid_atomic_addfetch32(p, (__UINT32_TYPE__)-1, order)
#endif /* ... */
#endif /* !__hybrid_atomic_decfetch32 */

#ifndef __hybrid_atomic_inc32
#ifdef __hybrid_atomic_inc
#define __hybrid_atomic_inc32 __hybrid_atomic_inc
#elif defined(__hybrid_atomic_add32)
#define __hybrid_atomic_inc32(p, order) __hybrid_atomic_add32(p, 1, order)
#elif defined(__hybrid_atomic_fetchinc32)
#define __hybrid_atomic_inc32 (void)__hybrid_atomic_fetchinc32
#elif defined(__hybrid_atomic_incfetch32)
#define __hybrid_atomic_inc32 (void)__hybrid_atomic_incfetch32
#endif /* ... */
#endif /* !__hybrid_atomic_inc32 */

#ifndef __hybrid_atomic_dec32
#ifdef __hybrid_atomic_dec
#define __hybrid_atomic_dec32 __hybrid_atomic_dec
#elif defined(__hybrid_atomic_sub32)
#define __hybrid_atomic_dec32(p, order) __hybrid_atomic_sub32(p, 1, order)
#elif defined(__hybrid_atomic_fetchdec32)
#define __hybrid_atomic_dec32 (void)__hybrid_atomic_fetchdec32
#elif defined(__hybrid_atomic_decfetch32)
#define __hybrid_atomic_dec32 (void)__hybrid_atomic_decfetch32
#endif /* ... */
#endif /* !__hybrid_atomic_dec32 */

#ifndef __hybrid_atomic_add32
#ifdef __hybrid_atomic_add
#define __hybrid_atomic_add32 __hybrid_atomic_add
#elif defined(__hybrid_atomic_fetchadd32)
#define __hybrid_atomic_add32 (void)__hybrid_atomic_fetchadd32
#elif defined(__hybrid_atomic_addfetch32)
#define __hybrid_atomic_add32 (void)__hybrid_atomic_addfetch32
#endif /* ... */
#endif /* !__hybrid_atomic_add32 */

#ifndef __hybrid_atomic_sub32
#ifdef __hybrid_atomic_sub
#define __hybrid_atomic_sub32 __hybrid_atomic_sub
#elif defined(__hybrid_atomic_fetchsub32)
#define __hybrid_atomic_sub32 (void)__hybrid_atomic_fetchsub32
#elif defined(__hybrid_atomic_subfetch32)
#define __hybrid_atomic_sub32 (void)__hybrid_atomic_subfetch32
#endif /* ... */
#endif /* !__hybrid_atomic_sub32 */

#ifndef __hybrid_atomic_and32
#ifdef __hybrid_atomic_and
#define __hybrid_atomic_and32 __hybrid_atomic_and
#elif defined(__hybrid_atomic_fetchand32)
#define __hybrid_atomic_and32 (void)__hybrid_atomic_fetchand32
#elif defined(__hybrid_atomic_andfetch32)
#define __hybrid_atomic_and32 (void)__hybrid_atomic_andfetch32
#endif /* ... */
#endif /* !__hybrid_atomic_and32 */

#ifndef __hybrid_atomic_xor32
#ifdef __hybrid_atomic_xor
#define __hybrid_atomic_xor32 __hybrid_atomic_xor
#elif defined(__hybrid_atomic_fetchxor32)
#define __hybrid_atomic_xor32 (void)__hybrid_atomic_fetchxor32
#elif defined(__hybrid_atomic_xorfetch32)
#define __hybrid_atomic_xor32 (void)__hybrid_atomic_xorfetch32
#endif /* ... */
#endif /* !__hybrid_atomic_xor32 */

#ifndef __hybrid_atomic_or32
#ifdef __hybrid_atomic_or
#define __hybrid_atomic_or32 __hybrid_atomic_or
#elif defined(__hybrid_atomic_fetchor32)
#define __hybrid_atomic_or32 (void)__hybrid_atomic_fetchor32
#elif defined(__hybrid_atomic_orfetch32)
#define __hybrid_atomic_or32 (void)__hybrid_atomic_orfetch32
#endif /* ... */
#endif /* !__hybrid_atomic_or32 */

#ifndef __hybrid_atomic_nand32
#ifdef __hybrid_atomic_nand
#define __hybrid_atomic_nand32 __hybrid_atomic_nand
#elif defined(__hybrid_atomic_fetchnand32)
#define __hybrid_atomic_nand32 (void)__hybrid_atomic_fetchnand32
#elif defined(__hybrid_atomic_nandfetch32)
#define __hybrid_atomic_nand32 (void)__hybrid_atomic_nandfetch32
#endif /* ... */
#endif /* !__hybrid_atomic_nand32 */

#ifdef __UINT64_TYPE__
#ifndef __hybrid_atomic_cmpxch64
#ifdef __hybrid_atomic_cmpxch
#define __hybrid_atomic_cmpxch64 __hybrid_atomic_cmpxch
#elif defined(__hybrid_atomic_cmpxch_val64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch64(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT64_TYPE__ __hacx64_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val64(p, __hacx64_ov, newval, succ, fail) == __hacx64_ov; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch64 __hybrid_atomic_cmpxch64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
	return __hybrid_atomic_cmpxch_val64(__p, __oldval, __newval, __succ, __fail) == __oldval;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch64 */

#ifndef __hybrid_atomic_cmpxch_weak64
#ifdef __hybrid_atomic_cmpxch_weak
#define __hybrid_atomic_cmpxch_weak64 __hybrid_atomic_cmpxch_weak
#elif defined(__hybrid_atomic_cmpxch64)
#define __hybrid_atomic_cmpxch_weak64 __hybrid_atomic_cmpxch64
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch_weak64 */

#ifndef __hybrid_atomic_load64
#ifdef __hybrid_atomic_load
#define __hybrid_atomic_load64 __hybrid_atomic_load
#elif defined(__hybrid_atomic_fetchadd64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_fetchadd64(p, 0, order)
#elif defined(__hybrid_atomic_addfetch64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_addfetch64(p, 0, order)
#elif defined(__hybrid_atomic_fetchsub64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_fetchsub64(p, 0, order)
#elif defined(__hybrid_atomic_subfetch64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_subfetch64(p, 0, order)
#elif defined(__hybrid_atomic_fetchand64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_fetchand64(p, (__UINT64_TYPE__)-1, order)
#elif defined(__hybrid_atomic_andfetch64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_andfetch64(p, (__UINT64_TYPE__)-1, order)
#elif defined(__hybrid_atomic_fetchor64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_fetchor64(p, 0, order)
#elif defined(__hybrid_atomic_orfetch64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_orfetch64(p, 0, order)
#elif defined(__hybrid_atomic_fetchxor64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_fetchxor64(p, 0, order)
#elif defined(__hybrid_atomic_xorfetch64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_xorfetch64(p, 0, order)
#elif defined(__hybrid_atomic_cmpxch_val64)
#define __hybrid_atomic_load64(p, order) __hybrid_atomic_cmpxch_val64(p, 0, 0, order, order)
#elif defined(__hybrid_atomic_cmpxch_weak64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_load64(p, order) \
	__XBLOCK({ __UINT64_TYPE__ const *__hal64_p = (p); __UINT64_TYPE__ __hal64_res; \
	           do { __hal64_res = *__hal64_p; __COMPILER_READ_BARRIER(); \
	           } while (!__hybrid_atomic_cmpxch_weak((__UINT64_TYPE__ *)__hal64_p, __hal64_res, __hal64_res, order, order)); \
	           __XRETURN __hal64_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_load64 __hybrid_atomic_load64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_load64)(__UINT64_TYPE__ const *__p, int __order) {
	__UINT64_TYPE__ __res;
	(void)__order;
	do { __res = *__p; __COMPILER_READ_BARRIER();
	} while (!__hybrid_atomic_cmpxch_weak((__UINT64_TYPE__ *)__p, __res, __res, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_load64 */

#ifndef __hybrid_atomic_cmpxch_val64
#ifdef __hybrid_atomic_cmpxch_val
#define __hybrid_atomic_cmpxch_val64 __hybrid_atomic_cmpxch_val
#elif defined(__hybrid_atomic_cmpxch_weak64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch_val64(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT64_TYPE__ __hacxv64_p = (p), __hacxv64_ov = (oldval), __hacxv64_nv = (newval), __hacxv64_res; \
	           do if ((__hacxv64_res = __hybrid_atomic_load64(__hacxv64_p, __ATOMIC_ACQUIRE)) != __hacxv64_ov) break; \
	           while (!__hybrid_atomic_cmpxch_weak64(__hacxv64_p, __hacxv64_res, __hacxv64_nv, succ, fail)); \
	           __XRETURN __hacxv64_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch_val64 __hybrid_atomic_cmpxch_val64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_cmpxch_val64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval, int __succ, int __fail) {
	__UINT64_TYPE__ __res;
	(void)__succ, (void)__fail;
	do if ((__res = __hybrid_atomic_load64(__p, __ATOMIC_ACQUIRE)) != __oldval) break;
	while (!__hybrid_atomic_cmpxch_weak64(__p, __res, __newval, __succ, __fail));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch_val64 */

#if !defined(__hybrid_atomic_cmpxch64) && defined(__hybrid_atomic_cmpxch_val64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch64(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT64_TYPE__ __hacx64_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val64(p, __hacx64_ov, newval, succ, fail) == __hacx64_ov; })
#else /* __NO_XBLOCK */
__LOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
	return __hybrid_atomic_cmpxch_val64(__p, __oldval, __newval, __succ, __fail) == __oldval;
}
#endif /* !__NO_XBLOCK */
#endif /* !__hybrid_atomic_cmpxch64 && __hybrid_atomic_cmpxch_val64 */

#if !defined(__hybrid_atomic_cmpxch_weak64) && defined(__hybrid_atomic_cmpxch64)
#define __hybrid_atomic_cmpxch_weak64 __hybrid_atomic_cmpxch64
#endif /* !__hybrid_atomic_cmpxch_weak64 && __hybrid_atomic_cmpxch64 */

#ifndef __hybrid_atomic_xch64
#ifdef __hybrid_atomic_xch
#define __hybrid_atomic_xch64 __hybrid_atomic_xch
#elif defined(__hybrid_atomic_load64) && defined(__hybrid_atomic_cmpxch_weak64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_xch64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ *__hal64_p = (p); __UINT64_TYPE__ __hal64_res, __hal64_val = (val); \
	           do __hal64_res = __hybrid_atomic_load(__hal64_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak(__hal64_p, __hal64_res, __hal64_val, order, order)); \
	           __XRETURN __hal64_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_xch64 __hybrid_atomic_xch64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xch64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	__UINT64_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak(__p, __res, __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xch64 */

#ifndef __hybrid_atomic_store64
#ifdef __hybrid_atomic_store
#define __hybrid_atomic_store64 __hybrid_atomic_store
#elif defined(__hybrid_atomic_xch64)
#define __hybrid_atomic_store64 (void)__hybrid_atomic_xch64
#endif /* ... */
#endif /* !__hybrid_atomic_store64 */

#ifndef __hybrid_atomic_fetchadd64
#ifdef __hybrid_atomic_fetchadd
#define __hybrid_atomic_fetchadd64 __hybrid_atomic_fetchadd
#elif defined(__hybrid_atomic_fetchsub)
#define __hybrid_atomic_fetchadd64(p, val, order) __hybrid_atomic_fetchsub(p, (__UINT64_TYPE__)(-(__INT64_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchsub64)
#define __hybrid_atomic_fetchadd64(p, val, order) __hybrid_atomic_fetchsub64(p, (__UINT64_TYPE__)(-(__INT64_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_addfetch64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchadd64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __hafx64_val = (val); __XRETURN __hybrid_atomic_addfetch64(p, __hafx64_val, order) - __hafx64_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchadd64 __hybrid_atomic_fetchadd64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchadd64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_addfetch64(__p, __val, __order) - __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load64) && defined(__hybrid_atomic_cmpxch_weak64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchadd64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __hacxv64_p = (p), __hacxv64_val = (val), __hacxv64_res; \
	           do __hacxv64_res = __hybrid_atomic_load64(__hacxv64_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak64(__hacxv64_p, __hacxv64_res, __hacxv64_res + __hacxv64_val, order, order)); \
	           __XRETURN __hacxv64_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchadd64 __hybrid_atomic_fetchadd64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchadd64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	__UINT64_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load64(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak64(__p, __res, __res + __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_add64 */

#ifndef __hybrid_atomic_fetchsub64
#ifdef __hybrid_atomic_fetchsub
#define __hybrid_atomic_fetchsub64 __hybrid_atomic_fetchsub
#elif defined(__hybrid_atomic_fetchadd)
#define __hybrid_atomic_fetchsub64(p, val, order) __hybrid_atomic_fetchadd(p, (__UINT64_TYPE__)(-(__INT64_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchadd64)
#define __hybrid_atomic_fetchsub64(p, val, order) __hybrid_atomic_fetchadd64(p, (__UINT64_TYPE__)(-(__INT64_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_subfetch64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchsub64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __hafx64_val = (val); __XRETURN __hybrid_atomic_subfetch64(p, __hafx64_val, order) + __hafx64_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchsub64 __hybrid_atomic_fetchsub64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchsub64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_subfetch64(__p, __val, __order) + __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load64) && defined(__hybrid_atomic_cmpxch_weak64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchsub64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __hacxv64_p = (p), __hacxv64_val = (val), __hacxv64_res; \
	           do __hacxv64_res = __hybrid_atomic_load64(__hacxv64_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak64(__hacxv64_p, __hacxv64_res, __hacxv64_res - __hacxv64_val, order, order)); \
	           __XRETURN __hacxv64_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchsub64 __hybrid_atomic_fetchsub64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchsub64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	__UINT64_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load64(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak64(__p, __res, __res - __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_sub64 */

#ifndef __hybrid_atomic_fetchand64
#ifdef __hybrid_atomic_fetchand
#define __hybrid_atomic_fetchand64 __hybrid_atomic_fetchand
#elif defined(__hybrid_atomic_load64) && defined(__hybrid_atomic_cmpxch_weak64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchand64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __hacxv64_p = (p), __hacxv64_val = (val), __hacxv64_res; \
	           do __hacxv64_res = __hybrid_atomic_load64(__hacxv64_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak64(__hacxv64_p, __hacxv64_res, __hacxv64_res & __hacxv64_val, order, order)); \
	           __XRETURN __hacxv64_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchand64 __hybrid_atomic_fetchand64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchand64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	__UINT64_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load64(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak64(__p, __res, __res & __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_and64 */

#ifndef __hybrid_atomic_fetchxor64
#ifdef __hybrid_atomic_fetchxor
#define __hybrid_atomic_fetchxor64 __hybrid_atomic_fetchxor
#elif defined(__hybrid_atomic_xorfetch64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchxor64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __hafx64_val = (val); __XRETURN __hybrid_atomic_xorfetch64(p, __hafx64_val, order) ^ __hafx64_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchxor64 __hybrid_atomic_fetchxor64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchxor64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_xorfetch64(__p, __val, __order) ^ __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load64) && defined(__hybrid_atomic_cmpxch_weak64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchxor64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __hacxv64_p = (p), __hacxv64_val = (val), __hacxv64_res; \
	           do __hacxv64_res = __hybrid_atomic_load64(__hacxv64_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak64(__hacxv64_p, __hacxv64_res, __hacxv64_res ^ __hacxv64_val, order, order)); \
	           __XRETURN __hacxv64_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchxor64 __hybrid_atomic_fetchxor64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchxor64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	__UINT64_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load64(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak64(__p, __res, __res ^ __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xor64 */

#ifndef __hybrid_atomic_fetchor64
#ifdef __hybrid_atomic_fetchor
#define __hybrid_atomic_fetchor64 __hybrid_atomic_fetchor
#elif defined(__hybrid_atomic_load64) && defined(__hybrid_atomic_cmpxch_weak64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchor64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __hacxv64_p = (p), __hacxv64_val = (val), __hacxv64_res; \
	           do __hacxv64_res = __hybrid_atomic_load64(__hacxv64_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak64(__hacxv64_p, __hacxv64_res, __hacxv64_res | __hacxv64_val, order, order)); \
	           __XRETURN __hacxv64_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchor64 __hybrid_atomic_fetchor64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchor64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	__UINT64_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load64(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak64(__p, __res, __res | __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_or64 */

#ifndef __hybrid_atomic_fetchnand64
#ifdef __hybrid_atomic_fetchnand
#define __hybrid_atomic_fetchnand64 __hybrid_atomic_fetchnand
#elif defined(__hybrid_atomic_load64) && defined(__hybrid_atomic_cmpxch_weak64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchnand64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __hacxv64_p = (p), __hacxv64_val = (val), __hacxv64_res; \
	           do __hacxv64_res = __hybrid_atomic_load64(__hacxv64_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak64(__hacxv64_p, __hacxv64_res, ~(__hacxv64_res & __hacxv64_val), order, order)); \
	           __XRETURN __hacxv64_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchnand64 __hybrid_atomic_fetchnand64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchnand64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	__UINT64_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load64(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak64(__p, __res, ~(__res & __val), __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_nand64 */

#ifndef __hybrid_atomic_fetchinc64
#ifdef __hybrid_atomic_fetchinc
#define __hybrid_atomic_fetchinc64 __hybrid_atomic_fetchinc
#elif defined(__hybrid_atomic_fetchadd64)
#define __hybrid_atomic_fetchinc64(p, order) __hybrid_atomic_fetchadd64(p, 1, order)
#elif defined(__hybrid_atomic_fetchsub64)
#define __hybrid_atomic_fetchinc64(p, order) __hybrid_atomic_fetchsub64(p, (__UINT64_TYPE__)-1, order)
#elif defined(__hybrid_atomic_incfetch64)
#define __hybrid_atomic_fetchinc64(p, order) (__hybrid_atomic_incfetch64(p, val, order) - 1)
#endif /* ... */
#endif /* !__hybrid_atomic_inc64 */

#ifndef __hybrid_atomic_fetchdec64
#ifdef __hybrid_atomic_fetchdec
#define __hybrid_atomic_fetchdec64 __hybrid_atomic_fetchdec
#elif defined(__hybrid_atomic_fetchsub64)
#define __hybrid_atomic_fetchdec64(p, order) __hybrid_atomic_fetchsub64(p, 1, order)
#elif defined(__hybrid_atomic_fetchadd64)
#define __hybrid_atomic_fetchdec64(p, order) __hybrid_atomic_fetchadd64(p, (__UINT64_TYPE__)-1, order)
#elif defined(__hybrid_atomic_decfetch64)
#define __hybrid_atomic_fetchdec64(p, order) (__hybrid_atomic_decfetch64(p, val, order) + 1)
#endif /* ... */
#endif /* !__hybrid_atomic_dec64 */

#ifndef __hybrid_atomic_addfetch64
#ifdef __hybrid_atomic_addfetch
#define __hybrid_atomic_addfetch64 __hybrid_atomic_addfetch
#elif defined(__hybrid_atomic_subfetch)
#define __hybrid_atomic_addfetch64(p, val, order) __hybrid_atomic_subfetch(p, (__UINT64_TYPE__)(-(__INT64_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_subfetch64)
#define __hybrid_atomic_addfetch64(p, val, order) __hybrid_atomic_subfetch64(p, (__UINT64_TYPE__)(-(__INT64_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchadd64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_addfetch64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __haxf64_val = (val); __XRETURN __hybrid_atomic_fetchadd64(p, __haxf64_val, order) + __haxf64_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_addfetch64 __hybrid_atomic_addfetch64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_addfetch64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchadd64(__p, __val, __order) + __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_addfetch64 */

#ifndef __hybrid_atomic_subfetch64
#ifdef __hybrid_atomic_subfetch
#define __hybrid_atomic_subfetch64 __hybrid_atomic_subfetch
#elif defined(__hybrid_atomic_addfetch)
#define __hybrid_atomic_subfetch64(p, val, order) __hybrid_atomic_addfetch(p, (__UINT64_TYPE__)(-(__INT64_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_addfetch64)
#define __hybrid_atomic_subfetch64(p, val, order) __hybrid_atomic_addfetch64(p, (__UINT64_TYPE__)(-(__INT64_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchsub64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_subfetch64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __haxf64_val = (val); __XRETURN __hybrid_atomic_fetchsub64(p, __haxf64_val, order) - __haxf64_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_subfetch64 __hybrid_atomic_subfetch64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_subfetch64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchsub64(__p, __val, __order) - __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_subfetch64 */

#ifndef __hybrid_atomic_andfetch64
#ifdef __hybrid_atomic_andfetch
#define __hybrid_atomic_andfetch64 __hybrid_atomic_andfetch
#elif defined(__hybrid_atomic_fetchand64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_andfetch64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __haxf64_val = (val); __XRETURN __hybrid_atomic_fetchand64(p, __haxf64_val, order) & __haxf64_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_andfetch64 __hybrid_atomic_andfetch64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_andfetch64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchand64(__p, __val, __order) & __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_andfetch64 */

#ifndef __hybrid_atomic_xorfetch64
#ifdef __hybrid_atomic_xorfetch
#define __hybrid_atomic_xorfetch64 __hybrid_atomic_xorfetch
#elif defined(__hybrid_atomic_fetchxor64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_xorfetch64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __haxf64_val = (val); __XRETURN __hybrid_atomic_fetchxor64(p, __haxf64_val, order) ^ __haxf64_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_xorfetch64 __hybrid_atomic_xorfetch64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xorfetch64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchxor64(__p, __val, __order) ^ __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xorfetch64 */

#ifndef __hybrid_atomic_orfetch64
#ifdef __hybrid_atomic_orfetch
#define __hybrid_atomic_orfetch64 __hybrid_atomic_orfetch
#elif defined(__hybrid_atomic_fetchor64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_orfetch64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __haxf64_val = (val); __XRETURN __hybrid_atomic_fetchor64(p, __haxf64_val, order) | __haxf64_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_orfetch64 __hybrid_atomic_orfetch64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_orfetch64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchor64(__p, __val, __order) | __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_orfetch64 */

#ifndef __hybrid_atomic_nandfetch64
#ifdef __hybrid_atomic_nandfetch
#define __hybrid_atomic_nandfetch64 __hybrid_atomic_nandfetch
#elif defined(__hybrid_atomic_fetchnand64)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_nandfetch64(p, val, order) \
	__XBLOCK({ __UINT64_TYPE__ __haxf64_val = (val); __XRETURN ~(__hybrid_atomic_fetchnand64(p, __haxf64_val, order) & __haxf64_val); })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_nandfetch64 __hybrid_atomic_nandfetch64
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__hybrid_atomic_nandfetch64)(__UINT64_TYPE__ *__p, __UINT64_TYPE__ __val, int __order) {
	(void)__order;
	return ~(__hybrid_atomic_fetchnand64(__p, __val, __order) & __val);
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_nandfetch64 */

#ifndef __hybrid_atomic_incfetch64
#ifdef __hybrid_atomic_incfetch
#define __hybrid_atomic_incfetch64 __hybrid_atomic_incfetch
#elif defined(__hybrid_atomic_addfetch64)
#define __hybrid_atomic_incfetch64(p, order) __hybrid_atomic_addfetch64(p, 1, order)
#elif defined(__hybrid_atomic_subfetch64)
#define __hybrid_atomic_incfetch64(p, order) __hybrid_atomic_subfetch64(p, (__UINT64_TYPE__)-1, order)
#endif /* ... */
#endif /* !__hybrid_atomic_incfetch64 */

#ifndef __hybrid_atomic_decfetch64
#ifdef __hybrid_atomic_decfetch
#define __hybrid_atomic_decfetch64 __hybrid_atomic_decfetch
#elif defined(__hybrid_atomic_subfetch64)
#define __hybrid_atomic_decfetch64(p, order) __hybrid_atomic_subfetch64(p, 1, order)
#elif defined(__hybrid_atomic_addfetch64)
#define __hybrid_atomic_decfetch64(p, order) __hybrid_atomic_addfetch64(p, (__UINT64_TYPE__)-1, order)
#endif /* ... */
#endif /* !__hybrid_atomic_decfetch64 */

#ifndef __hybrid_atomic_inc64
#ifdef __hybrid_atomic_inc
#define __hybrid_atomic_inc64 __hybrid_atomic_inc
#elif defined(__hybrid_atomic_add64)
#define __hybrid_atomic_inc64(p, order) __hybrid_atomic_add64(p, 1, order)
#elif defined(__hybrid_atomic_fetchinc64)
#define __hybrid_atomic_inc64 (void)__hybrid_atomic_fetchinc64
#elif defined(__hybrid_atomic_incfetch64)
#define __hybrid_atomic_inc64 (void)__hybrid_atomic_incfetch64
#endif /* ... */
#endif /* !__hybrid_atomic_inc64 */

#ifndef __hybrid_atomic_dec64
#ifdef __hybrid_atomic_dec
#define __hybrid_atomic_dec64 __hybrid_atomic_dec
#elif defined(__hybrid_atomic_sub64)
#define __hybrid_atomic_dec64(p, order) __hybrid_atomic_sub64(p, 1, order)
#elif defined(__hybrid_atomic_fetchdec64)
#define __hybrid_atomic_dec64 (void)__hybrid_atomic_fetchdec64
#elif defined(__hybrid_atomic_decfetch64)
#define __hybrid_atomic_dec64 (void)__hybrid_atomic_decfetch64
#endif /* ... */
#endif /* !__hybrid_atomic_dec64 */

#ifndef __hybrid_atomic_add64
#ifdef __hybrid_atomic_add
#define __hybrid_atomic_add64 __hybrid_atomic_add
#elif defined(__hybrid_atomic_fetchadd64)
#define __hybrid_atomic_add64 (void)__hybrid_atomic_fetchadd64
#elif defined(__hybrid_atomic_addfetch64)
#define __hybrid_atomic_add64 (void)__hybrid_atomic_addfetch64
#endif /* ... */
#endif /* !__hybrid_atomic_add64 */

#ifndef __hybrid_atomic_sub64
#ifdef __hybrid_atomic_sub
#define __hybrid_atomic_sub64 __hybrid_atomic_sub
#elif defined(__hybrid_atomic_fetchsub64)
#define __hybrid_atomic_sub64 (void)__hybrid_atomic_fetchsub64
#elif defined(__hybrid_atomic_subfetch64)
#define __hybrid_atomic_sub64 (void)__hybrid_atomic_subfetch64
#endif /* ... */
#endif /* !__hybrid_atomic_sub64 */

#ifndef __hybrid_atomic_and64
#ifdef __hybrid_atomic_and
#define __hybrid_atomic_and64 __hybrid_atomic_and
#elif defined(__hybrid_atomic_fetchand64)
#define __hybrid_atomic_and64 (void)__hybrid_atomic_fetchand64
#elif defined(__hybrid_atomic_andfetch64)
#define __hybrid_atomic_and64 (void)__hybrid_atomic_andfetch64
#endif /* ... */
#endif /* !__hybrid_atomic_and64 */

#ifndef __hybrid_atomic_xor64
#ifdef __hybrid_atomic_xor
#define __hybrid_atomic_xor64 __hybrid_atomic_xor
#elif defined(__hybrid_atomic_fetchxor64)
#define __hybrid_atomic_xor64 (void)__hybrid_atomic_fetchxor64
#elif defined(__hybrid_atomic_xorfetch64)
#define __hybrid_atomic_xor64 (void)__hybrid_atomic_xorfetch64
#endif /* ... */
#endif /* !__hybrid_atomic_xor64 */

#ifndef __hybrid_atomic_or64
#ifdef __hybrid_atomic_or
#define __hybrid_atomic_or64 __hybrid_atomic_or
#elif defined(__hybrid_atomic_fetchor64)
#define __hybrid_atomic_or64 (void)__hybrid_atomic_fetchor64
#elif defined(__hybrid_atomic_orfetch64)
#define __hybrid_atomic_or64 (void)__hybrid_atomic_orfetch64
#endif /* ... */
#endif /* !__hybrid_atomic_or64 */

#ifndef __hybrid_atomic_nand64
#ifdef __hybrid_atomic_nand
#define __hybrid_atomic_nand64 __hybrid_atomic_nand
#elif defined(__hybrid_atomic_fetchnand64)
#define __hybrid_atomic_nand64 (void)__hybrid_atomic_fetchnand64
#elif defined(__hybrid_atomic_nandfetch64)
#define __hybrid_atomic_nand64 (void)__hybrid_atomic_nandfetch64
#endif /* ... */
#endif /* !__hybrid_atomic_nand64 */

#endif /* __UINT64_TYPE__ */
#ifdef __UINT128_TYPE__
#ifndef __hybrid_atomic_cmpxch128
#ifdef __hybrid_atomic_cmpxch
#define __hybrid_atomic_cmpxch128 __hybrid_atomic_cmpxch
#elif defined(__hybrid_atomic_cmpxch_val128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch128(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT128_TYPE__ __hacx128_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val128(p, __hacx128_ov, newval, succ, fail) == __hacx128_ov; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch128 __hybrid_atomic_cmpxch128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __oldval, __UINT128_TYPE__ __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
	return __hybrid_atomic_cmpxch_val128(__p, __oldval, __newval, __succ, __fail) == __oldval;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch128 */

#ifndef __hybrid_atomic_cmpxch_weak128
#ifdef __hybrid_atomic_cmpxch_weak
#define __hybrid_atomic_cmpxch_weak128 __hybrid_atomic_cmpxch_weak
#elif defined(__hybrid_atomic_cmpxch128)
#define __hybrid_atomic_cmpxch_weak128 __hybrid_atomic_cmpxch128
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch_weak128 */

#ifndef __hybrid_atomic_load128
#ifdef __hybrid_atomic_load
#define __hybrid_atomic_load128 __hybrid_atomic_load
#elif defined(__hybrid_atomic_fetchadd128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_fetchadd128(p, 0, order)
#elif defined(__hybrid_atomic_addfetch128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_addfetch128(p, 0, order)
#elif defined(__hybrid_atomic_fetchsub128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_fetchsub128(p, 0, order)
#elif defined(__hybrid_atomic_subfetch128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_subfetch128(p, 0, order)
#elif defined(__hybrid_atomic_fetchand128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_fetchand128(p, (__UINT128_TYPE__)-1, order)
#elif defined(__hybrid_atomic_andfetch128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_andfetch128(p, (__UINT128_TYPE__)-1, order)
#elif defined(__hybrid_atomic_fetchor128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_fetchor128(p, 0, order)
#elif defined(__hybrid_atomic_orfetch128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_orfetch128(p, 0, order)
#elif defined(__hybrid_atomic_fetchxor128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_fetchxor128(p, 0, order)
#elif defined(__hybrid_atomic_xorfetch128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_xorfetch128(p, 0, order)
#elif defined(__hybrid_atomic_cmpxch_val128)
#define __hybrid_atomic_load128(p, order) __hybrid_atomic_cmpxch_val128(p, 0, 0, order, order)
#elif defined(__hybrid_atomic_cmpxch_weak128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_load128(p, order) \
	__XBLOCK({ __UINT128_TYPE__ const *__hal128_p = (p); __UINT128_TYPE__ __hal128_res; \
	           do { __hal128_res = *__hal128_p; __COMPILER_READ_BARRIER(); \
	           } while (!__hybrid_atomic_cmpxch_weak((__UINT128_TYPE__ *)__hal128_p, __hal128_res, __hal128_res, order, order)); \
	           __XRETURN __hal128_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_load128 __hybrid_atomic_load128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_load128)(__UINT128_TYPE__ const *__p, int __order) {
	__UINT128_TYPE__ __res;
	(void)__order;
	do { __res = *__p; __COMPILER_READ_BARRIER();
	} while (!__hybrid_atomic_cmpxch_weak((__UINT128_TYPE__ *)__p, __res, __res, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_load128 */

#ifndef __hybrid_atomic_cmpxch_val128
#ifdef __hybrid_atomic_cmpxch_val
#define __hybrid_atomic_cmpxch_val128 __hybrid_atomic_cmpxch_val
#elif defined(__hybrid_atomic_cmpxch_weak128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch_val128(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT128_TYPE__ __hacxv128_p = (p), __hacxv128_ov = (oldval), __hacxv128_nv = (newval), __hacxv128_res; \
	           do if ((__hacxv128_res = __hybrid_atomic_load128(__hacxv128_p, __ATOMIC_ACQUIRE)) != __hacxv128_ov) break; \
	           while (!__hybrid_atomic_cmpxch_weak128(__hacxv128_p, __hacxv128_res, __hacxv128_nv, succ, fail)); \
	           __XRETURN __hacxv128_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch_val128 __hybrid_atomic_cmpxch_val128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_cmpxch_val128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __oldval, __UINT128_TYPE__ __newval, int __succ, int __fail) {
	__UINT128_TYPE__ __res;
	(void)__succ, (void)__fail;
	do if ((__res = __hybrid_atomic_load128(__p, __ATOMIC_ACQUIRE)) != __oldval) break;
	while (!__hybrid_atomic_cmpxch_weak128(__p, __res, __newval, __succ, __fail));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_cmpxch_val128 */

#if !defined(__hybrid_atomic_cmpxch128) && defined(__hybrid_atomic_cmpxch_val128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_cmpxch128(p, oldval, newval, succ, fail) \
	__XBLOCK({ __UINT128_TYPE__ __hacx128_ov = (oldval); __XRETURN __hybrid_atomic_cmpxch_val128(p, __hacx128_ov, newval, succ, fail) == __hacx128_ov; })
#else /* __NO_XBLOCK */
__LOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(__hybrid_atomic_cmpxch128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __oldval, __UINT128_TYPE__ __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
	return __hybrid_atomic_cmpxch_val128(__p, __oldval, __newval, __succ, __fail) == __oldval;
}
#endif /* !__NO_XBLOCK */
#endif /* !__hybrid_atomic_cmpxch128 && __hybrid_atomic_cmpxch_val128 */

#if !defined(__hybrid_atomic_cmpxch_weak128) && defined(__hybrid_atomic_cmpxch128)
#define __hybrid_atomic_cmpxch_weak128 __hybrid_atomic_cmpxch128
#endif /* !__hybrid_atomic_cmpxch_weak128 && __hybrid_atomic_cmpxch128 */

#ifndef __hybrid_atomic_xch128
#ifdef __hybrid_atomic_xch
#define __hybrid_atomic_xch128 __hybrid_atomic_xch
#elif defined(__hybrid_atomic_load128) && defined(__hybrid_atomic_cmpxch_weak128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_xch128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ *__hal128_p = (p); __UINT128_TYPE__ __hal128_res, __hal128_val = (val); \
	           do __hal128_res = __hybrid_atomic_load(__hal128_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak(__hal128_p, __hal128_res, __hal128_val, order, order)); \
	           __XRETURN __hal128_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_xch128 __hybrid_atomic_xch128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xch128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	__UINT128_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak(__p, __res, __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xch128 */

#ifndef __hybrid_atomic_store128
#ifdef __hybrid_atomic_store
#define __hybrid_atomic_store128 __hybrid_atomic_store
#elif defined(__hybrid_atomic_xch128)
#define __hybrid_atomic_store128 (void)__hybrid_atomic_xch128
#endif /* ... */
#endif /* !__hybrid_atomic_store128 */

#ifndef __hybrid_atomic_fetchadd128
#ifdef __hybrid_atomic_fetchadd
#define __hybrid_atomic_fetchadd128 __hybrid_atomic_fetchadd
#elif defined(__hybrid_atomic_fetchsub)
#define __hybrid_atomic_fetchadd128(p, val, order) __hybrid_atomic_fetchsub(p, (__UINT128_TYPE__)(-(__INT128_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchsub128)
#define __hybrid_atomic_fetchadd128(p, val, order) __hybrid_atomic_fetchsub128(p, (__UINT128_TYPE__)(-(__INT128_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_addfetch128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchadd128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __hafx128_val = (val); __XRETURN __hybrid_atomic_addfetch128(p, __hafx128_val, order) - __hafx128_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchadd128 __hybrid_atomic_fetchadd128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchadd128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_addfetch128(__p, __val, __order) - __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load128) && defined(__hybrid_atomic_cmpxch_weak128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchadd128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __hacxv128_p = (p), __hacxv128_val = (val), __hacxv128_res; \
	           do __hacxv128_res = __hybrid_atomic_load128(__hacxv128_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak128(__hacxv128_p, __hacxv128_res, __hacxv128_res + __hacxv128_val, order, order)); \
	           __XRETURN __hacxv128_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchadd128 __hybrid_atomic_fetchadd128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchadd128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	__UINT128_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load128(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak128(__p, __res, __res + __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_add128 */

#ifndef __hybrid_atomic_fetchsub128
#ifdef __hybrid_atomic_fetchsub
#define __hybrid_atomic_fetchsub128 __hybrid_atomic_fetchsub
#elif defined(__hybrid_atomic_fetchadd)
#define __hybrid_atomic_fetchsub128(p, val, order) __hybrid_atomic_fetchadd(p, (__UINT128_TYPE__)(-(__INT128_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchadd128)
#define __hybrid_atomic_fetchsub128(p, val, order) __hybrid_atomic_fetchadd128(p, (__UINT128_TYPE__)(-(__INT128_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_subfetch128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchsub128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __hafx128_val = (val); __XRETURN __hybrid_atomic_subfetch128(p, __hafx128_val, order) + __hafx128_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchsub128 __hybrid_atomic_fetchsub128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchsub128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_subfetch128(__p, __val, __order) + __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load128) && defined(__hybrid_atomic_cmpxch_weak128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchsub128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __hacxv128_p = (p), __hacxv128_val = (val), __hacxv128_res; \
	           do __hacxv128_res = __hybrid_atomic_load128(__hacxv128_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak128(__hacxv128_p, __hacxv128_res, __hacxv128_res - __hacxv128_val, order, order)); \
	           __XRETURN __hacxv128_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchsub128 __hybrid_atomic_fetchsub128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchsub128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	__UINT128_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load128(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak128(__p, __res, __res - __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_sub128 */

#ifndef __hybrid_atomic_fetchand128
#ifdef __hybrid_atomic_fetchand
#define __hybrid_atomic_fetchand128 __hybrid_atomic_fetchand
#elif defined(__hybrid_atomic_load128) && defined(__hybrid_atomic_cmpxch_weak128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchand128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __hacxv128_p = (p), __hacxv128_val = (val), __hacxv128_res; \
	           do __hacxv128_res = __hybrid_atomic_load128(__hacxv128_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak128(__hacxv128_p, __hacxv128_res, __hacxv128_res & __hacxv128_val, order, order)); \
	           __XRETURN __hacxv128_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchand128 __hybrid_atomic_fetchand128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchand128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	__UINT128_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load128(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak128(__p, __res, __res & __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_and128 */

#ifndef __hybrid_atomic_fetchxor128
#ifdef __hybrid_atomic_fetchxor
#define __hybrid_atomic_fetchxor128 __hybrid_atomic_fetchxor
#elif defined(__hybrid_atomic_xorfetch128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchxor128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __hafx128_val = (val); __XRETURN __hybrid_atomic_xorfetch128(p, __hafx128_val, order) ^ __hafx128_val; })
#else /* !__NO_XBLOCK */
#define __hybrid_atomic_fetchxor128 __hybrid_atomic_fetchxor128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchxor128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_xorfetch128(__p, __val, __order) ^ __val;
}
#endif /* __NO_XBLOCK */
#elif defined(__hybrid_atomic_load128) && defined(__hybrid_atomic_cmpxch_weak128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchxor128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __hacxv128_p = (p), __hacxv128_val = (val), __hacxv128_res; \
	           do __hacxv128_res = __hybrid_atomic_load128(__hacxv128_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak128(__hacxv128_p, __hacxv128_res, __hacxv128_res ^ __hacxv128_val, order, order)); \
	           __XRETURN __hacxv128_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchxor128 __hybrid_atomic_fetchxor128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchxor128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	__UINT128_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load128(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak128(__p, __res, __res ^ __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xor128 */

#ifndef __hybrid_atomic_fetchor128
#ifdef __hybrid_atomic_fetchor
#define __hybrid_atomic_fetchor128 __hybrid_atomic_fetchor
#elif defined(__hybrid_atomic_load128) && defined(__hybrid_atomic_cmpxch_weak128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchor128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __hacxv128_p = (p), __hacxv128_val = (val), __hacxv128_res; \
	           do __hacxv128_res = __hybrid_atomic_load128(__hacxv128_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak128(__hacxv128_p, __hacxv128_res, __hacxv128_res | __hacxv128_val, order, order)); \
	           __XRETURN __hacxv128_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchor128 __hybrid_atomic_fetchor128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchor128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	__UINT128_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load128(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak128(__p, __res, __res | __val, __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_or128 */

#ifndef __hybrid_atomic_fetchnand128
#ifdef __hybrid_atomic_fetchnand
#define __hybrid_atomic_fetchnand128 __hybrid_atomic_fetchnand
#elif defined(__hybrid_atomic_load128) && defined(__hybrid_atomic_cmpxch_weak128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_fetchnand128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __hacxv128_p = (p), __hacxv128_val = (val), __hacxv128_res; \
	           do __hacxv128_res = __hybrid_atomic_load128(__hacxv128_p, __ATOMIC_ACQUIRE); \
	           while (!__hybrid_atomic_cmpxch_weak128(__hacxv128_p, __hacxv128_res, ~(__hacxv128_res & __hacxv128_val), order, order)); \
	           __XRETURN __hacxv128_res; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_fetchnand128 __hybrid_atomic_fetchnand128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_fetchnand128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	__UINT128_TYPE__ __res;
	(void)__order;
	do __res = __hybrid_atomic_load128(__p, __ATOMIC_ACQUIRE);
	while (!__hybrid_atomic_cmpxch_weak128(__p, __res, ~(__res & __val), __order, __order));
	return __res;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_nand128 */

#ifndef __hybrid_atomic_fetchinc128
#ifdef __hybrid_atomic_fetchinc
#define __hybrid_atomic_fetchinc128 __hybrid_atomic_fetchinc
#elif defined(__hybrid_atomic_fetchadd128)
#define __hybrid_atomic_fetchinc128(p, order) __hybrid_atomic_fetchadd128(p, 1, order)
#elif defined(__hybrid_atomic_fetchsub128)
#define __hybrid_atomic_fetchinc128(p, order) __hybrid_atomic_fetchsub128(p, (__UINT128_TYPE__)-1, order)
#elif defined(__hybrid_atomic_incfetch128)
#define __hybrid_atomic_fetchinc128(p, order) (__hybrid_atomic_incfetch128(p, val, order) - 1)
#endif /* ... */
#endif /* !__hybrid_atomic_inc128 */

#ifndef __hybrid_atomic_fetchdec128
#ifdef __hybrid_atomic_fetchdec
#define __hybrid_atomic_fetchdec128 __hybrid_atomic_fetchdec
#elif defined(__hybrid_atomic_fetchsub128)
#define __hybrid_atomic_fetchdec128(p, order) __hybrid_atomic_fetchsub128(p, 1, order)
#elif defined(__hybrid_atomic_fetchadd128)
#define __hybrid_atomic_fetchdec128(p, order) __hybrid_atomic_fetchadd128(p, (__UINT128_TYPE__)-1, order)
#elif defined(__hybrid_atomic_decfetch128)
#define __hybrid_atomic_fetchdec128(p, order) (__hybrid_atomic_decfetch128(p, val, order) + 1)
#endif /* ... */
#endif /* !__hybrid_atomic_dec128 */

#ifndef __hybrid_atomic_addfetch128
#ifdef __hybrid_atomic_addfetch
#define __hybrid_atomic_addfetch128 __hybrid_atomic_addfetch
#elif defined(__hybrid_atomic_subfetch)
#define __hybrid_atomic_addfetch128(p, val, order) __hybrid_atomic_subfetch(p, (__UINT128_TYPE__)(-(__INT128_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_subfetch128)
#define __hybrid_atomic_addfetch128(p, val, order) __hybrid_atomic_subfetch128(p, (__UINT128_TYPE__)(-(__INT128_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchadd128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_addfetch128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __haxf128_val = (val); __XRETURN __hybrid_atomic_fetchadd128(p, __haxf128_val, order) + __haxf128_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_addfetch128 __hybrid_atomic_addfetch128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_addfetch128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchadd128(__p, __val, __order) + __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_addfetch128 */

#ifndef __hybrid_atomic_subfetch128
#ifdef __hybrid_atomic_subfetch
#define __hybrid_atomic_subfetch128 __hybrid_atomic_subfetch
#elif defined(__hybrid_atomic_addfetch)
#define __hybrid_atomic_subfetch128(p, val, order) __hybrid_atomic_addfetch(p, (__UINT128_TYPE__)(-(__INT128_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_addfetch128)
#define __hybrid_atomic_subfetch128(p, val, order) __hybrid_atomic_addfetch128(p, (__UINT128_TYPE__)(-(__INT128_TYPE__)(val)), order)
#elif defined(__hybrid_atomic_fetchsub128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_subfetch128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __haxf128_val = (val); __XRETURN __hybrid_atomic_fetchsub128(p, __haxf128_val, order) - __haxf128_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_subfetch128 __hybrid_atomic_subfetch128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_subfetch128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchsub128(__p, __val, __order) - __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_subfetch128 */

#ifndef __hybrid_atomic_andfetch128
#ifdef __hybrid_atomic_andfetch
#define __hybrid_atomic_andfetch128 __hybrid_atomic_andfetch
#elif defined(__hybrid_atomic_fetchand128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_andfetch128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __haxf128_val = (val); __XRETURN __hybrid_atomic_fetchand128(p, __haxf128_val, order) & __haxf128_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_andfetch128 __hybrid_atomic_andfetch128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_andfetch128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchand128(__p, __val, __order) & __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_andfetch128 */

#ifndef __hybrid_atomic_xorfetch128
#ifdef __hybrid_atomic_xorfetch
#define __hybrid_atomic_xorfetch128 __hybrid_atomic_xorfetch
#elif defined(__hybrid_atomic_fetchxor128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_xorfetch128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __haxf128_val = (val); __XRETURN __hybrid_atomic_fetchxor128(p, __haxf128_val, order) ^ __haxf128_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_xorfetch128 __hybrid_atomic_xorfetch128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_xorfetch128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchxor128(__p, __val, __order) ^ __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_xorfetch128 */

#ifndef __hybrid_atomic_orfetch128
#ifdef __hybrid_atomic_orfetch
#define __hybrid_atomic_orfetch128 __hybrid_atomic_orfetch
#elif defined(__hybrid_atomic_fetchor128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_orfetch128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __haxf128_val = (val); __XRETURN __hybrid_atomic_fetchor128(p, __haxf128_val, order) | __haxf128_val; })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_orfetch128 __hybrid_atomic_orfetch128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_orfetch128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	(void)__order;
	return __hybrid_atomic_fetchor128(__p, __val, __order) | __val;
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_orfetch128 */

#ifndef __hybrid_atomic_nandfetch128
#ifdef __hybrid_atomic_nandfetch
#define __hybrid_atomic_nandfetch128 __hybrid_atomic_nandfetch
#elif defined(__hybrid_atomic_fetchnand128)
#ifndef __NO_XBLOCK
#define __hybrid_atomic_nandfetch128(p, val, order) \
	__XBLOCK({ __UINT128_TYPE__ __haxf128_val = (val); __XRETURN ~(__hybrid_atomic_fetchnand128(p, __haxf128_val, order) & __haxf128_val); })
#else /* __NO_XBLOCK */
#define __hybrid_atomic_nandfetch128 __hybrid_atomic_nandfetch128
__LOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT128_TYPE__ __NOTHROW_NCX(__hybrid_atomic_nandfetch128)(__UINT128_TYPE__ *__p, __UINT128_TYPE__ __val, int __order) {
	(void)__order;
	return ~(__hybrid_atomic_fetchnand128(__p, __val, __order) & __val);
}
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__hybrid_atomic_nandfetch128 */

#ifndef __hybrid_atomic_incfetch128
#ifdef __hybrid_atomic_incfetch
#define __hybrid_atomic_incfetch128 __hybrid_atomic_incfetch
#elif defined(__hybrid_atomic_addfetch128)
#define __hybrid_atomic_incfetch128(p, order) __hybrid_atomic_addfetch128(p, 1, order)
#elif defined(__hybrid_atomic_subfetch128)
#define __hybrid_atomic_incfetch128(p, order) __hybrid_atomic_subfetch128(p, (__UINT128_TYPE__)-1, order)
#endif /* ... */
#endif /* !__hybrid_atomic_incfetch128 */

#ifndef __hybrid_atomic_decfetch128
#ifdef __hybrid_atomic_decfetch
#define __hybrid_atomic_decfetch128 __hybrid_atomic_decfetch
#elif defined(__hybrid_atomic_subfetch128)
#define __hybrid_atomic_decfetch128(p, order) __hybrid_atomic_subfetch128(p, 1, order)
#elif defined(__hybrid_atomic_addfetch128)
#define __hybrid_atomic_decfetch128(p, order) __hybrid_atomic_addfetch128(p, (__UINT128_TYPE__)-1, order)
#endif /* ... */
#endif /* !__hybrid_atomic_decfetch128 */

#ifndef __hybrid_atomic_inc128
#ifdef __hybrid_atomic_inc
#define __hybrid_atomic_inc128 __hybrid_atomic_inc
#elif defined(__hybrid_atomic_add128)
#define __hybrid_atomic_inc128(p, order) __hybrid_atomic_add128(p, 1, order)
#elif defined(__hybrid_atomic_fetchinc128)
#define __hybrid_atomic_inc128 (void)__hybrid_atomic_fetchinc128
#elif defined(__hybrid_atomic_incfetch128)
#define __hybrid_atomic_inc128 (void)__hybrid_atomic_incfetch128
#endif /* ... */
#endif /* !__hybrid_atomic_inc128 */

#ifndef __hybrid_atomic_dec128
#ifdef __hybrid_atomic_dec
#define __hybrid_atomic_dec128 __hybrid_atomic_dec
#elif defined(__hybrid_atomic_sub128)
#define __hybrid_atomic_dec128(p, order) __hybrid_atomic_sub128(p, 1, order)
#elif defined(__hybrid_atomic_fetchdec128)
#define __hybrid_atomic_dec128 (void)__hybrid_atomic_fetchdec128
#elif defined(__hybrid_atomic_decfetch128)
#define __hybrid_atomic_dec128 (void)__hybrid_atomic_decfetch128
#endif /* ... */
#endif /* !__hybrid_atomic_dec128 */

#ifndef __hybrid_atomic_add128
#ifdef __hybrid_atomic_add
#define __hybrid_atomic_add128 __hybrid_atomic_add
#elif defined(__hybrid_atomic_fetchadd128)
#define __hybrid_atomic_add128 (void)__hybrid_atomic_fetchadd128
#elif defined(__hybrid_atomic_addfetch128)
#define __hybrid_atomic_add128 (void)__hybrid_atomic_addfetch128
#endif /* ... */
#endif /* !__hybrid_atomic_add128 */

#ifndef __hybrid_atomic_sub128
#ifdef __hybrid_atomic_sub
#define __hybrid_atomic_sub128 __hybrid_atomic_sub
#elif defined(__hybrid_atomic_fetchsub128)
#define __hybrid_atomic_sub128 (void)__hybrid_atomic_fetchsub128
#elif defined(__hybrid_atomic_subfetch128)
#define __hybrid_atomic_sub128 (void)__hybrid_atomic_subfetch128
#endif /* ... */
#endif /* !__hybrid_atomic_sub128 */

#ifndef __hybrid_atomic_and128
#ifdef __hybrid_atomic_and
#define __hybrid_atomic_and128 __hybrid_atomic_and
#elif defined(__hybrid_atomic_fetchand128)
#define __hybrid_atomic_and128 (void)__hybrid_atomic_fetchand128
#elif defined(__hybrid_atomic_andfetch128)
#define __hybrid_atomic_and128 (void)__hybrid_atomic_andfetch128
#endif /* ... */
#endif /* !__hybrid_atomic_and128 */

#ifndef __hybrid_atomic_xor128
#ifdef __hybrid_atomic_xor
#define __hybrid_atomic_xor128 __hybrid_atomic_xor
#elif defined(__hybrid_atomic_fetchxor128)
#define __hybrid_atomic_xor128 (void)__hybrid_atomic_fetchxor128
#elif defined(__hybrid_atomic_xorfetch128)
#define __hybrid_atomic_xor128 (void)__hybrid_atomic_xorfetch128
#endif /* ... */
#endif /* !__hybrid_atomic_xor128 */

#ifndef __hybrid_atomic_or128
#ifdef __hybrid_atomic_or
#define __hybrid_atomic_or128 __hybrid_atomic_or
#elif defined(__hybrid_atomic_fetchor128)
#define __hybrid_atomic_or128 (void)__hybrid_atomic_fetchor128
#elif defined(__hybrid_atomic_orfetch128)
#define __hybrid_atomic_or128 (void)__hybrid_atomic_orfetch128
#endif /* ... */
#endif /* !__hybrid_atomic_or128 */

#ifndef __hybrid_atomic_nand128
#ifdef __hybrid_atomic_nand
#define __hybrid_atomic_nand128 __hybrid_atomic_nand
#elif defined(__hybrid_atomic_fetchnand128)
#define __hybrid_atomic_nand128 (void)__hybrid_atomic_fetchnand128
#elif defined(__hybrid_atomic_nandfetch128)
#define __hybrid_atomic_nand128 (void)__hybrid_atomic_nandfetch128
#endif /* ... */
#endif /* !__hybrid_atomic_nand128 */

#endif /* __UINT128_TYPE__ */
/*[[[end]]]*/
/* clang-format on */



/* Type-generic functions */

#ifndef __cplusplus
#ifdef __COMPILER_HAVE_TYPEOF
#define __HYBRID_ATOMIC_RECAST(p, y) ((__typeof__(*(p)))(y))
#elif 1
#define __HYBRID_ATOMIC_RECAST(p, y) (1 ? (y) : *(p))
#else /* ... */
#define __HYBRID_ATOMIC_RECAST(p, y) (y)
#endif /* !... */
#endif /* !__cplusplus */

#if defined(_MSC_VER) && !defined(__cplusplus)
#define __HYBRID_ATOMIC_DOWNCAST(T) (T)(__UINTPTR_TYPE__)
#else /* _MSC_VER && !__cplusplus */
#define __HYBRID_ATOMIC_DOWNCAST(T) (T)
#endif /* !_MSC_VER || __cplusplus */

/* clang-format off */
/*[[[deemon
import * from deemon;
global final SIZES = [8, 16, 32, 64, 128];
function makeTypeGeneric(
		name: string,
		returnType: string = "__T",
		params: {string...} = (),
		order2: bool = false,
		const: bool = false) {
	print("#ifndef __hybrid_atomic_", name);
	local minSize = SIZES < ...;
	if (name in ["inc", "dec", "fetchinc", "fetchdec", "incfetch", "decfetch"]) {
		local subname = "inc" in name ? name.replace("inc", "add")
		                              : name.replace("dec", "sub");
		print("#ifdef __hybrid_atomic_", subname);
		print("#define __hybrid_atomic_", name, "(p, order) __hybrid_atomic_", subname, "(p, 1, order)");
		print("#elif defined(__hybrid_atomic_", name, minSize, ")");
	} else {
		print("#ifdef __hybrid_atomic_", name, minSize);
	}
	print("#ifdef __cplusplus");
	print('extern "C++" {');
	print("#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED");
	print("#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED");
	print("__NAMESPACE_INT_BEGIN");
	print("template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };");
	print("template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};");
	print("__NAMESPACE_INT_END");
	print("#endif /" "* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED *" "/");
	print("#define __hybrid_atomic_", name, " __hybrid_atomic_", name);
	print("template<class __T"),;
	for (local p: params)
		print(", class __T", p),;
	print("> inline __ATTR_ARTIFICIAL "),;
	if (returnType != "void")
		print("__ATTR_WUNUSED "),;
	print("__ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false");
	for (local n: SIZES) {
		print("#ifdef __hybrid_atomic_", name, n);
		print("	|| sizeof(__T) == ", (n / 8));
		print("#endif /" "* __hybrid_atomic_", name, n, " *" "/");
	}
	print(", ", returnType, ">::__type __NOTHROW_NCX(__hybrid_atomic_", name, ")(__T "),;
	if (const)
		print("const "),;
	print("*__p"),;
	for (local p: params)
		print(", __T", p, " __", p),;
	print(", ", order2 ? "int __succ, int __fail" : "int __order", ") {");
	print("	", order2 ? "(void)__succ, (void)__fail" : "(void)__order", ";");
	for (local n: SIZES) {
		print("#ifdef __hybrid_atomic_", name, n);
		print("	__STATIC_IF(sizeof(__T) == ", (n / 8), ") { "),;
		if (returnType != "void") {
			print("return "),;
			if (returnType == "__T")
				print("(__T)"),;
		}
		print("__hybrid_atomic_", name, n, "("),;
		print("(__UINT", n, "_TYPE__ "),;
		if (const)
			print("const "),;
		print("*)__p"),;
		for (local p: params)
			print(", (__UINT", n, "_TYPE__)__", p),;
		print(", ", order2 ? "__succ, __fail" : "__order", "); }");
		print("	__STATIC_ELSE(sizeof(__T) == ", (n / 8), ")");
		print("#endif /" "* __hybrid_atomic_", name, n, " *" "/");
		print("	{"),;
		if (n != SIZES.last)
			print;
	}
	print(" __builtin_unreachable(); ", "}" * #SIZES);
	print("}");
	print('} /' '* extern "C++" *' '/');
	print("#else /" "* __cplusplus *" "/");

	function defineCOverloadMacro(sizes: {int...}) {
		print("#define __hybrid_atomic_", name, "(p"),;
		for (local p: params)
			print(", ", p),;
		print(", ", order2 ? "succ, fail" : "order", ") \\");
		if (returnType != "void") {
			print("	__HYBRID_ATOMIC_RECAST(p, "),;
		} else {
			print("	("),;
		}
		local isFirst = true;
		local maxSizeWidth = #str((for (local s: sizes[:-1]) s / 8) > ...);
		for (local n: sizes) {
			if (!isFirst) {
				print(" \\");
				if (returnType != "void") {
					print("	                          "),;
				} else {
					print("	 "),;
				}
			}
			if (n != sizes.last) {
				print("sizeof(*(p)) == ", str(n / 8).ljust(maxSizeWidth), " ? "),;
			} else if (n != sizes.first) {
				print("                ", " ".ljust(maxSizeWidth), "   "),;
			}
			print("__hybrid_atomic_", name, n, "((__UINT", n, "_TYPE__ "),;
			if (const)
				print("const "),;
			print("*)(p)"),;
			for (local p: params)
				print(", __HYBRID_ATOMIC_DOWNCAST(__UINT", n, "_TYPE__)(", p, ")"),;
			print(", ", order2 ? "succ, fail" : "order", ")"),;
			if (n != sizes.last)
				print(" :"),;
			isFirst = false;
		}
		print(")");
	}
	print("#ifdef __hybrid_atomic_", name, "128");
	defineCOverloadMacro([8, 16, 32, 64, 128]);
	print("#elif defined(__hybrid_atomic_", name, "64)");
	defineCOverloadMacro([8, 16, 32, 64]);
	print("#elif defined(__hybrid_atomic_", name, "32)");
	defineCOverloadMacro([8, 16, 32]);
	print("#elif defined(__hybrid_atomic_", name, "16)");
	defineCOverloadMacro([8, 16]);
	print("#else /" "* ... *" "/");
	defineCOverloadMacro([8]);
	print("#endif /" "* !... *" "/");
	print("#endif /" "* !__cplusplus *" "/");
	print("#endif /" "* __hybrid_atomic_", name, minSize, " *" "/");
	print("#endif /" "* !__hybrid_atomic_", name, " *" "/");
}

makeTypeGeneric("cmpxch",      returnType: "bool", params: ["oldval", "newval"], order2: true);
makeTypeGeneric("cmpxch_weak", returnType: "bool", params: ["oldval", "newval"], order2: true);
makeTypeGeneric("cmpxch_val",  returnType: "__T",  params: ["oldval", "newval"], order2: true);
makeTypeGeneric("load",        returnType: "__T",  params: [], const: true);
makeTypeGeneric("store",       returnType: "void", params: ["val"]);
makeTypeGeneric("xch",         returnType: "__T",  params: ["val"]);
makeTypeGeneric("fetchadd",    returnType: "__T",  params: ["val"]);
makeTypeGeneric("fetchsub",    returnType: "__T",  params: ["val"]);
makeTypeGeneric("fetchand",    returnType: "__T",  params: ["val"]);
makeTypeGeneric("fetchxor",    returnType: "__T",  params: ["val"]);
makeTypeGeneric("fetchor",     returnType: "__T",  params: ["val"]);
makeTypeGeneric("fetchnand",   returnType: "__T",  params: ["val"]);
makeTypeGeneric("fetchinc",    returnType: "__T",  params: []);
makeTypeGeneric("fetchdec",    returnType: "__T",  params: []);
makeTypeGeneric("addfetch",    returnType: "__T",  params: ["val"]);
makeTypeGeneric("subfetch",    returnType: "__T",  params: ["val"]);
makeTypeGeneric("andfetch",    returnType: "__T",  params: ["val"]);
makeTypeGeneric("xorfetch",    returnType: "__T",  params: ["val"]);
makeTypeGeneric("orfetch",     returnType: "__T",  params: ["val"]);
makeTypeGeneric("nandfetch",   returnType: "__T",  params: ["val"]);
makeTypeGeneric("incfetch",    returnType: "__T",  params: []);
makeTypeGeneric("decfetch",    returnType: "__T",  params: []);
makeTypeGeneric("add",         returnType: "void", params: ["val"]);
makeTypeGeneric("sub",         returnType: "void", params: ["val"]);
makeTypeGeneric("and",         returnType: "void", params: ["val"]);
makeTypeGeneric("xor",         returnType: "void", params: ["val"]);
makeTypeGeneric("or",          returnType: "void", params: ["val"]);
makeTypeGeneric("nand",        returnType: "void", params: ["val"]);
makeTypeGeneric("inc",         returnType: "void", params: []);
makeTypeGeneric("dec",         returnType: "void", params: []);
]]]*/
#ifndef __hybrid_atomic_cmpxch
#ifdef __hybrid_atomic_cmpxch8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_cmpxch __hybrid_atomic_cmpxch
template<class __T, class __Toldval, class __Tnewval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_cmpxch8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_cmpxch8 */
#ifdef __hybrid_atomic_cmpxch16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_cmpxch16 */
#ifdef __hybrid_atomic_cmpxch32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_cmpxch32 */
#ifdef __hybrid_atomic_cmpxch64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_cmpxch64 */
#ifdef __hybrid_atomic_cmpxch128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_cmpxch128 */
, bool>::__type __NOTHROW_NCX(__hybrid_atomic_cmpxch)(__T *__p, __Toldval __oldval, __Tnewval __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
#ifdef __hybrid_atomic_cmpxch8
	__STATIC_IF(sizeof(__T) == 1) { return __hybrid_atomic_cmpxch8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__oldval, (__UINT8_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_cmpxch8 */
	{
#ifdef __hybrid_atomic_cmpxch16
	__STATIC_IF(sizeof(__T) == 2) { return __hybrid_atomic_cmpxch16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__oldval, (__UINT16_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_cmpxch16 */
	{
#ifdef __hybrid_atomic_cmpxch32
	__STATIC_IF(sizeof(__T) == 4) { return __hybrid_atomic_cmpxch32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__oldval, (__UINT32_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_cmpxch32 */
	{
#ifdef __hybrid_atomic_cmpxch64
	__STATIC_IF(sizeof(__T) == 8) { return __hybrid_atomic_cmpxch64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__oldval, (__UINT64_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_cmpxch64 */
	{
#ifdef __hybrid_atomic_cmpxch128
	__STATIC_IF(sizeof(__T) == 16) { return __hybrid_atomic_cmpxch128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__oldval, (__UINT128_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_cmpxch128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_cmpxch128
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_cmpxch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_cmpxch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_cmpxch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(newval), succ, fail))
#elif defined(__hybrid_atomic_cmpxch64)
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_cmpxch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_cmpxch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(newval), succ, fail))
#elif defined(__hybrid_atomic_cmpxch32)
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_cmpxch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(newval), succ, fail))
#elif defined(__hybrid_atomic_cmpxch16)
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail))
#else /* ... */
#define __hybrid_atomic_cmpxch(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_cmpxch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_cmpxch8 */
#endif /* !__hybrid_atomic_cmpxch */
#ifndef __hybrid_atomic_cmpxch_weak
#ifdef __hybrid_atomic_cmpxch_weak8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_cmpxch_weak __hybrid_atomic_cmpxch_weak
template<class __T, class __Toldval, class __Tnewval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_cmpxch_weak8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_cmpxch_weak8 */
#ifdef __hybrid_atomic_cmpxch_weak16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_cmpxch_weak16 */
#ifdef __hybrid_atomic_cmpxch_weak32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_cmpxch_weak32 */
#ifdef __hybrid_atomic_cmpxch_weak64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_cmpxch_weak64 */
#ifdef __hybrid_atomic_cmpxch_weak128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_cmpxch_weak128 */
, bool>::__type __NOTHROW_NCX(__hybrid_atomic_cmpxch_weak)(__T *__p, __Toldval __oldval, __Tnewval __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
#ifdef __hybrid_atomic_cmpxch_weak8
	__STATIC_IF(sizeof(__T) == 1) { return __hybrid_atomic_cmpxch_weak8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__oldval, (__UINT8_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_cmpxch_weak8 */
	{
#ifdef __hybrid_atomic_cmpxch_weak16
	__STATIC_IF(sizeof(__T) == 2) { return __hybrid_atomic_cmpxch_weak16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__oldval, (__UINT16_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_cmpxch_weak16 */
	{
#ifdef __hybrid_atomic_cmpxch_weak32
	__STATIC_IF(sizeof(__T) == 4) { return __hybrid_atomic_cmpxch_weak32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__oldval, (__UINT32_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_cmpxch_weak32 */
	{
#ifdef __hybrid_atomic_cmpxch_weak64
	__STATIC_IF(sizeof(__T) == 8) { return __hybrid_atomic_cmpxch_weak64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__oldval, (__UINT64_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_cmpxch_weak64 */
	{
#ifdef __hybrid_atomic_cmpxch_weak128
	__STATIC_IF(sizeof(__T) == 16) { return __hybrid_atomic_cmpxch_weak128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__oldval, (__UINT128_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_cmpxch_weak128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_cmpxch_weak128
#define __hybrid_atomic_cmpxch_weak(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch_weak8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_cmpxch_weak16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_cmpxch_weak32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_cmpxch_weak64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch_weak128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(newval), succ, fail))
#elif defined(__hybrid_atomic_cmpxch_weak64)
#define __hybrid_atomic_cmpxch_weak(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch_weak8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_cmpxch_weak16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_cmpxch_weak32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch_weak64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(newval), succ, fail))
#elif defined(__hybrid_atomic_cmpxch_weak32)
#define __hybrid_atomic_cmpxch_weak(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch_weak8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_cmpxch_weak16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch_weak32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(newval), succ, fail))
#elif defined(__hybrid_atomic_cmpxch_weak16)
#define __hybrid_atomic_cmpxch_weak(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch_weak8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch_weak16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail))
#else /* ... */
#define __hybrid_atomic_cmpxch_weak(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_cmpxch_weak8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_cmpxch_weak8 */
#endif /* !__hybrid_atomic_cmpxch_weak */
#ifndef __hybrid_atomic_cmpxch_val
#ifdef __hybrid_atomic_cmpxch_val8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_cmpxch_val __hybrid_atomic_cmpxch_val
template<class __T, class __Toldval, class __Tnewval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_cmpxch_val8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_cmpxch_val8 */
#ifdef __hybrid_atomic_cmpxch_val16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_cmpxch_val16 */
#ifdef __hybrid_atomic_cmpxch_val32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_cmpxch_val32 */
#ifdef __hybrid_atomic_cmpxch_val64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_cmpxch_val64 */
#ifdef __hybrid_atomic_cmpxch_val128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_cmpxch_val128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_cmpxch_val)(__T *__p, __Toldval __oldval, __Tnewval __newval, int __succ, int __fail) {
	(void)__succ, (void)__fail;
#ifdef __hybrid_atomic_cmpxch_val8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_cmpxch_val8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__oldval, (__UINT8_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_cmpxch_val8 */
	{
#ifdef __hybrid_atomic_cmpxch_val16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_cmpxch_val16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__oldval, (__UINT16_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_cmpxch_val16 */
	{
#ifdef __hybrid_atomic_cmpxch_val32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_cmpxch_val32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__oldval, (__UINT32_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_cmpxch_val32 */
	{
#ifdef __hybrid_atomic_cmpxch_val64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_cmpxch_val64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__oldval, (__UINT64_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_cmpxch_val64 */
	{
#ifdef __hybrid_atomic_cmpxch_val128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_cmpxch_val128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__oldval, (__UINT128_TYPE__)__newval, __succ, __fail); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_cmpxch_val128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_cmpxch_val128
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch_val8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_cmpxch_val16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_cmpxch_val32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_cmpxch_val64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch_val128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(newval), succ, fail))
#elif defined(__hybrid_atomic_cmpxch_val64)
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch_val8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_cmpxch_val16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_cmpxch_val32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch_val64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(newval), succ, fail))
#elif defined(__hybrid_atomic_cmpxch_val32)
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch_val8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_cmpxch_val16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch_val32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(newval), succ, fail))
#elif defined(__hybrid_atomic_cmpxch_val16)
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_cmpxch_val8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail) : \
	                                              __hybrid_atomic_cmpxch_val16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(newval), succ, fail))
#else /* ... */
#define __hybrid_atomic_cmpxch_val(p, oldval, newval, succ, fail) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_cmpxch_val8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(oldval), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(newval), succ, fail))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_cmpxch_val8 */
#endif /* !__hybrid_atomic_cmpxch_val */
#ifndef __hybrid_atomic_load
#ifdef __hybrid_atomic_load8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_load __hybrid_atomic_load
template<class __T> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_load8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_load8 */
#ifdef __hybrid_atomic_load16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_load16 */
#ifdef __hybrid_atomic_load32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_load32 */
#ifdef __hybrid_atomic_load64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_load64 */
#ifdef __hybrid_atomic_load128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_load128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_load)(__T const *__p, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_load8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_load8((__UINT8_TYPE__ const *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_load8 */
	{
#ifdef __hybrid_atomic_load16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_load16((__UINT16_TYPE__ const *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_load16 */
	{
#ifdef __hybrid_atomic_load32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_load32((__UINT32_TYPE__ const *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_load32 */
	{
#ifdef __hybrid_atomic_load64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_load64((__UINT64_TYPE__ const *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_load64 */
	{
#ifdef __hybrid_atomic_load128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_load128((__UINT128_TYPE__ const *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_load128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_load128
#define __hybrid_atomic_load(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_load8((__UINT8_TYPE__ const *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_load16((__UINT16_TYPE__ const *)(p), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_load32((__UINT32_TYPE__ const *)(p), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_load64((__UINT64_TYPE__ const *)(p), order) : \
	                                              __hybrid_atomic_load128((__UINT128_TYPE__ const *)(p), order))
#elif defined(__hybrid_atomic_load64)
#define __hybrid_atomic_load(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_load8((__UINT8_TYPE__ const *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_load16((__UINT16_TYPE__ const *)(p), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_load32((__UINT32_TYPE__ const *)(p), order) : \
	                                              __hybrid_atomic_load64((__UINT64_TYPE__ const *)(p), order))
#elif defined(__hybrid_atomic_load32)
#define __hybrid_atomic_load(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_load8((__UINT8_TYPE__ const *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_load16((__UINT16_TYPE__ const *)(p), order) : \
	                                              __hybrid_atomic_load32((__UINT32_TYPE__ const *)(p), order))
#elif defined(__hybrid_atomic_load16)
#define __hybrid_atomic_load(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_load8((__UINT8_TYPE__ const *)(p), order) : \
	                                              __hybrid_atomic_load16((__UINT16_TYPE__ const *)(p), order))
#else /* ... */
#define __hybrid_atomic_load(p, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_load8((__UINT8_TYPE__ const *)(p), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_load8 */
#endif /* !__hybrid_atomic_load */
#ifndef __hybrid_atomic_store
#ifdef __hybrid_atomic_store8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_store __hybrid_atomic_store
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_store8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_store8 */
#ifdef __hybrid_atomic_store16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_store16 */
#ifdef __hybrid_atomic_store32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_store32 */
#ifdef __hybrid_atomic_store64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_store64 */
#ifdef __hybrid_atomic_store128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_store128 */
, void>::__type __NOTHROW_NCX(__hybrid_atomic_store)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_store8
	__STATIC_IF(sizeof(__T) == 1) { __hybrid_atomic_store8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_store8 */
	{
#ifdef __hybrid_atomic_store16
	__STATIC_IF(sizeof(__T) == 2) { __hybrid_atomic_store16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_store16 */
	{
#ifdef __hybrid_atomic_store32
	__STATIC_IF(sizeof(__T) == 4) { __hybrid_atomic_store32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_store32 */
	{
#ifdef __hybrid_atomic_store64
	__STATIC_IF(sizeof(__T) == 8) { __hybrid_atomic_store64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_store64 */
	{
#ifdef __hybrid_atomic_store128
	__STATIC_IF(sizeof(__T) == 16) { __hybrid_atomic_store128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_store128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_store128
#define __hybrid_atomic_store(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_store8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_store16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_store32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	 sizeof(*(p)) == 8 ? __hybrid_atomic_store64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                     __hybrid_atomic_store128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_store64)
#define __hybrid_atomic_store(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_store8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_store16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_store32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                     __hybrid_atomic_store64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_store32)
#define __hybrid_atomic_store(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_store8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_store16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                     __hybrid_atomic_store32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_store16)
#define __hybrid_atomic_store(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_store8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                     __hybrid_atomic_store16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_store(p, val, order) \
	(__hybrid_atomic_store8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_store8 */
#endif /* !__hybrid_atomic_store */
#ifndef __hybrid_atomic_xch
#ifdef __hybrid_atomic_xch8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_xch __hybrid_atomic_xch
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_xch8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_xch8 */
#ifdef __hybrid_atomic_xch16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_xch16 */
#ifdef __hybrid_atomic_xch32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_xch32 */
#ifdef __hybrid_atomic_xch64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_xch64 */
#ifdef __hybrid_atomic_xch128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_xch128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_xch)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_xch8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_xch8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_xch8 */
	{
#ifdef __hybrid_atomic_xch16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_xch16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_xch16 */
	{
#ifdef __hybrid_atomic_xch32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_xch32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_xch32 */
	{
#ifdef __hybrid_atomic_xch64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_xch64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_xch64 */
	{
#ifdef __hybrid_atomic_xch128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_xch128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_xch128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_xch128
#define __hybrid_atomic_xch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_xch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_xch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_xch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_xch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_xch128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_xch64)
#define __hybrid_atomic_xch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_xch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_xch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_xch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_xch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_xch32)
#define __hybrid_atomic_xch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_xch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_xch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_xch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_xch16)
#define __hybrid_atomic_xch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_xch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_xch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_xch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_xch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_xch8 */
#endif /* !__hybrid_atomic_xch */
#ifndef __hybrid_atomic_fetchadd
#ifdef __hybrid_atomic_fetchadd8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_fetchadd __hybrid_atomic_fetchadd
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_fetchadd8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_fetchadd8 */
#ifdef __hybrid_atomic_fetchadd16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_fetchadd16 */
#ifdef __hybrid_atomic_fetchadd32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_fetchadd32 */
#ifdef __hybrid_atomic_fetchadd64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_fetchadd64 */
#ifdef __hybrid_atomic_fetchadd128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_fetchadd128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_fetchadd)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_fetchadd8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_fetchadd8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_fetchadd8 */
	{
#ifdef __hybrid_atomic_fetchadd16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_fetchadd16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_fetchadd16 */
	{
#ifdef __hybrid_atomic_fetchadd32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_fetchadd32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_fetchadd32 */
	{
#ifdef __hybrid_atomic_fetchadd64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_fetchadd64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_fetchadd64 */
	{
#ifdef __hybrid_atomic_fetchadd128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_fetchadd128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_fetchadd128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_fetchadd128
#define __hybrid_atomic_fetchadd(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchadd8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchadd16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchadd32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_fetchadd64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchadd128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchadd64)
#define __hybrid_atomic_fetchadd(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchadd8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchadd16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchadd32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchadd64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchadd32)
#define __hybrid_atomic_fetchadd(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchadd8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchadd16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchadd32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchadd16)
#define __hybrid_atomic_fetchadd(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchadd8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchadd16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_fetchadd(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_fetchadd8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_fetchadd8 */
#endif /* !__hybrid_atomic_fetchadd */
#ifndef __hybrid_atomic_fetchsub
#ifdef __hybrid_atomic_fetchsub8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_fetchsub __hybrid_atomic_fetchsub
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_fetchsub8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_fetchsub8 */
#ifdef __hybrid_atomic_fetchsub16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_fetchsub16 */
#ifdef __hybrid_atomic_fetchsub32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_fetchsub32 */
#ifdef __hybrid_atomic_fetchsub64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_fetchsub64 */
#ifdef __hybrid_atomic_fetchsub128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_fetchsub128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_fetchsub)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_fetchsub8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_fetchsub8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_fetchsub8 */
	{
#ifdef __hybrid_atomic_fetchsub16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_fetchsub16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_fetchsub16 */
	{
#ifdef __hybrid_atomic_fetchsub32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_fetchsub32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_fetchsub32 */
	{
#ifdef __hybrid_atomic_fetchsub64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_fetchsub64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_fetchsub64 */
	{
#ifdef __hybrid_atomic_fetchsub128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_fetchsub128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_fetchsub128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_fetchsub128
#define __hybrid_atomic_fetchsub(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchsub8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchsub16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchsub32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_fetchsub64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchsub128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchsub64)
#define __hybrid_atomic_fetchsub(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchsub8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchsub16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchsub32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchsub64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchsub32)
#define __hybrid_atomic_fetchsub(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchsub8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchsub16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchsub32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchsub16)
#define __hybrid_atomic_fetchsub(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchsub8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchsub16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_fetchsub(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_fetchsub8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_fetchsub8 */
#endif /* !__hybrid_atomic_fetchsub */
#ifndef __hybrid_atomic_fetchand
#ifdef __hybrid_atomic_fetchand8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_fetchand __hybrid_atomic_fetchand
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_fetchand8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_fetchand8 */
#ifdef __hybrid_atomic_fetchand16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_fetchand16 */
#ifdef __hybrid_atomic_fetchand32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_fetchand32 */
#ifdef __hybrid_atomic_fetchand64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_fetchand64 */
#ifdef __hybrid_atomic_fetchand128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_fetchand128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_fetchand)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_fetchand8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_fetchand8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_fetchand8 */
	{
#ifdef __hybrid_atomic_fetchand16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_fetchand16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_fetchand16 */
	{
#ifdef __hybrid_atomic_fetchand32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_fetchand32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_fetchand32 */
	{
#ifdef __hybrid_atomic_fetchand64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_fetchand64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_fetchand64 */
	{
#ifdef __hybrid_atomic_fetchand128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_fetchand128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_fetchand128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_fetchand128
#define __hybrid_atomic_fetchand(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchand32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_fetchand64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchand128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchand64)
#define __hybrid_atomic_fetchand(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchand32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchand64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchand32)
#define __hybrid_atomic_fetchand(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchand32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchand16)
#define __hybrid_atomic_fetchand(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_fetchand(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_fetchand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_fetchand8 */
#endif /* !__hybrid_atomic_fetchand */
#ifndef __hybrid_atomic_fetchxor
#ifdef __hybrid_atomic_fetchxor8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_fetchxor __hybrid_atomic_fetchxor
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_fetchxor8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_fetchxor8 */
#ifdef __hybrid_atomic_fetchxor16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_fetchxor16 */
#ifdef __hybrid_atomic_fetchxor32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_fetchxor32 */
#ifdef __hybrid_atomic_fetchxor64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_fetchxor64 */
#ifdef __hybrid_atomic_fetchxor128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_fetchxor128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_fetchxor)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_fetchxor8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_fetchxor8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_fetchxor8 */
	{
#ifdef __hybrid_atomic_fetchxor16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_fetchxor16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_fetchxor16 */
	{
#ifdef __hybrid_atomic_fetchxor32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_fetchxor32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_fetchxor32 */
	{
#ifdef __hybrid_atomic_fetchxor64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_fetchxor64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_fetchxor64 */
	{
#ifdef __hybrid_atomic_fetchxor128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_fetchxor128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_fetchxor128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_fetchxor128
#define __hybrid_atomic_fetchxor(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchxor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchxor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchxor32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_fetchxor64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchxor128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchxor64)
#define __hybrid_atomic_fetchxor(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchxor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchxor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchxor32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchxor64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchxor32)
#define __hybrid_atomic_fetchxor(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchxor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchxor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchxor32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchxor16)
#define __hybrid_atomic_fetchxor(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchxor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchxor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_fetchxor(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_fetchxor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_fetchxor8 */
#endif /* !__hybrid_atomic_fetchxor */
#ifndef __hybrid_atomic_fetchor
#ifdef __hybrid_atomic_fetchor8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_fetchor __hybrid_atomic_fetchor
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_fetchor8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_fetchor8 */
#ifdef __hybrid_atomic_fetchor16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_fetchor16 */
#ifdef __hybrid_atomic_fetchor32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_fetchor32 */
#ifdef __hybrid_atomic_fetchor64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_fetchor64 */
#ifdef __hybrid_atomic_fetchor128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_fetchor128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_fetchor)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_fetchor8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_fetchor8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_fetchor8 */
	{
#ifdef __hybrid_atomic_fetchor16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_fetchor16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_fetchor16 */
	{
#ifdef __hybrid_atomic_fetchor32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_fetchor32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_fetchor32 */
	{
#ifdef __hybrid_atomic_fetchor64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_fetchor64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_fetchor64 */
	{
#ifdef __hybrid_atomic_fetchor128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_fetchor128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_fetchor128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_fetchor128
#define __hybrid_atomic_fetchor(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchor32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_fetchor64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchor128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchor64)
#define __hybrid_atomic_fetchor(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchor32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchor64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchor32)
#define __hybrid_atomic_fetchor(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchor32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchor16)
#define __hybrid_atomic_fetchor(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_fetchor(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_fetchor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_fetchor8 */
#endif /* !__hybrid_atomic_fetchor */
#ifndef __hybrid_atomic_fetchnand
#ifdef __hybrid_atomic_fetchnand8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_fetchnand __hybrid_atomic_fetchnand
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_fetchnand8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_fetchnand8 */
#ifdef __hybrid_atomic_fetchnand16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_fetchnand16 */
#ifdef __hybrid_atomic_fetchnand32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_fetchnand32 */
#ifdef __hybrid_atomic_fetchnand64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_fetchnand64 */
#ifdef __hybrid_atomic_fetchnand128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_fetchnand128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_fetchnand)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_fetchnand8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_fetchnand8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_fetchnand8 */
	{
#ifdef __hybrid_atomic_fetchnand16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_fetchnand16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_fetchnand16 */
	{
#ifdef __hybrid_atomic_fetchnand32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_fetchnand32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_fetchnand32 */
	{
#ifdef __hybrid_atomic_fetchnand64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_fetchnand64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_fetchnand64 */
	{
#ifdef __hybrid_atomic_fetchnand128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_fetchnand128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_fetchnand128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_fetchnand128
#define __hybrid_atomic_fetchnand(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchnand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchnand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchnand32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_fetchnand64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchnand128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchnand64)
#define __hybrid_atomic_fetchnand(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchnand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchnand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchnand32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchnand64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchnand32)
#define __hybrid_atomic_fetchnand(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchnand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchnand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchnand32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_fetchnand16)
#define __hybrid_atomic_fetchnand(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchnand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_fetchnand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_fetchnand(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_fetchnand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_fetchnand8 */
#endif /* !__hybrid_atomic_fetchnand */
#ifndef __hybrid_atomic_fetchinc
#ifdef __hybrid_atomic_fetchadd
#define __hybrid_atomic_fetchinc(p, order) __hybrid_atomic_fetchadd(p, 1, order)
#elif defined(__hybrid_atomic_fetchinc8)
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_fetchinc __hybrid_atomic_fetchinc
template<class __T> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_fetchinc8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_fetchinc8 */
#ifdef __hybrid_atomic_fetchinc16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_fetchinc16 */
#ifdef __hybrid_atomic_fetchinc32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_fetchinc32 */
#ifdef __hybrid_atomic_fetchinc64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_fetchinc64 */
#ifdef __hybrid_atomic_fetchinc128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_fetchinc128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_fetchinc)(__T *__p, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_fetchinc8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_fetchinc8((__UINT8_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_fetchinc8 */
	{
#ifdef __hybrid_atomic_fetchinc16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_fetchinc16((__UINT16_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_fetchinc16 */
	{
#ifdef __hybrid_atomic_fetchinc32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_fetchinc32((__UINT32_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_fetchinc32 */
	{
#ifdef __hybrid_atomic_fetchinc64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_fetchinc64((__UINT64_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_fetchinc64 */
	{
#ifdef __hybrid_atomic_fetchinc128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_fetchinc128((__UINT128_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_fetchinc128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_fetchinc128
#define __hybrid_atomic_fetchinc(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchinc8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchinc16((__UINT16_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchinc32((__UINT32_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_fetchinc64((__UINT64_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_fetchinc128((__UINT128_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_fetchinc64)
#define __hybrid_atomic_fetchinc(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchinc8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchinc16((__UINT16_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchinc32((__UINT32_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_fetchinc64((__UINT64_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_fetchinc32)
#define __hybrid_atomic_fetchinc(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchinc8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchinc16((__UINT16_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_fetchinc32((__UINT32_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_fetchinc16)
#define __hybrid_atomic_fetchinc(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchinc8((__UINT8_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_fetchinc16((__UINT16_TYPE__ *)(p), order))
#else /* ... */
#define __hybrid_atomic_fetchinc(p, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_fetchinc8((__UINT8_TYPE__ *)(p), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_fetchinc8 */
#endif /* !__hybrid_atomic_fetchinc */
#ifndef __hybrid_atomic_fetchdec
#ifdef __hybrid_atomic_fetchsub
#define __hybrid_atomic_fetchdec(p, order) __hybrid_atomic_fetchsub(p, 1, order)
#elif defined(__hybrid_atomic_fetchdec8)
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_fetchdec __hybrid_atomic_fetchdec
template<class __T> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_fetchdec8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_fetchdec8 */
#ifdef __hybrid_atomic_fetchdec16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_fetchdec16 */
#ifdef __hybrid_atomic_fetchdec32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_fetchdec32 */
#ifdef __hybrid_atomic_fetchdec64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_fetchdec64 */
#ifdef __hybrid_atomic_fetchdec128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_fetchdec128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_fetchdec)(__T *__p, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_fetchdec8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_fetchdec8((__UINT8_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_fetchdec8 */
	{
#ifdef __hybrid_atomic_fetchdec16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_fetchdec16((__UINT16_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_fetchdec16 */
	{
#ifdef __hybrid_atomic_fetchdec32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_fetchdec32((__UINT32_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_fetchdec32 */
	{
#ifdef __hybrid_atomic_fetchdec64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_fetchdec64((__UINT64_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_fetchdec64 */
	{
#ifdef __hybrid_atomic_fetchdec128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_fetchdec128((__UINT128_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_fetchdec128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_fetchdec128
#define __hybrid_atomic_fetchdec(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchdec8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchdec16((__UINT16_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchdec32((__UINT32_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_fetchdec64((__UINT64_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_fetchdec128((__UINT128_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_fetchdec64)
#define __hybrid_atomic_fetchdec(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchdec8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchdec16((__UINT16_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_fetchdec32((__UINT32_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_fetchdec64((__UINT64_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_fetchdec32)
#define __hybrid_atomic_fetchdec(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchdec8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_fetchdec16((__UINT16_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_fetchdec32((__UINT32_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_fetchdec16)
#define __hybrid_atomic_fetchdec(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_fetchdec8((__UINT8_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_fetchdec16((__UINT16_TYPE__ *)(p), order))
#else /* ... */
#define __hybrid_atomic_fetchdec(p, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_fetchdec8((__UINT8_TYPE__ *)(p), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_fetchdec8 */
#endif /* !__hybrid_atomic_fetchdec */
#ifndef __hybrid_atomic_addfetch
#ifdef __hybrid_atomic_addfetch8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_addfetch __hybrid_atomic_addfetch
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_addfetch8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_addfetch8 */
#ifdef __hybrid_atomic_addfetch16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_addfetch16 */
#ifdef __hybrid_atomic_addfetch32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_addfetch32 */
#ifdef __hybrid_atomic_addfetch64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_addfetch64 */
#ifdef __hybrid_atomic_addfetch128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_addfetch128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_addfetch)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_addfetch8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_addfetch8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_addfetch8 */
	{
#ifdef __hybrid_atomic_addfetch16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_addfetch16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_addfetch16 */
	{
#ifdef __hybrid_atomic_addfetch32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_addfetch32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_addfetch32 */
	{
#ifdef __hybrid_atomic_addfetch64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_addfetch64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_addfetch64 */
	{
#ifdef __hybrid_atomic_addfetch128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_addfetch128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_addfetch128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_addfetch128
#define __hybrid_atomic_addfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_addfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_addfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_addfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_addfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_addfetch128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_addfetch64)
#define __hybrid_atomic_addfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_addfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_addfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_addfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_addfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_addfetch32)
#define __hybrid_atomic_addfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_addfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_addfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_addfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_addfetch16)
#define __hybrid_atomic_addfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_addfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_addfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_addfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_addfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_addfetch8 */
#endif /* !__hybrid_atomic_addfetch */
#ifndef __hybrid_atomic_subfetch
#ifdef __hybrid_atomic_subfetch8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_subfetch __hybrid_atomic_subfetch
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_subfetch8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_subfetch8 */
#ifdef __hybrid_atomic_subfetch16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_subfetch16 */
#ifdef __hybrid_atomic_subfetch32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_subfetch32 */
#ifdef __hybrid_atomic_subfetch64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_subfetch64 */
#ifdef __hybrid_atomic_subfetch128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_subfetch128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_subfetch)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_subfetch8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_subfetch8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_subfetch8 */
	{
#ifdef __hybrid_atomic_subfetch16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_subfetch16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_subfetch16 */
	{
#ifdef __hybrid_atomic_subfetch32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_subfetch32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_subfetch32 */
	{
#ifdef __hybrid_atomic_subfetch64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_subfetch64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_subfetch64 */
	{
#ifdef __hybrid_atomic_subfetch128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_subfetch128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_subfetch128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_subfetch128
#define __hybrid_atomic_subfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_subfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_subfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_subfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_subfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_subfetch128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_subfetch64)
#define __hybrid_atomic_subfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_subfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_subfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_subfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_subfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_subfetch32)
#define __hybrid_atomic_subfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_subfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_subfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_subfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_subfetch16)
#define __hybrid_atomic_subfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_subfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_subfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_subfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_subfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_subfetch8 */
#endif /* !__hybrid_atomic_subfetch */
#ifndef __hybrid_atomic_andfetch
#ifdef __hybrid_atomic_andfetch8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_andfetch __hybrid_atomic_andfetch
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_andfetch8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_andfetch8 */
#ifdef __hybrid_atomic_andfetch16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_andfetch16 */
#ifdef __hybrid_atomic_andfetch32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_andfetch32 */
#ifdef __hybrid_atomic_andfetch64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_andfetch64 */
#ifdef __hybrid_atomic_andfetch128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_andfetch128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_andfetch)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_andfetch8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_andfetch8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_andfetch8 */
	{
#ifdef __hybrid_atomic_andfetch16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_andfetch16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_andfetch16 */
	{
#ifdef __hybrid_atomic_andfetch32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_andfetch32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_andfetch32 */
	{
#ifdef __hybrid_atomic_andfetch64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_andfetch64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_andfetch64 */
	{
#ifdef __hybrid_atomic_andfetch128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_andfetch128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_andfetch128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_andfetch128
#define __hybrid_atomic_andfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_andfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_andfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_andfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_andfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_andfetch128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_andfetch64)
#define __hybrid_atomic_andfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_andfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_andfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_andfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_andfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_andfetch32)
#define __hybrid_atomic_andfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_andfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_andfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_andfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_andfetch16)
#define __hybrid_atomic_andfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_andfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_andfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_andfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_andfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_andfetch8 */
#endif /* !__hybrid_atomic_andfetch */
#ifndef __hybrid_atomic_xorfetch
#ifdef __hybrid_atomic_xorfetch8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_xorfetch __hybrid_atomic_xorfetch
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_xorfetch8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_xorfetch8 */
#ifdef __hybrid_atomic_xorfetch16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_xorfetch16 */
#ifdef __hybrid_atomic_xorfetch32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_xorfetch32 */
#ifdef __hybrid_atomic_xorfetch64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_xorfetch64 */
#ifdef __hybrid_atomic_xorfetch128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_xorfetch128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_xorfetch)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_xorfetch8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_xorfetch8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_xorfetch8 */
	{
#ifdef __hybrid_atomic_xorfetch16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_xorfetch16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_xorfetch16 */
	{
#ifdef __hybrid_atomic_xorfetch32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_xorfetch32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_xorfetch32 */
	{
#ifdef __hybrid_atomic_xorfetch64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_xorfetch64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_xorfetch64 */
	{
#ifdef __hybrid_atomic_xorfetch128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_xorfetch128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_xorfetch128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_xorfetch128
#define __hybrid_atomic_xorfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_xorfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_xorfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_xorfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_xorfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_xorfetch128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_xorfetch64)
#define __hybrid_atomic_xorfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_xorfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_xorfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_xorfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_xorfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_xorfetch32)
#define __hybrid_atomic_xorfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_xorfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_xorfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_xorfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_xorfetch16)
#define __hybrid_atomic_xorfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_xorfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_xorfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_xorfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_xorfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_xorfetch8 */
#endif /* !__hybrid_atomic_xorfetch */
#ifndef __hybrid_atomic_orfetch
#ifdef __hybrid_atomic_orfetch8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_orfetch __hybrid_atomic_orfetch
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_orfetch8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_orfetch8 */
#ifdef __hybrid_atomic_orfetch16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_orfetch16 */
#ifdef __hybrid_atomic_orfetch32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_orfetch32 */
#ifdef __hybrid_atomic_orfetch64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_orfetch64 */
#ifdef __hybrid_atomic_orfetch128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_orfetch128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_orfetch)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_orfetch8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_orfetch8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_orfetch8 */
	{
#ifdef __hybrid_atomic_orfetch16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_orfetch16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_orfetch16 */
	{
#ifdef __hybrid_atomic_orfetch32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_orfetch32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_orfetch32 */
	{
#ifdef __hybrid_atomic_orfetch64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_orfetch64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_orfetch64 */
	{
#ifdef __hybrid_atomic_orfetch128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_orfetch128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_orfetch128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_orfetch128
#define __hybrid_atomic_orfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_orfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_orfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_orfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_orfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_orfetch128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_orfetch64)
#define __hybrid_atomic_orfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_orfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_orfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_orfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_orfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_orfetch32)
#define __hybrid_atomic_orfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_orfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_orfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_orfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_orfetch16)
#define __hybrid_atomic_orfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_orfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_orfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_orfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_orfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_orfetch8 */
#endif /* !__hybrid_atomic_orfetch */
#ifndef __hybrid_atomic_nandfetch
#ifdef __hybrid_atomic_nandfetch8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_nandfetch __hybrid_atomic_nandfetch
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_nandfetch8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_nandfetch8 */
#ifdef __hybrid_atomic_nandfetch16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_nandfetch16 */
#ifdef __hybrid_atomic_nandfetch32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_nandfetch32 */
#ifdef __hybrid_atomic_nandfetch64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_nandfetch64 */
#ifdef __hybrid_atomic_nandfetch128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_nandfetch128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_nandfetch)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_nandfetch8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_nandfetch8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_nandfetch8 */
	{
#ifdef __hybrid_atomic_nandfetch16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_nandfetch16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_nandfetch16 */
	{
#ifdef __hybrid_atomic_nandfetch32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_nandfetch32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_nandfetch32 */
	{
#ifdef __hybrid_atomic_nandfetch64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_nandfetch64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_nandfetch64 */
	{
#ifdef __hybrid_atomic_nandfetch128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_nandfetch128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_nandfetch128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_nandfetch128
#define __hybrid_atomic_nandfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_nandfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_nandfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_nandfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_nandfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                                              __hybrid_atomic_nandfetch128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_nandfetch64)
#define __hybrid_atomic_nandfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_nandfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_nandfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_nandfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                                              __hybrid_atomic_nandfetch64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_nandfetch32)
#define __hybrid_atomic_nandfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_nandfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_nandfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                                              __hybrid_atomic_nandfetch32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_nandfetch16)
#define __hybrid_atomic_nandfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_nandfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                                              __hybrid_atomic_nandfetch16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_nandfetch(p, val, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_nandfetch8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_nandfetch8 */
#endif /* !__hybrid_atomic_nandfetch */
#ifndef __hybrid_atomic_incfetch
#ifdef __hybrid_atomic_addfetch
#define __hybrid_atomic_incfetch(p, order) __hybrid_atomic_addfetch(p, 1, order)
#elif defined(__hybrid_atomic_incfetch8)
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_incfetch __hybrid_atomic_incfetch
template<class __T> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_incfetch8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_incfetch8 */
#ifdef __hybrid_atomic_incfetch16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_incfetch16 */
#ifdef __hybrid_atomic_incfetch32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_incfetch32 */
#ifdef __hybrid_atomic_incfetch64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_incfetch64 */
#ifdef __hybrid_atomic_incfetch128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_incfetch128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_incfetch)(__T *__p, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_incfetch8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_incfetch8((__UINT8_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_incfetch8 */
	{
#ifdef __hybrid_atomic_incfetch16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_incfetch16((__UINT16_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_incfetch16 */
	{
#ifdef __hybrid_atomic_incfetch32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_incfetch32((__UINT32_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_incfetch32 */
	{
#ifdef __hybrid_atomic_incfetch64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_incfetch64((__UINT64_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_incfetch64 */
	{
#ifdef __hybrid_atomic_incfetch128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_incfetch128((__UINT128_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_incfetch128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_incfetch128
#define __hybrid_atomic_incfetch(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_incfetch8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_incfetch16((__UINT16_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_incfetch32((__UINT32_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_incfetch64((__UINT64_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_incfetch128((__UINT128_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_incfetch64)
#define __hybrid_atomic_incfetch(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_incfetch8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_incfetch16((__UINT16_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_incfetch32((__UINT32_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_incfetch64((__UINT64_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_incfetch32)
#define __hybrid_atomic_incfetch(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_incfetch8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_incfetch16((__UINT16_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_incfetch32((__UINT32_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_incfetch16)
#define __hybrid_atomic_incfetch(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_incfetch8((__UINT8_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_incfetch16((__UINT16_TYPE__ *)(p), order))
#else /* ... */
#define __hybrid_atomic_incfetch(p, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_incfetch8((__UINT8_TYPE__ *)(p), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_incfetch8 */
#endif /* !__hybrid_atomic_incfetch */
#ifndef __hybrid_atomic_decfetch
#ifdef __hybrid_atomic_subfetch
#define __hybrid_atomic_decfetch(p, order) __hybrid_atomic_subfetch(p, 1, order)
#elif defined(__hybrid_atomic_decfetch8)
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_decfetch __hybrid_atomic_decfetch
template<class __T> inline __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_decfetch8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_decfetch8 */
#ifdef __hybrid_atomic_decfetch16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_decfetch16 */
#ifdef __hybrid_atomic_decfetch32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_decfetch32 */
#ifdef __hybrid_atomic_decfetch64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_decfetch64 */
#ifdef __hybrid_atomic_decfetch128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_decfetch128 */
, __T>::__type __NOTHROW_NCX(__hybrid_atomic_decfetch)(__T *__p, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_decfetch8
	__STATIC_IF(sizeof(__T) == 1) { return (__T)__hybrid_atomic_decfetch8((__UINT8_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_decfetch8 */
	{
#ifdef __hybrid_atomic_decfetch16
	__STATIC_IF(sizeof(__T) == 2) { return (__T)__hybrid_atomic_decfetch16((__UINT16_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_decfetch16 */
	{
#ifdef __hybrid_atomic_decfetch32
	__STATIC_IF(sizeof(__T) == 4) { return (__T)__hybrid_atomic_decfetch32((__UINT32_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_decfetch32 */
	{
#ifdef __hybrid_atomic_decfetch64
	__STATIC_IF(sizeof(__T) == 8) { return (__T)__hybrid_atomic_decfetch64((__UINT64_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_decfetch64 */
	{
#ifdef __hybrid_atomic_decfetch128
	__STATIC_IF(sizeof(__T) == 16) { return (__T)__hybrid_atomic_decfetch128((__UINT128_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_decfetch128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_decfetch128
#define __hybrid_atomic_decfetch(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_decfetch8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_decfetch16((__UINT16_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_decfetch32((__UINT32_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 8 ? __hybrid_atomic_decfetch64((__UINT64_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_decfetch128((__UINT128_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_decfetch64)
#define __hybrid_atomic_decfetch(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_decfetch8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_decfetch16((__UINT16_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 4 ? __hybrid_atomic_decfetch32((__UINT32_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_decfetch64((__UINT64_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_decfetch32)
#define __hybrid_atomic_decfetch(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_decfetch8((__UINT8_TYPE__ *)(p), order) : \
	                          sizeof(*(p)) == 2 ? __hybrid_atomic_decfetch16((__UINT16_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_decfetch32((__UINT32_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_decfetch16)
#define __hybrid_atomic_decfetch(p, order) \
	__HYBRID_ATOMIC_RECAST(p, sizeof(*(p)) == 1 ? __hybrid_atomic_decfetch8((__UINT8_TYPE__ *)(p), order) : \
	                                              __hybrid_atomic_decfetch16((__UINT16_TYPE__ *)(p), order))
#else /* ... */
#define __hybrid_atomic_decfetch(p, order) \
	__HYBRID_ATOMIC_RECAST(p, __hybrid_atomic_decfetch8((__UINT8_TYPE__ *)(p), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_decfetch8 */
#endif /* !__hybrid_atomic_decfetch */
#ifndef __hybrid_atomic_add
#ifdef __hybrid_atomic_add8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_add __hybrid_atomic_add
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_add8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_add8 */
#ifdef __hybrid_atomic_add16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_add16 */
#ifdef __hybrid_atomic_add32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_add32 */
#ifdef __hybrid_atomic_add64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_add64 */
#ifdef __hybrid_atomic_add128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_add128 */
, void>::__type __NOTHROW_NCX(__hybrid_atomic_add)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_add8
	__STATIC_IF(sizeof(__T) == 1) { __hybrid_atomic_add8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_add8 */
	{
#ifdef __hybrid_atomic_add16
	__STATIC_IF(sizeof(__T) == 2) { __hybrid_atomic_add16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_add16 */
	{
#ifdef __hybrid_atomic_add32
	__STATIC_IF(sizeof(__T) == 4) { __hybrid_atomic_add32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_add32 */
	{
#ifdef __hybrid_atomic_add64
	__STATIC_IF(sizeof(__T) == 8) { __hybrid_atomic_add64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_add64 */
	{
#ifdef __hybrid_atomic_add128
	__STATIC_IF(sizeof(__T) == 16) { __hybrid_atomic_add128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_add128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_add128
#define __hybrid_atomic_add(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_add8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_add16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_add32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	 sizeof(*(p)) == 8 ? __hybrid_atomic_add64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                     __hybrid_atomic_add128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_add64)
#define __hybrid_atomic_add(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_add8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_add16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_add32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                     __hybrid_atomic_add64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_add32)
#define __hybrid_atomic_add(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_add8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_add16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                     __hybrid_atomic_add32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_add16)
#define __hybrid_atomic_add(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_add8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                     __hybrid_atomic_add16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_add(p, val, order) \
	(__hybrid_atomic_add8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_add8 */
#endif /* !__hybrid_atomic_add */
#ifndef __hybrid_atomic_sub
#ifdef __hybrid_atomic_sub8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_sub __hybrid_atomic_sub
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_sub8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_sub8 */
#ifdef __hybrid_atomic_sub16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_sub16 */
#ifdef __hybrid_atomic_sub32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_sub32 */
#ifdef __hybrid_atomic_sub64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_sub64 */
#ifdef __hybrid_atomic_sub128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_sub128 */
, void>::__type __NOTHROW_NCX(__hybrid_atomic_sub)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_sub8
	__STATIC_IF(sizeof(__T) == 1) { __hybrid_atomic_sub8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_sub8 */
	{
#ifdef __hybrid_atomic_sub16
	__STATIC_IF(sizeof(__T) == 2) { __hybrid_atomic_sub16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_sub16 */
	{
#ifdef __hybrid_atomic_sub32
	__STATIC_IF(sizeof(__T) == 4) { __hybrid_atomic_sub32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_sub32 */
	{
#ifdef __hybrid_atomic_sub64
	__STATIC_IF(sizeof(__T) == 8) { __hybrid_atomic_sub64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_sub64 */
	{
#ifdef __hybrid_atomic_sub128
	__STATIC_IF(sizeof(__T) == 16) { __hybrid_atomic_sub128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_sub128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_sub128
#define __hybrid_atomic_sub(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_sub8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_sub16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_sub32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	 sizeof(*(p)) == 8 ? __hybrid_atomic_sub64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                     __hybrid_atomic_sub128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_sub64)
#define __hybrid_atomic_sub(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_sub8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_sub16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_sub32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                     __hybrid_atomic_sub64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_sub32)
#define __hybrid_atomic_sub(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_sub8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_sub16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                     __hybrid_atomic_sub32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_sub16)
#define __hybrid_atomic_sub(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_sub8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                     __hybrid_atomic_sub16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_sub(p, val, order) \
	(__hybrid_atomic_sub8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_sub8 */
#endif /* !__hybrid_atomic_sub */
#ifndef __hybrid_atomic_and
#ifdef __hybrid_atomic_and8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_and __hybrid_atomic_and
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_and8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_and8 */
#ifdef __hybrid_atomic_and16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_and16 */
#ifdef __hybrid_atomic_and32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_and32 */
#ifdef __hybrid_atomic_and64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_and64 */
#ifdef __hybrid_atomic_and128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_and128 */
, void>::__type __NOTHROW_NCX(__hybrid_atomic_and)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_and8
	__STATIC_IF(sizeof(__T) == 1) { __hybrid_atomic_and8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_and8 */
	{
#ifdef __hybrid_atomic_and16
	__STATIC_IF(sizeof(__T) == 2) { __hybrid_atomic_and16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_and16 */
	{
#ifdef __hybrid_atomic_and32
	__STATIC_IF(sizeof(__T) == 4) { __hybrid_atomic_and32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_and32 */
	{
#ifdef __hybrid_atomic_and64
	__STATIC_IF(sizeof(__T) == 8) { __hybrid_atomic_and64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_and64 */
	{
#ifdef __hybrid_atomic_and128
	__STATIC_IF(sizeof(__T) == 16) { __hybrid_atomic_and128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_and128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_and128
#define __hybrid_atomic_and(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_and8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_and16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_and32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	 sizeof(*(p)) == 8 ? __hybrid_atomic_and64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                     __hybrid_atomic_and128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_and64)
#define __hybrid_atomic_and(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_and8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_and16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_and32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                     __hybrid_atomic_and64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_and32)
#define __hybrid_atomic_and(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_and8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_and16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                     __hybrid_atomic_and32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_and16)
#define __hybrid_atomic_and(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_and8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                     __hybrid_atomic_and16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_and(p, val, order) \
	(__hybrid_atomic_and8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_and8 */
#endif /* !__hybrid_atomic_and */
#ifndef __hybrid_atomic_xor
#ifdef __hybrid_atomic_xor8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_xor __hybrid_atomic_xor
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_xor8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_xor8 */
#ifdef __hybrid_atomic_xor16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_xor16 */
#ifdef __hybrid_atomic_xor32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_xor32 */
#ifdef __hybrid_atomic_xor64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_xor64 */
#ifdef __hybrid_atomic_xor128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_xor128 */
, void>::__type __NOTHROW_NCX(__hybrid_atomic_xor)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_xor8
	__STATIC_IF(sizeof(__T) == 1) { __hybrid_atomic_xor8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_xor8 */
	{
#ifdef __hybrid_atomic_xor16
	__STATIC_IF(sizeof(__T) == 2) { __hybrid_atomic_xor16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_xor16 */
	{
#ifdef __hybrid_atomic_xor32
	__STATIC_IF(sizeof(__T) == 4) { __hybrid_atomic_xor32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_xor32 */
	{
#ifdef __hybrid_atomic_xor64
	__STATIC_IF(sizeof(__T) == 8) { __hybrid_atomic_xor64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_xor64 */
	{
#ifdef __hybrid_atomic_xor128
	__STATIC_IF(sizeof(__T) == 16) { __hybrid_atomic_xor128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_xor128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_xor128
#define __hybrid_atomic_xor(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_xor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_xor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_xor32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	 sizeof(*(p)) == 8 ? __hybrid_atomic_xor64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                     __hybrid_atomic_xor128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_xor64)
#define __hybrid_atomic_xor(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_xor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_xor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_xor32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                     __hybrid_atomic_xor64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_xor32)
#define __hybrid_atomic_xor(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_xor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_xor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                     __hybrid_atomic_xor32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_xor16)
#define __hybrid_atomic_xor(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_xor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                     __hybrid_atomic_xor16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_xor(p, val, order) \
	(__hybrid_atomic_xor8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_xor8 */
#endif /* !__hybrid_atomic_xor */
#ifndef __hybrid_atomic_or
#ifdef __hybrid_atomic_or8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_or __hybrid_atomic_or
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_or8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_or8 */
#ifdef __hybrid_atomic_or16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_or16 */
#ifdef __hybrid_atomic_or32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_or32 */
#ifdef __hybrid_atomic_or64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_or64 */
#ifdef __hybrid_atomic_or128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_or128 */
, void>::__type __NOTHROW_NCX(__hybrid_atomic_or)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_or8
	__STATIC_IF(sizeof(__T) == 1) { __hybrid_atomic_or8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_or8 */
	{
#ifdef __hybrid_atomic_or16
	__STATIC_IF(sizeof(__T) == 2) { __hybrid_atomic_or16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_or16 */
	{
#ifdef __hybrid_atomic_or32
	__STATIC_IF(sizeof(__T) == 4) { __hybrid_atomic_or32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_or32 */
	{
#ifdef __hybrid_atomic_or64
	__STATIC_IF(sizeof(__T) == 8) { __hybrid_atomic_or64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_or64 */
	{
#ifdef __hybrid_atomic_or128
	__STATIC_IF(sizeof(__T) == 16) { __hybrid_atomic_or128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_or128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_or128
#define __hybrid_atomic_or(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_or8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_or16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_or32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	 sizeof(*(p)) == 8 ? __hybrid_atomic_or64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                     __hybrid_atomic_or128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_or64)
#define __hybrid_atomic_or(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_or8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_or16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_or32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                     __hybrid_atomic_or64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_or32)
#define __hybrid_atomic_or(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_or8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_or16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                     __hybrid_atomic_or32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_or16)
#define __hybrid_atomic_or(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_or8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                     __hybrid_atomic_or16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_or(p, val, order) \
	(__hybrid_atomic_or8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_or8 */
#endif /* !__hybrid_atomic_or */
#ifndef __hybrid_atomic_nand
#ifdef __hybrid_atomic_nand8
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_nand __hybrid_atomic_nand
template<class __T, class __Tval> inline __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_nand8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_nand8 */
#ifdef __hybrid_atomic_nand16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_nand16 */
#ifdef __hybrid_atomic_nand32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_nand32 */
#ifdef __hybrid_atomic_nand64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_nand64 */
#ifdef __hybrid_atomic_nand128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_nand128 */
, void>::__type __NOTHROW_NCX(__hybrid_atomic_nand)(__T *__p, __Tval __val, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_nand8
	__STATIC_IF(sizeof(__T) == 1) { __hybrid_atomic_nand8((__UINT8_TYPE__ *)__p, (__UINT8_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_nand8 */
	{
#ifdef __hybrid_atomic_nand16
	__STATIC_IF(sizeof(__T) == 2) { __hybrid_atomic_nand16((__UINT16_TYPE__ *)__p, (__UINT16_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_nand16 */
	{
#ifdef __hybrid_atomic_nand32
	__STATIC_IF(sizeof(__T) == 4) { __hybrid_atomic_nand32((__UINT32_TYPE__ *)__p, (__UINT32_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_nand32 */
	{
#ifdef __hybrid_atomic_nand64
	__STATIC_IF(sizeof(__T) == 8) { __hybrid_atomic_nand64((__UINT64_TYPE__ *)__p, (__UINT64_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_nand64 */
	{
#ifdef __hybrid_atomic_nand128
	__STATIC_IF(sizeof(__T) == 16) { __hybrid_atomic_nand128((__UINT128_TYPE__ *)__p, (__UINT128_TYPE__)__val, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_nand128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_nand128
#define __hybrid_atomic_nand(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_nand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_nand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_nand32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	 sizeof(*(p)) == 8 ? __hybrid_atomic_nand64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order) : \
	                     __hybrid_atomic_nand128((__UINT128_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT128_TYPE__)(val), order))
#elif defined(__hybrid_atomic_nand64)
#define __hybrid_atomic_nand(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_nand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_nand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_nand32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order) : \
	                     __hybrid_atomic_nand64((__UINT64_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT64_TYPE__)(val), order))
#elif defined(__hybrid_atomic_nand32)
#define __hybrid_atomic_nand(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_nand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_nand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order) : \
	                     __hybrid_atomic_nand32((__UINT32_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT32_TYPE__)(val), order))
#elif defined(__hybrid_atomic_nand16)
#define __hybrid_atomic_nand(p, val, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_nand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order) : \
	                     __hybrid_atomic_nand16((__UINT16_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT16_TYPE__)(val), order))
#else /* ... */
#define __hybrid_atomic_nand(p, val, order) \
	(__hybrid_atomic_nand8((__UINT8_TYPE__ *)(p), __HYBRID_ATOMIC_DOWNCAST(__UINT8_TYPE__)(val), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_nand8 */
#endif /* !__hybrid_atomic_nand */
#ifndef __hybrid_atomic_inc
#ifdef __hybrid_atomic_add
#define __hybrid_atomic_inc(p, order) __hybrid_atomic_add(p, 1, order)
#elif defined(__hybrid_atomic_inc8)
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_inc __hybrid_atomic_inc
template<class __T> inline __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_inc8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_inc8 */
#ifdef __hybrid_atomic_inc16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_inc16 */
#ifdef __hybrid_atomic_inc32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_inc32 */
#ifdef __hybrid_atomic_inc64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_inc64 */
#ifdef __hybrid_atomic_inc128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_inc128 */
, void>::__type __NOTHROW_NCX(__hybrid_atomic_inc)(__T *__p, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_inc8
	__STATIC_IF(sizeof(__T) == 1) { __hybrid_atomic_inc8((__UINT8_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_inc8 */
	{
#ifdef __hybrid_atomic_inc16
	__STATIC_IF(sizeof(__T) == 2) { __hybrid_atomic_inc16((__UINT16_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_inc16 */
	{
#ifdef __hybrid_atomic_inc32
	__STATIC_IF(sizeof(__T) == 4) { __hybrid_atomic_inc32((__UINT32_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_inc32 */
	{
#ifdef __hybrid_atomic_inc64
	__STATIC_IF(sizeof(__T) == 8) { __hybrid_atomic_inc64((__UINT64_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_inc64 */
	{
#ifdef __hybrid_atomic_inc128
	__STATIC_IF(sizeof(__T) == 16) { __hybrid_atomic_inc128((__UINT128_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_inc128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_inc128
#define __hybrid_atomic_inc(p, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_inc8((__UINT8_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_inc16((__UINT16_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_inc32((__UINT32_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 8 ? __hybrid_atomic_inc64((__UINT64_TYPE__ *)(p), order) : \
	                     __hybrid_atomic_inc128((__UINT128_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_inc64)
#define __hybrid_atomic_inc(p, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_inc8((__UINT8_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_inc16((__UINT16_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_inc32((__UINT32_TYPE__ *)(p), order) : \
	                     __hybrid_atomic_inc64((__UINT64_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_inc32)
#define __hybrid_atomic_inc(p, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_inc8((__UINT8_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_inc16((__UINT16_TYPE__ *)(p), order) : \
	                     __hybrid_atomic_inc32((__UINT32_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_inc16)
#define __hybrid_atomic_inc(p, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_inc8((__UINT8_TYPE__ *)(p), order) : \
	                     __hybrid_atomic_inc16((__UINT16_TYPE__ *)(p), order))
#else /* ... */
#define __hybrid_atomic_inc(p, order) \
	(__hybrid_atomic_inc8((__UINT8_TYPE__ *)(p), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_inc8 */
#endif /* !__hybrid_atomic_inc */
#ifndef __hybrid_atomic_dec
#ifdef __hybrid_atomic_sub
#define __hybrid_atomic_dec(p, order) __hybrid_atomic_sub(p, 1, order)
#elif defined(__hybrid_atomic_dec8)
#ifdef __cplusplus
extern "C++" {
#ifndef __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
#define __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED
__NAMESPACE_INT_BEGIN
template<bool __V, class __T> struct __hybrid_atomic_enable_if { typedef __T __type; };
template<class __T> struct __hybrid_atomic_enable_if<false, __T> {};
__NAMESPACE_INT_END
#endif /* __HYBRID_PRIVATE_ATOMIC_ENABLE_IF_DEFINED */
#define __hybrid_atomic_dec __hybrid_atomic_dec
template<class __T> inline __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) typename __NAMESPACE_INT_SYM __hybrid_atomic_enable_if<false
#ifdef __hybrid_atomic_dec8
	|| sizeof(__T) == 1
#endif /* __hybrid_atomic_dec8 */
#ifdef __hybrid_atomic_dec16
	|| sizeof(__T) == 2
#endif /* __hybrid_atomic_dec16 */
#ifdef __hybrid_atomic_dec32
	|| sizeof(__T) == 4
#endif /* __hybrid_atomic_dec32 */
#ifdef __hybrid_atomic_dec64
	|| sizeof(__T) == 8
#endif /* __hybrid_atomic_dec64 */
#ifdef __hybrid_atomic_dec128
	|| sizeof(__T) == 16
#endif /* __hybrid_atomic_dec128 */
, void>::__type __NOTHROW_NCX(__hybrid_atomic_dec)(__T *__p, int __order) {
	(void)__order;
#ifdef __hybrid_atomic_dec8
	__STATIC_IF(sizeof(__T) == 1) { __hybrid_atomic_dec8((__UINT8_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 1)
#endif /* __hybrid_atomic_dec8 */
	{
#ifdef __hybrid_atomic_dec16
	__STATIC_IF(sizeof(__T) == 2) { __hybrid_atomic_dec16((__UINT16_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 2)
#endif /* __hybrid_atomic_dec16 */
	{
#ifdef __hybrid_atomic_dec32
	__STATIC_IF(sizeof(__T) == 4) { __hybrid_atomic_dec32((__UINT32_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 4)
#endif /* __hybrid_atomic_dec32 */
	{
#ifdef __hybrid_atomic_dec64
	__STATIC_IF(sizeof(__T) == 8) { __hybrid_atomic_dec64((__UINT64_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 8)
#endif /* __hybrid_atomic_dec64 */
	{
#ifdef __hybrid_atomic_dec128
	__STATIC_IF(sizeof(__T) == 16) { __hybrid_atomic_dec128((__UINT128_TYPE__ *)__p, __order); }
	__STATIC_ELSE(sizeof(__T) == 16)
#endif /* __hybrid_atomic_dec128 */
	{ __builtin_unreachable(); }}}}}
}
} /* extern "C++" */
#else /* __cplusplus */
#ifdef __hybrid_atomic_dec128
#define __hybrid_atomic_dec(p, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_dec8((__UINT8_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_dec16((__UINT16_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_dec32((__UINT32_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 8 ? __hybrid_atomic_dec64((__UINT64_TYPE__ *)(p), order) : \
	                     __hybrid_atomic_dec128((__UINT128_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_dec64)
#define __hybrid_atomic_dec(p, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_dec8((__UINT8_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_dec16((__UINT16_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 4 ? __hybrid_atomic_dec32((__UINT32_TYPE__ *)(p), order) : \
	                     __hybrid_atomic_dec64((__UINT64_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_dec32)
#define __hybrid_atomic_dec(p, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_dec8((__UINT8_TYPE__ *)(p), order) : \
	 sizeof(*(p)) == 2 ? __hybrid_atomic_dec16((__UINT16_TYPE__ *)(p), order) : \
	                     __hybrid_atomic_dec32((__UINT32_TYPE__ *)(p), order))
#elif defined(__hybrid_atomic_dec16)
#define __hybrid_atomic_dec(p, order) \
	(sizeof(*(p)) == 1 ? __hybrid_atomic_dec8((__UINT8_TYPE__ *)(p), order) : \
	                     __hybrid_atomic_dec16((__UINT16_TYPE__ *)(p), order))
#else /* ... */
#define __hybrid_atomic_dec(p, order) \
	(__hybrid_atomic_dec8((__UINT8_TYPE__ *)(p), order))
#endif /* !... */
#endif /* !__cplusplus */
#endif /* __hybrid_atomic_dec8 */
#endif /* !__hybrid_atomic_dec */
/*[[[end]]]*/
/* clang-format on */

#endif /* !__GUARD_HYBRID___ATOMIC_COMPLETE_H */
