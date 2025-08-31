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
%(c_prefix){
/* (>) Standard: ISO C23 (ISO/IEC 9899:2024) */
/* (#) Portability: GNU C Library (/stdlib/stdbit.h) */
/* (#) Portability: GNU Hurd      (/usr/include/stdbit.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.stdbit")]

%{
}%[insert:prefix(
#include <hybrid/__bit.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <hybrid/byteorder.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#define __STDC_VERSION_STDBIT_H__ 202311L
#define __STDC_ENDIAN_LITTLE__    __ORDER_LITTLE_ENDIAN__
#define __STDC_ENDIAN_BIG__       __ORDER_BIG_ENDIAN__
#define __STDC_ENDIAN_NATIVE__    __BYTE_ORDER__

}
%#ifdef __CC__
%{
__SYSDECL_BEGIN

}


/*[[[deemon
import * from deemon;
function T_printFunction(name: string, T: string, printExtra: Callable | none,
                         expr: string, suffix: string,
                         needHybridBit: bool = true,
                         needTypeCore: bool = false,
                         returnType: string = "unsigned int") {
	print('[[extern_inline, nothrow, const, wunused'),;
	if (needHybridBit || needTypeCore) {
		print(', impl_include('),;
		if (needHybridBit)
			print('"<hybrid/__bit.h>"'),;
		if (needTypeCore) {
			if (needHybridBit)
				print(', '),;
			print('"<hybrid/typecore.h>"'),;
		}
		print(')'),;
	}
	print(']]');
	printExtra();
	print(returnType.format({ "T": T }), ' ', name, '(', T, ' x) {');
	print('	return ', expr
		.format({ "x": "x", "suffix": suffix, "sizeof_T": f"sizeof({T})", "T": T })
		.replace("sizeof(unsigned char)", "__SIZEOF_CHAR__")
		.replace("sizeof(unsigned short)", "__SIZEOF_SHORT__")
		.replace("sizeof(unsigned int)", "__SIZEOF_INT__")
		.replace("sizeof(unsigned long)", "__SIZEOF_LONG__")
		.replace("sizeof(__ULONGLONG)", "__SIZEOF_LONG_LONG__")
		, ';');
	print('}');
}

global LL_CODE_PRINTERS: {Callable...} = [];

@@List of (doc: string, name: string, expr: string, returnType: string)
global FUNCTIONS: {(string, string, string, string)...} = [];

function printFunction(doc: string, name: string, expr: string,
                       needHybridBit: bool = true,
                       needTypeCore: bool = false,
                       charAndShortOnly: bool = false,
                       returnType: string = "unsigned int") {
	FUNCTIONS.append((doc, name, expr, returnType));
	print(f"@@>> {name}(3) (type-generic)");
	print(f"@@>> {name}_uc(3), {name}_us(3), {name}_ui(3)");
	print(f"@@>> {name}_ul(3), {name}_ull(3)");
	print(f"@@{doc}");
	T_printFunction(f"{name}_uc", "unsigned char", none, expr, "_uc", needHybridBit, needTypeCore, returnType);
	print(f'[[doc_alias("{name}_uc")]]');
	T_printFunction(f"{name}_us", "unsigned short", none, expr, "_us", needHybridBit, needTypeCore, returnType);
	if (!charAndShortOnly) {
		print(f'[[doc_alias("{name}_uc")]]');
		T_printFunction(f"{name}_ui", "unsigned int", () -> {
			print(f'[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_{name}_ul")]]');
			print(f'[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_{name}_ull")]]');
			print(f'[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("{name}_ul")]]');
			print(f'[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("{name}_ull")]]');
		}, expr, "_ui", needHybridBit, needTypeCore, returnType);
		print(f'[[doc_alias("{name}_uc")]]');
		T_printFunction(f"{name}_ul", "unsigned long", () -> {
			print(f'[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_{name}_ull")]]');
			print(f'[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("{name}_ui")]]');
			print(f'[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("{name}_ull")]]');
		}, expr, "_ul", needHybridBit, needTypeCore, returnType);
		LL_CODE_PRINTERS.append(() -> {
			print(f'[[doc_alias("{name}_uc")]]');
			T_printFunction(f"{name}_ull", "__ULONGLONG", () -> {
				print(f'[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("{name}_ui")]]');
				print(f'[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("{name}_ul")]]');
			}, expr, "_ull", needHybridBit, needTypeCore, returnType);
		});
		print;
		print;
		print;
	}
}

printFunction("Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0')",
	"stdc_leading_zeros", "{x} == 0 ? ({sizeof_T} * __CHAR_BIT__) : __hybrid_clz({x})",
	needTypeCore: true);

printFunction("Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1')",
	"stdc_leading_ones", "{x} == ({T})-1 ? ({sizeof_T} * __CHAR_BIT__) : __hybrid_clz(({T})~{x})",
//	"stdc_leading_ones", "stdc_leading_zeros{suffix}(({T})~{x})",
	needHybridBit: false);

printFunction("Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0')",
	"stdc_trailing_zeros", "{x} == 0 ? ({sizeof_T} * __CHAR_BIT__) : __hybrid_ctz(x)",
	needTypeCore: true);

printFunction("Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1')",
	"stdc_trailing_ones", "{x} == ({T})-1 ? ({sizeof_T} * __CHAR_BIT__) : __hybrid_ctz(({T})~x)",
//	"stdc_trailing_ones", "stdc_trailing_zeros{suffix}(({T})~{x})",
	needHybridBit: false);

printFunction("Find first set (1-based, returning `0' when `x == 0')",
	"stdc_first_leading_one", "__hybrid_ffs({x})",
	charAndShortOnly: true);
print('[[doc_alias("stdc_first_leading_one_uc")]]');
print('unsigned int stdc_first_leading_one_ui(unsigned int i) = ffs;');
print('[[doc_alias("stdc_first_leading_one_uc")]]');
print('unsigned int stdc_first_leading_one_ul(unsigned long i) = ffsl;');
LL_CODE_PRINTERS.append(() -> {
	print('[[doc_alias("stdc_first_leading_one_uc")]]');
	print('unsigned int stdc_first_leading_one_ull(__ULONGLONG i) = ffsll;');
});
print;
print;
print;

printFunction("Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0')",
	"stdc_first_leading_zero", "__hybrid_ffs(({T})~{x})",
	needHybridBit: false);

printFunction("Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0')",
	"stdc_first_trailing_zero", "{x} == 0 ? ({sizeof_T} * __CHAR_BIT__) : __hybrid_ctz({x})",
	needTypeCore: true);

printFunction("Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1')",
	"stdc_first_trailing_one", "{x} == ({T})-1 ? ({sizeof_T} * __CHAR_BIT__) : __hybrid_ctz(({T})~{x})",
//	"stdc_first_trailing_one", "stdc_first_trailing_zero{suffix}(({T})~{x})",
	needHybridBit: false);

printFunction("Popcount",
	"stdc_count_ones",
	"__hybrid_popcount({x})", charAndShortOnly: true);

print('[[doc_alias("stdc_count_ones_uc")]]');
print('unsigned int stdc_count_ones_ui(unsigned int i) = popcount;');
print('[[doc_alias("stdc_count_ones_uc")]]');
print('unsigned int stdc_count_ones_ul(unsigned long i) = popcountl;');
LL_CODE_PRINTERS.append(() -> {
	print('[[doc_alias("stdc_count_ones_uc")]]');
	print('unsigned int stdc_count_ones_ull(__ULONGLONG i) = popcountll;');
});
print;
print;
print;

printFunction("Popcount (zeros)",
	"stdc_count_zeros", "__hybrid_popcount(({T})~{x})");

printFunction("Is power of 2 (and not zero)",
	"stdc_has_single_bit", "({T})({x} ^ ({x} - 1)) > ({T})({x} - 1)",
	needHybridBit: false, returnType: "bool");

printFunction("Number of bits needed to represent `x'",
	"stdc_bit_width", "{x} == 0 ? 0 : ({sizeof_T} * __CHAR_BIT__) - __hybrid_clz({x})",
	needTypeCore: true);

printFunction("Mask for the most significant bit set in `x', or `0' when `x == 0'",
	"stdc_bit_floor", "{x} == 0 ? 0 : (({T})1 << ((({sizeof_T} * __CHAR_BIT__) - 1) - __hybrid_clz({x})))",
	needTypeCore: true, returnType: "{T}");

printFunction("Returns the next power-of-2 that is `>= x'",
	"stdc_bit_ceil", "{x} <= 1 ? 1 : (({T})1 << (({sizeof_T} * __CHAR_BIT__) - __hybrid_clz(({T})({x} - 1))))",
	needTypeCore: true, returnType: "{T}");




print("%");
print("%");
print("%#ifdef __COMPILER_HAVE_LONGLONG");
for (local printer: LL_CODE_PRINTERS)
	printer();
print("%#endif /" "* __COMPILER_HAVE_LONGLONG *" "/");

print("%");
print("%");
print("%");
print("%/" "* Type-generic implementations *" "/");
print("%");
print("%{");
print("#ifndef __PRIVATE_STDC_BIT_RECAST");
print("#ifdef __COMPILER_HAVE_TYPEOF");
print("#define __PRIVATE_STDC_BIT_RECAST(x, v) ((__typeof__(x))(v))");
print("#elif defined(__COMPILER_HAVE_C11_GENERIC) && defined(__COMPILER_HAVE_LONGLONG)");
print("#define __PRIVATE_STDC_BIT_RECAST(x, v) _Generic((x)"),;
for (local T: { "unsigned char", "unsigned short", "unsigned int", "unsigned long", "__ULONGLONG" })
	print(", ", T, ": (", T, ")(v)"),;
print("default: v)");
print("#elif defined(__COMPILER_HAVE_C11_GENERIC)");
print("#define __PRIVATE_STDC_BIT_RECAST(x, v) _Generic((x)"),;
for (local T: { "unsigned char", "unsigned short", "unsigned int", "unsigned long" })
	print(", ", T, ": (", T, ")(v)"),;
print(", default: v)");
print("#else /" "* ... *" "/");
print("#define __PRIVATE_STDC_BIT_RECAST(x, v) v");
print("#endif /" "* !... *" "/");
print("#endif /" "* __PRIVATE_STDC_BIT_RECAST *" "/");
for (local doc, name, expr, returnType: FUNCTIONS) {
	print;
	print("/" "* >> ", name, "(3) (type-generic)");
	print(" * >> ", name, "_uc(3), ", name, "_us(3), ", name, "_ui(3)");
	print(" * >> ", name, "_ul(3), ", name, "_ull(3)");
	print(" * ", doc, " *" "/");
	print("#if __has_builtin(__builtin_", name, ")");
	print("#define ", name, "(x) __builtin_", name, "(x)");
	local recastResultPre = "";
	local recastResultPost = "";
	if (returnType == "{T}") {
		recastResultPre = "__PRIVATE_STDC_BIT_RECAST(x, ";
		recastResultPost = ")";
	}
	if ("{suffix}" !in expr && "{T}" !in expr && "?" !in expr && expr.count("{x}") <= 1) {
		print("#elif !defined(__OPTIMIZE_SIZE__)");
		print("#define ", name, "(x) ", expr.format({ "x": "(x)", "sizeof_T": f"sizeof(x)" }).replace("((x))", "(x)"));
	}
	print("#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)");
	print("#define ", name, "(x) ", recastResultPre, "\\");
	print("	__builtin_choose_expr(sizeof(x) <= sizeof(char),  ", name, "_uc((unsigned char)(x)),  \\");
	print("	__builtin_choose_expr(sizeof(x) <= sizeof(short), ", name, "_us((unsigned short)(x)), \\");
	print("	__builtin_choose_expr(sizeof(x) <= sizeof(int),   ", name, "_ui((unsigned int)(x)),   \\");
	print("	__builtin_choose_expr(sizeof(x) <= sizeof(long),  ", name, "_ul((unsigned long)(x)),  \\");
	print("	                                                  ", name, "_ull((__ULONGLONG)(x))))))", recastResultPost);
	print("#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__");
	print("#define ", name, "(x) ", recastResultPre, "\\");
	print("	(sizeof(x) <= sizeof(char)  ? ", name, "_uc((unsigned char)(x))  : \\");
	print("	 sizeof(x) <= sizeof(short) ? ", name, "_us((unsigned short)(x)) : \\");
	print("	 sizeof(x) <= sizeof(int)   ? ", name, "_ui((unsigned int)(x))   : \\");
	print("	 sizeof(x) <= sizeof(long)  ? ", name, "_ul((unsigned long)(x))  : \\");
	print("	                            : ", name, "_ull((__ULONGLONG)(x)))", recastResultPost);
	print("#elif !defined(__NO_builtin_choose_expr)");
	print("#define ", name, "(x) ", recastResultPre, "\\");
	print("	__builtin_choose_expr(sizeof(x) <= sizeof(char),  ", name, "_uc((unsigned char)(x)),  \\");
	print("	__builtin_choose_expr(sizeof(x) <= sizeof(short), ", name, "_us((unsigned short)(x)), \\");
	print("	__builtin_choose_expr(sizeof(x) <= sizeof(int),   ", name, "_ui((unsigned int)(x)),   \\");
	print("	                                                  ", name, "_ul((unsigned long)(x)))))", recastResultPost);
	print("#else /" "* ... *" "/");
	print("#define ", name, "(x) ", recastResultPre, "\\");
	print("	(sizeof(x) <= sizeof(char)  ? ", name, "_uc((unsigned char)(x))  : \\");
	print("	 sizeof(x) <= sizeof(short) ? ", name, "_us((unsigned short)(x)) : \\");
	print("	 sizeof(x) <= sizeof(int)   ? ", name, "_ui((unsigned int)(x))   : \\");
	print("	                            : ", name, "_ul((unsigned long)(x)))", recastResultPost);
	print("#endif /" "* !... *" "/");
	print("");
}
print("}");

]]]*/
@@>> stdc_leading_zeros(3) (type-generic)
@@>> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
@@>> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
@@Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0')
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned int stdc_leading_zeros_uc(unsigned char x) {
	return x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_clz(x);
}
[[doc_alias("stdc_leading_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned int stdc_leading_zeros_us(unsigned short x) {
	return x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_clz(x);
}
[[doc_alias("stdc_leading_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_leading_zeros_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_leading_zeros_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_leading_zeros_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_leading_zeros_ull")]]
unsigned int stdc_leading_zeros_ui(unsigned int x) {
	return x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz(x);
}
[[doc_alias("stdc_leading_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_leading_zeros_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_leading_zeros_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_leading_zeros_ull")]]
unsigned int stdc_leading_zeros_ul(unsigned long x) {
	return x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz(x);
}



@@>> stdc_leading_ones(3) (type-generic)
@@>> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
@@>> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
@@Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1')
[[extern_inline, nothrow, const, wunused]]
unsigned int stdc_leading_ones_uc(unsigned char x) {
	return x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_clz((unsigned char)~x);
}
[[doc_alias("stdc_leading_ones_uc")]]
[[extern_inline, nothrow, const, wunused]]
unsigned int stdc_leading_ones_us(unsigned short x) {
	return x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_clz((unsigned short)~x);
}
[[doc_alias("stdc_leading_ones_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_leading_ones_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_leading_ones_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_leading_ones_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_leading_ones_ull")]]
unsigned int stdc_leading_ones_ui(unsigned int x) {
	return x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz((unsigned int)~x);
}
[[doc_alias("stdc_leading_ones_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_leading_ones_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_leading_ones_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_leading_ones_ull")]]
unsigned int stdc_leading_ones_ul(unsigned long x) {
	return x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz((unsigned long)~x);
}



@@>> stdc_trailing_zeros(3) (type-generic)
@@>> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
@@>> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
@@Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0')
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned int stdc_trailing_zeros_uc(unsigned char x) {
	return x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
[[doc_alias("stdc_trailing_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned int stdc_trailing_zeros_us(unsigned short x) {
	return x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
[[doc_alias("stdc_trailing_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_trailing_zeros_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_trailing_zeros_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_trailing_zeros_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_trailing_zeros_ull")]]
unsigned int stdc_trailing_zeros_ui(unsigned int x) {
	return x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
[[doc_alias("stdc_trailing_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_trailing_zeros_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_trailing_zeros_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_trailing_zeros_ull")]]
unsigned int stdc_trailing_zeros_ul(unsigned long x) {
	return x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(x);
}



@@>> stdc_trailing_ones(3) (type-generic)
@@>> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
@@>> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
@@Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1')
[[extern_inline, nothrow, const, wunused]]
unsigned int stdc_trailing_ones_uc(unsigned char x) {
	return x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz((unsigned char)~x);
}
[[doc_alias("stdc_trailing_ones_uc")]]
[[extern_inline, nothrow, const, wunused]]
unsigned int stdc_trailing_ones_us(unsigned short x) {
	return x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned short)~x);
}
[[doc_alias("stdc_trailing_ones_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_trailing_ones_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_trailing_ones_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_trailing_ones_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_trailing_ones_ull")]]
unsigned int stdc_trailing_ones_ui(unsigned int x) {
	return x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~x);
}
[[doc_alias("stdc_trailing_ones_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_trailing_ones_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_trailing_ones_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_trailing_ones_ull")]]
unsigned int stdc_trailing_ones_ul(unsigned long x) {
	return x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~x);
}



@@>> stdc_first_leading_one(3) (type-generic)
@@>> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
@@>> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
@@Find first set (1-based, returning `0' when `x == 0')
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>")]]
unsigned int stdc_first_leading_one_uc(unsigned char x) {
	return __hybrid_ffs(x);
}
[[doc_alias("stdc_first_leading_one_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>")]]
unsigned int stdc_first_leading_one_us(unsigned short x) {
	return __hybrid_ffs(x);
}
[[doc_alias("stdc_first_leading_one_uc")]]
unsigned int stdc_first_leading_one_ui(unsigned int i) = ffs;
[[doc_alias("stdc_first_leading_one_uc")]]
unsigned int stdc_first_leading_one_ul(unsigned long i) = ffsl;



@@>> stdc_first_leading_zero(3) (type-generic)
@@>> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
@@>> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
@@Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0')
[[extern_inline, nothrow, const, wunused]]
unsigned int stdc_first_leading_zero_uc(unsigned char x) {
	return __hybrid_ffs((unsigned char)~x);
}
[[doc_alias("stdc_first_leading_zero_uc")]]
[[extern_inline, nothrow, const, wunused]]
unsigned int stdc_first_leading_zero_us(unsigned short x) {
	return __hybrid_ffs((unsigned short)~x);
}
[[doc_alias("stdc_first_leading_zero_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_first_leading_zero_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_first_leading_zero_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_first_leading_zero_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_first_leading_zero_ull")]]
unsigned int stdc_first_leading_zero_ui(unsigned int x) {
	return __hybrid_ffs((unsigned int)~x);
}
[[doc_alias("stdc_first_leading_zero_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_first_leading_zero_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_first_leading_zero_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_first_leading_zero_ull")]]
unsigned int stdc_first_leading_zero_ul(unsigned long x) {
	return __hybrid_ffs((unsigned long)~x);
}



@@>> stdc_first_trailing_zero(3) (type-generic)
@@>> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
@@>> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
@@Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0')
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned int stdc_first_trailing_zero_uc(unsigned char x) {
	return x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
[[doc_alias("stdc_first_trailing_zero_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned int stdc_first_trailing_zero_us(unsigned short x) {
	return x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
[[doc_alias("stdc_first_trailing_zero_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_first_trailing_zero_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_first_trailing_zero_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_first_trailing_zero_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_first_trailing_zero_ull")]]
unsigned int stdc_first_trailing_zero_ui(unsigned int x) {
	return x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
[[doc_alias("stdc_first_trailing_zero_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_first_trailing_zero_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_first_trailing_zero_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_first_trailing_zero_ull")]]
unsigned int stdc_first_trailing_zero_ul(unsigned long x) {
	return x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(x);
}



@@>> stdc_first_trailing_one(3) (type-generic)
@@>> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
@@>> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
@@Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1')
[[extern_inline, nothrow, const, wunused]]
unsigned int stdc_first_trailing_one_uc(unsigned char x) {
	return x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz((unsigned char)~x);
}
[[doc_alias("stdc_first_trailing_one_uc")]]
[[extern_inline, nothrow, const, wunused]]
unsigned int stdc_first_trailing_one_us(unsigned short x) {
	return x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned short)~x);
}
[[doc_alias("stdc_first_trailing_one_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_first_trailing_one_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_first_trailing_one_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_first_trailing_one_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_first_trailing_one_ull")]]
unsigned int stdc_first_trailing_one_ui(unsigned int x) {
	return x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~x);
}
[[doc_alias("stdc_first_trailing_one_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_first_trailing_one_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_first_trailing_one_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_first_trailing_one_ull")]]
unsigned int stdc_first_trailing_one_ul(unsigned long x) {
	return x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~x);
}



@@>> stdc_count_ones(3) (type-generic)
@@>> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
@@>> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
@@Popcount
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>")]]
unsigned int stdc_count_ones_uc(unsigned char x) {
	return __hybrid_popcount(x);
}
[[doc_alias("stdc_count_ones_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>")]]
unsigned int stdc_count_ones_us(unsigned short x) {
	return __hybrid_popcount(x);
}
[[doc_alias("stdc_count_ones_uc")]]
unsigned int stdc_count_ones_ui(unsigned int i) = popcount;
[[doc_alias("stdc_count_ones_uc")]]
unsigned int stdc_count_ones_ul(unsigned long i) = popcountl;



@@>> stdc_count_zeros(3) (type-generic)
@@>> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
@@>> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
@@Popcount (zeros)
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>")]]
unsigned int stdc_count_zeros_uc(unsigned char x) {
	return __hybrid_popcount((unsigned char)~x);
}
[[doc_alias("stdc_count_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>")]]
unsigned int stdc_count_zeros_us(unsigned short x) {
	return __hybrid_popcount((unsigned short)~x);
}
[[doc_alias("stdc_count_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_count_zeros_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_count_zeros_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_count_zeros_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_count_zeros_ull")]]
unsigned int stdc_count_zeros_ui(unsigned int x) {
	return __hybrid_popcount((unsigned int)~x);
}
[[doc_alias("stdc_count_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_count_zeros_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_count_zeros_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_count_zeros_ull")]]
unsigned int stdc_count_zeros_ul(unsigned long x) {
	return __hybrid_popcount((unsigned long)~x);
}



@@>> stdc_has_single_bit(3) (type-generic)
@@>> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
@@>> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
@@Is power of 2 (and not zero)
[[extern_inline, nothrow, const, wunused]]
bool stdc_has_single_bit_uc(unsigned char x) {
	return (unsigned char)(x ^ (x - 1)) > (unsigned char)(x - 1);
}
[[doc_alias("stdc_has_single_bit_uc")]]
[[extern_inline, nothrow, const, wunused]]
bool stdc_has_single_bit_us(unsigned short x) {
	return (unsigned short)(x ^ (x - 1)) > (unsigned short)(x - 1);
}
[[doc_alias("stdc_has_single_bit_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_has_single_bit_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_has_single_bit_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_has_single_bit_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_has_single_bit_ull")]]
bool stdc_has_single_bit_ui(unsigned int x) {
	return (unsigned int)(x ^ (x - 1)) > (unsigned int)(x - 1);
}
[[doc_alias("stdc_has_single_bit_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_has_single_bit_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_has_single_bit_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_has_single_bit_ull")]]
bool stdc_has_single_bit_ul(unsigned long x) {
	return (unsigned long)(x ^ (x - 1)) > (unsigned long)(x - 1);
}



@@>> stdc_bit_width(3) (type-generic)
@@>> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
@@>> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
@@Number of bits needed to represent `x'
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned int stdc_bit_width_uc(unsigned char x) {
	return x == 0 ? 0 : (__SIZEOF_CHAR__ * __CHAR_BIT__) - __hybrid_clz(x);
}
[[doc_alias("stdc_bit_width_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned int stdc_bit_width_us(unsigned short x) {
	return x == 0 ? 0 : (__SIZEOF_SHORT__ * __CHAR_BIT__) - __hybrid_clz(x);
}
[[doc_alias("stdc_bit_width_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_bit_width_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_bit_width_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_bit_width_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_bit_width_ull")]]
unsigned int stdc_bit_width_ui(unsigned int x) {
	return x == 0 ? 0 : (__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz(x);
}
[[doc_alias("stdc_bit_width_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_bit_width_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_bit_width_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_bit_width_ull")]]
unsigned int stdc_bit_width_ul(unsigned long x) {
	return x == 0 ? 0 : (__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz(x);
}



@@>> stdc_bit_floor(3) (type-generic)
@@>> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
@@>> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
@@Mask for the most significant bit set in `x', or `0' when `x == 0'
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned char stdc_bit_floor_uc(unsigned char x) {
	return x == 0 ? 0 : ((unsigned char)1 << (((__SIZEOF_CHAR__ * __CHAR_BIT__) - 1) - __hybrid_clz(x)));
}
[[doc_alias("stdc_bit_floor_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned short stdc_bit_floor_us(unsigned short x) {
	return x == 0 ? 0 : ((unsigned short)1 << (((__SIZEOF_SHORT__ * __CHAR_BIT__) - 1) - __hybrid_clz(x)));
}
[[doc_alias("stdc_bit_floor_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_bit_floor_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_bit_floor_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_bit_floor_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_bit_floor_ull")]]
unsigned int stdc_bit_floor_ui(unsigned int x) {
	return x == 0 ? 0 : ((unsigned int)1 << (((__SIZEOF_INT__ * __CHAR_BIT__) - 1) - __hybrid_clz(x)));
}
[[doc_alias("stdc_bit_floor_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_bit_floor_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_bit_floor_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_bit_floor_ull")]]
unsigned long stdc_bit_floor_ul(unsigned long x) {
	return x == 0 ? 0 : ((unsigned long)1 << (((__SIZEOF_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(x)));
}



@@>> stdc_bit_ceil(3) (type-generic)
@@>> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
@@>> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
@@Returns the next power-of-2 that is `>= x'
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned char stdc_bit_ceil_uc(unsigned char x) {
	return x <= 1 ? 1 : ((unsigned char)1 << ((__SIZEOF_CHAR__ * __CHAR_BIT__) - __hybrid_clz((unsigned char)(x - 1))));
}
[[doc_alias("stdc_bit_ceil_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
unsigned short stdc_bit_ceil_us(unsigned short x) {
	return x <= 1 ? 1 : ((unsigned short)1 << ((__SIZEOF_SHORT__ * __CHAR_BIT__) - __hybrid_clz((unsigned short)(x - 1))));
}
[[doc_alias("stdc_bit_ceil_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      crt_intern_kos_alias("libc_stdc_bit_ceil_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_bit_ceil_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("stdc_bit_ceil_ul")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("stdc_bit_ceil_ull")]]
unsigned int stdc_bit_ceil_ui(unsigned int x) {
	return x <= 1 ? 1 : ((unsigned int)1 << ((__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz((unsigned int)(x - 1))));
}
[[doc_alias("stdc_bit_ceil_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), crt_intern_kos_alias("libc_stdc_bit_ceil_ull")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__),       alias("stdc_bit_ceil_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("stdc_bit_ceil_ull")]]
unsigned long stdc_bit_ceil_ul(unsigned long x) {
	return x <= 1 ? 1 : ((unsigned long)1 << ((__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz((unsigned long)(x - 1))));
}



%
%
%#ifdef __COMPILER_HAVE_LONGLONG
[[doc_alias("stdc_leading_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_leading_zeros_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_leading_zeros_ul")]]
unsigned int stdc_leading_zeros_ull(__ULONGLONG x) {
	return x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz(x);
}
[[doc_alias("stdc_leading_ones_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_leading_ones_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_leading_ones_ul")]]
unsigned int stdc_leading_ones_ull(__ULONGLONG x) {
	return x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz((__ULONGLONG)~x);
}
[[doc_alias("stdc_trailing_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_trailing_zeros_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_trailing_zeros_ul")]]
unsigned int stdc_trailing_zeros_ull(__ULONGLONG x) {
	return x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
[[doc_alias("stdc_trailing_ones_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_trailing_ones_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_trailing_ones_ul")]]
unsigned int stdc_trailing_ones_ull(__ULONGLONG x) {
	return x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~x);
}
[[doc_alias("stdc_first_leading_one_uc")]]
unsigned int stdc_first_leading_one_ull(__ULONGLONG i) = ffsll;
[[doc_alias("stdc_first_leading_zero_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_first_leading_zero_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_first_leading_zero_ul")]]
unsigned int stdc_first_leading_zero_ull(__ULONGLONG x) {
	return __hybrid_ffs((__ULONGLONG)~x);
}
[[doc_alias("stdc_first_trailing_zero_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_first_trailing_zero_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_first_trailing_zero_ul")]]
unsigned int stdc_first_trailing_zero_ull(__ULONGLONG x) {
	return x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
[[doc_alias("stdc_first_trailing_one_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_first_trailing_one_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_first_trailing_one_ul")]]
unsigned int stdc_first_trailing_one_ull(__ULONGLONG x) {
	return x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~x);
}
[[doc_alias("stdc_count_ones_uc")]]
unsigned int stdc_count_ones_ull(__ULONGLONG i) = popcountll;
[[doc_alias("stdc_count_zeros_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_count_zeros_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_count_zeros_ul")]]
unsigned int stdc_count_zeros_ull(__ULONGLONG x) {
	return __hybrid_popcount((__ULONGLONG)~x);
}
[[doc_alias("stdc_has_single_bit_uc")]]
[[extern_inline, nothrow, const, wunused]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_has_single_bit_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_has_single_bit_ul")]]
bool stdc_has_single_bit_ull(__ULONGLONG x) {
	return (__ULONGLONG)(x ^ (x - 1)) > (__ULONGLONG)(x - 1);
}
[[doc_alias("stdc_bit_width_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_bit_width_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_bit_width_ul")]]
unsigned int stdc_bit_width_ull(__ULONGLONG x) {
	return x == 0 ? 0 : (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz(x);
}
[[doc_alias("stdc_bit_floor_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_bit_floor_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_bit_floor_ul")]]
__ULONGLONG stdc_bit_floor_ull(__ULONGLONG x) {
	return x == 0 ? 0 : ((__ULONGLONG)1 << (((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(x)));
}
[[doc_alias("stdc_bit_ceil_uc")]]
[[extern_inline, nothrow, const, wunused, impl_include("<hybrid/__bit.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__),  alias("stdc_bit_ceil_ui")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("stdc_bit_ceil_ul")]]
__ULONGLONG stdc_bit_ceil_ull(__ULONGLONG x) {
	return x <= 1 ? 1 : ((__ULONGLONG)1 << ((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz((__ULONGLONG)(x - 1))));
}
%#endif /* __COMPILER_HAVE_LONGLONG */
%
%
%
%/* Type-generic implementations */
%
%{
#ifndef __PRIVATE_STDC_BIT_RECAST
#ifdef __COMPILER_HAVE_TYPEOF
#define __PRIVATE_STDC_BIT_RECAST(x, v) ((__typeof__(x))(v))
#elif defined(__COMPILER_HAVE_C11_GENERIC) && defined(__COMPILER_HAVE_LONGLONG)
#define __PRIVATE_STDC_BIT_RECAST(x, v) _Generic((x), unsigned char: (unsigned char)(v), unsigned short: (unsigned short)(v), unsigned int: (unsigned int)(v), unsigned long: (unsigned long)(v), __ULONGLONG: (__ULONGLONG)(v)default: v)
#elif defined(__COMPILER_HAVE_C11_GENERIC)
#define __PRIVATE_STDC_BIT_RECAST(x, v) _Generic((x), unsigned char: (unsigned char)(v), unsigned short: (unsigned short)(v), unsigned int: (unsigned int)(v), unsigned long: (unsigned long)(v), default: v)
#else /* ... */
#define __PRIVATE_STDC_BIT_RECAST(x, v) v
#endif /* !... */
#endif /* __PRIVATE_STDC_BIT_RECAST */

/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
#if __has_builtin(__builtin_stdc_leading_zeros)
#define stdc_leading_zeros(x) __builtin_stdc_leading_zeros(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_leading_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_leading_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_leading_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_leading_zeros_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_leading_zeros_ul((unsigned long)(x)),  \
	                                                  stdc_leading_zeros_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_leading_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_leading_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_leading_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_leading_zeros_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_leading_zeros_ul((unsigned long)(x))  : \
	                            : stdc_leading_zeros_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_leading_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_leading_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_leading_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_leading_zeros_ui((unsigned int)(x)),   \
	                                                  stdc_leading_zeros_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_leading_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_leading_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_leading_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_leading_zeros_ui((unsigned int)(x))   : \
	                            : stdc_leading_zeros_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
#if __has_builtin(__builtin_stdc_leading_ones)
#define stdc_leading_ones(x) __builtin_stdc_leading_ones(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_leading_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_leading_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_leading_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_leading_ones_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_leading_ones_ul((unsigned long)(x)),  \
	                                                  stdc_leading_ones_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_leading_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_leading_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_leading_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_leading_ones_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_leading_ones_ul((unsigned long)(x))  : \
	                            : stdc_leading_ones_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_leading_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_leading_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_leading_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_leading_ones_ui((unsigned int)(x)),   \
	                                                  stdc_leading_ones_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_leading_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_leading_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_leading_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_leading_ones_ui((unsigned int)(x))   : \
	                            : stdc_leading_ones_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
#if __has_builtin(__builtin_stdc_trailing_zeros)
#define stdc_trailing_zeros(x) __builtin_stdc_trailing_zeros(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_trailing_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_trailing_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_trailing_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_trailing_zeros_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_trailing_zeros_ul((unsigned long)(x)),  \
	                                                  stdc_trailing_zeros_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_trailing_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_trailing_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_trailing_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_trailing_zeros_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_trailing_zeros_ul((unsigned long)(x))  : \
	                            : stdc_trailing_zeros_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_trailing_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_trailing_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_trailing_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_trailing_zeros_ui((unsigned int)(x)),   \
	                                                  stdc_trailing_zeros_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_trailing_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_trailing_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_trailing_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_trailing_zeros_ui((unsigned int)(x))   : \
	                            : stdc_trailing_zeros_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
#if __has_builtin(__builtin_stdc_trailing_ones)
#define stdc_trailing_ones(x) __builtin_stdc_trailing_ones(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_trailing_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_trailing_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_trailing_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_trailing_ones_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_trailing_ones_ul((unsigned long)(x)),  \
	                                                  stdc_trailing_ones_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_trailing_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_trailing_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_trailing_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_trailing_ones_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_trailing_ones_ul((unsigned long)(x))  : \
	                            : stdc_trailing_ones_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_trailing_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_trailing_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_trailing_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_trailing_ones_ui((unsigned int)(x)),   \
	                                                  stdc_trailing_ones_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_trailing_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_trailing_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_trailing_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_trailing_ones_ui((unsigned int)(x))   : \
	                            : stdc_trailing_ones_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
#if __has_builtin(__builtin_stdc_first_leading_one)
#define stdc_first_leading_one(x) __builtin_stdc_first_leading_one(x)
#elif !defined(__OPTIMIZE_SIZE__)
#define stdc_first_leading_one(x) __hybrid_ffs(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_first_leading_one(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_leading_one_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_leading_one_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_leading_one_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_first_leading_one_ul((unsigned long)(x)),  \
	                                                  stdc_first_leading_one_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_first_leading_one(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_leading_one_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_leading_one_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_leading_one_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_first_leading_one_ul((unsigned long)(x))  : \
	                            : stdc_first_leading_one_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_first_leading_one(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_leading_one_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_leading_one_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_leading_one_ui((unsigned int)(x)),   \
	                                                  stdc_first_leading_one_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_first_leading_one(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_leading_one_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_leading_one_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_leading_one_ui((unsigned int)(x))   : \
	                            : stdc_first_leading_one_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
#if __has_builtin(__builtin_stdc_first_leading_zero)
#define stdc_first_leading_zero(x) __builtin_stdc_first_leading_zero(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_first_leading_zero(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_leading_zero_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_leading_zero_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_leading_zero_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_first_leading_zero_ul((unsigned long)(x)),  \
	                                                  stdc_first_leading_zero_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_first_leading_zero(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_leading_zero_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_leading_zero_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_leading_zero_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_first_leading_zero_ul((unsigned long)(x))  : \
	                            : stdc_first_leading_zero_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_first_leading_zero(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_leading_zero_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_leading_zero_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_leading_zero_ui((unsigned int)(x)),   \
	                                                  stdc_first_leading_zero_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_first_leading_zero(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_leading_zero_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_leading_zero_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_leading_zero_ui((unsigned int)(x))   : \
	                            : stdc_first_leading_zero_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
#if __has_builtin(__builtin_stdc_first_trailing_zero)
#define stdc_first_trailing_zero(x) __builtin_stdc_first_trailing_zero(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_first_trailing_zero(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_trailing_zero_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_trailing_zero_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_trailing_zero_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_first_trailing_zero_ul((unsigned long)(x)),  \
	                                                  stdc_first_trailing_zero_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_first_trailing_zero(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_trailing_zero_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_trailing_zero_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_trailing_zero_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_first_trailing_zero_ul((unsigned long)(x))  : \
	                            : stdc_first_trailing_zero_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_first_trailing_zero(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_trailing_zero_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_trailing_zero_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_trailing_zero_ui((unsigned int)(x)),   \
	                                                  stdc_first_trailing_zero_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_first_trailing_zero(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_trailing_zero_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_trailing_zero_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_trailing_zero_ui((unsigned int)(x))   : \
	                            : stdc_first_trailing_zero_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
#if __has_builtin(__builtin_stdc_first_trailing_one)
#define stdc_first_trailing_one(x) __builtin_stdc_first_trailing_one(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_first_trailing_one(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_trailing_one_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_trailing_one_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_trailing_one_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_first_trailing_one_ul((unsigned long)(x)),  \
	                                                  stdc_first_trailing_one_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_first_trailing_one(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_trailing_one_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_trailing_one_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_trailing_one_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_first_trailing_one_ul((unsigned long)(x))  : \
	                            : stdc_first_trailing_one_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_first_trailing_one(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_trailing_one_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_trailing_one_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_trailing_one_ui((unsigned int)(x)),   \
	                                                  stdc_first_trailing_one_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_first_trailing_one(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_trailing_one_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_trailing_one_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_trailing_one_ui((unsigned int)(x))   : \
	                            : stdc_first_trailing_one_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
#if __has_builtin(__builtin_stdc_count_ones)
#define stdc_count_ones(x) __builtin_stdc_count_ones(x)
#elif !defined(__OPTIMIZE_SIZE__)
#define stdc_count_ones(x) __hybrid_popcount(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_count_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_count_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_count_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_count_ones_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_count_ones_ul((unsigned long)(x)),  \
	                                                  stdc_count_ones_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_count_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_count_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_count_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_count_ones_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_count_ones_ul((unsigned long)(x))  : \
	                            : stdc_count_ones_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_count_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_count_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_count_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_count_ones_ui((unsigned int)(x)),   \
	                                                  stdc_count_ones_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_count_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_count_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_count_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_count_ones_ui((unsigned int)(x))   : \
	                            : stdc_count_ones_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
#if __has_builtin(__builtin_stdc_count_zeros)
#define stdc_count_zeros(x) __builtin_stdc_count_zeros(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_count_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_count_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_count_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_count_zeros_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_count_zeros_ul((unsigned long)(x)),  \
	                                                  stdc_count_zeros_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_count_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_count_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_count_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_count_zeros_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_count_zeros_ul((unsigned long)(x))  : \
	                            : stdc_count_zeros_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_count_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_count_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_count_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_count_zeros_ui((unsigned int)(x)),   \
	                                                  stdc_count_zeros_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_count_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_count_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_count_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_count_zeros_ui((unsigned int)(x))   : \
	                            : stdc_count_zeros_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
#if __has_builtin(__builtin_stdc_has_single_bit)
#define stdc_has_single_bit(x) __builtin_stdc_has_single_bit(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_has_single_bit(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_has_single_bit_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_has_single_bit_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_has_single_bit_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_has_single_bit_ul((unsigned long)(x)),  \
	                                                  stdc_has_single_bit_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_has_single_bit(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_has_single_bit_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_has_single_bit_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_has_single_bit_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_has_single_bit_ul((unsigned long)(x))  : \
	                            : stdc_has_single_bit_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_has_single_bit(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_has_single_bit_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_has_single_bit_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_has_single_bit_ui((unsigned int)(x)),   \
	                                                  stdc_has_single_bit_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_has_single_bit(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_has_single_bit_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_has_single_bit_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_has_single_bit_ui((unsigned int)(x))   : \
	                            : stdc_has_single_bit_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
#if __has_builtin(__builtin_stdc_bit_width)
#define stdc_bit_width(x) __builtin_stdc_bit_width(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_bit_width(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_width_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_width_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_width_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_bit_width_ul((unsigned long)(x)),  \
	                                                  stdc_bit_width_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_bit_width(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_width_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_width_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_width_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_bit_width_ul((unsigned long)(x))  : \
	                            : stdc_bit_width_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_bit_width(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_width_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_width_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_width_ui((unsigned int)(x)),   \
	                                                  stdc_bit_width_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_bit_width(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_width_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_width_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_width_ui((unsigned int)(x))   : \
	                            : stdc_bit_width_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
#if __has_builtin(__builtin_stdc_bit_floor)
#define stdc_bit_floor(x) __builtin_stdc_bit_floor(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_bit_floor(x) __PRIVATE_STDC_BIT_RECAST(x, \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_floor_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_floor_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_floor_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_bit_floor_ul((unsigned long)(x)),  \
	                                                  stdc_bit_floor_ull((__ULONGLONG)(x)))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_bit_floor(x) __PRIVATE_STDC_BIT_RECAST(x, \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_floor_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_floor_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_floor_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_bit_floor_ul((unsigned long)(x))  : \
	                            : stdc_bit_floor_ull((__ULONGLONG)(x))))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_bit_floor(x) __PRIVATE_STDC_BIT_RECAST(x, \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_floor_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_floor_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_floor_ui((unsigned int)(x)),   \
	                                                  stdc_bit_floor_ul((unsigned long)(x))))))
#else /* ... */
#define stdc_bit_floor(x) __PRIVATE_STDC_BIT_RECAST(x, \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_floor_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_floor_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_floor_ui((unsigned int)(x))   : \
	                            : stdc_bit_floor_ul((unsigned long)(x))))
#endif /* !... */


/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
#if __has_builtin(__builtin_stdc_bit_ceil)
#define stdc_bit_ceil(x) __builtin_stdc_bit_ceil(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_bit_ceil(x) __PRIVATE_STDC_BIT_RECAST(x, \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_ceil_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_ceil_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_ceil_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_bit_ceil_ul((unsigned long)(x)),  \
	                                                  stdc_bit_ceil_ull((__ULONGLONG)(x)))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_bit_ceil(x) __PRIVATE_STDC_BIT_RECAST(x, \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_ceil_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_ceil_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_ceil_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_bit_ceil_ul((unsigned long)(x))  : \
	                            : stdc_bit_ceil_ull((__ULONGLONG)(x))))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_bit_ceil(x) __PRIVATE_STDC_BIT_RECAST(x, \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_ceil_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_ceil_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_ceil_ui((unsigned int)(x)),   \
	                                                  stdc_bit_ceil_ul((unsigned long)(x))))))
#else /* ... */
#define stdc_bit_ceil(x) __PRIVATE_STDC_BIT_RECAST(x, \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_ceil_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_ceil_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_ceil_ui((unsigned int)(x))   : \
	                            : stdc_bit_ceil_ul((unsigned long)(x))))
#endif /* !... */

}
/*[[[end]]]*/


%{

__SYSDECL_END
}
%#endif /* __CC__ */
%{

}
