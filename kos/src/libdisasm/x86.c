/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBDISASM_X86_C
#define GUARD_LIBDISASM_X86_C 1

#define DISABLE_BRANCH_PROFILING
#define _GNU_SOURCE                1
#define _KOS_SOURCE                1
#define LIBEMU86_CONFIG_WANT_16BIT 1
#define LIBEMU86_CONFIG_WANT_32BIT 1
#define LIBEMU86_CONFIG_WANT_64BIT 1
#define LIBEMU86_WANT_PROTOTYPES   1
#define __LIBEMU86_STATIC          1

#include "x86.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/unaligned.h>

#include <kos/kernel/types.h>
#include <kos/types.h>

#include <inttypes.h> /* PRI* */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libemu86/emu86.h>

#include "_binstr.h"
#include "x86-db.h"

DECL_BEGIN


PRIVATE char const gp_register_names8[16][5] = {
	{ '%', 'a', 'l', 0, 0 },
	{ '%', 'c', 'l', 0, 0 },
	{ '%', 'd', 'l', 0, 0 },
	{ '%', 'b', 'l', 0, 0 },
	{ '%', 'a', 'h', 0, 0 },
	{ '%', 'c', 'h', 0, 0 },
	{ '%', 'd', 'h', 0, 0 },
	{ '%', 'b', 'h', 0, 0 },
	{ '%', 'r', '8', 'l', 0 },
	{ '%', 'r', '9', 'l', 0 },
	{ '%', 'r', '1', '0', 'l' },
	{ '%', 'r', '1', '1', 'l' },
	{ '%', 'r', '1', '2', 'l' },
	{ '%', 'r', '1', '3', 'l' },
	{ '%', 'r', '1', '4', 'l' },
	{ '%', 'r', '1', '5', 'l' },
};

PRIVATE char const gp_register_names8_rex[16][5] = {
	{ '%', 'a', 'l', 0, 0 },
	{ '%', 'c', 'l', 0, 0 },
	{ '%', 'd', 'l', 0, 0 },
	{ '%', 'b', 'l', 0, 0 },
	{ '%', 's', 'p', 'l', 0 },
	{ '%', 'b', 'p', 'l', 0 },
	{ '%', 's', 'i', 'l', 0 },
	{ '%', 'd', 'i', 'l', 0 },
	{ '%', 'r', '8', 'l', 0 },
	{ '%', 'r', '9', 'l', 0 },
	{ '%', 'r', '1', '0', 'l' },
	{ '%', 'r', '1', '1', 'l' },
	{ '%', 'r', '1', '2', 'l' },
	{ '%', 'r', '1', '3', 'l' },
	{ '%', 'r', '1', '4', 'l' },
	{ '%', 'r', '1', '5', 'l' },
};

PRIVATE char const gp_register_names16[16][5] = {
	{ '%', 'a', 'x', 0, 0 },
	{ '%', 'c', 'x', 0, 0 },
	{ '%', 'd', 'x', 0, 0 },
	{ '%', 'b', 'x', 0, 0 },
	{ '%', 's', 'p', 0, 0 },
	{ '%', 'b', 'p', 0, 0 },
	{ '%', 's', 'i', 0, 0 },
	{ '%', 'd', 'i', 0, 0 },
	{ '%', 'r', '8', 'w', 0 },
	{ '%', 'r', '9', 'w', 0 },
	{ '%', 'r', '1', '0', 'w' },
	{ '%', 'r', '1', '1', 'w' },
	{ '%', 'r', '1', '2', 'w' },
	{ '%', 'r', '1', '3', 'w' },
	{ '%', 'r', '1', '4', 'w' },
	{ '%', 'r', '1', '5', 'w' },
};

PRIVATE char const gp_register_names32[17][5] = {
	{ '%', 'e', 'a', 'x', 0 },
	{ '%', 'e', 'c', 'x', 0 },
	{ '%', 'e', 'd', 'x', 0 },
	{ '%', 'e', 'b', 'x', 0 },
	{ '%', 'e', 's', 'p', 0 },
	{ '%', 'e', 'b', 'p', 0 },
	{ '%', 'e', 's', 'i', 0 },
	{ '%', 'e', 'd', 'i', 0 },
	{ '%', 'r', '8', 'd', 0 },
	{ '%', 'r', '9', 'd', 0 },
	{ '%', 'r', '1', '0', 'd' },
	{ '%', 'r', '1', '1', 'd' },
	{ '%', 'r', '1', '2', 'd' },
	{ '%', 'r', '1', '3', 'd' },
	{ '%', 'r', '1', '4', 'd' },
	{ '%', 'r', '1', '5', 'd' },
	{ '%', 'e', 'i', 'p', 0 },
};

PRIVATE char const gp_register_names64[17][4] = {
	{ '%', 'r', 'a', 'x' },
	{ '%', 'r', 'c', 'x' },
	{ '%', 'r', 'd', 'x' },
	{ '%', 'r', 'b', 'x' },
	{ '%', 'r', 's', 'p' },
	{ '%', 'r', 'b', 'p' },
	{ '%', 'r', 's', 'i' },
	{ '%', 'r', 'd', 'i' },
	{ '%', 'r', '8', 0 },
	{ '%', 'r', '9', 0 },
	{ '%', 'r', '1', '0' },
	{ '%', 'r', '1', '1' },
	{ '%', 'r', '1', '2' },
	{ '%', 'r', '1', '3' },
	{ '%', 'r', '1', '4' },
	{ '%', 'r', '1', '5' },
	{ '%', 'r', 'i', 'p' }  /* EMU86_R_RIP */
};

PRIVATE char const sreg_register_names[16][4] = {
	{ '%', 'e', 's', 0 },
	{ '%', 'c', 's', 0 },
	{ '%', 's', 's', 0 },
	{ '%', 'd', 's', 0 },
	{ '%', 'f', 's', 0 },
	{ '%', 'g', 's', 0 },
	{ '%', 's', '6', 0 },
	{ '%', 's', '7', 0 },
	{ '%', 's', '8', 0 },
	{ '%', 's', '9', 0 },
	{ '%', 's', '1', '0' },
	{ '%', 's', '1', '1' },
	{ '%', 's', '1', '2' },
	{ '%', 's', '1', '3' },
	{ '%', 's', '1', '4' },
	{ '%', 's', '1', '5' },
};

PRIVATE char const creg_register_names[16][5] = {
	{ '%', 'c', 'r', '0', 0 },
	{ '%', 'c', 'r', '1', 0 },
	{ '%', 'c', 'r', '2', 0 },
	{ '%', 'c', 'r', '3', 0 },
	{ '%', 'c', 'r', '4', 0 },
	{ '%', 'c', 'r', '5', 0 },
	{ '%', 'c', 'r', '6', 0 },
	{ '%', 'c', 'r', '7', 0 },
	{ '%', 'c', 'r', '8', 0 },
	{ '%', 'c', 'r', '9', 0 },
	{ '%', 'c', 'r', '1', '0' },
	{ '%', 'c', 'r', '1', '1' },
	{ '%', 'c', 'r', '1', '2' },
	{ '%', 'c', 'r', '1', '3' },
	{ '%', 'c', 'r', '1', '4' },
	{ '%', 'c', 'r', '1', '5' },
};

PRIVATE char const dreg_register_names[16][5] = {
	{ '%', 'd', 'r', '0', 0 },
	{ '%', 'd', 'r', '1', 0 },
	{ '%', 'd', 'r', '2', 0 },
	{ '%', 'd', 'r', '3', 0 },
	{ '%', 'd', 'r', '4', 0 },
	{ '%', 'd', 'r', '5', 0 },
	{ '%', 'd', 'r', '6', 0 },
	{ '%', 'd', 'r', '7', 0 },
	{ '%', 'd', 'r', '8', 0 },
	{ '%', 'd', 'r', '9', 0 },
	{ '%', 'd', 'r', '1', '0' },
	{ '%', 'd', 'r', '1', '1' },
	{ '%', 'd', 'r', '1', '2' },
	{ '%', 'd', 'r', '1', '3' },
	{ '%', 'd', 'r', '1', '4' },
	{ '%', 'd', 'r', '1', '5' },
};

