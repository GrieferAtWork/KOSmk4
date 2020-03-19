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
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

#include "pushpop-util.h"

EMU86_INTELLISENSE_BEGIN(misc) {


case 0xfe:
	MODRM_DECODE();
	switch (modrm.mi_reg) {

#define DO_INC_modrm(bwlq, BWLQ, Nbits, Nbytes)                                       \
	u##Nbits oldval, newval;                                                          \
	u32 eflags_addend = 0;                                                            \
	NIF_ONLY_MEMORY(                                                                  \
	if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                           \
		if unlikely(op_flags &EMU86_F_LOCK)                                           \
			goto return_unknown_instruction;                                          \
		oldval = MODRM_GETRMREG##BWLQ();                                              \
		MODRM_SETRMREG##BWLQ((u##Nbits)(oldval + 1));                                 \
	} else) {                                                                         \
		byte_t *addr = MODRM_MEMADDR();                                               \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                        \
		oldval = EMU86_EMULATE_ATOMIC_FETCHADD##BWLQ(addr, 1,                         \
		                                             (op_flags & EMU86_F_LOCK) != 0); \
	}                                                                                 \
	if (OVERFLOW_UADD(oldval, 1, &newval))                                            \
		eflags_addend |= EFLAGS_OF;                                                   \
	if ((oldval & 0xf) == 0xf)                                                        \
		eflags_addend |= EFLAGS_AF;                                                   \
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),      \
	               eflags_addend | emu86_geteflags_test##bwlq(newval));

#define DO_DEC_modrm(bwlq, BWLQ, Nbits, Nbytes)                                       \
	u##Nbits oldval, newval;                                                          \
	u32 eflags_addend = EFLAGS_AF;                                                    \
	NIF_ONLY_MEMORY(                                                                  \
	if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                           \
		if unlikely(op_flags &EMU86_F_LOCK)                                           \
			goto return_unknown_instruction;                                          \
		oldval = MODRM_GETRMREG##BWLQ();                                              \
		MODRM_SETRMREG##BWLQ(oldval - 1);                                             \
	} else) {                                                                         \
		byte_t *addr = MODRM_MEMADDR();                                               \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                        \
		oldval = EMU86_EMULATE_ATOMIC_FETCHSUB##BWLQ(addr, 1,                         \
		                                             (op_flags & EMU86_F_LOCK) != 0); \
	}                                                                                 \
	if (OVERFLOW_USUB(oldval, 1, &newval))                                            \
		eflags_addend |= EFLAGS_OF;                                                   \
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),      \
	               eflags_addend | emu86_geteflags_test##bwlq(newval));



	case 0: {
		/* FE /0      INC r/m8      Increment r/m byte by 1 */
		DO_INC_modrm(b, B, 8, 1)
		goto done;
	}

	case 1: {
		/* FE /1      DEC r/m8      Decrement r/m8 by 1 */
		DO_DEC_modrm(b, B, 8, 1)
		goto done;
	}

	default:
		break;
	}
	goto return_unknown_instruction;


