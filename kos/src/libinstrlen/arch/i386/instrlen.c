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
#ifndef GUARD_LIBINSTRLEN_ARCH_I386_INSTRLEN_C
#define GUARD_LIBINSTRLEN_ARCH_I386_INSTRLEN_C 1

#include <hybrid/host.h>

#ifdef __x86_64__
#define LIBEMU86_CONFIG_WANT_64BIT 1
#define LIBEMU86_CONFIG_WANT_32BIT 1
#define LIBEMU86_CONFIG_WANT_16BIT 0
#else /* __x86_64__ */
#define LIBEMU86_CONFIG_WANT_64BIT 0
#define LIBEMU86_CONFIG_WANT_32BIT 1
#define LIBEMU86_CONFIG_WANT_16BIT 1
#endif /* !__x86_64__ */

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/atomic.h>

#include <kos/types.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include <libemu86/emu86.h>

#include "../../instrlen.h"

#ifndef __KERNEL__
#include <dlfcn.h>
#endif /* !__KERNEL__ */

#include "db.h"

DECL_BEGIN

#ifndef __KERNEL__
PRIVATE void *libemu86 = NULL;
PRIVATE void *CC open_libemu86(void) {
	void *result;
	result = ATOMIC_READ(libemu86);
	if (!result) {
		result = dlopen(LIBEMU86_LIBRARY_NAME, RTLD_LOCAL);
		if likely(result) {
			void *new_result;
			new_result = ATOMIC_CMPXCH_VAL(libemu86, NULL, result);
			if unlikely(new_result != NULL) {
				dlclose(result);
				result = new_result;
			}
		}
	}
	return result;
}

__attribute__((destructor))
PRIVATE void CC close_libemu86(void) {
	if (libemu86)
		dlclose(libemu86);
}

#define emu86_opcode_decode (*pdyn_emu86_opcode_decode)
#define emu86_modrm_decode  (*pdyn_emu86_modrm_decode)
PRIVATE PEMU86_OPCODE_DECODE pdyn_emu86_opcode_decode = NULL;
PRIVATE PEMU86_MODRM_DECODE pdyn_emu86_modrm_decode = NULL;

PRIVATE bool CC libemu86_init(void) {
	void *mod;
	if (pdyn_emu86_opcode_decode)
		return true;
	mod = open_libemu86();
	if unlikely(!mod)
		return false;
	*(void **)&pdyn_emu86_modrm_decode = dlsym(mod, "emu86_modrm_decode");
	if unlikely(!pdyn_emu86_modrm_decode)
		return false;
	COMPILER_WRITE_BARRIER();
	*(void **)&pdyn_emu86_opcode_decode = dlsym(mod, "emu86_opcode_decode");
	return pdyn_emu86_opcode_decode != NULL;
}
#endif /* !__KERNEL__ */


/* Return a pointer to the next instruction following opcode#8f */
PRIVATE ATTR_NOINLINE ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC succ_8f)(byte_t *pc_after_8f, emu86_opflags_t op_flags) {
	uint8_t opcode;
	uint16_t vex;
	byte_t *result;
	struct emu86_modrm modrm;
	/* Firstly, try to decode a modr/m tail and deal with 8f/0 being a pop-instruction */
	result = emu86_modrm_decode(pc_after_8f, &modrm, op_flags);
	if (modrm.mi_reg == 0)
		return result; /* 8f/0: pop(w|l|q) r/m(16|32|64) */
	/* XOP instruction */
	result = pc_after_8f;
	vex = *result++;
	vex <<= 8;
	vex |= *result++;
#if 0 /* Not needed */
	op_flags |= EMU86_F_HASVEX;
	if (!(vex & EMU86_VEX3B_R))
		op_flags |= EMU86_F_REX_R;
	if (!(vex & EMU86_VEX3B_X))
		op_flags |= EMU86_F_REX_X;
	if (!(vex & EMU86_VEX3B_B))
		op_flags |= EMU86_F_REX_B;
	if (vex & EMU86_VEX3B_L)
		op_flags |= 1 << EMU86_F_VEX_LL_S;
	if (vex & EMU86_VEX3B_W)
		op_flags |= EMU86_F_VEX_W;
	op_flags |= ((~vex & EMU86_VEX3B_VVVV_M) >> EMU86_VEX3B_VVVV_S) << EMU86_F_VEX_VVVVV_S;
	switch (vex & EMU86_VEX3B_PP_M) {
	case 0x01 << EMU86_VEX3B_PP_S: op_flags |= EMU86_F_OP16; break;  /* same as 0x66 prefix */
	case 0x02 << EMU86_VEX3B_PP_S: op_flags |= EMU86_F_REP; break;   /* same as 0xf3 prefix */
	case 0x03 << EMU86_VEX3B_PP_S: op_flags |= EMU86_F_REPNE; break; /* same as 0xf2 prefix */
	default: break;
	}
#endif
	/* The actual instruction opcode byte */
	opcode = *result++;
	/* NOTE: The  behavior of  undefined opcodes  if assumed,  and inferred from
	 *       likely correct patterns in how AMD appears to allocate XOP opcodes. */
	switch (vex & EMU86_VEX3B_MMMMM_M) {

	case 0x8 << EMU86_VEX3B_MMMMM_S:
		if (opcode >= 0xc0)
			result += 1; /* All (defined) opcodes of this table+range have an "Ib"-operand (e.g. `vprotb') */
		break;

	case 0x9 << EMU86_VEX3B_MMMMM_S:
		/* No (defined) opcode of this table has any kind of immediate operand */
		break;

	case 0xa << EMU86_VEX3B_MMMMM_S:
		/* All (defined) opcodes of table have 32-bit immediate operands */
		result += 4;
		break;

	default:
		goto ud; /* Instructions from this opcode table aren't recognized! */
	}
	return result;
ud:
	return NULL;
}