PRIVATE char const treg_register_names[16][5] = {
	{ '%', 't', 'r', '0', 0 },
	{ '%', 't', 'r', '1', 0 },
	{ '%', 't', 'r', '2', 0 },
	{ '%', 't', 'r', '3', 0 },
	{ '%', 't', 'r', '4', 0 },
	{ '%', 't', 'r', '5', 0 },
	{ '%', 't', 'r', '6', 0 },
	{ '%', 't', 'r', '7', 0 },
	{ '%', 't', 'r', '8', 0 },
	{ '%', 't', 'r', '9', 0 },
	{ '%', 't', 'r', '1', '0' },
	{ '%', 't', 'r', '1', '1' },
	{ '%', 't', 'r', '1', '2' },
	{ '%', 't', 'r', '1', '3' },
	{ '%', 't', 'r', '1', '4' },
	{ '%', 't', 'r', '1', '5' },
};

PRIVATE char const bnd_register_names[16][6] = {
	{ '%', 'b', 'n', 'd', '0', 0 },
	{ '%', 'b', 'n', 'd', '1', 0 },
	{ '%', 'b', 'n', 'd', '2', 0 },
	{ '%', 'b', 'n', 'd', '3', 0 },
	{ '%', 'b', 'n', 'd', '4', 0 },
	{ '%', 'b', 'n', 'd', '5', 0 },
	{ '%', 'b', 'n', 'd', '6', 0 },
	{ '%', 'b', 'n', 'd', '7', 0 },
	{ '%', 'b', 'n', 'd', '8', 0 },
	{ '%', 'b', 'n', 'd', '9', 0 },
	{ '%', 'b', 'n', 'd', '1', '0' },
	{ '%', 'b', 'n', 'd', '1', '1' },
	{ '%', 'b', 'n', 'd', '1', '2' },
	{ '%', 'b', 'n', 'd', '1', '3' },
	{ '%', 'b', 'n', 'd', '1', '4' },
	{ '%', 'b', 'n', 'd', '1', '5' },
};

PRIVATE char const sti_register_names[16][7] = {
	{ '%', 's', 't', '(', '0', ')', 0 },
	{ '%', 's', 't', '(', '1', ')', 0 },
	{ '%', 's', 't', '(', '2', ')', 0 },
	{ '%', 's', 't', '(', '3', ')', 0 },
	{ '%', 's', 't', '(', '4', ')', 0 },
	{ '%', 's', 't', '(', '5', ')', 0 },
	{ '%', 's', 't', '(', '6', ')', 0 },
	{ '%', 's', 't', '(', '7', ')', 0 },
	{ '%', 's', 't', '(', '8', ')', 0 },
	{ '%', 's', 't', '(', '9', ')', 0 },
	{ '%', 's', 't', '(', '1', '0', ')' },
	{ '%', 's', 't', '(', '1', '1', ')' },
	{ '%', 's', 't', '(', '1', '2', ')' },
	{ '%', 's', 't', '(', '1', '3', ')' },
	{ '%', 's', 't', '(', '1', '4', ')' },
	{ '%', 's', 't', '(', '1', '5', ')' },
};

PRIVATE char const segment_prefix[][4] = {
	{ '%', 'e', 's', ':' },
	{ '%', 'c', 's', ':' },
	{ '%', 's', 's', ':' },
	{ '%', 'd', 's', ':' },
	{ '%', 'f', 's', ':' },
	{ '%', 'g', 's', ':' },
};




PRIVATE void CC
da_print_reg8(struct disassembler *__restrict self, u8 regno, emu86_opflags_t flags) {
	char const *name = gp_register_names8[regno & 15];
	if (flags & EMU86_F_HASREX)
		name = gp_register_names8_rex[regno & 15];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[4] ? 5 : name[3] ? 4 : 3);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_reg16(struct disassembler *__restrict self, u8 regno) {
	char const *name = gp_register_names16[regno & 15];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[4] ? 5 : name[3] ? 4 : 3);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_reg32(struct disassembler *__restrict self, u8 regno) {
	char const *name;
	name = gp_register_names32[regno <= EMU86_R_RIP ? regno : (regno & 15)];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[4] ? 5 : 4);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_reg64(struct disassembler *__restrict self, u8 regno) {
	char const *name;
	name = gp_register_names64[regno <= EMU86_R_RIP ? regno : (regno & 15)];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[3] ? 4 : 3);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_sreg(struct disassembler *__restrict self, u8 regno) {
	char const *name = sreg_register_names[regno & 15];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[3] ? 4 : 3);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_creg(struct disassembler *__restrict self, u8 regno) {
	char const *name = creg_register_names[regno & 15];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[4] ? 5 : 4);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_dreg(struct disassembler *__restrict self, u8 regno) {
	char const *name = dreg_register_names[regno & 15];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[4] ? 5 : 4);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_treg(struct disassembler *__restrict self, u8 regno) {
	char const *name = treg_register_names[regno & 15];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[4] ? 5 : 4);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_regno31_str(char name[2], u8 regno) {
	regno &= 31;
	if (regno >= 10) {
		name[0] = itoa_decimal(regno / 10);
		name[1] = itoa_decimal(regno % 10);
	} else {
		name[0] = itoa_decimal(regno);
		name[1] = 0;
	}
}

PRIVATE void CC
da_print_mmreg(struct disassembler *__restrict self, u8 regno) {
	char name[5];
	name[0] = '%';
	name[1] = 'm';
	name[2] = 'm';
	da_regno31_str(&name[3], regno);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[4] ? 5 : 4);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_kreg(struct disassembler *__restrict self, u8 regno) {
	char name[5];
	name[0] = '%';
	name[1] = 'k';
	name[2] = itoa_decimal(regno & 7);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, 3);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

#define da_print_xmmreg(self, regno) da_print_Xmmreg(self, regno, 'x')
#define da_print_ymmreg(self, regno) da_print_Xmmreg(self, regno, 'y')
#define da_print_zmmreg(self, regno) da_print_Xmmreg(self, regno, 'z')
PRIVATE void CC
da_print_Xmmreg(struct disassembler *__restrict self, u8 regno, char x) {
	char name[6];
	name[0] = '%';
	name[1] = x;
	name[2] = 'm';
	name[3] = 'm';
	da_regno31_str(&name[4], regno);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[5] ? 6 : 5);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}
PRIVATE void CC
da_print_Xmmmask(struct disassembler *__restrict self, emu86_opflags_t flags) {
	if ((flags & EMU86_F_EVEX_aaa_M) != 0) {
		disasm_print(self, "{", 1);
		da_print_kreg(self, EMU86_F_EVEX_aaa(flags));
		disasm_print(self, "}", 1);
	}
	if (flags & EMU86_F_EVEX_z) {
		disasm_print(self, "{", 1);
		disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_PREFIX);
		disasm_print(self, "z", 1);
		disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_SUFFIX);
		disasm_print(self, "}", 1);
	}
}

