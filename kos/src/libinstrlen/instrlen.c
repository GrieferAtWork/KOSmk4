/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBINSTRLEN_INSTRLEN_C
#define GUARD_LIBINSTRLEN_INSTRLEN_C 1

#include "instrlen.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/except.h>
#include <kos/types.h>

#include <stddef.h>

#include <libinstrlen/instrlen.h>

#ifdef __KERNEL__
#include <kernel/except.h>

#include <string.h>
#endif

DECL_BEGIN

/* Return a pointer to the successor/predecessor instruction of `pc',
 * assuming that `pc' points to the start of another instruction.
 * WARNING: These functions may trigger a segmentation fault when `pc' is an invalid pointer.
 * @return: NULL: The pointed-to instruction wasn't recognized. */
#ifdef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
INTERN ATTR_PURE WUNUSED void const *
(CC libil_instruction_succ)(void const *pc) {
	return (byte_t *)pc + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH;
}
INTERN ATTR_PURE WUNUSED void const *
(CC libil_instruction_pred)(void const *pc) {
	return (byte_t *)pc - LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH;
}
#elif defined(__i386__) || defined(__x86_64__)
#define INSTR_0       0x0 /* Normal, direct instruction */
#define INSTR_1B      0x1 /* 1 byte immediate. */
#define INSTR_2B      0x2 /* 2 byte immediate. */
#define INSTR_3B      0x3 /* 3 byte immediate. */
#define INSTR_24B     0x4 /* 2/4 byte immediate (based on OPFLAG_66 prefix). */
#define INSTR_248B    0x5 /* 2/4/8 byte immediate (based on OPFLAG_66 &  prefix). */
#define INSTR_46B     0x6 /* 4/6 byte immediate (based on OPFLAG_66 prefix). */
#define INSTR_RM_1B   0x7 /* modr/m operand + 1 byte immediate. */
#define INSTR_RM_24B  0x8 /* modr/m operand + 2/4 byte immediate (based on OPFLAG_67 prefix). */
#define INSTR_RM      0x9 /* modr/m operand. */
#define INSTR_RM0_1   0xa /* modr/m operand + 1 (if mod.reg == 0). */
#define INSTR_RM0_24  0xb /* modr/m operand + 2/4 (if mod.reg == 0) (based on OPFLAG_66 prefix). */
#define INSTR_RM_661  0xc /* modr/m operand + 1 (if 0x66 prefix is given). */
#define INSTR_UNDEF   0xf /* Undefined instruction */
#define PAIR(a,b)   ((a) | (b) << 4)
#include "x86.inl"
#undef PAIR

#define MODRM_MOD_MASK     0xc0 /* 0b11000000 */
#define MODRM_REG_MASK     0x38 /* 0b00111000 */
#define MODRM_RM_MASK      0x07 /* 0b00000111 */
#define MODRM_MOD_SHIFT    6
#define MODRM_REG_SHIFT    3
#define MODRM_RM_SHIFT     0
#define MODRM_GETMOD(x) (((x) & MODRM_MOD_MASK) >> MODRM_MOD_SHIFT)
#define MODRM_GETREG(x) (((x) & MODRM_REG_MASK) >> MODRM_REG_SHIFT)
#define MODRM_GETRM(x)  (((x) & MODRM_RM_MASK) >> MODRM_RM_SHIFT)

#define R_EAX     0 /* Accumulator. */
#define R_ECX     1 /* Counter register. */
#define R_EDX     2 /* General purpose d-register. */
#define R_EBX     3 /* General purpose b-register. */
#define R_ESP     4 /* Stack pointer. */
#define R_EBP     5 /* Stack base pointer. */
#define R_ESI     6 /* Source pointer. */
#define R_EDI     7 /* Destination pointer. */

