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
#ifdef __INTELLISENSE__
#define EMU86_UNSUPPORTED_MEMACCESS(addr, num_bytes, reading, writing) (void)0
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

/* Instructions that aren't supported. */

EMU86_INTELLISENSE_BEGIN(_notsup) {

#if EMU86_EMULATE_CONFIG_CHECKERROR || defined(__DEEMON__)

/*[[[deemon
import * from deemon;
local db_filename = "./../../../src/libdisasm/x86-db.h";
local opcodes = Dict();
local current_namespace = none;

for (local l: File.open(db_filename, "r")) {
	l = l.strip().decode("utf-8");
	if (l.startswith("/" "*[[[") && l.endswith("]]]*" "/")) {
		l = l[5:-5];
		if (l.startswith("end:")) {
			current_namespace = none;
		} else if (l.startswith("start:")) {
			l = l[6:];
			current_namespace = {
				"ops"      : 0x000000,
				"ops_0f"   : 0x000f00,
				"ops_0f38" : 0x0f3800,
				"ops_0f3a" : 0x0f3a00,
			}.get(l);
		}
		continue;
	}
	if (current_namespace is none)
		continue;
	if (!l)
		continue;
	local opcode, flags, desc;
	try {
		opcode, flags, desc = l.scanf("I ( %[^,],%[^,],%[^]")...;
		opcode = int(opcode.strip());
	} catch (...) {
		continue;
	}
	opcode = current_namespace | opcode;
	flags  = flags.strip();
	opcodes.setdefault(opcode, []).append((flags, desc));
}

function splitWords(text: string): {string...} {
	local i = 0, len = #text;
	while (i < len) {
		if (text.isspace(i)) {
			++i;
			continue;
		}
		if (!text.issymstrt(i)) {
			++i;
			continue;
		}
		local start = i;
		do {
			++i;
		} while (i < len && text.issymcont(i));
		yield text[start:i];
	}
}

function containsAny(seq: {Object...}, elem: {Object...}): bool {
	for (local e: elem) {
		if (e in seq)
			return true;
	}
	return false;
}

local SEE_rd_opcodes = HashSet();
local SEE_wr_opcodes = HashSet();
local SEE_rdwr_opcodes = HashSet();
for (local opcode, data: opcodes) {
	for (local d: data) {
		local flags, desc = d...;
		local keywords = HashSet(splitWords(desc));
		if (opcode in SEE_rd_opcodes || opcode in SEE_wr_opcodes || opcode in SEE_rdwr_opcodes)
			continue;
		if (containsAny(keywords, {
			"OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK",
			"OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK",
			"OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK",
			"OP_RM128_XMM__OP_VRXMM__OP_RXMM",
			"OP_RM256_YMM__OP_VRYMM__OP_RYMM",
			"OP_RM512_ZMM__OP_VRZMM__OP_RZMM",
		})) {
			SEE_rd_opcodes.insert(opcode);
			continue;
		} else if (containsAny(keywords, {
			"OP_VRXMM_MASK",
			"OP_VRYMM_MASK",
			"OP_VRZMM_MASK",
			"OP_VRXMM",
			"OP_VRYMM",
			"OP_VRZMM",
			"OP_RXMM_MASK",
			"OP_RYMM_MASK",
			"OP_RZMM_MASK",
			"OP_RXMM",
			"OP_RYMM",
			"OP_RZMM",
			"OP_RM128_XMM_MASK",
			"OP_RM256_YMM_MASK",
			"OP_RM512_ZMM_MASK",
			"OP_RM128_XMM",
			"OP_RM256_YMM",
			"OP_RM512_ZMM",
			"OP_IMM8_XMM",
			"OP_IMM8_YMM",
			"OP_IMM8_ZMM",
			"xmm", "xmm1", "xmm2", "xmm3",
			"ymm", "ymm1", "ymm2", "ymm3",
			"zmm", "zmm1", "zmm2", "zmm3",
			"mm", "mm1", "mm2", "mm3",
		})) {
			local commentStart = desc.find("/" "*");
			if (commentStart >= 0) {
				local opsStart = desc.index("/", commentStart + 2) + 1;
				while (desc.issymcont(opsStart)) ++opsStart;
				while (desc.isspace(opsStart)) ++opsStart;
				if (desc.substr(opsStart, opsStart + 2) in ["ib"]) {
					opsStart += 2;
					while (desc.isspace(opsStart)) ++opsStart;
				}
				if (desc.substr(opsStart, opsStart + 4) in ["/is4"]) {
					opsStart += 4;
					while (desc.isspace(opsStart)) ++opsStart;
				}
				while (desc.issymcont(opsStart)) ++opsStart;
				while (desc.isspace(opsStart)) ++opsStart;
				local intel_repr = desc[opsStart:desc.rindex("*" "/", opsStart)].strip();
				intel_repr = intel_repr.replace(", ", ",");
				intel_repr = intel_repr.replace("xmm", "REG");
				intel_repr = intel_repr.replace("ymm", "REG");
				intel_repr = intel_repr.replace("zmm", "REG");
				intel_repr = intel_repr.replace("REG1", "REG");
				intel_repr = intel_repr.replace("REG2", "REG");
				intel_repr = intel_repr.replace("REG3", "REG");
				intel_repr = intel_repr.replace("REG4", "REG");
				intel_repr = intel_repr.replace("REG+3", "REG");
				intel_repr = intel_repr.replace("{sae}", "");
				intel_repr = intel_repr.replace("{er}", "");
				intel_repr = intel_repr.replace("k1", "k");
				intel_repr = intel_repr.replace("k2", "k");
				intel_repr = intel_repr.replace("k3", "k");
				intel_repr = intel_repr.replace("{k}", "");
				intel_repr = intel_repr.replace("{z}", "");
				intel_repr = intel_repr.replace("/m32bcst", "");
				intel_repr = intel_repr.replace("/m64bcst", "");
				intel_repr = intel_repr.replace("/m8", "/m");
				intel_repr = intel_repr.replace("/m16", "/m");
				intel_repr = intel_repr.replace("/m32", "/m");
				intel_repr = intel_repr.replace("/m64", "/m");
				intel_repr = intel_repr.replace("/m128", "/m");
				intel_repr = intel_repr.replace("/m256", "/m");
				intel_repr = intel_repr.replace("/m512", "/m");
				intel_repr = intel_repr.replace("r8/", "r/");
				intel_repr = intel_repr.replace("r16/", "r/");
				intel_repr = intel_repr.replace("r32/", "r/");
				intel_repr = intel_repr.replace("r64/", "r/");
				intel_repr = intel_repr.replace("REG/m", "MEM");
				intel_repr = intel_repr.replace("r/m", "MEM");
				intel_repr = intel_repr.replace(",r8", ",REG");
				intel_repr = intel_repr.replace(",r16", ",REG");
				intel_repr = intel_repr.replace(",r32", ",REG");
				intel_repr = intel_repr.replace(",r64", ",REG");
				intel_repr = intel_repr.replace(",mm", ",REG");
				intel_repr = intel_repr.replace("r8,", "REG,");
				intel_repr = intel_repr.replace("r16,", "REG,");
				intel_repr = intel_repr.replace("r32,", "REG,");
				intel_repr = intel_repr.replace("r64,", "REG,");
				intel_repr = intel_repr.replace("mm,", "REG,");
				intel_repr = intel_repr.replace(",m8", ",MEM");
				intel_repr = intel_repr.replace(",m16", ",MEM");
				intel_repr = intel_repr.replace(",m32", ",MEM");
				intel_repr = intel_repr.replace(",m64", ",MEM");
				intel_repr = intel_repr.replace(",m128", ",MEM");
				intel_repr = intel_repr.replace(",m256", ",MEM");
				intel_repr = intel_repr.replace(",m512", ",MEM");
				intel_repr = intel_repr.replace("m8,", "MEM,");
				intel_repr = intel_repr.replace("m16,", "MEM,");
				intel_repr = intel_repr.replace("m32,", "MEM,");
				intel_repr = intel_repr.replace("m64,", "MEM,");
				intel_repr = intel_repr.replace("m128,", "MEM,");
				intel_repr = intel_repr.replace("m256,", "MEM,");
				intel_repr = intel_repr.replace("m512,", "MEM,");
				if (intel_repr in {
					"REG,REG,MEM",
					"REG,REG,MEM,REG",
					"REG,MEM",
					"REG,MEM,imm8",
					"REG,REG,imm8",
					"REG,REG,MEM,imm8",
					"k,REG,MEM",
					"k,REG,MEM,imm8",
					"k,MEM,imm8",
					"REG,k",
					"k,REG",
					"REG,REG",
				}) {
					SEE_rd_opcodes.insert(opcode);
				} else if (intel_repr in {
					"MEM,REG",
					"MEM,REG,REG",
					"MEM,REG,imm8",
				}) {
					if (" vmov" in desc) {
						SEE_rdwr_opcodes.insert(opcode);
					} else {
						SEE_wr_opcodes.insert(opcode);
					}
				} else {
					throw Error("Unable to determine read/write for " + repr(opcode.hex()) + " (" + repr(intel_repr) + ")");
				}
			} else {
				throw Error("Unable to determine read/write for " + repr(opcode.hex()) + " (" + repr(desc) + ")");
			}
		}
	}
}

if (SEE_rd_opcodes) {
	SEE_rd_opcodes = SEE_rd_opcodes.sorted();
	for (local opcode: SEE_rd_opcodes) {
		local z = opcode >= 0x1000 ? 6 : opcode >= 0x100 ? 4 : 2;
		print("	case EMU86_OPCODE_ENCODE(0x", opcode.hex()[2:].zfill(z), "):");
	}
	print "		goto notsup_modrm_getxyzmm;";
	print "#define NEED_notsup_modrm_getxyzmm";
	print;
}

if (SEE_wr_opcodes) {
	SEE_wr_opcodes = SEE_wr_opcodes.sorted();
	for (local opcode: SEE_wr_opcodes) {
		local z = opcode >= 0x1000 ? 6 : opcode >= 0x100 ? 4 : 2;
		print("	case EMU86_OPCODE_ENCODE(0x", opcode.hex()[2:].zfill(z), "):");
	}
	print "		goto notsup_modrm_setxyzmm;";
	print "#define NEED_notsup_modrm_setxyzmm";
	print;
}

if (SEE_rdwr_opcodes) {
	SEE_rdwr_opcodes = SEE_rdwr_opcodes.sorted();
	for (local opcode: SEE_rdwr_opcodes) {
		local z = opcode >= 0x1000 ? 6 : opcode >= 0x100 ? 4 : 2;
		print("	case EMU86_OPCODE_ENCODE(0x", opcode.hex()[2:].zfill(z), "):");
	}
	print "		goto notsup_modrm_getsetxyzmm;";
	print "#define NEED_notsup_modrm_getsetxyzmm";
	print;
}

]]]*/
	case EMU86_OPCODE_ENCODE(0x0f10):
	case EMU86_OPCODE_ENCODE(0x0f12):
	case EMU86_OPCODE_ENCODE(0x0f14):
	case EMU86_OPCODE_ENCODE(0x0f15):
	case EMU86_OPCODE_ENCODE(0x0f16):
	case EMU86_OPCODE_ENCODE(0x0f28):
	case EMU86_OPCODE_ENCODE(0x0f2a):
	case EMU86_OPCODE_ENCODE(0x0f2c):
	case EMU86_OPCODE_ENCODE(0x0f2d):
	case EMU86_OPCODE_ENCODE(0x0f2e):
	case EMU86_OPCODE_ENCODE(0x0f2f):
	case EMU86_OPCODE_ENCODE(0x0f50):
	case EMU86_OPCODE_ENCODE(0x0f51):
	case EMU86_OPCODE_ENCODE(0x0f52):
	case EMU86_OPCODE_ENCODE(0x0f53):
	case EMU86_OPCODE_ENCODE(0x0f54):
	case EMU86_OPCODE_ENCODE(0x0f55):
	case EMU86_OPCODE_ENCODE(0x0f56):
	case EMU86_OPCODE_ENCODE(0x0f57):
	case EMU86_OPCODE_ENCODE(0x0f58):
	case EMU86_OPCODE_ENCODE(0x0f59):
	case EMU86_OPCODE_ENCODE(0x0f5a):
	case EMU86_OPCODE_ENCODE(0x0f5b):
	case EMU86_OPCODE_ENCODE(0x0f5c):
	case EMU86_OPCODE_ENCODE(0x0f5d):
	case EMU86_OPCODE_ENCODE(0x0f5e):
	case EMU86_OPCODE_ENCODE(0x0f5f):
	case EMU86_OPCODE_ENCODE(0x0f60):
	case EMU86_OPCODE_ENCODE(0x0f61):
	case EMU86_OPCODE_ENCODE(0x0f62):
	case EMU86_OPCODE_ENCODE(0x0f63):
	case EMU86_OPCODE_ENCODE(0x0f64):
	case EMU86_OPCODE_ENCODE(0x0f65):
	case EMU86_OPCODE_ENCODE(0x0f66):
	case EMU86_OPCODE_ENCODE(0x0f67):
	case EMU86_OPCODE_ENCODE(0x0f68):
	case EMU86_OPCODE_ENCODE(0x0f69):
	case EMU86_OPCODE_ENCODE(0x0f6a):
	case EMU86_OPCODE_ENCODE(0x0f6b):
	case EMU86_OPCODE_ENCODE(0x0f6c):
	case EMU86_OPCODE_ENCODE(0x0f6d):
	case EMU86_OPCODE_ENCODE(0x0f6e):
	case EMU86_OPCODE_ENCODE(0x0f6f):
	case EMU86_OPCODE_ENCODE(0x0f70):
	case EMU86_OPCODE_ENCODE(0x0f71):
	case EMU86_OPCODE_ENCODE(0x0f72):
	case EMU86_OPCODE_ENCODE(0x0f73):
	case EMU86_OPCODE_ENCODE(0x0f74):
	case EMU86_OPCODE_ENCODE(0x0f75):
	case EMU86_OPCODE_ENCODE(0x0f76):
	case EMU86_OPCODE_ENCODE(0x0f78):
	case EMU86_OPCODE_ENCODE(0x0f79):
	case EMU86_OPCODE_ENCODE(0x0f7a):
	case EMU86_OPCODE_ENCODE(0x0f7b):
	case EMU86_OPCODE_ENCODE(0x0f7c):
	case EMU86_OPCODE_ENCODE(0x0f7d):
	case EMU86_OPCODE_ENCODE(0x0fc2):
	case EMU86_OPCODE_ENCODE(0x0fc4):
	case EMU86_OPCODE_ENCODE(0x0fc5):
	case EMU86_OPCODE_ENCODE(0x0fc6):
	case EMU86_OPCODE_ENCODE(0x0fd0):
	case EMU86_OPCODE_ENCODE(0x0fd1):
	case EMU86_OPCODE_ENCODE(0x0fd2):
	case EMU86_OPCODE_ENCODE(0x0fd3):
	case EMU86_OPCODE_ENCODE(0x0fd4):
	case EMU86_OPCODE_ENCODE(0x0fd5):
	case EMU86_OPCODE_ENCODE(0x0fd6):
	case EMU86_OPCODE_ENCODE(0x0fd7):
	case EMU86_OPCODE_ENCODE(0x0fd8):
	case EMU86_OPCODE_ENCODE(0x0fd9):
	case EMU86_OPCODE_ENCODE(0x0fda):
	case EMU86_OPCODE_ENCODE(0x0fdb):
	case EMU86_OPCODE_ENCODE(0x0fdc):
	case EMU86_OPCODE_ENCODE(0x0fdd):
	case EMU86_OPCODE_ENCODE(0x0fde):
	case EMU86_OPCODE_ENCODE(0x0fdf):
	case EMU86_OPCODE_ENCODE(0x0fe0):
	case EMU86_OPCODE_ENCODE(0x0fe1):
	case EMU86_OPCODE_ENCODE(0x0fe2):
	case EMU86_OPCODE_ENCODE(0x0fe3):
	case EMU86_OPCODE_ENCODE(0x0fe4):
	case EMU86_OPCODE_ENCODE(0x0fe5):
	case EMU86_OPCODE_ENCODE(0x0fe6):
	case EMU86_OPCODE_ENCODE(0x0fe8):
	case EMU86_OPCODE_ENCODE(0x0fe9):
	case EMU86_OPCODE_ENCODE(0x0fea):
	case EMU86_OPCODE_ENCODE(0x0feb):
	case EMU86_OPCODE_ENCODE(0x0fec):
	case EMU86_OPCODE_ENCODE(0x0fed):
	case EMU86_OPCODE_ENCODE(0x0fee):
	case EMU86_OPCODE_ENCODE(0x0fef):
	case EMU86_OPCODE_ENCODE(0x0ff0):
	case EMU86_OPCODE_ENCODE(0x0ff1):
	case EMU86_OPCODE_ENCODE(0x0ff2):
	case EMU86_OPCODE_ENCODE(0x0ff3):
	case EMU86_OPCODE_ENCODE(0x0ff4):
	case EMU86_OPCODE_ENCODE(0x0ff5):
	case EMU86_OPCODE_ENCODE(0x0ff6):
	case EMU86_OPCODE_ENCODE(0x0ff7):
	case EMU86_OPCODE_ENCODE(0x0ff8):
	case EMU86_OPCODE_ENCODE(0x0ff9):
	case EMU86_OPCODE_ENCODE(0x0ffa):
	case EMU86_OPCODE_ENCODE(0x0ffb):
	case EMU86_OPCODE_ENCODE(0x0ffc):
	case EMU86_OPCODE_ENCODE(0x0ffd):
	case EMU86_OPCODE_ENCODE(0x0ffe):
	case EMU86_OPCODE_ENCODE(0x0f3800):
	case EMU86_OPCODE_ENCODE(0x0f3801):
	case EMU86_OPCODE_ENCODE(0x0f3802):
	case EMU86_OPCODE_ENCODE(0x0f3803):
	case EMU86_OPCODE_ENCODE(0x0f3804):
	case EMU86_OPCODE_ENCODE(0x0f3805):
	case EMU86_OPCODE_ENCODE(0x0f3806):
	case EMU86_OPCODE_ENCODE(0x0f3807):
	case EMU86_OPCODE_ENCODE(0x0f3808):
	case EMU86_OPCODE_ENCODE(0x0f3809):
	case EMU86_OPCODE_ENCODE(0x0f380a):
	case EMU86_OPCODE_ENCODE(0x0f380b):
	case EMU86_OPCODE_ENCODE(0x0f380c):
	case EMU86_OPCODE_ENCODE(0x0f380d):
	case EMU86_OPCODE_ENCODE(0x0f380e):
	case EMU86_OPCODE_ENCODE(0x0f380f):
	case EMU86_OPCODE_ENCODE(0x0f3816):
	case EMU86_OPCODE_ENCODE(0x0f3817):
	case EMU86_OPCODE_ENCODE(0x0f3818):
	case EMU86_OPCODE_ENCODE(0x0f3819):
	case EMU86_OPCODE_ENCODE(0x0f381a):
	case EMU86_OPCODE_ENCODE(0x0f381b):
	case EMU86_OPCODE_ENCODE(0x0f381c):
	case EMU86_OPCODE_ENCODE(0x0f381d):
	case EMU86_OPCODE_ENCODE(0x0f381e):
	case EMU86_OPCODE_ENCODE(0x0f381f):
	case EMU86_OPCODE_ENCODE(0x0f3826):
	case EMU86_OPCODE_ENCODE(0x0f3827):
	case EMU86_OPCODE_ENCODE(0x0f3828):
	case EMU86_OPCODE_ENCODE(0x0f3829):
	case EMU86_OPCODE_ENCODE(0x0f382a):
	case EMU86_OPCODE_ENCODE(0x0f382b):
	case EMU86_OPCODE_ENCODE(0x0f382c):
	case EMU86_OPCODE_ENCODE(0x0f382d):
	case EMU86_OPCODE_ENCODE(0x0f3836):
	case EMU86_OPCODE_ENCODE(0x0f3837):
	case EMU86_OPCODE_ENCODE(0x0f3838):
	case EMU86_OPCODE_ENCODE(0x0f3839):
	case EMU86_OPCODE_ENCODE(0x0f383a):
	case EMU86_OPCODE_ENCODE(0x0f383b):
	case EMU86_OPCODE_ENCODE(0x0f383c):
	case EMU86_OPCODE_ENCODE(0x0f383d):
	case EMU86_OPCODE_ENCODE(0x0f383e):
	case EMU86_OPCODE_ENCODE(0x0f383f):
	case EMU86_OPCODE_ENCODE(0x0f3840):
	case EMU86_OPCODE_ENCODE(0x0f3841):
	case EMU86_OPCODE_ENCODE(0x0f3842):
	case EMU86_OPCODE_ENCODE(0x0f3843):
	case EMU86_OPCODE_ENCODE(0x0f3844):
	case EMU86_OPCODE_ENCODE(0x0f3845):
	case EMU86_OPCODE_ENCODE(0x0f3846):
	case EMU86_OPCODE_ENCODE(0x0f3847):
	case EMU86_OPCODE_ENCODE(0x0f384c):
	case EMU86_OPCODE_ENCODE(0x0f384d):
	case EMU86_OPCODE_ENCODE(0x0f384e):
	case EMU86_OPCODE_ENCODE(0x0f384f):
	case EMU86_OPCODE_ENCODE(0x0f3852):
	case EMU86_OPCODE_ENCODE(0x0f3853):
	case EMU86_OPCODE_ENCODE(0x0f3858):
	case EMU86_OPCODE_ENCODE(0x0f3859):
	case EMU86_OPCODE_ENCODE(0x0f385a):
	case EMU86_OPCODE_ENCODE(0x0f385b):
	case EMU86_OPCODE_ENCODE(0x0f3864):
	case EMU86_OPCODE_ENCODE(0x0f3865):
	case EMU86_OPCODE_ENCODE(0x0f3866):
	case EMU86_OPCODE_ENCODE(0x0f3875):
	case EMU86_OPCODE_ENCODE(0x0f3876):
	case EMU86_OPCODE_ENCODE(0x0f3877):
	case EMU86_OPCODE_ENCODE(0x0f3878):
	case EMU86_OPCODE_ENCODE(0x0f3879):
	case EMU86_OPCODE_ENCODE(0x0f387a):
	case EMU86_OPCODE_ENCODE(0x0f387b):
	case EMU86_OPCODE_ENCODE(0x0f387c):
	case EMU86_OPCODE_ENCODE(0x0f387d):
	case EMU86_OPCODE_ENCODE(0x0f387e):
	case EMU86_OPCODE_ENCODE(0x0f387f):
	case EMU86_OPCODE_ENCODE(0x0f3883):
	case EMU86_OPCODE_ENCODE(0x0f3888):
	case EMU86_OPCODE_ENCODE(0x0f3889):
	case EMU86_OPCODE_ENCODE(0x0f388c):
	case EMU86_OPCODE_ENCODE(0x0f388d):
	case EMU86_OPCODE_ENCODE(0x0f3896):
	case EMU86_OPCODE_ENCODE(0x0f3897):
	case EMU86_OPCODE_ENCODE(0x0f3898):
	case EMU86_OPCODE_ENCODE(0x0f3899):
	case EMU86_OPCODE_ENCODE(0x0f389a):
	case EMU86_OPCODE_ENCODE(0x0f389b):
	case EMU86_OPCODE_ENCODE(0x0f38a6):
	case EMU86_OPCODE_ENCODE(0x0f38a7):
	case EMU86_OPCODE_ENCODE(0x0f38a8):
	case EMU86_OPCODE_ENCODE(0x0f38a9):
	case EMU86_OPCODE_ENCODE(0x0f38aa):
	case EMU86_OPCODE_ENCODE(0x0f38ab):
	case EMU86_OPCODE_ENCODE(0x0f38b4):
	case EMU86_OPCODE_ENCODE(0x0f38b5):
	case EMU86_OPCODE_ENCODE(0x0f38b6):
	case EMU86_OPCODE_ENCODE(0x0f38b7):
	case EMU86_OPCODE_ENCODE(0x0f38b8):
	case EMU86_OPCODE_ENCODE(0x0f38b9):
	case EMU86_OPCODE_ENCODE(0x0f38ba):
	case EMU86_OPCODE_ENCODE(0x0f38bb):
	case EMU86_OPCODE_ENCODE(0x0f38c4):
	case EMU86_OPCODE_ENCODE(0x0f38c8):
	case EMU86_OPCODE_ENCODE(0x0f38c9):
	case EMU86_OPCODE_ENCODE(0x0f38ca):
	case EMU86_OPCODE_ENCODE(0x0f38cb):
	case EMU86_OPCODE_ENCODE(0x0f38cf):
	case EMU86_OPCODE_ENCODE(0x0f38db):
	case EMU86_OPCODE_ENCODE(0x0f38dc):
	case EMU86_OPCODE_ENCODE(0x0f38dd):
	case EMU86_OPCODE_ENCODE(0x0f38de):
	case EMU86_OPCODE_ENCODE(0x0f38df):
	case EMU86_OPCODE_ENCODE(0x0f3a00):
	case EMU86_OPCODE_ENCODE(0x0f3a01):
	case EMU86_OPCODE_ENCODE(0x0f3a02):
	case EMU86_OPCODE_ENCODE(0x0f3a03):
	case EMU86_OPCODE_ENCODE(0x0f3a04):
	case EMU86_OPCODE_ENCODE(0x0f3a05):
	case EMU86_OPCODE_ENCODE(0x0f3a06):
	case EMU86_OPCODE_ENCODE(0x0f3a08):
	case EMU86_OPCODE_ENCODE(0x0f3a09):
	case EMU86_OPCODE_ENCODE(0x0f3a0a):
	case EMU86_OPCODE_ENCODE(0x0f3a0b):
	case EMU86_OPCODE_ENCODE(0x0f3a0c):
	case EMU86_OPCODE_ENCODE(0x0f3a0d):
	case EMU86_OPCODE_ENCODE(0x0f3a0e):
	case EMU86_OPCODE_ENCODE(0x0f3a0f):
	case EMU86_OPCODE_ENCODE(0x0f3a18):
	case EMU86_OPCODE_ENCODE(0x0f3a1a):
	case EMU86_OPCODE_ENCODE(0x0f3a1e):
	case EMU86_OPCODE_ENCODE(0x0f3a1f):
	case EMU86_OPCODE_ENCODE(0x0f3a20):
	case EMU86_OPCODE_ENCODE(0x0f3a21):
	case EMU86_OPCODE_ENCODE(0x0f3a22):
	case EMU86_OPCODE_ENCODE(0x0f3a23):
	case EMU86_OPCODE_ENCODE(0x0f3a25):
	case EMU86_OPCODE_ENCODE(0x0f3a26):
	case EMU86_OPCODE_ENCODE(0x0f3a27):
	case EMU86_OPCODE_ENCODE(0x0f3a38):
	case EMU86_OPCODE_ENCODE(0x0f3a3a):
	case EMU86_OPCODE_ENCODE(0x0f3a3e):
	case EMU86_OPCODE_ENCODE(0x0f3a3f):
	case EMU86_OPCODE_ENCODE(0x0f3a40):
	case EMU86_OPCODE_ENCODE(0x0f3a41):
	case EMU86_OPCODE_ENCODE(0x0f3a42):
	case EMU86_OPCODE_ENCODE(0x0f3a43):
	case EMU86_OPCODE_ENCODE(0x0f3a44):
	case EMU86_OPCODE_ENCODE(0x0f3a46):
	case EMU86_OPCODE_ENCODE(0x0f3a4a):
	case EMU86_OPCODE_ENCODE(0x0f3a4b):
	case EMU86_OPCODE_ENCODE(0x0f3a4c):
	case EMU86_OPCODE_ENCODE(0x0f3a50):
	case EMU86_OPCODE_ENCODE(0x0f3a51):
	case EMU86_OPCODE_ENCODE(0x0f3a54):
	case EMU86_OPCODE_ENCODE(0x0f3a55):
	case EMU86_OPCODE_ENCODE(0x0f3a56):
	case EMU86_OPCODE_ENCODE(0x0f3a57):
	case EMU86_OPCODE_ENCODE(0x0f3a60):
	case EMU86_OPCODE_ENCODE(0x0f3a61):
	case EMU86_OPCODE_ENCODE(0x0f3a62):
	case EMU86_OPCODE_ENCODE(0x0f3a63):
	case EMU86_OPCODE_ENCODE(0x0f3a66):
	case EMU86_OPCODE_ENCODE(0x0f3a67):
	case EMU86_OPCODE_ENCODE(0x0f3ace):
	case EMU86_OPCODE_ENCODE(0x0f3acf):
	case EMU86_OPCODE_ENCODE(0x0f3adf):
		goto notsup_modrm_getxyzmm;
#define NEED_notsup_modrm_getxyzmm

	case EMU86_OPCODE_ENCODE(0x0f3810):
	case EMU86_OPCODE_ENCODE(0x0f3811):
	case EMU86_OPCODE_ENCODE(0x0f3812):
	case EMU86_OPCODE_ENCODE(0x0f3813):
	case EMU86_OPCODE_ENCODE(0x0f3814):
	case EMU86_OPCODE_ENCODE(0x0f3815):
	case EMU86_OPCODE_ENCODE(0x0f3820):
	case EMU86_OPCODE_ENCODE(0x0f3821):
	case EMU86_OPCODE_ENCODE(0x0f3822):
	case EMU86_OPCODE_ENCODE(0x0f3823):
	case EMU86_OPCODE_ENCODE(0x0f3824):
	case EMU86_OPCODE_ENCODE(0x0f3825):
	case EMU86_OPCODE_ENCODE(0x0f382e):
	case EMU86_OPCODE_ENCODE(0x0f382f):
	case EMU86_OPCODE_ENCODE(0x0f3830):
	case EMU86_OPCODE_ENCODE(0x0f3831):
	case EMU86_OPCODE_ENCODE(0x0f3832):
	case EMU86_OPCODE_ENCODE(0x0f3833):
	case EMU86_OPCODE_ENCODE(0x0f3834):
	case EMU86_OPCODE_ENCODE(0x0f3835):
	case EMU86_OPCODE_ENCODE(0x0f388a):
	case EMU86_OPCODE_ENCODE(0x0f388b):
	case EMU86_OPCODE_ENCODE(0x0f388e):
	case EMU86_OPCODE_ENCODE(0x0f3a14):
	case EMU86_OPCODE_ENCODE(0x0f3a15):
	case EMU86_OPCODE_ENCODE(0x0f3a16):
	case EMU86_OPCODE_ENCODE(0x0f3a17):
	case EMU86_OPCODE_ENCODE(0x0f3a19):
	case EMU86_OPCODE_ENCODE(0x0f3a1b):
	case EMU86_OPCODE_ENCODE(0x0f3a1d):
	case EMU86_OPCODE_ENCODE(0x0f3a39):
	case EMU86_OPCODE_ENCODE(0x0f3a3b):
		goto notsup_modrm_setxyzmm;
#define NEED_notsup_modrm_setxyzmm

	case EMU86_OPCODE_ENCODE(0x0f11):
	case EMU86_OPCODE_ENCODE(0x0f13):
	case EMU86_OPCODE_ENCODE(0x0f17):
	case EMU86_OPCODE_ENCODE(0x0f29):
	case EMU86_OPCODE_ENCODE(0x0f2b):
	case EMU86_OPCODE_ENCODE(0x0f7e):
	case EMU86_OPCODE_ENCODE(0x0f7f):
	case EMU86_OPCODE_ENCODE(0x0fe7):
		goto notsup_modrm_getsetxyzmm;
#define NEED_notsup_modrm_getsetxyzmm
//[[[end]]]

	/* SSE/MMX instructions. - All of these are:
	 * >> VEX+LL=0    foo xmm/m128, xmm, xmm
	 * >> VEX+LL=1    foo ymm/m256, ymm, ymm
	 * >> VEX+LL=2    foo zmm/m512, zmm, zmm
	 * >>             foo mm/m64, mm
	 * Some only exist when 66h, F2h or F3h is given, but the those prefixes don't
	 * change  the  general behavior  of  how the  opcode  is encoded  or behaves. */
#define SSE_OPERAND_SIZE_IN_BYTES()                                          \
	(!(op_flags & (EMU86_F_HASEVEX | EMU86_F_66))                            \
	 ? 8 /* MM */                                                            \
	 : (!(op_flags & EMU86_F_VEX_LL_M))                                      \
	   ? 16                                                                  \
	   : IF_64BIT(((op_flags & EMU86_F_VEX_LL_M) >= (2 << EMU86_F_VEX_LL_S)) \
	              ? 64                                                       \
	              :) 32)

#ifdef EMU86_UNSUPPORTED_MEMACCESS_IS_NOOP
#ifdef NEED_notsup_modrm_getxyzmm
#undef NEED_notsup_modrm_getxyzmm
notsup_modrm_getxyzmm:
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* NEED_notsup_modrm_getxyzmm */

#ifdef NEED_notsup_modrm_setxyzmm
#undef NEED_notsup_modrm_setxyzmm
notsup_modrm_setxyzmm:
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* NEED_notsup_modrm_setxyzmm */

#ifdef NEED_notsup_modrm_getsetxyzmm
#undef NEED_notsup_modrm_getsetxyzmm
notsup_modrm_getsetxyzmm:
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* NEED_notsup_modrm_getsetxyzmm */

#elif (defined(NEED_notsup_modrm_getxyzmm) && \
       defined(NEED_notsup_modrm_setxyzmm) && \
       defined(NEED_notsup_modrm_getsetxyzmm))