PRIVATE void CC
da_print_bndreg(struct disassembler *__restrict self, u8 regno) {
	char const *name = bnd_register_names[regno & 15];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[5] ? 6 : 5);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_stireg(struct disassembler *__restrict self, u8 regno) {
	char const *name = sti_register_names[regno & 15];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[6] ? 7 : 6);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_modrm_rm_memory(struct disassembler *__restrict self,
                         struct emu86_modrm const *__restrict rm,
                         emu86_opflags_t flags) {
	bool has_register;
	if (EMU86_F_HASSEG(flags))
		disasm_print(self, segment_prefix[EMU86_F_SEGREG(flags)], 4);
	has_register = rm->mi_rm != 0xff || rm->mi_index != 0xff;
	if (rm->mi_offset || !has_register) {
		s32 offset;
		disasm_print_format(self, DISASSEMBLER_FORMAT_OFFSET_PREFIX);
		offset = rm->mi_offset;
		/* Only render small negative  offsets as actually being  negative.
		 * Very large offsets are probably absolute pointers, unless a base
		 * register is given. In that  case, always render negative  number
		 * as actually being negative! */
		if (offset < 0 && (rm->mi_rm != 0xff
		                   ? offset != INT32_MIN /* Special case for INT32_MIN (always render as being positive) */
		                   : offset > INT16_MIN)) {
			if (offset >= INT8_MIN) {
				disasm_printf(self, "-%" PRIu32, (u32)-offset);
			} else {
				disasm_printf(self, "-%#" PRIx32, (u32)-offset);
			}
		} else {
			if ((u32)offset <= INT8_MAX) {
				/* Render small, positive numbers as decimals, rather than hex. */
				disasm_printf(self, "%" PRIu32, (u32)offset);
			} else {
				disasm_printf(self, "%#" PRIxPTR,
				              (uintptr_t)(intptr_t)offset);
			}
		}
		disasm_print_format(self, DISASSEMBLER_FORMAT_OFFSET_SUFFIX);
	}
	if (has_register) {
		disasm_print(self, "(", 1);
		if (rm->mi_rm != 0xff) {
			if (DA86_IS64(self)) {
				if (flags & EMU86_F_67)
					goto do_print_base32;
				da_print_reg64(self, rm->mi_rm);
			} else if (DA86_IS32(self) ^ ((flags & EMU86_F_67) != 0)) {
			do_print_base32:
				da_print_reg32(self, rm->mi_rm);
			} else {
				da_print_reg16(self, rm->mi_rm);
			}
		}
		if (rm->mi_index != 0xff) {
			disasm_print(self, ",", 1);
			if (DA86_IS64(self)) {
				if (flags & EMU86_F_67)
					goto do_print_index32;
				da_print_reg64(self, rm->mi_index);
			} else if (DA86_IS32(self) ^ ((flags & EMU86_F_67) != 0)) {
do_print_index32:
				da_print_reg32(self, rm->mi_index);
			} else {
				da_print_reg16(self, rm->mi_index);
			}
			disasm_print(self, ",", 1);
			disasm_print_format(self, DISASSEMBLER_FORMAT_SCALE_PREFIX);
			disasm_printf(self, "%u", 1 << rm->mi_shift);
			disasm_print_format(self, DISASSEMBLER_FORMAT_SCALE_SUFFIX);
		}
		disasm_print(self, ")", 1);
	}
}

PRIVATE void CC
da_print_modrm_rm(struct disassembler *__restrict self,
                  struct emu86_modrm const *__restrict rm,
                  emu86_opflags_t flags, unsigned int size) {
	if (EMU86_MODRM_ISREG(rm->mi_type)) {
		if (size == 8)
			da_print_reg64(self, rm->mi_rm);
		else if (size == 4)
			da_print_reg32(self, rm->mi_rm);
		else if (size == 2)
			da_print_reg16(self, rm->mi_rm);
		else {
			da_print_reg8(self, rm->mi_rm, flags);
		}
	} else {
		da_print_modrm_rm_memory(self, rm, flags);
	}
}

PRIVATE void CC
da_print_modrm_rm64_mm(struct disassembler *__restrict self,
                       struct emu86_modrm const *__restrict rm,
                       emu86_opflags_t flags) {
	if (EMU86_MODRM_ISREG(rm->mi_type)) {
		da_print_mmreg(self, rm->mi_rm);
	} else {
		da_print_modrm_rm_memory(self, rm, flags);
	}
}

#define da_print_modrm_rm128_xmm(self, rm, flag) da_print_modrm_rmNNN_Xmm(self, rm, flag, 'x')
#define da_print_modrm_rm256_ymm(self, rm, flag) da_print_modrm_rmNNN_Xmm(self, rm, flag, 'y')
#define da_print_modrm_rm512_zmm(self, rm, flag) da_print_modrm_rmNNN_Xmm(self, rm, flag, 'z')
PRIVATE void CC
da_print_modrm_rmNNN_Xmm(struct disassembler *__restrict self,
                         struct emu86_modrm const *__restrict rm,
                         emu86_opflags_t flags, char x) {
	if (EMU86_MODRM_ISREG(rm->mi_type)) {
		da_print_Xmmreg(self, rm->mi_rm, x);
	} else {
		da_print_modrm_rm_memory(self, rm, flags);
	}
}






#ifdef CONFIG_LIBDISASM_X86_AUTOSELECT_JCC
PRIVATE ATTR_CONST bool CC
is_carry_instruction(u32 opcode, u8 reg) {
	switch (opcode) {

	case EMU86_OPCODE_ENCODE(0xc0):
	case EMU86_OPCODE_ENCODE(0xc1):
	case EMU86_OPCODE_ENCODE(0xd0):
	case EMU86_OPCODE_ENCODE(0xd1):
	case EMU86_OPCODE_ENCODE(0xd2):
	case EMU86_OPCODE_ENCODE(0xd3):
	case EMU86_OPCODE_ENCODE(0x0fa3):
	case EMU86_OPCODE_ENCODE(0x0fa4):
	case EMU86_OPCODE_ENCODE(0x0fa5):
	case EMU86_OPCODE_ENCODE(0x0fab):
	case EMU86_OPCODE_ENCODE(0x0fac):
	case EMU86_OPCODE_ENCODE(0x0fad):
	case EMU86_OPCODE_ENCODE(0x0fb3):
	case EMU86_OPCODE_ENCODE(0x0fba):
	case EMU86_OPCODE_ENCODE(0x0fbb):
	case EMU86_OPCODE_ENCODE(0x0fbc):
	case EMU86_OPCODE_ENCODE(0x0ff7):
	case EMU86_OPCODE_ENCODE(0x00):
	case EMU86_OPCODE_ENCODE(0x01):
	case EMU86_OPCODE_ENCODE(0x02):
	case EMU86_OPCODE_ENCODE(0x03):
	case EMU86_OPCODE_ENCODE(0x04):
	case EMU86_OPCODE_ENCODE(0x05):
	case EMU86_OPCODE_ENCODE(0x10):
	case EMU86_OPCODE_ENCODE(0x11):
	case EMU86_OPCODE_ENCODE(0x12):
	case EMU86_OPCODE_ENCODE(0x13):
	case EMU86_OPCODE_ENCODE(0x14):
	case EMU86_OPCODE_ENCODE(0x15):
	case EMU86_OPCODE_ENCODE(0x18):
	case EMU86_OPCODE_ENCODE(0x19):
	case EMU86_OPCODE_ENCODE(0x1a):
	case EMU86_OPCODE_ENCODE(0x1b):
	case EMU86_OPCODE_ENCODE(0x1c):
	case EMU86_OPCODE_ENCODE(0x1d):
	case EMU86_OPCODE_ENCODE(0x28):
	case EMU86_OPCODE_ENCODE(0x29):
	case EMU86_OPCODE_ENCODE(0x2a):
	case EMU86_OPCODE_ENCODE(0x2b):
	case EMU86_OPCODE_ENCODE(0x2c):
	case EMU86_OPCODE_ENCODE(0x2d):
		return true;

	case EMU86_OPCODE_ENCODE(0x80):
	case EMU86_OPCODE_ENCODE(0x81):
	case EMU86_OPCODE_ENCODE(0x82):
	case EMU86_OPCODE_ENCODE(0x83):
		return reg == 0 || reg == 2 ||
		       reg == 3 || reg == 5;

	default: break;
	}
	return false;
}

