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

EMU86_INTELLISENSE_BEGIN(mov_moffs) {


#ifdef EMU86_GETSEGBASE_IS_NOOP_ALL
#define SEGMENT_ADDR_EX(segment_regno, offset) (byte_t *)(uintptr_t)(offset)
#elif defined(EMU86_GETSEGBASE_IS_NOOP_ANY)
#define SEGMENT_ADDR_EX(segment_regno, offset) \
	(EMU86_GETSEGBASE_IS_NOOP(segment_regno) \
	 ? (byte_t *)(uintptr_t)(offset)         \
	 : EMU86_SEGADDR((uintptr_t)EMU86_GETSEGBASE(segment_regno), (uintptr_t)(offset)))
#else /* EMU86_GETSEGBASE_IS_NOOP */
#define SEGMENT_ADDR_EX(segment_regno, offset) \
	EMU86_SEGADDR((uintptr_t)EMU86_GETSEGBASE(segment_regno), (uintptr_t)(offset))
#endif /* !EMU86_GETSEGBASE_IS_NOOP */
#define SEGMENT_ADDR(offset)                   \
	SEGMENT_ADDR_EX(EMU86_F_HASSEG(op_flags)   \
	                ? EMU86_F_SEGREG(op_flags) \
	                : EMU86_R_DS,              \
	                offset)




#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS
case EMU86_OPCODE_ENCODE(0xa0): {
	/* A0      MOV AL,moffs8*      Move byte at (seg:offset) to AL */
	byte_t *addr;
	u32 offset;
#if EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS
	u8 value;
#endif /* EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */
	if (!!EMU86_F_IS16(op_flags) ^ !!(op_flags & EMU86_F_AD16)) {
		offset = UNALIGNED_GETLE16(pc);
		pc += 2;
	} else {
		offset = UNALIGNED_GETLE32(pc);
		pc += 4;
	}
	addr = SEGMENT_ADDR(offset);
	(void)addr;
#if EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS
	EMU86_READ_USER_MEMORY(addr, 1);
	value = EMU86_MEMREADB(addr);
	EMU86_SETAL(value);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */
	EMU86_UNSUPPORTED_MEMACCESS(addr, 1, true, false);
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS
case EMU86_OPCODE_ENCODE(0xa1): {
	/* A1      MOV AX,moffs16*      Move word at (seg:offset) to AX */
	/* A1      MOV EAX,moffs32*     Move doubleword at (seg:offset) to EAX */
	/* A1      MOV RAX,moffs32*     Move quadword at (seg:offset) to RAX */
	byte_t *addr;
	u32 offset;
	if (!!EMU86_F_IS16(op_flags) ^ !!(op_flags & EMU86_F_AD16)) {
		offset = UNALIGNED_GETLE16(pc);
		pc += 2;
	} else {
		offset = UNALIGNED_GETLE32(pc);
		pc += 4;
	}
	addr = SEGMENT_ADDR(offset);
	(void)addr;
#if EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		EMU86_READ_USER_MEMORY(addr, 8);
		value = EMU86_MEMREADQ(addr);
		EMU86_SETRAX(value);
	} else) if (!IS_16BIT()) {
		u32 value;
		EMU86_READ_USER_MEMORY(addr, 4);
		value = EMU86_MEMREADL(addr);
		EMU86_SETEAX(value);
	} else {
		u16 value;
		EMU86_READ_USER_MEMORY(addr, 2);
		value = EMU86_MEMREADW(addr);
		EMU86_SETAX(value);
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */
	EMU86_UNSUPPORTED_MEMACCESS(addr, IF_64BIT(IS_64BIT() ? 8 :) !IS_16BIT() ? 4 : 2, true, false);
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS
case EMU86_OPCODE_ENCODE(0xa2): {
	/* A2      MOV moffs8*,AL      Move AL to (seg:offset) */
	byte_t *addr;
	u32 offset;
#if EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS
	u8 value;
#endif /* EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */
	if (!!EMU86_F_IS16(op_flags) ^ !!(op_flags & EMU86_F_AD16)) {
		offset = UNALIGNED_GETLE16(pc);
		pc += 2;
	} else {
		offset = UNALIGNED_GETLE32(pc);
		pc += 4;
	}
	addr = SEGMENT_ADDR(offset);
	(void)addr;
#if EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS
	EMU86_WRITE_USER_MEMORY(addr, 1);
	value = EMU86_GETAL();
	EMU86_MEMWRITEB(addr, value);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */
	EMU86_UNSUPPORTED_MEMACCESS(addr, 1, false, true);
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS
case EMU86_OPCODE_ENCODE(0xa3): {
	/* A3      MOV moffs16*,AX      Move AX to word at (seg:offset) */
	/* A3      MOV moffs32*,EAX     Move EAX to doubleword at (seg:offset) */
	/* A3      MOV moffs64*,RAX     Move RAX to quadword at (seg:offset) */
	byte_t *addr;
	u32 offset;
	if (!!EMU86_F_IS16(op_flags) ^ !!(op_flags & EMU86_F_AD16)) {
		offset = UNALIGNED_GETLE16(pc);
		pc += 2;
	} else {
		offset = UNALIGNED_GETLE32(pc);
		pc += 4;
	}
	addr = SEGMENT_ADDR(offset);
	(void)addr;
#if EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		EMU86_WRITE_USER_MEMORY(addr, 8);
		value = EMU86_GETRAX();
		EMU86_MEMWRITEQ(addr, value);
	} else) if (!IS_16BIT()) {
		u32 value;
		EMU86_WRITE_USER_MEMORY(addr, 4);
		value = EMU86_GETEAX();
		EMU86_MEMWRITEL(addr, value);
	} else {
		u16 value;
		EMU86_WRITE_USER_MEMORY(addr, 2);
		value = EMU86_GETAX();
		EMU86_MEMWRITEW(addr, value);
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */
	EMU86_UNSUPPORTED_MEMACCESS(addr, IF_64BIT(IS_64BIT() ? 8 :) !IS_16BIT() ? 4 : 2, false, true);
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS */

#undef SEGMENT_ADDR
#undef SEGMENT_ADDR_EX

}
EMU86_INTELLISENSE_END
