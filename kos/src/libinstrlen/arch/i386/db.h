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
#ifndef GUARD_LIBINSTRLEN_ARCH_I386_DB_H
#define GUARD_LIBINSTRLEN_ARCH_I386_DB_H 1

#include "../../api.h"
/**/

#include <kos/types.h>

DECL_BEGIN

/* Instruction type codes */

/* clang-format off */
#define I_UD      0x0 /* Instruction is not defined */
#define I_0       0x1 /* Instruction doesn't have any sort of tail */
#define I_1       0x2 /* Instruction has a 1-byte tail */
#define I_24      0x3 /* Instruction has a 2- or 4-byte tail (based on EMU86_F_OP16) */
#define I_RM      0x4 /* Instruction has a modr/m tail */
#define I_RM1     0x5 /* Instruction has a modr/m tail, followed by a 1-byte immediate operand */
#define I_RM24    0x6 /* Instruction has a modr/m tail, followed by a 2- or 4-byte immediate operand (based on EMU86_F_OP16) */
#define I_2       0x7 /* Instruction has a 2-byte tail */
#define I_3       0x8 /* Instruction has a 3-byte tail */
#define I_RM1_01  0x9 /* Instruction has a modr/m tail, followed by a 1-byte immediate operand when modrm.mi_reg in [0, 1] */
#define I_RM24_01 0xa /* Instruction has a modr/m tail, followed by a 2- or 4-byte immediate operand (based on EMU86_F_OP16) when modrm.mi_reg in [0, 1] */
#define I_AD24    0xb /* Instruction has a 2- or 4-byte tail (based on EMU86_F_AD16) */
#define I_AD46    0xc /* Instruction has a 4- or 6-byte tail (based on EMU86_F_AD16) */
/*      I_        0xd  * ... */
#ifdef __x86_64__
#define I_248     0xe /* Instruction has a 2-, 4- or 8-byte tail (based on EMU86_F_OP16 and EMU86_F_REX_W) */
#else /* __x86_64__ */
/*      I_        0xe  * ... */
#endif /* !__x86_64__ */
#define I_SPEC    0xf /* Determining this instruction's length requires special handling. (s.a. `IS_SPECIAL_INSTRUCTION()') */
/* clang-format on */


#ifndef __x86_64__
/* 64-bit operand aren't used outside  of 64-bit mode, so  we can just alias  the
 * 16-/32-/64-bit immediate operand instruction type with the 16-/32-bit variant! */
#define I_248 I_24
#endif /* !__x86_64__ */


/* Check if a given instruction `opcode' requires special handling */
#define IS_SPECIAL_INSTRUCTION(opcode) \
	((opcode) == 0x8f /* AMD XOP */)


#define PAIR(a, b) (a) | (b) << 4
#define LINE(_0, _1, _2, _3, _4, _5, _6, _7) \
	PAIR(_0, _1), PAIR(_2, _3), PAIR(_4, _5), PAIR(_6, _7)

