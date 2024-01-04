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

#include "string-util.h"

EMU86_INTELLISENSE_BEGIN(movs) {

#if EMU86_EMULATE_CONFIG_WANT_MOVS
#define DEFINE_MOVSn_TRANSFER(BWLQ, Nbits, Nbytes)      \
	EMU86_READ_USER_MEMORY(psi_addr, Nbytes);           \
	EMU86_WRITE_USER_MEMORY(pdi_addr, Nbytes);          \
	{                                                   \
		u##Nbits transfer_value;                        \
		transfer_value = EMU86_MEMREAD##BWLQ(psi_addr); \
		EMU86_MEMWRITE##BWLQ(pdi_addr, transfer_value); \
	}                                                   \
	if (EMU86_GETFLAGS() & EFLAGS_DF) {                 \
		psi -= Nbytes;                                  \
		pdi -= Nbytes;                                  \
	} else {                                            \
		psi += Nbytes;                                  \
		pdi += Nbytes;                                  \
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_MOVS */


	/* Temporary storage for the %(|e|r)si and %(|e|r)di registers. */
#if EMU86_EMULATE_CONFIG_WANT_MOVS
	EMU86_UREG_TYPE psi, pdi;
#endif /* EMU86_EMULATE_CONFIG_WANT_MOVS */

case EMU86_OPCODE_ENCODE(0xa4):
#if !EMU86_EMULATE_CONFIG_WANT_MOVS
case EMU86_OPCODE_ENCODE(0xa5):
#endif /* !EMU86_EMULATE_CONFIG_WANT_MOVS */
{
	/* A4     MOVSB     For legacy mode, Move byte from address DS:(E)SI to ES:(E)DI.
	 *                  For 64-bit mode  move byte from  address (R|E)SI to  (R|E)DI. */
	byte_t *psi_addr, *pdi_addr;
#if !EMU86_EMULATE_CONFIG_WANT_MOVS
	EMU86_UREG_TYPE psi, pdi;
#endif /* EMU86_EMULATE_CONFIG_WANT_MOVS */
	EMU86_PSIPDIn_LOAD_POINTERS(psi, pdi, psi_addr, pdi_addr,
	                            op_flags & EMU86_F_REP);
	(void)psi_addr;
	(void)pdi_addr;
#if EMU86_EMULATE_CONFIG_WANT_MOVS
	DEFINE_MOVSn_TRANSFER(B, 8, 1);
do_movs_save_pointer:
	EMU86_PSIPDIn_SAVE_POINTERS(psi, pdi, op_flags & EMU86_F_REP);
	/* Check for repeat */
	if (op_flags & EMU86_F_REP)
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MOVS */
#define MOVS_N_BYTES() \
	(tiny_opcode == EMU86_OPCODE_ENCODE(0xa6) ? 1 : IF_64BIT(IS_64BIT() ? 8 : ) !IS_16BIT() ? 4 : 2)
	EMU86_UNSUPPORTED_MEMACCESS(psi_addr, MOVS_N_BYTES(), true, false);
	EMU86_UNSUPPORTED_MEMACCESS(pdi_addr, MOVS_N_BYTES(), false, true);
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#undef MOVS_N_BYTES
#endif /* !EMU86_EMULATE_CONFIG_WANT_MOVS */
}


#if EMU86_EMULATE_CONFIG_WANT_MOVS
case EMU86_OPCODE_ENCODE(0xa5): {
	/*         A5     MOVSW     For legacy mode, move word from address DS:(E)SI to ES:(E)DI.
	 *                          For 64-bit  mode move  word at  address (R|E)SI  to  (R|E)DI.
	 *         A5     MOVSD     For legacy mode, move dword from address DS:(E)SI to ES:(E)DI.
	 *                          For 64-bit mode  move dword from  address (R|E)SI to  (R|E)DI.
	 * REX.W + A5     MOVSQ     Move qword from address (R|E)SI to (R|E)DI. */
	byte_t *psi_addr, *pdi_addr;
	EMU86_PSIPDIn_LOAD_POINTERS(psi, pdi, psi_addr, pdi_addr,
	                            op_flags & EMU86_F_REP);
	IF_64BIT(if (IS_64BIT()) {
		DEFINE_MOVSn_TRANSFER(Q, 64, 8);
	} else) if (!IS_16BIT()) {
		DEFINE_MOVSn_TRANSFER(L, 32, 4);
	} else {
		DEFINE_MOVSn_TRANSFER(W, 16, 2);
	}
	goto do_movs_save_pointer;
}
#endif /* EMU86_EMULATE_CONFIG_WANT_MOVS */

#undef DEFINE_MOVSn_TRANSFER

}
EMU86_INTELLISENSE_END