LOCAL NONNULL((1))
byte_t (CC skip_modrm)(byte_t **__restrict ppc) {
	byte_t op = *((*ppc)++);
	switch (op & MODRM_MOD_MASK) {

	case 0x0 << MODRM_MOD_SHIFT:
		/* R/M */
		if (MODRM_GETRM(op) == R_EBP) {
			(*ppc) += 4;
		} else if (MODRM_GETRM(op) == R_ESP) {
			(*ppc) += 1;
		}
		break;

	case 0x1 << MODRM_MOD_SHIFT:
		/* R/M + 1-byte offset */
		(*ppc) += 1;
		break;

	case 0x2 << MODRM_MOD_SHIFT:
		/* R/M + 4-byte offset */
		(*ppc) += 4;
		break;

	case 0x3 << MODRM_MOD_SHIFT:
		/* Register operand. */
		break;

	default: __builtin_unreachable();
	}
	return op;
}

INTERN ATTR_PURE WUNUSED void const *
(CC libil_instruction_succ)(void const *pc) {
	uint8_t const *my_itab;
	uint8_t op, *reader      = (uint8_t *)pc;
	uint8_t action, op_flags = 0;
#define OPFLAG_66   0x01
#define OPFLAG_67   0x02
#define OPFLAG_REXW 0x04
	my_itab = itab;
next_byte:
	op = *reader++;
	switch (op) {
#define VEX3B_R        0x8000 /* FLAG:  3-byte VEX.R */
#define VEX3B_X        0x4000 /* FLAG:  3-byte VEX.X */
#define VEX3B_B        0x2000 /* FLAG:  3-byte VEX.B */
#define VEX3B_M_MMMM_M 0x1f00 /* MASK:  3-byte VEX.M_MMMM */
#define VEX3B_M_MMMM_S      8 /* SHIFT: 3-byte VEX.M_MMMM */
#define VEX3B_W        0x0080 /* FLAG:  3-byte VEX.B */
#define VEX3B_VVVV_M   0x0078 /* MASK:  3-byte VEX.VVVV */
#define VEX3B_VVVV_S        3 /* SHIFT: 3-byte VEX.VVVV */
#define VEX3B_L        0x0004 /* FLAG:  3-byte VEX.L */
#define VEX3B_PP_M     0x0003 /* MASK:  3-byte VEX.PP */
#define VEX3B_PP_S          0 /* SHIFT: 3-byte VEX.PP */

	/* VEX Prefix */
	case 0xc4: { /* 3-byte form */
		uint16_t vex;
		vex = *reader++;
		vex <<= 8;
		vex |= *reader++;
#ifndef __x86_64__
		if (!(vex & (VEX3B_R | VEX3B_X))) {
			reader -= 2;
			/*op = 0xc4;*/
			break;
		}
#endif
		if ((vex & VEX3B_PP_M) == (0x01 << VEX3B_PP_S))
			op_flags |= OPFLAG_66;
		switch (vex & VEX3B_M_MMMM_M) {
		case 0x1 << VEX3B_M_MMMM_S: my_itab = itab_0f; break;
		case 0x2 << VEX3B_M_MMMM_S: my_itab = itab_0f38; break;
		case 0x3 << VEX3B_M_MMMM_S: my_itab = itab_0f3a; break;
		default: return NULL;
		}
		/* The actual instruction opcode byte */
		op = *reader++;
	}	break;

#define VEX2B_R      0x80 /* FLAG:  2-byte VEX.R */
#define VEX2B_VVVV_M 0x78 /* MASK:  2-byte VEX.VVVV */
#define VEX2B_1      0x40 /* FLAG:  Must be one (if 0, not a prefix + generate opcode `0xc5') */
#define VEX2B_VVVV_S    3 /* SHIFT: 2-byte VEX.VVVV */
#define VEX2B_L      0x04 /* FLAG:  2-byte VEX.L */
#define VEX2B_PP_M   0x03 /* MASK:  2-byte VEX.PP */
#define VEX2B_PP_S      0 /* SHIFT: 2-byte VEX.PP */

	/* VEX Prefix */
	case 0xc5: /* 2-byte form */
		op = *reader++;
#ifndef __x86_64__
		if (!(op & (VEX2B_R | VEX2B_1))) {
			--reader;
			op = 0xc5;
			break;
		}
#endif
		if ((op & VEX3B_PP_M) == (0x01 << VEX3B_PP_S))
			op_flags |= OPFLAG_66;
		goto next_byte;

	/* Prefix bytes */
	case 0x66: op_flags |= OPFLAG_66; goto next_byte;
	case 0x67: op_flags |= OPFLAG_67; goto next_byte;
	case 0xf0: goto next_byte;
	case 0xf2: goto next_byte;
	case 0xf3: goto next_byte;
#ifdef __x86_64__
	case 0x40 ... 0x4f:
		if (op & 0x08)
			op_flags |= OPFLAG_REXW;
		goto next_byte;
#else
	case 0x26: goto next_byte;
	case 0x2e: goto next_byte;
	case 0x36: goto next_byte;
	case 0x3e: goto next_byte;
#endif
	case 0x64: goto next_byte;
	case 0x65: goto next_byte;
	case 0x0f:
		my_itab = itab_0f;
		op      = *reader++;
		if (op == 0x38) {
			my_itab = itab_0f38;
			op      = *reader++;
		} else if (op == 0x3a) {
			my_itab = itab_0f3a;
			op      = *reader++;
		}
		break;

	default: break;
	}
	action = my_itab[op >> 1];
	if (op & 1)
		action >>= 4;
	action &= 0xf;
	switch (action) {

	case INSTR_0:
		break;

	case INSTR_1B:
		reader += 1;
		break;

	case INSTR_2B:
		reader += 2;
		break;

	case INSTR_3B:
		reader += 3;
		break;

	case INSTR_24B:
		reader += op_flags & OPFLAG_66 ? 2 : 4;
		break;

	case INSTR_248B:
		reader += op_flags & OPFLAG_REXW ? 8 : op_flags & OPFLAG_66 ? 2 : 4;
		break;

	case INSTR_46B:
		reader += op_flags & OPFLAG_66 ? 4 : 6;
		break;

	case INSTR_RM0_1:
	case INSTR_RM0_24:
		op = skip_modrm(&reader);
		if (MODRM_GETREG(op) == 0) {
			if (action == INSTR_RM0_1)
				reader += 1;
			else {
				reader += op_flags & OPFLAG_66 ? 2 : 4;
			}
		}
		break;

	case INSTR_RM_1B:
	case INSTR_RM_24B:
	case INSTR_RM:
	case INSTR_RM_661:
		skip_modrm(&reader);
		if (action == INSTR_RM_1B)
			reader += 1;
		else if (action == INSTR_RM_24B)
			reader += op_flags & OPFLAG_67 ? 2 : 4;
		else if (action == INSTR_RM_661) {
			if (op_flags & OPFLAG_66)
				reader += 1;
		}
		break;

	default:
		return NULL;
	}
	return (void const *)reader;
}

