/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBDISASM_X86_C
#define GUARD_LIBDISASM_X86_C 1
#define DISABLE_BRANCH_PROFILING 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "x86.h"

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

DECL_BEGIN


#define R_AX      0 /* Accumulator. */
#define R_CX      1 /* Counter register. */
#define R_DX      2 /* General purpose d-register. */
#define R_BX      3 /* General purpose b-register. */
#define R_SP      4 /* Stack pointer. */
#define R_BP      5 /* Stack base pointer. */
#define R_SI      6 /* Source pointer. */
#define R_DI      7 /* Destination pointer. */

#define R_EAX     0 /* Accumulator. */
#define R_ECX     1 /* Counter register. */
#define R_EDX     2 /* General purpose d-register. */
#define R_EBX     3 /* General purpose b-register. */
#define R_ESP     4 /* Stack pointer. */
#define R_EBP     5 /* Stack base pointer. */
#define R_ESI     6 /* Source pointer. */
#define R_EDI     7 /* Destination pointer. */
#define R_R8      8 /* R8 */
#define R_R9      9 /* R9 */
#define R_R10    10 /* R10 */
#define R_R11    11 /* R11 */
#define R_R12    12 /* R12 */
#define R_R13    13 /* R13 */
#define R_R14    14 /* R14 */
#define R_R15    15 /* R15 */
#define R_RIP    16 /* %rip (special value that may appear in `mi_rm') */

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
	{ '%', 'r', 'i', 'p' }  /* R_RIP */
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
	{ '%', 'd', 's', ':' },
	{ '%', 'e', 's', ':' },
	{ '%', 'c', 's', ':' },
	{ '%', 's', 's', ':' },
	{ '%', 'f', 's', ':' },
	{ '%', 'g', 's', ':' },
};




/* Instruction flags. */
typedef u32 op_flag_t;
#define F_OP16       0x00000001 /* The 0x66 prefix is being used. */
#define F_AD16       0x00000002 /* The 0x67 prefix is being used. */
#define F_LOCK       0x00000004 /* The `lock' (0xf0) prefix is being used. */
#define F_REPNE      0x00000010 /* The `repne' (0xf2) prefix is being used. */
#define F_REP        0x00000020 /* The `rep' (0xf3) prefix is being used. */
#define F_HASVEX     0x00000040 /* A VEX prefix was given. */
#define F_SEGMASK    0x0000f000 /* Mask for segment overrides. */
#define F_SEGSHIFT           12 /* Shift for segment overrides. */
#define F_VEX_VVVV_M 0x000f0000 /* Mask for VEX.VVVV */
#define F_VEX_VVVV_S         16 /* Shift for VEX.VVVV */
#define F_VEX_W      0x00100000 /* Value of VEX.W */
#define F_VEX_L      0x00200000 /* Value of VEX.L */
#define F_AD64       F_AD16     /* The 0x67 prefix is being used. */
#define F_HASREX     0x00000080 /* A REX prefix is being used. */
#define F_REXSHFT             8 /* Shift for the REX prefix byte. */
#define F_REXMASK    0x00000f00 /* Mask of the REX prefix byte. */
#define F_REX_W      0x00000800 /* The REX.W flag (Indicates 64-bit operands). */
#define F_REX_R      0x00000400 /* The REX.R flag (1-bit extension to MODRM.reg). */
#define F_REX_X      0x00000200 /* The REX.X flag (1-bit extension to SIB.index). */
#define F_REX_B      0x00000100 /* The REX.B flag (1-bit extension to MODRM.rm). */
#define F_SEGDS      0x00001000 /* DS override. */
#define F_SEGES      0x00002000 /* ES override. */
#define F_SEGCS      0x00003000 /* CS override. */
#define F_SEGSS      0x00004000 /* SS override. */
#define F_SEGFS      0x00005000 /* FS override. */
#define F_SEGGS      0x00006000 /* GS override. */

/* Explicit prefix byte flags. */
#define F_66        F_OP16  /* The 0x66 prefix is being used. */
#define F_67        F_AD16  /* The 0x67 prefix is being used. */
#define F_f0        F_LOCK  /* The 0xf0 prefix is being used. */
#define F_f2        F_REPNE /* The 0xf2 prefix is being used. */
#define F_f3        F_REP   /* The 0xf3 prefix is being used. */



#define MODRM_MOD_MASK     0xc0 /* 0b11000000 */
#define MODRM_REG_MASK     0x38 /* 0b00111000 */
#define MODRM_RM_MASK      0x07 /* 0b00000111 */
#define MODRM_MOD_SHIFT    6
#define MODRM_REG_SHIFT    3
#define MODRM_RM_SHIFT     0
#define MODRM_GETMOD(x) (((x) & MODRM_MOD_MASK) >> MODRM_MOD_SHIFT)
#define MODRM_GETREG(x) (((x) & MODRM_REG_MASK) >> MODRM_REG_SHIFT)
#define MODRM_GETRM(x)  (((x) & MODRM_RM_MASK) >> MODRM_RM_SHIFT)

struct modrm {
	s32       mi_offset; /* Memory address. */
#define MODRM_REGISTER 0
#define MODRM_MEMORY   1
	/* EXAMPLES:
	 *  - mov $42, %mi_rm                                   # mi_type == MODRM_REGISTER
	 *  - mov $42, mi_offset(%mi_rm)                        # mi_type == MODRM_MEMORY
	 *  - mov %mi_reg, mi_offset(%mi_rm,%mi_index,mi_shift) # mi_type == MODRM_MEMORY
	 */
	u8        mi_type;   /* mod R/M type (One of `MODRM_*') */
	u8        mi_reg;    /* Secondary register operand, or instruction sub-class. */
	u8        mi_rm;     /* Base register (or 0xff when not set). */
	u8        mi_index;  /* Index register (or 0xff when not set). */
	u8        mi_shift;  /* Index shift (or 0). */
};

PRIVATE void CC
decode_modrm(struct disassembler *__restrict self,
             struct modrm *__restrict info,
             op_flag_t flags) {
	u8 rmbyte = *self->d_pc++;
	u8 sibbyte;
	info->mi_reg = MODRM_GETREG(rmbyte);
	if (!DA86_IS64(self) && (DA86_IS16(self) ^ ((flags & F_67) != 0))) {
		/* XXX: What about mandatory 67h prefix bytes? */
		info->mi_shift = 0;
		if ((rmbyte & MODRM_MOD_MASK) == (0x3 << MODRM_MOD_SHIFT)) {
			/* Register operand. */
			info->mi_rm    = MODRM_GETRM(rmbyte);
			info->mi_type  = MODRM_REGISTER;
			info->mi_index = 0xff;
		} else {
			info->mi_offset = 0;
			info->mi_type = MODRM_MEMORY;
			switch (MODRM_GETRM(rmbyte)) {

			case 0: /* [BX + SI] */
				info->mi_rm    = R_BX;
				info->mi_index = R_SI;
				break;

			case 1: /* [BX + DI] */
				info->mi_rm    = R_BX;
				info->mi_index = R_DI;
				break;

			case 2: /* [BP + SI] */
				info->mi_rm    = R_BP;
				info->mi_index = R_SI;
				break;

			case 3: /* [BP + DI] */
				info->mi_rm    = R_BP;
				info->mi_index = R_DI;
				break;

			case 4: /* [SI] */
				info->mi_rm    = R_SI;
				info->mi_index = 0xff;
				break;

			case 5: /* [DI] */
				info->mi_rm    = R_DI;
				info->mi_index = 0xff;
				break;

			case 6: /* [BP] */
				info->mi_index = 0xff;
				info->mi_rm    = R_BP;
				if ((rmbyte & MODRM_MOD_MASK) == (0x0 << MODRM_MOD_SHIFT)) { /* [disp16] */
					info->mi_rm     = 0xff;
					info->mi_offset = (s32)(s16)UNALIGNED_GET16((uint16_t *)self->d_pc);
					self->d_pc += 2;
				}
				break;

			case 7: /* [BX] */
				info->mi_rm    = R_BX;
				info->mi_index = 0xff;
				break;

			default: __builtin_unreachable();
			}
			if ((rmbyte & MODRM_MOD_MASK) == (0x1 << MODRM_MOD_SHIFT)) {
				/* [... + disp8] */
				info->mi_offset = (s32)*(int8_t *)self->d_pc;
				self->d_pc += 1;
			} else if ((rmbyte & MODRM_MOD_MASK) == (0x2 << MODRM_MOD_SHIFT)) {
				/* [... + disp16] */
				info->mi_offset = (s32)(s16)UNALIGNED_GET16((uint16_t *)self->d_pc);
				self->d_pc += 2;
			}
		}
	} else {
		info->mi_rm = MODRM_GETRM(rmbyte);
		if (flags & F_REX_R)
			info->mi_reg |= 0x8;
		if (flags & F_REX_B)
			info->mi_rm |= 0x8;
		switch (rmbyte & MODRM_MOD_MASK) {

		case 0x0 << MODRM_MOD_SHIFT:
			/* R/M */
			info->mi_type = MODRM_MEMORY;
			if (info->mi_rm == R_EBP) {
				info->mi_rm     = 0xff;
				info->mi_index  = 0xff;
				info->mi_offset = (s32)UNALIGNED_GET32((u32 *)self->d_pc);
				self->d_pc += 4;
				if (DA86_IS64(self))
					info->mi_rm = R_RIP; /* RIP-relative addressing */
			} else if (info->mi_rm == R_ESP) {
				sibbyte         = *self->d_pc++;
				info->mi_offset = 0;
parse_sib_byte:
				info->mi_shift = MODRM_GETMOD(sibbyte);
				info->mi_index = MODRM_GETREG(sibbyte);
				info->mi_rm    = MODRM_GETRM(sibbyte);
				if (flags & F_REX_X)
					info->mi_index |= 0x8;
				if (info->mi_index == R_ESP)
					info->mi_index = 0xff;
				if ((info->mi_rm == R_EBP) &&
				    (rmbyte & MODRM_MOD_MASK) == (0x0 << MODRM_MOD_SHIFT)) {
					info->mi_rm = 0xff; /* disp32 */
					info->mi_offset = (s32)UNALIGNED_GET32((u32 *)self->d_pc);
					self->d_pc += 4;
				}
			} else {
				info->mi_index  = 0xff;
				info->mi_offset = 0;
			}
			break;

		case 0x1 << MODRM_MOD_SHIFT:
			/* R/M + 1-byte offset */
			info->mi_type  = MODRM_MEMORY;
			info->mi_index = 0xff;
			if (info->mi_rm == R_ESP) {
				sibbyte         = *self->d_pc++;
				info->mi_offset = (s32)*(s8 *)self->d_pc;
				++self->d_pc;
				goto parse_sib_byte;
			}
			info->mi_offset = (s32)*(s8 *)self->d_pc;
			++self->d_pc;
			break;

		case 0x2 << MODRM_MOD_SHIFT:
			/* R/M + 4-byte offset */
			info->mi_type  = MODRM_MEMORY;
			info->mi_index = 0xff;
			if (info->mi_rm == R_ESP) {
				sibbyte         = *self->d_pc++;
				info->mi_offset = (s32)UNALIGNED_GET32((u32 *)self->d_pc);
				self->d_pc += 4;
				goto parse_sib_byte;
			}
			info->mi_offset = (s32)UNALIGNED_GET32((u32 *)self->d_pc);
			self->d_pc += 4;
			break;

		case 0x3 << MODRM_MOD_SHIFT:
			/* Register operand. */
			info->mi_type  = MODRM_REGISTER;
			info->mi_index = 0xff;
			break;

		default: __builtin_unreachable();
		}
	}
}


