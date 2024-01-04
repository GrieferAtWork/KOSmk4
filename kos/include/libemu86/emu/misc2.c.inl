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

#include "push-pop-util.h"

EMU86_INTELLISENSE_BEGIN(misc2) {

#if ((!EMU86_EMULATE_CONFIG_ONLY_MEMORY &&                                            \
      (EMU86_EMULATE_CONFIG_CHECKERROR ||                                             \
       ((EMU86_EMULATE_CONFIG_WANT_RDFSBASE || EMU86_EMULATE_CONFIG_WANT_RDGSBASE ||  \
         EMU86_EMULATE_CONFIG_WANT_WRFSBASE || EMU86_EMULATE_CONFIG_WANT_WRGSBASE) && \
        (LIBEMU86_CONFIG_WANT_64BIT || EMU86_EMULATE_CONFIG_FSGSBASE_32BIT)) ||       \
       (EMU86_EMULATE_CONFIG_WANT_CLWB || EMU86_EMULATE_CONFIG_WANT_CLFLUSH ||        \
        EMU86_EMULATE_CONFIG_WANT_LFENCE || EMU86_EMULATE_CONFIG_WANT_SFENCE ||       \
        EMU86_EMULATE_CONFIG_WANT_MFENCE || EMU86_EMULATE_CONFIG_WANT_TPAUSE))) ||    \
     (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LDMXCSR ||         \
      EMU86_EMULATE_CONFIG_WANT_STMXCSR))

case EMU86_OPCODE_ENCODE(0x0fae): {
	MODRM_DECODE();
	if (op_flags & EMU86_F_f3) {
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||                                             \
     ((EMU86_EMULATE_CONFIG_WANT_RDFSBASE || EMU86_EMULATE_CONFIG_WANT_RDGSBASE ||  \
       EMU86_EMULATE_CONFIG_WANT_WRFSBASE || EMU86_EMULATE_CONFIG_WANT_WRGSBASE) && \
      (LIBEMU86_CONFIG_WANT_64BIT || EMU86_EMULATE_CONFIG_FSGSBASE_32BIT)))
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
#ifdef EMU86_EMULATE_PATCH_RDFSBASE
			EMU86_EMULATE_PATCH_RDFSBASE(start_pc);
#endif /* EMU86_EMULATE_PATCH_RDFSBASE */
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
#ifdef EMU86_EMULATE_PATCH_RDGSBASE
			EMU86_EMULATE_PATCH_RDGSBASE(start_pc);
#endif /* EMU86_EMULATE_PATCH_RDGSBASE */
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
#ifdef EMU86_EMULATE_PATCH_WRFSBASE
			EMU86_EMULATE_PATCH_WRFSBASE(start_pc);
#endif /* EMU86_EMULATE_PATCH_WRFSBASE */
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
        (LIBEMU86_CONFIG_WANT_64BIT && !defined(EMU86_VALIDATE_CANONICAL_IS_NOOP))))
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