PRIVATE ATTR_PURE WUNUSED void const *
(CC libil_instruction_pred_impl)(void const *pc) {
	byte_t *result;
	unsigned int i = 15; /* 15 is the max instruction length on X86 */
	do {
		result = (byte_t *)pc - i;
		if (libil_instruction_succ(result) == pc)
			goto done;
	} while (--i);
	result = NULL;
done:
	return (void const *)result;
}

/* # of instructions to unwind for the purpose of
 * verifying the program counter when walking backwards. */
#define LIBIL_PRED_VERIFY_DISTANCE 8


INTERN ATTR_PURE WUNUSED void const *
(CC libil_instruction_pred)(void const *pc) {
	void const *baseline, *result;
	unsigned int i;
	baseline = libil_instruction_pred_impl(pc);
	if unlikely(!baseline)
		return NULL;
	/* Go backwards up to `LIBIL_PRED_VERIFY_DISTANCE' by guessing the length of the instructions.
	 * Then, move forward until the given `pc' has once again been reached. */
	for (i = 1; i < LIBIL_PRED_VERIFY_DISTANCE; ++i) {
		void const *next;
		next = libil_instruction_pred_impl(baseline);
		if (!next)
			break;
		baseline = next;
	}
	for (;;) {
		void const *next;
		result = baseline;
		next = libil_instruction_succ(baseline);
		if (!next)
			next = (byte_t *)baseline + 1;
		if (next >= pc)
			break;
		baseline = next;
	}
	return result;
}
#else
#warning "Unsupported architecture"
INTERN ATTR_PURE WUNUSED void const *
(CC libil_instruction_succ)(void const *pc) {
	(void)pc;
	return NULL;
}
INTERN ATTR_PURE WUNUSED void const *
(CC libil_instruction_pred)(void const *pc) {
	(void)pc;
	return NULL;
}
#endif