PRIVATE ATTR_CONST bool CC
is_compare_instruction(u32 opcode, u8 reg) {
	switch (opcode) {

	case EMU86_OPCODE_ENCODE(0x38):
	case EMU86_OPCODE_ENCODE(0x39):
	case EMU86_OPCODE_ENCODE(0x3a):
	case EMU86_OPCODE_ENCODE(0x3b):
	case EMU86_OPCODE_ENCODE(0x3c):
	case EMU86_OPCODE_ENCODE(0x3d):
	case EMU86_OPCODE_ENCODE(0xa6):
	case EMU86_OPCODE_ENCODE(0xa7):
		return true;

	case EMU86_OPCODE_ENCODE(0x80):
	case EMU86_OPCODE_ENCODE(0x81):
	case EMU86_OPCODE_ENCODE(0x82):
	case EMU86_OPCODE_ENCODE(0x83):
		return reg == 7;

	default:
		break;
	}
	return false;
}

INTERN NONNULL((1)) void CC
libda_select_jcc(struct disassembler *__restrict self,
                 unsigned int which) {
	char const *repr;
	switch (which) {

	case 0x2: /* "[b|c|nae]" */
	case 0x3: /* "[ae|nb|nc]" */
		repr = which == 0x2 ? "b" : "ae";
		if (is_carry_instruction((u32)(uintptr_t)self->d_pad1[0],
		                         (u8)(uintptr_t)self->d_pad1[1]))
			repr = which == 0x2 ? "c" : "nc"; /* use carry/not-carray after carry instructions */
		break;

	case 0x4: /* "[z|e]" */
	case 0x5: /* "[nz|ne]" */
		repr = which == 0x4 ? "z" : "nz";
		if (is_compare_instruction((u32)(uintptr_t)self->d_pad1[0],
		                           (u8)(uintptr_t)self->d_pad1[1]))
			repr = which == 0x4 ? "e" : "ne"; /* use equal/not-equal after compare instructions */
		break;

	case 0x6: /* "[be|na]" */
		repr = "be";
		break;

	case 0x7: /* "[a|nbe]" */
		repr = "a";
		break;

	case 0xa: /* "[p|pe]" */
		repr = "p";
		break;

	case 0xb: /* "[np|po]" */
		repr = "np";
		break;

	case 0xc: /* "[l|nge]" */
		repr = "l";
		break;

	case 0xd: /* "[ge|nl]" */
		repr = "ge";
		break;

	case 0xe: /* "[le|ng]" */
		repr = "le";
		break;

	case 0xf: /* "[g|nle]" */
		repr = "g";
		break;

	default:
		return;
	}
	disasm_print(self, repr, strlen(repr));
}
#endif /* CONFIG_LIBDISASM_X86_AUTOSELECT_JCC */

#ifdef __GNUC__
/* GCC  emits  a false  warning about  `self->d_pad1[0] = (void *)(uintptr_t)whole_opcode' supposedly
 * using  the uninitialized variable `opcode'. Now mind you that this isn't a typo. - That expression
 * is neither using  the variable `opcode',  nor is opcode  uninitialized at the  time that piece  of
 * code is reached, nor is this is the first time that `opcode' is accessed within any of the control
 * paths that lead to said statement. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif /* __GNUC__ */