PRIVATE bool CC
decode_opcode(struct disassembler *__restrict self,
              u32 *__restrict popcode,
              op_flag_t *__restrict pflags) {
	u32 result;
	byte_t *text;
	text    = self->d_pc;
	*pflags = 0;
	result  = 0;
next_byte:
	result = *text++;
	switch (result) {

#define VEX3B_R        0x8000 /* FLAG:  3-byte VEX.R */
#define VEX3B_X        0x4000 /* FLAG:  3-byte VEX.X */
#define VEX3B_B        0x2000 /* FLAG:  3-byte VEX.B */
#define VEX3B_M_MMMM_M 0x1f00 /* MASK:  3-byte VEX.M_MMMM */
#define VEX3B_M_MMMM_S      8 /* SHIFT: 3-byte VEX.M_MMMM */
#define VEX3B_W        0x0080 /* FLAG:  3-byte VEX.B */
#define VEX3B_VVVV_M   0x0078 /* MASK:  3-byte VEX.VVVV */
#define VEX3B_VVVV_S        3 /* SHIFT: 3-byte VEX.VVVV */
#define VEX3B_L        0x0004 /* FLAG:  3-byte VEX.L */
#define VEX3B_PP_M     0x0003 /* MASK:  3-byte VEX.PP */
#define VEX3B_PP_S          0 /* SHIFT: 3-byte VEX.PP */

	/* VEX Prefix */
	case 0xc4: { /* 3-byte form */
		u16 vex;
		vex = *text++;
		vex <<= 8;
		vex |= *text++;
		if (DA86_IS64(self)) {
			if (!(vex & VEX3B_R))
				*pflags |= F_REX_R;
			if (!(vex & VEX3B_X))
				*pflags |= F_REX_X;
			if (!(vex & VEX3B_B))
				*pflags |= F_REX_B;
		} else {
			if (!(vex & (VEX3B_R | VEX3B_X))) {
				text -= 2;
				/*result = 0xc4;*/
				break;
			}
		}
		*pflags |= F_HASVEX;
		if (vex & VEX3B_L)
			*pflags |= F_VEX_L;
		if (vex & VEX3B_W)
			*pflags |= F_VEX_W;
		*pflags |= ((~vex & VEX3B_VVVV_M) >> VEX3B_VVVV_S) << F_VEX_VVVV_S;
		switch (vex & VEX3B_PP_M) {
		case 0x01 << VEX3B_PP_S: *pflags |= F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << VEX3B_PP_S: *pflags |= F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << VEX3B_PP_S: *pflags |= F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		switch (vex & VEX3B_M_MMMM_M) {
		case 0x1 << VEX3B_M_MMMM_S: result = 0x0f00; break;
		case 0x2 << VEX3B_M_MMMM_S: result = 0x0f3800; break;
		case 0x3 << VEX3B_M_MMMM_S: result = 0x0f3a00; break;
		default: goto err;
		}
		/* The actual instruction opcode byte */
		result |= *text++;
	}	break;

#define VEX2B_R      0x80 /* FLAG:  2-byte VEX.R */
#define VEX2B_VVVV_M 0x78 /* MASK:  2-byte VEX.VVVV */
#define VEX2B_1      0x40 /* FLAG:  Must be one (if 0, not a prefix + generate opcode `0xc5') */
#define VEX2B_VVVV_S    3 /* SHIFT: 2-byte VEX.VVVV */
#define VEX2B_L      0x04 /* FLAG:  2-byte VEX.L */
#define VEX2B_PP_M   0x03 /* MASK:  2-byte VEX.PP */
#define VEX2B_PP_S      0 /* SHIFT: 2-byte VEX.PP */

	/* VEX Prefix */
	case 0xc5: /* 2-byte form */
		result = *text++;
		if (DA86_IS64(self)) {
			if (!(result & VEX2B_R))
				*pflags |= F_REX_R;
		} else {
			if (!(result & (VEX2B_R | VEX2B_1))) {
				--text;
				result = 0xc5;
				break;
			}
		}
		*pflags |= F_HASVEX;
		if (result & VEX2B_L)
			*pflags |= F_VEX_L;
		*pflags |= ((~result & VEX2B_VVVV_M) >> VEX2B_VVVV_S) << F_VEX_VVVV_S;
		switch (result & VEX2B_PP_M) {
		case 0x01 << VEX2B_PP_S: *pflags |= F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << VEX2B_PP_S: *pflags |= F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << VEX2B_PP_S: *pflags |= F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		goto next_byte;

		/* Prefix bytes */
	case 0x66: *pflags |= F_66; goto next_byte;
	case 0x67: *pflags |= F_67; goto next_byte;
	case 0xf0: *pflags |= F_f0; goto next_byte;
	case 0xf2: *pflags |= F_f2; goto next_byte;
	case 0xf3: *pflags |= F_f3; goto next_byte;

	case 0x40 ... 0x4f:
		if (!DA86_IS64(self))
			break;
		*pflags |= F_HASREX | ((result & 0xf) << F_REXSHFT);
		goto next_byte;

	case 0x26:
		if (DA86_IS64(self))
			goto err;
		*pflags = (*pflags & ~F_SEGMASK) | F_SEGES;
		goto next_byte;

	case 0x2e:
		if (DA86_IS64(self))
			goto err;
		*pflags = (*pflags & ~F_SEGMASK) | F_SEGCS;
		goto next_byte;

	case 0x36:
		if (DA86_IS64(self))
			goto err;
		*pflags = (*pflags & ~F_SEGMASK) | F_SEGSS;
		goto next_byte;

	case 0x3e:
		if (DA86_IS64(self))
			goto err;
		*pflags = (*pflags & ~F_SEGMASK) | F_SEGDS;
		goto next_byte;

	case 0x64:
		*pflags = (*pflags & ~F_SEGMASK) | F_SEGFS;
		goto next_byte;

	case 0x65:
		*pflags = (*pflags & ~F_SEGMASK) | F_SEGGS;
		goto next_byte;

	case 0x0f:
		result <<= 8;
		result |= *text++;
		if (result == 0x0f38 || result == 0x0f3a) {
			result <<= 8;
			result |= *text++;
		}
		break;

	default: break;
	}
	self->d_pc = text;
	*popcode   = result;
	return true;
err:
	return false;
}


PRIVATE void CC
da_print_reg8(struct disassembler *__restrict self, u8 regno, op_flag_t flags) {
	char const *name = gp_register_names8[regno & 15];
	if (flags & F_HASREX)
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
	name = gp_register_names32[regno <= R_RIP ? regno : (regno & 15)];
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_PREFIX);
	disasm_print(self, name, name[4] ? 5 : 4);
	disasm_print_format(self, DISASSEMBLER_FORMAT_REGISTER_SUFFIX);
}

PRIVATE void CC
da_print_reg64(struct disassembler *__restrict self, u8 regno) {
	char const *name;
	name = gp_register_names64[regno <= R_RIP ? regno : (regno & 15)];
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
da_print_modrm_rm(struct disassembler *__restrict self,
                  struct modrm const *__restrict rm,
                  op_flag_t flags, unsigned int size) {
	if (rm->mi_type == MODRM_REGISTER) {
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
		bool has_register;
		if ((flags & F_SEGMASK) != 0)
			disasm_print(self, segment_prefix[((flags & F_SEGMASK) >> F_SEGSHIFT) - 1], 4);
		has_register = rm->mi_rm != 0xff || rm->mi_index != 0xff;
		if (rm->mi_offset || !has_register) {
			s32 offset;
			disasm_print_format(self, DISASSEMBLER_FORMAT_OFFSET_PREFIX);
			offset = rm->mi_offset;
			/* Only render small negative offsets as actually being negative.
			 * Very large offsets are probably absolute pointers, unless a base
			 * register is given. In that case, always render negative number
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
					if (flags & F_67)
						goto do_print_base32;
					da_print_reg64(self, rm->mi_rm);
				} else if (DA86_IS32(self) ^ ((flags & F_67) != 0)) {
do_print_base32:
					da_print_reg32(self, rm->mi_rm);
				} else {
					da_print_reg16(self, rm->mi_rm);
				}
			}
			if (rm->mi_index != 0xff) {
				disasm_print(self, ",", 1);
				if (DA86_IS64(self)) {
					if (flags & F_67)
						goto do_print_index32;
					da_print_reg64(self, rm->mi_index);
				} else if (DA86_IS32(self) ^ ((flags & F_67) != 0)) {
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
}




#define I(op, flags, repr) { flags, op, repr }
struct instruction {
#define IF_REG0  0x0008
#define IF_REG1  0x0009
#define IF_REG2  0x000a
#define IF_REG3  0x000b
#define IF_REG4  0x000c
#define IF_REG5  0x000d
#define IF_REG6  0x000e
#define IF_REG7  0x000f
#define IF_MODRM 0x0010
#define IF_BYTE2 0x3010 /* The first repr-byte is required as a follow-up on the instruction byte. */
#define IF_66    0x0020
#define IF_F2    0x0040
#define IF_F3    0x0080
#define IF_67    0x0100
#define IF_REXW  0x0200
#define IF_REXR  0xc000
#define IF_RMM   0x0400 /* Modrm is memory */
#define IF_RMR   0x0800 /* Modrm is register */
#define IF_VEXW0 0x1000 /* VEX + VEX.W == 0 */
#define IF_VEXW1 0x2000 /* VEX + VEX.W == 1 */
#define IF_VEX   0x3000 /* VEX */
#define IF_X32   0x4000
#define IF_X64   0x8000
	u16  i_flags;    /* Instruction flags. */
	u8   i_opcode;   /* Instruction opcode. */
	char i_repr[13];
};


#define OPC_RM8     '1'
#define OPC_RM16    '2'
#define OPC_RM32    '3'
#define OPC_RM64    '4'
#define OPC_XRM16   '~'
#define OPC_XRM32   '+'
#define OPC_XRM64   '*'
#define OPC_RMBND   '5'
#define OPC_RMBND_RANGE '6'
#define OPC_RMSTi   '7'
#define OPC_S8      'a'
#define OPC_U8      'A'
#define OPC_S16     'b'
#define OPC_U16     'B'
#define OPC_S32     'c'
#define OPC_U32     'C'
#define OPC_U64     'd'
#define OPC_MOFFS8  'E'
#define OPC_MOFFS16 'F'
#define OPC_MOFFS32 'G'
#define OPC_MOFFS64 'H'
#define OPC_R8      'r'
#define OPC_R16     's'
#define OPC_R32     't'
#define OPC_R64     'u'
#define OPC_VR8     'R'
#define OPC_VR16    'S'
#define OPC_VR32    'T'
#define OPC_VR64    'U'
#define OPC_RSEG    'v'
#define OPC_RCR     'w'
#define OPC_RDR     'x'
#define OPC_RBND    'y'
#define OPC_RTR     'z'
#define OPC_DISP8   'm'
#define OPC_DISP16  'n'
#define OPC_DISP32  'o'
#define OPC_LJMP    'P'

#define OP_RM8     "1"
#define OP_RM16    "2"
#define OP_RM32    "3"
#define OP_RM      "3"
#define OP_RM64    "4"
#define OP_XRM16   "~"
#define OP_XRM32   "+"
#define OP_XRM64   "*"
#define OP_RMBND   "5"
#define OP_RMBND_RANGE "6"
#define OP_RMSTi   "7"
#define OP_S8      "a"
#define OP_U8      "A"
#define OP_S16     "b"
#define OP_U16     "B"
#define OP_S32     "c"
#define OP_U32     "C"
#define OP_U64     "d"
#define OP_MOFFS8  "E"
#define OP_MOFFS16 "F"
#define OP_MOFFS32 "G"
#define OP_MOFFS64 "H"
#define OP_R8      "r"
#define OP_R16     "s"
#define OP_R32     "t"
#define OP_R64     "u"
#define OP_RSEG    "v"
#define OP_RCR     "w"
#define OP_RDR     "x"
#define OP_RBND    "y"
#define OP_RTR     "z"
#define OP_VR8     "R"
#define OP_VR16    "S"
#define OP_VR32    "T"
#define OP_VR64    "U"
#define OP_DISP8   "m"
#define OP_DISP16  "n"
#define OP_DISP32  "o"
#define OP_LJMP    "P"
#define OP_ESC(s)  "{" s "}"

#define OP_PAX_PCX_PDX ":a"
#define OP_PAX_PCX     ":b"
#define OP_PSI         ":c" /* %si, %esi, %rsi (same as pointer-size; s.a. `DA86_IS(16|32|64)()') */

/* Smaller encodings for a couple of fixed register operands.
 * While all of these could be implemented with `OP_ESC()', this
 * format uses much less memory, allowing `i_repr' to be much smaller. */
#define OP_ST0     ":0" /* %st(0) */
#define OP_ST1     ":1" /* %st(1) */
#define OP_ST2     ":2" /* %st(2) */
#define OP_ST3     ":3" /* %st(3) */
#define OP_ST4     ":4" /* %st(4) */
#define OP_ST5     ":5" /* %st(5) */
#define OP_ST6     ":6" /* %st(6) */
#define OP_ST7     ":7" /* %st(7) */
#define OP_R8W     ":K" /* %r8w */
#define OP_R8D     ":L" /* %r8d */
#define OP_R9W     ":M" /* %r9w */
#define OP_R9D     ":N" /* %r9d */
#define OP_R10W    ":O" /* %r10w */
#define OP_R10D    ":P" /* %r10d */
#define OP_R11W    ":Q" /* %r11w */
#define OP_R11D    ":R" /* %r11d */
#define OP_R12W    ":S" /* %r12w */
#define OP_R12D    ":T" /* %r12d */
#define OP_R13W    ":U" /* %r13w */
#define OP_R13D    ":V" /* %r13d */
#define OP_R14W    ":W" /* %r14w */
#define OP_R14D    ":X" /* %r14d */
#define OP_R15W    ":Y" /* %r15w */
#define OP_R15D    ":Z" /* %r15d */
#define OP_EAX     ":k" /* %eax */
#define OP_ECX     ":l" /* %ecx */
#define OP_EDX     ":m" /* %edx */
#define OP_EBX     ":n" /* %ebx */
#define OP_ESP     ":o" /* %esp */
#define OP_EBP     ":p" /* %ebp */
#define OP_ESI     ":q" /* %esi */
#define OP_EDI     ":r" /* %edi */
#define OP_RAX     ":s" /* %rax */
#define OP_RCX     ":t" /* %rcx */
#define OP_RDX     ":u" /* %rdx */
#define OP_RBX     ":v" /* %rbx */
#define OP_RSP     ":w" /* %rsp */
#define OP_RBP     ":x" /* %rbp */
#define OP_RSI     ":y" /* %rsi */
#define OP_RDI     ":z" /* %rdi */

#define OP_AX      ":A"
#define OP_CX      ":B"
#define OP_DX      ":C"
#define OP_BX      ":D"
#define OP_SP      ":E"
#define OP_BP      ":F"
#define OP_SI      ":G"
#define OP_DI      ":H"

#define OP_X64_RN_MIN ' '
#define OP_X64_RN_MAX '\''
#define OP_X64_R8  ": "
#define OP_R9      ":!"
#define OP_R10     ":\""
#define OP_R11     ":#"
#define OP_R12     ":$"
#define OP_R13     ":%"
#define OP_R14     ":&"
#define OP_R15     ":\'"

#define OP_GP16_MIN '('
#define OP_GP16_MAX '/'
#define OP_AL      ":("
#define OP_CL      ":)"
#define OP_DL      ":*"
#define OP_BL      ":+"
#define OP_AH      ":,"
#define OP_CH      ":-"
#define OP_DH      ":."
#define OP_BH      ":/"


#define OP_DS   OP_ESC("%ds")
#define OP_ES   OP_ESC("%es")
#define OP_FS   OP_ESC("%fs")
#define OP_GS   OP_ESC("%gs")
#define OP_CS   OP_ESC("%cs")
#define OP_SS   OP_ESC("%ss")
#define OP_IMM1 OP_ESC("$1")


#undef CONFIG_AUTOSELECT_JCC
#define CONFIG_AUTOSELECT_JCC  1

#ifdef CONFIG_AUTOSELECT_JCC
#define NAME_jc0 "o"   /* "o" */
#define NAME_jc1 "no"  /* "no" */
#define NAME_jc2 "[2]" /* "[b|c|nae]" */
#define NAME_jc3 "[3]" /* "[ae|nb|nc]" */
#define NAME_jc4 "[4]" /* "[z|e]" */
#define NAME_jc5 "[5]" /* "[nz|ne]" */
#define NAME_jc6 "[6]" /* "[be|na]" */
#define NAME_jc7 "[7]" /* "[a|nbe]" */
#define NAME_jc8 "s"   /* "s" */
#define NAME_jc9 "ns"  /* "ns" */
#define NAME_jca "[a]" /* "[p|pe]" */
#define NAME_jcb "[b]" /* "[np|po]" */
#define NAME_jcc "[c]" /* "[l|nge]" */
#define NAME_jcd "[d]" /* "[ge|nl]" */
#define NAME_jce "[e]" /* "[le|ng]" */
#define NAME_jcf "[f]" /* "[g|nle]" */
#else /* CONFIG_AUTOSELECT_JCC */
#define NAME_jc0 "o"
#define NAME_jc1 "no"
#define NAME_jc2 "b"
#define NAME_jc3 "ae"
#define NAME_jc4 "z"
#define NAME_jc5 "nz"
#define NAME_jc6 "be"
#define NAME_jc7 "a"
#define NAME_jc8 "s"
#define NAME_jc9 "ns"
#define NAME_jca "p"
#define NAME_jcb "np"
#define NAME_jcc "l"
#define NAME_jcd "ge"
#define NAME_jce "le"
#define NAME_jcf "g"
#endif /* !CONFIG_AUTOSELECT_JCC */

enum {
#define LONGOP(name, repr) name, _LO_next##name = name + sizeof(repr) - 1,
#include "x86-longops.def"
#undef LONGOP
	_LO_size
};

PRIVATE char const longops_repr[_LO_size + 1] = {
#define LONGOP(name, repr) repr "\0"
#include "x86-longops.def"
#undef LONGOP
};

/* Encode extended-length opcode representation (for better compression). */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define LONGREPR(n)      { '?', (char)(u8)((n) & 0xff), (char)(u8)(((n) >> 8) & 0xff) }
#define LONGREPR_B(b, n) { (char)(u8)b, '?', (char)(u8)((n) & 0xff), (char)(u8)(((n) >> 8) & 0xff) }
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define LONGREPR(n)      { '?', (char)(u8)(((n) >> 8) & 0xff), (char)(u8)((n) & 0xff) }
#define LONGREPR_B(b, n) { (char)(u8)b, '?', (char)(u8)(((n) >> 8) & 0xff), (char)(u8)((n) & 0xff) }
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */


/* clang-format off */
PRIVATE struct instruction const ops[] = {
/*[[[start:ops]]]*/
	/* REMINDER: After adding/removing instructions from this table, you must run:
	 *           $ deemon -F kos/src/libdisasm/x86.c */

	I(0x00, IF_MODRM,        "addb\t" OP_R8   OP_RM8),
	I(0x01, IF_66|IF_MODRM,  "addw\t" OP_R16  OP_RM16),
	I(0x01, IF_MODRM,        "addl\t" OP_R32  OP_RM32),
	I(0x01, IF_REXW|IF_MODRM,"addq\t" OP_R64  OP_RM64),
	I(0x02, IF_MODRM,        "addb\t" OP_RM8  OP_R32),
	I(0x03, IF_66|IF_MODRM,  "addw\t" OP_RM16 OP_R32),
	I(0x03, IF_MODRM,        "addl\t" OP_RM32 OP_R32),
	I(0x03, IF_REXW|IF_MODRM,"addq\t" OP_RM64 OP_R64),
	I(0x04, 0,               "addb\t" OP_U8   OP_AL),
	I(0x05, IF_66,           "addw\t" OP_U16  OP_AX),
	I(0x05, 0,               "addl\t" OP_U32  OP_EAX),
	I(0x05, IF_REXW,         "addq\t" OP_S32  OP_RAX),

	I(0x06, IF_66,           "pushw\t" OP_ES),
	I(0x06, 0,               "pushl\t" OP_ES),
	I(0x07, IF_66,           "popw\t" OP_ES),
	I(0x07, 0,               "popl\t" OP_ES),

	I(0x08, IF_MODRM,        "orb\t" OP_R8   OP_RM8),
	I(0x09, IF_66|IF_MODRM,  "orw\t" OP_R16  OP_RM16),
	I(0x09, IF_MODRM,        "orl\t" OP_R32  OP_RM32),
	I(0x09, IF_REXW|IF_MODRM,"orq\t" OP_R64  OP_RM64),
	I(0x0a, IF_MODRM,        "orb\t" OP_RM8  OP_R32),
	I(0x0b, IF_66|IF_MODRM,  "orw\t" OP_RM16 OP_R32),
	I(0x0b, IF_MODRM,        "orl\t" OP_RM32 OP_R32),
	I(0x0b, IF_REXW|IF_MODRM,"orq\t" OP_RM64 OP_R64),
	I(0x0c, 0,               "orb\t" OP_U8   OP_AL),
	I(0x0d, IF_66,           "orw\t" OP_U16  OP_AX),
	I(0x0d, 0,               "orl\t" OP_U32  OP_EAX),
	I(0x0d, IF_REXW,         "orq\t" OP_S32  OP_RAX),

	I(0x0e, IF_66,           "pushw\t" OP_CS),
	I(0x0e, 0,               "pushl\t" OP_CS),

	I(0x10, IF_MODRM,        "adcb\t" OP_R8   OP_RM8),
	I(0x11, IF_66|IF_MODRM,  "adcw\t" OP_R16  OP_RM16),
	I(0x11, IF_MODRM,        "adcl\t" OP_R32  OP_RM32),
	I(0x11, IF_REXW|IF_MODRM,"adcq\t" OP_R64  OP_RM64),
	I(0x12, IF_MODRM,        "adcb\t" OP_RM8  OP_R32),
	I(0x13, IF_66|IF_MODRM,  "adcw\t" OP_RM16 OP_R32),
	I(0x13, IF_MODRM,        "adcl\t" OP_RM32 OP_R32),
	I(0x13, IF_REXW|IF_MODRM,"adcq\t" OP_RM64 OP_R64),
	I(0x14, 0,               "adcb\t" OP_U8   OP_AL),
	I(0x15, IF_66,           "adcw\t" OP_U16  OP_AX),
	I(0x15, 0,               "adcl\t" OP_U32  OP_EAX),
	I(0x15, IF_REXW,         "adcq\t" OP_S32  OP_RAX),

	I(0x16, IF_66,           "pushw\t" OP_SS),
	I(0x16, 0,               "pushl\t" OP_SS),
	I(0x17, IF_66,           "popw\t" OP_SS),
	I(0x17, 0,               "popl\t" OP_SS),

	I(0x18, IF_MODRM,        "sbbb\t" OP_R8   OP_RM8),
	I(0x19, IF_66|IF_MODRM,  "sbbw\t" OP_R16  OP_RM16),
	I(0x19, IF_MODRM,        "sbbl\t" OP_R32  OP_RM32),
	I(0x19, IF_REXW|IF_MODRM,"sbbq\t" OP_R64  OP_RM64),
	I(0x1a, IF_MODRM,        "sbbb\t" OP_RM8  OP_R32),
	I(0x1b, IF_66|IF_MODRM,  "sbbw\t" OP_RM16 OP_R32),
	I(0x1b, IF_MODRM,        "sbbl\t" OP_RM32 OP_R32),
	I(0x1b, IF_REXW|IF_MODRM,"sbbq\t" OP_RM64 OP_R64),
	I(0x1c, 0,               "sbbb\t" OP_U8   OP_AL),
	I(0x1d, IF_66,           "sbbw\t" OP_U16  OP_AX),
	I(0x1d, 0,               "sbbl\t" OP_U32  OP_EAX),
	I(0x1d, IF_REXW,         "sbbq\t" OP_S32  OP_RAX),

	I(0x1e, IF_66,           "pushw\t" OP_DS),
	I(0x1e, 0,               "pushl\t" OP_DS),
	I(0x1f, IF_66,           "popw\t" OP_DS),
	I(0x1f, 0,               "popl\t" OP_DS),

	I(0x20, IF_MODRM,        "andb\t" OP_R8   OP_RM8),
	I(0x21, IF_66|IF_MODRM,  "andw\t" OP_R16  OP_RM16),
	I(0x21, IF_MODRM,        "andl\t" OP_R32  OP_RM32),
	I(0x21, IF_REXW|IF_MODRM,"andq\t" OP_R64  OP_RM64),
	I(0x22, IF_MODRM,        "andb\t" OP_RM8  OP_R32),
	I(0x23, IF_66|IF_MODRM,  "andw\t" OP_RM16 OP_R32),
	I(0x23, IF_MODRM,        "andl\t" OP_RM32 OP_R32),
	I(0x23, IF_REXW|IF_MODRM,"andq\t" OP_RM64 OP_R64),
	I(0x24, 0,               "andb\t" OP_U8   OP_AL),
	I(0x25, IF_66,           "andw\t" OP_U16  OP_AX),
	I(0x25, 0,               "andl\t" OP_U32  OP_EAX),
	I(0x25, IF_REXW,         "andq\t" OP_S32  OP_RAX),

	/* 0x26 -- PREFIX */
	I(0x27, 0,               "daa"),

	I(0x28, IF_MODRM,        "subb\t" OP_R8   OP_RM8),
	I(0x29, IF_66|IF_MODRM,  "subw\t" OP_R16  OP_RM16),
	I(0x29, IF_MODRM,        "subl\t" OP_R32  OP_RM32),
	I(0x29, IF_REXW|IF_MODRM,"subq\t" OP_R64  OP_RM64),
	I(0x2a, IF_MODRM,        "subb\t" OP_RM8  OP_R32),
	I(0x2b, IF_66|IF_MODRM,  "subw\t" OP_RM16 OP_R32),
	I(0x2b, IF_MODRM,        "subl\t" OP_RM32 OP_R32),
	I(0x2b, IF_REXW|IF_MODRM,"subq\t" OP_RM64 OP_R64),
	I(0x2c, 0,               "subb\t" OP_U8   OP_AL),
	I(0x2d, IF_66,           "subw\t" OP_U16  OP_AX),
	I(0x2d, 0,               "subl\t" OP_U32  OP_EAX),
	I(0x2d, IF_REXW,         "subq\t" OP_S32  OP_RAX),

	/* 0x2e -- PREFIX */
	I(0x2f, 0,               "das"),

	I(0x30, IF_MODRM,        "xorb\t" OP_R8   OP_RM8),
	I(0x31, IF_66|IF_MODRM,  "xorw\t" OP_R16  OP_RM16),
	I(0x31, IF_MODRM,        "xorl\t" OP_R32  OP_RM32),
	I(0x31, IF_REXW|IF_MODRM,"xorq\t" OP_R64  OP_RM64),
	I(0x32, IF_MODRM,        "xorb\t" OP_RM8  OP_R32),
	I(0x33, IF_66|IF_MODRM,  "xorw\t" OP_RM16 OP_R32),
	I(0x33, IF_MODRM,        "xorl\t" OP_RM32 OP_R32),
	I(0x33, IF_REXW|IF_MODRM,"xorq\t" OP_RM64 OP_R64),
	I(0x34, 0,               "xorb\t" OP_U8   OP_AL),
	I(0x35, IF_66,           "xorw\t" OP_U16  OP_AX),
	I(0x35, 0,               "xorl\t" OP_U32  OP_EAX),
	I(0x35, IF_REXW,         "xorq\t" OP_S32  OP_RAX),

	/* 0x36 -- PREFIX */
	I(0x37, 0,               "aaa"),

	I(0x38, IF_MODRM,        "cmpb\t" OP_R8   OP_RM8),
	I(0x39, IF_66|IF_MODRM,  "cmpw\t" OP_R16  OP_RM16),
	I(0x39, IF_MODRM,        "cmpl\t" OP_R32  OP_RM32),
	I(0x39, IF_REXW|IF_MODRM,"cmpq\t" OP_R64  OP_RM64),
	I(0x3a, IF_MODRM,        "cmpb\t" OP_RM8  OP_R32),
	I(0x3b, IF_66|IF_MODRM,  "cmpw\t" OP_RM16 OP_R32),
	I(0x3b, IF_MODRM,        "cmpl\t" OP_RM32 OP_R32),
	I(0x3b, IF_REXW|IF_MODRM,"cmpq\t" OP_RM64 OP_R64),
	I(0x3c, 0,               "cmpb\t" OP_U8   OP_AL),
	I(0x3d, IF_66,           "cmpw\t" OP_U16  OP_AX),
	I(0x3d, 0,               "cmpl\t" OP_U32  OP_EAX),
	I(0x3d, IF_REXW,         "cmpq\t" OP_S32  OP_RAX),

	/* 0x3e -- PREFIX */
	I(0x3f, 0,               "aas"),

	I(0x40, IF_66,           "incw\t" OP_AX),
	I(0x40, 0,               "incl\t" OP_EAX),
	I(0x41, IF_66,           "incw\t" OP_CX),
	I(0x41, 0,               "incl\t" OP_ECX),
	I(0x42, IF_66,           "incw\t" OP_DX),
	I(0x42, 0,               "incl\t" OP_EDX),
	I(0x43, IF_66,           "incw\t" OP_BX),
	I(0x43, 0,               "incl\t" OP_EBX),
	I(0x44, IF_66,           "incw\t" OP_SP),
	I(0x44, 0,               "incl\t" OP_ESP),
	I(0x45, IF_66,           "incw\t" OP_BP),
	I(0x45, 0,               "incl\t" OP_EBP),
	I(0x46, IF_66,           "incw\t" OP_SI),
	I(0x46, 0,               "incl\t" OP_ESI),
	I(0x47, IF_66,           "incw\t" OP_DI),
	I(0x47, 0,               "incl\t" OP_EDI),

	I(0x48, IF_66,           "decw\t" OP_AX),
	I(0x48, 0,               "decl\t" OP_EAX),
	I(0x49, IF_66,           "decw\t" OP_CX),
	I(0x49, 0,               "decl\t" OP_ECX),
	I(0x4a, IF_66,           "decw\t" OP_DX),
	I(0x4a, 0,               "decl\t" OP_EDX),
	I(0x4b, IF_66,           "decw\t" OP_BX),
	I(0x4b, 0,               "decl\t" OP_EBX),
	I(0x4c, IF_66,           "decw\t" OP_SP),
	I(0x4c, 0,               "decl\t" OP_ESP),
	I(0x4d, IF_66,           "decw\t" OP_BP),
	I(0x4d, 0,               "decl\t" OP_EBP),
	I(0x4e, IF_66,           "decw\t" OP_SI),
	I(0x4e, 0,               "decl\t" OP_ESI),
	I(0x4f, IF_66,           "decw\t" OP_DI),
	I(0x4f, 0,               "decl\t" OP_EDI),

	I(0x50, IF_66,           "pushw\t" OP_AX),
	I(0x50, IF_REXR,         "pushq\t" OP_X64_R8),
	I(0x50, IF_X32,          "pushl\t" OP_EAX),
	I(0x50, IF_X64,          "pushq\t" OP_RAX),
	I(0x51, IF_66,           "pushw\t" OP_CX),
	I(0x51, IF_REXR,         "pushq\t" OP_R9),
	I(0x51, IF_X32,          "pushl\t" OP_ECX),
	I(0x51, IF_X64,          "pushq\t" OP_RCX),
	I(0x52, IF_66,           "pushw\t" OP_DX),
	I(0x52, IF_REXR,         "pushq\t" OP_R10),
	I(0x52, IF_X32,          "pushl\t" OP_EDX),
	I(0x52, IF_X64,          "pushq\t" OP_RDX),
	I(0x53, IF_66,           "pushw\t" OP_BX),
	I(0x53, IF_REXR,         "pushq\t" OP_R11),
	I(0x53, IF_X32,          "pushl\t" OP_EBX),
	I(0x53, IF_X64,          "pushq\t" OP_RBX),
	I(0x54, IF_66,           "pushw\t" OP_SP),
	I(0x54, IF_REXR,         "pushq\t" OP_R12),
	I(0x54, IF_X32,          "pushl\t" OP_ESP),
	I(0x54, IF_X64,          "pushq\t" OP_RSP),
	I(0x55, IF_66,           "pushw\t" OP_BP),
	I(0x55, IF_REXR,         "pushq\t" OP_R13),
	I(0x55, IF_X32,          "pushl\t" OP_EBP),
	I(0x55, IF_X64,          "pushq\t" OP_RBP),
	I(0x56, IF_66,           "pushw\t" OP_SI),
	I(0x56, IF_REXR,         "pushq\t" OP_R14),
	I(0x56, IF_X32,          "pushl\t" OP_ESI),
	I(0x56, IF_X64,          "pushq\t" OP_RSI),
	I(0x57, IF_66,           "pushw\t" OP_DI),
	I(0x57, IF_REXR,         "pushq\t" OP_R15),
	I(0x57, IF_X32,          "pushl\t" OP_EDI),
	I(0x57, IF_X64,          "pushq\t" OP_RDI),

	I(0x58, IF_66,           "popw\t" OP_AX),
	I(0x58, IF_REXR,         "popq\t" OP_X64_R8),
	I(0x58, IF_X32,          "popl\t" OP_EAX),
	I(0x58, IF_X64,          "popq\t" OP_RAX),
	I(0x59, IF_66,           "popw\t" OP_CX),
	I(0x59, IF_REXR,         "popq\t" OP_R9),
	I(0x59, IF_X32,          "popl\t" OP_ECX),
	I(0x59, IF_X64,          "popq\t" OP_RCX),
	I(0x5a, IF_66,           "popw\t" OP_DX),
	I(0x5a, IF_REXR,         "popq\t" OP_R10),
	I(0x5a, IF_X32,          "popl\t" OP_EDX),
	I(0x5a, IF_X64,          "popq\t" OP_RDX),
	I(0x5b, IF_66,           "popw\t" OP_BX),
	I(0x5b, IF_REXR,         "popq\t" OP_R11),
	I(0x5b, IF_X32,          "popl\t" OP_EBX),
	I(0x5b, IF_X64,          "popq\t" OP_RBX),
	I(0x5c, IF_66,           "popw\t" OP_SP),
	I(0x5c, IF_REXR,         "popq\t" OP_R12),
	I(0x5c, IF_X32,          "popl\t" OP_ESP),
	I(0x5c, IF_X64,          "popq\t" OP_RSP),
	I(0x5d, IF_66,           "popw\t" OP_BP),
	I(0x5d, IF_REXR,         "popq\t" OP_R13),
	I(0x5d, IF_X32,          "popl\t" OP_EBP),
	I(0x5d, IF_X64,          "popq\t" OP_RBP),
	I(0x5e, IF_66,           "popw\t" OP_SI),
	I(0x5e, IF_REXR,         "popq\t" OP_R14),
	I(0x5e, IF_X32,          "popl\t" OP_ESI),
	I(0x5e, IF_X64,          "popq\t" OP_RSI),
	I(0x5f, IF_66,           "popw\t" OP_DI),
	I(0x5f, IF_REXR,         "popq\t" OP_R15),
	I(0x5f, IF_X32,          "popl\t" OP_EDI),
	I(0x5f, IF_X64,          "popq\t" OP_RDI),

	I(0x60, IF_66,           "pushaw"),
	I(0x60, 0,               "pushal"),

	I(0x61, IF_66,           "popaw"),
	I(0x61, 0,               "popal"),

	I(0x62, IF_66|IF_MODRM,  "boundw\t" OP_RM32 OP_R16),
	I(0x62, IF_MODRM,        "boundl\t" OP_RM64 OP_R32),

	I(0x63, IF_MODRM,        "arpl\t" OP_R16 OP_RM16),

	/* 0x64 -- PREFIX */
	/* 0x65 -- PREFIX */
	/* 0x66 -- PREFIX */
	/* 0x67 -- PREFIX */

	I(0x68, IF_66,           "pushw\t" OP_U16),
	I(0x68, 0,               "pushl\t" OP_U32),
	I(0x68, IF_REXW,         "pushq\t" OP_S32),

	I(0x69, IF_66|IF_MODRM,  "imulw\t" OP_U16 OP_RM16 OP_R16),
	I(0x69, IF_MODRM,        "imull\t" OP_U32 OP_RM32 OP_R32),
	I(0x69, IF_REXW|IF_MODRM,"imulq\t" OP_S32 OP_RM64 OP_R64),

	I(0x6a, 0,               "pushl\t" OP_S8),

	I(0x6b, IF_66|IF_MODRM,  "imulw\t" OP_U8 OP_RM16 OP_R16),
	I(0x6b, IF_MODRM,        "imull\t" OP_U8 OP_RM32 OP_R32),
	I(0x6b, IF_REXW|IF_MODRM,"imulq\t" OP_U8 OP_RM64 OP_R64),

	I(0x6c, 0,               "insb"),
	I(0x6c, IF_F3,           "rep insb"),
	I(0x6d, IF_66,           "insw"),
	I(0x6d, 0,               "insl"),
	I(0x6d, IF_F3|IF_66,     "rep insw"),
	I(0x6d, IF_F3,           "rep insl"),

	I(0x6e, 0,               "outsb"),
	I(0x6e, IF_F3,           "rep outsb"),
	I(0x6f, IF_66,           "outsw"),
	I(0x6f, 0,               "outsl"),
	I(0x6f, IF_F3|IF_66,     "rep outsw"),
	I(0x6f, IF_F3,           "rep outsl"),

	I(0x70, 0,               "j" NAME_jc0 "\t" OP_DISP8),
	I(0x71, 0,               "j" NAME_jc1 "\t" OP_DISP8),
	I(0x72, 0,               "j" NAME_jc2 "\t" OP_DISP8),
	I(0x73, 0,               "j" NAME_jc3 "\t" OP_DISP8),
	I(0x74, 0,               "j" NAME_jc4 "\t" OP_DISP8),
	I(0x75, 0,               "j" NAME_jc5 "\t" OP_DISP8),
	I(0x76, 0,               "j" NAME_jc6 "\t" OP_DISP8),
	I(0x77, 0,               "j" NAME_jc7 "\t" OP_DISP8),
	I(0x78, 0,               "j" NAME_jc8 "\t" OP_DISP8),
	I(0x79, 0,               "j" NAME_jc9 "\t" OP_DISP8),
	I(0x7a, 0,               "j" NAME_jca "\t" OP_DISP8),
	I(0x7b, 0,               "j" NAME_jcb "\t" OP_DISP8),
	I(0x7c, 0,               "j" NAME_jcc "\t" OP_DISP8),
	I(0x7d, 0,               "j" NAME_jcd "\t" OP_DISP8),
	I(0x7e, 0,               "j" NAME_jce "\t" OP_DISP8),
	I(0x7f, 0,               "j" NAME_jcf "\t" OP_DISP8),

	I(0x80, IF_MODRM|IF_REG0, "addb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG1, "orb\t"  OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG2, "adcb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG3, "sbbb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG4, "andb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG5, "subb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG6, "xorb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG7, "cmpb\t" OP_U8 OP_RM8),

	I(0x81, IF_66|IF_MODRM|IF_REG0, "addw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG0, "addl\t" OP_U32 OP_RM32),
	I(0x81, IF_REXW|IF_MODRM|IF_REG0, "addq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG1, "orw\t"  OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG1, "orl\t"  OP_U32 OP_RM32),
	I(0x81, IF_REXW|IF_MODRM|IF_REG1, "orq\t"  OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG2, "adcw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG2, "adcl\t" OP_U32 OP_RM32),
	I(0x81, IF_REXW|IF_MODRM|IF_REG2, "adcq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG3, "sbbw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG3, "sbbl\t" OP_U32 OP_RM32),
	I(0x81, IF_REXW|IF_MODRM|IF_REG3, "sbbq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG4, "andw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG4, "andl\t" OP_U32 OP_RM32),
	I(0x81, IF_REXW|IF_MODRM|IF_REG4, "andq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG5, "subw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG5, "subl\t" OP_U32 OP_RM32),
	I(0x81, IF_REXW|IF_MODRM|IF_REG5, "subq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG6, "xorw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG6, "xorl\t" OP_U32 OP_RM32),
	I(0x81, IF_REXW|IF_MODRM|IF_REG6, "xorq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG7, "cmpw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG7, "cmpl\t" OP_U32 OP_RM32),
	I(0x81, IF_REXW|IF_MODRM|IF_REG7, "cmpq\t" OP_S32 OP_RM32),

	/* 0x82 is an alias for 0x80, but is only valid in 32-bit mode (not in 64-bit mode!) */
	I(0x82, IF_X32|IF_MODRM|IF_REG0, "addb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG1, "orb\t"  OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG2, "adcb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG3, "sbbb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG4, "andb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG5, "subb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG6, "xorb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG7, "cmpb\t" OP_U8 OP_RM8),

	I(0x83, IF_66|IF_MODRM|IF_REG0, "addw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG0, "addl\t" OP_S8 OP_RM32),
	I(0x83, IF_REXW|IF_MODRM|IF_REG0, "addq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG1, "orw\t"  OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG1, "orl\t"  OP_S8 OP_RM32),
	I(0x83, IF_REXW|IF_MODRM|IF_REG1, "orq\t"  OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG2, "adcw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG2, "adcl\t" OP_S8 OP_RM32),
	I(0x83, IF_REXW|IF_MODRM|IF_REG2, "adcq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG3, "sbbw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG3, "sbbl\t" OP_S8 OP_RM32),
	I(0x83, IF_REXW|IF_MODRM|IF_REG3, "sbbq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG4, "andw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG4, "andl\t" OP_S8 OP_RM32),
	I(0x83, IF_REXW|IF_MODRM|IF_REG4, "andq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG5, "subw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG5, "subl\t" OP_S8 OP_RM32),
	I(0x83, IF_REXW|IF_MODRM|IF_REG5, "subq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG6, "xorw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG6, "xorl\t" OP_S8 OP_RM32),
	I(0x83, IF_REXW|IF_MODRM|IF_REG6, "xorq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG7, "cmpw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG7, "cmpl\t" OP_S8 OP_RM32),
	I(0x83, IF_REXW|IF_MODRM|IF_REG7, "cmpq\t" OP_S8 OP_RM64),

	I(0x84, IF_MODRM,         "testb\t" OP_R8 OP_RM8),
	I(0x85, IF_66|IF_MODRM,   "testw\t" OP_R16 OP_RM16),
	I(0x85, IF_MODRM,         "testl\t" OP_R32 OP_RM32),
	I(0x85, IF_REXW|IF_MODRM, "testq\t" OP_R64 OP_RM64),

	I(0x86, IF_MODRM,         "xchgb\t" OP_R8 OP_RM8),
	I(0x87, IF_66|IF_MODRM,   "xchgw\t" OP_R16 OP_RM16),
	I(0x87, IF_MODRM,         "xchgl\t" OP_R32 OP_RM32),
	I(0x87, IF_REXW|IF_MODRM, "xchgq\t" OP_R64 OP_RM64),

	I(0x88, IF_MODRM,         "movb\t" OP_R8 OP_RM8),
	I(0x89, IF_66|IF_MODRM,   "movw\t" OP_R16 OP_RM16),
	I(0x89, IF_MODRM,         "movl\t" OP_R32 OP_RM32),
	I(0x89, IF_REXW|IF_MODRM, "movq\t" OP_R64 OP_RM64),

	I(0x8a, IF_MODRM,         "movb\t" OP_RM8 OP_R8),
	I(0x8b, IF_66|IF_MODRM,   "movw\t" OP_RM16 OP_R16),
	I(0x8b, IF_MODRM,         "movl\t" OP_RM32 OP_R32),
	I(0x8b, IF_REXW|IF_MODRM, "movq\t" OP_RM64 OP_R64),

	I(0x8c, IF_66|IF_MODRM,   "movw\t" OP_RSEG OP_RM16),
	I(0x8c, IF_MODRM,         "movl\t" OP_RSEG OP_RM32),
	I(0x8c, IF_REXW|IF_MODRM, "movq\t" OP_RSEG OP_RM64),

	I(0x8d, IF_66|IF_MODRM,   "leaw\t" OP_RM16 OP_R16),
	I(0x8d, IF_MODRM,         "leal\t" OP_RM32 OP_R32),
	I(0x8d, IF_REXW|IF_MODRM, "leaq\t" OP_RM64 OP_R64),

	I(0x8e, IF_66|IF_MODRM,   "movw\t" OP_RM16 OP_RSEG),
	I(0x8e, IF_MODRM,         "movl\t" OP_RM32 OP_RSEG),
	I(0x8e, IF_REXW|IF_MODRM, "movq\t" OP_RM64 OP_RSEG),

	I(0x8f, IF_66|IF_MODRM,         "popw\t" OP_RM16),
	I(0x8f, IF_MODRM,               "popl\t" OP_RM32),
	I(0x8f, IF_REXW|IF_MODRM,       "popq\t" OP_RM64),
	I(0x8f, IF_67|IF_66|IF_MODRM,   "popw\t" OP_RM16),
	I(0x8f, IF_67|IF_MODRM,         "popl\t" OP_RM32),
	I(0x8f, IF_67|IF_REXW|IF_MODRM, "popq\t" OP_RM64),

	I(0x90, 0,                "nop"),
	I(0x90, IF_F3,            "pause"),

	I(0x90, IF_REXR|IF_66,    "xchgw\t" OP_R8W OP_AX),
	I(0x90, IF_REXR,          "xchgl\t" OP_R8D OP_EAX),
	I(0x90, IF_REXR|IF_REXW,  "xchgq\t" OP_X64_R8 OP_RAX),
	I(0x90, IF_66,            "xchgw\t" OP_AX  OP_AX),
/*  I(0x90, 0,                "xchgl\t" OP_EAX OP_EAX), */
	I(0x90, IF_REXW,          "xchgq\t" OP_RAX OP_RAX),
	I(0x91, IF_REXR|IF_66,    "xchgw\t" OP_R9W OP_AX),
	I(0x91, IF_REXR,          "xchgl\t" OP_R9D OP_EAX),
	I(0x91, IF_REXR|IF_REXW,  "xchgq\t" OP_R9  OP_RAX),
	I(0x91, IF_66,            "xchgw\t" OP_CX  OP_AX),
	I(0x91, 0,                "xchgl\t" OP_ECX OP_EAX),
	I(0x91, IF_REXW,          "xchgq\t" OP_RCX OP_RAX),
	I(0x92, IF_REXR|IF_66,    "xchgw\t" OP_R10W OP_AX),
	I(0x92, IF_REXR,          "xchgl\t" OP_R10D OP_EAX),
	I(0x92, IF_REXR|IF_REXW,  "xchgq\t" OP_R10 OP_RAX),
	I(0x92, IF_66,            "xchgw\t" OP_DX  OP_AX),
	I(0x92, 0,                "xchgl\t" OP_EDX OP_EAX),
	I(0x92, IF_REXW,          "xchgq\t" OP_RDX OP_RAX),
	I(0x93, IF_REXR|IF_66,    "xchgw\t" OP_R11W OP_AX),
	I(0x93, IF_REXR,          "xchgl\t" OP_R11D OP_EAX),
	I(0x93, IF_REXR|IF_REXW,  "xchgq\t" OP_R11 OP_RAX),
	I(0x93, IF_66,            "xchgw\t" OP_BX  OP_AX),
	I(0x93, 0,                "xchgl\t" OP_EBX OP_EAX),
	I(0x93, IF_REXW,          "xchgq\t" OP_RBX OP_RAX),
	I(0x94, IF_REXR|IF_66,    "xchgw\t" OP_R12W OP_AX),
	I(0x94, IF_REXR,          "xchgl\t" OP_R12D OP_EAX),
	I(0x94, IF_REXR|IF_REXW,  "xchgq\t" OP_R12 OP_RAX),
	I(0x94, IF_66,            "xchgw\t" OP_SP  OP_AX),
	I(0x94, 0,                "xchgl\t" OP_ESP OP_EAX),
	I(0x94, IF_REXW,          "xchgq\t" OP_RSP OP_RAX),
	I(0x95, IF_REXR|IF_66,    "xchgw\t" OP_R13W OP_AX),
	I(0x95, IF_REXR,          "xchgl\t" OP_R13D OP_EAX),
	I(0x95, IF_REXR|IF_REXW,  "xchgq\t" OP_R13 OP_RAX),
	I(0x95, IF_66,            "xchgw\t" OP_BP  OP_AX),
	I(0x95, 0,                "xchgl\t" OP_EBP OP_EAX),
	I(0x95, IF_REXW,          "xchgq\t" OP_RBP OP_RAX),
	I(0x96, IF_REXR|IF_66,    "xchgw\t" OP_R14W OP_AX),
	I(0x96, IF_REXR,          "xchgl\t" OP_R14D OP_EAX),
	I(0x96, IF_REXR|IF_REXW,  "xchgq\t" OP_R14 OP_RAX),
	I(0x96, IF_66,            "xchgw\t" OP_DI  OP_AX),
	I(0x96, 0,                "xchgl\t" OP_EDI OP_EAX),
	I(0x96, IF_REXW,          "xchgq\t" OP_RDI OP_RAX),
	I(0x97, IF_REXR|IF_66,    "xchgw\t" OP_R15W OP_AX),
	I(0x97, IF_REXR,          "xchgl\t" OP_R15D OP_EAX),
	I(0x97, IF_REXR|IF_REXW,  "xchgq\t" OP_R15 OP_RAX),
	I(0x97, IF_66,            "xchgw\t" OP_SI  OP_AX),
	I(0x97, 0,                "xchgl\t" OP_ESI OP_EAX),
	I(0x97, IF_REXW,          "xchgq\t" OP_RSI OP_RAX),

	I(0x98, 0,                "cbw"),
	I(0x99, IF_66,            "cwd"),
	I(0x99, 0,                "cdq"),
	I(0x9a, IF_67,            "lcallw\t" OP_LJMP),
	I(0x9a, 0,                "lcalll\t" OP_LJMP),

	I(0x9b, IF_66,            "wait"),
	I(0x9b, 0,                "fwait"),

	I(0x9c, IF_66,            "pushfw"),
	I(0x9c, IF_X32,           "pushfl"),
	I(0x9c, IF_X64,           "pushfq"),
	I(0x9d, IF_66,            "popfw"),
	I(0x9d, IF_X32,           "popfl"),
	I(0x9d, IF_X64,           "popfq"),

	I(0x9e, 0,                "sahf"),
	I(0x9f, 0,                "lahf"),

	I(0xa0, 0,                "movb\t" OP_MOFFS8 OP_AL),
	I(0xa0, IF_REXW,          "movb\t" OP_MOFFS8 OP_AL),   /* XXX: This variant ignores segment overrides... */
	I(0xa1, IF_67|IF_66,      "movw\t" OP_MOFFS16 OP_AX),
	I(0xa1, IF_67,            "movl\t" OP_MOFFS16 OP_EAX),
	I(0xa1, IF_66,            "movw\t" OP_MOFFS32 OP_AX),
	I(0xa1, 0,                "movl\t" OP_MOFFS32 OP_EAX),
	I(0xa2, 0,                "movb\t" OP_AL OP_MOFFS8),
	I(0xa2, IF_REXW,          "movb\t" OP_AL OP_MOFFS8),   /* XXX: This variant ignores segment overrides... */
	I(0xa3, IF_67|IF_66,      "movw\t" OP_AX OP_MOFFS16),
	I(0xa3, IF_67,            "movl\t" OP_EAX OP_MOFFS16),
	I(0xa3, IF_66,            "movw\t" OP_AX OP_MOFFS32),
	I(0xa3, 0,                "movl\t" OP_EAX OP_MOFFS32),

	I(0xa4, 0,                "movsb"),
	I(0xa4, IF_F3,            "rep movsb"),
	I(0xa5, IF_66,            "movsw"),
	I(0xa5, 0,                "movsl"),
	I(0xa5, IF_REXW,          "movsq"),
	I(0xa5, IF_F3|IF_66,      "rep movsw"),
	I(0xa5, IF_F3,            "rep movsl"),
	I(0xa5, IF_F3|IF_REXW,    "rep movsq"),

	I(0xa6, 0,                "cmpsb"),
	I(0xa6, IF_F2,            "repne cmpsb"),
	I(0xa6, IF_F3,            "repe cmpsb"),
	I(0xa7, IF_66,            "cmpsw"),
	I(0xa7, 0,                "cmpsl"),
	I(0xa7, IF_REXW,          "cmpsq"),
	I(0xa7, IF_F2|IF_66,      "repne cmpsw"),
	I(0xa7, IF_F3|IF_66,      "repe cmpsw"),
	I(0xa7, IF_F2,            "repne cmpsl"),
	I(0xa7, IF_F3,            "repe cmpsl"),
	I(0xa7, IF_F2|IF_REXW,    "repne cmpsq"),
	I(0xa7, IF_F3|IF_REXW,    "repe cmpsq"),

	I(0xa8, 0,                "testb\t" OP_U8 OP_AL),
	I(0xa9, IF_66,            "testw\t" OP_U16 OP_AX),
	I(0xa9, 0,                "testl\t" OP_U32 OP_EAX),
	I(0xa9, IF_REXW,          "testq\t" OP_S32 OP_RAX),

	I(0xaa, 0,                "stosb"),
	I(0xaa, IF_F3,            "rep stosb"),
	I(0xab, IF_66,            "stosw"),
	I(0xab, 0,                "stosl"),
	I(0xab, IF_REXW,          "stosq"),
	I(0xab, IF_F3|IF_66,      "rep stosw"),
	I(0xab, IF_F3,            "rep stosl"),
	I(0xab, IF_F3|IF_REXW,    "rep stosq"),

	I(0xac, 0,                "lodsb"),
	I(0xac, IF_F3,            "rep lodsb"),
	I(0xad, IF_66,            "lodsw"),
	I(0xad, 0,                "lodsl"),
	I(0xad, IF_REXW,          "lodsq"),
	I(0xad, IF_F3|IF_66,      "rep lodsw"),
	I(0xad, IF_F3,            "rep lodsl"),
	I(0xad, IF_F3|IF_REXW,    "rep lodsq"),

	I(0xae, 0,                "scasb"),
	I(0xae, IF_F2,            "repne scasb"),
	I(0xae, IF_F3,            "repe scasb"),
	I(0xaf, IF_66,            "scasw"),
	I(0xaf, 0,                "scasl"),
	I(0xaf, IF_REXW,          "scasq"),
	I(0xaf, IF_F2|IF_66,      "repne scasw"),
	I(0xaf, IF_F3|IF_66,      "repe scasw"),
	I(0xaf, IF_F2,            "repne scasl"),
	I(0xaf, IF_F3,            "repe scasl"),
	I(0xaf, IF_F2|IF_REXW,    "repne scasq"),
	I(0xaf, IF_F3|IF_REXW,    "repe scasq"),

	I(0xb0, IF_REXR,          "movb\t" OP_U8 OP_R8D),
	I(0xb0, 0,                "movb\t" OP_U8 OP_AL),
	I(0xb1, IF_REXR,          "movb\t" OP_U8 OP_R9D),
	I(0xb1, 0,                "movb\t" OP_U8 OP_CL),
	I(0xb2, IF_REXR,          "movb\t" OP_U8 OP_R10D),
	I(0xb2, 0,                "movb\t" OP_U8 OP_DL),
	I(0xb3, IF_REXR,          "movb\t" OP_U8 OP_R11D),
	I(0xb3, 0,                "movb\t" OP_U8 OP_BL),
	I(0xb4, IF_REXR,          "movb\t" OP_U8 OP_R12D),
	I(0xb4, 0,                "movb\t" OP_U8 OP_AH),
	I(0xb5, IF_REXR,          "movb\t" OP_U8 OP_R13D),
	I(0xb5, 0,                "movb\t" OP_U8 OP_CH),
	I(0xb6, IF_REXR,          "movb\t" OP_U8 OP_R14D),
	I(0xb6, 0,                "movb\t" OP_U8 OP_DH),
	I(0xb7, IF_REXR,          "movb\t" OP_U8 OP_R15D),
	I(0xb7, 0,                "movb\t" OP_U8 OP_BH),

	I(0xb8, IF_REXR|IF_66,    "movw\t"   OP_U16 OP_R8W),
	I(0xb8, IF_REXR,          "movl\t"   OP_U32 OP_R8D),
	I(0xb8, IF_REXR|IF_REXW,  "movabs\t" OP_U64 OP_X64_R8),
	I(0xb8, IF_66,            "movw\t"   OP_U16 OP_AX),
	I(0xb8, 0,                "movl\t"   OP_U32 OP_EAX),
	I(0xb8, IF_REXW,          "movabs\t" OP_U64 OP_RAX),
	I(0xb9, IF_REXR|IF_66,    "movw\t"   OP_U16 OP_R9W),
	I(0xb9, IF_REXR,          "movl\t"   OP_U32 OP_R9D),
	I(0xb9, IF_REXR|IF_REXW,  "movabs\t" OP_U64 OP_R9),
	I(0xb9, IF_66,            "movw\t"   OP_U16 OP_CX),
	I(0xb9, 0,                "movl\t"   OP_U32 OP_ECX),
	I(0xb9, IF_REXW,          "movabs\t" OP_U64 OP_RCX),
	I(0xba, IF_REXR|IF_66,    "movw\t"   OP_U16 OP_R10W),
	I(0xba, IF_REXR,          "movl\t"   OP_U32 OP_R10D),
	I(0xba, IF_REXR|IF_REXW,  "movabs\t" OP_U64 OP_R10),
	I(0xba, IF_66,            "movw\t"   OP_U16 OP_DX),
	I(0xba, 0,                "movl\t"   OP_U32 OP_EDX),
	I(0xba, IF_REXW,          "movabs\t" OP_U64 OP_RDX),
	I(0xbb, IF_REXR|IF_66,    "movw\t"   OP_U16 OP_R11W),
	I(0xbb, IF_REXR,          "movl\t"   OP_U32 OP_R11D),
	I(0xbb, IF_REXR|IF_REXW,  "movabs\t" OP_U64 OP_R11),
	I(0xbb, IF_66,            "movw\t"   OP_U16 OP_BX),
	I(0xbb, 0,                "movl\t"   OP_U32 OP_EBX),
	I(0xbb, IF_REXW,          "movabs\t" OP_U64 OP_RBX),
	I(0xbc, IF_REXR|IF_66,    "movw\t"   OP_U16 OP_R12W),
	I(0xbc, IF_REXR,          "movl\t"   OP_U32 OP_R12D),
	I(0xbc, IF_REXR|IF_REXW,  "movabs\t" OP_U64 OP_R12),
	I(0xbc, IF_66,            "movw\t"   OP_U16 OP_SP),
	I(0xbc, 0,                "movl\t"   OP_U32 OP_ESP),
	I(0xbc, IF_REXW,          "movabs\t" OP_U64 OP_RSP),
	I(0xbd, IF_REXR|IF_66,    "movw\t"   OP_U16 OP_R13W),
	I(0xbd, IF_REXR,          "movl\t"   OP_U32 OP_R13D),
	I(0xbd, IF_REXR|IF_REXW,  "movabs\t" OP_U64 OP_R13),
	I(0xbd, IF_66,            "movw\t"   OP_U16 OP_BP),
	I(0xbd, 0,                "movl\t"   OP_U32 OP_EBP),
	I(0xbd, IF_REXW,          "movabs\t" OP_U64 OP_RBP),
	I(0xbe, IF_REXR|IF_66,    "movw\t"   OP_U16 OP_R14W),
	I(0xbe, IF_REXR,          "movl\t"   OP_U32 OP_R14D),
	I(0xbe, IF_REXR|IF_REXW,  "movabs\t" OP_U64 OP_R14),
	I(0xbe, IF_66,            "movw\t"   OP_U16 OP_DI),
	I(0xbe, 0,                "movl\t"   OP_U32 OP_EDI),
	I(0xbe, IF_REXW,          "movabs\t" OP_U64 OP_RDI),
	I(0xbf, IF_REXR|IF_66,    "movw\t"   OP_U16 OP_R15W),
	I(0xbf, IF_REXR,          "movl\t"   OP_U32 OP_R15D),
	I(0xbf, IF_REXR|IF_REXW,  "movabs\t" OP_U64 OP_R15),
	I(0xbf, IF_66,            "movw\t"   OP_U16 OP_SI),
	I(0xbf, 0,                "movl\t"   OP_U32 OP_ESI),
	I(0xbf, IF_REXW,          "movabs\t" OP_U64 OP_RSI),

	I(0xc0, IF_MODRM|IF_REG0, "rolb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG1, "rorb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG2, "rclb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG3, "rcrb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG4, "salb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG5, "shrb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG6, "shlb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG7, "sarb\t" OP_U8 OP_RM8),

	I(0xc1, IF_66|IF_MODRM|IF_REG0, "rolw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG0, "roll\t" OP_U8 OP_RM32),
	I(0xc1, IF_REXW|IF_MODRM|IF_REG0, "rolq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG1, "rorw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG1, "rorl\t" OP_U8 OP_RM32),
	I(0xc1, IF_REXW|IF_MODRM|IF_REG1, "rorq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG2, "rclw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG2, "rcll\t" OP_U8 OP_RM32),
	I(0xc1, IF_REXW|IF_MODRM|IF_REG2, "rclq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG3, "rcrw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG3, "rcrl\t" OP_U8 OP_RM32),
	I(0xc1, IF_REXW|IF_MODRM|IF_REG3, "rcrq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG4, "salw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG4, "sall\t" OP_U8 OP_RM32),
	I(0xc1, IF_REXW|IF_MODRM|IF_REG4, "salq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG5, "shrw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG5, "shrl\t" OP_U8 OP_RM32),
	I(0xc1, IF_REXW|IF_MODRM|IF_REG5, "shrq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG6, "shlw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG6, "shll\t" OP_U8 OP_RM32),
	I(0xc1, IF_REXW|IF_MODRM|IF_REG6, "shlq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG7, "sarw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG7, "sarl\t" OP_U8 OP_RM32),
	I(0xc1, IF_REXW|IF_MODRM|IF_REG7, "sarq\t" OP_U8 OP_RM64),

	I(0xc2, IF_66,            "retw\t" OP_U16),
	I(0xc2, 0,                "ret\t" OP_U16),
	I(0xc3, IF_66,            "retw"),
	I(0xc3, 0,                "ret"),

	I(0xc4, IF_66|IF_MODRM|IF_RMM, "lesw\t" OP_RM/*32*/ OP_R16),
	I(0xc4, IF_MODRM|IF_RMM,       "lesl\t" OP_RM/*48*/ OP_R32),
	I(0xc5, IF_66|IF_MODRM|IF_RMM, "ldsw\t" OP_RM/*32*/ OP_R16),
	I(0xc5, IF_MODRM|IF_RMM,       "ldsl\t" OP_RM/*48*/ OP_R32),

	I(0xc6, IF_MODRM|IF_REG0,        "movb\t" OP_U8 OP_RM8),
	I(0xc6, IF_BYTE2,         "\xf8" "xabort\t" OP_U8),

	I(0xc7, IF_66|IF_MODRM|IF_REG0,  "movw\t" OP_U16 OP_RM16),
	I(0xc7, IF_MODRM|IF_REG0,        "movl\t" OP_U32 OP_RM32),
	I(0xc7, IF_REXW|IF_MODRM|IF_REG0,"movq\t" OP_S32 OP_RM64),
	I(0xc7, IF_BYTE2|IF_66,   "\xf8" "xabortw\t" OP_DISP16),
	I(0xc7, IF_BYTE2,         "\xf8" "xabort\t" OP_DISP32),

	I(0xc8, 0,                "enter\t" OP_U16 OP_U8),
	I(0xc9, 0,                "leave"),
	I(0xca, 0,                "lret\t" OP_U16),
	I(0xcb, 0,                "lret"),
	I(0xcc, 0,                "int3"),
	I(0xcd, 0,                "int\t" OP_U8),
	I(0xce, 0,                "into"),
	I(0xcf, IF_66,            "iretw"),
	I(0xcf, IF_X32,           "iret"),
	I(0xcf, IF_X64,           "iretl"),
	I(0xcf, IF_REXW,          "iretq"),

	I(0xd0, IF_MODRM|IF_REG0, "rolb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG1, "rorb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG2, "rclb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG3, "rcrb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG4, "shlb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG5, "shrb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG6, "salb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG7, "sarb\t" OP_IMM1 OP_RM8),

	I(0xd1, IF_66|IF_MODRM|IF_REG0, "rolw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG0, "roll\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_REXW|IF_MODRM|IF_REG0, "rolq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG1, "rorw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG1, "rorl\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_REXW|IF_MODRM|IF_REG1, "rorq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG2, "rclw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG2, "rcll\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_REXW|IF_MODRM|IF_REG2, "rclq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG3, "rcrw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG3, "rcrl\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_REXW|IF_MODRM|IF_REG3, "rcrq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG4, "shlw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG4, "shll\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_REXW|IF_MODRM|IF_REG4, "shlq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG5, "shrw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG5, "shrl\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_REXW|IF_MODRM|IF_REG5, "shrq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG6, "salw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG6, "sall\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_REXW|IF_MODRM|IF_REG6, "salq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG7, "sarw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG7, "sarl\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_REXW|IF_MODRM|IF_REG7, "sarq\t" OP_IMM1 OP_RM64),

	I(0xd2, IF_MODRM|IF_REG0, "rolb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG1, "rorb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG2, "rclb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG3, "rcrb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG4, "shlb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG5, "shrb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG6, "salb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG7, "sarb\t" OP_CL OP_RM8),

	I(0xd3, IF_66|IF_MODRM|IF_REG0, "rolw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG0, "roll\t" OP_CL OP_RM32),
	I(0xd3, IF_REXW|IF_MODRM|IF_REG0, "rolq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG1, "rorw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG1, "rorl\t" OP_CL OP_RM32),
	I(0xd3, IF_REXW|IF_MODRM|IF_REG1, "rorq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG2, "rclw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG2, "rcll\t" OP_CL OP_RM32),
	I(0xd3, IF_REXW|IF_MODRM|IF_REG2, "rclq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG3, "rcrw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG3, "rcrl\t" OP_CL OP_RM32),
	I(0xd3, IF_REXW|IF_MODRM|IF_REG3, "rcrq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG4, "shlw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG4, "shll\t" OP_CL OP_RM32),
	I(0xd3, IF_REXW|IF_MODRM|IF_REG4, "shlq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG5, "shrw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG5, "shrl\t" OP_CL OP_RM32),
	I(0xd3, IF_REXW|IF_MODRM|IF_REG5, "shrq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG6, "salw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG6, "sall\t" OP_CL OP_RM32),
	I(0xd3, IF_REXW|IF_MODRM|IF_REG6, "salq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG7, "sarw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG7, "sarl\t" OP_CL OP_RM32),
	I(0xd3, IF_REXW|IF_MODRM|IF_REG7, "sarq\t" OP_CL OP_RM64),

	I(0xd4, 0,                "aam\t" OP_U8),
	I(0xd5, 0,                "aad\t" OP_U8),
	I(0xd6, 0,                "salc"),
	I(0xd7, 0,                "xlatb"),

	I(0xd8, IF_MODRM|IF_RMR|IF_REG0, "fadd\t" OP_RMSTi OP_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG0, "faddl\t" OP_RMSTi /*OP_ST0*/),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG1, "fmul\t" OP_RMSTi OP_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG1, "fmull\t" OP_RM32 /*OP_ST0*/),

	I(0xd8, IF_MODRM|IF_RMR|IF_REG2, "fcom\t" OP_RMSTi /*OP_ST0*/),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG2, "fcoml\t" OP_RM32 /*OP_ST0*/),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG3, "fcomp\t" OP_RMSTi /*OP_ST0*/),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG3, "fcompl\t" OP_RM32 /*OP_ST0*/),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG4, "fsub\t" OP_RMSTi OP_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG4, "fsubl\t" OP_RM32 /*OP_ST0*/),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG5, "fsubr\t" OP_RMSTi OP_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG5, "fsubrl\t" OP_RM32 /*OP_ST0*/),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG6, "fdiv\t" OP_RMSTi /*OP_ST0*/),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG6, "fdivl\t" OP_RM32 /*OP_ST0*/),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG7, "fdivr\t" OP_RMSTi /*OP_ST0*/),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG7, "fdivrl\t" OP_RM32 /*OP_ST0*/),

	I(0xd9, IF_BYTE2,        "\xc0" "fld" OP_ST0),
	I(0xd9, IF_BYTE2,        "\xc1" "fld" OP_ST1),
	I(0xd9, IF_BYTE2,        "\xc2" "fld" OP_ST2),
	I(0xd9, IF_BYTE2,        "\xc3" "fld" OP_ST3),
	I(0xd9, IF_BYTE2,        "\xc4" "fld" OP_ST4),
	I(0xd9, IF_BYTE2,        "\xc5" "fld" OP_ST5),
	I(0xd9, IF_BYTE2,        "\xc6" "fld" OP_ST6),
	I(0xd9, IF_BYTE2,        "\xc7" "fld" OP_ST7),
	I(0xd9, IF_BYTE2,        "\xc8" "fxch" OP_ST0),
	I(0xd9, IF_BYTE2,        "\xc9" "fxch" OP_ST1),
	I(0xd9, IF_BYTE2,        "\xca" "fxch" OP_ST2),
	I(0xd9, IF_BYTE2,        "\xcb" "fxch" OP_ST3),
	I(0xd9, IF_BYTE2,        "\xcc" "fxch" OP_ST4),
	I(0xd9, IF_BYTE2,        "\xcd" "fxch" OP_ST5),
	I(0xd9, IF_BYTE2,        "\xce" "fxch" OP_ST6),
	I(0xd9, IF_BYTE2,        "\xcf" "fxch" OP_ST7),
	I(0xd9, IF_BYTE2,        "\xd0" "fnop"),
	I(0xd9, IF_BYTE2,        "\xe0" "fchs"),
	I(0xd9, IF_BYTE2,        "\xe1" "fabs"),
	I(0xd9, IF_BYTE2,        "\xe4" "ftst"),
	I(0xd9, IF_BYTE2,        "\xe5" "fxam"),
	I(0xd9, IF_BYTE2,        "\xe8" "fld1"),
	I(0xd9, IF_BYTE2,        "\xe9" "fldl2t"),
	I(0xd9, IF_BYTE2,        "\xea" "fldl2e"),
	I(0xd9, IF_BYTE2,        "\xeb" "fldpi"),
	I(0xd9, IF_BYTE2,        "\xec" "fldlg2"),
	I(0xd9, IF_BYTE2,        "\xed" "fldln2"),
	I(0xd9, IF_BYTE2,        "\xee" "fldz"),
	I(0xd9, IF_BYTE2,        "\xf0" "f2xm1"),
	I(0xd9, IF_BYTE2,        "\xf1" "fyl2x"),
	I(0xd9, IF_BYTE2,        "\xf2" "fptan"),
	I(0xd9, IF_BYTE2,        "\xf3" "fpatan"),
	I(0xd9, IF_BYTE2,        "\xf4" "fxtract"),
	I(0xd9, IF_BYTE2,        "\xf5" "fprem1"),
	I(0xd9, IF_BYTE2,        "\xf6" "fdecstp"),
	I(0xd9, IF_BYTE2,        "\xf7" "fincstp"),
	I(0xd9, IF_BYTE2,        "\xf8" "fprem"),
	I(0xd9, IF_BYTE2,        "\xf9" "fyl2xp1"),
	I(0xd9, IF_BYTE2,        "\xfa" "fsqrt"),
	I(0xd9, IF_BYTE2,        "\xfb" "fsincos"),
	I(0xd9, IF_BYTE2,        "\xfc" "frndint"),
	I(0xd9, IF_BYTE2,        "\xfd" "fscale"),
	I(0xd9, IF_BYTE2,        "\xfe" "fsin"),
	I(0xd9, IF_BYTE2,        "\xff" "fcos"),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG0, "fldl\t" OP_RM32),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG2, "fstl\t" OP_RM32),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG3, "fstpl\t" OP_RM32),
	I(0xd9, IF_66|IF_MODRM|IF_RMM|IF_REG4, "fldenv14\t" OP_RM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG4, "fldenv28\t" OP_RM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG5, "fldcww\t" OP_RM16),
	I(0xd9, IF_66|IF_MODRM|IF_RMM|IF_REG6, "fnstenv94\t" OP_RM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG6, "fnstenv108\t" OP_RM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG7, "fnstcww\t" OP_RM16),

	I(0xda, IF_BYTE2, "\xe9" "fucompp\t" /*OP_ST1 OP_ST0*/),
	I(0xda, IF_MODRM|IF_RMM|IF_REG0, "fiaddl\t" OP_RM32 /*OP_ST0*/),
	I(0xda, IF_MODRM|IF_RMR|IF_REG0, "fcmovb\t" OP_RMSTi OP_ST0),
	I(0xda, IF_MODRM|IF_RMR|IF_REG1, "fcmove\t" OP_RMSTi OP_ST0),
	I(0xda, IF_MODRM|IF_RMR|IF_REG2, "fcmovbe\t" OP_RMSTi OP_ST0),
	I(0xda, IF_MODRM|IF_RMR|IF_REG3, "fcmovu\t" OP_RMSTi OP_ST0),

	I(0xda, IF_MODRM|IF_RMM|IF_REG1, "fimull\t" OP_RM32 /*OP_ST0*/),
	I(0xda, IF_MODRM|IF_RMM|IF_REG2, "ficoml\t" OP_RM32 /*OP_ST0*/),
	I(0xda, IF_MODRM|IF_RMM|IF_REG3, "ficompl\t" OP_RM32 /*OP_ST0*/),
	I(0xda, IF_MODRM|IF_RMM|IF_REG4, "fisubl\t" OP_RM32 /*OP_ST0*/),
	I(0xda, IF_MODRM|IF_RMM|IF_REG5, "fisubrl\t" OP_RM32 /*OP_ST0*/),
	I(0xda, IF_MODRM|IF_RMM|IF_REG6, "fidivl\t" OP_RM32 /*OP_ST0*/),
	I(0xda, IF_MODRM|IF_RMM|IF_REG7, "fidivrl\t" OP_RM32 /*OP_ST0*/),

	I(0xdb, IF_BYTE2,  "\xe2" "fnclex"),
	I(0xdb, IF_BYTE2,  "\xe3" "fninit"),
	I(0xdb, IF_BYTE2,  "\xe8" "fucomi" OP_ST0 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xe9" "fucomi" OP_ST1 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xea" "fucomi" OP_ST2 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xeb" "fucomi" OP_ST3 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xec" "fucomi" OP_ST4 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xed" "fucomi" OP_ST5 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xee" "fucomi" OP_ST6 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xef" "fucomi" OP_ST7 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf0" "fcomi" OP_ST0 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf1" "fcomi" OP_ST1 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf2" "fcomi" OP_ST2 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf3" "fcomi" OP_ST3 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf4" "fcomi" OP_ST4 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf5" "fcomi" OP_ST5 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf6" "fcomi" OP_ST6 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf7" "fcomi" OP_ST7 OP_ST0),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG0, "fildl\t" OP_RM32),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG1, "fisttpl\t" OP_RM32),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG2, "fistl\t" OP_RM32),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG3, "fistpl\t" OP_RM32),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG5, "fld80" OP_RM),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG7, "fstp80" OP_RM),

	I(0xdc, IF_MODRM|IF_RMR|IF_REG0, "fadd\t" OP_ST0 OP_RMSTi),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG0, "faddq\t" OP_RM64 /*OP_ST0*/),
	I(0xdc, IF_MODRM|IF_RMR|IF_REG1, "fmul\t" OP_ST0 OP_RMSTi),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG1, "fmulq\t" OP_RM64 /*OP_ST0*/),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG2, "fcomq\t" OP_RM64 /*OP_ST0*/),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG3, "fcompq\t" OP_RM64 /*OP_ST0*/),
	I(0xdc, IF_MODRM|IF_RMR|IF_REG4, "fsub\t" OP_ST0 OP_RMSTi),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG4, "fsubq\t" OP_RM64 /*OP_ST0*/),
	I(0xdc, IF_MODRM|IF_RMR|IF_REG5, "fsubr\t" OP_ST0 OP_RMSTi),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG5, "fsubrq\t" OP_RM64 /*OP_ST0*/),
	I(0xdc, IF_MODRM|IF_RMR|IF_REG6, "fdiv\t" OP_RMSTi /*OP_ST0*/),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG6, "fdivq\t" OP_RM64 /*OP_ST0*/),
	I(0xdc, IF_MODRM|IF_RMR|IF_REG7, "fdivr\t" OP_RMSTi /*OP_ST0*/),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG7, "fdivrq\t" OP_RM64 /*OP_ST0*/),

	I(0xdd, IF_BYTE2, "\xc0" "ffree\t" OP_ST0),
	I(0xdd, IF_BYTE2, "\xc1" "ffree\t" OP_ST1),
	I(0xdd, IF_BYTE2, "\xc2" "ffree\t" OP_ST2),
	I(0xdd, IF_BYTE2, "\xc3" "ffree\t" OP_ST3),
	I(0xdd, IF_BYTE2, "\xc4" "ffree\t" OP_ST4),
	I(0xdd, IF_BYTE2, "\xc5" "ffree\t" OP_ST5),
	I(0xdd, IF_BYTE2, "\xc6" "ffree\t" OP_ST6),
	I(0xdd, IF_BYTE2, "\xc7" "ffree\t" OP_ST7),
	I(0xdd, IF_BYTE2, "\xe0" "fucom\t" OP_ST0),
	I(0xdd, IF_BYTE2, "\xe1" "fucom\t" OP_ST1),
	I(0xdd, IF_BYTE2, "\xe2" "fucom\t" OP_ST2),
	I(0xdd, IF_BYTE2, "\xe3" "fucom\t" OP_ST3),
	I(0xdd, IF_BYTE2, "\xe4" "fucom\t" OP_ST4),
	I(0xdd, IF_BYTE2, "\xe5" "fucom\t" OP_ST5),
	I(0xdd, IF_BYTE2, "\xe6" "fucom\t" OP_ST6),
	I(0xdd, IF_BYTE2, "\xe7" "fucom\t" OP_ST7),
	I(0xdd, IF_BYTE2, "\xe8" "fucomp\t" OP_ST0),
	I(0xdd, IF_BYTE2, "\xe9" "fucomp\t" OP_ST1),
	I(0xdd, IF_BYTE2, "\xea" "fucomp\t" OP_ST2),
	I(0xdd, IF_BYTE2, "\xeb" "fucomp\t" OP_ST3),
	I(0xdd, IF_BYTE2, "\xec" "fucomp\t" OP_ST4),
	I(0xdd, IF_BYTE2, "\xed" "fucomp\t" OP_ST5),
	I(0xdd, IF_BYTE2, "\xee" "fucomp\t" OP_ST6),
	I(0xdd, IF_BYTE2, "\xef" "fucomp\t" OP_ST7),

	I(0xdd, IF_MODRM|IF_RMM|IF_REG0, "fldq" OP_RM64),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG1, "fisttpq\t" OP_RM64),
	I(0xdd, IF_MODRM|IF_RMR|IF_REG2, "fst\t" OP_RMSTi),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG2, "fstq\t" OP_RM64),
	I(0xdd, IF_MODRM|IF_RMR|IF_REG3, "fstp\t" OP_RMSTi),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG3, "fstpq\t" OP_RM64),
	I(0xdd, IF_66|IF_MODRM|IF_RMM|IF_REG4, "frstor94\t" OP_RM),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG4, "frstor108\t" OP_RM),
	I(0xdd, IF_66|IF_MODRM|IF_RMM|IF_REG6, "fnsave94\t" OP_RM),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG6, "fnsave108\t" OP_RM),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG7, "fnstcww\t" OP_RM16),

	I(0xde, IF_BYTE2, "\xd9" "fcompp\t" /*OP_ST1*/ /*OP_ST0*/),

	I(0xde, IF_MODRM|IF_RMR|IF_REG0, "faddp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG0, "fiaddw\t" OP_RM16 /*OP_ST0*/),
	I(0xde, IF_MODRM|IF_RMR|IF_REG1, "fmulp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG1, "fimulw\t" OP_RM16 /*OP_ST0*/),
	I(0xde, IF_MODRM|IF_RMM|IF_REG2, "ficomw\t" OP_RM16 /*OP_ST0*/),
	I(0xde, IF_MODRM|IF_RMM|IF_REG3, "ficompw\t" OP_RM16 /*OP_ST0*/),
	I(0xde, IF_MODRM|IF_RMR|IF_REG4, "fsubp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG4, "fisubw\t" OP_RM16 /*OP_ST0*/),
	I(0xde, IF_MODRM|IF_RMR|IF_REG5, "fsubrp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG5, "fisubrw\t" OP_RM16 /*OP_ST0*/),
	I(0xde, IF_MODRM|IF_RMR|IF_REG6, "fdivp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG6, "fidivw\t" OP_RM16 /*OP_ST0*/),
	I(0xde, IF_MODRM|IF_RMR|IF_REG7, "fdivrp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG7, "fidivrw\t" OP_RM16 /*OP_ST0*/),

	I(0xdf, IF_BYTE2,  "\xe0" "fnstsw" OP_AX),
	I(0xdf, IF_BYTE2,  "\xe8" "fucomip" OP_ST0 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xe9" "fucomip" OP_ST1 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xea" "fucomip" OP_ST2 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xeb" "fucomip" OP_ST3 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xec" "fucomip" OP_ST4 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xed" "fucomip" OP_ST5 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xee" "fucomip" OP_ST6 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xef" "fucomip" OP_ST7 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf0" "fcomip" OP_ST0 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf1" "fcomip" OP_ST1 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf2" "fcomip" OP_ST2 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf3" "fcomip" OP_ST3 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf4" "fcomip" OP_ST4 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf5" "fcomip" OP_ST5 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf6" "fcomip" OP_ST6 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf7" "fcomip" OP_ST7 OP_ST0),

	I(0xdf, IF_MODRM|IF_RMM|IF_REG0, "fildw\t" OP_RM16),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG1, "fisttpw\t" OP_RM16),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG2, "fistw\t" OP_RM16),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG3, "fistpw\t" OP_RM16),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG4, "fbld\t" OP_RM),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG5, "fildq\t" OP_RM64),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG6, "fbstp\t" OP_RM),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG7, "fistpq\t" OP_RM64),


	I(0xe0, 0,                "loopnz\t" OP_DISP8),
	I(0xe1, 0,                "loopz\t" OP_DISP8),
	I(0xe2, 0,                "loop\t" OP_DISP8),
	I(0xe3, IF_66,            "jcxz\t" OP_DISP8),
	I(0xe3, 0,                "jecxz\t" OP_DISP8),
	I(0xe3, IF_REXW,          "jrcxz\t" OP_DISP8),

	I(0xe4, 0,                "inb\t" OP_U8 OP_AL),
	I(0xe5, IF_66,            "inw\t" OP_U8 OP_AX),
	I(0xe5, 0,                "inl\t" OP_U8 OP_EAX),
	I(0xe6, 0,                "outb\t" OP_AL OP_U8),
	I(0xe7, IF_66,            "outw\t" OP_AX OP_U8),
	I(0xe7, 0,                "outl\t" OP_EAX OP_U8),
	/* NOTE: Ignore 66h prefix on x86_64. (the hardware does the same!)
	 *       However, only Intel ignores it. - AMD still obeys the 66h
	 *       prefix and truncates the operand to 16 bits */
