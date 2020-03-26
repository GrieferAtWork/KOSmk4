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


EMU86_INTELLISENSE_BEGIN(misc2) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||                                             \
     ((EMU86_EMULATE_CONFIG_WANT_RDFSBASE || EMU86_EMULATE_CONFIG_WANT_RDGSBASE ||  \
       EMU86_EMULATE_CONFIG_WANT_WRFSBASE || EMU86_EMULATE_CONFIG_WANT_WRGSBASE) && \
      (CONFIG_LIBEMU86_WANT_64BIT || EMU86_EMULATE_CONFIG_FSGSBASE_32BIT)) ||       \
     (EMU86_EMULATE_CONFIG_WANT_CLWB || EMU86_EMULATE_CONFIG_WANT_CLFLUSH ||        \
      EMU86_EMULATE_CONFIG_WANT_LFENCE || EMU86_EMULATE_CONFIG_WANT_SFENCE ||       \
      EMU86_EMULATE_CONFIG_WANT_MFENCE))

case EMU86_OPCODE_ENCODE(0x0fae): {
	MODRM_DECODE();
	if (op_flags & EMU86_F_f3) {
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||                                             \
     ((EMU86_EMULATE_CONFIG_WANT_RDFSBASE || EMU86_EMULATE_CONFIG_WANT_RDGSBASE ||  \
       EMU86_EMULATE_CONFIG_WANT_WRFSBASE || EMU86_EMULATE_CONFIG_WANT_WRGSBASE) && \
      (CONFIG_LIBEMU86_WANT_64BIT || EMU86_EMULATE_CONFIG_FSGSBASE_32BIT)))
		/* Need a register operand */
		if unlikely(!EMU86_MODRM_ISREG(modrm.mi_type))
			goto return_expected_register_modrm_rmreg;
#define NEED_return_expected_register_modrm_rmreg
		/* Need 64-bit mode, or the 32-bit support extension */
#if !EMU86_EMULATE_CONFIG_FSGSBASE_32BIT
		if unlikely(!EMU86_F_IS64(op_flags))
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_FSGSBASE_32BIT */
		switch (modrm.mi_reg) {
	
#if EMU86_EMULATE_CONFIG_WANT_RDFSBASE
		case 0: {
			/* F3       0F AE /0     RDFSBASE r32     Load the 32-bit destination register with the FS base address.
			 * F3 REX.W 0F AE /0     RDFSBASE r64     Load the 64-bit destination register with the FS base address. */
			EMU86_UREG_TYPE value;
			value = (EMU86_UREG_TYPE)(uintptr_t)EMU86_GETFSBASE();
			IF_64BIT(if (IS_64BIT()) {
				MODRM_SETRMREGQ(value);
			} else) {
				MODRM_SETRMREGL(value);
			}
			goto done;
		}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
		case 0:
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */
	

#if EMU86_EMULATE_CONFIG_WANT_RDGSBASE
		case 1: {
			/* F3       0F AE /1     RDGSBASE r32     Load the 32-bit destination register with the GS base address.
			 * F3 REX.W 0F AE /1     RDGSBASE r64     Load the 64-bit destination register with the GS base address. */
			EMU86_UREG_TYPE value;
			value = (EMU86_UREG_TYPE)(uintptr_t)EMU86_GETGSBASE();
			IF_64BIT(if (IS_64BIT()) {
				MODRM_SETRMREGQ(value);
			} else) {
				MODRM_SETRMREGL(value);
			}
			goto done;
		}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
		case 1:
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */

	
#if EMU86_EMULATE_CONFIG_WANT_WRFSBASE && defined(EMU86_SETFSBASE)
		case 2: {
			/* F3       0F AE /2     WRFSBASE r32     Load the FS base address with the 32-bit value in the source register.
			 * F3 REX.W 0F AE /2     WRFSBASE r64     Load the FS base address with the 64-bit value in the source register. */
			EMU86_UREG_TYPE value;
			IF_64BIT(if (IS_64BIT()) {
				value = MODRM_GETRMREGQ();
				EMU86_VALIDATE_CANONICAL(value);
			} else) {
				value = MODRM_GETRMREGL();
			}
			EMU86_SETFSBASE(value);
			goto done;
		}
#elif (EMU86_EMULATE_CONFIG_CHECKERROR && \
       (!EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC || \
        (CONFIG_LIBEMU86_WANT_64BIT && !defined(EMU86_VALIDATE_CANONICAL_IS_NOOP))))
		case 2:
#ifndef EMU86_VALIDATE_CANONICAL_IS_NOOP
			IF_64BIT(if (IS_64BIT()) {
				EMU86_UREG_TYPE value;
				value = MODRM_GETRMREGQ();
				EMU86_VALIDATE_CANONICAL(value);
			})
#endif /* !EMU86_VALIDATE_CANONICAL_IS_NOOP */
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */
	
#if EMU86_EMULATE_CONFIG_WANT_WRFSBASE && defined(EMU86_SETGSBASE)
		case 3: {
			/* F3       0F AE /3     WRGSBASE r32     Load the GS base address with the 32-bit value in the source register.
			 * F3 REX.W 0F AE /3     WRGSBASE r64     Load the GS base address with the 64-bit value in the source register. */
			EMU86_UREG_TYPE value;
			IF_64BIT(if (IS_64BIT()) {
				value = MODRM_GETRMREGQ();
				EMU86_VALIDATE_CANONICAL(value);
			} else) {
				value = MODRM_GETRMREGL();
			}
			EMU86_SETGSBASE(value);
			goto done;
		}
#elif (EMU86_EMULATE_CONFIG_CHECKERROR && \
       (!EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC || \
        (CONFIG_LIBEMU86_WANT_64BIT && !defined(EMU86_VALIDATE_CANONICAL_IS_NOOP))))
		case 3:
#ifndef EMU86_VALIDATE_CANONICAL_IS_NOOP
			IF_64BIT(if (IS_64BIT()) {
				EMU86_UREG_TYPE value;
				value = MODRM_GETRMREGQ();
				EMU86_VALIDATE_CANONICAL(value);
			})
#endif /* !EMU86_VALIDATE_CANONICAL_IS_NOOP */
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */
	
		default:
			break;
		}
#endif /* ... */
	} else {
		switch (modrm.mi_reg) {

//TODO:	I(0xae, IF_MODRM|IF_RMM|IF_REG0,               "fxsave\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_REXW|IF_RMM|IF_REG0,       "fxsave64\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_RMM|IF_REG1,               "fxrstor\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_REXW|IF_RMM|IF_REG1,       "fxrstor64\t" OP_MEM),
//TODO:	I(0xae, IF_VEX|IF_MODRM|IF_RMM|IF_REG2, OP_VEX_B0(0,1,0,0) "vldmxcsr\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_RMM|IF_REG2,               "ldmxcsr\t" OP_MEM),
//TODO:	I(0xae, IF_VEX|IF_MODRM|IF_RMM|IF_REG3, OP_VEX_B0(0,1,0,0) "vstmxcsr\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_RMM|IF_REG3,               "stmxcsr\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_RMM|IF_REG4,               "xsave\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_REXW|IF_RMM|IF_REG4,       "xsave64\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_RMM|IF_REG5,               "xrstor\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_REXW|IF_RMM|IF_REG5,       "xrstor64\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_RMM|IF_REG6,               "xsaveopt\t" OP_MEM),
//TODO:	I(0xae, IF_MODRM|IF_REXW|IF_RMM|IF_REG6,       "xsaveopt64\t" OP_MEM),


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LFENCE
		case 5: {
			if (!EMU86_MODRM_ISREG(modrm.mi_type))
				goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
#if EMU86_EMULATE_CONFIG_WANT_LFENCE
			goto do_mfence;
#else /* EMU86_EMULATE_CONFIG_WANT_LFENCE */
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LFENCE */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LFENCE */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_CLWB || EMU86_EMULATE_CONFIG_WANT_MFENCE
		case 6:
			/* 66 0F AE /6     CLWB m8     Writes back modified cache line containing m8, and may
			 *                             retain the line in cache hierarchy in non-modified state. */
			if (op_flags & EMU86_F_66) {
				if (!EMU86_MODRM_ISMEM(modrm.mi_type))
					goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
#if EMU86_EMULATE_CONFIG_WANT_CLWB
#ifdef EMU86_EMULATE_CLWB
				EMU86_EMULATE_CLWB(MODRM_MEMADDR());
#endif /* EMU86_EMULATE_CLWB */
				goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_CLWB */
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_CLWB */
			}
#if EMU86_EMULATE_CONFIG_WANT_MFENCE
			else if (EMU86_MODRM_ISREG(modrm.mi_type)) {
				goto do_mfence;
			}
#endif /* EMU86_EMULATE_CONFIG_WANT_MFENCE */
			break;
#endif /* EMU86_EMULATE_CONFIG_WANT_CLWB || EMU86_EMULATE_CONFIG_WANT_MFENCE */


#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_CLFLUSHOPT || \
     EMU86_EMULATE_CONFIG_WANT_CLFLUSH || EMU86_EMULATE_CONFIG_WANT_SFENCE)
		case 7:
			if (EMU86_MODRM_ISMEM(modrm.mi_type)) {
				/* 0F AE /7      CLFLUSH m8      Flushes cache line containing m8 */
#if EMU86_EMULATE_CONFIG_WANT_CLFLUSHOPT || EMU86_EMULATE_CONFIG_WANT_CLFLUSH
				if (op_flags & EMU86_F_66) {
#if EMU86_EMULATE_CONFIG_WANT_CLFLUSHOPT
#ifdef EMU86_EMULATE_CLFLUSHOPT
					EMU86_EMULATE_CLFLUSHOPT(MODRM_MEMADDR());
#endif /* EMU86_EMULATE_CLFLUSHOPT */
#else /* EMU86_EMULATE_CONFIG_WANT_CLFLUSHOPT */
					goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_CLFLUSHOPT */
				} else {
#if EMU86_EMULATE_CONFIG_WANT_CLFLUSH
#ifdef EMU86_EMULATE_CLFLUSH
					EMU86_EMULATE_CLFLUSH(MODRM_MEMADDR());
#endif /* EMU86_EMULATE_CLFLUSH */
#else /* EMU86_EMULATE_CONFIG_WANT_CLFLUSH */
					goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_CLFLUSH */
				}
#else /* EMU86_EMULATE_CONFIG_WANT_CLFLUSHOPT || EMU86_EMULATE_CONFIG_WANT_CLFLUSH */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_CLFLUSHOPT && !EMU86_EMULATE_CONFIG_WANT_CLFLUSH */
			}
#if EMU86_EMULATE_CONFIG_WANT_SFENCE
			else {
				goto do_mfence;
			}
#endif /* EMU86_EMULATE_CONFIG_WANT_SFENCE */
			break;
#endif /* ... */

		default:
			break;

#if (EMU86_EMULATE_CONFIG_WANT_LFENCE || \
     EMU86_EMULATE_CONFIG_WANT_SFENCE || \
     EMU86_EMULATE_CONFIG_WANT_MFENCE)
		{
			static int fence_word = 0;
do_mfence:
			if (modrm.mi_rm != 0)
				goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
			/* NP 0F AE F8     SFENCE     Serializes store operations. */
			__hybrid_atomic_xch(fence_word, 1, __ATOMIC_SEQ_CST);
			goto done;
		}
#endif /* ... */

		}
	}
	goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
}
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