INTERN NONNULL((1)) void CC
libda_single_x86(struct disassembler *__restrict self) {
#ifdef CONFIG_LIBDISASM_X86_AUTOSELECT_JCC
	emu86_opcode_t whole_opcode;
#endif /* CONFIG_LIBDISASM_X86_AUTOSELECT_JCC */
	emu86_opcode_t opcode;
	emu86_opflags_t op_flags;
	byte_t const *text_start = self->d_pc;
	byte_t const *args_start = NULL;
	struct instruction const *chain;
	struct emu86_modrm rm;
	bzero(&rm, sizeof(rm));
	switch (self->d_target) {
	case DISASSEMBLER_TARGET_8086:
		op_flags = EMU86_F_NORMAL | EMU86_F_16BIT;
		break;
	case DISASSEMBLER_TARGET_I386:
		op_flags = EMU86_F_NORMAL | EMU86_F_32BIT;
		break;
	case DISASSEMBLER_TARGET_X86_64:
		op_flags = EMU86_F_NORMAL | EMU86_F_64BIT;
		break;
	default: __builtin_unreachable();
	}
	self->d_pc = emu86_opcode_decode(self->d_pc, &opcode, &op_flags);
#ifdef CONFIG_LIBDISASM_X86_AUTOSELECT_JCC
	whole_opcode = opcode;
#endif /* CONFIG_LIBDISASM_X86_AUTOSELECT_JCC */
	/* Print the instruction. */
	if (opcode < EMU86_OPCODE_BASE0f) {
#if EMU86_OPCODE_BASE0 != 0
		opcode &= 0xff;
#endif /* EMU86_OPCODE_BASE0 != 0 */
		chain = ops;
#ifdef HAVE_OPS_OFFSETS
		chain += ops_offsets[opcode];
#endif /* HAVE_OPS_OFFSETS */
	} else if (opcode < EMU86_OPCODE_BASE0f38) {
		opcode &= 0xff;
		chain = ops_0f;
#ifdef HAVE_OPS_0F_OFFSETS
		chain += ops_0f_offsets[opcode];
#endif /* HAVE_OPS_0F_OFFSETS */
	} else if (opcode < EMU86_OPCODE_BASE0f3a) {
		opcode &= 0xff;
		chain = ops_0f38;
#ifdef HAVE_OPS_0F38_OFFSETS
		chain += ops_0f38_offsets[opcode];
#endif /* HAVE_OPS_0F38_OFFSETS */
	} else {
		if unlikely(opcode >= EMU86_OPCODE_BASE0f3a + 0x100)
			goto unknown_opcode;
		opcode &= 0xff;
		chain = ops_0f3a;
#ifdef HAVE_OPS_0F3A_OFFSETS
		chain += ops_0f3a_offsets[opcode];
#endif /* HAVE_OPS_0F3A_OFFSETS */
	}
search_chain:
	for (;; ++chain) {
		if (chain->i_opcode != opcode) {
			if (chain->i_opcode > opcode) {
				/* Opcodes are always  sorted ascendingly, so  if the  encountered
				 * code is greater than ours, then we know that we've already went
				 * past what we were looking for. */
				break;
			}
			if (!chain->i_opcode)
				break; /* End-of-chain reached. */
			continue;
		}
		if (((chain->i_flags & IF_REXW) != 0) !=
		    ((op_flags & EMU86_F_REX_W) != 0))
			continue;
		if (DA86_IS16(self)) {
			/* The 0x66 prefix acts inverted on 16-bit mode.
			 * As such, instruction _with_ the prefix are used by default,
			 * whilst instruction _without_ the prefix are used any  other
			 * time (thus not breaking instructions that don't care  about
			 * the prefix at all). */
			if ((chain->i_flags & IF_66) && (op_flags & EMU86_F_66))
				continue;
			if ((chain->i_flags & IF_67) && (op_flags & EMU86_F_67))
				continue;
		} else {
			/* Do an exact match for the 0x66 prefix due to it being a
			 * so-called mandatory prefix, that also modifies the name
			 * of an instruction when ATnT representation is printed. */
			if (((chain->i_flags & IF_66) != 0) != ((op_flags & EMU86_F_66) != 0))
				continue;
			if ((chain->i_flags & IF_67) && !(op_flags & EMU86_F_67))
				continue;
		}
		if (((chain->i_flags & IF_F2) != 0) !=
		    ((op_flags & EMU86_F_f2) != 0))
			continue;
		if (((chain->i_flags & IF_F3) != 0) !=
		    ((op_flags & EMU86_F_f3) != 0))
			continue;
		if ((chain->i_flags & IF_REXB) == IF_REXB) {
			if (!(op_flags & EMU86_F_REX_B))
				continue;
		} else if (chain->i_flags & (IF_X32 | IF_X64)) {
			if (chain->i_flags & IF_X32) {
				if (DA86_IS64(self))
					continue;
			} else {
				if (!DA86_IS64(self))
					continue;
			}
		}
		if ((chain->i_flags & IF_BYTE2) == IF_BYTE2) {
			if (args_start) {
				self->d_pc = args_start;
				args_start = NULL;
			}
			if (self->d_pc[0] != (byte_t)chain->i_repr[0])
				continue;
			++self->d_pc;
		} else {
			if (chain->i_flags & IF_VEX) {
				if (!(op_flags & EMU86_F_HASVEX))
					continue;
				if ((chain->i_flags & IF_VEX) == IF_VEX) {
					byte_t f = (byte_t)chain->i_repr[0];
					if ((f & IF_VEX_B0_LIG) != IF_VEX_B0_LIG) {
						if (op_flags & EMU86_F_EVEX_b) {
							/* When EVEX.b is set, then a 512-bit vector size is implied,
							 * SAE is enabled, and VEX.LL  is used as a rounding  control
							 * indicator, as displayed by `OP_ER' and `OP_SAE' */
							if ((f & IF_VEX_B0_LL_M) != 2 << IF_VEX_B0_LL_S)
								continue; /* Different length value */
						} else {
							if (EMU86_F_VEX_LL(op_flags) != IF_VEX_B0_LL(f))
								continue; /* Different length value */
						}
					}
					if ((f & IF_VEX_B0_NOEVEX) && (op_flags & EMU86_F_HASEVEX))
						continue; /* Require that no EVEX prefix was used. */
					if (!(f & IF_VEX_B0_WIG)) {
						if (!!(f & IF_VEX_B0_W) != !!(op_flags & EMU86_F_VEX_W))
							continue; /* Different width value */
					}
				} else {
					if (!!(chain->i_flags & IF_VEXW1) != !!(op_flags & EMU86_F_VEX_W))
						continue;
				}
			}
			if (chain->i_flags & IF_MODRM) {
				if (!args_start) {
					args_start = self->d_pc;
					self->d_pc = emu86_modrm_decode(args_start, &rm, op_flags);
				}
				if (chain->i_flags & IF_REG0) {
					if (rm.mi_reg != (chain->i_flags & 7))
						continue;
				}
				if ((chain->i_flags & IF_RMM) &&
				    (EMU86_MODRM_ISREG(rm.mi_type)))
					continue;
			} else if (args_start) {
				self->d_pc = args_start;
			}
		}
		/* Got it! */
		{
			char const *start;
			char const *p;
			char ch;
			bool is_first = true;
			start         = chain->i_repr;
			if ((chain->i_flags & IF_BYTE2) == IF_BYTE2 ||
			    (chain->i_flags & IF_VEX) == IF_VEX)
				++start;
			if (*start == OPC_LONGREPR) {
				/* Extended-length opcode representation. */
				u16 offset = UNALIGNED_GET16((u16 const *)(start + 1));
				start = longops_repr + offset;
			}
			p = strchrnul(start, '\t');
			if (*p)
				++p;
			disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_PREFIX);
			if (op_flags & EMU86_F_LOCK)
				disasm_print(self, "lock ", 5);
			{
#ifdef CONFIG_LIBDISASM_X86_AUTOSELECT_JCC
				char const *sel_start;
again_instruction_part:
				sel_start = (char *)memchr(start, '[', (size_t)(p - start));
				if (sel_start && (sel_start + 2) < p && sel_start[2] == ']') {
					unsigned int which;
					if (sel_start[1] >= '0' && sel_start[1] <= '9')
						which = (unsigned int)(sel_start[1] - '0');
					else if (sel_start[1] >= 'a' && sel_start[1] <= 'z')
						which = 10u + (unsigned int)(sel_start[1] - 'a');
					else if (sel_start[1] >= 'A' && sel_start[1] <= 'Z')
						which = 10u + (unsigned int)(sel_start[1] - 'A');
					else {
						goto no_jcc_sel;
					}
					disasm_print(self, start,
					             (size_t)(sel_start - start));
					libda_select_jcc(self, which);
					start = sel_start + 3;
					goto again_instruction_part;
				}
no_jcc_sel:
#endif /* CONFIG_LIBDISASM_X86_AUTOSELECT_JCC */
				disasm_print(self, start,
				             (size_t)(p - start));
			}
			disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_SUFFIX);
			for (;;) {
				ch = *p++;
				if (!ch)
					goto done_operands;
				if (!is_first)
					disasm_print(self, ", ", 2);
				is_first = false;
do_nextop_nocomma:
				switch (ch) {
#define VEX_VVVVV() EMU86_F_VEX_VVVVV(op_flags)

				case OPC_RM8:
					da_print_modrm_rm(self, &rm, op_flags, 1);
					break;

				case OPC_RM16:
					da_print_modrm_rm(self, &rm, op_flags, 2);
					break;

				case OPC_RM32:
					da_print_modrm_rm(self, &rm, op_flags, 4);
					break;

				case OPC_RM64:
					da_print_modrm_rm(self, &rm, op_flags, 8);
					break;

				case OPC_XRM16:
					disasm_print(self, "*", 1);
					da_print_modrm_rm(self, &rm, op_flags, 2);
					break;

				case OPC_XRM32:
					disasm_print(self, "*", 1);
					da_print_modrm_rm(self, &rm, op_flags, 4);
					break;

				case OPC_XRM64:
					disasm_print(self, "*", 1);
					da_print_modrm_rm(self, &rm, op_flags, 8);
					break;

				case OPC_RMBND:
					if (EMU86_MODRM_ISREG(rm.mi_type)) {
						da_print_bndreg(self, rm.mi_rm);
					} else {
						da_print_modrm_rm(self, &rm, op_flags, DA86_IS64(self) ? 16 : 8);
					}
					break;

				case OPC_RMBND_RANGE:
					if (EMU86_MODRM_ISREG(rm.mi_type) ||
					    rm.mi_index == 0xff ||
					    rm.mi_rm == 0xff) {
						disasm_print(self, "??" "? /*", 6);
						da_print_modrm_rm(self, &rm, op_flags, DA86_IS64(self) ? 8 : 4);
						disasm_print(self, "*/", 2);
					} else if (DA86_IS64(self)) {
						da_print_reg64(self, rm.mi_rm);
						disasm_print(self, ":", 1);
						da_print_reg64(self, rm.mi_index);
					} else {
						da_print_reg32(self, rm.mi_rm);
						disasm_print(self, ":", 1);
						da_print_reg32(self, rm.mi_index);
					}
					break;

				case OPC_RMSTi:
					if (EMU86_MODRM_ISREG(rm.mi_type)) {
						da_print_stireg(self, rm.mi_rm);
					} else {
						da_print_modrm_rm(self, &rm, op_flags, DA86_IS64(self) ? 16 : 8);
					}
					break;

				case OPC_S8:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#tx", (ptrdiff_t)(*(s8 const *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 1;
					break;

				case OPC_U8:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#" PRIx8, *(u8 const *)self->d_pc);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 1;
					break;

				case OPC_S16:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#tx", (ptrdiff_t)(s16)UNALIGNED_GET16((u16 const *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 2;
					break;

				case OPC_U16:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#" PRIx16, UNALIGNED_GET16((u16 const *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 2;
					break;

				case OPC_S32:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#tx", (ptrdiff_t)(s32)UNALIGNED_GET32((u32 const *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 4;
					break;

				case OPC_U32:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#" PRIx32, UNALIGNED_GET32((u32 const *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 4;
					break;

				case OPC_U64:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#" PRIx64, UNALIGNED_GET64((u64 const *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 8;
					break;

				case OPC_SHORT: {
					PRIVATE char const conv_table2[] = { 'a', 'c', 'd', 'b', 's', 'b', 's', 'd' };
					PRIVATE char const conv_table3[] = { 'x', 'x', 'p', 'i' };
					char regname[COMPILER_STRLEN("%st(0)")];
					char name = *p++;
					unsigned int reglen;
					regname[0] = '%';
					if (name >= '0' && name <= '7') {
						regname[1] = 's';
						regname[2] = 't';
						regname[3] = '(';
						regname[4] = name;
						regname[5] = ')';
						reglen = 6;
					} else if (name >= 'A' && name <= 'H') {
						/* %ax, %cx, %dx, %bx, %sp, %bp, %di, %si */
						regname[1] = conv_table2[name - 'A'];
						regname[2] = conv_table3[(name - 'A') >> 1];
						reglen = 3;
					} else if (name >= 'K' && name <= 'Z') {
						regname[1] = 'r';
						if (name >= 'O') {
							regname[2] = '1';
							regname[3] = itoa_decimal((uint8_t)(name - 'O') >> 1);
							regname[4] = (name - 'K') & 1 ? 'd' : 'w';
							reglen = 5;
						} else {
							regname[2] = itoa_decimal(8 + ((uint8_t)(name - 'K') >> 1));
							regname[3] = (name - 'K') & 1 ? 'd' : 'w';
							reglen = 4;
						}
					} else if (name >= 'k' && name <= 'z') {
						/* %eax, %ecx, %edx, %ebx, %esp, %ebp, %edi, %esi */
						/* %rax, %rcx, %rdx, %rbx, %rsp, %rbp, %rdi, %rsi */
						unsigned int index = (unsigned int)((name - 'k') & 7);
						regname[1] = name >= 's' ? 'r' : 'e';
						regname[2] = conv_table2[index];
						regname[3] = conv_table3[index >> 1];
						reglen     = 4;
					} else if (name >= OP_GP16_MIN && name <= OP_GP16_MAX) {
						/* %al, %cl, %dl, %bl, %(ah|spl), %(ch|bpl), %(dh|dil), %(bh|sil) */
						if (name >= (OP_GP16_MIN + 4) && (op_flags & EMU86_F_HASREX)) {
							unsigned int index;
							index      = (unsigned int)(name - OP_GP16_MIN);
							regname[1] = conv_table2[index];
							regname[2] = conv_table3[index >> 1];
							regname[3] = 'l';
							reglen     = 4;
						} else {
							regname[1] = conv_table2[(name - OP_GP16_MIN) & 3];
							regname[2] = (name >= (OP_GP16_MIN + 4)) ? 'h' : 'l';
							reglen     = 3;
						}
					} else if (name >= OP_X64_RN_MIN && name <= OP_X64_RN_MAX) {
						/* %r8 - %r15 */
						regname[1] = 'r';
						if (name >= OP_X64_RN_MIN + 2) {
							regname[2] = '1';
							regname[3] = itoa_decimal(name - (OP_X64_RN_MIN + 2));
							reglen = 4;
						} else {
							regname[2] = itoa_decimal(8 + (name - OP_X64_RN_MIN));
							reglen = 3;
						}
					} else if (name == 'a' || name == 'b' || name == 'c') {
						unsigned int i, n;
						/* OP_PAX / OP_PAX_PCX / OP_PAX_PCX_PDX */
						n = 1 + (name - 'a');
						if (!DA86_IS64(self) && (DA86_IS16(self) ^ ((op_flags & EMU86_F_66) != 0))) {
							regname[2] = 'x';
							for (i = 0; i < n; ++i) {
								regname[1] = conv_table2[i];
								if (i != 0)
									disasm_print(self, ", ", 2);
								disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
								disasm_print(self, regname, 3);
								disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
							}
						} else {
							regname[1] = DA86_IS64(self) ? 'r' : 'e';
							regname[3] = 'x';
							for (i = 0; i < n; ++i) {
								regname[2] = conv_table2[i];
								if (i != 0)
									disasm_print(self, ", ", 2);
								disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
								disasm_print(self, regname, 4);
								disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
							}
						}
						goto done_escape_register;
					} else if (name == 'd') { /* OP_PSI */
						if (!DA86_IS64(self) && (DA86_IS16(self) ^ ((op_flags & EMU86_F_66) != 0))) {
							regname[1] = 's';
							regname[2] = 'i';
							reglen = 3;
						} else {
							regname[1] = DA86_IS64(self) ? 'r' : 'e';
							regname[2] = 's';
							regname[3] = 'i';
							reglen = 4;
						}
					} else {
						/* Unused... */
						regname[0] = '?';
						reglen     = 1;
					}
					disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
					disasm_print(self, regname, reglen);
					disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
done_escape_register:
					;
				}	break;

				case OPC_MOFFS8: {
					uintptr_t addr;
					addr = (uintptr_t)(*(u8 const *)self->d_pc);
					self->d_pc += 1;
					goto do_print_moffs;
				case OPC_MOFFS16:
					addr = (uintptr_t)UNALIGNED_GET16((u16 const *)self->d_pc);
					self->d_pc += 2;
					goto do_print_moffs;
				case OPC_MOFFS32:
					addr = (uintptr_t)UNALIGNED_GET32((u32 const *)self->d_pc);
					self->d_pc += 4;
					goto do_print_moffs;
				case OPC_MOFFS64:
					addr = (uintptr_t)UNALIGNED_GET64((u64 const *)self->d_pc);
					self->d_pc += 8;
do_print_moffs:
					if (EMU86_F_HASSEG(op_flags))
						disasm_print(self, segment_prefix[EMU86_F_SEGREG(op_flags)], 4);
					libda_disasm_print_symbol(self, (void *)addr);
				}	break;

				case OPC_R8:
					da_print_reg8(self, rm.mi_reg, op_flags);
					break;

				case OPC_R16:
					da_print_reg16(self, rm.mi_reg);
					break;

				case OPC_R32:
					da_print_reg32(self, rm.mi_reg);
					break;

				case OPC_R64:
					da_print_reg64(self, rm.mi_reg);
					break;

				case OPC_VR8:
					da_print_reg8(self, VEX_VVVVV(), op_flags);
					break;

				case OPC_VR16:
					da_print_reg16(self, VEX_VVVVV());
					break;

				case OPC_VR32:
					da_print_reg32(self, VEX_VVVVV());
					break;

				case OPC_VR64:
					da_print_reg64(self, VEX_VVVVV());
					break;

				case OPC_RSEG:
					da_print_sreg(self, rm.mi_reg);
					break;

				case OPC_RCR:
					da_print_creg(self, rm.mi_reg);
					break;

				case OPC_RDR:
					da_print_dreg(self, rm.mi_reg);
					break;

				case OPC_RBND:
					da_print_bndreg(self, rm.mi_reg);
					break;

				case OPC_RTR:
					da_print_treg(self, rm.mi_reg);
					break;

				case OPC_RMM:
					da_print_mmreg(self, rm.mi_reg);
					break;

				case OPC_RK:
					da_print_kreg(self, rm.mi_reg);
					break;

				case OPC_RXMM:
do_OPC_RXMM:
					da_print_xmmreg(self, rm.mi_reg);
					break;

				case OPC_RYMM:
do_OPC_RYMM:
					da_print_ymmreg(self, rm.mi_reg);
					break;

				case OPC_RZMM:
do_OPC_RZMM:
					da_print_zmmreg(self, rm.mi_reg);
					break;

				case OPC_RXMM_MASK:
do_OPC_RXMM_MASK:
					da_print_xmmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_RYMM_MASK:
do_OPC_RYMM_MASK:
					da_print_ymmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_RZMM_MASK:
do_OPC_RZMM_MASK:
					da_print_zmmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_RK_MASK:
					da_print_kreg(self, rm.mi_reg);
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_RMK:
					if (EMU86_MODRM_ISREG(rm.mi_type)) {
						da_print_kreg(self, rm.mi_rm);
					} else {
						da_print_modrm_rm(self, &rm, op_flags, DA86_IS64(self) ? 16 : 8);
					}
					break;

				case OPC_RM64_MM:
					da_print_modrm_rm64_mm(self, &rm, op_flags);
					break;

				case OPC_RM128_XMM:
do_OPC_RM128_XMM:
					da_print_modrm_rm128_xmm(self, &rm, op_flags);
					break;

				case OPC_RM256_YMM:
do_OPC_RM256_YMM:
					da_print_modrm_rm256_ymm(self, &rm, op_flags);
					break;

				case OPC_RM512_ZMM:
do_OPC_RM512_ZMM:
					da_print_modrm_rm512_zmm(self, &rm, op_flags);
					break;

				case OPC_RM128_XMM_MASK:
do_OPC_RM128_XMM_MASK:
					da_print_modrm_rm128_xmm(self, &rm, op_flags);
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_RM256_YMM_MASK:
do_OPC_RM256_YMM_MASK:
					da_print_modrm_rm256_ymm(self, &rm, op_flags);
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_RM512_ZMM_MASK:
do_OPC_RM512_ZMM_MASK:
					da_print_modrm_rm512_zmm(self, &rm, op_flags);
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_VRK:
					da_print_kreg(self, VEX_VVVVV());
					break;

				case OPC_VRXMM:
do_OPC_VRXMM:
					da_print_xmmreg(self, VEX_VVVVV());
					break;

				case OPC_VRYMM:
do_OPC_VRYMM:
					da_print_ymmreg(self, VEX_VVVVV());
					break;

				case OPC_VRZMM:
do_OPC_VRZMM:
					da_print_zmmreg(self, VEX_VVVVV());
					break;

				case OPC_VRXMM_MASK:
do_OPC_VRXMM_MASK:
					da_print_xmmreg(self, VEX_VVVVV());
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_VRYMM_MASK:
do_OPC_VRYMM_MASK:
					da_print_ymmreg(self, VEX_VVVVV());
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_VRZMM_MASK:
do_OPC_VRZMM_MASK:
					da_print_zmmreg(self, VEX_VVVVV());
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_IMM8_XMM: {
					u8 byte;
do_OPC_IMM8_XMM:
					byte = *(u8 const *)self->d_pc;
					self->d_pc += 1;
					da_print_xmmreg(self, (byte & 0xf0) >> 4);
				}	break;

				case OPC_IMM8_YMM: {
					u8 byte;
do_OPC_IMM8_YMM:
					byte = *(u8 const *)self->d_pc;
					self->d_pc += 1;
					da_print_ymmreg(self, (byte & 0xf0) >> 4);
				}	break;

				case OPC_IMM8_ZMM: {
					u8 byte;
do_OPC_IMM8_ZMM:
					byte = *(u8 const *)self->d_pc;
					self->d_pc += 1;
					da_print_zmmreg(self, (byte & 0xf0) >> 4);
				}	break;

				case OPC_RM128_XMM__OPC_VRXMM__OPC_RXMM_MASK:
do_OPC_RM128_XMM__OPC_VRXMM__OPC_RXMM_MASK:
					/* OPC_RM128_XMM OPC_VRXMM OPC_RXMM_MASK */
					da_print_modrm_rm128_xmm(self, &rm, op_flags);
					disasm_print(self, ", ", 2);
					da_print_xmmreg(self, VEX_VVVVV());
					disasm_print(self, ", ", 2);
					da_print_xmmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_RM256_YMM__OPC_VRYMM__OPC_RYMM_MASK:
do_OPC_RM256_YMM__OPC_VRYMM__OPC_RYMM_MASK:
					/* OPC_RM256_YMM OPC_VRYMM OPC_RYMM_MASK */
					da_print_modrm_rm256_ymm(self, &rm, op_flags);
					disasm_print(self, ", ", 2);
					da_print_ymmreg(self, VEX_VVVVV());
					disasm_print(self, ", ", 2);
					da_print_ymmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_RM512_ZMM__OPC_VRZMM__OPC_RZMM_MASK:
do_OPC_RM512_ZMM__OPC_VRZMM__OPC_RZMM_MASK:
					/* OPC_RM512_ZMM OPC_VRZMM OPC_RZMM_MASK */
					da_print_modrm_rm512_zmm(self, &rm, op_flags);
					disasm_print(self, ", ", 2);
					da_print_zmmreg(self, VEX_VVVVV());
					disasm_print(self, ", ", 2);
					da_print_zmmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, op_flags);
					break;

				case OPC_RMn_xMM__OPC_VRxMM__OPC_RxMM_MASK:
					if ((op_flags & EMU86_F_VEX_LL_M) == 0 << EMU86_F_VEX_LL_S)
						goto do_OPC_RM128_XMM__OPC_VRXMM__OPC_RXMM_MASK;
					if ((op_flags & EMU86_F_VEX_LL_M) == 1 << EMU86_F_VEX_LL_S)
						goto do_OPC_RM256_YMM__OPC_VRYMM__OPC_RYMM_MASK;
					goto do_OPC_RM512_ZMM__OPC_VRZMM__OPC_RZMM_MASK;

				case OPC_VRxMM_MASK:
					if ((op_flags & EMU86_F_VEX_LL_M) == 0 << EMU86_F_VEX_LL_S)
						goto do_OPC_VRXMM_MASK;
					if ((op_flags & EMU86_F_VEX_LL_M) == 1 << EMU86_F_VEX_LL_S)
						goto do_OPC_VRYMM_MASK;
					goto do_OPC_VRZMM_MASK;

				case OPC_RxMM:
					if ((op_flags & EMU86_F_VEX_LL_M) == 0 << EMU86_F_VEX_LL_S)
						goto do_OPC_RXMM;
					if ((op_flags & EMU86_F_VEX_LL_M) == 1 << EMU86_F_VEX_LL_S)
						goto do_OPC_RYMM;
					goto do_OPC_RZMM;

				case OPC_RxMM_MASK:
					if ((op_flags & EMU86_F_VEX_LL_M) == 0 << EMU86_F_VEX_LL_S)
						goto do_OPC_RXMM_MASK;
					if ((op_flags & EMU86_F_VEX_LL_M) == 1 << EMU86_F_VEX_LL_S)
						goto do_OPC_RYMM_MASK;
					goto do_OPC_RZMM_MASK;

				case OPC_RMn_xMM_MASK:
					if ((op_flags & EMU86_F_VEX_LL_M) == 0 << EMU86_F_VEX_LL_S)
						goto do_OPC_RM128_XMM_MASK;
					if ((op_flags & EMU86_F_VEX_LL_M) == 1 << EMU86_F_VEX_LL_S)
						goto do_OPC_RM256_YMM_MASK;
					goto do_OPC_RM512_ZMM_MASK;

				case OPC_RMn_xMM:
					if ((op_flags & EMU86_F_VEX_LL_M) == 0 << EMU86_F_VEX_LL_S)
						goto do_OPC_RM128_XMM;
					if ((op_flags & EMU86_F_VEX_LL_M) == 1 << EMU86_F_VEX_LL_S)
						goto do_OPC_RM256_YMM;
					goto do_OPC_RM512_ZMM;

				case OPC_VRxMM:
					if ((op_flags & EMU86_F_VEX_LL_M) == 0 << EMU86_F_VEX_LL_S)
						goto do_OPC_VRXMM;
					if ((op_flags & EMU86_F_VEX_LL_M) == 1 << EMU86_F_VEX_LL_S)
						goto do_OPC_VRYMM;
					goto do_OPC_VRZMM;

				case OPC_IMM8_xMM:
					if ((op_flags & EMU86_F_VEX_LL_M) == 0 << EMU86_F_VEX_LL_S)
						goto do_OPC_IMM8_XMM;
					if ((op_flags & EMU86_F_VEX_LL_M) == 1 << EMU86_F_VEX_LL_S)
						goto do_OPC_IMM8_YMM;
					goto do_OPC_IMM8_ZMM;

				case OPC_ER: {
					PRIVATE char const rounding_modes[4] = { 'n', 'd', 'u', 'z' };
					char rmrepr[6];
					if (!(op_flags & EMU86_F_EVEX_b)) {
nextop_nocomma:
						ch = *p++;
						if (!ch)
							goto done_operands;
						goto do_nextop_nocomma;
					}
					disasm_print(self, "{", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_PREFIX);
					rmrepr[0] = 'r';
					rmrepr[1] = rounding_modes[EMU86_F_VEX_LL(op_flags)];
					rmrepr[2] = '-';
					rmrepr[3] = 's';
					rmrepr[4] = 'a';
					rmrepr[5] = 'e';
					disasm_print(self, rmrepr, 6);
					disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_SUFFIX);
					disasm_print(self, "}", 1);
				}	break;

				case OPC_SAE:
					if (!(op_flags & EMU86_F_EVEX_b))
						goto nextop_nocomma;
					disasm_print(self, "{", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_PREFIX);
					disasm_print(self, "sae", 3);
					disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_SUFFIX);
					disasm_print(self, "}", 1);
					break;

				case OPC_DISP8:
					libda_disasm_print_symbol(self,
					                          (self->d_pc + 1 + self->d_baseoff) +
					                          (intptr_t)(*(s8 const *)self->d_pc));
					self->d_pc += 1;
					break;

				case OPC_DISP16:
					libda_disasm_print_symbol(self,
					                          (self->d_pc + 2 + self->d_baseoff) +
					                          (intptr_t)(s16)UNALIGNED_GET16((u16 const *)self->d_pc));
					self->d_pc += 2;
					break;

				case OPC_DISP32:
					libda_disasm_print_symbol(self,
					                          (self->d_pc + 4 + self->d_baseoff) +
					                          (intptr_t)(s32)UNALIGNED_GET32((u32 const *)self->d_pc));
					self->d_pc += 4;
					break;

				case OPC_LJMP: {
					u16 segment;
					u32 offset;
					if (!!DA86_IS16(self) ^ !!(op_flags & EMU86_F_AD16)) {
						offset = UNALIGNED_GET16((u16 const *)self->d_pc);
						self->d_pc += 2;
					} else {
						offset = UNALIGNED_GET32((u32 const *)self->d_pc);
						self->d_pc += 4;
					}
					segment = UNALIGNED_GET16((u16 const *)self->d_pc);
					self->d_pc += 2;
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#" PRIx16, segment);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					disasm_print(self, ":$", 2);
					disasm_print_format(self, DISASSEMBLER_FORMAT_SYMBOL_PREFIX);
					disasm_printf(self, "%#" PRIp32, offset);
					disasm_print_format(self, DISASSEMBLER_FORMAT_SYMBOL_SUFFIX);
				}	break;

				case OPC_ESC: {
					char const *end;
					end = strchrnul(p, OPC_ESC_END);
					/* Figure out the proper prefix/suffix for the escaped string. */
					if (*p == '$') {
						disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
						disasm_print(self, p, (size_t)(end - p));
						disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					} else if (*p == '%') {
						disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
						disasm_print(self, p, (size_t)(end - p));
						disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
					} else {
						disasm_print(self, p, (size_t)(end - p));
					}
					p = end;
					if (*p)
						++p;
				}	break;

				default:
					disasm_print(self, p - 1, 1);
					break;
				}
			}