#undef NEED_notsup_modrm_getxyzmm
#undef NEED_notsup_modrm_setxyzmm
#undef NEED_notsup_modrm_getsetxyzmm
	{
		bool reading, writing;
		__IF0 {
notsup_modrm_getxyzmm:
			reading = true;
			writing = false;
		}
		__IF0 {
notsup_modrm_setxyzmm:
			reading = false;
			writing = true;
		}
		__IF0 {
notsup_modrm_getsetxyzmm:
			reading = true;
			writing = true;
		}
		MODRM_DECODE();
		if (EMU86_MODRM_ISMEM(modrm.mi_type)) {
			EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
			                            SSE_OPERAND_SIZE_IN_BYTES(),
			                            reading, writing);
		}
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
	}
#else /* All 3 */
#ifdef NEED_notsup_modrm_getxyzmm
#undef NEED_notsup_modrm_getxyzmm
notsup_modrm_getxyzmm:
	MODRM_DECODE();
	if (EMU86_MODRM_ISMEM(modrm.mi_type)) {
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            SSE_OPERAND_SIZE_IN_BYTES(),
		                            true, false);
	}
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* NEED_notsup_modrm_getxyzmm */

#ifdef NEED_notsup_modrm_setxyzmm
#undef NEED_notsup_modrm_setxyzmm
notsup_modrm_getxyzmm:
	MODRM_DECODE();
	if (EMU86_MODRM_ISMEM(modrm.mi_type)) {
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            SSE_OPERAND_SIZE_IN_BYTES(),
		                            false, true);
	}
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* NEED_notsup_modrm_setxyzmm */

