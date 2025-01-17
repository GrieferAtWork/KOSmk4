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
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(adcx) {

#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_ADCX || \
     EMU86_EMULATE_CONFIG_WANT_ADOX || EMU86_EMULATE_CONFIG_WANT_MULX)

case EMU86_OPCODE_ENCODE(0x0f38f6): {
	MODRM_DECODE();
	if (op_flags & EMU86_F_f2) {
		/* VEX.LZ.F2.0F38.W0 F6 /r     MULX r32a, r32b, r/m32     Unsigned multiply of r/m32 with EDX without affecting arithmetic flags.
		 * VEX.LZ.F2.0F38.W1 F6 /r     MULX r64a, r64b, r/m64     Unsigned multiply of r/m64 with RDX without affecting arithmetic flags. */
		if ((op_flags & (EMU86_F_HASVEX | EMU86_F_VEX_LL_M)) != EMU86_F_HASVEX)
			goto return_unexpected_prefix;
#define NEED_return_unexpected_prefix
#if EMU86_EMULATE_CONFIG_WANT_MULX
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
#ifdef __UINT128_TYPE__
			union {
				__UINT128_TYPE__ i128;
				u64 q[2];
			} res;
			u64 src1, src2;
			src1 = EMU86_GETRDX();
			src2 = MODRM_GETRMQ();
			res.i128 = (__UINT128_TYPE__)src1 *
			           (__UINT128_TYPE__)src2;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			VEX_SETREGQ(res.q[0]);
			MODRM_SETREGQ(res.q[1]);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			VEX_SETREGQ(res.q[1]);
			MODRM_SETREGQ(res.q[0]);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#else /* __UINT128_TYPE__ */
			goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !__UINT128_TYPE__ */
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			union {
				u64 q;
				u32 l[2];
			} res;
			u32 src1, src2;
			src1 = EMU86_GETEDX();
			src2 = MODRM_GETRML();
			res.q = (u64)src1 * (u64)src2;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			VEX_SETREGL(res.l[0]);
			MODRM_SETREGL(res.l[1]);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			VEX_SETREGL(res.l[1]);
			MODRM_SETREGL(res.l[0]);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MULX */
		goto notsup_modrm_getz_rex_w_modrm_parsed;
#define NEED_notsup_modrm_getz_rex_w_modrm_parsed
#endif /* !EMU86_EMULATE_CONFIG_WANT_MULX */
	} else {
#if EMU86_EMULATE_CONFIG_WANT_ADCX || EMU86_EMULATE_CONFIG_WANT_ADOX
		u32 old_eflags, new_eflags;
		old_eflags = EMU86_GETFLAGS();
		new_eflags = old_eflags;
#endif /* EMU86_EMULATE_CONFIG_WANT_ADCX || EMU86_EMULATE_CONFIG_WANT_ADOX */
		if (op_flags & EMU86_F_66) {
			/* 66       0F 38 F6 /r     ADCX r32, r/m32     Unsigned addition of r32 with CF, r/m32 to r32, writes CF.
			 * 66 REX.w 0F 38 F6 /r     ADCX r64, r/m64     Unsigned addition of r64 with CF, r/m64 to r64, writes CF. */
			if ((op_flags & (EMU86_F_HASVEX)) != 0)
				goto return_unexpected_prefix;
#define NEED_return_unexpected_prefix
#if EMU86_EMULATE_CONFIG_WANT_ADCX
			new_eflags &= ~EFLAGS_CF;
#if LIBEMU86_CONFIG_WANT_64BIT
			if (IS_64BIT()) {
				u64 lhs, rhs, result;
				lhs = MODRM_GETREGQ();
				rhs = MODRM_GETRMQ();
				if (OVERFLOW_UADD(lhs, rhs, &result))
					new_eflags |= EFLAGS_CF;
				if (old_eflags & EFLAGS_CF) {
					if (OVERFLOW_UADD(result, 1, &result))
						new_eflags |= EFLAGS_CF;
				}
				MODRM_SETREGQ(result);
			} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
			{
				u32 lhs, rhs, result;
				lhs = MODRM_GETREGL();
				rhs = MODRM_GETRML();
				if (OVERFLOW_UADD(lhs, rhs, &result))
					new_eflags |= EFLAGS_CF;
				if (old_eflags & EFLAGS_CF) {
					if (OVERFLOW_UADD(result, 1, &result))
						new_eflags |= EFLAGS_CF;
				}
				MODRM_SETREGL(result);
			}
#else /* EMU86_EMULATE_CONFIG_WANT_ADCX */
			goto notsup_modrm_getz_rex_w_modrm_parsed;
#define NEED_notsup_modrm_getz_rex_w_modrm_parsed
#endif /* !EMU86_EMULATE_CONFIG_WANT_ADCX */
		} else if (op_flags & EMU86_F_f3) {
			/* F3       0F 38 F6 /r     ADOX r32, r/m32     Unsigned addition of r32 with OF, r/m32 to r32, writes OF.
			 * F3 REX.w 0F 38 F6 /r     ADOX r64, r/m64     Unsigned addition of r64 with OF, r/m64 to r64, writes OF. */
			if ((op_flags & (EMU86_F_HASVEX)) != 0)
				goto return_unexpected_prefix;
#define NEED_return_unexpected_prefix
#if EMU86_EMULATE_CONFIG_WANT_ADOX
			new_eflags &= ~EFLAGS_OF;
#if LIBEMU86_CONFIG_WANT_64BIT
			if (IS_64BIT()) {
				u64 lhs, rhs, result;
				lhs = MODRM_GETREGQ();
				rhs = MODRM_GETRMQ();
				if (OVERFLOW_UADD(lhs, rhs, &result))
					new_eflags |= EFLAGS_OF;
				if (old_eflags & EFLAGS_OF) {
					if (OVERFLOW_UADD(result, 1, &result))
						new_eflags |= EFLAGS_OF;
				}
				MODRM_SETREGQ(result);
			} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
			{
				u32 lhs, rhs, result;
				lhs = MODRM_GETREGL();
				rhs = MODRM_GETRML();
				if (OVERFLOW_UADD(lhs, rhs, &result))
					new_eflags |= EFLAGS_OF;
				if (old_eflags & EFLAGS_OF) {
					if (OVERFLOW_UADD(result, 1, &result))
						new_eflags |= EFLAGS_OF;
				}
				MODRM_SETREGL(result);
			}
#else /* EMU86_EMULATE_CONFIG_WANT_ADOX */
			goto notsup_modrm_getz_rex_w_modrm_parsed;
#define NEED_notsup_modrm_getz_rex_w_modrm_parsed
#endif /* !EMU86_EMULATE_CONFIG_WANT_ADOX */
		} else {
			goto return_unexpected_prefix;
#define NEED_return_unexpected_prefix
		}
#if EMU86_EMULATE_CONFIG_WANT_ADCX || EMU86_EMULATE_CONFIG_WANT_ADOX
		EMU86_SETFLAGS(new_eflags);
		goto done;
#endif /* EMU86_EMULATE_CONFIG_WANT_ADCX || EMU86_EMULATE_CONFIG_WANT_ADOX */
	}
	break;
}
#endif /* EMU86_EMULATE_CONFIG_WANT_ADCX */


}
EMU86_INTELLISENSE_END
