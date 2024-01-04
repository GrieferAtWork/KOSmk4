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
#ifndef _LIBEMU86_EMU86_C
#define _LIBEMU86_EMU86_C 1

#ifndef _LIBEMU86_EMU86_H
#include "emu86.h"
#endif /* !_LIBEMU86_EMU86_H */

#include "api.h"

#include <hybrid/__unaligned.h>

#include <bits/types.h>

/* Helpers for decoding/disassembling/emulation of x86 instructions. */

__DECL_BEGIN

#ifdef __CC__

/* Decode an opcode from `pc', store it in `*popcode' and `*pflags',
 * before returning a pointer past the opcode's ID.
 * @return: * :   A pointer to the first byte past the opcode's ID
 * @param: popcode: Filled with the opcode's number
 * @param: pflags:  [in(EMU86_F_BITMASK)|out] Opcode flags. */
LIBEMU86_IMPL __ATTR_UNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1, 2, 3)) __byte_t *
__NOTHROW_NCX(LIBEMU86_CC emu86_opcode_decode)(__byte_t const *__restrict pc,
                                               emu86_opcode_t *__restrict popcode,
                                               emu86_opflags_t *__restrict pflags) {
	emu86_opcode_t opcode;
next_byte:
	opcode = *pc++;
	switch (opcode) {

#if LIBEMU86_CONFIG_WANT_64BIT
	/* EVEX Prefix */
	case 0x62: {
		__uint32_t evex;
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
		/* EVEX only exists in 64-bit mode! */
		if (!EMU86_F_IS64(*pflags))
			break;
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
		evex = *pc++;
		evex <<= 8;
		evex |= *pc++;
		evex <<= 8;
		evex |= *pc++;
		if ((evex & EMU86_EVEX_IDENT_M) != EMU86_EVEX_IDENT_V) {
			pc -= 3;
			/*result = 0x62;*/
			goto done;
		}
		*pflags |= EMU86_F_HASVEX | EMU86_F_HASEVEX;
		*pflags |= ((~evex & EMU86_EVEX_VVVV_M) >> EMU86_EVEX_VVVV_S) << EMU86_F_VEX_VVVVV_S;
		*pflags |= ((evex & EMU86_EVEX_aaa_M) >> EMU86_EVEX_aaa_S) << EMU86_F_EVEX_aaa_S;
		if (!(evex & EMU86_EVEX_Vi))
			*pflags |= 0x10 << EMU86_F_VEX_VVVVV_S;
		if (!(evex & EMU86_EVEX_R))
			*pflags |= EMU86_F_REX_R;
		if (!(evex & EMU86_EVEX_Ri))
			*pflags |= EMU86_F_EVEX_R;
		if (!(evex & EMU86_EVEX_X))
			*pflags |= EMU86_F_REX_X;
		if (!(evex & EMU86_EVEX_B))
			*pflags |= EMU86_F_REX_B;
		if (evex & EMU86_EVEX_W)
			*pflags |= EMU86_F_VEX_W;
		if (evex & EMU86_EVEX_z)
			*pflags |= EMU86_F_EVEX_z;
		if (evex & EMU86_EVEX_b)
			*pflags |= EMU86_F_EVEX_b;
		if (evex & EMU86_EVEX_L)
			*pflags |= 1 << EMU86_F_VEX_LL_S;
		if (evex & EMU86_EVEX_Li)
			*pflags |= 2 << EMU86_F_VEX_LL_S;
		switch (evex & EMU86_EVEX_PP_M) {
		case 0x01 << EMU86_EVEX_PP_S: *pflags |= EMU86_F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << EMU86_EVEX_PP_S: *pflags |= EMU86_F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << EMU86_EVEX_PP_S: *pflags |= EMU86_F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		switch (evex & EMU86_EVEX_MM_M) {
		case 0x1 << EMU86_EVEX_MM_S: opcode = EMU86_OPCODE_BASE0f; break;
		case 0x2 << EMU86_EVEX_MM_S: opcode = EMU86_OPCODE_BASE0f38; break;
		case 0x3 << EMU86_EVEX_MM_S: opcode = EMU86_OPCODE_BASE0f3a; break;
		default:
			pc -= 3;
			/*result = 0x62;*/
			goto done;
		}
		/* The actual instruction opcode byte */
		opcode |= *pc++;
	}	break;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */


	/* VEX Prefix (3-byte form) */
	case 0xc4: {
		__uint16_t vex;
		vex = *pc++;
		vex <<= 8;
		vex |= *pc++;
#if LIBEMU86_CONFIG_WANT_64BIT
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
		if (EMU86_F_IS64(*pflags))
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
		{
			if (!(vex & EMU86_VEX3B_R))
				*pflags |= EMU86_F_REX_R;
			if (!(vex & EMU86_VEX3B_X))
				*pflags |= EMU86_F_REX_X;
			if (!(vex & EMU86_VEX3B_B))
				*pflags |= EMU86_F_REX_B;
		}
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
		else
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
		{
			if (!(vex & (EMU86_VEX3B_R | EMU86_VEX3B_X))) {
				pc -= 2;
				/*result = 0xc4;*/
				goto done;
			}
		}
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
		*pflags |= EMU86_F_HASVEX;
		if (vex & EMU86_VEX3B_L)
			*pflags |= 1 << EMU86_F_VEX_LL_S;
		if (vex & EMU86_VEX3B_W)
			*pflags |= EMU86_F_VEX_W;
		*pflags |= ((~vex & EMU86_VEX3B_VVVV_M) >> EMU86_VEX3B_VVVV_S) << EMU86_F_VEX_VVVVV_S;
		switch (vex & EMU86_VEX3B_PP_M) {
		case 0x01 << EMU86_VEX3B_PP_S: *pflags |= EMU86_F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << EMU86_VEX3B_PP_S: *pflags |= EMU86_F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << EMU86_VEX3B_PP_S: *pflags |= EMU86_F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		switch (vex & EMU86_VEX3B_MMMMM_M) {
		case 0x1 << EMU86_VEX3B_MMMMM_S: opcode = EMU86_OPCODE_BASE0f; break;
		case 0x2 << EMU86_VEX3B_MMMMM_S: opcode = EMU86_OPCODE_BASE0f38; break;
		case 0x3 << EMU86_VEX3B_MMMMM_S: opcode = EMU86_OPCODE_BASE0f3a; break;
		default:
			pc -= 2;
			/*result = 0xc4;*/
			goto done;
		}
		/* The actual instruction opcode byte */
		opcode |= *pc++;
	}	break;

	/* VEX Prefix (2-byte form) */
	case 0xc5:
		opcode = *pc++;
#if LIBEMU86_CONFIG_WANT_64BIT
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
		if (EMU86_F_IS64(*pflags))
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
		{
			if (!(opcode & EMU86_VEX2B_R))
				*pflags |= EMU86_F_REX_R;
		}
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
		else
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
		{
			if (!(opcode & (EMU86_VEX2B_R | EMU86_VEX2B_1))) {
				--pc;
				opcode = 0xc5;
				break;
			}
		}
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
		*pflags |= EMU86_F_HASVEX;
		if (opcode & EMU86_VEX2B_L)
			*pflags |= 1 << EMU86_F_VEX_LL_S;
		*pflags |= ((~opcode & EMU86_VEX2B_VVVV_M) >> EMU86_VEX2B_VVVV_S) << EMU86_F_VEX_VVVVV_S;
		switch (opcode & EMU86_VEX2B_PP_M) {
		case 0x01 << EMU86_VEX2B_PP_S: *pflags |= EMU86_F_OP16; break;  /* same as 0x66 prefix */
		case 0x02 << EMU86_VEX2B_PP_S: *pflags |= EMU86_F_REP; break;   /* same as 0xf3 prefix */
		case 0x03 << EMU86_VEX2B_PP_S: *pflags |= EMU86_F_REPNE; break; /* same as 0xf2 prefix */
		default: break;
		}
		/* The actual instruction opcode byte */
		opcode = EMU86_OPCODE_BASE0f | *pc++;
		break;

		/* Prefix bytes */
	case 0x66: *pflags |= EMU86_F_66; goto next_byte;
	case 0x67: *pflags |= EMU86_F_67; goto next_byte;
	case 0xf0: *pflags |= EMU86_F_f0; goto next_byte;
	case 0xf2: *pflags |= EMU86_F_f2; goto next_byte;
	case 0xf3: *pflags |= EMU86_F_f3; goto next_byte;

#if LIBEMU86_CONFIG_WANT_64BIT
	case 0x40 ... 0x4f:
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
		if (!EMU86_F_IS64(*pflags))
			break;
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
		*pflags |= EMU86_F_HASREX | ((opcode & 0xf) << EMU86_F_REXSHFT);
		goto next_byte;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */

#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
	case 0x26:
#if LIBEMU86_CONFIG_WANT_64BIT
		if (EMU86_F_IS64(*pflags))
			goto done;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		*pflags = (*pflags & ~EMU86_F_SEGMASK) | EMU86_F_SEGES;
		goto next_byte;

	case 0x2e:
#if LIBEMU86_CONFIG_WANT_64BIT
		if (EMU86_F_IS64(*pflags))
			goto done;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		*pflags = (*pflags & ~EMU86_F_SEGMASK) | EMU86_F_SEGCS;
		goto next_byte;

	case 0x36:
#if LIBEMU86_CONFIG_WANT_64BIT
		if (EMU86_F_IS64(*pflags))
			goto done;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		*pflags = (*pflags & ~EMU86_F_SEGMASK) | EMU86_F_SEGSS;
		goto next_byte;

	case 0x3e:
#if LIBEMU86_CONFIG_WANT_64BIT
		if (EMU86_F_IS64(*pflags))
			goto done;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		*pflags = (*pflags & ~EMU86_F_SEGMASK) | EMU86_F_SEGDS;
		goto next_byte;
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */

	case 0x64:
		*pflags = (*pflags & ~EMU86_F_SEGMASK) | EMU86_F_SEGFS;
		goto next_byte;

	case 0x65:
		*pflags = (*pflags & ~EMU86_F_SEGMASK) | EMU86_F_SEGGS;
		goto next_byte;

	case 0x0f:
		opcode = EMU86_OPCODE_BASE0f | *pc++;
		if (opcode == (EMU86_OPCODE_BASE0f | 0x38)) {
			opcode = EMU86_OPCODE_BASE0f38 | *pc++;
		} else if (opcode == (EMU86_OPCODE_BASE0f | 0x3a)) {
			opcode = EMU86_OPCODE_BASE0f3a | *pc++;
		}
		break;

	default: break;
	}
done:
	*popcode = opcode;
	return (__byte_t *)pc;
}




/* Decode a MODRM suffix from `pc' and return a pointer past the end of the suffix.
 * @param: result: Filled in with information regarding the MODRM value.
 * @param: flags:  Opcode flags. */
LIBEMU86_IMPL __ATTR_UNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __byte_t *
__NOTHROW_NCX(LIBEMU86_CC emu86_modrm_decode)(__byte_t const *__restrict pc,
                                              struct emu86_modrm *__restrict result,
                                              emu86_opflags_t flags) {
	__uint8_t rmbyte = *pc++;
	__uint8_t sibbyte;
	result->mi_reg = EMU86_MODRM_GETREG(rmbyte);
#if LIBEMU86_CONFIG_WANT_16BIT
	if (!EMU86_F_IS64(flags) && (EMU86_F_IS16(flags) ^ ((flags & EMU86_F_67) != 0))) {
		/* HINT: This handling is OK, since there aren't any mandatory 67h prefix bytes! */
		result->mi_shift = 0;
		if ((rmbyte & EMU86_MODRM_MOD_MASK) == (0x3 << EMU86_MODRM_MOD_SHIFT)) {
			/* Register operand. */
			result->mi_rm    = EMU86_MODRM_GETRM(rmbyte);
			result->mi_type  = EMU86_MODRM_REGISTER;
			result->mi_index = 0xff;
		} else {
			result->mi_offset = 0;
			result->mi_type   = EMU86_MODRM_MEMORY;
			switch (EMU86_MODRM_GETRM(rmbyte)) {

			case 0: /* [BX + SI] */
				result->mi_rm    = EMU86_R_BX;
				result->mi_index = EMU86_R_SI;
				break;

			case 1: /* [BX + DI] */
				result->mi_rm    = EMU86_R_BX;
				result->mi_index = EMU86_R_DI;
				break;

			case 2: /* [BP + SI] */
				result->mi_rm    = EMU86_R_BP;
				result->mi_index = EMU86_R_SI;
				break;

			case 3: /* [BP + DI] */
				result->mi_rm    = EMU86_R_BP;
				result->mi_index = EMU86_R_DI;
				break;

			case 4: /* [SI] */
				result->mi_rm    = EMU86_R_SI;
				result->mi_index = 0xff;
				break;

			case 5: /* [DI] */
				result->mi_rm    = EMU86_R_DI;
				result->mi_index = 0xff;
				break;

			case 6: /* [BP] */
				result->mi_index = 0xff;
				result->mi_rm    = EMU86_R_BP;
				if ((rmbyte & EMU86_MODRM_MOD_MASK) == (0x0 << EMU86_MODRM_MOD_SHIFT)) { /* [disp16] */
					result->mi_rm     = 0xff;
					result->mi_offset = (__int32_t)(__uint32_t)__hybrid_unaligned_getle16(pc);
					pc += 2;
				}
				break;

			case 7: /* [BX] */
				result->mi_rm    = EMU86_R_BX;
				result->mi_index = 0xff;
				break;

			default: __builtin_unreachable();
			}
			if ((rmbyte & EMU86_MODRM_MOD_MASK) == (0x1 << EMU86_MODRM_MOD_SHIFT)) {
				/* [... + disp8] */
				result->mi_offset = (__int32_t)(*(__int8_t const *)pc);
				pc += 1;
			} else if ((rmbyte & EMU86_MODRM_MOD_MASK) == (0x2 << EMU86_MODRM_MOD_SHIFT)) {
				/* [... + disp16] */
				result->mi_offset = (__int32_t)(__uint32_t)__hybrid_unaligned_getle16(pc);
				pc += 2;
			}
		}
	} else
#endif /* LIBEMU86_CONFIG_WANT_16BIT */
	{
		result->mi_rm = EMU86_MODRM_GETRM(rmbyte);
#if LIBEMU86_CONFIG_WANT_64BIT
		if (flags & EMU86_F_REX_R)
			result->mi_reg |= 0x8;
		if (flags & EMU86_F_EVEX_R)
			result->mi_reg |= 0x10;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		switch (rmbyte & EMU86_MODRM_MOD_MASK) {

		case 0x0 << EMU86_MODRM_MOD_SHIFT:
			/* R/M */
			result->mi_type = EMU86_MODRM_MEMORY;
			if (result->mi_rm == EMU86_R_EBP) {
				result->mi_rm     = 0xff;
				result->mi_index  = 0xff;
				result->mi_offset = (__int32_t)__hybrid_unaligned_getle32(pc);
				pc += 4;
#if LIBEMU86_CONFIG_WANT_64BIT
				if (EMU86_F_IS64(flags))
					result->mi_rm = EMU86_R_RIP; /* RIP-relative addressing */
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
			} else if (result->mi_rm == EMU86_R_ESP) {
				sibbyte           = *pc++;
				result->mi_offset = 0;
parse_sib_byte:
				result->mi_shift = EMU86_MODRM_GETMOD(sibbyte);
				result->mi_index = EMU86_MODRM_GETREG(sibbyte);
				result->mi_rm    = EMU86_MODRM_GETRM(sibbyte);
#if LIBEMU86_CONFIG_WANT_64BIT
				if (flags & EMU86_F_REX_X)
					result->mi_index |= 0x8;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
				if (result->mi_index == EMU86_R_ESP)
					result->mi_index = 0xff;
				if ((result->mi_rm == EMU86_R_EBP) &&
				    (rmbyte & EMU86_MODRM_MOD_MASK) == (0x0 << EMU86_MODRM_MOD_SHIFT)) {
					result->mi_rm     = 0xff; /* disp32 */
					result->mi_offset = (__int32_t)__hybrid_unaligned_getle32(pc);
					pc += 4;
				}
			} else {
				result->mi_index  = 0xff;
				result->mi_offset = 0;
			}
			break;

		case 0x1 << EMU86_MODRM_MOD_SHIFT:
			/* R/M + 1-byte offset */
			result->mi_type  = EMU86_MODRM_MEMORY;
			result->mi_index = 0xff;
			if (result->mi_rm == EMU86_R_ESP) {
				sibbyte           = *pc++;
				result->mi_offset = (__int32_t)(*(__int8_t const *)pc);
				++pc;
				goto parse_sib_byte;
			}
			result->mi_offset = (__int32_t)(*(__int8_t const *)pc);
			++pc;
			break;

		case 0x2 << EMU86_MODRM_MOD_SHIFT:
			/* R/M + 4-byte offset */
			result->mi_type  = EMU86_MODRM_MEMORY;
			result->mi_index = 0xff;
			if (result->mi_rm == EMU86_R_ESP) {
				sibbyte           = *pc++;
				result->mi_offset = (__int32_t)__hybrid_unaligned_getle32(pc);
				pc += 4;
				goto parse_sib_byte;
			}
			result->mi_offset = (__int32_t)__hybrid_unaligned_getle32(pc);
			pc += 4;
			break;

		case 0x3 << EMU86_MODRM_MOD_SHIFT:
			/* Register operand. */
			result->mi_type  = EMU86_MODRM_REGISTER;
			result->mi_index = 0xff;
#if LIBEMU86_CONFIG_WANT_64BIT
			if ((flags & (EMU86_F_REX_X | EMU86_F_HASVEX)) == (EMU86_F_REX_X | EMU86_F_HASVEX))
				result->mi_rm |= 0x10;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
			break;

		default: __builtin_unreachable();
		}
#if LIBEMU86_CONFIG_WANT_64BIT
		if (flags & EMU86_F_REX_B)
			result->mi_rm |= 0x8;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	}
	return (__byte_t *)pc;
}

#endif /* __CC__ */

__DECL_END

#endif /* !_LIBEMU86_EMU86_C */