#ifdef NEED_notsup_modrm_getsetxyzmm
#undef NEED_notsup_modrm_getsetxyzmm
notsup_modrm_getxyzmm:
	MODRM_DECODE();
	if (EMU86_MODRM_ISMEM(modrm.mi_type)) {
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            SSE_OPERAND_SIZE_IN_BYTES(),
		                            true, true);
	}
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* NEED_notsup_modrm_getsetxyzmm */
#endif /* Not all 3 */
#undef SSE_OPERAND_SIZE_IN_BYTES



#if !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case 0x0f77: {
	/* 0F 77                 EMMS           Set the x87 FPU tag word to empty. */
	/* VEX.256.0F.WIG 77     VZEROALL       Zero all YMM registers. */
	/* VEX.128.0F.WIG 77     VZEROUPPER     Zero upper 128 bits of all YMM registers. */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
}
#endif /* !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC */


case 0x0faa:
	/* 0F AA     RSM     Resume operation of interrupted program. */
	/* NOTE: RSM   is   only   allowed   from   system   management  mode.
	 *       Since libemu86 is not  designed to emulate that  environment,
	 *       this instruction is considered privileged from every context. */
	goto return_privileged_instruction;
#define NEED_return_privileged_instruction

#endif /* EMU86_EMULATE_CONFIG_CHECKERROR */

}
EMU86_INTELLISENSE_END