#if EMU86_EMULATE_CONFIG_WANT_WRGSBASE && defined(EMU86_SETGSBASE)
		case 3: {
			/* F3       0F AE /3     WRGSBASE r32     Load the GS base address with the 32-bit value in the source register.
			 * F3 REX.W 0F AE /3     WRGSBASE r64     Load the GS base address with the 64-bit value in the source register. */
			EMU86_UREG_TYPE value;
#ifdef EMU86_EMULATE_PATCH_WRGSBASE
			EMU86_EMULATE_PATCH_WRGSBASE(start_pc);
#endif /* EMU86_EMULATE_PATCH_WRGSBASE */
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
        (LIBEMU86_CONFIG_WANT_64BIT && !defined(EMU86_VALIDATE_CANONICAL_IS_NOOP))))
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
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
	} else {
		switch (modrm.mi_reg) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LDMXCSR
		case 2: {
			/*         NP 0F AE /2 LDMXCSR m32      Load MXCSR register from m32.
			 * VEX.LZ.0F.WIG AE /2 VLDMXCSR m32     Load MXCSR register from m32. */
			u32 mxcsr;
			if ((op_flags & (EMU86_F_VEX_VVVVV_M | EMU86_F_VEX_LL_M)) != 0)
				goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
			if (!EMU86_MODRM_ISMEM(modrm.mi_type))
				goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
			mxcsr = MODRM_GETRMMEML();
			if (mxcsr & ~0xffff) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
				EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,
				                                                 X86_REGISTER_MISC_MXCSR, 0, mxcsr, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			}
#if EMU86_EMULATE_CONFIG_WANT_LDMXCSR && defined(EMU86_EMULATE_LDMXCSR)
			EMU86_EMULATE_LDMXCSR(mxcsr);
			goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LDMXCSR && EMU86_EMULATE_LDMXCSR */
#define NEED_notsup_modrm_getl_rmreg_modrm_parsed
			goto notsup_modrm_getl_rmreg_modrm_parsed;
#endif /* !EMU86_EMULATE_CONFIG_WANT_LDMXCSR || !EMU86_EMULATE_LDMXCSR */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LDMXCSR */



#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STMXCSR
		case 3: {
			/*         NP 0F AE /3 STMXCSR m32      Store contents of MXCSR register to m32.
			 * VEX.LZ.0F.WIG AE /3 VSTMXCSR m32     Store contents of MXCSR register to m32. */
			if ((op_flags & (EMU86_F_VEX_VVVVV_M | EMU86_F_VEX_LL_M)) != 0)
				goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
			if (!EMU86_MODRM_ISMEM(modrm.mi_type))
				goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_WANT_STMXCSR && defined(EMU86_EMULATE_STMXCSR)
			{
				u32 mxcsr = EMU86_EMULATE_STMXCSR();
				MODRM_SETRMMEML(mxcsr);
				goto done;
			}
#else /* EMU86_EMULATE_CONFIG_WANT_STMXCSR && EMU86_EMULATE_STMXCSR */
#define NEED_notsup_modrm_setl_rmreg_modrm_parsed
			goto notsup_modrm_setl_rmreg_modrm_parsed;
#endif /* !EMU86_EMULATE_CONFIG_WANT_STMXCSR || !EMU86_EMULATE_STMXCSR */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STMXCSR */



#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LFENCE
		case 5: {
			/* NP 0F AE E8     LFENCE     Serializes load operations. */
			if (!EMU86_MODRM_ISREG(modrm.mi_type))
				goto return_expected_register_modrm_rmreg;
#define NEED_return_expected_register_modrm_rmreg
#if EMU86_EMULATE_CONFIG_WANT_LFENCE
#ifdef EMU86_EMULATE_LFENCE
			if unlikely(modrm.mi_rm != 0)
				goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
			if unlikely(op_flags & (EMU86_F_66 | EMU86_F_f2 | EMU86_F_f3))
				goto return_unexpected_prefix_rmreg;
#define NEED_return_unexpected_prefix_rmreg
			EMU86_EMULATE_LFENCE();
			goto done;
#else /* EMU86_EMULATE_LFENCE */
			goto check_mi_rm_and_op_flags_and_do_fencelock;
#define NEED_check_mi_rm_and_op_flags_and_do_fencelock
#endif /* !EMU86_EMULATE_LFENCE */
#else /* EMU86_EMULATE_CONFIG_WANT_LFENCE */
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LFENCE */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LFENCE */



#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_CLWB || \
     EMU86_EMULATE_CONFIG_WANT_MFENCE || EMU86_EMULATE_CONFIG_WANT_TPAUSE)
		case 6:
			if (op_flags & EMU86_F_66) {
				if (!EMU86_MODRM_ISMEM(modrm.mi_type)) {
#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_TPAUSE
					/* 66 0F AE /6     TPAUSE r32, <edx>, <eax> */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_TSD_IS_ZERO
					if (EMU86_GETCR4_TSD() && EMU86_ISUSER()) {
						goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
					}
#endif /* !EMU86_GETCR4_TSD_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_CHECKERROR || (EMU86_EMULATE_CONFIG_WANT_TPAUSE && defined(EMU86_EMULATE_TPAUSE))
					{
						u32 mode;
						mode = MODRM_GETRMREGL();
						if ((mode & ~1) != 0) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
							EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,
							                                                 X86_REGISTER_MISC_TPAUSE, 0, mode, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
							goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
						}
#if EMU86_EMULATE_CONFIG_WANT_TPAUSE && defined(EMU86_EMULATE_TPAUSE)
						{
							bool ok;
							ok = EMU86_EMULATE_TPAUSE((mode & 1) != 0,
							                          (u64)(EMU86_GETEAX()) |
							                          (u64)(EMU86_GETEDX() << 32));
							EMU86_MSKFLAGS(~(EFLAGS_AF | EFLAGS_PF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_OF),
							               ok ? EFLAGS_CF : 0);
							goto done;
						}
#else /* EMU86_EMULATE_CONFIG_WANT_TPAUSE && EMU86_EMULATE_TPAUSE */
						goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_TPAUSE || !EMU86_EMULATE_TPAUSE */
					}
#else /* EMU86_EMULATE_CONFIG_CHECKERROR || (EMU86_EMULATE_CONFIG_WANT_TPAUSE && EMU86_EMULATE_TPAUSE) */
					goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_CHECKERROR && (!EMU86_EMULATE_CONFIG_WANT_TPAUSE || !EMU86_EMULATE_TPAUSE) */
#else /* EMU86_EMULATE_CONFIG_WANT_TPAUSE */
					goto return_expected_register_modrm_rmreg;
#define NEED_return_expected_register_modrm_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_TPAUSE */
				}


				/* 66 0F AE /6     CLWB m8     Writes back modified  cache line containing  m8, and  may
				 *                             retain the line in cache hierarchy in non-modified state. */
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
				/* NP 0F AE F0     MFENCE     Serializes load and store operations. */
#ifdef EMU86_EMULATE_MFENCE
				if unlikely(modrm.mi_rm != 0)
					goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
				if unlikely(op_flags & (EMU86_F_66 | EMU86_F_f2 | EMU86_F_f3))
					goto return_unexpected_prefix_rmreg;
#define NEED_return_unexpected_prefix_rmreg
				EMU86_EMULATE_MFENCE();
				goto done;
#else /* EMU86_EMULATE_MFENCE */
				goto check_mi_rm_and_op_flags_and_do_fencelock;
#define NEED_check_mi_rm_and_op_flags_and_do_fencelock
#endif /* !EMU86_EMULATE_MFENCE */
			}
#endif /* EMU86_EMULATE_CONFIG_WANT_MFENCE */
			break;
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_(CLWB|MFENCE|TPAUSE) */



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
				/* NP 0F AE F8     SFENCE     Serializes store operations. */
#ifdef EMU86_EMULATE_SFENCE
				if unlikely(modrm.mi_rm != 0)
					goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
				if unlikely(op_flags & (EMU86_F_66 | EMU86_F_f2 | EMU86_F_f3))
					goto return_unexpected_prefix_rmreg;
#define NEED_return_unexpected_prefix_rmreg
				EMU86_EMULATE_SFENCE();
				goto done;
#else /* EMU86_EMULATE_SFENCE */
				goto check_mi_rm_and_op_flags_and_do_fencelock;
#define NEED_check_mi_rm_and_op_flags_and_do_fencelock
#endif /* !EMU86_EMULATE_SFENCE */
			}
#endif /* EMU86_EMULATE_CONFIG_WANT_SFENCE */
			break;
#endif /* ... */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

		default:
			break;

#ifdef NEED_check_mi_rm_and_op_flags_and_do_fencelock
#undef NEED_check_mi_rm_and_op_flags_and_do_fencelock
check_mi_rm_and_op_flags_and_do_fencelock:
			if unlikely(modrm.mi_rm != 0)
				goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
			if unlikely(op_flags & (EMU86_F_66 | EMU86_F_f2 | EMU86_F_f3))
				goto return_unexpected_prefix_rmreg;
#define NEED_return_unexpected_prefix_rmreg
#ifdef EMU86_EMULATE_FENCELOCK
			EMU86_EMULATE_FENCELOCK();
			goto done;
#else /* EMU86_EMULATE_FENCELOCK */
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_FENCELOCK */
#endif /* NEED_check_mi_rm_and_op_flags_and_do_fencelock */

		}
	}
	goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
}
#endif /* ... */

}
EMU86_INTELLISENSE_END
