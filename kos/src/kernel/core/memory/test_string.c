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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_C
#define GUARD_KERNEL_SRC_MEMORY_VM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <stdint.h>
#include <string.h>

/* Quick, dirty (and _very_ excessive) generators for testing `memcpy()', `memmove()'
 * and `memset()', as well as all of their derivatives for conforming to requirements.
 * These tests are designed to also test the functions in cases where different arguments
 * are already known at compile-time, thus testing the various optimizations possible
 * when this is the case. */
#if 0
DECL_BEGIN

/*[[[deemon
local fp = (File from deemon).stdout;
tests = [];
local test_size = 36;
for (local i: [:test_size]) {
	fp << "PRIVATE volatile size_t i" << i << " = " << i << ";\n";
}
function gentest_memcpy(name,T,is_pcpy,is_move) {
	tests.append(name);
	fp << "PRIVATE void KCALL test_" << name << "(void) {\n";
	fp << "\t" << (T in ["u16","u32","u64"] ? T : "void") << " *return_value;\n";
	fp << "\tsize_t i;\n";
	for (local i: [:test_size]) {
		fp << "\t{\n";
		fp << "\t\t" << T << " dst[" << (i + 2) << "];\n";
		fp << "\t\t" << T << " src[" << (i + 2) << "];\n";
		fp << "\t\tdst[0] = 'a';\n";
		fp << "\t\tdst[" << (i + 1) << "] = 'z';\n";
		fp << "\t\tsrc[0] = 'A';\n";
		fp << "\t\tsrc[" << (i + 1) << "] = 'Z';\n";
		if (i) {
			fp << "\t\tfor (i = 0; i < " << i << "; ++i) {\n";
			fp << "\t\t\tdst[i + 1] = 0;\n";
			fp << "\t\t\tsrc[i + 1] = (" << T << ")i;\n";
			fp << "\t\t}\n";
		}
		fp << "\t\treturn_value = " << name << "(dst + 1,src + 1," << i << ");\n";
		fp << "\t\tassertf(return_value == " << (is_pcpy ? "COMPILER_ENDOF(dst) - 1" : "dst + 1") << ",\"%Iu\",(" << T << " *)return_value - (dst + 1));\n";
		fp << "\t\tassert(dst[0] == 'a');\n";
		fp << "\t\tassert(dst[" << (i + 1) << "] == 'z');\n";
		fp << "\t\tassert(src[0] == 'A');\n";
		fp << "\t\tassert(src[" << (i + 1) << "] == 'Z');\n";
		fp << "\t\tfor (i = 0; i < " << i << "; ++i) {\n";
		fp << "\t\t\tassertf(dst[i + 1] == (" << T << ")i,\"i + 1 = %Iu; dst[i + 1] = %Ix\",i + 1,(uintptr_t)dst[i + 1]);\n";
		fp << "\t\t\tassertf(src[i + 1] == (" << T << ")i,\"i + 1 = %Iu; src[i + 1] = %Ix\",i + 1,(uintptr_t)src[i + 1]);\n";
		fp << "\t\t}\n";
		fp << "\t\treturn_value = " << name << "(dst + 1,src + 1,i" << i << ");\n";
		fp << "\t\tassertf(return_value == " << (is_pcpy ? "COMPILER_ENDOF(dst) - 1" : "dst + 1") << ",\"%Iu\",(" << T << " *)return_value - (dst + 1));\n";
		fp << "\t\tassert(dst[0] == 'a');\n";
		fp << "\t\tassert(dst[" << (i + 1) << "] == 'z');\n";
		fp << "\t\tassert(src[0] == 'A');\n";
		fp << "\t\tassert(src[" << (i + 1) << "] == 'Z');\n";
		fp << "\t\tfor (i = 0; i < " << i << "; ++i) {\n";
		fp << "\t\t\tassertf(dst[i + 1] == (" << T << ")i,\"i + 1 = %Iu; dst[i + 1] = %Ix\",i + 1,(uintptr_t)dst[i + 1]);\n";
		fp << "\t\t\tassertf(src[i + 1] == (" << T << ")i,\"i + 1 = %Iu; src[i + 1] = %Ix\",i + 1,(uintptr_t)src[i + 1]);\n";
		fp << "\t\t}\n";
		if (is_move) {
			fp << "\t\t" << name << "(dst + 1,dst + 2," << i << ");\n";
			fp << "\t\tassert(dst[0] == 'a');\n";
			fp << "\t\tassert(dst[" << (i + 1) << "] == 'z');\n";
			if (i) fp << "\t\tassert(dst[" << (i) << "] == 'z');\n";
			if (i > 1) {
				fp << "\t\tfor (i = 0; i < " << (i - 1) << "; ++i) {\n";
				fp << "\t\t\tassertf(dst[i + 1] == (" << T << ")i + 1,\"i + 1 = %Iu; dst[i + 1] = %Ix\",i + 1,(uintptr_t)dst[i + 1]);\n";
				fp << "\t\t}\n";
			}
			fp << "\t\t" << name << "(src + 1,src + 2,i" << i << ");\n";
			fp << "\t\tassert(src[0] == 'A');\n";
			fp << "\t\tassert(src[" << (i + 1) << "] == 'Z');\n";
			if (i) fp << "\t\tassert(src[" << (i) << "] == 'Z');\n";
			if (i > 1) {
				fp << "\t\tfor (i = 0; i < " << (i - 1) << "; ++i) {\n";
				fp << "\t\t\tassertf(src[i + 1] == (" << T << ")i + 1,\"i + 1 = %Iu; src[i + 1] = %Ix\",i + 1,(uintptr_t)src[i + 1]);\n";
				fp << "\t\t}\n";
			}
			fp << "\t\t" << name << "(dst + 2,dst + 1," << i << ");\n";
			fp << "\t\tassert(dst[0] == 'a');\n";
			fp << "\t\tassert(dst[" << (i + 1) << "] == 'z');\n";
			if (i > 1) {
				fp << "\t\tassert(dst[1] == dst[2]);\n";
				fp << "\t\tfor (i = 1; i < " << i << "; ++i) {\n";
				fp << "\t\t\tassertf(dst[i + 1] == (" << T << ")i,\"i + 1 = %Iu; dst[i + 1] = %Ix\",i + 1,(uintptr_t)dst[i + 1]);\n";
				fp << "\t\t}\n";
			}
			fp << "\t\t" << name << "(src + 2,src + 1,i" << i << ");\n";
			fp << "\t\tassert(src[0] == 'A');\n";
			fp << "\t\tassert(src[" << (i + 1) << "] == 'Z');\n";
			if (i > 1) {
				fp << "\t\tassert(src[1] == src[2]);\n";
				fp << "\t\tfor (i = 1; i < " << i << "; ++i) {\n";
				fp << "\t\t\tassertf(src[i + 1] == (" << T << ")i,\"i + 1 = %Iu; src[i + 1] = %Ix\",i + 1,(uintptr_t)src[i + 1]);\n";
				fp << "\t\t}\n";
			}
		}
		fp << "\t}\n";
	}
	fp << "}\n";
}
function gentest_memset(name,T,is_pset,pat_c,patterns) {
	tests.append(name);
	fp << "PRIVATE void KCALL test_" << name << "(void) {\n";
	fp << "\t" << (T in ["u16","u32","u64"] ? T : "void") << " *return_value;\n";
	fp << "\tsize_t i;\n";
	for (local i: [:test_size]) {
		fp << "\t{\n";
		fp << "\t\t" << T << " dst[" << (i + 2) << "];\n";
		fp << "\t\tdst[0] = 'a';\n";
		fp << "\t\tdst[" << (i + 1) << "] = 'z';\n";
		for (local pat: patterns) {
			local ppat = "{}({})".format({ pat_c, pat.hex() });
			if (i) {
				fp << "\t\tfor (i = 0; i < " << i << "; ++i) {\n";
				fp << "\t\t\tdst[i + 1] = (" << T << ")~" << ppat << ";\n";
				fp << "\t\t}\n";
			}
			fp << "\t\treturn_value = " << name << "(dst + 1," << ppat << "," << i << ");\n";
			fp << "\t\tassertf(return_value == " << (is_pset ? "COMPILER_ENDOF(dst) - 1" : "dst + 1") << ",\"%Iu\",(" << T << " *)return_value - (dst + 1));\n";
			fp << "\t\tassert(dst[0] == 'a');\n";
			fp << "\t\tassert(dst[" << (i + 1) << "] == 'z');\n";
			fp << "\t\tfor (i = 0; i < " << i << "; ++i) {\n";
			fp << "\t\t\tassertf(dst[i + 1] == " << ppat << ",\"i + 1 = %Iu; dst[i + 1] = %Ix\",i + 1,(uintptr_t)dst[i + 1]);\n";
			fp << "\t\t}\n";
			fp << "\t\treturn_value = " << name << "(dst + 1," << ppat << ",i" << i << ");\n";
			fp << "\t\tassertf(return_value == " << (is_pset ? "COMPILER_ENDOF(dst) - 1" : "dst + 1") << ",\"%Iu\",(" << T << " *)return_value - (dst + 1));\n";
			fp << "\t\tassert(dst[0] == 'a');\n";
			fp << "\t\tassert(dst[" << (i + 1) << "] == 'z');\n";
			fp << "\t\tfor (i = 0; i < " << i << "; ++i) {\n";
			fp << "\t\t\tassertf(dst[i + 1] == " << ppat << ",\"i + 1 = %Iu; dst[i + 1] = %Ix\",i + 1,(uintptr_t)dst[i + 1]);\n";
			fp << "\t\t}\n";
		}
		fp << "\t}\n";
	}
	fp << "}\n";
}

// gentest_memcpy("memcpy","u8",false,false);
// gentest_memcpy("memcpyw","u16",false,false);
// gentest_memcpy("memcpyl","u32",false,false);
// gentest_memcpy("memcpyq","u64",false,false);
// gentest_memcpy("mempcpy","u8",true,false);
// gentest_memcpy("mempcpyw","u16",true,false);
// gentest_memcpy("mempcpyl","u32",true,false);
// gentest_memcpy("mempcpyq","u64",true,false);
// gentest_memcpy("memmove","u8",false,true);
// gentest_memcpy("memmovew","u16",false,true);
// gentest_memcpy("memmovel","u32",false,true);
// gentest_memcpy("memmoveq","u64",false,true);
// gentest_memcpy("mempmove","u8",true,true);
// gentest_memcpy("mempmovew","u16",true,true);
// gentest_memcpy("mempmovel","u32",true,true);
// gentest_memcpy("mempmoveq","u64",true,true);

// gentest_memset("memset","u8",false,"UINT8_C",[0,0xab,0xfe]);
// gentest_memset("memsetw","u16",false,"UINT16_C",[0,0xabcd,0xfe12]);
// gentest_memset("memsetl","u32",false,"UINT32_C",[0,0x89abcdef,0x412364fa]);
// gentest_memset("memsetq","u64",false,"UINT64_C",[0,0xab,0xff]);
// gentest_memset("mempset","u8",true,"UINT8_C",[0,0xab,0xfe]);
// gentest_memset("mempsetw","u16",true,"UINT16_C",[0,0xabcd,0xfe12]);
// gentest_memset("mempsetl","u32",true,"UINT32_C",[0,0x89abcdef,0x412364fa]);
// gentest_memset("mempsetq","u64",true,"UINT64_C",[0,0xab,0xff]);


fp << "INTERN void KCALL test_string(void) {\n";
for (local x: tests)
	fp << " test_" << x << "();\n";
fp << "}\n";

]]]*/
PRIVATE volatile size_t i0 = 0;
PRIVATE volatile size_t i1 = 1;
PRIVATE volatile size_t i2 = 2;
PRIVATE volatile size_t i3 = 3;
PRIVATE volatile size_t i4 = 4;
PRIVATE volatile size_t i5 = 5;
PRIVATE volatile size_t i6 = 6;
PRIVATE volatile size_t i7 = 7;
PRIVATE volatile size_t i8 = 8;
PRIVATE volatile size_t i9 = 9;
PRIVATE volatile size_t i10 = 10;
PRIVATE volatile size_t i11 = 11;
PRIVATE volatile size_t i12 = 12;
PRIVATE volatile size_t i13 = 13;
PRIVATE volatile size_t i14 = 14;
PRIVATE volatile size_t i15 = 15;
PRIVATE volatile size_t i16 = 16;
PRIVATE volatile size_t i17 = 17;
PRIVATE volatile size_t i18 = 18;
PRIVATE volatile size_t i19 = 19;
PRIVATE volatile size_t i20 = 20;
PRIVATE volatile size_t i21 = 21;
PRIVATE volatile size_t i22 = 22;
PRIVATE volatile size_t i23 = 23;
PRIVATE volatile size_t i24 = 24;
PRIVATE volatile size_t i25 = 25;
PRIVATE volatile size_t i26 = 26;
PRIVATE volatile size_t i27 = 27;
PRIVATE volatile size_t i28 = 28;
PRIVATE volatile size_t i29 = 29;
PRIVATE volatile size_t i30 = 30;
PRIVATE volatile size_t i31 = 31;
PRIVATE volatile size_t i32 = 32;
PRIVATE volatile size_t i33 = 33;
PRIVATE volatile size_t i34 = 34;
PRIVATE volatile size_t i35 = 35;
INTERN void KCALL test_string(void) {
}
//[[[end]]]

DECL_END
#endif

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_C */
