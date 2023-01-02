/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

#include "string-util.h"

EMU86_INTELLISENSE_BEGIN(cmps) {

#if EMU86_EMULATE_CONFIG_WANT_CMPS
#define DEFINE_CMPSn_COMPARE(bwlq, BWLQ, Nbits, Nbytes)      \
	EMU86_READ_USER_MEMORY(psi_addr, Nbytes);                \
	EMU86_READ_USER_MEMORY(pdi_addr, Nbytes);                \
	{                                                        \
		u##Nbits lhs, rhs;                                   \
		u32 eflags_addend;                                   \
		lhs = EMU86_MEMREAD##BWLQ(psi_addr);                 \
		rhs = EMU86_MEMREAD##BWLQ(pdi_addr);                 \
		COMPILER_READ_BARRIER();                             \
		eflags_addend = emu86_geteflags_cmp##bwlq(lhs, rhs); \
		EMU86_MSKFLAGS(~(EFLAGS_CF | EFLAGS_OF | EFLAGS_SF | \
		                 EFLAGS_ZF | EFLAGS_AF | EFLAGS_PF), \
		               eflags_addend);                       \
	}                                                        \
	if (EMU86_GETFLAGS() & EFLAGS_DF) {                      \
		psi -= Nbytes;                                       \
		pdi -= Nbytes;                                       \
	} else {                                                 \
		psi += Nbytes;                                       \
		pdi += Nbytes;                                       \
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPS */


	/* Temporary storage for the %(|e|r)si and %(|e|r)di registers. */
#if EMU86_EMULATE_CONFIG_WANT_CMPS
	EMU86_UREG_TYPE psi, pdi;
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPS */

case EMU86_OPCODE_ENCODE(0xa6):
#if !EMU86_EMULATE_CONFIG_WANT_CMPS
case EMU86_OPCODE_ENCODE(0xa7):
#endif /* !EMU86_EMULATE_CONFIG_WANT_CMPS */
{
	/* A6     CMPSB     For legacy mode, compare byte at address DS:(E)SI with byte at address ES:(E)DI;
	 *                  For 64-bit mode compare  byte at address (R|E)SI  with byte at address  (R|E)DI.
	 *                  The status flags are set accordingly. */
	byte_t *psi_addr, *pdi_addr;
#if !EMU86_EMULATE_CONFIG_WANT_CMPS
	EMU86_UREG_TYPE psi, pdi;
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPS */
	EMU86_PSIPDIn_LOAD_POINTERS(psi, pdi, psi_addr, pdi_addr,
	                            op_flags & (EMU86_F_REP | EMU86_F_REPNE));
	(void)psi_addr;
	(void)pdi_addr;
#if EMU86_EMULATE_CONFIG_WANT_CMPS
	DEFINE_CMPSn_COMPARE(b, B, 8, 1);
do_cmps_save_pointer:
	EMU86_PSIPDIn_SAVE_POINTERS(psi, pdi, op_flags & (EMU86_F_REP | EMU86_F_REPNE));
	/* Check for repeat */
	if (op_flags & EMU86_F_REP) {
		/* repe cmpsb   (repeat while equal) */
		if (EMU86_GETFLAGS() & EFLAGS_ZF)
			goto done_dont_set_pc; /* equal */
#define NEED_done_dont_set_pc
	} else if (op_flags & EMU86_F_REPNE) {
		/* repe cmpsb   (repeat while not equal) */
		if (!(EMU86_GETFLAGS() & EFLAGS_ZF))
			goto done_dont_set_pc; /* not equal */
#define NEED_done_dont_set_pc
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_CMPS */
#define CMPS_N_BYTES() \
	(tiny_opcode == EMU86_OPCODE_ENCODE(0xa6) ? 1 : IF_64BIT(IS_64BIT() ? 8 : ) !IS_16BIT() ? 4 : 2)
	EMU86_UNSUPPORTED_MEMACCESS(psi_addr, CMPS_N_BYTES(), true, false);
	EMU86_UNSUPPORTED_MEMACCESS(pdi_addr, CMPS_N_BYTES(), true, false);
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#undef CMPS_N_BYTES
#endif /* !EMU86_EMULATE_CONFIG_WANT_CMPS */
}


#if EMU86_EMULATE_CONFIG_WANT_CMPS
case EMU86_OPCODE_ENCODE(0xa7): {
	/*         A7     CMPSW     For legacy mode, compare word at address DS:(E)SI with word at address ES:(E)DI;
	 *                          For 64-bit mode compare  word at address (R|E)SI  with word at address  (R|E)DI.
	 *                          The status flags are set accordingly.
	 *         A7     CMPSD     For legacy mode, compare dword at address DS:(E)SI with dword at address ES:(E)DI;
	 *                          For 64-bit mode compare  dword at address (R|E)SI  with dword at address  (R|E)DI.
	 *                          The status flags are set accordingly.
	 * REX.W + A7     CMPSQ     Compares quadword at address (R|E)SI with quadword at address (R|E)DI and sets
	 *                          the status flags accordingly. */
	byte_t *psi_addr, *pdi_addr;
	EMU86_PSIPDIn_LOAD_POINTERS(psi, pdi, psi_addr, pdi_addr,
	                            op_flags & (EMU86_F_REP | EMU86_F_REPNE));
	IF_64BIT(if (IS_64BIT()) {
		DEFINE_CMPSn_COMPARE(q, Q, 64, 8);
	} else) if (!IS_16BIT()) {
		DEFINE_CMPSn_COMPARE(l, L, 32, 4);
	} else {
		DEFINE_CMPSn_COMPARE(w, W, 16, 2);
	}
	goto do_cmps_save_pointer;
}
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPS */

#undef DEFINE_CMPSn_COMPARE

}
EMU86_INTELLISENSE_END
