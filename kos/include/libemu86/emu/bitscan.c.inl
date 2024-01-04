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
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(bitscan) {


#if EMU86_EMULATE_CONFIG_WANT_TZCNT || EMU86_EMULATE_CONFIG_WANT_BSF
case EMU86_OPCODE_ENCODE(0x0fbc):
#if EMU86_EMULATE_CONFIG_WANT_TZCNT && EMU86_EMULATE_CONFIG_WANT_BSF
	MODRM_DECODE();
#endif /* EMU86_EMULATE_CONFIG_WANT_TZCNT && EMU86_EMULATE_CONFIG_WANT_BSF */
	if (op_flags & EMU86_F_REP) {
#if EMU86_EMULATE_CONFIG_WANT_TZCNT
		/* F3       0F BC /r TZCNT r16, r/m16   Count the number of trailing zero bits in r/m16, return result in r16.
		 * F3       0F BC /r TZCNT r32, r/m32   Count the number of trailing zero bits in r/m32, return result in r32.
		 * F3 REX.W 0F BC /r TZCNT r64, r/m64   Count the number of trailing zero bits in r/m64, return result in r64. */
		u32 flags = 0;
#if !EMU86_EMULATE_CONFIG_WANT_BSF
		MODRM_DECODE();
#endif /* !EMU86_EMULATE_CONFIG_WANT_BSF */
		IF_64BIT(if (IS_64BIT()) {
			MODRM_SETREGQ(emu86_tzcntq(MODRM_GETRMQ(), &flags));
		} else) if (!IS_16BIT()) {
			MODRM_SETREGL(emu86_tzcntl(MODRM_GETRML(), &flags));
		} else {
			MODRM_SETREGW(emu86_tzcntw(MODRM_GETRMW(), &flags));
		}
		EMU86_MSKFLAGS(~(EFLAGS_ZF | EFLAGS_CF), flags);
#else /* EMU86_EMULATE_CONFIG_WANT_TZCNT */
		goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_TZCNT */
	} else {
#if EMU86_EMULATE_CONFIG_WANT_BSF
		/*         0F BC /r BSF r16, r/m16   Bit scan forward on r/m16
		 *         0F BC /r BSF r32, r/m32   Bit scan forward on r/m32
		 * REX.W + 0F BC /r BSF r64, r/m64   Bit scan forward on r/m64. */
#if !EMU86_EMULATE_CONFIG_WANT_TZCNT
		MODRM_DECODE();
#endif /* !EMU86_EMULATE_CONFIG_WANT_TZCNT */
		IF_64BIT(if (IS_64BIT()) {
			unsigned int result = 0;
			u64 temp = MODRM_GETRMQ();
			if (!temp) {
				EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
			} else {
				EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
				while (!(temp & ((u64)1 << result)))
					++result;
			}
			MODRM_SETREGQ(result);
		} else) if (!IS_16BIT()) {
			unsigned int result = 0;
			u32 temp = MODRM_GETRML();
			if (!temp) {
				EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
			} else {
				EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
				while (!(temp & ((u32)1 << result)))
					++result;
			}
			MODRM_SETREGL(result);
		} else {
			unsigned int result = 0;
			u16 temp = MODRM_GETRMW();
			if (!temp) {
				EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
			} else {
				EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
				while (!(temp & ((u16)1 << result)))
					++result;
			}
			MODRM_SETREGW(result);
		}
#else /* EMU86_EMULATE_CONFIG_WANT_BSF */
		goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_BSF */
	}
	goto done;
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0fbc):
	goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#endif /* ... */




#if EMU86_EMULATE_CONFIG_WANT_LZCNT || EMU86_EMULATE_CONFIG_WANT_BSR
case EMU86_OPCODE_ENCODE(0x0fbd):
#if EMU86_EMULATE_CONFIG_WANT_LZCNT && EMU86_EMULATE_CONFIG_WANT_BSR
	MODRM_DECODE();
#endif /* EMU86_EMULATE_CONFIG_WANT_LZCNT && EMU86_EMULATE_CONFIG_WANT_BSR */
	if (op_flags & EMU86_F_REP) {
#if EMU86_EMULATE_CONFIG_WANT_LZCNT
		/* F3       0F BD /r  LZCNT r16, r/m16
		 * F3       0F BD /r  LZCNT r32, r/m32
		 * F3 REX.W 0F BD /r  LZCNT r64, r/m64 */
		u32 flags = 0;
#if !EMU86_EMULATE_CONFIG_WANT_BSR
		MODRM_DECODE();
#endif /* !EMU86_EMULATE_CONFIG_WANT_BSR */
		IF_64BIT(if (IS_64BIT()) {
			MODRM_SETREGQ(emu86_lzcntq(MODRM_GETRMQ(), &flags));
		} else) if (!IS_16BIT()) {
			MODRM_SETREGL(emu86_lzcntl(MODRM_GETRML(), &flags));
		} else {
			MODRM_SETREGW(emu86_lzcntw(MODRM_GETRMW(), &flags));
		}
		EMU86_MSKFLAGS(~(EFLAGS_ZF | EFLAGS_CF), flags);
#else /* EMU86_EMULATE_CONFIG_WANT_LZCNT */
		goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_LZCNT */
	} else {
#if EMU86_EMULATE_CONFIG_WANT_BSR
		/*         0F BD /r BSR r16, r/m16   Bit scan reverse on r/m16
		 *         0F BD /r BSR r32, r/m32   Bit scan reverse on r/m32
		 * REX.W + 0F BD /r BSR r64, r/m64   Bit scan reverse on r/m64. */
#if !EMU86_EMULATE_CONFIG_WANT_LZCNT
		MODRM_DECODE();
#endif /* !EMU86_EMULATE_CONFIG_WANT_LZCNT */
		IF_64BIT(if (IS_64BIT()) {
			unsigned int result = 63;
			u64 temp = MODRM_GETRMQ();
			if (!temp) {
				EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
			} else {
				EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
				while (!(temp & ((u64)1 << result)))
					--result;
			}
			MODRM_SETREGQ(result);
		} else) if (!IS_16BIT()) {
			unsigned int result = 31;
			u32 temp = MODRM_GETRML();
			if (!temp) {
				EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
			} else {
				EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
				while (!(temp & ((u32)1 << result)))
					--result;
			}
			MODRM_SETREGL(result);
		} else {
			unsigned int result = 15;
			u16 temp = MODRM_GETRMW();
			if (!temp) {
				EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
			} else {
				EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
				while (!(temp & ((u16)1 << result)))
					--result;
			}
			MODRM_SETREGW(result);
		}
#else /* EMU86_EMULATE_CONFIG_WANT_BSR */
		goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_BSR */
	}
	goto done;
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0fbd):
	goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#endif /* ... */


}
EMU86_INTELLISENSE_END