done_operands:
			;
		}
#ifdef CONFIG_LIBDISASM_X86_AUTOSELECT_JCC
		/* Remember the last-written opcode (for selecting JCC encodings) */
		self->d_pad1[0] = (void *)(uintptr_t)whole_opcode;
		self->d_pad1[1] = (void *)(uintptr_t)rm.mi_reg;
#endif /* CONFIG_LIBDISASM_X86_AUTOSELECT_JCC */
		return;
	}
unknown_opcode:
	self->d_pc = text_start;
	if (chain == ops + OPS_OFFETSOF_90h &&
	    !(op_flags & ~(EMU86_F_SEGMASK | EMU86_F_BITMASK))) { /* whole_opcode == 0x8f */
		/* Try to decode an XOP instruction. */
		u16 vex;
		byte_t const *pc = args_start;
		if unlikely(!pc) /* Shouldn't happen... */
			pc = text_start + 1;
		vex = *pc++;
		vex <<= 8;
		vex |= *pc++;
		op_flags |= EMU86_F_HASVEX;
		if (!(vex & EMU86_VEX3B_R))
			op_flags |= EMU86_F_REX_R;
		if (!(vex & EMU86_VEX3B_X))
			op_flags |= EMU86_F_REX_X;
		if (!(vex & EMU86_VEX3B_B))
			op_flags |= EMU86_F_REX_B;
		if (vex & EMU86_VEX3B_L)
			op_flags |= 1 << EMU86_F_VEX_LL_S;
		if (vex & EMU86_VEX3B_W)
			op_flags |= EMU86_F_VEX_W;
		op_flags |= ((~vex & EMU86_VEX3B_VVVV_M) >> EMU86_VEX3B_VVVV_S) << EMU86_F_VEX_VVVVV_S;
		switch (vex & EMU86_VEX3B_PP_M) {
		case 0x01 << EMU86_VEX3B_PP_S: op_flags |= EMU86_F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << EMU86_VEX3B_PP_S: op_flags |= EMU86_F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << EMU86_VEX3B_PP_S: op_flags |= EMU86_F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		/* The actual instruction opcode byte */
		opcode = *pc++;
		switch (vex & EMU86_VEX3B_MMMMM_M) {

#if 0 /* Currently unused... */
		case 0x8 << EMU86_VEX3B_MMMMM_S:
			chain = ops_xop8;
#ifdef HAVE_OPS_XOP8_OFFSETS
			chain += ops_xop8_offsets[opcode];
#endif /* HAVE_OPS_XOP8_OFFSETS */
			break;
#endif

		case 0x9 << EMU86_VEX3B_MMMMM_S:
			chain = ops_xop9;
#ifdef HAVE_OPS_XOP9_OFFSETS
			chain += ops_xop9_offsets[opcode];
#endif /* HAVE_OPS_XOP9_OFFSETS */
			break;

		case 0xa << EMU86_VEX3B_MMMMM_S:
			chain = ops_xopa;
#ifdef HAVE_OPS_XOPA_OFFSETS
			chain += ops_xopa_offsets[opcode];
#endif /* HAVE_OPS_XOPA_OFFSETS */
			break;

		default:
			goto print_byte;
		}
		self->d_pc = pc;
#ifdef CONFIG_LIBDISASM_X86_AUTOSELECT_JCC
		whole_opcode = 0;
#endif /* CONFIG_LIBDISASM_X86_AUTOSELECT_JCC */
		args_start = NULL;
		goto search_chain;
	}
	if (chain == ops_0f + OPS_0F_OFFETSOF_0fh && opcode == 0x0f) {
		/* Special case: `3DNow!` instructions. */
		args_start = (byte_t *)emu86_opcode_decode(text_start, &opcode, &op_flags);
		self->d_pc = emu86_modrm_decode(args_start, &rm, op_flags);
		chain      = ops_3dnow;
		/* `3DNow!` instructions encode the opcode byte _after_ the modr/m suffix!
		 * as such, all together, they behave more akin to a single instruction:
		 *    >> I(0x0f0f, IF_MODRM, "3dnow\t" OP_U8 OP_RMxx OP_Rxx) */
		opcode     = *self->d_pc++;
#ifdef CONFIG_LIBDISASM_X86_AUTOSELECT_JCC
		whole_opcode = 0;
#endif /* CONFIG_LIBDISASM_X86_AUTOSELECT_JCC */
		goto search_chain;
	}
print_byte:
	disasm_print_format(self, DISASSEMBLER_FORMAT_PSEUDOOP_PREFIX);
	disasm_print(self, ".byte", 5);
	disasm_print_format(self, DISASSEMBLER_FORMAT_PSEUDOOP_SUFFIX);
	disasm_printf(self, " %#.2" PRIx8, *self->d_pc++);
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */


DECL_END

#endif /* !GUARD_LIBDISASM_X86_C */
