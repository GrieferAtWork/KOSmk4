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

#include "x86-db.h"
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
	for (;; ++chain) {
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
			/* Do an exact match for the 0x66 prefix due to it being a
			 * so-called mandatory prefix, that also modifies the name
			 * of an instruction when ATnT representation is printed. */
			if (((chain->i_flags & IF_66) != 0) != ((flags & F_66) != 0))
				continue;
			if ((chain->i_flags & IF_67) && !(flags & F_67))
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
						if (flags & F_EVEX_b) {
							/* When EVEX.b is set, then a 512-bit vector size is implied,
							 * SAE is enabled, and VEX.LL is used as a rounding control
							 * indicator, as displayed by `OP_ER' and `OP_SAE' */
							if ((f & IF_VEX_B0_LL_M) != 2 << IF_VEX_B0_LL_S)
								continue; /* Different length value */
						} else {
							if (((flags & F_VEX_LL_M) >> F_VEX_LL_S) !=
							    ((f & IF_VEX_B0_LL_M) >> IF_VEX_B0_LL_S))
								continue; /* Different length value */
						}
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
					goto done_operands;
				if (!is_first)
					disasm_print(self, ", ", 2);
				is_first = false;
do_nextop_nocomma:
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

				case OPC_RK_MASK:
					da_print_kreg(self, rm.mi_reg);
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

				case OPC_ER: {
					PRIVATE char const rounding_modes[4] = { 'n', 'd', 'u', 'z' };
					char rmrepr[6];
					if (!(flags & F_EVEX_b)) {
nextop_nocomma:
						ch = *p++;
						if (!ch)
							goto done_operands;
						goto do_nextop_nocomma;
					}
					disasm_print(self, "{", 1);
					disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_PREFIX);
					rmrepr[0] = 'r';
					rmrepr[1] = rounding_modes[(flags & F_VEX_LL_M) >> F_VEX_LL_S];
					rmrepr[2] = '-';
					rmrepr[3] = 's';
					rmrepr[4] = 'a';
					rmrepr[5] = 'e';
					disasm_print(self, rmrepr, 6);
					disasm_print_format(self, DISASSEMBLER_FORMAT_MNEMONIC_SUFFIX);
					disasm_print(self, "}", 1);
				}	break;

				case OPC_SAE:
					if (!(flags & F_EVEX_b))
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
done_operands:
			;
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
