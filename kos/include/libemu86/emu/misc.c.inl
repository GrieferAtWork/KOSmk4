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

#include "push-pop-util.h"

EMU86_INTELLISENSE_BEGIN(misc) {


case 0xfe:
	MODRM_DECODE();
	switch (modrm.mi_reg) {

#define DO_INC_modrm(bwlq, BWLQ, Nbits, Nbytes)                                   \
	u##Nbits oldval, newval;                                                      \
	u32 eflags_addend = 0;                                                        \
	NIF_ONLY_MEMORY(                                                              \
	if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                       \
		if unlikely(op_flags &EMU86_F_LOCK)                                       \
			goto return_unknown_instruction;                                      \
		oldval = MODRM_GETRMREG##BWLQ();                                          \
		MODRM_SETRMREG##BWLQ((u##Nbits)(oldval + 1));                             \
	} else) {                                                                     \
		byte_t *addr = MODRM_MEMADDR();                                           \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                    \
		oldval = EMU86_MEM_ATOMIC_FETCHADD##BWLQ(addr, 1,                         \
		                                         (op_flags & EMU86_F_LOCK) != 0); \
	}                                                                             \
	if (OVERFLOW_SADD((s##Nbits)oldval, (s##Nbits)1, (s##Nbits *)&newval))        \
		eflags_addend |= EFLAGS_OF;                                               \
	if (emu86_getflags_AF_add(oldval, 1))                                         \
		eflags_addend |= EFLAGS_AF;                                               \
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),  \
	               eflags_addend | emu86_geteflags_test##bwlq(newval));

#define DO_DEC_modrm(bwlq, BWLQ, Nbits, Nbytes)                                   \
	u##Nbits oldval, newval;                                                      \
	u32 eflags_addend = 0;                                                        \
	NIF_ONLY_MEMORY(                                                              \
	if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                       \
		if unlikely(op_flags &EMU86_F_LOCK)                                       \
			goto return_unknown_instruction;                                      \
		oldval = MODRM_GETRMREG##BWLQ();                                          \
		MODRM_SETRMREG##BWLQ(oldval - 1);                                         \
	} else) {                                                                     \
		byte_t *addr = MODRM_MEMADDR();                                           \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                    \
		oldval = EMU86_MEM_ATOMIC_FETCHSUB##BWLQ(addr, 1,                         \
		                                         (op_flags & EMU86_F_LOCK) != 0); \
	}                                                                             \
	if (OVERFLOW_SSUB((s##Nbits)oldval, (s##Nbits)1, (s##Nbits *)&newval))        \
		eflags_addend |= EFLAGS_OF;                                               \
	if (emu86_getflags_AF_sub(oldval, 1))                                         \
		eflags_addend |= EFLAGS_AF;                                               \
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),  \
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
		/* FF /2      CALL r/m16      Call near, absolute indirect, address given in r/m16 */
		/* FF /2      CALL r/m32      Call near, absolute indirect, address given in r/m32 */
		/* FF /2      CALL r/m64      Call near, absolute indirect, address given in r/m64 */
		EMU86_UREG_TYPE dest_ip;
		EMU86_PUSH163264((dest_ip = MODRM_GETRMW(), (u16)REAL_IP()),
		                 (dest_ip = MODRM_GETRML(), (u32)REAL_IP()),
		                 (dest_ip = MODRM_GETRMQ(), (u64)REAL_IP()));
		EMU86_SETIPREG(dest_ip);
		goto done_dont_set_pc;
	}


	case 3: {
		/*       FF /3    CALL m16:16    Call far, absolute indirect, address given in m16:16.
		 *       FF /3    CALL m16:32    Call far, absolute indirect, address given in m16:32.
		 * REX.W FF /3    CALL m16:64    Call far, absolute indirect, address given in m16:64. */
		byte_t *sp;
		EMU86_UREG_TYPE offset;
		u16 segment;
		byte_t *addr;
#ifndef EMU86_EMULATE_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_unknown_instruction;
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
		addr = MODRM_MEMADDR();
		IF_64BIT(if (IS_64BIT()) {
			EMU86_READ_USER_MEMORY(addr, 10);
			offset = EMU86_MEMREADQ(addr);
			pc += 8;
		} else) if (!IS_16BIT()) {
			EMU86_READ_USER_MEMORY(addr, 6);
			offset = EMU86_MEMREADL(addr);
			pc += 4;
		} else {
			EMU86_READ_USER_MEMORY(addr, 4);
			offset = EMU86_MEMREADW(addr);
			pc += 2;
		}
		segment = EMU86_MEMREADW(addr);
		/* Verify the segment index. */
#if EMU86_EMULATE_CHECKUSER
		if (!SEGMENT_IS_VALID_USERCODE(segment) && EMU86_ISUSER_NOVM86()) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_CS, segment);
		}
