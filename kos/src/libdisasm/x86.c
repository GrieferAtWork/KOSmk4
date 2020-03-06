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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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

#include "_binstr.h"

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
#define F_OP16        0x00000001 /* The 0x66 prefix is being used. */
#define F_AD16        0x00000002 /* The 0x67 prefix is being used. */
#define F_LOCK        0x00000004 /* The `lock' (0xf0) prefix is being used. */
#define F_REPNE       0x00000010 /* The `repne' (0xf2) prefix is being used. */
#define F_REP         0x00000020 /* The `rep' (0xf3) prefix is being used. */
#define F_HASVEX      0x00000040 /* A VEX prefix was given. */
#define F_SEGMASK     0x0000f000 /* Mask for segment overrides. */
#define F_SEGSHIFT            12 /* Shift for segment overrides. */
#define F_VEX_VVVVV_M 0x001f0000 /* Mask for EVEX.Vi + VEX.VVVV */
#define F_VEX_VVVVV_S         16 /* Shift for EVEX.Vi + VEX.VVVV */
#define F_VEX_W       0x00200000 /* Value of VEX.W */
#define F_VEX_LL_M    0x00c00000 /* Value of VEX.LL */
#define F_VEX_LL_S            22 /* Shift for VEX.LL */
#define F_EVEX_z      0x01000000 /* Value of EVEX.z */
#define F_EVEX_b      0x02000000 /* Value of EVEX.b */
#define F_EVEX_R      0x04000000 /* The EVEX.R flag (a second 1-bit extension to MODRM.reg; use with `F_REX_R'). */
#define F_EVEX_aaa_M  0x38000000 /* Value of EVEX.aaa */
#define F_EVEX_aaa_S          27 /* Shift for EVEX.aaa */
#define F_HASEVEX     0x40000000 /* An EVEX prefix was given. */
#define F_AD64        F_AD16     /* The 0x67 prefix is being used. */
#define F_HASREX      0x00000080 /* A REX prefix is being used. */
#define F_REXSHFT              8 /* Shift for the REX prefix byte. */
#define F_REXMASK     0x00000f00 /* Mask of the REX prefix byte. */
#define F_REX_W       0x00000800 /* The REX.W flag (Indicates 64-bit operands). */
#define F_REX_R       0x00000400 /* The REX.R flag (1-bit extension to MODRM.reg). */
#define F_REX_X       0x00000200 /* The REX.X flag (1-bit extension to SIB.index). */
#define F_REX_B       0x00000100 /* The REX.B flag (1-bit extension to MODRM.rm). */
#define F_SEGDS       0x00001000 /* DS override. */
#define F_SEGES       0x00002000 /* ES override. */
#define F_SEGCS       0x00003000 /* CS override. */
#define F_SEGSS       0x00004000 /* SS override. */
#define F_SEGFS       0x00005000 /* FS override. */
#define F_SEGGS       0x00006000 /* GS override. */

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
		if (flags & F_EVEX_R)
			info->mi_reg |= 0x10;
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
			if ((flags & (F_REX_X | F_HASVEX)) == (F_REX_X | F_HASVEX))
				info->mi_rm |= 0x10;
			break;

		default: __builtin_unreachable();
		}
		if (flags & F_REX_B)
			info->mi_rm |= 0x8;
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

#define EVEX_IDENT_M  0x0c0400 /* Mask of constant bits */
#define EVEX_IDENT_V  0x000400 /* Value of constant bits */
#define EVEX_R        0x800000 /* FLAG:  VEX.R */
#define EVEX_X        0x400000 /* FLAG:  VEX.X */
#define EVEX_B        0x200000 /* FLAG:  VEX.B */
#define EVEX_Ri       0x100000 /* FLAG:  EVEX.R' */
#define EVEX_MM_M     0x030000 /* MASK:  EVEX.M_MM (same as VEX.M_MMMM) */
#define EVEX_MM_S           16 /* SHIFT: EVEX.M_MM */
#define EVEX_W        0x008000 /* FLAG:  VEX.W */
#define EVEX_VVVV_M   0x007800 /* MASK:  VEX.VVVV */
#define EVEX_VVVV_S         11 /* SHIFT: VEX.VVVV */
#define EVEX_PP_M     0x000300 /* MASK:  VEX.PP */
#define EVEX_PP_S            8 /* SHIFT: VEX.PP */
#define EVEX_z        0x000080 /* FLAG:  EVEX.z */
#define EVEX_Li       0x000040 /* FLAG:  EVEX.L' */
#define EVEX_L        0x000020 /* FLAG:  VEX.L */
#define EVEX_b        0x000010 /* FLAG:  EVEX.b */
#define EVEX_Vi       0x000008 /* FLAG:  EVEX.V' */
#define EVEX_aaa_M    0x000007 /* MASK:  EVEX.aaa */
#define EVEX_aaa_S           0 /* SHIFT: EVEX.aaa */

	/* EVEX Prefix */
	case 0x62: {
		u32 evex;
		/* EVEX only exists in 64-bit mode! */
		if (!DA86_IS64(self))
			break;
		evex = *text++;
		evex <<= 8;
		evex |= *text++;
		evex <<= 8;
		evex |= *text++;
		if ((evex & EVEX_IDENT_M) != EVEX_IDENT_V) {
			text -= 3;
			/*result = 0x62;*/
			break;
		}
		*pflags |= F_HASVEX | F_HASEVEX;
		*pflags |= ((~evex & EVEX_VVVV_M) >> EVEX_VVVV_S) << F_VEX_VVVVV_S;
		*pflags |= ((evex & EVEX_aaa_M) >> EVEX_aaa_S) << F_EVEX_aaa_S;
		if (!(evex & EVEX_Vi))
			*pflags |= 0x10 << F_VEX_VVVVV_S;
		if (!(evex & EVEX_R))
			*pflags |= F_REX_R;
		if (!(evex & EVEX_Ri))
			*pflags |= F_EVEX_R;
		if (!(evex & EVEX_X))
			*pflags |= F_REX_X;
		if (!(evex & EVEX_B))
			*pflags |= F_REX_B;
		if (evex & EVEX_W)
			*pflags |= F_VEX_W;
		if (evex & EVEX_z)
			*pflags |= F_EVEX_z;
		if (evex & EVEX_b)
			*pflags |= F_EVEX_b;
		if (evex & EVEX_L)
			*pflags |= 1 << F_VEX_LL_S;
		if (evex & EVEX_Li)
			*pflags |= 2 << F_VEX_LL_S;
		switch (evex & EVEX_PP_M) {
		case 0x01 << EVEX_PP_S: *pflags |= F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << EVEX_PP_S: *pflags |= F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << EVEX_PP_S: *pflags |= F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		switch (evex & EVEX_MM_M) {
		case 0x1 << EVEX_MM_S: result = 0x0f00; break;
		case 0x2 << EVEX_MM_S: result = 0x0f3800; break;
		case 0x3 << EVEX_MM_S: result = 0x0f3a00; break;
		default: goto err;
		}
		/* The actual instruction opcode byte */
		result |= *text++;
	}	break;

#define VEX3B_R       0x8000 /* FLAG:  3-byte VEX.R */
#define VEX3B_X       0x4000 /* FLAG:  3-byte VEX.X */
#define VEX3B_B       0x2000 /* FLAG:  3-byte VEX.B */
#define VEX3B_MMMMM_M 0x1f00 /* MASK:  3-byte VEX.MMMMM */
#define VEX3B_MMMMM_S      8 /* SHIFT: 3-byte VEX.MMMMM */
#define VEX3B_W       0x0080 /* FLAG:  3-byte VEX.W */
#define VEX3B_VVVV_M  0x0078 /* MASK:  3-byte VEX.VVVV */
#define VEX3B_VVVV_S       3 /* SHIFT: 3-byte VEX.VVVV */
#define VEX3B_L       0x0004 /* FLAG:  3-byte VEX.L */
#define VEX3B_PP_M    0x0003 /* MASK:  3-byte VEX.PP */
#define VEX3B_PP_S         0 /* SHIFT: 3-byte VEX.PP */

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
			*pflags |= 1 << F_VEX_LL_S;
		if (vex & VEX3B_W)
			*pflags |= F_VEX_W;
		*pflags |= ((~vex & VEX3B_VVVV_M) >> VEX3B_VVVV_S) << F_VEX_VVVVV_S;
		switch (vex & VEX3B_PP_M) {
		case 0x01 << VEX3B_PP_S: *pflags |= F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << VEX3B_PP_S: *pflags |= F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << VEX3B_PP_S: *pflags |= F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		switch (vex & VEX3B_MMMMM_M) {
		case 0x1 << VEX3B_MMMMM_S: result = 0x0f00; break;
		case 0x2 << VEX3B_MMMMM_S: result = 0x0f3800; break;
		case 0x3 << VEX3B_MMMMM_S: result = 0x0f3a00; break;
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
			*pflags |= 1 << F_VEX_LL_S;
		*pflags |= ((~result & VEX2B_VVVV_M) >> VEX2B_VVVV_S) << F_VEX_VVVVV_S;
		switch (result & VEX2B_PP_M) {
		case 0x01 << VEX2B_PP_S: *pflags |= F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << VEX2B_PP_S: *pflags |= F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << VEX2B_PP_S: *pflags |= F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		/* The actual instruction opcode byte */
		result = 0x0f00 | *text++;
		break;

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
da_regno31_str(char name[2], u8 regno) {
	regno &= 31;
	if (regno >= 10) {
		name[0] = '0' + (regno / 10);
		name[1] = '0' + (regno % 10);
	} else {
		name[0] = '0' + regno;
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
	name[2] = '0' + (regno & 7);
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
da_print_Xmmmask(struct disassembler *__restrict self, op_flag_t flags) {
	if ((flags & F_EVEX_aaa_M) != 0) {
		disasm_print(self, "{", 1);
		da_print_kreg(self, (flags & F_EVEX_aaa_M) >> F_EVEX_aaa_S);
		disasm_print(self, "}", 1);
	}
	if (flags & F_EVEX_z) {
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
                         struct modrm const *__restrict rm,
                         op_flag_t flags) {
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
		da_print_modrm_rm_memory(self, rm, flags);
	}
}

PRIVATE void CC
da_print_modrm_rm64_mm(struct disassembler *__restrict self,
                       struct modrm const *__restrict rm,
                       op_flag_t flags) {
	if (rm->mi_type == MODRM_REGISTER) {
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
                         struct modrm const *__restrict rm,
                         op_flag_t flags, char x) {
	if (rm->mi_type == MODRM_REGISTER) {
		da_print_Xmmreg(self, rm->mi_rm, x);
	} else {
		da_print_modrm_rm_memory(self, rm, flags);
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
#define IF_BYTE2 0x3017 /* The first repr-byte is required as a follow-up on the instruction byte. */
#define IF_66    0x0020
#define IF_F2    0x0040
#define IF_F3    0x0080
#define IF_67    0x0100
#define IF_REXW  0x0200
#define IF_REXB  0xc000
#define IF_RMM   0x0400 /* Modrm is memory */
#define IF_RMR   0x0800 /* Modrm is register */
#define IF_VEXW0 0x1000 /* VEX + VEX.W == 0 */
#define IF_VEXW1 0x2000 /* VEX + VEX.W == 1 */
#define IF_VEX   0x3000 /* VEX (further specified by first character of repr) */
#define IF_VEX_B0_LL_M   0x03 /* Required value for `VEX.LL' */
#define IF_VEX_B0_LL_S      0 /* Required value for `VEX.LL' */
#define IF_VEX_B0_LIG    0x03 /* Value of `IF_VEX_B0_LL_M' when vector length should be ignored. */
#define IF_VEX_B0_W      0x04 /* Required value for `VEX.W' */
#define IF_VEX_B0_WIG    0x08 /* Ignore `VEX.W' (`IF_VEX_B0_W' must not be set) */
#define IF_VEX_B0_NOEVEX 0x10 /* Require that no EVEX prefix be given */
#define IF_X32   0x4000
#define IF_X64   0x8000
	u16  i_flags;    /* Instruction flags. */
	u8   i_opcode;   /* Instruction opcode. */
	char i_repr[13];
};
#define _OP_VEX_B02(noevex, wig, w, ll) BINSTR_000##noevex##wig##w##ll
#define _OP_VEX_B0(noevex, wig, w, ll)  _OP_VEX_B02(noevex, wig, w, ll)
#define OP_VEX_B0(noevex, wig, w, ll)   _OP_VEX_B0(NORMBIN1(noevex), NORMBIN1(wig), NORMBIN1(w), NORMBIN2(ll))
#define B_OP_VEX_B0(noevex, wig, w, ll)  \
	(((noevex) ? IF_VEX_B0_NOEVEX : 0) | \
	 ((wig) ? IF_VEX_B0_WIG : 0) |       \
	 ((w) ? IF_VEX_B0_W : 0) |           \
	 ((ll) << IF_VEX_B0_LL_S))

#define _OP_VEX_B02_LIG(noevex, wig, w) BINSTR_000##noevex##wig##w##11
#define _OP_VEX_B0_LIG(noevex, wig, w)  _OP_VEX_B02_LIG(noevex, wig, w)
#define OP_VEX_B0_LIG(noevex, wig, w)   _OP_VEX_B0_LIG(NORMBIN1(noevex), NORMBIN1(wig), NORMBIN1(w))
#define B_OP_VEX_B0_LIG(noevex, wig, w)  \
	(((noevex) ? IF_VEX_B0_NOEVEX : 0) | \
	 ((wig) ? IF_VEX_B0_WIG : 0) |       \
	 ((w) ? IF_VEX_B0_W : 0) |           \
	 IF_VEX_B0_LL_M)


/* Valid operand namespace: ASCII 0x20-0x7e */

/*      OPC_            ' '  * ... */
/*      OP_             " "  * ... */
#define OPC_RM128_XMM__OPC_VRXMM__OPC_RXMM_MASK '!' /* Short form of: OPC_RM128_XMM OPC_VRXMM OPC_RXMM_MASK */
#define OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK    "!" /* Short form of: OP_RM128_XMM OP_VRXMM OP_RXMM_MASK */
#define OP_RM128_XMM__OP_VRXMM__OP_RXMM         "!" /* Short form of: OP_RM128_XMM OP_VRXMM OP_RXMM_MASK */
#define OPC_RM256_YMM__OPC_VRYMM__OPC_RYMM_MASK '\"'/* Short form of: OPC_RM256_YMM OPC_VRYMM OPC_RYMM_MASK */
#define OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK    "\""/* Short form of: OP_RM256_YMM OP_VRYMM OP_RYMM_MASK */
#define OP_RM256_YMM__OP_VRYMM__OP_RYMM         "\""/* Short form of: OP_RM256_YMM OP_VRYMM OP_RYMM_MASK */
#define OPC_RM512_ZMM__OPC_VRZMM__OPC_RZMM_MASK '#' /* Short form of: OPC_RM512_ZMM OPC_VRZMM OPC_RZMM_MASK */
#define OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK    "#" /* Short form of: OP_RM512_ZMM OP_VRZMM OP_RZMM_MASK */
#define OP_RM512_ZMM__OP_VRZMM__OP_RZMM         "#" /* Short form of: OP_RM512_ZMM OP_VRZMM OP_RZMM_MASK */
#define OPC_VRXMM_MASK  '$' /* %xmm0, %xmm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OP_VRXMM_MASK   "$" /* %xmm0, %xmm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OPC_VRYMM_MASK  '%' /* %ymm0, %ymm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OP_VRYMM_MASK   "%" /* %ymm0, %ymm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OPC_VRZMM_MASK  '&' /* %zmm0, %zmm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OP_VRZMM_MASK   "&" /* %zmm0, %zmm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OPC_RXMM        '\''/* %xmm0, %xmm1, etc. (based on rm.mi_reg) */
#define OP_RXMM         "\'"/* %xmm0, %xmm1, etc. (based on rm.mi_reg) */
#define OPC_RYMM        '(' /* %ymm0, %ymm1, etc. (based on rm.mi_reg) */
#define OP_RYMM         "(" /* %ymm0, %ymm1, etc. (based on rm.mi_reg) */
#define OPC_RZMM        ')' /* %zmm0, %zmm1, etc. (based on rm.mi_reg) */
#define OP_RZMM         ")" /* %zmm0, %zmm1, etc. (based on rm.mi_reg) */
#define OPC_XRM64       '*' /* 64-bit register or memory location prefixed by `*' (requires IF_MODRM) */
#define OP_XRM64        "*" /* 64-bit register or memory location prefixed by `*' (requires IF_MODRM) */
#define OPC_XRM32       '+' /* 32-bit register or memory location prefixed by `*' (requires IF_MODRM) */
#define OP_XRM32        "+" /* 32-bit register or memory location prefixed by `*' (requires IF_MODRM) */
#define OPC_RMM         ',' /* %mm0, %mm1, etc. (based on rm.mi_reg) */
#define OP_RMM          "," /* %mm0, %mm1, etc. (based on rm.mi_reg) */
#define OPC_RXMM_MASK   '-' /* %xmm0, %xmm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OP_RXMM_MASK    "-" /* %xmm0, %xmm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OPC_RYMM_MASK   '.' /* %ymm0, %ymm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OP_RYMM_MASK    "." /* %ymm0, %ymm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OPC_RZMM_MASK   '/' /* %zmm0, %zmm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OP_RZMM_MASK    "/" /* %zmm0, %zmm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OPC_RM8         '0' /* 8-bit register or memory location (requires IF_MODRM) */
#define OP_RM8          "0" /* 8-bit register or memory location (requires IF_MODRM) */
#define OPC_RM16        '1' /* 16-bit register or memory location (requires IF_MODRM) */
#define OP_RM16         "1" /* 16-bit register or memory location (requires IF_MODRM) */
#define OPC_RM32        '2' /* 32-bit register or memory location (requires IF_MODRM) */
#define OP_RM32         "2" /* 32-bit register or memory location (requires IF_MODRM) */
#define OP_MEM          "3" /* Memory location (requires IF_MODRM) */
#define OPC_RM64        '3' /* 64-bit register or memory location (requires IF_MODRM) */
#define OP_RM64         "3" /* 64-bit register or memory location (requires IF_MODRM) */
#define OPC_RMBND       '4' /* %bndN register or memory location (requires IF_MODRM) */
#define OP_RMBND        "4" /* %bndN register or memory location (requires IF_MODRM) */
#define OPC_RMBND_RANGE '5' /* %bndN:%bndN register pair (requires IF_MODRM) */
#define OP_RMBND_RANGE  "5" /* %bndN:%bndN register pair (requires IF_MODRM) */
#define OPC_RMSTi       '6' /* %st(N) register or memory location (requires IF_MODRM) */
#define OP_RMSTi        "6" /* %st(N) register or memory location (requires IF_MODRM) */
#define OPC_RM128_XMM_MASK '7' /* 128-bit memory location or %xmm0, %xmm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OP_RM128_XMM_MASK  "7" /* 128-bit memory location or %xmm0, %xmm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OP_MEM_MASK        "7" /* Memory location (requires IF_MODRM) (followed by {%kN}{z}) */
#define OPC_RM256_YMM_MASK '8' /* 256-bit memory location or %ymm0, %ymm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OP_RM256_YMM_MASK  "8" /* 256-bit memory location or %ymm0, %ymm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OPC_RM512_ZMM_MASK '9' /* 512-bit memory location or %zmm0, %zmm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OP_RM512_ZMM_MASK  "9" /* 512-bit memory location or %zmm0, %zmm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OPC_SHORT       ':' /* Prefix for shortened register names */
#define OP_SHORT        ":" /* Prefix for shortened register names */
#define OPC_RM64_MM     ';' /* 64-bit memory location or %mm0, %mm1, etc. (based on rm.mi_rm) */
#define OP_RM64_MM      ";" /* 64-bit memory location or %mm0, %mm1, etc. (based on rm.mi_rm) */
#define OPC_RM128_XMM   '<' /* 128-bit memory location or %xmm0, %xmm1, etc. (based on rm.mi_rm) */
#define OP_RM128_XMM    "<" /* 128-bit memory location or %xmm0, %xmm1, etc. (based on rm.mi_rm) */
#define OPC_RM256_YMM   '=' /* 256-bit memory location or %ymm0, %ymm1, etc. (based on rm.mi_rm) */
#define OP_RM256_YMM    "=" /* 256-bit memory location or %ymm0, %ymm1, etc. (based on rm.mi_rm) */
#define OPC_RM512_ZMM   '>' /* 512-bit memory location or %zmm0, %zmm1, etc. (based on rm.mi_rm) */
#define OP_RM512_ZMM    ">" /* 512-bit memory location or %zmm0, %zmm1, etc. (based on rm.mi_rm) */
#define OPC_LONGREPR    '?' /* Indicator for a long representation string. */
#define OPC_VRXMM       '@' /* %xmm0, %xmm1, etc. (based on F_VEX_VVVVV_M) */
#define OP_VRXMM        "@" /* %xmm0, %xmm1, etc. (based on F_VEX_VVVVV_M) */
#define OPC_U8          'A' /* imm8 (read from *PC before doing PC+=1) */
#define OP_U8           "A" /* imm8 (read from *PC before doing PC+=1) */
#define OPC_U16         'B' /* imm16 (read from *PC before doing PC+=2) */
#define OP_U16          "B" /* imm16 (read from *PC before doing PC+=2) */
#define OPC_U32         'C' /* imm32 (read from *PC before doing PC+=4) */
#define OP_U32          "C" /* imm32 (read from *PC before doing PC+=4) */
#define OPC_RMK         'D' /* %kN register or memory location (requires IF_MODRM) */
#define OP_RMK          "D" /* %kN register or memory location (requires IF_MODRM) */
#define OPC_MOFFS8      'E' /* moffs8 (read from *PC before doing PC+=1) */
#define OP_MOFFS8       "E" /* moffs8 (read from *PC before doing PC+=1) */
#define OPC_MOFFS16     'F' /* moffs16 (read from *PC before doing PC+=2) */
#define OP_MOFFS16      "F" /* moffs16 (read from *PC before doing PC+=2) */
#define OPC_MOFFS32     'G' /* moffs32 (read from *PC before doing PC+=4) */
#define OP_MOFFS32      "G" /* moffs32 (read from *PC before doing PC+=4) */
#define OPC_MOFFS64     'H' /* moffs64 (read from *PC before doing PC+=8) */
#define OP_MOFFS64      "H" /* moffs64 (read from *PC before doing PC+=8) */
/*      OPC_            'I'  * ... */
/*      OP_             "I"  * ... */
/*      OPC_            'J'  * ... */
/*      OP_             "J"  * ... */
/*      OPC_            'K'  * ... */
/*      OP_             "K"  * ... */
/*      OPC_            'L'  * ... */
/*      OP_             "L"  * ... */
/*      OPC_            'M'  * ... */
/*      OP_             "M"  * ... */
/*      OPC_            'N'  * ... */
/*      OP_             "N"  * ... */
/*      OPC_            'O'  * ... */
/*      OP_             "O"  * ... */
#define OPC_LJMP        'P' /* seg:offset pair (read from *PC before doing PC+=(4|6)) */
#define OP_LJMP         "P" /* seg:offset pair (read from *PC before doing PC+=(4|6)) */
/*      OPC_            'Q'  * ... */
/*      OP_             "Q"  * ... */
#define OPC_VR8         'R' /* 8-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OP_VR8          "R" /* 8-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OPC_VR16        'S' /* 16-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OP_VR16         "S" /* 16-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OPC_VR32        'T' /* 32-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OP_VR32         "T" /* 32-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OPC_VR64        'U' /* 64-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OP_VR64         "U" /* 64-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
/*      OPC_            'V'  * ... */
/*      OP_             "V"  * ... */
/*      OPC_            'W'  * ... */
/*      OP_             "W"  * ... */
/*      OPC_            'X'  * ... */
/*      OP_             "X"  * ... */
/*      OPC_            'Y'  * ... */
/*      OP_             "Y"  * ... */
/*      OPC_            'Z'  * ... */
/*      OP_             "Z"  * ... */
/*      OPC_            '['  * ... */
/*      OP_             "["  * ... */
/*      OPC_            '\\' * ... */
/*      OP_             "\\" * ... */
/*      OPC_            ']'  * ... */
/*      OP_             "]"  * ... */
/*      OPC_            '^'  * ... */
/*      OP_             "^"  * ... */
#define OPC_VRK         '_' /* %kN register (based on F_VEX_VVVVV_M) */
#define OP_VRK          "_" /* %kN register (based on F_VEX_VVVVV_M) */
#define OPC_VRYMM       '`' /* %ymm0, %ymm1, etc. (based on F_VEX_VVVVV_M) */
#define OP_VRYMM        "`" /* %ymm0, %ymm1, etc. (based on F_VEX_VVVVV_M) */
#define OPC_S8          'a' /* Simm8 (read from *PC before doing PC+=1) */
#define OP_S8           "a" /* Simm8 (read from *PC before doing PC+=1) */
#define OPC_S16         'b' /* Simm16 (read from *PC before doing PC+=2) */
#define OP_S16          "b" /* Simm16 (read from *PC before doing PC+=2) */
#define OPC_S32         'c' /* Simm32 (read from *PC before doing PC+=4) */
#define OP_S32          "c" /* Simm32 (read from *PC before doing PC+=4) */
#define OPC_U64         'd' /* imm64 (read from *PC before doing PC+=8) */
#define OP_U64          "d" /* imm64 (read from *PC before doing PC+=8) */
/*      OPC_            'e'  * ... */
/*      OP_             "e"  * ... */
/*      OPC_            'f'  * ... */
/*      OP_             "f"  * ... */
/*      OPC_            'g'  * ... */
/*      OP_             "g"  * ... */
/*      OPC_            'h'  * ... */
/*      OP_             "h"  * ... */
/*      OPC_            'i'  * ... */
/*      OP_             "i"  * ... */
/*      OPC_            'j'  * ... */
/*      OP_             "j"  * ... */
/*      OPC_            'k'  * ... */
/*      OP_             "k"  * ... */
/*      OPC_            'l'  * ... */
/*      OP_             "l"  * ... */
#define OPC_DISP8       'm' /* 8-bit PC-displacement symbol */
#define OP_DISP8        "m" /* 8-bit PC-displacement symbol */
#define OPC_DISP16      'n' /* 16-bit PC-displacement symbol */
#define OP_DISP16       "n" /* 16-bit PC-displacement symbol */
#define OPC_DISP32      'o' /* 32-bit PC-displacement symbol */
#define OP_DISP32       "o" /* 32-bit PC-displacement symbol */
/*      OPC_            'p'  * ... */
/*      OP_             "p"  * ... */
#define OPC_RK          'q' /* %kN register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RK           "q" /* %kN register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_R8          'r' /* 8-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_R8           "r" /* 8-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_R16         's' /* 16-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_R16          "s" /* 16-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_R32         't' /* 32-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_R32          "t" /* 32-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_R64         'u' /* 64-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_R64          "u" /* 64-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_RSEG        'v' /* segment register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RSEG         "v" /* segment register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_RCR         'w' /* %crN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RCR          "w" /* %crN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_RDR         'x' /* %drN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RDR          "x" /* %drN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_RBND        'y' /* %bndN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RBND         "y" /* %bndN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_RTR         'z' /* %trN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RTR          "z" /* %trN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_ESC         '{' /* Start of an inlined, escaped operand representation */
#define OPC_ESC_END     '}' /* End of an inlined, escaped operand representation (only recognized after `OPC_ESC') */
#define OP_ESC(s)       "{" s "}" /* Insert an escaped operand representation */
#define OPC_VRZMM       '|' /* %zmm0, %zmm1, etc. (based on F_VEX_VVVVV_M) */
#define OP_VRZMM        "|" /* %zmm0, %zmm1, etc. (based on F_VEX_VVVVV_M) */
/*      OPC_            '}'  * ... */
/*      OP_             "}"  * ... */
#define OPC_XRM16       '~' /* 16-bit register or memory location prefixed by `*' (requires IF_MODRM) */
#define OP_XRM16        "~" /* 16-bit register or memory location prefixed by `*' (requires IF_MODRM) */

#define OP_PAX_PCX_PDX OP_SHORT "a" /* %ax, %cx, %dx | %eax, %ecx, %edx | %rax, %rcx, %rdx (same as pointer-size; s.a. `DA86_IS(16|32|64)()') */
#define OP_PAX_PCX     OP_SHORT "b" /* %ax, %cx | %eax, %ecx | %rax, %rcx (same as pointer-size; s.a. `DA86_IS(16|32|64)()') */
#define OP_PSI         OP_SHORT "c" /* %si, %esi, %rsi (same as pointer-size; s.a. `DA86_IS(16|32|64)()') */

/* Smaller encodings for a couple of fixed register operands.
 * While all of these could be implemented with `OP_ESC()', this
 * format uses much less memory, allowing `i_repr' to be much smaller. */
#define OP_ST0     OP_SHORT "0" /* %st(0) */
#define OP_ST1     OP_SHORT "1" /* %st(1) */
#define OP_ST2     OP_SHORT "2" /* %st(2) */
#define OP_ST3     OP_SHORT "3" /* %st(3) */
#define OP_ST4     OP_SHORT "4" /* %st(4) */
#define OP_ST5     OP_SHORT "5" /* %st(5) */
#define OP_ST6     OP_SHORT "6" /* %st(6) */
#define OP_ST7     OP_SHORT "7" /* %st(7) */
#define OP_R8W     OP_SHORT "K" /* %r8w */
#define OP_R8D     OP_SHORT "L" /* %r8d */
#define OP_R9W     OP_SHORT "M" /* %r9w */
#define OP_R9D     OP_SHORT "N" /* %r9d */
#define OP_R10W    OP_SHORT "O" /* %r10w */
#define OP_R10D    OP_SHORT "P" /* %r10d */
#define OP_R11W    OP_SHORT "Q" /* %r11w */
#define OP_R11D    OP_SHORT "R" /* %r11d */
#define OP_R12W    OP_SHORT "S" /* %r12w */
#define OP_R12D    OP_SHORT "T" /* %r12d */
#define OP_R13W    OP_SHORT "U" /* %r13w */
#define OP_R13D    OP_SHORT "V" /* %r13d */
#define OP_R14W    OP_SHORT "W" /* %r14w */
#define OP_R14D    OP_SHORT "X" /* %r14d */
#define OP_R15W    OP_SHORT "Y" /* %r15w */
#define OP_R15D    OP_SHORT "Z" /* %r15d */
#define OP_EAX     OP_SHORT "k" /* %eax */
#define OP_ECX     OP_SHORT "l" /* %ecx */
#define OP_EDX     OP_SHORT "m" /* %edx */
#define OP_EBX     OP_SHORT "n" /* %ebx */
#define OP_ESP     OP_SHORT "o" /* %esp */
#define OP_EBP     OP_SHORT "p" /* %ebp */
#define OP_ESI     OP_SHORT "q" /* %esi */
#define OP_EDI     OP_SHORT "r" /* %edi */
#define OP_RAX     OP_SHORT "s" /* %rax */
#define OP_RCX     OP_SHORT "t" /* %rcx */
#define OP_RDX     OP_SHORT "u" /* %rdx */
#define OP_RBX     OP_SHORT "v" /* %rbx */
#define OP_RSP     OP_SHORT "w" /* %rsp */
#define OP_RBP     OP_SHORT "x" /* %rbp */
#define OP_RSI     OP_SHORT "y" /* %rsi */
#define OP_RDI     OP_SHORT "z" /* %rdi */

#define OP_AX      OP_SHORT "A" /* %ax */
#define OP_CX      OP_SHORT "B" /* %cx */
#define OP_DX      OP_SHORT "C" /* %dx */
#define OP_BX      OP_SHORT "D" /* %bx */
#define OP_SP      OP_SHORT "E" /* %sp */
#define OP_BP      OP_SHORT "F" /* %bp */
#define OP_SI      OP_SHORT "G" /* %si */
#define OP_DI      OP_SHORT "H" /* %di */

#define OP_X64_RN_MIN ' '
#define OP_X64_RN_MAX '\''
#define OP_X64_R8  OP_SHORT " " /* %r8 */
#define OP_R9      OP_SHORT "!" /* %r9 */
#define OP_R10     OP_SHORT "\""/* %r10 */
#define OP_R11     OP_SHORT "#" /* %r11 */
#define OP_R12     OP_SHORT "$" /* %r12 */
#define OP_R13     OP_SHORT "%" /* %r13 */
#define OP_R14     OP_SHORT "&" /* %r14 */
#define OP_R15     OP_SHORT "\'"/* %r15 */

#define OP_GP16_MIN '('
#define OP_GP16_MAX '/'
#define OP_AL      OP_SHORT "(" /* %al */
#define OP_CL      OP_SHORT ")" /* %cl */
#define OP_DL      OP_SHORT "*" /* %dl */
#define OP_BL      OP_SHORT "+" /* %bl */
#define OP_AH      OP_SHORT "," /* %ah */
#define OP_CH      OP_SHORT "-" /* %ch */
#define OP_DH      OP_SHORT "." /* %dh */
#define OP_BH      OP_SHORT "/" /* %bh */

#define OP_DS   OP_ESC("%ds") /* %ds */
#define OP_ES   OP_ESC("%es") /* %es */
#define OP_FS   OP_ESC("%fs") /* %fs */
#define OP_GS   OP_ESC("%gs") /* %gs */
#define OP_CS   OP_ESC("%cs") /* %cs */
#define OP_SS   OP_ESC("%ss") /* %ss */

#define OP_IMM1 OP_ESC("$1")  /* $1 */
#define OP_XMM0 OP_ESC("%xmm0") /* %xmm0 */


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
#define LONGREPR(n)      { '?', (char)(u8)((n) & 0xff), (char)(u8)(((n) >> 8) & 0xff), 0 }
#define LONGREPR_B(b, n) { (char)(u8)b, '?', (char)(u8)((n) & 0xff), (char)(u8)(((n) >> 8) & 0xff), 0 }
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define LONGREPR(n)      { '?', (char)(u8)(((n) >> 8) & 0xff), (char)(u8)((n) & 0xff), 0 }
#define LONGREPR_B(b, n) { (char)(u8)b, '?', (char)(u8)(((n) >> 8) & 0xff), (char)(u8)((n) & 0xff), 0 }
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
	I(0x50, IF_REXB,         "pushq\t" OP_X64_R8),
	I(0x50, IF_X32,          "pushl\t" OP_EAX),
	I(0x50, IF_X64,          "pushq\t" OP_RAX),
	I(0x51, IF_66,           "pushw\t" OP_CX),
	I(0x51, IF_REXB,         "pushq\t" OP_R9),
	I(0x51, IF_X32,          "pushl\t" OP_ECX),
	I(0x51, IF_X64,          "pushq\t" OP_RCX),
	I(0x52, IF_66,           "pushw\t" OP_DX),
	I(0x52, IF_REXB,         "pushq\t" OP_R10),
	I(0x52, IF_X32,          "pushl\t" OP_EDX),
	I(0x52, IF_X64,          "pushq\t" OP_RDX),
	I(0x53, IF_66,           "pushw\t" OP_BX),
	I(0x53, IF_REXB,         "pushq\t" OP_R11),
	I(0x53, IF_X32,          "pushl\t" OP_EBX),
	I(0x53, IF_X64,          "pushq\t" OP_RBX),
	I(0x54, IF_66,           "pushw\t" OP_SP),
	I(0x54, IF_REXB,         "pushq\t" OP_R12),
	I(0x54, IF_X32,          "pushl\t" OP_ESP),
	I(0x54, IF_X64,          "pushq\t" OP_RSP),
	I(0x55, IF_66,           "pushw\t" OP_BP),
	I(0x55, IF_REXB,         "pushq\t" OP_R13),
	I(0x55, IF_X32,          "pushl\t" OP_EBP),
	I(0x55, IF_X64,          "pushq\t" OP_RBP),
	I(0x56, IF_66,           "pushw\t" OP_SI),
	I(0x56, IF_REXB,         "pushq\t" OP_R14),
	I(0x56, IF_X32,          "pushl\t" OP_ESI),
	I(0x56, IF_X64,          "pushq\t" OP_RSI),
	I(0x57, IF_66,           "pushw\t" OP_DI),
	I(0x57, IF_REXB,         "pushq\t" OP_R15),
	I(0x57, IF_X32,          "pushl\t" OP_EDI),
	I(0x57, IF_X64,          "pushq\t" OP_RDI),

	I(0x58, IF_66,           "popw\t" OP_AX),
	I(0x58, IF_REXB,         "popq\t" OP_X64_R8),
	I(0x58, IF_X32,          "popl\t" OP_EAX),
	I(0x58, IF_X64,          "popq\t" OP_RAX),
	I(0x59, IF_66,           "popw\t" OP_CX),
	I(0x59, IF_REXB,         "popq\t" OP_R9),
	I(0x59, IF_X32,          "popl\t" OP_ECX),
	I(0x59, IF_X64,          "popq\t" OP_RCX),
	I(0x5a, IF_66,           "popw\t" OP_DX),
	I(0x5a, IF_REXB,         "popq\t" OP_R10),
	I(0x5a, IF_X32,          "popl\t" OP_EDX),
	I(0x5a, IF_X64,          "popq\t" OP_RDX),
	I(0x5b, IF_66,           "popw\t" OP_BX),
	I(0x5b, IF_REXB,         "popq\t" OP_R11),
	I(0x5b, IF_X32,          "popl\t" OP_EBX),
	I(0x5b, IF_X64,          "popq\t" OP_RBX),
	I(0x5c, IF_66,           "popw\t" OP_SP),
	I(0x5c, IF_REXB,         "popq\t" OP_R12),
	I(0x5c, IF_X32,          "popl\t" OP_ESP),
	I(0x5c, IF_X64,          "popq\t" OP_RSP),
	I(0x5d, IF_66,           "popw\t" OP_BP),
	I(0x5d, IF_REXB,         "popq\t" OP_R13),
	I(0x5d, IF_X32,          "popl\t" OP_EBP),
	I(0x5d, IF_X64,          "popq\t" OP_RBP),
	I(0x5e, IF_66,           "popw\t" OP_SI),
	I(0x5e, IF_REXB,         "popq\t" OP_R14),
	I(0x5e, IF_X32,          "popl\t" OP_ESI),
	I(0x5e, IF_X64,          "popq\t" OP_RSI),
	I(0x5f, IF_66,           "popw\t" OP_DI),
	I(0x5f, IF_REXB,         "popq\t" OP_R15),
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

	I(0x90, IF_REXB|IF_66,    "xchgw\t" OP_R8W OP_AX),
	I(0x90, IF_REXB,          "xchgl\t" OP_R8D OP_EAX),
	I(0x90, IF_REXB|IF_REXW,  "xchgq\t" OP_X64_R8 OP_RAX),
	I(0x90, IF_66,            "xchgw\t" OP_AX  OP_AX),
/*  I(0x90, 0,                "xchgl\t" OP_EAX OP_EAX), */
	I(0x90, IF_REXW,          "xchgq\t" OP_RAX OP_RAX),
	I(0x91, IF_REXB|IF_66,    "xchgw\t" OP_R9W OP_AX),
	I(0x91, IF_REXB,          "xchgl\t" OP_R9D OP_EAX),
	I(0x91, IF_REXB|IF_REXW,  "xchgq\t" OP_R9  OP_RAX),
	I(0x91, IF_66,            "xchgw\t" OP_CX  OP_AX),
	I(0x91, 0,                "xchgl\t" OP_ECX OP_EAX),
	I(0x91, IF_REXW,          "xchgq\t" OP_RCX OP_RAX),
	I(0x92, IF_REXB|IF_66,    "xchgw\t" OP_R10W OP_AX),
	I(0x92, IF_REXB,          "xchgl\t" OP_R10D OP_EAX),
	I(0x92, IF_REXB|IF_REXW,  "xchgq\t" OP_R10 OP_RAX),
	I(0x92, IF_66,            "xchgw\t" OP_DX  OP_AX),
	I(0x92, 0,                "xchgl\t" OP_EDX OP_EAX),
	I(0x92, IF_REXW,          "xchgq\t" OP_RDX OP_RAX),
	I(0x93, IF_REXB|IF_66,    "xchgw\t" OP_R11W OP_AX),
	I(0x93, IF_REXB,          "xchgl\t" OP_R11D OP_EAX),
	I(0x93, IF_REXB|IF_REXW,  "xchgq\t" OP_R11 OP_RAX),
	I(0x93, IF_66,            "xchgw\t" OP_BX  OP_AX),
	I(0x93, 0,                "xchgl\t" OP_EBX OP_EAX),
	I(0x93, IF_REXW,          "xchgq\t" OP_RBX OP_RAX),
	I(0x94, IF_REXB|IF_66,    "xchgw\t" OP_R12W OP_AX),
	I(0x94, IF_REXB,          "xchgl\t" OP_R12D OP_EAX),
	I(0x94, IF_REXB|IF_REXW,  "xchgq\t" OP_R12 OP_RAX),
	I(0x94, IF_66,            "xchgw\t" OP_SP  OP_AX),
	I(0x94, 0,                "xchgl\t" OP_ESP OP_EAX),
	I(0x94, IF_REXW,          "xchgq\t" OP_RSP OP_RAX),
	I(0x95, IF_REXB|IF_66,    "xchgw\t" OP_R13W OP_AX),
	I(0x95, IF_REXB,          "xchgl\t" OP_R13D OP_EAX),
	I(0x95, IF_REXB|IF_REXW,  "xchgq\t" OP_R13 OP_RAX),
	I(0x95, IF_66,            "xchgw\t" OP_BP  OP_AX),
	I(0x95, 0,                "xchgl\t" OP_EBP OP_EAX),
	I(0x95, IF_REXW,          "xchgq\t" OP_RBP OP_RAX),
	I(0x96, IF_REXB|IF_66,    "xchgw\t" OP_R14W OP_AX),
	I(0x96, IF_REXB,          "xchgl\t" OP_R14D OP_EAX),
	I(0x96, IF_REXB|IF_REXW,  "xchgq\t" OP_R14 OP_RAX),
	I(0x96, IF_66,            "xchgw\t" OP_DI  OP_AX),
	I(0x96, 0,                "xchgl\t" OP_EDI OP_EAX),
	I(0x96, IF_REXW,          "xchgq\t" OP_RDI OP_RAX),
	I(0x97, IF_REXB|IF_66,    "xchgw\t" OP_R15W OP_AX),
	I(0x97, IF_REXB,          "xchgl\t" OP_R15D OP_EAX),
	I(0x97, IF_REXB|IF_REXW,  "xchgq\t" OP_R15 OP_RAX),
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

	I(0xb0, IF_REXB,          "movb\t" OP_U8 OP_R8D),
	I(0xb0, 0,                "movb\t" OP_U8 OP_AL),
	I(0xb1, IF_REXB,          "movb\t" OP_U8 OP_R9D),
	I(0xb1, 0,                "movb\t" OP_U8 OP_CL),
	I(0xb2, IF_REXB,          "movb\t" OP_U8 OP_R10D),
	I(0xb2, 0,                "movb\t" OP_U8 OP_DL),
	I(0xb3, IF_REXB,          "movb\t" OP_U8 OP_R11D),
	I(0xb3, 0,                "movb\t" OP_U8 OP_BL),
	I(0xb4, IF_REXB,          "movb\t" OP_U8 OP_R12D),
	I(0xb4, 0,                "movb\t" OP_U8 OP_AH),
	I(0xb5, IF_REXB,          "movb\t" OP_U8 OP_R13D),
	I(0xb5, 0,                "movb\t" OP_U8 OP_CH),
	I(0xb6, IF_REXB,          "movb\t" OP_U8 OP_R14D),
	I(0xb6, 0,                "movb\t" OP_U8 OP_DH),
	I(0xb7, IF_REXB,          "movb\t" OP_U8 OP_R15D),
	I(0xb7, 0,                "movb\t" OP_U8 OP_BH),

	I(0xb8, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R8W),
	I(0xb8, IF_REXB,          "movl\t"   OP_U32 OP_R8D),
	I(0xb8, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_X64_R8),
	I(0xb8, IF_66,            "movw\t"   OP_U16 OP_AX),
	I(0xb8, 0,                "movl\t"   OP_U32 OP_EAX),
	I(0xb8, IF_REXW,          "movabs\t" OP_U64 OP_RAX),
	I(0xb9, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R9W),
	I(0xb9, IF_REXB,          "movl\t"   OP_U32 OP_R9D),
	I(0xb9, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R9),
	I(0xb9, IF_66,            "movw\t"   OP_U16 OP_CX),
	I(0xb9, 0,                "movl\t"   OP_U32 OP_ECX),
	I(0xb9, IF_REXW,          "movabs\t" OP_U64 OP_RCX),
	I(0xba, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R10W),
	I(0xba, IF_REXB,          "movl\t"   OP_U32 OP_R10D),
	I(0xba, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R10),
	I(0xba, IF_66,            "movw\t"   OP_U16 OP_DX),
	I(0xba, 0,                "movl\t"   OP_U32 OP_EDX),
	I(0xba, IF_REXW,          "movabs\t" OP_U64 OP_RDX),
	I(0xbb, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R11W),
	I(0xbb, IF_REXB,          "movl\t"   OP_U32 OP_R11D),
	I(0xbb, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R11),
	I(0xbb, IF_66,            "movw\t"   OP_U16 OP_BX),
	I(0xbb, 0,                "movl\t"   OP_U32 OP_EBX),
	I(0xbb, IF_REXW,          "movabs\t" OP_U64 OP_RBX),
	I(0xbc, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R12W),
	I(0xbc, IF_REXB,          "movl\t"   OP_U32 OP_R12D),
	I(0xbc, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R12),
	I(0xbc, IF_66,            "movw\t"   OP_U16 OP_SP),
	I(0xbc, 0,                "movl\t"   OP_U32 OP_ESP),
	I(0xbc, IF_REXW,          "movabs\t" OP_U64 OP_RSP),
	I(0xbd, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R13W),
	I(0xbd, IF_REXB,          "movl\t"   OP_U32 OP_R13D),
	I(0xbd, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R13),
	I(0xbd, IF_66,            "movw\t"   OP_U16 OP_BP),
	I(0xbd, 0,                "movl\t"   OP_U32 OP_EBP),
	I(0xbd, IF_REXW,          "movabs\t" OP_U64 OP_RBP),
	I(0xbe, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R14W),
	I(0xbe, IF_REXB,          "movl\t"   OP_U32 OP_R14D),
	I(0xbe, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R14),
	I(0xbe, IF_66,            "movw\t"   OP_U16 OP_DI),
	I(0xbe, 0,                "movl\t"   OP_U32 OP_EDI),
	I(0xbe, IF_REXW,          "movabs\t" OP_U64 OP_RDI),
	I(0xbf, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R15W),
	I(0xbf, IF_REXB,          "movl\t"   OP_U32 OP_R15D),
	I(0xbf, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R15),
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

	I(0xc4, IF_66|IF_MODRM|IF_RMM, "lesw\t" OP_MEM/*32*/ OP_R16),
	I(0xc4, IF_MODRM|IF_RMM,       "lesl\t" OP_MEM/*48*/ OP_R32),
	I(0xc5, IF_66|IF_MODRM|IF_RMM, "ldsw\t" OP_MEM/*32*/ OP_R16),
	I(0xc5, IF_MODRM|IF_RMM,       "ldsl\t" OP_MEM/*48*/ OP_R32),

	I(0xc6, IF_MODRM|IF_REG0,        "movb\t" OP_U8 OP_RM8),
	I(0xc6, IF_BYTE2,         "\xf8" "xabort\t" OP_U8),

	I(0xc7, IF_66|IF_MODRM|IF_REG0,  "movw\t" OP_U16 OP_RM16),
	I(0xc7, IF_MODRM|IF_REG0,        "movl\t" OP_U32 OP_RM32),
	I(0xc7, IF_REXW|IF_MODRM|IF_REG0,"movq\t" OP_S32 OP_RM64),
	I(0xc7, IF_BYTE2|IF_66,   "\xf8" "xbeginw\t" OP_DISP16),
	I(0xc7, IF_BYTE2,         "\xf8" "xbegin\t" OP_DISP32),

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
	I(0xd9, IF_66|IF_MODRM|IF_RMM|IF_REG4, "fldenv14\t" OP_MEM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG4, "fldenv28\t" OP_MEM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG5, "fldcww\t" OP_RM16),
	I(0xd9, IF_66|IF_MODRM|IF_RMM|IF_REG6, "fnstenv94\t" OP_MEM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG6, "fnstenv108\t" OP_MEM),
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
	I(0xdb, IF_MODRM|IF_RMM|IF_REG5, "fld80" OP_MEM),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG7, "fstp80" OP_MEM),

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
	I(0xdd, IF_66|IF_MODRM|IF_RMM|IF_REG4, "frstor94\t" OP_MEM),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG4, "frstor108\t" OP_MEM),
	I(0xdd, IF_66|IF_MODRM|IF_RMM|IF_REG6, "fnsave94\t" OP_MEM),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG6, "fnsave108\t" OP_MEM),
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
	I(0xdf, IF_MODRM|IF_RMM|IF_REG4, "fbld\t" OP_MEM),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG5, "fildq\t" OP_RM64),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG6, "fbstp\t" OP_MEM),
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

	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG0,  "sgdtl\t" OP_MEM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG0,  "sgdtq\t" OP_MEM),
	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG1,  "sidtl\t" OP_MEM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG1,  "sidtq\t" OP_MEM),
	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG2,  "lgdtl\t" OP_MEM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG2,  "lgdtq\t" OP_MEM),
	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG3,  "lidtl\t" OP_MEM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG3,  "lidtq\t" OP_MEM),

	I(0x01, IF_66|IF_MODRM|IF_REG4,          "smsww\t" OP_RM16),
	I(0x01, IF_MODRM|IF_REG4,                "smswl\t" OP_RM32),
	I(0x01, IF_REXW|IF_MODRM|IF_REG4,        "smswq\t" OP_RM64),

	I(0x01, IF_MODRM|IF_REG6,                "lmsw\t" OP_RM16),

	I(0x01, IF_MODRM|IF_RMM|IF_REG7,         "invlpg\t" OP_MEM),

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

	I(0x0d, IF_MODRM|IF_REG1|IF_RMM, "prefetchw\t" OP_MEM),
	I(0x0d, IF_MODRM|IF_REG2|IF_RMM, LONGREPR(LO_PREFETCHWT1)),

	I(0x10, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovups\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.0f.WIG 10 /r vmovups xmm1, xmm2/m128 */
	I(0x10, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovups\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.0f.WIG 10 /r vmovups ymm1, ymm2/m256 */
	I(0x10, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovups\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.0f.W0  10 /r vmovups xmm1{k1}{z}, xmm2/m128 */
	I(0x10, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovups\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.0f.W0  10 /r vmovups ymm1{k1}{z}, ymm2/m256 */
	I(0x10, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovups\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.0f.W0  10 /r vmovups zmm1{k1}{z}, zmm2/m512 */
	I(0x10, IF_MODRM,                              "movups\t" OP_RM128_XMM OP_RXMM),       /*              0f 10 /r movups xmm1, xmm2/m128 */

	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovupd\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.66.0f.WIG 10 /r vmovupd xmm1, xmm2/m128 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovupd\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.66.0f.WIG 10 /r vmovupd ymm1, ymm2/m256 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovupd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W1  10 /r vmovupd xmm1{k1}{z}, xmm2/m128 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vmovupd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.512.66.0f.W1  10 /r vmovupd ymm1{k1}{z}, ymm2/m256 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovupd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W1  10 /r vmovupd zmm1{k1}{z}, zmm2/m512 */
	I(0x10, IF_66|IF_MODRM,                              "movupd\t" OP_RM128_XMM OP_RXMM),       /*              66 0f 10 /r movupd xmm1, xmm2/m128 */

	I(0x11, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovups\t" OP_RXMM OP_RM128_XMM),      /*  VEX.128.0f.WIG 11 /r vmovups xmm2/m128, xmm1 */
	I(0x11, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovups\t" OP_RYMM OP_RM256_YMM),      /*  VEX.256.0f.WIG 11 /r vmovups ymm2/m256, ymm1 */
	I(0x11, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovups\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.0f.W0  11 /r vmovups xmm2/m128{k1}{z}, xmm1 */
	I(0x11, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovups\t" OP_RYMM OP_RM256_YMM_MASK), /* EVEX.256.0f.W0  11 /r vmovups ymm2/m256{k1}{z}, ymm1 */
	I(0x11, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovups\t" OP_RZMM OP_RM512_ZMM_MASK), /* EVEX.512.0f.W0  11 /r vmovups zmm2/m512{k1}{z}, zmm1 */
	I(0x11, IF_MODRM,                              "movups\t" OP_RXMM OP_RM128_XMM),       /*              0f 11 /r movups xmm2/m128, xmm1 */

	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovupd\t" OP_RXMM OP_RM128_XMM),      /*  VEX.128.66.0f.WIG 11 /r vmovupd xmm2/m128, xmm1 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovupd\t" OP_RYMM OP_RM256_YMM),      /*  VEX.256.66.0f.WIG 11 /r vmovupd ymm2/m256, ymm1 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovupd\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.66.0f.W1  11 /r vmovupd xmm2/m128{k1}{z}, xmm1 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vmovupd\t" OP_RYMM OP_RM256_YMM_MASK), /* EVEX.512.66.0f.W1  11 /r vmovupd ymm2/m256{k1}{z}, ymm1 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovupd\t" OP_RZMM OP_RM512_ZMM_MASK), /* EVEX.512.66.0f.W1  11 /r vmovupd zmm2/m512{k1}{z}, zmm1 */
	I(0x11, IF_66|IF_MODRM,                              "movupd\t" OP_RXMM OP_RM128_XMM),       /*              66 0f 11 /r movupd xmm2/m128, xmm1 */

	I(0x12, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovddup\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.f2.0f.WIG 12 /r vmovddup xmm1, xmm2/m64 */
	I(0x12, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovddup\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.f2.0f.WIG 12 /r vmovddup ymm1, ymm2/m256 */
	I(0x12, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovddup\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.f2.0f.W1  12 /r vmovddup xmm1{k1}{z}, xmm2/m64 */
	I(0x12, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vmovddup\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.f2.0f.W1  12 /r vmovddup ymm1{k1}{z}, ymm2/m256 */
	I(0x12, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovddup\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.f2.0f.W1  12 /r vmovddup zmm1{k1}{z}, zmm2/m512 */
	I(0x12, IF_F2|IF_MODRM,                              "movddup\t" OP_RM128_XMM OP_RXMM),       /*              f2 0f 12 /r movddup xmm1, xmm2/m64 */

	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VMOVSLDUP_XMM)), /*  VEX.128.f3.0f.WIG 12 /r vmovsldup xmm1, xmm2/m128 */
	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VMOVSLDUP_YMM)), /*  VEX.256.f3.0f.WIG 12 /r vmovsldup ymm1, ymm2/m256 */
	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVSLDUP_XMM)), /* EVEX.128.f3.0f.W0  12 /r vmovsldup xmm1{k1}{z}, xmm2/m128 */
	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVSLDUP_YMM)), /* EVEX.256.f3.0f.W0  12 /r vmovsldup ymm1{k1}{z}, ymm2/m256 */
	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVSLDUP_ZMM)), /* EVEX.512.f3.0f.W0  12 /r vmovsldup zmm1{k1}{z}, zmm2/m512 */
	I(0x12, IF_F3|IF_MODRM,        "movsldup\t" OP_RM128_XMM OP_RXMM),                     /*              f3 0f 12 /r movsldup xmm1, xmm2/m128 */

	I(0x14, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vunpcklps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 14 /r vunpcklps xmm1, xmm2, xmm3/m128 */
	I(0x14, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vunpcklps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 14 /r vunpcklps ymm1, ymm2, ymm3/m256 */
	I(0x14, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vunpcklps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  14 /r vunpcklps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x14, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vunpcklps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  14 /r vunpcklps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x14, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vunpcklps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  14 /r vunpcklps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x14, IF_MODRM,                              "unpcklps\t" OP_RM128_XMM OP_RXMM),                  /*              0f 14 /r unpcklps xmm1, xmm2/m128 */

	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vunpcklpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 14 /r vunpcklpd xmm1, xmm2, xmm3/m128 */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vunpcklpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 14 /r vunpcklpd ymm1, ymm2, ymm3/m256 */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vunpcklpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  14 /r vunpcklpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vunpcklpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  14 /r vunpcklpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vunpcklpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  14 /r vunpcklpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x14, IF_66|IF_MODRM,                              "unpcklpd\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f 14 /r unpcklpd xmm1, xmm2/m128 */

	I(0x15, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vunpckhps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 15 /r vunpckhps xmm1, xmm2, xmm3/m128 */
	I(0x15, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vunpckhps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 15 /r vunpckhps ymm1, ymm2, ymm3/m256 */
	I(0x15, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vunpckhps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  15 /r vunpckhps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x15, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vunpckhps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  15 /r vunpckhps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x15, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vunpckhps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  15 /r vunpckhps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x15, IF_MODRM,                              "unpckhps\t" OP_RM128_XMM OP_RXMM),                  /*              0f 15 /r unpckhps xmm1, xmm2/m128 */

	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vunpckhpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 15 /r vunpckhpd xmm1, xmm2, xmm3/m128 */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vunpckhpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 15 /r vunpckhpd ymm1, ymm2, ymm3/m256 */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vunpckhpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  15 /r vunpckhpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vunpckhpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  15 /r vunpckhpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vunpckhpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  15 /r vunpckhpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x15, IF_66|IF_MODRM,                              "unpckhpd\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f 15 /r unpckhpd xmm1, xmm2/m128 */

	I(0x16, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VMOVSHDUP_XMM)), /*  VEX.128.f3.0f.WIG 16 /r vmovshdup xmm1, xmm2/m128 */
	I(0x16, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VMOVSHDUP_YMM)), /*  VEX.256.f3.0f.WIG 16 /r vmovshdup ymm1, ymm2/m256 */
	I(0x16, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVSHDUP_XMM)), /* EVEX.128.f3.0f.W0  16 /r vmovshdup xmm1{k1}{z}, xmm2/m128 */
	I(0x16, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVSHDUP_YMM)), /* EVEX.256.f3.0f.W0  16 /r vmovshdup ymm1{k1}{z}, ymm2/m256 */
	I(0x16, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVSHDUP_ZMM)), /* EVEX.512.f3.0f.W0  16 /r vmovshdup zmm1{k1}{z}, zmm2/m512 */
	I(0x16, IF_F3|IF_MODRM,        "movshdup\t" OP_RM128_XMM OP_RXMM),                     /*              f3 0f 16 /r movshdup xmm1, xmm2/m128 */

	I(0x18, IF_MODRM|IF_REG0|IF_RMM, LONGREPR(LO_PREFETCHNTA)),
	I(0x18, IF_MODRM|IF_REG1|IF_RMM, "prefetcht0\t" OP_MEM),
	I(0x18, IF_MODRM|IF_REG2|IF_RMM, "prefetcht1\t" OP_MEM),
	I(0x18, IF_MODRM|IF_REG3|IF_RMM, "prefetcht2\t" OP_MEM),

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

	I(0x1c, IF_MODRM|IF_REG0|IF_RMM, "cldemote\t" OP_MEM),

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

	I(0x28, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovaps\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.0f.WIG 28 /r vmovaps xmm1, xmm2/m128 */
	I(0x28, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovaps\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.0f.WIG 28 /r vmovaps ymm1, ymm2/m256 */
	I(0x28, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovaps\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.0f.W0  28 /r vmovaps xmm1{k1}{z}, xmm2/m128 */
	I(0x28, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovaps\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.0f.W0  28 /r vmovaps ymm1{k1}{z}, ymm2/m256 */
	I(0x28, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovaps\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.0f.W0  28 /r vmovaps zmm1{k1}{z}, zmm2/m512 */
	I(0x28, IF_MODRM,                              "movaps\t" OP_RM128_XMM OP_RXMM),       /*              0f 28 /r movaps xmm1, xmm2/m128 */

	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovapd\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.66.0f.WIG 28 /r vmovapd xmm1, xmm2/m128 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovapd\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.66.0f.WIG 28 /r vmovapd ymm1, ymm2/m256 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovapd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W1  28 /r vmovapd xmm1{k1}{z}, xmm2/m128 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vmovapd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.512.66.0f.W1  28 /r vmovapd ymm1{k1}{z}, ymm2/m256 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovapd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W1  28 /r vmovapd zmm1{k1}{z}, zmm2/m512 */
	I(0x28, IF_66|IF_MODRM,                              "movapd\t" OP_RM128_XMM OP_RXMM),       /*              66 0f 28 /r movapd xmm1, xmm2/m128 */

	I(0x29, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovaps\t" OP_RXMM OP_RM128_XMM),      /*  VEX.128.0f.WIG 29 /r vmovaps xmm2/m128, xmm1 */
	I(0x29, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovaps\t" OP_RYMM OP_RM256_YMM),      /*  VEX.256.0f.WIG 29 /r vmovaps ymm2/m256, ymm1 */
	I(0x29, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovaps\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.0f.W0  29 /r vmovaps xmm2/m128{k1}{z}, xmm1 */
	I(0x29, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovaps\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.0f.W0  29 /r vmovaps ymm2/m256{k1}{z}, ymm1 */
	I(0x29, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovaps\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.0f.W0  29 /r vmovaps zmm2/m512{k1}{z}, zmm1 */
	I(0x29, IF_MODRM,                              "movaps\t" OP_RXMM OP_RM128_XMM),       /*              0f 29 /r movaps xmm2/m128, xmm1 */

	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovapd\t" OP_RXMM OP_RM128_XMM),      /*  VEX.128.66.0f.WIG 29 /r vmovapd xmm2/m128, xmm1 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovapd\t" OP_RYMM OP_RM256_YMM),      /*  VEX.256.66.0f.WIG 29 /r vmovapd ymm2/m256, ymm1 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovapd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W1  29 /r vmovapd xmm2/m128{k1}{z}, xmm1 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vmovapd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.512.66.0f.W1  29 /r vmovapd ymm2/m256{k1}{z}, ymm1 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovapd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W1  29 /r vmovapd zmm2/m512{k1}{z}, zmm1 */
	I(0x29, IF_66|IF_MODRM,                              "movapd\t" OP_RXMM OP_RM128_XMM),       /*              66 0f 29 /r movapd xmm2/m128, xmm1 */

	I(0x2a, IF_MODRM,         "cvtpi2ps\t" OP_RM64_MM OP_RXMM_MASK),

	I(0x2b, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovntps\t" OP_RXMM OP_MEM), /*  VEX.128.0f.WIG 2b /r vmovntps m128, xmm1 */
	I(0x2b, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 1) "vmovntps\t" OP_RYMM OP_MEM), /*  VEX.256.0f.WIG 2b /r vmovntps m256, ymm1 */
	I(0x2b, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovntps\t" OP_RXMM OP_MEM), /* EVEX.128.0f.W0  2b /r vmovntps m128, xmm1 */
	I(0x2b, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vmovntps\t" OP_RYMM OP_MEM), /* EVEX.256.0f.W0  2b /r vmovntps m256, ymm1 */
	I(0x2b, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 2) "vmovntps\t" OP_RZMM OP_MEM), /* EVEX.512.0f.W0  2b /r vmovntps m512, zmm1 */
	I(0x2b, IF_MODRM|IF_RMM,                              "movntps\t" OP_RXMM OP_MEM),  /*              0f 2b /r movntps m128, xmm1 */

	I(0x2c, IF_66|IF_MODRM,   "cvttpd2pi\t" OP_RM128_XMM OP_RMM),
	I(0x2c, IF_MODRM,         "cvttps2pi\t" OP_RM128_XMM OP_RMM),

	I(0x2d, IF_66|IF_MODRM,   "cvtpd2pi\t" OP_RM128_XMM OP_RMM),
	I(0x2d, IF_MODRM,         "cvtps2pi\t" OP_RM128_XMM OP_RMM),

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

	I(0x41, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 0, 1) "kandw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 41 /r kandw k1, k2, k3 */
	I(0x41, IF_VEX|IF_66|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "kandb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 41 /r kandb k1, k2, k3 */
	I(0x41, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 1, 1) "kandq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 41 /r kandq k1, k2, k3 */
	I(0x41, IF_VEX|IF_66|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "kandd\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 41 /r kandd k1, k2, k3 */

	I(0x41, IF_66|IF_MODRM,   "cmov" NAME_jc1 "w\t" OP_RM16 OP_R16),
	I(0x41, IF_MODRM,         "cmov" NAME_jc1 "l\t" OP_RM32 OP_R32),
	I(0x41, IF_66|IF_MODRM,   "cmov" NAME_jc1 "q\t" OP_RM64 OP_R64),

	I(0x42, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 0, 1) "kandnw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 42 /r kandnw k1, k2, k3 */
	I(0x42, IF_VEX|IF_66|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "kandnb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 42 /r kandnb k1, k2, k3 */
	I(0x42, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 1, 1) "kandnq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 42 /r kandnq k1, k2, k3 */
	I(0x42, IF_VEX|IF_66|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "kandnd\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 42 /r kandnd k1, k2, k3 */

	I(0x42, IF_66|IF_MODRM,   "cmov" NAME_jc2 "w\t" OP_RM16 OP_R16),
	I(0x42, IF_MODRM,         "cmov" NAME_jc2 "l\t" OP_RM32 OP_R32),
	I(0x42, IF_66|IF_MODRM,   "cmov" NAME_jc2 "q\t" OP_RM64 OP_R64),

	I(0x43, IF_66|IF_MODRM,   "cmov" NAME_jc3 "w\t" OP_RM16 OP_R16),
	I(0x43, IF_MODRM,         "cmov" NAME_jc3 "l\t" OP_RM32 OP_R32),
	I(0x43, IF_66|IF_MODRM,   "cmov" NAME_jc3 "q\t" OP_RM64 OP_R64),

	I(0x44, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "knotb\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W0 44 /r knotb k1, k2 */
	I(0x44, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 0) "knotw\t" OP_RMK OP_RK), /* VEX.L0.   0f.W0 44 /r knotw k1, k2 */
	I(0x44, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "knotd\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W1 44 /r knotd k1, k2 */
	I(0x44, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 0) "knotq\t" OP_RMK OP_RK), /* VEX.L0.   0f.W1 44 /r knotq k1, k2 */

	I(0x44, IF_66|IF_MODRM,   "cmov" NAME_jc4 "w\t" OP_RM16 OP_R16),
	I(0x44, IF_MODRM,         "cmov" NAME_jc4 "l\t" OP_RM32 OP_R32),
	I(0x44, IF_66|IF_MODRM,   "cmov" NAME_jc4 "q\t" OP_RM64 OP_R64),

	I(0x45, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "korb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 45 /r korb k1, k2, k3 */
	I(0x45, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 1) "korw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 45 /r korw k1, k2, k3 */
	I(0x45, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "kord\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 45 /r kord k1, k2, k3 */
	I(0x45, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 1) "korq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 45 /r korq k1, k2, k3 */

	I(0x45, IF_66|IF_MODRM,   "cmov" NAME_jc5 "w\t" OP_RM16 OP_R16),
	I(0x45, IF_MODRM,         "cmov" NAME_jc5 "l\t" OP_RM32 OP_R32),
	I(0x45, IF_66|IF_MODRM,   "cmov" NAME_jc5 "q\t" OP_RM64 OP_R64),

	I(0x46, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "kxnorb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 46 /r kxnorb k1, k2, k3 */
	I(0x46, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 1) "kxnorw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 46 /r kxnorw k1, k2, k3 */
	I(0x46, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "kxnord\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 46 /r kxnord k1, k2, k3 */
	I(0x46, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 1) "kxnorq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 46 /r kxnorq k1, k2, k3 */

	I(0x46, IF_66|IF_MODRM,   "cmov" NAME_jc6 "w\t" OP_RM16 OP_R16),
	I(0x46, IF_MODRM,         "cmov" NAME_jc6 "l\t" OP_RM32 OP_R32),
	I(0x46, IF_66|IF_MODRM,   "cmov" NAME_jc6 "q\t" OP_RM64 OP_R64),

	I(0x47, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "kxorb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 47 /r kxorb k1, k2, k3 */
	I(0x47, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 1) "kxorw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 47 /r kxorw k1, k2, k3 */
	I(0x47, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "kxord\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 47 /r kxord k1, k2, k3 */
	I(0x47, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 1) "kxorq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 47 /r kxorq k1, k2, k3 */

	I(0x47, IF_66|IF_MODRM,   "cmov" NAME_jc7 "w\t" OP_RM16 OP_R16),
	I(0x47, IF_MODRM,         "cmov" NAME_jc7 "l\t" OP_RM32 OP_R32),
	I(0x47, IF_66|IF_MODRM,   "cmov" NAME_jc7 "q\t" OP_RM64 OP_R64),

	I(0x48, IF_66|IF_MODRM,   "cmov" NAME_jc8 "w\t" OP_RM16 OP_R16),
	I(0x48, IF_MODRM,         "cmov" NAME_jc8 "l\t" OP_RM32 OP_R32),
	I(0x48, IF_66|IF_MODRM,   "cmov" NAME_jc8 "q\t" OP_RM64 OP_R64),

	I(0x49, IF_66|IF_MODRM,   "cmov" NAME_jc9 "w\t" OP_RM16 OP_R16),
	I(0x49, IF_MODRM,         "cmov" NAME_jc9 "l\t" OP_RM32 OP_R32),
	I(0x49, IF_66|IF_MODRM,   "cmov" NAME_jc9 "q\t" OP_RM64 OP_R64),

	I(0x4a, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 0, 1) "kaddw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 4a /r kaddw k1, k2, k3 */
	I(0x4a, IF_VEX|IF_66|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "kaddb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 4a /r kaddb k1, k2, k3 */
	I(0x4a, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 1, 1) "kaddq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 4a /r kaddq k1, k2, k3 */
	I(0x4a, IF_VEX|IF_66|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "kaddd\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 4a /r kaddd k1, k2, k3 */

	I(0x4a, IF_66|IF_MODRM,   "cmov" NAME_jca "w\t" OP_RM16 OP_R16),
	I(0x4a, IF_MODRM,         "cmov" NAME_jca "l\t" OP_RM32 OP_R32),
	I(0x4a, IF_66|IF_MODRM,   "cmov" NAME_jca "q\t" OP_RM64 OP_R64),

	I(0x4b, IF_VEX|IF_66|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_KUNPCKBW)), /* VEX.L1.66.0f.W0 4b /r kunpckbw k1, k2, k3 */
	I(0x4b, IF_VEX|IF_MODRM,       LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_KUNPCKWD)), /* VEX.L1.   0f.W0 4b /r kunpckwd k1, k2, k3 */
	I(0x4b, IF_VEX|IF_MODRM,       LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_KUNPCKDQ)), /* VEX.L1.   0f.W1 4b /r kunpckdq k1, k2, k3 */

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

	I(0x52, IF_VEX|IF_MODRM,       OP_VEX_B0(1, 1, 0, 0)  "vrsqrtps\t" OP_RM128_XMM OP_RXMM),            /*    VEX.128.0f.WIG 52 /r vrsqrtps xmm1, xmm2/m128 */
	I(0x52, IF_VEX|IF_MODRM,       OP_VEX_B0(1, 1, 0, 1)  "vrsqrtps\t" OP_RM256_YMM OP_RYMM),            /*    VEX.256.0f.WIG 52 /r vrsqrtps ymm1, ymm2/m256 */
	I(0x52, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 1, 0) "vrsqrtss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.LIG.f3.0f.WIG 52 /r vrsqrtss xmm1, xmm2, xmm3/m32 */
	I(0x52, IF_MODRM,                                     "rsqrtps\t" OP_RM128_XMM OP_RXMM),             /*                0f 52 /r rsqrtps xmm1, xmm2/m128 */
	I(0x52, IF_F3|IF_MODRM,                               "rsqrtss\t" OP_RM128_XMM OP_RXMM),             /*             f3 0f 52 /r rsqrtss xmm1, xmm2/m32 */

	I(0x53, IF_VEX|IF_MODRM,       OP_VEX_B0(1, 1, 0, 0)  "vrcpps\t" OP_RM128_XMM OP_RXMM),            /*    VEX.128.0f.WIG 53 /r vrcpps xmm1, xmm2/m128 */
	I(0x53, IF_VEX|IF_MODRM,       OP_VEX_B0(1, 1, 0, 1)  "vrcpps\t" OP_RM256_YMM OP_RYMM),            /*    VEX.256.0f.WIG 53 /r vrcpps ymm1, ymm2/m256 */
	I(0x53, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 1, 0) "vrcpss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.LIG.f3.0f.WIG 53 /r vrcpss xmm1, xmm2, xmm3/m32 */
	I(0x53, IF_MODRM,                                     "rcpps\t" OP_RM128_XMM OP_RXMM),             /*                0f 53 /r rcpps xmm1, xmm2/m128 */
	I(0x53, IF_F3|IF_MODRM,                               "rcpss\t" OP_RM128_XMM OP_RXMM),             /*             f3 0f 53 /r rcpss xmm1, xmm2/m32 */

	I(0x54, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vandps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 54 /r vandps xmm1, xmm2, xmm3/m128 */
	I(0x54, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vandps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 54 /r vandps ymm1, ymm2, ymm3/m256 */
	I(0x54, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vandps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  54 /r vandps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x54, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vandps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  54 /r vandps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x54, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vandps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  54 /r vandps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x54, IF_MODRM,                              "andps\t" OP_RM128_XMM OP_RXMM),                  /*              0f 54 /r andps xmm1, xmm2/m128 */

	I(0x54, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vandpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 54 /r vandpd xmm1, xmm2, xmm3/m128 */
	I(0x54, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vandpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 54 /r vandpd ymm1, ymm2, ymm3/m256 */
	I(0x54, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vandpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  54 /r vandpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x54, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vandpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  54 /r vandpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x54, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vandpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  54 /r vandpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x54, IF_66|IF_MODRM,                              "andpd\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f  54 /r andpd xmm1, xmm2/m128 */

	I(0x55, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vandnps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 55 /r vandnps xmm1, xmm2, xmm3/m128 */
	I(0x55, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vandnps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 55 /r vandnps ymm1, ymm2, ymm3/m256 */
	I(0x55, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vandnps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  55 /r vandnps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x55, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vandnps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  55 /r vandnps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x55, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vandnps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  55 /r vandnps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x55, IF_MODRM,                              "andnps\t" OP_RM128_XMM OP_RXMM),                  /*              0f 55 /r andnps xmm1, xmm2/m128 */

	I(0x55, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vandnpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 55 /r vandnpd xmm1, xmm2, xmm3/m128 */
	I(0x55, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vandnpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 55 /r vandnpd ymm1, ymm2, ymm3/m256 */
	I(0x55, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vandnpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  55 /r vandnpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x55, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vandnpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  55 /r vandnpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x55, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vandnpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  55 /r vandnpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x55, IF_66|IF_MODRM,                              "andnpd\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f  55 /r andnpd xmm1, xmm2/m128 */

	I(0x56, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vorps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 56 /r vorps xmm1, xmm2, xmm3/m128 */
	I(0x56, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vorps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 56 /r vorps ymm1, ymm2, ymm3/m256 */
	I(0x56, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vorps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  56 /r vorps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x56, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vorps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  56 /r vorps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x56, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vorps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  56 /r vorps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x56, IF_MODRM,                              "orps\t" OP_RM128_XMM OP_RXMM),                  /*              0f 56 /r orps xmm1, xmm2/m128 */

	I(0x56, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vorpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 56 /r vorpd xmm1, xmm2, xmm3/m128 */
	I(0x56, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vorpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 56 /r vorpd ymm1, ymm2, ymm3/m256 */
	I(0x56, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vorpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  56 /r vorpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x56, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vorpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  56 /r vorpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x56, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vorpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  56 /r vorpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x56, IF_66|IF_MODRM,                              "orpd\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f 56 /r orpd xmm1, xmm2/m128 */

	I(0x57, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vxorps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 57 /r vxorps xmm1, xmm2, xmm3/m128 */
	I(0x57, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vxorps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 57 /r vxorps ymm1, ymm2, ymm3/m256 */
	I(0x57, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vxorps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  57 /r vxorps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x57, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vxorps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  57 /r vxorps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x57, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vxorps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  57 /r vxorps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x57, IF_MODRM,                              "xorps\t" OP_RM128_XMM OP_RXMM),                  /*              0f 57 /r xorps xmm1, xmm2/m128 */

	I(0x57, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vxorpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 57 /r vxorpd xmm1, xmm2, xmm3/m128 */
	I(0x57, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vxorpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 57 /r vxorpd ymm1, ymm2, ymm3/m256 */
	I(0x57, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vxorpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  57 /r vxorpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x57, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vxorpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  57 /r vxorpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x57, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vxorpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  57 /r vxorpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x57, IF_66|IF_MODRM,                              "xorpd\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f 57 /r xorpd xmm1, xmm2/m128 */

	I(0x60, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPUNPCKLBW_XMM)), /* EVEX.128.66.0f.WIG 60 /r vpunpcklbw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x60, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPUNPCKLBW_YMM)), /* EVEX.256.66.0f.WIG 60 /r vpunpcklbw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x60, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPUNPCKLBW_ZMM)), /* EVEX.512.66.0f.WIG 60 /r vpunpcklbw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x60, IF_MODRM,              "punpcklbw\t" OP_RM64_MM OP_RMM),                        /*                 0f 60 /r punpcklbw mm, mm/m32 */
	I(0x60, IF_66|IF_MODRM,        "punpcklbw\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 60 /r punpcklbw xmm1, xmm2/m128 */

	I(0x61, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPUNPCKLWD_XMM)), /* EVEX.128.66.0f.WIG 61 /r vpunpcklwd xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x61, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPUNPCKLWD_YMM)), /* EVEX.256.66.0f.WIG 61 /r vpunpcklwd ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x61, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPUNPCKLWD_ZMM)), /* EVEX.512.66.0f.WIG 61 /r vpunpcklwd zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x61, IF_MODRM,              "punpcklwd\t" OP_RM64_MM OP_RMM),                        /*                 0f 61 /r punpcklwd mm, mm/m32 */
	I(0x61, IF_66|IF_MODRM,        "punpcklwd\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 61 /r punpcklwd xmm1, xmm2/m128 */

	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPUNPCKLDQ_XMM)), /*  VEX.128.66.0f.WIG 62 /r vpunpckldq xmm1, xmm2, xmm3/m128 */
	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPUNPCKLDQ_YMM)), /*  VEX.256.66.0f.WIG 62 /r vpunpckldq ymm1, ymm2, ymm3/m256 */
	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPUNPCKLDQ_XMM)), /* EVEX.128.66.0f.W0  62 /r vpunpckldq xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPUNPCKLDQ_YMM)), /* EVEX.256.66.0f.W0  62 /r vpunpckldq ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPUNPCKLDQ_ZMM)), /* EVEX.512.66.0f.W0  62 /r vpunpckldq zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x62, IF_MODRM,              "punpckldq\t" OP_RM64_MM OP_RMM),                        /*                 0f 62 /r punpckldq mm, mm/m32 */
	I(0x62, IF_66|IF_MODRM,        "punpckldq\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 62 /r punpckldq xmm1, xmm2/m128 */

	I(0x63, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpacksswb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F.WIG 63 /r vpacksswb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x63, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpacksswb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F.WIG 63 /r vpacksswb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x63, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpacksswb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F.WIG 63 /r vpacksswb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x63, IF_MODRM,              "packsswb\t" OP_RM64_MM OP_RMM),                                           /*                 0F 63 /r packsswb mm1, mm2/m64 */
	I(0x63, IF_66|IF_MODRM,        "packsswb\t" OP_RM128_XMM OP_RXMM_MASK),                                   /*              66 0F 63 /r packsswb xmm1, xmm2/m128 */

	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpcmpgtb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpcmpgtb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpcmpgtb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x64, IF_MODRM,              "pcmpgtb\t" OP_RMM OP_RM64_MM),
	I(0x64, IF_66|IF_MODRM,        "pcmpgtb\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpcmpgtw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpcmpgtw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpcmpgtw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x65, IF_MODRM,              "pcmpgtw\t" OP_RMM OP_RM64_MM),
	I(0x65, IF_66|IF_MODRM,        "pcmpgtw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpcmpgtd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcmpgtd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpcmpgtd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcmpgtd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcmpgtd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x66, IF_MODRM,              "pcmpgtd\t" OP_RMM OP_RM64_MM),
	I(0x66, IF_66|IF_MODRM,        "pcmpgtd\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x67, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpackuswb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x67, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpackuswb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x67, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpackuswb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x67, IF_MODRM,              "packuswb\t" OP_RM64_MM OP_RMM),
	I(0x67, IF_66|IF_MODRM,        "packuswb\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x68, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPUNPCKHBW_XMM)), /* EVEX.128.66.0f.WIG 68 /r vpunpckhbw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x68, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPUNPCKHBW_YMM)), /* EVEX.256.66.0f.WIG 68 /r vpunpckhbw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x68, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPUNPCKHBW_ZMM)), /* EVEX.512.66.0f.WIG 68 /r vpunpckhbw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x68, IF_MODRM,              "punpckhbw\t" OP_RM64_MM OP_RMM),                        /*                 0f 68 /r punpckhbw mm, mm/m64 */
	I(0x68, IF_66|IF_MODRM,        "punpckhbw\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 68 /r punpckhbw xmm1, xmm2/m128 */

	I(0x69, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPUNPCKHWD_XMM)), /* EVEX.128.66.0f.WIG 69 /r vpunpckhwd xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x69, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPUNPCKHWD_YMM)), /* EVEX.256.66.0f.WIG 69 /r vpunpckhwd ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x69, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPUNPCKHWD_ZMM)), /* EVEX.512.66.0f.WIG 69 /r vpunpckhwd zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x69, IF_MODRM,              "punpckhwd\t" OP_RM64_MM OP_RMM),                        /*                 0f 69 /r punpckhwd mm, mm/m64 */
	I(0x69, IF_66|IF_MODRM,        "punpckhwd\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 69 /r punpckhwd xmm1, xmm2/m128 */

	I(0x6a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPUNPCKHDQ_XMM)), /*  VEX.128.66.0f.WIG 6a /r vpunpckhdq xmm1, xmm2, xmm3/m128 */
	I(0x6a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPUNPCKHDQ_YMM)), /*  VEX.256.66.0f.WIG 6a /r vpunpckhdq ymm1, ymm2, ymm3/m256 */
	I(0x6a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPUNPCKHDQ_XMM)), /* EVEX.128.66.0f.W0  6a /r vpunpckhdq xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x6a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPUNPCKHDQ_YMM)), /* EVEX.256.66.0f.W0  6a /r vpunpckhdq ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x6a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPUNPCKHDQ_ZMM)), /* EVEX.512.66.0f.W0  6a /r vpunpckhdq zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x6a, IF_MODRM,              "punpckhdq\t" OP_RM64_MM OP_RMM),                        /*                 0f 6a /r punpckhdq mm, mm/m64 */
	I(0x6a, IF_66|IF_MODRM,        "punpckhdq\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 6a /r punpckhdq xmm1, xmm2/m128 */

	I(0x6b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpackssdw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x6b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpackssdw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x6b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpackssdw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x6b, IF_MODRM,              "packssdw\t" OP_RM64_MM OP_RMM),
	I(0x6b, IF_66|IF_MODRM,        "packssdw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x6c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPUNPCKLQDQ_XMM)), /*  VEX.128.66.0f.WIG 6c /r vpunpcklqdq xmm1, xmm2, xmm3/m128 */
	I(0x6c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPUNPCKLQDQ_YMM)), /*  VEX.256.66.0f.WIG 6c /r vpunpcklqdq ymm1, ymm2, ymm3/m256 */
	I(0x6c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPUNPCKLQDQ_XMM)), /* EVEX.128.66.0f.W1  6c /r vpunpcklqdq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x6c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPUNPCKLQDQ_YMM)), /* EVEX.512.66.0f.W1  6c /r vpunpcklqdq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x6c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPUNPCKLQDQ_ZMM)), /* EVEX.512.66.0f.W1  6c /r vpunpcklqdq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x6c, IF_66|IF_MODRM,        LONGREPR(LO_PUNPCKLQDQ_XMM)),                             /*              66 0f 6c /r punpcklqdq xmm1, xmm2/m128 */

	I(0x6d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPUNPCKHQDQ_XMM)), /*  VEX.128.66.0f.WIG 6d /r vpunpckhqdq xmm1, xmm2, xmm3/m128 */
	I(0x6d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPUNPCKHQDQ_YMM)), /*  VEX.256.66.0f.WIG 6d /r vpunpckhqdq ymm1, ymm2, ymm3/m256 */
	I(0x6d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPUNPCKHQDQ_XMM)), /* EVEX.128.66.0f.W1  6d /r vpunpckhqdq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x6d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPUNPCKHQDQ_YMM)), /* EVEX.512.66.0f.W1  6d /r vpunpckhqdq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x6d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPUNPCKHQDQ_ZMM)), /* EVEX.512.66.0f.W1  6d /r vpunpckhqdq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x6d, IF_66|IF_MODRM,        LONGREPR(LO_PUNPCKHQDQ_XMM)),                             /*              66 0f 6d /r punpckhqdq xmm1, xmm2/m128 */

	I(0x6e, IF_VEXW0|IF_66|IF_MODRM,"vmovd\t" OP_RM32 OP_RXMM_MASK),
	I(0x6e, IF_VEXW1|IF_66|IF_MODRM,"vmovq\t" OP_RM64 OP_RXMM_MASK),
	I(0x6e, IF_MODRM,               "movd\t" OP_RM32 OP_RMM),
	I(0x6e, IF_REXW|IF_MODRM,       "movq\t" OP_RM64 OP_RMM),
	I(0x6e, IF_66|IF_MODRM,         "movd\t" OP_RM32 OP_RXMM_MASK),
	I(0x6e, IF_REXW|IF_66|IF_MODRM, "movq\t" OP_RM64 OP_RXMM_MASK),

	I(0x6f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovdqa\t" OP_RM128_XMM OP_RXMM), /*  VEX.128.66.0f.WIG 6f /r vmovdqa xmm1, xmm2/m128 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovdqa\t" OP_RM256_YMM OP_RYMM), /*  VEX.256.66.0f.WIG 6f /r vmovdqa ymm1, ymm2/m256 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVDQA32_XMM)),  /* EVEX.128.66.0f.W0  6f /r vmovdqa32 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVDQA32_YMM)),  /* EVEX.256.66.0f.W0  6f /r vmovdqa32 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVDQA32_ZMM)),  /* EVEX.512.66.0f.W0  6f /r vmovdqa32 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQA64_XMM)),  /* EVEX.128.66.0f.W1  6f /r vmovdqa64 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQA64_YMM)),  /* EVEX.512.66.0f.W1  6f /r vmovdqa64 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQA64_ZMM)),  /* EVEX.512.66.0f.W1  6f /r vmovdqa64 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_66|IF_MODRM,        "movdqa\t" OP_RM128_XMM OP_RXMM),                        /*              66 0f 6f /r movdqa xmm1, xmm2/m128 */

	I(0x6f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovdqu\t" OP_RM128_XMM OP_RXMM),       /*  VEX.128.f3.0f.WIG 6f /r vmovdqu xmm1, xmm2/m128 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovdqu\t" OP_RM256_YMM OP_RYMM),       /*  VEX.256.f3.0f.WIG 6f /r vmovdqu ymm1, ymm2/m256 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovdqu8\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.f2.0f.W0  6f /r vmovdqu8 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovdqu8\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.f2.0f.W0  6f /r vmovdqu8 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovdqu8\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.f2.0f.W0  6f /r vmovdqu8 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQU16_XMM)),        /* EVEX.128.f2.0f.W1  6f /r vmovdqu16 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQU16_YMM)),        /* EVEX.256.f2.0f.W1  6f /r vmovdqu16 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQU16_ZMM)),        /* EVEX.512.f2.0f.W1  6f /r vmovdqu16 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVDQU32_XMM)),        /* EVEX.128.f3.0f.W0  6f /r vmovdqu32 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVDQU32_YMM)),        /* EVEX.256.f3.0f.W0  6f /r vmovdqu32 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVDQU32_ZMM)),        /* EVEX.512.f3.0f.W0  6f /r vmovdqu32 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQU64_XMM)),        /* EVEX.128.f3.0f.W1  6f /r vmovdqu64 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQU64_YMM)),        /* EVEX.256.f3.0f.W1  6f /r vmovdqu64 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQU64_ZMM)),        /* EVEX.512.f3.0f.W1  6f /r vmovdqu64 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_F3|IF_MODRM,        "movdqu\t" OP_RM128_XMM OP_RXMM),                              /*              f3 0f 6f /r movdqu xmm1, xmm2/m128 */

	I(0x70, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpshufd\t" OP_U8 OP_RM128_XMM OP_RXMM),      /*  VEX.128.66.0f.WIG 70 /r ib vpshufd xmm1, xmm2/m128, imm8 */
	I(0x70, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpshufd\t" OP_U8 OP_RM256_YMM OP_RYMM),      /*  VEX.256.66.0f.WIG 70 /r ib vpshufd ymm1, ymm2/m256, imm8 */
	I(0x70, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpshufd\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W0  70 /r ib vpshufd xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x70, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpshufd\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f.W0  70 /r ib vpshufd ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x70, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpshufd\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W0  70 /r ib vpshufd zmm1{k1}{z}, zmm2/m512/m32bcst, imm8 */
	I(0x70, IF_66|IF_MODRM,                              "pshufd\t" OP_U8 OP_RM128_XMM OP_RXMM),       /*              66 0f 70 /r ib pshufd xmm1, xmm2/m128, imm8 */

	I(0x70, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPSHUFHW_XMM)), /* EVEX.128.f3.0f.WIG 70 /r ib vpshufhw xmm1{k1}{z}, xmm2/m128, imm8 */
	I(0x70, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPSHUFHW_YMM)), /* EVEX.256.f3.0f.WIG 70 /r ib vpshufhw ymm1{k1}{z}, ymm2/m256, imm8 */
	I(0x70, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPSHUFHW_ZMM)), /* EVEX.512.f3.0f.WIG 70 /r ib vpshufhw zmm1{k1}{z}, zmm2/m512, imm8 */
	I(0x70, IF_F3|IF_MODRM,        "pshufhw\t" OP_U8 OP_RM128_XMM OP_RXMM),               /*              f3 0f 70 /r ib pshufhw xmm1, xmm2/m128, imm8 */

	I(0x70, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPSHUFLW_XMM)), /* EVEX.128.f2.0f.WIG 70 /r ib vpshuflw xmm1{k1}{z}, xmm2/m128, imm8 */
	I(0x70, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPSHUFLW_YMM)), /* EVEX.256.f2.0f.WIG 70 /r ib vpshuflw ymm1{k1}{z}, ymm2/m256, imm8 */
	I(0x70, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPSHUFLW_ZMM)), /* EVEX.512.f2.0f.WIG 70 /r ib vpshuflw zmm1{k1}{z}, zmm2/m512, imm8 */
	I(0x70, IF_F2|IF_MODRM,        "pshuflw\t" OP_U8 OP_RM128_XMM OP_RXMM),               /*              f2 0f 70 /r ib pshuflw xmm1, xmm2/m128, imm8 */

	I(0x70, IF_MODRM, "pshufw\t" OP_U8 OP_RM64_MM OP_RMM),

	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 1, 0, 0) "vpsrlw\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.WIG 71 /2 ib vpsrlw xmm1{k1}{z}, xmm2/m128, imm8 */
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 1, 0, 1) "vpsrlw\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.256.66.0f.WIG 71 /2 ib vpsrlw ymm1{k1}{z}, ymm2/m256, imm8 */
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 1, 0, 2) "vpsrlw\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.WIG 71 /2 ib vpsrlw zmm1{k1}{z}, zmm2/m512, imm8 */
	I(0x71, IF_MODRM|IF_REG2,                                    "psrlw\t" OP_U8 OP_RM64_MM),                  /*                 0f 71 /2 ib psrlw mm, imm8 */
	I(0x71, IF_66|IF_MODRM|IF_REG2,                              "psrlw\t" OP_U8 OP_RM128_XMM),                /*              66 0f 71 /2 ib psrlw xmm1, imm8 */

	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 1, 0, 0) "vpsraw\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.WIG 71 /4 ib vpsraw xmm1{k1}{z}, xmm2/m128, imm8 */
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 1, 0, 1) "vpsraw\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.256.66.0f.WIG 71 /4 ib vpsraw ymm1{k1}{z}, ymm2/m256, imm8 */
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 1, 0, 2) "vpsraw\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.WIG 71 /4 ib vpsraw zmm1{k1}{z}, zmm2/m512, imm8 */
	I(0x71, IF_MODRM|IF_REG4,                                    "psraw\t" OP_U8 OP_RM64_MM),                  /*                 0f 71 /4 ib psraw mm, imm8 */
	I(0x71, IF_66|IF_MODRM|IF_REG4,                              "psraw\t" OP_U8 OP_RM128_XMM),                /*              66 0f 71 /4 ib psraw xmm1, imm8 */

	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 1, 0, 0) "vpsllw\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK),
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 1, 0, 1) "vpsllw\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK),
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 1, 0, 2) "vpsllw\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK),
	I(0x71, IF_MODRM|IF_RMR|IF_REG6,       "psllw\t" OP_U8 OP_RM64_MM),
	I(0x71, IF_66|IF_MODRM|IF_RMR|IF_REG6, "psllw\t" OP_U8 OP_RM128_XMM),

	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(1, 1, 0, 0) "vpsrld\t" OP_U8 OP_RM128_XMM OP_VRXMM),      /*  VEX.128.66.0f.WIG 72 /2 ib vpsrld xmm1, xmm2, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(1, 1, 0, 1) "vpsrld\t" OP_U8 OP_RM256_YMM OP_VRYMM),      /*  VEX.256.66.0f.WIG 72 /2 ib vpsrld ymm1, ymm2, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 0, 0) "vpsrld\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.W0  72 /2 ib vpsrld xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 0, 1) "vpsrld\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.256.66.0f.W0  72 /2 ib vpsrld ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 0, 2) "vpsrld\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.W0  72 /2 ib vpsrld zmm1{k1}{z}, zmm2/m512/m32bcst, imm8 */
	I(0x72, IF_MODRM|IF_REG2,                                    "psrld\t" OP_U8 OP_RM64_MM),                  /*                 0f 72 /2 ib psrld mm, imm8 */
	I(0x72, IF_66|IF_MODRM|IF_REG2,                              "psrld\t" OP_U8 OP_RM128_XMM),                /*              66 0f 72 /2 ib psrld xmm1, imm8 */

	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(1, 1, 0, 0) "vpsrad\t" OP_U8 OP_RM128_XMM OP_VRXMM),      /*  VEX.128.66.0f.WIG 72 /4 ib vpsrad xmm1, xmm2, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(1, 1, 0, 1) "vpsrad\t" OP_U8 OP_RM256_YMM OP_VRYMM),      /*  VEX.256.66.0f.WIG 72 /4 ib vpsrad ymm1, ymm2, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 0, 0) "vpsrad\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.W0  72 /4 ib vpsrad xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 0, 1) "vpsrad\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.256.66.0f.W0  72 /4 ib vpsrad ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 0, 2) "vpsrad\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.W0  72 /4 ib vpsrad zmm1{k1}{z}, zmm2/m512/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 1, 0) "vpsraq\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.W1  72 /4 ib vpsraq xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 1, 1) "vpsraq\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.512.66.0f.W1  72 /4 ib vpsraq ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 1, 2) "vpsraq\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.W1  72 /4 ib vpsraq zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */
	I(0x72, IF_MODRM|IF_REG4,                                    "psrad\t" OP_U8 OP_RM64_MM),                  /*                 0f 72 /4 ib psrad mm, imm8 */
	I(0x72, IF_66|IF_MODRM|IF_REG4,                              "psrad\t" OP_U8 OP_RM128_XMM),                /*              66 0f 72 /4 ib psrad xmm1, imm8 */

	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_RMM|IF_REG6, OP_VEX_B0(1, 1, 0, 0) "vpslld\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK),
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_RMM|IF_REG6, OP_VEX_B0(1, 1, 0, 1) "vpslld\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK),
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 0, 0) "vpslld\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK),
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 0, 1) "vpslld\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK),
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 0, 2) "vpslld\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK),
	I(0x72, IF_MODRM|IF_RMR|IF_REG6,       "pslld\t" OP_U8 OP_RM64_MM),
	I(0x72, IF_66|IF_MODRM|IF_RMR|IF_REG6, "pslld\t" OP_U8 OP_RM128_XMM),

	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(1, 1, 0, 0) "vpsrlq\t" OP_U8 OP_RM128_XMM OP_VRXMM),      /*  VEX.128.66.0f.WIG 73 /2 ib vpsrlq xmm1, xmm2, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(1, 1, 0, 1) "vpsrlq\t" OP_U8 OP_RM256_YMM OP_VRYMM),      /*  VEX.256.66.0f.WIG 73 /2 ib vpsrlq ymm1, ymm2, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 1, 0) "vpsrlq\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.W1  73 /2 ib vpsrlq xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 1, 1) "vpsrlq\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.512.66.0f.W1  73 /2 ib vpsrlq ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 1, 2) "vpsrlq\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.W1  73 /2 ib vpsrlq zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */
	I(0x73, IF_MODRM|IF_REG2,                                    "psrlq\t" OP_U8 OP_RM64_MM),                  /*                 0f 73 /2 ib psrlq mm, imm8 */
	I(0x73, IF_66|IF_MODRM|IF_REG2,                              "psrlq\t" OP_U8 OP_RM128_XMM),                /*              66 0f 73 /2 ib psrlq xmm1, imm8 */

	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG3, OP_VEX_B0(0, 1, 0, 0) "vpsrldq\t" OP_U8 OP_RM128_XMM OP_VRXMM), /* EVEX.128.66.0f.WIG 73 /3 ib vpsrldq xmm1, xmm2/m128, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG3, OP_VEX_B0(0, 1, 0, 1) "vpsrldq\t" OP_U8 OP_RM256_YMM OP_VRYMM), /* EVEX.256.66.0f.WIG 73 /3 ib vpsrldq ymm1, ymm2/m256, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG3, OP_VEX_B0(0, 1, 0, 2) "vpsrldq\t" OP_U8 OP_RM512_ZMM OP_VRZMM), /* EVEX.512.66.0f.WIG 73 /3 ib vpsrldq zmm1, zmm2/m512, imm8 */
	I(0x73, IF_66|IF_MODRM|IF_REG3,                              "psrldq\t" OP_U8 OP_RM128_XMM),           /*              66 0f 73 /3 ib psrldq xmm1, imm8 */

	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(1, 1, 0, 0) "vpsllq\t" OP_U8 OP_RM128_XMM OP_VRXMM),      /*  VEX.128.66.0f.WIG 73 /6 ib vpsllq xmm1, xmm2, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(1, 1, 0, 1) "vpsllq\t" OP_U8 OP_RM256_YMM OP_VRYMM),      /*  VEX.256.66.0f.WIG 73 /6 ib vpsllq ymm1, ymm2, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 1, 0) "vpsllq\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.W1  73 /6 ib vpsllq xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 1, 1) "vpsllq\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.512.66.0f.W1  73 /6 ib vpsllq ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 1, 2) "vpsllq\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.W1  73 /6 ib vpsllq zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */
	I(0x73, IF_MODRM|IF_REG6,                                    "psllq\t" OP_U8 OP_RM64_MM),                  /*                 0f 73 /6 ib psllq mm, imm8 */
	I(0x73, IF_66|IF_MODRM|IF_REG6,                              "psllq\t" OP_U8 OP_RM128_XMM),                /*              66 0f 73 /6 ib psllq xmm1, imm8 */

	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG7, OP_VEX_B0(0, 1, 0, 0) "vpslldq\t" OP_U8 OP_RM128_XMM OP_VRXMM), /* EVEX.128.66.0f.WIG 73 /7 ib vpslldq xmm1, xmm2/m128, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG7, OP_VEX_B0(0, 1, 0, 1) "vpslldq\t" OP_U8 OP_RM256_YMM OP_VRYMM), /* EVEX.256.66.0f.WIG 73 /7 ib vpslldq ymm1, ymm2/m256, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG7, OP_VEX_B0(0, 1, 0, 2) "vpslldq\t" OP_U8 OP_RM512_ZMM OP_VRZMM), /* EVEX.512.66.0f.WIG 73 /7 ib vpslldq zmm1, zmm2/m512, imm8 */
	I(0x73, IF_66|IF_MODRM|IF_REG7,                              "pslldq\t" OP_U8 OP_RM128_XMM),           /*              66 0f 73 /7 ib pslldq xmm1, imm8 */

	I(0x74, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpcmpeqb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x74, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpcmpeqb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x74, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpcmpeqb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x74, IF_MODRM,              "pcmpeqb\t" OP_RMM OP_RM64_MM),
	I(0x74, IF_66|IF_MODRM,        "pcmpeqb\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpcmpeqw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpcmpeqw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpcmpeqw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x75, IF_MODRM,              "pcmpeqw\t" OP_RMM OP_RM64_MM),
	I(0x75, IF_66|IF_MODRM,        "pcmpeqw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpcmpeqd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcmpeqd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpcmpeqd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcmpeqd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcmpeqd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x76, IF_MODRM,              "pcmpeqd\t" OP_RMM OP_RM64_MM),
	I(0x76, IF_66|IF_MODRM,        "pcmpeqd\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x77, IF_VEX, OP_VEX_B0(0, 1, 0, 0) "vzeroupper"),
	I(0x77, IF_VEX, OP_VEX_B0(0, 1, 0, 1) "vzeroall"),
	I(0x77, 0,                      "emms"),

//	I(0x78, IF_MODRM|IF_RMM,  "svdc\t" OP_RSEG OP_MEM/*80*/), /* Unofficial */
//	I(0x79, IF_MODRM|IF_RMM,  "rsdc\t" OP_MEM/*80*/ OP_RSEG), /* Unofficial */

	I(0x78, IF_X32|IF_MODRM,        "vmreadl\t" OP_R32 OP_RM32),
	I(0x78, IF_X64|IF_MODRM,        "vmreadq\t" OP_R64 OP_RM64),

	I(0x79, IF_X32|IF_MODRM,        "vmwritel\t" OP_R32 OP_RM32),
	I(0x79, IF_X64|IF_MODRM,        "vmwriteq\t" OP_R64 OP_RM64),

	I(0x7c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vhaddpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f.WIG 7c /r vhaddpd xmm1, xmm2, xmm3/m128 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vhaddpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f.WIG 7c /r vhaddpd ymm1, ymm2, ymm3/m256 */
	I(0x7c, IF_66|IF_MODRM,                              "haddpd\t" OP_RM128_XMM OP_RXMM),             /*             66 0f 7c /r haddpd xmm1, xmm2/m128 */

	I(0x7c, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vhaddps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.f2.0f.WIG 7c /r vhaddps xmm1, xmm2, xmm3/m128 */
	I(0x7c, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vhaddps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.f2.0f.WIG 7c /r vhaddps ymm1, ymm2, ymm3/m256 */
	I(0x7c, IF_F2|IF_MODRM,                              "haddps\t" OP_RM128_XMM OP_RXMM),             /*             f2 0f 7c /r haddps xmm1, xmm2/m128 */

	I(0x7d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vhsubpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f.WIG 7d /r vhsubpd xmm1, xmm2, xmm3/m128 */
	I(0x7d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vhsubpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f.WIG 7d /r vhsubpd ymm1, ymm2, ymm3/m256 */
	I(0x7d, IF_66|IF_MODRM,                              "hsubpd\t" OP_RM128_XMM OP_RXMM),             /*             66 0f 7d /r hsubpd xmm1, xmm2/m128 */

	I(0x7d, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vhsubps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.f2.0f.WIG 7d /r vhsubps xmm1, xmm2, xmm3/m128 */
	I(0x7d, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vhsubps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.f2.0f.WIG 7d /r vhsubps ymm1, ymm2, ymm3/m256 */
	I(0x7d, IF_F2|IF_MODRM,                              "hsubps\t" OP_RM128_XMM OP_RXMM),             /*             f2 0f 7d /r hsubps xmm1, xmm2/m128 */

	I(0x7e, IF_VEXW0|IF_66|IF_MODRM,"vmovd\t" OP_RXMM OP_RM32),
	I(0x7e, IF_VEXW1|IF_66|IF_MODRM,"vmovq\t" OP_RXMM OP_RM64),
	I(0x7e, IF_MODRM,               "movd\t" OP_RMM OP_RM32),
	I(0x7e, IF_REXW|IF_MODRM,       "movq\t" OP_RMM OP_RM64),
	I(0x7e, IF_66|IF_MODRM,         "movd\t" OP_RXMM OP_RM32),
	I(0x7e, IF_REXW|IF_66|IF_MODRM, "movq\t" OP_RXMM OP_RM64),

	I(0x7f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovdqa\t" OP_RXMM OP_RM128_XMM),    /*  VEX.128.66.0f.WIG 7f /r vmovdqa xmm2/m128, xmm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovdqa\t" OP_RYMM OP_RM256_YMM),    /*  VEX.256.66.0f.WIG 7f /r vmovdqa ymm2/m256, ymm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVDQA32_XMM_REV)), /* EVEX.128.66.0f.W0  7f /r vmovdqa32 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVDQA32_YMM_REV)), /* EVEX.256.66.0f.W0  7f /r vmovdqa32 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVDQA32_ZMM_REV)), /* EVEX.512.66.0f.W0  7f /r vmovdqa32 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQA64_XMM_REV)), /* EVEX.128.66.0f.W1  7f /r vmovdqa64 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQA64_YMM_REV)), /* EVEX.512.66.0f.W1  7f /r vmovdqa64 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQA64_ZMM_REV)), /* EVEX.512.66.0f.W1  7f /r vmovdqa64 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_66|IF_MODRM,        "movdqa\t" OP_RXMM OP_RM128_XMM),                           /*              66 0f 7f /r movdqa xmm2/m128, xmm1 */

	I(0x7f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovdqu\t" OP_RXMM OP_RM128_XMM),       /*  VEX.128.f3.0f.WIG 7f /r vmovdqu xmm2/m128, xmm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovdqu\t" OP_RYMM OP_RM256_YMM),       /*  VEX.256.f3.0f.WIG 7f /r vmovdqu ymm2/m256, ymm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovdqu8\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.f2.0f.W0  7f /r vmovdqu8 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovdqu8\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.f2.0f.W0  7f /r vmovdqu8 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovdqu8\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.f2.0f.W0  7f /r vmovdqu8 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQU16_XMM_REV)),    /* EVEX.128.f2.0f.W1  7f /r vmovdqu16 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQU16_YMM_REV)),    /* EVEX.256.f2.0f.W1  7f /r vmovdqu16 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQU16_ZMM_REV)),    /* EVEX.512.f2.0f.W1  7f /r vmovdqu16 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVDQU32_XMM_REV)),    /* EVEX.128.f3.0f.W0  7f /r vmovdqu32 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVDQU32_YMM_REV)),    /* EVEX.256.f3.0f.W0  7f /r vmovdqu32 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVDQU32_ZMM_REV)),    /* EVEX.512.f3.0f.W0  7f /r vmovdqu32 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQU64_XMM_REV)),    /* EVEX.128.f3.0f.W1  7f /r vmovdqu64 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQU64_YMM_REV)),    /* EVEX.256.f3.0f.W1  7f /r vmovdqu64 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQU64_ZMM_REV)),    /* EVEX.512.f3.0f.W1  7f /r vmovdqu64 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_F3|IF_MODRM,        "movdqu\t" OP_RXMM OP_RM128_XMM),                              /*              f3 0f 7f /r movdqu xmm2/m128, xmm1 */

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

	I(0x90, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "kmovb\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W0 90 /r kmovb k1, k2/m8 */
	I(0x90, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 0) "kmovw\t" OP_RMK OP_RK), /* VEX.L0.   0f.W0 90 /r kmovw k1, k2/m16 */
	I(0x90, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "kmovd\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W1 90 /r kmovd k1, k2/m32 */
	I(0x90, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 0) "kmovq\t" OP_RMK OP_RK), /* VEX.L0.   0f.W1 90 /r kmovq k1, k2/m64 */

	I(0x90, IF_MODRM,         "set" NAME_jc0 "\t" OP_RM8),

	I(0x91, IF_VEX|IF_66|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "kmovb\t" OP_RK OP_MEM), /* VEX.L0.66.0f.W0 91 /r kmovb m8, k1 */
	I(0x91, IF_VEX|IF_MODRM|IF_RMM,       OP_VEX_B0(0, 0, 0, 0) "kmovw\t" OP_RK OP_MEM), /* VEX.L0.   0f.W0 91 /r kmovw m16, k1 */
	I(0x91, IF_VEX|IF_66|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "kmovd\t" OP_RK OP_MEM), /* VEX.L0.66.0f.W1 91 /r kmovd m32, k1 */
	I(0x91, IF_VEX|IF_MODRM|IF_RMM,       OP_VEX_B0(0, 0, 1, 0) "kmovq\t" OP_RK OP_MEM), /* VEX.L0.   0f.W1 91 /r kmovq m64, k1 */

	I(0x91, IF_MODRM,         "set" NAME_jc1 "\t" OP_RM8),

	I(0x92, IF_VEX|IF_66|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "kmovb\t" OP_RM32 OP_RK), /* VEX.L0.66.0f.W0 92 /r kmovb k1, r32 */
	I(0x92, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 0, 0) "kmovw\t" OP_RM32 OP_RK), /* VEX.L0.   0f.W0 92 /r kmovw k1, r32 */
	I(0x92, IF_VEX|IF_F2|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "kmovd\t" OP_RM32 OP_RK), /* VEX.L0.f2.0f.W0 92 /r kmovd k1, r32 */
	I(0x92, IF_VEX|IF_F2|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "kmovq\t" OP_RM64 OP_RK), /* VEX.L0.f2.0f.W1 92 /r kmovq k1, r64 */

	I(0x92, IF_MODRM,         "set" NAME_jc2 "\t" OP_RM8),

	I(0x93, IF_VEX|IF_66|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "kmovb\t" OP_RMK OP_R32), /* VEX.L0.66.0f.W0 93 /r kmovb r32, k1 */
	I(0x93, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 0, 0) "kmovw\t" OP_RMK OP_R32), /* VEX.L0.   0f.W0 93 /r kmovw r32, k1 */
	I(0x93, IF_VEX|IF_F2|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "kmovd\t" OP_RMK OP_R32), /* VEX.L0.f2.0f.W0 93 /r kmovd r32, k1 */
	I(0x93, IF_VEX|IF_F2|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "kmovq\t" OP_RMK OP_R64), /* VEX.L0.f2.0f.W1 93 /r kmovq r64, k1 */

	I(0x93, IF_MODRM,         "set" NAME_jc3 "\t" OP_RM8),

	I(0x94, IF_MODRM,         "set" NAME_jc4 "\t" OP_RM8),

	I(0x95, IF_MODRM,         "set" NAME_jc5 "\t" OP_RM8),

	I(0x96, IF_MODRM,         "set" NAME_jc6 "\t" OP_RM8),

	I(0x97, IF_MODRM,         "set" NAME_jc7 "\t" OP_RM8),

	I(0x98, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "kortestb\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W0 98 /r kortestb k1, k2 */
	I(0x98, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 0) "kortestw\t" OP_RMK OP_RK), /* VEX.L0.   0f.W0 98 /r kortestw k1, k2 */
	I(0x98, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "kortestd\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W1 98 /r kortestd k1, k2 */
	I(0x98, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 0) "kortestq\t" OP_RMK OP_RK), /* VEX.L0.   0f.W1 98 /r kortestq k1, k2 */

	I(0x98, IF_MODRM,         "set" NAME_jc8 "\t" OP_RM8),

	I(0x99, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "ktestb\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W0 99 /r ktestb k1, k2 */
	I(0x99, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 0) "ktestw\t" OP_RMK OP_RK), /* VEX.L0.   0f.W0 99 /r ktestw k1, k2 */
	I(0x99, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "ktestd\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W1 99 /r ktestd k1, k2 */
	I(0x99, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 0) "ktestq\t" OP_RMK OP_RK), /* VEX.L0.   0f.W1 99 /r ktestq k1, k2 */

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

	I(0xae, IF_VEX|IF_MODRM|IF_RMM|IF_REG2, OP_VEX_B0(0,1,0,0) "vldmxcsr\t" OP_MEM),
	I(0xae, IF_VEX|IF_MODRM|IF_RMM|IF_REG3, OP_VEX_B0(0,1,0,0) "vstmxcsr\t" OP_MEM),
	I(0xae, IF_F3|IF_MODRM|IF_REG0,         "rdfsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG0, "rdfsbaseq\t" OP_RM64),

	I(0xae, IF_F3|IF_MODRM|IF_REG1,         "rdgsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG1, "rdgsbaseq\t" OP_RM64),

	I(0xae, IF_F3|IF_MODRM|IF_REG2,         "wrfsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG2, "wrfsbaseq\t" OP_RM64),

	I(0xae, IF_F3|IF_MODRM|IF_REG3,         "wrgsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG3, "wrgsbaseq\t" OP_RM64),

	I(0xae, IF_MODRM|IF_RMM|IF_REG0,        "fxsave\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG1,        "fxrstor\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG2,        "ldmxcsr\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG3,        "stmxcsr\t" OP_MEM),

	I(0xae, IF_MODRM|IF_RMM|IF_REG4,        "xsave\t" OP_MEM),
	I(0xae, IF_REXW|IF_MODRM|IF_RMM|IF_REG4,"xsave64\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG5,        "xrstor\t" OP_MEM),
	I(0xae, IF_REXW|IF_MODRM|IF_RMM|IF_REG5,"xrstor64\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG6,        "xsaveopt\t" OP_MEM),
	I(0xae, IF_REXW|IF_MODRM|IF_RMM|IF_REG6,"xsaveopt64\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG7,        "clflush\t" OP_MEM),
	I(0xae, IF_66|IF_MODRM|IF_RMM|IF_REG7,  "clflushopt\t" OP_RM32),

	I(0xae, IF_MODRM|IF_RMM|IF_REG0,         "fxsave\t" OP_MEM),
	I(0xae, IF_REXW|IF_MODRM|IF_RMM|IF_REG0, "fxsave64\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG1,         "fxrstor\t" OP_MEM),
	I(0xae, IF_REXW|IF_MODRM|IF_RMM|IF_REG1, "fxrstor64\t" OP_MEM),

	I(0xae, IF_F3|IF_MODRM|IF_REG6|IF_RMR|IF_X32, "umonitorl\t" OP_RM32),
	I(0xae, IF_F3|IF_MODRM|IF_REG6|IF_RMR|IF_X64, "umonitorq\t" OP_RM64),
	I(0xae, IF_F2|IF_MODRM|IF_REG6,               "umwait\t" OP_EAX OP_EDX OP_RM32),

	I(0xae, IF_BYTE2,                "\xe8" "lfence"),
	I(0xae, IF_BYTE2,                "\xf0" "mfence"),
	I(0xae, IF_BYTE2,                "\xf8" "sfence"),

	I(0xaf, IF_66|IF_MODRM,  "imulb\t" OP_RM8 OP_R8),
	I(0xaf, IF_MODRM,        "imulw\t" OP_RM16 OP_R16),
	I(0xaf, IF_REXW|IF_MODRM,"imull\t" OP_RM32 OP_R32),

	I(0xb0, IF_MODRM,        "cmpxchgb\t" OP_R8 OP_RM8),
	I(0xb1, IF_66|IF_MODRM,  "cmpxchgw\t" OP_R16 OP_RM16),
	I(0xb1, IF_MODRM,        "cmpxchgl\t" OP_R32 OP_RM32),
	I(0xb1, IF_REXW|IF_MODRM,"cmpxchgq\t" OP_R64 OP_RM64),

	I(0xb2, IF_66|IF_MODRM|IF_RMM,  "lssw\t" OP_MEM/*32*/ OP_R16),
	I(0xb2, IF_MODRM|IF_RMM,        "lssl\t" OP_MEM/*48*/ OP_R32),
	I(0xb2, IF_REXW|IF_MODRM|IF_RMM,"lssq\t" OP_MEM/*80*/ OP_R64),

	I(0xb3, IF_66|IF_MODRM,  "btrw\t" OP_R16 OP_RM16),
	I(0xb3, IF_MODRM,        "btrl\t" OP_R32 OP_RM32),
	I(0xb3, IF_REXW|IF_MODRM,"btrq\t" OP_R64 OP_RM64),

	I(0xb4, IF_66|IF_MODRM|IF_RMM,  "lfsw\t" OP_MEM/*32*/ OP_R16),
	I(0xb4, IF_MODRM|IF_RMM,        "lfsl\t" OP_MEM/*48*/ OP_R32),
	I(0xb4, IF_REXW|IF_MODRM|IF_RMM,"lfsq\t" OP_MEM/*80*/ OP_R64),
	I(0xb5, IF_66|IF_MODRM|IF_RMM,  "lgsw\t" OP_MEM/*32*/ OP_R16),
	I(0xb5, IF_MODRM|IF_RMM,        "lgsl\t" OP_MEM/*48*/ OP_R32),
	I(0xb5, IF_REXW|IF_MODRM|IF_RMM,"lgsq\t" OP_MEM/*80*/ OP_R64),

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

	I(0xc3, IF_MODRM|IF_RMM,        "movntil\t" OP_R32 OP_RM32),
	I(0xc3, IF_REXW|IF_MODRM|IF_RMM,"movntiq\t" OP_R64 OP_RM64),

	I(0xc6, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vshufps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG c6 /r ib vshufps xmm1, xmm2, xmm3/m128, imm8 */
	I(0xc6, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vshufps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG c6 /r ib vshufps ymm1, ymm2, ymm3/m256, imm8 */
	I(0xc6, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vshufps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  c6 /r ib vshufps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst, imm8 */
	I(0xc6, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vshufps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  c6 /r ib vshufps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0xc6, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vshufps\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  c6 /r ib vshufps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst, imm8 */
	I(0xc6, IF_MODRM,                              "shufps\t" OP_U8 OP_RM128_XMM OP_RXMM),                  /*              0f c6 /r ib shufps xmm1, xmm3/m128, imm8 */

	I(0xc6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vshufpd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG c6 /r ib vshufpd xmm1, xmm2, xmm3/m128, imm8 */
	I(0xc6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vshufpd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG c6 /r ib vshufpd ymm1, ymm2, ymm3/m256, imm8 */
	I(0xc6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vshufpd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  c6 /r ib vshufpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst, imm8 */
	I(0xc6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vshufpd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  c6 /r ib vshufpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0xc6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vshufpd\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  c6 /r ib vshufpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst, imm8 */
	I(0xc6, IF_66|IF_MODRM,                              "shufpd\t" OP_U8 OP_RM128_XMM OP_RXMM),                  /*              66 0f c6 /r ib shufpd xmm1, xmm2/m128, imm8 */

	I(0xc7, IF_X32|IF_MODRM|IF_RMM|IF_REG1,       "cmpxchg8b\t" OP_MEM),
	I(0xc7, IF_X64|IF_MODRM|IF_RMM|IF_REG1,       "cmpxchg16b\t" OP_MEM),

	I(0xc7, IF_MODRM|IF_RMM|IF_REG4,              "xsavec\t" OP_MEM),
	I(0xc7, IF_REXW|IF_MODRM|IF_RMM|IF_REG4,      "xsavec64\t" OP_MEM),

	I(0xc7, IF_MODRM|IF_RMM|IF_REG5,              "xsaves\t" OP_MEM),
	I(0xc7, IF_REXW|IF_MODRM|IF_RMM|IF_REG5,      "xsaves64\t" OP_MEM),

	I(0xc7, IF_MODRM|IF_RMM|IF_REG6,              "vmptrld\t" OP_RM64),
	I(0xc7, IF_66|IF_MODRM|IF_RMM|IF_REG6,        "vmclear\t" OP_RM64),
	I(0xc7, IF_F3|IF_MODRM|IF_RMM|IF_REG6,        "vmxon\t" OP_RM64),
	I(0xc7, IF_X32|IF_MODRM|IF_RMR|IF_REG6,       "rdrandl\t" OP_RM32),
	I(0xc7, IF_X64|IF_MODRM|IF_RMR|IF_REG6,       "rdrandq\t" OP_RM64),

	I(0xc7, IF_MODRM|IF_RMM|IF_RMM|IF_REG7,       "vmptrst\t" OP_MEM),
	I(0xc7, IF_X32|IF_MODRM|IF_RMR|IF_REG7,       "rdseedl\t" OP_RM32),
	I(0xc7, IF_X64|IF_MODRM|IF_RMR|IF_REG7,       "rdseedq\t" OP_RM64),
	I(0xc7, IF_F3|IF_X32|IF_MODRM|IF_RMR|IF_REG7, "rdpidl\t" OP_RM32),
	I(0xc7, IF_F3|IF_X64|IF_MODRM|IF_RMR|IF_REG7, "rdpidq\t" OP_RM64),

	I(0xc8, IF_REXB,         "bswapl\t" OP_R8D),
	I(0xc8, IF_REXB|IF_REXW, "bswapq\t" OP_X64_R8),
	I(0xc8, 0,               "bswapl\t" OP_EAX),
	I(0xc8, IF_REXW,         "bswapq\t" OP_RAX),
	I(0xc9, IF_REXB,         "bswapl\t" OP_R9D),
	I(0xc9, IF_REXB|IF_REXW, "bswapq\t" OP_R9),
	I(0xc9, 0,               "bswapl\t" OP_ECX),
	I(0xc9, IF_REXW,         "bswapq\t" OP_RCX),
	I(0xca, IF_REXB,         "bswapl\t" OP_R10D),
	I(0xca, IF_REXB|IF_REXW, "bswapq\t" OP_R10),
	I(0xca, 0,               "bswapl\t" OP_EDX),
	I(0xca, IF_REXW,         "bswapq\t" OP_RDX),
	I(0xcb, IF_REXB,         "bswapl\t" OP_R11D),
	I(0xcb, IF_REXB|IF_REXW, "bswapq\t" OP_R11),
	I(0xcb, 0,               "bswapl\t" OP_EBX),
	I(0xcb, IF_REXW,         "bswapq\t" OP_RBX),
	I(0xcc, IF_REXB,         "bswapl\t" OP_R12D),
	I(0xcc, IF_REXB|IF_REXW, "bswapq\t" OP_R12),
	I(0xcc, 0,               "bswapl\t" OP_ESP),
	I(0xcc, IF_REXW,         "bswapq\t" OP_RSP),
	I(0xcd, IF_REXB,         "bswapl\t" OP_R13D),
	I(0xcd, IF_REXB|IF_REXW, "bswapq\t" OP_R13),
	I(0xcd, 0,               "bswapl\t" OP_EBP),
	I(0xcd, IF_REXW,         "bswapq\t" OP_RBP),
	I(0xce, IF_REXB,         "bswapl\t" OP_R14D),
	I(0xce, IF_REXB|IF_REXW, "bswapq\t" OP_R14),
	I(0xce, 0,               "bswapl\t" OP_ESI),
	I(0xce, IF_REXW,         "bswapq\t" OP_RSI),
	I(0xcf, IF_REXB,         "bswapl\t" OP_R15D),
	I(0xcf, IF_REXB|IF_REXW, "bswapq\t" OP_R15),
	I(0xcf, 0,               "bswapl\t" OP_EDI),
	I(0xcf, IF_REXW,         "bswapq\t" OP_RDI),

	I(0xd0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vaddsubpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f.WIG d0 /r vaddsubpd xmm1, xmm2, xmm3/m128 */
	I(0xd0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vaddsubpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f.WIG d0 /r vaddsubpd ymm1, ymm2, ymm3/m256 */
	I(0xd0, IF_66|IF_MODRM,                              "addsubpd\t" OP_RM128_XMM OP_RXMM),             /*             66 0f d0 /r addsubpd xmm1, xmm2/m128 */

	I(0xd0, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vaddsubps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.f2.0f.WIG d0 /r vaddsubps xmm1, xmm2, xmm3/m128 */
	I(0xd0, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vaddsubps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.f2.0f.WIG d0 /r vaddsubps ymm1, ymm2, ymm3/m256 */
	I(0xd0, IF_F2|IF_MODRM,                              "addsubps\t" OP_RM128_XMM OP_RXMM),             /*             f2 0f d0 /r addsubps xmm1, xmm2/m128 */

	I(0xd1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsrlw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG d1 /r vpsrlw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xd1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsrlw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG d1 /r vpsrlw ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xd1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsrlw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG d1 /r vpsrlw zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xd1, IF_MODRM,                                    "psrlw\t" OP_RM64_MM OP_RMM),                     /*                 0f d1 /r psrlw mm, mm/m64 */
	I(0xd1, IF_66|IF_MODRM,                              "psrlw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d1 /r psrlw xmm1, xmm2/m128 */

	I(0xd2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsrld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG d2 /r vpsrld xmm1, xmm2, xmm3/m128 */
	I(0xd2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsrld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG d2 /r vpsrld ymm1, ymm2, xmm3/m128 */
	I(0xd2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsrld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W0  d2 /r vpsrld xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xd2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsrld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.W0  d2 /r vpsrld ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xd2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsrld\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W0  d2 /r vpsrld zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xd2, IF_MODRM,                                    "psrld\t" OP_RM64_MM OP_RMM),                     /*                 0f d2 /r psrld mm, mm/m64 */
	I(0xd2, IF_66|IF_MODRM,                              "psrld\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d2 /r psrld xmm1, xmm2/m128 */

	I(0xd3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsrlq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG d3 /r vpsrlq xmm1, xmm2, xmm3/m128 */
	I(0xd3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsrlq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG d3 /r vpsrlq ymm1, ymm2, xmm3/m128 */
	I(0xd3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsrlq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  d3 /r vpsrlq xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xd3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsrlq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  d3 /r vpsrlq ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xd3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsrlq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  d3 /r vpsrlq zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xd3, IF_MODRM,                                    "psrlq\t" OP_RM64_MM OP_RMM),                     /*                 0f d3 /r psrlq mm, mm/m64 */
	I(0xd3, IF_66|IF_MODRM,                              "psrlq\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d3 /r psrlq xmm1, xmm2/m128 */

	I(0xd4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpaddq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG d4 /r vpaddq xmm1, xmm2, xmm3/m128 */
	I(0xd4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpaddq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG d4 /r vpaddq ymm1, ymm2, ymm3/m256 */
	I(0xd4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpaddq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  d4 /r vpaddq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xd4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpaddq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  d4 /r vpaddq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xd4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpaddq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  d4 /r vpaddq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0xd4, IF_MODRM,                                    "paddq\t" OP_RM64_MM OP_RMM),                     /*                 0f d4 /r paddq mm, mm/m64 */
	I(0xd4, IF_66|IF_MODRM,                              "paddq\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d4 /r paddq xmm1, xmm2/m128 */

	I(0xd5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmullw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xd5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmullw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xd5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmullw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xd5, IF_MODRM,              "pmullw\t" OP_RMM OP_RM64_MM),
	I(0xd5, IF_66|IF_MODRM,        "pmullw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xd6, IF_F2|IF_MODRM|IF_RMR, "movdq2q\t" OP_RM128_XMM OP_RMM),
	I(0xd6, IF_F2|IF_MODRM|IF_RMR, "movq2dq\t" OP_RMM OP_RM128_XMM),

	I(0xd7, IF_66|IF_VEX|IF_MODRM,         LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVMSKB_XMM_R32)), /* VEX.128.66.0f.WIG d7 /r vpmovmskb r32, xmm1 */
	I(0xd7, IF_66|IF_VEX|IF_MODRM|IF_REXW, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVMSKB_XMM_R64)), /* VEX.128.66.0f.WIG d7 /r vpmovmskb r64, xmm1 */
	I(0xd7, IF_66|IF_VEX|IF_MODRM,         LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVMSKB_YMM_R32)), /* VEX.256.66.0f.WIG d7 /r vpmovmskb r32, ymm1 */
	I(0xd7, IF_66|IF_VEX|IF_MODRM|IF_REXW, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVMSKB_YMM_R64)), /* VEX.256.66.0f.WIG d7 /r vpmovmskb r64, ymm1 */
	I(0xd7, IF_MODRM|IF_RMR,               "pmovmskbl\t" OP_RMM OP_R32),                               /*                0f d7 /r pmovmskb r32, mm */
	I(0xd7, IF_MODRM|IF_RMR|IF_REXW,       "pmovmskbq\t" OP_RMM OP_R64),                               /*                0f d7 /r pmovmskb r64, mm */
	I(0xd7, IF_66|IF_MODRM|IF_RMR,         "pmovmskbl\t" OP_RXMM OP_R32),                              /*             66 0f d7 /r pmovmskb r32, xmm */
	I(0xd7, IF_66|IF_MODRM|IF_RMR|IF_REXW, "pmovmskbl\t" OP_RXMM OP_R64),                              /*             66 0f d7 /r pmovmskb r64, xmm */

	I(0xd8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubusb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG d8 /r vpsubusb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xd8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubusb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG d8 /r vpsubusb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xd8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubusb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG d8 /r vpsubusb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xd8, IF_MODRM,                                    "psubusb\t" OP_RM64_MM OP_RMM),                     /*                 0f d8 /r psubusb mm, mm/m64 */
	I(0xd8, IF_66|IF_MODRM,                              "psubusb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d8 /r psubusb xmm1, xmm2/m128 */

	I(0xd9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubusw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG d9 /r vpsubusw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xd9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubusw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG d9 /r vpsubusw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xd9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubusw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG d9 /r vpsubusw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xd9, IF_MODRM,                                    "psubusw\t" OP_RM64_MM OP_RMM),                     /*                 0f d9 /r psubusw mm, mm/m64 */
	I(0xd9, IF_66|IF_MODRM,                              "psubusw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d9 /r psubusw xmm1, xmm2/m128 */

	I(0xda, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpminub\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG da /r vpminub xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xda, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpminub\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG da /r vpminub ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xda, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpminub\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG da /r vpminub zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xda, IF_MODRM,                                    "pminub\t" OP_RM64_MM OP_RMM),                     /*                 0f da /r pminub mm1, mm2/m64 */
	I(0xda, IF_66|IF_MODRM,                              "pminub\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f da /r pminub xmm1, xmm2/m128 */

	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpand\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpand\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpandd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpandd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpandd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpandq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpandq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpandq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdb, IF_MODRM,              "pand\t" OP_RM64_MM OP_RMM),
	I(0xdb, IF_66|IF_MODRM,        "pand\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xdc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddusb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddusb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddusb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdc, IF_MODRM,              "paddusb\t" OP_RMM OP_RM64_MM),
	I(0xdc, IF_66|IF_MODRM,        "paddusb\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xdd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddusw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddusw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddusw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdd, IF_MODRM,              "paddusw\t" OP_RMM OP_RM64_MM),
	I(0xdd, IF_66|IF_MODRM,        "paddusw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xde, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmaxub\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG de /r vpmaxub xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xde, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmaxub\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG de /r vpmaxub ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xde, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmaxub\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG de /r vpmaxub zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xde, IF_MODRM,                                    "pmaxub\t" OP_RM64_MM OP_RMM),                     /*                 0f de /r pmaxub mm1, mm2/m64 */
	I(0xde, IF_66|IF_MODRM,                              "pmaxub\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f de /r pmaxub xmm1, xmm2/m128 */

	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpandn\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpandn\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpandnd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpandnd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpandnd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpandnq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpandnq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpandnq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdf, IF_MODRM,              "pandn\t" OP_RM64_MM OP_RMM),
	I(0xdf, IF_66|IF_MODRM,        "pandn\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xe0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpavgb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e0 /r vpavgb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpavgb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e0 /r vpavgb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xe0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpavgb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e0 /r vpavgb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xe0, IF_MODRM,                                    "pavgb\t" OP_RM64_MM OP_RMM),                     /*                 0f e0 /r pavgb mm1, mm2/m64 */
	I(0xe0, IF_66|IF_MODRM,                              "pavgb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e0 /r pavgb xmm1, xmm2/m128 */

	I(0xe1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsraw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e1 /r vpsraw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsraw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e1 /r vpsraw ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xe1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsraw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e1 /r vpsraw zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xe1, IF_MODRM,                                    "psraw\t" OP_RM64_MM OP_RMM),                     /*                 0f e1 /r psraw mm, mm/m64 */
	I(0xe1, IF_66|IF_MODRM,                              "psraw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e1 /r psraw xmm1, xmm2/m128 */

	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsrad\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG e2 /r vpsrad xmm1, xmm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsrad\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG e2 /r vpsrad ymm1, ymm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsrad\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W0  e2 /r vpsrad xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsrad\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.W0  e2 /r vpsrad ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsrad\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W0  e2 /r vpsrad zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsraq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  e2 /r vpsraq xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsraq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  e2 /r vpsraq ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsraq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  e2 /r vpsraq zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xe2, IF_MODRM,                                    "psrad\t" OP_RM64_MM OP_RMM),                     /*                 0f e2 /r psrad mm, mm/m64 */
	I(0xe2, IF_66|IF_MODRM,                              "psrad\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e2 /r psrad xmm1, xmm2/m128 */

	I(0xe3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpavgw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e3 /r vpavgw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpavgw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e3 /r vpavgw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xe3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpavgw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e3 /r vpavgw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xe3, IF_MODRM,                                    "pavgw\t" OP_RM64_MM OP_RMM),                     /*                 0f e3 /r pavgw mm1, mm2/m64 */
	I(0xe3, IF_66|IF_MODRM,                              "pavgw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e3 /r pavgw xmm1, xmm2/m128 */

	I(0xe4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmulhuw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e4 /r vpmulhuw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmulhuw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e4 /r vpmulhuw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xe4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmulhuw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e4 /r vpmulhuw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xe4, IF_MODRM,                                    "pmulhuw\t" OP_RM64_MM OP_RMM),                     /*                 0f e4 /r pmulhuw mm1, mm2/m64 */
	I(0xe4, IF_66|IF_MODRM,                              "pmulhuw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e4 /r pmulhuw xmm1, xmm2/m128 */

	I(0xe5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmulhw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xe5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmulhw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xe5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmulhw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xe5, IF_MODRM,              "pmulhw\t" OP_RMM OP_RM64_MM),
	I(0xe5, IF_66|IF_MODRM,        "pmulhw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VCVTDQ2PD_XMM)), /*  VEX.128.f3.0f.WIG e6 /r vcvtdq2pd xmm1, xmm2/m64 */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VCVTDQ2PD_YMM)), /*  VEX.256.f3.0f.WIG e6 /r vcvtdq2pd ymm1, xmm2/m128 */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTDQ2PD_XMM)), /* EVEX.128.f3.0f.W0  e6 /r vcvtdq2pd xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTDQ2PD_YMM)), /* EVEX.256.f3.0f.W0  e6 /r vcvtdq2pd ymm1{k1}{z}, xmm2/m128/m32bcst */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTDQ2PD_ZMM)), /* EVEX.512.f3.0f.W0  e6 /r vcvtdq2pd zmm1{k1}{z}, ymm2/m256/m32bcst */
	I(0xe6, IF_F3|IF_MODRM,        "cvtdq2pd\t" OP_RM128_XMM OP_RXMM),                     /*              f3 0f e6 /r cvtdq2pd xmm1, xmm2/m64 */

	I(0xe7, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovntdq\t" OP_RXMM OP_MEM), /*  VEX.128.66.0f.WIG e7 /r vmovntdq m128, xmm1 */
	I(0xe7, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 1) "vmovntdq\t" OP_RYMM OP_MEM), /*  VEX.256.66.0f.WIG e7 /r vmovntdq m256, ymm1 */
	I(0xe7, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovntdq\t" OP_RXMM OP_MEM), /* EVEX.128.66.0f.W0  e7 /r vmovntdq m128, xmm1 */
	I(0xe7, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vmovntdq\t" OP_RYMM OP_MEM), /* EVEX.256.66.0f.W0  e7 /r vmovntdq m256, ymm1 */
	I(0xe7, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 2) "vmovntdq\t" OP_RZMM OP_MEM), /* EVEX.512.66.0f.W0  e7 /r vmovntdq m512, zmm1 */
	I(0xe7, IF_66|IF_MODRM|IF_RMM,                              "movntdq\t" OP_RXMM OP_MEM),  /*              66 0f e7 /r movntdq m128, xmm1 */
	I(0xe7, IF_MODRM|IF_RMM,                                    "movntq\t" OP_RMM OP_MEM),

	I(0xe8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubsb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e8 /r vpsubsb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubsb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e8 /r vpsubsb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xe8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubsb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e8 /r vpsubsb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xe8, IF_MODRM,                                    "psubsb\t" OP_RM64_MM OP_RMM),                     /*                 0f e8 /r psubsb mm, mm/m64 */
	I(0xe8, IF_66|IF_MODRM,                              "psubsb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e8 /r psubsb xmm1, xmm2/m128 */

	I(0xe9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e9 /r vpsubsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e9 /r vpsubsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xe9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubsw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e9 /r vpsubsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xe9, IF_MODRM,                                    "psubsw\t" OP_RM64_MM OP_RMM),                     /*                 0f e9 /r psubsw mm, mm/m64 */
	I(0xe9, IF_66|IF_MODRM,                              "psubsw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e9 /r psubsw xmm1, xmm2/m128 */

	I(0xea, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpminsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG ea /r vpminsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xea, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpminsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG ea /r vpminsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xea, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpminsw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG ea /r vpminsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xea, IF_MODRM,                                    "pminsw\t" OP_RM64_MM OP_RMM),                     /*                 0f ea /r pminsw mm1, mm2/m64 */
	I(0xea, IF_66|IF_MODRM,                              "pminsw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f ea /r pminsw xmm1, xmm2/m128 */

	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpor\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpor\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpord\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpord\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpord\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vporq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vporq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vporq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xeb, IF_MODRM,              "por\t" OP_RM64_MM OP_RMM),
	I(0xeb, IF_66|IF_MODRM,        "por\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xec, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddsb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG ec /r vpaddsb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xec, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddsb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG ec /r vpaddsb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xec, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddsb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG ec /r vpaddsb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xec, IF_MODRM,                                    "paddsb\t" OP_RM64_MM OP_RMM),                     /*                 0f ec /r paddsb mm, mm/m64 */
	I(0xec, IF_66|IF_MODRM,                              "paddsb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f ec /r paddsb xmm1, xmm2/m128 */

	I(0xed, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG ed /r vpaddsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xed, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG ed /r vpaddsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xed, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddsw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG ed /r vpaddsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xed, IF_MODRM,                                    "paddsw\t" OP_RM64_MM OP_RMM),                     /*                 0f ed /r paddsw mm, mm/m64 */
	I(0xed, IF_66|IF_MODRM,                              "paddsw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f ed /r paddsw xmm1, xmm2/m128 */

	I(0xee, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmaxsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG ee /r vpmaxsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xee, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmaxsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG ee /r vpmaxsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xee, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmaxsw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG ee /r vpmaxsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xee, IF_MODRM,                                    "pmaxsw\t" OP_RM64_MM OP_RMM),                     /*                 0f ee /r pmaxsw mm1, mm2/m64 */
	I(0xee, IF_66|IF_MODRM,                              "pmaxsw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f ee /r pmaxsw xmm1, xmm2/m128 */

	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpxor\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),       /*  VEX.128.66.0f.WIG ef /r vpxor xmm1, xmm2, xmm3/m128 */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpxor\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),       /*  VEX.256.66.0f.WIG ef /r vpxor ymm1, ymm2, ymm3/m256 */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpxord\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W0  ef /r vpxord xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpxord\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.W0  ef /r vpxord ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpxord\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W0  ef /r vpxord zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpxorq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  ef /r vpxorq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpxorq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  ef /r vpxorq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpxorq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  ef /r vpxorq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0xef, IF_MODRM,                                    "pxor\t" OP_RM64_MM OP_RMM),                      /*                 0f ef /r pxor mm, mm/m64 */
	I(0xef, IF_66|IF_MODRM,                              "pxor\t" OP_RM128_XMM OP_RXMM),                   /*              66 0f ef /r pxor xmm1, xmm2/m128 */

	I(0xf1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsllw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xf1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsllw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xf1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsllw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xf1, IF_MODRM,              "psllw\t" OP_RMM OP_RM64_MM),
	I(0xf1, IF_66|IF_MODRM,        "psllw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xf2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpslld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xf2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpslld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xf2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpslld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xf2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpslld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xf2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpslld\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xf2, IF_MODRM,              "pslld\t" OP_RMM OP_RM64_MM),
	I(0xf2, IF_66|IF_MODRM,        "pslld\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xf3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsllq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG f3 /r vpsllq xmm1, xmm2, xmm3/m128 */
	I(0xf3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsllq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG f3 /r vpsllq ymm1, ymm2, xmm3/m128 */
	I(0xf3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsllq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  f3 /r vpsllq xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xf3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsllq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  f3 /r vpsllq ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xf3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsllq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  f3 /r vpsllq zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xf3, IF_MODRM,                                    "psllq\t" OP_RM64_MM OP_RMM),                     /*                 0f f3 /r psllq mm, mm/m64 */
	I(0xf3, IF_66|IF_MODRM,                              "psllq\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f f3 /r psllq xmm1, xmm2/m128 */

	I(0xf4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpmuludq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG f4 /r vpmuludq xmm1, xmm2, xmm3/m128 */
	I(0xf4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpmuludq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG f4 /r vpmuludq ymm1, ymm2, ymm3/m256 */
	I(0xf4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmuludq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  f4 /r vpmuludq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xf4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmuludq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  f4 /r vpmuludq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xf4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmuludq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  f4 /r vpmuludq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0xf4, IF_MODRM,                                    "pmuludq\t" OP_RM64_MM OP_RMM),                     /*                 0f f4 /r pmuludq mm1, mm2/m64 */
	I(0xf4, IF_66|IF_MODRM,                              "pmuludq\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f f4 /r pmuludq xmm1, xmm2/m128 */

	I(0xf5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmaddwd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xf5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmaddwd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xf5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmaddwd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xf5, IF_MODRM,              "pmaddwd\t" OP_RMM OP_RM64_MM),
	I(0xf5, IF_66|IF_MODRM,        "pmaddwd\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xf6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsadbw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.128.66.0f.WIG f6 /r vpsadbw xmm1, xmm2, xmm3/m128 */
	I(0xf6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsadbw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* EVEX.256.66.0f.WIG f6 /r vpsadbw ymm1, ymm2, ymm3/m256 */
	I(0xf6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsadbw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM), /* EVEX.512.66.0f.WIG f6 /r vpsadbw zmm1, zmm2, zmm3/m512 */
	I(0xf6, IF_MODRM,                                    "psadbw\t" OP_RM64_MM OP_RMM),                /*                 0f f6 /r psadbw mm1, mm2/m64 */
	I(0xf6, IF_66|IF_MODRM,                              "psadbw\t" OP_RM128_XMM OP_RXMM),             /*              66 0f f6 /r psadbw xmm1, xmm2/m128 */

	I(0xf7, IF_MODRM|IF_RMR,       "maskmovq\t" OP_RM64_MM OP_RMM),

	I(0xf8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG f8 /r vpsubb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xf8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG f8 /r vpsubb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xf8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG f8 /r vpsubb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xf8, IF_MODRM,                                    "psubb\t" OP_RM64_MM OP_RMM),                     /*                 0f f8 /r psubb mm, mm/m64 */
	I(0xf8, IF_66|IF_MODRM,                              "psubb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f f8 /r psubb xmm1, xmm2/m128 */

	I(0xf9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG f9 /r vpsubw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xf9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG f9 /r vpsubw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xf9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG f9 /r vpsubw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xf9, IF_MODRM,                                    "psubw\t" OP_RM64_MM OP_RMM),                     /*                 0f f9 /r psubw mm, mm/m64 */
	I(0xf9, IF_66|IF_MODRM,                              "psubw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f f9 /r psubw xmm1, xmm2/m128 */

	I(0xfa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsubd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG fa /r vpsubd xmm1, xmm2, xmm3/m128 */
	I(0xfa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsubd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG fa /r vpsubd ymm1, ymm2, ymm3/m256 */
	I(0xfa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsubd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W0  fa /r vpsubd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xfa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsubd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.W0  fa /r vpsubd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xfa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsubd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W0  fa /r vpsubd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0xfa, IF_MODRM,                                    "psubd\t" OP_RM64_MM OP_RMM),                     /*                 0f fa /r psubd mm, mm/m64 */
	I(0xfa, IF_66|IF_MODRM,                              "psubd\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f fa /r psubd xmm1, xmm2/m128 */

	I(0xfb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsubq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG fb /r vpsubq xmm1, xmm2, xmm3/m128 */
	I(0xfb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsubq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG fb /r vpsubq ymm1, ymm2, ymm3/m256 */
	I(0xfb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsubq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  fb /r vpsubq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xfb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsubq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  fb /r vpsubq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xfb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsubq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  fb /r vpsubq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0xfb, IF_MODRM,                                    "psubq\t" OP_RM64_MM OP_RMM),                     /*                 0f fb /r psubq mm1, mm2/m64 */
	I(0xfb, IF_66|IF_MODRM,                              "psubq\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f fb /r psubq xmm1, xmm2/m128 */

	I(0xfc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG fc /r vpaddb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xfc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG fc /r vpaddb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xfc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG fc /r vpaddb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xfc, IF_MODRM,                                    "paddb\t" OP_RM64_MM OP_RMM),                     /*                 0f fc /r paddb mm, mm/m64 */
	I(0xfc, IF_66|IF_MODRM,                              "paddb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f fc /r paddb xmm1, xmm2/m128 */

	I(0xfd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG fd /r vpaddw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xfd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG fd /r vpaddw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xfd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG fd /r vpaddw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xfd, IF_MODRM,                                    "paddw\t" OP_RM64_MM OP_RMM),                     /*                 0f fd /r paddw mm, mm/m64 */
	I(0xfd, IF_66|IF_MODRM,                              "paddw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f fd /r paddw xmm1, xmm2/m128 */

	I(0xfe, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpaddd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG fe /r vpaddd xmm1, xmm2, xmm3/m128 */
	I(0xfe, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpaddd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG fe /r vpaddd ymm1, ymm2, ymm3/m256 */
	I(0xfe, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpaddd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W0  fe /r vpaddd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xfe, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpaddd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.W0  fe /r vpaddd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xfe, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpaddd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W0  fe /r vpaddd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0xfe, IF_MODRM,                                    "paddd\t" OP_RM64_MM OP_RMM),                     /*                 0f fe /r paddd mm, mm/m64 */
	I(0xfe, IF_66|IF_MODRM,                              "paddd\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f fe /r paddd xmm1, xmm2/m128 */

	I(0xff, IF_MODRM,        "ud0\t" OP_RM32 OP_R32),

	I(0, 0, "")
/*[[[end:ops_0f]]]*/
};
/* clang-format on */

#if 0
	I(0x58, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vaddps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.0F.WIG 58 /R VADDPS XMM1, XMM2, XMM3/M128 */
	I(0x58, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vaddps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.0F.WIG 58 /R VADDPS YMM1, YMM2, YMM3/M256 */
	I(0x58, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vaddps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.0F.W0  58 /R VADDPS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x58, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vaddps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.0F.W0  58 /R VADDPS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x58, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vaddps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.0F.W0  58 /R VADDPS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0x58, IF_MODRM,                              "addps\t" OP_RM128_XMM OP_RXMM),                         /*              0F 58 /R ADDPS XMM1, XMM2/M128 */

	I(0x58, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vaddss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F3.0F.WIG 58 /R VADDSS XMM1, XMM2, XMM3/M32 */
	I(0x58, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vaddss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F3.0F.W0  58 /R VADDSS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */
	I(0x58, IF_F3|IF_MODRM,                               "addss\t" OP_RM128_XMM OP_RXMM),                         /*              F3 0F 58 /R ADDSS XMM1, XMM2/M32 */

	I(0xc2, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcmpps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM),          /*  VEX.128.0F.WIG C2 /R IB VCMPPS XMM1, XMM2, XMM3/M128, IMM8 */
	I(0xc2, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcmpps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM),          /*  VEX.256.0F.WIG C2 /R IB VCMPPS YMM1, YMM2, YMM3/M256, IMM8 */
	I(0xc2, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcmpps\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK),         /* EVEX.128.0F.W0  C2 /R IB VCMPPS K1{K2}, XMM2, XMM3/M128/M32BCST, IMM8 */
	I(0xc2, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcmpps\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK),         /* EVEX.256.0F.W0  C2 /R IB VCMPPS K1{K2}, YMM2, YMM3/M256/M32BCST, IMM8 */
	I(0xc2, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcmpps\t" OP_U8 OP_RM512_ZMM "{sae}" OP_VRZMM OP_RK_MASK), /* EVEX.512.0F.W0  C2 /R IB VCMPPS K1{K2}, ZMM2, ZMM3/M512/M32BCST{SAE}, IMM8 */
	I(0xc2, IF_MODRM,                              "cmpps\t" OP_U8 OP_RM128_XMM OP_RXMM),                      /*              0F C2 /R IB CMPPS XMM1, XMM2/M128, IMM8 */

	I(0xc2, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcmpss\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM),          /*  VEX.LIG.F3.0F.WIG C2 /R IB VCMPSS XMM1, XMM2, XMM3/M32, IMM8 */
	I(0xc2, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcmpss\t" OP_U8 OP_RM128_XMM "{sae}" OP_VRXMM OP_RK_MASK), /* EVEX.LIG.F3.0F.W0  C2 /R IB VCMPSS K1{K2}, XMM2, XMM3/M32{SAE}, IMM8 */
	I(0xc2, IF_F3|IF_MODRM,                               "cmpss\t" OP_U8 OP_RM128_XMM OP_RXMM),                      /*              F3 0F C2 /R IB CMPSS XMM1, XMM2/M32, IMM8 */

	I(0x2f, IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcomiss\t" OP_RM128_XMM OP_RXMM),              /*  VEX.LIG.0F.WIG 2F /R VCOMISS XMM1, XMM2/M32 */
	I(0x2f, IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcomiss\t" OP_RM128_XMM OP_RXMM_MASK "{sae}"), /* EVEX.LIG.0F.W0  2F /R VCOMISS XMM1, XMM2/M32{SAE} */
	I(0x2f, IF_MODRM,                               "comiss\t" OP_RM128_XMM OP_RXMM),               /*              0F 2F /R COMISS XMM1, XMM2/M32 */

	I(0x2a, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvtsi2ss\t" OP_RM32 "{er}" OP_VRXMM OP_RXMM), /* EVEX.LIG.F3.0F.W0 2A /R VCVTSI2SS XMM1, XMM2, R/M32{ER} */
	I(0x2a, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtsi2ss\t" OP_RM64 "{er}" OP_VRXMM OP_RXMM), /* EVEX.LIG.F3.0F.W1 2A /R VCVTSI2SS XMM1, XMM2, R/M64{ER} */
	I(0x2a, IF_F3|IF_MODRM,                               "cvtsi2ss\t" OP_RM32 OP_RXMM),                  /*       F3       0F 2A /R CVTSI2SS XMM1, R/M32 */
	I(0x2a, IF_F3|IF_MODRM,                               "cvtsi2ss\t" OP_RM64 OP_RXMM),                  /*       F3 REX.W 0F 2A /R CVTSI2SS XMM1, R/M64 */

	I(0x2d, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvtss2si\t" OP_RM128_XMM "{er}" OP_R32), /* EVEX.LIG.F3.0F.W0 2D /R VCVTSS2SI R32, XMM1/M32{ER} */
	I(0x2d, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtss2si\t" OP_RM128_XMM "{er}" OP_R64), /* EVEX.LIG.F3.0F.W1 2D /R VCVTSS2SI R64, XMM1/M32{ER} */
	I(0x2d, IF_F3|IF_MODRM,                               "cvtss2si\t" OP_RM128_XMM OP_R32),         /*       F3       0F 2D /R CVTSS2SI R32, XMM1/M32 */
	I(0x2d, IF_F3|IF_MODRM,                               "cvtss2si\t" OP_RM128_XMM OP_R64),         /*       F3 REX.W 0F 2D /R CVTSS2SI R64, XMM1/M32 */

	I(0x2c, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvttss2si\t" OP_RM128_XMM OP_R32 "{sae}"), /* EVEX.LIG.F3.0F.W0 2C /R VCVTTSS2SI R32, XMM1/M32{SAE} */
	I(0x2c, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvttss2si\t" OP_RM128_XMM OP_R64 "{sae}"), /* EVEX.LIG.F3.0F.W1 2C /R VCVTTSS2SI R64, XMM1/M32{SAE} */
	I(0x2c, IF_F3|IF_MODRM,                               "cvttss2si\t" OP_RM128_XMM OP_R32),          /*       F3       0F 2C /R CVTTSS2SI R32, XMM1/M32 */
	I(0x2c, IF_F3|IF_MODRM,                               "cvttss2si\t" OP_RM128_XMM OP_R64),          /*       F3 REX.W 0F 2C /R CVTTSS2SI R64, XMM1/M32 */

	I(0x5e, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vdivps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.0F.WIG 5E /R VDIVPS XMM1, XMM2, XMM3/M128 */
	I(0x5e, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vdivps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.0F.WIG 5E /R VDIVPS YMM1, YMM2, YMM3/M256 */
	I(0x5e, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vdivps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.0F.W0  5E /R VDIVPS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x5e, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vdivps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.0F.W0  5E /R VDIVPS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x5e, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vdivps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.0F.W0  5E /R VDIVPS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0x5e, IF_MODRM,                              "divps\t" OP_RM128_XMM OP_RXMM),                         /*              0F 5E /R DIVPS XMM1, XMM2/M128 */

	I(0x5e, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vdivss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F3.0F.WIG 5E /R VDIVSS XMM1, XMM2, XMM3/M32 */
	I(0x5e, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vdivss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F3.0F.W0  5E /R VDIVSS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */
	I(0x5e, IF_F3|IF_MODRM,                               "divss\t" OP_RM128_XMM OP_RXMM),                         /*              F3 0F 5E /R DIVSS XMM1, XMM2/M32 */

	I(0x5f, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmaxps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),              /*  VEX.128.0F.WIG 5F /R VMAXPS XMM1, XMM2, XMM3/M128 */
	I(0x5f, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmaxps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),              /*  VEX.256.0F.WIG 5F /R VMAXPS YMM1, YMM2, YMM3/M256 */
	I(0x5f, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmaxps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),         /* EVEX.128.0F.W0  5F /R VMAXPS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x5f, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmaxps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),         /* EVEX.256.0F.W0  5F /R VMAXPS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x5f, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmaxps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{sae}"), /* EVEX.512.0F.W0  5F /R VMAXPS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{SAE} */
	I(0x5f, IF_MODRM,                              "maxps\t" OP_RM128_XMM OP_RXMM),                          /*              0F 5F /R MAXPS XMM1, XMM2/M128 */

	I(0x5f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vmaxss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),              /*  VEX.LIG.F3.0F.WIG 5F /R VMAXSS XMM1, XMM2, XMM3/M32 */
	I(0x5f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vmaxss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.F3.0F.W0  5F /R VMAXSS XMM1{K1}{Z}, XMM2, XMM3/M32{SAE} */
	I(0x5f, IF_F3|IF_MODRM,                               "maxss\t" OP_RM128_XMM OP_RXMM),                          /*              F3 0F 5F /R MAXSS XMM1, XMM2/M32 */

	I(0x5d, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vminps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),              /*  VEX.128.0F.WIG 5D /R VMINPS XMM1, XMM2, XMM3/M128 */
	I(0x5d, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vminps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),              /*  VEX.256.0F.WIG 5D /R VMINPS YMM1, YMM2, YMM3/M256 */
	I(0x5d, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vminps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),         /* EVEX.128.0F.W0  5D /R VMINPS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x5d, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vminps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),         /* EVEX.256.0F.W0  5D /R VMINPS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x5d, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vminps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{sae}"), /* EVEX.512.0F.W0  5D /R VMINPS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{SAE} */
	I(0x5d, IF_MODRM,                              "minps\t" OP_RM128_XMM OP_RXMM),                          /*              0F 5D /R MINPS XMM1, XMM2/M128 */

	I(0x5d, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vminss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),              /*  VEX.LIG.F3.0F.WIG 5D /R VMINSS XMM1, XMM2, XMM3/M32 */
	I(0x5d, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vminss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.F3.0F.W0  5D /R VMINSS XMM1{K1}{Z}, XMM2, XMM3/M32{SAE} */
	I(0x5d, IF_F3|IF_MODRM,                               "minss\t" OP_RM128_XMM OP_RXMM),                          /*              F3 0F 5D /R MINSS XMM1, XMM2/M32 */

	I(0x12, IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(1, 1, 0, 0) "vmovhlps\t" OP_RM128_XMM OP_VRXMM OP_RXMM), /*  VEX.128.0F.WIG 12 /R VMOVHLPS XMM1, XMM2, XMM3 */
	I(0x12, IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vmovhlps\t" OP_RM128_XMM OP_VRXMM OP_RXMM), /* EVEX.128.0F.W0  12 /R VMOVHLPS XMM1, XMM2, XMM3 */
	I(0x12, IF_MODRM|IF_RMR,                              "movhlps\t" OP_RM128_XMM OP_RXMM),           /*              0F 12 /R MOVHLPS XMM1, XMM2 */

	I(0x16, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovhps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.128.0F.WIG 16 /R VMOVHPS XMM2, XMM1, M64 */
	I(0x16, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovhps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.128.0F.W0  16 /R VMOVHPS XMM2, XMM1, M64 */
	I(0x17, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovhps\t" OP_RXMM OP_MEM),                  /*  VEX.128.0F.WIG 17 /R VMOVHPS M64, XMM1 */
	I(0x17, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovhps\t" OP_RXMM OP_MEM),                  /* EVEX.128.0F.W0  17 /R VMOVHPS M64, XMM1 */
	I(0x16, IF_MODRM|IF_RMM,                              "movhps\t" OP_MEM OP_RXMM),                   /*              0F 16 /R MOVHPS XMM1, M64 */
	I(0x17, IF_MODRM|IF_RMM,                              "movhps\t" OP_RXMM OP_MEM),                   /*              0F 17 /R MOVHPS M64, XMM1 */

	I(0x16, IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(1, 1, 0, 0) "vmovlhps\t" OP_RM128_XMM OP_VRXMM OP_RXMM), /*  VEX.128.0F.WIG 16 /R VMOVLHPS XMM1, XMM2, XMM3 */
	I(0x16, IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vmovlhps\t" OP_RM128_XMM OP_VRXMM OP_RXMM), /* EVEX.128.0F.W0  16 /R VMOVLHPS XMM1, XMM2, XMM3 */
	I(0x16, IF_MODRM|IF_RMR,                              "movlhps\t" OP_RM128_XMM OP_RXMM),           /*              0F 16 /R MOVLHPS XMM1, XMM2 */

	I(0x12, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovlps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.128.0F.WIG 12 /R VMOVLPS XMM2, XMM1, M64 */
	I(0x12, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovlps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.128.0F.W0  12 /R VMOVLPS XMM2, XMM1, M64 */
	I(0x13, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovlps\t" OP_RXMM OP_MEM),                  /*  VEX.128.0F.WIG 13 /R VMOVLPS M64, XMM1 */
	I(0x13, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovlps\t" OP_RXMM OP_MEM),                  /* EVEX.128.0F.W0  13 /R VMOVLPS M64, XMM1 */
	I(0x12, IF_MODRM|IF_RMM,                              "movlps\t" OP_MEM OP_RXMM),                   /*              0F 12 /R MOVLPS XMM1, M64 */
	I(0x13, IF_MODRM|IF_RMM,                              "movlps\t" OP_RXMM OP_MEM),                   /*              0F 13 /R MOVLPS M64, XMM1 */

	I(0x50, IF_VEX|IF_MODRM|IF_RMR,         OP_VEX_B0(0, 1, 0, 0)  "vmovmskps\t" OP_RM128_XMM OP_R32), /* VEX.128.0F.WIG 50 /R VMOVMSKPS R32, XMM2 */
	I(0x50, IF_VEX|IF_MODRM|IF_RMR|IF_REXW, OP_VEX_B0(0, 1, 0, 0)  "vmovmskps\t" OP_RM128_XMM OP_R64), /* VEX.128.0F.WIG 50 /R VMOVMSKPS R64, XMM2 */
	I(0x50, IF_VEX|IF_MODRM|IF_RMR,         OP_VEX_B0(0, 1, 0, 1)  "vmovmskps\t" OP_RM256_YMM OP_R32), /* VEX.256.0F.WIG 50 /R VMOVMSKPS R32, YMM2 */
	I(0x50, IF_VEX|IF_MODRM|IF_RMR|IF_REXW, OP_VEX_B0(0, 1, 0, 1)  "vmovmskps\t" OP_RM256_YMM OP_R64), /* VEX.256.0F.WIG 50 /R VMOVMSKPS R64, YMM2 */
	I(0x50, IF_MODRM|IF_RMR,                                       "movmskps\t" OP_RM128_XMM OP_R32),  /*             0F 50 /R MOVMSKPS R32, XMM */
	I(0x50, IF_MODRM|IF_RMR|IF_REXW,                               "movmskps\t" OP_RM128_XMM OP_R64),  /*             0F 50 /R MOVMSKPS R64, XMM */

	I(0x10, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(1, 1, 0) "vmovss\t" OP_RM128_XMM OP_VRXMM OP_RXMM),   /*  VEX.LIG.F3.0F.WIG 10 /R VMOVSS XMM1, XMM2, XMM3 */
	I(0x10, IF_F3|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(1, 1, 0) "vmovss\t" OP_MEM OP_RXMM),                  /*  VEX.LIG.F3.0F.WIG 10 /R VMOVSS XMM1, M32 */
	I(0x10, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(0, 0, 0) "vmovss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.LIG.F3.0F.W0  10 /R VMOVSS XMM1{K1}{Z}, XMM2, XMM3 */
	I(0x10, IF_F3|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(0, 0, 0) "vmovss\t" OP_MEM OP_RXMM_MASK),             /* EVEX.LIG.F3.0F.W0  10 /R VMOVSS XMM1{K1}{Z}, M32 */
	I(0x11, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(1, 1, 0) "vmovss\t" OP_RM128_XMM OP_VRXMM OP_RXMM),   /*  VEX.LIG.F3.0F.WIG 11 /R VMOVSS XMM1, XMM2, XMM3 */
	I(0x11, IF_F3|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(1, 1, 0) "vmovss\t" OP_RXMM OP_MEM),                  /*  VEX.LIG.F3.0F.WIG 11 /R VMOVSS M32, XMM1 */
	I(0x11, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(0, 0, 0) "vmovss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.LIG.F3.0F.W0  11 /R VMOVSS XMM1{K1}{Z}, XMM2, XMM3 */
	I(0x11, IF_F3|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(0, 0, 0) "vmovss\t" OP_RXMM OP_MEM_MASK),             /* EVEX.LIG.F3.0F.W0  11 /R VMOVSS M32{K1}, XMM1 */
	I(0x10, IF_F3|IF_MODRM|IF_RMR,                               "movss\t" OP_RM128_XMM OP_RXMM),             /*              F3 0F 10 /R MOVSS XMM1, XMM2 */
	I(0x10, IF_F3|IF_MODRM|IF_RMM,                               "movss\t" OP_MEM OP_RXMM),                   /*              F3 0F 10 /R MOVSS XMM1, M32 */
	I(0x11, IF_F3|IF_MODRM|IF_RMR,                               "movss\t" OP_RXMM OP_RM128_XMM),             /*              F3 0F 11 /R MOVSS XMM2/M32, XMM1 */

	I(0x59, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmulps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.0F.WIG 59 /R VMULPS XMM1, XMM2, XMM3/M128 */
	I(0x59, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmulps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.0F.WIG 59 /R VMULPS YMM1, YMM2, YMM3/M256 */
	I(0x59, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmulps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.0F.W0  59 /R VMULPS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x59, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmulps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.0F.W0  59 /R VMULPS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x59, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmulps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.0F.W0  59 /R VMULPS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0x59, IF_MODRM,                              "mulps\t" OP_RM128_XMM OP_RXMM),                         /*              0F 59 /R MULPS XMM1, XMM2/M128 */

	I(0x59, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vmulss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F3.0F.WIG 59 /R VMULSS XMM1, XMM2, XMM3/M32 */
	I(0x59, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vmulss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F3.0F.W0  59 /R VMULSS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */
	I(0x59, IF_F3|IF_MODRM,                               "mulss\t" OP_RM128_XMM OP_RXMM),                         /*              F3 0F 59 /R MULSS XMM1, XMM2/M32 */

	I(0xc5, IF_66|IF_VEX|IF_MODRM|IF_RMR,         OP_VEX_B0(1, 0, 0, 0) "vpextrw\t" OP_U8 OP_RM128_XMM OP_R32), /*  VEX.128.66.0F.W0  C5 /R IB VPEXTRW R32, XMM1, IMM8 */
	I(0xc5, IF_66|IF_VEX|IF_MODRM|IF_RMR|IF_REXW, OP_VEX_B0(1, 0, 0, 0) "vpextrw\t" OP_U8 OP_RM128_XMM OP_R64), /*  VEX.128.66.0F.W0  C5 /R IB VPEXTRW R64, XMM1, IMM8 */
	I(0xc5, IF_66|IF_VEX|IF_MODRM|IF_RMR,         OP_VEX_B0(0, 1, 0, 0) "vpextrw\t" OP_U8 OP_RM128_XMM OP_R32), /* EVEX.128.66.0F.WIG C5 /R IB VPEXTRW R32, XMM1, IMM8 */
	I(0xc5, IF_66|IF_VEX|IF_MODRM|IF_RMR|IF_REXW, OP_VEX_B0(0, 1, 0, 0) "vpextrw\t" OP_U8 OP_RM128_XMM OP_R64), /* EVEX.128.66.0F.WIG C5 /R IB VPEXTRW R64, XMM1, IMM8 */
	I(0xc5, IF_MODRM|IF_RMR,                                            "pextrw\t" OP_U8 OP_RM64_MM OP_R32),    /*                 0F C5 /R IB PEXTRW R32, MM, IMM8 */
	I(0xc5, IF_MODRM|IF_RMR|IF_REXW,                                    "pextrw\t" OP_U8 OP_RM64_MM OP_R64),    /*                 0F C5 /R IB PEXTRW R64, MM, IMM8 */
	I(0xc5, IF_66|IF_MODRM|IF_RMR,                                      "pextrw\t" OP_U8 OP_RM128_XMM OP_R32),  /*              66 0F C5 /R IB PEXTRW R32, XMM, IMM8 */
	I(0xc5, IF_66|IF_MODRM|IF_RMR|IF_REXW,                              "pextrw\t" OP_U8 OP_RM128_XMM OP_R64),  /*              66 0F C5 /R IB PEXTRW R64, XMM, IMM8 */

	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 0) "vpextrw\t" OP_U8 OP_RXMM OP_RM16), /*  VEX.128.66.0F3A.W0  15 /R IB VPEXTRW R/M16, XMM2, IMM8 */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpextrw\t" OP_U8 OP_RXMM OP_RM16), /* EVEX.128.66.0F3A.WIG 15 /R IB VPEXTRW R/M16, XMM2, IMM8 */
	I(0x15, IF_66|IF_MODRM,                              "pextrw\t" OP_U8 OP_RXMM OP_RM16),  /*             66 0F 3A 15 /R IB PEXTRW R/M16, XMM, IMM8 */

	I(0xc4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 0) "vpinsrw\t" OP_U8 OP_RM32 OP_VRXMM OP_RXMM), /*  VEX.128.66.0F.W0  C4 /R IB VPINSRW XMM1, XMM2, R32/M16, IMM8 */
	I(0xc4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpinsrw\t" OP_U8 OP_RM32 OP_VRXMM OP_RXMM), /* EVEX.128.66.0F.WIG C4 /R IB VPINSRW XMM1, XMM2, R32/M16, IMM8 */
	I(0xc4, IF_MODRM,                                    "pinsrw\t" OP_U8 OP_RM32 OP_RMM),            /*                 0F C4 /R IB PINSRW MM, R32/M16, IMM8 */
	I(0xc4, IF_66|IF_MODRM,                              "pinsrw\t" OP_U8 OP_RM32 OP_RXMM),           /*              66 0F C4 /R IB PINSRW XMM, R32/M16, IMM8 */

	I(0x51, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vsqrtps\t" OP_RM128_XMM OP_RXMM),             /*  VEX.128.0F.WIG 51 /R VSQRTPS XMM1, XMM2/M128 */
	I(0x51, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vsqrtps\t" OP_RM256_YMM OP_RYMM),             /*  VEX.256.0F.WIG 51 /R VSQRTPS YMM1, YMM2/M256 */
	I(0x51, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vsqrtps\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.0F.W0  51 /R VSQRTPS XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x51, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vsqrtps\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.0F.W0  51 /R VSQRTPS YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x51, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vsqrtps\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.0F.W0  51 /R VSQRTPS ZMM1{K1}{Z}, ZMM2/M512/M32BCST{ER} */
	I(0x51, IF_MODRM,                              "sqrtps\t" OP_RM128_XMM OP_RXMM),              /*              0F 51 /R SQRTPS XMM1, XMM2/M128 */

	I(0x51, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vsqrtss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F3.0F.WIG 51 /R VSQRTSS XMM1, XMM2, XMM3/M32 */
	I(0x51, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vsqrtss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F3.0F.W0  51 /R VSQRTSS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */
	I(0x51, IF_F3|IF_MODRM,                               "sqrtss\t" OP_RM128_XMM OP_RXMM),                         /*              F3 0F 51 /R SQRTSS XMM1, XMM2/M32 */

	I(0x5c, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vsubps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.0F.WIG 5C /R VSUBPS XMM1, XMM2, XMM3/M128 */
	I(0x5c, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vsubps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.0F.WIG 5C /R VSUBPS YMM1, YMM2, YMM3/M256 */
	I(0x5c, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vsubps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.0F.W0  5C /R VSUBPS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x5c, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vsubps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.0F.W0  5C /R VSUBPS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x5c, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vsubps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.0F.W0  5C /R VSUBPS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0x5c, IF_MODRM,                              "subps\t" OP_RM128_XMM OP_RXMM),                         /*              0F 5C /R SUBPS XMM1, XMM2/M128 */

	I(0x5c, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vsubss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F3.0F.WIG 5C /R VSUBSS XMM1, XMM2, XMM3/M32 */
	I(0x5c, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vsubss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F3.0F.W0  5C /R VSUBSS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */
	I(0x5c, IF_F3|IF_MODRM,                               "subss\t" OP_RM128_XMM OP_RXMM),                         /*              F3 0F 5C /R SUBSS XMM1, XMM2/M32 */

	I(0x2e, IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vucomiss\t" OP_RM128_XMM OP_RXMM),              /*  VEX.LIG.0F.WIG 2E /R VUCOMISS XMM1, XMM2/M32 */
	I(0x2e, IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vucomiss\t" OP_RM128_XMM OP_RXMM_MASK "{sae}"), /* EVEX.LIG.0F.W0  2E /R VUCOMISS XMM1, XMM2/M32{SAE} */
	I(0x2e, IF_MODRM,                               "ucomiss\t" OP_RM128_XMM OP_RXMM),               /*              0F 2E /R UCOMISS XMM1, XMM2/M32 */

	I(0x58, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vaddpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.66.0F.WIG 58 /R VADDPD XMM1, XMM2, XMM3/M128 */
	I(0x58, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vaddpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.66.0F.WIG 58 /R VADDPD YMM1, YMM2, YMM3/M256 */
	I(0x58, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vaddpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F.W1  58 /R VADDPD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x58, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vaddpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.512.66.0F.W1  58 /R VADDPD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x58, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vaddpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F.W1  58 /R VADDPD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0x58, IF_66|IF_MODRM,                              "addpd\t" OP_RM128_XMM OP_RXMM),                         /*              66 0F 58 /R ADDPD XMM1, XMM2/M128 */

	I(0x58, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vaddsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F2.0F.WIG 58 /R VADDSD XMM1, XMM2, XMM3/M64 */
	I(0x58, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vaddsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F2.0F.W1  58 /R VADDSD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */
	I(0x58, IF_F2|IF_MODRM,                               "addsd\t" OP_RM128_XMM OP_RXMM),                         /*              F2 0F 58 /R ADDSD XMM1, XMM2/M64 */

	I(0xc2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcmppd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM),          /*  VEX.128.66.0F.WIG C2 /R IB VCMPPD XMM1, XMM2, XMM3/M128, IMM8 */
	I(0xc2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcmppd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM),          /*  VEX.256.66.0F.WIG C2 /R IB VCMPPD YMM1, YMM2, YMM3/M256, IMM8 */
	I(0xc2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcmppd\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK),         /* EVEX.128.66.0F.W1  C2 /R IB VCMPPD K1{K2}, XMM2, XMM3/M128/M64BCST, IMM8 */
	I(0xc2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcmppd\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK),         /* EVEX.512.66.0F.W1  C2 /R IB VCMPPD K1{K2}, YMM2, YMM3/M256/M64BCST, IMM8 */
	I(0xc2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcmppd\t" OP_U8 OP_RM512_ZMM "{sae}" OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F.W1  C2 /R IB VCMPPD K1{K2}, ZMM2, ZMM3/M512/M64BCST{SAE}, IMM8 */
	I(0xc2, IF_66|IF_MODRM,                              "cmppd\t" OP_U8 OP_RM128_XMM OP_RXMM),                      /*              66 0F C2 /R IB CMPPD XMM1, XMM2/M128, IMM8 */

	I(0xc2, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcmpsd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM),          /*  VEX.LIG.F2.0F.WIG C2 /R IB VCMPSD XMM1, XMM2, XMM3/M64, IMM8 */
	I(0xc2, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcmpsd\t" OP_U8 OP_RM128_XMM "{sae}" OP_VRXMM OP_RK_MASK), /* EVEX.LIG.F2.0F.W1  C2 /R IB VCMPSD K1{K2}, XMM2, XMM3/M64{SAE}, IMM8 */
	I(0xc2, IF_F2|IF_MODRM,                               "cmpsd\t" OP_U8 OP_RM128_XMM OP_RXMM),                      /*              F2 0F C2 /R IB CMPSD XMM1, XMM2/M64, IMM8 */

	I(0x2f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcomisd\t" OP_RM128_XMM OP_RXMM),         /*  VEX.LIG.66.0F.WIG 2F /R VCOMISD XMM1, XMM2/M64 */
	I(0x2f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcomisd\t" OP_RM128_XMM "{sae}" OP_RXMM), /* EVEX.LIG.66.0F.W1  2F /R VCOMISD XMM1, XMM2/M64{SAE} */
	I(0x2f, IF_66|IF_MODRM,                               "comisd\t" OP_RM128_XMM OP_RXMM),          /*              66 0F 2F /R COMISD XMM1, XMM2/M64 */

	I(0x2a, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvtsi2sd\t" OP_RM32 OP_VRXMM OP_RXMM),        /* EVEX.LIG.F2.0F.W0 2A /R VCVTSI2SD XMM1, XMM2, R/M32 */
	I(0x2a, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtsi2sd\t" OP_RM64 "{er}" OP_VRXMM OP_RXMM), /* EVEX.LIG.F2.0F.W1 2A /R VCVTSI2SD XMM1, XMM2, R/M64{ER} */
	I(0x2a, IF_66|IF_MODRM,                               "cvtpi2pd\t" OP_RM64_MM OP_RXMM),               /*             66 0F 2A /R CVTPI2PD XMM, MM/M64* */
	I(0x2a, IF_F2|IF_MODRM,                               "cvtsi2sd\t" OP_RM32 OP_RXMM),                  /*       F2       0F 2A /R CVTSI2SD XMM1, R32/M32 */
	I(0x2a, IF_F2|IF_MODRM,                               "cvtsi2sd\t" OP_RM64 OP_RXMM),                  /*       F2 REX.W 0F 2A /R CVTSI2SD XMM1, R/M64 */

	I(0x5e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vdivpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.66.0F.WIG 5E /R VDIVPD XMM1, XMM2, XMM3/M128 */
	I(0x5e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vdivpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.66.0F.WIG 5E /R VDIVPD YMM1, YMM2, YMM3/M256 */
	I(0x5e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vdivpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F.W1  5E /R VDIVPD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x5e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vdivpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.512.66.0F.W1  5E /R VDIVPD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x5e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vdivpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F.W1  5E /R VDIVPD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0x5e, IF_66|IF_MODRM,                              "divpd\t" OP_RM128_XMM OP_RXMM),                         /*              66 0F 5E /R DIVPD XMM1, XMM2/M128 */

	I(0x5e, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vdivsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F2.0F.WIG 5E /R VDIVSD XMM1, XMM2, XMM3/M64 */
	I(0x5e, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vdivsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F2.0F.W1  5E /R VDIVSD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */
	I(0x5e, IF_F2|IF_MODRM,                               "divsd\t" OP_RM128_XMM OP_RXMM),                         /*              F2 0F 5E /R DIVSD XMM1, XMM2/M64 */

	I(0x5f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmaxpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),              /*  VEX.128.66.0F.WIG 5F /R VMAXPD XMM1, XMM2, XMM3/M128 */
	I(0x5f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmaxpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),              /*  VEX.256.66.0F.WIG 5F /R VMAXPD YMM1, YMM2, YMM3/M256 */
	I(0x5f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmaxpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),         /* EVEX.128.66.0F.W1  5F /R VMAXPD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x5f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmaxpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),         /* EVEX.512.66.0F.W1  5F /R VMAXPD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x5f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmaxpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F.W1  5F /R VMAXPD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{SAE} */
	I(0x5f, IF_66|IF_MODRM,                              "maxpd\t" OP_RM128_XMM OP_RXMM),                          /*              66 0F 5F /R MAXPD XMM1, XMM2/M128 */

	I(0x5f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vmaxsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),              /*  VEX.LIG.F2.0F.WIG 5F /R VMAXSD XMM1, XMM2, XMM3/M64 */
	I(0x5f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vmaxsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.F2.0F.W1  5F /R VMAXSD XMM1{K1}{Z}, XMM2, XMM3/M64{SAE} */
	I(0x5f, IF_F2|IF_MODRM,                               "maxsd\t" OP_RM128_XMM OP_RXMM),                          /*              F2 0F 5F /R MAXSD XMM1, XMM2/M64 */

	I(0x5d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vminpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),              /*  VEX.128.66.0F.WIG 5D /R VMINPD XMM1, XMM2, XMM3/M128 */
	I(0x5d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vminpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),              /*  VEX.256.66.0F.WIG 5D /R VMINPD YMM1, YMM2, YMM3/M256 */
	I(0x5d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vminpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),         /* EVEX.128.66.0F.W1  5D /R VMINPD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x5d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vminpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),         /* EVEX.512.66.0F.W1  5D /R VMINPD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x5d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vminpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F.W1  5D /R VMINPD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{SAE} */
	I(0x5d, IF_66|IF_MODRM,                              "minpd\t" OP_RM128_XMM OP_RXMM),                          /*              66 0F 5D /R MINPD XMM1, XMM2/M128 */

	I(0x5d, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vminsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),              /*  VEX.LIG.F2.0F.WIG 5D /R VMINSD XMM1, XMM2, XMM3/M64 */
	I(0x5d, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vminsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.F2.0F.W1  5D /R VMINSD XMM1{K1}{Z}, XMM2, XMM3/M64{SAE} */
	I(0x5d, IF_F2|IF_MODRM,                               "minsd\t" OP_RM128_XMM OP_RXMM),                          /*              F2 0F 5D /R MINSD XMM1, XMM2/M64 */

	I(0x16, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovhpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.128.66.0F.WIG 16 /R VMOVHPD XMM2, XMM1, M64 */
	I(0x16, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "vmovhpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.128.66.0F.W1  16 /R VMOVHPD XMM2, XMM1, M64 */
	I(0x17, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovhpd\t" OP_RXMM OP_MEM),                  /*  VEX.128.66.0F.WIG 17 /R VMOVHPD M64, XMM1 */
	I(0x17, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "vmovhpd\t" OP_RXMM OP_MEM),                  /* EVEX.128.66.0F.W1  17 /R VMOVHPD M64, XMM1 */
	I(0x16, IF_66|IF_MODRM|IF_RMM,                              "movhpd\t" OP_MEM OP_RXMM),                   /*              66 0F 16 /R MOVHPD XMM1, M64 */
	I(0x17, IF_66|IF_MODRM|IF_RMM,                              "movhpd\t" OP_RXMM OP_MEM),                   /*              66 0F 17 /R MOVHPD M64, XMM1 */

	I(0x12, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovlpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.128.66.0F.WIG 12 /R VMOVLPD XMM2, XMM1, M64 */
	I(0x12, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "vmovlpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.128.66.0F.W1  12 /R VMOVLPD XMM2, XMM1, M64 */
	I(0x13, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovlpd\t" OP_RXMM OP_MEM),                  /*  VEX.128.66.0F.WIG 13 /R VMOVLPD M64, XMM1 */
	I(0x13, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "vmovlpd\t" OP_RXMM OP_MEM),                  /* EVEX.128.66.0F.W1  13 /R VMOVLPD M64, XMM1 */
	I(0x12, IF_66|IF_MODRM|IF_RMM,                              "movlpd\t" OP_MEM OP_RXMM),                   /*              66 0F 12 /R MOVLPD XMM1, M64 */
	I(0x13, IF_66|IF_MODRM|IF_RMM,                              "movlpd\t" OP_RXMM OP_MEM),                   /*              66 0F 13 /R MOVLPD M64, XMM1 */

	I(0x50, IF_66|IF_VEX|IF_MODRM|IF_RMR,         OP_VEX_B0(0, 1, 0, 0) "vmovmskpd\t" OP_RM128_XMM OP_R32), /* VEX.128.66.0F.WIG 50 /R VMOVMSKPD R32, XMM2 */
	I(0x50, IF_66|IF_VEX|IF_MODRM|IF_RMR|IF_REXW, OP_VEX_B0(0, 1, 0, 0) "vmovmskpd\t" OP_RM128_XMM OP_R64), /* VEX.128.66.0F.WIG 50 /R VMOVMSKPD R64, XMM2 */
	I(0x50, IF_66|IF_VEX|IF_MODRM|IF_RMR,         OP_VEX_B0(0, 1, 0, 1) "vmovmskpd\t" OP_RM256_YMM OP_R32), /* VEX.256.66.0F.WIG 50 /R VMOVMSKPD R32, YMM2 */
	I(0x50, IF_66|IF_VEX|IF_MODRM|IF_RMR|IF_REXW, OP_VEX_B0(0, 1, 0, 1) "vmovmskpd\t" OP_RM256_YMM OP_R64), /* VEX.256.66.0F.WIG 50 /R VMOVMSKPD R64, YMM2 */
	I(0x50, IF_66|IF_MODRM|IF_RMR,                                      "movmskpd\t" OP_RM128_XMM OP_R32),  /*             66 0F 50 /R MOVMSKPD R32, XMM */
	I(0x50, IF_66|IF_MODRM|IF_RMR|IF_REXW,                              "movmskpd\t" OP_RM128_XMM OP_R64),  /*             66 0F 50 /R MOVMSKPD R64, XMM */

	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovntpd\t" OP_RXMM OP_MEM), /*  VEX.128.66.0F.WIG 2B /R VMOVNTPD M128, XMM1 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovntpd\t" OP_RYMM OP_MEM), /*  VEX.256.66.0F.WIG 2B /R VMOVNTPD M256, YMM1 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovntpd\t" OP_RXMM OP_MEM), /* EVEX.128.66.0F.W1  2B /R VMOVNTPD M128, XMM1 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovntpd\t" OP_RYMM OP_MEM), /* EVEX.512.66.0F.W1  2B /R VMOVNTPD M256, YMM1 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovntpd\t" OP_RZMM OP_MEM), /* EVEX.512.66.0F.W1  2B /R VMOVNTPD M512, ZMM1 */
	I(0x2b, IF_66|IF_MODRM,                              "movntpd\t" OP_RXMM OP_MEM),  /*              66 0F 2B /R MOVNTPD M128, XMM1 */

	I(0x10, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(1, 1, 0) "vmovsd\t" OP_RM128_XMM OP_VRXMM OP_RXMM),   /*  VEX.LIG.F2.0F.WIG 10 /R VMOVSD XMM1, XMM2, XMM3 */
	I(0x10, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(1, 1, 0) "vmovsd\t" OP_MEM OP_RXMM),                  /*  VEX.LIG.F2.0F.WIG 10 /R VMOVSD XMM1, M64 */
	I(0x10, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(0, 0, 1) "vmovsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.LIG.F2.0F.W1  10 /R VMOVSD XMM1{K1}{Z}, XMM2, XMM3 */
	I(0x10, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(0, 0, 1) "vmovsd\t" OP_MEM OP_RXMM_MASK),             /* EVEX.LIG.F2.0F.W1  10 /R VMOVSD XMM1{K1}{Z}, M64 */
	I(0x11, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(1, 1, 0) "vmovsd\t" OP_RM128_XMM OP_VRXMM OP_RXMM),   /*  VEX.LIG.F2.0F.WIG 11 /R VMOVSD XMM1, XMM2, XMM3 */
	I(0x11, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(1, 1, 0) "vmovsd\t" OP_RXMM OP_MEM),                  /*  VEX.LIG.F2.0F.WIG 11 /R VMOVSD M64, XMM1 */
	I(0x11, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(0, 0, 1) "vmovsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.LIG.F2.0F.W1  11 /R VMOVSD XMM1{K1}{Z}, XMM2, XMM3 */
	I(0x11, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(0, 0, 1) "vmovsd\t" OP_RXMM OP_MEM_MASK),             /* EVEX.LIG.F2.0F.W1  11 /R VMOVSD M64{K1}, XMM1 */
	I(0x10, IF_F2|IF_MODRM|IF_RMR,                               "movsd\t" OP_RM128_XMM OP_RXMM),             /*              F2 0F 10 /R MOVSD XMM1, XMM2 */
	I(0x10, IF_F2|IF_MODRM|IF_RMM,                               "movsd\t" OP_MEM OP_RXMM),                   /*              F2 0F 10 /R MOVSD XMM1, M64 */
	I(0x11, IF_F2|IF_MODRM,                                      "movsd\t" OP_RXMM OP_RM128_XMM),             /*              F2 0F 11 /R MOVSD XMM1/M64, XMM2 */

	I(0x59, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmulpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.66.0F.WIG 59 /R VMULPD XMM1, XMM2, XMM3/M128 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmulpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.66.0F.WIG 59 /R VMULPD YMM1, YMM2, YMM3/M256 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmulpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F.W1  59 /R VMULPD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x59, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmulpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.512.66.0F.W1  59 /R VMULPD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x59, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmulpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F.W1  59 /R VMULPD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0x59, IF_66|IF_MODRM,                              "mulpd\t" OP_RM128_XMM OP_RXMM),                         /*              66 0F 59 /R MULPD XMM1, XMM2/M128 */

	I(0x59, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vmulsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F2.0F.WIG 59 /R VMULSD XMM1, XMM2, XMM3/M64 */
	I(0x59, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vmulsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F2.0F.W1  59 /R VMULSD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */
	I(0x59, IF_F2|IF_MODRM,                               "mulsd\t" OP_RM128_XMM OP_RXMM),                         /*              F2 0F 59 /R MULSD XMM1, XMM2/M64 */

	I(0x51, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vsqrtpd\t" OP_RM128_XMM OP_RXMM),             /*  VEX.128.66.0F.WIG 51 /R VSQRTPD XMM1, XMM2/M128 */
	I(0x51, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vsqrtpd\t" OP_RM256_YMM OP_RYMM),             /*  VEX.256.66.0F.WIG 51 /R VSQRTPD YMM1, YMM2/M256 */
	I(0x51, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vsqrtpd\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.66.0F.W1  51 /R VSQRTPD XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x51, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vsqrtpd\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.512.66.0F.W1  51 /R VSQRTPD YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x51, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vsqrtpd\t" OP_RM128_XMM OP_RXMM_MASK "{er}"), /* EVEX.512.66.0F.W1  51 /R VSQRTPD ZMM1{K1}{Z}, ZMM2/M512/M64BCST{ER} */
	I(0x51, IF_66|IF_MODRM,                              "sqrtpd\t" OP_RM128_XMM OP_RXMM),              /*              66 0F 51 /R SQRTPD XMM1, XMM2/M128 */

	I(0x51, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vsqrtsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F2.0F.WIG 51 /R VSQRTSD XMM1, XMM2, XMM3/M64 */
	I(0x51, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vsqrtsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F2.0F.W1  51 /R VSQRTSD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */
	I(0x51, IF_F2|IF_MODRM,                               "sqrtsd\t" OP_RM128_XMM OP_RXMM),                         /*              F2 0F 51 /R SQRTSD XMM1, XMM2/M64 */

	I(0x5c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vsubpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.66.0F.WIG 5C /R VSUBPD XMM1, XMM2, XMM3/M128 */
	I(0x5c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vsubpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.66.0F.WIG 5C /R VSUBPD YMM1, YMM2, YMM3/M256 */
	I(0x5c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vsubpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F.W1  5C /R VSUBPD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x5c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vsubpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.512.66.0F.W1  5C /R VSUBPD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x5c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vsubpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F.W1  5C /R VSUBPD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0x5c, IF_66|IF_MODRM,                              "subpd\t" OP_RM128_XMM OP_RXMM),                         /*              66 0F 5C /R SUBPD XMM1, XMM2/M128 */

	I(0x5c, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vsubsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F2.0F.WIG 5C /R VSUBSD XMM1, XMM2, XMM3/M64 */
	I(0x5c, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vsubsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F2.0F.W1  5C /R VSUBSD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */
	I(0x5c, IF_F2|IF_MODRM,                               "subsd\t" OP_RM128_XMM OP_RXMM),                         /*              F2 0F 5C /R SUBSD XMM1, XMM2/M64 */

	I(0x2e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vucomisd\t" OP_RM128_XMM OP_RXMM),              /*  VEX.LIG.66.0F.WIG 2E /R VUCOMISD XMM1, XMM2/M64 */
	I(0x2e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vucomisd\t" OP_RM128_XMM OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F.W1  2E /R VUCOMISD XMM1, XMM2/M64{SAE} */
	I(0x2e, IF_66|IF_MODRM,                               "ucomisd\t" OP_RM128_XMM OP_RXMM),               /*              66 0F 2E /R UCOMISD XMM1, XMM2/M64 */

	I(0xe6, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcvtpd2dq\t" OP_RM128_XMM OP_RXMM),             /*  VEX.128.F2.0F.WIG E6 /R VCVTPD2DQ XMM1, XMM2/M128 */
	I(0xe6, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcvtpd2dq\t" OP_RM256_YMM OP_RXMM),             /*  VEX.256.F2.0F.WIG E6 /R VCVTPD2DQ XMM1, YMM2/M256 */
	I(0xe6, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvtpd2dq\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.F2.0F.W1  E6 /R VCVTPD2DQ XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0xe6, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvtpd2dq\t" OP_RM256_YMM OP_RXMM_MASK),        /* EVEX.256.F2.0F.W1  E6 /R VCVTPD2DQ XMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0xe6, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvtpd2dq\t" OP_RM512_ZMM "{er}" OP_RYMM_MASK), /* EVEX.512.F2.0F.W1  E6 /R VCVTPD2DQ YMM1{K1}{Z}, ZMM2/M512/M64BCST{ER} */
	I(0xe6, IF_F2|IF_MODRM,                              "cvtpd2dq\t" OP_RM128_XMM OP_RXMM),              /*              F2 0F E6 /R CVTPD2DQ XMM1, XMM2/M128 */

	I(0x5b, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcvtdq2ps\t" OP_RM128_XMM OP_RXMM),             /*  VEX.128.0F.WIG 5B /R VCVTDQ2PS XMM1, XMM2/M128 */
	I(0x5b, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcvtdq2ps\t" OP_RM256_YMM OP_RYMM),             /*  VEX.256.0F.WIG 5B /R VCVTDQ2PS YMM1, YMM2/M256 */
	I(0x5b, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvtdq2ps\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.0F.W0  5B /R VCVTDQ2PS XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x5b, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvtdq2ps\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.0F.W0  5B /R VCVTDQ2PS YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x5b, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvtdq2ps\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.0F.W0  5B /R VCVTDQ2PS ZMM1{K1}{Z}, ZMM2/M512/M32BCST{ER} */
	I(0x5b, IF_MODRM,                              "cvtdq2ps\t" OP_RM128_XMM OP_RXMM),              /*              0F 5B /R CVTDQ2PS XMM1, XMM2/M128 */

	I(0x5a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcvtpd2ps\t" OP_RM128_XMM OP_RXMM),             /*  VEX.128.66.0F.WIG 5A /R VCVTPD2PS XMM1, XMM2/M128 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcvtpd2ps\t" OP_RM256_YMM OP_RXMM),             /*  VEX.256.66.0F.WIG 5A /R VCVTPD2PS XMM1, YMM2/M256 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvtpd2ps\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.66.0F.W1  5A /R VCVTPD2PS XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvtpd2ps\t" OP_RM256_YMM OP_RXMM_MASK),        /* EVEX.512.66.0F.W1  5A /R VCVTPD2PS XMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvtpd2ps\t" OP_RM512_ZMM "{er}" OP_RYMM_MASK), /* EVEX.512.66.0F.W1  5A /R VCVTPD2PS YMM1{K1}{Z}, ZMM2/M512/M64BCST{ER} */
	I(0x5a, IF_66|IF_MODRM,                              "cvtpd2ps\t" OP_RM128_XMM OP_RXMM),              /*              66 0F 5A /R CVTPD2PS XMM1, XMM2/M128 */

	I(0x5a, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcvtps2pd\t" OP_RM128_XMM OP_RXMM),              /*  VEX.128.0F.WIG 5A /R VCVTPS2PD XMM1, XMM2/M64 */
	I(0x5a, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcvtps2pd\t" OP_RM128_XMM OP_RYMM),              /*  VEX.256.0F.WIG 5A /R VCVTPS2PD YMM1, XMM2/M128 */
	I(0x5a, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvtps2pd\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.0F.W0  5A /R VCVTPS2PD XMM1{K1}{Z}, XMM2/M64/M32BCST */
	I(0x5a, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvtps2pd\t" OP_RM128_XMM OP_RYMM_MASK),         /* EVEX.256.0F.W0  5A /R VCVTPS2PD YMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x5a, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvtps2pd\t" OP_RM256_YMM OP_RZMM_MASK "{sae}"), /* EVEX.512.0F.W0  5A /R VCVTPS2PD ZMM1{K1}{Z}, YMM2/M256/M32BCST{SAE} */
	I(0x5a, IF_MODRM,                              "cvtps2pd\t" OP_RM128_XMM OP_RXMM),               /*              0F 5A /R CVTPS2PD XMM1, XMM2/M64 */

	I(0x5b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcvtps2dq\t" OP_RM128_XMM OP_RXMM),             /*  VEX.128.66.0F.WIG 5B /R VCVTPS2DQ XMM1, XMM2/M128 */
	I(0x5b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcvtps2dq\t" OP_RM256_YMM OP_RYMM),             /*  VEX.256.66.0F.WIG 5B /R VCVTPS2DQ YMM1, YMM2/M256 */
	I(0x5b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvtps2dq\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.66.0F.W0  5B /R VCVTPS2DQ XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x5b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvtps2dq\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.66.0F.W0  5B /R VCVTPS2DQ YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x5b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvtps2dq\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.66.0F.W0  5B /R VCVTPS2DQ ZMM1{K1}{Z}, ZMM2/M512/M32BCST{ER} */
	I(0x5b, IF_66|IF_MODRM,                              "cvtps2dq\t" OP_RM128_XMM OP_RXMM),              /*              66 0F 5B /R CVTPS2DQ XMM1, XMM2/M128 */

	I(0x2d, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvtsd2si\t" OP_RM128_XMM "{er}" OP_R32), /* EVEX.LIG.F2.0F.W0 2D /R VCVTSD2SI R32, XMM1/M64{ER} */
	I(0x2d, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtsd2si\t" OP_RM128_XMM "{er}" OP_R64), /* EVEX.LIG.F2.0F.W1 2D /R VCVTSD2SI R64, XMM1/M64{ER} */
	I(0x2d, IF_F2|IF_MODRM,                               "cvtsd2si\t" OP_RM128_XMM OP_R32),         /*       F2       0F 2D /R CVTSD2SI R32, XMM1/M64 */
	I(0x2d, IF_F2|IF_MODRM,                               "cvtsd2si\t" OP_RM128_XMM OP_R64),         /*       F2 REX.W 0F 2D /R CVTSD2SI R64, XMM1/M64 */

	I(0x5a, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcvtsd2ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.F2.0F.WIG 5A /R VCVTSD2SS XMM1, XMM2, XMM3/M64 */
	I(0x5a, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtsd2ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.F2.0F.W1  5A /R VCVTSD2SS XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */
	I(0x5a, IF_F2|IF_MODRM,                               "cvtsd2ss\t" OP_RM128_XMM OP_RXMM),                         /*              F2 0F 5A /R CVTSD2SS XMM1, XMM2/M64 */

	I(0x5a, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcvtss2sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),              /*  VEX.LIG.F3.0F.WIG 5A /R VCVTSS2SD XMM1, XMM2, XMM3/M32 */
	I(0x5a, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvtss2sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.F3.0F.W0  5A /R VCVTSS2SD XMM1{K1}{Z}, XMM2, XMM3/M32{SAE} */
	I(0x5a, IF_F3|IF_MODRM,                               "cvtss2sd\t" OP_RM128_XMM OP_RXMM),                          /*              F3 0F 5A /R CVTSS2SD XMM1, XMM2/M32 */

	I(0x2c, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvttsd2si\t" OP_RM128_XMM OP_R32 "{sae}"), /* EVEX.LIG.F2.0F.W0 2C /R VCVTTSD2SI R32, XMM1/M64{SAE} */
	I(0x2c, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvttsd2si\t" OP_RM128_XMM OP_R64 "{sae}"), /* EVEX.LIG.F2.0F.W1 2C /R VCVTTSD2SI R64, XMM1/M64{SAE} */
	I(0x2c, IF_F2|IF_MODRM,                               "cvttsd2si\t" OP_RM128_XMM OP_R32),          /*       F2       0F 2C /R CVTTSD2SI R32, XMM1/M64 */
	I(0x2c, IF_F2|IF_MODRM,                               "cvttsd2si\t" OP_RM128_XMM OP_R64),          /*       F2 REX.W 0F 2C /R CVTTSD2SI R64, XMM1/M64 */

	I(0xe6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcvttpd2dq\t" OP_RM128_XMM OP_RXMM),              /*  VEX.128.66.0F.WIG E6 /R VCVTTPD2DQ XMM1, XMM2/M128 */
	I(0xe6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcvttpd2dq\t" OP_RM256_YMM OP_RXMM),              /*  VEX.256.66.0F.WIG E6 /R VCVTTPD2DQ XMM1, YMM2/M256 */
	I(0xe6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvttpd2dq\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F.W1  E6 /R VCVTTPD2DQ XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0xe6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvttpd2dq\t" OP_RM256_YMM OP_RXMM_MASK),         /* EVEX.512.66.0F.W1  E6 /R VCVTTPD2DQ XMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0xe6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvttpd2dq\t" OP_RM512_ZMM OP_RYMM_MASK "{sae}"), /* EVEX.512.66.0F.W1  E6 /R VCVTTPD2DQ YMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE} */
	I(0xe6, IF_66|IF_MODRM,                              "cvttpd2dq\t" OP_RM128_XMM OP_RXMM),               /*              66 0F E6 /R CVTTPD2DQ XMM1, XMM2/M128 */

	I(0x5b, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcvttps2dq\t" OP_RM128_XMM OP_RXMM),              /*  VEX.128.F3.0F.WIG 5B /R VCVTTPS2DQ XMM1, XMM2/M128 */
	I(0x5b, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcvttps2dq\t" OP_RM256_YMM OP_RYMM),              /*  VEX.256.F3.0F.WIG 5B /R VCVTTPS2DQ YMM1, YMM2/M256 */
	I(0x5b, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvttps2dq\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.F3.0F.W0  5B /R VCVTTPS2DQ XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x5b, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvttps2dq\t" OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.F3.0F.W0  5B /R VCVTTPS2DQ YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x5b, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvttps2dq\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.F3.0F.W0  5B /R VCVTTPS2DQ ZMM1{K1}{Z}, ZMM2/M512/M32BCST{SAE} */
	I(0x5b, IF_F3|IF_MODRM,                              "cvttps2dq\t" OP_RM128_XMM OP_RXMM),               /*              F3 0F 5B /R CVTTPS2DQ XMM1, XMM2/M128 */

	I(0xf7, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 1, 0, 0) "vmaskmovdqu\t" OP_RM128_XMM OP_RXMM), /* VEX.128.66.0F.WIG F7 /R VMASKMOVDQU XMM1, XMM2 */
	I(0xf7, IF_66|IF_MODRM|IF_RMR,                              "maskmovdqu\t" OP_RM128_XMM OP_RXMM),  /*             66 0F F7 /R MASKMOVDQU XMM1, XMM2 */

	I(0xf0, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 1, 0, 0) "vlddqu\t" OP_MEM OP_RXMM), /* VEX.128.F2.0F.WIG F0 /R VLDDQU XMM1, M128 */
	I(0xf0, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 1, 0, 1) "vlddqu\t" OP_MEM OP_RYMM), /* VEX.256.F2.0F.WIG F0 /R VLDDQU YMM1, M256 */
	I(0xf0, IF_F2|IF_MODRM|IF_RMM,                              "lddqu\t" OP_MEM OP_RXMM),  /*             F2 0F F0 /R LDDQU XMM1, MEM */

	I(0x4b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "/is4 vblendvpd " OP_RM128_XMM__OP_VRXMM__OP_RXMM ", xmm4"), /* VEX.128.66.0F3A.W0 4B /R /IS4 VBLENDVPD XMM1, XMM2, XMM3/M128, XMM4 */
	I(0x4b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "/is4 vblendvpd " OP_RM256_YMM__OP_VRYMM__OP_RYMM ", ymm4"), /* VEX.256.66.0F3A.W0 4B /R /IS4 VBLENDVPD YMM1, YMM2, YMM3/M256, YMM4 */
	I(0x15, IF_66|IF_MODRM,                              "blendvpd\t" OP_XMM0 OP_RM128_XMM OP_RXMM),                  /*           66 0F 38 15 /R      BLENDVPD XMM1, XMM2/M128, <XMM0> */

	I(0x4a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "/is4 vblendvps " OP_RM128_XMM__OP_VRXMM__OP_RXMM ", xmm4"), /* VEX.128.66.0F3A.W0 4A /R /IS4 VBLENDVPS XMM1, XMM2, XMM3/M128, XMM4 */
	I(0x4a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "/is4 vblendvps " OP_RM256_YMM__OP_VRYMM__OP_RYMM ", ymm4"), /* VEX.256.66.0F3A.W0 4A /R /IS4 VBLENDVPS YMM1, YMM2, YMM3/M256, YMM4 */
	I(0x14, IF_66|IF_MODRM,                              "blendvps\t" OP_XMM0 OP_RM128_XMM OP_RXMM),                  /*           66 0F 38 14 /R      BLENDVPS XMM1, XMM2/M128, <XMM0> */

	I(0x17, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vextractps\t" OP_U8 OP_RXMM OP_RM32), /* EVEX.128.66.0F3A.WIG 17 /R IB VEXTRACTPS R/M32, XMM1, IMM8 */
	I(0x17, IF_66|IF_MODRM,                              "extractps\t" OP_U8 OP_RXMM OP_RM32),  /*             66 0F 3A 17 /R IB EXTRACTPS R/M32, XMM1, IMM8 */

	I(0x4c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "/is4 vpblendvb " OP_RM128_XMM__OP_VRXMM__OP_RXMM ", xmm4"), /* VEX.128.66.0F3A.W0 4C /R /IS4 VPBLENDVB XMM1, XMM2, XMM3/M128, XMM4 */
	I(0x4c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "/is4 vpblendvb " OP_RM256_YMM__OP_VRYMM__OP_RYMM ", ymm4"), /* VEX.256.66.0F3A.W0 4C /R /IS4 VPBLENDVB YMM1, YMM2, YMM3/M256, YMM4 */
	I(0x10, IF_66|IF_MODRM,                              "pblendvb\t" OP_XMM0 OP_RM128_XMM OP_RXMM),                  /*           66 0F 38 10 /R      PBLENDVB XMM1, XMM2/M128, <XMM0> */

	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpcmpeqq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),  /*  VEX.128.66.0F38.WIG 29 /R VPCMPEQQ XMM1, XMM2, XMM3/M128 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpcmpeqq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),  /*  VEX.256.66.0F38.WIG 29 /R VPCMPEQQ YMM1, YMM2, YMM3 /M256 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpcmpeqq\t" OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0F38.W1  29 /R VPCMPEQQ K1{K2}, XMM2, XMM3/M128/M64BCST */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpcmpeqq\t" OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0F38.W1  29 /R VPCMPEQQ K1{K2}, YMM2, YMM3/M256/M64BCST */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpcmpeqq\t" OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F38.W1  29 /R VPCMPEQQ K1{K2}, ZMM2, ZMM3/M512/M64BCST */
	I(0x29, IF_66|IF_MODRM,                              "pcmpeqq\t" OP_RM128_XMM OP_RXMM),              /*             66 0F 38 29 /R PCMPEQQ XMM1, XMM2/M128 */

	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 0) "vpextrb\t" OP_U8 OP_RXMM OP_RM8),  /*  VEX.128.66.0F3A.W0  14 /R IB VPEXTRB R/M8, XMM2, IMM8 */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpextrb\t" OP_U8 OP_RXMM OP_RM8),  /* EVEX.128.66.0F3A.WIG 14 /R IB VPEXTRB R/M8, XMM2, IMM8 */
	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpextrd\t" OP_U8 OP_RXMM OP_RM32), /* EVEX.128.66.0F3A.W0  16 /R IB VPEXTRD R32/M32, XMM2, IMM8 */
	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpextrq\t" OP_U8 OP_RXMM OP_RM64), /* EVEX.128.66.0F3A.W1  16 /R IB VPEXTRQ R64/M64, XMM2, IMM8 */
	I(0x14, IF_66|IF_MODRM,                              "pextrb\t" OP_U8 OP_RXMM OP_RM8),   /*       66       0F 3A 14 /R IB PEXTRB R/M8, XMM2, IMM8 */
	I(0x16, IF_66|IF_MODRM,                              "pextrd\t" OP_U8 OP_RXMM OP_RM32),  /*       66       0F 3A 16 /R IB PEXTRD R/M32, XMM2, IMM8 */
	I(0x16, IF_66|IF_MODRM,                              "pextrq\t" OP_U8 OP_RXMM OP_RM64),  /*       66 REX.W 0F 3A 16 /R IB PEXTRQ R/M64, XMM2, IMM8 */

	I(0x20, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 0) "vpinsrb\t" OP_U8 OP_RM8 OP_VRXMM OP_RXMM),  /*  VEX.128.66.0F3A.W0  20 /R IB VPINSRB XMM1, XMM2, R32/M8, IMM8 */
	I(0x20, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpinsrb\t" OP_U8 OP_RM8 OP_VRXMM OP_RXMM),  /* EVEX.128.66.0F3A.WIG 20 /R IB VPINSRB XMM1, XMM2, R32/M8, IMM8 */
	I(0x22, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpinsrd\t" OP_U8 OP_RM32 OP_VRXMM OP_RXMM), /* EVEX.128.66.0F3A.W0  22 /R IB VPINSRD XMM1, XMM2, R32/M32, IMM8 */
	I(0x22, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpinsrq\t" OP_U8 OP_RM64 OP_VRXMM OP_RXMM), /* EVEX.128.66.0F3A.W1  22 /R IB VPINSRQ XMM1, XMM2, R64/M64, IMM8 */
	I(0x20, IF_66|IF_MODRM,                              "pinsrb\t" OP_U8 OP_RM8 OP_RXMM),            /*       66       0F 3A 20 /R IB PINSRB XMM1, R32/M8, IMM8 */
	I(0x22, IF_66|IF_MODRM,                              "pinsrd\t" OP_U8 OP_RM32 OP_RXMM),           /*       66       0F 3A 22 /R IB PINSRD XMM1, R/M32, IMM8 */
	I(0x22, IF_66|IF_MODRM,                              "pinsrq\t" OP_U8 OP_RM64 OP_RXMM),           /*       66 REX.W 0F 3A 22 /R IB PINSRQ XMM1, R/M64, IMM8 */

	I(0x37, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpcmpgtq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),  /*  VEX.128.66.0F38.WIG 37 /R VPCMPGTQ XMM1, XMM2, XMM3/M128 */
	I(0x37, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpcmpgtq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),  /*  VEX.256.66.0F38.WIG 37 /R VPCMPGTQ YMM1, YMM2, YMM3/M256 */
	I(0x37, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpcmpgtq\t" OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0F38.W1  37 /R VPCMPGTQ K1{K2}, XMM2, XMM3/M128/M64BCST */
	I(0x37, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpcmpgtq\t" OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0F38.W1  37 /R VPCMPGTQ K1{K2}, YMM2, YMM3/M256/M64BCST */
	I(0x37, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpcmpgtq\t" OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F38.W1  37 /R VPCMPGTQ K1{K2}, ZMM2, ZMM3/M512/M64BCST */
	I(0x37, IF_66|IF_MODRM,                              "pcmpgtq\t" OP_RM128_XMM OP_RXMM),              /*             66 0F 38 37 /R PCMPGTQ XMM1, XMM2/M128 */

	I(0x19, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 1) "vextractf128\t" OP_U8 OP_RYMM OP_RM128_XMM),       /*  VEX.256.66.0F3A.W0 19 /R IB VEXTRACTF128 XMM1/M128, YMM2, IMM8 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vextractf32x4\t" OP_U8 OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.66.0F3A.W0 19 /R IB VEXTRACTF32X4 XMM1/M128{K1}{Z}, YMM2, IMM8 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vextractf32x4\t" OP_U8 OP_RZMM OP_RM128_XMM_MASK), /* EVEX.512.66.0F3A.W0 19 /R IB VEXTRACTF32X4 XMM1/M128{K1}{Z}, ZMM2, IMM8 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vextractf64x2\t" OP_U8 OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.66.0F3A.W1 19 /R IB VEXTRACTF64X2 XMM1/M128{K1}{Z}, YMM2, IMM8 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vextractf64x2\t" OP_U8 OP_RZMM OP_RM128_XMM_MASK), /* EVEX.512.66.0F3A.W1 19 /R IB VEXTRACTF64X2 XMM1/M128{K1}{Z}, ZMM2, IMM8 */
	I(0x1b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vextractf32x8\t" OP_U8 OP_RZMM OP_RM256_YMM_MASK), /* EVEX.512.66.0F3A.W0 1B /R IB VEXTRACTF32X8 YMM1/M256{K1}{Z}, ZMM2, IMM8 */
	I(0x1b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vextractf64x4\t" OP_U8 OP_RZMM OP_RM256_YMM_MASK), /* EVEX.512.66.0F3A.W1 1B /R IB VEXTRACTF64X4 YMM1/M256{K1}{Z}, ZMM2, IMM8 */

	I(0x18, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 0) "vbroadcastss\t" OP_RM128_XMM OP_RXMM_MASK),    /*  VEX.128.66.0F38.W0 18 /R VBROADCASTSS XMM1, XMM2/M32 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 1) "vbroadcastss\t" OP_RM128_XMM OP_RYMM_MASK),    /*  VEX.256.66.0F38.W0 18 /R VBROADCASTSS YMM1, XMM2/M32 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vbroadcastss\t" OP_RM128_XMM OP_RXMM_MASK),    /* EVEX.128.66.0F38.W0 18 /R VBROADCASTSS XMM1{K1}{Z}, XMM2/M32 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vbroadcastss\t" OP_RM128_XMM OP_RYMM_MASK),    /* EVEX.256.66.0F38.W0 18 /R VBROADCASTSS YMM1{K1}{Z}, XMM2/M32 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vbroadcastss\t" OP_RM128_XMM OP_RZMM_MASK),    /* EVEX.512.66.0F38.W0 18 /R VBROADCASTSS ZMM1{K1}{Z}, XMM2/M32 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 1) "vbroadcastsd\t" OP_RM128_XMM OP_RYMM),         /*  VEX.256.66.0F38.W0 19 /R VBROADCASTSD YMM1, XMM2 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vbroadcastsd\t" OP_RM256_YMM OP_RYMM_MASK),    /* EVEX.256.66.0F38.W1 19 /R VBROADCASTSD YMM1{K1}{Z}, XMM2/M64 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vbroadcastsd\t" OP_RM128_XMM OP_RZMM_MASK),    /* EVEX.512.66.0F38.W1 19 /R VBROADCASTSD ZMM1{K1}{Z}, XMM2/M64 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vbroadcastf32x2\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 19 /R VBROADCASTF32X2 YMM1{K1}{Z}, XMM2/M64 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vbroadcastf32x2\t" OP_RM128_XMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 19 /R VBROADCASTF32X2 ZMM1{K1}{Z}, XMM2/M64 */

	I(0x1a, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 0, 0, 1) "vbroadcastf128\t" OP_MEM OP_RYMM),       /*  VEX.256.66.0F38.W0 1A /R VBROADCASTF128 YMM1, M128 */
	I(0x1a, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vbroadcastf32x4\t" OP_MEM OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 1A /R VBROADCASTF32X4 YMM1{K1}{Z}, M128 */
	I(0x1a, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 2) "vbroadcastf32x4\t" OP_MEM OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 1A /R VBROADCASTF32X4 ZMM1{K1}{Z}, M128 */
	I(0x1a, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 1) "vbroadcastf64x2\t" OP_MEM OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 1A /R VBROADCASTF64X2 YMM1{K1}{Z}, M128 */
	I(0x1a, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 2) "vbroadcastf64x2\t" OP_MEM OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 1A /R VBROADCASTF64X2 ZMM1{K1}{Z}, M128 */
	I(0x1b, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 2) "vbroadcastf32x8\t" OP_MEM OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 1B /R VBROADCASTF32X8 ZMM1{K1}{Z}, M256 */
	I(0x1b, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 2) "vbroadcastf64x4\t" OP_MEM OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 1B /R VBROADCASTF64X4 ZMM1{K1}{Z}, M256 */

	I(0x2c, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmaskmovps\t" OP_MEM OP_VRXMM OP_RXMM), /* VEX.128.66.0F38.W0 2C /R VMASKMOVPS XMM1, XMM2, M128 */
	I(0x2c, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vmaskmovps\t" OP_MEM OP_VRYMM OP_RYMM), /* VEX.256.66.0F38.W0 2C /R VMASKMOVPS YMM1, YMM2, M256 */
	I(0x2d, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmaskmovpd\t" OP_MEM OP_VRXMM OP_RXMM), /* VEX.128.66.0F38.W0 2D /R VMASKMOVPD XMM1, XMM2, M128 */
	I(0x2d, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vmaskmovpd\t" OP_MEM OP_VRYMM OP_RYMM), /* VEX.256.66.0F38.W0 2D /R VMASKMOVPD YMM1, YMM2, M256 */
	I(0x2e, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmaskmovps\t" OP_RXMM OP_VRXMM OP_MEM), /* VEX.128.66.0F38.W0 2E /R VMASKMOVPS M128, XMM1, XMM2 */
	I(0x2e, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vmaskmovps\t" OP_RYMM OP_VRYMM OP_MEM), /* VEX.256.66.0F38.W0 2E /R VMASKMOVPS M256, YMM1, YMM2 */
	I(0x2f, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmaskmovpd\t" OP_RXMM OP_VRXMM OP_MEM), /* VEX.128.66.0F38.W0 2F /R VMASKMOVPD M128, XMM1, XMM2 */
	I(0x2f, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vmaskmovpd\t" OP_RYMM OP_VRYMM OP_MEM), /* VEX.256.66.0F38.W0 2F /R VMASKMOVPD M256, YMM1, YMM2 */

	I(0x6e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovd\t" OP_RM32 OP_RXMM), /* EVEX.128.66.0F.W0 6E /R VMOVD XMM1, R32/M32 */
	I(0x6e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovq\t" OP_RM64 OP_RXMM), /* EVEX.128.66.0F.W1 6E /R VMOVQ XMM1, R64/M64 */
	I(0x7e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovd\t" OP_RXMM OP_RM32), /* EVEX.128.66.0F.W0 7E /R VMOVD R32/M32, XMM1 */
	I(0x7e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovq\t" OP_RXMM OP_RM64), /* EVEX.128.66.0F.W1 7E /R VMOVQ R64/M64, XMM1 */
	I(0x6e, IF_MODRM,                                    "movd\t" OP_RM32 OP_RMM),   /*                0F 6E /R MOVD MM, R/M32 */
	I(0x6e, IF_MODRM,                                    "movq\t" OP_RM64 OP_RMM),   /*        REX.W + 0F 6E /R MOVQ MM, R/M64 */
	I(0x7e, IF_MODRM,                                    "movd\t" OP_RMM OP_RM32),   /*                0F 7E /R MOVD R/M32, MM */
	I(0x7e, IF_MODRM,                                    "movq\t" OP_RMM OP_RM64),   /*        REX.W + 0F 7E /R MOVQ R/M64, MM */
	I(0x6e, IF_66|IF_MODRM,                              "movd\t" OP_RM32 OP_RXMM),  /*     66         0F 6E /R MOVD XMM, R/M32 */
	I(0x6e, IF_66|IF_MODRM|IF_REXW,                      "movq\t" OP_RM64 OP_RXMM),  /*     66 REX.W + 0F 6E /R MOVQ XMM, R/M64 */
	I(0x7e, IF_66|IF_MODRM,                              "movd\t" OP_RXMM OP_RM32),  /*     66         0F 7E /R MOVD R/M32, XMM */
	I(0x7e, IF_66|IF_MODRM|IF_REXW,                      "movq\t" OP_RXMM OP_RM64),  /*     66 REX.W + 0F 7E /R MOVQ R/M64, XMM */

	I(0x7a, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpbroadcastb\t" OP_RM8 OP_RXMM_MASK),  /* EVEX.128.66.0F38.W0 7A /R VPBROADCASTB XMM1{K1}{Z}, R8 */
	I(0x7a, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpbroadcastb\t" OP_RM8 OP_RYMM_MASK),  /* EVEX.256.66.0F38.W0 7A /R VPBROADCASTB YMM1{K1}{Z}, R8 */
	I(0x7a, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpbroadcastb\t" OP_RM8 OP_RZMM_MASK),  /* EVEX.512.66.0F38.W0 7A /R VPBROADCASTB ZMM1{K1}{Z}, R8 */
	I(0x7b, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpbroadcastw\t" OP_RM16 OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 7B /R VPBROADCASTW XMM1{K1}{Z}, R16 */
	I(0x7b, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpbroadcastw\t" OP_RM16 OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 7B /R VPBROADCASTW YMM1{K1}{Z}, R16 */
	I(0x7b, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpbroadcastw\t" OP_RM16 OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 7B /R VPBROADCASTW ZMM1{K1}{Z}, R16 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpbroadcastd\t" OP_RM32 OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 7C /R VPBROADCASTD XMM1{K1}{Z}, R32 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpbroadcastd\t" OP_RM32 OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 7C /R VPBROADCASTD YMM1{K1}{Z}, R32 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpbroadcastd\t" OP_RM32 OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 7C /R VPBROADCASTD ZMM1{K1}{Z}, R32 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "vpbroadcastq\t" OP_RM64 OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 7C /R VPBROADCASTQ XMM1{K1}{Z}, R64 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "vpbroadcastq\t" OP_RM64 OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 7C /R VPBROADCASTQ YMM1{K1}{Z}, R64 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 2) "vpbroadcastq\t" OP_RM64 OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 7C /R VPBROADCASTQ ZMM1{K1}{Z}, R64 */

	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 1) "vextracti128\t" OP_U8 OP_RYMM OP_RM128_XMM),       /*  VEX.256.66.0F3A.W0 39 /R IB VEXTRACTI128 XMM1/M128, YMM2, IMM8 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vextracti32x4\t" OP_U8 OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.66.0F3A.W0 39 /R IB VEXTRACTI32X4 XMM1/M128{K1}{Z}, YMM2, IMM8 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vextracti32x4\t" OP_U8 OP_RZMM OP_RM128_XMM_MASK), /* EVEX.512.66.0F3A.W0 39 /R IB VEXTRACTI32X4 XMM1/M128{K1}{Z}, ZMM2, IMM8 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vextracti64x2\t" OP_U8 OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.66.0F3A.W1 39 /R IB VEXTRACTI64X2 XMM1/M128{K1}{Z}, YMM2, IMM8 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vextracti64x2\t" OP_U8 OP_RZMM OP_RM128_XMM_MASK), /* EVEX.512.66.0F3A.W1 39 /R IB VEXTRACTI64X2 XMM1/M128{K1}{Z}, ZMM2, IMM8 */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vextracti32x8\t" OP_U8 OP_RZMM OP_RM256_YMM_MASK), /* EVEX.512.66.0F3A.W0 3B /R IB VEXTRACTI32X8 YMM1/M256{K1}{Z}, ZMM2, IMM8 */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vextracti64x4\t" OP_U8 OP_RZMM OP_RM256_YMM_MASK), /* EVEX.512.66.0F3A.W1 3B /R IB VEXTRACTI64X4 YMM1/M256{K1}{Z}, ZMM2, IMM8 */

	I(0x8c, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vpmaskmovd\t" OP_MEM OP_VRXMM OP_RXMM), /* VEX.128.66.0F38.W0 8C /R VPMASKMOVD XMM1, XMM2, M128 */
	I(0x8c, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vpmaskmovd\t" OP_MEM OP_VRYMM OP_RYMM), /* VEX.256.66.0F38.W0 8C /R VPMASKMOVD YMM1, YMM2, M256 */
	I(0x8c, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "vpmaskmovq\t" OP_MEM OP_VRXMM OP_RXMM), /* VEX.128.66.0F38.W1 8C /R VPMASKMOVQ XMM1, XMM2, M128 */
	I(0x8c, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 1) "vpmaskmovq\t" OP_MEM OP_VRYMM OP_RYMM), /* VEX.256.66.0F38.W1 8C /R VPMASKMOVQ YMM1, YMM2, M256 */
	I(0x8e, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vpmaskmovd\t" OP_RXMM OP_VRXMM OP_MEM), /* VEX.128.66.0F38.W0 8E /R VPMASKMOVD M128, XMM1, XMM2 */
	I(0x8e, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vpmaskmovd\t" OP_RYMM OP_VRYMM OP_MEM), /* VEX.256.66.0F38.W0 8E /R VPMASKMOVD M256, YMM1, YMM2 */
	I(0x8e, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "vpmaskmovq\t" OP_RXMM OP_VRXMM OP_MEM), /* VEX.128.66.0F38.W1 8E /R VPMASKMOVQ M128, XMM1, XMM2 */
	I(0x8e, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 1) "vpmaskmovq\t" OP_RYMM OP_VRYMM OP_MEM), /* VEX.256.66.0F38.W1 8E /R VPMASKMOVQ M256, YMM1, YMM2 */

	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vgatherdpd\txmm, vm32x, xmm2"), /* VEX.128.66.0F38.W1 92 /R VGATHERDPD XMM1, VM32X, XMM2 */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vgatherdpd\tymm, vm32x, ymm"),  /* VEX.256.66.0F38.W1 92 /R VGATHERDPD YMM1, VM32X, YMM2 */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vgatherqpd\txmm, vm64x, xmm2"), /* VEX.128.66.0F38.W1 93 /R VGATHERQPD XMM1, VM64X, XMM2 */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vgatherqpd\tymm, vm64y, ymm"),  /* VEX.256.66.0F38.W1 93 /R VGATHERQPD YMM1, VM64Y, YMM2 */

	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vgatherdps\txmm{k1}, vm32x"),  /* EVEX.128.66.0F38.W0 92 /VSIB VGATHERDPS XMM1{K1}, VM32X */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vgatherdps\tymm1{k1}, vm32y"), /* EVEX.256.66.0F38.W0 92 /VSIB VGATHERDPS YMM1{K1}, VM32Y */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vgatherdps\tzmm1{k1}, vm32z"), /* EVEX.512.66.0F38.W0 92 /VSIB VGATHERDPS ZMM1{K1}, VM32Z */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vgatherdpd\txmm{k1}, vm32x"),  /* EVEX.128.66.0F38.W1 92 /VSIB VGATHERDPD XMM1{K1}, VM32X */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vgatherdpd\tymm1{k1}, vm32x"), /* EVEX.256.66.0F38.W1 92 /VSIB VGATHERDPD YMM1{K1}, VM32X */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vgatherdpd\tzmm1{k1}, vm32y"), /* EVEX.512.66.0F38.W1 92 /VSIB VGATHERDPD ZMM1{K1}, VM32Y */

	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vgatherdps\txmm, vm32x, xmm2"), /* VEX.128.66.0F38.W0 92 /R VGATHERDPS XMM1, VM32X, XMM2 */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vgatherdps\tymm, vm32y, ymm"),  /* VEX.256.66.0F38.W0 92 /R VGATHERDPS YMM1, VM32Y, YMM2 */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vgatherqps\txmm, vm64x, xmm2"), /* VEX.128.66.0F38.W0 93 /R VGATHERQPS XMM1, VM64X, XMM2 */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vgatherqps\txmm, vm64y, xmm2"), /* VEX.256.66.0F38.W0 93 /R VGATHERQPS XMM1, VM64Y, XMM2 */

	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vgatherqps\txmm{k1}, vm64x"),  /* EVEX.128.66.0F38.W0 93 /VSIB VGATHERQPS XMM1{K1}, VM64X */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vgatherqps\txmm{k1}, vm64y"),  /* EVEX.256.66.0F38.W0 93 /VSIB VGATHERQPS XMM1{K1}, VM64Y */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vgatherqps\tymm1{k1}, vm64z"), /* EVEX.512.66.0F38.W0 93 /VSIB VGATHERQPS YMM1{K1}, VM64Z */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vgatherqpd\txmm{k1}, vm64x"),  /* EVEX.128.66.0F38.W1 93 /VSIB VGATHERQPD XMM1{K1}, VM64X */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vgatherqpd\tymm1{k1}, vm64y"), /* EVEX.256.66.0F38.W1 93 /VSIB VGATHERQPD YMM1{K1}, VM64Y */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vgatherqpd\tzmm1{k1}, vm64z"), /* EVEX.512.66.0F38.W1 93 /VSIB VGATHERQPD ZMM1{K1}, VM64Z */

	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpgatherdd\txmm, vm32x, xmm2"), /* VEX.128.66.0F38.W0 90 /R VPGATHERDD XMM1, VM32X, XMM2 */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpgatherdd\tymm, vm32y, ymm"),  /* VEX.256.66.0F38.W0 90 /R VPGATHERDD YMM1, VM32Y, YMM2 */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpgatherqd\txmm, vm64x, xmm2"), /* VEX.128.66.0F38.W0 91 /R VPGATHERQD XMM1, VM64X, XMM2 */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpgatherqd\txmm, vm64y, xmm2"), /* VEX.256.66.0F38.W0 91 /R VPGATHERQD XMM1, VM64Y, XMM2 */

	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpgatherdd\txmm{k1}, vm32x"),  /* EVEX.128.66.0F38.W0 90 /VSIB VPGATHERDD XMM1{K1}, VM32X */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpgatherdd\tymm1{k1}, vm32y"), /* EVEX.256.66.0F38.W0 90 /VSIB VPGATHERDD YMM1{K1}, VM32Y */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpgatherdd\tzmm1{k1}, vm32z"), /* EVEX.512.66.0F38.W0 90 /VSIB VPGATHERDD ZMM1{K1}, VM32Z */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpgatherdq\txmm{k1}, vm32x"),  /* EVEX.128.66.0F38.W1 90 /VSIB VPGATHERDQ XMM1{K1}, VM32X */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpgatherdq\tymm1{k1}, vm32x"), /* EVEX.256.66.0F38.W1 90 /VSIB VPGATHERDQ YMM1{K1}, VM32X */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpgatherdq\tzmm1{k1}, vm32y"), /* EVEX.512.66.0F38.W1 90 /VSIB VPGATHERDQ ZMM1{K1}, VM32Y */

	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpgatherqd\txmm{k1}, vm64x"),  /* EVEX.128.66.0F38.W0 91 /VSIB VPGATHERQD XMM1{K1}, VM64X */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpgatherqd\txmm{k1}, vm64y"),  /* EVEX.256.66.0F38.W0 91 /VSIB VPGATHERQD XMM1{K1}, VM64Y */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpgatherqd\tymm1{k1}, vm64z"), /* EVEX.512.66.0F38.W0 91 /VSIB VPGATHERQD YMM1{K1}, VM64Z */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpgatherqq\txmm{k1}, vm64x"),  /* EVEX.128.66.0F38.W1 91 /VSIB VPGATHERQQ XMM1{K1}, VM64X */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpgatherqq\tymm1{k1}, vm64y"), /* EVEX.256.66.0F38.W1 91 /VSIB VPGATHERQQ YMM1{K1}, VM64Y */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpgatherqq\tzmm1{k1}, vm64z"), /* EVEX.512.66.0F38.W1 91 /VSIB VPGATHERQQ ZMM1{K1}, VM64Z */

	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpgatherdq\txmm, vm32x, xmm2"), /* VEX.128.66.0F38.W1 90 /R VPGATHERDQ XMM1, VM32X, XMM2 */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpgatherdq\tymm, vm32x, ymm"),  /* VEX.256.66.0F38.W1 90 /R VPGATHERDQ YMM1, VM32X, YMM2 */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpgatherqq\txmm, vm64x, xmm2"), /* VEX.128.66.0F38.W1 91 /R VPGATHERQQ XMM1, VM64X, XMM2 */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpgatherqq\tymm, vm64y, ymm"),  /* VEX.256.66.0F38.W1 91 /R VPGATHERQQ YMM1, VM64Y, YMM2 */

	I(0x13, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvtph2ps\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F38.W0 13 /R VCVTPH2PS XMM1{K1}{Z}, XMM2/M64 */
	I(0x13, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvtph2ps\t" OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F38.W0 13 /R VCVTPH2PS YMM1{K1}{Z}, XMM2/M128 */
	I(0x13, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvtph2ps\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F38.W0 13 /R VCVTPH2PS ZMM1{K1}{Z}, YMM2/M256{SAE} */

	I(0x1d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvtps2ph\t" OP_U8 OP_RXMM OP_RM128_XMM_MASK),         /* EVEX.128.66.0F3A.W0 1D /R IB VCVTPS2PH XMM1/M64{K1}{Z}, XMM2, IMM8 */
	I(0x1d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvtps2ph\t" OP_U8 OP_RYMM OP_RM128_XMM_MASK),         /* EVEX.256.66.0F3A.W0 1D /R IB VCVTPS2PH XMM1/M128{K1}{Z}, YMM2, IMM8 */
	I(0x1d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvtps2ph\t" OP_U8 OP_RZMM "{sae}" OP_RM256_YMM_MASK), /* EVEX.512.66.0F3A.W0 1D /R IB VCVTPS2PH YMM1/M256{K1}{Z}, ZMM2{SAE}, IMM8 */

	I(0x98, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmadd132pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 98 /R VFMADD132PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmadd213pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 A8 /R VFMADD213PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmadd231pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 B8 /R VFMADD231PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x98, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmadd132pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 98 /R VFMADD132PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmadd213pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 A8 /R VFMADD213PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmadd231pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 B8 /R VFMADD231PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x98, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmadd132pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 98 /R VFMADD132PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmadd213pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 A8 /R VFMADD213PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmadd231pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 B8 /R VFMADD231PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */

	I(0x98, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmadd132ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 98 /R VFMADD132PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmadd213ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 A8 /R VFMADD213PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmadd231ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 B8 /R VFMADD231PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x98, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmadd132ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 98 /R VFMADD132PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmadd213ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 A8 /R VFMADD213PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmadd231ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 B8 /R VFMADD231PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x98, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmadd132ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 98 /R VFMADD132PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmadd213ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 A8 /R VFMADD213PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmadd231ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 B8 /R VFMADD231PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */

	I(0x99, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vfmadd132sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W1 99 /R VFMADD132SD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */
	I(0xa9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vfmadd213sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W1 A9 /R VFMADD213SD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */
	I(0xb9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vfmadd231sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W1 B9 /R VFMADD231SD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */

	I(0x99, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vfmadd132ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W0 99 /R VFMADD132SS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */
	I(0xa9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vfmadd213ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W0 A9 /R VFMADD213SS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */
	I(0xb9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vfmadd231ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W0 B9 /R VFMADD231SS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */

	I(0x96, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmaddsub132pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 96 /R VFMADDSUB132PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x96, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmaddsub132pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 96 /R VFMADDSUB132PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x96, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmaddsub132pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 96 /R VFMADDSUB132PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmaddsub213pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 A6 /R VFMADDSUB213PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmaddsub213pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 A6 /R VFMADDSUB213PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmaddsub213pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 A6 /R VFMADDSUB213PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmaddsub231pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 B6 /R VFMADDSUB231PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmaddsub231pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 B6 /R VFMADDSUB231PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmaddsub231pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 B6 /R VFMADDSUB231PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */

	I(0x96, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmaddsub132ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 96 /R VFMADDSUB132PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x96, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmaddsub132ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 96 /R VFMADDSUB132PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x96, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmaddsub132ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 96 /R VFMADDSUB132PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmaddsub213ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 A6 /R VFMADDSUB213PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmaddsub213ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 A6 /R VFMADDSUB213PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmaddsub213ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 A6 /R VFMADDSUB213PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmaddsub231ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 B6 /R VFMADDSUB231PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmaddsub231ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 B6 /R VFMADDSUB231PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmaddsub231ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 B6 /R VFMADDSUB231PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */

	I(0x97, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmsubadd132pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 97 /R VFMSUBADD132PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x97, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmsubadd132pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 97 /R VFMSUBADD132PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x97, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmsubadd132pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 97 /R VFMSUBADD132PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmsubadd213pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 A7 /R VFMSUBADD213PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmsubadd213pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 A7 /R VFMSUBADD213PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmsubadd213pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 A7 /R VFMSUBADD213PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmsubadd231pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 B7 /R VFMSUBADD231PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmsubadd231pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 B7 /R VFMSUBADD231PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmsubadd231pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 B7 /R VFMSUBADD231PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */

	I(0x97, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmsubadd132ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 97 /R VFMSUBADD132PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x97, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmsubadd132ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 97 /R VFMSUBADD132PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x97, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmsubadd132ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 97 /R VFMSUBADD132PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmsubadd213ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 A7 /R VFMSUBADD213PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmsubadd213ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 A7 /R VFMSUBADD213PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmsubadd213ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 A7 /R VFMSUBADD213PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmsubadd231ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 B7 /R VFMSUBADD231PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmsubadd231ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 B7 /R VFMSUBADD231PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmsubadd231ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 B7 /R VFMSUBADD231PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */

	I(0x9a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmsub132pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 9A /R VFMSUB132PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x9a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmsub132pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 9A /R VFMSUB132PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x9a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmsub132pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 9A /R VFMSUB132PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmsub213pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 AA /R VFMSUB213PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmsub213pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 AA /R VFMSUB213PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmsub213pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 AA /R VFMSUB213PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */
	I(0xba, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfmsub231pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 BA /R VFMSUB231PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0xba, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfmsub231pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 BA /R VFMSUB231PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0xba, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfmsub231pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 BA /R VFMSUB231PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */

	I(0x9a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmsub132ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 9A /R VFMSUB132PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x9a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmsub132ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 9A /R VFMSUB132PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x9a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmsub132ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 9A /R VFMSUB132PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmsub213ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 AA /R VFMSUB213PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmsub213ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 AA /R VFMSUB213PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmsub213ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 AA /R VFMSUB213PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */
	I(0xba, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfmsub231ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 BA /R VFMSUB231PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0xba, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfmsub231ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 BA /R VFMSUB231PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0xba, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfmsub231ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 BA /R VFMSUB231PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */

	I(0x9b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vfmsub132sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W1 9B /R VFMSUB132SD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */
	I(0xab, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vfmsub213sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W1 AB /R VFMSUB213SD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */
	I(0xbb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vfmsub231sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W1 BB /R VFMSUB231SD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */

	I(0x9b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vfmsub132ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W0 9B /R VFMSUB132SS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */
	I(0xab, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vfmsub213ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W0 AB /R VFMSUB213SS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */
	I(0xbb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vfmsub231ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W0 BB /R VFMSUB231SS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */



	I(0x03, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "valignd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F3A.W0 03 /R IB VALIGND XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST, IMM8 */
	I(0x03, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "valignq\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F3A.W1 03 /R IB VALIGNQ XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST, IMM8 */
	I(0x03, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "valignd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F3A.W0 03 /R IB VALIGND YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST, IMM8 */
	I(0x03, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "valignq\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F3A.W1 03 /R IB VALIGNQ YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST, IMM8 */
	I(0x03, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "valignd\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F3A.W0 03 /R IB VALIGND ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST, IMM8 */
	I(0x03, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "valignq\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F3A.W1 03 /R IB VALIGNQ ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST, IMM8 */

	I(0x65, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vblendmpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 65 /R VBLENDMPD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x65, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vblendmpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 65 /R VBLENDMPD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x65, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vblendmpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 65 /R VBLENDMPD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */
	I(0x65, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vblendmps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 65 /R VBLENDMPS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x65, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vblendmps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 65 /R VBLENDMPS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x65, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vblendmps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 65 /R VBLENDMPS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST */

	I(0x8a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcompresspd\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.66.0F38.W1 8A /R VCOMPRESSPD XMM1/M128{K1}{Z}, XMM2 */
	I(0x8a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcompresspd\t" OP_RYMM OP_RM256_YMM_MASK), /* EVEX.256.66.0F38.W1 8A /R VCOMPRESSPD YMM1/M256{K1}{Z}, YMM2 */
	I(0x8a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcompresspd\t" OP_RZMM OP_RM512_ZMM_MASK), /* EVEX.512.66.0F38.W1 8A /R VCOMPRESSPD ZMM1/M512{K1}{Z}, ZMM2 */

	I(0x8a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcompressps\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.66.0F38.W0 8A /R VCOMPRESSPS XMM1/M128{K1}{Z}, XMM2 */
	I(0x8a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcompressps\t" OP_RYMM OP_RM256_YMM_MASK), /* EVEX.256.66.0F38.W0 8A /R VCOMPRESSPS YMM1/M256{K1}{Z}, YMM2 */
	I(0x8a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcompressps\t" OP_RZMM OP_RM512_ZMM_MASK), /* EVEX.512.66.0F38.W0 8A /R VCOMPRESSPS ZMM1/M512{K1}{Z}, ZMM2 */

	I(0x7b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvtpd2qq\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.66.0F.W1 7B /R VCVTPD2QQ XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x7b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvtpd2qq\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.66.0F.W1 7B /R VCVTPD2QQ YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x7b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvtpd2qq\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.66.0F.W1 7B /R VCVTPD2QQ ZMM1{K1}{Z}, ZMM2/M512/M64BCST{ER} */

	I(0x79, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvtpd2udq\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.0F.W1 79 /R VCVTPD2UDQ XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x79, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvtpd2udq\t" OP_RM256_YMM OP_RXMM_MASK),        /* EVEX.256.0F.W1 79 /R VCVTPD2UDQ XMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x79, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvtpd2udq\t" OP_RM512_ZMM "{er}" OP_RYMM_MASK), /* EVEX.512.0F.W1 79 /R VCVTPD2UDQ YMM1{K1}{Z}, ZMM2/M512/M64BCST{ER} */

	I(0x79, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvtpd2uqq\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.66.0F.W1 79 /R VCVTPD2UQQ XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x79, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvtpd2uqq\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.66.0F.W1 79 /R VCVTPD2UQQ YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x79, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvtpd2uqq\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.66.0F.W1 79 /R VCVTPD2UQQ ZMM1{K1}{Z}, ZMM2/M512/M64BCST{ER} */

	I(0x7b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvtps2qq\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.66.0F.W0 7B /R VCVTPS2QQ XMM1{K1}{Z}, XMM2/M64/M32BCST */
	I(0x7b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvtps2qq\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.66.0F.W0 7B /R VCVTPS2QQ YMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x7b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvtps2qq\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.66.0F.W0 7B /R VCVTPS2QQ ZMM1{K1}{Z}, YMM2/M256/M32BCST{ER} */

	I(0x79, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvtps2udq\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.0F.W0 79 /R VCVTPS2UDQ XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x79, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvtps2udq\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.0F.W0 79 /R VCVTPS2UDQ YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x79, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvtps2udq\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.0F.W0 79 /R VCVTPS2UDQ ZMM1{K1}{Z}, ZMM2/M512/M32BCST{ER} */

	I(0x79, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvtps2uqq\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.66.0F.W0 79 /R VCVTPS2UQQ XMM1{K1}{Z}, XMM2/M64/M32BCST */
	I(0x79, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvtps2uqq\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.66.0F.W0 79 /R VCVTPS2UQQ YMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x79, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvtps2uqq\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.66.0F.W0 79 /R VCVTPS2UQQ ZMM1{K1}{Z}, YMM2/M256/M32BCST{ER} */

	I(0xe6, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvtqq2pd\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.F3.0F.W1 E6 /R VCVTQQ2PD XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0xe6, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvtqq2pd\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.F3.0F.W1 E6 /R VCVTQQ2PD YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0xe6, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvtqq2pd\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.F3.0F.W1 E6 /R VCVTQQ2PD ZMM1{K1}{Z}, ZMM2/M512/M64BCST{ER} */

	I(0x5b, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvtqq2ps\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.0F.W1 5B /R VCVTQQ2PS XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x5b, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvtqq2ps\t" OP_RM256_YMM OP_RXMM_MASK),        /* EVEX.256.0F.W1 5B /R VCVTQQ2PS XMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x5b, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvtqq2ps\t" OP_RM512_ZMM "{er}" OP_RYMM_MASK), /* EVEX.512.0F.W1 5B /R VCVTQQ2PS YMM1{K1}{Z}, ZMM2/M512/M64BCST{ER} */

	I(0x79, IF_VEX|IF_F2|IF_MODRM,        OP_VEX_B0_LIG(0, 0, 0) "vcvtsd2usi\t" OP_RM128_XMM "{er}" OP_R32), /* EVEX.LIG.F2.0F.W0 79 /R VCVTSD2USI R32, XMM1/M64{ER} */
	I(0x79, IF_X32|IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtsd2usi\t" OP_RM128_XMM "{er}" OP_R32), /* EVEX.LIG.F2.0F.W1 79 /R VCVTSD2USI R64, XMM1/M64{ER} */
	I(0x79, IF_X64|IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtsd2usi\t" OP_RM128_XMM "{er}" OP_R64), /* EVEX.LIG.F2.0F.W1 79 /R VCVTSD2USI R64, XMM1/M64{ER} */

	I(0x79, IF_VEX|IF_F3|IF_MODRM,        OP_VEX_B0_LIG(0, 0, 0) "vcvtss2usi\t" OP_RM128_XMM "{er}" OP_R32), /* EVEX.LIG.F3.0F.W0 79 /R VCVTSS2USI R32, XMM1/M32{ER} */
	I(0x79, IF_X32|IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtss2usi\t" OP_RM128_XMM "{er}" OP_R32), /* EVEX.LIG.F3.0F.W1 79 /R VCVTSS2USI R64, XMM1/M32{ER} */
	I(0x79, IF_X64|IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtss2usi\t" OP_RM128_XMM "{er}" OP_R64), /* EVEX.LIG.F3.0F.W1 79 /R VCVTSS2USI R64, XMM1/M32{ER} */

	I(0x7a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvttpd2qq\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F.W1 7A /R VCVTTPD2QQ XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x7a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvttpd2qq\t" OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F.W1 7A /R VCVTTPD2QQ YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x7a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvttpd2qq\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F.W1 7A /R VCVTTPD2QQ ZMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE} */

	I(0x78, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvttpd2udq\t" OP_RM128_XMM OP_RXMM_MASK),         /*    EVEX.128.0F.W1 78 /R VCVTTPD2UDQ XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x02, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvttpd2udq\t" OP_RM256_YMM OP_RXMM_MASK),         /* EVEX.256.0F.W1 78 02 /R VCVTTPD2UDQ XMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x78, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvttpd2udq\t" OP_RM512_ZMM OP_RYMM_MASK "{sae}"), /*    EVEX.512.0F.W1 78 /R VCVTTPD2UDQ YMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE} */

	I(0x78, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvttpd2uqq\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F.W1 78 /R VCVTTPD2UQQ XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x78, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvttpd2uqq\t" OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F.W1 78 /R VCVTTPD2UQQ YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x78, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvttpd2uqq\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F.W1 78 /R VCVTTPD2UQQ ZMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE} */

	I(0x7a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvttps2qq\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F.W0 7A /R VCVTTPS2QQ XMM1{K1}{Z}, XMM2/M64/M32BCST */
	I(0x7a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvttps2qq\t" OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F.W0 7A /R VCVTTPS2QQ YMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x7a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvttps2qq\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F.W0 7A /R VCVTTPS2QQ ZMM1{K1}{Z}, YMM2/M256/M32BCST{SAE} */

	I(0x78, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvttps2udq\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.0F.W0 78 /R VCVTTPS2UDQ XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x78, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvttps2udq\t" OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.0F.W0 78 /R VCVTTPS2UDQ YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x78, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvttps2udq\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.0F.W0 78 /R VCVTTPS2UDQ ZMM1{K1}{Z}, ZMM2/M512/M32BCST{SAE} */

	I(0x78, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvttps2uqq\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F.W0 78 /R VCVTTPS2UQQ XMM1{K1}{Z}, XMM2/M64/M32BCST */
	I(0x78, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvttps2uqq\t" OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F.W0 78 /R VCVTTPS2UQQ YMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x78, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvttps2uqq\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F.W0 78 /R VCVTTPS2UQQ ZMM1{K1}{Z}, YMM2/M256/M32BCST{SAE} */

	I(0x78, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvttsd2usi\t" OP_RM128_XMM OP_R32 "{sae}"), /* EVEX.LIG.F2.0F.W0 78 /R VCVTTSD2USI R32, XMM1/M64{SAE} */
	I(0x78, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvttsd2usi\t" OP_RM128_XMM OP_R64 "{sae}"), /* EVEX.LIG.F2.0F.W1 78 /R VCVTTSD2USI R64, XMM1/M64{SAE} */

	I(0x78, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvttss2usi\t" OP_RM128_XMM OP_R32 "{sae}"), /* EVEX.LIG.F3.0F.W0 78 /R VCVTTSS2USI R32, XMM1/M32{SAE} */
	I(0x78, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvttss2usi\t" OP_RM128_XMM OP_R64 "{sae}"), /* EVEX.LIG.F3.0F.W1 78 /R VCVTTSS2USI R64, XMM1/M32{SAE} */

	I(0x7a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvtudq2pd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.F3.0F.W0 7A /R VCVTUDQ2PD XMM1{K1}{Z}, XMM2/M64/M32BCST */
	I(0x7a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvtudq2pd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.F3.0F.W0 7A /R VCVTUDQ2PD YMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x7a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvtudq2pd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.F3.0F.W0 7A /R VCVTUDQ2PD ZMM1{K1}{Z}, YMM2/M256/M32BCST */

	I(0x7a, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcvtudq2ps\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.F2.0F.W0 7A /R VCVTUDQ2PS XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x7a, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcvtudq2ps\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.F2.0F.W0 7A /R VCVTUDQ2PS YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x7a, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vcvtudq2ps\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.F2.0F.W0 7A /R VCVTUDQ2PS ZMM1{K1}{Z}, ZMM2/M512/M32BCST{ER} */

	I(0x7a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvtuqq2pd\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.F3.0F.W1 7A /R VCVTUQQ2PD XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x7a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvtuqq2pd\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.256.F3.0F.W1 7A /R VCVTUQQ2PD YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x7a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvtuqq2pd\t" OP_RM512_ZMM "{er}" OP_RZMM_MASK), /* EVEX.512.F3.0F.W1 7A /R VCVTUQQ2PD ZMM1{K1}{Z}, ZMM2/M512/M64BCST{ER} */

	I(0x7a, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcvtuqq2ps\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.F2.0F.W1 7A /R VCVTUQQ2PS XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x7a, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vcvtuqq2ps\t" OP_RM256_YMM OP_RXMM_MASK),        /* EVEX.256.F2.0F.W1 7A /R VCVTUQQ2PS XMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x7a, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcvtuqq2ps\t" OP_RM512_ZMM "{er}" OP_RYMM_MASK), /* EVEX.512.F2.0F.W1 7A /R VCVTUQQ2PS YMM1{K1}{Z}, ZMM2/M512/M64BCST{ER} */

	I(0x7b, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvtusi2sd\t" OP_RM32 OP_VRXMM OP_RXMM),        /* EVEX.LIG.F2.0F.W0 7B /R VCVTUSI2SD XMM1, XMM2, R/M32 */
	I(0x7b, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtusi2sd\t" OP_RM64 "{er}" OP_VRXMM OP_RXMM), /* EVEX.LIG.F2.0F.W1 7B /R VCVTUSI2SD XMM1, XMM2, R/M64{ER} */

	I(0x7b, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcvtusi2ss\t" OP_RM32 "{er}" OP_VRXMM OP_RXMM), /* EVEX.LIG.F3.0F.W0 7B /R VCVTUSI2SS XMM1, XMM2, R/M32{ER} */
	I(0x7b, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcvtusi2ss\t" OP_RM64 "{er}" OP_VRXMM OP_RXMM), /* EVEX.LIG.F3.0F.W1 7B /R VCVTUSI2SS XMM1, XMM2, R/M64{ER} */

	I(0x42, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vdbpsadbw\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F3A.W0 42 /R IB VDBPSADBW XMM1{K1}{Z}, XMM2, XMM3/M128, IMM8 */
	I(0x42, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vdbpsadbw\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F3A.W0 42 /R IB VDBPSADBW YMM1{K1}{Z}, YMM2, YMM3/M256, IMM8 */
	I(0x42, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vdbpsadbw\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F3A.W0 42 /R IB VDBPSADBW ZMM1{K1}{Z}, ZMM2, ZMM3/M512, IMM8 */

	I(0x88, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vexpandpd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 88 /R VEXPANDPD XMM1{K1}{Z}, XMM2/M128 */
	I(0x88, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vexpandpd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 88 /R VEXPANDPD YMM1{K1}{Z}, YMM2/M256 */
	I(0x88, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vexpandpd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 88 /R VEXPANDPD ZMM1{K1}{Z}, ZMM2/M512 */

	I(0x88, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vexpandps\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 88 /R VEXPANDPS XMM1{K1}{Z}, XMM2/M128 */
	I(0x88, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vexpandps\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 88 /R VEXPANDPS YMM1{K1}{Z}, YMM2/M256 */
	I(0x88, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vexpandps\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 88 /R VEXPANDPS ZMM1{K1}{Z}, ZMM2/M512 */

	I(0x54, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfixupimmpd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),         /* EVEX.128.66.0F3A.W1 54 /R IB VFIXUPIMMPD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST, IMM8 */
	I(0x54, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfixupimmpd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),         /* EVEX.256.66.0F3A.W1 54 /R IB VFIXUPIMMPD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST, IMM8 */
	I(0x54, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfixupimmpd\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F3A.W1 54 /R IB VFIXUPIMMPD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{SAE}, IMM8 */

	I(0x54, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfixupimmps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),         /* EVEX.128.66.0F3A.W0 54 /R VFIXUPIMMPS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST, IMM8 */
	I(0x54, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfixupimmps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),         /* EVEX.256.66.0F3A.W0 54 /R VFIXUPIMMPS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST, IMM8 */
	I(0x54, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfixupimmps\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F3A.W0 54 /R IB VFIXUPIMMPS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{SAE}, IMM8 */

	I(0x55, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vfixupimmsd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F3A.W1 55 /R IB VFIXUPIMMSD XMM1{K1}{Z}, XMM2, XMM3/M64{SAE}, IMM8 */

	I(0x55, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vfixupimmss\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F3A.W0 55 /R IB VFIXUPIMMSS XMM1{K1}{Z}, XMM2, XMM3/M32{SAE}, IMM8 */

	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vfpclasspd\t" OP_U8 OP_RM128_XMM OP_RK_MASK), /* EVEX.128.66.0F3A.W1 66 /R IB VFPCLASSPD K2{K1}, XMM2/M128/M64BCST, IMM8 */
	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vfpclasspd\t" OP_U8 OP_RM256_YMM OP_RK_MASK), /* EVEX.256.66.0F3A.W1 66 /R IB VFPCLASSPD K2{K1}, YMM2/M256/M64BCST, IMM8 */
	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vfpclasspd\t" OP_U8 OP_RM512_ZMM OP_RK_MASK), /* EVEX.512.66.0F3A.W1 66 /R IB VFPCLASSPD K2{K1}, ZMM2/M512/M64BCST, IMM8 */

	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vfpclassps\t" OP_U8 OP_RM128_XMM OP_RK_MASK), /* EVEX.128.66.0F3A.W0 66 /R IB VFPCLASSPS K2{K1}, XMM2/M128/M32BCST, IMM8 */
	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vfpclassps\t" OP_U8 OP_RM256_YMM OP_RK_MASK), /* EVEX.256.66.0F3A.W0 66 /R IB VFPCLASSPS K2{K1}, YMM2/M256/M32BCST, IMM8 */
	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vfpclassps\t" OP_U8 OP_RM512_ZMM OP_RK_MASK), /* EVEX.512.66.0F3A.W0 66 /R IB VFPCLASSPS K2{K1}, ZMM2/M512/M32BCST, IMM8 */

	I(0x67, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vfpclasssd\t" OP_U8 OP_RM128_XMM OP_RK_MASK), /* EVEX.LIG.66.0F3A.W1 67 /R IB VFPCLASSSD K2{K1}, XMM2/M64, IMM8 */

	I(0x67, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vfpclassss\t" OP_U8 OP_RM128_XMM OP_RK_MASK), /* EVEX.LIG.66.0F3A.W0 67 /R VFPCLASSSS K2{K1}, XMM2/M32, IMM8 */

	I(0x42, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vgetexppd\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F38.W1 42 /R VGETEXPPD XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x42, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vgetexppd\t" OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F38.W1 42 /R VGETEXPPD YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x42, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vgetexppd\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F38.W1 42 /R VGETEXPPD ZMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE} */

	I(0x42, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vgetexpps\t" OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F38.W0 42 /R VGETEXPPS XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x42, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vgetexpps\t" OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F38.W0 42 /R VGETEXPPS YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x42, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vgetexpps\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F38.W0 42 /R VGETEXPPS ZMM1{K1}{Z}, ZMM2/M512/M32BCST{SAE} */

	I(0x43, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vgetexpsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F38.W1 43 /R VGETEXPSD XMM1{K1}{Z}, XMM2, XMM3/M64{SAE} */

	I(0x43, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vgetexpss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F38.W0 43 /R VGETEXPSS XMM1{K1}{Z}, XMM2, XMM3/M32{SAE} */

	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vgetmantpd\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F3A.W1 26 /R IB VGETMANTPD XMM1{K1}{Z}, XMM2/M128/M64BCST, IMM8 */
	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vgetmantpd\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F3A.W1 26 /R IB VGETMANTPD YMM1{K1}{Z}, YMM2/M256/M64BCST, IMM8 */
	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vgetmantpd\t" OP_U8 OP_RM256_YMM "{sae}" OP_RYMM_MASK), /* EVEX.512.66.0F3A.W1 26 /R IB VGETMANTPD ZMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE}, IMM8 */

	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vgetmantps\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F3A.W0 26 /R IB VGETMANTPS XMM1{K1}{Z}, XMM2/M128/M32BCST, IMM8 */
	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vgetmantps\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F3A.W0 26 /R IB VGETMANTPS YMM1{K1}{Z}, YMM2/M256/M32BCST, IMM8 */
	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vgetmantps\t" OP_U8 OP_RM256_YMM "{sae}" OP_RYMM_MASK), /* EVEX.512.66.0F3A.W0 26 /R IB VGETMANTPS ZMM1{K1}{Z}, ZMM2/M512/M32BCST{SAE}, IMM8 */

	I(0x27, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vgetmantsd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F3A.W1 27 /R IB VGETMANTSD XMM1{K1}{Z}, XMM2, XMM3/M64{SAE}, IMM8 */

	I(0x27, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vgetmantss\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F3A.W0 27 /R IB VGETMANTSS XMM1{K1}{Z}, XMM2, XMM3/M32{SAE}, IMM8 */

	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpblendmb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 66 /R VPBLENDMB XMM1{K1}{Z}, XMM2, XMM3/M128 */
	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpblendmb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 66 /R VPBLENDMB YMM1{K1}{Z}, YMM2, YMM3/M256 */
	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpblendmb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 66 /R VPBLENDMB ZMM1{K1}{Z}, ZMM2, ZMM3/M512 */
	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpblendmw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 66 /R VPBLENDMW XMM1{K1}{Z}, XMM2, XMM3/M128 */
	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpblendmw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 66 /R VPBLENDMW YMM1{K1}{Z}, YMM2, YMM3/M256 */
	I(0x66, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpblendmw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 66 /R VPBLENDMW ZMM1{K1}{Z}, ZMM2, ZMM3/M512 */

	I(0x64, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpblendmd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 64 /R VPBLENDMD XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x64, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpblendmd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 64 /R VPBLENDMD YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x64, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpblendmd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 64 /R VPBLENDMD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST */
	I(0x64, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpblendmq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 64 /R VPBLENDMQ XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x64, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpblendmq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 64 /R VPBLENDMQ YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x64, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpblendmq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 64 /R VPBLENDMQ ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */

	I(0x2a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpbroadcastmb2q\t" OP_RMK OP_RXMM), /* EVEX.128.F3.0F38.W1 2A /R VPBROADCASTMB2Q XMM1, K1 */
	I(0x2a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpbroadcastmb2q\t" OP_RMK OP_RYMM), /* EVEX.256.F3.0F38.W1 2A /R VPBROADCASTMB2Q YMM1, K1 */
	I(0x2a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpbroadcastmb2q\t" OP_RMK OP_RZMM), /* EVEX.512.F3.0F38.W1 2A /R VPBROADCASTMB2Q ZMM1, K1 */
	I(0x3a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpbroadcastmw2d\t" OP_RMK OP_RXMM), /* EVEX.128.F3.0F38.W0 3A /R VPBROADCASTMW2D XMM1, K1 */
	I(0x3a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpbroadcastmw2d\t" OP_RMK OP_RYMM), /* EVEX.256.F3.0F38.W0 3A /R VPBROADCASTMW2D YMM1, K1 */
	I(0x3a, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpbroadcastmw2d\t" OP_RMK OP_RZMM), /* EVEX.512.F3.0F38.W0 3A /R VPBROADCASTMW2D ZMM1, K1 */

	I(0x3f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcmpb\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK),  /* EVEX.128.66.0F3A.W0 3F /R IB VPCMPB K1{K2}, XMM2, XMM3/M128, IMM8 */
	I(0x3f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcmpb\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK),  /* EVEX.256.66.0F3A.W0 3F /R IB VPCMPB K1{K2}, YMM2, YMM3/M256, IMM8 */
	I(0x3f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcmpb\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK),  /* EVEX.512.66.0F3A.W0 3F /R IB VPCMPB K1{K2}, ZMM2, ZMM3/M512, IMM8 */
	I(0x3e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcmpub\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0F3A.W0 3E /R IB VPCMPUB K1{K2}, XMM2, XMM3/M128, IMM8 */
	I(0x3e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcmpub\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0F3A.W0 3E /R IB VPCMPUB K1{K2}, YMM2, YMM3/M256, IMM8 */
	I(0x3e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcmpub\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F3A.W0 3E /R IB VPCMPUB K1{K2}, ZMM2, ZMM3/M512, IMM8 */

	I(0x1f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcmpd\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK),  /* EVEX.128.66.0F3A.W0 1F /R IB VPCMPD K1{K2}, XMM2, XMM3/M128/M32BCST, IMM8 */
	I(0x1f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcmpd\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK),  /* EVEX.256.66.0F3A.W0 1F /R IB VPCMPD K1{K2}, YMM2, YMM3/M256/M32BCST, IMM8 */
	I(0x1f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcmpd\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK),  /* EVEX.512.66.0F3A.W0 1F /R IB VPCMPD K1{K2}, ZMM2, ZMM3/M512/M32BCST, IMM8 */
	I(0x1e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcmpud\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0F3A.W0 1E /R IB VPCMPUD K1{K2}, XMM2, XMM3/M128/M32BCST, IMM8 */
	I(0x1e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcmpud\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0F3A.W0 1E /R IB VPCMPUD K1{K2}, YMM2, YMM3/M256/M32BCST, IMM8 */
	I(0x1e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcmpud\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F3A.W0 1E /R IB VPCMPUD K1{K2}, ZMM2, ZMM3/M512/M32BCST, IMM8 */

	I(0x1f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpcmpq\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK),  /* EVEX.128.66.0F3A.W1 1F /R IB VPCMPQ K1{K2}, XMM2, XMM3/M128/M64BCST, IMM8 */
	I(0x1f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpcmpq\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK),  /* EVEX.256.66.0F3A.W1 1F /R IB VPCMPQ K1{K2}, YMM2, YMM3/M256/M64BCST, IMM8 */
	I(0x1f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpcmpq\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK),  /* EVEX.512.66.0F3A.W1 1F /R IB VPCMPQ K1{K2}, ZMM2, ZMM3/M512/M64BCST, IMM8 */
	I(0x1e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpcmpuq\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0F3A.W1 1E /R IB VPCMPUQ K1{K2}, XMM2, XMM3/M128/M64BCST, IMM8 */
	I(0x1e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpcmpuq\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0F3A.W1 1E /R IB VPCMPUQ K1{K2}, YMM2, YMM3/M256/M64BCST, IMM8 */
	I(0x1e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpcmpuq\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F3A.W1 1E /R IB VPCMPUQ K1{K2}, ZMM2, ZMM3/M512/M64BCST, IMM8 */

	I(0x3f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpcmpw\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK),  /* EVEX.128.66.0F3A.W1 3F /R IB VPCMPW K1{K2}, XMM2, XMM3/M128, IMM8 */
	I(0x3f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpcmpw\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK),  /* EVEX.256.66.0F3A.W1 3F /R IB VPCMPW K1{K2}, YMM2, YMM3/M256, IMM8 */
	I(0x3f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpcmpw\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK),  /* EVEX.512.66.0F3A.W1 3F /R IB VPCMPW K1{K2}, ZMM2, ZMM3/M512, IMM8 */
	I(0x3e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpcmpuw\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0F3A.W1 3E /R IB VPCMPUW K1{K2}, XMM2, XMM3/M128, IMM8 */
	I(0x3e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpcmpuw\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0F3A.W1 3E /R IB VPCMPUW K1{K2}, YMM2, YMM3/M256, IMM8 */
	I(0x3e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpcmpuw\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F3A.W1 3E /R IB VPCMPUW K1{K2}, ZMM2, ZMM3/M512, IMM8 */

	I(0x8b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcompressd\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.66.0F38.W0 8B /R VPCOMPRESSD XMM1/M128{K1}{Z}, XMM2 */
	I(0x8b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcompressd\t" OP_RYMM OP_RM256_YMM_MASK), /* EVEX.256.66.0F38.W0 8B /R VPCOMPRESSD YMM1/M256{K1}{Z}, YMM2 */
	I(0x8b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcompressd\t" OP_RZMM OP_RM512_ZMM_MASK), /* EVEX.512.66.0F38.W0 8B /R VPCOMPRESSD ZMM1/M512{K1}{Z}, ZMM2 */

	I(0x8b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpcompressq\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.66.0F38.W1 8B /R VPCOMPRESSQ XMM1/M128{K1}{Z}, XMM2 */
	I(0x8b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpcompressq\t" OP_RYMM OP_RM256_YMM_MASK), /* EVEX.256.66.0F38.W1 8B /R VPCOMPRESSQ YMM1/M256{K1}{Z}, YMM2 */
	I(0x8b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpcompressq\t" OP_RZMM OP_RM512_ZMM_MASK), /* EVEX.512.66.0F38.W1 8B /R VPCOMPRESSQ ZMM1/M512{K1}{Z}, ZMM2 */

	I(0xc4, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpconflictd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 C4 /R VPCONFLICTD XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0xc4, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpconflictd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 C4 /R VPCONFLICTD YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0xc4, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpconflictd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 C4 /R VPCONFLICTD ZMM1{K1}{Z}, ZMM2/M512/M32BCST */
	I(0xc4, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpconflictq\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 C4 /R VPCONFLICTQ XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0xc4, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpconflictq\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 C4 /R VPCONFLICTQ YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0xc4, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpconflictq\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 C4 /R VPCONFLICTQ ZMM1{K1}{Z}, ZMM2/M512/M64BCST */

	I(0x8d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 8D /R VPERMB XMM1{K1}{Z}, XMM2, XMM3/M128 */
	I(0x8d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 8D /R VPERMB YMM1{K1}{Z}, YMM2, YMM3/M256 */
	I(0x8d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 8D /R VPERMB ZMM1{K1}{Z}, ZMM2, ZMM3/M512 */

	I(0x75, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermi2b\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 75 /R VPERMI2B XMM1{K1}{Z}, XMM2, XMM3/M128 */
	I(0x75, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermi2b\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 75 /R VPERMI2B YMM1{K1}{Z}, YMM2, YMM3/M256 */
	I(0x75, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermi2b\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 75 /R VPERMI2B ZMM1{K1}{Z}, ZMM2, ZMM3/M512 */

	I(0x75, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermi2w\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0F38.W1 75 /R VPERMI2W XMM1{K1}{Z}, XMM2, XMM3/M128 */
	I(0x75, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermi2w\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0F38.W1 75 /R VPERMI2W YMM1{K1}{Z}, YMM2, YMM3/M256 */
	I(0x75, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermi2w\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0F38.W1 75 /R VPERMI2W ZMM1{K1}{Z}, ZMM2, ZMM3/M512 */
	I(0x76, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermi2d\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0F38.W0 76 /R VPERMI2D XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x76, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermi2d\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0F38.W0 76 /R VPERMI2D YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x76, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermi2d\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0F38.W0 76 /R VPERMI2D ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST */
	I(0x76, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermi2q\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0F38.W1 76 /R VPERMI2Q XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x76, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermi2q\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0F38.W1 76 /R VPERMI2Q YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x76, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermi2q\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0F38.W1 76 /R VPERMI2Q ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */
	I(0x77, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermi2ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 77 /R VPERMI2PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x77, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermi2ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 77 /R VPERMI2PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x77, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermi2ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 77 /R VPERMI2PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST */
	I(0x77, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermi2pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 77 /R VPERMI2PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x77, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermi2pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 77 /R VPERMI2PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x77, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermi2pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 77 /R VPERMI2PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */

	I(0x7d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermt2b\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 7D /R VPERMT2B XMM1{K1}{Z}, XMM2, XMM3/M128 */
	I(0x7d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermt2b\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 7D /R VPERMT2B YMM1{K1}{Z}, YMM2, YMM3/M256 */
	I(0x7d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermt2b\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 7D /R VPERMT2B ZMM1{K1}{Z}, ZMM2, ZMM3/M512 */

	I(0x7d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermt2w\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0F38.W1 7D /R VPERMT2W XMM1{K1}{Z}, XMM2, XMM3/M128 */
	I(0x7d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermt2w\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0F38.W1 7D /R VPERMT2W YMM1{K1}{Z}, YMM2, YMM3/M256 */
	I(0x7d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermt2w\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0F38.W1 7D /R VPERMT2W ZMM1{K1}{Z}, ZMM2, ZMM3/M512 */
	I(0x7e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermt2d\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0F38.W0 7E /R VPERMT2D XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x7e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermt2d\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0F38.W0 7E /R VPERMT2D YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x7e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermt2d\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0F38.W0 7E /R VPERMT2D ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST */
	I(0x7e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermt2q\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0F38.W1 7E /R VPERMT2Q XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x7e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermt2q\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0F38.W1 7E /R VPERMT2Q YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x7e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermt2q\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0F38.W1 7E /R VPERMT2Q ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */
	I(0x7f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermt2ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 7F /R VPERMT2PS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x7f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermt2ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 7F /R VPERMT2PS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x7f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermt2ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 7F /R VPERMT2PS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST */
	I(0x7f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermt2pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 7F /R VPERMT2PD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x7f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermt2pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 7F /R VPERMT2PD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x7f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermt2pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 7F /R VPERMT2PD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */

	I(0x89, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpexpandd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 89 /R VPEXPANDD XMM1{K1}{Z}, XMM2/M128 */
	I(0x89, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpexpandd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 89 /R VPEXPANDD YMM1{K1}{Z}, YMM2/M256 */
	I(0x89, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpexpandd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 89 /R VPEXPANDD ZMM1{K1}{Z}, ZMM2/M512 */

	I(0x89, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpexpandq\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 89 /R VPEXPANDQ XMM1{K1}{Z}, XMM2/M128 */
	I(0x89, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpexpandq\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 89 /R VPEXPANDQ YMM1{K1}{Z}, YMM2/M256 */
	I(0x89, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpexpandq\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 89 /R VPEXPANDQ ZMM1{K1}{Z}, ZMM2/M512 */

	I(0x44, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vplzcntd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 44 /R VPLZCNTD XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x44, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vplzcntd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 44 /R VPLZCNTD YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x44, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vplzcntd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 44 /R VPLZCNTD ZMM1{K1}{Z}, ZMM2/M512/M32BCST */
	I(0x44, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vplzcntq\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 44 /R VPLZCNTQ XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x44, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vplzcntq\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 44 /R VPLZCNTQ YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x44, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vplzcntq\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 44 /R VPLZCNTQ ZMM1{K1}{Z}, ZMM2/M512/M64BCST */

	I(0xb5, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmadd52huq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 B5 /R VPMADD52HUQ XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0xb5, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmadd52huq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 B5 /R VPMADD52HUQ YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0xb5, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmadd52huq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 B5 /R VPMADD52HUQ ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */

	I(0xb4, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmadd52luq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 B4 /R VPMADD52LUQ XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0xb4, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmadd52luq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 B4 /R VPMADD52LUQ YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0xb4, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmadd52luq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 B4 /R VPMADD52LUQ ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */

	I(0x29, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpmovb2m\t" OP_RM128_XMM OP_RK), /* EVEX.128.F3.0F38.W0 29 /R VPMOVB2M K1, XMM1 */
	I(0x29, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpmovb2m\t" OP_RM256_YMM OP_RK), /* EVEX.256.F3.0F38.W0 29 /R VPMOVB2M K1, YMM1 */
	I(0x29, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpmovb2m\t" OP_RM512_ZMM OP_RK), /* EVEX.512.F3.0F38.W0 29 /R VPMOVB2M K1, ZMM1 */
	I(0x29, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "vpmovw2m\t" OP_RM128_XMM OP_RK), /* EVEX.128.F3.0F38.W1 29 /R VPMOVW2M K1, XMM1 */
	I(0x29, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "vpmovw2m\t" OP_RM256_YMM OP_RK), /* EVEX.256.F3.0F38.W1 29 /R VPMOVW2M K1, YMM1 */
	I(0x29, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 2) "vpmovw2m\t" OP_RM512_ZMM OP_RK), /* EVEX.512.F3.0F38.W1 29 /R VPMOVW2M K1, ZMM1 */
	I(0x39, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpmovd2m\t" OP_RM128_XMM OP_RK), /* EVEX.128.F3.0F38.W0 39 /R VPMOVD2M K1, XMM1 */
	I(0x39, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpmovd2m\t" OP_RM256_YMM OP_RK), /* EVEX.256.F3.0F38.W0 39 /R VPMOVD2M K1, YMM1 */
	I(0x39, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpmovd2m\t" OP_RM512_ZMM OP_RK), /* EVEX.512.F3.0F38.W0 39 /R VPMOVD2M K1, ZMM1 */
	I(0x39, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "vpmovq2m\t" OP_RM128_XMM OP_RK), /* EVEX.128.F3.0F38.W1 39 /R VPMOVQ2M K1, XMM1 */
	I(0x39, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "vpmovq2m\t" OP_RM256_YMM OP_RK), /* EVEX.256.F3.0F38.W1 39 /R VPMOVQ2M K1, YMM1 */
	I(0x39, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 2) "vpmovq2m\t" OP_RM512_ZMM OP_RK), /* EVEX.512.F3.0F38.W1 39 /R VPMOVQ2M K1, ZMM1 */

	I(0x31, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovdb\t" OP_RXMM OP_RM128_XMM_MASK),   /* EVEX.128.F3.0F38.W0 31 /R VPMOVDB XMM1/M32{K1}{Z}, XMM2 */
	I(0x21, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovsdb\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.F3.0F38.W0 21 /R VPMOVSDB XMM1/M32{K1}{Z}, XMM2 */
	I(0x11, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovusdb\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.F3.0F38.W0 11 /R VPMOVUSDB XMM1/M32{K1}{Z}, XMM2 */
	I(0x31, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovdb\t" OP_RYMM OP_RM128_XMM_MASK),   /* EVEX.256.F3.0F38.W0 31 /R VPMOVDB XMM1/M64{K1}{Z}, YMM2 */
	I(0x21, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovsdb\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.F3.0F38.W0 21 /R VPMOVSDB XMM1/M64{K1}{Z}, YMM2 */
	I(0x11, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovusdb\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.F3.0F38.W0 11 /R VPMOVUSDB XMM1/M64{K1}{Z}, YMM2 */
	I(0x31, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovdb\t" OP_RZMM OP_RM128_XMM_MASK),   /* EVEX.512.F3.0F38.W0 31 /R VPMOVDB XMM1/M128{K1}{Z}, ZMM2 */
	I(0x21, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovsdb\t" OP_RZMM OP_RM128_XMM_MASK),  /* EVEX.512.F3.0F38.W0 21 /R VPMOVSDB XMM1/M128{K1}{Z}, ZMM2 */
	I(0x11, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovusdb\t" OP_RZMM OP_RM128_XMM_MASK), /* EVEX.512.F3.0F38.W0 11 /R VPMOVUSDB XMM1/M128{K1}{Z}, ZMM2 */

	I(0x33, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovdw\t" OP_RXMM OP_RM128_XMM_MASK),   /* EVEX.128.F3.0F38.W0 33 /R VPMOVDW XMM1/M64{K1}{Z}, XMM2 */
	I(0x23, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovsdw\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.F3.0F38.W0 23 /R VPMOVSDW XMM1/M64{K1}{Z}, XMM2 */
	I(0x13, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovusdw\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.F3.0F38.W0 13 /R VPMOVUSDW XMM1/M64{K1}{Z}, XMM2 */
	I(0x33, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovdw\t" OP_RYMM OP_RM128_XMM_MASK),   /* EVEX.256.F3.0F38.W0 33 /R VPMOVDW XMM1/M128{K1}{Z}, YMM2 */
	I(0x23, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovsdw\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.F3.0F38.W0 23 /R VPMOVSDW XMM1/M128{K1}{Z}, YMM2 */
	I(0x13, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovusdw\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.F3.0F38.W0 13 /R VPMOVUSDW XMM1/M128{K1}{Z}, YMM2 */
	I(0x33, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovdw\t" OP_RZMM OP_RM256_YMM_MASK),   /* EVEX.512.F3.0F38.W0 33 /R VPMOVDW YMM1/M256{K1}{Z}, ZMM2 */
	I(0x23, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovsdw\t" OP_RZMM OP_RM256_YMM_MASK),  /* EVEX.512.F3.0F38.W0 23 /R VPMOVSDW YMM1/M256{K1}{Z}, ZMM2 */
	I(0x13, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovusdw\t" OP_RZMM OP_RM256_YMM_MASK), /* EVEX.512.F3.0F38.W0 13 /R VPMOVUSDW YMM1/M256{K1}{Z}, ZMM2 */

	I(0x28, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpmovm2b\t" OP_RMK OP_RXMM), /* EVEX.128.F3.0F38.W0 28 /R VPMOVM2B XMM1, K1 */
	I(0x28, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpmovm2b\t" OP_RMK OP_RYMM), /* EVEX.256.F3.0F38.W0 28 /R VPMOVM2B YMM1, K1 */
	I(0x28, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpmovm2b\t" OP_RMK OP_RZMM), /* EVEX.512.F3.0F38.W0 28 /R VPMOVM2B ZMM1, K1 */
	I(0x28, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "vpmovm2w\t" OP_RMK OP_RXMM), /* EVEX.128.F3.0F38.W1 28 /R VPMOVM2W XMM1, K1 */
	I(0x28, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "vpmovm2w\t" OP_RMK OP_RYMM), /* EVEX.256.F3.0F38.W1 28 /R VPMOVM2W YMM1, K1 */
	I(0x28, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 2) "vpmovm2w\t" OP_RMK OP_RZMM), /* EVEX.512.F3.0F38.W1 28 /R VPMOVM2W ZMM1, K1 */
	I(0x38, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpmovm2d\t" OP_RMK OP_RXMM), /* EVEX.128.F3.0F38.W0 38 /R VPMOVM2D XMM1, K1 */
	I(0x38, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpmovm2d\t" OP_RMK OP_RYMM), /* EVEX.256.F3.0F38.W0 38 /R VPMOVM2D YMM1, K1 */
	I(0x38, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpmovm2d\t" OP_RMK OP_RZMM), /* EVEX.512.F3.0F38.W0 38 /R VPMOVM2D ZMM1, K1 */
	I(0x38, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "vpmovm2q\t" OP_RMK OP_RXMM), /* EVEX.128.F3.0F38.W1 38 /R VPMOVM2Q XMM1, K1 */
	I(0x38, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "vpmovm2q\t" OP_RMK OP_RYMM), /* EVEX.256.F3.0F38.W1 38 /R VPMOVM2Q YMM1, K1 */
	I(0x38, IF_VEX|IF_F3|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 2) "vpmovm2q\t" OP_RMK OP_RZMM), /* EVEX.512.F3.0F38.W1 38 /R VPMOVM2Q ZMM1, K1 */

	I(0x32, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovqb\t" OP_RXMM OP_RM128_XMM_MASK),   /* EVEX.128.F3.0F38.W0 32 /R VPMOVQB XMM1/M16{K1}{Z}, XMM2 */
	I(0x22, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovsqb\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.F3.0F38.W0 22 /R VPMOVSQB XMM1/M16{K1}{Z}, XMM2 */
	I(0x12, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovusqb\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.F3.0F38.W0 12 /R VPMOVUSQB XMM1/M16{K1}{Z}, XMM2 */
	I(0x32, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovqb\t" OP_RYMM OP_RM128_XMM_MASK),   /* EVEX.256.F3.0F38.W0 32 /R VPMOVQB XMM1/M32{K1}{Z}, YMM2 */
	I(0x22, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovsqb\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.F3.0F38.W0 22 /R VPMOVSQB XMM1/M32{K1}{Z}, YMM2 */
	I(0x12, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovusqb\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.F3.0F38.W0 12 /R VPMOVUSQB XMM1/M32{K1}{Z}, YMM2 */
	I(0x32, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovqb\t" OP_RZMM OP_RM128_XMM_MASK),   /* EVEX.512.F3.0F38.W0 32 /R VPMOVQB XMM1/M64{K1}{Z}, ZMM2 */
	I(0x22, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovsqb\t" OP_RZMM OP_RM128_XMM_MASK),  /* EVEX.512.F3.0F38.W0 22 /R VPMOVSQB XMM1/M64{K1}{Z}, ZMM2 */
	I(0x12, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovusqb\t" OP_RZMM OP_RM128_XMM_MASK), /* EVEX.512.F3.0F38.W0 12 /R VPMOVUSQB XMM1/M64{K1}{Z}, ZMM2 */

	I(0x35, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovqd\t" OP_RXMM OP_RM128_XMM_MASK),   /* EVEX.128.F3.0F38.W0 35 /R VPMOVQD XMM1/M128{K1}{Z}, XMM2 */
	I(0x25, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovsqd\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.F3.0F38.W0 25 /R VPMOVSQD XMM1/M64{K1}{Z}, XMM2 */
	I(0x15, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovusqd\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.F3.0F38.W0 15 /R VPMOVUSQD XMM1/M64{K1}{Z}, XMM2 */
	I(0x35, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovqd\t" OP_RYMM OP_RM128_XMM_MASK),   /* EVEX.256.F3.0F38.W0 35 /R VPMOVQD XMM1/M128{K1}{Z}, YMM2 */
	I(0x25, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovsqd\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.F3.0F38.W0 25 /R VPMOVSQD XMM1/M128{K1}{Z}, YMM2 */
	I(0x15, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovusqd\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.F3.0F38.W0 15 /R VPMOVUSQD XMM1/M128{K1}{Z}, YMM2 */
	I(0x35, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovqd\t" OP_RZMM OP_RM256_YMM_MASK),   /* EVEX.512.F3.0F38.W0 35 /R VPMOVQD YMM1/M256{K1}{Z}, ZMM2 */
	I(0x25, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovsqd\t" OP_RZMM OP_RM256_YMM_MASK),  /* EVEX.512.F3.0F38.W0 25 /R VPMOVSQD YMM1/M256{K1}{Z}, ZMM2 */
	I(0x15, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovusqd\t" OP_RZMM OP_RM256_YMM_MASK), /* EVEX.512.F3.0F38.W0 15 /R VPMOVUSQD YMM1/M256{K1}{Z}, ZMM2 */

	I(0x34, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovqw\t" OP_RXMM OP_RM128_XMM_MASK),   /* EVEX.128.F3.0F38.W0 34 /R VPMOVQW XMM1/M32{K1}{Z}, XMM2 */
	I(0x24, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovsqw\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.F3.0F38.W0 24 /R VPMOVSQW XMM1/M32{K1}{Z}, XMM2 */
	I(0x14, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovusqw\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.F3.0F38.W0 14 /R VPMOVUSQW XMM1/M32{K1}{Z}, XMM2 */
	I(0x34, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovqw\t" OP_RYMM OP_RM128_XMM_MASK),   /* EVEX.256.F3.0F38.W0 34 /R VPMOVQW XMM1/M64{K1}{Z}, YMM2 */
	I(0x24, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovsqw\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.F3.0F38.W0 24 /R VPMOVSQW XMM1/M64{K1}{Z}, YMM2 */
	I(0x14, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovusqw\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.F3.0F38.W0 14 /R VPMOVUSQW XMM1/M64{K1}{Z}, YMM2 */
	I(0x34, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovqw\t" OP_RZMM OP_RM128_XMM_MASK),   /* EVEX.512.F3.0F38.W0 34 /R VPMOVQW XMM1/M128{K1}{Z}, ZMM2 */
	I(0x24, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovsqw\t" OP_RZMM OP_RM128_XMM_MASK),  /* EVEX.512.F3.0F38.W0 24 /R VPMOVSQW XMM1/M128{K1}{Z}, ZMM2 */
	I(0x14, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovusqw\t" OP_RZMM OP_RM128_XMM_MASK), /* EVEX.512.F3.0F38.W0 14 /R VPMOVUSQW XMM1/M128{K1}{Z}, ZMM2 */

	I(0x30, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovwb\t" OP_RXMM OP_RM128_XMM_MASK),   /* EVEX.128.F3.0F38.W0 30 /R VPMOVWB XMM1/M64{K1}{Z}, XMM2 */
	I(0x20, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovswb\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.F3.0F38.W0 20 /R VPMOVSWB XMM1/M64{K1}{Z}, XMM2 */
	I(0x10, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovuswb\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.F3.0F38.W0 10 /R VPMOVUSWB XMM1/M64{K1}{Z}, XMM2 */
	I(0x30, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovwb\t" OP_RYMM OP_RM128_XMM_MASK),   /* EVEX.256.F3.0F38.W0 30 /R VPMOVWB XMM1/M128{K1}{Z}, YMM2 */
	I(0x20, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovswb\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.F3.0F38.W0 20 /R VPMOVSWB XMM1/M128{K1}{Z}, YMM2 */
	I(0x10, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovuswb\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.F3.0F38.W0 10 /R VPMOVUSWB XMM1/M128{K1}{Z}, YMM2 */
	I(0x30, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovwb\t" OP_RZMM OP_RM256_YMM_MASK),   /* EVEX.512.F3.0F38.W0 30 /R VPMOVWB YMM1/M256{K1}{Z}, ZMM2 */
	I(0x20, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovswb\t" OP_RZMM OP_RM256_YMM_MASK),  /* EVEX.512.F3.0F38.W0 20 /R VPMOVSWB YMM1/M256{K1}{Z}, ZMM2 */
	I(0x10, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovuswb\t" OP_RZMM OP_RM256_YMM_MASK), /* EVEX.512.F3.0F38.W0 10 /R VPMOVUSWB YMM1/M256{K1}{Z}, ZMM2 */

	I(0x83, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmultishiftqb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 83 /R VPMULTISHIFTQB XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x83, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmultishiftqb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 83 /R VPMULTISHIFTQB YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x83, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmultishiftqb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 83 /R VPMULTISHIFTQB ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */

	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 0, 0) "vprold\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK),       /*   EVEX.128.66.0F.W0 72 /1 IB VPROLD XMM1{K1}{Z}, XMM2/M128/M32BCST, IMM8 */
	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 1, 0) "vprolq\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK),       /*   EVEX.128.66.0F.W1 72 /1 IB VPROLQ XMM1{K1}{Z}, XMM2/M128/M64BCST, IMM8 */
	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 0, 1) "vprold\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK),       /*   EVEX.256.66.0F.W0 72 /1 IB VPROLD YMM1{K1}{Z}, YMM2/M256/M32BCST, IMM8 */
	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 1, 1) "vprolq\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK),       /*   EVEX.256.66.0F.W1 72 /1 IB VPROLQ YMM1{K1}{Z}, YMM2/M256/M64BCST, IMM8 */
	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 0, 2) "vprold\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK),       /*   EVEX.512.66.0F.W0 72 /1 IB VPROLD ZMM1{K1}{Z}, ZMM2/M512/M32BCST, IMM8 */
	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 1, 2) "vprolq\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK),       /*   EVEX.512.66.0F.W1 72 /1 IB VPROLQ ZMM1{K1}{Z}, ZMM2/M512/M64BCST, IMM8 */
	I(0x15, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0)         "vprolvd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 15 /R VPROLVD XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x15, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0)         "vprolvq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 15 /R VPROLVQ XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x15, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1)         "vprolvd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 15 /R VPROLVD YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x15, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1)         "vprolvq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 15 /R VPROLVQ YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x15, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2)         "vprolvd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 15 /R VPROLVD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST */
	I(0x15, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2)         "vprolvq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 15 /R VPROLVQ ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */

	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 0, 0) "vprord\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK),       /*   EVEX.128.66.0F.W0 72 /0 IB VPRORD XMM1{K1}{Z}, XMM2/M128/M32BCST, IMM8 */
	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 1, 0) "vprorq\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK),       /*   EVEX.128.66.0F.W1 72 /0 IB VPRORQ XMM1{K1}{Z}, XMM2/M128/M64BCST, IMM8 */
	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 0, 1) "vprord\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK),       /*   EVEX.256.66.0F.W0 72 /0 IB VPRORD YMM1{K1}{Z}, YMM2/M256/M32BCST, IMM8 */
	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 1, 1) "vprorq\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK),       /*   EVEX.256.66.0F.W1 72 /0 IB VPRORQ YMM1{K1}{Z}, YMM2/M256/M64BCST, IMM8 */
	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 0, 2) "vprord\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK),       /*   EVEX.512.66.0F.W0 72 /0 IB VPRORD ZMM1{K1}{Z}, ZMM2/M512/M32BCST, IMM8 */
	I(0x72, IF_VEX|IF_66|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 1, 2) "vprorq\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK),       /*   EVEX.512.66.0F.W1 72 /0 IB VPRORQ ZMM1{K1}{Z}, ZMM2/M512/M64BCST, IMM8 */
	I(0x14, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0)         "vprorvd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 14 /R VPRORVD XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x14, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0)         "vprorvq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 14 /R VPRORVQ XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x14, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1)         "vprorvd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 14 /R VPRORVD YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x14, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1)         "vprorvq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 14 /R VPRORVQ YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x14, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2)         "vprorvd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 14 /R VPRORVD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST */
	I(0x14, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2)         "vprorvq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 14 /R VPRORVQ ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST */

	I(0xa0, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpscatterdd\tvm32x{k1}, xmm"), /* EVEX.128.66.0F38.W0 A0 /VSIB VPSCATTERDD VM32X{K1}, XMM1 */
	I(0xa0, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpscatterdd\tvm32y{k1}, ymm"), /* EVEX.256.66.0F38.W0 A0 /VSIB VPSCATTERDD VM32Y{K1}, YMM1 */
	I(0xa0, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpscatterdd\tvm32z{k1}, zmm"), /* EVEX.512.66.0F38.W0 A0 /VSIB VPSCATTERDD VM32Z{K1}, ZMM1 */
	I(0xa0, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpscatterdq\tvm32x{k1}, xmm"), /* EVEX.128.66.0F38.W1 A0 /VSIB VPSCATTERDQ VM32X{K1}, XMM1 */
	I(0xa0, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpscatterdq\tvm32x{k1}, ymm"), /* EVEX.256.66.0F38.W1 A0 /VSIB VPSCATTERDQ VM32X{K1}, YMM1 */
	I(0xa0, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpscatterdq\tvm32y{k1}, zmm"), /* EVEX.512.66.0F38.W1 A0 /VSIB VPSCATTERDQ VM32Y{K1}, ZMM1 */
	I(0xa1, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpscatterqd\tvm64x{k1}, xmm"), /* EVEX.128.66.0F38.W0 A1 /VSIB VPSCATTERQD VM64X{K1}, XMM1 */
	I(0xa1, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpscatterqd\tvm64y{k1}, xmm"), /* EVEX.256.66.0F38.W0 A1 /VSIB VPSCATTERQD VM64Y{K1}, XMM1 */
	I(0xa1, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpscatterqd\tvm64z{k1}, ymm"), /* EVEX.512.66.0F38.W0 A1 /VSIB VPSCATTERQD VM64Z{K1}, YMM1 */
	I(0xa1, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpscatterqq\tvm64x{k1}, xmm"), /* EVEX.128.66.0F38.W1 A1 /VSIB VPSCATTERQQ VM64X{K1}, XMM1 */
	I(0xa1, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpscatterqq\tvm64y{k1}, ymm"), /* EVEX.256.66.0F38.W1 A1 /VSIB VPSCATTERQQ VM64Y{K1}, YMM1 */
	I(0xa1, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpscatterqq\tvm64z{k1}, zmm"), /* EVEX.512.66.0F38.W1 A1 /VSIB VPSCATTERQQ VM64Z{K1}, ZMM1 */

	I(0x25, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpternlogd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F3A.W0 25 /R IB VPTERNLOGD XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST, IMM8 */
	I(0x25, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpternlogd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F3A.W0 25 /R IB VPTERNLOGD YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST, IMM8 */
	I(0x25, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpternlogd\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F3A.W0 25 /R IB VPTERNLOGD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST, IMM8 */
	I(0x25, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpternlogq\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0F3A.W1 25 /R IB VPTERNLOGQ XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST, IMM8 */
	I(0x25, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpternlogq\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F3A.W1 25 /R IB VPTERNLOGQ YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST, IMM8 */
	I(0x25, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpternlogq\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F3A.W1 25 /R IB VPTERNLOGQ ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST, IMM8 */

	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vptestmb\t" OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0F38.W0 26 /R VPTESTMB K2{K1}, XMM2, XMM3/M128 */
	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vptestmb\t" OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0F38.W0 26 /R VPTESTMB K2{K1}, YMM2, YMM3/M256 */
	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vptestmb\t" OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F38.W0 26 /R VPTESTMB K2{K1}, ZMM2, ZMM3/M512 */
	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vptestmw\t" OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0F38.W1 26 /R VPTESTMW K2{K1}, XMM2, XMM3/M128 */
	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vptestmw\t" OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0F38.W1 26 /R VPTESTMW K2{K1}, YMM2, YMM3/M256 */
	I(0x26, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vptestmw\t" OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F38.W1 26 /R VPTESTMW K2{K1}, ZMM2, ZMM3/M512 */
	I(0x27, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vptestmd\t" OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0F38.W0 27 /R VPTESTMD K2{K1}, XMM2, XMM3/M128/M32BCST */
	I(0x27, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vptestmd\t" OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0F38.W0 27 /R VPTESTMD K2{K1}, YMM2, YMM3/M256/M32BCST */
	I(0x27, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vptestmd\t" OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F38.W0 27 /R VPTESTMD K2{K1}, ZMM2, ZMM3/M512/M32BCST */
	I(0x27, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vptestmq\t" OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0F38.W1 27 /R VPTESTMQ K2{K1}, XMM2, XMM3/M128/M64BCST */
	I(0x27, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vptestmq\t" OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0F38.W1 27 /R VPTESTMQ K2{K1}, YMM2, YMM3/M256/M64BCST */
	I(0x27, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vptestmq\t" OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0F38.W1 27 /R VPTESTMQ K2{K1}, ZMM2, ZMM3/M512/M64BCST */

	I(0x26, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vptestnmb\t" OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.F3.0F38.W0 26 /R VPTESTNMB K2{K1}, XMM2, XMM3/M128 */
	I(0x26, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vptestnmb\t" OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.F3.0F38.W0 26 /R VPTESTNMB K2{K1}, YMM2, YMM3/M256 */
	I(0x26, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vptestnmb\t" OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.F3.0F38.W0 26 /R VPTESTNMB K2{K1}, ZMM2, ZMM3/M512 */
	I(0x26, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vptestnmw\t" OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.F3.0F38.W1 26 /R VPTESTNMW K2{K1}, XMM2, XMM3/M128 */
	I(0x26, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vptestnmw\t" OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.F3.0F38.W1 26 /R VPTESTNMW K2{K1}, YMM2, YMM3/M256 */
	I(0x26, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vptestnmw\t" OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.F3.0F38.W1 26 /R VPTESTNMW K2{K1}, ZMM2, ZMM3/M512 */
	I(0x27, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vptestnmd\t" OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.F3.0F38.W0 27 /R VPTESTNMD K2{K1}, XMM2, XMM3/M128/M32BCST */
	I(0x27, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vptestnmd\t" OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.F3.0F38.W0 27 /R VPTESTNMD K2{K1}, YMM2, YMM3/M256/M32BCST */
	I(0x27, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vptestnmd\t" OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.F3.0F38.W0 27 /R VPTESTNMD K2{K1}, ZMM2, ZMM3/M512/M32BCST */
	I(0x27, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vptestnmq\t" OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.F3.0F38.W1 27 /R VPTESTNMQ K2{K1}, XMM2, XMM3/M128/M64BCST */
	I(0x27, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vptestnmq\t" OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.F3.0F38.W1 27 /R VPTESTNMQ K2{K1}, YMM2, YMM3/M256/M64BCST */
	I(0x27, IF_VEX|IF_F3|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vptestnmq\t" OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.F3.0F38.W1 27 /R VPTESTNMQ K2{K1}, ZMM2, ZMM3/M512/M64BCST */

	I(0x50, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vrangepd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),         /* EVEX.128.66.0F3A.W1 50 /R IB VRANGEPD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST, IMM8 */
	I(0x50, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vrangepd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),         /* EVEX.256.66.0F3A.W1 50 /R IB VRANGEPD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST, IMM8 */
	I(0x50, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vrangepd\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F3A.W1 50 /R IB VRANGEPD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{SAE}, IMM8 */

	I(0x50, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vrangeps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),         /* EVEX.128.66.0F3A.W0 50 /R IB VRANGEPS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST, IMM8 */
	I(0x50, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vrangeps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),         /* EVEX.256.66.0F3A.W0 50 /R IB VRANGEPS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST, IMM8 */
	I(0x50, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vrangeps\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F3A.W0 50 /R IB VRANGEPS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{SAE}, IMM8 */

	I(0x51, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vrangesd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F3A.W1 51 /R VRANGESD XMM1{K1}{Z}, XMM2, XMM3/M64{SAE}, IMM8 */

	I(0x51, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vrangess\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F3A.W0 51 /R VRANGESS XMM1{K1}{Z}, XMM2, XMM3/M32{SAE}, IMM8 */

	I(0x4c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vrcp14pd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 4C /R VRCP14PD XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x4c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vrcp14pd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 4C /R VRCP14PD YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x4c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vrcp14pd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 4C /R VRCP14PD ZMM1{K1}{Z}, ZMM2/M512/M64BCST */

	I(0x4c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vrcp14ps\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 4C /R VRCP14PS XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x4c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vrcp14ps\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 4C /R VRCP14PS YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x4c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vrcp14ps\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 4C /R VRCP14PS ZMM1{K1}{Z}, ZMM2/M512/M32BCST */

	I(0x4d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vrcp14sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.66.0F38.W1 4D /R VRCP14SD XMM1{K1}{Z}, XMM2, XMM3/M64 */

	I(0x4d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vrcp14ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.66.0F38.W0 4D /R VRCP14SS XMM1{K1}{Z}, XMM2, XMM3/M32 */

	I(0x56, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vreducepd\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F3A.W1 56 /R IB VREDUCEPD XMM1{K1}{Z}, XMM2/M128/M64BCST, IMM8 */
	I(0x56, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vreducepd\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F3A.W1 56 /R IB VREDUCEPD YMM1{K1}{Z}, YMM2/M256/M64BCST, IMM8 */
	I(0x56, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vreducepd\t" OP_U8 OP_RM256_YMM "{sae}" OP_RYMM_MASK), /* EVEX.512.66.0F3A.W1 56 /R IB VREDUCEPD ZMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE}, IMM8 */

	I(0x56, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vreduceps\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F3A.W0 56 /R IB VREDUCEPS XMM1{K1}{Z}, XMM2/M128/M32BCST, IMM8 */
	I(0x56, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vreduceps\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F3A.W0 56 /R IB VREDUCEPS YMM1{K1}{Z}, YMM2/M256/M32BCST, IMM8 */
	I(0x56, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vreduceps\t" OP_U8 OP_RM256_YMM "{sae}" OP_RYMM_MASK), /* EVEX.512.66.0F3A.W0 56 /R IB VREDUCEPS ZMM1{K1}{Z}, ZMM2/M512/M32BCST{SAE}, IMM8 */

	I(0x57, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vreducesd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F3A.W1 57 /R VREDUCESD XMM1{K1}{Z}, XMM2, XMM3/M64{SAE}, IMM8 */

	I(0x57, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "/ib vreducess " OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F3A.W0 57 /R /IB VREDUCESS XMM1{K1}{Z}, XMM2, XMM3/M32{SAE}, IMM8 */

	I(0x09, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vrndscalepd\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F3A.W1 09 /R IB VRNDSCALEPD XMM1{K1}{Z}, XMM2/M128/M64BCST, IMM8 */
	I(0x09, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vrndscalepd\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F3A.W1 09 /R IB VRNDSCALEPD YMM1{K1}{Z}, YMM2/M256/M64BCST, IMM8 */
	I(0x09, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vrndscalepd\t" OP_U8 OP_RM256_YMM "{sae}" OP_RYMM_MASK), /* EVEX.512.66.0F3A.W1 09 /R IB VRNDSCALEPD ZMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE}, IMM8 */

	I(0x08, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vrndscaleps\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK),         /* EVEX.128.66.0F3A.W0 08 /R IB VRNDSCALEPS XMM1{K1}{Z}, XMM2/M128/M32BCST, IMM8 */
	I(0x08, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vrndscaleps\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK),         /* EVEX.256.66.0F3A.W0 08 /R IB VRNDSCALEPS YMM1{K1}{Z}, YMM2/M256/M32BCST, IMM8 */
	I(0x08, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vrndscaleps\t" OP_U8 OP_RM256_YMM "{sae}" OP_RYMM_MASK), /* EVEX.512.66.0F3A.W0 08 /R IB VRNDSCALEPS ZMM1{K1}{Z}, ZMM2/M512/M32BCST{SAE}, IMM8 */

	I(0x0b, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vrndscalesd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F3A.W1 0B /R IB VRNDSCALESD XMM1{K1}{Z}, XMM2, XMM3/M64{SAE}, IMM8 */

	I(0x0a, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vrndscaless\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F3A.W0 0A /R IB VRNDSCALESS XMM1{K1}{Z}, XMM2, XMM3/M32{SAE}, IMM8 */

	I(0x4e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vrsqrt14pd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W1 4E /R VRSQRT14PD XMM1{K1}{Z}, XMM2/M128/M64BCST */
	I(0x4e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vrsqrt14pd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W1 4E /R VRSQRT14PD YMM1{K1}{Z}, YMM2/M256/M64BCST */
	I(0x4e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vrsqrt14pd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W1 4E /R VRSQRT14PD ZMM1{K1}{Z}, ZMM2/M512/M64BCST */

	I(0x4e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vrsqrt14ps\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0F38.W0 4E /R VRSQRT14PS XMM1{K1}{Z}, XMM2/M128/M32BCST */
	I(0x4e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vrsqrt14ps\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0F38.W0 4E /R VRSQRT14PS YMM1{K1}{Z}, YMM2/M256/M32BCST */
	I(0x4e, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vrsqrt14ps\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0F38.W0 4E /R VRSQRT14PS ZMM1{K1}{Z}, ZMM2/M512/M32BCST */

	I(0x4f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vrsqrt14sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.66.0F38.W1 4F /R VRSQRT14SD XMM1{K1}{Z}, XMM2, XMM3/M64 */

	I(0x4f, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vrsqrt14ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.66.0F38.W0 4F /R VRSQRT14SS XMM1{K1}{Z}, XMM2, XMM3/M32 */

	I(0x2c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vscalefpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W1 2C /R VSCALEFPD XMM1{K1}{Z}, XMM2, XMM3/M128/M64BCST */
	I(0x2c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vscalefpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W1 2C /R VSCALEFPD YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST */
	I(0x2c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vscalefpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W1 2C /R VSCALEFPD ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST{ER} */

	I(0x2c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vscalefps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0F38.W0 2C /R VSCALEFPS XMM1{K1}{Z}, XMM2, XMM3/M128/M32BCST */
	I(0x2c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vscalefps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.66.0F38.W0 2C /R VSCALEFPS YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST */
	I(0x2c, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vscalefps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK "{er}"), /* EVEX.512.66.0F38.W0 2C /R VSCALEFPS ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST{ER} */

	I(0x2d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vscalefsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W1 2D /R VSCALEFSD XMM1{K1}{Z}, XMM2, XMM3/M64{ER} */

	I(0x2d, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vscalefss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{er}"), /* EVEX.LIG.66.0F38.W0 2D /R VSCALEFSS XMM1{K1}{Z}, XMM2, XMM3/M32{ER} */

	I(0xa2, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vscatterdps\tvm32x{k1}, xmm"), /* EVEX.128.66.0F38.W0 A2 /VSIB VSCATTERDPS VM32X{K1}, XMM1 */
	I(0xa2, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vscatterdps\tvm32y{k1}, ymm"), /* EVEX.256.66.0F38.W0 A2 /VSIB VSCATTERDPS VM32Y{K1}, YMM1 */
	I(0xa2, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vscatterdps\tvm32z{k1}, zmm"), /* EVEX.512.66.0F38.W0 A2 /VSIB VSCATTERDPS VM32Z{K1}, ZMM1 */
	I(0xa2, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vscatterdpd\tvm32x{k1}, xmm"), /* EVEX.128.66.0F38.W1 A2 /VSIB VSCATTERDPD VM32X{K1}, XMM1 */
	I(0xa2, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vscatterdpd\tvm32x{k1}, ymm"), /* EVEX.256.66.0F38.W1 A2 /VSIB VSCATTERDPD VM32X{K1}, YMM1 */
	I(0xa2, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vscatterdpd\tvm32y{k1}, zmm"), /* EVEX.512.66.0F38.W1 A2 /VSIB VSCATTERDPD VM32Y{K1}, ZMM1 */
	I(0xa3, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vscatterqps\tvm64x{k1}, xmm"), /* EVEX.128.66.0F38.W0 A3 /VSIB VSCATTERQPS VM64X{K1}, XMM1 */
	I(0xa3, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vscatterqps\tvm64y{k1}, xmm"), /* EVEX.256.66.0F38.W0 A3 /VSIB VSCATTERQPS VM64Y{K1}, XMM1 */
	I(0xa3, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vscatterqps\tvm64z{k1}, ymm"), /* EVEX.512.66.0F38.W0 A3 /VSIB VSCATTERQPS VM64Z{K1}, YMM1 */
	I(0xa3, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vscatterqpd\tvm64x{k1}, xmm"), /* EVEX.128.66.0F38.W1 A3 /VSIB VSCATTERQPD VM64X{K1}, XMM1 */
	I(0xa3, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vscatterqpd\tvm64y{k1}, ymm"), /* EVEX.256.66.0F38.W1 A3 /VSIB VSCATTERQPD VM64Y{K1}, YMM1 */
	I(0xa3, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vscatterqpd\tvm64z{k1}, zmm"), /* EVEX.512.66.0F38.W1 A3 /VSIB VSCATTERQPD VM64Z{K1}, ZMM1 */

	I(0x23, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vshuff32x4\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F3A.W0 23 /R IB VSHUFF32X4 YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST, IMM8 */
	I(0x23, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vshuff32x4\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F3A.W0 23 /R IB VSHUFF32X4 ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST, IMM8 */
	I(0x23, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vshuff64x2\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F3A.W1 23 /R IB VSHUFF64X2 YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST, IMM8 */
	I(0x23, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vshuff64x2\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F3A.W1 23 /R IB VSHUFF64X2 ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST, IMM8 */
	I(0x43, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vshufi32x4\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F3A.W0 43 /R IB VSHUFI32X4 YMM1{K1}{Z}, YMM2, YMM3/M256/M32BCST, IMM8 */
	I(0x43, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vshufi32x4\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F3A.W0 43 /R IB VSHUFI32X4 ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M32BCST, IMM8 */
	I(0x43, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vshufi64x2\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0F3A.W1 43 /R IB VSHUFI64X2 YMM1{K1}{Z}, YMM2, YMM3/M256/M64BCST, IMM8 */
	I(0x43, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vshufi64x2\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0F3A.W1 43 /R IB VSHUFI64X2 ZMM1{K1}{Z}, ZMM2, ZMM3/M512/M64BCST, IMM8 */

	I(0x9a, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "v4fmaddps\tzmm1{k1}{z}, zmm+3, m"),  /* EVEX.512.F2.0F38.W0 9A /R V4FMADDPS ZMM1{K1}{Z}, ZMM2+3, M128 */
	I(0xaa, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "v4fnmaddps\tzmm1{k1}{z}, zmm+3, m"), /* EVEX.512.F2.0F38.W0 AA /R V4FNMADDPS ZMM1{K1}{Z}, ZMM2+3, M128 */

	I(0x9b, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "v4fmaddss\txmm{k1}{z}, xmm2+3, m"),  /* EVEX.LIG.F2.0F38.W0 9B /R V4FMADDSS XMM1{K1}{Z}, XMM2+3, M128 */
	I(0xab, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "v4fnmaddss\txmm{k1}{z}, xmm2+3, m"), /* EVEX.LIG.F2.0F38.W0 AB /R V4FNMADDSS XMM1{K1}{Z}, XMM2+3, M128 */

	I(0xc8, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vexp2pd\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F38.W1 C8 /R VEXP2PD ZMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE} */

	I(0xc8, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vexp2ps\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F38.W0 C8 /R VEXP2PS ZMM1{K1}{Z}, ZMM2/M512/M32BCST{SAE} */

	I(0xc6, IF_VEX|IF_66|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 0, 2) "/vsib vgatherpf0dps vm32z{k1}"), /* EVEX.512.66.0F38.W0 C6 /1 /VSIB VGATHERPF0DPS VM32Z{K1} */
	I(0xc7, IF_VEX|IF_66|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 0, 2) "/vsib vgatherpf0qps vm64z{k1}"), /* EVEX.512.66.0F38.W0 C7 /1 /VSIB VGATHERPF0QPS VM64Z{K1} */
	I(0xc6, IF_VEX|IF_66|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 1, 2) "/vsib vgatherpf0dpd vm32y{k1}"), /* EVEX.512.66.0F38.W1 C6 /1 /VSIB VGATHERPF0DPD VM32Y{K1} */
	I(0xc7, IF_VEX|IF_66|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 1, 2) "/vsib vgatherpf0qpd vm64z{k1}"), /* EVEX.512.66.0F38.W1 C7 /1 /VSIB VGATHERPF0QPD VM64Z{K1} */

	I(0xc6, IF_VEX|IF_66|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 0, 2) "/vsib vgatherpf1dps vm32z{k1}"), /* EVEX.512.66.0F38.W0 C6 /2 /VSIB VGATHERPF1DPS VM32Z{K1} */
	I(0xc7, IF_VEX|IF_66|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 0, 2) "/vsib vgatherpf1qps vm64z{k1}"), /* EVEX.512.66.0F38.W0 C7 /2 /VSIB VGATHERPF1QPS VM64Z{K1} */
	I(0xc6, IF_VEX|IF_66|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 1, 2) "/vsib vgatherpf1dpd vm32y{k1}"), /* EVEX.512.66.0F38.W1 C6 /2 /VSIB VGATHERPF1DPD VM32Y{K1} */
	I(0xc7, IF_VEX|IF_66|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 1, 2) "/vsib vgatherpf1qpd vm64z{k1}"), /* EVEX.512.66.0F38.W1 C7 /2 /VSIB VGATHERPF1QPD VM64Z{K1} */

	I(0x52, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vp4dpwssd\tzmm1{k1}{z}, zmm+3, m"), /* EVEX.512.F2.0F38.W0 52 /R VP4DPWSSD ZMM1{K1}{Z}, ZMM2+3, M128 */

	I(0x53, IF_VEX|IF_F2|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vp4dpwssds\tzmm1{k1}{z}, zmm+3, m"), /* EVEX.512.F2.0F38.W0 53 /R VP4DPWSSDS ZMM1{K1}{Z}, ZMM2+3, M128 */

	I(0xca, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vrcp28pd\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F38.W1 CA /R VRCP28PD ZMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE} */

	I(0xca, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vrcp28ps\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F38.W0 CA /R VRCP28PS ZMM1{K1}{Z}, ZMM2/M512/M32BCST{SAE} */

	I(0xcb, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vrcp28sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F38.W1 CB /R VRCP28SD XMM1{K1}{Z}, XMM2, XMM3/M64{SAE} */

	I(0xcb, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vrcp28ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK "{sae}"), /* EVEX.LIG.66.0F38.W0 CB /R VRCP28SS XMM1{K1}{Z}, XMM2, XMM3/M32{SAE} */

	I(0xcc, IF_VEX|IF_66|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vrsqrt28pd\t" OP_RM512_ZMM OP_RZMM_MASK "{sae}"), /* EVEX.512.66.0F38.W1 CC /R VRSQRT28PD ZMM1{K1}{Z}, ZMM2/M512/M64BCST{SAE} */
#endif


/* clang-format off */
PRIVATE struct instruction const ops_0f38[] = {
/*[[[start:ops_0f38]]]*/
	/* REMINDER: After adding/removing instructions from this table, you must run:
	 *           $ deemon -F kos/src/libdisasm/x86.c */

	/* 0x0f38XX */

	I(0x00, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpshufb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 00 /r vpshufb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x00, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpshufb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 00 /r vpshufb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x00, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpshufb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 00 /r vpshufb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x00, IF_MODRM,                                    "pshufb\t" OP_RM64_MM OP_RMM),                     /*                0f 38 00 /r pshufb mm1, mm2/m64 */
	I(0x00, IF_66|IF_MODRM,                              "pshufb\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 00 /r pshufb xmm1, xmm2/m128 */

	I(0x01, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphaddw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 01 /r vphaddw xmm1, xmm2, xmm3/m128 */
	I(0x01, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphaddw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 01 /r vphaddw ymm1, ymm2, ymm3/m256 */
	I(0x01, IF_MODRM,                                    "phaddw\t" OP_RM64_MM OP_RMM),                /*               0f 38 01 /r phaddw mm1, mm2/m64 */
	I(0x01, IF_66|IF_MODRM,                              "phaddw\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 01 /r phaddw xmm1, xmm2/m128 */

	I(0x02, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphaddd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 02 /r vphaddd xmm1, xmm2, xmm3/m128 */
	I(0x02, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphaddd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 02 /r vphaddd ymm1, ymm2, ymm3/m256 */
	I(0x02, IF_MODRM,                                    "phaddd\t" OP_RM64_MM OP_RMM),                /*               0f 38 02 /r phaddd mm1, mm2/m64 */
	I(0x02, IF_66|IF_MODRM,                              "phaddd\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 02 /r phaddd xmm1, xmm2/m128 */

	I(0x03, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphaddsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 03 /r vphaddsw xmm1, xmm2, xmm3/m128 */
	I(0x03, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphaddsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 03 /r vphaddsw ymm1, ymm2, ymm3/m256 */
	I(0x03, IF_MODRM,                                    "phaddsw\t" OP_RM64_MM OP_RMM),                /*               0f 38 03 /r phaddsw mm1, mm2/m64 */
	I(0x03, IF_66|IF_MODRM,                              "phaddsw\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 03 /r phaddsw xmm1, xmm2/m128 */

	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMADDUBSW_XMM)), /* EVEX.128.66.0f38.WIG 04 /r vpmaddubsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMADDUBSW_YMM)), /* EVEX.256.66.0f38.WIG 04 /r vpmaddubsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMADDUBSW_ZMM)), /* EVEX.512.66.0f38.WIG 04 /r vpmaddubsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x04, IF_MODRM,              "pmaddubsw\t" OP_RM64_MM OP_RMM),                        /*                0f 38 04 /r pmaddubsw mm1, mm2/m64 */
	I(0x04, IF_66|IF_MODRM,        "pmaddubsw\t" OP_RM128_XMM OP_RXMM),                     /*             66 0f 38 04 /r pmaddubsw xmm1, xmm2/m128 */

	I(0x05, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphsubw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 05 /r vphsubw xmm1, xmm2, xmm3/m128 */
	I(0x05, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphsubw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 05 /r vphsubw ymm1, ymm2, ymm3/m256 */
	I(0x05, IF_MODRM,                                    "phsubw\t" OP_RM64_MM OP_RMM),                /*               0f 38 05 /r phsubw mm1, mm2/m64 */
	I(0x05, IF_66|IF_MODRM,                              "phsubw\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 05 /r phsubw xmm1, xmm2/m128 */

	I(0x06, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphsubd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 06 /r vphsubd xmm1, xmm2, xmm3/m128 */
	I(0x06, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphsubd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 06 /r vphsubd ymm1, ymm2, ymm3/m256 */
	I(0x06, IF_MODRM,                                    "phsubd\t" OP_RM64_MM OP_RMM),                /*               0f 38 06 /r phsubd mm1, mm2/m64 */
	I(0x06, IF_66|IF_MODRM,                              "phsubd\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 06 /r phsubd xmm1, xmm2/m128 */

	I(0x07, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphsubsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 07 /r vphsubsw xmm1, xmm2, xmm3/m128 */
	I(0x07, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphsubsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 07 /r vphsubsw ymm1, ymm2, ymm3/m256 */
	I(0x07, IF_MODRM,                                    "phsubsw\t" OP_RM64_MM OP_RMM),                /*               0f 38 07 /r phsubsw mm1, mm2/m64 */
	I(0x07, IF_66|IF_MODRM,                              "phsubsw\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 07 /r phsubsw xmm1, xmm2/m128 */

	I(0x08, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsignb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 08 /r vpsignb xmm1, xmm2, xmm3/m128 */
	I(0x08, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsignb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 08 /r vpsignb ymm1, ymm2, ymm3/m256 */
	I(0x08, IF_MODRM,                                    "psignb\t" OP_RM64_MM OP_RMM),                /*               0f 38 08 /r psignb mm1, mm2/m64 */
	I(0x08, IF_66|IF_MODRM,                              "psignb\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 08 /r psignb xmm1, xmm2/m128 */

	I(0x09, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsignw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 09 /r vpsignw xmm1, xmm2, xmm3/m128 */
	I(0x09, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsignw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 09 /r vpsignw ymm1, ymm2, ymm3/m256 */
	I(0x09, IF_MODRM,                                    "psignw\t" OP_RM64_MM OP_RMM),                /*               0f 38 09 /r psignw mm1, mm2/m64 */
	I(0x09, IF_66|IF_MODRM,                              "psignw\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 09 /r psignw xmm1, xmm2/m128 */

	I(0x0a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsignd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 0a /r vpsignd xmm1, xmm2, xmm3/m128 */
	I(0x0a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsignd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 0a /r vpsignd ymm1, ymm2, ymm3/m256 */
	I(0x0a, IF_MODRM,                                    "psignd\t" OP_RM64_MM OP_RMM),                /*               0f 38 0a /r psignd mm1, mm2/m64 */
	I(0x0a, IF_66|IF_MODRM,                              "psignd\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 0a /r psignd xmm1, xmm2/m128 */

	I(0x0b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmulhrsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 0b /r vpmulhrsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x0b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmulhrsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 0b /r vpmulhrsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x0b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmulhrsw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 0b /r vpmulhrsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x0b, IF_MODRM,                                    "pmulhrsw\t" OP_RM64_MM OP_RMM),                     /*                0f 38 0b /r pmulhrsw mm1, mm2/m64 */
	I(0x0b, IF_66|IF_MODRM,                              "pmulhrsw\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 0b /r pmulhrsw xmm1, xmm2/m128 */

	I(0x0c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermilps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 0c /r vpermilps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x0c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermilps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 0c /r vpermilps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x0c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermilps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 0c /r vpermilps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 0) "vpermilpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.W0 0d /r vpermilpd xmm1, xmm2, xmm3/m128 */
	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 1) "vpermilpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.W0 0d /r vpermilpd ymm1, ymm2, ymm3/m256 */
	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermilpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 0d /r vpermilpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermilpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 0d /r vpermilpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermilpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 0d /r vpermilpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x0e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vtestps\t" OP_RM128_XMM OP_RXMM), /* VEX.128.66.0f38.W0 0e /r vtestps xmm1, xmm2/m128 */
	I(0x0e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vtestps\t" OP_RM256_YMM OP_RYMM), /* VEX.256.66.0f38.W0 0e /r vtestps ymm1, ymm2/m256 */

	I(0x0f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vtestpd\t" OP_RM128_XMM OP_RXMM), /* VEX.128.66.0f38.W0 0f /r vtestpd xmm1, xmm2/m128 */
	I(0x0f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vtestpd\t" OP_RM256_YMM OP_RYMM), /* VEX.256.66.0f38.W0 0f /r vtestpd ymm1, ymm2/m256 */

	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsrlvw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 10 /r vpsrlvw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsrlvw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 10 /r vpsrlvw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsrlvw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 10 /r vpsrlvw zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsravw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 11 /r vpsravw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsravw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 11 /r vpsravw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsravw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 11 /r vpsravw zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x12, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsllvw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 12 /r vpsllvw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x12, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsllvw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 12 /r vpsllvw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x12, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsllvw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 12 /r vpsllvw zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 16 /r vpermpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 16 /r vpermpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 16 /r vpermps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 16 /r vpermps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x17, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vptest\t" OP_RM128_XMM OP_RXMM), /* VEX.128.66.0f38.WIG 17 /r vptest xmm1, xmm2/m128 */
	I(0x17, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vptest\t" OP_RM256_YMM OP_RYMM), /* VEX.256.66.0f38.WIG 17 /r vptest ymm1, ymm2/m256 */
	I(0x17, IF_66|IF_MODRM,                              "ptest\t" OP_RM128_XMM OP_RXMM),  /*            66 0f 38 17 /r ptest xmm1, xmm2/m128 */

	I(0x1c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpabsb\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 1c /r vpabsb xmm1{k1}{z}, xmm2/m128 */
	I(0x1c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpabsb\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 1c /r vpabsb ymm1{k1}{z}, ymm2/m256 */
	I(0x1c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpabsb\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 1c /r vpabsb zmm1{k1}{z}, zmm2/m512 */
	I(0x1c, IF_MODRM,                                    "pabsb\t" OP_RM64_MM OP_RMM),          /*                0f 38 1c /r pabsb mm1, mm2/m64 */
	I(0x1c, IF_66|IF_MODRM,                              "pabsb\t" OP_RM128_XMM OP_RXMM),       /*             66 0f 38 1c /r pabsb xmm1, xmm2/m128 */

	I(0x1d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpabsw\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 1d /r vpabsw xmm1{k1}{z}, xmm2/m128 */
	I(0x1d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpabsw\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 1d /r vpabsw ymm1{k1}{z}, ymm2/m256 */
	I(0x1d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpabsw\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 1d /r vpabsw zmm1{k1}{z}, zmm2/m512 */
	I(0x1d, IF_MODRM,                                    "pabsw\t" OP_RM64_MM OP_RMM),          /*                0f 38 1d /r pabsw mm1, mm2/m64 */
	I(0x1d, IF_66|IF_MODRM,                              "pabsw\t" OP_RM128_XMM OP_RXMM),       /*             66 0f 38 1d /r pabsw xmm1, xmm2/m128 */

	I(0x1e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpabsd\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.66.0f38.WIG 1e /r vpabsd xmm1, xmm2/m128 */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpabsd\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.66.0f38.WIG 1e /r vpabsd ymm1, ymm2/m256 */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpabsd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  1e /r vpabsd xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpabsd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  1e /r vpabsd ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpabsd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  1e /r vpabsd zmm1{k1}{z}, zmm2/m512/m32bcst */
	I(0x1e, IF_MODRM,                                    "pabsd\t" OP_RM64_MM OP_RMM),          /*                0f 38 1e /r pabsd mm1, mm2/m64 */
	I(0x1e, IF_66|IF_MODRM,                              "pabsd\t" OP_RM128_XMM OP_RXMM),       /*             66 0f 38 1e /r pabsd xmm1, xmm2/m128 */

	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpabsq\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  1f /r vpabsq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpabsq\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  1f /r vpabsq ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpabsq\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  1f /r vpabsq zmm1{k1}{z}, zmm2/m512/m64bcst */

	I(0x20, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVSXBW_RXMM)), /* EVEX.128.66.0f38.WIG 20 /r vpmovsxbw xmm1{k1}{z}, xmm2/m64 */
	I(0x20, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVSXBW_RYMM)), /* EVEX.256.66.0f38.WIG 20 /r vpmovsxbw ymm1{k1}{z}, xmm2/m128 */
	I(0x20, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVSXBW_RZMM)), /* EVEX.512.66.0f38.WIG 20 /r vpmovsxbw zmm1{k1}{z}, ymm2/m256 */
	I(0x20, IF_66|IF_MODRM,        "pmovsxbw\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 20 /r pmovsxbw xmm1, xmm2/m64 */

	I(0x21, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVSXBD_RXMM)), /* EVEX.128.66.0f38.WIG 21 /r vpmovsxbd xmm1{k1}{z}, xmm2/m32 */
	I(0x21, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVSXBD_RYMM)), /* EVEX.256.66.0f38.WIG 21 /r vpmovsxbd ymm1{k1}{z}, xmm2/m64 */
	I(0x21, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVSXBD_RZMM)), /* EVEX.512.66.0f38.WIG 21 /r vpmovsxbd zmm1{k1}{z}, xmm2/m128 */
	I(0x21, IF_66|IF_MODRM,        "pmovsxbd\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 21 /r pmovsxbd xmm1, xmm2/m32 */

	I(0x22, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVSXBQ_RXMM)), /* EVEX.128.66.0f38.WIG 22 /r vpmovsxbq xmm1{k1}{z}, xmm2/m16 */
	I(0x22, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVSXBQ_RYMM)), /* EVEX.256.66.0f38.WIG 22 /r vpmovsxbq ymm1{k1}{z}, xmm2/m32 */
	I(0x22, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVSXBQ_RZMM)), /* EVEX.512.66.0f38.WIG 22 /r vpmovsxbq zmm1{k1}{z}, xmm2/m64 */
	I(0x22, IF_66|IF_MODRM,        "pmovsxbq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 22 /r pmovsxbq xmm1, xmm2/m16 */

	I(0x23, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVSXWD_RXMM)), /* EVEX.128.66.0f38.WIG 23 /r vpmovsxwd xmm1{k1}{z}, xmm2/m64 */
	I(0x23, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVSXWD_RYMM)), /* EVEX.256.66.0f38.WIG 23 /r vpmovsxwd ymm1{k1}{z}, xmm2/m128 */
	I(0x23, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVSXWD_RZMM)), /* EVEX.512.66.0f38.WIG 23 /r vpmovsxwd zmm1{k1}{z}, ymm2/m256 */
	I(0x23, IF_66|IF_MODRM,        "pmovsxwd\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 23 /r pmovsxwd xmm1, xmm2/m64 */

	I(0x24, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVSXWQ_RXMM)), /* EVEX.128.66.0f38.WIG 24 /r vpmovsxwq xmm1{k1}{z}, xmm2/m32 */
	I(0x24, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVSXWQ_RYMM)), /* EVEX.256.66.0f38.WIG 24 /r vpmovsxwq ymm1{k1}{z}, xmm2/m64 */
	I(0x24, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVSXWQ_RZMM)), /* EVEX.512.66.0f38.WIG 24 /r vpmovsxwq zmm1{k1}{z}, xmm2/m128 */
	I(0x24, IF_66|IF_MODRM,        "pmovsxwq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 24 /r pmovsxwq xmm1, xmm2/m32 */

	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPMOVSXDQ_RXMM)), /*  VEX.128.66.0f38.WIG 25 /r vpmovsxdq xmm1, xmm2/m64 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPMOVSXDQ_RYMM)), /*  VEX.256.66.0f38.WIG 25 /r vpmovsxdq ymm1, xmm2/m128 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMOVSXDQ_RXMM)), /* EVEX.128.66.0f38.W0  25 /r vpmovsxdq xmm1{k1}{z}, xmm2/m64 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMOVSXDQ_RYMM)), /* EVEX.256.66.0f38.W0  25 /r vpmovsxdq ymm1{k1}{z}, xmm2/m128 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPMOVSXDQ_RZMM)), /* EVEX.512.66.0f38.W0  25 /r vpmovsxdq zmm1{k1}{z}, ymm2/m256 */
	I(0x25, IF_66|IF_MODRM,        "pmovsxdq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 25 /r pmovsxdq xmm1, xmm2/m64 */

	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpmuldq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 28 /r vpmuldq xmm1, xmm2, xmm3/m128 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpmuldq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 28 /r vpmuldq ymm1, ymm2, ymm3/m256 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmuldq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  28 /r vpmuldq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmuldq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  28 /r vpmuldq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmuldq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  28 /r vpmuldq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x28, IF_66|IF_MODRM,                              "pmuldq\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 28 /r pmuldq xmm1, xmm2/m128 */

	I(0x2a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VMOVNTDQA_XMM)), /*  VEX.128.66.0f38.WIG 2a /r vmovntdqa xmm1, m128 */
	I(0x2a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VMOVNTDQA_YMM)), /*  VEX.256.66.0f38.WIG 2a /r vmovntdqa ymm1, m256 */
	I(0x2a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVNTDQA_XMM)), /* EVEX.128.66.0f38.W0  2a /r vmovntdqa xmm1, m128 */
	I(0x2a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVNTDQA_YMM)), /* EVEX.256.66.0f38.W0  2a /r vmovntdqa ymm1, m256 */
	I(0x2a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVNTDQA_ZMM)), /* EVEX.512.66.0f38.W0  2a /r vmovntdqa zmm1, m512 */
	I(0x2a, IF_66|IF_MODRM,        "movntdqa\t" OP_MEM OP_RXMM),                           /*             66 0f 38 2a /r movntdqa xmm1, m128 */

	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpackusdw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /* VEX.128.66.0f38.WIG 2b /r vpackusdw xmm1, xmm2, xmm3/m128 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpackusdw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /* VEX.256.66.0f38.WIG 2b /r vpackusdw ymm1, ymm2, ymm3/m256 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpackusdw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 2b /r vpackusdw xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpackusdw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 2b /r vpackusdw ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpackusdw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 2b /r vpackusdw zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x2b, IF_66|IF_MODRM,                              "packusdw\t" OP_RM128_XMM OP_RXMM),                  /*            66 0f 38 2b /r packusdw xmm1, xmm2/m128 */

	I(0x30, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVZXBW_RXMM)), /* EVEX.128.66.0f38.WIG 30 /r vpmovzxbw xmm1{k1}{z}, xmm2/m64 */
	I(0x30, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVZXBW_RYMM)), /* EVEX.256.66.0f38.WIG 30 /r vpmovzxbw ymm1{k1}{z}, xmm2/m128 */
	I(0x30, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVZXBW_RZMM)), /* EVEX.512.66.0f38.WIG 30 /r vpmovzxbw zmm1{k1}{z}, ymm2/m256 */
	I(0x30, IF_66|IF_MODRM,        "pmovzxbw\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 30 /r pmovzxbw xmm1, xmm2/m64 */

	I(0x31, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVZXBD_RXMM)), /* EVEX.128.66.0f38.WIG 31 /r vpmovzxbd xmm1{k1}{z}, xmm2/m32 */
	I(0x31, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVZXBD_RYMM)), /* EVEX.256.66.0f38.WIG 31 /r vpmovzxbd ymm1{k1}{z}, xmm2/m64 */
	I(0x31, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVZXBD_RZMM)), /* EVEX.512.66.0f38.WIG 31 /r vpmovzxbd zmm1{k1}{z}, xmm2/m128 */
	I(0x31, IF_66|IF_MODRM,        "pmovzxbd\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 31 /r pmovzxbd xmm1, xmm2/m32 */

	I(0x32, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVZXBQ_RXMM)), /* EVEX.128.66.0f38.WIG 32 /r vpmovzxbq xmm1{k1}{z}, xmm2/m16 */
	I(0x32, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVZXBQ_RYMM)), /* EVEX.256.66.0f38.WIG 32 /r vpmovzxbq ymm1{k1}{z}, xmm2/m32 */
	I(0x32, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVZXBQ_RZMM)), /* EVEX.512.66.0f38.WIG 32 /r vpmovzxbq zmm1{k1}{z}, xmm2/m64 */
	I(0x32, IF_66|IF_MODRM,        "pmovzxbq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 32 /r pmovzxbq xmm1, xmm2/m16 */

	I(0x33, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVZXWD_RXMM)), /* EVEX.128.66.0f38.WIG 33 /r vpmovzxwd xmm1{k1}{z}, xmm2/m64 */
	I(0x33, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVZXWD_RYMM)), /* EVEX.256.66.0f38.WIG 33 /r vpmovzxwd ymm1{k1}{z}, xmm2/m128 */
	I(0x33, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVZXWD_RZMM)), /* EVEX.512.66.0f38.WIG 33 /r vpmovzxwd zmm1{k1}{z}, ymm2/m256 */
	I(0x33, IF_66|IF_MODRM,        "pmovzxwd\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 33 /r pmovzxwd xmm1, xmm2/m64 */

	I(0x34, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVZXWQ_RXMM)), /* EVEX.128.66.0f38.WIG 34 /r vpmovzxwq xmm1{k1}{z}, xmm2/m32 */
	I(0x34, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVZXWQ_RYMM)), /* EVEX.256.66.0f38.WIG 34 /r vpmovzxwq ymm1{k1}{z}, xmm2/m64 */
	I(0x34, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVZXWQ_RZMM)), /* EVEX.512.66.0f38.WIG 34 /r vpmovzxwq zmm1{k1}{z}, xmm2/m128 */
	I(0x34, IF_66|IF_MODRM,        "pmovzxwq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 34 /r pmovzxwq xmm1, xmm2/m32 */

	I(0x35, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPMOVZXDQ_RXMM)), /*  VEX.128.66.0f38.WIG 35 /r vpmovzxdq xmm1, xmm2/m64 */
	I(0x35, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPMOVZXDQ_RYMM)), /*  VEX.256.66.0f38.WIG 35 /r vpmovzxdq ymm1, xmm2/m128 */
	I(0x35, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMOVZXDQ_RXMM)), /* EVEX.128.66.0f38.W0  35 /r vpmovzxdq xmm1{k1}{z}, xmm2/m64 */
	I(0x35, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMOVZXDQ_RYMM)), /* EVEX.256.66.0f38.W0  35 /r vpmovzxdq ymm1{k1}{z}, xmm2/m128 */
	I(0x35, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPMOVZXDQ_RZMM)), /* EVEX.512.66.0f38.W0  35 /r vpmovzxdq zmm1{k1}{z}, ymm2/m256 */
	I(0x35, IF_66|IF_MODRM,        "pmovzxdq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 35 /r pmovzxdq xmm1, xmm2/m64 */

	I(0x36, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 36 /r vpermq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x36, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 36 /r vpermq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x36, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 36 /r vpermd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x36, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 36 /r vpermd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x38, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpminsb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 38 /r vpminsb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpminsb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 38 /r vpminsb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpminsb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 38 /r vpminsb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x38, IF_66|IF_MODRM,                              "pminsb\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 38 /r pminsb xmm1, xmm2/m128 */

	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpminsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 39 /r vpminsd xmm1, xmm2, xmm3/m128 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpminsd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 39 /r vpminsd ymm1, ymm2, ymm3/m256 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpminsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  39 /r vpminsd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpminsd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  39 /r vpminsd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpminsd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  39 /r vpminsd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpminsq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  39 /r vpminsq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpminsq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  39 /r vpminsq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpminsq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  39 /r vpminsq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x39, IF_66|IF_MODRM,                              "pminsd\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 39 /r pminsd xmm1, xmm2/m128 */

	I(0x3a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpminuw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 3a /r vpminuw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x3a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpminuw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 3a /r vpminuw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x3a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpminuw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 3a /r vpminuw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x3a, IF_66|IF_MODRM,                              "pminuw\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3a /r pminuw xmm1, xmm2/m128 */

	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpminud\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 3b /r vpminud xmm1, xmm2, xmm3/m128 */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpminud\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 3b /r vpminud ymm1, ymm2, ymm3/m256 */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpminud\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  3b /r vpminud xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpminud\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  3b /r vpminud ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpminud\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  3b /r vpminud zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpminuq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  3b /r vpminuq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpminuq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  3b /r vpminuq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpminuq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  3b /r vpminuq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x3b, IF_66|IF_MODRM,                              "pminud\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3b /r pminud xmm1, xmm2/m128 */

	I(0x3c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmaxsb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 3c /r vpmaxsb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x3c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmaxsb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 3c /r vpmaxsb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x3c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmaxsb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 3c /r vpmaxsb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x3c, IF_66|IF_MODRM,                              "pmaxsb\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3c /r pmaxsb xmm1, xmm2/m128 */

	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpmaxsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 3d /r vpmaxsd xmm1, xmm2, xmm3/m128 */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpmaxsd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 3d /r vpmaxsd ymm1, ymm2, ymm3/m256 */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmaxsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  3d /r vpmaxsd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmaxsd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  3d /r vpmaxsd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmaxsd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  3d /r vpmaxsd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmaxsq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  3d /r vpmaxsq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmaxsq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  3d /r vpmaxsq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmaxsq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  3d /r vpmaxsq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x3d, IF_66|IF_MODRM,                              "pmaxsd\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3d /r pmaxsd xmm1, xmm2/m128 */

	I(0x3e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmaxuw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 3e /r vpmaxuw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x3e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmaxuw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 3e /r vpmaxuw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x3e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmaxuw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 3e /r vpmaxuw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x3e, IF_66|IF_MODRM,                              "pmaxuw\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3e /r pmaxuw xmm1, xmm2/m128 */

	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpmaxud\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 3f /r vpmaxud xmm1, xmm2, xmm3/m128 */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpmaxud\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 3f /r vpmaxud ymm1, ymm2, ymm3/m256 */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmaxud\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  3f /r vpmaxud xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmaxud\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  3f /r vpmaxud ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmaxud\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  3f /r vpmaxud zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmaxuq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  3f /r vpmaxuq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmaxuq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  3f /r vpmaxuq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmaxuq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  3f /r vpmaxuq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x3f, IF_66|IF_MODRM,                              "pmaxud\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3f /r pmaxud xmm1, xmm2/m128 */

	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpmulld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 40 /r vpmulld xmm1, xmm2, xmm3/m128 */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpmulld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 40 /r vpmulld ymm1, ymm2, ymm3/m256 */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmulld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  40 /r vpmulld xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmulld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  40 /r vpmulld ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmulld\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  40 /r vpmulld zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmullq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  40 /r vpmullq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmullq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  40 /r vpmullq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmullq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  40 /r vpmullq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x40, IF_66|IF_MODRM,                              "pmulld\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 40 /r pmulld xmm1, xmm2/m128 */

	I(0x41, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPHMINPOSUW)), /* VEX.128.66.0f38.WIG 41 /r vphminposuw xmm1, xmm2/m128 */
	I(0x41, IF_66|IF_MODRM,        LONGREPR(LO_PHMINPOSUW)),                             /*            66 0f 38 41 /r phminposuw xmm1, xmm2/m128 */

	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsrlvd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 45 /r vpsrlvd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsrlvd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 45 /r vpsrlvd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsrlvd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 45 /r vpsrlvd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsrlvq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 45 /r vpsrlvq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsrlvq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 45 /r vpsrlvq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsrlvq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 45 /r vpsrlvq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsravd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 46 /r vpsravd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsravd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 46 /r vpsravd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsravd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 46 /r vpsravd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsravq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 46 /r vpsravq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsravq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 46 /r vpsravq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsravq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 46 /r vpsravq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsllvd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 47 /r vpsllvd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsllvd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 47 /r vpsllvd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsllvd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 47 /r vpsllvd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsllvq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 47 /r vpsllvq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsllvq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 47 /r vpsllvq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsllvq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 47 /r vpsllvq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x58, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBROADCASTD_XX)), /* EVEX.128.66.0f38.W0 58 /r vpbroadcastd xmm1{k1}{z}, xmm2/m32 */
	I(0x58, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBROADCASTD_XY)), /* EVEX.256.66.0f38.W0 58 /r vpbroadcastd ymm1{k1}{z}, xmm2/m32 */
	I(0x58, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPBROADCASTD_XZ)), /* EVEX.512.66.0f38.W0 58 /r vpbroadcastd zmm1{k1}{z}, xmm2/m32 */

	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 0), LO_VPBROADCASTQ_XX)),    /*  VEX.128.66.0f38.W0 59 /r vpbroadcastq xmm1, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VPBROADCASTQ_XY)),    /*  VEX.256.66.0f38.W0 59 /r vpbroadcastq ymm1, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPBROADCASTQ_XX)),    /* EVEX.128.66.0f38.W1 59 /r vpbroadcastq xmm1{k1}{z}, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPBROADCASTQ_XY)),    /* EVEX.256.66.0f38.W1 59 /r vpbroadcastq ymm1{k1}{z}, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPBROADCASTQ_XZ)),    /* EVEX.512.66.0f38.W1 59 /r vpbroadcastq zmm1{k1}{z}, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VBROADCASTI32X2_XX)), /* EVEX.128.66.0f38.W0 59 /r vbroadcasti32x2 xmm1{k1}{z}, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VBROADCASTI32X2_XY)), /* EVEX.256.66.0f38.W0 59 /r vbroadcasti32x2 ymm1{k1}{z}, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VBROADCASTI32X2_XZ)), /* EVEX.512.66.0f38.W0 59 /r vbroadcasti32x2 zmm1{k1}{z}, xmm2/m64 */

	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VBROADCASTI128)),     /*  VEX.256.66.0f38.W0 5a /r vbroadcasti128 ymm1, m128 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VBROADCASTI32X4_XY)), /* EVEX.256.66.0f38.W0 5a /r vbroadcasti32x4 ymm1{k1}{z}, m128 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VBROADCASTI32X4_XZ)), /* EVEX.512.66.0f38.W0 5a /r vbroadcasti32x4 zmm1{k1}{z}, m128 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VBROADCASTI64X2_XY)), /* EVEX.256.66.0f38.W1 5a /r vbroadcasti64x2 ymm1{k1}{z}, m128 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VBROADCASTI64X2_XZ)), /* EVEX.512.66.0f38.W1 5a /r vbroadcasti64x2 zmm1{k1}{z}, m128 */

	I(0x5b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VBROADCASTI32X8)), /* EVEX.512.66.0f38.W0 5b /r vbroadcasti32x8 zmm1{k1}{z}, m256 */
	I(0x5b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VBROADCASTI64X4)), /* EVEX.512.66.0f38.W1 5b /r vbroadcasti64x4 zmm1{k1}{z}, m256 */

	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBROADCASTB_XX)), /* EVEX.128.66.0f38.W0 78 /r vpbroadcastb xmm1{k1}{z}, xmm2/m8 */
	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBROADCASTB_XY)), /* EVEX.256.66.0f38.W0 78 /r vpbroadcastb ymm1{k1}{z}, xmm2/m8 */
	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPBROADCASTB_XZ)), /* EVEX.512.66.0f38.W0 78 /r vpbroadcastb zmm1{k1}{z}, xmm2/m8 */

	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBROADCASTW_XX)), /* EVEX.128.66.0f38.W0 79 /r vpbroadcastw xmm1{k1}{z}, xmm2/m16 */
	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBROADCASTW_XY)), /* EVEX.256.66.0f38.W0 79 /r vpbroadcastw ymm1{k1}{z}, xmm2/m16 */
	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPBROADCASTW_XZ)), /* EVEX.512.66.0f38.W0 79 /r vpbroadcastw zmm1{k1}{z}, xmm2/m16 */

	I(0x80, IF_X32|IF_66|IF_MODRM|IF_RMM,"inveptl\t" OP_MEM OP_R32),
	I(0x80, IF_X64|IF_66|IF_MODRM|IF_RMM,"inveptq\t" OP_MEM OP_R64),

	I(0x81, IF_X32|IF_66|IF_MODRM|IF_RMM,"invvpidl\t" OP_MEM OP_R32),
	I(0x81, IF_X64|IF_66|IF_MODRM|IF_RMM,"invvpidq\t" OP_MEM OP_R64),

	I(0x82, IF_X32|IF_66|IF_MODRM|IF_RMM,"invpcidl\t" OP_MEM OP_R32),
	I(0x82, IF_X64|IF_66|IF_MODRM|IF_RMM,"invpcidq\t" OP_MEM OP_R64),

	I(0x8d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 8d /r vpermw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x8d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 8d /r vpermw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x8d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 8d /r vpermw zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0xc8, IF_MODRM, "sha1nexte\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xc9, IF_MODRM, "sha1msg1\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xca, IF_MODRM, "sha1msg2\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xcb, IF_MODRM, LONGREPR(LO_SHA256RNDS2)),

	I(0xcc, IF_MODRM, LONGREPR(LO_SHA256MSG1)),

	I(0xcd, IF_MODRM, LONGREPR(LO_SHA256MSG2)),

	I(0xcf, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VGF2P8MULB)), /* VEX.128.66.0f38.WIG cf /r vgf2p8mulb xmm1, xmm2/m128 */
	I(0xcf, IF_66|IF_MODRM,        "gf2p8mulb\t" OP_RM128_XMM OP_RXMM),                 /*            66 0f 38 cf /r gf2p8mulb xmm1, xmm2/m128 */

	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vaesimc\t" OP_RM128_XMM OP_RXMM), /* VEX.128.66.0f38.WIG db /r vaesimc xmm1, xmm2/m128 */
	I(0xdb, IF_66|IF_MODRM,                              "aesimc\t" OP_RM128_XMM OP_RXMM),  /*            66 0f 38 db /r aesimc xmm1, xmm2/m128 */

	I(0xdc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vaesenc\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG dc /r vaesenc xmm1, xmm2, xmm3/m128 */
	I(0xdc, IF_66|IF_MODRM,                              "aesenc\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 dc /r aesenc xmm1, xmm2/m128 */

	I(0xdd, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VAESENCLAST)), /* VEX.128.66.0f38.WIG dd /r vaesenclast xmm1, xmm2, xmm3/m128 */
	I(0xdd, IF_66|IF_MODRM,        LONGREPR(LO_AESEECLAST)),                             /*            66 0f 38 dd /r aesenclast xmm1, xmm2/m128 */

	I(0xde, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vaesdec\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG de /r vaesdec xmm1, xmm2, xmm3/m128 */
	I(0xde, IF_66|IF_MODRM,                              "aesdec\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 de /r aesdec xmm1, xmm2/m128 */

	I(0xdf, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VAESDECLAST)), /* VEX.128.66.0f38.WIG df /r vaesdeclast xmm1, xmm2, xmm3/m128 */
	I(0xdf, IF_66|IF_MODRM,        LONGREPR(LO_AESDECLAST)),                             /*            66 0f 38 df /r aesdeclast xmm1, xmm2/m128 */

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

	I(0xf8, IF_66|IF_X32|IF_MODRM|IF_RMM, "movdir64b\t" OP_RM64 OP_R32),
	I(0xf8, IF_66|IF_X64|IF_MODRM|IF_RMM, "movdir64b\t" OP_RM64 OP_R64),

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
	I(0x00, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermq\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f3a.W1 00 /r ib vpermq ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x00, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermq\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f3a.W1 00 /r ib vpermq zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */

	I(0x01, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermpd\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f3a.W1 01 /r ib vpermpd ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x01, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermpd\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f3a.W1 01 /r ib vpermpd zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */

	I(0x02, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpblendd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.W0 02 /r ib vpblendd xmm1, xmm2, xmm3/m128, imm8 */
	I(0x02, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpblendd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.W0 02 /r ib vpblendd ymm1, ymm2, ymm3/m256, imm8 */

	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPERMILPS_XMM)), /* EVEX.128.66.0f3a.W0 04 /r ib vpermilps xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPERMILPS_YMM)), /* EVEX.256.66.0f3a.W0 04 /r ib vpermilps ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPERMILPS_ZMM)), /* EVEX.512.66.0f3a.W0 04 /r ib vpermilps zmm1{k1}{z}, zmm2/m512/m32bcst, imm8 */

	I(0x05, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 0), LO_VPERMILPD_XMM)), /*  VEX.128.66.0f3a.W0 05 /r ib vpermilpd xmm1, xmm2/m128, imm8 */
	I(0x05, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VPERMILPD_YMM)), /*  VEX.256.66.0f3a.W0 05 /r ib vpermilpd ymm1, ymm2/m256, imm8 */
	I(0x05, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPERMILPD_XMM)), /* EVEX.128.66.0f3a.W1 05 /r ib vpermilpd xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x05, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPERMILPD_YMM)), /* EVEX.256.66.0f3a.W1 05 /r ib vpermilpd ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x05, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPERMILPD_ZMM)), /* EVEX.512.66.0f3a.W1 05 /r ib vpermilpd zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */

	I(0x06, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPERM2F128)), /* VEX.256.66.0f3a.W0 06 /r ib vperm2f128 ymm1, ymm2, ymm3/m256, imm8 */

	I(0x08, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VROUNDPS_RXMM)), /* VEX.128.66.0f3a.WIG 08 /r ib vroundps xmm1, xmm2/m128, imm8 */
	I(0x08, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VROUNDPS_RYMM)), /* VEX.256.66.0f3a.WIG 08 /r ib vroundps ymm1, ymm2/m256, imm8 */
	I(0x08, IF_66|IF_MODRM,        "roundps\t" OP_U8 OP_RM128_XMM OP_RXMM),                /*            66 0f 3a 08 /r ib roundps xmm1, xmm2/m128, imm8 */

	I(0x09, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VROUNDPD_RXMM)), /* VEX.128.66.0f3a.WIG 09 /r ib vroundpd xmm1, xmm2/m128, imm8 */
	I(0x09, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VROUNDPD_RYMM)), /* VEX.256.66.0f3a.WIG 09 /r ib vroundpd ymm1, ymm2/m256, imm8 */
	I(0x09, IF_66|IF_MODRM,        "roundpd\t" OP_U8 OP_RM128_XMM OP_RXMM),                /*            66 0f 3a 09 /r ib roundpd xmm1, xmm2/m128, imm8 */

	I(0x0a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 1, 0) "vroundss\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.LIG.66.0f3a.WIG 0a /r ib vroundss xmm1, xmm2, xmm3/m32, imm8 */
	I(0x0a, IF_66|IF_MODRM,                               "roundss\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 0a /r ib roundss xmm1, xmm2/m32, imm8 */

	I(0x0b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 1, 0) "vroundsd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.LIG.66.0f3a.WIG 0b /r ib vroundsd xmm1, xmm2, xmm3/m64, imm8 */
	I(0x0b, IF_66|IF_MODRM,                               "roundsd\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 0b /r ib roundsd xmm1, xmm2/m64, imm8 */

	I(0x0c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vblendps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 0c /r ib vblendps xmm1, xmm2, xmm3/m128, imm8 */
	I(0x0c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vblendps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.WIG 0c /r ib vblendps ymm1, ymm2, ymm3/m256, imm8 */
	I(0x0c, IF_66|IF_MODRM,                              "blendps\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 0c /r ib blendps xmm1, xmm2/m128, imm8 */

	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vblendpd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 0d /r ib vblendpd xmm1, xmm2, xmm3/m128, imm8 */
	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vblendpd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.WIG 0d /r ib vblendpd ymm1, ymm2, ymm3/m256, imm8 */
	I(0x0d, IF_66|IF_MODRM,                              "blendpd\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 0d /r ib blendpd xmm1, xmm2/m128, imm8 */

	I(0x0e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpblendw\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 0e /r ib vpblendw xmm1, xmm2, xmm3/m128, imm8 */
	I(0x0e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpblendw\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.WIG 0e /r ib vpblendw ymm1, ymm2, ymm3/m256, imm8 */
	I(0x0e, IF_66|IF_MODRM,                              "pblendw\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 0e /r ib pblendw xmm1, xmm2/m128, imm8 */

	I(0x0f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpalignr\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f3a.WIG 0f /r ib vpalignr xmm1{k1}{z}, xmm2, xmm3/m128, imm8 */
	I(0x0f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpalignr\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f3a.WIG 0f /r ib vpalignr ymm1{k1}{z}, ymm2, ymm3/m256, imm8 */
	I(0x0f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpalignr\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f3a.WIG 0f /r ib vpalignr zmm1{k1}{z}, zmm2, zmm3/m512, imm8 */
	I(0x0f, IF_MODRM,                                    "palignr\t" OP_U8 OP_RM64_MM OP_RMM),                /*                0f 3a 0f /r ib palignr mm1, mm2/m64, imm8 */
	I(0x0f, IF_66|IF_MODRM,                              "palignr\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*             66 0f 3a 0f /r ib palignr xmm1, xmm2/m128, imm8 */

	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VINSERTF128)),      /*  VEX.256.66.0f3a.W0 18 /r ib vinsertf128 ymm1, ymm2, xmm3/m128, imm8 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VINSERTF32X4_YMM)), /* EVEX.256.66.0f3a.W0 18 /r ib vinsertf32x4 ymm1{k1}{z}, ymm2, xmm3/m128, imm8 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VINSERTF32X4_ZMM)), /* EVEX.512.66.0f3a.W0 18 /r ib vinsertf32x4 zmm1{k1}{z}, zmm2, xmm3/m128, imm8 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VINSERTF64X2_YMM)), /* EVEX.256.66.0f3a.W1 18 /r ib vinsertf64x2 ymm1{k1}{z}, ymm2, xmm3/m128, imm8 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VINSERTF64X2_ZMM)), /* EVEX.512.66.0f3a.W1 18 /r ib vinsertf64x2 zmm1{k1}{z}, zmm2, xmm3/m128, imm8 */

	I(0x1a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VINSERTF32X8)), /* EVEX.512.66.0f3a.W0 1a /r ib vinsertf32x8 zmm1{k1}{z}, zmm2, ymm3/m256, imm8 */
	I(0x1a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VINSERTF64X4)), /* EVEX.512.66.0f3a.W1 1a /r ib vinsertf64x4 zmm1{k1}{z}, zmm2, ymm3/m256, imm8 */

	I(0x21, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VINSERTPS_XMM)), /*  VEX.128.66.0f3a.WIG 21 /r ib vinsertps xmm1, xmm2, xmm3/m32, imm8 */
	I(0x21, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VINSERTPS_YMM)), /* EVEX.128.66.0f3a.W0  21 /r ib vinsertps xmm1, xmm2, xmm3/m32, imm8 */
	I(0x21, IF_66|IF_MODRM,        "insertps\t" OP_U8 OP_RM128_XMM OP_RXMM),               /*             66 0f 3a 21 /r ib insertps xmm1, xmm2/m32, imm8 */

	I(0x30, IF_VEX|IF_66|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_KSHIFTRB)), /* VEX.L0.66.0f3a.W0 30 /r kshiftrb k1, k2, imm8 */
	I(0x30, IF_VEX|IF_66|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_KSHIFTRW)), /* VEX.L0.66.0f3a.W1 30 /r kshiftrw k1, k2, imm8 */

	I(0x31, IF_VEX|IF_66|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_KSHIFTRD)), /* VEX.L0.66.0f3a.W0 31 /r kshiftrd k1, k2, imm8 */
	I(0x31, IF_VEX|IF_66|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_KSHIFTRQ)), /* VEX.L0.66.0f3a.W1 31 /r kshiftrq k1, k2, imm8 */

	I(0x32, IF_VEX|IF_66|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_KSHIFTLB)), /* VEX.L0.66.0f3a.W0 32 /r kshiftlb k1, k2, imm8 */
	I(0x32, IF_VEX|IF_66|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_KSHIFTLW)), /* VEX.L0.66.0f3a.W1 32 /r kshiftlw k1, k2, imm8 */

	I(0x33, IF_VEX|IF_66|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_KSHIFTLD)), /* VEX.L0.66.0f3a.W0 33 /r kshiftld k1, k2, imm8 */
	I(0x33, IF_VEX|IF_66|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_KSHIFTLQ)), /* VEX.L0.66.0f3a.W1 33 /r kshiftlq k1, k2, imm8 */

	I(0x38, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VINSERTI128)),      /*  VEX.256.66.0f3a.W0 38 /r ib vinserti128 ymm1, ymm2, xmm3/m128, imm8 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VINSERTI32X4_YMM)), /* EVEX.256.66.0f3a.W0 38 /r ib vinserti32x4 ymm1{k1}{z}, ymm2, xmm3/m128, imm8 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VINSERTI32X4_ZMM)), /* EVEX.512.66.0f3a.W0 38 /r ib vinserti32x4 zmm1{k1}{z}, zmm2, xmm3/m128, imm8 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VINSERTI64X2_YMM)), /* EVEX.256.66.0f3a.W1 38 /r ib vinserti64x2 ymm1{k1}{z}, ymm2, xmm3/m128, imm8 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VINSERTI64X2_ZMM)), /* EVEX.512.66.0f3a.W1 38 /r ib vinserti64x2 zmm1{k1}{z}, zmm2, xmm3/m128, imm8 */

	I(0x3a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VINSERTI32X8)), /* EVEX.512.66.0f3a.W0 3a /r ib vinserti32x8 zmm1{k1}{z}, zmm2, ymm3/m256, imm8 */
	I(0x3a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VINSERTI64X4)), /* EVEX.512.66.0f3a.W1 3a /r ib vinserti64x4 zmm1{k1}{z}, zmm2, ymm3/m256, imm8 */

	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vdpps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 40 /r ib vdpps xmm1, xmm2, xmm3/m128, imm8 */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vdpps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.WIG 40 /r ib vdpps ymm1, ymm2, ymm3/m256, imm8 */
	I(0x40, IF_66|IF_MODRM,                              "dpps\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 40 /r ib dpps xmm1, xmm2/m128, imm8 */

	I(0x41, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vdppd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 41 /r ib vdppd xmm1, xmm2, xmm3/m128, imm8 */
	I(0x41, IF_66|IF_MODRM,                              "dppd\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 41 /r ib dppd xmm1, xmm2/m128, imm8 */

	I(0x42, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vmpsadbw\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 42 /r ib vmpsadbw xmm1, xmm2, xmm3/m128, imm8 */
	I(0x42, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vmpsadbw\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.WIG 42 /r ib vmpsadbw ymm1, ymm2, ymm3/m256, imm8 */
	I(0x42, IF_66|IF_MODRM,                              "mpsadbw\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 42 /r ib mpsadbw xmm1, xmm2/m128, imm8 */

	I(0x44, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPCLMULQDQ)), /* VEX.128.66.0f3a.WIG 44 /r ib vpclmulqdq xmm1, xmm2, xmm3/m128, imm8 */
	I(0x44, IF_66|IF_MODRM,        LONGREPR(LO_PCLMULQDQ)),                             /*            66 0f 3a 44 /r ib pclmulqdq xmm1, xmm2/m128, imm8 */

	I(0x46, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPERM2I128)), /* VEX.256.66.0f3a.W0 46 /r ib vperm2i128 ymm1, ymm2, ymm3/m256, imm8 */

	I(0x60, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPCMPESTRM)), /* VEX.128.66.0f3a.WIG 60 /r ib vpcmpestrm xmm1, xmm2/m128, imm8 */
	I(0x60, IF_66|IF_MODRM,        LONGREPR(LO_PCMPESTRM)),                             /*            66 0f 3a 60 /r ib pcmpestrm xmm1, xmm2/m128, imm8 */

	I(0x61, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPCMPESTRI)), /* VEX.128.66.0f3a.WIG 61 /r ib vpcmpestri xmm1, xmm2/m128, imm8 */
	I(0x61, IF_66|IF_MODRM,        LONGREPR(LO_PCMPESTRI)),                             /*            66 0f 3a 61 /r ib pcmpestri xmm1, xmm2/m128, imm8 */

	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPCMPISTRM)), /* VEX.128.66.0f3a.WIG 62 /r ib vpcmpistrm xmm1, xmm2/m128, imm8 */
	I(0x62, IF_66|IF_MODRM,        LONGREPR(LO_PCMPISTRM)),                             /*            66 0f 3a 62 /r ib pcmpistrm xmm1, xmm2/m128, imm8 */

	I(0x63, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPCMPISTRI)), /* VEX.128.66.0f3a.WIG 63 /r ib vpcmpistri xmm1, xmm2/m128, imm8 */
	I(0x63, IF_66|IF_MODRM,        LONGREPR(LO_PCMPISTRI)),                             /*            66 0f 3a 63 /r ib pcmpistri xmm1, xmm2/m128, imm8 */

	I(0xcc, IF_MODRM, LONGREPR(LO_SHA1RNDS4)),

	I(0xce, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VGF2P8AFFINEQB)), /* VEX.128.66.0f3a.WIG ce /r ib vgf2p8affineqb xmm1, xmm2/m128, imm8 */
	I(0xce, IF_66|IF_MODRM,        LONGREPR(LO_GF2P8AFFINEQB)),                             /*             66 0f3a ce /r ib gf2p8affineqb xmm1, xmm2/m128, imm8 */

	I(0xcf, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VGF2P8AFFINEINVQB)), /* VEX.128.66.0f3a.WIG cf /r ib vgf2p8affineinvqb xmm1, xmm2/m128, imm8 */
	I(0xcf, IF_66|IF_MODRM,        LONGREPR(LO_GF2P8AFFINEINVQB)),                             /*             66 0f3a cf /r ib gf2p8affineinvqb xmm1, xmm2/m128, imm8 */

	I(0xdf, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VAESKEYGENASSIST)), /* VEX.128.66.0f3a.WIG df /r ib vaeskeygenassist xmm1, xmm2/m128, imm8 */
	I(0xdf, IF_66|IF_MODRM,        LONGREPR(LO_AESKEYGENASSIST)),                             /*            66 0f 3a df /r ib aeskeygenassist xmm1, xmm2/m128, imm8 */

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
generateOffsetTable("ops_0f3a");
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
STATIC_ASSERT(COMPILER_LENOF(ops_0f) == 1113);
PRIVATE u16 const ops_0f_offsets[256] = {
	0, 6, 36, 38, 1112, 40, 42, 43, 45, 46, 47, 48, 1112, 49, 1112, 1112,
	51, 63, 75, 1112, 87, 99, 111, 1112, 117, 1112, 121, 127, 132, 1112, 1112, 133,
	135, 137, 139, 141, 143, 1112, 144, 1112, 145, 157, 169, 170, 176, 178, 1112, 1112,
	180, 181, 182, 183, 184, 185, 186, 187, 1112, 1112, 1112, 1112, 1112, 1112, 1112, 188,
	189, 192, 199, 206, 209, 216, 223, 230, 237, 240, 243, 250, 256, 259, 262, 265,
	1112, 1112, 268, 273, 278, 290, 302, 314, 1112, 1112, 1112, 1112, 1112, 1112, 1112, 1112,
	326, 331, 336, 343, 348, 353, 358, 365, 370, 375, 380, 387, 392, 398, 404, 410,
	434, 449, 464, 488, 510, 515, 520, 527, 530, 532, 1112, 1112, 534, 540, 546, 552,
	576, 578, 580, 582, 584, 586, 588, 590, 592, 594, 596, 598, 600, 602, 604, 606,
	608, 613, 618, 623, 628, 629, 630, 631, 632, 637, 642, 643, 644, 645, 646, 647,
	648, 651, 654, 655, 658, 661, 1112, 1112, 664, 667, 670, 671, 674, 677, 680, 712,
	715, 716, 719, 722, 725, 728, 731, 734, 736, 739, 740, 752, 755, 761, 767, 770,
	772, 773, 1112, 776, 1112, 1112, 778, 790, 806, 810, 814, 818, 822, 826, 830, 834,
	838, 844, 849, 856, 863, 870, 875, 877, 885, 890, 895, 900, 910, 915, 920, 925,
	935, 940, 945, 955, 960, 965, 970, 976, 983, 988, 993, 998, 1008, 1013, 1018, 1023,
	1112, 1033, 1038, 1045, 1052, 1059, 1064, 1069, 1070, 1075, 1080, 1087, 1094, 1099, 1104, 1111
};

#define HAVE_OPS_0F38_OFFSETS 1
STATIC_ASSERT(COMPILER_LENOF(ops_0f38) == 347);
PRIVATE u16 const ops_0f38_offsets[256] = {
	0, 5, 9, 13, 17, 22, 26, 30, 34, 38, 42, 46, 51, 54, 59, 61,
	63, 66, 69, 346, 346, 346, 72, 76, 346, 346, 346, 346, 79, 84, 89, 96,
	99, 103, 107, 111, 115, 119, 346, 346, 125, 346, 131, 137, 346, 346, 346, 346,
	143, 147, 151, 155, 159, 163, 169, 346, 173, 177, 186, 190, 199, 203, 212, 216,
	225, 234, 346, 346, 346, 236, 242, 248, 346, 346, 346, 346, 346, 346, 346, 346,
	346, 346, 346, 346, 346, 346, 346, 346, 254, 257, 265, 270, 346, 346, 346, 346,
	346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346,
	346, 346, 346, 346, 346, 346, 346, 346, 272, 275, 346, 346, 346, 346, 346, 346,
	278, 280, 282, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 284, 346, 346,
	346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346,
	346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346,
	346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346,
	346, 346, 346, 346, 346, 346, 346, 346, 287, 288, 289, 290, 291, 292, 346, 293,
	346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 295, 297, 299, 301, 303,
	346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346, 346,
	305, 310, 316, 318, 346, 324, 330, 336, 344, 346, 346, 346, 346, 346, 346, 346
};

#define HAVE_OPS_0F3A_OFFSETS 1
STATIC_ASSERT(COMPILER_LENOF(ops_0f3a) == 93);
PRIVATE u8 const ops_0f3a_offsets[256] = {
	0, 2, 4, 92, 6, 9, 14, 92, 15, 18, 21, 23, 25, 28, 31, 34,
	92, 92, 92, 92, 92, 92, 92, 92, 39, 92, 44, 92, 92, 92, 92, 92,
	92, 46, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	49, 51, 53, 55, 92, 92, 92, 92, 57, 92, 62, 92, 92, 92, 92, 92,
	64, 67, 69, 92, 72, 92, 74, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	75, 77, 79, 81, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 83, 92, 84, 86,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 88,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	90, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92
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
		if ((chain->i_flags & IF_REXB) == IF_REXB) {
			if (!(flags & F_REX_B))
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
			if (chain->i_flags & IF_VEX) {
				if (!(flags & F_HASVEX))
					continue;
				if ((chain->i_flags & IF_VEX) == IF_VEX) {
					byte_t f = (byte_t)chain->i_repr[0];
					if ((f & IF_VEX_B0_LIG) != IF_VEX_B0_LIG) {
						if (((flags & F_VEX_LL_M) >> F_VEX_LL_S) !=
						    ((f & IF_VEX_B0_LL_M) >> IF_VEX_B0_LL_S))
							continue; /* Different length value */
					}
					if ((f & IF_VEX_B0_NOEVEX) && (flags & F_HASEVEX))
						continue; /* Require that no EVEX prefix was used. */
					if (!(f & IF_VEX_B0_WIG)) {
						if (!!(f & IF_VEX_B0_W) != !!(flags & F_VEX_W))
							continue; /* Different width value */
					}
				} else {
					if (!!(flags & F_VEX_W) != !!(flags & IF_VEXW1))
						continue;
				}
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
			if ((chain->i_flags & IF_BYTE2) == IF_BYTE2 ||
			    (chain->i_flags & IF_VEX) == IF_VEX)
				++start;
			if (*start == OPC_LONGREPR) {
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
#define VEX_VVVVV() ((flags & F_VEX_VVVVV_M) >> F_VEX_VVVVV_S)

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
					da_print_reg8(self, VEX_VVVVV(), flags);
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
					da_print_xmmreg(self, rm.mi_reg);
					break;

				case OPC_RYMM:
					da_print_ymmreg(self, rm.mi_reg);
					break;

				case OPC_RZMM:
					da_print_zmmreg(self, rm.mi_reg);
					break;

				case OPC_RXMM_MASK:
					da_print_xmmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, flags);
					break;

				case OPC_RYMM_MASK:
					da_print_ymmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, flags);
					break;

				case OPC_RZMM_MASK:
					da_print_zmmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, flags);
					break;

				case OPC_RMK:
					if (rm.mi_type == MODRM_REGISTER) {
						da_print_kreg(self, rm.mi_rm);
					} else {
						da_print_modrm_rm(self, &rm, flags, DA86_IS64(self) ? 16 : 8);
					}
					break;

				case OPC_RM64_MM:
					da_print_modrm_rm64_mm(self, &rm, flags);
					break;

				case OPC_RM128_XMM:
					da_print_modrm_rm128_xmm(self, &rm, flags);
					break;

				case OPC_RM256_YMM:
					da_print_modrm_rm256_ymm(self, &rm, flags);
					break;

				case OPC_RM512_ZMM:
					da_print_modrm_rm512_zmm(self, &rm, flags);
					break;

				case OPC_RM128_XMM_MASK:
					da_print_modrm_rm128_xmm(self, &rm, flags);
					da_print_Xmmmask(self, flags);
					break;

				case OPC_RM256_YMM_MASK:
					da_print_modrm_rm256_ymm(self, &rm, flags);
					da_print_Xmmmask(self, flags);
					break;

				case OPC_RM512_ZMM_MASK:
					da_print_modrm_rm512_zmm(self, &rm, flags);
					da_print_Xmmmask(self, flags);
					break;

				case OPC_VRK:
					da_print_kreg(self, VEX_VVVVV());
					break;

				case OPC_VRXMM:
					da_print_xmmreg(self, VEX_VVVVV());
					break;

				case OPC_VRYMM:
					da_print_ymmreg(self, VEX_VVVVV());
					break;

				case OPC_VRZMM:
					da_print_zmmreg(self, VEX_VVVVV());
					break;

				case OPC_VRXMM_MASK:
					da_print_xmmreg(self, VEX_VVVVV());
					da_print_Xmmmask(self, flags);
					break;

				case OPC_VRYMM_MASK:
					da_print_ymmreg(self, VEX_VVVVV());
					da_print_Xmmmask(self, flags);
					break;

				case OPC_VRZMM_MASK:
					da_print_zmmreg(self, VEX_VVVVV());
					da_print_Xmmmask(self, flags);
					break;

				case OPC_RM128_XMM__OPC_VRXMM__OPC_RXMM_MASK:
					/* OPC_RM128_XMM OPC_VRXMM OPC_RXMM_MASK */
					da_print_modrm_rm128_xmm(self, &rm, flags);
					disasm_print(self, ", ", 2);
					da_print_xmmreg(self, VEX_VVVVV());
					disasm_print(self, ", ", 2);
					da_print_xmmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, flags);
					break;

				case OPC_RM256_YMM__OPC_VRYMM__OPC_RYMM_MASK:
					/* OPC_RM256_YMM OPC_VRYMM OPC_RYMM_MASK */
					da_print_modrm_rm256_ymm(self, &rm, flags);
					disasm_print(self, ", ", 2);
					da_print_ymmreg(self, VEX_VVVVV());
					disasm_print(self, ", ", 2);
					da_print_ymmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, flags);
					break;

				case OPC_RM512_ZMM__OPC_VRZMM__OPC_RZMM_MASK:
					/* OPC_RM512_ZMM OPC_VRZMM OPC_RZMM_MASK */
					da_print_modrm_rm512_zmm(self, &rm, flags);
					disasm_print(self, ", ", 2);
					da_print_zmmreg(self, VEX_VVVVV());
					disasm_print(self, ", ", 2);
					da_print_zmmreg(self, rm.mi_reg);
					da_print_Xmmmask(self, flags);
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