#if 1
	I(0xe8, IF_66|IF_X32,     "callw\t" OP_DISP16),
	I(0xe8, 0,                "call\t" OP_DISP32),
	I(0xe9, IF_66|IF_X32,     "jmpw\t" OP_DISP16),
	I(0xe9, 0,                "jmp\t" OP_DISP32),
#else
/*	I(0xe8, IF_66,            "callw\t" OP_DISP16), */
/*	I(0xe8, 0,                "call\t" OP_DISP32), */
/*	I(0xe9, IF_66,            "jmpw\t" OP_DISP16), */
/*	I(0xe9, 0,                "jmp\t" OP_DISP32), */
#endif
	I(0xea, IF_67,            "ljmpw\t" OP_LJMP),
	I(0xea, 0,                "ljmpl\t" OP_LJMP),
	I(0xeb, 0,                "jmp\t" OP_DISP8),
	I(0xec, 0,                "inb\t" OP_DX OP_AL),
	I(0xed, IF_66,            "inw\t" OP_DX OP_AX),
	I(0xed, 0,                "inl\t" OP_DX OP_EAX),
	I(0xee, 0,                "outb\t" OP_AL OP_DX),
	I(0xef, IF_66,            "outw\t" OP_AX OP_DX),
	I(0xef, 0,                "outl\t" OP_EAX OP_DX),

	/* 0xf0 -- PREFIX */

	I(0xf1, 0,                "int1"),

	/* 0xf2 -- PREFIX */
	/* 0xf3 -- PREFIX */

	I(0xf4, 0,                "hlt"),

	I(0xf5, 0,                "cmc"),

	I(0xf6, IF_MODRM|IF_REG0, "testb\t" OP_U8 OP_RM8),
	I(0xf6, IF_MODRM|IF_REG1, "testb\t" OP_U8 OP_RM8), /* Undocumented alias */
	I(0xf6, IF_MODRM|IF_REG2, "notb\t" OP_RM8),
	I(0xf6, IF_MODRM|IF_REG3, "negb\t" OP_RM8),
	I(0xf6, IF_MODRM|IF_REG4, "mulb\t" OP_RM8),
	I(0xf6, IF_MODRM|IF_REG5, "imulb\t" OP_RM8),
	I(0xf6, IF_MODRM|IF_REG6, "divb\t" OP_RM8),
	I(0xf6, IF_MODRM|IF_REG7, "idivb\t" OP_RM8),

	I(0xf7, IF_66|IF_MODRM|IF_REG0, "testw\t" OP_U16 OP_RM16),
	I(0xf7, IF_MODRM|IF_REG0, "testl\t" OP_U32 OP_RM32),
	I(0xf7, IF_REXW|IF_MODRM|IF_REG0, "testq\t" OP_S32 OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG1, "testw\t" OP_U16 OP_RM16), /* Undocumented alias */
	I(0xf7, IF_MODRM|IF_REG1, "testl\t" OP_U32 OP_RM32), /* Undocumented alias */
	I(0xf7, IF_REXW|IF_MODRM|IF_REG1, "testq\t" OP_S32 OP_RM64), /* Undocumented alias */

	I(0xf7, IF_66|IF_MODRM|IF_REG2, "notw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG2, "notl\t" OP_RM32),
	I(0xf7, IF_REXW|IF_MODRM|IF_REG2, "notq\t" OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG3, "negw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG3, "negl\t" OP_RM32),
	I(0xf7, IF_REXW|IF_MODRM|IF_REG3, "negq\t" OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG4, "mulw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG4, "mull\t" OP_RM32),
	I(0xf7, IF_REXW|IF_MODRM|IF_REG4, "mulq\t" OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG5, "imulw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG5, "imull\t" OP_RM32),
	I(0xf7, IF_REXW|IF_MODRM|IF_REG5, "imulq\t" OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG6, "divw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG6, "divl\t" OP_RM32),
	I(0xf7, IF_REXW|IF_MODRM|IF_REG6, "divq\t" OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG7, "idivw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG7, "idivl\t" OP_RM32),
	I(0xf7, IF_REXW|IF_MODRM|IF_REG7, "idivq\t" OP_RM64),

	I(0xf8, 0,                "clc"),
	I(0xf9, 0,                "stc"),
	I(0xfa, 0,                "cli"),
	I(0xfb, 0,                "sti"),
	I(0xfc, 0,                "cld"),
	I(0xfd, 0,                "std"),

	I(0xfe, IF_MODRM|IF_REG0, "incb\t" OP_RM8),
	I(0xfe, IF_MODRM|IF_REG1, "decb\t" OP_RM8),

	I(0xff, IF_66|IF_MODRM|IF_REG0, "incw\t" OP_RM16),
	I(0xff, IF_MODRM|IF_REG0, "incl\t" OP_RM32),
	I(0xff, IF_REXW|IF_MODRM|IF_REG0, "incq\t" OP_RM64),

	I(0xff, IF_66|IF_MODRM|IF_REG1, "decw\t" OP_RM16),
	I(0xff, IF_MODRM|IF_REG1, "decl\t" OP_RM32),
	I(0xff, IF_REXW|IF_MODRM|IF_REG1, "decq\t" OP_RM64),

	I(0xff, IF_66|IF_MODRM|IF_REG2, "callw\t" OP_XRM16),
	I(0xff, IF_MODRM|IF_REG2, "calll\t" OP_XRM32),
	I(0xff, IF_REXW|IF_MODRM|IF_REG2, "callq\t" OP_XRM64),

	I(0xff, IF_RMM|IF_66|IF_MODRM|IF_REG3, "lcallw\t" OP_XRM16),
	I(0xff, IF_RMM|IF_MODRM|IF_REG3, "lcalll\t" OP_XRM32),
	I(0xff, IF_RMM|IF_REXW|IF_MODRM|IF_REG3, "lcallq\t" OP_XRM64),

	I(0xff, IF_66|IF_MODRM|IF_REG4, "jmpw\t" OP_XRM16),
	I(0xff, IF_MODRM|IF_REG4, "jmpl\t" OP_XRM32),
	I(0xff, IF_REXW|IF_MODRM|IF_REG4, "jmpq\t" OP_XRM64),

	I(0xff, IF_RMM|IF_66|IF_MODRM|IF_REG5, "ljmpw\t" OP_XRM16),
	I(0xff, IF_RMM|IF_MODRM|IF_REG5, "ljmpl\t" OP_XRM32),
	I(0xff, IF_RMM|IF_REXW|IF_MODRM|IF_REG5, "ljmpq\t" OP_XRM64),

	I(0xff, IF_66|IF_MODRM|IF_REG6, "pushw\t" OP_RM16),
	I(0xff, IF_MODRM|IF_REG6, "pushl\t" OP_RM32),
	I(0xff, IF_REXW|IF_MODRM|IF_REG6, "pushq\t" OP_RM64),

	I(0, 0, "")
/*[[[end:ops]]]*/
};
/* clang-format on */


/* clang-format off */
PRIVATE struct instruction const ops_0f[] = {
/*[[[start:ops_0f]]]*/
	/* REMINDER: After adding/removing instructions from this table, you must run:
	 *           $ deemon -F kos/src/libdisasm/x86.c */
	I(0x00, IF_MODRM|IF_REG0, "sldt\t" OP_RM16),
	I(0x00, IF_MODRM|IF_REG1, "str\t"  OP_RM16),
	I(0x00, IF_MODRM|IF_REG2, "lldt\t" OP_RM16),
	I(0x00, IF_MODRM|IF_REG3, "ltr\t"  OP_RM16),
	I(0x00, IF_MODRM|IF_REG4, "verr\t" OP_RM16),
	I(0x00, IF_MODRM|IF_REG5, "verw\t" OP_RM16),

	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG0,  "sgdtl\t" OP_RM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG0,  "sgdtq\t" OP_RM),
	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG1,  "sidtl\t" OP_RM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG1,  "sidtq\t" OP_RM),
	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG2,  "lgdtl\t" OP_RM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG2,  "lgdtq\t" OP_RM),
	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG3,  "lidtl\t" OP_RM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG3,  "lidtq\t" OP_RM),

	I(0x01, IF_66|IF_MODRM|IF_REG4,          "smsww\t" OP_RM16),
	I(0x01, IF_MODRM|IF_REG4,                "smswl\t" OP_RM32),
	I(0x01, IF_REXW|IF_MODRM|IF_REG4,        "smswq\t" OP_RM64),

	I(0x01, IF_MODRM|IF_REG6,                "lmsw\t" OP_RM16),

	I(0x01, IF_MODRM|IF_RMM|IF_REG7,         "invlpg\t" OP_RM),

	I(0x01, IF_BYTE2,                 "\xf8" "swapgs"),
	I(0x01, IF_BYTE2,                 "\xf9" "rdtscp"),

	I(0x01, IF_BYTE2,                 "\xc1" "vmcall"),
	I(0x01, IF_BYTE2,                 "\xc2" "vmlaunch"),
	I(0x01, IF_BYTE2,                 "\xc3" "vmresume"),
	I(0x01, IF_BYTE2,                 "\xc4" "vmxoff"),
	I(0x01, IF_BYTE2,                 "\xc8" "monitor\t" OP_PAX_PCX_PDX),
	I(0x01, IF_BYTE2,                 "\xc9" "mwait\t" OP_PAX_PCX),
	I(0x01, IF_BYTE2,                 "\xca" "clac"),
	I(0x01, IF_BYTE2,                 "\xcb" "stac"),
	I(0x01, IF_BYTE2,                 "\xcf" "encls"),
	I(0x01, IF_BYTE2,                 "\xd0" "xgetbv"),
	I(0x01, IF_BYTE2,                 "\xd1" "xsetbv"),
	I(0x01, IF_BYTE2,                 "\xd4" "vmfunc"),
	I(0x01, IF_BYTE2,                 "\xd5" "xend"),
	I(0x01, IF_BYTE2,                 "\xd6" "xtest"),
	I(0x01, IF_BYTE2,                 "\xd7" "enclu"),

	I(0x02, IF_66|IF_MODRM,   "larw\t" OP_RM16 OP_R16),
	I(0x02, IF_MODRM,         "larl\t" OP_RM32 OP_R32),
	I(0x03, IF_66|IF_MODRM,   "lslw\t" OP_RM16 OP_R16),
	I(0x03, IF_MODRM,         "lsll\t" OP_RM32 OP_R32),

	I(0x05, IF_X32,           "loadall"), /* Unofficial */
	I(0x05, IF_X64,           "syscall"),
	I(0x06, 0,                "clts"),
	I(0x07, IF_X32,           "loadall\t" OP_PSI), /* Unofficial */
	I(0x07, IF_X64,           "sysret"),
	I(0x08, 0,                "invd"),
	I(0x09, 0,                "wbinvd"),

	I(0x0a, 0,                "cflsh"),

	I(0x0b, 0,                "ud2"),

	I(0x0d, IF_MODRM|IF_REG1|IF_RMM, "prefetchw\t" OP_RM),

	I(0x18, IF_MODRM|IF_REG0|IF_RMM, LONGREPR(LO_PREFETCHNTA)),
	I(0x18, IF_MODRM|IF_REG1|IF_RMM, "prefetch0\t" OP_RM),
	I(0x18, IF_MODRM|IF_REG2|IF_RMM, "prefetch1\t" OP_RM),
	I(0x18, IF_MODRM|IF_REG3|IF_RMM, "prefetch2\t" OP_RM),

	I(0x1a, IF_F2|IF_X32|IF_MODRM, "bndcu\t" OP_RM32 OP_RBND),
	I(0x1a, IF_F2|IF_X64|IF_MODRM, "bndcu\t" OP_RM64 OP_RBND),
	I(0x1a, IF_F3|IF_X32|IF_MODRM, "bndcl\t" OP_RM32 OP_RBND),
	I(0x1a, IF_F3|IF_X64|IF_MODRM, "bndcl\t" OP_RM64 OP_RBND),
	I(0x1a, IF_MODRM,              "bndldx\t" OP_RMBND_RANGE OP_RBND),
	I(0x1a, IF_66|IF_MODRM,        "bndmov\t" OP_RMBND OP_RBND),
	I(0x1b, IF_F2|IF_X32|IF_MODRM, "bndcn\t" OP_RM32 OP_RBND),
	I(0x1b, IF_F2|IF_X64|IF_MODRM, "bndcn\t" OP_RM64 OP_RBND),
	I(0x1b, IF_66|IF_MODRM,        "bndmov\t" OP_RBND OP_RMBND),
	I(0x1b, IF_F3|IF_X32|IF_MODRM, "bndmk\t" OP_RM32 OP_RBND),
	I(0x1b, IF_F3|IF_X64|IF_MODRM, "bndmk\t" OP_RM64 OP_RBND),

	I(0x1c, IF_MODRM|IF_REG0|IF_RMM, "cldemote\t" OP_RM),

	I(0x1f, IF_66|IF_MODRM|IF_REG0, "nopw\t" OP_RM16),
	I(0x1f, IF_MODRM|IF_REG0,       "nopl\t" OP_RM32),

	I(0x20, IF_X32|IF_MODRM|IF_RMR,"movl\t" OP_RCR OP_RM32),
	I(0x20, IF_X64|IF_MODRM|IF_RMR,"movq\t" OP_RCR OP_RM64),
	I(0x21, IF_X32|IF_MODRM|IF_RMR,"movl\t" OP_RDR OP_RM32),
	I(0x21, IF_X64|IF_MODRM|IF_RMR,"movq\t" OP_RDR OP_RM64),
	I(0x22, IF_X32|IF_MODRM|IF_RMR,"movl\t" OP_RM32 OP_RCR),
	I(0x22, IF_X64|IF_MODRM|IF_RMR,"movq\t" OP_RM64 OP_RCR),
	I(0x23, IF_X32|IF_MODRM|IF_RMR,"movl\t" OP_RM32 OP_RDR),
	I(0x23, IF_X64|IF_MODRM|IF_RMR,"movq\t" OP_RM64 OP_RDR),

	/* Move to/from test registers (s.a. `https://css.csail.mit.edu/6.858/2014/readings/i386/MOVRS.htm')
	 * Note that these instructions only existed on the i386 and were removed on later processors! */
	I(0x24, IF_MODRM|IF_RMR,  "movl\t" OP_RTR OP_RM32),
	I(0x26, IF_MODRM|IF_RMR,  "movl\t" OP_RM32 OP_RTR),

	I(0x30, 0,                "wrmsr"),
	I(0x31, 0,                "rdtsc"),
	I(0x32, 0,                "rdmsr"),
	I(0x33, 0,                "rdpmc"),
	I(0x34, 0,                "sysenter"), /* Unofficial: WRECR??? */
	I(0x35, 0,                "sysexit"),
	I(0x36, 0,                "rdecr"), /* Unofficial */

	I(0x37, 0,                "getsec"),

	/* 0x38 -- PREFIX */
	/* 0x3a -- PREFIX */

	/* VIA secret DEC-enable instruction (activated with msr 1107:bit[0],
	 * instructions send by `bound %eax, <OPCODE>(,%eax,1)') */
	I(0x3f, 0,                "jmp\t" OP_EAX),

	I(0x40, IF_66|IF_MODRM,   "cmov" NAME_jc0 "w\t" OP_RM16 OP_R16),
	I(0x40, IF_MODRM,         "cmov" NAME_jc0 "l\t" OP_RM32 OP_R32),
	I(0x40, IF_66|IF_MODRM,   "cmov" NAME_jc0 "q\t" OP_RM64 OP_R64),
	I(0x41, IF_66|IF_MODRM,   "cmov" NAME_jc1 "w\t" OP_RM16 OP_R16),
	I(0x41, IF_MODRM,         "cmov" NAME_jc1 "l\t" OP_RM32 OP_R32),
	I(0x41, IF_66|IF_MODRM,   "cmov" NAME_jc1 "q\t" OP_RM64 OP_R64),
	I(0x42, IF_66|IF_MODRM,   "cmov" NAME_jc2 "w\t" OP_RM16 OP_R16),
	I(0x42, IF_MODRM,         "cmov" NAME_jc2 "l\t" OP_RM32 OP_R32),
	I(0x42, IF_66|IF_MODRM,   "cmov" NAME_jc2 "q\t" OP_RM64 OP_R64),
	I(0x43, IF_66|IF_MODRM,   "cmov" NAME_jc3 "w\t" OP_RM16 OP_R16),
	I(0x43, IF_MODRM,         "cmov" NAME_jc3 "l\t" OP_RM32 OP_R32),
	I(0x43, IF_66|IF_MODRM,   "cmov" NAME_jc3 "q\t" OP_RM64 OP_R64),
	I(0x44, IF_66|IF_MODRM,   "cmov" NAME_jc4 "w\t" OP_RM16 OP_R16),
	I(0x44, IF_MODRM,         "cmov" NAME_jc4 "l\t" OP_RM32 OP_R32),
	I(0x44, IF_66|IF_MODRM,   "cmov" NAME_jc4 "q\t" OP_RM64 OP_R64),
	I(0x45, IF_66|IF_MODRM,   "cmov" NAME_jc5 "w\t" OP_RM16 OP_R16),
	I(0x45, IF_MODRM,         "cmov" NAME_jc5 "l\t" OP_RM32 OP_R32),
	I(0x45, IF_66|IF_MODRM,   "cmov" NAME_jc5 "q\t" OP_RM64 OP_R64),
	I(0x46, IF_66|IF_MODRM,   "cmov" NAME_jc6 "w\t" OP_RM16 OP_R16),
	I(0x46, IF_MODRM,         "cmov" NAME_jc6 "l\t" OP_RM32 OP_R32),
	I(0x46, IF_66|IF_MODRM,   "cmov" NAME_jc6 "q\t" OP_RM64 OP_R64),
	I(0x47, IF_66|IF_MODRM,   "cmov" NAME_jc7 "w\t" OP_RM16 OP_R16),
	I(0x47, IF_MODRM,         "cmov" NAME_jc7 "l\t" OP_RM32 OP_R32),
	I(0x47, IF_66|IF_MODRM,   "cmov" NAME_jc7 "q\t" OP_RM64 OP_R64),
	I(0x48, IF_66|IF_MODRM,   "cmov" NAME_jc8 "w\t" OP_RM16 OP_R16),
	I(0x48, IF_MODRM,         "cmov" NAME_jc8 "l\t" OP_RM32 OP_R32),
	I(0x48, IF_66|IF_MODRM,   "cmov" NAME_jc8 "q\t" OP_RM64 OP_R64),
	I(0x49, IF_66|IF_MODRM,   "cmov" NAME_jc9 "w\t" OP_RM16 OP_R16),
	I(0x49, IF_MODRM,         "cmov" NAME_jc9 "l\t" OP_RM32 OP_R32),
	I(0x49, IF_66|IF_MODRM,   "cmov" NAME_jc9 "q\t" OP_RM64 OP_R64),
	I(0x4a, IF_66|IF_MODRM,   "cmov" NAME_jca "w\t" OP_RM16 OP_R16),
	I(0x4a, IF_MODRM,         "cmov" NAME_jca "l\t" OP_RM32 OP_R32),
	I(0x4a, IF_66|IF_MODRM,   "cmov" NAME_jca "q\t" OP_RM64 OP_R64),
	I(0x4b, IF_66|IF_MODRM,   "cmov" NAME_jcb "w\t" OP_RM16 OP_R16),
	I(0x4b, IF_MODRM,         "cmov" NAME_jcb "l\t" OP_RM32 OP_R32),
	I(0x4b, IF_66|IF_MODRM,   "cmov" NAME_jcb "q\t" OP_RM64 OP_R64),
	I(0x4c, IF_66|IF_MODRM,   "cmov" NAME_jcc "w\t" OP_RM16 OP_R16),
	I(0x4c, IF_MODRM,         "cmov" NAME_jcc "l\t" OP_RM32 OP_R32),
	I(0x4c, IF_66|IF_MODRM,   "cmov" NAME_jcc "q\t" OP_RM64 OP_R64),
	I(0x4d, IF_66|IF_MODRM,   "cmov" NAME_jcd "w\t" OP_RM16 OP_R16),
	I(0x4d, IF_MODRM,         "cmov" NAME_jcd "l\t" OP_RM32 OP_R32),
	I(0x4d, IF_66|IF_MODRM,   "cmov" NAME_jcd "q\t" OP_RM64 OP_R64),
	I(0x4e, IF_66|IF_MODRM,   "cmov" NAME_jce "w\t" OP_RM16 OP_R16),
	I(0x4e, IF_MODRM,         "cmov" NAME_jce "l\t" OP_RM32 OP_R32),
	I(0x4e, IF_66|IF_MODRM,   "cmov" NAME_jce "q\t" OP_RM64 OP_R64),
	I(0x4f, IF_66|IF_MODRM,   "cmov" NAME_jcf "w\t" OP_RM16 OP_R16),
	I(0x4f, IF_MODRM,         "cmov" NAME_jcf "l\t" OP_RM32 OP_R32),
	I(0x4f, IF_66|IF_MODRM,   "cmov" NAME_jcf "q\t" OP_RM64 OP_R64),

//	I(0x78, IF_MODRM|IF_RMM,  "svdc\t" OP_RSEG OP_RM/*80*/), /* Unofficial */
//	I(0x79, IF_MODRM|IF_RMM,  "rsdc\t" OP_RM/*80*/ OP_RSEG), /* Unofficial */

	I(0x80, IF_66,            "j" NAME_jc0 "\t" OP_DISP16),
	I(0x80, 0,                "j" NAME_jc0 "\t" OP_DISP32),
	I(0x81, IF_66,            "j" NAME_jc1 "\t" OP_DISP16),
	I(0x81, 0,                "j" NAME_jc1 "\t" OP_DISP32),
	I(0x82, IF_66,            "j" NAME_jc2 "\t" OP_DISP16),
	I(0x82, 0,                "j" NAME_jc2 "\t" OP_DISP32),
	I(0x83, IF_66,            "j" NAME_jc3 "\t" OP_DISP16),
	I(0x83, 0,                "j" NAME_jc3 "\t" OP_DISP32),
	I(0x84, IF_66,            "j" NAME_jc4 "\t" OP_DISP16),
	I(0x84, 0,                "j" NAME_jc4 "\t" OP_DISP32),
	I(0x85, IF_66,            "j" NAME_jc5 "\t" OP_DISP16),
	I(0x85, 0,                "j" NAME_jc5 "\t" OP_DISP32),
	I(0x86, IF_66,            "j" NAME_jc6 "\t" OP_DISP16),
	I(0x86, 0,                "j" NAME_jc6 "\t" OP_DISP32),
	I(0x87, IF_66,            "j" NAME_jc7 "\t" OP_DISP16),
	I(0x87, 0,                "j" NAME_jc7 "\t" OP_DISP32),
	I(0x88, IF_66,            "j" NAME_jc8 "\t" OP_DISP16),
	I(0x88, 0,                "j" NAME_jc8 "\t" OP_DISP32),
	I(0x89, IF_66,            "j" NAME_jc9 "\t" OP_DISP16),
	I(0x89, 0,                "j" NAME_jc9 "\t" OP_DISP32),
	I(0x8a, IF_66,            "j" NAME_jca "\t" OP_DISP16),
	I(0x8a, 0,                "j" NAME_jca "\t" OP_DISP32),
	I(0x8b, IF_66,            "j" NAME_jcb "\t" OP_DISP16),
	I(0x8b, 0,                "j" NAME_jcb "\t" OP_DISP32),
	I(0x8c, IF_66,            "j" NAME_jcc "\t" OP_DISP16),
	I(0x8c, 0,                "j" NAME_jcc "\t" OP_DISP32),
	I(0x8d, IF_66,            "j" NAME_jcd "\t" OP_DISP16),
	I(0x8d, 0,                "j" NAME_jcd "\t" OP_DISP32),
	I(0x8e, IF_66,            "j" NAME_jce "\t" OP_DISP16),
	I(0x8e, 0,                "j" NAME_jce "\t" OP_DISP32),
	I(0x8f, IF_66,            "j" NAME_jcf "\t" OP_DISP16),
	I(0x8f, 0,                "j" NAME_jcf "\t" OP_DISP32),

	I(0x90, IF_MODRM,         "set" NAME_jc0 "\t" OP_RM8),
	I(0x91, IF_MODRM,         "set" NAME_jc1 "\t" OP_RM8),
	I(0x92, IF_MODRM,         "set" NAME_jc2 "\t" OP_RM8),
	I(0x93, IF_MODRM,         "set" NAME_jc3 "\t" OP_RM8),
	I(0x94, IF_MODRM,         "set" NAME_jc4 "\t" OP_RM8),
	I(0x95, IF_MODRM,         "set" NAME_jc5 "\t" OP_RM8),
	I(0x96, IF_MODRM,         "set" NAME_jc6 "\t" OP_RM8),
	I(0x97, IF_MODRM,         "set" NAME_jc7 "\t" OP_RM8),
	I(0x98, IF_MODRM,         "set" NAME_jc8 "\t" OP_RM8),
	I(0x99, IF_MODRM,         "set" NAME_jc9 "\t" OP_RM8),
	I(0x9a, IF_MODRM,         "set" NAME_jca "\t" OP_RM8),
	I(0x9b, IF_MODRM,         "set" NAME_jcb "\t" OP_RM8),
	I(0x9c, IF_MODRM,         "set" NAME_jcc "\t" OP_RM8),
	I(0x9d, IF_MODRM,         "set" NAME_jcd "\t" OP_RM8),
	I(0x9e, IF_MODRM,         "set" NAME_jce "\t" OP_RM8),
	I(0x9f, IF_MODRM,         "set" NAME_jcf "\t" OP_RM8),

	I(0xa0, IF_66,            "pushw\t" OP_FS),
	I(0xa0, IF_X32,           "pushl\t" OP_FS),
	I(0xa0, IF_X64,           "pushq\t" OP_FS),
	I(0xa1, IF_66,            "popw\t"  OP_FS),
	I(0xa1, IF_X32,           "popl\t"  OP_FS),
	I(0xa1, IF_X64,           "popq\t"  OP_FS),

	I(0xa2, 0,                "cpuid"),

	I(0xa3, IF_66|IF_MODRM,   "btw\t" OP_R16 OP_RM16),
	I(0xa3, IF_MODRM,         "btl\t" OP_R32 OP_RM32),
	I(0xa3, IF_REXW|IF_MODRM, "btq\t" OP_R64 OP_RM64),

	I(0xa4, IF_66|IF_MODRM,   "shldw\t" OP_RM16 OP_R16 OP_U8),
	I(0xa4, IF_MODRM,         "shldl\t" OP_RM32 OP_R32 OP_U8),
	I(0xa4, IF_REXW|IF_MODRM, "shldq\t" OP_RM64 OP_R64 OP_U8),

	I(0xa5, IF_66|IF_MODRM,   "shldw\t" OP_RM16 OP_R16 OP_CL),
	I(0xa5, IF_MODRM,         "shldl\t" OP_RM32 OP_R32 OP_CL),
	I(0xa5, IF_REXW|IF_MODRM, "shldq\t" OP_RM64 OP_R64 OP_CL),

	I(0xa8, IF_66,            "pushw\t" OP_GS),
	I(0xa8, IF_X32,           "pushl\t" OP_GS),
	I(0xa8, IF_X64,           "pushq\t" OP_GS),

	I(0xa9, IF_66,            "popw\t"  OP_GS),
	I(0xa9, IF_X32,           "popl\t"  OP_GS),
	I(0xa9, IF_X64,           "popq\t"  OP_GS),

	I(0xaa, 0,                "rsm"),

	I(0xab, IF_66|IF_MODRM,   "btsw\t" OP_R8 OP_RM8),
	I(0xab, IF_MODRM,         "btsl\t" OP_R16 OP_RM16),
	I(0xab, IF_REXW|IF_MODRM, "btsq\t" OP_R32 OP_RM32),

	I(0xac, IF_66|IF_MODRM,   "shrdw\t" OP_RM16 OP_R16 OP_U8),
	I(0xac, IF_MODRM,         "shrdl\t" OP_RM32 OP_R32 OP_U8),
	I(0xac, IF_REXW|IF_MODRM, "shrdq\t" OP_RM64 OP_R64 OP_U8),

	I(0xad, IF_66|IF_MODRM,   "shrdw\t" OP_RM16 OP_R16 OP_CL),
	I(0xad, IF_MODRM,         "shrdl\t" OP_RM32 OP_R32 OP_CL),
	I(0xad, IF_REXW|IF_MODRM, "shrdq\t" OP_RM64 OP_R64 OP_CL),

	I(0xae, IF_F3|IF_MODRM|IF_REG0,         "rdfsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG0, "rdfsbaseq\t" OP_RM64),

	I(0xae, IF_F3|IF_MODRM|IF_REG1,         "rdgsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG1, "rdgsbaseq\t" OP_RM64),

	I(0xae, IF_F3|IF_MODRM|IF_REG2,         "wrfsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG2, "wrfsbaseq\t" OP_RM64),

	I(0xae, IF_F3|IF_MODRM|IF_REG3,         "wrgsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG3, "wrgsbaseq\t" OP_RM64),

	I(0xae, IF_MODRM|IF_RMM|IF_REG0,        "fxsave\t" OP_RM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG1,        "fxrstor\t" OP_RM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG2,        "ldmxcsr\t" OP_RM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG3,        "stmxcsr\t" OP_RM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG4,        "xsave\t" OP_RM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG5,        "xrstor\t" OP_RM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG6,        "xsaveopt\t" OP_RM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG7,        "clflush\t" OP_RM),
	I(0xae, IF_66|IF_MODRM|IF_RMM|IF_REG7,  "clflushopt\t" OP_RM32),
	I(0xae, IF_BYTE2,                "\xe8" "lfence"),
	I(0xae, IF_BYTE2,                "\xf0" "mfence"),
	I(0xae, IF_BYTE2,                "\xf8" "sfence"),

	I(0xae, IF_MODRM|IF_RMM|IF_REG0,         "fxsave\t" OP_RM),
	I(0xae, IF_REXW|IF_MODRM|IF_RMM|IF_REG0, "fxsave64\t" OP_RM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG1,         "fxrstor\t" OP_RM),
	I(0xae, IF_REXW|IF_MODRM|IF_RMM|IF_REG1, "fxrstor64\t" OP_RM),

	I(0xaf, IF_66|IF_MODRM,  "imulb\t" OP_RM8 OP_R8),
	I(0xaf, IF_MODRM,        "imulw\t" OP_RM16 OP_R16),
	I(0xaf, IF_REXW|IF_MODRM,"imull\t" OP_RM32 OP_R32),

	I(0xb0, IF_MODRM,        "cmpxchgb\t" OP_R8 OP_RM8),
	I(0xb1, IF_66|IF_MODRM,  "cmpxchgw\t" OP_R16 OP_RM16),
	I(0xb1, IF_MODRM,        "cmpxchgl\t" OP_R32 OP_RM32),
	I(0xb1, IF_REXW|IF_MODRM,"cmpxchgq\t" OP_R64 OP_RM64),

	I(0xb2, IF_66|IF_MODRM|IF_RMM,  "lssw\t" OP_RM/*32*/ OP_R16),
	I(0xb2, IF_MODRM|IF_RMM,        "lssl\t" OP_RM/*48*/ OP_R32),
	I(0xb2, IF_REXW|IF_MODRM|IF_RMM,"lssq\t" OP_RM/*80*/ OP_R64),

	I(0xb3, IF_66|IF_MODRM,  "btrw\t" OP_R16 OP_RM16),
	I(0xb3, IF_MODRM,        "btrl\t" OP_R32 OP_RM32),
	I(0xb3, IF_REXW|IF_MODRM,"btrq\t" OP_R64 OP_RM64),

	I(0xb4, IF_66|IF_MODRM|IF_RMM,  "lfsw\t" OP_RM/*32*/ OP_R16),
	I(0xb4, IF_MODRM|IF_RMM,        "lfsl\t" OP_RM/*48*/ OP_R32),
	I(0xb4, IF_REXW|IF_MODRM|IF_RMM,"lfsq\t" OP_RM/*80*/ OP_R64),
	I(0xb5, IF_66|IF_MODRM|IF_RMM,  "lgsw\t" OP_RM/*32*/ OP_R16),
	I(0xb5, IF_MODRM|IF_RMM,        "lgsl\t" OP_RM/*48*/ OP_R32),
	I(0xb5, IF_REXW|IF_MODRM|IF_RMM,"lgsq\t" OP_RM/*80*/ OP_R64),

	I(0xb6, IF_66|IF_MODRM,  "movzbw\t" OP_RM8 OP_R32),
	I(0xb6, IF_MODRM,        "movzbl\t" OP_RM8 OP_R32),
	I(0xb6, IF_REXW|IF_MODRM,"movzbq\t" OP_RM8 OP_R64),
	I(0xb7, IF_MODRM,        "movzwl\t" OP_RM16 OP_R32),
	I(0xb7, IF_REXW|IF_MODRM,"movzwq\t" OP_RM16 OP_R64),

	I(0xb8, IF_F3|IF_66|IF_MODRM,  "popcntw\t" OP_RM16 OP_R16),
	I(0xb8, IF_F3|IF_MODRM,        "popcntl\t" OP_RM32 OP_R32),
	I(0xb8, IF_F3|IF_REXW|IF_MODRM,"popcntq\t" OP_RM64 OP_R64),

	I(0xb9, IF_MODRM,        "ud1\t" OP_RM32 OP_R32),

	I(0xba, IF_66|IF_MODRM|IF_REG4,"btw\t" OP_U8 OP_RM16),
	I(0xba, IF_MODRM|IF_REG4,"btl\t" OP_U8 OP_RM32),
	I(0xba, IF_REXW|IF_MODRM|IF_REG4,"btq\t" OP_U8 OP_RM64),

	I(0xba, IF_66|IF_MODRM|IF_REG5,"btsw\t" OP_U8 OP_RM16),
	I(0xba, IF_MODRM|IF_REG5,"btsl\t" OP_U8 OP_RM32),
	I(0xba, IF_REXW|IF_MODRM|IF_REG5,"btsq\t" OP_U8 OP_RM64),

	I(0xba, IF_66|IF_MODRM|IF_REG6,"btrw\t" OP_U8 OP_RM16),
	I(0xba, IF_MODRM|IF_REG6,"btrl\t" OP_U8 OP_RM32),
	I(0xba, IF_REXW|IF_MODRM|IF_REG6,"btrq\t" OP_U8 OP_RM64),

	I(0xba, IF_66|IF_MODRM|IF_REG7,"btcw\t" OP_U8 OP_RM16),
	I(0xba, IF_MODRM|IF_REG7,"btcl\t" OP_U8 OP_RM32),
	I(0xba, IF_REXW|IF_MODRM|IF_REG7,"btcq\t" OP_U8 OP_RM64),

	I(0xbb, IF_66|IF_MODRM,  "btcw\t" OP_R16 OP_RM16),
	I(0xbb, IF_MODRM,        "btcl\t" OP_R32 OP_RM32),
	I(0xbb, IF_REXW|IF_MODRM,"btcq\t" OP_R64 OP_RM64),

	I(0xbc, IF_66|IF_MODRM,  "bsfw\t" OP_RM16 OP_R16),
	I(0xbc, IF_MODRM,        "bsfl\t" OP_RM32 OP_R32),
	I(0xbc, IF_REXW|IF_MODRM,"bsfq\t" OP_RM64 OP_R64),

	I(0xbc, IF_F3|IF_66|IF_MODRM,  "tzcntw\t" OP_RM16 OP_R16),
	I(0xbc, IF_F3|IF_MODRM,        "tzcntl\t" OP_RM32 OP_R32),
	I(0xbc, IF_F3|IF_REXW|IF_MODRM,"tzcntq\t" OP_RM64 OP_R64),

	I(0xbd, IF_66|IF_MODRM,  "bsrw\t" OP_RM16 OP_R16),
	I(0xbd, IF_MODRM,        "bsrl\t" OP_RM32 OP_R32),
	I(0xbd, IF_REXW|IF_MODRM,"bsrq\t" OP_RM64 OP_R64),

	I(0xbd, IF_F3|IF_66|IF_MODRM,  "lzcntw\t" OP_RM16 OP_R16),
	I(0xbd, IF_F3|IF_MODRM,        "lzcntl\t" OP_RM32 OP_R32),
	I(0xbd, IF_F3|IF_REXW|IF_MODRM,"lzcntq\t" OP_RM64 OP_R64),

	I(0xbe, IF_66|IF_MODRM,  "movsbw\t" OP_RM8 OP_R32),
	I(0xbe, IF_MODRM,        "movsbl\t" OP_RM8 OP_R32),
	I(0xbe, IF_REXW|IF_MODRM,"movsbq\t" OP_RM8 OP_R64),
	I(0xbf, IF_MODRM,        "movswl\t" OP_RM16 OP_R32),
	I(0xbf, IF_REXW|IF_MODRM,"movswq\t" OP_RM16 OP_R64),

	I(0xc0, IF_MODRM,        "xaddb\t" OP_R8 OP_RM8),
	I(0xc1, IF_66|IF_MODRM,  "xaddw\t" OP_R16 OP_RM16),
	I(0xc1, IF_MODRM,        "xaddl\t" OP_R32 OP_RM32),
	I(0xc1, IF_REXW|IF_MODRM,"xaddq\t" OP_R64 OP_RM64),

	I(0xc7, IF_X32|IF_MODRM|IF_RMM|IF_REG1,       "cmpxchg8b\t" OP_RM),
	I(0xc7, IF_X64|IF_MODRM|IF_RMM|IF_REG1,       "cmpxchg16b\t" OP_RM),
	I(0xc7, IF_MODRM|IF_RMM|IF_REG6,              "vmptrld\t" OP_RM64),
	I(0xc7, IF_MODRM|IF_RMM|IF_REG6|IF_66,        "vmclear\t" OP_RM64),
	I(0xc7, IF_MODRM|IF_RMM|IF_REG6|IF_F3,        "vmxon\t" OP_RM64),
	I(0xc7, IF_X32|IF_MODRM|IF_RMR|IF_REG6,       "rdrandl\t" OP_RM32),
	I(0xc7, IF_X64|IF_MODRM|IF_RMR|IF_REG6,       "rdrandq\t" OP_RM64),
	I(0xc7, IF_X32|IF_MODRM|IF_RMR|IF_REG7,       "rdseedl\t" OP_RM32),
	I(0xc7, IF_X64|IF_MODRM|IF_RMR|IF_REG7,       "rdseedq\t" OP_RM64),
	I(0xc7, IF_X32|IF_MODRM|IF_RMR|IF_F3|IF_REG7, "rdpidl\t" OP_RM32),
	I(0xc7, IF_X64|IF_MODRM|IF_RMR|IF_F3|IF_REG7, "rdpidq\t" OP_RM64),

	I(0xc8, IF_REXR,         "bswapl\t" OP_R8D),
	I(0xc8, IF_REXR|IF_REXW, "bswapq\t" OP_X64_R8),
	I(0xc8, 0,               "bswapl\t" OP_EAX),
	I(0xc8, IF_REXW,         "bswapq\t" OP_RAX),
	I(0xc9, IF_REXR,         "bswapl\t" OP_R9D),
	I(0xc9, IF_REXR|IF_REXW, "bswapq\t" OP_R9),
	I(0xc9, 0,               "bswapl\t" OP_ECX),
	I(0xc9, IF_REXW,         "bswapq\t" OP_RCX),
	I(0xca, IF_REXR,         "bswapl\t" OP_R10D),
	I(0xca, IF_REXR|IF_REXW, "bswapq\t" OP_R10),
	I(0xca, 0,               "bswapl\t" OP_EDX),
	I(0xca, IF_REXW,         "bswapq\t" OP_RDX),
	I(0xcb, IF_REXR,         "bswapl\t" OP_R11D),
	I(0xcb, IF_REXR|IF_REXW, "bswapq\t" OP_R11),
	I(0xcb, 0,               "bswapl\t" OP_EBX),
	I(0xcb, IF_REXW,         "bswapq\t" OP_RBX),
	I(0xcc, IF_REXR,         "bswapl\t" OP_R12D),
	I(0xcc, IF_REXR|IF_REXW, "bswapq\t" OP_R12),
	I(0xcc, 0,               "bswapl\t" OP_ESP),
	I(0xcc, IF_REXW,         "bswapq\t" OP_RSP),
	I(0xcd, IF_REXR,         "bswapl\t" OP_R13D),
	I(0xcd, IF_REXR|IF_REXW, "bswapq\t" OP_R13),
	I(0xcd, 0,               "bswapl\t" OP_EBP),
	I(0xcd, IF_REXW,         "bswapq\t" OP_RBP),
	I(0xce, IF_REXR,         "bswapl\t" OP_R14D),
	I(0xce, IF_REXR|IF_REXW, "bswapq\t" OP_R14),
	I(0xce, 0,               "bswapl\t" OP_ESI),
	I(0xce, IF_REXW,         "bswapq\t" OP_RSI),
	I(0xcf, IF_REXR,         "bswapl\t" OP_R15D),
	I(0xcf, IF_REXR|IF_REXW, "bswapq\t" OP_R15),
	I(0xcf, 0,               "bswapl\t" OP_EDI),
	I(0xcf, IF_REXW,         "bswapq\t" OP_RDI),

	I(0xff, IF_MODRM,        "ud0\t" OP_RM32 OP_R32),

	I(0, 0, "")
/*[[[end:ops_0f]]]*/
};
/* clang-format on */


/* clang-format off */
PRIVATE struct instruction const ops_0f38[] = {
/*[[[start:ops_0f38]]]*/
	/* REMINDER: After adding/removing instructions from this table, you must run:
	 *           $ deemon -F kos/src/libdisasm/x86.c */

	/* 0x0f38XX */
	I(0xf0, IF_66|IF_MODRM/*|IF_RMM*/,   "movbew\t" OP_RM16 OP_R16), /* KOS Emulates the register variant */
	I(0xf0, IF_MODRM/*|IF_RMM*/,         "movbel\t" OP_RM32 OP_R32),
	I(0xf0, IF_REXW|IF_MODRM/*|IF_RMM*/, "movbeq\t" OP_RM64 OP_R64),
	I(0xf0, IF_F2|IF_MODRM,              "crc32b\t" OP_RM8 OP_R32),
	I(0xf0, IF_F2|IF_REXW|IF_MODRM,      "crc32b\t" OP_RM8 OP_R64),
	I(0xf1, IF_66|IF_MODRM/*|IF_RMM*/,   "movbew\t" OP_R16 OP_RM16), /* KOS Emulates the register variant */
	I(0xf1, IF_MODRM/*|IF_RMM*/,         "movbel\t" OP_R32 OP_RM32),
	I(0xf1, IF_REXW|IF_MODRM/*|IF_RMM*/, "movbeq\t" OP_R64 OP_RM64),
	I(0xf1, IF_F2|IF_66|IF_MODRM,        "crc32w\t" OP_RM16 OP_R32),
	I(0xf1, IF_F2|IF_MODRM,              "crc32l\t" OP_RM32 OP_R32),
	I(0xf1, IF_F2|IF_REXW|IF_MODRM,      "crc32q\t" OP_RM64 OP_R64),

	I(0xf2, IF_VEXW0|IF_MODRM, "andnl\t" OP_RM32 OP_VR32 OP_R32),
	I(0xf2, IF_VEXW1|IF_MODRM, "andnq\t" OP_RM64 OP_VR64 OP_R64),

	I(0xf3, IF_VEXW0|IF_MODRM|IF_REG1,"blsrl\t" OP_RM32 OP_VR32),
	I(0xf3, IF_VEXW1|IF_MODRM|IF_REG1,"blsrq\t" OP_RM64 OP_VR64),
	I(0xf3, IF_VEXW0|IF_MODRM|IF_REG2,"blsmskl\t" OP_RM32 OP_VR32),
	I(0xf3, IF_VEXW1|IF_MODRM|IF_REG2,"blsmskq\t" OP_RM64 OP_VR64),
	I(0xf3, IF_VEXW0|IF_MODRM|IF_REG3,"blsil\t" OP_RM32 OP_VR32),
	I(0xf3, IF_VEXW1|IF_MODRM|IF_REG3,"blsiq\t" OP_RM64 OP_VR64),

	I(0xf5, IF_VEXW0|IF_MODRM,       "bzhil\t" OP_VR32 OP_RM32 OP_R32),
	I(0xf5, IF_VEXW1|IF_MODRM,       "bzhiq\t" OP_VR64 OP_RM64 OP_R64),
	I(0xf5, IF_VEXW0|IF_F3|IF_MODRM, "pextl\t" OP_RM32 OP_VR32 OP_R32),
	I(0xf5, IF_VEXW1|IF_F3|IF_MODRM, "pextq\t" OP_RM64 OP_VR64 OP_R64),
	I(0xf5, IF_VEXW0|IF_F2|IF_MODRM, "pdepl\t" OP_RM32 OP_VR32 OP_R32),
	I(0xf5, IF_VEXW1|IF_F2|IF_MODRM, "pdepq\t" OP_RM64 OP_VR64 OP_R64),

	I(0xf6, IF_66|IF_MODRM,         "adcxl\t" OP_RM32 OP_R32),
	I(0xf6, IF_66|IF_REXW|IF_MODRM, "adcxq\t" OP_RM64 OP_R64),
	I(0xf6, IF_F3|IF_MODRM,         "adoxl\t" OP_RM32 OP_R32),
	I(0xf6, IF_F3|IF_REXW|IF_MODRM, "adoxq\t" OP_RM64 OP_R64),
	I(0xf6, IF_F2|IF_MODRM,         "mulxl\t" OP_RM32 OP_VR32 OP_R32),
	I(0xf6, IF_F2|IF_REXW|IF_MODRM, "mulxq\t" OP_RM64 OP_VR64 OP_R64),

	I(0xf7, IF_VEXW0|IF_MODRM,       "bextrl\t" OP_VR32 OP_RM32 OP_R32),
	I(0xf7, IF_VEXW1|IF_MODRM,       "bextrq\t" OP_VR64 OP_RM64 OP_R64),
	I(0xf7, IF_66|IF_VEXW0|IF_MODRM, "shlxl\t" OP_VR32 OP_RM32 OP_R32),
	I(0xf7, IF_66|IF_VEXW1|IF_MODRM, "shlxq\t" OP_VR64 OP_RM64 OP_R64),
	I(0xf7, IF_F3|IF_VEXW0|IF_MODRM, "sarxl\t" OP_VR32 OP_RM32 OP_R32),
	I(0xf7, IF_F3|IF_VEXW1|IF_MODRM, "sarxq\t" OP_VR64 OP_RM64 OP_R64),
	I(0xf7, IF_F2|IF_VEXW0|IF_MODRM, "shrxl\t" OP_VR32 OP_RM32 OP_R32),
	I(0xf7, IF_F2|IF_VEXW1|IF_MODRM, "shrxq\t" OP_VR64 OP_RM64 OP_R64),

	I(0, 0, "")
/*[[[end:ops_0f38]]]*/
};
/* clang-format on */

/* clang-format off */
PRIVATE struct instruction const ops_0f3a[] = {
/*[[[start:ops_0f3a]]]*/
	/* REMINDER: After adding/removing instructions from this table, you must run:
	 *           $ deemon -F kos/src/libdisasm/x86.c */

	/* 0x0f3aXX */
	I(0xf0, IF_F2|IF_VEXW0|IF_MODRM, "rorxl\t" OP_U8 OP_RM32 OP_R32),
	I(0xf0, IF_F2|IF_VEXW1|IF_MODRM, "rorxq\t" OP_U8 OP_RM64 OP_R64),


	I(0, 0, "")
/*[[[end:ops_0f3a]]]*/
};
/* clang-format on */


/*[[[deemon
import * from deemon;
local mytext = File.open(__FILE__, "r").read().decode("utf-8");

@@Calculate the offsets of opcodes and return a 256-element vector of offset indices
@@The return value is (OffsetTable, OpcodeCount)
function calculateOpcodeOffsets(start: string, end: string): ({int...}, int) {
	local data = mytext[mytext.index(start) + #start:mytext.index(end)].strip();
	local result = [none] * 256;
	local prev_opcode = -1;
	local curr_offset = 0;
	for (local l: data.splitlines(false)) {
		l = l.lstrip();
		if (!l.startswith("I("))
			continue;
		local line_opcode;
		try {
			line_opcode = l.scanf("I( %[xX0-9a-fA-F]")...;
		} catch (...) {
			print File.stderr: "ERROR: Failed to parse line:", repr l;
			throw;
		}
		if (line_opcode == "0")
			break; // Sentinel marker
		line_opcode = int(line_opcode);
		if (line_opcode < prev_opcode) {
			print File.stderr: "ERROR: Invalid opcode ordering";
			print File.stderr: "Line for opcode", line_opcode.hex(), ":", repr l;
			print File.stderr: "Should come before line for opcode", prev_opcode.hex();
			throw Error("Invalid opcode ordering");
		}
		if (result[line_opcode] is none)
			result[line_opcode] = curr_offset;
		prev_opcode = line_opcode;
		++curr_offset;
	}
	for (local i: [:256]) {
		// All undefined opcodes should point at the end of the tables.
		if (result[i] is none)
			result[i] = curr_offset;
	}
	return (result, curr_offset + 1);
}

function generateOffsetTable(name: string) {
	final local START_MARKER_PATTERN = "/" "*[[[start:{}]]]*" "/";
	final local END_MARKER_PATTERN = "/" "*[[[end:{}]]]*" "/";
	local offsets, count = calculateOpcodeOffsets(
		START_MARKER_PATTERN.format({ name }),
		END_MARKER_PATTERN.format({ name }))...;
	local maxOffset = offsets[0xff];
	local offsetType = "u8";
	if (maxOffset > 0xff)
		offsetType = "u16";
	if (maxOffset > 0xffff)
		offsetType = "u32";
	print "#define HAVE_",;
	print name.upper(),;
	print "_OFFSETS 1";
	print "STATIC_ASSERT(COMPILER_LENOF(",;
	print name,;
	print ") == ",;
	print count,;
	print ");";
	print "PRIVATE ",;
	print offsetType,;
	print " const ",;
	print name,;
	print "_offsets[256] = {";
	for (local i: [:256]) {
		if ((i % 16) == 0)
			print "\t",;
		else {
			print " ",;
		}
		print offsets[i],;
		if (i != 255)
			print ",",;
		if ((i % 16) == 15)
			print "\n",;
	}
	print "};";
	print;
}
generateOffsetTable("ops");
generateOffsetTable("ops_0f");
generateOffsetTable("ops_0f38");
//generateOffsetTable("ops_0f3a"); // Not needed (yet)
]]]*/
#define HAVE_OPS_OFFSETS 1
STATIC_ASSERT(COMPILER_LENOF(ops) == 953);
PRIVATE u16 const ops_offsets[256] = {
	0, 1, 4, 5, 8, 9, 12, 14, 16, 17, 20, 21, 24, 25, 28, 952,
	30, 31, 34, 35, 38, 39, 42, 44, 46, 47, 50, 51, 54, 55, 58, 60,
	62, 63, 66, 67, 70, 71, 952, 74, 75, 76, 79, 80, 83, 84, 952, 87,
	88, 89, 92, 93, 96, 97, 952, 100, 101, 102, 105, 106, 109, 110, 952, 113,
	114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144,
	146, 150, 154, 158, 162, 166, 170, 174, 178, 182, 186, 190, 194, 198, 202, 206,
	210, 212, 214, 216, 952, 952, 952, 952, 217, 220, 223, 224, 227, 229, 233, 235,
	239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
	255, 263, 287, 295, 319, 320, 323, 324, 327, 328, 331, 332, 335, 338, 341, 344,
	350, 357, 363, 369, 375, 381, 387, 393, 399, 400, 402, 404, 406, 409, 412, 413,
	414, 416, 420, 422, 426, 428, 434, 437, 446, 447, 450, 452, 458, 460, 466, 469,
	478, 480, 482, 484, 486, 488, 490, 492, 494, 500, 506, 512, 518, 524, 530, 536,
	542, 550, 574, 576, 578, 580, 582, 584, 589, 590, 591, 592, 593, 594, 595, 596,
	600, 608, 632, 640, 664, 665, 666, 667, 668, 684, 737, 750, 774, 788, 823, 838,
	863, 864, 865, 866, 869, 870, 872, 873, 875, 877, 879, 881, 882, 883, 885, 886,
	952, 888, 952, 952, 889, 890, 891, 899, 923, 924, 925, 926, 927, 928, 929, 931
};

#define HAVE_OPS_0F_OFFSETS 1
STATIC_ASSERT(COMPILER_LENOF(ops_0f) == 348);
PRIVATE u16 const ops_0f_offsets[256] = {
	0, 6, 36, 38, 347, 40, 42, 43, 45, 46, 47, 48, 347, 49, 347, 347,
	347, 347, 347, 347, 347, 347, 347, 347, 50, 347, 54, 60, 65, 347, 347, 66,
	68, 70, 72, 74, 76, 347, 77, 347, 347, 347, 347, 347, 347, 347, 347, 347,
	78, 79, 80, 81, 82, 83, 84, 85, 347, 347, 347, 347, 347, 347, 347, 86,
	87, 90, 93, 96, 99, 102, 105, 108, 111, 114, 117, 120, 123, 126, 129, 132,
	347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347,
	347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347,
	347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347,
	135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165,
	167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182,
	183, 186, 189, 190, 193, 196, 347, 347, 199, 202, 205, 206, 209, 212, 215, 239,
	242, 243, 246, 249, 252, 255, 258, 261, 263, 266, 267, 279, 282, 288, 294, 297,
	299, 300, 347, 347, 347, 347, 347, 303, 314, 318, 322, 326, 330, 334, 338, 342,
	347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347,
	347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347,
	347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 347, 346
};

#define HAVE_OPS_0F38_OFFSETS 1
STATIC_ASSERT(COMPILER_LENOF(ops_0f38) == 40);
PRIVATE u8 const ops_0f38_offsets[256] = {
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	0, 5, 11, 13, 39, 19, 25, 31, 39, 39, 39, 39, 39, 39, 39, 39
};
//[[[end]]]


#ifdef CONFIG_AUTOSELECT_JCC
PRIVATE ATTR_CONST bool CC
is_carry_instruction(u32 opcode, u8 reg) {
	switch (opcode) {

	case 0xc0:
	case 0xc1:
	case 0xd0:
	case 0xd1:
	case 0xd2:
	case 0xd3:
	case 0x0fa3:
	case 0x0fa4:
	case 0x0fa5:
	case 0x0fab:
	case 0x0fac:
	case 0x0fad:
	case 0x0fb3:
	case 0x0fba:
	case 0x0fbb:
	case 0x0fbc:
	case 0x0ff7:
	case 0x00:
	case 0x01:
	case 0x02:
	case 0x03:
	case 0x04:
	case 0x05:
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x13:
	case 0x14:
	case 0x15:
	case 0x18:
	case 0x19:
	case 0x1a:
	case 0x1b:
	case 0x1c:
	case 0x1d:
	case 0x28:
	case 0x29:
	case 0x2a:
	case 0x2b:
	case 0x2c:
	case 0x2d:
		return true;

	case 0x80:
	case 0x81:
	case 0x82:
	case 0x83:
		return reg == 0 || reg == 2 ||
		       reg == 3 || reg == 5;

	default: break;
	}
	return false;
}

PRIVATE ATTR_CONST bool CC
is_compare_instruction(u32 opcode, u8 reg) {
	switch (opcode) {

	case 0x38:
	case 0x39:
	case 0x3a:
	case 0x3b:
	case 0x3c:
	case 0x3d:
	case 0xa6:
	case 0xa7:
		return true;

	case 0x80:
	case 0x81:
	case 0x82:
	case 0x83:
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
#endif /* CONFIG_AUTOSELECT_JCC */

#ifdef __GNUC__
/* GCC emits a false warning about `self->d_pad1[0] = (void *)(uintptr_t)whole_opcode' supposedly
 * using the uninitialized variable `opcode'. Now mind you that this isn't a typo. - That expression
 * is neither using the variable `opcode', nor is opcode uninitialized at the time that piece of
 * code is reached, nor is this is the first time that `opcode' is accessed within any of the control
 * paths that lead to said statement. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif /* __GNUC__ */


INTERN NONNULL((1)) void CC
libda_single_x86(struct disassembler *__restrict self) {
#ifdef CONFIG_AUTOSELECT_JCC
	u32 whole_opcode;
#endif /* CONFIG_AUTOSELECT_JCC */
	u32 opcode;
	op_flag_t flags;
	byte_t *text_start = self->d_pc;
	byte_t *args_start = NULL;
	struct instruction const *chain;
	struct modrm rm;
	memset(&rm, 0, sizeof(rm));
	if (!decode_opcode(self, &opcode, &flags)) {
print_byte:
		disasm_print_format(self, DISASSEMBLER_FORMAT_PSEUDOOP_PREFIX);
		disasm_print(self, ".byte", 5);
		disasm_print_format(self, DISASSEMBLER_FORMAT_PSEUDOOP_SUFFIX);
		disasm_printf(self, " %#.2I8x", *self->d_pc++);
		return;
	}
#ifdef CONFIG_AUTOSELECT_JCC
	whole_opcode = opcode;
#endif /* CONFIG_AUTOSELECT_JCC */
	/* Print the instruction. */
	if (opcode <= 0xff) {
		chain = ops;
#ifdef HAVE_OPS_OFFSETS
		chain += ops_offsets[opcode];
#endif /* HAVE_OPS_OFFSETS */
	} else if ((opcode & 0xff00) == 0x0f00) {
		/* Multi-byte opcodes. */
		if ((opcode & 0xffff00) == 0x0f3800) {
			chain = ops_0f38;
			opcode &= 0xff;
#ifdef HAVE_OPS_0F38_OFFSETS
			chain += ops_0f38_offsets[opcode];
#endif /* HAVE_OPS_0F38_OFFSETS */
		} else if ((opcode & 0xffff00) == 0x0f3a00) {
			chain = ops_0f3a;
			opcode &= 0xff;
#ifdef HAVE_OPS_0F3A_OFFSETS
			chain += ops_0f3a_offsets[opcode];
#endif /* HAVE_OPS_0F3A_OFFSETS */
		} else {
			chain = ops_0f;
			opcode &= 0xff;
#ifdef HAVE_OPS_0F_OFFSETS
			chain += ops_0f_offsets[opcode];
#endif /* HAVE_OPS_0F_OFFSETS */
		}
	} else {
		goto unknown_opcode;
	}

	for (; chain->i_repr[0]; ++chain) {
		if (chain->i_opcode != opcode) {
			if (chain->i_opcode > opcode) {
				/* Opcodes are always sorted ascendingly, so if the encountered
				 * code is greater than ours, then we know that we've already went
				 * past what we were looking for. */
				break;
			}
			continue;
		}
		if (((chain->i_flags & IF_REXW) != 0) !=
		    ((flags & F_REX_W) != 0))
			continue;
		if (DA86_IS16(self)) {
			/* The 0x66 prefix acts inverted on 16-bit mode.
			 * As such, instruction _with_ the prefix are used by default,
			 * whilst instruction _without_ the prefix are used any other
			 * time (thus not breaking instructions that don't care about
			 * the prefix at all). */
			if ((chain->i_flags & IF_66) && (flags & F_66))
				continue;
			if ((chain->i_flags & IF_67) && (flags & F_67))
				continue;
		} else {
			if (((chain->i_flags & IF_66) != 0) !=
			    ((flags & F_66) != 0))
				continue;
			if (((chain->i_flags & IF_67) != 0) !=
			    ((flags & F_67) != 0))
				continue;
		}
		if (((chain->i_flags & IF_F2) != 0) !=
		    ((flags & F_f2) != 0))
			continue;
		if (((chain->i_flags & IF_F3) != 0) !=
		    ((flags & F_f3) != 0))
			continue;
		if ((chain->i_flags & IF_REXR) == IF_REXR) {
			if (!(flags & F_REX_R))
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
			if (args_start)
				self->d_pc = args_start, args_start = NULL;
			if (self->d_pc[0] != (byte_t)chain->i_repr[0])
				continue;
			++self->d_pc;
		} else {
			if (chain->i_flags & (IF_VEXW0 | IF_VEXW1)) {
				if (!(flags & F_HASVEX))
					continue;
				if (((flags & F_VEX_W) != 0) != ((flags & IF_VEXW1) != 0))
					continue;
			}
			if (chain->i_flags & IF_MODRM) {
				if (!args_start) {
					args_start = self->d_pc;
					decode_modrm(self, &rm, flags);
				}
				if (chain->i_flags & IF_REG0) {
					if (rm.mi_reg != (chain->i_flags & 7))
						continue;
				}
				if ((chain->i_flags & IF_RMM) &&
				    (rm.mi_type == MODRM_REGISTER))
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
			if ((chain->i_flags & IF_BYTE2) == IF_BYTE2)
				++start;
			if (*start == '?') {
				/* Extended-length opcode representation. */
				u16 offset = UNALIGNED_GET16((u16 *)(start + 1));
				start = longops_repr + offset;
			}
			p = strchrnul(start, '\t');
			if (*p)
				++p;
			disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_PREFIX);
			if (flags & F_LOCK)
				disasm_print(self, "lock ", 5);
			{
#ifdef CONFIG_AUTOSELECT_JCC
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
#endif /* CONFIG_AUTOSELECT_JCC */
				disasm_print(self, start,
				             (size_t)(p - start));
			}
			disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_SUFFIX);
			for (;;) {
				ch = *p++;
				if (!ch)
					break;
				if (!is_first)
					disasm_print(self, ", ", 2);
				is_first = false;
				switch (ch) {

				case OPC_RM8:
					da_print_modrm_rm(self, &rm, flags, 1);
					break;

				case OPC_RM16:
					da_print_modrm_rm(self, &rm, flags, 2);
					break;

				case OPC_RM32:
					da_print_modrm_rm(self, &rm, flags, 4);
					break;

				case OPC_RM64:
					da_print_modrm_rm(self, &rm, flags, 8);
					break;

				case OPC_XRM16:
					disasm_print(self, "*", 1);
					da_print_modrm_rm(self, &rm, flags, 2);
					break;

				case OPC_XRM32:
					disasm_print(self, "*", 1);
					da_print_modrm_rm(self, &rm, flags, 4);
					break;

				case OPC_XRM64:
					disasm_print(self, "*", 1);
					da_print_modrm_rm(self, &rm, flags, 8);
					break;

				case OPC_RMBND:
					if (rm.mi_type == MODRM_REGISTER) {
						da_print_bndreg(self, rm.mi_rm);
					} else {
						da_print_modrm_rm(self, &rm, flags, DA86_IS64(self) ? 16 : 8);
					}
					break;

				case OPC_RMBND_RANGE:
					if (rm.mi_type == MODRM_REGISTER ||
					    rm.mi_index == 0xff ||
					    rm.mi_rm == 0xff) {
						disasm_print(self, "??" "? /*", 6);
						da_print_modrm_rm(self, &rm, flags, DA86_IS64(self) ? 8 : 4);
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
					if (rm.mi_type == MODRM_REGISTER) {
						da_print_stireg(self, rm.mi_rm);
					} else {
						da_print_modrm_rm(self, &rm, flags, DA86_IS64(self) ? 16 : 8);
					}
					break;

				case OPC_S8:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#tx", (ptrdiff_t)*(s8 *)self->d_pc);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 1;
					break;

				case OPC_U8:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#I8x", *(u8 *)self->d_pc);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 1;
					break;

				case OPC_S16:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#tx", (ptrdiff_t)(s16)UNALIGNED_GET16((u16 *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 2;
					break;

				case OPC_U16:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#I16x", UNALIGNED_GET16((u16 *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 2;
					break;

				case OPC_S32:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#tx", (ptrdiff_t)(s32)UNALIGNED_GET32((u32 *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 4;
					break;

				case OPC_U32:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#I32x", UNALIGNED_GET32((u32 *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 4;
					break;

				case OPC_U64:
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#I64x", UNALIGNED_GET64((u64 *)self->d_pc));
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					self->d_pc += 8;
					break;

				case ':': {
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
							regname[3] = '0' + ((uint8_t)(name - 'O') >> 1);
							regname[4] = (name - 'K') & 1 ? 'd' : 'w';
							reglen = 5;
						} else {
							regname[2] = '8' + ((uint8_t)(name - 'K') >> 1);
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
						/* %al, %cl, %dl, %bl, %ah, %ch, %dh, %bh */
						regname[1] = conv_table2[(name - OP_GP16_MIN) & 3];
						regname[2] = (name >= (OP_GP16_MIN + 4)) ? 'h' : 'l';
						reglen = 3;
					} else if (name >= OP_X64_RN_MIN && name <= OP_X64_RN_MAX) {
						/* %r8 - %r15 */
						regname[1] = 'r';
						if (name >= OP_X64_RN_MIN + 2) {
							regname[2] = '1';
							regname[3] = '0' + (name - (OP_X64_RN_MIN + 2));
							reglen = 4;
						} else {
							regname[2] = '8' + (name - OP_X64_RN_MIN);
							reglen = 3;
						}
					} else if (name == 'a' || name == 'b') {
						unsigned int i, n;
						/* OP_PAX_PCX_PDX / OP_PAX_PCX */
						n = name == 'b' ? 2 : 3;
						if (!DA86_IS64(self) && (DA86_IS16(self) ^ ((flags & F_66) != 0))) {
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
					} else if (name == 'c') { /* OP_PSI */
						if (!DA86_IS64(self) && (DA86_IS16(self) ^ ((flags & F_66) != 0))) {
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

				{
					uintptr_t addr;
				case OPC_MOFFS8:
					addr = (uintptr_t) * (u8 *)self->d_pc;
					self->d_pc += 1;
					goto do_print_moffs;
				case OPC_MOFFS16:
					addr = (uintptr_t)UNALIGNED_GET16((u16 *)self->d_pc);
					self->d_pc += 2;
					goto do_print_moffs;
				case OPC_MOFFS32:
					addr = (uintptr_t)UNALIGNED_GET32((u32 *)self->d_pc);
					self->d_pc += 4;
					goto do_print_moffs;
				case OPC_MOFFS64:
					addr = (uintptr_t)UNALIGNED_GET64((u64 *)self->d_pc);
					self->d_pc += 8;
do_print_moffs:
					if ((flags & F_SEGMASK) != 0)
						disasm_print(self, segment_prefix[((flags & F_SEGMASK) >> F_SEGSHIFT) - 1], 4);
					libda_disasm_print_symbol(self, (void *)addr);
				}	break;

				case OPC_R8:
					da_print_reg8(self, rm.mi_reg, flags);
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
					da_print_reg8(self, (flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S, flags);
					break;

				case OPC_VR16:
					da_print_reg16(self, (flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S);
					break;

				case OPC_VR32:
					da_print_reg32(self, (flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S);
					break;

				case OPC_VR64:
					da_print_reg64(self, (flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S);
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

				case OPC_DISP8:
					libda_disasm_print_symbol(self,
					                          (self->d_pc + 1 + self->d_baseoff) +
					                          ((intptr_t)*(s8 *)self->d_pc));
					self->d_pc += 1;
					break;
				case OPC_DISP16:
					libda_disasm_print_symbol(self,
					                          (self->d_pc + 2 + self->d_baseoff) +
					                          ((intptr_t)(s16)UNALIGNED_GET16((u16 *)self->d_pc)));
					self->d_pc += 2;
					break;
				case OPC_DISP32:
					libda_disasm_print_symbol(self,
					                          (self->d_pc + 4 + self->d_baseoff) +
					                          ((intptr_t)(s32)UNALIGNED_GET32((u32 *)self->d_pc)));
					self->d_pc += 4;
					break;

				case OPC_LJMP: {
					u16 segment;
					u32 offset;
					if (flags & F_AD16) {
						offset = UNALIGNED_GET16((u16 *)self->d_pc);
						self->d_pc += 2;
					} else {
						offset = UNALIGNED_GET32((u32 *)self->d_pc);
						self->d_pc += 4;
					}
					segment = UNALIGNED_GET16((u16 *)self->d_pc);
					self->d_pc += 2;
					disasm_print(self, "$", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX);
					disasm_printf(self, "%#I16x", segment);
					disasm_print_format(self, DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX);
					disasm_print(self, ":", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_SYMBOL_PREFIX);
					disasm_printf(self, "%#I32p", offset);
					disasm_print_format(self, DISASSEMBLER_FORMAT_SYMBOL_SUFFIX);
				}	break;

				case '{': {
					char const *end;
					end = strchrnul(p, '}');
					disasm_print(self, p, (size_t)(end - p));
					p = end;
					if (*p)
						++p;
				}	break;

				default:
					disasm_print(self, p - 1, 1);
					break;
				}
			}
		}
#ifdef CONFIG_AUTOSELECT_JCC
		/* Remember the last-written opcode (for selecting JCC encodings) */
		self->d_pad1[0] = (void *)(uintptr_t)whole_opcode;
		self->d_pad1[1] = (void *)(uintptr_t)rm.mi_reg;
#endif /* CONFIG_AUTOSELECT_JCC */
		return;
	}
unknown_opcode:
	self->d_pc = text_start;
	goto print_byte;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */


DECL_END

#endif /* !GUARD_LIBDISASM_X86_C */