case 0xff:
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 0: {
		/* FF /0      INC r/m16      Increment r/m byte by 1
		 * FF /0      INC r/m32      Increment r/m byte by 1
		 * FF /0      INC r/m64      Increment r/m byte by 1 */
		IF_64BIT(if (IS_64BIT()) {
			DO_INC_modrm(q, Q, 64, 8)
		} else) if (!IS_16BIT()) {
			DO_INC_modrm(l, L, 32, 4)
		} else {
			DO_INC_modrm(w, W, 16, 2)
		}
		goto done;
	}

	case 1: {
		/* FF /1      DEC r/m16      Decrement r/m byte by 1
		 * FF /1      DEC r/m32      Decrement r/m byte by 1
		 * FF /1      DEC r/m64      Decrement r/m byte by 1 */
		IF_64BIT(if (IS_64BIT()) {
			DO_DEC_modrm(q, Q, 64, 8)
		} else) if (!IS_16BIT()) {
			DO_DEC_modrm(l, L, 32, 4)
		} else {
			DO_DEC_modrm(w, W, 16, 2)
		}
		goto done;
	}


	case 2: {
		byte_t *sp = (byte_t *)EMU86_GETSP();
		/* FF /2      CALL r/m16      Call near, absolute indirect, address given in r/m16 */
		/* FF /2      CALL r/m32      Call near, absolute indirect, address given in r/m32 */
		/* FF /2      CALL r/m64      Call near, absolute indirect, address given in r/m64 */
#if CONFIG_LIBEMU86_WANT_64BIT
		IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
			/* 64-bit mode */
			u64 dest_pc = MODRM_GETRMQ();
			sp -= 8;
			EMU86_EMULATE_PUSH(sp, 8);
			EMU86_WRITE_USER_MEMORY(sp, 8);
			EMU86_EMULATE_WRITEQ(sp, (u64)REAL_PC());
			EMU86_EMULATE_SETPC(dest_pc);
		}
		IF_16BIT_OR_32BIT(else)
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
		{
			/* 16/32-bit mode */
			if (!IS_16BIT()) {
				u32 dest_pc = MODRM_GETRML();
				sp -= 4;
				EMU86_EMULATE_PUSH(sp, 4);
				EMU86_WRITE_USER_MEMORY(sp, 4);
				EMU86_EMULATE_WRITEL(sp, (u32)REAL_PC());
				EMU86_EMULATE_SETPC(dest_pc);
			} else {
				u16 dest_pc = MODRM_GETRMW();
				sp -= 2;
				EMU86_EMULATE_PUSH(sp, 2);
				EMU86_WRITE_USER_MEMORY(sp, 2);
				EMU86_EMULATE_WRITEW(sp, (u16)REAL_PC());
				EMU86_EMULATE_SETPC(dest_pc);
			}
		}
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
		EMU86_SETSP(sp);
		goto done_dont_set_pc;
	}


	case 3: {
		/*       FF /3    CALL m16:16    Call far, absolute indirect, address given in m16:16.
		 *       FF /3    CALL m16:32    Call far, absolute indirect, address given in m16:32.
		 * REX.W FF /3    CALL m16:64    Call far, absolute indirect, address given in m16:64. */
		byte_t *sp;
#if CONFIG_LIBEMU86_WANT_64BIT
		u64 offset;
#else /* CONFIG_LIBEMU86_WANT_64BIT */
		u32 offset;
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
		u16 segment;
		byte_t *addr;
#ifndef EMU86_EMULATE_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_unknown_instruction;
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
		addr = MODRM_MEMADDR();
		IF_64BIT(if (IS_64BIT()) {
			EMU86_READ_USER_MEMORY(addr, 10);
			offset = EMU86_EMULATE_READQ(addr);
			pc += 8;
		} else) if (!IS_16BIT()) {
			EMU86_READ_USER_MEMORY(addr, 6);
			offset = EMU86_EMULATE_READL(addr);
			pc += 4;
		} else {
			EMU86_READ_USER_MEMORY(addr, 4);
			offset = EMU86_EMULATE_READW(addr);
			pc += 2;
		}
		segment = EMU86_EMULATE_READW(addr);
		/* Verify the segment index. */
#if EMU86_EMULATE_CHECKUSER
		if (!SEGMENT_IS_VALID_USERCODE(segment) && EMU86_ISUSER_NOVM86()) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_CS, segment);
		}