#endif /* EMU86_EMULATE_CHECKUSER */
		sp = EMU86_GETSTACKPTR();
		IF_64BIT(if (IS_64BIT()) {
			sp -= 16;
			EMU86_EMULATE_PUSH(sp, 16);
			EMU86_WRITE_USER_MEMORY(sp, 16);
			EMU86_MEMWRITEQ(sp + 8, (u64)EMU86_GETCS());
			EMU86_MEMWRITEQ(sp + 0, (u64)REAL_IP());
		} else) if (!IS_16BIT()) {
			sp -= 8;
			EMU86_EMULATE_PUSH(sp, 8);
			EMU86_WRITE_USER_MEMORY(sp, 8);
			EMU86_MEMWRITEL(sp + 4, (u32)EMU86_GETCS());
			EMU86_MEMWRITEL(sp + 0, (u32)REAL_IP());
		} else {
			sp -= 4;
			EMU86_EMULATE_PUSH(sp, 4);
			EMU86_WRITE_USER_MEMORY(sp, 4);
			EMU86_MEMWRITEW(sp + 2, (u16)EMU86_GETCS());
			EMU86_MEMWRITEW(sp + 0, (u16)REAL_IP());
		}
		EMU86_SETSTACKPTR(sp);
		EMU86_SETCS(segment);
		EMU86_SETIPREG(offset);
		goto done_dont_set_pc;
	}


	case 4: {
		/* FF /2      JMP r/m16      Jump near, absolute indirect, address given in r/m16 */
		/* FF /2      JMP r/m32      Jump near, absolute indirect, address given in r/m32 */
		/* FF /2      JMP r/m64      Jump near, absolute indirect, address given in r/m64 */
		EMU86_UREG_TYPE dest_ip;
		if (IS_16BIT()) {
			dest_ip = MODRM_GETRMW();
		} IF_64BIT(else IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
			dest_ip = MODRM_GETRMQ();
		}) IF_16BIT_OR_32BIT(else {
			dest_ip = MODRM_GETRML();
		})
		EMU86_SETIPREG(dest_ip);
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
			offset = EMU86_MEMREADQ(addr);
			pc += 8;
		} else) if (!IS_16BIT()) {
			EMU86_READ_USER_MEMORY(addr, 6);
			offset = EMU86_MEMREADL(addr);
			pc += 4;
		} else {
			EMU86_READ_USER_MEMORY(addr, 4);
			offset = EMU86_MEMREADW(addr);
			pc += 2;
		}
		segment = EMU86_MEMREADW(addr);
		/* Verify the segment index. */
#if EMU86_EMULATE_CHECKUSER
		if (!SEGMENT_IS_VALID_USERCODE(segment) && EMU86_ISUSER_NOVM86()) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_CS, segment);
		}
#endif /* EMU86_EMULATE_CHECKUSER */
		EMU86_SETCS(segment);
		EMU86_SETIPREG(offset);
		goto done_dont_set_pc;
	}


	case 6:
		/* FF /6     PUSH r/m16     Push r/m16.
		 * FF /6     PUSH r/m32     Push r/m32.
		 * FF /6     PUSH r/m64     Push r/m64. */
		if unlikely(op_flags & EMU86_F_LOCK)
			goto return_unknown_instruction;
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
