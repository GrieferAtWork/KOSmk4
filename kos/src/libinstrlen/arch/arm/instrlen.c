/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBINSTRLEN_ARCH_ARM_INSTRLEN_C
#define GUARD_LIBINSTRLEN_ARCH_ARM_INSTRLEN_C 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <arm-kos/libinstrlen/bits/isa.h>
#include <kos/except.h>
#include <kos/types.h>

#include <libinstrlen/instrlen.h>

#include "../../instrlen.h"

DECL_BEGIN

/* Return the length of an instruction that starts at `pc'
 * WARNING: This function may trigger a segmentation fault when `pc' is an invalid pointer.
 * @return: 0 : The pointed-to instruction wasn't recognized. */
INTERN ATTR_PURE WUNUSED size_t
NOTHROW_NCX(CC libil_instruction_length)(void const *pc, instrlen_isa_t isa) {
	uint16_t instruction;
	if (isa == INSTRLEN_ISA_ARM)
		return 4; /* ARM instructions are always 4 bytes */

	/* Special handling for thumb instructions
	 * From: >> A6.3 32-bit Thumb instruction encoding */
	instruction = *(uint16_t const *)pc;
	if ((instruction & 0x1800) == 0x0000)
		return 2; /* 2-byte thumb */
	return 4; /* 4-byte thumb */
}


/* Return a pointer to the successor/predecessor instruction of `pc',
 * assuming  that `pc'  points to  the start  of another instruction.
 * WARNING: These functions may trigger a segmentation fault when `pc' is an invalid pointer.
 * @param: isa: The ISA type (s.a. `instrlen_isa_from_Xcpustate()' or `INSTRLEN_ISA_DEFAULT')
 * @return: NULL: The pointed-to instruction wasn't recognized. */
INTERN ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_pred)(void const *pc, instrlen_isa_t isa) {
	uint16_t instruction;
	if (isa == INSTRLEN_ISA_ARM)
		return (byte_t *)pc - 4;

	NESTED_TRY {
		instruction = *(uint16_t const *)((byte_t *)pc - 4);
	} EXCEPT {
		if (!was_thrown(E_SEGFAULT))
			RETHROW();
		return (byte_t *)pc - 2;
	}
	if ((instruction & 0x1800) != 0x0000)
		return (byte_t *)pc - 4; /* 4-byte thumb */

	/* Instruction 4 bytes back wasn't a 32-bit thumb  instruction
	 * As such, it as well as whatever followed it, must have been
	 * a 16-bit-wide thumb instruction! */
	return (byte_t *)pc - 2; /* 2-byte thumb */
}

#define ARM_DEFAULT_ISA_LENGTH(isa) \
	((isa) == INSTRLEN_ISA_ARM ? 4 : 2)


/* Same as `instruction_(succ|pred)_nx', but return pc +/- 1 instead of NULL.
 * @param: isa: The ISA type (s.a. `instrlen_isa_from_Xcpustate()' or `INSTRLEN_ISA_DEFAULT') */
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_trysucc)(void const *pc, instrlen_isa_t isa) {
	byte_t *result;
	result = libil_instruction_succ_nx(pc, isa);
	if unlikely(!result)
		result = (byte_t *)pc + ARM_DEFAULT_ISA_LENGTH(isa);
	return result;
}
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_trypred)(void const *pc, instrlen_isa_t isa) {
	byte_t *result;
	result = libil_instruction_pred_nx(pc, isa);
	if unlikely(!result)
		result = (byte_t *)pc - ARM_DEFAULT_ISA_LENGTH(isa);
	return result;
}


DEFINE_PUBLIC_ALIAS(instruction_length, libil_instruction_length);
DEFINE_PUBLIC_ALIAS(instruction_pred, libil_instruction_pred);
DEFINE_PUBLIC_ALIAS(instruction_trysucc, libil_instruction_trysucc);
DEFINE_PUBLIC_ALIAS(instruction_trypred, libil_instruction_trypred);

DECL_END

#endif /* !GUARD_LIBINSTRLEN_ARCH_ARM_INSTRLEN_C */