#ifdef __KERNEL__
/* In kernel-space, also catch `E_WOULDBLOCK', as may be thrown by accessing
 * memory that hasn't been loaded while preemption was disabled (since the
 * kernel would not be allowed to block in such a scenario) */
#define WAS_SEGFAULT() (was_thrown(E_SEGFAULT) || was_thrown(E_WOULDBLOCK))
#else /* __KERNEL__ */
#define WAS_SEGFAULT() (was_thrown(E_SEGFAULT))
#endif /* !__KERNEL__ */

/* Same as above, but return pc +/- 1, and discard a SEGFAULT and restore any old
 * exception when `pc' is invalid invalid pointer, or when `arch_instruction_(curr|pred)'
 * would have returned `NULL'. */
INTERN ATTR_PURE WUNUSED void const *
NOTHROW(CC libil_instruction_trysucc)(void const *pc) {
#ifdef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
	return (byte_t *)pc + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH;
#else /* LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */
	void const *result;
#ifdef __KERNEL__
	struct exception_info old_info;
	memcpy(&old_info, &THIS_EXCEPTION_INFO, sizeof(struct exception_info));
#endif
	TRY {
		result = libil_instruction_succ(pc);
	} EXCEPT {
		if (!WAS_SEGFAULT())
			RETHROW();
#ifdef __KERNEL__
		goto err_segfault;
#else
		result = NULL;
#endif
	}
	if unlikely(!result)
		result = (byte_t *)pc + 1;
	return result;
#ifdef __KERNEL__
err_segfault:
	memcpy(&THIS_EXCEPTION_INFO, &old_info, sizeof(struct exception_info));
	return (byte_t *)pc + 1;
#endif
#endif /* !LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */
}

INTERN ATTR_PURE WUNUSED void const *
NOTHROW(CC libil_instruction_trypred)(void const *pc) {
#ifdef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
	return (byte_t *)pc - LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH;
#else /* LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */
	void const *result;
#ifdef __KERNEL__
	struct exception_info old_info;
	memcpy(&old_info, &THIS_EXCEPTION_INFO, sizeof(struct exception_info));
#endif
	TRY {
		result = libil_instruction_pred(pc);
	} EXCEPT {
		if (!WAS_SEGFAULT())
			RETHROW();
#ifdef __KERNEL__
		goto err_segfault;
#else
		result = NULL;
#endif
	}
	if (!result)
		result = (byte_t *)pc - 1;
	return result;
#ifdef __KERNEL__
err_segfault:
	memcpy(&THIS_EXCEPTION_INFO, &old_info, sizeof(struct exception_info));
	return (byte_t *)pc - 1;
#endif
#endif /* !LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */
}

/* Return the length of an instruction that starts at `pc'
 * WARNING: This function may trigger a segmentation fault when `pc' is an invalid pointer.
 * @return: 0 : The pointed-to instruction wasn't recognized. */
INTERN ATTR_PURE WUNUSED size_t
(CC libil_instruction_length)(void const *pc) {
#ifdef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
	(void)pc;
	return LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH;
#else
	void const *endpc;
	endpc = libil_instruction_succ(pc);
	if (!endpc)
		return 0;
	return (size_t)((byte_t *)endpc - (byte_t *)pc);
#endif
}


DEFINE_PUBLIC_ALIAS(instruction_length, libil_instruction_length);
DEFINE_PUBLIC_ALIAS(instruction_succ, libil_instruction_succ);
DEFINE_PUBLIC_ALIAS(instruction_pred, libil_instruction_pred);
DEFINE_PUBLIC_ALIAS(instruction_trysucc, libil_instruction_trysucc);
DEFINE_PUBLIC_ALIAS(instruction_trypred, libil_instruction_trypred);

DECL_END

#endif /* !GUARD_LIBINSTRLEN_INSTRLEN_C */