/* clang-format off */
PRIVATE uint8_t const optypes[] = {

	/* `deemon -F' script to automatically update the opcode type database
	 *             with information extracted from libdisasm for x86!
	 * >> deemon -F kos/src/libinstrlen/arch/i386/db.h
	 */
/*[[[deemon
import * from deemon;
local final OPCODE_NAME_WIDTH = 6;

local opcodes: {int: string | HashSet with string} = Dict();
{
	local markers = {
		"ops"      : 0x000000,
		"ops_0f"   : 0x000f00,
		"ops_0f38" : 0x0f3800,
		"ops_0f3a" : 0x0f3a00,
	};
	local longreprs = Dict();
	for (local l: File.open("../../../libdisasm/x86-longops.def")) {
		local name, decl;
		try {
			name, decl = l.scanf(" LONGOP ( %[^,], %[^]")...;
		} catch (...) {
			continue;
		}
		name = name.strip();
		longreprs[name] = decl;
	}
	local opbase = none;
	for (local l: File.open("../../../libdisasm/x86-db.h")) {
		local final PREFIX = "/" "*[[[";
		local final SUFFIX = "]]]*" "/";
		l = l.strip();
		if (l.startswith(PREFIX) && l.endswith(SUFFIX)) {
			l = l[#PREFIX:-#SUFFIX].strip();
			if (opbase is none) {
				if (!l.startswith("start:"))
					continue;
				l = l[6:];
				opbase = markers.get(l);
			} else {
				local final PREFIX_VIRTUAL = "virtual:";
				if (l.startswith(PREFIX_VIRTUAL)) {
					l = l[#PREFIX_VIRTUAL:].lstrip();
					goto got_line;
				}
				if (!l.startswith("end:"))
					continue;
				opbase = none;
			}
			continue;
		}
got_line:
		if (opbase is none)
			continue;
		local opcode, decl;
		try {
			opcode, decl = l.scanf(" I ( %[^,], %[^]")...;
			opcode = int(opcode.strip());
		} catch (...) {
			continue;
		}
		opcode = opbase + opcode;
		local table = opcodes.get(opcode);
		if (table is none)
			opcodes[opcode] = table = HashSet();
		{
			local i = decl.find("/" "*");
			if (i >= 0)
				decl = decl[:i];
		}
		{
			local i = decl.find("LONGREPR");
			if (i >= 0) {
				local nameEnd = decl.find("(", i);
				if (nameEnd >= 0) {
					nameEnd = decl.findmatch("(", ")", nameEnd + 1);
					if (nameEnd >= 0) {
						local nameStart = decl.rfind(",", i, nameEnd);
						if (nameStart < 0)
							nameStart = decl.find("(", i, nameEnd);
						if (nameStart >= 0) {
							local name = decl[nameStart + 1:nameEnd].strip();
							if (name !in longreprs) {
								print File.stderr: ("Unknown long repr: ", repr name, " (in line: ", repr l, ")");
							} else {
								local decl1 = decl[:i];
								local decl2 = longreprs[name];
								if (decl.find("LONGREPR_B") == i) {
									local bStart = decl.index("(", i, nameStart) + 1;
									local bEnd = decl.find(",", bStart, nameStart);
									if (bEnd < 0)
										bEnd = nameStart;
									if (bEnd > bStart) {
										local firstByte = decl[bStart:bEnd].strip();
										firstByte = try int(firstByte) catch (...) none;
										if (firstByte !is none) {
											firstByte = r'"\x{}"'.format({ firstByte.hex()[2:] });
											if (decl2.startswith("\"")) {
												decl2 = firstByte[:-1] + decl2[1:];
											} else {
												decl2 = f"{firstByte} {decl2}";
											}
										}
									}
								}
								decl = decl1 + decl2;
							}
						}
					}
				}
			}
		}
		decl = decl.strip().strip("(),");
		// Unify immediate operand encodings to all use OP_U(8|16|32|64)
		decl = decl.replace("OP_S8", "OP_U8").replace("OP_DISP8", "OP_U8");
		decl = decl.replace("OP_S16", "OP_U16").replace("OP_DISP16", "OP_U16");
		decl = decl.replace("OP_S32", "OP_U32").replace("OP_DISP32", "OP_U32");
		decl = decl.replace("OP_S64", "OP_U64").replace("OP_DISP64", "OP_U64");
		decl = decl.replace("OP_MOFFS8", "OP_U8");
		decl = decl.replace("OP_MOFFS16", "OP_U16");
		decl = decl.replace("OP_MOFFS32", "OP_U32");
		decl = decl.replace("OP_MOFFS64", "OP_U64");
		decl = decl.replace("OP_IMM8_XMM", "OP_U8");
		decl = decl.replace("OP_IMM8_YMM", "OP_U8");
		decl = decl.replace("OP_IMM8_ZMM", "OP_U8");
		decl = decl.replace("OP_IMM8_xMM", "OP_U8");
		if (opcode == opbase && decl.replace(" ", "") == '0,""')
			continue;
		table.insert(decl);
	}
}

local final UNDEF = -1;
local final NO    = 0;
local final YES   = 1;

function isOpcodeTail1632(decls: HashSet with string, if_66: string = "IF_66"): bool {
	for (local d: decls) {
		if ("OP_U16" in d) {
			if (if_66 !in d)
				return false;
		} else {
			if ("OP_U32" !in d)
				return false;
			if (if_66 in d)
				return false;
		}
	}
	return true;
}

function isOpcodeTail163264(decls: HashSet with string): bool {
	for (local d: decls) {
		local want66   = false;
		local wantrexw = false;
		if ("OP_U16" in d) {
			want66 = true;
		} else if ("OP_U64" in d) {
			wantrexw = true;
		} else {
			if ("OP_U32" !in d)
				return false;
		}
		if (("IF_66" in d) != want66)
			return false;
		if (("IF_REXW" in d) != wantrexw)
			return false;
	}
	return true;
}

function declHasModrm(d: string): bool {
	if ("IF_MODRM" in d)
		return true;
	if ("IF_BYTE2" in d) {
		local i = d.find("\"\\x");
		if (i >= 0) {
			local h = d[i + 3:i + 5];
			h = try int(h, 16) catch (...) none;
			if (h !is none && h >= 0xc0 && h <= 0xff)
				return true; // A second byte code >= 0xc0 is a valid single-byte modr/m tail!
		}
	}
	return false;
}

function isOpcodeTail8_modrm_01(decls: HashSet with string): bool {
	for (local d: decls) {
		if (!declHasModrm(d))
			return false;
		local hasreg01 = "IF_REG0" in d || "IF_REG1" in d;
		if ("OP_U8" in d) {
			if (!hasreg01)
				return false;
		} else {
			if (hasreg01)
				return false;
		}
	}
	return true;
}

function isOpcodeTail1632_modrm_01(decls: HashSet with string): bool {
	for (local d: decls) {
		if (!declHasModrm(d))
			return false;
		local hasreg01 = "IF_REG0" in d || "IF_REG1" in d;
		if ("OP_U16" in d) {
			if (!hasreg01)
				return false;
			if ("IF_66" !in d)
				return false;
		} else if ("OP_U32" in d) {
			if (!hasreg01)
				return false;
			if ("IF_66" in d)
				return false;
		} else {
			if (hasreg01)
				return false;
		}
	}
	return true;
}

global hasUnrecognizedOpcodeTypes = false;
global specialOpcodeCount = 0;

function getOpcodeType(opcode: int, decls: HashSet with string): string {
	if (IS_SPECIAL_INSTRUCTION(opcode)) {
		++specialOpcodeCount;
		return "I_SPEC";
	}
	if (!decls)
		return "I_UD";
	local has8  = none;
	local has16 = none;
	local has32 = none;
	local has64 = none;
	local hasrm = none;
	local hasljmp = none;
	for (local d: decls) {
		local d_has8  = "OP_U8" in d;
		local d_has16 = "OP_U16" in d;
		local d_has32 = "OP_U32" in d;
		local d_has64 = "OP_U64" in d;
		local d_hasrm = declHasModrm(d);
		local d_hasljmp = "OP_LJMP" in d;
#define APPLY(dst, src)          \
		if (dst is none) {       \
			dst = int(src);      \
		} else if (dst != src) { \
			dst = UNDEF;         \
		}
		APPLY(has8, d_has8)
		APPLY(has16, d_has16)
		APPLY(has32, d_has32)
		APPLY(has64, d_has64)
		APPLY(hasrm, d_hasrm)
		APPLY(hasljmp, d_hasljmp)
	}
	if (hasljmp != NO) {
		if (hasljmp == YES && has8 == NO && has16 == NO && has32 == NO && has64 == NO && hasrm == NO)
			return "I_AD46";
	} else if (hasrm != UNDEF) {
		if (has8 == YES && has16 == NO && has32 == NO && has64 == NO)
			return hasrm == YES ? "I_RM1" : "I_1";
		if (has8 == NO && has16 == UNDEF && has32 == UNDEF && has64 == NO && isOpcodeTail1632(decls))
			return hasrm == YES ? "I_RM24" : "I_24";
		if (has8 == NO && has16 == NO && has32 == NO && has64 == NO)
			return hasrm == YES ? "I_RM" : "I_0";
		// Special instruction types
		if (has8 == NO && has16 == UNDEF && has32 == UNDEF && has64 == UNDEF && hasrm == NO && isOpcodeTail163264(decls))
			return "I_248";
		if (has8 == NO && has16 == YES && has32 == NO && has64 == NO && hasrm == NO)
			return "I_2";
		if (has8 == YES && has16 == YES && has32 == NO && has64 == NO && hasrm == NO)
			return "I_3";
		if (has8 == UNDEF && has16 == NO && has32 == NO && has64 == NO && hasrm == YES && isOpcodeTail8_modrm_01(decls))
			return "I_RM1_01";
		if (has8 == NO && has16 == UNDEF && has32 == UNDEF && has64 == NO && hasrm == YES && isOpcodeTail1632_modrm_01(decls))
			return "I_RM24_01";
		if (has8 == NO && has16 == UNDEF && has32 == UNDEF && has64 == NO && hasrm == NO && isOpcodeTail1632(decls, "IF_67"))
			return "I_AD24";
	}
	print File.stderr: (opcode.hex(), ":"),
		("has8:", has8), ("has16:", has16),
		("has32:", has32), ("has64:", has64),
		("hasrm:", hasrm);
	for (local d: decls.sorted())
		print File.stderr: ("\t", repr d);
	hasUnrecognizedOpcodeTypes = true;
	return "?";
}

// Load opcode types into the "opcodes" Dict
for (local opcode: HashSet(opcodes.keys)) {
	opcodes[opcode] = getOpcodeType(opcode, opcodes.get(opcode));
}

if (hasUnrecognizedOpcodeTypes)
	throw Error("Unrecognized opcode types present");

#define GETTYPE(opcode) opcodes.get(opcode, "I_UD")


@@Find the common opcode type for all opcodes in @[min:max+1],
@@whilst ignoring opcodes with a type of @"I_UD"
@@If no such common type exists, return @none instead.
function getCommonOpcodeTypeForRange(min: int, max: int): string | none {
	local result = none;
	for (local opcode: [min:max + 1]) {
		local temp = GETTYPE(opcode);
		if (temp == "I_UD")
			continue;
		if (result is none) {
			result = temp;
		} else if (result != temp) {
			return none;
		}
	}
	if (result is none)
		result = "I_UD";
	return result;
}

function setCommonOpcodeTypeForRange(min: int, max: int, typ: string) {
	for (local opcode: [min:max + 1])
		opcodes[opcode] = typ;
}

function printOpcodeTypeLine(start: int) {
	print("	/" "*", (start & 0xff).hex()[2:].zfill(2), "*" "/ LINE("),;
	for (local opcode: [start:start + 8]) {
		local typ = GETTYPE(opcode);
		if (opcode != start + 7)
			typ = (typ + ",").ljust(OPCODE_NAME_WIDTH + 1);
		print typ,;
	}
	print "),";
}

function printOpcodeTypeRange(min: int, max: int) {
	print("	/" "* ", min.hex()[2:].zfill(6), "-", max.hex()[2:].zfill(6), " *" "/");
	for (local start: [min:max + 1, 8])
		printOpcodeTypeLine(start);
}

// Print basic opcode ranges.
printOpcodeTypeRange(0x00, 0xff);
print;
printOpcodeTypeRange(0x0f00, 0x0fff);
print;


// Check for a common opcode type for ranges known to contain such types.
local common_0f38 = getCommonOpcodeTypeForRange(0x0f3800, 0x0f38ff);
local common_0f3a = getCommonOpcodeTypeForRange(0x0f3a00, 0x0f3aff);

if (common_0f38 !is none)
	setCommonOpcodeTypeForRange(0x0f3800, 0x0f38ff, common_0f38);
if (common_0f3a !is none)
	setCommonOpcodeTypeForRange(0x0f3a00, 0x0f3aff, common_0f3a);

// Figure out how many opcodes we want to (must) define explicitly.
local numberOfExplicitlyDefinedOpcodes = 0x200;
if (common_0f3a is none)
	numberOfExplicitlyDefinedOpcodes = 0x400;
else if (common_0f38 is none) {
	numberOfExplicitlyDefinedOpcodes = 0x300;
}

if (numberOfExplicitlyDefinedOpcodes >= 0x300) {
	printOpcodeTypeRange(0x0f3800, 0x0f38ff);
	print;
}

if (numberOfExplicitlyDefinedOpcodes >= 0x400) {
	printOpcodeTypeRange(0x0f3a00, 0x0f3aff);
	print;
}

print "#define SPECIAL_INSTRUCTION_COUNT", specialOpcodeCount, "/" "* # of instructions that use `I_SPEC' *" "/";
print "#define NUMBER_OF_EXPLICITLY_DEFINED_OPCODES", numberOfExplicitlyDefinedOpcodes.hex();
if (common_0f38 !is none)
	print "#define COMMON_OPCODE_TYPE_0f38xx ", common_0f38;
if (common_0f3a !is none)
	print "#define COMMON_OPCODE_TYPE_0f3axx ", common_0f3a;

]]]*/
	/* 000000-0000ff */
	/*00*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_1,   I_24,  I_0,   I_0),
	/*08*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_1,   I_24,  I_0,   I_UD),
	/*10*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_1,   I_24,  I_0,   I_0),
	/*18*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_1,   I_24,  I_0,   I_0),
	/*20*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_1,   I_24,  I_UD,  I_0),
	/*28*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_1,   I_24,  I_UD,  I_0),
	/*30*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_1,   I_24,  I_UD,  I_0),
	/*38*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_1,   I_24,  I_UD,  I_0),
	/*40*/ LINE(I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0),
	/*48*/ LINE(I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0),
	/*50*/ LINE(I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0),
	/*58*/ LINE(I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0),
	/*60*/ LINE(I_0,   I_0,   I_RM,  I_RM,  I_UD,  I_UD,  I_UD,  I_UD),
	/*68*/ LINE(I_24,  I_RM24,I_1,   I_RM1, I_0,   I_0,   I_0,   I_0),
	/*70*/ LINE(I_1,   I_1,   I_1,   I_1,   I_1,   I_1,   I_1,   I_1),
	/*78*/ LINE(I_1,   I_1,   I_1,   I_1,   I_1,   I_1,   I_1,   I_1),
	/*80*/ LINE(I_RM1, I_RM24,I_RM1, I_RM1, I_RM,  I_RM,  I_RM,  I_RM),
	/*88*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_SPEC),
	/*90*/ LINE(I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0),
	/*98*/ LINE(I_0,   I_0,   I_AD46,I_0,   I_0,   I_0,   I_0,   I_0),
	/*a0*/ LINE(I_1,   I_AD24,I_1,   I_AD24,I_0,   I_0,   I_0,   I_0),
	/*a8*/ LINE(I_1,   I_24,  I_0,   I_0,   I_0,   I_0,   I_0,   I_0),
	/*b0*/ LINE(I_1,   I_1,   I_1,   I_1,   I_1,   I_1,   I_1,   I_1),
	/*b8*/ LINE(I_248, I_248, I_248, I_248, I_248, I_248, I_248, I_248),
	/*c0*/ LINE(I_RM1, I_RM1, I_2,   I_0,   I_RM,  I_RM,  I_RM1, I_RM24),
	/*c8*/ LINE(I_3,   I_0,   I_2,   I_0,   I_0,   I_1,   I_0,   I_0),
	/*d0*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_1,   I_1,   I_0,   I_0),
	/*d8*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*e0*/ LINE(I_1,   I_1,   I_1,   I_1,   I_1,   I_1,   I_1,   I_1),
	/*e8*/ LINE(I_24,  I_24,  I_AD46,I_1,   I_0,   I_0,   I_0,   I_0),
	/*f0*/ LINE(I_UD,  I_0,   I_UD,  I_UD,  I_0,   I_0,   I_RM1_01,I_RM24_01),
	/*f8*/ LINE(I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_RM,  I_RM),

	/* 000f00-000fff */
	/*00*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_UD,  I_0,   I_0,   I_0),
	/*08*/ LINE(I_0,   I_0,   I_0,   I_0,   I_UD,  I_RM,  I_0,   I_RM1),
	/*10*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*18*/ LINE(I_RM,  I_UD,  I_RM,  I_RM,  I_RM,  I_UD,  I_RM,  I_RM),
	/*20*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_UD,  I_RM,  I_UD),
	/*28*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*30*/ LINE(I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0),
	/*38*/ LINE(I_UD,  I_UD,  I_UD,  I_UD,  I_UD,  I_UD,  I_UD,  I_0),
	/*40*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*48*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*50*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*58*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*60*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*68*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*70*/ LINE(I_RM1, I_RM1, I_RM1, I_RM1, I_RM,  I_RM,  I_RM,  I_0),
	/*78*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*80*/ LINE(I_24,  I_24,  I_24,  I_24,  I_24,  I_24,  I_24,  I_24),
	/*88*/ LINE(I_24,  I_24,  I_24,  I_24,  I_24,  I_24,  I_24,  I_24),
	/*90*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*98*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*a0*/ LINE(I_0,   I_0,   I_0,   I_RM,  I_RM1, I_RM,  I_RM,  I_RM),
	/*a8*/ LINE(I_0,   I_0,   I_0,   I_RM,  I_RM1, I_RM,  I_RM,  I_RM),
	/*b0*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*b8*/ LINE(I_RM,  I_RM,  I_RM1, I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*c0*/ LINE(I_RM,  I_RM,  I_RM1, I_RM,  I_RM1, I_RM1, I_RM1, I_RM),
	/*c8*/ LINE(I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0,   I_0),
	/*d0*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*d8*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*e0*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*e8*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*f0*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM),
	/*f8*/ LINE(I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_RM,  I_0),

#define SPECIAL_INSTRUCTION_COUNT 1 /* # of instructions that use `I_SPEC' */
#define NUMBER_OF_EXPLICITLY_DEFINED_OPCODES 0x200
#define COMMON_OPCODE_TYPE_0f38xx  I_RM
#define COMMON_OPCODE_TYPE_0f3axx  I_RM1
//[[[end]]]
};
/* clang-format on */

#undef LINE
#undef PAIR

/* Make sure that the correct # of opcodes have been defined */
STATIC_ASSERT(sizeof(optypes) * 2 == NUMBER_OF_EXPLICITLY_DEFINED_OPCODES);


DECL_END

#endif /* !GUARD_LIBINSTRLEN_ARCH_I386_DB_H */