/* Return a pointer to the successor/predecessor instruction of `pc',
 * assuming  that `pc'  points to  the start  of another instruction.
 * WARNING: These functions may trigger a segmentation fault when `pc' is an invalid pointer.
 * @param: isa: The ISA type (s.a. `instrlen_isa_from_Xcpustate()' or `INSTRLEN_ISA_DEFAULT')
 * @return: NULL: The pointed-to instruction wasn't recognized. */
INTERN ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_succ)(void const *pc,
                                       instrlen_isa_t isa) {
	byte_t *result;
	emu86_opcode_t opcode;
	emu86_opflags_t op_flags;
	unsigned int type;
	struct emu86_modrm modrm;
#if LIBEMU86_CONFIG_WANT_16BIT
#define IS_OP16() (!!(op_flags & EMU86_F_OP16) ^ !!EMU86_F_IS16(op_flags))
#define IS_AD16() (!!(op_flags & EMU86_F_AD16) ^ !!EMU86_F_IS16(op_flags))
#else /* LIBEMU86_CONFIG_WANT_16BIT */
#define IS_OP16() (op_flags & EMU86_F_OP16)
#define IS_AD16() (op_flags & EMU86_F_AD16)
#endif /* !LIBEMU86_CONFIG_WANT_16BIT */
#ifndef __KERNEL__
	if unlikely(!libemu86_init())
		return NULL;
#endif /* !__KERNEL__ */
	op_flags = instrlen_isa_to_emu86_opflags_t(isa);
	result   = emu86_opcode_decode((byte_t *)pc, &opcode, &op_flags);
	/* Make sure that the opcode isn't too great. */
	if (opcode >= NUMBER_OF_EXPLICITLY_DEFINED_OPCODES) {
#if NUMBER_OF_EXPLICITLY_DEFINED_OPCODES <= 0x2ff
		if (opcode <= 0x2ff) {
			/* All 0x0f3800-0x0f38ff opcodes encode to either
			 * I_RM  or  I_UD  (always use  I_RM  for these!) */
			type = COMMON_OPCODE_TYPE_0f38xx;
		} else
#endif /* NUMBER_OF_EXPLICITLY_DEFINED_OPCODES <= 0x2ff */
#if NUMBER_OF_EXPLICITLY_DEFINED_OPCODES <= 0x3ff
		if (opcode <= 0x3ff) {
			/* All 0x0f3a00-0x0f3aff opcodes encode to either
			 * I_RM1 or I_UD  (always use  I_RM1 for  these!) */
			type = COMMON_OPCODE_TYPE_0f3axx;
		} else
#endif /* NUMBER_OF_EXPLICITLY_DEFINED_OPCODES <= 0x3ff */
		{
			/* Shouldn't get here. (but since `emu86_opcode_decode()' is
			 * part of a different library, better be safe about  this!) */
			goto ud;
		}
	} else {
		/* Determine the type of instruction we're dealing with. */
		type = optypes[opcode >> 1];
		if (opcode & 1)
			type >>= 4;
		type &= 0xf;
	}
	/* switch on the type of instruction */
	switch (type) {

	case I_UD:
		/* Instruction is not defined */
		goto ud;

	case I_0:
		/* Instruction doesn't have any sort of tail */
		break;

	case I_1:
		/* Instruction has a 1-byte tail */
		result += 1;
		break;

	case I_2:
		/* Instruction has a 2-byte tail */
		result += 2;
		break;

	case I_3:
		/* Instruction has a 3-byte tail */
		result += 3;
		break;

#ifdef __x86_64__
	case I_248:
		/* Instruction has a 2-, 4- or 8-byte tail (based on EMU86_F_OP16 and EMU86_F_REX_W) */
		if (op_flags & EMU86_F_REX_W) {
			result += 8; /* 64-bit immediate operand */
			break;
		}
		ATTR_FALLTHROUGH
#endif /* __x86_64__ */
	case I_24:
		/* Instruction has a 2- or 4-byte tail (based on EMU86_F_OP16) */
		if (IS_OP16()) {
			result += 2; /* 16-bit immediate operand */
		} else {
			result += 4; /* 32-bit immediate operand */
		}
		break;

	case I_RM:      /* Instruction has a modr/m tail */
	case I_RM1:     /* Instruction has a modr/m tail, followed by a 1-byte immediate operand */
	case I_RM24:    /* Instruction has a modr/m tail, followed by a 2- or 4-byte immediate operand (based on EMU86_F_OP16) */
	case I_RM1_01:  /* Instruction has a modr/m tail, followed by a 1-byte immediate operand when modrm.mi_reg in [0, 1] */
	case I_RM24_01: /* Instruction has a modr/m tail, followed by a 2- or 4-byte immediate operand (based on EMU86_F_OP16) when modrm.mi_reg in [0, 1] */
		/* Decode the modr/m tail. */
		result = emu86_modrm_decode(result, &modrm, op_flags);
		switch (type) {

		case I_RM: /* Instruction has a modr/m tail */
			break;

		case I_RM1:
			/* Instruction has a modr/m tail, followed by a 1-byte immediate operand */
handle_rm1:
			result += 1;
			break;

		case I_RM24:
			/* Instruction has a modr/m tail, followed by a 2- or 4-byte immediate operand (based on EMU86_F_OP16) */
handle_rm24:
			if (IS_OP16()) {
				result += 2; /* 16-bit immediate operand */
			} else {
				result += 4; /* 32-bit immediate operand */
			}
			break;

		case I_RM1_01:
			/* Instruction has a modr/m tail, followed by a 1-byte immediate operand when modrm.mi_reg in [0, 1] */
			if (modrm.mi_reg == 0 || modrm.mi_reg == 1)
				goto handle_rm1;
			break;

		case I_RM24_01:
			/* Instruction has a modr/m tail, followed by a 2- or 4-byte immediate operand (based on EMU86_F_OP16) when modrm.mi_reg in [0, 1] */
			if (modrm.mi_reg == 0 || modrm.mi_reg == 1)
				goto handle_rm24;
			break;

		default: __builtin_unreachable();
		}
		break;

	case I_AD24:
		/* Instruction has a 2- or 4-byte tail (based on EMU86_F_AD16) */
		if (IS_AD16()) {
			result += 2; /* 16-bit immediate operand */
		} else {
			result += 4; /* 32-bit immediate operand */
		}
		break;

	case I_AD46:
		/* Instruction has a 4- or 6-byte tail (based on EMU86_F_AD16) */
		if (IS_AD16()) {
			result += 4; /* 16+16-bit immediate operand */
		} else {
			result += 6; /* 32+16-bit immediate operand */
		}
		break;

	case I_SPEC:
		/* Determining this instruction's length requires special handling. (s.a. `IS_SPECIAL_INSTRUCTION()') */
#if SPECIAL_INSTRUCTION_COUNT != 1
#error "Exactly 1 special instruction should currently be defined: 0x8f"
#endif /* SPECIAL_INSTRUCTION_COUNT != 1 */
		assert(opcode == EMU86_OPCODE_ENCODE(0x8f));
		result = succ_8f(result, op_flags);
		break;

	default:
		__builtin_unreachable();
	}
	/* Return a pointer to the next program counter. */
	return result;
ud:
	return NULL;
}

DEFINE_PUBLIC_ALIAS(instruction_succ, libil_instruction_succ);

DECL_END

#endif /* !GUARD_LIBINSTRLEN_ARCH_I386_INSTRLEN_C */