#endif /* EMU86_EMULATE_CHECKUSER */
		sp = (byte_t *)EMU86_GETSP();
		IF_64BIT(if (IS_64BIT()) {
			sp -= 16;
			EMU86_EMULATE_PUSH(sp, 16);
			EMU86_WRITE_USER_MEMORY(sp, 16);
			EMU86_EMULATE_WRITEQ(sp + 8, (u64)EMU86_GETCS());
			EMU86_EMULATE_WRITEQ(sp + 0, (u64)REAL_PC());
		} else) if (!IS_16BIT()) {
			sp -= 8;
			EMU86_EMULATE_PUSH(sp, 8);
			EMU86_WRITE_USER_MEMORY(sp, 8);
			EMU86_EMULATE_WRITEL(sp + 4, (u32)EMU86_GETCS());
			EMU86_EMULATE_WRITEL(sp + 0, (u32)REAL_PC());
		} else {
			sp -= 4;
			EMU86_EMULATE_PUSH(sp, 4);
			EMU86_WRITE_USER_MEMORY(sp, 4);
			EMU86_EMULATE_WRITEW(sp + 2, (u16)EMU86_GETCS());
			EMU86_EMULATE_WRITEW(sp + 0, (u16)REAL_PC());
		}
		EMU86_SETSP(sp);
		EMU86_SETCS(segment);
		EMU86_EMULATE_SETIP(offset);
		goto done_dont_set_pc;
	}


	case 4: {
		/* FF /2      JMP r/m16      Jump near, absolute indirect, address given in r/m16 */
		/* FF /2      JMP r/m32      Jump near, absolute indirect, address given in r/m32 */
		/* FF /2      JMP r/m64      Jump near, absolute indirect, address given in r/m64 */
#if CONFIG_LIBEMU86_WANT_64BIT
		IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
			/* 64-bit mode */
			u64 dest_pc = MODRM_GETRMQ();
			EMU86_EMULATE_SETPC(dest_pc);
		}
		IF_16BIT_OR_32BIT(else)
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
		{
			/* 16/32-bit mode */
			if (!IS_16BIT()) {
				u32 dest_pc = MODRM_GETRML();
				EMU86_EMULATE_SETPC(dest_pc);
			} else {
				u16 dest_pc = MODRM_GETRMW();
				EMU86_EMULATE_SETPC(dest_pc);
			}
		}
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
		goto done_dont_set_pc;
	}


	case 5: {
		/*       FF /5    JMP m16:16    Jump far, absolute indirect, address given in m16:16.
		 *       FF /5    JMP m16:32    Jump far, absolute indirect, address given in m16:32.
		 * REX.W FF /5    JMP m16:64    Jump far, absolute indirect, address given in m16:64. */
#if CONFIG_LIBEMU86_WANT_64BIT
		u64 offset;
#else /* CONFIG_LIBEMU86_WANT_64BIT */
		u32 offset;
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
		u16 segment;
		byte_t *addr;
#ifndef EMU86_EMULATE_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_unknown_instruction;
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
		addr = MODRM_MEMADDR();
		IF_64BIT(if (IS_64BIT()) {
			EMU86_READ_USER_MEMORY(addr, 10);
			offset = EMU86_EMULATE_READQ(addr);
			pc += 8;
		} else) if (!IS_16BIT()) {
			EMU86_READ_USER_MEMORY(addr, 6);
			offset = EMU86_EMULATE_READL(addr);
			pc += 4;
		} else {
			EMU86_READ_USER_MEMORY(addr, 4);
			offset = EMU86_EMULATE_READW(addr);
			pc += 2;
		}
		segment = EMU86_EMULATE_READW(addr);
		/* Verify the segment index. */
#if EMU86_EMULATE_CHECKUSER
		if (!SEGMENT_IS_VALID_USERCODE(segment) && EMU86_ISUSER_NOVM86()) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_CS, segment);
		}
#endif /* EMU86_EMULATE_CHECKUSER */
		EMU86_SETCS(segment);
		EMU86_EMULATE_SETIP(offset);
		goto done_dont_set_pc;
	}


	case 6:
		/* FF /6     PUSH r/m16     Push r/m16.
		 * FF /6     PUSH r/m32     Push r/m32.
		 * FF /6     PUSH r/m64     Push r/m64. */
		EMU86_PUSH163264(MODRM_GETRMW(),
		                 MODRM_GETRML(),
		                 MODRM_GETRMQ());
		break;


	default:
		break;
	}
	goto return_unknown_instruction;

#undef DO_DEC_modrm
#undef DO_INC_modrm


}
EMU86_INTELLISENSE_END
